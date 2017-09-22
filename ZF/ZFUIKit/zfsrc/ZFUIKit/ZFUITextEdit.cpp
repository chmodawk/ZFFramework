/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUITextEdit.h"
#include "protocol/ZFProtocolZFUITextEdit.h"

#include "ZFUIViewFocus.h"
#include "ZFUIOnScreenKeyboardState.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFENUM_DEFINE(ZFUITextEditKeyboardType)

ZFENUM_DEFINE(ZFUITextEditKeyboardReturnType)
ZFENUM_DEFINE(ZFUITextEditKeyboardReturnAction)

ZFSTYLE_DEFAULT_DEFINE(ZFUITextEdit)

// ============================================================
// _ZFP_ZFUITextEditPrivate
zfclassNotPOD _ZFP_ZFUITextEditPrivate
{
public:
    ZFPROTOCOL_INTERFACE_CLASS(ZFUITextEdit) *impl;
    ZFUITextEdit *pimplOwner;
    zfbool textEditing;
    zfbool textChangedByImplFlag;
    zfbool textSelectRangeChangedByImplFlag;

public:
    void updateSizeRelatedProperty(void)
    {
        this->impl->textShadowOffsetSet(this->pimplOwner, ZFUISizeApplyScale(this->pimplOwner->textShadowOffset(), this->pimplOwner->scaleGetFixed()));
        this->impl->textSizeSet(this->pimplOwner, ZFUISizeApplyScale(this->pimplOwner->textSize(), this->pimplOwner->scaleGetFixed()));
    }

public:
    _ZFP_ZFUITextEditPrivate(void)
    : impl(ZFPROTOCOL_ACCESS(ZFUITextEdit))
    , pimplOwner(zfnull)
    , textEditing(zffalse)
    , textChangedByImplFlag(zffalse)
    , textSelectRangeChangedByImplFlag(zffalse)
    {
    }
};

// ============================================================
// ZFUITextEdit
ZFOBJECT_REGISTER(ZFUITextEdit)

ZFOBSERVER_EVENT_REGISTER(ZFUITextEdit, TextOnEditBegin)
ZFOBSERVER_EVENT_REGISTER(ZFUITextEdit, TextOnEditEnd)
ZFOBSERVER_EVENT_REGISTER(ZFUITextEdit, TextOnChangeCheck)
ZFOBSERVER_EVENT_REGISTER(ZFUITextEdit, TextOnChange)
ZFOBSERVER_EVENT_REGISTER(ZFUITextEdit, TextOnReturnClick)
ZFOBSERVER_EVENT_REGISTER(ZFUITextEdit, TextOnEditConfirm)

ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextEdit, zfbool, textEditEnable)
{
    d->impl->textEditEnableSet(this, this->textEditEnable());
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextEdit, zfbool, textEditSecured)
{
    d->impl->textEditSecuredSet(this, this->textEditSecured());
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextEdit, ZFUITextEditKeyboardTypeEnum, textEditKeyboardType)
{
    d->impl->textEditKeyboardTypeSet(this, this->textEditKeyboardType());
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextEdit, ZFUITextEditKeyboardReturnTypeEnum, textEditKeyboardReturnType)
{
    d->impl->textEditKeyboardReturnTypeSet(this, this->textEditKeyboardReturnType());
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextEdit, ZFRegExp *, textEditFilter)
{
    if(!this->text().isEmpty() && !this->textShouldChange(this->text()))
    {
        this->textSet(zfText(""));
    }
}
ZFPROPERTY_CUSTOM_ON_VERIFY_DEFINE(ZFUITextEdit, zfindexRange, textSelectRange)
{
    zfindex textLength = this->text().length();
    if(propertyValue.start >= textLength)
    {
        propertyValue = zfindexRangeZero();
    }
    else if(propertyValue.count > textLength - propertyValue.start)
    {
        propertyValue.count = textLength - propertyValue.start;
    }
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextEdit, zfindexRange, textSelectRange)
{
    if(d->textSelectRangeChangedByImplFlag)
    {
        d->textSelectRangeChangedByImplFlag = zffalse;
    }
    else
    {
        d->impl->textSelectRangeSet(this, this->textSelectRange());
    }
}

ZFPROPERTY_CUSTOM_ON_VERIFY_DEFINE(ZFUITextEdit, zfstring, text)
{
    if(!propertyValue.isEmpty() && !this->textShouldChange(propertyValue))
    {
        propertyValue.removeAll();
    }
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextEdit, zfstring, text)
{
    if(d->textChangedByImplFlag)
    {
        d->textChangedByImplFlag = zffalse;
    }
    else
    {
        d->impl->textSet(this, this->text());
    }
    if(propertyValueOld.compare(this->text()) != 0)
    {
        ZFCastZFObjectUnchecked(ZFUIView *, this->textPlaceHolder())->viewVisibleSet(this->text().isEmpty());
        this->layoutRequest();
    }
}

ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextEdit, ZFUITextAppearanceEnum, textAppearance)
{
    d->impl->textAppearanceSet(this, this->textAppearance());
    if(this->textAppearance() != propertyValueOld)
    {
        this->layoutRequest();
    }
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextEdit, ZFUIAlignFlags, textAlign)
{
    d->impl->textAlignSet(this, this->textAlign());
    this->textPlaceHolder()->textAlignSet(this->textAlign());
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextEdit, ZFUIColor, textColor)
{
    d->impl->textColorSet(this, this->textColor());
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextEdit, ZFUIColor, textShadowColor)
{
    d->impl->textShadowColorSet(this, this->textShadowColor());
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextEdit, ZFUISize, textShadowOffset)
{
    d->impl->textShadowOffsetSet(this, ZFUISizeApplyScale(this->textShadowOffset(), this->scaleGetFixed()));
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(ZFUITextEdit, zfint, textSize)
{
    d->impl->textSizeSet(this, ZFUISizeApplyScale(this->textSize(), this->scaleGetFixed()));
    if(this->textSize() != propertyValueOld)
    {
        this->layoutRequest();
    }
}

ZFObject *ZFUITextEdit::objectOnInit(void)
{
    zfsuper::objectOnInit();
    d = zfpoolNew(_ZFP_ZFUITextEditPrivate);
    d->pimplOwner = this;

    zfCoreAssert(this->nativeImplView() == zfnull);
    zfclassNotPOD _ZFP_ZFUITextEdit_nativeImplViewDestroy
    {
    public:
        static void action(ZF_IN ZFUIView *view,
                           ZF_IN void *nativeImplView)
        {
            ZFPROTOCOL_ACCESS(ZFUITextEdit)->nativeTextEditDestroy(view->to<ZFUITextEdit *>(), nativeImplView);
        }
    };
    this->nativeImplViewSet(d->impl->nativeTextEditCreate(this),
        _ZFP_ZFUITextEdit_nativeImplViewDestroy::action);

    ZFUIView *textPlaceHolderTmp = ZFCastZFObject(ZFUIView *, this->textPlaceHolder());
    if(textPlaceHolderTmp == zfnull)
    {
        if(this->textPlaceHolder() != zfnull)
        {
            zfCoreCriticalClassNotTypeOf(this->textPlaceHolder()->classData(), ZFUIView::ClassData());
        }
        else
        {
            zfCoreCriticalMessage(zfTextA("textPlaceHolder must not be null"));
        }
        return zfnull;
    }
    this->internalImplViewAdd(textPlaceHolderTmp);
    textPlaceHolderTmp->layoutParam()->sizeParamSet(ZFUISizeParamFillWidthFillHeight());
    textPlaceHolderTmp->serializableRefLayoutParam()->sizeParamSet(ZFUISizeParamFillWidthFillHeight());

    return this;
}
void ZFUITextEdit::objectOnDealloc(void)
{
    zfpoolDelete(d);
    d = zfnull;
    zfsuper::objectOnDealloc();
}
void ZFUITextEdit::objectOnInitFinish(void)
{
    zfsuper::objectOnInitFinish();
    d->updateSizeRelatedProperty();
}

void ZFUITextEdit::objectInfoOnAppend(ZF_IN_OUT zfstring &ret)
{
    zfsuper::objectInfoOnAppend(ret);

    if(!this->textPlaceHolder()->text().isEmpty())
    {
        zfstringAppend(ret, zfText(" (%s)"), this->textPlaceHolder()->text().cString());
    }

    if(this->textEditSecured())
    {
        ret += zfText(" EditSecured");
    }
    else if(!this->text().isEmpty())
    {
        zfstringAppend(ret, zfText(" \"%s\""), this->text().cString());
    }

    if(!this->textEditEnable())
    {
        ret += zfText(" EditDisabled");
    }
}

ZFMETHOD_DEFINE_1(ZFUITextEdit, ZFUISize, measureTextEdit,
                  ZFMP_IN_OPT(const ZFUISize &, sizeHint, ZFUISizeZero()))
{
    ZFUISize ret = ZFUISizeZero();
    ZFUISizeApplyScaleReversely(ret, d->impl->measureNativeTextEdit(this,
        ZFUISizeApplyScale(ZFUIViewLayoutParam::sizeHintOffset(sizeHint, ZFUISizeMake(
                    0 - ZFUIMarginGetX(this->nativeImplViewMargin()),
                    0 - ZFUIMarginGetY(this->nativeImplViewMargin())
                )),
            this->scaleGetFixed()),
        ZFUISizeApplyScale(this->textSize(), this->scaleGetFixed())),
        this->scaleGetFixed());
    if(ZFPropertyIsValueAccessed(ZFPropertyAccess(ZFUITextEdit, textPlaceHolder), this)
        && !this->textPlaceHolder()->text().isEmpty())
    {
        ZFUISize hintSize = this->textPlaceHolder()->to<ZFUITextView *>()->measureTextView();
        if(ret.width < hintSize.width)
        {
            ret.width = hintSize.width;
        }
        if(ret.height < hintSize.height)
        {
            ret.height = hintSize.height;
        }
    }
    ZFUISizeApplyMarginReversely(ret, ret, this->nativeImplViewMargin());
    return ret;
}

void ZFUITextEdit::_ZFP_ZFUITextEdit_textNotifyBeginEdit(void)
{
    d->textEditing = zftrue;
    this->textOnEditBegin();
}
void ZFUITextEdit::_ZFP_ZFUITextEdit_textNotifyEndEdit(void)
{
    d->textEditing = zffalse;
    this->textOnEditEnd();
}
void ZFUITextEdit::_ZFP_ZFUITextEdit_textNotifyChange(ZF_IN const zfchar *newText)
{
    zfstring oldText = this->text();

    d->textChangedByImplFlag = zftrue;
    this->textSet(newText);

    this->textOnChange(oldText);
}
void ZFUITextEdit::_ZFP_ZFUITextEdit_textSelectRangeNotifyChange(void)
{
    if(d->textSelectRangeChangedByImplFlag)
    {
        return ;
    }

    zfindexRange tmp = zfindexRangeZero();
    d->impl->textSelectRange(this, tmp);

    d->textSelectRangeChangedByImplFlag = zftrue;
    this->textSelectRangeSet(tmp);
}
void ZFUITextEdit::_ZFP_ZFUITextEdit_textNotifyReturnClicked(void)
{
    this->textOnReturnClick();

    switch(this->textEditKeyboardReturnAction())
    {
        case ZFUITextEditKeyboardReturnAction::e_None:
            break;
        case ZFUITextEditKeyboardReturnAction::e_Confirm:
            this->textEditNotifyConfirm();
            break;
        case ZFUITextEditKeyboardReturnAction::e_FocusNext:
            if(!this->viewFocused() || !this->textEditConfirmWhenLostFocus())
            {
                this->textEditNotifyConfirm();
            }
            if(this->viewFocused())
            {
                ZFUIView *next = ZFUIViewFocusNextFind(this);
                if(next == zfnull)
                {
                    this->textEditEnd();
                }
                else
                {
                    ZFUITextEdit *nextTmp = ZFCastZFObject(ZFUITextEdit *, next);
                    if(nextTmp != zfnull)
                    {
                        nextTmp->textEditBegin();
                    }
                    else
                    {
                        next->viewFocusRequest(zftrue);
                    }
                }
            }
            break;
        case ZFUITextEditKeyboardReturnAction::e_HideKeyboard:
        {
            this->textEditNotifyConfirm();
            ZFUIOnScreenKeyboardState *keyboardState = ZFUIOnScreenKeyboardState::instanceForView(this);
            if(keyboardState != zfnull && keyboardState->keyboardShowing() && this->textEditing())
            {
                this->textEditEnd();
            }
        }
            break;
        default:
            zfCoreCriticalShouldNotGoHere();
            return ;
    }
}
ZFMETHOD_DEFINE_1(ZFUITextEdit, zfbool, textShouldChange,
                  ZFMP_IN(const zfchar *, newText))
{
    zfbool shouldChange = zftrue;
    this->textOnChangeCheck(newText, shouldChange);
    if(!shouldChange && newText != zfnull && *newText != '\0')
    {
        return zffalse;
    }
    else
    {
        return zftrue;
    }
}
ZFMETHOD_DEFINE_0(ZFUITextEdit, void, textEditBegin)
{
    d->impl->textEditBegin(this);
}
ZFMETHOD_DEFINE_0(ZFUITextEdit, void, textEditEnd)
{
    d->impl->textEditEnd(this);
}
ZFMETHOD_DEFINE_0(ZFUITextEdit, zfbool, textEditing)
{
    return d->textEditing;
}

void ZFUITextEdit::textOnEditBegin(void)
{
    this->observerNotify(ZFUITextEdit::EventTextOnEditBegin());
}
void ZFUITextEdit::textOnEditEnd(void)
{
    this->observerNotify(ZFUITextEdit::EventTextOnEditEnd());
}
void ZFUITextEdit::textOnChangeCheck(ZF_IN const zfchar *newText, ZF_IN_OUT zfbool &shouldChange)
{
    shouldChange = zftrue;
    if(newText != zfnull && *newText != '\0' && this->textEditFilter() != zfnull)
    {
        ZFRegExpResult regexpResult;
        this->textEditFilter()->regExpMatchExact(regexpResult, newText);
        if(!regexpResult.matched)
        {
            shouldChange = zffalse;
            return ;
        }
    }

    if(this->observerHasAdd(ZFUITextEdit::EventTextOnChangeCheck()))
    {
        zfautoObject t = ZFValueEditable::boolValueCreate(shouldChange);
        this->observerNotify(ZFUITextEdit::EventTextOnChangeCheck(), zflineAllocWithoutLeakTest(ZFString, newText), t.toObject());
        shouldChange = t.to<ZFValue *>()->boolValue();
    }
}
void ZFUITextEdit::textOnChange(ZF_IN const zfchar *oldText)
{
    if(this->observerHasAdd(ZFUITextEdit::EventTextOnChange()))
    {
        zfblockedAlloc(ZFString, oldTextTmp, oldText);
        this->observerNotify(ZFUITextEdit::EventTextOnChange(), oldTextTmp);
    }
}
void ZFUITextEdit::textOnReturnClick(void)
{
    this->observerNotify(ZFUITextEdit::EventTextOnReturnClick());
}
void ZFUITextEdit::textOnEditConfirm(void)
{
    this->observerNotify(ZFUITextEdit::EventTextOnEditConfirm());
}

void ZFUITextEdit::scaleOnChange(void)
{
    zfsuper::scaleOnChange();
    d->updateSizeRelatedProperty();
}
void ZFUITextEdit::layoutOnMeasure(ZF_OUT ZFUISize &ret,
                                   ZF_IN const ZFUISize &sizeHint,
                                   ZF_IN const ZFUISizeParam &sizeParam)
{
    ret = this->viewSizePrefered();
    if(ret.width < 0)
    {
        ret.width = ZFUIGlobalStyle::DefaultStyle()->itemSizeControl();
    }
    if(ret.height < 0)
    {
        ret.height = ZFUIGlobalStyle::DefaultStyle()->itemSizeControl();
    }
}
void ZFUITextEdit::layoutOnLayout(ZF_IN const ZFUIRect &bounds)
{
    zfsuper::layoutOnLayout(bounds);
}
void ZFUITextEdit::viewEventOnKeyEvent(ZF_IN ZFUIKeyEvent *keyEvent)
{
    switch(keyEvent->keyCode)
    {
        case ZFUIKeyCode::e_kShift:
        case ZFUIKeyCode::e_kTab:
            zfsuper::viewEventOnKeyEvent(keyEvent);
            break;
        default:
            keyEvent->eventResolvedSet(zftrue);
            break;
    }
}
void ZFUITextEdit::viewFocusOnChange(void)
{
    zfsuper::viewFocusOnChange();
    if(!this->viewFocused() && this->textEditConfirmWhenLostFocus())
    {
        this->textEditNotifyConfirm();
    }
}

zfbool ZFUITextEdit::internalViewShouldLayout(ZF_IN ZFUIView *internalView)
{
    if(internalView == this->textPlaceHolder()->toObject())
    {
        return zffalse;
    }
    return zfsuper::internalViewShouldLayout(internalView);
}
void ZFUITextEdit::internalBackgroundViewOnLayout(ZF_IN const ZFUIRect &bounds)
{
    zfsuper::internalBackgroundViewOnLayout(bounds);

    ZFUITextView *textPlaceHolder = this->textPlaceHolder()->to<ZFUITextView *>();
    textPlaceHolder->layout(ZFUIRectApplyMargin(
            bounds,
            ZFUIMarginInc(this->nativeImplViewMargin(), textPlaceHolder->layoutParam()->layoutMargin())
        ));
}

ZF_NAMESPACE_GLOBAL_END

