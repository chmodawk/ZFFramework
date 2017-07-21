/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFPropertyTypeFwd.h
 * @brief type define for ZFProperty
 */

#ifndef _ZFI_ZFPropertyTypeFwd_h_
#define _ZFI_ZFPropertyTypeFwd_h_

#include "ZFPropertyFwd.h"
#include "zfautoObjectFwd.h"
#include "ZFAny.h"
ZF_NAMESPACE_GLOBAL_BEGIN

zfclassFwd ZFSerializableData;
/**
 * @brief base protocol for #ZFPropertyTypeIdData
 */
zfclassNotPOD ZF_ENV_EXPORT ZFPropertyTypeIdDataBase
{
public:
    virtual ~ZFPropertyTypeIdDataBase(void) {}

public:
    /**
     * @brief see #ZFPropertyTypeIdData::PropertyAccessable
     */
    virtual zfbool propertyAccessable(void) const zfpurevirtual;
    /**
     * @brief see #ZFPropertyTypeIdData::PropertySerializable
     */
    virtual zfbool propertySerializable(void) const zfpurevirtual;
    /**
     * @brief the property type id
     */
    virtual const zfchar *propertyTypeId(void) const zfpurevirtual;
    /**
     * @brief return the proper wrapper type if available
     */
    virtual void propertyWrapper(ZF_OUT zfautoObject &v) const
    {
    }
    /**
     * @brief convert from serializable data
     */
    virtual zfbool propertyWrapperFromSerializableData(ZF_OUT zfautoObject &v,
                                                       ZF_IN const ZFSerializableData &serializableData,
                                                       ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                       ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull) const;
    /**
     * @brief convert to serializable data
     */
    virtual zfbool propertyWrapperToSerializableData(ZF_OUT ZFSerializableData &serializableData,
                                                     ZF_IN ZFObject *v,
                                                     ZF_OUT_OPT zfstring *outErrorHint = zfnull) const;
    /**
     * @brief convert from string, return error pos or empty string if fail
     */
    virtual zfbool propertyWrapperFromString(ZF_OUT zfautoObject &v,
                                             ZF_IN const zfchar *src,
                                             ZF_IN_OPT zfindex srcLen = zfindexMax) const;
    /**
     * @brief convert to string
     */
    virtual zfbool propertyWrapperToString(ZF_IN_OUT zfstring &s,
                                           ZF_IN ZFObject *v) const;
};
#define _ZFP_ZFPROPERTY_TYPE_ID_DATA_BASE_EXPAND(T_Type) \
    public: \
        zfoverride \
        virtual zfbool propertyAccessable(void) const \
        { \
            return PropertyAccessable; \
        } \
        zfoverride \
        virtual zfbool propertySerializable(void) const \
        { \
            return PropertySerializable; \
        } \
        zfoverride \
        virtual const zfchar *propertyTypeId(void) const \
        { \
            return PropertyTypeId(); \
        }

// ============================================================
extern ZF_ENV_EXPORT void _ZFP_ZFPropertyTypeIdDataRegister(ZF_IN const zfchar *propertyTypeId,
                                                            ZF_IN ZFPropertyTypeIdDataBase *propertyTypeIdData);
extern ZF_ENV_EXPORT void _ZFP_ZFPropertyTypeIdDataUnregister(ZF_IN const zfchar *propertyTypeId);
/**
 * @brief access property type id data
 */
extern ZF_ENV_EXPORT const ZFPropertyTypeIdDataBase *ZFPropertyTypeIdDataGet(ZF_IN const zfchar *propertyTypeId);
/**
 * @brief access property type id data
 */
extern ZF_ENV_EXPORT void ZFPropertyTypeIdDataGetAllT(ZF_OUT ZFCoreArray<const ZFPropertyTypeIdDataBase *> &ret);
/**
 * @brief access property type id data
 */
inline ZFCoreArrayPOD<const ZFPropertyTypeIdDataBase *> ZFPropertyTypeIdDataGetAll(void)
{
    ZFCoreArrayPOD<const ZFPropertyTypeIdDataBase *> ret;
    ZFPropertyTypeIdDataGetAllT(ret);
    return ret;
}

// ============================================================
template<typename T_Dummy>
zfclassNotPOD _ZFP_ZFPropertyTypeChecker
{
};
/**
 * @brief type data traits for #ZFPROPERTY_TYPE_DECLARE
 *
 * for advanced reflection use only\n
 * type must be registered by #ZFPROPERTY_TYPE_DECLARE before use this template,
 * and T_Type must be plain type without reference,
 * use #zftTraitsType::TraitsRemoveReference if necessary
 */
template<typename T_Type, typename T_ZFObjectFix = void, typename T_PointerFix = void>
zfclassNotPOD ZFPropertyTypeIdData : zfextendsNotPOD ZFPropertyTypeIdDataBase
{
public:
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_BASE_EXPAND(T_Type)
    /** @cond ZFPrivateDoc */
    typedef typename _ZFP_ZFPropertyTypeChecker<T_Type>::AllTypeMustBeRegisteredBy_ZFPROPERTY_TYPE_XXX _TypeChecker;
    /** @endcond */
public:
    enum {
        /**
         * @brief whether this type already registered
         *
         * property is registered if declared by any of these:
         * -  #ZFPROPERTY_TYPE_DECLARE
         * -  #ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE
         * -  #ZFPROPERTY_TYPE_ALIAS_DECLARE
         * -  #ZFPROPERTY_TYPE_DISABLE
         */
        PropertyRegistered = 0,
        /**
         * @brief whether this type can be accessed
         *
         * property is accessable if declared by any of these:
         * -  #ZFPROPERTY_TYPE_DECLARE
         * -  #ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE
         * -  #ZFPROPERTY_TYPE_ALIAS_DECLARE
         */
        PropertyAccessable = 0,
        /**
         * @brief whether this type can be serialized
         *
         * property is serializable if declared by any of these:
         * -  #ZFPROPERTY_TYPE_DECLARE
         * -  #ZFPROPERTY_TYPE_ALIAS_DECLARE
         */
        PropertySerializable = 0,
    };

    /**
     * @brief get property type id, or return #ZFPropertyTypeId_none if not registered
     */
    static const zfchar *PropertyTypeId(void);

    /**
     * @brief convert from serializable data
     */
    static zfbool PropertyFromSerializableData(ZF_OUT T_Type &v,
                                               ZF_IN const ZFSerializableData &serializableData,
                                               ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                               ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull);
    /**
     * @brief convert to serializable data
     */
    static zfbool PropertyToSerializableData(ZF_OUT ZFSerializableData &serializableData,
                                             ZF_IN T_Type const &v,
                                             ZF_OUT_OPT zfstring *outErrorHint = zfnull);
    /**
     * @brief convert from string, return error pos or empty string if fail
     */
    static zfbool PropertyFromString(ZF_OUT T_Type &v, ZF_IN const zfchar *src, ZF_IN_OPT zfindex srcLen = zfindexMax);
    /**
     * @brief convert to string
     */
    static zfbool PropertyToString(ZF_IN_OUT zfstring &s, ZF_IN T_Type const &v);

    /**
     * @brief store the value to wrapper object
     *
     * the stored value can be further accessed by #ZFPropertyTypeIdData::Value
     */
    static zfbool ValueStore(ZF_OUT zfautoObject &obj, ZF_IN T_Type const &v);

    /**
     * @brief try access as raw value
     *
     * this method used to convert types from/to ZFObject without knowing its actual type,
     * currently used by #ZFMethod::methodGenericInvoker\n
     * \n
     * types must be registered by #ZFPROPERTY_TYPE_DECLARE or #ZFPROPERTY_TYPE_ALIAS_DECLARE,
     * which would automatically declare a wrapper object type for you\n
     * assume your type's name is "YourType",
     * then there would be a wrapper class named "v_YourType",
     * with only one plain member variable named "zfv":
     * @code
     *   zfclass v_YourType : zfextends ZFPropertyTypeWrapper
     *   {
     *       ZFOBJECT_DECLARE(v_YourType, ZFPropertyTypeWrapper)
     *   public:
     *       YourType zfv;
     *   };
     * @endcode
     * \n
     * this method may or may not access the original value\n
     * must first check whether it's available to access
     * by #ZFPropertyTypeIdData::Value::accessAvailable\n
     */
    template<typename T_Access = T_Type, int T_IsPointer = 0, typename T_Fix = void>
    zfclassNotPOD Value
    {
    public:
        /** @brief try access as raw value, see #ZFPropertyTypeIdData::Value */
        static zfbool accessAvailable(ZF_IN ZFObject *obj);
        /** @brief try access as raw value, see #ZFPropertyTypeIdData::Value */
        static typename zftTraitsType<T_Access>::TraitsRemoveReference access(ZF_IN ZFObject *obj);
    };
    /*
     * if available, the templates above should handle these types,
     * and access as proper type:
     * -  Type
     * -  Type const &
     * -  Type *
     * -  const Type *
     * -  Type &
     * -  Type * &
     * -  Type * const &
     * -  const Type * &
     * -  const Type * const &
     *
     * for aliased type, only `Type` and `Type const &` available
     */
};

// ============================================================
#define _ZFP_ZFPROPERTY_TYPE_ID_DATA_DECLARE(TypeName, Type) \
    typedef Type _ZFP_ZFPropertyTypeWrapper_##TypeName; \
    /** @brief type wrapper for #ZFPropertyTypeIdData::Value */ \
    zfclass ZF_ENV_EXPORT v_##TypeName : zfextends ZFPropertyTypeWrapper \
    { \
        ZFOBJECT_DECLARE_ALLOW_CUSTOM_CONSTRUCTOR(v_##TypeName, ZFPropertyTypeWrapper) \
    public: \
        /** @brief the value, see #ZFPropertyTypeIdData::Value */ \
        _ZFP_ZFPropertyTypeWrapper_##TypeName zfv; \
    protected: \
        v_##TypeName(void) : zfv() {} \
    public: \
        zfoverride \
        virtual ZFObject *objectOnInit(void) {return zfsuper::objectOnInit();} \
        /** @brief init with value */ \
        virtual ZFObject *objectOnInit(ZF_IN _ZFP_ZFPropertyTypeWrapper_##TypeName const &value) \
        { \
            this->objectOnInit(); \
            this->zfv = value; \
            return this; \
        } \
        zfoverride \
        virtual inline void objectInfoOnAppendTokenLeft(ZF_IN_OUT zfstring &ret) {} \
        zfoverride \
        virtual inline void objectInfoOnAppendTokenRight(ZF_IN_OUT zfstring &ret) {} \
        zfoverride \
        virtual void objectInfoOnAppend(ZF_IN_OUT zfstring &ret); \
        zfoverride \
        virtual ZFCompareResult objectCompare(ZF_IN ZFObject *anotherObj); \
    public: \
        zfoverride \
        virtual const zfchar *wrappedValuePropertyTypeId(void); \
        zfoverride \
        virtual void *wrappedValue(void) {return &(this->zfv);} \
        zfoverride \
        virtual void wrappedValueSet(ZF_IN const void *v) {this->zfv = *(const _ZFP_ZFPropertyTypeWrapper_##TypeName *)v;} \
    public: \
        zfoverride \
        virtual void wrappedValueReset(void) \
        {this->zfv = zftValue<_ZFP_ZFPropertyTypeWrapper_##TypeName>().zfv;} \
        zfoverride \
        virtual zfbool wrappedValueIsInit(void); \
        zfoverride \
        virtual ZFCompareResult wrappedValueCompare(ZF_IN const void *v); \
    public: \
        zfoverride \
        virtual zfbool wrappedValueFromSerializableData(ZF_IN const ZFSerializableData &serializableData, \
                                                        ZF_OUT_OPT zfstring *outErrorHint = zfnull, \
                                                        ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull) \
        {return TypeName##FromSerializableData(this->zfv, serializableData, outErrorHint, outErrorPos);} \
        zfoverride \
        virtual zfbool wrappedValueToSerializableData(ZF_OUT ZFSerializableData &serializableData, \
                                                      ZF_OUT_OPT zfstring *outErrorHint = zfnull) \
        {return TypeName##ToSerializableData(serializableData, this->zfv, outErrorHint);} \
        zfoverride \
        virtual zfbool wrappedValueFromString(ZF_IN const zfchar *src, \
                                              ZF_IN_OPT zfindex srcLen = zfindexMax) \
        {return TypeName##FromString(this->zfv, src, srcLen);} \
        zfoverride \
        virtual zfbool wrappedValueToString(ZF_IN_OUT zfstring &s) \
        {return TypeName##ToString(s, this->zfv);} \
    }; \
    /** @cond ZFPrivateDoc */ \
    template<> \
    zfclassNotPOD ZFPropertyTypeIdData<_ZFP_ZFPropertyTypeWrapper_##TypeName> : zfextendsNotPOD ZFPropertyTypeIdDataBase \
    { \
        _ZFP_ZFPROPERTY_TYPE_ID_DATA_BASE_EXPAND(_ZFP_ZFPropertyTypeWrapper_##TypeName) \
    public: \
        enum { \
            PropertyRegistered = 1, \
            PropertyAccessable = 1, \
            PropertySerializable = 1, \
        }; \
        static inline const zfchar *PropertyTypeId(void) \
        { \
            return ZFPropertyTypeId_##TypeName(); \
        } \
        zfoverride \
        virtual void propertyWrapper(ZF_OUT zfautoObject &v) const \
        { \
            v_##TypeName *t = zfAllocWithoutLeakTest(v_##TypeName); \
            v = zfautoObjectCreateWithoutLeakTest(t); \
            zfReleaseWithoutLeakTest(t); \
        } \
        static zfbool PropertyFromSerializableData(ZF_OUT _ZFP_ZFPropertyTypeWrapper_##TypeName &v, \
                                                   ZF_IN const ZFSerializableData &serializableData, \
                                                   ZF_OUT_OPT zfstring *outErrorHint = zfnull, \
                                                   ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull) \
        { \
            return TypeName##FromSerializableData(v, serializableData, outErrorHint, outErrorPos); \
        } \
        static zfbool PropertyToSerializableData(ZF_OUT ZFSerializableData &serializableData, \
                                                 ZF_IN _ZFP_ZFPropertyTypeWrapper_##TypeName const &v, \
                                                 ZF_OUT_OPT zfstring *outErrorHint = zfnull) \
        { \
            return TypeName##ToSerializableData(serializableData, v, outErrorHint); \
        } \
        static zfbool PropertyFromString(ZF_OUT _ZFP_ZFPropertyTypeWrapper_##TypeName &v, ZF_IN const zfchar *src, ZF_IN_OPT zfindex srcLen = zfindexMax) \
        { \
            return TypeName##FromString(v, src, srcLen); \
        } \
        static zfbool PropertyToString(ZF_IN_OUT zfstring &s, ZF_IN _ZFP_ZFPropertyTypeWrapper_##TypeName const &v) \
        { \
            return TypeName##ToString(s, v); \
        } \
        static zfbool ValueStore(ZF_OUT zfautoObject &obj, ZF_IN _ZFP_ZFPropertyTypeWrapper_##TypeName const &v) \
        { \
            v_##TypeName *t = zfAllocWithoutLeakTest(v_##TypeName, v); \
            obj = zfautoObjectCreateWithoutLeakTest(t); \
            zfReleaseWithoutLeakTest(t); \
            return zftrue; \
        } \
        template<typename T_Access = _ZFP_ZFPropertyTypeWrapper_##TypeName \
            , int T_IsPointer = ((zftTraitsType<T_Access>::TypeIsPointer \
                && zftTypeIsSame< \
                        typename zftTraitsType<T_Access>::TraitsRemoveReference, \
                        _ZFP_ZFPropertyTypeWrapper_##TypeName \
                    >::TypeIsSame != 1) \
                ? 1 : 0) \
            , typename T_Fix = void \
            > \
        zfclassNotPOD Value \
        { \
        public: \
            static zfbool accessAvailable(ZF_IN ZFObject *obj) \
            { \
                return (ZFCastZFObject(v_##TypeName *, obj) != zfnull); \
            } \
            static T_Access access(ZF_IN ZFObject *obj) \
            { \
                return ZFCastZFObject(v_##TypeName *, obj)->zfv; \
            } \
        }; \
        template<typename T_Access> \
        zfclassNotPOD Value<T_Access, 1> \
        { \
        public: \
            static zfbool accessAvailable(ZF_IN ZFObject *obj) \
            { \
                return (ZFCastZFObject(v_##TypeName *, obj) != zfnull); \
            } \
            static typename zftTraitsType<T_Access>::TraitsRemoveReference access(ZF_IN ZFObject *obj) \
            { \
                return &(ZFCastZFObject(v_##TypeName *, obj)->zfv); \
            } \
        }; \
    }; \
    /** @endcond */

#define _ZFP_ZFPROPERTY_TYPE_ID_DATA_DEFINE(TypeName, Type, convertFromStringAction, convertToStringAction) \
    ZFOBJECT_REGISTER(v_##TypeName) \
    void v_##TypeName::objectInfoOnAppend(ZF_IN_OUT zfstring &ret) \
    { \
        ZFCoreElementInfoGetter<Type>::elementInfoGetter(ret, this->zfv); \
    } \
    ZFCompareResult v_##TypeName::objectCompare(ZF_IN ZFObject *anotherObj) \
    { \
        ZFPropertyTypeWrapper *t = ZFCastZFObject(ZFPropertyTypeWrapper *, anotherObj); \
        if(t == zfnull || !zfscmpTheSame(this->wrappedValuePropertyTypeId(), t->wrappedValuePropertyTypeId())) \
        { \
            return ZFCompareUncomparable; \
        } \
        else \
        { \
            return ZFComparerCheckEqual(this->zfv, *(_ZFP_ZFPropertyTypeWrapper_##TypeName *)t->wrappedValue()); \
        } \
    } \
    const zfchar *v_##TypeName::wrappedValuePropertyTypeId(void) \
    { \
        return ZFPropertyTypeIdData<_ZFP_ZFPropertyTypeWrapper_##TypeName>::PropertyTypeId(); \
    } \
    zfbool v_##TypeName::wrappedValueIsInit(void) \
    { \
        return (ZFComparerCheckEqual(this->zfv, zftValue<_ZFP_ZFPropertyTypeWrapper_##TypeName>().zfv) == ZFCompareTheSame); \
    } \
    ZFCompareResult v_##TypeName::wrappedValueCompare(ZF_IN const void *v) \
    { \
        return ZFComparerCheckEqual(this->zfv, *(const _ZFP_ZFPropertyTypeWrapper_##TypeName *)v); \
    } \
    ZF_STATIC_REGISTER_INIT(PropTIReg_##TypeName) \
    { \
        _ZFP_ZFPropertyTypeIdDataRegister(ZFPropertyTypeId_##TypeName(), \
            zfnew(ZFPropertyTypeIdData<_ZFP_ZFPropertyTypeWrapper_##TypeName>)); \
    } \
    ZF_STATIC_REGISTER_DESTROY(PropTIReg_##TypeName) \
    { \
        _ZFP_ZFPropertyTypeIdDataUnregister(ZFPropertyTypeId_##TypeName()); \
    } \
    ZF_STATIC_REGISTER_END(PropTIReg_##TypeName)

// ============================================================
#define _ZFP_ZFPROPERTY_TYPE_ID_DATA_ACCESS_ONLY_DECLARE(TypeName, Type) \
    typedef Type _ZFP_ZFPropertyTypeWrapper_##TypeName; \
    /** @brief type wrapper for #ZFPropertyTypeIdData::Value */ \
    zfclass ZF_ENV_EXPORT v_##TypeName : zfextends ZFPropertyTypeWrapper \
    { \
        ZFOBJECT_DECLARE_ALLOW_CUSTOM_CONSTRUCTOR(v_##TypeName, ZFPropertyTypeWrapper) \
    public: \
        /** @brief the value, see #ZFPropertyTypeIdData::Value */ \
        _ZFP_ZFPropertyTypeWrapper_##TypeName zfv; \
    protected: \
        v_##TypeName(void) : zfv() {} \
    public: \
        zfoverride \
        virtual ZFObject *objectOnInit(void) {return zfsuper::objectOnInit();} \
        /** @brief init with value */ \
        virtual ZFObject *objectOnInit(ZF_IN _ZFP_ZFPropertyTypeWrapper_##TypeName const &value) \
        { \
            this->objectOnInit(); \
            this->zfv = value; \
            return this; \
        } \
        zfoverride \
        virtual inline void objectInfoOnAppendTokenLeft(ZF_IN_OUT zfstring &ret) {} \
        zfoverride \
        virtual inline void objectInfoOnAppendTokenRight(ZF_IN_OUT zfstring &ret) {} \
        zfoverride \
        virtual void objectInfoOnAppend(ZF_IN_OUT zfstring &ret); \
        zfoverride \
        virtual ZFCompareResult objectCompare(ZF_IN ZFObject *anotherObj); \
    public: \
        zfoverride \
        virtual const zfchar *wrappedValuePropertyTypeId(void); \
        zfoverride \
        virtual void *wrappedValue(void) {return &(this->zfv);} \
        zfoverride \
        virtual void wrappedValueSet(ZF_IN const void *v) {this->zfv = *(const _ZFP_ZFPropertyTypeWrapper_##TypeName *)v;} \
    public: \
        zfoverride \
        virtual void wrappedValueReset(void) \
        {this->zfv = zftValue<_ZFP_ZFPropertyTypeWrapper_##TypeName>().zfv;} \
        zfoverride \
        virtual zfbool wrappedValueIsInit(void); \
        zfoverride \
        virtual ZFCompareResult wrappedValueCompare(ZF_IN const void *v); \
    public: \
        zfoverride \
        virtual zfbool wrappedValueFromSerializableData(ZF_IN const ZFSerializableData &serializableData, \
                                                        ZF_OUT_OPT zfstring *outErrorHint = zfnull, \
                                                        ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull) \
        { \
            ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData, \
                zfText("registered type %s is not serializable"), zfText(#TypeName)); \
            return zffalse; \
        } \
        zfoverride \
        virtual zfbool wrappedValueToSerializableData(ZF_OUT ZFSerializableData &serializableData, \
                                                      ZF_OUT_OPT zfstring *outErrorHint = zfnull) \
        { \
            ZFSerializableUtil::errorOccurred(outErrorHint, \
                zfText("registered type %s is not serializable"), zfText(#TypeName)); \
            return zffalse; \
        } \
        zfoverride \
        virtual zfbool wrappedValueFromString(ZF_IN const zfchar *src, \
                                              ZF_IN_OPT zfindex srcLen = zfindexMax) \
        {return zffalse;} \
        zfoverride \
        virtual zfbool wrappedValueToString(ZF_IN_OUT zfstring &s) \
        {return zffalse;} \
    }; \
    /** @cond ZFPrivateDoc */ \
    template<> \
    zfclassNotPOD ZFPropertyTypeIdData<_ZFP_ZFPropertyTypeWrapper_##TypeName> : zfextendsNotPOD ZFPropertyTypeIdDataBase \
    { \
        _ZFP_ZFPROPERTY_TYPE_ID_DATA_BASE_EXPAND(_ZFP_ZFPropertyTypeWrapper_##TypeName) \
    public: \
        enum { \
            PropertyRegistered = 1, \
            PropertyAccessable = 1, \
            PropertySerializable = 0, \
        }; \
        static inline const zfchar *PropertyTypeId(void) \
        { \
            return ZFPropertyTypeId_none; \
        } \
        zfoverride \
        virtual void propertyWrapper(ZF_OUT zfautoObject &v) const \
        { \
            v_##TypeName *t = zfAllocWithoutLeakTest(v_##TypeName); \
            v = zfautoObjectCreateWithoutLeakTest(t); \
            zfReleaseWithoutLeakTest(t); \
        } \
        static zfbool PropertyFromSerializableData(ZF_OUT _ZFP_ZFPropertyTypeWrapper_##TypeName &v, \
                                                   ZF_IN const ZFSerializableData &serializableData, \
                                                   ZF_OUT_OPT zfstring *outErrorHint = zfnull, \
                                                   ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull) \
        { \
            ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData, \
                zfText("registered type %s is not serializable"), zfText(#TypeName)); \
            return zffalse; \
        } \
        static zfbool PropertyToSerializableData(ZF_OUT ZFSerializableData &serializableData, \
                                                 ZF_IN _ZFP_ZFPropertyTypeWrapper_##TypeName const &v, \
                                                 ZF_OUT_OPT zfstring *outErrorHint = zfnull) \
        { \
            ZFSerializableUtil::errorOccurred(outErrorHint, \
                zfText("registered type %s is not serializable"), zfText(#TypeName)); \
            return zffalse; \
        } \
        static zfbool PropertyFromString(ZF_OUT _ZFP_ZFPropertyTypeWrapper_##TypeName &v, ZF_IN const zfchar *src, ZF_IN_OPT zfindex srcLen = zfindexMax) \
        { \
            return zffalse; \
        } \
        static zfbool PropertyToString(ZF_IN_OUT zfstring &s, ZF_IN _ZFP_ZFPropertyTypeWrapper_##TypeName const &v) \
        { \
            return zffalse; \
        } \
        static zfbool ValueStore(ZF_OUT zfautoObject &obj, ZF_IN _ZFP_ZFPropertyTypeWrapper_##TypeName const &v) \
        { \
            v_##TypeName *t = zfAllocWithoutLeakTest(v_##TypeName, v); \
            obj = zfautoObjectCreateWithoutLeakTest(t); \
            zfReleaseWithoutLeakTest(t); \
            return zftrue; \
        } \
        template<typename T_Access = _ZFP_ZFPropertyTypeWrapper_##TypeName \
            , int T_IsPointer = ((zftTraitsType<T_Access>::TypeIsPointer \
                && zftTypeIsSame< \
                        typename zftTraitsType<T_Access>::TraitsRemoveReference, \
                        _ZFP_ZFPropertyTypeWrapper_##TypeName \
                    >::TypeIsSame != 1) \
                ? 1 : 0) \
            , typename T_Fix = void \
            > \
        zfclassNotPOD Value \
        { \
        public: \
            static zfbool accessAvailable(ZF_IN ZFObject *obj) \
            { \
                return (ZFCastZFObject(v_##TypeName *, obj) != zfnull); \
            } \
            static T_Access access(ZF_IN ZFObject *obj) \
            { \
                return ZFCastZFObject(v_##TypeName *, obj)->zfv; \
            } \
        }; \
        template<typename T_Access> \
        zfclassNotPOD Value<T_Access, 1> \
        { \
        public: \
            static zfbool accessAvailable(ZF_IN ZFObject *obj) \
            { \
                return (ZFCastZFObject(v_##TypeName *, obj) != zfnull); \
            } \
            static typename zftTraitsType<T_Access>::TraitsRemoveReference access(ZF_IN ZFObject *obj) \
            { \
                return &(ZFCastZFObject(v_##TypeName *, obj)->zfv); \
            } \
        }; \
    }; \
    /** @endcond */

#define _ZFP_ZFPROPERTY_TYPE_ID_DATA_ACCESS_ONLY_DEFINE(TypeName, Type) \
    ZFOBJECT_REGISTER(v_##TypeName) \
    void v_##TypeName::objectInfoOnAppend(ZF_IN_OUT zfstring &ret) \
    { \
        ZFCoreElementInfoGetter<Type>::elementInfoGetter(ret, this->zfv); \
    } \
    ZFCompareResult v_##TypeName::objectCompare(ZF_IN ZFObject *anotherObj) \
    { \
        ZFPropertyTypeWrapper *t = ZFCastZFObject(ZFPropertyTypeWrapper *, anotherObj); \
        if(t == zfnull || !zfscmpTheSame(this->wrappedValuePropertyTypeId(), t->wrappedValuePropertyTypeId())) \
        { \
            return ZFCompareUncomparable; \
        } \
        else \
        { \
            return ZFComparerCheckEqual(this->zfv, *(_ZFP_ZFPropertyTypeWrapper_##TypeName *)t->wrappedValue()); \
        } \
    } \
    const zfchar *v_##TypeName::wrappedValuePropertyTypeId(void) \
    { \
        return ZFPropertyTypeIdData<_ZFP_ZFPropertyTypeWrapper_##TypeName>::PropertyTypeId(); \
    } \
    zfbool v_##TypeName::wrappedValueIsInit(void) \
    { \
        return (ZFComparerCheckEqual(this->zfv, zftValue<_ZFP_ZFPropertyTypeWrapper_##TypeName>().zfv) == ZFCompareTheSame); \
    } \
    ZFCompareResult v_##TypeName::wrappedValueCompare(ZF_IN const void *v) \
    { \
        return ZFComparerCheckEqual(this->zfv, *(const _ZFP_ZFPropertyTypeWrapper_##TypeName *)v); \
    }

#define _ZFP_ZFPROPERTY_TYPE_ID_DATA_ACCESS_ONLY_DEFINE_UNCOMPARABLE(TypeName, Type) \
    ZFOBJECT_REGISTER(v_##TypeName) \
    void v_##TypeName::objectInfoOnAppend(ZF_IN_OUT zfstring &ret) \
    { \
        ZFCoreElementInfoGetter<Type>::elementInfoGetter(ret, this->zfv); \
    } \
    ZFCompareResult v_##TypeName::objectCompare(ZF_IN ZFObject *anotherObj) \
    { \
        return ZFCompareUncomparable; \
    } \
    const zfchar *v_##TypeName::wrappedValuePropertyTypeId(void) \
    { \
        return ZFPropertyTypeIdData<_ZFP_ZFPropertyTypeWrapper_##TypeName>::PropertyTypeId(); \
    } \
    zfbool v_##TypeName::wrappedValueIsInit(void) \
    { \
        return zffalse; \
    } \
    ZFCompareResult v_##TypeName::wrappedValueCompare(ZF_IN const void *v) \
    { \
        return ZFCompareUncomparable; \
    }

// ============================================================
#define _ZFP_ZFPROPERTY_TYPE_ID_DATA_DISABLE(Type) \
    typedef Type _ZFP_ZFPropertyTypeWrapper_##TypeName; \
    /** @cond ZFPrivateDoc */ \
    template<> \
    zfclassNotPOD ZFPropertyTypeIdData<Type> : zfextendsNotPOD ZFPropertyTypeIdDataBase \
    { \
        _ZFP_ZFPROPERTY_TYPE_ID_DATA_BASE_EXPAND(Type) \
    public: \
        enum { \
            PropertyRegistered = 1, \
            PropertyAccessable = 0, \
            PropertySerializable = 0, \
        }; \
        static inline const zfchar *PropertyTypeId(void) \
        { \
            return ZFPropertyTypeId_none; \
        } \
        static zfbool PropertyFromSerializableData(ZF_OUT _ZFP_ZFPropertyTypeWrapper_##TypeName &v, \
                                                   ZF_IN const ZFSerializableData &serializableData, \
                                                   ZF_OUT_OPT zfstring *outErrorHint = zfnull, \
                                                   ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull) \
        { \
            ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData, \
                zfText("not serializable")); \
            return zffalse; \
        } \
        static zfbool PropertyToSerializableData(ZF_OUT ZFSerializableData &serializableData, \
                                                 ZF_IN _ZFP_ZFPropertyTypeWrapper_##TypeName const &v, \
                                                 ZF_OUT_OPT zfstring *outErrorHint = zfnull) \
        { \
            ZFSerializableUtil::errorOccurred(outErrorHint, \
                zfText("not serializable")); \
            return zffalse; \
        } \
        static zfbool PropertyFromString(ZF_OUT _ZFP_ZFPropertyTypeWrapper_##TypeName &v, ZF_IN const zfchar *src, ZF_IN_OPT zfindex srcLen = zfindexMax) \
        { \
            return zffalse; \
        } \
        static zfbool PropertyToString(ZF_IN_OUT zfstring &s, ZF_IN _ZFP_ZFPropertyTypeWrapper_##TypeName const &v) \
        { \
            return zffalse; \
        } \
        static zfbool ValueStore(ZF_OUT zfautoObject &obj, ZF_IN _ZFP_ZFPropertyTypeWrapper_##TypeName const &v) \
        { \
            return zffalse; \
        } \
        template<typename T_Access = Type> \
        zfclassNotPOD Value \
        { \
        public: \
            static zfbool accessAvailable(ZF_IN ZFObject *obj) \
            { \
                return zffalse; \
            } \
            static typename zftTraitsType<T_Access>::TraitsRemoveReference access(ZF_IN ZFObject *obj) \
            { \
                return typename zftTraitsType<T_Access>::TraitsRemoveReference(); \
            } \
        }; \
    }; \
    /** @endcond */

// ============================================================
#define _ZFP_ZFPROPERTY_TYPE_ID_DATA_ALIAS_DECLARE(ExistTypeName, ExistType, TypeName, Type) \
    /** @cond ZFPrivateDoc */ \
    typedef Type _ZFP_ZFPropertyTypeWrapper_##TypeName; \
    template<> \
    zfclassNotPOD ZFPropertyTypeIdData<Type> : zfextendsNotPOD ZFPropertyTypeIdDataBase \
    { \
        _ZFP_ZFPROPERTY_TYPE_ID_DATA_BASE_EXPAND(Type) \
    public: \
        enum { \
            PropertyRegistered = ZFPropertyTypeIdData<ExistType>::PropertyRegistered, \
            PropertyAccessable = ZFPropertyTypeIdData<ExistType>::PropertyAccessable, \
            PropertySerializable = ZFPropertyTypeIdData<ExistType>::PropertySerializable, \
        }; \
        static inline const zfchar *PropertyTypeId(void) \
        { \
            return ZFPropertyTypeIdData<ExistType>::PropertyTypeId(); \
        } \
        zfoverride \
        virtual void propertyWrapper(ZF_OUT zfautoObject &v) const \
        { \
            ZFPropertyTypeIdData<ExistType> t; \
            t.propertyWrapper(v); \
        } \
        static zfbool PropertyFromSerializableData(ZF_OUT _ZFP_ZFPropertyTypeWrapper_##TypeName &v, \
                                                   ZF_IN const ZFSerializableData &serializableData, \
                                                   ZF_OUT_OPT zfstring *outErrorHint = zfnull, \
                                                   ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull) \
        { \
            zftValue<ExistType> t; \
            if(ZFPropertyTypeIdData<ExistType>::PropertyFromSerializableData(t.zfv, serializableData, outErrorHint, outErrorPos)) \
            { \
                v = t.zfv; \
                return zftrue; \
            } \
            else \
            { \
                return zffalse; \
            } \
        } \
        static zfbool PropertyToSerializableData(ZF_OUT ZFSerializableData &serializableData, \
                                                 ZF_IN _ZFP_ZFPropertyTypeWrapper_##TypeName const &v, \
                                                 ZF_OUT_OPT zfstring *outErrorHint = zfnull) \
        { \
            return ZFPropertyTypeIdData<ExistType>::PropertyToSerializableData(serializableData, (ExistType)v, outErrorHint); \
        } \
        static zfbool PropertyFromString(ZF_OUT _ZFP_ZFPropertyTypeWrapper_##TypeName &v, ZF_IN const zfchar *src, ZF_IN_OPT zfindex srcLen = zfindexMax) \
        { \
            zftValue<ExistType> t; \
            if(ZFPropertyTypeIdData<ExistType>::PropertyFromString(t.zfv, src, srcLen)) \
            { \
                v = t.zfv; \
                return zftrue; \
            } \
            else \
            { \
                return zffalse; \
            } \
        } \
        static zfbool PropertyToString(ZF_IN_OUT zfstring &s, ZF_IN _ZFP_ZFPropertyTypeWrapper_##TypeName const &v) \
        { \
            return ZFPropertyTypeIdData<ExistType>::PropertyToString(s, (ExistType)v); \
        } \
        static zfbool ValueStore(ZF_OUT zfautoObject &obj, ZF_IN _ZFP_ZFPropertyTypeWrapper_##TypeName const &v) \
        { \
            return ZFPropertyTypeIdData<ExistType>::ValueStore(obj, (ExistType)v); \
        } \
        template<typename T_Access = _ZFP_ZFPropertyTypeWrapper_##TypeName, typename T_Fix = void> \
        zfclassNotPOD Value \
        { \
            /* not support */ \
        }; \
        template<typename T_Fix> \
        zfclassNotPOD Value<_ZFP_ZFPropertyTypeWrapper_##TypeName, T_Fix> \
        { \
        public: \
            static zfbool accessAvailable(ZF_IN ZFObject *obj) \
            { \
                return ZFPropertyTypeIdData<ExistType>::Value<ExistType const &>::accessAvailable(obj); \
            } \
            static _ZFP_ZFPropertyTypeWrapper_##TypeName access(ZF_IN ZFObject *obj) \
            { \
                return (_ZFP_ZFPropertyTypeWrapper_##TypeName)ZFPropertyTypeIdData<ExistType>::Value<ExistType const &>::access(obj); \
            } \
        }; \
        template<typename T_Fix> \
        zfclassNotPOD Value<_ZFP_ZFPropertyTypeWrapper_##TypeName const &, T_Fix> \
        { \
        public: \
            static zfbool accessAvailable(ZF_IN ZFObject *obj) \
            { \
                return ZFPropertyTypeIdData<ExistType>::Value<ExistType const &>::accessAvailable(obj); \
            } \
            static _ZFP_ZFPropertyTypeWrapper_##TypeName access(ZF_IN ZFObject *obj) \
            { \
                return (_ZFP_ZFPropertyTypeWrapper_##TypeName)ZFPropertyTypeIdData<ExistType>::Value<ExistType const &>::access(obj); \
            } \
        }; \
    }; \
    /** @endcond */ \
    /** @brief type wrapper for #ZFPropertyTypeIdData::Value */ \
    zfclass ZF_ENV_EXPORT v_##TypeName : zfextends v_##ExistTypeName \
    { \
        ZFOBJECT_DECLARE(v_##TypeName, v_##ExistTypeName) \
    };
#define _ZFP_ZFPROPERTY_TYPE_ID_DATA_ALIAS_DEFINE(ExistTypeName, ExistType, TypeName, Type) \
    ZFOBJECT_REGISTER(v_##TypeName)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFPropertyTypeFwd_h_

