/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIKeyEvent.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFOBJECT_REGISTER(ZFUIKeyEvent)
ZFCACHEABLE_DEFINE(ZFUIKeyEvent, ZFUIKeyEvent)

void ZFUIKeyEvent::objectInfoOnAppend(ZF_IN_OUT zfstring &ret)
{
    ret += ZFUIKeyAction::EnumNameForValue(this->keyAction);
    ret += zfText(" ");
    ret += ZFUIKeyCode::EnumNameForValue(this->keyCode);

    if(this->eventResolved())
    {
        ret += zfText(" (resolved)");
    }
}

// ============================================================
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFUIKeyEvent, zfidentity, keyId)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFUIKeyEvent, ZFUIKeyActionEnum, keyAction)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFUIKeyEvent, ZFUIKeyCodeEnum, keyCode)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR(ZFUIKeyEvent, zfflags, keyCodeRaw)

ZF_NAMESPACE_GLOBAL_END

