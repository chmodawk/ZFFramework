/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFImpl_sys_Posix_ZFCore.h"
#include "ZFCore/protocol/ZFProtocolZFObjectMutex.h"
#include "ZFCore/ZFSTLWrapper/zfstl_map.h"

#if ZF_ENV_sys_Posix || ZF_ENV_sys_unknown
#include <pthread.h>
#include <sys/syscall.h>
#include <sys/types.h>

ZF_NAMESPACE_GLOBAL_BEGIN

zfclassNotPOD _ZFP_ZFObjectMutexImpl_sys_Posix_MutexImpl : zfextendsNotPOD ZFObjectMutexImpl
{
public:
    _ZFP_ZFObjectMutexImpl_sys_Posix_MutexImpl(void)
    : ZFObjectMutexImpl()
    {
        pthread_mutexattr_t Attr;
        pthread_mutexattr_init(&Attr);
        pthread_mutexattr_settype(&Attr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&(this->mutex), &Attr);
    }
    virtual ~_ZFP_ZFObjectMutexImpl_sys_Posix_MutexImpl(void)
    {
        pthread_mutex_destroy(&(this->mutex));
    }
public:
    virtual void mutexImplLock(void)
    {
        pthread_mutex_lock(&(this->mutex));
    }
    virtual void mutexImplUnlock(void)
    {
        pthread_mutex_unlock(&(this->mutex));
    }
    virtual zfbool mutexImplTryLock(void)
    {
        return (pthread_mutex_trylock(&(this->mutex)) == 0);
    }

private:
    pthread_mutex_t mutex;
};

ZFPROTOCOL_IMPLEMENTATION_BEGIN(ZFObjectMutexImpl_sys_Posix, ZFObjectMutex, ZFProtocolLevel::e_SystemLow)
public:
    virtual ZFObjectMutexImpl *nativeMutexCreate(void)
    {
        return zfnew(_ZFP_ZFObjectMutexImpl_sys_Posix_MutexImpl);
    }
    virtual void nativeMutexDestroy(ZF_IN ZFObjectMutexImpl *nativeMutex)
    {
        zfdelete(nativeMutex);
    }
ZFPROTOCOL_IMPLEMENTATION_END(ZFObjectMutexImpl_sys_Posix)
ZFPROTOCOL_IMPLEMENTATION_REGISTER(ZFObjectMutexImpl_sys_Posix)

ZF_NAMESPACE_GLOBAL_END
#endif // #if ZF_ENV_sys_Posix || ZF_ENV_sys_unknown

