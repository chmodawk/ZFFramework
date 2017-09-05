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
static int _ZFP_ZFImpl_ZFLua_zfl_toNumber(ZF_IN lua_State *L)
{
    zfint count = (zfint)lua_gettop(L);
    if(count != 1)
    {
        ZFLuaErrorOccurredTrim(
            zfText("[zfl_toNumber] takes only one param, got %zi"),
            (zfindex)count);
        return luaL_error(L, "");
    }

    lua_Number v = 0;
    if(!ZFImpl_ZFLua_toNumber(v, L, 1))
    {
        ZFLuaErrorOccurredTrim(zfText("[zfl_toNumber] unknown param type, got %s"),
            ZFImpl_ZFLua_luaObjectInfo(L, 1, zftrue).cString());
        return luaL_error(L, "");
    }
    lua_pushnumber(L, (lua_Number)v);
    return 1;
}

ZFImpl_ZFLua_implSetupCallback_DEFINE(zfl_toNumber, {
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("zfl_toNumber"), _ZFP_ZFImpl_ZFLua_zfl_toNumber);
    }, {
    })

ZF_NAMESPACE_GLOBAL_END

