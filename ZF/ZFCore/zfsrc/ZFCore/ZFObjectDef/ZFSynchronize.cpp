/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFSynchronize.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
ZFObject *_ZFP_zfsynchronizeObject = zfnull;
ZFCoreArrayPOD<ZFSynchronizeLogCallback> ZFSynchronizeLogCallbackList;
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(zfsynchronizeDataHolder, ZFLevelZFFrameworkEssential)
{
    _ZFP_zfsynchronizeObject = zfAllocWithoutLeakTest(ZFObject);
}
ZF_GLOBAL_INITIALIZER_DESTROY(zfsynchronizeDataHolder)
{
    zfReleaseWithoutLeakTest(_ZFP_zfsynchronizeObject);
    _ZFP_zfsynchronizeObject = zfnull;
    ZFSynchronizeLogCallbackList.removeAll();
}
ZF_GLOBAL_INITIALIZER_END(zfsynchronizeDataHolder)

static void _ZFP_ZFSynchronizeLogAction(ZF_IN const ZFCallerInfo &callerInfo,
                                        ZF_IN const zfcharA *fmt,
                                        ...)
{
    va_list vaList;
    va_start(vaList, fmt);
    zfstring text;
    zfstringAppendV(text, fmt, vaList);
    va_end(vaList);
    for(zfindex i = 0; i < ZFSynchronizeLogCallbackList.count(); ++i)
    {
        ZFSynchronizeLogCallbackList[i](callerInfo, text.cString());
    }
}

// ============================================================
_ZFP_ZFSynchronizedObjectContainerWithLog::_ZFP_ZFSynchronizedObjectContainerWithLog(ZF_IN ZFObject *obj,
                                                                                     ZF_IN const ZFCallerInfo &callerInfo)
: m_obj(obj)
, callerInfo(callerInfo)
{
    if(obj == zfnull)
    {
        zfCoreCriticalErrorPrepare();
        _ZFP_ZFSynchronizeLogAction(callerInfo,
            zfTextA("try synchronize a null object"));
        zfCoreCriticalError();
        return ;
    }
    zfRetainWithoutLeakTest(m_obj);
    _ZFP_ZFSynchronizeLogAction(callerInfo,
        zfTextA("lock object %s"),
        zfsCoreZ2A(m_obj->objectInfoOfInstance().cString()));
    m_obj->_ZFP_ZFObjectLock();
    _ZFP_ZFSynchronizeLogAction(callerInfo,
        zfTextA("lock object %s success"),
        zfsCoreZ2A(m_obj->objectInfoOfInstance().cString()));
}
_ZFP_ZFSynchronizedObjectContainerWithLog::~_ZFP_ZFSynchronizedObjectContainerWithLog(void)
{
    _ZFP_ZFSynchronizeLogAction(callerInfo,
        zfTextA("unlock object %s"),
        zfsCoreZ2A(m_obj->objectInfoOfInstance().cString()));
    m_obj->_ZFP_ZFObjectUnlock();
    _ZFP_ZFSynchronizeLogAction(callerInfo,
        zfTextA("unlock object %s success"),
        zfsCoreZ2A(m_obj->objectInfoOfInstance().cString()));
    zfReleaseWithoutLeakTest(m_obj);
}

// ============================================================
void _ZFP_ZFSynchronizedObjectLockWithLog(ZF_IN ZFObject *obj,
                                          ZF_IN const ZFCallerInfo &callerInfo)
{
    if(obj == zfnull)
    {
        zfCoreCriticalErrorPrepare();
        _ZFP_ZFSynchronizeLogAction(callerInfo,
            zfTextA("try lock a null object"));
        zfCoreCriticalError();
        return ;
    }

    zfRetainWithoutLeakTest(obj);
    _ZFP_ZFSynchronizeLogAction(callerInfo,
        zfTextA("lock object %s"),
        zfsCoreZ2A(obj->objectInfoOfInstance().cString()));
    obj->_ZFP_ZFObjectLock();
    _ZFP_ZFSynchronizeLogAction(callerInfo,
        zfTextA("lock object %s success"),
        callerInfo.callerInfoA().cString(),
        zfsCoreZ2A(obj->objectInfoOfInstance().cString()));
}
void _ZFP_ZFSynchronizedObjectUnlockWithLog(ZF_IN ZFObject *obj,
                                            ZF_IN const ZFCallerInfo &callerInfo)
{
    if(obj == zfnull)
    {
        zfCoreCriticalErrorPrepare();
        _ZFP_ZFSynchronizeLogAction(callerInfo,
            zfTextA("try unlock a null object"));
        zfCoreCriticalError();
        return ;
    }

    _ZFP_ZFSynchronizeLogAction(callerInfo,
        zfTextA("unlock object %s"),
        zfsCoreZ2A(obj->objectInfoOfInstance().cString()));
    obj->_ZFP_ZFObjectUnlock();
    _ZFP_ZFSynchronizeLogAction(callerInfo,
        zfTextA("unlock object %s success"),
        zfsCoreZ2A(obj->objectInfoOfInstance().cString()));
    zfReleaseWithoutLeakTest(obj);
}

// ============================================================
_ZFP_ZFSynchronizeContainerWithLog::_ZFP_ZFSynchronizeContainerWithLog(ZF_IN const ZFCallerInfo &callerInfo)
: locked(zffalse)
, callerInfo()
{
    if(_ZFP_zfsynchronizeObject)
    {
        zfRetainWithoutLeakTest(_ZFP_zfsynchronizeObject);
        _ZFP_ZFSynchronizeLogAction(callerInfo,
            zfTextA("lock global sync object"));
        _ZFP_zfsynchronizeObject->_ZFP_ZFObjectLock();
        _ZFP_ZFSynchronizeLogAction(callerInfo,
            zfTextA("lock global sync object success"));
        this->locked = zftrue;
    }
}
_ZFP_ZFSynchronizeContainerWithLog::~_ZFP_ZFSynchronizeContainerWithLog(void)
{
    if(this->locked && _ZFP_zfsynchronizeObject)
    {
        _ZFP_ZFSynchronizeLogAction(callerInfo,
            zfTextA("unlock global sync object"));
        _ZFP_zfsynchronizeObject->_ZFP_ZFObjectUnlock();
        _ZFP_ZFSynchronizeLogAction(callerInfo,
            zfTextA("unlock global sync object success"));
        zfReleaseWithoutLeakTest(_ZFP_zfsynchronizeObject);
    }
}

// ============================================================
void _ZFP_ZFSynchronizeLockWithLog(ZF_IN const ZFCallerInfo &callerInfo)
{
    if(_ZFP_zfsynchronizeObject)
    {
        zfRetainWithoutLeakTest(_ZFP_zfsynchronizeObject);
        _ZFP_ZFSynchronizeLogAction(callerInfo,
            zfTextA("lock global sync object"));
        _ZFP_zfsynchronizeObject->_ZFP_ZFObjectLock();
        _ZFP_ZFSynchronizeLogAction(callerInfo,
            zfTextA("lock global sync object success"));
    }
}
void _ZFP_ZFSynchronizeUnlockWithLog(ZF_IN const ZFCallerInfo &callerInfo)
{
    if(_ZFP_zfsynchronizeObject)
    {
        _ZFP_ZFSynchronizeLogAction(callerInfo,
            zfTextA("unlock global sync object"));
        _ZFP_zfsynchronizeObject->_ZFP_ZFObjectUnlock();
        _ZFP_ZFSynchronizeLogAction(callerInfo,
            zfTextA("unlock global sync object success"));
        zfReleaseWithoutLeakTest(_ZFP_zfsynchronizeObject);
    }
}

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_0(void, zfsynchronizeLock)
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_0(void, zfsynchronizeUnlock)
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(void, zfsynchronizedObjectLock, ZFMP_IN(ZFObject *, obj))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(void, zfsynchronizedObjectUnlock, ZFMP_IN(ZFObject *, obj))

ZF_NAMESPACE_GLOBAL_END
#endif

