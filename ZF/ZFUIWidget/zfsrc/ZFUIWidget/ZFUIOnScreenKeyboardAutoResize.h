/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFUIOnScreenKeyboardAutoResize.h
 * @brief auto fit #ZFUIWindow accorrding to #ZFUIOnScreenKeyboardState
 */

#ifndef _ZFI_ZFUIOnScreenKeyboardAutoResize_h_
#define _ZFI_ZFUIOnScreenKeyboardAutoResize_h_

#include "ZFUIWidgetDef.h"

ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief auto resize #ZFUIWindow accorrding to #ZFUIOnScreenKeyboardState
 *
 * resize logic are done by changing window's #ZFUIViewLayoutParam::layoutMargin\n
 * \n
 * #ZFUIOnScreenKeyboardAutoFitStop would be applied automatically when owner window destroyed
 */
ZFMETHOD_FUNC_DECLARE_1(void, ZFUIOnScreenKeyboardAutoResizeStart,
                        ZFMP_IN(ZFUIWindow *, window))
/** @brief see #ZFUIOnScreenKeyboardAutoResizeStart */
ZFMETHOD_FUNC_DECLARE_1(void, ZFUIOnScreenKeyboardAutoResizeStop,
                        ZFMP_IN(ZFUIWindow *, window))

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIOnScreenKeyboardAutoResize_h_

