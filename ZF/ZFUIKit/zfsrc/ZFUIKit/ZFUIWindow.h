/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFUIWindow.h
 * @brief window as a ZFUIView
 */

#ifndef _ZFI_ZFUIWindow_h_
#define _ZFI_ZFUIWindow_h_

#include "ZFUISysWindow.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief window level for #ZFUIWindow, value is ensured from low to high
 */
ZFENUM_BEGIN(ZFUIWindowLevel)
    ZFENUM_VALUE(ZFFrameworkBgLowest)
    ZFENUM_VALUE(ZFFrameworkBgLow)
    ZFENUM_VALUE(ZFFrameworkBgNormal)
    ZFENUM_VALUE(ZFFrameworkBgHigh)
    ZFENUM_VALUE(ZFFrameworkBgHighest)
    ZFENUM_VALUE(AppLowest)
    ZFENUM_VALUE(AppLow)
    ZFENUM_VALUE(AppNormal)
    ZFENUM_VALUE(AppHigh)
    ZFENUM_VALUE(AppHighest)
    ZFENUM_VALUE(ZFFrameworkFgLowest)
    ZFENUM_VALUE(ZFFrameworkFgLow)
    ZFENUM_VALUE(ZFFrameworkFgNormal)
    ZFENUM_VALUE(ZFFrameworkFgHigh)
    ZFENUM_VALUE(ZFFrameworkFgHighest)
ZFENUM_SEPARATOR(ZFUIWindowLevel)
    ZFENUM_VALUE_REGISTER(ZFFrameworkBgLowest)
    ZFENUM_VALUE_REGISTER(ZFFrameworkBgLow)
    ZFENUM_VALUE_REGISTER(ZFFrameworkBgNormal)
    ZFENUM_VALUE_REGISTER(ZFFrameworkBgHigh)
    ZFENUM_VALUE_REGISTER(ZFFrameworkBgHighest)
    ZFENUM_VALUE_REGISTER(AppLowest)
    ZFENUM_VALUE_REGISTER(AppLow)
    ZFENUM_VALUE_REGISTER(AppNormal)
    ZFENUM_VALUE_REGISTER(AppHigh)
    ZFENUM_VALUE_REGISTER(AppHighest)
    ZFENUM_VALUE_REGISTER(ZFFrameworkFgLowest)
    ZFENUM_VALUE_REGISTER(ZFFrameworkFgLow)
    ZFENUM_VALUE_REGISTER(ZFFrameworkFgNormal)
    ZFENUM_VALUE_REGISTER(ZFFrameworkFgHigh)
    ZFENUM_VALUE_REGISTER(ZFFrameworkFgHighest)
ZFENUM_END_WITH_DEFAULT(ZFUIWindowLevel, AppNormal)

// ============================================================
// ZFUIWindow
zfclassFwd _ZFP_ZFUIWindowPrivate;
/**
 * @brief window as a ZFUIView
 *
 * a ZFUIWindow is a ZFUIView's manager for showing view tree on screen,
 * it's a ZFUIView in fact, added to #ZFUISysWindow as a normal view,
 * with internal management\n
 * your app should always start with a ZFUIWindow as root view,
 * then build your own view tree\n
 * \n
 * to show a window, simply create a ZFUIWindow's instance and invoke #windowShow,
 * which would internally add this window to #ZFUISysWindow,
 * you must not add ZFUIWindow to any other view manully\n
 * \n
 * after show, window would be automatically retained and you may release it,
 * and it would be released automatically when you hide window by #windowHide\n
 * \n
 * ADVANCED:\n
 * ZFUIWindow would be attached to main ZFUISysWindow (#ZFUISysWindow::mainWindow) by default,
 * you may change its owner ZFUISysWindow by #windowSysWindowSet,
 * but only before #windowShow is called
 */
zfclass ZF_ENV_EXPORT ZFUIWindow : zfextends ZFUIView
{
    ZFOBJECT_DECLARE(ZFUIWindow, ZFUIView)
    ZFSTYLE_DEFAULT_DECLARE(ZFUIWindow)

    // ============================================================
    // observer events
public:
    /**
     * @brief see #ZFObject::observerNotify
     *
     * notified when window's windowSysWindow changed,
     * param0 is the old value
     */
    ZFOBSERVER_EVENT(WindowOwnerSysWindowOnChange)

    /**
     * @brief see #ZFObject::observerNotify
     *
     * notified when window attached to native container
     */
    ZFOBSERVER_EVENT(WindowOnShow)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * notified when window detached from native container
     */
    ZFOBSERVER_EVENT(WindowOnHide)

public:
    /**
     * @brief util method to get window of a view, or null if not in a window
     */
    ZFMETHOD_DECLARE_STATIC_1(ZFUIWindow *, windowForView,
                              ZFMP_IN(ZFUIView *, forView));

    /**
     * @brief util method to get owner sys window for the view,
     *   return null if not in view tree or failed to get
     */
    ZFMETHOD_DECLARE_STATIC_1(ZFUISysWindow *, sysWindowForView,
                              ZFMP_IN(ZFUIView *, view));

public:
    zfoverride
    virtual ZFObject *objectOnInit(void);
    zfoverride
    virtual void objectOnDealloc(void);

    // ============================================================
    // properties
    /**
     * @brief window's level
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(ZFUIWindowLevelEnum, windowLevel,
                                ZFPropertyInitValue(ZFUIWindowLevel::EnumDefault()))
    ZFPROPERTY_CUSTOM_ON_VERIFY_DECLARE(ZFUIWindowLevelEnum, windowLevel);

    /**
     * @brief whether this window update layout accorrding to #ZFUISysWindow::sysWindowMargin,
     *   true by default
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(zfbool, windowLayoutAccorrdingToSysWindowMargin, ZFPropertyInitValue(zftrue))

public:
    /**
     * @brief change owner #ZFUISysWindow, must be called before #windowShow is called
     *
     * usually you should have only one #ZFUISysWindow in your app
     * so you have no need to care about this method
     */
    ZFMETHOD_DECLARE_1(void, windowSysWindowSet,
                       ZFMP_IN(ZFUISysWindow *, windowSysWindow));
    /**
     * @brief get the owner #ZFUISysWindow, even if not showing
     *
     * usually you should have only one #ZFUISysWindow in your app
     * so you have no need to care about this method
     */
    ZFMETHOD_DECLARE_0(ZFUISysWindow *, windowSysWindow);
protected:
    /** @brief see #EventWindowOwnerSysWindowOnChange */
    virtual inline void windowSysWindowOnChange(ZF_IN ZFUISysWindow *oldSysWindow)
    {
        this->observerNotify(ZFUIWindow::EventWindowOwnerSysWindowOnChange(), oldSysWindow);
    }

public:
    /**
     * @brief show the window, automatically retain the window
     */
    ZFMETHOD_DECLARE_0(void, windowShow);
    /**
     * @brief hide the window, automatically release the window
     */
    ZFMETHOD_DECLARE_0(void, windowHide);
    /**
     * @brief whether the window is showing
     */
    ZFMETHOD_DECLARE_0(zfbool, windowShowing);

public:
    /**
     * @brief move window to top of all same level window
     */
    ZFMETHOD_DECLARE_0(void, windowMoveToTop);
    /**
     * @brief move window to bottom of all same level window
     */
    ZFMETHOD_DECLARE_0(void, windowMoveToBottom);

public:
    /**
     * @brief access window's layout param,
     *   automatically call #ZFUIView::layoutRequest
     *
     * default param is fill parent (with sizeWeight (1, 1) and all others zero)
     */
    ZFMETHOD_DECLARE_0(ZFUIViewLayoutParam *, windowLayoutParam);

protected:
    /** @brief see #EventWindowOnShow */
    virtual inline void windowOnShow(void)
    {
        this->observerNotify(ZFUIWindow::EventWindowOnShow());
    }
    /** @brief see #EventWindowOnHide */
    virtual inline void windowOnHide(void)
    {
        this->observerNotify(ZFUIWindow::EventWindowOnHide());
    }

protected:
    zfoverride
    virtual void viewOnAddToParent(ZF_IN ZFUIView *parent);
    zfoverride
    virtual void viewOnRemoveFromParent(ZF_IN ZFUIView *parent);

private:
    _ZFP_ZFUIWindowPrivate *d;
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIWindow_h_

