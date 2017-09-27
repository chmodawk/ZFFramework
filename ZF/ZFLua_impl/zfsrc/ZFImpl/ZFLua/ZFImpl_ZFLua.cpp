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
ZFOBJECT_REGISTER(ZFImpl_ZFLua_UnknownParam)

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
                            ZF_IN_OPT zfbool luaResultRequire /* = zffalse */,
                            ZF_OUT_OPT zfautoObject *luaResult /* = zfnull */,
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
    int error = (
            luaL_loadbuffer(L, buf, (bufLen == zfindexMax()) ? zfslen(buf) : bufLen, "")
            || lua_pcall(L, 0, (luaResultRequire ? 1 : 0), 0)
        );
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

    if(luaResultRequire && luaResult != zfnull)
    {
        zfstring t;
        if(lua_isuserdata(L, -1))
        {
            *luaResult = ZFImpl_ZFLua_luaGet(L, -1);
            v_zfautoObject *tmp = ZFCastZFObject(v_zfautoObject *, *luaResult);
            if(tmp != zfnull)
            {
                *luaResult = tmp->zfv;
            }
            lua_pop(L, 1);
        }
        else if(ZFImpl_ZFLua_toNumber(*luaResult, L, -1, zftrue))
        {
            lua_pop(L, 1);
        }
        else if(ZFImpl_ZFLua_toString(t, L, -1, zftrue))
        {
            zfblockedAllocWithoutLeakTest(v_zfstring, v);
            v->zfv = t;
            *luaResult = zfautoObjectCreateWithoutLeakTest(v);
            lua_pop(L, 1);
        }
        else
        {
            if(errHint != zfnull)
            {
                *errHint += zfText("unable to access return value");
            }
            return zffalse;
        }
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

zfbool ZFImpl_ZFLua_toString(ZF_IN_OUT zfstring &s,
                             ZF_IN lua_State *L,
                             ZF_IN zfint luaStackOffset,
                             ZF_IN_OPT zfbool allowEmpty /* = zffalse */,
                             ZF_OUT_OPT const ZFClass **holderCls /* = zfnull */)
{
    if(holderCls != zfnull) {*holderCls = zfnull;}
    if(lua_isstring(L, luaStackOffset))
    {
        s += ZFStringA2Z(lua_tostring(L, luaStackOffset));
        return zftrue;
    }
    if(!lua_isuserdata(L, luaStackOffset))
    {
        return zffalse;
    }

    zfautoObject const &param = ZFImpl_ZFLua_luaGet(L, luaStackOffset);
    return ZFImpl_ZFLua_toString(s, param.toObject(), allowEmpty, holderCls);
}
zfbool ZFImpl_ZFLua_toString(ZF_IN_OUT zfstring &s,
                             ZF_IN ZFObject *obj,
                             ZF_IN_OPT zfbool allowEmpty /* = zffalse */,
                             ZF_OUT_OPT const ZFClass **holderCls /* = zfnull */)
{
    if(holderCls != zfnull) {*holderCls = zfnull;}
    if(obj == zfnull)
    {
        return allowEmpty;
    }

    const ZFClass *cls = obj->classData();
    if(cls->classIsTypeOf(ZFString::ClassData()))
    {
        if(holderCls != zfnull) {*holderCls = ZFString::ClassData();}
        ZFString *t = obj->to<ZFString *>();
        if(t != zfnull)
        {
            s += t->stringValue();
        }
        return zftrue;
    }
    else if(cls->classIsTypeOf(v_zfstring::ClassData()))
    {
        if(holderCls != zfnull) {*holderCls = v_zfstring::ClassData();}
        s += obj->to<v_zfstring *>()->zfv;
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
                             ZF_IN_OPT zfbool allowEmpty /* = zffalse */,
                             ZF_OUT_OPT const ZFClass **holderCls /* = zfnull */)
{
    if(holderCls != zfnull) {*holderCls = zfnull;}
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
    return ZFImpl_ZFLua_toNumber(ret, param.toObject(), allowEmpty, holderCls);
}

static zfbool _ZFP_ZFImpl_ZFLua_toNumber_ZFEnum(ZF_OUT zfautoObject &ret,
                                                ZF_IN ZFPropertyTypeWrapper *enumWrapper,
                                                ZF_OUT_OPT const ZFClass **holderCls = zfnull);
zfbool ZFImpl_ZFLua_toNumber(ZF_OUT zfautoObject &ret,
                             ZF_IN ZFObject *obj,
                             ZF_IN_OPT zfbool allowEmpty /* = zffalse */,
                             ZF_OUT_OPT const ZFClass **holderCls /* = zfnull */)
{
    if(holderCls != zfnull) {*holderCls = zfnull;}
    if(obj == zfnull)
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

    const ZFClass *cls = obj->classData();
    if(holderCls != zfnull) {*holderCls = cls;}
    if(cls->classIsTypeOf(ZFValue::ClassData()))
    {
        ret = zfautoObjectCreateWithoutLeakTest(obj);
        return zftrue;
    }
    else if(cls->classIsTypeOf(v_zfbool::ClassData()))
    {
        ret = ZFValue::boolValueCreate(obj->to<v_zfbool *>()->zfv);
        return zftrue;
    }
    else if(cls->classIsTypeOf(v_zfindex::ClassData()))
    {
        ret = ZFValue::indexValueCreate(obj->to<v_zfindex *>()->zfv);
        return zftrue;
    }
    else if(cls->classIsTypeOf(v_zfint::ClassData()))
    {
        ret = ZFValue::intValueCreate(obj->to<v_zfint *>()->zfv);
        return zftrue;
    }
    else if(cls->classIsTypeOf(v_zfuint::ClassData()))
    {
        ret = ZFValue::unsignedIntValueCreate(obj->to<v_zfuint *>()->zfv);
        return zftrue;
    }
    else if(cls->classIsTypeOf(v_zffloat::ClassData()))
    {
        ret = ZFValue::floatValueCreate(obj->to<v_zffloat *>()->zfv);
        return zftrue;
    }
    else if(cls->classIsTypeOf(v_zfdouble::ClassData()))
    {
        ret = ZFValue::doubleValueCreate(obj->to<v_zfdouble *>()->zfv);
        return zftrue;
    }
    else if(cls->classIsTypeOf(v_zflongdouble::ClassData()))
    {
        ret = ZFValue::longDoubleValueCreate(obj->to<v_zflongdouble *>()->zfv);
        return zftrue;
    }
    else if(cls->classIsTypeOf(v_zfbyte::ClassData()))
    {
        ret = ZFValue::unsignedIntValueCreate((zfuint)obj->to<v_zfbyte *>()->zfv);
        return zftrue;
    }
    else if(cls->classIsTypeOf(v_zftimet::ClassData()))
    {
        ret = ZFValue::timeValueCreate(obj->to<v_zftimet *>()->zfv);
        return zftrue;
    }
    else if(cls->classIsTypeOf(v_zfflags::ClassData()))
    {
        ret = ZFValue::flagsValueCreate(obj->to<v_zfflags *>()->zfv);
        return zftrue;
    }
    else if(cls->classIsTypeOf(v_zfidentity::ClassData()))
    {
        ret = ZFValue::identityValueCreate(obj->to<v_zfidentity *>()->zfv);
        return zftrue;
    }
    else if(cls->classIsTypeOf(ZFEnum::ClassData()))
    {
        ret = ZFValue::flagsValueCreate((zfflags)obj->to<ZFEnum *>()->enumValue());
        return zftrue;
    }
    else if(cls->classIsTypeOf(ZFPropertyTypeWrapper::ClassData())
        && _ZFP_ZFImpl_ZFLua_toNumber_ZFEnum(ret, obj->to<ZFPropertyTypeWrapper *>(), holderCls))
    {
        return zftrue;
    }
    else
    {
        return zffalse;
    }
}
static zfbool _ZFP_ZFImpl_ZFLua_toNumber_ZFEnum(ZF_OUT zfautoObject &ret,
                                                ZF_IN ZFPropertyTypeWrapper *enumWrapper,
                                                ZF_OUT_OPT const ZFClass **holderCls /* = zfnull */)
{
    const ZFClass *enumClass = zfnull;
    zfuint enumValue = 0;
    zfbool isEnumFlags = zffalse;
    if(ZFEnumInfoFromWrapper(enumClass, enumValue, isEnumFlags, enumWrapper))
    {
        if(holderCls != zfnull)
        {
            *holderCls = enumClass;
        }
        ret = ZFValue::flagsValueCreate((zfflags)enumValue);
        return zftrue;
    }
    else
    {
        return zffalse;
    }
}

zfbool ZFImpl_ZFLua_toLuaValue(ZF_IN lua_State *L,
                               ZF_IN ZFObject *obj,
                               ZF_IN_OPT zfbool allowEmpty /* = zffalse */)
{
    if(obj == zfnull)
    {
        if(allowEmpty)
        {
            lua_pushnumber(L, 0);
            return zftrue;
        }
        else
        {
            return zffalse;
        }
    }

    zfautoObject v;
    if(ZFImpl_ZFLua_toNumber(v, obj, allowEmpty))
    {
        ZFValue *t = v.to<ZFValue *>();
        switch(t->valueType())
        {
            case ZFValueType::e_bool:
                lua_pushboolean(L, t->boolValue());
                return 1;
            case ZFValueType::e_char:
                lua_pushinteger(L, (lua_Integer)t->charValueAccess());
                return 1;
            case ZFValueType::e_int:
                lua_pushinteger(L, (lua_Integer)t->intValueAccess());
                return 1;
            case ZFValueType::e_unsignedInt:
                lua_pushinteger(L, (lua_Integer)t->unsignedIntValueAccess());
                return 1;
            case ZFValueType::e_index:
                lua_pushinteger(L, (lua_Integer)t->indexValueAccess());
                return 1;
            case ZFValueType::e_float:
                lua_pushinteger(L, (lua_Number)t->floatValueAccess());
                return 1;
            case ZFValueType::e_double:
                lua_pushinteger(L, (lua_Number)t->doubleValueAccess());
                return 1;
            case ZFValueType::e_longDouble:
                lua_pushinteger(L, (lua_Number)t->longDoubleValueAccess());
                return 1;
            case ZFValueType::e_time:
                lua_pushinteger(L, (lua_Integer)t->timeValueAccess());
                return 1;
            case ZFValueType::e_flags:
                lua_pushinteger(L, (lua_Integer)t->flagsValueAccess());
                return 1;
            case ZFValueType::e_identity:
                lua_pushinteger(L, (lua_Integer)t->identityValueAccess());
                return 1;
            case ZFValueType::e_serializableData:
            default:
                ZFLuaErrorOccurredTrim(zfText("[zfl_luaValue] unknown param type, got %s"),
                    t->objectInfo().cString());
                return luaL_error(L, "");
        }
    }

    zfstring s;
    if(ZFImpl_ZFLua_toString(s, obj, allowEmpty))
    {
        lua_pushstring(L, ZFStringZ2A(s.cString()));
        return 1;
    }

    ZFLuaErrorOccurredTrim(zfText("[zfl_luaValue] unknown param type, got %s"),
        obj->objectInfo().cString());
    return luaL_error(L, "");
}

ZF_NAMESPACE_GLOBAL_END

