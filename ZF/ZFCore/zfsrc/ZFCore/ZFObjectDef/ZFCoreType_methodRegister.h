/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFCoreTypeMethodRegister.h
 * @brief export some methods for ZFObject core
 */

#ifndef _ZFI_ZFCoreTypeMethodRegister_h_
#define _ZFI_ZFCoreTypeMethodRegister_h_

#include "ZFExport.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFEXPORT_VAR_READONLY_DECLARE(zfindexRange, zfindexRangeZero)
ZFEXPORT_VAR_READONLY_DECLARE(zfindexRange, zfindexRangeMax)

ZFEXPORT_VAR_READONLY_DECLARE(zfindex, ZFVERSION_MAIN)
ZFEXPORT_VAR_READONLY_DECLARE(zfindex, ZFVERSION_SUB)
ZFEXPORT_VAR_READONLY_DECLARE(zfindex, ZFVERSION_MINOR)
ZFEXPORT_VAR_READONLY_DECLARE(zfindex, ZFVERSION_BUILD)

ZFEXPORT_VAR_READONLY_DECLARE(ZFTokenForContainer, ZFTokenForContainerTrim)
ZFEXPORT_VAR_READONLY_DECLARE(ZFTokenForContainer, ZFTokenForContainerDetail)
ZFEXPORT_VAR_READONLY_DECLARE(ZFTokenForContainer, ZFTokenForContainerPlainList)
ZFEXPORT_VAR_DECLARE(ZFTokenForContainer, ZFTokenForContainerDefault)

ZFEXPORT_VAR_READONLY_DECLARE(ZFTokenForKeyValueContainer, ZFTokenForKeyValueContainerTrim)
ZFEXPORT_VAR_READONLY_DECLARE(ZFTokenForKeyValueContainer, ZFTokenForKeyValueContainerDetail)
ZFEXPORT_VAR_DECLARE(ZFTokenForKeyValueContainer, ZFTokenForKeyValueContainerDefault)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFCoreTypeMethodRegister_h_

