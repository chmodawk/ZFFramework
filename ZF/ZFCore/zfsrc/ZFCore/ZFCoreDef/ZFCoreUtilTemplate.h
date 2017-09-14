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
// zftTraits
/**
 * @brief type traits similar to STL's traits
 *
 * @note this is a walkaround to reduce dependency of STL,
 *   no rvalue reference support
 */
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraits
{
public:
    enum {
        TrIsPtr = 0, /** @brief true if the type is pointer type */
        TrIsRef = 0, /** @brief true if the type is reference type */
    };
    typedef T_Type                  TrType;         /**< @brief original type */
    typedef T_Type &                TrRef;          /**< @brief reference type */
    typedef T_Type const &          TrConstRef;     /**< @brief const reference type */
    typedef T_Type *                TrPtr;          /**< @brief pointer type */
    typedef const T_Type *          TrConstPtr;     /**< @brief const pointer type */
    typedef T_Type                  TrNoRef;        /**< @brief remove reference */
};
/** @cond ZFPrivateDoc */
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraits<T_Type *>
{
public:
    enum {
        TrIsPtr = 1,
        TrIsRef = 0,
    };
    typedef T_Type                  TrType;
    typedef T_Type &                TrRef;
    typedef T_Type const &          TrConstRef;
    typedef T_Type *                TrPtr;
    typedef const T_Type *          TrConstPtr;
    typedef T_Type *                TrNoRef;
};
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraits<const T_Type *>
{
public:
    enum {
        TrIsPtr = 1,
        TrIsRef = 0,
    };
    typedef T_Type                  TrType;
    typedef T_Type &                TrRef;
    typedef T_Type const &          TrConstRef;
    typedef T_Type *                TrPtr;
    typedef const T_Type *          TrConstPtr;
    typedef const T_Type *          TrNoRef;
};
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraits<T_Type &>
{
public:
    enum {
        TrIsPtr = 0,
        TrIsRef = 1,
    };
    typedef T_Type                  TrType;
    typedef T_Type &                TrRef;
    typedef T_Type const &          TrConstRef;
    typedef T_Type *                TrPtr;
    typedef const T_Type *          TrConstPtr;
    typedef T_Type                  TrNoRef;
};
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraits<T_Type const &>
{
public:
    enum {
        TrIsPtr = 0,
        TrIsRef = 1,
    };
    typedef T_Type                  TrType;
    typedef T_Type &                TrRef;
    typedef T_Type const &          TrConstRef;
    typedef T_Type *                TrPtr;
    typedef const T_Type *          TrConstPtr;
    typedef T_Type                  TrNoRef;
};
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraits<T_Type * &>
{
public:
    enum {
        TrIsPtr = 1,
        TrIsRef = 1,
    };
    typedef T_Type                  TrType;
    typedef T_Type &                TrRef;
    typedef T_Type const &          TrConstRef;
    typedef T_Type *                TrPtr;
    typedef const T_Type *          TrConstPtr;
    typedef T_Type *                TrNoRef;
};
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraits<T_Type * const &>
{
public:
    enum {
        TrIsPtr = 1,
        TrIsRef = 1,
    };
    typedef T_Type                  TrType;
    typedef T_Type &                TrRef;
    typedef T_Type const &          TrConstRef;
    typedef T_Type *                TrPtr;
    typedef const T_Type *          TrConstPtr;
    typedef T_Type *                TrNoRef;
};
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraits<const T_Type * &>
{
public:
    enum {
        TrIsPtr = 1,
        TrIsRef = 1,
    };
    typedef T_Type                  TrType;
    typedef T_Type &                TrRef;
    typedef T_Type const &          TrConstRef;
    typedef T_Type *                TrPtr;
    typedef const T_Type *          TrConstPtr;
    typedef const T_Type *          TrNoRef;
};
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT zftTraits<const T_Type * const &>
{
public:
    enum {
        TrIsPtr = 1,
        TrIsRef = 1,
    };
    typedef T_Type                  TrType;
    typedef T_Type &                TrRef;
    typedef T_Type const &          TrConstRef;
    typedef T_Type *                TrPtr;
    typedef const T_Type *          TrConstPtr;
    typedef const T_Type *          TrNoRef;
};
template<>
zfclassNotPOD ZF_ENV_EXPORT zftTraits<void>
{
public:
    enum {
        TrIsPtr = 0,
        TrIsRef = 0,
    };
    typedef void                    TrType;
    typedef void                    TrRef;
    typedef void                    TrConstRef;
    typedef void *                  TrPtr;
    typedef const void *            TrConstPtr;
    typedef void                    TrNoRef;
};
template<>
zfclassNotPOD ZF_ENV_EXPORT zftTraits<void *>
{
public:
    enum {
        TrIsPtr = 1,
        TrIsRef = 0,
    };
    typedef void                    TrType;
    typedef void                    TrRef;
    typedef void * const &          TrConstRef;
    typedef void *                  TrPtr;
    typedef const void *            TrConstPtr;
    typedef void *                  TrNoRef;
};
template<>
zfclassNotPOD ZF_ENV_EXPORT zftTraits<const void *>
{
public:
    enum {
        TrIsPtr = 1,
        TrIsRef = 0,
    };
    typedef void                    TrType;
    typedef void                    TrRef;
    typedef const void * const &    TrConstRef;
    typedef void *                  TrPtr;
    typedef const void *            TrConstPtr;
    typedef const void *            TrNoRef;
};
template<>
zfclassNotPOD ZF_ENV_EXPORT zftTraits<void * &>
{
public:
    enum {
        TrIsPtr = 1,
        TrIsRef = 1,
    };
    typedef void                    TrType;
    typedef void                    TrRef;
    typedef void * const &          TrConstRef;
    typedef void *                  TrPtr;
    typedef const void *            TrConstPtr;
    typedef void *                  TrNoRef;
};
template<>
zfclassNotPOD ZF_ENV_EXPORT zftTraits<void * const &>
{
public:
    enum {
        TrIsPtr = 1,
        TrIsRef = 1,
    };
    typedef void                    TrType;
    typedef void                    TrRef;
    typedef void * const &          TrConstRef;
    typedef void *                  TrPtr;
    typedef const void *            TrConstPtr;
    typedef void *                  TrNoRef;
};
template<>
zfclassNotPOD ZF_ENV_EXPORT zftTraits<const void * &>
{
public:
    enum {
        TrIsPtr = 1,
        TrIsRef = 1,
    };
    typedef void                    TrType;
    typedef void                    TrRef;
    typedef void * const &          TrConstRef;
    typedef void *                  TrPtr;
    typedef const void *            TrConstPtr;
    typedef const void *            TrNoRef;
};
template<>
zfclassNotPOD ZF_ENV_EXPORT zftTraits<const void * const &>
{
public:
    enum {
        TrIsPtr = 1,
        TrIsRef = 1,
    };
    typedef void                    TrType;
    typedef void                    TrRef;
    typedef void * const &          TrConstRef;
    typedef void *                  TrPtr;
    typedef const void *            TrConstPtr;
    typedef const void *            TrNoRef;
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

