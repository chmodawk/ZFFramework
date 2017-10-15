/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFUIImageView.h
 * @brief image view
 */

#ifndef _ZFI_ZFUIImageView_h_
#define _ZFI_ZFUIImageView_h_

#include "ZFUIView.h"
#include "ZFUIImage.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// ZFUIImageView
/**
 * @brief native image view
 */
zfclass ZF_ENV_EXPORT ZFUIImageView : zfextends ZFUIView
{
    ZFOBJECT_DECLARE(ZFUIImageView, ZFUIView)
    ZFSTYLE_DEFAULT_DECLARE(ZFUIImageView)

public:
    // ============================================================
    // properties
    ZFPROPERTY_OVERRIDE_ON_INIT_DECLARE(zfbool, viewUIEnable)
    {
        propertyValue = zffalse;
    }
    ZFPROPERTY_OVERRIDE_ON_INIT_DECLARE(zfbool, viewUIEnableTree)
    {
        propertyValue = zffalse;
    }

    /**
     * @brief image for this view
     */
    ZFPROPERTY_RETAIN(ZFUIImage *, image)
    ZFPROPERTY_CUSTOM_ON_ATTACH_DECLARE(ZFUIImage *, image);
    ZFPROPERTY_CUSTOM_ON_DETACH_DECLARE(ZFUIImage *, image);
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(ZFUIImage *, image);

    /**
     * @brief image scale type, fill by default
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(ZFUIContentScaleTypeEnum, imageScaleType,
                                ZFPropertyInitValue(ZFUIContentScaleType::EnumDefault()))
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(ZFUIContentScaleTypeEnum, imageScaleType)
    {
        this->layoutRequest();
    }

    /**
     * @brief margin of the content image
     */
    ZFPROPERTY_ASSIGN(ZFUIMargin, imageMargin)
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(ZFUIMargin, imageMargin)
    {
        this->nativeImplViewMarginUpdate();
    }

protected:
    /**
     * @brief init with image
     */
    ZFMETHOD_DECLARE_PROTECTED_1(void, objectOnInit,
                                 ZFMP_IN(ZFUIImage *, image))
    {
        this->objectOnInit();
        this->imageSet(image);
    }

    zfoverride
    virtual void objectOnInit(void);
    zfoverride
    virtual void objectOnDealloc(void);

    zfoverride
    virtual void objectInfoOnAppend(ZF_IN_OUT zfstring &ret);

protected:
    /**
     * @brief for image view, we will update accorrding to #imageScaleType
     */
    zfoverride
    virtual void nativeImplViewOnLayout(ZF_OUT ZFUIRect &result,
                                        ZF_IN const ZFUIRect &bounds);
    zfoverride
    virtual void nativeImplViewMarginOnUpdate(ZF_IN_OUT ZFUIMargin &nativeImplViewMargin);
    /**
     * @brief image view would measure accorrding image size
     */
    zfoverride
    virtual void layoutOnMeasure(ZF_OUT ZFUISize &ret,
                                 ZF_IN const ZFUISize &sizeHint,
                                 ZF_IN const ZFUISizeParam &sizeParam);
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIImageView_h_

