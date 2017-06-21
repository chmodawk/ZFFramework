/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFUIPageBasic.h
 * @brief basic #ZFUIPage with animation logic
 */

#ifndef _ZFI_ZFUIPageBasic_h_
#define _ZFI_ZFUIPageBasic_h_

#include "ZFUIPage.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
zfclassFwd ZFUIPageManagerBasic;
zfclassFwd _ZFP_ZFUIPageManagerBasicPrivate;
zfclassFwd _ZFP_ZFUIPageBasicPrivate;
/**
 * @brief basic page with animation logic,
 *   see #ZFUIPageManager and #ZFUIPageManagerBasic for how to use
 */
zfabstract ZF_ENV_EXPORT ZFUIPageBasic : zfextends ZFObject, zfimplements ZFUIPage
{
    ZFOBJECT_DECLARE_ABSTRACT(ZFUIPageBasic, ZFObject)
    ZFIMPLEMENTS_DECLARE(ZFUIPage)

    // ============================================================
    // observers
public:
    /**
     * @brief see #ZFObject::observerNotify
     *
     * called when page about to start animation,
     * ensured called even if no animation to start for convenient\n
     * param0 is the animation to start or null if no animation to start,
     * param1 is the #ZFUIPagePauseReason or #ZFUIPageResumeReason
     */
    ZFOBSERVER_EVENT(PageAniOnStart)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * called when page about to stop animation,
     * ensured called even if no animation to start for convenient\n
     * param0 is the animation to stop or null if no animation to stop,
     * param1 is the #ZFUIPagePauseReason or #ZFUIPageResumeReason
     */
    ZFOBSERVER_EVENT(PageAniOnStop)

    // ============================================================
    // pageAni
public:
    /**
     * @brief page's animation
     *
     * we have these animations for page to setup:
     * -  pageAniResumeByRequest / pagePauseAniToBackground:
     *   used when a page is resumed by user request,
     *   and the previous resume page would be sent to background
     * -  pageAniResumeFromBackground / pagePauseAniBeforeDestroy:
     *   used when a foreground page is destroyed by user request,
     *   and background page would result to be moved to foreground
     *
     * see #ZFUIPageManagerBasic::pageAniOnUpdate for more info
     */
    ZFPROPERTY_RETAIN(ZFAnimation *, pageAniResumeByRequest)
    /**
     * @brief page's animation, see #pageAniResumeByRequest
     */
    ZFPROPERTY_RETAIN(ZFAnimation *, pageAniResumeFromBackground)
    /**
     * @brief page's animation, see #pageAniResumeByRequest
     */
    ZFPROPERTY_RETAIN(ZFAnimation *, pageAniPauseToBackground)
    /**
     * @brief page's animation, see #pageAniResumeByRequest
     */
    ZFPROPERTY_RETAIN(ZFAnimation *, pageAniPauseBeforeDestroy)

private:
    zfbool _ZFP_ZFUIPage_pageAniCanChange;
public:
    /**
     * @brief the final animation being used when page stack changed, null to disable animation
     *
     * this value can only be updated by #pageAniOnUpdate,
     * you may override the method to override the animation\n
     * this value would be reset to null when animation stopped or page destroyed\n
     */
    virtual void pageAniSet(ZF_IN ZFAnimation *pageAni);
    /**
     * @brief see #pageAniSet
     */
    virtual ZFAnimation *pageAni(void);

public:
    /**
     * @brief whether this page need higher priority for animation,
     *   typically a higher priority animation would have its view on the top
     */
    zfbool pageAniPriorityNeedHigher;
protected:
    /**
     * @brief for page to update it's final animation, see #ZFUIPageManagerBasic::pageAniOnUpdate
     */
    virtual void pageAniOnUpdate(ZF_IN ZFUIPageBasic *resumePageOrNull,
                                 ZF_IN ZFUIPageBasic *pausePageOrNull,
                                 ZF_IN ZFUIPageResumeReasonEnum reason);
    /**
     * @brief called to update animation's target, do nothing by default
     */
    virtual void pageAniOnUpdateAniTarget(ZF_IN ZFAnimation *pageAni)
    {
    }

    // ============================================================
    // event
protected:
    /** @brief see #EventPageAniOnStart */
    virtual void pageAniOnStart(ZF_IN ZFAnimation *pageAni,
                                ZF_IN ZFEnum *pagePauseReasonOrResumeReason)
    {
        this->observerNotify(ZFUIPageBasic::EventPageAniOnStart(),
                             pageAni, pagePauseReasonOrResumeReason);
    }
    /** @brief see #EventPageAniOnStop */
    virtual void pageAniOnStop(ZF_IN ZFAnimation *pageAni,
                               ZF_IN ZFEnum *pagePauseReasonOrResumeReason)
    {
        this->observerNotify(ZFUIPageBasic::EventPageAniOnStop(),
                             pageAni, pagePauseReasonOrResumeReason);
    }

    // ============================================================
    // override
protected:
    zfoverride
    virtual void pageOnCreate(void);
    zfoverride
    virtual void pageOnResume(ZF_IN ZFUIPageResumeReasonEnum reason);
    zfoverride
    virtual void pageOnPause(ZF_IN ZFUIPagePauseReasonEnum reason);
    zfoverride
    virtual void pageOnDestroy(void);

protected:
    zfoverride
    virtual void pageDelayDestroyOnCheck(void);

private:
    _ZFP_ZFUIPageBasicPrivate *d;
    friend zfclassFwd ZFUIPageManagerBasic;
    friend zfclassFwd _ZFP_ZFUIPageManagerBasicPrivate;
    friend zfclassFwd _ZFP_ZFUIPageBasicPrivate;
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIPageBasic_h_

