/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUtility_test.h"

ZF_NAMESPACE_GLOBAL_BEGIN

#if 0
ZF_GLOBAL_INITIALIZER_INIT(ZFUtility_ZFAnimation_debug_LogEvent)
{
    this->taskOwner = zfAllocWithoutLeakTest(ZFObject);

    ZFLISTENER_LOCAL(aniOnAlloc, {
        if(listenerData.sender->classData()->classIsTypeOf(ZFAnimation::ClassData()))
        {
            zfLogTrimT() << zfLogCurTimeString() << listenerData.sender << zfText("alloc");
        }
    })
    ZFObjectGlobalEventObserver.observerAdd(ZFObject::EventObjectAfterAlloc(), aniOnAlloc);

    ZFLISTENER_LOCAL(aniOnDealloc, {
        if(listenerData.sender->classData()->classIsTypeOf(ZFAnimation::ClassData()))
        {
            zfLogTrimT() << zfLogCurTimeString() << listenerData.sender << zfText("dealloc");
        }
    })
    ZFObjectGlobalEventObserver.observerAdd(ZFObject::EventObjectBeforeDealloc(), aniOnDealloc);

    ZFLISTENER_LOCAL(aniOnInvalid, {
        zfLogTrimT() << zfLogCurTimeString() << listenerData.sender << zfText("invalid");
    })
    ZFObjectGlobalEventObserver.observerAdd(ZFAnimation::EventAniOnInvalid(), aniOnInvalid);

    ZFLISTENER_LOCAL(aniOnStart, {
        zfLogTrimT() << zfLogCurTimeString() << listenerData.sender << zfText("start");
    })
    ZFObjectGlobalEventObserver.observerAdd(ZFAnimation::EventAniOnStart(), aniOnStart);

    ZFLISTENER_LOCAL(aniOnStop, {
        zfLogTrimT() << zfLogCurTimeString() << listenerData.sender << zfText("stop");
    })
    ZFObjectGlobalEventObserver.observerAdd(ZFAnimation::EventAniOnStop(), aniOnStop);
}
ZF_GLOBAL_INITIALIZER_DESTROY(ZFUtility_ZFAnimation_debug_LogEvent)
{
    ZFObjectGlobalEventObserver.observerRemoveByOwner(this->taskOwner);
    zfReleaseWithoutLeakTest(this->taskOwner);
}
private:
    ZFObject *taskOwner;
ZF_GLOBAL_INITIALIZER_END(ZFUtility_ZFAnimation_debug_LogEvent)
#endif

ZF_NAMESPACE_GLOBAL_END

