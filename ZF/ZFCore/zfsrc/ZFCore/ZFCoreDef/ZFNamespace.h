/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFNamespace.h
 * @brief namespace used by ZFFramework
 */
#ifndef _ZFI_ZFNamespace_h_
#define _ZFI_ZFNamespace_h_

/**
 * @brief begin namespace
 */
#define ZF_NAMESPACE_BEGIN(NameSpace) \
    /** @brief \n */ \
    namespace NameSpace {
/**
 * @brief end namespace
 */
#define ZF_NAMESPACE_END(NameSpace) \
    }
/**
 * @brief use namespace
 */
#define ZF_NAMESPACE_USE(NameSpace) \
    using namespace NameSpace;

/**
 * @brief global namespace id for impl
 */
#define ZF_NAMESPACE_GLOBAL_ID ZF
/**
 * @brief abbreviation for global namespace id for impl
 */
#define ZF_NAMESPACE_GLOBAL_ID_ABBR zf
/**
 * @def ZF_NAMESPACE_GLOBAL
 * @brief namespace of ZFFramework
 * @def ZF_NAMESPACE_GLOBAL_BEGIN
 * @brief begin namespace ZFFramework
 * @def ZF_NAMESPACE_GLOBAL_END
 * @brief end namespace ZFFramework
 * @def ZF_NAMESPACE_GLOBAL_USE
 * @brief use namespace ZFFramework
 */
#if !ZF_ENV_NAMESPACE_GLOBAL_DISABLE
    #define ZF_NAMESPACE_GLOBAL ZF_NAMESPACE_GLOBAL_ID
    #define ZF_NAMESPACE_GLOBAL_BEGIN ZF_NAMESPACE_BEGIN(ZF_NAMESPACE_GLOBAL)
    #define ZF_NAMESPACE_GLOBAL_END ZF_NAMESPACE_END(ZF_NAMESPACE_GLOBAL)
    #define ZF_NAMESPACE_GLOBAL_USE ZF_NAMESPACE_USE(ZF_NAMESPACE_GLOBAL)
#else
    #define ZF_NAMESPACE_GLOBAL
    #define ZF_NAMESPACE_GLOBAL_BEGIN
    #define ZF_NAMESPACE_GLOBAL_END
    #define ZF_NAMESPACE_GLOBAL_USE
#endif

ZF_NAMESPACE_GLOBAL_BEGIN
ZF_NAMESPACE_GLOBAL_END
ZF_NAMESPACE_GLOBAL_USE

#endif // #ifndef _ZFI_ZFNamespace_h_

