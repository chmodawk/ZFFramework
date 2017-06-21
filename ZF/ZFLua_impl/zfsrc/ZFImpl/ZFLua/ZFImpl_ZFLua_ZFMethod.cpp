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
static void _ZFP_ZFImpl_ZFLua_ZFMethod_setupGlobalMethod(ZF_IN const ZFCoreArrayPOD<lua_State *> &luaStateList,
                                                         ZF_IN const ZFMethod *method)
{
    if(!method->methodIsFunctionType()
        || !zfscmpTheSame(method->methodNamespace(), ZFMethodFuncNamespaceGlobal))
    {
        return ;
    }

    zfstring code;
    zfstringAppend(code, zfText(
            "function %s(...)\n"
            "    return zfl_callStatic2(\"zf\", \"%s\", ...)\n"
            "end\n"
        ), method->methodName(), method->methodName());
    for(zfindex i = 0; i < luaStateList.count(); ++i)
    {
        ZFImpl_ZFLua_execute(luaStateList[i], code);
    }
}
static ZFLISTENER_PROTOTYPE_EXPAND(_ZFP_ZFImpl_ZFLua_ZFMethod_methodOnChange)
{
    const ZFClassDataChangeData *data = listenerData.param0->to<ZFPointerHolder *>()->holdedDataPointer<const ZFClassDataChangeData *>();
    if(data->changedMethod != zfnull && data->changeType == ZFClassDataChangeTypeAttach)
    {
        if(data->changedMethod->methodIsFunctionType())
        {
            const ZFCoreArrayPOD<lua_State *> &luaStateList = ZFImpl_ZFLua_luaStateAttached();
            for(zfindex i = 0; i < luaStateList.count(); ++i)
            {
                ZFImpl_ZFLua_implSetupScope(luaStateList[i], data->changedMethod->methodNamespace());
            }

            _ZFP_ZFImpl_ZFLua_ZFMethod_setupGlobalMethod(luaStateList, data->changedMethod);
        }
    }
}
ZFImpl_ZFLua_implSetupCallback_DEFINE(ZFMethod, {
        ZFCoreArrayPOD<const ZFMethod *> allMethod = ZFMethodFuncGetAll();
        if(!allMethod.isEmpty())
        {
            const zfchar **methodNameList = (const zfchar **)zfmalloc(sizeof(const zfchar *) * (allMethod.count() + 1));
            zfblockedFree(methodNameList);

            ZFCoreArrayPOD<lua_State *> luaStateList;
            luaStateList.add(L);
            for(zfindex i = 0; i < allMethod.count(); ++i)
            {
                const ZFMethod *method = allMethod[i];
                methodNameList[i] = method->methodNamespace();
                _ZFP_ZFImpl_ZFLua_ZFMethod_setupGlobalMethod(luaStateList, method);
            }
            methodNameList[allMethod.count()] = zfnull;

            ZFImpl_ZFLua_implSetupScope(L, methodNameList);
        }

        ZFClassDataChangeObserver.observerAdd(
            ZFGlobalEvent::EventClassDataChange(),
            ZFCallbackForRawFunction(_ZFP_ZFImpl_ZFLua_ZFMethod_methodOnChange));

        ZFImpl_ZFLua_implSetupScope(L, ZFLuaGlobalFuncNamespace);
        ZFImpl_ZFLua_implSetupScope(L, ZFMethodFuncNamespaceGlobal);
    }, {
        ZFClassDataChangeObserver.observerRemove(
            ZFGlobalEvent::EventClassDataChange(),
            ZFCallbackForRawFunction(_ZFP_ZFImpl_ZFLua_ZFMethod_methodOnChange));
    })

ZF_NAMESPACE_GLOBAL_END

