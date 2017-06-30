/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFObjectMutex.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
ZFObjectMutexImplCheckCallback _ZFP_ZFObjectMutexImplCheckCallbackRef = zfnull;
ZFObjectMutexImplInitCallback _ZFP_ZFObjectMutexImplInitCallbackRef = zfnull;
ZFObjectMutexImplCleanupCallback _ZFP_ZFObjectMutexImplCleanupCallbackRef = zfnull;
void ZFObjectMutexImplSet(ZF_IN_OPT ZFObjectMutexImplCheckCallback checkCallback /* = zfnull */,
                          ZF_IN_OPT ZFObjectMutexImplInitCallback initCallback /* = zfnull */,
                          ZF_IN_OPT ZFObjectMutexImplCleanupCallback cleanupCallback /* = zfnull */)
{
    _ZFP_ZFObjectMutexImplCheckCallbackRef = checkCallback;
    _ZFP_ZFObjectMutexImplInitCallbackRef = initCallback;
    _ZFP_ZFObjectMutexImplCleanupCallbackRef = cleanupCallback;
}

ZF_NAMESPACE_GLOBAL_END

