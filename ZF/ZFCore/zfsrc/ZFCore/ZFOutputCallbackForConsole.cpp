/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFOutputCallbackForConsole.h"
#include "protocol/ZFProtocolZFOutput.h"
#include "ZFString.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// ZFOutputCallbackForConsole
static zfindex _ZFP_ZFOutputCallbackForConsoleFunction(ZF_IN const void *s, ZF_IN zfindex count)
{
    ZFPROTOCOL_INTERFACE_CLASS(ZFOutput) *impl = ZFPROTOCOL_TRY_ACCESS(ZFOutput);
    if(impl == zfnull)
    {
        if(count == zfindexMax())
        {
            printf(zfTextA("%s"), ZFStringZ2A(s));
        }
        else
        {
            zfstring tmp((const zfchar *)s, count);
            printf(zfTextA("%s"), ZFStringZ2A(tmp.cString()));
        }
    }
    else
    {
        return impl->outputLog((const zfchar *)s, count);
    }
    return zfindexMax();
}

ZFEXPORT_VAR_READONLY_DEFINE(ZFOutputCallback, ZFOutputCallbackForConsole, ZFCallbackForRawFunction(_ZFP_ZFOutputCallbackForConsoleFunction))
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFOutputCallbackForConsoleInit, ZFLevelZFFrameworkEssential)
{
    ZFExportVarEnsureInit_ZFOutputCallbackForConsole();
    ZFOutputCallbackDefaultSet(ZFOutputCallbackForConsole());
}
ZF_GLOBAL_INITIALIZER_DESTROY(ZFOutputCallbackForConsoleInit)
{
    ZFOutputCallbackDefaultSet(ZFCallbackNull());
}
ZF_GLOBAL_INITIALIZER_END(ZFOutputCallbackForConsoleInit)

ZF_NAMESPACE_GLOBAL_END

