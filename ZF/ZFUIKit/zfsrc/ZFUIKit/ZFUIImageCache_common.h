/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFUIImageCache_common.h
 * @brief image load with cache logic
 */

#ifndef _ZFI_ZFUIImageCache_common_h_
#define _ZFI_ZFUIImageCache_common_h_

#include "ZFUIImageCache.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief #ZFUIImageLoadFromInput with cache logic
 */
ZFMETHOD_FUNC_DECLARE_1(zfautoObject, ZFUIImageLoadFromInputWithCache,
                        ZFMP_IN(const ZFInputCallback &, input))

/**
 * @brief #ZFUIImageLoadFromColor with cache logic
 */
ZFMETHOD_FUNC_DECLARE_2(zfautoObject, ZFUIImageLoadFromColorWithCache,
                        ZFMP_IN(const ZFUIColor &, color),
                        ZFMP_IN_OPT(const ZFUISize &, size, ZFUISizeZero))

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIImageCache_common_h_

