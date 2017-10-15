/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUITextView.h"
#include "protocol/ZFProtocolZFUITextView.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFSTYLE_DEFAULT_DEFINE(ZFUITextView)

// ============================================================
// _ZFP_ZFUITextViewPrivate
zfclassNotPOD _ZFP_ZFUITextViewPrivate
{
public:
    ZFPROTOCOL_INTERFACE_CLASS(ZFUITextView) *impl;
    ZFUITextView *pimplOwner;

public:
    void updateSizeRelatedProperty(void)
    {
        this->impl->textShadowOffsetSet(this->pimplOwner, ZFUISizeApplyScale(this->pimplOwner->textShadowOffset(), this->pimplOwner->scaleGetFixed()));
        this->impl->textSizeSet(this->pimplOwner, ZFUISizeApplyScale(this->pimplOwner->textSize(), this->pimplOwner->scaleGetFixed()));
        this->impl->textSizeAutoChangeMinSizeSet(this->pimplOwner, ZFUISizeApplyScale(this->pimplOwner->textSizeAutoChangeMinSize(), this->pimplOwner->scaleGetFixed()));
        this->impl->textSizeAutoChangeMaxSizeSet(this->pimplOwner, ZFUISizeApplyScale(this->pimplOwner->textSizeAutoChangeMaxSize(), this->pimplOwner->scaleGetFixed()));
    }

public:
    _ZFP_ZFUITextViewPrivate(void)
    : impl(ZFPROTOCOL_ACCESS(ZFUITextView))
    , pimplOwner(zfnull)
    {
    }
};

// ============================================================
// ZFUITextView
ZFOBJECT_REGISTER(ZFUITextView)

ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextView, zfstring, text)
{
    d->impl->textSet(this, this->text());
    if(propertyValueOld.compare(this->text()) != 0)
    {
        this->layoutRequest();
    }
}

ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextView, ZFUITextAppearanceEnum, textAppearance)
{
    d->impl->textAppearanceSet(this, this->textAppearance());
    if(this->textAppearance() != propertyValueOld)
    {
        this->layoutRequest();
    }
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextView, ZFUIAlignFlags, textAlign)
{
    d->impl->textAlignSet(this, this->textAlign());
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextView, ZFUIColor, textColor)
{
    d->impl->textColorSet(this, this->textColor());
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextView, ZFUIColor, textShadowColor)
{
    d->impl->textShadowColorSet(this, this->textShadowColor());
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextView, ZFUISize, textShadowOffset)
{
    d->impl->textShadowOffsetSet(this, ZFUISizeApplyScale(this->textShadowOffset(), this->scaleGetFixed()));
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextView, zfint, textSize)
{
    d->impl->textSizeSet(this, ZFUISizeApplyScale(this->textSize(), this->scaleGetFixed()));
    if(this->textSize() != propertyValueOld)
    {
        this->layoutRequest();
    }
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextView, zfint, textSizeAutoChangeMinSize)
{
    d->impl->textSizeAutoChangeMinSizeSet(this, ZFUISizeApplyScale(this->textSizeAutoChangeMinSize(), this->scaleGetFixed()));
    if(this->textSizeAutoChangeMinSize() != propertyValueOld)
    {
        this->layoutRequest();
    }
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextView, zfint, textSizeAutoChangeMaxSize)
{
    d->impl->textSizeAutoChangeMaxSizeSet(this, ZFUISizeApplyScale(this->textSizeAutoChangeMaxSize(), this->scaleGetFixed()));
    if(this->textSizeAutoChangeMaxSize() != propertyValueOld)
    {
        this->layoutRequest();
    }
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextView, zfbool, textSingleLine)
{
    d->impl->textSingleLineSet(this, this->textSingleLine());
    if(this->textSingleLine() != propertyValueOld)
    {
        this->layoutRequest();
    }
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextView, ZFUITextTruncateModeEnum, textTruncateMode)
{
    d->impl->textTruncateModeSet(this, this->textTruncateMode());
    if(this->textTruncateMode() != propertyValueOld)
    {
        this->layoutRequest();
    }
}

void ZFUITextView::objectOnInit(void)
{
    zfsuper::objectOnInit();
    d = zfpoolNew(_ZFP_ZFUITextViewPrivate);
    d->pimplOwner = this;

    zfCoreAssert(this->nativeImplView() == zfnull);
    zfclassNotPOD _ZFP_ZFUITextView_nativeImplViewDestroy
    {
    public:
        static void action(ZF_IN ZFUIView *view,
                           ZF_IN void *nativeImplView)
        {
            ZFPROTOCOL_ACCESS(ZFUITextView)->nativeTextViewDestroy(view->to<ZFUITextView *>(), nativeImplView);
        }
    };
    this->nativeImplViewSet(d->impl->nativeTextViewCreate(this),
                            _ZFP_ZFUITextView_nativeImplViewDestroy::action);
}
void ZFUITextView::objectOnDealloc(void)
{
    zfpoolDelete(d);
    d = zfnull;
    zfsuper::objectOnDealloc();
}
void ZFUITextView::objectOnInitFinish(void)
{
    zfsuper::objectOnInitFinish();
    d->updateSizeRelatedProperty();
}

void ZFUITextView::objectInfoOnAppend(ZF_IN_OUT zfstring &ret)
{
    zfsuper::objectInfoOnAppend(ret);

    if(!this->text().isEmpty())
    {
        ret += zfText(" \"");
        ret += this->text();
        ret += zfText("\"");
    }
}

ZFMETHOD_DEFINE_1(ZFUITextView, ZFUISize, measureTextView,
                  ZFMP_IN_OPT(const ZFUISize &, sizeHint, ZFUISizeZero()))
{
    return ZFUISizeApplyScaleReversely(d->impl->measureNativeTextView(this,
        ZFUISizeApplyScale(sizeHint, this->scaleGetFixed()),
        ZFUISizeApplyScale(this->textSize(), this->scaleGetFixed())),
        this->scaleGetFixed());
}

ZFMETHOD_DEFINE_0(ZFUITextView, zfint, textSizeCurrent)
{
    return ZFUISizeApplyScaleReversely(d->impl->textSizeCurrent(this), this->scaleGetFixed());
}

void ZFUITextView::scaleOnChange(void)
{
    zfsuper::scaleOnChange();
    d->updateSizeRelatedProperty();
}
void ZFUITextView::layoutOnMeasure(ZF_OUT ZFUISize &ret,
                                   ZF_IN const ZFUISize &sizeHint,
                                   ZF_IN const ZFUISizeParam &sizeParam)
{
    ret = this->measureTextView(sizeHint);
}
void ZFUITextView::layoutOnLayout(ZF_IN const ZFUIRect &bounds)
{
    zfsuper::layoutOnLayout(bounds);
    d->impl->layoutNativeTextView(this,
        ZFUISizeApplyScale(ZFUISizeApplyMargin(bounds.size, this->nativeImplViewMargin()), this->scaleGetFixed()));
}

// ============================================================
ZFLANGAPPLY_DEFINE(ZFUITextView, ZFUITextViewText, {obj->textSet(langValue);})

ZF_NAMESPACE_GLOBAL_END

