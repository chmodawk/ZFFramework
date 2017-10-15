/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIButtonBasic.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// _ZFP_ZFUIButtonBasicPrivate
zfclassNotPOD _ZFP_ZFUIButtonBasicPrivate
{
public:
    ZFUIButtonBasic *pimplOwner;
    ZFUITextView *buttonLabel;
    ZFUIImageView *buttonIcon;
    ZFUIImageView *buttonBackground;

public:
    _ZFP_ZFUIButtonBasicPrivate(void)
    : pimplOwner(zfnull)
    , buttonLabel(zfnull)
    , buttonIcon(zfnull)
    , buttonBackground(zfnull)
    {
    }

public:
    void updateButtonLabel(void)
    {
        const zfchar *value = this->pimplOwner->buttonLabelStyle(this->pimplOwner->buttonState())->text();
        if(*value == '\0')
        {
            if(this->pimplOwner->buttonState() == ZFUIButtonState::e_Checked)
            {
                value = this->pimplOwner->buttonLabelStyleHighlighted()->text();
            }
            else if(this->pimplOwner->buttonState() == ZFUIButtonState::e_CheckedHighlighted)
            {
                value = this->pimplOwner->buttonLabelStyleChecked()->text();
                if(*value == '\0')
                {
                    value = this->pimplOwner->buttonLabelStyleHighlighted()->text();
                }
            }
            if(*value == '\0')
            {
                value = this->pimplOwner->buttonLabelStyleNormal()->text();
            }
        }
        this->buttonLabel->textSet(value);
    }
    void updateButtonIcon(void)
    {
        ZFUIImage *value = this->pimplOwner->buttonIconStyle(this->pimplOwner->buttonState())->image();
        if(value == zfnull)
        {
            if(this->pimplOwner->buttonState() == ZFUIButtonState::e_Checked)
            {
                value = this->pimplOwner->buttonIconStyleHighlighted()->image();
            }
            else if(this->pimplOwner->buttonState() == ZFUIButtonState::e_CheckedHighlighted)
            {
                value = this->pimplOwner->buttonIconStyleChecked()->image();
                if(value == zfnull)
                {
                    value = this->pimplOwner->buttonIconStyleHighlighted()->image();
                }
            }
            if(value == zfnull)
            {
                value = this->pimplOwner->buttonIconStyleNormal()->image();
            }
        }
        this->buttonIcon->imageSet(value);
    }
    void updateButtonBackground(void)
    {
        ZFUIImage *value = this->pimplOwner->buttonBackgroundStyle(this->pimplOwner->buttonState())->image();
        if(value == zfnull)
        {
            if(this->pimplOwner->buttonState() == ZFUIButtonState::e_Checked)
            {
                value = this->pimplOwner->buttonBackgroundStyleHighlighted()->image();
            }
            else if(this->pimplOwner->buttonState() == ZFUIButtonState::e_CheckedHighlighted)
            {
                value = this->pimplOwner->buttonBackgroundStyleChecked()->image();
                if(value == zfnull)
                {
                    value = this->pimplOwner->buttonBackgroundStyleHighlighted()->image();
                }
            }
            if(value == zfnull)
            {
                value = this->pimplOwner->buttonBackgroundStyleNormal()->image();
            }
        }
        this->buttonBackground->imageSet(value);
    }

public:
    #define _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(T_Component, T_State) \
        static ZFLISTENER_PROTOTYPE_EXPAND(button##T_Component##Style##T_State##Changed) \
        { \
            const ZFProperty *property = listenerData.param0->to<ZFPointerHolder *>()->holdedDataPointer<const ZFProperty *>(); \
            ZFUIButtonBasic *button = userData->to<ZFObjectHolder *>()->holdedObj.to<ZFUIButtonBasic *>(); \
            button->prepareButton##T_Component(); \
            if(button->buttonState() == ZFUIButtonState::e_##T_State) \
            { \
                property->callbackCopy(property, button->button##T_Component()->toObject(), listenerData.sender); \
            } \
            else if(property == ZFPropertyAccess(ZFUITextView, text)) \
            { \
                button->d->updateButton##T_Component(); \
            } \
        }

    _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(Label, Normal)
    _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(Label, Highlighted)
    _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(Label, Checked)
    _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(Label, CheckedHighlighted)
    _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(Label, Disabled)

    _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(Icon, Normal)
    _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(Icon, Highlighted)
    _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(Icon, Checked)
    _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(Icon, CheckedHighlighted)
    _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(Icon, Disabled)

    _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(Background, Normal)
    _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(Background, Highlighted)
    _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(Background, Checked)
    _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(Background, CheckedHighlighted)
    _ZFP_ZFUIButtonBasic_LISTENER_EXPAND_STYLE_CHANGED(Background, Disabled)
};
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFUIButtonBasicListenerHolder, ZFLevelZFFrameworkEssential)
{
    this->buttonLabelStyleNormalChangedListener = ZFCallbackForRawFunction(_ZFP_ZFUIButtonBasicPrivate::buttonLabelStyleNormalChanged);
    this->buttonLabelStyleHighlightedChangedListener = ZFCallbackForRawFunction(_ZFP_ZFUIButtonBasicPrivate::buttonLabelStyleHighlightedChanged);
    this->buttonLabelStyleCheckedChangedListener = ZFCallbackForRawFunction(_ZFP_ZFUIButtonBasicPrivate::buttonLabelStyleCheckedChanged);
    this->buttonLabelStyleCheckedHighlightedChangedListener = ZFCallbackForRawFunction(_ZFP_ZFUIButtonBasicPrivate::buttonLabelStyleCheckedHighlightedChanged);
    this->buttonLabelStyleDisabledChangedListener = ZFCallbackForRawFunction(_ZFP_ZFUIButtonBasicPrivate::buttonLabelStyleDisabledChanged);
    this->buttonIconStyleNormalChangedListener = ZFCallbackForRawFunction(_ZFP_ZFUIButtonBasicPrivate::buttonIconStyleNormalChanged);
    this->buttonIconStyleHighlightedChangedListener = ZFCallbackForRawFunction(_ZFP_ZFUIButtonBasicPrivate::buttonIconStyleHighlightedChanged);
    this->buttonIconStyleCheckedChangedListener = ZFCallbackForRawFunction(_ZFP_ZFUIButtonBasicPrivate::buttonIconStyleCheckedChanged);
    this->buttonIconStyleCheckedHighlightedChangedListener = ZFCallbackForRawFunction(_ZFP_ZFUIButtonBasicPrivate::buttonIconStyleCheckedHighlightedChanged);
    this->buttonIconStyleDisabledChangedListener = ZFCallbackForRawFunction(_ZFP_ZFUIButtonBasicPrivate::buttonIconStyleDisabledChanged);
    this->buttonBackgroundStyleNormalChangedListener = ZFCallbackForRawFunction(_ZFP_ZFUIButtonBasicPrivate::buttonBackgroundStyleNormalChanged);
    this->buttonBackgroundStyleHighlightedChangedListener = ZFCallbackForRawFunction(_ZFP_ZFUIButtonBasicPrivate::buttonBackgroundStyleHighlightedChanged);
    this->buttonBackgroundStyleCheckedChangedListener = ZFCallbackForRawFunction(_ZFP_ZFUIButtonBasicPrivate::buttonBackgroundStyleCheckedChanged);
    this->buttonBackgroundStyleCheckedHighlightedChangedListener = ZFCallbackForRawFunction(_ZFP_ZFUIButtonBasicPrivate::buttonBackgroundStyleCheckedHighlightedChanged);
    this->buttonBackgroundStyleDisabledChangedListener = ZFCallbackForRawFunction(_ZFP_ZFUIButtonBasicPrivate::buttonBackgroundStyleDisabledChanged);
}
public:
    ZFListener buttonLabelStyleNormalChangedListener;
    ZFListener buttonLabelStyleHighlightedChangedListener;
    ZFListener buttonLabelStyleCheckedChangedListener;
    ZFListener buttonLabelStyleCheckedHighlightedChangedListener;
    ZFListener buttonLabelStyleDisabledChangedListener;
    ZFListener buttonIconStyleNormalChangedListener;
    ZFListener buttonIconStyleHighlightedChangedListener;
    ZFListener buttonIconStyleCheckedChangedListener;
    ZFListener buttonIconStyleCheckedHighlightedChangedListener;
    ZFListener buttonIconStyleDisabledChangedListener;
    ZFListener buttonBackgroundStyleNormalChangedListener;
    ZFListener buttonBackgroundStyleHighlightedChangedListener;
    ZFListener buttonBackgroundStyleCheckedChangedListener;
    ZFListener buttonBackgroundStyleCheckedHighlightedChangedListener;
    ZFListener buttonBackgroundStyleDisabledChangedListener;
ZF_GLOBAL_INITIALIZER_END(ZFUIButtonBasicListenerHolder)

// ============================================================
// ZFUIButtonBasic
ZFOBJECT_REGISTER(ZFUIButtonBasic)
ZFSTYLE_DEFAULT_DEFINE(ZFUIButtonBasic)

#define _ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(Type, ComponentName, StateName) \
    ZFPROPERTY_CUSTOM_ON_ATTACH_DEFINE(ZFUIButtonBasic, Type, button##ComponentName##Style##StateName) \
    { \
        this->button##ComponentName##Style##StateName()->toObject()->observerAdd( \
            ZFObject::EventObjectPropertyValueOnUpdate(), \
            ZF_GLOBAL_INITIALIZER_INSTANCE(ZFUIButtonBasicListenerHolder)->button##ComponentName##Style##StateName##ChangedListener, \
            this->objectHolder()); \
    } \
    ZFPROPERTY_CUSTOM_ON_DETACH_DEFINE(ZFUIButtonBasic, Type, button##ComponentName##Style##StateName) \
    { \
        this->button##ComponentName##Style##StateName()->toObject()->observerRemove( \
            ZFObject::EventObjectPropertyValueOnUpdate(), \
            ZF_GLOBAL_INITIALIZER_INSTANCE(ZFUIButtonBasicListenerHolder)->button##ComponentName##Style##StateName##ChangedListener); \
    }

_ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(ZFUITextView *, Label, Normal)
_ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(ZFUITextView *, Label, Highlighted)
_ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(ZFUITextView *, Label, Checked)
_ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(ZFUITextView *, Label, CheckedHighlighted)
_ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(ZFUITextView *, Label, Disabled)

_ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(ZFUIImageView *, Icon, Normal)
_ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(ZFUIImageView *, Icon, Highlighted)
_ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(ZFUIImageView *, Icon, Checked)
_ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(ZFUIImageView *, Icon, CheckedHighlighted)
_ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(ZFUIImageView *, Icon, Disabled)

_ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(ZFUIImageView *, Background, Normal)
_ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(ZFUIImageView *, Background, Highlighted)
_ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(ZFUIImageView *, Background, Checked)
_ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(ZFUIImageView *, Background, CheckedHighlighted)
_ZFP_ZFUIBUTTONBASIC_BUTTON_COMPONENT_DEFINE(ZFUIImageView *, Background, Disabled)

void ZFUIButtonBasic::objectOnInit(void)
{
    zfsuper::objectOnInit();
    d = zfpoolNew(_ZFP_ZFUIButtonBasicPrivate);
    d->pimplOwner = this;
}

void ZFUIButtonBasic::objectOnDealloc(void)
{
    zfReleaseWithoutLeakTest(d->buttonLabel);
    zfReleaseWithoutLeakTest(d->buttonIcon);
    zfReleaseWithoutLeakTest(d->buttonBackground);
    zfpoolDelete(d);
    d = zfnull;
    zfsuper::objectOnDealloc();
}
void ZFUIButtonBasic::objectOnInitFinish(void)
{
    zfsuper::objectOnInitFinish();

    const ZFClass *cls = this->classData();
    if(d->buttonLabel == zfnull)
    {
        if(cls->propertyHasOverrideInitStep(ZFPropertyAccess(zfself, buttonLabelStyleNormal))
            || cls->propertyHasOverrideInitStep(ZFPropertyAccess(zfself, buttonLabelStyleHighlighted))
            || cls->propertyHasOverrideInitStep(ZFPropertyAccess(zfself, buttonLabelStyleChecked))
            || cls->propertyHasOverrideInitStep(ZFPropertyAccess(zfself, buttonLabelStyleCheckedHighlighted))
            || cls->propertyHasOverrideInitStep(ZFPropertyAccess(zfself, buttonLabelStyleDisabled)))
        {
            this->prepareButtonLabel();
        }
    }
    if(d->buttonBackground == zfnull)
    {
        if(cls->propertyHasOverrideInitStep(ZFPropertyAccess(zfself, buttonBackgroundStyleNormal))
            || cls->propertyHasOverrideInitStep(ZFPropertyAccess(zfself, buttonBackgroundStyleHighlighted))
            || cls->propertyHasOverrideInitStep(ZFPropertyAccess(zfself, buttonBackgroundStyleChecked))
            || cls->propertyHasOverrideInitStep(ZFPropertyAccess(zfself, buttonBackgroundStyleCheckedHighlighted))
            || cls->propertyHasOverrideInitStep(ZFPropertyAccess(zfself, buttonBackgroundStyleDisabled)))
        {
            this->prepareButtonBackground();
        }
    }
    if(d->buttonIcon == zfnull)
    {
        if(cls->propertyHasOverrideInitStep(ZFPropertyAccess(zfself, buttonIconStyleNormal))
            || cls->propertyHasOverrideInitStep(ZFPropertyAccess(zfself, buttonIconStyleHighlighted))
            || cls->propertyHasOverrideInitStep(ZFPropertyAccess(zfself, buttonIconStyleChecked))
            || cls->propertyHasOverrideInitStep(ZFPropertyAccess(zfself, buttonIconStyleCheckedHighlighted))
            || cls->propertyHasOverrideInitStep(ZFPropertyAccess(zfself, buttonIconStyleDisabled)))
        {
            this->prepareButtonIcon();
        }
    }
}

void ZFUIButtonBasic::objectInfoOnAppend(ZF_IN_OUT zfstring &ret)
{
    zfsuper::objectInfoOnAppend(ret);

    if(this->buttonLabel() != zfnull && !this->buttonLabel()->text().isEmpty())
    {
        zfstringAppend(ret, zfText(" \"%s\""), this->buttonLabel()->text().cString());
    }
}

void ZFUIButtonBasic::layoutOnMeasure(ZF_OUT ZFUISize &ret,
                                      ZF_IN const ZFUISize &sizeHint,
                                      ZF_IN const ZFUISizeParam &sizeParam)
{
    ZFUIView *labelView = ZFCastZFObjectUnchecked(ZFUIView *, d->buttonLabel);
    ZFUIView *iconView = ZFCastZFObjectUnchecked(ZFUIView *, d->buttonIcon);
    ZFUIView *backgroundView = ZFCastZFObjectUnchecked(ZFUIView *, d->buttonBackground);
    ZFUISize sizeHintTmp = sizeHint;
    if(sizeHintTmp.width >= 0)
    {
        sizeHintTmp.width -= this->buttonContentMargin().left + this->buttonContentMargin().right;
        if(sizeHintTmp.width < 0)
        {
            sizeHintTmp.width = 0;
        }
    }
    if(sizeHintTmp.height >= 0)
    {
        sizeHintTmp.height -= this->buttonContentMargin().top + this->buttonContentMargin().bottom;
        if(sizeHintTmp.height < 0)
        {
            sizeHintTmp.height = 0;
        }
    }

    ZFUISize labelSize = ZFUISizeZero();
    if(labelView != zfnull && labelView->viewVisible() && !d->buttonLabel->text().isEmpty())
    {
        labelSize = labelView->layoutMeasure(sizeHintTmp, ZFUISizeParamWrapWidthWrapHeight());
    }

    ZFUISize iconSize = ZFUISizeZero();
    if(iconView != zfnull && iconView->viewVisible() && d->buttonIcon->image() != zfnull)
    {
        iconSize = iconView->layoutMeasure(sizeHintTmp, ZFUISizeParamWrapWidthWrapHeight());
    }

    ZFUISize backgroundSize = ZFUISizeZero();
    if(backgroundView != zfnull && backgroundView->viewVisible() && d->buttonBackground->image() != zfnull)
    {
        ZFUISize sizeHintBg = sizeHint;
        if(sizeHintBg.width >= 0)
        {
            sizeHintBg.width -= this->buttonContentMargin().left + this->buttonContentMargin().right;
            if(sizeHintBg.width < 0)
            {
                sizeHintBg.width = 0;
            }
        }
        if(sizeHintBg.height >= 0)
        {
            sizeHintBg.height -= this->buttonContentMargin().top + this->buttonContentMargin().bottom;
            if(sizeHintBg.height < 0)
            {
                sizeHintBg.height = 0;
            }
        }
        backgroundSize = backgroundView->layoutMeasure(sizeHintBg, ZFUISizeParamWrapWidthWrapHeight());
    }

    ZFUISize contentSize = ZFUISizeZero();
    zfint contentSpace = 0;
    switch(this->buttonContentIconPosition())
    {
        case ZFUIOrientation::e_Left:
        case ZFUIOrientation::e_Right:
            if(iconSize.width > 0 && labelSize.width > 0)
            {
                contentSpace = this->buttonContentSpace();
            }
            contentSize.width = iconSize.width + contentSpace + labelSize.width;
            contentSize.height = zfmMax(iconSize.height, labelSize.height);
            break;
        case ZFUIOrientation::e_Top:
        case ZFUIOrientation::e_Bottom:
            if(iconSize.height > 0 && labelSize.height > 0)
            {
                contentSpace = this->buttonContentSpace();
            }
            contentSize.width = zfmMax(iconSize.width, labelSize.width);
            contentSize.height = iconSize.height + contentSpace + labelSize.height;
            break;
        default:
            zfCoreCriticalShouldNotGoHere();
            return ;
    }

    if(backgroundSize.width > 0)
    {
        backgroundSize.width += ZFUIMarginGetX(this->buttonBackgroundMargin());
    }
    if(backgroundSize.height > 0)
    {
        backgroundSize.height += ZFUIMarginGetY(this->buttonBackgroundMargin());
    }
    if(contentSize.width > 0)
    {
        contentSize.width += ZFUIMarginGetX(this->buttonContentMargin());
    }
    if(contentSize.height > 0)
    {
        contentSize.height += ZFUIMarginGetY(this->buttonContentMargin());
    }
    ret.width = zfmMax(backgroundSize.width, contentSize.width);
    ret.height = zfmMax(backgroundSize.height, contentSize.height);
}
void ZFUIButtonBasic::internalBackgroundViewOnLayout(ZF_IN const ZFUIRect &bounds)
{
    zfsuper::internalBackgroundViewOnLayout(bounds);

    ZFUIView *backgroundView = ZFCastZFObjectUnchecked(ZFUIView *, d->buttonBackground);
    if(backgroundView != zfnull)
    {
        backgroundView->layout(ZFUIRectApplyMargin(bounds, this->buttonBackgroundMargin()));
    }

    ZFUISize sizeHint = ZFUISizeApplyMargin(bounds.size, this->buttonContentMargin());

    ZFUIView *labelView = ZFCastZFObjectUnchecked(ZFUIView *, d->buttonLabel);
    ZFUIView *iconView = ZFCastZFObjectUnchecked(ZFUIView *, d->buttonIcon);

    ZFUISize labelSize = ZFUISizeZero();
    if(labelView != zfnull && labelView->viewVisible() && !d->buttonLabel->text().isEmpty())
    {
        labelSize = labelView->layoutMeasure(sizeHint, ZFUISizeParamWrapWidthWrapHeight());
    }

    ZFUISize iconSize = ZFUISizeZero();
    if(iconView != zfnull && iconView->viewVisible() && d->buttonIcon->image() != zfnull)
    {
        iconSize = iconView->layoutMeasure(sizeHint, ZFUISizeParamWrapWidthWrapHeight());
    }

    ZFUIRect contentFrame = ZFUIRectZero();
    zfint contentSpace = 0;
    switch(this->buttonContentIconPosition())
    {
        case ZFUIOrientation::e_Left:
        case ZFUIOrientation::e_Right:
            if(iconSize.width > 0 && labelSize.width > 0)
            {
                contentSpace = this->buttonContentSpace();
            }
            contentFrame = ZFUIAlignApply(
                this->buttonContentAlign(),
                bounds,
                ZFUISizeMake(iconSize.width + contentSpace + labelSize.width, zfmMax(iconSize.height, labelSize.height)),
                this->buttonContentMargin());
            if(this->buttonContentIconPosition() == ZFUIOrientation::e_Left)
            {
                if(iconView != zfnull)
                {
                    iconView->layout(ZFUIAlignApply(ZFUIAlign::e_LeftInner, contentFrame, iconSize));
                }
                if(labelView != zfnull)
                {
                    labelView->layout(ZFUIAlignApply(ZFUIAlign::e_RightInner, contentFrame, labelSize));
                }
            }
            else
            {
                if(iconView != zfnull)
                {
                    iconView->layout(ZFUIAlignApply(ZFUIAlign::e_RightInner, contentFrame, iconSize));
                }
                if(labelView != zfnull)
                {
                    labelView->layout(ZFUIAlignApply(ZFUIAlign::e_LeftInner, contentFrame, labelSize));
                }
            }
            break;
        case ZFUIOrientation::e_Top:
        case ZFUIOrientation::e_Bottom:
            if(iconSize.height > 0 && labelSize.height > 0)
            {
                contentSpace = this->buttonContentSpace();
            }
            contentFrame = ZFUIAlignApply(
                this->buttonContentAlign(),
                bounds,
                ZFUISizeMake(zfmMax(iconSize.width, labelSize.width), iconSize.height + contentSpace + labelSize.height),
                this->buttonContentMargin());
            if(this->buttonContentIconPosition() == ZFUIOrientation::e_Top)
            {
                if(iconView != zfnull)
                {
                    iconView->layout(ZFUIAlignApply(ZFUIAlign::e_TopInner, contentFrame, iconSize));
                }
                if(labelView != zfnull)
                {
                    labelView->layout(ZFUIAlignApply(ZFUIAlign::e_BottomInner, contentFrame, labelSize));
                }
            }
            else
            {
                if(iconView != zfnull)
                {
                    iconView->layout(ZFUIAlignApply(ZFUIAlign::e_BottomInner, contentFrame, iconSize));
                }
                if(labelView != zfnull)
                {
                    labelView->layout(ZFUIAlignApply(ZFUIAlign::e_TopInner, contentFrame, labelSize));
                }
            }
            break;
        default:
            zfCoreCriticalShouldNotGoHere();
            return ;
    }
}

zfbool ZFUIButtonBasic::internalViewShouldLayout(ZF_IN ZFUIView *internalView)
{
    if((d->buttonLabel != zfnull && d->buttonLabel->toObject() == internalView)
        || (d->buttonIcon != zfnull && d->buttonIcon->toObject() == internalView)
        || (d->buttonBackground != zfnull && d->buttonBackground->toObject() == internalView))
    {
        return zffalse;
    }
    return zfsuper::internalViewShouldLayout(internalView);
}

void ZFUIButtonBasic::buttonStateOnUpdate(void)
{
    zfsuper::buttonStateOnUpdate();

    #define _ZFP_ZFUIButtonBasic_buttonStateOn(StateName) \
        if(d->buttonLabel != zfnull) \
        { \
            if(ZFPropertyIsValueAccessed(ZFPropertyAccess(ZFUIButtonBasic, buttonLabelStyle##StateName), this)) \
            { \
                ZFCastZFObjectUnchecked(ZFStyleable *, d->buttonLabel)->styleableCopyFrom(ZFCastZFObjectUnchecked(ZFStyleable *, this->buttonLabelStyle##StateName())); \
            } \
            d->updateButtonLabel(); \
        } \
        if(d->buttonIcon != zfnull) \
        { \
            if(ZFPropertyIsValueAccessed(ZFPropertyAccess(ZFUIButtonBasic, buttonIconStyle##StateName), this)) \
            { \
                ZFCastZFObjectUnchecked(ZFStyleable *, d->buttonIcon)->styleableCopyFrom(ZFCastZFObjectUnchecked(ZFStyleable *, this->buttonIconStyle##StateName())); \
            } \
            d->updateButtonIcon(); \
        } \
        if(d->buttonBackground != zfnull) \
        { \
            if(ZFPropertyIsValueAccessed(ZFPropertyAccess(ZFUIButtonBasic, buttonBackgroundStyle##StateName), this)) \
            { \
                ZFCastZFObjectUnchecked(ZFStyleable *, d->buttonBackground)->styleableCopyFrom(ZFCastZFObjectUnchecked(ZFStyleable *, this->buttonBackgroundStyle##StateName())); \
            } \
            d->updateButtonBackground(); \
        }
    switch(this->buttonState())
    {
        case ZFUIButtonState::e_Normal:
            _ZFP_ZFUIButtonBasic_buttonStateOn(Normal)
            break;
        case ZFUIButtonState::e_Highlighted:
            _ZFP_ZFUIButtonBasic_buttonStateOn(Highlighted)
            break;
        case ZFUIButtonState::e_Checked:
            _ZFP_ZFUIButtonBasic_buttonStateOn(Checked)
            break;
        case ZFUIButtonState::e_CheckedHighlighted:
            _ZFP_ZFUIButtonBasic_buttonStateOn(CheckedHighlighted)
            break;
        case ZFUIButtonState::e_Disabled:
            _ZFP_ZFUIButtonBasic_buttonStateOn(Disabled)
            break;
        default:
            break;
    }
}

const ZFClass *ZFUIButtonBasic::buttonLabelClass(void)
{
    return ZFUITextView::ClassData();
}
const ZFClass *ZFUIButtonBasic::buttonIconClass(void)
{
    return ZFUIImageView::ClassData();
}
const ZFClass *ZFUIButtonBasic::buttonBackgroundClass(void)
{
    return ZFUIImageView::ClassData();
}

ZFMETHOD_DEFINE_0(ZFUIButtonBasic, ZFUITextView *, buttonLabel)
{
    this->prepareButtonLabel();
    return d->buttonLabel;
}
ZFMETHOD_DEFINE_0(ZFUIButtonBasic, ZFUIImageView *, buttonIcon)
{
    this->prepareButtonIcon();
    return d->buttonIcon;
}
ZFMETHOD_DEFINE_0(ZFUIButtonBasic, ZFUIImageView *, buttonBackground)
{
    this->prepareButtonBackground();
    return d->buttonBackground;
}

ZFMETHOD_DEFINE_0(ZFUIButtonBasic, void, prepareButtonLabel)
{
    if(d->buttonLabel == zfnull)
    {
        ZFObject *obj = zfRetainWithoutLeakTest(this->buttonLabelClass()->newInstanceWithoutLeakTest().toObject());
        d->buttonLabel = ZFCastZFObject(ZFUITextView *, obj);
        zfCoreAssert(d->buttonLabel != zfnull);
        this->internalBackgroundViewAdd(ZFCastZFObjectUnchecked(ZFUIView *, d->buttonLabel));
    }
}
ZFMETHOD_DEFINE_0(ZFUIButtonBasic, void, prepareButtonIcon)
{
    if(d->buttonIcon == zfnull)
    {
        ZFObject *obj = zfRetainWithoutLeakTest(this->buttonIconClass()->newInstanceWithoutLeakTest().toObject());
        d->buttonIcon = ZFCastZFObject(ZFUIImageView *, obj);
        zfCoreAssert(d->buttonIcon != zfnull);
        this->internalBackgroundViewAdd(ZFCastZFObjectUnchecked(ZFUIView *, d->buttonIcon));

        if(d->buttonLabel != zfnull)
        {
            ZFUIView *t = d->buttonLabel->to<ZFUIView *>();
            this->internalBackgroundViewRemove(t);
            this->internalBackgroundViewAdd(t);
        }
    }
}
ZFMETHOD_DEFINE_0(ZFUIButtonBasic, void, prepareButtonBackground)
{
    if(d->buttonBackground == zfnull)
    {
        ZFObject *obj = zfRetainWithoutLeakTest(this->buttonBackgroundClass()->newInstanceWithoutLeakTest().toObject());
        d->buttonBackground = ZFCastZFObject(ZFUIImageView *, obj);
        zfCoreAssert(d->buttonBackground != zfnull);
        this->internalBackgroundViewAdd(ZFCastZFObjectUnchecked(ZFUIView *, d->buttonBackground));

        if(d->buttonIcon != zfnull)
        {
            ZFUIView *t = d->buttonIcon->to<ZFUIView *>();
            this->internalBackgroundViewRemove(t);
            this->internalBackgroundViewAdd(t);
        }
        if(d->buttonLabel != zfnull)
        {
            ZFUIView *t = d->buttonLabel->to<ZFUIView *>();
            this->internalBackgroundViewRemove(t);
            this->internalBackgroundViewAdd(t);
        }
    }
}

// ============================================================
ZFLANGAPPLY_DEFINE(ZFUIButtonBasic, ZFUIButtonBasicTextNormal, {obj->buttonLabelTextSet(langValue, ZFUIButtonState::e_Normal);})
ZFLANGAPPLY_DEFINE(ZFUIButtonBasic, ZFUIButtonBasicTextHighlighted, {obj->buttonLabelTextSet(langValue, ZFUIButtonState::e_Highlighted);})
ZFLANGAPPLY_DEFINE(ZFUIButtonBasic, ZFUIButtonBasicTextChecked, {obj->buttonLabelTextSet(langValue, ZFUIButtonState::e_Checked);})
ZFLANGAPPLY_DEFINE(ZFUIButtonBasic, ZFUIButtonBasicTextCheckedHighlighted, {obj->buttonLabelTextSet(langValue, ZFUIButtonState::e_CheckedHighlighted);})
ZFLANGAPPLY_DEFINE(ZFUIButtonBasic, ZFUIButtonBasicTextDisabled, {obj->buttonLabelTextSet(langValue, ZFUIButtonState::e_Disabled);})

ZF_NAMESPACE_GLOBAL_END

