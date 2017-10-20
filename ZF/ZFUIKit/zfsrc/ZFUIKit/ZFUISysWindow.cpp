/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUISysWindow.h"
#include "protocol/ZFProtocolZFUISysWindow.h"
#include "ZFUIRootView.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfclassNotPOD _ZFP_ZFUISysWindowPrivate
{
public:
    ZFPROTOCOL_INTERFACE_CLASS(ZFUISysWindow) *impl;
    ZFUISysWindowEmbedImpl *embedImpl;
    void *nativeWindow;
    ZFUIRootView *windowRootView;
    ZFUIOrientationFlags windowOrientationFlags;
    ZFUISysWindow *modalWindowOwner;
    ZFUISysWindow *modalWindowShowing;
    ZFUIViewLayoutParam *windowLayoutParam;
    ZFListener windowLayoutParamOnChangeListener;
    zfbool nativeWindowCreated;
    zfbool nativeWindowResumed;
    ZFUIMargin sysWindowMargin;

public:
    _ZFP_ZFUISysWindowPrivate(void)
    : impl(ZFPROTOCOL_ACCESS(ZFUISysWindow))
    , embedImpl(zfnull)
    , nativeWindow(zfnull)
    , windowRootView(zfnull)
    , windowOrientationFlags(ZFUIOrientation::e_Top)
    , modalWindowOwner(zfnull)
    , modalWindowShowing(zfnull)
    , windowLayoutParam(zfnull)
    , windowLayoutParamOnChangeListener(ZFCallbackForRawFunction(_ZFP_ZFUISysWindowPrivate::windowLayoutParamOnChange))
    , nativeWindowCreated(zffalse)
    , nativeWindowResumed(zffalse)
    , sysWindowMargin()
    {
    }

public:
    static ZFLISTENER_PROTOTYPE_EXPAND(windowLayoutParamOnChange)
    {
        ZFUISysWindow *sysWindow = userData->to<ZFObjectHolder *>()->holdedObj;
        if(sysWindow->nativeWindowEmbedImpl() != zfnull)
        {
            sysWindow->nativeWindowEmbedImpl()->windowLayoutParamOnChange(sysWindow);
        }
        else
        {
            ZFPROTOCOL_ACCESS(ZFUISysWindow)->windowLayoutParamOnChange(sysWindow);
        }
    }
};

ZFOBJECT_REGISTER(ZFUISysWindow)

ZFOBSERVER_EVENT_REGISTER(ZFUISysWindow, SysWindowOnCreate)
ZFOBSERVER_EVENT_REGISTER(ZFUISysWindow, SysWindowOnDestroy)
ZFOBSERVER_EVENT_REGISTER(ZFUISysWindow, SysWindowOnResume)
ZFOBSERVER_EVENT_REGISTER(ZFUISysWindow, SysWindowOnPause)
ZFOBSERVER_EVENT_REGISTER(ZFUISysWindow, SysWindowOnRotate)
ZFOBSERVER_EVENT_REGISTER(ZFUISysWindow, SysWindowMarginOnUpdate)

zfautoObject ZFUISysWindow::nativeWindowEmbed(ZF_IN ZFUISysWindowEmbedImpl *embedImpl)
{
    zfautoObject tmp = ZFUISysWindow::ClassData()->newInstance(ZFCallerInfoMake());
    ZFUISysWindow *ret = tmp.to<ZFUISysWindow *>();
    ret->d->embedImpl = embedImpl;
    embedImpl->_ZFP_ownerZFUISysWindow = ret;
    embedImpl->windowLayoutParamOnInit(ret);
    return zfautoObjectCreateMarkCached(ret);
}
ZFUISysWindowEmbedImpl *ZFUISysWindow::nativeWindowEmbedImpl(void)
{
    return d->embedImpl;
}

static ZFUISysWindow *_ZFP_ZFUISysWindow_mainWindowRegistered = zfnull;
static ZFUISysWindow *_ZFP_ZFUISysWindow_mainWindow = zfnull;
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFUISysWindowMainWindowCleanup, ZFLevelZFFrameworkLow)
{
}
ZF_GLOBAL_INITIALIZER_DESTROY(ZFUISysWindowMainWindowCleanup)
{
    ZFPROTOCOL_INTERFACE_CLASS(ZFUISysWindow) *impl = ZFPROTOCOL_TRY_ACCESS(ZFUISysWindow);
    if(impl != zfnull)
    {
        impl->mainWindowOnCleanup();
    }
    _ZFP_ZFUISysWindow_mainWindowRegistered = zfnull;
    _ZFP_ZFUISysWindow_mainWindow = zfnull;
}
ZF_GLOBAL_INITIALIZER_END(ZFUISysWindowMainWindowCleanup)
void ZFUISysWindow::mainWindowRegister(ZF_IN ZFUISysWindow *window)
{
    zfCoreAssertWithMessage(_ZFP_ZFUISysWindow_mainWindow == zfnull,
        zfTextA("mainWindowRegister must be called before accessing mainWindow"));
    _ZFP_ZFUISysWindow_mainWindowRegistered = window;
}

ZFMETHOD_DEFINE_0(ZFUISysWindow, ZFUISysWindow *, mainWindow)
{
    if(_ZFP_ZFUISysWindow_mainWindow == zfnull)
    {
        if(_ZFP_ZFUISysWindow_mainWindowRegistered != zfnull)
        {
            _ZFP_ZFUISysWindow_mainWindow = _ZFP_ZFUISysWindow_mainWindowRegistered;
        }
        else
        {
            _ZFP_ZFUISysWindow_mainWindow = ZFPROTOCOL_ACCESS(ZFUISysWindow)->mainWindow();
        }
    }
    return _ZFP_ZFUISysWindow_mainWindow;
}

ZFMETHOD_DEFINE_0(ZFUISysWindow, const ZFUIMargin &, sysWindowMargin)
{
    return d->sysWindowMargin;
}
void ZFUISysWindow::_ZFP_ZFUISysWindow_sysWindowMarginSet(ZF_IN const ZFUIMargin &sysWindowMargin)
{
    ZFUIMargin sysWindowMarginOld = d->sysWindowMargin;
    d->sysWindowMargin = ZFUIMarginApplyScaleReversely(sysWindowMargin, this->rootView()->scaleFixed());
    if(d->sysWindowMargin != sysWindowMarginOld)
    {
        this->sysWindowMarginOnUpdate(sysWindowMarginOld);
    }
}
void ZFUISysWindow::sysWindowMarginOnUpdate(ZF_IN const ZFUIMargin &sysWindowMarginOld)
{
    if(this->observerHasAdd(ZFUISysWindow::EventSysWindowMarginOnUpdate()))
    {
        ZFPointerHolder *param0 = ZFPointerHolder::cacheGet();
        param0->holdedData = &sysWindowMarginOld;
        this->observerNotify(ZFUISysWindow::EventSysWindowMarginOnUpdate(), param0);
        ZFPointerHolder::cacheAdd(param0);
    }
}

void ZFUISysWindow::objectOnInit(void)
{
    zfsuper::objectOnInit();
    d = zfpoolNew(_ZFP_ZFUISysWindowPrivate);
    d->windowRootView = zfRetainWithoutLeakTest(ZFUIRootView::ClassData()->newInstanceWithoutLeakTest().to<ZFUIRootView *>());
    d->windowLayoutParam = zfAllocWithoutLeakTest(ZFUIViewLayoutParam);
    d->windowLayoutParam->sizeParamSet(ZFUISizeParamFillWidthFillHeight());
}
void ZFUISysWindow::objectOnInitFinish(void)
{
    zfsuper::objectOnInitFinish();
    d->impl->windowLayoutParamOnInit(this);
    d->windowLayoutParam->observerAdd(ZFUILayoutParam::EventLayoutParamOnChange(), d->windowLayoutParamOnChangeListener, this->objectHolder());
}
void ZFUISysWindow::objectOnDeallocPrepare(void)
{
    if(d->nativeWindowResumed)
    {
        if(d->embedImpl != zfnull)
        {
            d->embedImpl->notifyOnPause(this);
        }
        else
        {
            d->impl->notifyOnPause(this);
        }
    }
    if(d->nativeWindowCreated)
    {
        if(d->embedImpl != zfnull)
        {
            d->embedImpl->notifyOnDestroy(this);
        }
        else
        {
            d->impl->notifyOnDestroy(this);
        }
    }

    if(d->embedImpl != zfnull)
    {
        d->embedImpl->nativeWindowOnCleanup(this);
    }
    else
    {
        d->impl->nativeWindowOnCleanup(this);
    }
    zfsuper::objectOnDeallocPrepare();
}
void ZFUISysWindow::objectOnDealloc(void)
{
    zfReleaseWithoutLeakTest(d->windowLayoutParam);
    zfReleaseWithoutLeakTest(d->windowRootView);
    zfpoolDelete(d);
    d = zfnull;
    zfsuper::objectOnDealloc();
}

ZFMETHOD_DEFINE_0(ZFUISysWindow, void *, nativeWindow)
{
    return d->nativeWindow;
}

ZFMETHOD_DEFINE_0(ZFUISysWindow, zfbool, nativeWindowIsCreated)
{
    return d->nativeWindowCreated;
}
ZFMETHOD_DEFINE_0(ZFUISysWindow, zfbool, nativeWindowIsResumed)
{
    return d->nativeWindowResumed;
}

ZFMETHOD_DEFINE_0(ZFUISysWindow, ZFUIOrientationEnum, windowOrientation)
{
    if(d->embedImpl != zfnull)
    {
        return d->embedImpl->windowOrientation(this);
    }
    else
    {
        return d->impl->windowOrientation(this);
    }
}
ZFMETHOD_DEFINE_1(ZFUISysWindow, void, windowOrientationFlagsSet,
                  ZFMP_IN(const ZFUIOrientationFlags &, windowOrientationFlags))
{
    zfuint tmp = 0;
    if(ZFBitTest(windowOrientationFlags.enumValue(), ZFUIOrientation::e_Left))
    {
        ZFBitSet(tmp, ZFUIOrientation::e_Left);
    }
    if(ZFBitTest(windowOrientationFlags.enumValue(), ZFUIOrientation::e_Top))
    {
        ZFBitSet(tmp, ZFUIOrientation::e_Top);
    }
    if(ZFBitTest(windowOrientationFlags.enumValue(), ZFUIOrientation::e_Right))
    {
        ZFBitSet(tmp, ZFUIOrientation::e_Right);
    }
    if(ZFBitTest(windowOrientationFlags.enumValue(), ZFUIOrientation::e_Bottom))
    {
        ZFBitSet(tmp, ZFUIOrientation::e_Bottom);
    }
    if(d->windowOrientationFlags != tmp)
    {
        d->windowOrientationFlags = tmp;
        if(d->embedImpl != zfnull)
        {
            d->embedImpl->windowOrientationFlagsSet(this, tmp);
        }
        else
        {
            if(this->nativeWindow() != zfnull)
            {
                d->impl->windowOrientationFlagsSet(this, tmp);
            }
        }
    }
}
ZFMETHOD_DEFINE_0(ZFUISysWindow, const ZFUIOrientationFlags &, windowOrientationFlags)
{
    return d->windowOrientationFlags;
}

ZFMETHOD_DEFINE_0(ZFUISysWindow, ZFUISysWindow *, modalWindowShow)
{
    zfCoreAssertWithMessage(d->modalWindowShowing == zfnull, zfTextA("already has a showing modal window, you must finish it first"));

    ZFUISysWindow *modalWindow = zfnull;
    if(d->embedImpl != zfnull)
    {
        modalWindow = d->embedImpl->modalWindowShow(this);
    }
    else
    {
        zfCoreAssertWithMessage(this->nativeWindow() != zfnull,
            zfTextA("you can only create modal window after ZFUISysWindow created, see ZFUISysWindow::nativeWindowIsCreated"));

        modalWindow = d->impl->modalWindowShow(this);
    }

    d->modalWindowShowing = modalWindow;
    modalWindow->d->modalWindowOwner = this;
    return modalWindow;
}
ZFMETHOD_DEFINE_0(ZFUISysWindow, void, modalWindowFinish)
{
    zfCoreAssertWithMessage(d->modalWindowOwner != zfnull, zfTextA("not a modal window"));

    if(d->embedImpl != zfnull)
    {
        d->embedImpl->modalWindowFinish(d->modalWindowOwner, this);
    }
    else
    {
        d->impl->modalWindowFinish(d->modalWindowOwner, this);
    }
    d->modalWindowOwner->d->modalWindowShowing = zfnull;
    d->modalWindowOwner = zfnull;

    zfRelease(this);
}
ZFMETHOD_DEFINE_0(ZFUISysWindow, ZFUISysWindow *, modalWindowGetShowing)
{
    return d->modalWindowShowing;
}
ZFMETHOD_DEFINE_0(ZFUISysWindow, ZFUISysWindow *, modalWindowGetOwner)
{
    return d->modalWindowOwner;
}

ZFMETHOD_DEFINE_0(ZFUISysWindow, ZFUIViewLayoutParam *, windowLayoutParam)
{
    return d->windowLayoutParam;
}
ZFMETHOD_DEFINE_0(ZFUISysWindow, ZFUIRootView *, rootView)
{
    return d->windowRootView;
}

ZFUIRect ZFUISysWindow::_ZFP_ZFUISysWindow_measureWindow(ZF_IN const ZFUIRect &rootRefRect)
{
    ZFUIRect ret = ZFUIRectApplyScale(ZFUIViewLayoutParam::layoutParamApply(
            ZFUIRectApplyScaleReversely(rootRefRect, this->rootView()->scaleFixed()),
            this->rootView(),
            this->windowLayoutParam()),
        this->rootView()->scaleFixed());
    return ret;
}
void ZFUISysWindow::_ZFP_ZFUISysWindow_onCreate(ZF_IN void *nativeWindow)
{
    zfCoreAssertWithMessage(!d->nativeWindowCreated, zfTextA("window already created"));

    d->nativeWindow = nativeWindow;
    d->nativeWindowCreated = zftrue;

    void *nativeParentView = zfnull;
    if(d->embedImpl != zfnull)
    {
        d->embedImpl->windowOrientationFlagsSet(this, d->windowOrientationFlags);
        d->embedImpl->nativeWindowRootViewOnAdd(this, nativeParentView);
    }
    else
    {
        d->impl->windowOrientationFlagsSet(this, d->windowOrientationFlags);
        d->impl->nativeWindowRootViewOnAdd(this, nativeParentView);
    }
    ZFUIView::_ZFP_ZFUIView_nativeViewNotifyAdd(this->rootView(), nativeParentView);

    this->observerNotify(ZFUISysWindow::EventSysWindowOnCreate());
}
void ZFUISysWindow::_ZFP_ZFUISysWindow_onDestroy(void)
{
    zfCoreAssertWithMessage(d->nativeWindowCreated, zfTextA("window not created"));
    zfCoreAssertWithMessage(!d->nativeWindowResumed, zfTextA("window still resumed"));
    d->nativeWindowCreated = zffalse;

    if(d->embedImpl != zfnull)
    {
        d->embedImpl->nativeWindowRootViewOnRemove(this);
    }
    else
    {
        d->impl->nativeWindowRootViewOnRemove(this);
    }

    ZFUIView::_ZFP_ZFUIView_nativeViewNotifyRemove(this->rootView());

    this->observerNotify(ZFUISysWindow::EventSysWindowOnDestroy());

    if(this == _ZFP_ZFUISysWindow_mainWindow)
    {
        d->impl->mainWindowOnDestroy();
    }
}
void ZFUISysWindow::_ZFP_ZFUISysWindow_onResume(void)
{
    zfCoreAssertWithMessage(d->nativeWindowCreated, zfTextA("window not created"));
    zfCoreAssertWithMessage(!d->nativeWindowResumed, zfTextA("window already resumed"));

    d->nativeWindowResumed = zftrue;
    this->observerNotify(ZFUISysWindow::EventSysWindowOnResume());
}
void ZFUISysWindow::_ZFP_ZFUISysWindow_onPause(void)
{
    zfCoreAssertWithMessage(d->nativeWindowCreated, zfTextA("window not created"));
    zfCoreAssertWithMessage(d->nativeWindowResumed, zfTextA("window already paused"));

    d->nativeWindowResumed = zffalse;
    this->observerNotify(ZFUISysWindow::EventSysWindowOnPause());
}
void ZFUISysWindow::_ZFP_ZFUISysWindow_onRotate(void)
{
    zfCoreAssertWithMessage(d->nativeWindowCreated, zfTextA("window not created"));
    zfCoreAssertWithMessage(d->nativeWindowResumed, zfTextA("window not resumed"));
    this->observerNotify(ZFUISysWindow::EventSysWindowOnRotate());
}

// ============================================================
ZFOBJECT_REGISTER(ZFUISysWindowEmbedImpl)

void ZFUISysWindowEmbedImpl::nativeWindowRootViewOnAdd(ZF_IN ZFUISysWindow *sysWindow,
                                                       ZF_OUT void *&nativeParentView)
{
}
void ZFUISysWindowEmbedImpl::nativeWindowRootViewOnRemove(ZF_IN ZFUISysWindow *sysWindow)
{
}

ZFUISysWindow *ZFUISysWindowEmbedImpl::modalWindowShow(ZF_IN ZFUISysWindow *sysWindowOwner)
{
    return ZFPROTOCOL_ACCESS(ZFUISysWindow)->modalWindowShow(sysWindowOwner);
}
void ZFUISysWindowEmbedImpl::modalWindowFinish(ZF_IN ZFUISysWindow *sysWindowOwner,
                                               ZF_IN ZFUISysWindow *sysWindowToFinish)
{
    ZFPROTOCOL_ACCESS(ZFUISysWindow)->modalWindowFinish(sysWindowOwner, sysWindowToFinish);
}

void ZFUISysWindowEmbedImpl::windowLayoutParamOnInit(ZF_IN ZFUISysWindow *sysWindow)
{
}
void ZFUISysWindowEmbedImpl::windowLayoutParamOnChange(ZF_IN ZFUISysWindow *sysWindow)
{
}

ZFUIOrientationEnum ZFUISysWindowEmbedImpl::windowOrientation(ZF_IN ZFUISysWindow *sysWindow)
{
    return ZFUIOrientation::e_Top;
}
void ZFUISysWindowEmbedImpl::windowOrientationFlagsSet(ZF_IN ZFUISysWindow *sysWindow,
                                                       ZF_IN const ZFUIOrientationFlags &flags)
{
}

ZF_NAMESPACE_GLOBAL_END

