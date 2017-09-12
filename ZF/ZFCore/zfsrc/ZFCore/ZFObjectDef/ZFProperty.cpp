/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFProperty.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
void ZFProperty::objectInfoT(ZF_IN_OUT zfstring &ret) const
{
    ret += '(';
    if(zfslen(this->propertyTypeId()) > 0)
    {
        ret += this->propertyTypeId();
    }
    else
    {
        ret += this->propertyTypeName();
    }
    ret += ')';
    ret += this->propertyOwnerClass()->className();
    ret += zfText("::");
    ret += this->propertyName();
}

/** @cond ZFPrivateDoc */
ZFProperty::ZFProperty(void)
: callbackIsValueAccessed(zfnull)
, callbackIsInitValue(zfnull)
, callbackCompare(zfnull)
, callbackCopy(zfnull)
, callbackRetainSet(zfnull)
, callbackRetainGet(zfnull)
, callbackAssignSet(zfnull)
, callbackAssignGet(zfnull)
, callbackGetInfo(zfnull)
, callbackUserRegisterInitValueSetup(zfnull)
, _ZFP_ZFPropertyNeedInit(zftrue)
, _ZFP_ZFProperty_propertyIsUserRegister(zffalse)
, _ZFP_ZFProperty_propertyOwnerClass(zfnull)
, _ZFP_ZFProperty_name()
, _ZFP_ZFProperty_typeName()
, _ZFP_ZFProperty_typeId()
, _ZFP_ZFProperty_setterMethod(zfnull)
, _ZFP_ZFProperty_getterMethod(zfnull)
, _ZFP_ZFProperty_propertyClassOfRetainProperty(zfnull)
, _ZFP_ZFProperty_callbackDealloc(zfnull)
, _ZFP_ZFProperty_cbCustomOnInit(zfnull)
, _ZFP_ZFProperty_cbCustomOnDealloc(zfnull)
, _ZFP_ZFProperty_cbCustomOnVerify(zfnull)
, _ZFP_ZFProperty_cbCustomOnAttach(zfnull)
, _ZFP_ZFProperty_cbCustomOnDetach(zfnull)
, _ZFP_ZFProperty_cbCustomOnUpdate(zfnull)
{
}
ZFProperty::~ZFProperty(void)
{
}
/** @endcond */
void ZFProperty::_ZFP_ZFPropertyInit(ZF_IN zfbool propertyIsUserRegister,
                                     ZF_IN const ZFClass *propertyOwnerClass,
                                     ZF_IN const zfchar *name,
                                     ZF_IN const zfchar *typeName,
                                     ZF_IN const zfchar *typeIdName,
                                     ZF_IN const ZFMethod *setterMethod,
                                     ZF_IN const ZFMethod *getterMethod,
                                     ZF_IN const ZFClass *propertyClassOfRetainProperty)
{
    this->_ZFP_ZFProperty_propertyIsUserRegister = propertyIsUserRegister;
    this->_ZFP_ZFProperty_propertyOwnerClass = propertyOwnerClass;
    this->_ZFP_ZFProperty_name = name;
    this->_ZFP_ZFProperty_typeName = typeName;
    if(propertyClassOfRetainProperty == zfnull && zfscmpTheSame(typeIdName, ZFPropertyTypeId_ZFObject))
    { // assign property with ZFObject type, is not serializable
        this->_ZFP_ZFProperty_typeId = ZFPropertyTypeId_none;
    }
    else
    {
        this->_ZFP_ZFProperty_typeId = typeIdName;
    }
    this->_ZFP_ZFProperty_serializable = (this->_ZFP_ZFProperty_typeId.compare(ZFPropertyTypeId_none) != 0);
    this->_ZFP_ZFProperty_setterMethod = setterMethod;
    this->_ZFP_ZFProperty_getterMethod = getterMethod;
    this->_ZFP_ZFProperty_propertyClassOfRetainProperty = propertyClassOfRetainProperty;
}

// ============================================================
zfclassLikePOD _ZFP_ZFPropertyMapData
{
public:
    zfindex refCount;
    ZFProperty propertyInfo;
public:
    _ZFP_ZFPropertyMapData(void)
    : refCount(1)
    , propertyInfo()
    {
    }
};
ZF_STATIC_INITIALIZER_INIT(ZFPropertyDataHolder)
{
}
ZFCoreMap propertyMap; // _ZFP_ZFPropertyMapData *
ZF_STATIC_INITIALIZER_END(ZFPropertyDataHolder)
#define _ZFP_ZFPropertyMap (ZF_STATIC_INITIALIZER_INSTANCE(ZFPropertyDataHolder)->propertyMap)

// ============================================================
void ZFPropertyGetAll(ZF_OUT ZFCoreArray<const ZFProperty *> &ret,
                      ZF_IN_OPT const ZFFilterForZFProperty *propertyFilter /* = zfnull */)
{
    zfCoreMutexLocker();
    const ZFCoreMap &m = _ZFP_ZFPropertyMap;
    if(propertyFilter != zfnull)
    {
        for(zfiterator it = m.iterator(); m.iteratorIsValid(it); )
        {
            _ZFP_ZFPropertyMapData *v = m.iteratorNextValue<_ZFP_ZFPropertyMapData *>(it);
            if(propertyFilter->filterCheckActive(&(v->propertyInfo)))
            {
                ret.add(&(v->propertyInfo));
            }
        }
    }
    else
    {
        for(zfiterator it = m.iterator(); m.iteratorIsValid(it); )
        {
            _ZFP_ZFPropertyMapData *v = m.iteratorNextValue<_ZFP_ZFPropertyMapData *>(it);
            ret.add(&(v->propertyInfo));
        }
    }
}

// ============================================================
static void _ZFP_ZFPropertyInstanceSig(ZF_OUT zfstring &ret,
                                       ZF_IN const zfchar *className,
                                       ZF_IN const zfchar *propertyName)
{
    if(className)
    {
        ret += className;
    }
    ret += ':';
    if(propertyName)
    {
        ret += propertyName;
    }
}
static ZFProperty *_ZFP_ZFPropertyInstanceFind(ZF_IN const zfchar *propertyInternalId)
{
    zfCoreMutexLocker();
    _ZFP_ZFPropertyMapData *v = _ZFP_ZFPropertyMap.get<_ZFP_ZFPropertyMapData *>(propertyInternalId);
    if(v == zfnull)
    {
        return zfnull;
    }
    else
    {
        return &(v->propertyInfo);
    }
}
static ZFProperty *_ZFP_ZFPropertyInstanceAccess(ZF_IN const zfchar *propertyInternalId)
{
    zfCoreMutexLocker();
    _ZFP_ZFPropertyMapData *v = _ZFP_ZFPropertyMap.get<_ZFP_ZFPropertyMapData *>(propertyInternalId);
    if(v == zfnull)
    {
        v = zfnew(_ZFP_ZFPropertyMapData);
        _ZFP_ZFPropertyMap.set(propertyInternalId, ZFCorePointerForObject<_ZFP_ZFPropertyMapData *>(v));
        v->propertyInfo._ZFP_ZFProperty_propertyInternalId = propertyInternalId;
    }
    else
    {
        ++(v->refCount);
    }
    return &(v->propertyInfo);
}
static zfbool _ZFP_ZFPropertyInstanceCleanup(ZF_IN const ZFProperty *property)
{
    zfCoreMutexLocker();
    _ZFP_ZFPropertyMapData *v = _ZFP_ZFPropertyMap.get<_ZFP_ZFPropertyMapData *>(property->propertyInternalId());
    if(v == zfnull)
    {
        return zffalse;
    }
    --(v->refCount);
    if(v->refCount == 0)
    {
        _ZFP_ZFPropertyMap.remove(property->propertyInternalId());
    }
    return zftrue;
}

ZFProperty *_ZFP_ZFPropertyRegister(ZF_IN zfbool propertyIsUserRegister
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
{
    zfCoreMutexLocker();
    ZFProperty *propertyInfo = zfnull;

    zfCoreAssert(propertyOwnerClass != zfnull);
    zfCoreAssert(name != zfnull && *name != '\0');
    zfCoreAssert(typeName != zfnull && *typeName != '\0');
    zfCoreAssert(typeIdName != zfnull && *typeIdName != '\0');
    zfCoreAssert(setterMethod != zfnull);
    zfCoreAssert(getterMethod != zfnull);
    zfCoreAssert(callbackIsValueAccessed != zfnull);
    zfCoreAssert(callbackIsInitValue != zfnull);
    zfCoreAssert(callbackCompare != zfnull);
    zfCoreAssert(callbackCopy != zfnull);
    zfCoreAssert((callbackRetainSet != zfnull && callbackRetainGet != zfnull)
        || (callbackAssignSet != zfnull && callbackAssignGet != zfnull));
    zfCoreAssert(callbackGetInfo != zfnull);

    zfstring propertyInternalId;
    _ZFP_ZFPropertyInstanceSig(propertyInternalId, propertyOwnerClass->className(), name);

    if(propertyIsUserRegister)
    {
        propertyInfo = _ZFP_ZFPropertyInstanceFind(propertyInternalId);
        zfCoreAssertWithMessageTrim(propertyInfo == zfnull,
            zfTextA("[ZFPropertyUserRegister] registering a property that already registered, class: %s, propertyName: %s"),
            zfsCoreZ2A(propertyOwnerClass->className()),
            zfsCoreZ2A(name));
    }
    propertyInfo = _ZFP_ZFPropertyInstanceAccess(propertyInternalId);

    if(propertyInfo->_ZFP_ZFPropertyNeedInit)
    {
        propertyInfo->_ZFP_ZFPropertyNeedInit = zffalse;
        propertyInfo->_ZFP_ZFPropertyInit(
            propertyIsUserRegister,
            propertyOwnerClass,
            name,
            typeName,
            typeIdName,
            setterMethod,
            getterMethod,
            propertyClassOfRetainProperty);
        propertyInfo->callbackIsValueAccessed = callbackIsValueAccessed;
        propertyInfo->callbackIsInitValue = callbackIsInitValue;
        propertyInfo->callbackCompare = callbackCompare;
        propertyInfo->callbackCopy = callbackCopy;
        propertyInfo->callbackRetainSet = callbackRetainSet;
        propertyInfo->callbackRetainGet = callbackRetainGet;
        propertyInfo->callbackAssignSet = callbackAssignSet;
        propertyInfo->callbackAssignGet = callbackAssignGet;
        propertyInfo->callbackGetInfo = callbackGetInfo;
        propertyInfo->callbackUserRegisterInitValueSetup = callbackUserRegisterInitValueSetup;
        propertyInfo->_ZFP_ZFProperty_callbackDealloc = callbackDealloc;

        propertyOwnerClass->_ZFP_ZFClass_removeConst()->_ZFP_ZFClass_propertyRegister(propertyInfo);
        _ZFP_ZFClassDataChangeNotify(ZFClassDataChangeTypeAttach, zfnull, propertyInfo, zfnull);
    }

    return propertyInfo;
}
void _ZFP_ZFPropertyUnregister(ZF_IN const ZFProperty *propertyInfo)
{
    zfCoreMutexLocker();
    _ZFP_ZFClassDataChangeNotify(ZFClassDataChangeTypeDetach, zfnull, propertyInfo, zfnull);

    if(propertyInfo->propertyIsUserRegister())
    {
        ZFMethodUserUnregister(propertyInfo->setterMethod());
        ZFMethodUserUnregister(propertyInfo->getterMethod());
        propertyInfo->propertyOwnerClass()->_ZFP_ZFClass_removeConst()->_ZFP_ZFClass_propertyUnregister(propertyInfo);
    }

    _ZFP_ZFPropertyInstanceCleanup(propertyInfo);
}

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFProperty, const zfchar *, propertyInternalId)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFProperty, zfbool, propertyIsUserRegister)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFProperty, const ZFClass *, propertyOwnerClass)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFProperty, const zfchar *, propertyName)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFProperty, const zfchar *, propertyTypeName)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFProperty, const zfchar *, propertyTypeId)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFProperty, zfbool, propertyIsSerializable)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFProperty, const ZFMethod *, setterMethod)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFProperty, const ZFMethod *, getterMethod)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFProperty, zfbool, propertyIsRetainProperty)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFProperty, const ZFClass *, propertyClassOfRetainProperty)

ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(void, ZFPropertyGetAll, ZFMP_OUT(ZFCoreArray<const ZFProperty *> &, ret), ZFMP_IN_OPT(const ZFFilterForZFProperty *, propertyFilter, zfnull))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(ZFCoreArrayPOD<const ZFProperty *>, ZFPropertyGetAll, ZFMP_IN_OPT(const ZFFilterForZFProperty *, propertyFilter, zfnull))

ZF_NAMESPACE_GLOBAL_END
#endif

