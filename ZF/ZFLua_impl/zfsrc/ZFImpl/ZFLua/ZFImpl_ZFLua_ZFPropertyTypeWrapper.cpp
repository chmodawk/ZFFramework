/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFImpl_ZFLua.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
static int _ZFP_ZFImpl_ZFLua_ZFPropertyTypeWrapper(ZF_IN lua_State *L)
{
    zfstring className;
    if(!ZFImpl_ZFLua_toString(className, L, 1))
    {
        ZFLuaErrorOccurredTrim(zfText("[ZFPropertyTypeWrapper] unable to access class name, expect string type, got %s"),
            ZFImpl_ZFLua_luaObjectInfo(L, 1, zftrue).cString());
        return luaL_error(L, "");
    }
    const ZFClass *cls = ZFClass::classForName(className);
    if(cls == zfnull)
    {
        ZFLuaErrorOccurredTrim(zfText("[ZFPropertyTypeWrapper] no such class %s"), className.cString());
        return luaL_error(L, "");
    }
    else if(!cls->classIsSubclassOf(ZFPropertyTypeWrapper::ClassData()))
    {
        ZFLuaErrorOccurredTrim(zfText("[ZFPropertyTypeWrapper] class %s is not type of %s"),
            className.cString(),
            ZFPropertyTypeWrapper::ClassData()->className());
        return luaL_error(L, "");
    }

    zfstring data;
    if(!ZFImpl_ZFLua_toString(data, L, 2))
    {
        data.removeAll();
    }

    zfautoObject ret = cls->newInstance();
    ZFPropertyTypeWrapper *wrapper = ret.to<ZFPropertyTypeWrapper *>();
    if(!data.isEmpty())
    {
        if(!wrapper->wrappedValueFromString(data))
        {
            ZFLuaErrorOccurredTrim(zfText("[ZFPropertyTypeWrapper] unable to convert %s from data: %s"),
                className.cString(),
                data.cString());
            return luaL_error(L, "");
        }
    }

    ZFImpl_ZFLua_luaPush(L, ret);
    ZFImpl_ZFLua_implSetupObject(L);
    return 1;
}
static void _ZFP_ZFImpl_ZFLua_ZFPropertyTypeWrapperSetup(ZF_IN lua_State *L, ZF_IN const ZFClass *cls)
{
    zfstring code;
    zfstringAppend(code, zfText(
            "function %s(data)\n"
            "    data = data or ''\n"
            "    return _ZFP_ZFImpl_ZFLua_ZFPropertyTypeWrapper('%s', data)\n"
            "end\n"
        ), cls->className() + ZFImpl_ZFLua_PropTypePrefixLen, cls->className());
    ZFImpl_ZFLua_execute(L, code);
}
static ZFLISTENER_PROTOTYPE_EXPAND(_ZFP_ZFImpl_ZFLua_ZFPropertyTypeWrapper_classOnChange)
{
    const ZFClassDataChangeData *data = listenerData.param0->to<ZFPointerHolder *>()->holdedDataPointer<const ZFClassDataChangeData *>();
    if(data->changedClass != zfnull && data->changeType == ZFClassDataChangeTypeAttach)
    {
        if(data->changedClass->classIsSubclassOf(ZFPropertyTypeWrapper::ClassData()))
        {
            const ZFCoreArrayPOD<lua_State *> &luaStateList = ZFImpl_ZFLua_luaStateAttached();
            for(zfindex i = 0; i < luaStateList.count(); ++i)
            {
                _ZFP_ZFImpl_ZFLua_ZFPropertyTypeWrapperSetup(luaStateList[i], data->changedClass);
            }
        }
    }
}
ZFImpl_ZFLua_implSetupCallback_DEFINE(ZFPropertyTypeWrapper, {
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_ZFPropertyTypeWrapper"), _ZFP_ZFImpl_ZFLua_ZFPropertyTypeWrapper);

        ZFCoreArrayPOD<const ZFClass *> allClass = ZFClassGetAll();
        if(!allClass.isEmpty())
        {
            const ZFClass *target = ZFPropertyTypeWrapper::ClassData();
            for(zfindex i = 0; i < allClass.count(); ++i)
            {
                const ZFClass *cls = allClass[i];
                if(cls != target && cls->classIsSubclassOf(target))
                {
                    _ZFP_ZFImpl_ZFLua_ZFPropertyTypeWrapperSetup(L, cls);
                }
            }
        }

        ZFClassDataChangeObserver.observerAdd(
            ZFGlobalEvent::EventClassDataChange(),
            ZFCallbackForRawFunction(_ZFP_ZFImpl_ZFLua_ZFPropertyTypeWrapper_classOnChange));
    }, {
        ZFClassDataChangeObserver.observerRemove(
            ZFGlobalEvent::EventClassDataChange(),
            ZFCallbackForRawFunction(_ZFP_ZFImpl_ZFLua_ZFPropertyTypeWrapper_classOnChange));
    })

ZF_NAMESPACE_GLOBAL_END

