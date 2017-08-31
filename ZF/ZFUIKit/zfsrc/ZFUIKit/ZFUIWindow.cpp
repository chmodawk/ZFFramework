/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIWindow.h"
#include "ZFUIRootView.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFENUM_DEFINE(ZFUIWindowLevel)

ZFSTYLE_DEFAULT_DEFINE(ZFUIWindow)

// ============================================================
// _ZFP_ZFUIWindowPrivate
zfclassNotPOD _ZFP_ZFUIWindowPrivate
{
public:
    ZFUISysWindow *windowSysWindow;
    ZFUIViewLayoutParam *windowLayoutParam;
    zfbool windowRemoveOverrideFlag;

public:
    _ZFP_ZFUIWindowPrivate(void)
    : windowSysWindow(zfnull)
    , windowLayoutParam(zfnull)
    , windowRemoveOverrideFlag(zffalse)
    {
    }
};

// ============================================================
// ZFUIWindow
ZFOBJECT_REGISTER(ZFUIWindow)

ZFOBSERVER_EVENT_REGISTER(ZFUIWindow, WindowOwnerSysWindowOnChange)
ZFOBSERVER_EVENT_REGISTER(ZFUIWindow, WindowLayoutParamOnInit)
ZFOBSERVER_EVENT_REGISTER(ZFUIWindow, WindowOnShow)
ZFOBSERVER_EVENT_REGISTER(ZFUIWindow, WindowOnHide)

ZFUIWindow *ZFUIWindow::windowForView(ZF_IN ZFUIView *forView)
{
    while(forView != zfnull && !forView->classData()->classIsSubclassOf(ZFUIWindow::ClassData()))
    {
        forView = forView->viewParent();
    }
    if(forView != zfnull)
    {
        return ZFCastZFObject(ZFUIWindow *, forView);
    }
    return zfnull;
}

ZFUISysWindow *ZFUIWindow::sysWindowForView(ZF_IN ZFUIView *view)
{
    ZFUIWindow *window = ZFUIWindow::windowForView(view);
    return ((window != zfnull) ? window->windowSysWindow() : zfnull);
}

ZFObject *ZFUIWindow::objectOnInit(void)
{
    zfsuper::objectOnInit();
    d = zfpoolNew(_ZFP_ZFUIWindowPrivate);
    d->windowSysWindow = ZFUISysWindow::mainWindow();
    d->windowLayoutParam = zfAlloc(ZFUIViewLayoutParam);
    d->windowLayoutParam->sizeParamSet(ZFUISizeParamFillWidthFillHeight());
    return this;
}
void ZFUIWindow::objectOnDealloc(void)
{
    zfRelease(d->windowLayoutParam);
    zfpoolDelete(d);
    d = zfnull;
    zfsuper::objectOnDealloc();
}
void ZFUIWindow::objectOnInitFinish(void)
{
    zfsuper::objectOnInitFinish();
    this->windowLayoutParamOnInit();
}

// ============================================================
// properties
ZFPROPERTY_CUSTOM_ON_VERIFY_DEFINE(ZFUIWindow, ZFUIWindowLevelEnum, windowLevel)
{
    zfCoreAssertWithMessage(!this->windowShowing(), zfTextA("you must not change window level while it's showing"));
}

void ZFUIWindow::windowSysWindowSet(ZF_IN ZFUISysWindow *windowSysWindow)
{
    if(d->windowSysWindow != windowSysWindow)
    {
        zfCoreAssertWithMessage(!this->windowShowing(), zfTextA("you must not change window's owner while it's showing"));
        zfCoreAssertWithMessage(windowSysWindow != zfnull, zfTextA("null owner sys window"));

        ZFUISysWindow *oldSysWindow = d->windowSysWindow;
        d->windowSysWindow = windowSysWindow;
        this->windowSysWindowOnChange(oldSysWindow);
    }
}
ZFUISysWindow *ZFUIWindow::windowSysWindow(void)
{
    return d->windowSysWindow;
}

void ZFUIWindow::windowShow(void)
{
    zfindex addToIndex = 0;
    ZFCoreArrayPOD<ZFUIView *> tmpArray = this->windowSysWindow()->rootView()->childArray();
    for(zfindex i = 0; i < tmpArray.count(); ++i)
    {
        ZFUIWindow *tmpWindow = ZFCastZFObject(ZFUIWindow *, tmpArray.get(i));
        if(tmpWindow != zfnull)
        {
            if(tmpWindow->windowLevel() <= this->windowLevel())
            {
                addToIndex = i + 1;
            }
            else
            {
                break;
            }
        }
    }
    this->windowSysWindow()->rootView()->childAdd(this, d->windowLayoutParam, addToIndex);
}
void ZFUIWindow::windowHide(void)
{
    zfRetainWithoutLeakTest(this);
    d->windowRemoveOverrideFlag = zftrue;
    this->viewRemoveFromParent();
    d->windowRemoveOverrideFlag = zffalse;
    zfReleaseWithoutLeakTest(this);
}
zfbool ZFUIWindow::windowShowing(void)
{
    return (this->viewParent() != zfnull);
}

void ZFUIWindow::windowMoveToTop(void)
{
    if(!this->windowShowing())
    {
        return ;
    }

    ZFCoreArrayPOD<ZFUIView *> tmpArray = this->windowSysWindow()->rootView()->childArray();
    ZFUIWindowLevelEnum selfWindowLevel = this->windowLevel();
    zfindex topIndex = zfindexMax;
    zfindex selfIndex = zfindexMax;
    for(zfindex i = tmpArray.count() - 1; i != zfindexMax; --i)
    {
        ZFUIWindow *tmpWindow = ZFCastZFObject(ZFUIWindow *, tmpArray.get(i));
        if(tmpWindow != zfnull)
        {
            if(topIndex == zfindexMax && tmpWindow->windowLevel() == selfWindowLevel)
            {
                topIndex = i;
            }
            if(tmpWindow == this)
            {
                selfIndex = i;
                break;
            }
        }
    }
    if(topIndex != selfIndex && topIndex != zfindexMax && selfIndex != zfindexMax)
    {
        this->windowSysWindow()->rootView()->childMove(selfIndex, topIndex);
    }
}
void ZFUIWindow::windowMoveToBottom(void)
{
    if(!this->windowShowing())
    {
        return ;
    }

    ZFCoreArrayPOD<ZFUIView *> tmpArray = this->windowSysWindow()->rootView()->childArray();
    ZFUIWindowLevelEnum selfWindowLevel = this->windowLevel();
    zfindex bottomIndex = zfindexMax;
    zfindex selfIndex = zfindexMax;
    for(zfindex i = 0; i < tmpArray.count(); ++i)
    {
        ZFUIWindow *tmpWindow = ZFCastZFObject(ZFUIWindow *, tmpArray.get(i));
        if(tmpWindow != zfnull)
        {
            if(bottomIndex == zfindexMax && tmpWindow->windowLevel() == selfWindowLevel)
            {
                bottomIndex = i;
            }
            if(tmpWindow == this)
            {
                selfIndex = i;
                break;
            }
        }
    }
    if(bottomIndex != selfIndex && bottomIndex != zfindexMax && selfIndex != zfindexMax)
    {
        this->windowSysWindow()->rootView()->childMove(selfIndex, bottomIndex);
    }
}

ZFUIViewLayoutParam *ZFUIWindow::windowLayoutParam(void)
{
    return d->windowLayoutParam;
}

void ZFUIWindow::viewOnAddToParent(ZF_IN ZFUIView *parent)
{
    zfCoreAssertWithMessage(parent->classData()->classIsSubclassOf(ZFUIRootView::ClassData()), zfTextA("you must not add a window to another view"));
    zfsuper::viewOnAddToParent(parent);

    this->windowOnShow();
}
void ZFUIWindow::viewOnRemoveFromParent(ZF_IN ZFUIView *parent)
{
    // should not check remove here,
    // since it's all right to remove this window when owner sys window deallocated or when hide window
    zfsuper::viewOnRemoveFromParent(parent);

    if(d->windowRemoveOverrideFlag)
    {
        this->windowOnHide();
    }
    else
    {
        this->windowHide();
    }
}

ZF_NAMESPACE_GLOBAL_END

