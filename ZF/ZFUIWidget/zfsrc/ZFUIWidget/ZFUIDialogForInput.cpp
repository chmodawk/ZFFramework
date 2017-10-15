/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIDialogForInput.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFSTYLE_DEFAULT_DEFINE(ZFUIDialogForInput)

void ZFUIDialogForInput::objectOnInit(void)
{
    zfsuper::objectOnInit();

    this->dialogContentContainer()->childAdd(this->inputView());

    ZFLISTENER_LOCAL(inputOnConfirm, {
        ZFUIDialogForInput *dialog = userData->to<ZFObjectHolder *>()->holdedObj;
        ZFUIButton *button = dialog->dialogButtonYes(zffalse);
        if(button != zfnull)
        {
            button->buttonSimulateClick();
        }
    })
    this->inputView()->observerAdd(ZFUITextEdit::EventTextOnEditConfirm(), inputOnConfirm, this->objectHolder());
}
void ZFUIDialogForInput::objectOnDealloc(void)
{
    zfsuper::objectOnDealloc();
}

ZF_NAMESPACE_GLOBAL_END

