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

static int _ZFP_ZFImpl_ZFLua_zfLog(ZF_IN lua_State *L)
{
    zfint count = (zfint)lua_gettop(L);
    if(count <= 0)
    {
        return 0;
    }

    zfstring fmt;
    if(!ZFImpl_ZFLua_toString(fmt, L, 1))
    {
        ZFLuaErrorOccurredTrim(
            zfText("[zfLog] unable to access log format, expect string, got %zi"),
            ZFImpl_ZFLua_luaObjectInfo(L, 1).cString());
        return luaL_error(L, "");
    }

    zfstring params[ZFMETHOD_MAX_PARAM];
    for(zfint i = 1; i < count; ++i)
    {
        zfautoObject t;
        if(ZFImpl_ZFLua_toObject(t, L, i + 1))
        {
            ZFObjectInfoT(params[i - 1], t.toObject());
        }
        else if(ZFImpl_ZFLua_toString(params[i - 1], L, i + 1))
        {
            // nothing to do
        }
        else
        {
            ZFImpl_ZFLua_luaObjectInfoT(params[i - 1], L, i + 1);
        }
    }

    /* ZFMETHOD_MAX_PARAM */
    zfLogTrim(fmt.cString()
            , params[0].cString()
            , params[1].cString()
            , params[2].cString()
            , params[3].cString()
            , params[4].cString()
            , params[5].cString()
            , params[6].cString()
            , params[7].cString()
        );

    return 0;
}

// ============================================================
ZFImpl_ZFLua_implSetupCallback_DEFINE(zfLog, {
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("zfLog"), _ZFP_ZFImpl_ZFLua_zfLog);
    }, {
    })

ZF_NAMESPACE_GLOBAL_END

