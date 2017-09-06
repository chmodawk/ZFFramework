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
static int _ZFP_ZFImpl_ZFLua_zfl_luaValue(ZF_IN lua_State *L)
{
    zfint count = (zfint)lua_gettop(L);
    if(count != 1)
    {
        ZFLuaErrorOccurredTrim(
            zfText("[zfl_luaValue] takes only one param, got %zi"),
            (zfindex)count);
        return luaL_error(L, "");
    }

    if(!lua_isuserdata(L, 1) && lua_islightuserdata(L, 1))
    {
        lua_pushvalue(L, 1);
        return 1;
    }

    return ZFImpl_ZFLua_toLuaValue(L, ZFImpl_ZFLua_luaGet(L, 1));
}

ZFImpl_ZFLua_implSetupCallback_DEFINE(zfl_luaValue, {
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("zfl_luaValue"), _ZFP_ZFImpl_ZFLua_zfl_luaValue);
    }, {
    })

ZF_NAMESPACE_GLOBAL_END

