/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFProperty.h
 * @brief property for ZFObject type
 */

#ifndef _ZFI_ZFProperty_h_
#define _ZFI_ZFProperty_h_

#include "ZFPropertyFwd.h"
#include "ZFPropertyTypeFwd.h"
#include "ZFMethod.h"
#include "ZFObjectClassTypeFwd.h"
#include "ZFObjectCast.h"
#include "ZFAny.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
zfclassFwd ZFProperty;
typedef void (*_ZFP_ZFPropertyCallbackDealloc)(ZF_IN ZFObject *owner, ZF_IN const ZFProperty *property);
/**
 * @brief info for a property for ZFObject, see #ZFPROPERTY_RETAIN for more info
 */
zffinal zfclassNotPOD ZF_ENV_EXPORT ZFProperty
{
    ZFCLASS_DISALLOW_COPY_CONSTRUCTOR(ZFProperty)

public:
    /**
     * @brief get info about this property
     */
    void objectInfoT(ZF_IN_OUT zfstring &ret) const;
    /** @brief see #objectInfoT */
    zfstring objectInfo(void) const
    {
        zfstring ret;
        this->objectInfoT(ret);
        return ret;
    }

public:
    /**
     * @brief internal property id, for debug use only
     */
    inline const zfchar *propertyInternalId(void) const
    {
        return this->_ZFP_ZFProperty_propertyInternalId;
    }
    /**
     * @brief true if this property is registered by #ZFPropertyUserRegisterRetain
     */
    inline zfbool propertyIsUserRegister(void) const
    {
        return this->_ZFP_ZFProperty_propertyIsUserRegister;
    }
    /**
     * @brief get the property's owner class
     */
    inline const ZFClass *propertyOwnerClass(void) const
    {
        return this->_ZFP_ZFProperty_propertyOwnerClass;
    }
    /**
     * @brief name for the property
     *
     * assume property's name is "myProperty",
     * then the setter would be "myPropertySet",
     * and the getter would be "myProperty",
     * and getter name would return "myProperty"
     */
    inline const zfchar *propertyName(void) const
    {
        return this->_ZFP_ZFProperty_name.cString();
    }
    /**
     * @brief type string for the property
     *
     * note the type string is the macro expand from the type,
     * it may or may not be same for same type,
     * usually for debug use only
     */
    inline const zfchar *propertyTypeName(void) const
    {
        return this->_ZFP_ZFProperty_typeName.cString();
    }
    /**
     * @brief typeid string declared in ZFPROPERTY_XXX
     *
     * this value should be ensured the type id for the type or #ZFPropertyTypeId_none if no known type,
     * this value is used for property's advanced copy function,
     * see #ZFPropertySerializeFrom
     * @note for retain property, this value is always #ZFPropertyTypeId_ZFObject
     * @note for non-serializable property (see #propertyIsSerializable),
     *   this value is always #ZFPropertyTypeId_none
     */
    inline const zfchar *propertyTypeId(void) const
    {
        return this->_ZFP_ZFProperty_typeId.cString();
    }
    /**
     * @brief whether this property is declared as serializable
     *
     * by default, all property can be serialized,
     * you may explicitly declare a property not serializable by
     * -  for assign property, using #ZFPROPERTY_ASSIGN_NOT_SERIALIZABLE,
     *   or declare property with #ZFPropertyTypeId_none as type id
     * -  for retain property, using #ZFPROPERTY_RETAIN_NOT_SERIALIZABLE
     *
     * a non-serializable property would be ignored while serializing its owner object
     */
    inline zfbool propertyIsSerializable(void) const
    {
        return this->_ZFP_ZFProperty_serializable;
    }
    /**
     * @brief get the getter method
     */
    inline const ZFMethod *setterMethod(void) const
    {
        return this->_ZFP_ZFProperty_setterMethod;
    }
    /**
     * @brief get the getter method
     */
    inline const ZFMethod *getterMethod(void) const
    {
        return this->_ZFP_ZFProperty_getterMethod;
    }

    /**
     * @brief true if the property is retain property
     *
     * note that bool property is also a assign property,
     * it also have a getter method named "propertyName"
     */
    inline zfbool propertyIsRetainProperty(void) const
    {
        return (this->callbackRetainSet != zfnull);
    }
    /**
     * @brief for retain property only, get the retain property's declared class
     *
     * note it's the declared class, property's value may be subclass of it
     */
    inline const ZFClass *propertyClassOfRetainProperty(void) const
    {
        return this->_ZFP_ZFProperty_propertyClassOfRetainProperty;
    }

public:
    /**
     * @brief used to check whether the property has been accessed
     */
    ZFPropertyCallbackIsValueAccessed callbackIsValueAccessed;
    /**
     * @brief used to check whether the property is in init value state
     */
    ZFPropertyCallbackIsInitValue callbackIsInitValue;
    /**
     * @brief used to compare two object's property value
     */
    ZFPropertyCallbackCompare callbackCompare;
    /**
     * @brief used to copy property from another object
     */
    ZFPropertyCallbackCopy callbackCopy;
    /**
     * @brief see #ZFPropertyRetainSet
     */
    ZFPropertyCallbackRetainSet callbackRetainSet;
    /**
     * @brief see #ZFPropertyRetainGet
     */
    ZFPropertyCallbackRetainGet callbackRetainGet;
    /**
     * @brief see #ZFPropertyAssignSet
     */
    ZFPropertyCallbackAssignSet callbackAssignSet;
    /**
     * @brief see #ZFPropertyAssignGet
     */
    ZFPropertyCallbackAssignGet callbackAssignGet;
    /**
     * @brief see #ZFPropertyGetInfo
     */
    ZFPropertyCallbackGetInfo callbackGetInfo;

    /**
     * @brief see #ZFPropertyUserRegisterAssign
     */
    ZFPropertyCallbackUserRegisterInitValueSetup callbackUserRegisterInitValueSetup;

public:
    /** @cond ZFPrivateDoc */
    ZFProperty(void);
    ~ZFProperty(void);
    /** @endcond */
    zfbool _ZFP_ZFPropertyNeedInit;
    void _ZFP_ZFPropertyInit(ZF_IN zfbool propertyIsUserRegister,
                             ZF_IN const ZFClass *propertyOwnerClass,
                             ZF_IN const zfchar *name,
                             ZF_IN const zfchar *typeName,
                             ZF_IN const zfchar *typeIdName,
                             ZF_IN const ZFMethod *setterMethod,
                             ZF_IN const ZFMethod *getterMethod,
                             ZF_IN const ZFClass *propertyClassOfRetainProperty);
    ZFProperty *_ZFP_ZFProperty_removeConst(void) const
    {
        return const_cast<ZFProperty *>(this);
    }
public:
    zfstring _ZFP_ZFProperty_propertyInternalId;
    zfbool _ZFP_ZFProperty_propertyIsUserRegister;
    const ZFClass *_ZFP_ZFProperty_propertyOwnerClass;
    zfstring _ZFP_ZFProperty_name;
    zfstring _ZFP_ZFProperty_typeName;
    zfstring _ZFP_ZFProperty_typeId;
    zfbool _ZFP_ZFProperty_serializable;
    const ZFMethod *_ZFP_ZFProperty_setterMethod;
    const ZFMethod *_ZFP_ZFProperty_getterMethod;
    const ZFClass *_ZFP_ZFProperty_propertyClassOfRetainProperty;
    _ZFP_ZFPropertyCallbackDealloc _ZFP_ZFProperty_callbackDealloc;
};

// ============================================================
zfclassFwd ZFFilterForZFProperty;
/**
 * @brief get all property currently registered, for debug use only
 */
extern ZF_ENV_EXPORT void ZFPropertyGetAll(ZF_OUT ZFCoreArray<const ZFProperty *> &ret,
                                           ZF_IN_OPT const ZFFilterForZFProperty *propertyFilter = zfnull);
/**
 * @brief get all property currently registered, for debug use only
 */
inline ZFCoreArrayPOD<const ZFProperty *> ZFPropertyGetAll(ZF_IN_OPT const ZFFilterForZFProperty *propertyFilter = zfnull)
{
    ZFCoreArrayPOD<const ZFProperty *> ret;
    ZFPropertyGetAll(ret, propertyFilter);
    return ret;
}

// ============================================================
extern ZF_ENV_EXPORT ZFProperty *_ZFP_ZFPropertyRegister(ZF_IN zfbool propertyIsUserRegister
                                                         , ZF_IN const ZFClass *propertyOwnerClass
                                                         , ZF_IN const zfchar *name
                                                         , ZF_IN const zfchar *typeName
                                                         , ZF_IN const zfchar *typeIdName
                                                         , ZF_IN const ZFMethod *setterMethod
                                                         , ZF_IN const ZFMethod *getterMethod
                                                         , ZF_IN const ZFClass *propertyClassOfRetainProperty
                                                         , ZF_IN ZFPropertyCallbackIsValueAccessed callbackIsValueAccessed
                                                         , ZF_IN ZFPropertyCallbackIsInitValue callbackIsInitValue
                                                         , ZF_IN ZFPropertyCallbackCompare callbackCompare
                                                         , ZF_IN ZFPropertyCallbackCopy callbackCopy
                                                         , ZF_IN ZFPropertyCallbackRetainSet callbackRetainSet
                                                         , ZF_IN ZFPropertyCallbackRetainGet callbackRetainGet
                                                         , ZF_IN ZFPropertyCallbackAssignSet callbackAssignSet
                                                         , ZF_IN ZFPropertyCallbackAssignGet callbackAssignGet
                                                         , ZF_IN ZFPropertyCallbackGetInfo callbackGetInfo
                                                         , ZF_IN ZFPropertyCallbackUserRegisterInitValueSetup callbackUserRegisterInitValueSetup
                                                         , ZF_IN _ZFP_ZFPropertyCallbackDealloc callbackDealloc
                                                         );
extern ZF_ENV_EXPORT void _ZFP_ZFPropertyUnregister(ZF_IN const ZFProperty *propertyInfo);

zfclassLikePOD ZF_ENV_EXPORT _ZFP_ZFPropertyRegisterHolder
{
public:
    _ZFP_ZFPropertyRegisterHolder(ZF_IN zfbool propertyIsUserRegister
                                  , ZF_IN const ZFClass *propertyOwnerClass
                                  , ZF_IN const zfchar *name
                                  , ZF_IN const zfchar *typeName
                                  , ZF_IN const zfchar *typeIdName
                                  , ZF_IN const ZFMethod *setterMethod
                                  , ZF_IN const ZFMethod *getterMethod
                                  , ZF_IN const ZFClass *propertyClassOfRetainProperty
                                  , ZF_IN ZFPropertyCallbackIsValueAccessed callbackIsValueAccessed
                                  , ZF_IN ZFPropertyCallbackIsInitValue callbackIsInitValue
                                  , ZF_IN ZFPropertyCallbackCompare callbackCompare
                                  , ZF_IN ZFPropertyCallbackCopy callbackCopy
                                  , ZF_IN ZFPropertyCallbackRetainSet callbackRetainSet
                                  , ZF_IN ZFPropertyCallbackRetainGet callbackRetainGet
                                  , ZF_IN ZFPropertyCallbackAssignSet callbackAssignSet
                                  , ZF_IN ZFPropertyCallbackAssignGet callbackAssignGet
                                  , ZF_IN ZFPropertyCallbackGetInfo callbackGetInfo
                                  , ZF_IN ZFPropertyCallbackUserRegisterInitValueSetup callbackUserRegisterInitValueSetup
                                  , ZF_IN _ZFP_ZFPropertyCallbackDealloc callbackDealloc
                                  )
    : propertyInfo(_ZFP_ZFPropertyRegister(propertyIsUserRegister
                                           , propertyOwnerClass
                                           , name
                                           , typeName
                                           , typeIdName
                                           , setterMethod
                                           , getterMethod
                                           , propertyClassOfRetainProperty
                                           , callbackIsValueAccessed
                                           , callbackIsInitValue
                                           , callbackCompare
                                           , callbackCopy
                                           , callbackRetainSet
                                           , callbackRetainGet
                                           , callbackAssignSet
                                           , callbackAssignGet
                                           , callbackGetInfo
                                           , callbackUserRegisterInitValueSetup
                                           , callbackDealloc
                                           ))
    {
    }
    ~_ZFP_ZFPropertyRegisterHolder(void)
    {
        _ZFP_ZFPropertyUnregister(this->propertyInfo);
    }
public:
    ZFProperty *propertyInfo;
};

// ============================================================
/** @brief default property callback impl */
template<typename T_Type>
inline ZFCompareResult ZFPropertyCallbackCompareDefault(ZF_IN const ZFProperty *property,
                                                        ZF_IN ZFObject *obj0,
                                                        ZF_IN ZFObject *obj1)
{
    return ZFComparerDefault(
        property->getterMethod()->execute<T_Type const &>(obj0),
        property->getterMethod()->execute<T_Type const &>(obj1));
}

/** @brief default property callback impl */
template<typename T_Type>
inline void ZFPropertyCallbackCopyDefault(ZF_IN const ZFProperty *property,
                                          ZF_IN ZFObject *dstObj,
                                          ZF_IN ZFObject *srcObj)
{
    property->setterMethod()->execute<void, T_Type const &>(dstObj,
        property->getterMethod()->execute<T_Type const &>(srcObj));
}

/** @brief default property callback impl */
template<typename T_Type>
inline void ZFPropertyCallbackRetainSetDefault(ZF_IN const ZFProperty *property,
                                               ZF_IN ZFObject *dstObj,
                                               ZF_IN ZFObject *src)
{
    property->setterMethod()->execute<void, T_Type const &>(dstObj, ZFCastZFObjectUnchecked(T_Type, src));
}

/** @brief default property callback impl */
template<typename T_Type>
inline ZFObject *ZFPropertyCallbackRetainGetDefault(ZF_IN const ZFProperty *property,
                                                    ZF_IN ZFObject *ownerObj)
{
    return ZFCastZFObjectUnchecked(ZFObject *, property->getterMethod()->execute<T_Type const &>(ownerObj));
}

/** @brief default property callback impl */
template<typename T_Type>
inline void ZFPropertyCallbackAssignSetDefault(ZF_IN const ZFProperty *property,
                                               ZF_IN ZFObject *dstObj,
                                               ZF_IN void *src)
{
    property->setterMethod()->execute<void, T_Type const &>(dstObj, *(ZFCastStatic(T_Type *, src)));
}

/** @brief default property callback impl */
template<typename T_Type>
inline const void *ZFPropertyCallbackAssignGetDefault(ZF_IN const ZFProperty *property,
                                                      ZF_IN ZFObject *ownerObj)
{
    return &(property->getterMethod()->execute<T_Type const &>(ownerObj));
}

/** @brief default property callback impl */
template<typename T_Type>
inline void ZFPropertyCallbackGetInfoDefault(ZF_IN const ZFProperty *property,
                                             ZF_IN ZFObject *ownerObj,
                                             ZF_IN_OUT zfstring &ret)
{
    ZFCoreElementInfoGetter<T_Type>::elementInfoGetter(ret,
        property->getterMethod()->execute<T_Type const &>(ownerObj));
}

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFProperty_h_

#include "ZFPropertyDeclare.h"
#include "ZFFilterForZFProperty.h"
#include "ZFPropertyUtil.h"

