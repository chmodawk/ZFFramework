/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFLuaExecute.h"
#include "protocol/ZFProtocolZFLua.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
ZFMETHOD_FUNC_DEFINE_3(zfbool, ZFLuaExecute,
                       ZFMP_IN(const ZFInputCallback &, input),
                       ZFMP_IN_OPT(zfbool, luaResultRequire, zffalse),
                       ZFMP_OUT_OPT(zfautoObject *, luaResult, zfnull))
{
    ZFBuffer buf = ZFInputCallbackReadToBuffer(input);
    return ZFLuaExecute(buf.bufferAsString(), buf.bufferAsStringLength(), luaResultRequire, luaResult);
}
ZFMETHOD_FUNC_DEFINE_4(zfbool, ZFLuaExecute,
                       ZFMP_IN(const zfchar *, buf),
                       ZFMP_IN_OPT(zfindex, bufLen, zfindexMax()),
                       ZFMP_IN_OPT(zfbool, luaResultRequire, zffalse),
                       ZFMP_OUT_OPT(zfautoObject *, luaResult, zfnull))
{
    zfstring errHint;
    if(!ZFPROTOCOL_ACCESS(ZFLua)->luaExecute(buf, bufLen, luaResultRequire, luaResult, &errHint))
    {
        ZFLuaErrorOccurredTrim(zfText("native lua error:\n    %s\n"), errHint.cString());
        return zffalse;
    }
    else
    {
        return zftrue;
    }
}

ZF_NAMESPACE_GLOBAL_END

