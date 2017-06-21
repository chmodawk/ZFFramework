/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFCoreLog.h"
#include "ZFCoreSPrintf.h"
#include "ZFCoreStaticInitializer.h"
#include "ZFCoreGlobalInitializer.h"
#include "ZFCoreArray.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZF_STATIC_INITIALIZER_INIT(ZFCoreLogDataHolder)
{
    outputCallback = ZFCoreLogOutputCallbackDefault;
}
ZF_STATIC_INITIALIZER_DESTROY(ZFCoreLogDataHolder)
{
    outputCallback = zfnull;
}
ZFCoreLogOutputCallbackType outputCallback;
ZFCoreArrayPOD<ZFCoreCriticalErrorCallback> criticalErrorCallbacks;
ZFCoreArrayPOD<ZFCoreCriticalErrorCallback> criticalErrorPrepareCallbacks;
ZF_STATIC_INITIALIZER_END(ZFCoreLogDataHolder)
#define _ZFP_ZFCoreLogOutputCallback (ZF_STATIC_INITIALIZER_INSTANCE(ZFCoreLogDataHolder)->outputCallback)
#define _ZFP_ZFCoreCriticalErrorCallbacks (ZF_STATIC_INITIALIZER_INSTANCE(ZFCoreLogDataHolder)->criticalErrorCallbacks)
#define _ZFP_ZFCoreCriticalErrorPrepareCallbacks (ZF_STATIC_INITIALIZER_INSTANCE(ZFCoreLogDataHolder)->criticalErrorPrepareCallbacks)

zfindex _ZFP_ZFCoreLogOutputCallbackDefault(ZF_IN const zfcharA *s)
{
    // try to print to std output
    fprintf(stderr, zfTextA("%s"), s);
    return zfindexMax;
}

void zfCoreLogOutputCallbackSet(ZF_IN_OPT ZFCoreLogOutputCallbackType callback /* = ZFCoreLogOutputCallbackDefault */)
{
    _ZFP_ZFCoreLogOutputCallback = callback;
}
ZFCoreLogOutputCallbackType zfCoreLogOutputCallbackGet(void)
{
    return _ZFP_ZFCoreLogOutputCallback;
}

void _ZFP_zfCoreLog(ZF_IN const ZFCallerInfo &callerInfo,
                    ZF_IN zfbool isAutoEndl,
                    ZF_IN const zfcharA *format,
                    ...)
{
    if(_ZFP_ZFCoreLogOutputCallback == zfnull)
    {
        return ;
    }

    zfstringA s;

    va_list vaList;
    va_start(vaList, format);
    if(callerInfo.callerInfoAT(s))
    {
        s += ' ';
    }
    zfstringAppendV(s, format, vaList);
    if(isAutoEndl)
    {
        zfstringAppend(s, zfTextA("\n"));
    }
    va_end(vaList);

    _ZFP_ZFCoreLogOutputCallback(zfsCoreZ2A(s.cString()));
}

void zfCoreCriticalErrorCallbackPrepareAdd(ZF_IN ZFCoreCriticalErrorCallback callback)
{
    if(callback != zfnull)
    {
        _ZFP_ZFCoreCriticalErrorPrepareCallbacks.add(callback);
    }
}
void zfCoreCriticalErrorCallbackPrepareRemove(ZF_IN ZFCoreCriticalErrorCallback callback)
{
    ZFCoreArrayPOD<ZFCoreCriticalErrorCallback> &d = _ZFP_ZFCoreCriticalErrorPrepareCallbacks;
    for(zfiterator it = d.iterator(); d.iteratorIsValid(it); d.iteratorNext(it))
    {
        if(d.iteratorGet(it) == callback)
        {
            d.iteratorRemove(it);
            break;
        }
    }
}
void zfCoreCriticalErrorCallbackAdd(ZF_IN ZFCoreCriticalErrorCallback callback)
{
    if(callback != zfnull)
    {
        _ZFP_ZFCoreCriticalErrorCallbacks.add(callback);
    }
}
void zfCoreCriticalErrorCallbackRemove(ZF_IN ZFCoreCriticalErrorCallback callback)
{
    ZFCoreArrayPOD<ZFCoreCriticalErrorCallback> &d = _ZFP_ZFCoreCriticalErrorCallbacks;
    for(zfiterator it = d.iterator(); d.iteratorIsValid(it); d.iteratorNext(it))
    {
        if(d.iteratorGet(it) == callback)
        {
            d.iteratorRemove(it);
            break;
        }
    }
}
void _ZFP_zfCoreCriticalErrorPrepare(ZF_IN const ZFCallerInfo &callerInfo)
{
    const ZFCoreArrayPOD<ZFCoreCriticalErrorCallback> &criticalErrorCallbacks = _ZFP_ZFCoreCriticalErrorPrepareCallbacks;
    for(zfindex i = 0; i < criticalErrorCallbacks.count(); ++i)
    {
        criticalErrorCallbacks[i](callerInfo);
    }
}
void _ZFP_zfCoreCriticalError(ZF_IN const ZFCallerInfo &callerInfo)
{
    const ZFCoreArrayPOD<ZFCoreCriticalErrorCallback> &criticalErrorCallbacks = _ZFP_ZFCoreCriticalErrorCallbacks;
    for(zfindex i = 0; i < criticalErrorCallbacks.count(); ++i)
    {
        criticalErrorCallbacks[i](callerInfo);
    }

    abort();
}

ZF_NAMESPACE_GLOBAL_END

