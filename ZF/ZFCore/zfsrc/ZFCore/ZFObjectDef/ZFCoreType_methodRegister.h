/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFCoreType_methodRegister.h
 * @brief export some methods for ZFObject core
 */

#ifndef _ZFI_ZFCoreType_methodRegister_h_
#define _ZFI_ZFCoreType_methodRegister_h_

#include "ZFExport.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/** @cond ZFPrivateDoc */
ZFEXPORT_VAR_READONLY_VALUEREF_DECLARE(zfindexRange, zfindexRangeZero, zfindexRangeZero())
ZFEXPORT_VAR_READONLY_VALUEREF_DECLARE(zfindexRange, zfindexRangeMax, zfindexRangeMax())

ZFEXPORT_VAR_READONLY_DECLARE(zfindex, ZFVERSION_MAIN)
ZFEXPORT_VAR_READONLY_DECLARE(zfindex, ZFVERSION_SUB)
ZFEXPORT_VAR_READONLY_DECLARE(zfindex, ZFVERSION_MINOR)
ZFEXPORT_VAR_READONLY_DECLARE(zfindex, ZFVERSION_BUILD)

ZFEXPORT_VAR_READONLY_VALUEREF_DECLARE(ZFTokenForContainer, ZFTokenForContainerTrim, ZFTokenForContainerTrim())
ZFEXPORT_VAR_READONLY_VALUEREF_DECLARE(ZFTokenForContainer, ZFTokenForContainerDetail, ZFTokenForContainerDetail())
ZFEXPORT_VAR_READONLY_VALUEREF_DECLARE(ZFTokenForContainer, ZFTokenForContainerPlainList, ZFTokenForContainerPlainList())
ZFEXPORT_VAR_VALUEREF_DECLARE(ZFTokenForContainer, ZFTokenForContainerDefault, ZFTokenForContainerDefault())

ZFEXPORT_VAR_READONLY_VALUEREF_DECLARE(ZFTokenForKeyValueContainer, ZFTokenForKeyValueContainerTrim, ZFTokenForKeyValueContainerTrim())
ZFEXPORT_VAR_READONLY_VALUEREF_DECLARE(ZFTokenForKeyValueContainer, ZFTokenForKeyValueContainerDetail, ZFTokenForKeyValueContainerDetail())
ZFEXPORT_VAR_VALUEREF_DECLARE(ZFTokenForKeyValueContainer, ZFTokenForKeyValueContainerDefault, ZFTokenForKeyValueContainerDefault())
/** @endcond */

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFCoreType_methodRegister_h_

