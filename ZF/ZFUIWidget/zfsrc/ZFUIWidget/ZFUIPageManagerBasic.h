/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFUIPageManagerBasic.h
 * @brief abstract page manager with animation logic
 */

#ifndef _ZFI_ZFUIPageManagerBasic_h_
#define _ZFI_ZFUIPageManagerBasic_h_

#include "ZFUIPageManager.h"
#include "ZFUIPageBasic.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
zfclassFwd _ZFP_ZFUIPageManagerBasicPrivate;
/**
 * @brief abstract page manager with animation logic
 */
zfabstract ZF_ENV_EXPORT ZFUIPageManagerBasic : zfextends ZFObject, zfimplements ZFUIPageManager
{
    ZFOBJECT_DECLARE_ABSTRACT(ZFUIPageManagerBasic, ZFObject)
    ZFIMPLEMENTS_DECLARE(ZFUIPageManager)

    // ============================================================
    // observers
public:
    /**
     * @brief see #ZFObject::observerNotify
     *
     * see #ZFUIPageBasic::EventPageAniOnStart
     */
    ZFOBSERVER_EVENT(PageAniOnStart)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * see #ZFUIPageBasic::EventPageAniOnStop
     */
    ZFOBSERVER_EVENT(PageAniOnStop)

    // ============================================================
    // animation
public:
    /**
     * @brief manually override default page animation for once
     *
     * set null to disable animation\n
     * overrided animation would be reset after animation stop,
     * or, you may cancel manually by #pageAniOverrideForOnceCancel
     * newly overrided animation would override old settings
     */
    ZFMETHOD_DECLARE_3(void, pageAniOverrideForOnce,
                       ZFMP_IN(ZFAnimation *, pageAniResume),
                       ZFMP_IN(ZFAnimation *, pageAniPause),
                       ZFMP_IN_OPT(zfbool, pageAniPauseHasHigherPriority, zffalse));
    /**
     * @brief see #pageAniOverrideForOnceCancel
     */
    ZFMETHOD_DECLARE_0(void, pageAniOverrideForOnceCancel);
protected:
    /**
     * @brief used by #pageAniOnUpdate to check update overrided animation
     */
    zffinal zfbool pageAniOverrideForOnceCheckUpdate(ZF_IN ZFUIPageBasic *resumePageOrNull,
                                                     ZF_IN ZFUIPageBasic *pausePageOrNull,
                                                     ZF_IN ZFUIPageResumeReasonEnum reason);
protected:
    /**
     * @brief called to achieve actual page animation
     *
     * by default, this method would:
     * -  if #pageAniOverrideForOnce has been set, use the overrided animation
     * -  otherwise, use page's default animation setting
     *
     * you may override without calling super to override default animation\n
     * \n
     * \n
     * the default impl:
     * @code
     *   ZFUIPageBasic *pausePage = xxx; // page to pause
     *   ZFUIPageBasic *resumePage = xxx; // page to resume
     *   resumePage->pageAniPriorityNeedHigher = zffalse;
     *   pausePage->pageAniPriorityNeedHigher = zffalse;
     *   pausePage->pageAniOnUpdate(resumePage, pausePage, reason);
     *   resumePage->pageAniOnUpdate(resumePage, pausePage, reason);
     *   zfbool pausePageHasHigherPriority = (!resumePage->pageAniPriorityNeedHigher && pausePage->pageAniPriorityNeedHigher);
     *   pageManager->pageAniOnUpdatePriority(resumePage, pausePage, pausePageHasHigherPriority);
     * @endcode
     * by default, #pageAniOnUpdate would update page animation
     * accorrding to page's resume and pause reason,
     * and page requested by user would have higher animation priority (request resume or request destroy)\n
     * the page's animation:
     * -  #ZFUIPageBasic::pageAniResumeByRequest
     * -  #ZFUIPageBasic::pageAniResumeFromBackground
     * -  #ZFUIPageBasic::pageAniPauseToBackground
     * -  #ZFUIPageBasic::pageAniPauseBeforeDestroy
     */
    virtual void pageAniOnUpdate(ZF_IN ZFUIPageBasic *resumePageOrNull,
                                 ZF_IN ZFUIPageBasic *pausePageOrNull,
                                 ZF_IN ZFUIPageResumeReasonEnum reason);
    /**
     * @brief called for subclass to do extra update accorrding the priority
     *
     * typically, for page with higher priority, its page view should be placed at top of view tree
     */
    virtual inline void pageAniOnUpdatePriority(ZF_IN ZFUIPageBasic *resumePageOrNull,
                                                ZF_IN ZFUIPageBasic *pausePageOrNull,
                                                ZF_IN zfbool pausePageHasHigherPriority)
    {
    }

    // ============================================================
    // page manager life cycle
protected:
    zfoverride
    virtual void managerOnCreate(void);
    zfoverride
    virtual void managerOnResume(void);
    zfoverride
    virtual void managerOnPause(void);
    zfoverride
    virtual void managerOnDestroy(void);

    // ============================================================
    // page life cycle
protected:
    zfoverride
    virtual void pageAfterResume(ZF_IN ZFUIPage *page, ZF_IN ZFUIPageResumeReasonEnum reason);
    zfoverride
    virtual void pageAfterPause(ZF_IN ZFUIPage *page, ZF_IN ZFUIPagePauseReasonEnum reason);

    // ============================================================
    // events
protected:
    /** @brief see #EventPageAniOnStart */
    virtual void pageAniOnStart(ZF_IN ZFUIPageBasic *page,
                                ZF_IN ZFAnimation *pageAni,
                                ZF_IN ZFEnum *pagePauseReasonOrResumeReason)
    {
        this->observerNotifyWithCustomSender(page,
                                             ZFUIPageManagerBasic::EventPageAniOnStart(),
                                             pageAni,
                                             pagePauseReasonOrResumeReason);
    }
    /** @brief see #EventPageAniOnStop */
    virtual void pageAniOnStop(ZF_IN ZFUIPageBasic *page,
                               ZF_IN ZFAnimation *pageAni,
                               ZF_IN ZFEnum *pagePauseReasonOrResumeReason)
    {
        this->observerNotifyWithCustomSender(page,
                                             ZFUIPageManagerBasic::EventPageAniOnStop(),
                                             pageAni,
                                             pagePauseReasonOrResumeReason);
    }
private:
    _ZFP_ZFUIPageManagerBasicPrivate *d;
    friend zfclassFwd _ZFP_ZFUIPageManagerBasicPrivate;
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIPageManagerBasic_h_

