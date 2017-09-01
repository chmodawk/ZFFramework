/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIViewUtil.h"

ZF_NAMESPACE_GLOBAL_BEGIN
ZF_NAMESPACE_BEGIN(ZFUIViewUtil)
/** @cond ZFPrivateDoc */ // ZFDoxygenBugFix: all uppercase macro not skipped within namespace

ZFMETHOD_FUNC_DEFINE_WITH_NS_1(ZFUIViewUtil, ZFUIView *, viewRoot,
                               ZFMP_IN(ZFUIView *, view))
{
    if(view != zfnull)
    {
        while(view->viewParent() != zfnull)
        {
            view = view->viewParent();
        }
    }
    return view;
}

ZFMETHOD_FUNC_DEFINE_WITH_NS_2(ZFUIViewUtil, zfbool, viewIsChildOf,
                               ZFMP_IN(ZFUIView *, view),
                               ZFMP_IN(ZFUIView *, parentToCheck))
{
    if(view != zfnull)
    {
        ZFUIView *tmp = parentToCheck;
        do
        {
            if(tmp == view)
            {
                return zftrue;
            }
            tmp = tmp->viewParentVirtual();
        } while(tmp != zfnull);
    }
    return zffalse;
}

ZFMETHOD_FUNC_DEFINE_WITH_NS_5(ZFUIViewUtil, ZFUIView *, viewChildAt,
                               ZFMP_IN(ZFUIView *, view),
                               ZFMP_IN(const ZFUIPoint &, pos),
                               ZFMP_IN_OPT(zfbool, filterDisabledView, zffalse),
                               ZFMP_IN_OPT(zfbool, filterInternalView, zftrue),
                               ZFMP_IN_OPT(const ZFFilterForZFObject *, filter, zfnull))
{
    if(view == zfnull
        || (filterDisabledView && !view->viewUIEnableTree())
        || (filter != zfnull && !filter->filterCheckActive(view)))
    {
        return zfnull;
    }
    if(pos.x < 0 || pos.y < 0 || pos.x > view->layoutedFrame().size.width || pos.y > view->layoutedFrame().size.height)
    {
        return zfnull;
    }

    ZFUIRect layoutedFrameFixed = ZFUIRectZero();

    ZFCoreArrayPOD<ZFUIView *> childList = view->internalForegroundViewArray();
    for(zfindex i = childList.count() - 1; i != zfindexMax(); --i)
    {
        ZFUIView *child = childList[i];
        child->layoutedFrameFixedT(layoutedFrameFixed);
        ZFUIView *tmp = ZFUIViewUtil::viewChildAt(childList[i], ZFUIPointMake(
                pos.x - layoutedFrameFixed.point.x,
                pos.y - layoutedFrameFixed.point.y
            ),
            filterDisabledView,
            filterInternalView,
            filter);
        if(tmp != zfnull)
        {
            return tmp;
        }
    }

    childList = view->childArray();
    for(zfindex i = childList.count() - 1; i != zfindexMax(); --i)
    {
        ZFUIView *child = childList[i];
        child->layoutedFrameFixedT(layoutedFrameFixed);
        ZFUIView *tmp = ZFUIViewUtil::viewChildAt(childList[i], ZFUIPointMake(
                pos.x - layoutedFrameFixed.point.x,
                pos.y - layoutedFrameFixed.point.y
            ),
            filterDisabledView,
            filterInternalView,
            filter);
        if(tmp != zfnull)
        {
            return tmp;
        }
    }

    childList = view->internalBackgroundViewArray();
    for(zfindex i = childList.count() - 1; i != zfindexMax(); --i)
    {
        ZFUIView *child = childList[i];
        child->layoutedFrameFixedT(layoutedFrameFixed);
        ZFUIView *tmp = ZFUIViewUtil::viewChildAt(childList[i], ZFUIPointMake(
                pos.x - layoutedFrameFixed.point.x,
                pos.y - layoutedFrameFixed.point.y
            ),
            filterDisabledView,
            filterInternalView,
            filter);
        if(tmp != zfnull)
        {
            return tmp;
        }
    }

    if(filterDisabledView && !view->viewUIEnable())
    {
        return zfnull;
    }

    return view;
}

ZFMETHOD_FUNC_DEFINE_WITH_NS_3(ZFUIViewUtil, void, viewRectToParent,
                               ZFMP_OUT(ZFUIRect &, rect),
                               ZFMP_IN(ZFUIView *, view),
                               ZFMP_IN(ZFUIView *, parent))
{
    if(view == zfnull || parent == zfnull)
    {
        rect = ZFUIRectZero();
        return ;
    }
    view->layoutedFrameFixedT(rect);
    ZFUIRect layoutedFrameFixed = ZFUIRectZero();
    while(view->viewParent() != zfnull && view != parent)
    {
        view = view->viewParent();
        view->layoutedFrameFixedT(layoutedFrameFixed);
        rect.point.x += layoutedFrameFixed.point.x;
        rect.point.y += layoutedFrameFixed.point.y;
    }
    if(view != parent)
    {
        rect = ZFUIRectZero();
    }
}
ZFMETHOD_FUNC_DEFINE_DETAIL_2(ZFMethodFuncIsInline, ZFUIViewUtil, ZFUIRect, viewRectToParent,
                              ZFMP_IN(ZFUIView *, view),
                              ZFMP_IN(ZFUIView *, parent))

/** @endcond */
ZF_NAMESPACE_END(ZFUIViewUtil)
ZF_NAMESPACE_GLOBAL_END

