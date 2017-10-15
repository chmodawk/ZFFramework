/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIListCellViewBasic.h"
#include "ZFUIViewLayout.h"
#include "ZFUILinearLayout.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFSTYLE_DEFAULT_DEFINE(ZFUIListCellViewBasic)

// ============================================================
zfclassNotPOD _ZFP_ZFUIListCellViewBasicPrivate
{
public:
    ZFUIViewLayout *cellIconContainer;
    ZFUILinearLayout *cellCenterContainer;
    ZFUIViewLayout *cellLabelMainContainer;
    ZFUIViewLayout *cellLabelSubContainer;
    ZFUIViewLayout *cellAccessoryContainer;
};

// ============================================================
ZFOBJECT_REGISTER(ZFUIListCellViewBasic)

ZFMETHOD_DEFINE_0(ZFUIListCellViewBasic, ZFUIView *, cellIconContainer)
{
    return d->cellIconContainer;
}
ZFMETHOD_DEFINE_0(ZFUIListCellViewBasic, ZFUIView *, cellCenterContainer)
{
    return d->cellCenterContainer;
}
ZFMETHOD_DEFINE_0(ZFUIListCellViewBasic, ZFUIView *, cellLabelMainContainer)
{
    return d->cellLabelMainContainer;
}
ZFMETHOD_DEFINE_0(ZFUIListCellViewBasic, ZFUIView *, cellLabelSubContainer)
{
    return d->cellLabelSubContainer;
}
ZFMETHOD_DEFINE_0(ZFUIListCellViewBasic, ZFUIView *, cellAccessoryContainer)
{
    return d->cellAccessoryContainer;
}

void ZFUIListCellViewBasic::objectOnInit(void)
{
    zfsuper::objectOnInit();

    d = zfpoolNew(_ZFP_ZFUIListCellViewBasicPrivate);

    d->cellIconContainer = zfAllocWithoutLeakTest(ZFUIViewLayout);

    {
        d->cellCenterContainer = zfAllocWithoutLeakTest(ZFUILinearLayout);
        d->cellCenterContainer->layoutOrientationSet(ZFUIOrientation::e_Top);

        d->cellLabelMainContainer = zfAllocWithoutLeakTest(ZFUIViewLayout);
        d->cellCenterContainer->childAdd(d->cellLabelMainContainer);
        d->cellLabelMainContainer->layoutParam()->layoutAlignSet(ZFUIAlign::e_LeftInner);

        d->cellLabelSubContainer = zfAllocWithoutLeakTest(ZFUIViewLayout);
        d->cellCenterContainer->childAdd(d->cellLabelSubContainer);
        d->cellLabelSubContainer->layoutParam()->layoutAlignSet(ZFUIAlign::e_LeftInner);
    }

    d->cellAccessoryContainer = zfAllocWithoutLeakTest(ZFUIViewLayout);
}
void ZFUIListCellViewBasic::objectOnDealloc(void)
{
    zfReleaseWithoutLeakTest(d->cellIconContainer);
    zfReleaseWithoutLeakTest(d->cellCenterContainer);
    zfReleaseWithoutLeakTest(d->cellLabelMainContainer);
    zfReleaseWithoutLeakTest(d->cellLabelSubContainer);
    zfReleaseWithoutLeakTest(d->cellAccessoryContainer);

    zfpoolDelete(d);
    zfsuper::objectOnDealloc();
}

ZF_NAMESPACE_GLOBAL_END

