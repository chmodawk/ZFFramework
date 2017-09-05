/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFUIDialogBasic.h
 * @brief basic dialog
 */

#ifndef _ZFI_ZFUIDialogBasic_h_
#define _ZFI_ZFUIDialogBasic_h_

#include "ZFUIDialog.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// ZFUIDialogButtonType
/**
 * @brief button state
 */
ZFENUM_BEGIN(ZFUIDialogButtonType)
    ZFENUM_VALUE(Normal) /**< @brief normal button */
    ZFENUM_VALUE(Yes) /**< @brief yes button */
    ZFENUM_VALUE(No) /**< @brief no button */
    ZFENUM_VALUE(Cancel) /**< @brief cancel button */
    ZFENUM_VALUE(Destructive) /**< @brief for destructive operations */
ZFENUM_SEPARATOR(ZFUIDialogButtonType)
    ZFENUM_VALUE_REGISTER(Normal)
    ZFENUM_VALUE_REGISTER(Yes)
    ZFENUM_VALUE_REGISTER(No)
    ZFENUM_VALUE_REGISTER(Cancel)
    ZFENUM_VALUE_REGISTER(Destructive)
ZFENUM_END(ZFUIDialogButtonType)

// ============================================================
/**
 * @brief abstract dialog content for #ZFUIDialogBasic
 */
zfinterface ZF_ENV_EXPORT ZFUIDialogContent : zfextends ZFInterface
{
    ZFINTERFACE_DECLARE(ZFUIDialogContent, ZFInterface)

public:
    // ============================================================
    // events
    /**
     * @brief see #ZFObject::observerNotify
     *
     * called when dialog button added,
     * param0 is the dialog button
     */
    ZFOBSERVER_EVENT(DialogButtonOnAdd)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * called when dialog button removed,
     * param0 is the dialog button
     */
    ZFOBSERVER_EVENT(DialogButtonOnRemove)

public:
    // ============================================================
    // title
    /**
     * @brief container to hold custom title views
     */
    virtual ZFUIView *dialogTitleContainer(void) zfpurevirtual;
    /**
     * @brief title text view
     */
    virtual ZFUITextView *dialogTitleView(void) zfpurevirtual;
    /**
     * @brief set the dialog's title text
     */
    ZFMETHOD_DECLARE_1(void, dialogTitleTextSet,
                       ZFMP_IN(const zfchar *, text))
    {
        this->dialogTitleView()->textContentStringSet(text);
    }
    /**
     * @brief get the dialog's title text
     */
    ZFMETHOD_DECLARE_0(const zfchar *, dialogTitleText)
    {
        return this->dialogTitleView()->textContentString();
    }

    // ============================================================
    // content
    /**
     * @brief container to hold custom content views
     */
    virtual ZFUIView *dialogContentContainer(void) zfpurevirtual;
    /**
     * @brief content text view
     */
    virtual ZFUITextView *dialogContentView(void) zfpurevirtual;
    /**
     * @brief set the dialog's content text
     */
    ZFMETHOD_DECLARE_1(void, dialogContentTextSet,
                       ZFMP_IN(const zfchar *, text))
    {
        this->dialogContentView()->textContentStringSet(text);
    }
    /**
     * @brief get the dialog's content text
     */
    ZFMETHOD_DECLARE_0(const zfchar *, dialogContentText)
    {
        return this->dialogContentView()->textContentString();
    }

    // ============================================================
    // button
    /**
     * @brief container to hold custom button views
     */
    virtual ZFUIView *dialogButtonContainer(void) zfpurevirtual;
    /**
     * @brief access dialog button with specifed type
     *
     * if autoCreateIfNotExist is not true,
     * button won't be created automatically,
     * and may return null if not exist,
     * see #dialogButtonRemove\n
     * access #ZFUIDialogButtonType::e_Normal would always return null
     */
    virtual ZFUIButton *dialogButton(ZF_IN ZFUIDialogButtonTypeEnum dialogButtonType,
                                     ZF_IN_OPT zfbool autoCreateIfNotExist = zftrue) zfpurevirtual;
    /**
     * @brief text of the button
     */
    virtual const zfchar *dialogButtonText(ZF_IN ZFUIDialogButtonTypeEnum dialogButtonType) zfpurevirtual;
    /**
     * @brief see #dialogButtonText
     */
    virtual void dialogButtonTextSet(ZF_IN ZFUIDialogButtonTypeEnum dialogButtonType,
                                     ZF_IN const zfchar *text) zfpurevirtual;
    /**
     * @brief remove specified button type, see #dialogButton
     */
    virtual void dialogButtonRemove(ZF_IN ZFUIDialogButtonTypeEnum dialogButtonType) zfpurevirtual;

    /** @brief util method to access #dialogButton */
    ZFMETHOD_DECLARE_1(ZFUIButton *, dialogButton_Yes,
                       ZFMP_IN_OPT(zfbool, autoCreateIfNotExist, zftrue))
    {
        return this->dialogButton(ZFUIDialogButtonType::e_Yes, autoCreateIfNotExist);
    }
    /** @brief util method to access #dialogButton */
    ZFMETHOD_DECLARE_1(ZFUIButton *, dialogButton_No,
                       ZFMP_IN_OPT(zfbool, autoCreateIfNotExist, zftrue))
    {
        return this->dialogButton(ZFUIDialogButtonType::e_No, autoCreateIfNotExist);
    }
    /** @brief util method to access #dialogButton */
    ZFMETHOD_DECLARE_1(ZFUIButton *, dialogButton_Cancel,
                       ZFMP_IN_OPT(zfbool, autoCreateIfNotExist, zftrue))
    {
        return this->dialogButton(ZFUIDialogButtonType::e_Cancel, autoCreateIfNotExist);
    }
    /** @brief util method to access #dialogButton */
    ZFMETHOD_DECLARE_1(ZFUIButton *, dialogButton_Destructive,
                       ZFMP_IN_OPT(zfbool, autoCreateIfNotExist, zftrue))
    {
        return this->dialogButton(ZFUIDialogButtonType::e_Destructive, autoCreateIfNotExist);
    }

    /** @brief util method to access #dialogButtonText */
    ZFMETHOD_DECLARE_0(const zfchar *, dialogButtonText_Yes)
    {
        return this->dialogButtonText(ZFUIDialogButtonType::e_Yes);
    }
    /** @brief util method to access #dialogButtonTextSet */
    ZFMETHOD_DECLARE_1(void, dialogButtonTextSet_Yes,
                       ZFMP_IN(const zfchar *, text))
    {
        this->dialogButtonTextSet(ZFUIDialogButtonType::e_Yes, text);
    }
    /** @brief util method to access #dialogButtonText */
    ZFMETHOD_DECLARE_0(const zfchar *, dialogButtonText_No)
    {
        return this->dialogButtonText(ZFUIDialogButtonType::e_No);
    }
    /** @brief util method to access #dialogButtonTextSet */
    ZFMETHOD_DECLARE_1(void, dialogButtonTextSet_No,
                       ZFMP_IN(const zfchar *, text))
    {
        this->dialogButtonTextSet(ZFUIDialogButtonType::e_No, text);
    }
    /** @brief util method to access #dialogButtonText */
    ZFMETHOD_DECLARE_0(const zfchar *, dialogButtonText_Cancel)
    {
        return this->dialogButtonText(ZFUIDialogButtonType::e_Cancel);
    }
    /** @brief util method to access #dialogButtonTextSet */
    ZFMETHOD_DECLARE_1(void, dialogButtonTextSet_Cancel,
                       ZFMP_IN(const zfchar *, text))
    {
        this->dialogButtonTextSet(ZFUIDialogButtonType::e_Cancel, text);
    }
    /** @brief util method to access #dialogButtonText */
    ZFMETHOD_DECLARE_0(const zfchar *, dialogButtonText_Destructive)
    {
        return this->dialogButtonText(ZFUIDialogButtonType::e_Destructive);
    }
    /** @brief util method to access #dialogButtonTextSet */
    ZFMETHOD_DECLARE_1(void, dialogButtonTextSet_Destructive,
                       ZFMP_IN(const zfchar *, text))
    {
        this->dialogButtonTextSet(ZFUIDialogButtonType::e_Destructive, text);
    }

    // ============================================================
    // button
    /**
     * @brief button count with #ZFUIDialogButtonType::e_Normal type
     */
    virtual zfindex dialogButtonCount(void) zfpurevirtual;
    /**
     * @brief access button at index, for #ZFUIDialogButtonType::e_Normal type only
     */
    virtual ZFUIButton *dialogButtonAtIndex(ZF_IN zfindex index) zfpurevirtual;
    /**
     * @brief find button's index, for #ZFUIDialogButtonType::e_Normal type only
     */
    virtual zfindex dialogButtonFind(ZF_IN ZFUIButton *dialogButton) zfpurevirtual;
    /**
     * @brief manually add a button with #ZFUIDialogButtonType::e_Normal type
     */
    virtual void dialogButtonAdd(ZF_IN ZFUIButton *button,
                                 ZF_IN_OPT zfindex atIndex = zfindexMax()) zfpurevirtual;
    /**
     * @brief manually remove a specified button, which can be #dialogButton
     */
    virtual void dialogButtonRemove(ZF_IN ZFUIButton *button) zfpurevirtual;
    /**
     * @brief manually remove a specified button at index
     */
    virtual void dialogButtonRemoveAtIndex(ZF_IN zfindex index) zfpurevirtual;
    /**
     * @brief manually remove all button
     */
    virtual void dialogButtonRemoveAll(void) zfpurevirtual;

protected:
    /** @brief see #EventDialogButtonOnAdd */
    virtual inline void dialogButtonOnAdd(ZF_IN ZFUIButton *button)
    {
        this->toObject()->observerNotify(ZFUIDialogContent::EventDialogButtonOnAdd(), button);
    }
    /** @brief see #EventDialogButtonOnRemove */
    virtual inline void dialogButtonOnRemove(ZF_IN ZFUIButton *button)
    {
        this->toObject()->observerNotify(ZFUIDialogContent::EventDialogButtonOnRemove(), button);
    }
};

// ============================================================
/**
 * @brief set the default class of content view for #ZFUIDialogBasic
 *
 * #ZFUIDialogContentBasic by default,
 * set null to reset to default
 */
ZFMETHOD_FUNC_DECLARE_1(void, ZFUIDialogContentClassSet,
                        ZFMP_IN(const ZFClass *, cls))
/**
 * @brief see #ZFUIDialogContentClassSet
 */
ZFMETHOD_FUNC_DECLARE_0(const ZFClass *, ZFUIDialogContentClass)

// ============================================================
// ZFUIDialogBasic
/**
 * @brief basic dialog with title, content and buttons
 *
 * actual dialog content is implemented by #ZFUIDialogContent,
 * you may change the default impl by #ZFUIDialogContentClassSet,
 * or directly change #ZFUIDialogBasic::dialogContent
 */
zfclass ZF_ENV_EXPORT ZFUIDialogBasic : zfextends ZFUIDialog, zfimplements ZFUIDialogContent
{
    ZFOBJECT_DECLARE(ZFUIDialogBasic, ZFUIDialog)
    ZFIMPLEMENTS_DECLARE(ZFUIDialogContent)
    ZFSTYLE_DEFAULT_DECLARE(ZFUIDialogBasic)

public:
    /**
     * @brief dialog content, create instance from #ZFUIDialogContentClass by default
     */
    ZFPROPERTY_RETAIN_WITH_INIT(ZFUIDialogContent *, dialogContent,
                                ZFPropertyInitValue(ZFUIDialogContentClass()->newInstance().to<ZFUIDialogContent *>()))
    ZFPROPERTY_CUSTOM_ON_VERIFY_DECLARE(ZFUIDialogContent *, dialogContent);
    ZFPROPERTY_CUSTOM_ON_ATTACH_DECLARE(ZFUIDialogContent *, dialogContent);
    ZFPROPERTY_CUSTOM_ON_DETACH_DECLARE(ZFUIDialogContent *, dialogContent);

public:
    // ============================================================
    // title
    ZFMETHOD_DECLARE_0(ZFUIView *, dialogTitleContainer)
    {
        return this->dialogContent()->dialogTitleContainer();
    }
    ZFMETHOD_DECLARE_0(ZFUITextView *, dialogTitleView)
    {
        return this->dialogContent()->dialogTitleView();
    }

    // ============================================================
    // content
    ZFMETHOD_DECLARE_0(ZFUIView *, dialogContentContainer)
    {
        return this->dialogContent()->dialogContentContainer();
    }
    ZFMETHOD_DECLARE_0(ZFUITextView *, dialogContentView)
    {
        return this->dialogContent()->dialogContentView();
    }

    // ============================================================
    // button
    ZFMETHOD_DECLARE_0(ZFUIView *, dialogButtonContainer)
    {
        return this->dialogContent()->dialogButtonContainer();
    }
    ZFMETHOD_DECLARE_2(ZFUIButton *, dialogButton,
                       ZFMP_IN(ZFUIDialogButtonTypeEnum, dialogButtonType),
                       ZFMP_IN_OPT(zfbool, autoCreateIfNotExist, zftrue))
    {
        return this->dialogContent()->dialogButton(dialogButtonType, autoCreateIfNotExist);
    }
    ZFMETHOD_DECLARE_1(const zfchar *, dialogButtonText,
                       ZFMP_IN(ZFUIDialogButtonTypeEnum, dialogButtonType))
    {
        return this->dialogContent()->dialogButtonText(dialogButtonType);
    }
    ZFMETHOD_DECLARE_2(void, dialogButtonTextSet,
                       ZFMP_IN(ZFUIDialogButtonTypeEnum, dialogButtonType),
                       ZFMP_IN(const zfchar *, text))
    {
        this->dialogContent()->dialogButtonTextSet(dialogButtonType, text);
    }
    ZFMETHOD_DECLARE_1(void, dialogButtonRemove,
                       ZFMP_IN(ZFUIDialogButtonTypeEnum , dialogButtonType))
    {
        this->dialogContent()->dialogButtonRemove(dialogButtonType);
    }

    // ============================================================
    // button
    ZFMETHOD_DECLARE_0(zfindex, dialogButtonCount)
    {
        return this->dialogContent()->dialogButtonCount();
    }
    ZFMETHOD_DECLARE_1(ZFUIButton *, dialogButtonAtIndex,
                       ZFMP_IN(zfindex, index))
    {
        return this->dialogContent()->dialogButtonAtIndex(index);
    }
    ZFMETHOD_DECLARE_1(zfindex, dialogButtonFind,
                       ZFMP_IN(ZFUIButton *, dialogButton))
    {
        return this->dialogContent()->dialogButtonFind(dialogButton);
    }
    ZFMETHOD_DECLARE_2(void, dialogButtonAdd,
                       ZFMP_IN(ZFUIButton *, button),
                       ZFMP_IN_OPT(zfindex, atIndex, zfindexMax()))
    {
        this->dialogContent()->dialogButtonAdd(button, atIndex);
    }
    ZFMETHOD_DECLARE_1(void, dialogButtonRemove,
                       ZFMP_IN(ZFUIButton *, button))
    {
        this->dialogContent()->dialogButtonRemove(button);
    }
    ZFMETHOD_DECLARE_1(void, dialogButtonRemoveAtIndex,
                       ZFMP_IN(zfindex, index))
    {
        this->dialogContent()->dialogButtonRemoveAtIndex(index);
    }
    ZFMETHOD_DECLARE_0(void, dialogButtonRemoveAll)
    {
        this->dialogContent()->dialogButtonRemoveAll();
    }

public:
    zfoverride
    virtual ZFObject *objectOnInit(void);
    zfoverride
    virtual void objectOnDeallocPrepare(void);
    zfoverride
    virtual void objectOnDealloc(void);

    zffinal void _ZFP_ZFUIDialogBasic_dialogButtonOnAdd(ZF_IN ZFUIButton *button)
    {
        this->dialogButtonOnAdd(button);
    }
    zffinal void _ZFP_ZFUIDialogBasic_dialogButtonOnRemove(ZF_IN ZFUIButton *button)
    {
        this->dialogButtonOnRemove(button);
    }
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIDialogBasic_h_

#include "ZFUIDialogContentBasic.h"

