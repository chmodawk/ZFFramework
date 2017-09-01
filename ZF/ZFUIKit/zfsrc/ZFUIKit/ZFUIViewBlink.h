/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFUIViewBlink.h
 * @brief blink view so that it's easy to be noticed
 */

#ifndef _ZFI_ZFUIViewBlink_h_
#define _ZFI_ZFUIViewBlink_h_

#include "ZFUIView.h"
#include "ZFUIImageIO.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief default mask image for #ZFUIViewBlink, an alpha white image by default
 */
ZFEXPORT_VAR_DECLARE(zfautoObject, ZFUIViewBlinkImageDefault)

/**
 * @brief param for #ZFUIViewBlink
 */
zfclassLikePOD ZF_ENV_EXPORT ZFUIViewBlinkParam
{
    ZFCORE_PARAM_DECLARE_SELF(ZFUIViewBlinkParam)

public:
    /** @brief image to blink, null to use default */
    ZFCORE_PARAM(ZFUIImage *, blinkImage)

    /** @brief duration to blink, #ZFUIGlobalStyle::aniDurationNormal by default */
    ZFCORE_PARAM_WITH_INIT(zftimet, blinkDuration, ZFUIGlobalStyle::DefaultStyle()->aniDurationNormal())
    /** @brief blink count, 1 by default */
    ZFCORE_PARAM_WITH_INIT(zfindex, blinkCount, 1)

public:
    /** @cond ZFPrivateDoc */
    zfbool operator == (ZF_IN const ZFUIViewBlinkParam &ref) const
    {
        return (zftrue
                && this->blinkImage() == ref.blinkImage()
                && this->blinkDuration() == ref.blinkDuration()
                && this->blinkCount() == ref.blinkCount()
            );
    }
    zfbool operator != (ZF_IN const ZFUIViewBlinkParam &ref) const
    {
        return !this->operator == (ref);
    }
    /** @endcond */
};
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFUIViewBlinkParam, ZFUIViewBlinkParam)
/**
 * @brief blink view so that it's easy to be noticed
 */
ZFMETHOD_FUNC_DECLARE_2(void, ZFUIViewBlink,
                        ZFMP_IN(ZFUIView *, view),
                        ZFMP_IN_OPT(const ZFUIViewBlinkParam &, blinkParam, ZFUIViewBlinkParam()));
/**
 * @brief blink view so that it's easy to be noticed
 */
ZFMETHOD_FUNC_DECLARE_INLINE_4(void, ZFUIViewBlink,
                               ZFMP_IN(ZFUIView *, view),
                               ZFMP_IN(ZFUIImage *, blinkImage),
                               ZFMP_IN_OPT(zftimet, blinkDuration, ZFUIGlobalStyle::DefaultStyle()->aniDurationNormal()),
                               ZFMP_IN_OPT(zfindex, blinkCount, 1))
{
    ZFUIViewBlink(view, ZFUIViewBlinkParam()
            .blinkImageSet(blinkImage)
            .blinkDurationSet(blinkDuration)
            .blinkCountSet(blinkCount)
        );
}

// ============================================================
ZF_NAMESPACE_BEGIN(ZFGlobalEvent)
/**
 * @brief see #ZFObject::observerNotify
 *
 * sender is the view that was blinked\n
 * notified when a view start to blink
 */
ZFOBSERVER_EVENT_GLOBAL(ViewBlinkOn)
/**
 * @brief see #ZFObject::observerNotify
 *
 * sender is the view that was blinked\n
 * notified when a view stop blink
 */
ZFOBSERVER_EVENT_GLOBAL(ViewBlinkOff)
ZF_NAMESPACE_END(ZFGlobalEvent)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIViewBlink_h_

