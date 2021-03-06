/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUINativeViewWrapper.h"
#include "protocol/ZFProtocolZFUIView.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFOBJECT_REGISTER(ZFUINativeViewWrapper)

void ZFUINativeViewWrapper::objectInfoOnAppend(ZF_IN_OUT zfstring &ret)
{
    zfsuper::objectInfoOnAppend(ret);
    if(this->wrappedNativeView() != zfnull)
    {
        ret += zfText(" ");
        zfsFromPointerT(ret, this->wrappedNativeView());
    }
}

ZFMETHOD_DEFINE_1(ZFUINativeViewWrapper, void, wrappedNativeViewSet,
                  ZFMP_IN(void *, wrappedNativeView))
{
    zfclassNotPOD _ZFP_ZFUINativeViewWrapper_nativeImplViewDestroy
    {
    public:
        static void action(ZF_IN ZFUIView *view,
                           ZF_IN void *nativeImplView)
        {
            // nothing to do
        }
    };
    this->nativeImplViewSet(wrappedNativeView, _ZFP_ZFUINativeViewWrapper_nativeImplViewDestroy::action);
}
ZFMETHOD_DEFINE_0(ZFUINativeViewWrapper, void *, wrappedNativeView)
{
    return this->nativeImplView();
}
void ZFUINativeViewWrapper::layoutOnMeasure(ZF_OUT ZFUISize &ret,
                                            ZF_IN const ZFUISize &sizeHint,
                                            ZF_IN const ZFUISizeParam &sizeParam)
{
    ZFPROTOCOL_ACCESS(ZFUIView)->measureNativeView(
        ret,
        this->wrappedNativeView(),
        ZFUISizeApplyScale(
            ZFUIViewLayoutParam::sizeHintOffset(sizeHint, ZFUISizeMake(
                    0 - ZFUIMarginGetX(this->nativeImplViewMargin()),
                    0 - ZFUIMarginGetY(this->nativeImplViewMargin())
                )),
            this->scaleFixed()),
        sizeParam);
    ZFUISizeApplyScaleReversely(ret, ret, this->scaleFixed());
    ZFUISizeApplyMarginReversely(ret, ret, this->nativeImplViewMargin());
}
void ZFUINativeViewWrapper::layoutOnLayout(ZF_IN const ZFUIRect &bounds)
{
    zfsuper::layoutOnLayout(bounds);
}

ZF_NAMESPACE_GLOBAL_END

