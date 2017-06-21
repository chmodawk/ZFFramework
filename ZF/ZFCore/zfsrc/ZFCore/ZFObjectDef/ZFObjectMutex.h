/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFObjectMutex.h
 * @brief mutex impl for ZFObject
 */

#ifndef _ZFI_ZFObjectMutex_h_
#define _ZFI_ZFObjectMutex_h_

#include "ZFObjectClassTypeFwd.h"

ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief lock object for mutex's implementation
 */
zfclassNotPOD ZF_ENV_EXPORT ZFObjectMutexImpl : zfextendsNotPOD ZFCoreMutexImpl
{
public:
    /**
     * @brief lock (must be reentrant)
     */
    virtual void mutexImplLock(void) zfpurevirtual;
    /**
     * @brief unlock
     */
    virtual void mutexImplUnlock(void) zfpurevirtual;
    /**
     * @brief try lock
     */
    virtual zfbool mutexImplTryLock(void) zfpurevirtual;
};

/**
 * @brief see #ZFObjectMutexImplSet
 */
typedef zfbool (*ZFObjectMutexImplCheckCallback)(void);
/**
 * @brief see #ZFObjectMutexImplSet
 */
typedef ZFObjectMutexImpl *(*ZFObjectMutexImplInitCallback)(void);
/**
 * @brief see #ZFObjectMutexImplSet
 */
typedef void (*ZFObjectMutexImplCleanupCallback)(ZF_IN ZFObjectMutexImpl *mutexImpl);

/**
 * @brief change the implementation for #zfsynchronizedObject
 *
 * the sync for ZFObject is an optional protocol,
 * each newly allocated object would have #ZFObjectMutexImplCheckCallback been called
 * to check whether the protocol is available,
 * if not, any other sync function to this object is disabled automatically,
 * otherwise, a mutex impl would be created by #ZFObjectMutexImplInitCallback when you
 * request to the sync logic,
 * and would be cleaned up during object's deallocation
 */
extern ZF_ENV_EXPORT void ZFObjectMutexImplSet(ZF_IN_OPT ZFObjectMutexImplCheckCallback checkCallback = zfnull,
                                               ZF_IN_OPT ZFObjectMutexImplInitCallback initCallback = zfnull,
                                               ZF_IN_OPT ZFObjectMutexImplCleanupCallback cleanupCallback = zfnull);

extern ZF_ENV_EXPORT ZFObjectMutexImplCheckCallback _ZFP_ZFObjectMutexImplCheckCallbackRef;
extern ZF_ENV_EXPORT ZFObjectMutexImplInitCallback _ZFP_ZFObjectMutexImplInitCallbackRef;
extern ZF_ENV_EXPORT ZFObjectMutexImplCleanupCallback _ZFP_ZFObjectMutexImplCleanupCallbackRef;

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFObjectMutex_h_

