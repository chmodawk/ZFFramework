/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFCoreLog_CommonLog.h"
#include "ZFCoreSPrintf.h"

ZF_NAMESPACE_GLOBAL_BEGIN

void _ZFP_zfCoreLogCriticalMessage(ZF_IN const ZFCallerInfo &callerInfo,
                                   ZF_IN const zfcharA *fmt,
                                   ...)
{
    va_list vaList;
    va_start(vaList, fmt);
    _ZFP_zfCoreLogCriticalMessageV(callerInfo, fmt, vaList);
    va_end(vaList);
}
void _ZFP_zfCoreLogCriticalMessageV(ZF_IN const ZFCallerInfo &callerInfo,
                                    ZF_IN const zfcharA *fmt,
                                    ZF_IN va_list vaList)
{
    zfCoreLogTrim(zfTextA("============================================================"));
    zfCoreLogTrimNoEndl(zfTextA("| "));
    zfCoreLogDetailV(callerInfo, fmt, vaList);
    zfCoreLogTrim(zfTextA("============================================================"));
}
void _ZFP_zfCoreCritical(ZF_IN const ZFCallerInfo &callerInfo,
                         ZF_IN const zfcharA *fmt,
                         ...)
{
    va_list vaList;
    va_start(vaList, fmt);
    _ZFP_zfCoreCriticalV(callerInfo, fmt, vaList);
    va_end(vaList);
}
void _ZFP_zfCoreCriticalV(ZF_IN const ZFCallerInfo &callerInfo,
                          ZF_IN const zfcharA *fmt,
                          ZF_IN va_list vaList)
{
    zfCoreCriticalErrorPrepareDetail(callerInfo);
    zfCoreLogCriticalMessageDetailV(callerInfo, fmt, vaList);
    zfCoreCriticalErrorDetail(callerInfo);
}

ZF_NAMESPACE_GLOBAL_END

