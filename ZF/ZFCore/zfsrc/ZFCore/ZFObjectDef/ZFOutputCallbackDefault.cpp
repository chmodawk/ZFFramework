/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFOutputCallbackDefault.h"
#include "ZFObjectImpl.h"
#include "ZFGlobalEventCenter.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFOBSERVER_EVENT_GLOBAL_REGISTER(ZFGlobalEvent, ZFOutputCallbackDefaultOnChange)

ZFOutputCallback _ZFP_ZFOutputCallbackDefault;

void ZFOutputCallbackDefaultSet(ZF_IN const ZFOutputCallback &v)
{
    _ZFP_ZFOutputCallbackDefault = v;
    ZFGlobalEventCenter::instance()->observerNotify(ZFGlobalEvent::EventZFOutputCallbackDefaultOnChange());
}

ZF_NAMESPACE_GLOBAL_END

#if 1 // ZFObject related method register
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_0(const ZFOutputCallback &, ZFOutputCallbackDefault)
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(void, ZFOutputCallbackDefaultSet, ZFMP_IN(const ZFOutputCallback &, v))

ZF_NAMESPACE_GLOBAL_END
#endif

