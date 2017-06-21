/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFDebugLevel.h
 * @brief debug level define
 */

#ifndef _ZFI_ZFDebugLevel_h_
#define _ZFI_ZFDebugLevel_h_

#include "ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief debug level
 *
 * similar to Android's Log.v() to Log.e()\n
 * app's global debug level can be set or get by #ZFDebugLevelSet/#ZFDebugLevelGet,
 * you may achieve your own debug level specified behavior\n
 * it's ensured lower level has smaller value
 */
ZFENUM_BEGIN(ZFDebugLevel)
    ZFENUM_VALUE(Verbose)
    ZFENUM_VALUE(Debug)
    ZFENUM_VALUE(Info)
    ZFENUM_VALUE(Warning)
    ZFENUM_VALUE(Error)
    ZFENUM_VALUE(Assert)
ZFENUM_SEPARATOR(ZFDebugLevel)
    ZFENUM_VALUE_REGISTER(Verbose)
    ZFENUM_VALUE_REGISTER(Debug)
    ZFENUM_VALUE_REGISTER(Info)
    ZFENUM_VALUE_REGISTER(Warning)
    ZFENUM_VALUE_REGISTER(Error)
    ZFENUM_VALUE_REGISTER(Assert)
ZFENUM_END_WITH_DEFAULT(ZFDebugLevel, Warning)

/** @brief see #ZFDebugLevel, #ZFDebugLevel::e_Warning by default */
extern ZF_ENV_EXPORT void ZFDebugLevelSet(ZF_IN ZFDebugLevelEnum level);
/** @brief see #ZFDebugLevel */
extern ZF_ENV_EXPORT ZFDebugLevelEnum ZFDebugLevelGet(void);

/**
 * @brief true if specified level is active
 *   (i.e. #ZFDebugLevelGet not greater than the specified level)
 */
inline zfbool ZFDebugLevelIsActive(ZF_IN ZFDebugLevelEnum level)
{
    return (ZFDebugLevelGet() <= level);
}

ZF_NAMESPACE_GLOBAL_END

#endif // #ifndef _ZFI_ZFDebugLevel_h_

