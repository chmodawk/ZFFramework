/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFFileBOM.h
 * @brief file BOM defines
 */

#ifndef _ZFI_ZFFileBOM_h_
#define _ZFI_ZFFileBOM_h_

#include "ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief max BOM size
 */
#define ZFFileBOMMaxSize 8
/**
 * @brief file's BOM info, '\0' terminated
 */
zfclassPOD ZF_ENV_EXPORT ZFFileBOM
{
public:
    /**
     * @brief file's BOM info, '\0' terminated
     */
    zfbyte BOM[ZFFileBOMMaxSize];
};
ZFPROPERTY_TYPE_DECLARE(ZFFileBOM, ZFFileBOM)
ZFOUTPUT_TYPE(ZFFileBOM, {output << ZFFileBOMToString(v);})
ZFCORE_POD_COMPARER_DECLARE(ZFFileBOM)

/** @brief list of file BOM */
typedef ZFCoreArrayPOD<ZFFileBOM> ZFFileBOMList;
ZFCORETYPE_STRING_CONVERTER_DECLARE(ZFFileBOMList, ZFFileBOMList)

// ============================================================
/**
 * @brief UTF8 BOM
 */
ZFEXPORT_VAR_READONLY_DECLARE(ZFFileBOM, ZFFileBOMUTF8)

// ============================================================
/**
 * @brief default file BOM list, #ZFFileBOMUTF8 by default
 */
ZFEXPORT_VAR_READONLY_DECLARE(ZFFileBOMList, ZFFileBOMListDefault)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFFileBOM_h_

