/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIViewPositionOnScreen.h"
#include "protocol/ZFProtocolZFUIViewPositionOnScreen.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_FUNC_DEFINE_2(void, ZFUIViewPositionOnScreen,
                       ZFMP_OUT(ZFUIRect &, rect),
                       ZFMP_IN(ZFUIView *, view))
{
    ZFPROTOCOL_ACCESS(ZFUIViewPositionOnScreen)->viewPositionOnScreen(view, rect);
    rect = ZFUIRectApplyScaleReversely(rect, view->scaleGetFixed());
}
ZFMETHOD_FUNC_DEFINE_INLINE_1(ZFUIRect, ZFUIViewPositionOnScreen,
                              ZFMP_IN(ZFUIView *, view))

ZF_NAMESPACE_GLOBAL_END

