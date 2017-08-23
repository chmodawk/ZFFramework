/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFEnvInfo.h
 * @brief info of native environment
 */

#ifndef _ZFI_ZFEnvInfo_h_
#define _ZFI_ZFEnvInfo_h_

#include "ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/** @brief see #ZFEnvInfo::envSummaryCallbackRegister */
typedef void (*ZFEnvSummaryCallback)(ZF_IN_OUT zfstring &ret);

ZF_NAMESPACE_BEGIN(ZFEnvInfo)

// ============================================================
/**
 * @brief util method to get summary info
 */
ZFMETHOD_FUNC_DECLARE_DETAIL_1(ZFEnvInfo, void, envSummary,
                               ZFMP_IN_OUT(zfstring &, ret))
/**
 * @brief name of native system, e.g. "iOS", empty if not available
 */
ZFMETHOD_FUNC_DECLARE_DETAIL_0(ZFEnvInfo, zfstring, envSummary)

/**
 * @brief register a callback to output custom env info, see #envSummary
 */
extern ZF_ENV_EXPORT void envSummaryCallbackRegister(ZF_IN const zfchar *name, ZF_IN ZFEnvSummaryCallback callback);
/** @brief see #envSummaryCallbackRegister */
extern ZF_ENV_EXPORT void envSummaryCallbackUnregister(ZF_IN const zfchar *name);

// ============================================================
/**
 * @brief name of native system, e.g. "iOS", empty if not available
 */
ZFMETHOD_FUNC_DECLARE_DETAIL_1(ZFEnvInfo, void, systemName,
                               ZFMP_IN_OUT(zfstring &, ret));
/**
 * @brief name of native system, e.g. "iOS", empty if not available
 */
ZFMETHOD_FUNC_DECLARE_DETAIL_0(ZFEnvInfo, zfstring, systemName)
/**
 * @brief version of native system, e.g. "9.0.1", empty if not available
 */
ZFMETHOD_FUNC_DECLARE_DETAIL_1(ZFEnvInfo, void, systemVersion,
                               ZFMP_IN_OUT(zfstring &, ret));
/**
 * @brief version of native system, e.g. "9.0.1", empty if not available
 */
ZFMETHOD_FUNC_DECLARE_DETAIL_0(ZFEnvInfo, zfstring, systemVersion)

// ============================================================
/**
 * @brief name of native framework, e.g. "Qt", empty if not available
 */
ZFMETHOD_FUNC_DECLARE_DETAIL_1(ZFEnvInfo, void, frameworkName,
                               ZFMP_IN_OUT(zfstring &, ret));
/**
 * @brief name of native framework, e.g. "Qt", empty if not available
 */
ZFMETHOD_FUNC_DECLARE_DETAIL_0(ZFEnvInfo, zfstring, frameworkName)
/**
 * @brief version of native framework, e.g. "9.0.1", empty if not available
 */
ZFMETHOD_FUNC_DECLARE_DETAIL_1(ZFEnvInfo, void, frameworkVersion,
                               ZFMP_IN_OUT(zfstring &, ret));
/**
 * @brief version of native framework, e.g. "9.0.1", empty if not available
 */
ZFMETHOD_FUNC_DECLARE_DETAIL_0(ZFEnvInfo, zfstring, frameworkVersion)

ZF_NAMESPACE_END(ZFEnvInfo)
ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFEnvInfo_h_

