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

zfclass _ZFP_I_ZFImpl_ZFLua_ZFCallbackForLuaHolder : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_I_ZFImpl_ZFLua_ZFCallbackForLuaHolder, ZFObject)

public:
    lua_State *L;
    int luaFunc;

    ZFLISTENER_DECLARE(callback)
    {
        lua_rawgeti(L, LUA_REGISTRYINDEX, luaFunc);
        if(lua_isfunction(L, -1))
        {
            zfblockedAllocWithoutLeakTest(v_ZFListenerData, listenerDataTmp, listenerData);
            ZFImpl_ZFLua_luaPush(L, zfautoObjectCreateWithoutLeakTest(listenerDataTmp));
            ZFImpl_ZFLua_implSetupObject(L);

            ZFImpl_ZFLua_luaPush(L, zfautoObjectCreateWithoutLeakTest(userData));
            ZFImpl_ZFLua_implSetupObject(L);

            lua_pcall(L, 2, 0, 0);
        }
    }
};

static int _ZFP_ZFImpl_ZFLua_ZFCallbackForLua(ZF_IN lua_State *L)
{
    zfint count = (zfint)lua_gettop(L);
    if(count != 1)
    {
        ZFLuaErrorOccurredTrim(
            zfText("[ZFCallbackForLua] expect one param, got %zi"),
            (zfindex)count);
        return luaL_error(L, "");
    }

    if(!lua_isfunction(L, 1))
    {
        ZFLuaErrorOccurredTrim(
            zfText("[ZFCallbackForLua] expect lua function as param, got %s"),
            ZFImpl_ZFLua_luaObjectInfo(L, 1).cString());
        return luaL_error(L, "");
    }

    zfblockedAllocWithoutLeakTest(_ZFP_I_ZFImpl_ZFLua_ZFCallbackForLuaHolder, holder);
    holder->L = L;
    lua_pushvalue(L, -1);
    holder->luaFunc = luaL_ref(L, LUA_REGISTRYINDEX);
    zfblockedAllocWithoutLeakTest(v_ZFCallback, ret);
    ret->zfv = ZFCallbackForMemberMethod(holder, ZFMethodAccess(_ZFP_I_ZFImpl_ZFLua_ZFCallbackForLuaHolder, callback));
    ret->zfv.callbackOwnerObjectRetain();
    ZFImpl_ZFLua_luaPush(L, zfautoObjectCreateWithoutLeakTest(ret));
    ZFImpl_ZFLua_implSetupObject(L);
    return 1;
}

// ============================================================
ZFImpl_ZFLua_implSetupCallback_DEFINE(ZFCallbackForLua, {
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("ZFCallbackForLua"), _ZFP_ZFImpl_ZFLua_ZFCallbackForLua);
    }, {
    })

ZF_NAMESPACE_GLOBAL_END

