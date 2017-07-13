/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFPropertyType_Core.h
 * @brief type define for ZFProperty
 */

#ifndef _ZFI_ZFPropertyType_Core_h_
#define _ZFI_ZFPropertyType_Core_h_

#include "ZFStyleable.h"
#include "ZFMethodUserRegister.h"
#include "ZFMethodFuncUserRegister.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief register a property type
 *
 * usually for implementation use only,
 * ZFFramework would supply most of the types,
 * however you may use this to register your own types\n
 * \n
 * typical code to register a type:
 * @code
 *   // ============================================================
 *   // in h file
 *   // declare your type, name must be unique
 *   / **
 *    * add your Doxygen docs here
 *    * /
 *   ZFPROPERTY_TYPE_DECLARE(YourType, YourType)
 *
 *   // ============================================================
 *   // in cpp file
 *   // register your type
 *   ZFPROPERTY_TYPE_DEFINE(YourType, YourType, {
 *           // serializeFrom callback, proto type:
 *           //   zfbool YourTypeFromSerializableData(
 *           //       ZF_OUT YourType &v,
 *           //       ZF_IN const ZFSerializableData &serializableData,
 *           //       ZF_OUT_OPT zfstring *outErrorHint = zfnull,
 *           //       ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull);
 *           // you should:
 *           //   * check whether the property's type match the serializableData's type
 *           //   * serialize from serializableData
 *           //   * set the property by the property's setter method
 *       }, {
 *           // serializeTo callback, proto type:
 *           //   zfbool YourTypeToSerializableData(
 *           //       ZF_OUT ZFSerializableData &serializableData,
 *           //       ZF_IN YourType const &v,
 *           //       ZF_OUT_OPT zfstring *outErrorHint = zfnull);
 *           // you should:
 *           //   * get the property's value by the property's getter method
 *           //   * save typeid to the serializableData
 *           //   * save property name to the serializableData
 *           //   * save property value to the serializableData
 *       }, {
 *           // convertFromString callback, proto type:
 *           //   zfbool YourTypeFromString(
 *           //       ZF_OUT YourType &v,
 *           //       ZF_IN const zfchar *src,
 *           //       ZF_IN_OPT zfindex srcLen = zfindexMax);
 *       }, {
 *           // convertToString callbackk, proto type:
 *           //   zfbool YourTypeToString(
 *           //       ZF_IN_OUT zfstring &s,
 *           //       ZF_IN YourType const &v);
 *       })
 *
 *   // or, you may use #ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER for short,
 *   // if your type support converter from/to string
 *   ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(YourType, YourType, YourTypeFromString, YourTypeToString)
 *
 *   // or, you may use #ZFPROPERTY_TYPE_DEFINE_BY_SERIALIZABLE_CONVERTER for short,
 *   // if your type support converter from/to ZFSerializableData
 *   ZFPROPERTY_TYPE_DEFINE_BY_SERIALIZABLE_CONVERTER(YourType, YourType, YourTypeFromSerializableData, YourTypeToSerializableData)
 * @endcode
 *
 * once registered, your type can be used as #ZFPROPERTY_ASSIGN
 * which benefits from the powerful automatic serialization logic,
 * or, can be used as reflectable param or return type for #ZFMETHOD_DECLARE_0\n
 * \n
 * \n
 * ADVANCED:\n
 * -  a type can be used as #ZFPROPERTY_ASSIGN only if declared by #ZFPROPERTY_TYPE_DECLARE
 * -  no inheritance support for #ZFPROPERTY_TYPE_DECLARE
 * -  for aliased type, you may use #ZFPROPERTY_TYPE_ALIAS_DECLARE
 */
#define ZFPROPERTY_TYPE_DECLARE(TypeName, Type) \
    /** \n */ \
    inline const zfchar *ZFPropertyTypeId_##TypeName(void) \
    { \
        return zfText(#TypeName); \
    } \
    /** @brief see #ZFPROPERTY_TYPE_DECLARE */ \
    extern ZF_ENV_EXPORT zfbool TypeName##FromSerializableData(ZF_OUT Type &v, \
                                                               ZF_IN const ZFSerializableData &serializableData, \
                                                               ZF_OUT_OPT zfstring *outErrorHint = zfnull, \
                                                               ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull); \
    /** @brief see #ZFPROPERTY_TYPE_DECLARE */ \
    inline Type TypeName##FromSerializableData(ZF_IN const ZFSerializableData &serializableData, \
                                               ZF_OUT_OPT zfstring *outErrorHint = zfnull, \
                                               ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull) \
    { \
        Type ret; \
        if(TypeName##FromSerializableData(ret, serializableData, outErrorHint, outErrorPos)) \
        { \
            return ret; \
        } \
        else \
        { \
            typedef Type _Type; \
            return _Type();\
        } \
        return ret; \
    } \
    /** @brief see #ZFPROPERTY_TYPE_DECLARE */ \
    extern ZF_ENV_EXPORT zfbool TypeName##ToSerializableData(ZF_OUT ZFSerializableData &serializableData, \
                                                             ZF_IN Type const &v, \
                                                             ZF_OUT_OPT zfstring *outErrorHint = zfnull); \
    /** @brief see #ZFPROPERTY_TYPE_DECLARE */ \
    inline ZFSerializableData TypeName##ToSerializableData(ZF_IN Type const &v, \
                                                           ZF_OUT_OPT zfstring *outErrorHint = zfnull) \
    { \
        ZFSerializableData ret; \
        if(TypeName##ToSerializableData(ret, v, outErrorHint)) \
        { \
            return ret; \
        } \
        else \
        { \
            return ZFSerializableData(); \
        } \
    } \
    ZFCORETYPE_STRING_CONVERTER_DECLARE(TypeName, Type) \
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_DECLARE(TypeName, Type)

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 */
#define ZFPROPERTY_TYPE_DEFINE(TypeName, Type, serializeFromAction, serializeToAction, convertFromStringAction, convertToStringAction) \
    zfclassNotPOD _ZFP_ZFPropertyTypeRegisterHolder_##TypeName \
    { \
    public: \
        static zfbool serializeFrom(ZF_IN const ZFProperty *propertyInfo, \
                                    ZF_IN ZFObject *ownerObject, \
                                    ZF_IN const ZFSerializableData &serializableData, \
                                    ZF_OUT_OPT zfstring *outErrorHint = zfnull, \
                                    ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull) \
        { \
            if(ZFSerializableUtil::requireSerializableClass(propertyInfo->propertyTypeId(), serializableData, outErrorHint, outErrorPos) == zfnull) \
            { \
                return zffalse; \
            } \
            Type v; \
            if(!TypeName##FromSerializableData(v, serializableData, outErrorHint, outErrorPos)) \
            { \
                return zffalse; \
            } \
            propertyInfo->setterMethod()->execute<void, Type const &>(ownerObject, v); \
            return zftrue; \
        } \
        static zfbool serializeTo(ZF_IN const ZFProperty *propertyInfo, \
                                  ZF_IN ZFObject *ownerObject, \
                                  ZF_OUT ZFSerializableData &serializableData, \
                                  ZF_OUT_OPT zfstring *outErrorHint = zfnull) \
        { \
            serializableData.itemClassSet(propertyInfo->propertyTypeId()); \
            serializableData.propertyNameSet(propertyInfo->propertyName()); \
            Type const &v = propertyInfo->getterMethod()->execute<Type const &>(ownerObject); \
            return TypeName##ToSerializableData(serializableData, v, outErrorHint); \
        } \
    }; \
    ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(PropId_##TypeName, ZFLevelZFFrameworkNormal) \
    { \
        _ZFP_ZFPropertyTypeRegister( \
            ZFPropertyTypeId_##TypeName(), \
            _ZFP_ZFPropertyTypeRegisterHolder_##TypeName::serializeFrom, \
            _ZFP_ZFPropertyTypeRegisterHolder_##TypeName::serializeTo); \
    } \
    ZF_GLOBAL_INITIALIZER_DESTROY(PropId_##TypeName) \
    { \
        _ZFP_ZFPropertyTypeUnregister(ZFPropertyTypeId_##TypeName()); \
    } \
    ZF_GLOBAL_INITIALIZER_END(PropId_##TypeName) \
    zfbool TypeName##FromSerializableData(ZF_OUT Type &v, \
                                          ZF_IN const ZFSerializableData &serializableData, \
                                          ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */, \
                                          ZF_OUT_OPT ZFSerializableData *outErrorPos /* = zfnull */) \
    { \
        ZFM_EXPAND(serializeFromAction) \
    } \
    zfbool TypeName##ToSerializableData(ZF_OUT ZFSerializableData &serializableData, \
                                        ZF_IN Type const &v, \
                                        ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */) \
    { \
        ZFM_EXPAND(serializeToAction) \
    } \
    ZFCORETYPE_STRING_CONVERTER_DEFINE(TypeName, Type, ZFM_EXPAND(convertFromStringAction), ZFM_EXPAND(convertToStringAction)) \
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_DEFINE(TypeName, Type, ZFM_EXPAND(convertFromStringAction), ZFM_EXPAND(convertToStringAction)) \
    _ZFP_ZFPROPERTY_TYPE_DEFINE_METHOD_REGISTER(TypeName, Type)

#define _ZFP_ZFPROPERTY_TYPE_DEFINE_METHOD_REGISTER(TypeName, Type) \
    ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(PropMtdReg_##TypeName, ZFLevelZFFrameworkNormal) \
    { \
        ZFMethodFuncUserRegister_4(method_FromSerializable, { \
                return TypeName##FromSerializableData(v, serializableData, outErrorHint, outErrorPos); \
            }, zfbool, TypeName##FromSerializableData \
            , ZFMP_OUT(Type &, v) \
            , ZFMP_IN(const ZFSerializableData &, serializableData) \
            , ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull) \
            , ZFMP_OUT_OPT(ZFSerializableData *, outErrorPos, zfnull) \
            ); \
        _method_FromSerializable = method_FromSerializable; \
        ZFMethodFuncUserRegister_3(method_ToSerializable, { \
                return TypeName##ToSerializableData(serializableData, v, outErrorHint); \
            }, zfbool, TypeName##ToSerializableData \
            , ZFMP_OUT(ZFSerializableData &, serializableData) \
            , ZFMP_IN(Type const &, v) \
            , ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull) \
            ); \
        _method_ToSerializable = method_ToSerializable; \
        ZFMethodFuncUserRegister_2(method_ToSerializable2, { \
                return TypeName##ToSerializableData(v, outErrorHint); \
            }, ZFSerializableData, TypeName##ToSerializableData \
            , ZFMP_IN(Type const &, v) \
            , ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull) \
            ); \
        _method_ToSerializable2 = method_ToSerializable2; \
        ZFMethodFuncUserRegister_3(method_FromString, { \
                return TypeName##FromString(v, src, srcLen); \
            }, zfbool, TypeName##FromString \
            , ZFMP_OUT(Type &, v) \
            , ZFMP_IN(const zfchar *, src) \
            , ZFMP_OUT_OPT(zfindex, srcLen, zfindexMax) \
            ); \
        _method_FromString = method_FromString; \
        ZFMethodFuncUserRegister_2(method_ToString, { \
                return TypeName##ToString(s, v); \
            }, zfbool, TypeName##ToString \
            , ZFMP_OUT(zfstring &, s) \
            , ZFMP_IN(Type const &, v) \
            ); \
        _method_ToString = method_ToString; \
        ZFMethodFuncUserRegister_1(method_ToString2, { \
                return TypeName##ToString(v); \
            }, zfstring, TypeName##ToString \
            , ZFMP_IN(Type const &, v) \
            ); \
        _method_ToString2 = method_ToString2; \
    } \
    ZF_GLOBAL_INITIALIZER_DESTROY(PropMtdReg_##TypeName) \
    { \
        ZFMethodFuncUserUnregister(_method_FromSerializable); \
        ZFMethodFuncUserUnregister(_method_ToSerializable); \
        ZFMethodFuncUserUnregister(_method_ToSerializable2); \
        ZFMethodFuncUserUnregister(_method_FromString); \
        ZFMethodFuncUserUnregister(_method_ToString); \
        ZFMethodFuncUserUnregister(_method_ToString2); \
    } \
    public: \
        const ZFMethod *_method_FromSerializable; \
        const ZFMethod *_method_ToSerializable; \
        const ZFMethod *_method_ToSerializable2; \
        const ZFMethod *_method_FromString; \
        const ZFMethod *_method_ToString; \
        const ZFMethod *_method_ToString2; \
    ZF_GLOBAL_INITIALIZER_END(PropMtdReg_##TypeName)

/** @brief see #ZFPROPERTY_TYPE_DECLARE */
#define ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(TypeName, Type, convertFromStringAction, convertToStringAction) \
    ZFPROPERTY_TYPE_DEFINE(TypeName, Type, { \
        if(ZFSerializableUtil::requireSerializableClass(ZFPropertyTypeId_##TypeName(), serializableData, outErrorHint, outErrorPos) == zfnull) \
        { \
            return zffalse; \
        } \
        const zfchar *valueString = ZFSerializableUtil::checkPropertyValue(serializableData); \
        if(valueString == zfnull) \
        { \
            typedef Type _Type; \
            v = _Type(); \
            return zftrue; \
        } \
        if(!TypeName##FromString(v, valueString)) \
        { \
            ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData, \
                zfText("invalid value: \"%s\""), valueString); \
            return zffalse; \
        } \
        serializableData.resolveMark(); \
        return zftrue; \
    }, { \
        serializableData.itemClassSet(ZFPropertyTypeId_##TypeName()); \
        zfstring s; \
        if(!TypeName##ToString(s, v)) \
        { \
            return zffalse; \
        } \
        serializableData.propertyValueSet(s.cString()); \
        return zftrue; \
    }, ZFM_EXPAND(convertFromStringAction), ZFM_EXPAND(convertToStringAction))

/** @brief see #ZFPROPERTY_TYPE_DECLARE */
#define ZFPROPERTY_TYPE_DEFINE_BY_SERIALIZABLE_CONVERTER(TypeName, Type, serializeFromAction, serializeToAction) \
    ZFPROPERTY_TYPE_DEFINE(TypeName, Type, ZFM_EXPAND(serializeFromAction), ZFM_EXPAND(serializeToAction), { \
        ZFSerializableData serializableData; \
        return (ZFSerializableDataFromString(serializableData, src, srcLen) \
            && TypeName##FromSerializableData(v, serializableData)); \
    }, { \
        ZFSerializableData serializableData; \
        if(TypeName##ToSerializableData(serializableData, v)) \
        { \
            return ZFSerializableDataToString(s, serializableData); \
        } \
        else \
        { \
            return zffalse; \
        } \
    })

// ============================================================
/**
 * @brief declare a type that reflectable and accessable, but not serializable
 *
 * by default, all return types and method types in ZFMethod
 * must be registered by #ZFPROPERTY_TYPE_DECLARE
 * for advanced reflection logic\n
 * if you simply want basic method declaration,
 * you may use this macro to disable your type explicitly\n
 * see #ZFPROPERTY_TYPE_DECLARE for more info
 */
#define ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(TypeName, Type) \
    /** \n */ \
    inline const zfchar *ZFPropertyTypeId_##TypeName(void) \
    { \
        return ZFPropertyTypeId_none; \
    } \
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_ACCESS_ONLY_DECLARE(TypeName, Type)
/** @brief see #ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE */
#define ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(TypeName, Type) \
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_ACCESS_ONLY_DEFINE(TypeName, Type)
/** @brief see #ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE */
#define ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE_UNCOMPARABLE(TypeName, Type) \
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_ACCESS_ONLY_DEFINE_UNCOMPARABLE(TypeName, Type)

// ============================================================
/**
 * @brief alias an existing type to another type, see #ZFPROPERTY_TYPE_DECLARE
 *
 * the original type must be declared by #ZFPROPERTY_TYPE_DECLARE or #ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE\n
 * the newly aliased type would share same type id,
 * serializable converter and string converter,
 * with the original exist one\n
 * see #ZFPROPERTY_TYPE_DECLARE for more info
 */
#define ZFPROPERTY_TYPE_ALIAS_DECLARE(ExistTypeName, ExistType, AnotherTypeName, AnotherType) \
    /** @brief see @ref ZFPropertyTypeId_##ExistTypeName */ \
    inline const zfchar *ZFPropertyTypeId_##AnotherTypeName(void) \
    { \
        return ZFPropertyTypeId_##ExistTypeName(); \
    } \
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_ALIAS_DECLARE(ExistTypeName, ExistType, AnotherTypeName, AnotherType)
/** @brief see #ZFPROPERTY_TYPE_ALIAS_DECLARE */
#define ZFPROPERTY_TYPE_ALIAS_DEFINE(ExistTypeName, ExistType, AnotherTypeName, AnotherType) \
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_ALIAS_DEFINE(ExistTypeName, ExistType, AnotherTypeName, AnotherType)

// ============================================================
/**
 * @brief explicitly mark the type can not be reflected when used in #ZFMETHOD_DECLARE_0 or #ZFPROPERTY_ASSIGN
 *
 * by default, all return types and method types in ZFMethod
 * must be registered by #ZFPROPERTY_TYPE_DECLARE
 * for advanced reflection logic\n
 * if you simply want basic method declaration,
 * you may use this macro to disable your type explicitly\n
 * see #ZFPROPERTY_TYPE_DECLARE for more info
 */
#define ZFPROPERTY_TYPE_DISABLE(Type) \
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_DISABLE(Type)

// ============================================================
/**
 * @brief see #ZFPropertyTypeGetSerializeFromCallback
 */
typedef zfbool (*ZFPropertyTypeSerializeFromCallback)(ZF_IN const ZFProperty *propertyInfo,
                                                      ZF_IN ZFObject *ownerObject,
                                                      ZF_IN const ZFSerializableData &serializableData,
                                                      ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */,
                                                      ZF_OUT_OPT ZFSerializableData *outErrorPos /* = zfnull */);
/**
 * @brief see #ZFPropertyTypeGetSerializeToCallback
 */
typedef zfbool (*ZFPropertyTypeSerializeToCallback)(ZF_IN const ZFProperty *propertyInfo,
                                                    ZF_IN ZFObject *ownerObject,
                                                    ZF_OUT ZFSerializableData &serializableData,
                                                    ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */);
extern ZF_ENV_EXPORT void _ZFP_ZFPropertyTypeRegister(ZF_IN const zfchar *typeIdName,
                                                      ZF_IN ZFPropertyTypeSerializeFromCallback serializeFromCallback,
                                                      ZF_IN ZFPropertyTypeSerializeToCallback serializeToCallback);
extern ZF_ENV_EXPORT void _ZFP_ZFPropertyTypeUnregister(ZF_IN const zfchar *typeIdName);

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * directly access the serialize callback, for performance use only
 */
extern ZF_ENV_EXPORT ZFPropertyTypeSerializeFromCallback ZFPropertyTypeGetSerializeFromCallback(ZF_IN const zfchar *typeIdName);
/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * directly access the serialize callback, for performance use only
 */
extern ZF_ENV_EXPORT ZFPropertyTypeSerializeToCallback ZFPropertyTypeGetSerializeToCallback(ZF_IN const zfchar *typeIdName);

/**
 * @brief serialize property from serializable data, see #ZFPROPERTY_TYPE_DECLARE
 */
extern ZF_ENV_EXPORT zfbool ZFPropertySerializeFrom(ZF_IN ZFObject *ownerObject,
                                                    ZF_IN const ZFSerializableData &serializableData,
                                                    ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                    ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull);
/**
 * @brief serialize property to serializable data, see #ZFPROPERTY_TYPE_DECLARE
 */
extern ZF_ENV_EXPORT zfbool ZFPropertySerializeTo(ZF_IN const ZFProperty *propertyInfo,
                                                  ZF_IN ZFObject *ownerObject,
                                                  ZF_OUT ZFSerializableData &serializableData,
                                                  ZF_OUT_OPT zfstring *outErrorHint = zfnull);

// ============================================================
/**
 * @brief dummy base for all wrapper types,
 *   see #ZFPropertyTypeIdData::PropertyConvertFromZFObject
 *
 * serializable data:
 * @code
 *   <WrapperTypeClass
 *       value="string content" // optional, empty by default
 *   />
 * @endcode
 */
zfabstract ZF_ENV_EXPORT ZFPropertyTypeWrapper : zfextends ZFStyleableObject
{
    ZFOBJECT_DECLARE_ABSTRACT(ZFPropertyTypeWrapper, ZFStyleableObject)

public:
    /**
     * @brief type id for this wrapper type
     */
    virtual const zfchar *wrappedValuePropertyTypeId(void) zfpurevirtual;
    /**
     * @brief access the value's address
     */
    virtual void *wrappedValue(void) zfpurevirtual;
    /**
     * @brief set the value, no type safe check
     */
    virtual void wrappedValueSet(ZF_IN const void *v) zfpurevirtual;

public:
    /**
     * @brief reset the value to it's init value
     */
    virtual void wrappedValueReset(void) zfpurevirtual;
    /**
     * @brief true if the value is in init value state
     */
    virtual zfbool wrappedValueIsInit(void) zfpurevirtual;
    /**
     * @brief compare the value
     */
    virtual ZFCompareResult wrappedValueCompare(ZF_IN const void *v) zfpurevirtual;

public:
    /**
     * @brief convert from serializable data, see #ZFPropertyTypeIdData::PropertyFromSerializableData
     */
    virtual zfbool wrappedValueFromSerializableData(ZF_IN const ZFSerializableData &serializableData,
                                                    ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                    ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull) zfpurevirtual;
    /**
     * @brief convert to serializable data, see #ZFPropertyTypeIdData::PropertyToSerializableData
     */
    virtual zfbool wrappedValueToSerializableData(ZF_OUT ZFSerializableData &serializableData,
                                                  ZF_OUT_OPT zfstring *outErrorHint = zfnull) zfpurevirtual;
    /**
     * @brief convert from string, see #ZFPropertyTypeIdData::PropertyFromString
     */
    virtual zfbool wrappedValueFromString(ZF_IN const zfchar *src,
                                          ZF_IN_OPT zfindex srcLen = zfindexMax) zfpurevirtual;
    /**
     * @brief convert to string, see #ZFPropertyTypeIdData::PropertyToString
     */
    virtual zfbool wrappedValueToString(ZF_IN_OUT zfstring &s) zfpurevirtual;

public:
    zfoverride
    virtual zfbool objectIsPrivate(void)
    {
        return zftrue;
    }
    zfoverride
    virtual zfbool objectIsInternal(void)
    {
        return zftrue;
    }

protected:
    zfoverride
    virtual inline void styleableOnCopyFrom(ZF_IN ZFStyleable *anotherStyleable)
    {
        zfsuper::styleableOnCopyFrom(anotherStyleable);
        this->wrappedValueSet(anotherStyleable->to<ZFPropertyTypeWrapper *>()->wrappedValue());
    }

protected:
    zfoverride
    virtual zfbool serializableOnSerializeFromData(ZF_IN const ZFSerializableData &serializableData,
                                                   ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                   ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull)
    {
        if(!zfsuperI(ZFSerializable)::serializableOnSerializeFromData(serializableData, outErrorHint, outErrorPos)) {return zffalse;}

        const zfchar *valueString = ZFSerializableUtil::checkPropertyValue(serializableData);
        if(valueString == zfnull)
        {
            this->wrappedValueReset();
        }
        else if(!this->wrappedValueFromString(valueString))
        {
            ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
                zfText("failed to convert from \"%s\""), valueString);
            return zffalse;
        }
        return zftrue;
    }
    zfoverride
    virtual zfbool serializableOnSerializeToData(ZF_IN_OUT ZFSerializableData &serializableData,
                                                 ZF_IN ZFSerializable *referencedOwnerOrNull,
                                                 ZF_OUT_OPT zfstring *outErrorHint = zfnull)
    {
        if(!zfsuperI(ZFSerializable)::serializableOnSerializeToData(serializableData, referencedOwnerOrNull, outErrorHint)) {return zffalse;}
        zfself *ref = ZFCastZFObject(zfself *, referencedOwnerOrNull);

        if((ref == zfnull && !this->wrappedValueIsInit())
            || (ref != zfnull && this->objectCompare(ref) != ZFCompareTheSame))
        {
            zfstring valueString;
            if(!this->wrappedValueToString(valueString))
            {
                return zffalse;
            }
            serializableData.propertyValueSet(valueString);
        }

        return zftrue;
    }
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFPropertyType_Core_h_

