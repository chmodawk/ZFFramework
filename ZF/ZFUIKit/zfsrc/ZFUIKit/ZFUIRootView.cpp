/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIRootView.h"
#include "ZFUIWindow.h"

#include "ZFUIKit/protocol/ZFProtocolZFUIView.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFOBJECT_REGISTER(ZFUIRootView)

void ZFUIRootView::scaleSet(ZF_IN zffloat scale)
{
    if(scale > 0)
    {
        this->_ZFP_ZFUIView_scaleSetRecursively(scale, this->scaleGetForImpl());
    }
}

void ZFUIRootView::viewOnAddToParent(ZF_IN ZFUIView *parent)
{
    zfCoreCriticalMessage(zfTextA("you must not add ZFUIRootView to another parent, parent: %s"), zfsCoreZ2A(ZFObjectInfo(parent).cString()));
}
void ZFUIRootView::viewOnRemoveFromParent(ZF_IN ZFUIView *parent)
{
    zfCoreCriticalMessage(zfTextA("you must not add ZFUIRootView to another parent, parent: %s"), zfsCoreZ2A(ZFObjectInfo(parent).cString()));
}

void ZFUIRootView::layoutOnMeasure(ZF_OUT ZFUISize &ret,
                                   ZF_IN const ZFUISize &sizeHint,
                                   ZF_IN const ZFUISizeParam &sizeParam)
{
    ret = sizeHint;
}

static void _ZFP_ZFUIRootView_layoutParamApply(ZF_OUT ZFUIRect &ret,
                                               ZF_IN const ZFUIRect &rect,
                                               ZF_IN ZFUIView *child,
                                               ZF_IN ZFUIViewLayoutParam *lp,
                                               ZF_IN const ZFUIMargin &sysWindowMargin)
{
    ZFUIMargin totalMargin = ZFUIMarginInc(lp->layoutMargin(), sysWindowMargin);
    ZFUISize refSizeTmp = ZFUIRectApplyMargin(rect, totalMargin).size;
    if(refSizeTmp.width < 0)
    {
        refSizeTmp.width = 0;
    }
    if(refSizeTmp.height < 0)
    {
        refSizeTmp.height = 0;
    }

    if(lp->sizeHint().width >= 0)
    {
        refSizeTmp.width = zfmMin(lp->sizeHint().width, refSizeTmp.width);
    }
    if(lp->sizeHint().height >= 0)
    {
        refSizeTmp.height = zfmMin(lp->sizeHint().height, refSizeTmp.height);
    }
    child->layoutMeasure(refSizeTmp, lp->sizeParam());
    ZFUIAlignApply(
            ret,
            lp->layoutAlign(),
            rect,
            child->layoutMeasuredSize(),
            totalMargin
        );
}
void ZFUIRootView::layoutOnLayout(ZF_IN const ZFUIRect &bounds)
{
    for(zfindex i = 0; i < this->childCount(); ++i)
    {
        ZFUIView *child = this->childAtIndex(i);
        ZFUIWindow *window = ZFCastZFObject(ZFUIWindow *, child);
        if(window == zfnull)
        {
            child->layout(
                ZFUIViewLayoutParam::layoutParamApply(
                    bounds,
                    child,
                    child->layoutParam()));
            continue;
        }

        ZFUIRect result = ZFUIRectZero();
        _ZFP_ZFUIRootView_layoutParamApply(
            result,
            bounds,
            child,
            child->layoutParam(),
            window->windowSysWindow()->sysWindowMargin());
        child->layout(result);
    }
}

ZF_NAMESPACE_GLOBAL_END

