/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFFileUtil.h
 * @brief file utility
 */

#ifndef _ZFI_ZFFileUtil_h_
#define _ZFI_ZFFileUtil_h_

#include "ZFFile.h"
ZF_NAMESPACE_GLOBAL_BEGIN
ZF_NAMESPACE_BEGIN(ZFFileUtil)

/**
 * @brief list all files, usually for debug use
 */
ZFMETHOD_FUNC_DECLARE_DETAIL_4(ZFFileUtil, void, fileList,
                               ZFMP_IN_OPT(const zfchar *, path, zfText(".")),
                               ZFMP_IN_OPT(const ZFOutputCallback &, outputCallback, ZFOutputCallbackDefault()),
                               ZFMP_IN_OPT(const zfchar *, headToken, zfnull),
                               ZFMP_IN_OPT(const zfchar *, indentToken, zfText("  ")))

/**
 * @brief list all resource files, usually for debug use
 */
ZFMETHOD_FUNC_DECLARE_DETAIL_4(ZFFileUtil, void, resFileList,
                               ZFMP_IN_OPT(const zfchar *, path, zfText(".")),
                               ZFMP_IN_OPT(const ZFOutputCallback &, outputCallback, ZFOutputCallbackDefault()),
                               ZFMP_IN_OPT(const zfchar *, headToken, zfnull),
                               ZFMP_IN_OPT(const zfchar *, indentToken, zfText("  ")))

ZF_NAMESPACE_END(ZFFileUtil)
ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFFileUtil_h_

