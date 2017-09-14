/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFPropertyType_Core.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
zfclassNotPOD _ZFP_ZFPropertyTypeData
{
public:
    ZFPropertyTypeSerializeFromCallback serializeFromCallback;
    ZFPropertyTypeSerializeToCallback serializeToCallback;
};

ZF_STATIC_INITIALIZER_INIT(ZFPropertyTypeIdHolder)
{
}
public:
    ZFCoreMap propertyTypeMap; // _ZFP_ZFPropertyTypeData
ZF_STATIC_INITIALIZER_END(ZFPropertyTypeIdHolder)
#define _ZFP_ZFPropertyTypeMap (ZF_STATIC_INITIALIZER_INSTANCE(ZFPropertyTypeIdHolder)->propertyTypeMap)

// ============================================================
void _ZFP_ZFPropertyTypeRegister(ZF_IN const zfchar *typeIdName,
                                 ZF_IN ZFPropertyTypeSerializeFromCallback serializeFromCallback,
                                 ZF_IN ZFPropertyTypeSerializeToCallback serializeToCallback)
{
    zfCoreAssert(typeIdName != zfnull);
    _ZFP_ZFPropertyTypeData *type = zfnew(_ZFP_ZFPropertyTypeData);
    type->serializeFromCallback = serializeFromCallback;
    type->serializeToCallback = serializeToCallback;
    _ZFP_ZFPropertyTypeMap.set(typeIdName, ZFCorePointerForObject<_ZFP_ZFPropertyTypeData *>(type));
}
void _ZFP_ZFPropertyTypeUnregister(ZF_IN const zfchar *typeIdName)
{
    _ZFP_ZFPropertyTypeMap.remove(typeIdName);
}
ZFPropertyTypeSerializeFromCallback ZFPropertyTypeGetSerializeFromCallback(ZF_IN const zfchar *typeIdName)
{
    _ZFP_ZFPropertyTypeData *typeData = _ZFP_ZFPropertyTypeMap.get<_ZFP_ZFPropertyTypeData *>(typeIdName);
    return ((typeData != zfnull) ? typeData->serializeFromCallback : zfnull);
}
ZFPropertyTypeSerializeToCallback ZFPropertyTypeGetSerializeToCallback(ZF_IN const zfchar *typeIdName)
{
    _ZFP_ZFPropertyTypeData *typeData = _ZFP_ZFPropertyTypeMap.get<_ZFP_ZFPropertyTypeData *>(typeIdName);
    return ((typeData != zfnull) ? typeData->serializeToCallback : zfnull);
}

zfbool ZFPropertySerializeFrom(ZF_IN ZFObject *ownerObject,
                               ZF_IN const ZFSerializableData &serializableData,
                               ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */,
                               ZF_OUT_OPT ZFSerializableData *outErrorPos /* = zfnull */)
{
    if(ownerObject == zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("null object"));
        return zffalse;
    }

    const zfchar *propertyName = ZFSerializableUtil::requirePropertyName(serializableData, outErrorHint, outErrorPos);
    if(propertyName == zfnull)
    {
        return zffalse;
    }
    const ZFProperty *property = ownerObject->classData()->propertyForName(propertyName);
    if(property == zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("no property named \"%s\" for object %s"),
            propertyName, ownerObject->objectInfoOfInstance().cString());
        return zffalse;
    }
    if(property->propertyIsRetainProperty())
    {
        zfautoObject obj;
        if(!ZFObjectFromData(obj, serializableData, outErrorHint, outErrorPos))
        {
            return zffalse;
        }
        if(obj != zfautoObjectNull() && !obj.toObject()->classData()->classIsTypeOf(property->propertyClassOfRetainProperty()))
        {
            ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
                zfText("object %s not type of %s"),
                obj.toObject()->objectInfoOfInstance().cString(), property->propertyClassOfRetainProperty()->className());
            return zffalse;
        }
        property->callbackRetainSet(property, ownerObject, obj.toObject());
        return zftrue;
    }

    ZFPropertyTypeSerializeFromCallback serializeFromCallback = ZFPropertyTypeGetSerializeFromCallback(serializableData.itemClass());
    if(serializeFromCallback == zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("type \"%s\" not registered while serializing \"%s\""),
            serializableData.itemClass(),
            ownerObject->classData()->className());
        return zffalse;
    }
    return serializeFromCallback(property, ownerObject, serializableData, outErrorHint, outErrorPos);
}
zfbool ZFPropertySerializeTo(ZF_IN const ZFProperty *propertyInfo,
                             ZF_IN ZFObject *ownerObject,
                             ZF_OUT ZFSerializableData &serializableData,
                             ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */)
{
    if(ownerObject == zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint,
            zfText("null object"));
        return zffalse;
    }
    if(propertyInfo == zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint,
            zfText("null property"));
        return zffalse;
    }
    if(propertyInfo->propertyIsRetainProperty())
    {
        ZFObject *obj = propertyInfo->callbackRetainGet(propertyInfo, ownerObject);
        if(!ZFObjectToData(serializableData, obj, outErrorHint))
        {
            return zffalse;
        }
        serializableData.propertyNameSet(propertyInfo->propertyName());
        return zftrue;
    }

    ZFPropertyTypeSerializeToCallback serializeToCallback = ZFPropertyTypeGetSerializeToCallback(propertyInfo->propertyTypeId());
    if(serializeToCallback == zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint,
            zfText("type \"%s\" not registered while serializing \"%s\""),
            propertyInfo->propertyTypeId(),
            ownerObject->classData()->className());
        return zffalse;
    }
    return serializeToCallback(propertyInfo, ownerObject, serializableData, outErrorHint);
}

// ============================================================
ZFOBJECT_REGISTER(ZFPropertyTypeWrapper)

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_4(zfbool, ZFPropertySerializeFrom, ZFMP_IN(ZFObject *, ownerObject), ZFMP_IN(const ZFSerializableData &, serializableData), ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull), ZFMP_OUT_OPT(ZFSerializableData *, outErrorPos, zfnull))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_4(zfbool, ZFPropertySerializeTo, ZFMP_IN(const ZFProperty *, propertyInfo), ZFMP_IN(ZFObject *, ownerObject), ZFMP_OUT(ZFSerializableData &, serializableData), ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull))

ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFPropertyTypeWrapper, const zfchar *, wrappedValueTypeId)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFPropertyTypeWrapper, void, wrappedValueReset)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFPropertyTypeWrapper, zfbool, wrappedValueIsInit)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_3(ZFPropertyTypeWrapper, zfbool, wrappedValueFromData, ZFMP_IN(const ZFSerializableData &, serializableData), ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull), ZFMP_OUT_OPT(ZFSerializableData *, outErrorPos, zfnull))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_2(ZFPropertyTypeWrapper, zfbool, wrappedValueToData, ZFMP_OUT(ZFSerializableData &, serializableData), ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_2(ZFPropertyTypeWrapper, zfbool, wrappedValueFromString, ZFMP_IN(const zfchar *, src), ZFMP_IN_OPT(zfindex, srcLen, zfindexMax()))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFPropertyTypeWrapper, zfbool, wrappedValueToString, ZFMP_IN_OUT(zfstring &, s))

ZF_NAMESPACE_GLOBAL_END
#endif

