/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFImpl_ZFLua.h"
#include "ZFImpl_ZFLua_metatable.h"

#include "ZFCore/ZFSTLWrapper/zfstl_string.h"
#include "ZFCore/ZFSTLWrapper/zfstl_vector.h"
#include "ZFCore/ZFSTLWrapper/zfstl_map.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFImpl_ZFLua_luaStateHolder, ZFLevelAppEssential)
{
    L = ZFImpl_ZFLua_luaOpen();
    ZFImpl_ZFLua_luaStateAttach(L);
}
ZF_GLOBAL_INITIALIZER_DESTROY(ZFImpl_ZFLua_luaStateHolder)
{
    ZFImpl_ZFLua_luaStateDetach(L);
    ZFImpl_ZFLua_luaClose(L);
}
lua_State *L;
ZF_GLOBAL_INITIALIZER_END(ZFImpl_ZFLua_luaStateHolder)
lua_State *_ZFP_ZFImpl_ZFLua_luaState(void)
{
    return ZF_GLOBAL_INITIALIZER_INSTANCE(ZFImpl_ZFLua_luaStateHolder)->L;
}

// ============================================================
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFImpl_ZFLua_luaStateGlobalHolder, ZFLevelZFFrameworkLow)
{
}
zfstlmap<lua_State *, zfbool> attachedState;
ZFCoreArrayPOD<lua_State *> attachedStateList;
ZFCoreArrayPOD<ZFImpl_ZFLua_ImplSetupCallback> setupAttach;
ZFCoreArrayPOD<ZFImpl_ZFLua_ImplSetupCallback> setupDetach;
ZF_GLOBAL_INITIALIZER_END(ZFImpl_ZFLua_luaStateGlobalHolder)

void ZFImpl_ZFLua_luaStateAttach(ZF_IN lua_State *L)
{
    zfCoreAssert(L != zfnull);
    zfCoreMutexLocker();

    ZF_GLOBAL_INITIALIZER_CLASS(ZFImpl_ZFLua_luaStateGlobalHolder) *d
        = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFImpl_ZFLua_luaStateGlobalHolder);

    zfCoreAssertWithMessageTrim(d->attachedState.find(L) == d->attachedState.end(),
        zfTextA("[ZFImpl_ZFLua_luaStateAttach] lua state %p already attached"),
        L);
    d->attachedState[L] = zftrue;
    d->attachedStateList.add(L);

    ZFImpl_ZFLua_luaClassRegister<zfautoObject>(L, zfText("zfautoObject"));

    // zfnull
    zfclassNotPOD _ZFP_ZFImpl_ZFLua_zfnullHolder
    {
    public:
        static zfautoObject get_zfnull(void)
        {
            return zfautoObjectNull();
        }
    };
    ZFImpl_ZFLua_luaFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_zfnull"), _ZFP_ZFImpl_ZFLua_zfnullHolder::get_zfnull);
    ZFImpl_ZFLua_execute(L, zfText(
            "zfnull = _ZFP_ZFImpl_ZFLua_zfnull()\n"
        ));

    // each impl setup callback
    for(zfindex i = 0; i < d->setupAttach.count(); ++i)
    {
        d->setupAttach[i](L);
    }
}
void ZFImpl_ZFLua_luaStateDetach(ZF_IN lua_State *L)
{
    zfCoreMutexLocker();

    ZF_GLOBAL_INITIALIZER_CLASS(ZFImpl_ZFLua_luaStateGlobalHolder) *d
        = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFImpl_ZFLua_luaStateGlobalHolder);

    zfCoreAssertWithMessageTrim(d->attachedState.find(L) != d->attachedState.end(),
        zfTextA("[ZFImpl_ZFLua_luaStateDetach] lua state %p not attached"),
        L);

    // each impl setup callback
    for(zfindex i = 0; i < d->setupDetach.count(); ++i)
    {
        d->setupDetach[i](L);
    }

    d->attachedState.erase(L);
    d->attachedStateList.removeElement(L);
}
const ZFCoreArrayPOD<lua_State *> &ZFImpl_ZFLua_luaStateAttached(void)
{
    return ZF_GLOBAL_INITIALIZER_INSTANCE(ZFImpl_ZFLua_luaStateGlobalHolder)->attachedStateList;
}

// ============================================================
void ZFImpl_ZFLua_implSetupCallbackRegister(ZF_IN ZFImpl_ZFLua_ImplSetupCallback setupAttachCallback,
                                            ZF_IN ZFImpl_ZFLua_ImplSetupCallback setupDetachCallback)
{
    zfCoreMutexLocker();

    ZF_GLOBAL_INITIALIZER_CLASS(ZFImpl_ZFLua_luaStateGlobalHolder) *d
        = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFImpl_ZFLua_luaStateGlobalHolder);
    d->setupAttach.add(setupAttachCallback);
    d->setupDetach.add(setupDetachCallback);
}
void ZFImpl_ZFLua_implSetupCallbackUnregister(ZF_IN ZFImpl_ZFLua_ImplSetupCallback setupAttachCallback,
                                              ZF_IN ZFImpl_ZFLua_ImplSetupCallback setupDetachCallback)
{
    zfCoreMutexLocker();

    ZF_GLOBAL_INITIALIZER_CLASS(ZFImpl_ZFLua_luaStateGlobalHolder) *d
        = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFImpl_ZFLua_luaStateGlobalHolder);
    d->setupAttach.removeElement(setupAttachCallback);
    d->setupDetach.removeElement(setupDetachCallback);
}

// ============================================================
void ZFImpl_ZFLua_implSetupScope(ZF_IN_OUT lua_State *L, ZF_IN const zfchar *scopeName)
{
    const zfchar *scopeNameList[2] = {scopeName, zfnull};
    ZFImpl_ZFLua_implSetupScope(L, scopeNameList);
}
void ZFImpl_ZFLua_implSetupScope(ZF_IN_OUT lua_State *L, ZF_IN const zfchar **scopeNameList)
{
    zfstring code;
    for(zfindex i = 0; *scopeNameList != zfnull; ++scopeNameList, ++i)
    {
        zfstringAppend(code, zfText(
                "%s = '%s'\n"
                "local tbl = debug.getmetatable(%s)\n"
                "tbl.__index = function(scope, k)\n"
                "    return function(...)\n"
                "        return zfl_callStatic2(scope, k, ...)\n"
                "    end\n"
                "end\n"
                "tbl.__call = function(scope)\n"
                "    return zfAlloc(scope)\n"
                "end\n"
                "debug.setmetatable(%s, tbl)\n"
            ), *scopeNameList, *scopeNameList, *scopeNameList, *scopeNameList);
        if(i >= 100)
        {
            ZFImpl_ZFLua_execute(L, code);
            code.removeAll();
            i = 0;
        }
    }
    if(!code.isEmpty())
    {
        ZFImpl_ZFLua_execute(L, code);
    }
}
void ZFImpl_ZFLua_implSetupObject(ZF_IN_OUT lua_State *L, ZF_IN_OPT zfint objIndex /* = -1 */)
{
    ZFImpl_ZFLua_implSetupObject_metatable(L, objIndex);
}

// ============================================================
ZFOBJECT_REGISTER(ZFImpl_ZFLua_UnknownParamHolder)

// ============================================================
static zfautoObject _ZFP_ZFImpl_ZFLua_implDispatchReturnValueNotSetInstance;
const zfautoObject &_ZFP_ZFImpl_ZFLua_implDispatchReturnValueNotSet(void)
{
    return _ZFP_ZFImpl_ZFLua_implDispatchReturnValueNotSetInstance;
}
zfclass _ZFP_I_ZFImpl_ZFLua_ImplDispatchReturnValueNotSet : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_I_ZFImpl_ZFLua_ImplDispatchReturnValueNotSet, ZFObject)
};
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(_ZFP_ZFImpl_ZFLua_implDispatchReturnValueNotSetInstanceInit, ZFLevelZFFrameworkLow)
{
    _ZFP_ZFImpl_ZFLua_implDispatchReturnValueNotSetInstance
        = zfautoObjectCreate(zflineAlloc(_ZFP_I_ZFImpl_ZFLua_ImplDispatchReturnValueNotSet));
}
ZF_GLOBAL_INITIALIZER_DESTROY(_ZFP_ZFImpl_ZFLua_implDispatchReturnValueNotSetInstanceInit)
{
    _ZFP_ZFImpl_ZFLua_implDispatchReturnValueNotSetInstance = zfautoObjectNull();
}
ZF_GLOBAL_INITIALIZER_END(_ZFP_ZFImpl_ZFLua_implDispatchReturnValueNotSetInstanceInit)

static zfstlmap<zfstlstringZ, zfstlmap<zfstlstringZ, zfstlvector<ZFImpl_ZFLua_ImplDispatchCallback> > > _ZFP_ZFImpl_ZFLua_implDispatchData;
void ZFImpl_ZFLua_implDispatchRegister(ZF_IN ZFImpl_ZFLua_ImplDispatchCallback invokerCallback,
                                       ZF_IN_OPT const zfchar *classOrNamespace /* = zfnull */,
                                       ZF_IN_OPT const zfchar *methodName /* = zfnull */)
{
    zfCoreAssert(invokerCallback != zfnull);
    zfCoreMutexLocker();

    if(classOrNamespace == zfnull
        || zfscmpTheSame(classOrNamespace, ZFLuaFuncNamespaceGlobal)
        || zfscmpTheSame(classOrNamespace, ZFMethodFuncNamespaceGlobal))
    {
        classOrNamespace = zfText("");
    }
    if(methodName == zfnull)
    {
        methodName = zfText("");
    }
    _ZFP_ZFImpl_ZFLua_implDispatchData[classOrNamespace][methodName].push_back(invokerCallback);
}
void ZFImpl_ZFLua_implDispatchUnregister(ZF_IN ZFImpl_ZFLua_ImplDispatchCallback invokerCallback,
                                         ZF_IN_OPT const zfchar *classOrNamespace /* = zfnull */,
                                         ZF_IN_OPT const zfchar *methodName /* = zfnull */)
{
    zfCoreMutexLocker();

    if(classOrNamespace == zfnull
        || zfscmpTheSame(classOrNamespace, ZFLuaFuncNamespaceGlobal)
        || zfscmpTheSame(classOrNamespace, ZFMethodFuncNamespaceGlobal))
    {
        classOrNamespace = zfText("");
    }
    if(methodName == zfnull)
    {
        methodName = zfText("");
    }

    zfstlmap<zfstlstringZ, zfstlmap<zfstlstringZ, zfstlvector<ZFImpl_ZFLua_ImplDispatchCallback> > >::iterator methodIt = _ZFP_ZFImpl_ZFLua_implDispatchData.find(classOrNamespace);
    if(methodIt != _ZFP_ZFImpl_ZFLua_implDispatchData.end())
    {
        zfstlmap<zfstlstringZ, zfstlvector<ZFImpl_ZFLua_ImplDispatchCallback> >::iterator methodNameIt = methodIt->second.find(methodName);
        if(methodNameIt != methodIt->second.end())
        {
            for(zfstlsize i = 0; i < methodNameIt->second.size(); ++i)
            {
                if(methodNameIt->second[i] == invokerCallback)
                {
                    methodNameIt->second.erase(methodNameIt->second.begin() + i);
                    break;
                }
            }
            if(methodNameIt->second.empty())
            {
                methodIt->second.erase(methodNameIt);
            }
        }
        if(methodIt->second.empty())
        {
            _ZFP_ZFImpl_ZFLua_implDispatchData.erase(methodIt);
        }
    }
}
void ZFImpl_ZFLua_implDispatch(ZF_IN_OUT ZFImpl_ZFLua_ImplDispatchInfo &dispatchInfo)
{
    if(dispatchInfo.classOrNamespace == zfnull
        || zfscmpTheSame(dispatchInfo.classOrNamespace, ZFLuaFuncNamespaceGlobal)
        || zfscmpTheSame(dispatchInfo.classOrNamespace, ZFMethodFuncNamespaceGlobal))
    {
        dispatchInfo.classOrNamespace = zfText("");
    }
    if(dispatchInfo.methodName == zfnull)
    {
        dispatchInfo.methodName = zfText("");
    }

    zfstlmap<zfstlstringZ, zfstlmap<zfstlstringZ, zfstlvector<ZFImpl_ZFLua_ImplDispatchCallback> > >::iterator methodIt = _ZFP_ZFImpl_ZFLua_implDispatchData.find(dispatchInfo.classOrNamespace);
    if(methodIt != _ZFP_ZFImpl_ZFLua_implDispatchData.end())
    {
        // Scope::methodName
        zfstlmap<zfstlstringZ, zfstlvector<ZFImpl_ZFLua_ImplDispatchCallback> >::iterator methodNameIt = methodIt->second.find(dispatchInfo.methodName);
        if(methodNameIt != methodIt->second.end())
        {
            for(zfstlsize i = 0; i < methodNameIt->second.size(); ++i)
            {
                methodNameIt->second[i](dispatchInfo);
                if(dispatchInfo.dispatchResult != ZFImpl_ZFLua_ImplDispatchResultForward)
                {
                    return ;
                }
            }
        }

        // Scope::*
        methodNameIt = methodIt->second.find(zfText(""));
        if(methodNameIt != methodIt->second.end())
        {
            for(zfstlsize i = 0; i < methodNameIt->second.size(); ++i)
            {
                methodNameIt->second[i](dispatchInfo);
                if(dispatchInfo.dispatchResult != ZFImpl_ZFLua_ImplDispatchResultForward)
                {
                    return ;
                }
            }
        }
    }

    methodIt = _ZFP_ZFImpl_ZFLua_implDispatchData.find(ZFImpl_ZFLua_implDispatchAll);
    if(methodIt != _ZFP_ZFImpl_ZFLua_implDispatchData.end())
    {
        // *::methodName
        zfstlmap<zfstlstringZ, zfstlvector<ZFImpl_ZFLua_ImplDispatchCallback> >::iterator methodNameIt = methodIt->second.find(dispatchInfo.methodName);
        if(methodNameIt != methodIt->second.end())
        {
            for(zfstlsize i = 0; i < methodNameIt->second.size(); ++i)
            {
                methodNameIt->second[i](dispatchInfo);
                if(dispatchInfo.dispatchResult != ZFImpl_ZFLua_ImplDispatchResultForward)
                {
                    return ;
                }
            }
        }

        // *::*
        methodNameIt = methodIt->second.find(zfText(""));
        if(methodNameIt != methodIt->second.end())
        {
            for(zfstlsize i = 0; i < methodNameIt->second.size(); ++i)
            {
                methodNameIt->second[i](dispatchInfo);
                if(dispatchInfo.dispatchResult != ZFImpl_ZFLua_ImplDispatchResultForward)
                {
                    return ;
                }
            }
        }
    }
}

// ============================================================
zfbool ZFImpl_ZFLua_execute(ZF_IN lua_State *L,
                            ZF_IN const zfchar *buf,
                            ZF_IN_OPT zfindex bufLen /* = zfindexMax() */,
                            ZF_OUT_OPT zfstring *errHint /* = zfnull */)
{
    ZF_GLOBAL_INITIALIZER_CLASS(ZFImpl_ZFLua_luaStateGlobalHolder) *d
        = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFImpl_ZFLua_luaStateGlobalHolder);
    if(d->attachedState.find(L) == d->attachedState.end())
    {
        if(errHint != zfnull)
        {
            zfstringAppend(*errHint, zfText("lua_State %p not attached"), L);
        }
        return zffalse;
    }

    ZFSTRINGENCODING_ASSERT(ZFStringEncoding::e_UTF8)
    int error = (luaL_loadbuffer(L, buf, (bufLen == zfindexMax()) ? zfslen(buf) : bufLen, "") || lua_pcall(L, 0, 0, 0));
    if(error)
    {
        if(errHint != zfnull)
        {
            *errHint += zfsCoreA2Z(lua_tostring(L, -1));
            lua_pop(L, 1);
        }
#if ZF_ENV_DEBUG
        else
        {
            zfstring _tmp = zfsCoreA2Z(lua_tostring(L, -1));
            lua_pop(L, 1);
        }
#endif
        return zffalse;
    }
    return zftrue;
}

// ============================================================
// utils
void ZFImpl_ZFLua_luaObjectInfoT(ZF_OUT zfstring &ret,
                                 ZF_IN lua_State *L,
                                 ZF_IN zfint luaStackOffset,
                                 ZF_IN_OPT zfbool printLuaType /* = zffalse */)
{
    if(printLuaType)
    {
        ret += zfText("(");
        ret += zfsCoreA2Z(luaL_typename(L, luaStackOffset));
        ret += zfText(")");
    }

    switch(lua_type(L, luaStackOffset))
    {
        case LUA_TNIL:
            ret += zfText("<nil>");
            break;
        case LUA_TBOOLEAN:
            zfboolToString(ret, (lua_toboolean(L, luaStackOffset) != 0));
            break;
        case LUA_TLIGHTUSERDATA:
        case LUA_TUSERDATA:
            {
                zfautoObject obj;
                if(ZFImpl_ZFLua_toObject(obj, L, luaStackOffset))
                {
                    ZFObjectInfoT(ret, obj);
                }
                else
                {
                    zfsFromPointerT(ret, lua_topointer(L, luaStackOffset));
                }
            }
            break;
        case LUA_TNUMBER:
            zfdoubleToString(ret, (zfdouble)(zft_zfdouble)lua_tonumber(L, luaStackOffset));
            break;
        case LUA_TSTRING:
            ret += ZFStringA2Z(lua_tostring(L, luaStackOffset));
            break;
        case LUA_TTABLE:
            lua_getglobal(L, "zfl_tableInfo");
            if(lua_isnil(L, -1))
            {
                lua_pop(L, 1);
                zfsFromPointerT(ret, lua_topointer(L, luaStackOffset));
            }
            else
            {
                if(luaStackOffset < 0)
                {
                    lua_pushvalue(L, luaStackOffset - 1);
                }
                else
                {
                    lua_pushvalue(L, luaStackOffset);
                }
                lua_call(L, 1, 1);
                ret += ZFStringA2Z(lua_tostring(L, -1));
                lua_pop(L, 1);
            }
            break;
        case LUA_TFUNCTION:
            zfsFromPointerT(ret, lua_topointer(L, luaStackOffset));
            break;
        case LUA_TTHREAD:
            zfsFromPointerT(ret, lua_topointer(L, luaStackOffset));
            break;
        default:
            ret += zfText("<Unknown>");
            break;
    }
}
zfbool ZFImpl_ZFLua_toObject(ZF_OUT zfautoObject &param,
                             ZF_IN lua_State *L,
                             ZF_IN zfint luaStackOffset)
{
    if(lua_isuserdata(L, luaStackOffset))
    {
        param = ZFImpl_ZFLua_luaGet(L, luaStackOffset);
        return zftrue;
    }
    else
    {
        return zffalse;
    }
}

zfbool ZFImpl_ZFLua_toValue(ZF_IN_OUT zfstring &s,
                            ZF_IN lua_State *L,
                            ZF_IN zfint luaStackOffset,
                            ZF_IN_OPT zfbool allowEmpty /* = zffalse */)
{
    if(lua_isstring(L, luaStackOffset))
    {
        s += zfsCoreA2Z(lua_tostring(L, luaStackOffset));
        return zftrue;
    }
    if(!lua_isuserdata(L, luaStackOffset))
    {
        return zffalse;
    }

    zfautoObject const &param = ZFImpl_ZFLua_luaGet(L, luaStackOffset);
    if(param == zfautoObjectNull())
    {
        return allowEmpty;
    }

    ZFValue *v = ZFCastZFObject(ZFValue *, param);
    if(v != zfnull)
    {
        if(v->valueType() == ZFValueType::e_serializableData)
        {
            return zffalse;
        }
        v->valueStringT(s);
        return zftrue;
    }

    ZFPropertyTypeWrapper *wrapper = ZFCastZFObject(ZFPropertyTypeWrapper *, param);
    if(wrapper != zfnull)
    {
        wrapper->wrappedValueToString(s);
        return zftrue;
    }

    return zffalse;
}

zfbool ZFImpl_ZFLua_toString(ZF_IN_OUT zfstring &s,
                             ZF_IN lua_State *L,
                             ZF_IN zfint luaStackOffset,
                             ZF_IN_OPT zfbool allowEmpty /* = zffalse */)
{
    if(lua_isstring(L, luaStackOffset))
    {
        s += zfsCoreA2Z(lua_tostring(L, luaStackOffset));
        return zftrue;
    }
    if(!lua_isuserdata(L, luaStackOffset))
    {
        return zffalse;
    }

    zfautoObject const &param = ZFImpl_ZFLua_luaGet(L, luaStackOffset);
    if(param == zfautoObjectNull())
    {
        return allowEmpty;
    }
    else if(param.toObject()->classData()->classIsTypeOf(ZFString::ClassData()))
    {
        ZFString *t = param.to<ZFString *>();
        if(t != zfnull)
        {
            s += t->stringValue();
        }
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfstring::ClassData()))
    {
        s += param.to<v_zfstring *>()->zfv;
        return zftrue;
    }
    else
    {
        return zffalse;
    }
}

zfbool ZFImpl_ZFLua_toNumber(ZF_OUT zfautoObject &ret,
                             ZF_IN lua_State *L,
                             ZF_IN zfint luaStackOffset,
                             ZF_IN_OPT zfbool allowEmpty /* = zffalse */)
{
    int success = 0;
    lua_Number num = lua_tonumberx(L, luaStackOffset, &success);
    if(success)
    {
        ret = ZFValue::doubleValueCreate((zfdouble)num);
        return zftrue;
    }
    if(!lua_isuserdata(L, luaStackOffset))
    {
        return zffalse;
    }

    zfautoObject const &param = ZFImpl_ZFLua_luaGet(L, luaStackOffset);
    if(param == zfautoObjectNull())
    {
        if(allowEmpty)
        {
            ret = ZFValue::intValueCreate(0);
            return zftrue;
        }
        else
        {
            return zffalse;
        }
    }
    else if(param.toObject()->classData()->classIsTypeOf(ZFValue::ClassData()))
    {
        ret = param;
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfbool::ClassData()))
    {
        ret = ZFValue::boolValueCreate(param.to<v_zfbool *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfindex::ClassData()))
    {
        ret = ZFValue::indexValueCreate(param.to<v_zfindex *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfint::ClassData()))
    {
        ret = ZFValue::intValueCreate(param.to<v_zfint *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfuint::ClassData()))
    {
        ret = ZFValue::unsignedIntValueCreate(param.to<v_zfuint *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zffloat::ClassData()))
    {
        ret = ZFValue::floatValueCreate(param.to<v_zffloat *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfdouble::ClassData()))
    {
        ret = ZFValue::doubleValueCreate(param.to<v_zfdouble *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zflongdouble::ClassData()))
    {
        ret = ZFValue::longDoubleValueCreate(param.to<v_zflongdouble *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfbyte::ClassData()))
    {
        ret = ZFValue::unsignedIntValueCreate((zfuint)param.to<v_zfbyte *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zftimet::ClassData()))
    {
        ret = ZFValue::timeValueCreate(param.to<v_zftimet *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfflags::ClassData()))
    {
        ret = ZFValue::flagsValueCreate(param.to<v_zfflags *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfidentity::ClassData()))
    {
        ret = ZFValue::identityValueCreate(param.to<v_zfidentity *>()->zfv);
        return zftrue;
    }
    else
    {
        return zffalse;
    }
}
zfbool ZFImpl_ZFLua_toNumber(ZF_OUT lua_Number &ret,
                             ZF_IN lua_State *L,
                             ZF_IN zfint luaStackOffset,
                             ZF_IN_OPT zfbool allowEmpty /* = zffalse */)
{
    int success = 0;
    ret = lua_tonumberx(L, luaStackOffset, &success);
    if(success)
    {
        return zftrue;
    }
    if(!lua_isuserdata(L, luaStackOffset))
    {
        return zffalse;
    }

    zfautoObject const &param = ZFImpl_ZFLua_luaGet(L, luaStackOffset);
    if(param == zfautoObjectNull())
    {
        if(allowEmpty)
        {
            ret = 0;
            return zftrue;
        }
        else
        {
            return zffalse;
        }
    }
    else if(param.toObject()->classData()->classIsTypeOf(ZFValue::ClassData()))
    {
        ZFValue *v = param.to<ZFValue *>();
        if(v->valueConvertableTo(ZFValueType::e_double))
        {
            ret = v->doubleValue();
            return zftrue;
        }
        else
        {
            return zffalse;
        }
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfbool::ClassData()))
    {
        ret = (lua_Number)(param.to<v_zfbool *>()->zfv ? 1 : 0);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfindex::ClassData()))
    {
        ret = (lua_Number)(param.to<v_zfindex *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfint::ClassData()))
    {
        ret = (lua_Number)(param.to<v_zfint *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfuint::ClassData()))
    {
        ret = (lua_Number)(param.to<v_zfuint *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zffloat::ClassData()))
    {
        ret = (lua_Number)(param.to<v_zffloat *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfdouble::ClassData()))
    {
        ret = (lua_Number)(param.to<v_zfdouble *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zflongdouble::ClassData()))
    {
        ret = (lua_Number)(param.to<v_zflongdouble *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfbyte::ClassData()))
    {
        ret = (lua_Number)(param.to<v_zfbyte *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zftimet::ClassData()))
    {
        ret = (lua_Number)(param.to<v_zftimet *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfflags::ClassData()))
    {
        ret = (lua_Number)(param.to<v_zfflags *>()->zfv);
        return zftrue;
    }
    else if(param.toObject()->classData()->classIsTypeOf(v_zfidentity::ClassData()))
    {
        ret = (lua_Number)(param.to<v_zfidentity *>()->zfv);
        return zftrue;
    }
    else
    {
        return zffalse;
    }
}

ZF_NAMESPACE_GLOBAL_END

