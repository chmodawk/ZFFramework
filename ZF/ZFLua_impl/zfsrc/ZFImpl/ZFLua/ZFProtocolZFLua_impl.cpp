/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFImpl.h"
#include "ZFLua/protocol/ZFProtocolZFLua.h"
#include "ZFImpl_ZFLua.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFPROTOCOL_IMPLEMENTATION_BEGIN(ZFLua_impl, ZFLua, ZFProtocolLevel::e_Default)
public:
    virtual zfbool luaExecute(ZF_IN const zfchar *src,
                              ZF_IN_OPT zfindex srcLen = zfindexMax(),
                              ZF_IN_OPT zfbool luaResultRequire = zffalse,
                              ZF_OUT_OPT zfautoObject *luaResult = zfnull,
                              ZF_OUT_OPT zfstring *errorHint = zfnull)
    {
        if(ZFFrameworkStateCheck(ZFLevelZFFrameworkLow) != ZFFrameworkStateAvailable)
        {
            ZFLuaErrorOccurredTrim(
                zfText("[ZFLua] lua module only available after ZFFrameworkStateCheck(ZFLevelZFFrameworkLow)")
                );
            return zffalse;
        }

        return ZFImpl_ZFLua_execute(ZFImpl_ZFLua_luaState, src, srcLen, luaResultRequire, luaResult, errorHint);
    }
    virtual void luaGC(void)
    {
        lua_gc(ZFImpl_ZFLua_luaState, LUA_GCCOLLECT, 0);
    }
ZFPROTOCOL_IMPLEMENTATION_END(ZFLua_impl)
ZFPROTOCOL_IMPLEMENTATION_REGISTER(ZFLua_impl)

ZF_NAMESPACE_GLOBAL_END

