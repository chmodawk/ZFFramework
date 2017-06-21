/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIPageBasic.h"
#include "ZFUIPageManagerBasic.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
zfclassNotPOD _ZFP_ZFUIPageBasicPrivate
{
public:
    ZFAnimation *pageAni;

public:
    static ZFLISTENER_PROTOTYPE_EXPAND(pageAniOnFinish)
    {
        ZFUIPageBasic *page = userData->to<ZFObjectHolder *>()->holdedObj;
        page->pageDelayDestroyNotifyFinish();
    }

public:
    _ZFP_ZFUIPageBasicPrivate(void)
    : pageAni(zfnull)
    {
    }
};

// ============================================================
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFUIPageBasicListenerHolder, ZFLevelZFFrameworkEssential)
{
    this->pageAniOnFinishListener = ZFCallbackForRawFunction(_ZFP_ZFUIPageBasicPrivate::pageAniOnFinish);
}
public:
    ZFListener pageAniOnFinishListener;
ZF_GLOBAL_INITIALIZER_END(ZFUIPageBasicListenerHolder)

// ============================================================
ZFOBJECT_REGISTER(ZFUIPageBasic)

ZFOBSERVER_EVENT_REGISTER(ZFUIPageBasic, PageAniOnStart)
ZFOBSERVER_EVENT_REGISTER(ZFUIPageBasic, PageAniOnStop)

void ZFUIPageBasic::pageAniSet(ZF_IN ZFAnimation *pageAni)
{
    zfCoreAssertWithMessage(this->_ZFP_ZFUIPage_pageAniCanChange,
        zfTextA("you can only change pageAni during")
        zfTextA(" Page::pageAniOnUpdate")
        zfTextA("or Manager::pageAniOnUpdate"));
    ZFPropertyChange(d->pageAni, pageAni);
}
ZFAnimation *ZFUIPageBasic::pageAni(void)
{
    return d->pageAni;
}

void ZFUIPageBasic::pageAniOnUpdate(ZF_IN ZFUIPageBasic *resumePageOrNull,
                                    ZF_IN ZFUIPageBasic *pausePageOrNull,
                                    ZF_IN ZFUIPageResumeReasonEnum reason)
{
    switch(reason)
    {
        case ZFUIPageResumeReason::e_ByManagerResume:
            break;
        case ZFUIPageResumeReason::e_ByRequest:
            if(resumePageOrNull == this)
            {
                if(pausePageOrNull != zfnull)
                {
                    pausePageOrNull->pageAniSet(pausePageOrNull->pageAniPauseToBackground());
                }
                this->pageAniSet(this->pageAniResumeByRequest());
            }
            break;
        case ZFUIPageResumeReason::e_FromBackground:
            if(pausePageOrNull == this)
            {
                this->pageAniPriorityNeedHigher = zftrue;
                this->pageAniSet(this->pageAniPauseBeforeDestroy());
                if(resumePageOrNull != zfnull)
                {
                    resumePageOrNull->pageAniSet(resumePageOrNull->pageAniResumeFromBackground());
                }
            }
            break;
        default:
            zfCoreCriticalShouldNotGoHere();
            return ;
    }
}

// ============================================================
// override
void ZFUIPageBasic::pageOnCreate(void)
{
    zfsuperI(ZFUIPage)::pageOnCreate();
    d = zfpoolNew(_ZFP_ZFUIPageBasicPrivate);
    this->_ZFP_ZFUIPage_pageAniCanChange = zffalse;
}
void ZFUIPageBasic::pageOnResume(ZF_IN ZFUIPageResumeReasonEnum reason)
{
    zfsuperI(ZFUIPage)::pageOnResume(reason);
}
void ZFUIPageBasic::pageOnPause(ZF_IN ZFUIPagePauseReasonEnum reason)
{
    zfsuperI(ZFUIPage)::pageOnPause(reason);
}
void ZFUIPageBasic::pageOnDestroy(void)
{
    this->_ZFP_ZFUIPage_pageAniCanChange = zftrue;
    this->pageAniSet(zfnull);
    this->_ZFP_ZFUIPage_pageAniCanChange = zffalse;
    zfpoolDelete(d);
    d = zfnull;
    zfsuperI(ZFUIPage)::pageOnDestroy();
}

void ZFUIPageBasic::pageDelayDestroyOnCheck(void)
{
    zfsuperI(ZFUIPage)::pageDelayDestroyOnCheck();
    if(this->pageAni() != zfnull && this->pageAni()->aniRunning())
    {
        this->pageAni()->observerAdd(ZFObserverAddParam()
                .eventIdSet(ZFAnimation::EventAniOnStop())
                .observerSet(ZF_GLOBAL_INITIALIZER_INSTANCE(ZFUIPageBasicListenerHolder)->pageAniOnFinishListener)
                .userDataSet(this->objectHolder())
                .autoRemoveAfterActivateSet(zftrue)
            );
        this->pageDelayDestroyEnable();
    }
}

ZF_NAMESPACE_GLOBAL_END

