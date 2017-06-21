/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFCoreTypeDef_OtherType.h
 * @brief types for ZFFramework
 */

#ifndef _ZFI_ZFCoreTypeDef_OtherType_h_
#define _ZFI_ZFCoreTypeDef_OtherType_h_

#include "ZFCoreTypeDef_CoreType.h"
#include "ZFCoreTypeDef_CharType.h"
#include "ZFCoreTypeDef_StringType.h"
#include "ZFCoreTypeDef_ClassType.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/** @brief string tokens */
#define ZFTOKEN_zfchar_LOWERCASE zfText("0123456789abcdefghijklmnopqrstuvwxyz")
/** @brief string tokens */
#define ZFTOKEN_zfchar_UPPERCASE zfText("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ")

/** @brief string tokens */
#define ZFTOKEN_zfnull zfText("null")

/** @brief string tokens */
#define ZFTOKEN_zfbool_zftrue zfText("true")
/** @brief string tokens */
#define ZFTOKEN_zfbool_zffalse zfText("false")

// ============================================================
/**
 * @brief compare result of two ZFObjects
 * @see ZFObject::compare
 */
typedef enum
{
    ZFCompareUncomparable = -2, /**< can't be compared */
    ZFCompareSmaller = -1, /**< left < right */
    ZFCompareTheSame = 0, /**< left == right */
    ZFCompareGreater = 1, /**< left > right */
} ZFCompareResult;
/** @brief string tokens */
#define ZFTOKEN_ZFCompareUncomparable zfText("CompareUncomparable")
/** @brief string tokens */
#define ZFTOKEN_ZFCompareSmaller zfText("CompareSmaller")
/** @brief string tokens */
#define ZFTOKEN_ZFCompareTheSame zfText("CompareTheSame")
/** @brief string tokens */
#define ZFTOKEN_ZFCompareGreater zfText("CompareGreater")

// ============================================================
/**
 * @brief seek position similar to SEEK_SET of FILE operation
 */
typedef enum
{
    ZFSeekPosBegin,
    ZFSeekPosCur,
    ZFSeekPosCurReversely,
    ZFSeekPosEnd,
} ZFSeekPos;
/** @brief string tokens */
#define ZFTOKEN_ZFSeekPosBegin zfText("SeekBegin")
/** @brief string tokens */
#define ZFTOKEN_ZFSeekPosCur zfText("SeekCur")
/** @brief string tokens */
#define ZFTOKEN_ZFSeekPosCurReversely zfText("SeekCurReversely")
/** @brief string tokens */
#define ZFTOKEN_ZFSeekPosEnd zfText("SeekEnd")

// ============================================================
/**
 * @brief POD data to hold index range
 */
zfclassPOD ZF_ENV_EXPORT zfindexRange
{
public:
    zfindex start; /**< @brief start */
    zfindex count; /**< @brief count */
};
extern ZF_ENV_EXPORT const zfindexRange _ZFP_zfindexRangeZero;
extern ZF_ENV_EXPORT const zfindexRange _ZFP_zfindexRangeMax;
/**
 * @brief zero index range
 */
#define zfindexRangeZero() _ZFP_zfindexRangeZero
/**
 * @brief max index range (0, zfindexMax)
 */
#define zfindexRangeMax() _ZFP_zfindexRangeMax
/**
 * @brief make a zfindexRange
 */
inline zfindexRange zfindexRangeMake(ZF_IN zfindex start,
                                     ZF_IN zfindex count)
{
    zfindexRange ret = {start, count};
    return ret;
}
/**
 * @brief compare
 */
inline ZFCompareResult zfindexRangeIsEqual(ZF_IN const zfindexRange &e0,
                                           ZF_IN const zfindexRange &e1)
{
    return ((e0.start == e1.start && e0.count == e1.count) ? ZFCompareTheSame : ZFCompareUncomparable);
}
/**
 * @brief true if contain index in range
 */
inline zfbool zfindexRangeContain(ZF_IN const zfindexRange &range,
                                  ZF_IN zfindex index)
{
    return (range.count > 0 && index >= range.start && index < range.start + range.count);
}
/**
 * @brief compare
 */
inline zfbool operator == (ZF_IN const zfindexRange &v0,
                           ZF_IN const zfindexRange &v1)
{
    return (v0.start == v1.start && v0.count == v1.count);
}
/**
 * @brief compare
 */
inline zfbool operator != (ZF_IN const zfindexRange &v0,
                           ZF_IN const zfindexRange &v1)
{
    return (v0.start != v1.start || v0.count != v1.count);
}

// ============================================================
/**
 * @brief comparar for template types
 *
 * for common types (that support operation "==", "<", ">", such as pointers, built-in types)
 * you may use #ZFComparerDefault:
 * @code
 *   ZFComparerDefault<YourType>
 * @endcode
 * for custom types you may declare your own comparar:
 * @code
 *   ZFCompareResult YourCompareFunction(ZF_IN YourType const &e0, ZF_IN YourType const &e1)
 *   {
 *       // do your compare
 *   }
 * @endcode
 * and pass the comparar as:
 * @code
 *   YourCompareFunction
 * @endcode
 */
template<typename T_Comparable, typename T_Comparable2 = T_Comparable>
zfclassNotPOD ZFComparer
{
public:
    /**
     * @brief see #ZFComparer
     */
    typedef ZFCompareResult (*Comparer)(ZF_IN T_Comparable const &e0, ZF_IN T_Comparable2 const &e1);
};

// ============================================================
/**
 * @brief converter template typedef
 *
 * example:
 * @code
 *   static const zfint *MyConverter0(zfint const &v)
 *   {
 *       return &v;
 *   }
 *   static zfstring MyConverter1(const zfchar * const &v)
 *   {
 *       return zfstring(v);
 *   }
 *
 *   ZFTypeConverter<zfint, const zfint *>::TypeConverter converter0 = MyConverter0;
 *   zfint src0 = ...;
 *   const zfint *dst0 = ...;
 *   dst0 = converter0(src0);
 *
 *   ZFTypeConverter<const zfchar *, zfstring>::TypeConverter converter1 = MyConverter1;
 *   const zfchar *src1 = ...;
 *   zfstring dst0 = ...;
 *   dst1 = converter1(src1);
 * @endcode
 */
template<typename T_Src, typename T_Dst>
zfclassNotPOD ZFTypeConverter
{
public:
    /**
     * @brief see #ZFTypeConverter
     */
    typedef T_Dst (*TypeConverter)(ZF_IN T_Src const &);
};

/**
 * @brief dummy type converter that return the src itself
 */
template<typename T_Type>
T_Type ZFTypeConverterDummy(ZF_IN T_Type const &src)
{
    return src;
}

// ============================================================
/**
 * @brief base type for info getter
 */
template<typename T_Element>
zfclassNotPOD ZF_ENV_EXPORT ZFCoreInfoGetter
{
public:
    /** @brief see #ZFCoreInfoGetter */
    typedef void (*InfoGetter)(ZF_IN_OUT zfstring &ret, ZF_IN T_Element const &v);
};

/**
 * @brief string if the content info not available
 */
#define ZFTOKEN_ZFCoreInfoGetterNotAvailable zfText("N/A")

// ============================================================
/**
 * @brief dummy function address type
 */
typedef void (*ZFFuncAddrType)(void);

/**
 * @brief see #ZFMemberFuncAddrType
 */
zfclassNotPOD ZF_ENV_EXPORT ZFMemberFuncAddrTypeOwner {};
/**
 * @brief dummy member function address type
 */
typedef void (ZFMemberFuncAddrTypeOwner::*ZFMemberFuncAddrType)(void);

ZF_NAMESPACE_GLOBAL_END

#endif // #ifndef _ZFI_ZFCoreTypeDef_OtherType_h_

