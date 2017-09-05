/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFUIListCellViewBasic.h
 * @brief basic list cell view with icon and label
 */

#ifndef _ZFI_ZFUIListCellViewBasic_h_
#define _ZFI_ZFUIListCellViewBasic_h_

#include "ZFUIListCellView.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// ZFUIListCellViewBasic
zfclassFwd _ZFP_ZFUIListCellViewBasicPrivate;
/**
 * @brief basic list cell view with icon and label
 */
zfclass ZF_ENV_EXPORT ZFUIListCellViewBasic : zfextends ZFUIListCellView
{
    ZFOBJECT_DECLARE(ZFUIListCellViewBasic, ZFUIListCellView)
    ZFSTYLE_DEFAULT_DECLARE(ZFUIListCellViewBasic)

public:
    // ============================================================
    // properties
    /**
     * @brief cell's icon
     */
    ZFPROPERTY_RETAIN_READONLY(ZFUIImageView *, cellIcon, ZFPropertyNoInitValue)
    ZFPROPERTY_CUSTOM_ON_INIT_DECLARE(ZFUIImageView *, cellIcon)
    {
        zfblockedAlloc(ZFUIImageView, cellIcon);
        propertyValue = zfautoObjectCreateWithoutLeakTest(cellIcon);
        cellIcon->viewSizeMaxSet(ZFUISizeMake(ZFUIGlobalStyle::DefaultStyle()->itemSizeIcon()));
    }
    ZFPROPERTY_CUSTOM_ON_ATTACH_DECLARE(ZFUIImageView *, cellIcon)
    {
        this->cellIconContainer()->childAdd(this->cellIcon());
        this->cellIcon()->layoutParam()->layoutAlignSet(ZFUIAlign::e_Center);
    }
    ZFPROPERTY_CUSTOM_ON_DETACH_DECLARE(ZFUIImageView *, cellIcon)
    {
        this->cellIcon()->viewRemoveFromParent();
    }

    /**
     * @brief cell's main label
     */
    ZFPROPERTY_RETAIN_READONLY(ZFUITextView *, cellLabelMain, ZFPropertyNoInitValue)
    ZFPROPERTY_CUSTOM_ON_INIT_DECLARE(ZFUITextView *, cellLabelMain)
    {
        zfblockedAlloc(ZFUITextView, cellLabelMain);
        propertyValue = zfautoObjectCreateWithoutLeakTest(cellLabelMain);
    }
    ZFPROPERTY_CUSTOM_ON_ATTACH_DECLARE(ZFUITextView *, cellLabelMain)
    {
        this->cellLabelMainContainer()->childAdd(this->cellLabelMain());
        this->cellLabelMain()->layoutParam()->layoutAlignSet(ZFUIAlign::e_LeftInner);
    }
    ZFPROPERTY_CUSTOM_ON_DETACH_DECLARE(ZFUITextView *, cellLabelMain)
    {
        this->cellLabelMain()->viewRemoveFromParent();
    }

    /**
     * @brief cell's sub label
     */
    ZFPROPERTY_RETAIN_READONLY(ZFUITextView *, cellLabelSub, ZFPropertyNoInitValue)
    ZFPROPERTY_CUSTOM_ON_INIT_DECLARE(ZFUITextView *, cellLabelSub)
    {
        zfblockedAlloc(ZFUITextView, cellLabelSub);
        propertyValue = zfautoObjectCreateWithoutLeakTest(cellLabelSub);
        cellLabelSub->textColorSet(ZFUIGlobalStyle::DefaultStyle()->textColorSecondary());
        cellLabelSub->textSizeSet(ZFUIGlobalStyle::DefaultStyle()->textSizeSmall());
    }
    ZFPROPERTY_CUSTOM_ON_ATTACH_DECLARE(ZFUITextView *, cellLabelSub)
    {
        this->cellLabelSubContainer()->childAdd(this->cellLabelSub());
        this->cellLabelSub()->layoutParam()->layoutAlignSet(ZFUIAlign::e_LeftInner);
    }
    ZFPROPERTY_CUSTOM_ON_DETACH_DECLARE(ZFUITextView *, cellLabelSub)
    {
        this->cellLabelSub()->viewRemoveFromParent();
    }

public:
    /**
     * @brief container for icon, you may add your own custom view
     */
    ZFMETHOD_DECLARE_0(ZFUIView *, cellIconContainer);
    /**
     * @brief container for center item, you may add your own custom view
     */
    ZFMETHOD_DECLARE_0(ZFUIView *, cellCenterContainer);
    /**
     * @brief container for main label, you may add your own custom view
     */
    ZFMETHOD_DECLARE_0(ZFUIView *, cellLabelMainContainer);
    /**
     * @brief container for sub label, you may add your own custom view
     */
    ZFMETHOD_DECLARE_0(ZFUIView *, cellLabelSubContainer);
    /**
     * @brief container for accessory, you may add your own custom view
     */
    ZFMETHOD_DECLARE_0(ZFUIView *, cellAccessoryContainer);

public:
    zfoverride
    virtual ZFObject *objectOnInit(void);
    zfoverride
    virtual void objectOnDealloc(void);

private:
    _ZFP_ZFUIListCellViewBasicPrivate *d;
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIListCellViewBasic_h_

