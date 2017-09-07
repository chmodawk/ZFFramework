/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFImpl_sys_Windows_ZFCore.h"
#include "ZFCore/protocol/ZFProtocolZFSemaphore.h"

#if ZF_ENV_sys_Windows
#include <Windows.h>

ZF_NAMESPACE_GLOBAL_BEGIN

zfclassNotPOD _ZFP_ZFSemaphoreImpl_sys_Windows_Token
{
public:
    zfindex waiterCount;
    HANDLE sema;
    CRITICAL_SECTION semaMutex;
    CRITICAL_SECTION mutexParamLocker;
};

ZFPROTOCOL_IMPLEMENTATION_BEGIN(ZFSemaphoreImpl_sys_Windows, ZFSemaphore, ZFProtocolLevel::e_SystemLow)
public:
    virtual void *nativeSemaphoreCreate(ZF_IN ZFSemaphore *semaphore)
    {
        _ZFP_ZFSemaphoreImpl_sys_Windows_Token *semaphoreToken = zfnew(_ZFP_ZFSemaphoreImpl_sys_Windows_Token);
        semaphoreToken->waiterCount = 0;
        semaphoreToken->sema = CreateSemaphore(zfnull, 0, MAXLONG, zfnull);
        InitializeCriticalSection(&(semaphoreToken->semaMutex));
        InitializeCriticalSection(&(semaphoreToken->mutexParamLocker));
        return semaphoreToken;
    }
    virtual void nativeSemaphoreDestroy(ZF_IN ZFSemaphore *semaphore,
                                        ZF_IN void *nativeSemaphore)
    {
        _ZFP_ZFSemaphoreImpl_sys_Windows_Token *semaphoreToken = ZFCastStatic(_ZFP_ZFSemaphoreImpl_sys_Windows_Token *, nativeSemaphore);
        CloseHandle(semaphoreToken->sema);
        DeleteCriticalSection(&(semaphoreToken->semaMutex));
        DeleteCriticalSection(&(semaphoreToken->mutexParamLocker));
        zfdelete(semaphoreToken);
    }

    virtual void semaphoreLock(ZF_IN ZFSemaphore *semaphore)
    {
        _ZFP_ZFSemaphoreImpl_sys_Windows_Token *semaphoreToken = ZFCastStatic(_ZFP_ZFSemaphoreImpl_sys_Windows_Token *, semaphore->nativeSemaphore());
        EnterCriticalSection(&(semaphoreToken->mutexParamLocker));
    }
    virtual void semaphoreUnlock(ZF_IN ZFSemaphore *semaphore)
    {
        _ZFP_ZFSemaphoreImpl_sys_Windows_Token *semaphoreToken = ZFCastStatic(_ZFP_ZFSemaphoreImpl_sys_Windows_Token *, semaphore->nativeSemaphore());
        LeaveCriticalSection(&(semaphoreToken->mutexParamLocker));
    }

    virtual void semaphoreSignal(ZF_IN ZFSemaphore *semaphore)
    {
        _ZFP_ZFSemaphoreImpl_sys_Windows_Token *semaphoreToken = ZFCastStatic(_ZFP_ZFSemaphoreImpl_sys_Windows_Token *, semaphore->nativeSemaphore());

        EnterCriticalSection(&(semaphoreToken->mutexParamLocker));
        if(semaphoreToken->waiterCount > 0)
        {
            --(semaphoreToken->waiterCount);
            LeaveCriticalSection(&(semaphoreToken->mutexParamLocker));
            this->semaSignal(semaphoreToken, 1);
        }
        else
        {
            LeaveCriticalSection(&(semaphoreToken->mutexParamLocker));
        }
    }
    virtual void semaphoreBroadcast(ZF_IN ZFSemaphore *semaphore)
    {
        _ZFP_ZFSemaphoreImpl_sys_Windows_Token *semaphoreToken = ZFCastStatic(_ZFP_ZFSemaphoreImpl_sys_Windows_Token *, semaphore->nativeSemaphore());

        EnterCriticalSection(&(semaphoreToken->mutexParamLocker));
        if(semaphoreToken->waiterCount > 0)
        {
            zfindex tmp = semaphoreToken->waiterCount;
            semaphoreToken->waiterCount = 0;
            LeaveCriticalSection(&(semaphoreToken->mutexParamLocker));
            this->semaSignal(semaphoreToken, tmp);
        }
        else
        {
            LeaveCriticalSection(&(semaphoreToken->mutexParamLocker));
        }
    }
    virtual void semaphoreWait(ZF_IN ZFSemaphore *semaphore)
    {
        _ZFP_ZFSemaphoreImpl_sys_Windows_Token *semaphoreToken = ZFCastStatic(_ZFP_ZFSemaphoreImpl_sys_Windows_Token *, semaphore->nativeSemaphore());

        EnterCriticalSection(&(semaphoreToken->mutexParamLocker));
        ++(semaphoreToken->waiterCount);
        LeaveCriticalSection(&(semaphoreToken->mutexParamLocker));
        this->semaWait(semaphoreToken);
    }
    virtual zfbool semaphoreWait(ZF_IN ZFSemaphore *semaphore,
                                 ZF_IN const zftimet &miliSecsTimeout)
    {
        _ZFP_ZFSemaphoreImpl_sys_Windows_Token *semaphoreToken = ZFCastStatic(_ZFP_ZFSemaphoreImpl_sys_Windows_Token *, semaphore->nativeSemaphore());

        EnterCriticalSection(&(semaphoreToken->mutexParamLocker));
        ++(semaphoreToken->waiterCount);
        LeaveCriticalSection(&(semaphoreToken->mutexParamLocker));

        if(this->semaWait(semaphoreToken, miliSecsTimeout))
        {
            return zftrue;
        }
        else
        {
            EnterCriticalSection(&(semaphoreToken->mutexParamLocker));
            if(semaphoreToken->waiterCount > 0)
            {
                --(semaphoreToken->waiterCount);
            }
            LeaveCriticalSection(&(semaphoreToken->mutexParamLocker));
            return zffalse;
        }
    }

public:
    void semaSignal(ZF_IN _ZFP_ZFSemaphoreImpl_sys_Windows_Token *semaphoreToken,
                    ZF_IN zfindex num1orBroadcastNum)
    {
        LeaveCriticalSection(&(semaphoreToken->semaMutex));
        ReleaseSemaphore(semaphoreToken->sema, num1orBroadcastNum, zfnull);
        EnterCriticalSection(&(semaphoreToken->semaMutex));
    }
    void semaWait(ZF_IN _ZFP_ZFSemaphoreImpl_sys_Windows_Token *semaphoreToken)
    {
        LeaveCriticalSection(&(semaphoreToken->semaMutex));
        WaitForSingleObject(semaphoreToken->sema, INFINITE);
        EnterCriticalSection(&(semaphoreToken->semaMutex));
    }
    zfbool semaWait(ZF_IN _ZFP_ZFSemaphoreImpl_sys_Windows_Token *semaphoreToken,
                    ZF_IN const zftimet &miliSecs)
    {
        LeaveCriticalSection(&(semaphoreToken->semaMutex));
        zfbool ret = (WaitForSingleObject(semaphoreToken->sema, (DWORD)(miliSecs)) == WAIT_OBJECT_0);
        EnterCriticalSection(&(semaphoreToken->semaMutex));
        return ret;
    }
ZFPROTOCOL_IMPLEMENTATION_END(ZFSemaphoreImpl_sys_Windows)
ZFPROTOCOL_IMPLEMENTATION_REGISTER(ZFSemaphoreImpl_sys_Windows)

ZF_NAMESPACE_GLOBAL_END
#endif

