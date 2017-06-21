/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFLuaGC.h
 * @brief perform garbage collect in lua
 */

#ifndef _ZFI_ZFLuaGC_h_
#define _ZFI_ZFLuaGC_h_

#include "ZFLuaDef.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief performa garbage collector in lua
 */
extern ZF_ENV_EXPORT void ZFLuaGC(void);

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFLuaGC_h_

