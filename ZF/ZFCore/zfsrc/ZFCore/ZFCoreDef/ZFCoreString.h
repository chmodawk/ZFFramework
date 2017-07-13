/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFCoreString.h
 * @brief tricks to wrap std::string
 */

#ifndef _ZFI_ZFCoreString_h_
#define _ZFI_ZFCoreString_h_

#include "ZFCoreString_impl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

/** @brief see #_zfstr */
#ifndef _ZFT_ZFCoreStringA
    typedef ZFCoreStringA_impl ZFCoreStringA;
#else
    typedef _ZFT_ZFCoreStringA ZFCoreStringA;
#endif

/** @brief see #_zfstr */
#ifndef _ZFT_ZFCoreStringW
    typedef ZFCoreStringW_impl ZFCoreStringW;
#else
    typedef _ZFT_ZFCoreStringW ZFCoreStringW;
#endif

// ============================================================
#if 1 // you must change these if change zfchar's type
/**
 * @brief string types used in ZFFramework
 */
#ifndef _ZFT_ZFCoreString
    typedef ZFCoreStringA ZFCoreString;
#else
    typedef _ZFT_ZFCoreString ZFCoreString;
#endif
#endif // you must change these if change zfchar's type
// ============================================================

ZF_NAMESPACE_GLOBAL_END

#endif // #ifndef _ZFI_ZFCoreString_h_

