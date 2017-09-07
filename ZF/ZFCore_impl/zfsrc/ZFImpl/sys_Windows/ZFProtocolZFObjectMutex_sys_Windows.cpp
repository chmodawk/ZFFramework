/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFImpl_sys_Windows_ZFCore.h"
#include "ZFCore/protocol/ZFProtocolZFObjectMutex.h"
#include "ZFCore/ZFSTLWrapper/zfstl_map.h"

#if ZF_ENV_sys_Windows
#include <Windows.h>

ZF_NAMESPACE_GLOBAL_BEGIN

zfclassNotPOD _ZFP_ZFObjectMutexImpl_sys_Windows_MutexImpl : zfextendsNotPOD ZFObjectMutexImpl
{
public:
    _ZFP_ZFObjectMutexImpl_sys_Windows_MutexImpl(void)
    : ZFObjectMutexImpl()
    {
        this->INVALID_THREAD_ID = (DWORD)INVALID_HANDLE_VALUE;
        InitializeCriticalSection(&(this->mutex));
        InitializeCriticalSection(&(this->mutexParamLocker));
        this->runningThreadId = this->INVALID_THREAD_ID;
    }
    virtual ~_ZFP_ZFObjectMutexImpl_sys_Windows_MutexImpl(void)
    {
        DeleteCriticalSection(&(this->mutex));
        DeleteCriticalSection(&(this->mutexParamLocker));
    }
public:
    virtual void mutexImplLock(void)
    {
        EnterCriticalSection(&(this->mutexParamLocker));
        DWORD curThreadId = GetCurrentThreadId();
        if(this->runningThreadId == this->INVALID_THREAD_ID)
        {
            this->lockedThreadCountMap[curThreadId] = 1;
            LeaveCriticalSection(&(this->mutexParamLocker));
            // first time to lock the object
            EnterCriticalSection(&(this->mutex));

            // now we owned the lock
            this->runningThreadId = curThreadId;
        }
        else
        {
            zfstlmap<DWORD, zfindex>::iterator it = this->lockedThreadCountMap.find(curThreadId);
            if(curThreadId == this->runningThreadId)
            {
                ++(it->second);
                LeaveCriticalSection(&(this->mutexParamLocker));
                // lock the same thread more than one time, no need to lock again
            }
            else
            {
                if(it == this->lockedThreadCountMap.end())
                {
                    this->lockedThreadCountMap[curThreadId] = 1;
                }
                else
                {
                    ++(it->second);
                }
                LeaveCriticalSection(&(this->mutexParamLocker));
                // lock while another thread acquiring the lock,
                // should be locked here until another thread release the lock
                EnterCriticalSection(&(this->mutex));

                // now we owned the lock
                this->runningThreadId = curThreadId;
            }
        }
    }
    virtual void mutexImplUnlock(void)
    {
        EnterCriticalSection(&(this->mutexParamLocker));
        DWORD curThreadId = GetCurrentThreadId();
        zfstlmap<DWORD, zfindex>::iterator it = this->lockedThreadCountMap.find(curThreadId);
        if(curThreadId == this->runningThreadId)
        {
            --(it->second);
            if(it->second == 0)
            {
                this->lockedThreadCountMap.erase(it);
                this->runningThreadId = this->INVALID_THREAD_ID;
                LeaveCriticalSection(&(this->mutexParamLocker));
                // all locks locked by current thread are relesed, unlock
                LeaveCriticalSection(&(this->mutex));
            }
            else
            {
                LeaveCriticalSection(&(this->mutexParamLocker));
                // current thread still hold some locks, just return
            }
        }
        else
        {
            LeaveCriticalSection(&(this->mutexParamLocker));

            // current thread doesn't lock, it's a error state
            zfCoreCriticalShouldNotGoHere();
            return ;
        }
    }
    virtual zfbool mutexImplTryLock(void)
    {
        EnterCriticalSection(&(this->mutexParamLocker));
        DWORD curThreadId = GetCurrentThreadId();
        if(this->runningThreadId == this->INVALID_THREAD_ID)
        {
            this->runningThreadId = curThreadId;
            this->lockedThreadCountMap[this->runningThreadId] = 1;
            LeaveCriticalSection(&(this->mutexParamLocker));
            // first time to lock the object
            EnterCriticalSection(&(this->mutex));
            return zftrue;
        }
        else
        {
            zfstlmap<DWORD, zfindex>::iterator it = this->lockedThreadCountMap.find(curThreadId);
            if(curThreadId == this->runningThreadId)
            {
                ++(it->second);
                LeaveCriticalSection(&(this->mutexParamLocker));
                // lock the same thread more than one time, no need to lock again
                return zftrue;
            }
            else
            {
                LeaveCriticalSection(&(this->mutexParamLocker));
                // lock while another thread acquiring the lock,
                // just return false for mutexTryLock
                return zffalse;
            }
        }
    }

private:
    CRITICAL_SECTION mutex;
    CRITICAL_SECTION mutexParamLocker;
    zfstlmap<DWORD, zfindex> lockedThreadCountMap;
    DWORD runningThreadId;
    DWORD INVALID_THREAD_ID;
};

ZFPROTOCOL_IMPLEMENTATION_BEGIN(ZFObjectMutexImpl_sys_Windows, ZFObjectMutex, ZFProtocolLevel::e_SystemLow)
public:
    virtual ZFObjectMutexImpl *nativeMutexCreate(void)
    {
        return zfnew(_ZFP_ZFObjectMutexImpl_sys_Windows_MutexImpl);
    }
    virtual void nativeMutexDestroy(ZF_IN ZFObjectMutexImpl *nativeMutex)
    {
        zfdelete(nativeMutex);
    }
ZFPROTOCOL_IMPLEMENTATION_END(ZFObjectMutexImpl_sys_Windows)
ZFPROTOCOL_IMPLEMENTATION_REGISTER(ZFObjectMutexImpl_sys_Windows)

ZF_NAMESPACE_GLOBAL_END
#endif // #if ZF_ENV_sys_Windows

