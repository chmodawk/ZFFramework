/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIOnScreenKeyboardAutoResize.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfclassFwd _ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData;
static void _ZFP_ZFUIOnScreenKeyboardAutoResize_doStart(ZF_IN ZFUIWindow *window);
static void _ZFP_ZFUIOnScreenKeyboardAutoResize_doStop(ZF_IN ZFUIWindow *window, ZF_IN _ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData *taskData);
static ZFLISTENER_PROTOTYPE_EXPAND(_ZFP_ZFUIOnScreenKeyboardAutoResize_onScreenKeyboardStateChange);
static ZFLISTENER_PROTOTYPE_EXPAND(_ZFP_ZFUIOnScreenKeyboardAutoResize_windowOnShow);
static ZFLISTENER_PROTOTYPE_EXPAND(_ZFP_ZFUIOnScreenKeyboardAutoResize_windowLayoutMarginChange);

zfclass _ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData, ZFObject)

public:
    virtual ZFObject *objectOnInit(void)
    {
        zfsuper::objectOnInit();
        this->ownerWindow = zfnull;
        this->startCount = 1;
        this->layoutMarginSaved = ZFUIMarginZero();
        this->layoutMarginHasStored = zffalse;
        return this;
    }
    virtual void objectOnDeallocPrepare(void)
    {
        _ZFP_ZFUIOnScreenKeyboardAutoResize_doStop(this->ownerWindow, this);
        zfsuper::objectOnDeallocPrepare();
    }

public:
    ZFUIWindow *ownerWindow;
    zfindex startCount;
    ZFUIMargin layoutMarginSaved;
    zfbool layoutMarginHasStored;
};

ZFMETHOD_FUNC_DEFINE_1(void, ZFUIOnScreenKeyboardAutoResizeStart,
                       ZFMP_IN(ZFUIWindow *, window))
{
    if(window == zfnull)
    {
        return ;
    }

    zfCoreMutexLocker();

    _ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData *taskData = ZFAny(window->tagGet(
        _ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData::ClassData()->className()));
    if(taskData != zfnull)
    {
        taskData->startCount += 1;
        return ;
    }
    zfblockedAlloc(_ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData, taskDataTmp);
    taskData = taskDataTmp;
    taskData->ownerWindow = window;
    window->tagSetMarkCached(_ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData::ClassData()->className(), taskDataTmp);

    _ZFP_ZFUIOnScreenKeyboardAutoResize_doStart(window);
}
ZFMETHOD_FUNC_DEFINE_1(void, ZFUIOnScreenKeyboardAutoResizeStop,
                       ZFMP_IN(ZFUIWindow *, window))
{
    if(window == zfnull)
    {
        return ;
    }

    zfCoreMutexLocker();

    _ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData *taskData = ZFAny(window->tagGet(
        _ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData::ClassData()->className()));
    if(taskData == zfnull)
    {
        return ;
    }
    if(taskData->startCount > 1)
    {
        taskData->startCount -= 1;
        return ;
    }
    window->tagRemove(_ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData::ClassData()->className());
}

// ============================================================
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFUIOnScreenKeyboardAutoResizeDataHolder, ZFLevelZFFrameworkEssential)
{
    this->onScreenKeyboardStateChangeListener = ZFCallbackForRawFunction(_ZFP_ZFUIOnScreenKeyboardAutoResize_onScreenKeyboardStateChange);
    this->windowOnShowListener = ZFCallbackForRawFunction(_ZFP_ZFUIOnScreenKeyboardAutoResize_windowOnShow);
    this->windowLayoutMarginChangeListener = ZFCallbackForRawFunction(_ZFP_ZFUIOnScreenKeyboardAutoResize_windowLayoutMarginChange);
}
ZF_GLOBAL_INITIALIZER_DESTROY(ZFUIOnScreenKeyboardAutoResizeDataHolder)
{
    zfCoreAssertWithMessageTrim(this->windowList.isEmpty(),
        zfText("ZFUIOnScreenKeyboardAutoResizeStart/ZFUIOnScreenKeyboardAutoResizeStop mismatch, have you forgot to stop?"));
}
public:
    ZFCoreArrayPOD<ZFUIWindow *> windowList;
    ZFListener onScreenKeyboardStateChangeListener;
    ZFListener windowOnShowListener;
    ZFListener windowLayoutMarginChangeListener;
ZF_GLOBAL_INITIALIZER_END(ZFUIOnScreenKeyboardAutoResizeDataHolder)

static void _ZFP_ZFUIOnScreenKeyboardAutoResize_apply(ZF_IN ZFUIWindow *window, ZF_IN ZFUIOnScreenKeyboardState *state)
{
    ZF_GLOBAL_INITIALIZER_CLASS(ZFUIOnScreenKeyboardAutoResizeDataHolder) *d = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFUIOnScreenKeyboardAutoResizeDataHolder);
    _ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData *taskData = ZFAny(window->tagGet(
        _ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData::ClassData()->className()));
    if(taskData == zfnull)
    {
        return ;
    }
    const ZFUIMargin &layoutMarginOld = (taskData->layoutMarginHasStored ? taskData->layoutMarginSaved : window->windowLayoutParam()->layoutMargin());
    if(state->keyboardShowing() && window->windowShowing())
    {
        ZFUIMargin margin = layoutMarginOld;
        ZFUIRect windowFrame = ZFUIRectApplyMargin(ZFUIViewPositionOnScreen(window->viewParent()), margin);
        ZFUIRect clientFrame = ZFUIRectZero();
        state->keyboardFixClientFrameT(clientFrame);
        if(ZFUIRectGetLeft(clientFrame) > ZFUIRectGetLeft(windowFrame))
        {
            margin.left += ZFUIRectGetLeft(clientFrame) - ZFUIRectGetLeft(windowFrame);
        }
        if(ZFUIRectGetTop(clientFrame) > ZFUIRectGetTop(windowFrame))
        {
            margin.top += ZFUIRectGetTop(clientFrame) - ZFUIRectGetTop(windowFrame);
        }
        if(ZFUIRectGetRight(clientFrame) < ZFUIRectGetRight(windowFrame))
        {
            margin.right += ZFUIRectGetRight(windowFrame) - ZFUIRectGetRight(clientFrame);
        }
        if(ZFUIRectGetBottom(clientFrame) < ZFUIRectGetBottom(windowFrame))
        {
            margin.bottom += ZFUIRectGetBottom(windowFrame) - ZFUIRectGetBottom(clientFrame);
        }

        if(!taskData->layoutMarginHasStored)
        {
            taskData->layoutMarginHasStored = zftrue;
            taskData->layoutMarginSaved = layoutMarginOld;
        }

        window->windowLayoutParam()->observerRemove(
            ZFObject::EventObjectPropertyValueOnUpdate(),
            d->windowLayoutMarginChangeListener);
        window->windowLayoutParam()->layoutMarginSet(margin);
        window->windowLayoutParam()->observerAdd(
            ZFObject::EventObjectPropertyValueOnUpdate(),
            d->windowLayoutMarginChangeListener,
            window->objectHolder());
    }
    else
    {
        window->windowLayoutParam()->observerRemove(
            ZFObject::EventObjectPropertyValueOnUpdate(),
            d->windowLayoutMarginChangeListener);
        taskData->layoutMarginHasStored = zffalse;
        window->windowLayoutParam()->layoutMarginSet(layoutMarginOld);
    }
}

static void _ZFP_ZFUIOnScreenKeyboardAutoResize_doStart(ZF_IN ZFUIWindow *window)
{
    ZF_GLOBAL_INITIALIZER_CLASS(ZFUIOnScreenKeyboardAutoResizeDataHolder) *d = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFUIOnScreenKeyboardAutoResizeDataHolder);
    if(d->windowList.isEmpty())
    {
        ZFObjectGlobalEventObserver().observerAdd(ZFUIOnScreenKeyboardState::EventKeyboardStateOnChange(), d->onScreenKeyboardStateChangeListener);
    }
    d->windowList.add(window);

    window->observerAdd(ZFUIWindow::EventWindowOnShow(), d->windowOnShowListener);
    _ZFP_ZFUIOnScreenKeyboardAutoResize_apply(window, ZFUIOnScreenKeyboardState::instanceForView(window));
}
static void _ZFP_ZFUIOnScreenKeyboardAutoResize_doStop(ZF_IN ZFUIWindow *window, ZF_IN _ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData *taskData)
{
    ZF_GLOBAL_INITIALIZER_CLASS(ZFUIOnScreenKeyboardAutoResizeDataHolder) *d = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFUIOnScreenKeyboardAutoResizeDataHolder);

    window->observerRemove(ZFUIWindow::EventWindowOnShow(), d->windowOnShowListener);
    window->windowLayoutParam()->observerRemove(ZFObject::EventObjectPropertyValueOnUpdate(), d->windowLayoutMarginChangeListener);
    window->layoutRequest();

    if(taskData->layoutMarginHasStored)
    {
        taskData->layoutMarginHasStored = zffalse;
        window->windowLayoutParam()->layoutMarginSet(taskData->layoutMarginSaved);
    }

    d->windowList.removeElement(window);
    if(d->windowList.isEmpty())
    {
        ZFObjectGlobalEventObserver().observerRemove(ZFUIOnScreenKeyboardState::EventKeyboardStateOnChange(), d->onScreenKeyboardStateChangeListener);
    }
}
static ZFLISTENER_PROTOTYPE_EXPAND(_ZFP_ZFUIOnScreenKeyboardAutoResize_onScreenKeyboardStateChange)
{
    ZFUIOnScreenKeyboardState *state = listenerData.sender->to<ZFUIOnScreenKeyboardState *>();
    ZF_GLOBAL_INITIALIZER_CLASS(ZFUIOnScreenKeyboardAutoResizeDataHolder) *d = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFUIOnScreenKeyboardAutoResizeDataHolder);
    for(zfindex i = 0; i < d->windowList.count(); ++i)
    {
        ZFUIWindow *window = d->windowList[i];
        if(window->windowSysWindow() != state->windowSysWindow())
        {
            continue;
        }

        _ZFP_ZFUIOnScreenKeyboardAutoResize_apply(window, state);
    }
}
static ZFLISTENER_PROTOTYPE_EXPAND(_ZFP_ZFUIOnScreenKeyboardAutoResize_windowOnShow)
{
    ZFUIWindow *window = listenerData.sender->to<ZFUIWindow *>();
    _ZFP_ZFUIOnScreenKeyboardAutoResize_apply(window, ZFUIOnScreenKeyboardState::instanceForView(window));
}
static ZFLISTENER_PROTOTYPE_EXPAND(_ZFP_ZFUIOnScreenKeyboardAutoResize_windowLayoutMarginChange)
{
    const ZFProperty *property = listenerData.param0->to<ZFPointerHolder *>()->holdedDataPointer<const ZFProperty *>();
    if(property != ZFPropertyAccess(ZFUIViewLayoutParam, layoutMargin))
    {
        return ;
    }

    ZFUIViewLayoutParam *layoutParam = listenerData.sender->to<ZFUIViewLayoutParam *>();
    ZFUIWindow *window = userData->to<ZFObjectHolder *>()->holdedObj;
    _ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData *taskData = ZFAny(window->tagGet(
        _ZFP_I_ZFUIOnScreenKeyboardAutoResizeTaskData::ClassData()->className()));
    if(taskData == zfnull)
    {
        return ;
    }
    if(taskData->layoutMarginHasStored)
    {
        taskData->layoutMarginSaved = layoutParam->layoutMargin();
    }
}

ZF_NAMESPACE_GLOBAL_END

