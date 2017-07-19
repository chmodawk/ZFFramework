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
static ZFLISTENER_PROTOTYPE_EXPAND(_ZFP_ZFImpl_ZFLua_ZFClass_classOnChange)
{
    const ZFClassDataChangeData *data = listenerData.param0->to<ZFPointerHolder *>()->holdedDataPointer<const ZFClassDataChangeData *>();
    if(data->changedClass != zfnull && data->changeType == ZFClassDataChangeTypeAttach)
    {
        const ZFCoreArrayPOD<lua_State *> &luaStateList = ZFImpl_ZFLua_luaStateAttached();
        for(zfindex i = 0; i < luaStateList.count(); ++i)
        {
            ZFImpl_ZFLua_implSetupScope(luaStateList[i], data->changedClass->className());
        }
    }
}
ZFImpl_ZFLua_implSetupCallback_DEFINE(ZFClass, {
        ZFCoreArrayPOD<const ZFClass *> allClass = ZFClassGetAll();
        if(!allClass.isEmpty())
        {
            const zfchar **classNameList = (const zfchar **)zfmalloc(sizeof(const zfchar *) * (allClass.count() + 1));
            zfblockedFree(classNameList);
            for(zfindex i = 0; i < allClass.count(); ++i)
            {
                classNameList[i] = allClass[i]->className();
            }
            classNameList[allClass.count()] = zfnull;

            ZFImpl_ZFLua_implSetupScope(L, classNameList);
        }

        ZFImpl_ZFLua_implSetupScope(L, zfText("ZFClass"));

        ZFClassDataChangeObserver.observerAdd(
            ZFGlobalEvent::EventClassDataChange(),
            ZFCallbackForRawFunction(_ZFP_ZFImpl_ZFLua_ZFClass_classOnChange));
    }, {
        ZFClassDataChangeObserver.observerRemove(
            ZFGlobalEvent::EventClassDataChange(),
            ZFCallbackForRawFunction(_ZFP_ZFImpl_ZFLua_ZFClass_classOnChange));
    })

ZF_NAMESPACE_GLOBAL_END

