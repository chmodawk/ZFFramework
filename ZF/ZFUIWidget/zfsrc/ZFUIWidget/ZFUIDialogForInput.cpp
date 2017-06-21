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

ZFObject *ZFUIDialogForInput::objectOnInit(void)
{
    zfsuper::objectOnInit();

    this->dialogContentContainer()->childAdd(this->inputView());

    return this;
}
void ZFUIDialogForInput::objectOnDealloc(void)
{
    zfsuper::objectOnDealloc();
}

ZF_NAMESPACE_GLOBAL_END

