/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFTimeLineProperty_ZFCore4.h
 * @brief see #ZFTimeLineProperty
 */
#ifndef _ZFI_ZFTimeLineProperty_ZFCore4_h_
#define _ZFI_ZFTimeLineProperty_ZFCore4_h_

#include "ZFTimeLineProperty.h"
// ZFDoxygenBugFix
// this file was separated from ZFTimeLineProperty_ZFCore.h
// because of doxygen can not parse large macro generated file
// the original error message was:
//   "input buffer overflow, can't enlarge buffer because scanner uses REJECT"
ZF_NAMESPACE_GLOBAL_BEGIN

/** @cond ZFPrivateDoc */
#if defined(_MSC_VER)
    // implicit convert from float to int64
    #pragma warning(push)
    #pragma warning(disable:4244)
#endif
/** @endcond */
ZFTIMELINEPROPERTY_DECLARE_BY_VALUE(zftimet)
/** @cond ZFPrivateDoc */
#if defined(_MSC_VER)
    #pragma warning(pop)
#endif
/** @endcond */

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFTimeLineProperty_ZFCore4_h_

