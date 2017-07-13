/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFCoreUtilTemplate.h
 * @brief template utils
 */

#ifndef _ZFI_ZFCoreUtilTemplate_h_
#define _ZFI_ZFCoreUtilTemplate_h_

#include "ZFCoreTypeDef.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// zftValue
/**
 * @brief util wrapper class to hold a type
 */
template<typename T_Type>
zfclassLikePOD ZF_ENV_EXPORT zftValue
{
public:
    /** @brief the wrapped value */
    T_Type zfv;
public:
    /** @cond ZFPrivateDoc */
    zftValue(void) : zfv() {}
    zftValue(ZF_IN T_Type const &ref) : zfv(ref) {}
    zftValue(ZF_IN zftValue<T_Type> const &ref) : zfv(ref.zfv) {}
    template<typename T_Ref> zftValue(ZF_IN T_Ref const &ref) : zfv(ref) {}
    inline zftValue<T_Type> &operator = (ZF_IN T_Type const &ref) {zfv = ref; return *this;}
    inline zftValue<T_Type> &operator = (ZF_IN zftValue<T_Type> const &ref) {zfv = ref.zfv; return *this;}
    template<typename T_Ref> inline zftValue<T_Type> &operator =(ZF_IN T_Ref const &ref) {zfv = ref; return *this;}
    inline operator T_Type const &(void) const {return zfv;}
    inline operator T_Type &(void) {return zfv;}
    /** @endcond */
};

// ============================================================
// zftTraitsType
/**
 * @brief type traits similar to STL's traits
 *
 * @note this is a walkaround to reduce dependency of STL,
 *   no rvalue reference support
 */
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType
{
public:
    enum {
        /** @brief true if the type is pointer type */
        TypeIsPointer = 0,
        /** @brief true if the type is reference type */
        TypeIsReference = 0,
    };
    typedef T_Type                  TraitsType;             /**< @brief original type */
    typedef T_Type &                TraitsReference;        /**< @brief reference type */
    typedef T_Type const &          TraitsConstReference;   /**< @brief const reference type */
    typedef T_Type *                TraitsPointer;          /**< @brief pointer type */
    typedef const T_Type *          TraitsConstPointer;     /**< @brief const pointer type */
    typedef T_Type                  TraitsRemoveReference;  /**< @brief remove reference */
};
/** @cond ZFPrivateDoc */
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType<T_Type *>
{
public:
    enum {
        TypeIsPointer = 1,
        TypeIsReference = 0,
    };
    typedef T_Type                  TraitsType;
    typedef T_Type &                TraitsReference;
    typedef T_Type const &          TraitsConstReference;
    typedef T_Type *                TraitsPointer;
    typedef const T_Type *          TraitsConstPointer;
    typedef T_Type *                TraitsRemoveReference;
};
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType<const T_Type *>
{
public:
    enum {
        TypeIsPointer = 1,
        TypeIsReference = 0,
    };
    typedef T_Type                  TraitsType;
    typedef T_Type &                TraitsReference;
    typedef T_Type const &          TraitsConstReference;
    typedef T_Type *                TraitsPointer;
    typedef const T_Type *          TraitsConstPointer;
    typedef const T_Type *          TraitsRemoveReference;
};
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType<T_Type &>
{
public:
    enum {
        TypeIsPointer = 0,
        TypeIsReference = 1,
    };
    typedef T_Type                  TraitsType;
    typedef T_Type &                TraitsReference;
    typedef T_Type const &          TraitsConstReference;
    typedef T_Type *                TraitsPointer;
    typedef const T_Type *          TraitsConstPointer;
    typedef T_Type                  TraitsRemoveReference;
};
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType<T_Type const &>
{
public:
    enum {
        TypeIsPointer = 0,
        TypeIsReference = 1,
    };
    typedef T_Type                  TraitsType;
    typedef T_Type &                TraitsReference;
    typedef T_Type const &          TraitsConstReference;
    typedef T_Type *                TraitsPointer;
    typedef const T_Type *          TraitsConstPointer;
    typedef T_Type                  TraitsRemoveReference;
};
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType<T_Type * &>
{
public:
    enum {
        TypeIsPointer = 1,
        TypeIsReference = 1,
    };
    typedef T_Type                  TraitsType;
    typedef T_Type &                TraitsReference;
    typedef T_Type const &          TraitsConstReference;
    typedef T_Type *                TraitsPointer;
    typedef const T_Type *          TraitsConstPointer;
    typedef T_Type *                TraitsRemoveReference;
};
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType<T_Type * const &>
{
public:
    enum {
        TypeIsPointer = 1,
        TypeIsReference = 1,
    };
    typedef T_Type                  TraitsType;
    typedef T_Type &                TraitsReference;
    typedef T_Type const &          TraitsConstReference;
    typedef T_Type *                TraitsPointer;
    typedef const T_Type *          TraitsConstPointer;
    typedef T_Type *                TraitsRemoveReference;
};
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType<const T_Type * &>
{
public:
    enum {
        TypeIsPointer = 1,
        TypeIsReference = 1,
    };
    typedef T_Type                  TraitsType;
    typedef T_Type &                TraitsReference;
    typedef T_Type const &          TraitsConstReference;
    typedef T_Type *                TraitsPointer;
    typedef const T_Type *          TraitsConstPointer;
    typedef const T_Type *          TraitsRemoveReference;
};
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType<const T_Type * const &>
{
public:
    enum {
        TypeIsPointer = 1,
        TypeIsReference = 1,
    };
    typedef T_Type                  TraitsType;
    typedef T_Type &                TraitsReference;
    typedef T_Type const &          TraitsConstReference;
    typedef T_Type *                TraitsPointer;
    typedef const T_Type *          TraitsConstPointer;
    typedef const T_Type *          TraitsRemoveReference;
};
template<>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType<void>
{
public:
    enum {
        TypeIsPointer = 0,
        TypeIsReference = 0,
    };
    typedef void                    TraitsType;
    typedef void                    TraitsReference;
    typedef void                    TraitsConstReference;
    typedef void *                  TraitsPointer;
    typedef const void *            TraitsConstPointer;
    typedef void                    TraitsRemoveReference;
};
template<>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType<void *>
{
public:
    enum {
        TypeIsPointer = 1,
        TypeIsReference = 0,
    };
    typedef void                    TraitsType;
    typedef void                    TraitsReference;
    typedef void * const &          TraitsConstReference;
    typedef void *                  TraitsPointer;
    typedef const void *            TraitsConstPointer;
    typedef void *                  TraitsRemoveReference;
};
template<>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType<const void *>
{
public:
    enum {
        TypeIsPointer = 1,
        TypeIsReference = 0,
    };
    typedef void                    TraitsType;
    typedef void                    TraitsReference;
    typedef const void * const &    TraitsConstReference;
    typedef void *                  TraitsPointer;
    typedef const void *            TraitsConstPointer;
    typedef const void *            TraitsRemoveReference;
};
template<>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType<void * &>
{
public:
    enum {
        TypeIsPointer = 1,
        TypeIsReference = 1,
    };
    typedef void                    TraitsType;
    typedef void                    TraitsReference;
    typedef void * const &          TraitsConstReference;
    typedef void *                  TraitsPointer;
    typedef const void *            TraitsConstPointer;
    typedef void *                  TraitsRemoveReference;
};
template<>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType<void * const &>
{
public:
    enum {
        TypeIsPointer = 1,
        TypeIsReference = 1,
    };
    typedef void                    TraitsType;
    typedef void                    TraitsReference;
    typedef void * const &          TraitsConstReference;
    typedef void *                  TraitsPointer;
    typedef const void *            TraitsConstPointer;
    typedef void *                  TraitsRemoveReference;
};
template<>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType<const void * &>
{
public:
    enum {
        TypeIsPointer = 1,
        TypeIsReference = 1,
    };
    typedef void                    TraitsType;
    typedef void                    TraitsReference;
    typedef void * const &          TraitsConstReference;
    typedef void *                  TraitsPointer;
    typedef const void *            TraitsConstPointer;
    typedef const void *            TraitsRemoveReference;
};
template<>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsType<const void * const &>
{
public:
    enum {
        TypeIsPointer = 1,
        TypeIsReference = 1,
    };
    typedef void                    TraitsType;
    typedef void                    TraitsReference;
    typedef void * const &          TraitsConstReference;
    typedef void *                  TraitsPointer;
    typedef const void *            TraitsConstPointer;
    typedef const void *            TraitsRemoveReference;
};
/** @endcond */

// ============================================================
// zftTraitsTemplate
/**
 * @brief util template to traits the template's param
 *
 * usage:
 * @code
 *   // var0's type would be "vector<int>" 's first template param's type
 *   // int in this example
 *   zftTraitsTemplate<vector<int> >::TraitsParam0 var0;
 *
 *   // var1's type would be "map<int, float>" 's first template param's type
 *   // int in this example
 *   zftTraitsTemplate<map<int, float> >::TraitsParam0 var1;
 *
 *   // var2's type would be "map<int, float>" 's second template param's type
 *   // float in this example
 *   zftTraitsTemplate<map<int, float> >::TraitsParam1 var2;
 * @endcode
 * @note this is a walkaround to reduce dependency of STL,
 *   no rvalue reference support
 */
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsTemplate
{
};
/** @cond ZFPrivateDoc */
template<template<typename> class T_Template, typename T0>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsTemplate<T_Template<T0> >
{
public:
    typedef T0 TraitsParam0;
};
template<template<typename, typename> class T_Template, typename T0, typename T1>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsTemplate<T_Template<T0, T1> >
{
public:
    typedef T0 TraitsParam0;
    typedef T1 TraitsParam1;
};
template<template<typename, typename, typename> class T_Template, typename T0, typename T1, typename T2>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsTemplate<T_Template<T0, T1, T2> >
{
public:
    typedef T0 TraitsParam0;
    typedef T1 TraitsParam1;
    typedef T2 TraitsParam2;
};
template<template<typename, typename, typename, typename> class T_Template, typename T0, typename T1, typename T2, typename T3>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsTemplate<T_Template<T0, T1, T2, T3> >
{
public:
    typedef T0 TraitsParam0;
    typedef T1 TraitsParam1;
    typedef T2 TraitsParam2;
    typedef T3 TraitsParam3;
};
template<template<typename, typename, typename, typename, typename> class T_Template, typename T0, typename T1, typename T2, typename T3, typename T4>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsTemplate<T_Template<T0, T1, T2, T3, T4> >
{
public:
    typedef T0 TraitsParam0;
    typedef T1 TraitsParam1;
    typedef T2 TraitsParam2;
    typedef T3 TraitsParam3;
    typedef T3 TraitsParam4;
};
template<template<typename, typename, typename, typename, typename, typename> class T_Template, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsTemplate<T_Template<T0, T1, T2, T3, T4, T5> >
{
public:
    typedef T0 TraitsParam0;
    typedef T1 TraitsParam1;
    typedef T2 TraitsParam2;
    typedef T3 TraitsParam3;
    typedef T3 TraitsParam4;
    typedef T3 TraitsParam5;
};
template<template<typename, typename, typename, typename, typename, typename, typename> class T_Template, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsTemplate<T_Template<T0, T1, T2, T3, T4, T5, T6> >
{
public:
    typedef T0 TraitsParam0;
    typedef T1 TraitsParam1;
    typedef T2 TraitsParam2;
    typedef T3 TraitsParam3;
    typedef T3 TraitsParam4;
    typedef T3 TraitsParam5;
    typedef T3 TraitsParam6;
};
template<template<typename, typename, typename, typename, typename, typename, typename, typename> class T_Template, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
zfclassNotPOD ZF_ENV_EXPORT zftTraitsTemplate<T_Template<T0, T1, T2, T3, T4, T5, T6, T7> >
{
public:
    typedef T0 TraitsParam0;
    typedef T1 TraitsParam1;
    typedef T2 TraitsParam2;
    typedef T3 TraitsParam3;
    typedef T3 TraitsParam4;
    typedef T3 TraitsParam5;
    typedef T3 TraitsParam6;
    typedef T3 TraitsParam7;
};
/** @endcond */

// ============================================================
/** @brief std::enable_if wrapper */
template<bool cond = false>
zfclassNotPOD ZF_ENV_EXPORT zftEnableIf
{
};
/** @brief std::enable_if wrapper */
template<>
zfclassNotPOD ZF_ENV_EXPORT zftEnableIf<true>
{
public:
    /** @brief std::enable_if wrapper */
    typedef void EnableIf;
};

// ============================================================
/** @brief std::is_same wrapper */
template<typename T0, typename T1>
zfclassNotPOD ZF_ENV_EXPORT zftTypeIsSame
{
public:
    enum {
        /** @brief std::is_same wrapper */
        TypeIsSame = 0
    };
};
/** @brief std::is_same wrapper */
template<typename T>
zfclassNotPOD ZF_ENV_EXPORT zftTypeIsSame<T, T>
{
public:
    enum {
        /** @brief std::is_same wrapper */
        TypeIsSame = 1
    };
};

// ============================================================
/** @brief std::is_class wrapper */
template<typename T>
zfclassNotPOD ZF_ENV_EXPORT zftTypeIsClass
{
private:
    template<typename U>
    static char _test(int U::*);
    template<typename U>
    static int _test(...);
public:
    enum {
        /** @brief std::is_class wrapper */
        TypeIsClass = ((sizeof(_test<T>(0)) == sizeof(char)) ? 1 : 0)
    };
};

// ============================================================
/** @brief std::is_base_of wrapper */
template<typename TChild, typename TBase,
    bool _IsClass = (zftTypeIsClass<TChild>::TypeIsClass && zftTypeIsClass<TBase>::TypeIsClass)>
zfclassNotPOD ZF_ENV_EXPORT zftTypeIsTypeOf
{
private:
    template<typename T_Dummy>
    static char _test(TChild const &, T_Dummy);
    static int _test(TBase const &, int);
    zfclassNotPOD _Conv
    {
    public:
        operator TChild const & (void);
        operator TBase const & (void) const;
    };
public:
    enum {
        /** @brief std::is_base_of wrapper */
        TypeIsTypeOf = ((sizeof(_test(_Conv(), 0)) == sizeof(char)) ? 1 : 0)
    };
};
/** @brief std::is_base_of wrapper */
template<typename TChild, typename TBase>
zfclassNotPOD ZF_ENV_EXPORT zftTypeIsTypeOf<TChild, TBase, false>
{
public:
    enum {
        /** @brief std::is_base_of wrapper */
        TypeIsTypeOf = zftTypeIsSame<TChild, TBase>::TypeIsSame
    };
};
/** @brief std::is_base_of wrapper */
template<typename T>
zfclassNotPOD ZF_ENV_EXPORT zftTypeIsTypeOf<T, T, true>
{
public:
    enum {
        /** @brief std::is_base_of wrapper */
        TypeIsTypeOf = 1
    };
};

ZF_NAMESPACE_GLOBAL_END

#endif // #ifndef _ZFI_ZFCoreUtilTemplate_h_

