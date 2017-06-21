/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFCoreMutex.h
 * @brief core mutex
 */

#ifndef _ZFI_ZFCoreMutex_h_
#define _ZFI_ZFCoreMutex_h_

#include "ZFCoreTypeDef.h"
#include "ZFCoreUtil.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief impl object for #zfCoreMutexLock
 */
zfclassNotPOD ZF_ENV_EXPORT ZFCoreMutexImpl
{
public:
    /** @cond ZFPrivateDoc */
    ZFCoreMutexImpl(void) {}
    virtual ~ZFCoreMutexImpl(void) {}
    /** @endcond */
public:
    /**
     * @brief lock (must be reentrant)
     */
    virtual void mutexImplLock(void) zfpurevirtual;
    /**
     * @brief unlock
     */
    virtual void mutexImplUnlock(void) zfpurevirtual;
};
extern ZF_ENV_EXPORT ZFCoreMutexImpl *_ZFP_ZFCoreMutexImplObject;
/**
 * @brief #zfCoreMutexLock's implementation, change with caution
 */
extern ZF_ENV_EXPORT void ZFCoreMutexImplSet(ZF_IN ZFCoreMutexImpl *impl);
/**
 * @brief see #ZFCoreMutexImplSet
 */
extern ZF_ENV_EXPORT ZFCoreMutexImpl *ZFCoreMutexImplGet(void);

extern ZF_ENV_EXPORT ZFFuncAddrType _ZFP_ZFCoreMutexImpl_lock;
extern ZF_ENV_EXPORT ZFFuncAddrType _ZFP_ZFCoreMutexImpl_unlock;

/**
 * @brief internal use only
 *
 * you may change it at run time by changing #ZFCoreMutexImplSet
 */
#define zfCoreMutexLock() _ZFP_ZFCoreMutexImpl_lock()
/** @brief see #zfCoreMutexLock */
#define zfCoreMutexUnlock() _ZFP_ZFCoreMutexImpl_unlock()

/**
 * @brief see #zfCoreMutexLocker
 */
zfclassLikePOD ZF_ENV_EXPORT zfCoreMutexLockerHolder
{
public:
    /** @cond ZFPrivateDoc */
    zfCoreMutexLockerHolder(void)
    {
        zfCoreMutexLock();
    }
    ~zfCoreMutexLockerHolder(void)
    {
        zfCoreMutexUnlock();
    }
    /** @endcond */
};
/**
 * @brief util method to lock current block
 *
 * usage:
 * @code
 *   {
 *       zfCoreMutexLocker(); // lock
 *       if(...) return ; // safe to return
 *   } // unlock after block
 * @endcode
 *
 * you may also use the helper #zfCoreMutexLockerHolder
 * @code
 *   Type var = (zfCoreMutexLockerHolder(), yourFuncSynced());
 * @endcode
 */
#define zfCoreMutexLocker() zfCoreMutexLockerHolder _ZFP_ZFCoreMutexLocker_hold

ZF_NAMESPACE_GLOBAL_END

#endif // #ifndef _ZFI_ZFCoreMutex_h_

