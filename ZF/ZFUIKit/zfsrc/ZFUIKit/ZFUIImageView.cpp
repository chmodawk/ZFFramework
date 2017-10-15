/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIImageView.h"
#include "protocol/ZFProtocolZFUIImageView.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFSTYLE_DEFAULT_DEFINE(ZFUIImageView)

// ============================================================
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFUIImageViewListenerHolder, ZFLevelZFFrameworkEssential)
{
    this->imageNinePatchChangedListener = ZFCallbackForRawFunction(zfself::imageNinePatchChanged);
}
public:
    ZFListener imageNinePatchChangedListener;
    static ZFLISTENER_PROTOTYPE_EXPAND(imageNinePatchChanged)
    {
        const ZFProperty *property = listenerData.param0->to<ZFPointerHolder *>()->holdedDataPointer<const ZFProperty *>();
        if(property == ZFPropertyAccess(ZFUIImage, imageNinePatch))
        {
            ZFUIImageView *imageView = userData->to<ZFObjectHolder *>()->holdedObj;
            ZFUIImage *image = imageView->image();
            ZFPROTOCOL_ACCESS(ZFUIImageView)->imageNinePatchChanged(
                imageView,
                image->imageScaleFixed(),
                ZFUIMarginApplyScale(image->imageNinePatch(), image->imageScaleFixed()));
        }
    }
ZF_GLOBAL_INITIALIZER_END(ZFUIImageViewListenerHolder)

// ============================================================
// ZFUIImageView
ZFOBJECT_REGISTER(ZFUIImageView)

ZFPROPERTY_CUSTOM_ON_ATTACH_DEFINE(ZFUIImageView, ZFUIImage *, image)
{
    ZF_GLOBAL_INITIALIZER_CLASS(ZFUIImageViewListenerHolder) *listenerHolder = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFUIImageViewListenerHolder);
    if(this->image() != zfnull)
    {
        this->image()->observerAdd(ZFObject::EventObjectPropertyValueOnUpdate(), listenerHolder->imageNinePatchChangedListener, this->objectHolder());
    }
}
ZFPROPERTY_CUSTOM_ON_DETACH_DEFINE(ZFUIImageView, ZFUIImage *, image)
{
    ZF_GLOBAL_INITIALIZER_CLASS(ZFUIImageViewListenerHolder) *listenerHolder = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFUIImageViewListenerHolder);
    if(this->image() != zfnull)
    {
        this->image()->observerRemove(ZFObject::EventObjectPropertyValueOnUpdate(), listenerHolder->imageNinePatchChangedListener);
    }
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUIImageView, ZFUIImage *, image)
{
    ZFPROTOCOL_ACCESS(ZFUIImageView)->imageSet(this, this->image());
    ZFUIImage *image = this->image();
    if(image != zfnull)
    {
        ZFPROTOCOL_ACCESS(ZFUIImageView)->imageNinePatchChanged(
            this,
            image->imageScaleFixed(),
            ZFUIMarginApplyScale(image->imageNinePatch(), image->imageScaleFixed()));
    }
    this->layoutRequest();
}

void ZFUIImageView::objectOnInit(void)
{
    zfsuper::objectOnInit();

    zfCoreAssert(this->nativeImplView() == zfnull);
    zfclassNotPOD _ZFP_ZFUIImageView_nativeImplViewDestroy
    {
    public:
        static void action(ZF_IN ZFUIView *view,
                           ZF_IN void *nativeImplView)
        {
            ZFPROTOCOL_ACCESS(ZFUIImageView)->nativeImageViewDestroy(view->to<ZFUIImageView *>(), nativeImplView);
        }
    };
    this->nativeImplViewSet(
        ZFPROTOCOL_ACCESS(ZFUIImageView)->nativeImageViewCreate(this),
        _ZFP_ZFUIImageView_nativeImplViewDestroy::action);
}
void ZFUIImageView::objectOnDealloc(void)
{
    this->imageSet(zfnull);
    zfsuper::objectOnDealloc();
}

void ZFUIImageView::objectInfoOnAppend(ZF_IN_OUT zfstring &ret)
{
    zfsuper::objectInfoOnAppend(ret);
    if(this->image() != zfnull)
    {
        ret += zfText(" ");
        this->image()->objectInfoT(ret);
    }
}

void ZFUIImageView::nativeImplViewOnLayout(ZF_OUT ZFUIRect &result,
                                           ZF_IN const ZFUIRect &bounds)
{
    if(this->image() == zfnull
        || bounds.size.width == 0
        || bounds.size.height == 0)
    {
        return ;
    }

    ZFUIContentScaleTypeApply(result, this->imageScaleType(), bounds, this->image()->imageSize());
}
void ZFUIImageView::nativeImplViewMarginOnUpdate(ZF_IN_OUT ZFUIMargin &nativeImplViewMargin)
{
    zfsuper::nativeImplViewMarginOnUpdate(nativeImplViewMargin);
    ZFUIMarginInc(nativeImplViewMargin, nativeImplViewMargin, this->imageMargin());
}
void ZFUIImageView::layoutOnMeasure(ZF_OUT ZFUISize &ret,
                                    ZF_IN const ZFUISize &sizeHint,
                                    ZF_IN const ZFUISizeParam &sizeParam)
{
    ret = ((this->image() != zfnull) ? this->image()->imageSize() : ZFUISizeZero());
}

ZF_NAMESPACE_GLOBAL_END

