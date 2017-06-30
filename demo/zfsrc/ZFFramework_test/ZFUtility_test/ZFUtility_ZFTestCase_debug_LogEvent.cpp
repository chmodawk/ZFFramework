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

#if 1
ZF_GLOBAL_INITIALIZER_INIT(ZFUtility_ZFTestCase_debug_LogEvent)
{
    ZFLISTENER_LOCAL(testCaseOnOutput, {
        zfLogTrimT()
            << zfLogCurTimeString()
            << zfstringWithFormat(zfText("[%s]"), listenerData.sender->classData()->className())
            << listenerData.param0->to<ZFPointerHolder *>()->holdedDataPointer<const zfchar *>();
    })
    this->testCaseOnOutputListener = testCaseOnOutput;
    ZFObjectGlobalEventObserver().observerAdd(ZFTestCase::EventTestCaseOnOutput(), this->testCaseOnOutputListener);

    ZFLISTENER_LOCAL(testCaseOnStart, {
        zfLogTrimT()
            << zfLogCurTimeString()
            << zfstringWithFormat(zfText("[%s]"), listenerData.sender->classData()->className())
            << zfText("========================== start ===========================");
    })
    this->testCaseOnStartListener = testCaseOnStart;
    ZFObjectGlobalEventObserver().observerAdd(ZFTestCase::EventTestCaseOnStart(), this->testCaseOnStartListener);

    ZFLISTENER_LOCAL(testCaseOnProgress, {
        zfLogTrimT()
            << zfLogCurTimeString()
            << zfstringWithFormat(zfText("[%s]"), listenerData.sender->classData()->className())
            << zfText("progress updated");
    })
    this->testCaseOnProgressListener = testCaseOnProgress;
    ZFObjectGlobalEventObserver().observerAdd(ZFTestCase::EventTestCaseOnProgress(), this->testCaseOnProgressListener);

    ZFLISTENER_LOCAL(testCaseOnStop, {
        zfLogTrimT()
            << zfLogCurTimeString()
            << zfstringWithFormat(zfText("[%s]"), listenerData.sender->classData()->className())
            << zfText("-------------------------- stop ----------------------------");
    })
    this->testCaseOnStopListener = testCaseOnStop;
    ZFObjectGlobalEventObserver().observerAdd(ZFTestCase::EventTestCaseOnStop(), this->testCaseOnStopListener);
}
ZF_GLOBAL_INITIALIZER_DESTROY(ZFUtility_ZFTestCase_debug_LogEvent)
{
    ZFObjectGlobalEventObserver().observerRemove(ZFTestCase::EventTestCaseOnOutput(), this->testCaseOnOutputListener);
    ZFObjectGlobalEventObserver().observerRemove(ZFTestCase::EventTestCaseOnStart(), this->testCaseOnStartListener);
    ZFObjectGlobalEventObserver().observerRemove(ZFTestCase::EventTestCaseOnProgress(), this->testCaseOnProgressListener);
    ZFObjectGlobalEventObserver().observerRemove(ZFTestCase::EventTestCaseOnStop(), this->testCaseOnStopListener);
}
private:
    ZFListener testCaseOnOutputListener;
    ZFListener testCaseOnStartListener;
    ZFListener testCaseOnProgressListener;
    ZFListener testCaseOnStopListener;
ZF_GLOBAL_INITIALIZER_END(ZFUtility_ZFTestCase_debug_LogEvent)
#endif

ZF_NAMESPACE_GLOBAL_END

