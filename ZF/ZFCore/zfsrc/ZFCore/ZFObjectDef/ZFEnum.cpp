/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFEnum.h"
#include "ZFObjectImpl.h"

#include "ZFCore/ZFSTLWrapper/zfstl_map.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
ZF_STATIC_INITIALIZER_INIT(ZFEnumDataHolder)
{
}
ZFCoreMap enumDataMap;
ZF_STATIC_INITIALIZER_END(ZFEnumDataHolder)
#define _ZFP_ZFEnumDataMap (ZF_STATIC_INITIALIZER_INSTANCE(ZFEnumDataHolder)->enumDataMap)

// ============================================================
// ZFEnum
ZFOBJECT_REGISTER(ZFEnum)

zfbool ZFEnum::serializableOnSerializeFromData(ZF_IN const ZFSerializableData &serializableData,
                                               ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */,
                                               ZF_OUT_OPT ZFSerializableData *outErrorPos /* = zfnull */)
{
    if(!zfsuperI(ZFSerializable)::serializableOnSerializeFromData(serializableData, outErrorHint, outErrorPos)) {return zffalse;}

    const zfchar *valueString = ZFSerializableUtil::checkPropertyValue(serializableData);
    if(valueString != zfnull)
    {
        zfuint enumValue = ZFEnumInvalid();
        if(!zfscmpTheSame(valueString, ZFEnumNameInvalid()))
        {
            enumValue = this->enumValueForName(valueString);
            if(enumValue == ZFEnumInvalid())
            {
                ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
                    zfText("invalid value %s for enum %s"), valueString, this->classData()->className());
                return zffalse;
            }
        }
        this->enumValueSet(enumValue);
    }
    else
    {
        this->enumValueSet(ZFEnumInvalid());
    }
    return zftrue;
}
zfbool ZFEnum::serializableOnSerializeToData(ZF_IN_OUT ZFSerializableData &serializableData,
                                             ZF_IN ZFSerializable *referencedOwnerOrNull,
                                             ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */)
{
    if(!zfsuperI(ZFSerializable)::serializableOnSerializeToData(serializableData, referencedOwnerOrNull, outErrorHint)) {return zffalse;}
    zfself *ref = ZFCastZFObject(zfself *, referencedOwnerOrNull);

    if((ref == zfnull && this->enumValue() != ZFEnumInvalid())
        || (ref != zfnull && this->enumValue() != ref->enumValue()))
    {
        serializableData.propertyValueSet(this->enumName());
    }
    return zftrue;
}

ZFObject *ZFEnum::objectOnInit(ZF_IN zfuint value)
{
    this->objectOnInit();
    zfself::enumValueSet(value);
    return this;
}
ZFObject *ZFEnum::objectOnInit(ZF_IN ZFEnum *another)
{
    this->objectOnInit();
    if(another != zfnull && another->classData()->classIsTypeOf(this->classData()))
    {
        zfself::enumValueSet(another->enumValue());
    }
    return this;
}
ZFObject *ZFEnum::objectOnInit(void)
{
    zfsuper::objectOnInit();
    _ZFP_ZFEnum_value = ZFEnumInvalid();
    return this;
}
void ZFEnum::objectOnDealloc(void)
{
    zfsuper::objectOnDealloc();
}

void ZFEnum::objectInfoOnAppend(ZF_IN_OUT zfstring &ret)
{
    ret += this->classData()->className();
    ret += zfText("::");
    ret += this->enumName();
}

ZFCompareResult ZFEnum::objectCompare(ZF_IN ZFObject *anotherObj)
{
    if(this == anotherObj)
    {
        return ZFCompareTheSame;
    }
    if(anotherObj == zfnull || anotherObj->classData() != this->classData())
    {
        return ZFCompareUncomparable;
    }

    zfself *another = ZFCastZFObjectUnchecked(zfself *, anotherObj);
    if(this->enumValue() == ZFEnumInvalid()
        || another->enumValue() == ZFEnumInvalid())
    {
        return ZFCompareUncomparable;
    }
    zfint n = this->enumValue() - another->enumValue();
    if(n < 0)
    {
        return ZFCompareSmaller;
    }
    else if(n == 0)
    {
        return ZFCompareTheSame;
    }
    else
    {
        return ZFCompareGreater;
    }
}

zfclassNotPOD _ZFP_ZFEnumDataPrivate
{
public:
    typedef zfstlmap<zfuint, ZFCoreArrayPOD<zfchar *> > MapType;
    MapType m;
    ZFCoreArrayPOD<zfuint> vl;
    ZFCoreArrayPOD<zfchar *> nl; // for duplicated value, only first stored
public:
    ~_ZFP_ZFEnumDataPrivate(void)
    {
        for(MapType::iterator it = this->m.begin(); it != this->m.end(); ++it)
        {
            for(zfindex j = 0; j < it->second.count(); ++j)
            {
                zffree(it->second[j]);
            }
        }
    }
};
_ZFP_ZFEnumData::_ZFP_ZFEnumData(void)
: needInitFlag(zftrue)
, ownerClass(zfnull)
, d(zfnew(_ZFP_ZFEnumDataPrivate))
{
}
_ZFP_ZFEnumData::~_ZFP_ZFEnumData(void)
{
    zfdelete(d);
    d = zfnull;
}
void _ZFP_ZFEnumData::add(ZF_IN zfbool isEnableDuplicateValue,
                          ZF_IN zfuint value,
                          ZF_IN const zfchar *name)
{
    zfCoreAssert(value != ZFEnumInvalid());
    _ZFP_ZFEnumDataPrivate::MapType::iterator it = d->m.find(value);
    if(it != d->m.end())
    {
        zfCoreAssertWithMessageTrim(isEnableDuplicateValue,
            zfTextA("[ZFEnum] duplicate value %s (new: %s, old: %s) when define %s"),
            zfsFromInt<zfstringA>(value).cString(),
            zfsCoreZ2A(name),
            zfsCoreZ2A(it->second[0]),
            zfsCoreZ2A(this->ownerClass->className()));
        it->second.add(zfsCopy(name));
    }
    else
    {
        zfchar *nameTmp = zfsCopy(name);
        d->m[value].add(nameTmp);
        d->vl.add(value);
        d->nl.add(nameTmp);
    }
}
zfindex _ZFP_ZFEnumData::enumCount(void) const
{
    return d->vl.count();
}
zfindex _ZFP_ZFEnumData::enumIndexForValue(ZF_IN zfuint value) const
{
    return d->vl.find(value);
}
zfuint _ZFP_ZFEnumData::enumValueAtIndex(ZF_IN zfindex index) const
{
    if(index >= d->vl.count())
    {
        return ZFEnumInvalid();
    }
    else
    {
        return d->vl[index];
    }
}
const zfchar *_ZFP_ZFEnumData::enumNameAtIndex(ZF_IN zfindex index) const
{
    if(index >= d->nl.count())
    {
        return zfnull;
    }
    else
    {
        return d->nl[index];
    }
}
zfbool _ZFP_ZFEnumData::enumContainValue(ZF_IN zfuint value) const
{
    return (d->m.find(value) != d->m.end());
}
zfuint _ZFP_ZFEnumData::enumValueForName(ZF_IN const zfchar *name) const
{
    for(zfindex i = 0; i < d->nl.count(); ++i)
    {
        if(zfscmpTheSame(name, d->nl[i]))
        {
            return d->vl[i];
        }
    }
    return ZFEnumInvalid();
}
const zfchar *_ZFP_ZFEnumData::enumNameForValue(ZF_IN zfuint value) const
{
    _ZFP_ZFEnumDataPrivate::MapType::const_iterator it = d->m.find(value);
    if(it != d->m.end())
    {
        return it->second[0];
    }
    else
    {
        return ZFEnumNameInvalid();
    }
}

_ZFP_ZFEnumData *_ZFP_ZFEnumDataAccess(ZF_IN const ZFClass *ownerClass)
{
    zfCoreMutexLocker();
    _ZFP_ZFEnumData *d = _ZFP_ZFEnumDataMap.get<_ZFP_ZFEnumData *>(ownerClass->className());
    if(d != zfnull)
    {
        return d;
    }
    d = zfnew(_ZFP_ZFEnumData);
    _ZFP_ZFEnumDataMap.set(ownerClass->className(), ZFCorePointerForObject<_ZFP_ZFEnumData *>(d));
    d->ownerClass = ownerClass;
    return d;
}

// ============================================================
// zfflags conversion
zfclass _ZFP_I_ZFEnum_stringConverterDataHolder : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_I_ZFEnum_stringConverterDataHolder, ZFObject)

public:
    zfindex enumCount;
    zfflags *flagList;
    const zfchar **nameList;

public:
    static _ZFP_I_ZFEnum_stringConverterDataHolder *setup(ZF_IN const ZFClass *enumClass)
    {
        _ZFP_I_ZFEnum_stringConverterDataHolder *ret = enumClass->classTagGet<_ZFP_I_ZFEnum_stringConverterDataHolder *>(_ZFP_I_ZFEnum_stringConverterDataHolder::ClassData()->className());
        if(ret == zfnull)
        {
            const ZFMethod *enumCountMethod = enumClass->methodForName(zfText("EnumCount"));
            const ZFMethod *enumValueAtIndexMethod = enumClass->methodForName(zfText("EnumValueAtIndex"));
            const ZFMethod *enumNameAtIndexMethod = enumClass->methodForName(zfText("EnumNameAtIndex"));
            zfCoreAssert(enumCountMethod != zfnull && enumValueAtIndexMethod != zfnull && enumNameAtIndexMethod != zfnull);

            ret = zfAllocWithoutLeakTest(_ZFP_I_ZFEnum_stringConverterDataHolder);
            enumClass->classTagSet(_ZFP_I_ZFEnum_stringConverterDataHolder::ClassData()->className(), ret);
            zfReleaseWithoutLeakTest(ret);

            ret->enumCount = enumCountMethod->executeStatic<zfindex>();
            ret->flagList = (zfflags *)zfmalloc(sizeof(zfflags) * ret->enumCount);
            ret->nameList = (const zfchar **)zfmalloc(sizeof(const zfchar *) * ret->enumCount);
            for(zfindex i = 0; i < ret->enumCount; ++i)
            {
                ret->flagList[i] = enumValueAtIndexMethod->executeStatic<zfuint, zfindex>(i);
                ret->nameList[i] = enumNameAtIndexMethod->executeStatic<const zfchar *, zfindex>(i);
            }
        }
        return ret;
    }

public:
    virtual void objectOnDealloc(void)
    {
        zffree(this->flagList);
        this->flagList = zfnull;
        zffree(this->nameList);
        this->nameList = zfnull;
        zfsuper::objectOnDealloc();
    }
};
zfbool zfflagsToString(ZF_IN_OUT zfstring &ret,
                       ZF_IN const ZFClass *enumClass,
                       ZF_IN zfflags const &value,
                       ZF_IN_OPT zfbool includeNotConverted /* = zftrue */,
                       ZF_IN_OPT zfbool exclusiveMode /* = zffalse */,
                       ZF_OUT_OPT zfflags *notConverted /* = zfnull */,
                       ZF_IN_OPT zfchar separatorToken /* = '|' */)
{
    zfCoreMutexLocker();
    if(enumClass != zfnull && enumClass->classIsTypeOf(ZFEnum::ClassData()))
    {
        _ZFP_I_ZFEnum_stringConverterDataHolder *d = _ZFP_I_ZFEnum_stringConverterDataHolder::setup(enumClass);
        return zfflagsToString(ret,
            d->flagList, d->nameList, d->enumCount,
            value,
            includeNotConverted, exclusiveMode, notConverted, separatorToken);
    }
    else
    {
        return zfflagsToString(ret,
            zfnull, zfnull, 0,
            value,
            includeNotConverted, exclusiveMode, notConverted, separatorToken);
    }
}
zfbool zfflagsFromString(ZF_OUT zfflags &ret,
                         ZF_IN const ZFClass *enumClass,
                         ZF_IN const zfchar *src,
                         ZF_IN_OPT zfindex srcLen /* = zfindexMax() */,
                         ZF_IN_OPT zfchar separatorToken /* = '|' */,
                         ZF_OUT_OPT const zfchar **outErrorPos /* = zfnull */)
{
    zfCoreMutexLocker();
    if(enumClass != zfnull && enumClass->classIsTypeOf(ZFEnum::ClassData()))
    {
        _ZFP_I_ZFEnum_stringConverterDataHolder *d = _ZFP_I_ZFEnum_stringConverterDataHolder::setup(enumClass);
        return zfflagsFromString(
            ret,
            d->flagList, d->nameList, d->enumCount,
            src, srcLen, separatorToken,
            outErrorPos);
    }
    else
    {
        return zfflagsFromString(
            ret,
            zfnull, zfnull, 0,
            src, srcLen, separatorToken,
            outErrorPos);
    }
}

ZFOUTPUT_TYPE_DEFINE(ZFEnumFlagsBase, {output << v.objectInfo();})

// ============================================================
zfbool ZFEnumWrapperInfo(ZF_OUT const ZFClass *&enumClass,
                         ZF_OUT zfuint &enumValue,
                         ZF_IN ZFPropertyTypeWrapper *enumWrapper)
{
    if(enumWrapper == zfnull)
    {
        return zffalse;
    }
    const ZFMethod *m = enumWrapper->classData()->methodForName(zfText("_ZFP_ZFEnumWrapperInfo"));
    if(m == zfnull)
    {
        return zffalse;
    }
    return m->executeStatic<zfbool, const ZFClass *&, zfuint &, ZFPropertyTypeWrapper *>(enumClass, enumValue, enumWrapper);
}

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFEnum, zfindex, enumCount)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFEnum, zfindex, enumIndexForValue, ZFMP_IN(zfuint, value))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFEnum, zfuint, enumValueAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFEnum, const zfchar *, enumNameAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFEnum, zfbool, enumContainValue, ZFMP_IN(zfuint, value))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFEnum, zfuint, enumValueForName, ZFMP_IN(const zfchar *, name))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFEnum, const zfchar *, enumNameForValue, ZFMP_IN(zfuint, value))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFEnum, zfuint, enumValue)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFEnum, const zfchar *, enumName)
static void _ZFP_ZFEnum_enumValueSet_methodInvoker(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfuint value)
{
    invokerObject->to<ZFEnum *>()->_ZFP_ZFEnum_enumValueSet(value);
}
ZFMETHOD_USER_REGISTER_DETAIL_1(ZFEnum_enumValueSet, _ZFP_ZFEnum_enumValueSet_methodInvoker, ZFEnum::ClassData(), protected, ZFMethodIsVirtual, void, zfText("enumValueSet"), ZFMP_IN(zfuint, value))

ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_7(zfbool, zfflagsToString, ZFMP_IN_OUT(zfstring &, ret), ZFMP_IN(const ZFClass *, enumClass), ZFMP_IN(zfflags const &, value), ZFMP_IN_OPT(zfbool, includeNotConverted, zftrue), ZFMP_IN_OPT(zfbool, exclusiveMode, zffalse), ZFMP_OUT_OPT(zfflags *, notConverted, zfnull), ZFMP_IN_OPT(zfchar, separatorToken, '|'))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_6(zfstring, zfflagsToString, ZFMP_IN(const ZFClass *, enumClass), ZFMP_IN(zfflags const &, value), ZFMP_IN_OPT(zfbool, includeNotConverted, zftrue), ZFMP_IN_OPT(zfbool, exclusiveMode, zffalse), ZFMP_OUT_OPT(zfflags *, notConverted, zfnull), ZFMP_IN_OPT(zfchar, separatorToken, '|'))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_5(zfbool, zfflagsFromString, ZFMP_OUT(zfflags &, ret), ZFMP_IN(const ZFClass *, enumClass), ZFMP_IN(const zfchar *, src), ZFMP_IN_OPT(zfindex, srcLen, zfindexMax()), ZFMP_IN_OPT(zfchar, separatorToken, '|'))

ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_3(zfbool, ZFEnumWrapperInfo, ZFMP_OUT(const ZFClass *&, enumClass), ZFMP_OUT(zfuint &, enumValue), ZFMP_IN(ZFPropertyTypeWrapper *, enumWrapper))

ZF_NAMESPACE_GLOBAL_END
#endif

