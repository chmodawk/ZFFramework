/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFObjectCast.h
 * @brief ZFCastZFObject declarations
 */

#ifndef _ZFI_ZFObjectCast_h_
#define _ZFI_ZFObjectCast_h_

#include "ZFObjectClassTypeFwd.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfclassFwd ZFClass;
zfclassFwd ZFObject;
zfclassFwd ZFInterface;

// ============================================================
/**
 * @brief safely cast ZFObject types, return null if not desired type
 *
 * types can only be ZFObject or ZFInterface types\n
 * \n
 * ADVANCED:\n
 * -  cast between ZFInterface or it's children types may take much time for dynamic checking,
 *   use with caution
 * -  try not to cast from and to the base ZFInterface * type
 */
#define ZFCastZFObject(T_To, obj) _ZFP_ZFCastZFObject<T_To>::_ZFP_cast(obj)

/**
 * @brief cast ZFObject types without safe check, use only for performance
 *
 * ADVANCED:\n
 * -  this method would have better performance while cast ZFObject types to ZFObject types,
 *   while cast ZFInterface types would always consume some CPU for dynamic check
 * -  try not to cast from and to the base ZFInterface * type
 */
#define ZFCastZFObjectUnchecked(T_To, obj) _ZFP_ZFCastZFObjectUnchecked<T_To>::_ZFP_cast(obj)

#define _ZFP_ZFCastZFObjectInternal(T_To, obj) \
    static_cast<T_To>(obj)


// ============================================================
// for impl
/** @cond ZFPrivateDoc */
template<typename T_ZFObjectTo, typename T_ZFObjectFrom>
inline T_ZFObjectTo _ZFP_ZFCastZFObjectExplicit(T_ZFObjectFrom const &obj)
{
    return ((obj->classData()->classIsSubclassOf(zftTraitsType<T_ZFObjectTo>::TraitsType::ClassData()))
        ? static_cast<T_ZFObjectTo>(obj)
        : zfnull);
}

template<typename T_Unknown>
inline ZFObject *_ZFP_ZFCastZFObjectFromUnknown(T_Unknown const &obj)
{
    return obj;
}
template<typename T_Unknown>
inline void _ZFP_ZFCastZFObjectToUnknown(T_Unknown &ret,
                                         ZFObject * const &obj)
{
    ret = obj;
}

template<typename T_Unknown>
inline ZFObject *_ZFP_ZFCastZFObjectFromUnknownUnchecked(T_Unknown const &obj)
{
    return obj;
}
template<typename T_Unknown>
inline void _ZFP_ZFCastZFObjectToUnknownUnchecked(T_Unknown &ret,
                                                  ZFObject * const &obj)
{
    ret = obj;
}
/** @endcond */



// ============================================================
#define _ZFP_ZFCastZFObjectTypeZFObject 1
#define _ZFP_ZFCastZFObjectTypeZFInterface 2
#define _ZFP_ZFCastZFObjectTypeUnknown 3

#define _ZFP_ZFCastZFObjectType(Type) \
    (ZFM_CLASS_HAS_MEMBER(_ZFP_ZFCastZFObject, ClassData, typename zftTraitsType<Type>::TraitsType) \
        ? (zftTypeIsTypeOf<typename zftTraitsType<Type>::TraitsType, ZFObject>::TypeIsTypeOf \
                ? _ZFP_ZFCastZFObjectTypeZFObject \
                : _ZFP_ZFCastZFObjectTypeZFInterface \
            ) \
        : _ZFP_ZFCastZFObjectTypeUnknown)

ZFM_CLASS_HAS_MEMBER_DECLARE(_ZFP_ZFCastZFObject, ClassData, const ZFClass * (*F)(void))



// ============================================================
// ZFCastZFObject
template<typename T_To>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObject
{
public:
    template<typename T_From>
    static inline T_To _ZFP_cast(T_From const &obj);
};
template<int T_CanCastDirectly, typename T_To, typename T_From, int T_ToType, int T_FromType>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectHolder
{
};

// can cast directly
template<typename T_To, typename T_From, int T_ToType, int T_FromType>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectHolder<1, T_To, T_From, T_ToType, T_FromType>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        return static_cast<T_To>(obj);
    }
};
// object to object
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeZFObject, _ZFP_ZFCastZFObjectTypeZFObject>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        return (obj
            ? _ZFP_ZFCastZFObjectExplicit<T_To>(obj)
            : zfnull);
    }
};
// object to interface
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeZFInterface, _ZFP_ZFCastZFObjectTypeZFObject>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        return (obj
            ? static_cast<T_To>(obj->classData()->_ZFP_ZFClass_interfaceCast(
                obj,
                zftTraitsType<T_To>::TraitsType::ClassData()))
            : zfnull);
    }
};
// object to unknown
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeUnknown, _ZFP_ZFCastZFObjectTypeZFObject>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        T_To ret;
        _ZFP_ZFCastZFObjectToUnknown(ret, obj);
        return ret;
    }
};
// interface to object
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeZFObject, _ZFP_ZFCastZFObjectTypeZFInterface>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        return (obj
            ? _ZFP_ZFCastZFObjectExplicit<T_To>(obj->toObject())
            : zfnull);
    }
};
// interface to interface
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeZFInterface, _ZFP_ZFCastZFObjectTypeZFInterface>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        return (obj
            ? static_cast<T_To>(obj->classData()->_ZFP_ZFClass_interfaceCast(
                obj->toObject(),
                zftTraitsType<T_To>::TraitsType::ClassData()))
            : zfnull);
    }
};
// interface to unknown
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeUnknown, _ZFP_ZFCastZFObjectTypeZFInterface>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        T_To ret;
        _ZFP_ZFCastZFObjectToUnknown(ret, obj ? obj->toObject() : zfnull);
        return ret;
    }
};
// unknown to object
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeZFObject, _ZFP_ZFCastZFObjectTypeUnknown>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        return ZFCastZFObject(T_To, _ZFP_ZFCastZFObjectFromUnknown(obj));
    }
};
// unknown to interface
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeZFInterface, _ZFP_ZFCastZFObjectTypeUnknown>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        return ZFCastZFObject(T_To, _ZFP_ZFCastZFObjectFromUnknown(obj));
    }
};
// unknown to unknown
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeUnknown, _ZFP_ZFCastZFObjectTypeUnknown>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        ZFObject *tmp = _ZFP_ZFCastZFObjectFromUnknown(obj);
        T_To ret;
        _ZFP_ZFCastZFObjectToUnknown(ret, tmp);
        return ret;
    }
};

// invoker
template<typename T_To>
template<typename T_From>
inline T_To _ZFP_ZFCastZFObject<T_To>::_ZFP_cast(T_From const &obj)
{
    return _ZFP_ZFCastZFObjectHolder<
            zftTypeIsTypeOf<typename zftTraitsType<T_From>::TraitsType, typename zftTraitsType<T_To>::TraitsType>::TypeIsTypeOf,
            T_To, T_From,
            _ZFP_ZFCastZFObjectType(T_To), _ZFP_ZFCastZFObjectType(T_From)
        >::_ZFP_cast(obj);
}
template<>
template<typename T_From>
inline ZFInterface *_ZFP_ZFCastZFObject<ZFInterface *>::_ZFP_cast(T_From const &obj)
{
    zfCoreCriticalMessageTrim(zfTextA("[ZFCastZFObjectUnchecked] direct cast to ZFInterface is not allowed"));
    return zfnull;
}


// ============================================================
// ZFCastZFObjectUnchecked
template<typename T_To>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectUnchecked
{
public:
    template<typename T_From>
    static inline T_To _ZFP_cast(T_From const &obj);
};
template<int T_CanCastDirectly, typename T_To, typename T_From, int T_ToType, int T_FromType>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectUncheckedHolder
{
};

// can cast directly
template<typename T_To, typename T_From, int T_ToType, int T_FromType>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectUncheckedHolder<1, T_To, T_From, T_ToType, T_FromType>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        return static_cast<T_To>(obj);
    }
};
// object to object
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectUncheckedHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeZFObject, _ZFP_ZFCastZFObjectTypeZFObject>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        return static_cast<T_To>(obj);
    }
};
// object to interface
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectUncheckedHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeZFInterface, _ZFP_ZFCastZFObjectTypeZFObject>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        return (obj
            ? static_cast<T_To>(obj->classData()->_ZFP_ZFClass_interfaceCast(
                obj,
                zftTraitsType<T_To>::TraitsType::ClassData()))
            : zfnull);
    }
};
// object to unknown
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectUncheckedHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeUnknown, _ZFP_ZFCastZFObjectTypeZFObject>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        T_To ret;
        _ZFP_ZFCastZFObjectToUnknownUnchecked(ret, obj);
        return ret;
    }
};
// interface to object
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectUncheckedHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeZFObject, _ZFP_ZFCastZFObjectTypeZFInterface>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        return (obj
            ? static_cast<T_To>(obj->toObject())
            : zfnull);
    }
};
// interface to interface
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectUncheckedHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeZFInterface, _ZFP_ZFCastZFObjectTypeZFInterface>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        return (obj
            ? static_cast<T_To>(obj->classData()->_ZFP_ZFClass_interfaceCast(
                obj->toObject(),
                zftTraitsType<T_To>::TraitsType::ClassData()))
            : zfnull);
    }
};
// interface to unknown
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectUncheckedHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeUnknown, _ZFP_ZFCastZFObjectTypeZFInterface>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        T_To ret;
        _ZFP_ZFCastZFObjectToUnknownUnchecked(ret, obj ? obj->toObject() : zfnull);
        return ret;
    }
};
// unknown to object
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectUncheckedHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeZFObject, _ZFP_ZFCastZFObjectTypeUnknown>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        return ZFCastZFObjectUnchecked(T_To, _ZFP_ZFCastZFObjectFromUnknownUnchecked(obj));
    }
};
// unknown to interface
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectUncheckedHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeZFInterface, _ZFP_ZFCastZFObjectTypeUnknown>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        return ZFCastZFObjectUnchecked(T_To, _ZFP_ZFCastZFObjectFromUnknownUnchecked(obj));
    }
};
// unknown to unknown
template<typename T_To, typename T_From>
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCastZFObjectUncheckedHolder<0, T_To, T_From, _ZFP_ZFCastZFObjectTypeUnknown, _ZFP_ZFCastZFObjectTypeUnknown>
{
public:
    static inline T_To _ZFP_cast(T_From const &obj)
    {
        ZFObject *tmp = _ZFP_ZFCastZFObjectFromUnknownUnchecked(obj);
        T_To ret;
        _ZFP_ZFCastZFObjectToUnknownUnchecked(ret, tmp);
        return ret;
    }
};

// invoker
template<typename T_To>
template<typename T_From>
inline T_To _ZFP_ZFCastZFObjectUnchecked<T_To>::_ZFP_cast(T_From const &obj)
{
    return _ZFP_ZFCastZFObjectUncheckedHolder<
            zftTypeIsTypeOf<typename zftTraitsType<T_From>::TraitsType, typename zftTraitsType<T_To>::TraitsType>::TypeIsTypeOf,
            T_To, T_From,
            _ZFP_ZFCastZFObjectType(T_To), _ZFP_ZFCastZFObjectType(T_From)
        >::_ZFP_cast(obj);
}
template<>
template<typename T_From>
inline ZFInterface *_ZFP_ZFCastZFObjectUnchecked<ZFInterface *>::_ZFP_cast(T_From const &obj)
{
    zfCoreCriticalMessageTrim(zfTextA("[ZFCastZFObjectUnchecked] direct cast to ZFInterface is not allowed"));
    return zfnull;
}

ZF_NAMESPACE_GLOBAL_END

#endif // #ifndef _ZFI_ZFObjectCast_h_

