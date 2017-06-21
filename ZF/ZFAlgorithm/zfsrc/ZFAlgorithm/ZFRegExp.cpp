/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFRegExp.h"
#include "protocol/ZFProtocolZFRegExp.h"

ZF_NAMESPACE_GLOBAL_BEGIN

void ZFRegExpResult::objectInfoT(ZF_IN_OUT zfstring &ret) const
{
    ret += ZFTOKEN_ZFObjectInfoLeft;
    if(this->matched)
    {
        ret += zfText("matched");
        if(this->matchedRange != zfindexRangeZero())
        {
            ret += zfText(" in ");
            zfindexRangeToString(ret, this->matchedRange);
        }
        if(!this->namedGroups.isEmpty())
        {
            ret += zfText(", named groups: ");
            for(zfindex i = 0; i < this->namedGroups.count(); ++i)
            {
                if(i != 0)
                {
                    ret += zfText(", ");
                }
                zfindexRangeToString(ret, this->namedGroups[i]);
            }
        }
    }
    else
    {
        ret += zfText("no match");
    }
    ret += ZFTOKEN_ZFObjectInfoRight;
}

ZFPROPERTY_TYPE_DEFINE_BY_SERIALIZABLE_CONVERTER(ZFRegExpResult, ZFRegExpResult, {
        if(ZFSerializableUtil::requireSerializableClass(ZFPropertyTypeId_ZFRegExpResult(), serializableData, outErrorHint, outErrorPos) == zfnull)
        {
            return zffalse;
        }

        const ZFSerializableData *element = zfnull;

        v.matched = zffalse;
        element = ZFSerializableUtil::checkElementByName(serializableData, ZFSerializableKeyword_ZFRegExpResult_matched);
        if(element != zfnull && !zfboolFromSerializableData(v.matched, *element, outErrorHint, outErrorPos))
        {
            return zffalse;
        }

        v.matchedRange = zfindexRangeZero();
        element = ZFSerializableUtil::checkElementByName(serializableData, ZFSerializableKeyword_ZFRegExpResult_matchedRange);
        if(element != zfnull && !zfindexRangeFromSerializableData(v.matchedRange, serializableData, outErrorHint, outErrorPos))
        {
            return zffalse;
        }

        v.namedGroups.removeAll();
        element = ZFSerializableUtil::checkElementByName(serializableData, ZFSerializableKeyword_ZFRegExpResult_namedGroups);
        if(element != zfnull && !ZFPropertyTypeIdData<ZFCoreArrayPOD<zfindexRange> >::PropertyFromSerializableData(v.namedGroups, serializableData, outErrorHint, outErrorPos))
        {
            return zffalse;
        }
        return zftrue;
    }, {
        serializableData.itemClassSet(ZFPropertyTypeId_ZFRegExpResult());

        if(v.matched)
        {
            ZFSerializableData element;
            if(!zfboolToSerializableData(element, v.matched, outErrorHint))
            {
                return zffalse;
            }
            element.propertyNameSet(ZFSerializableKeyword_ZFRegExpResult_matched);
            serializableData.elementAdd(element);
        }

        if(v.matchedRange != zfindexRangeZero())
        {
            ZFSerializableData element;
            if(!zfindexRangeToSerializableData(element, v.matchedRange, outErrorHint))
            {
                return zffalse;
            }
            element.propertyNameSet(ZFSerializableKeyword_ZFRegExpResult_matchedRange);
            serializableData.elementAdd(element);
        }

        if(!v.namedGroups.isEmpty())
        {
            ZFSerializableData element;
            if(!ZFCoreArrayToSerializableData(element, v.namedGroups, outErrorHint))
            {
                return zffalse;
            }
            element.propertyNameSet(ZFSerializableKeyword_ZFRegExpResult_namedGroups);
            serializableData.elementAdd(element);
        }

        return zftrue;
    })

ZFMETHOD_USER_REGISTER_0({return invokerObject->to<v_ZFRegExpResult *>()->zfv.matched;}, v_ZFRegExpResult, zfbool, matched)
ZFMETHOD_USER_REGISTER_0({return invokerObject->to<v_ZFRegExpResult *>()->zfv.matchedRange;}, v_ZFRegExpResult, zfindexRange, matchedRange)
ZFMETHOD_USER_REGISTER_0({return invokerObject->to<v_ZFRegExpResult *>()->zfv.namedGroups;}, v_ZFRegExpResult, ZFCoreArrayPOD<zfindexRange>, namedGroups)

// ============================================================
// global
ZFENUM_DEFINE(ZFRegExpOption)
ZFENUM_FLAGS_DEFINE(ZFRegExpOption, ZFRegExpOptionFlags)

// ============================================================
// _ZFP_ZFRegExpPrivate
zfclassNotPOD _ZFP_ZFRegExpPrivate
{
public:
    void *nativeRegExp;
    zfstring pattern;
    ZFRegExpOptionFlags flag;

public:
    _ZFP_ZFRegExpPrivate(void)
    : nativeRegExp(zfnull)
    , pattern()
    , flag()
    {
    }
};

// ============================================================
// ZFRegExp
ZFOBJECT_REGISTER(ZFRegExp)

zfbool ZFRegExp::serializableOnSerializeFromData(ZF_IN const ZFSerializableData &serializableData,
                                                 ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */,
                                                 ZF_OUT_OPT ZFSerializableData *outErrorPos /* = zfnull */)
{
    if(!zfsuperI(ZFSerializable)::serializableOnSerializeFromData(serializableData, outErrorHint, outErrorPos)) {return zffalse;}

    const zfchar *pattern = zfnull;
    ZFSerializableUtilSerializeAttributeFromData(serializableData, outErrorHint, outErrorPos,
        check, ZFSerializableKeyword_ZFRegExp_pattern, zfstring, pattern);

    ZFRegExpOptionFlags flag = ZFRegExpOptionFlags::EnumDefault();
    ZFSerializableUtilSerializeAttributeFromData(serializableData, outErrorHint, outErrorPos,
        check, ZFSerializableKeyword_ZFRegExp_flag, ZFRegExpOptionFlags, flag);

    this->regExpCompile(pattern ? pattern : zfText(""), flag);

    return zftrue;
}
zfbool ZFRegExp::serializableOnSerializeToData(ZF_IN_OUT ZFSerializableData &serializableData,
                                               ZF_IN ZFSerializable *referencedOwnerOrNull,
                                               ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */)
{
    if(!zfsuperI(ZFSerializable)::serializableOnSerializeToData(serializableData, referencedOwnerOrNull, outErrorHint)) {return zffalse;}
    zfself *ref = ZFCastZFObject(zfself *, referencedOwnerOrNull);

    ZFSerializableUtilSerializeAttributeToData(serializableData, outErrorHint, ref,
        ZFSerializableKeyword_ZFRegExp_pattern, zfstring, this->regExpPattern(), ref->regExpPattern(), zfText(""));

    ZFSerializableUtilSerializeAttributeToData(serializableData, outErrorHint, ref,
        ZFSerializableKeyword_ZFRegExp_flag, ZFRegExpOptionFlags, this->regExpFlag(), ref->regExpFlag(), ZFRegExpOptionFlags::EnumDefault());

    return zftrue;
}

ZFObject *ZFRegExp::objectOnInit(ZF_IN const zfchar *pattern,
                                 ZF_IN_OPT ZFRegExpOptionFlags flag /* = ZFRegExpOptionFlags::EnumDefault() */)
{
    this->objectOnInit();
    zfself::regExpCompile(pattern, flag);
    return this;
}
ZFObject *ZFRegExp::objectOnInit(void)
{
    zfsuper::objectOnInit();
    d = zfpoolNew(_ZFP_ZFRegExpPrivate);
    d->nativeRegExp = ZFPROTOCOL_ACCESS(ZFRegExp)->nativeRegExpCreate(this);
    return this;
}
void ZFRegExp::objectOnDealloc(void)
{
    ZFPROTOCOL_ACCESS(ZFRegExp)->nativeRegExpDestroy(this, d->nativeRegExp);
    zfpoolDelete(d);
    d = zfnull;
    zfsuper::objectOnDealloc();
}

void ZFRegExp::objectInfoOnAppend(ZF_IN_OUT zfstring &ret)
{
    zfsuper::objectInfoOnAppend(ret);
    ZFClassUtil::objectPropertyInfo(ret, this);
}

zfidentity ZFRegExp::objectHash(void)
{
    ZFRegExpOptionFlags flag = this->regExpFlag();
    return zfidentityHash(zfidentityCalcString(this->regExpPattern()),
                         zfidentityCalcPOD(flag));
}
ZFCompareResult ZFRegExp::objectCompare(ZF_IN ZFObject *anotherObj)
{
    if(this == anotherObj) {return ZFCompareTheSame;}
    zfself *another = ZFCastZFObject(zfself *, anotherObj);
    if(another == zfnull) {return ZFCompareUncomparable;}

    if(zfscmpTheSame(this->regExpPattern(), another->regExpPattern())
        && this->regExpFlag() == another->regExpFlag())
    {
        return ZFCompareTheSame;
    }
    return ZFCompareUncomparable;
}

void *ZFRegExp::nativeRegExp(void)
{
    return d->nativeRegExp;
}

ZFMETHOD_DEFINE_0(ZFRegExp, const zfchar *, regExpPattern)
{
    return (d->pattern.isEmpty() ? zfnull : d->pattern.cString());
}
ZFMETHOD_DEFINE_0(ZFRegExp, ZFRegExpOptionFlags, regExpFlag)
{
    return d->flag;
}
ZFMETHOD_DEFINE_1(ZFRegExp, zfindex, regExpNamedGroupIndexForName, ZFMP_IN(const zfchar *, name))
{
    if(name == zfnull)
    {
        return zfindexMax;
    }
    return ZFPROTOCOL_ACCESS(ZFRegExp)->regExpNamedGroupIndexForName(this, name);
}

ZFMETHOD_DEFINE_2(ZFRegExp, void, regExpCompile,
                  ZFMP_IN(const zfchar *, pattern),
                  ZFMP_IN_OPT(ZFRegExpOptionFlags, flag, ZFRegExpOptionFlags::EnumDefault()))
{
    if(pattern == zfnull)
    {
        pattern = zfText("");
    }
    d->pattern = pattern;
    d->flag = flag;
    ZFPROTOCOL_ACCESS(ZFRegExp)->regExpCompile(this, pattern, flag);
}
ZFMETHOD_DEFINE_3(ZFRegExp, void, regExpMatch,
                  ZFMP_OUT(ZFRegExpResult &, result),
                  ZFMP_IN(const zfchar *, src),
                  ZFMP_IN_OPT(zfindex, srcLength, zfindexMax))
{
    result.namedGroups.removeAll();
    ZFPROTOCOL_ACCESS(ZFRegExp)->regExpMatch(this, result, src, srcLength);
}
ZFMETHOD_DEFINE_3(ZFRegExp, void, regExpMatchExact,
                  ZFMP_OUT(ZFRegExpResult &, result),
                  ZFMP_IN(const zfchar *, src),
                  ZFMP_IN_OPT(zfindex, srcLength, zfindexMax))
{
    result.namedGroups.removeAll();
    ZFPROTOCOL_ACCESS(ZFRegExp)->regExpMatchExact(this, result, src, srcLength);
}
ZFMETHOD_DEFINE_6(ZFRegExp, void, regExpReplace,
                  ZFMP_OUT(zfstring &, ret),
                  ZFMP_OUT(ZFRegExpResult &, result),
                  ZFMP_IN(const zfchar *, src),
                  ZFMP_IN(const zfchar *, replacePattern),
                  ZFMP_IN_OPT(zfindex, maxReplaceCount, zfindexMax),
                  ZFMP_IN_OPT(zfindex, srcLength, zfindexMax))
{
    result.namedGroups.removeAll();
    ZFPROTOCOL_ACCESS(ZFRegExp)->regExpReplace(this, ret, result, src, replacePattern, maxReplaceCount, srcLength);
}

ZF_NAMESPACE_GLOBAL_END

