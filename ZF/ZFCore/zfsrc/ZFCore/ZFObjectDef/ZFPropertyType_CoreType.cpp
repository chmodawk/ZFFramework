/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFPropertyType_CoreType.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// string conversion spec
#define _ZFP_zfflagsInvalidToken (zfText("0x0"))
zfbool zfflagsToString(ZF_IN_OUT zfstring &ret,
                       ZF_IN const zfflags *flagList,
                       ZF_IN const zfchar **nameList,
                       ZF_IN zfindex listCount,
                       ZF_IN zfflags const &value,
                       ZF_IN_OPT zfbool includeNotConverted /* = zftrue */,
                       ZF_IN_OPT zfbool exclusiveMode /* = zffalse */,
                       ZF_OUT_OPT zfflags *notConverted /* = zfnull */,
                       ZF_IN_OPT zfchar separatorToken /* = '|' */)
{
    zfflags flagsLeft = value;
    if(exclusiveMode)
    {
        for(zfindex i = 0; i < listCount; ++i)
        {
            if(flagList[i] && ZFBitTest(flagsLeft, flagList[i]))
            {
                ret += nameList[i];
                ret += separatorToken;
                ZFBitUnset(flagsLeft, flagList[i]);
            }
            if(flagsLeft == 0)
            {
                break;
            }
        }
    }
    else
    {
        for(zfindex i = 0; i < listCount; ++i)
        {
            if(flagList[i] && ZFBitTest(value, flagList[i]))
            {
                ret += nameList[i];
                ret += separatorToken;
                ZFBitUnset(flagsLeft, flagList[i]);
            }
        }
    }

    // check flagsLeft and remove tailing separatorToken from ret
    if(flagsLeft == 0)
    {
        if(ret.isEmpty())
        {
            zfindex zeroTokenIndex = zfindexMax();
            for(zfindex i = 0; i < listCount; ++i)
            {
                if(flagList[i] == 0)
                {
                    zeroTokenIndex = i;
                    break;
                }
            }
            if(zeroTokenIndex == zfindexMax())
            {
                ret = _ZFP_zfflagsInvalidToken;
            }
            else
            {
                ret = nameList[zeroTokenIndex];
            }
        }
        else
        {
            ret.remove(ret.length() - 1);
        }
    }
    else if(includeNotConverted)
    {
        ret += zfText("0x");
        zfsFromIntT(ret, flagsLeft,
            zfHint("radix")16,
            zfHint("upper case?")zftrue);
    }

    if(notConverted != zfnull)
    {
        *notConverted = flagsLeft;
    }

    return zftrue;
}
zfbool zfflagsFromString(ZF_OUT zfflags &ret,
                         ZF_IN const zfflags *flagList,
                         ZF_IN const zfchar **nameList,
                         ZF_IN zfindex listCount,
                         ZF_IN const zfchar *src,
                         ZF_IN_OPT zfindex srcLen /* = zfindexMax() */,
                         ZF_IN_OPT zfchar separatorToken /* = '|' */,
                         ZF_OUT_OPT const zfchar **outErrorPos /* = zfnull */)
{
    if(src == zfnull)
    {
        if(outErrorPos != zfnull)
        {
            *outErrorPos = src;
        }
        return zffalse;
    }
    ZFCoreArrayPOD<zfindexRange> pos;
    zfstring separatorTokens;
    separatorTokens += separatorToken;
    if(!zfCoreDataPairSplitString(pos, zfindexMax(), src, srcLen, separatorTokens, zfnull, zfnull, zffalse, outErrorPos))
    {
        return zffalse;
    }
    ret = 0;
    for(zfindex iSrc = 0; iSrc < pos.count(); ++iSrc)
    {
        zfbool recognized = zffalse;
        for(zfindex iList = 0; iList < listCount; ++iList)
        {
            if(zfsncmp(src + pos[iSrc].start, nameList[iList], pos[iSrc].count) == 0)
            {
                recognized = zftrue;
                ZFBitSet(ret, flagList[iList]);
                break;
            }
        }
        if(!recognized)
        {
            if(pos[iSrc].count > 2 && *(src + pos[iSrc].start) == '0' && *(src + pos[iSrc].start + 1) == 'x')
            {
                zfflags tmp = zfflagsZero();
                if(!zfsToIntT(tmp, src + pos[iSrc].start + 2, pos[iSrc].count - 2, 16, zftrue, outErrorPos))
                {
                    return zffalse;
                }
                ZFBitSet(ret, tmp);
            }
            else
            {
                if(outErrorPos != zfnull)
                {
                    *outErrorPos = (src + pos[iSrc].start);
                }
                return zffalse;
            }
        }
    }
    return zftrue;
}

zfbool zfstringFromData(ZF_OUT const zfchar * &v,
                        ZF_IN const ZFSerializableData &serializableData,
                        ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */,
                        ZF_OUT_OPT ZFSerializableData *outErrorPos /* = zfnull */)
{
    if(ZFSerializableUtil::requireSerializableClass(ZFPropertyTypeId_zfstring(), serializableData, outErrorHint, outErrorPos) == zfnull)
    {
        return zffalse;
    }
    const zfchar *valueString = ZFSerializableUtil::checkPropertyValue(serializableData);
    if(valueString == zfnull)
    {
        v = zfnull;
        return zftrue;
    }
    serializableData.resolveMark();
    v = valueString;
    return zftrue;
}
zfbool zfstringToData(ZF_OUT ZFSerializableData &serializableData,
                      ZF_IN const zfchar * const &v,
                      ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */)
{
    if(v == zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint,
            zfText("null string"));
        return zffalse;
    }

    serializableData.itemClassSet(ZFPropertyTypeId_zfstring());
    serializableData.propertyValueSet(v);
    return zftrue;
}

// ============================================================
// utils
#define _ZFP_ZFPROPERTY_TYPE_DEFINE_int_allow_negative(TypeName, Type) \
    ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(TypeName, Type, { \
            return zfsToIntT(v, src, srcLen, 10, zftrue); \
        }, { \
            return zfsFromIntT(s, v); \
        })
#define _ZFP_ZFPROPERTY_TYPE_DEFINE_int_disallow_negative(TypeName, Type) \
    ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(TypeName, Type, { \
            if(srcLen == zfindexMax()) \
            { \
                srcLen = zfslen(src); \
            } \
            if(srcLen == 2 && src != zfnull && zfsncmp(src, zfText("-1"), srcLen) == 0) \
            { \
                v = (Type)-1; \
                return zftrue; \
            } \
            else \
            { \
                return zfsToIntT(v, src, srcLen, 10, zffalse); \
            } \
        }, { \
            if(v == ((Type)-1)) \
            { \
                s += zfText("-1"); \
                return zftrue; \
            } \
            else \
            { \
                return zfsFromIntT(s, v); \
            } \
        })
#define _ZFP_ZFPROPERTY_TYPE_DEFINE_float(TypeName, Type) \
    ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(TypeName, Type, { \
            return zfsToFloatT(v, src, srcLen); \
        }, { \
            return zfsFromFloatT(s, v); \
        })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(zfbool, zfbool, {
        const zfchar *tokens[] = ZFM_EXPAND({
            ZFTOKEN_zfbool_zftrue,
            ZFTOKEN_zfbool_zffalse,
        });
        zfindex matched = zfsCheckMatch(tokens, ZFM_ARRAY_SIZE(tokens), src, srcLen);
        v = zffalse;
        switch(matched)
        {
            case 0:
                v = zftrue;
                return zftrue;
            case 1:
                v = zffalse;
                return zftrue;
            default:
                return zffalse;
        }
    }, {
        s += (v ? ZFTOKEN_zfbool_zftrue : ZFTOKEN_zfbool_zffalse);
        return zftrue;
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(zfbyte, zfbyte, {
        return zfsToIntT(v, src, srcLen, 16, zffalse);
    }, {
        return zfsFromIntT(s, v, 16);
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(zfchar, zfchar, {
        if(src == zfnull)
        {
            return zffalse;
        }
        v = *src;
        return zftrue;
    }, {
        s += v;
        return zftrue;
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(zfstring, zfstring, {
        if(src == zfnull)
        {
            return zffalse;
        }
        v.append(src, srcLen);
        return zftrue;
    }, {
        s += v;
        return zftrue;
    })

ZFPROPERTY_TYPE_ALIAS_DEFINE(zfstring, zfstring, cString, const zfchar *)

// ============================================================
_ZFP_ZFPROPERTY_TYPE_DEFINE_int_allow_negative(zfint, zfint)
// ============================================================
_ZFP_ZFPROPERTY_TYPE_DEFINE_int_disallow_negative(zfuint, zfuint)

// ============================================================
_ZFP_ZFPROPERTY_TYPE_DEFINE_int_disallow_negative(zfindex, zfindex)

// ============================================================
_ZFP_ZFPROPERTY_TYPE_DEFINE_float(zffloat, zffloat)

// ============================================================
_ZFP_ZFPROPERTY_TYPE_DEFINE_float(zfdouble, zfdouble)

// ============================================================
_ZFP_ZFPROPERTY_TYPE_DEFINE_float(zflongdouble, zflongdouble)

// ============================================================
_ZFP_ZFPROPERTY_TYPE_DEFINE_int_allow_negative(zftimet, zftimet)

// ============================================================
_ZFP_ZFPROPERTY_TYPE_DEFINE_int_disallow_negative(zfidentity, zfidentity)

// ============================================================
_ZFP_ZFPROPERTY_TYPE_DEFINE_int_disallow_negative(zfflags, zfflags)

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFCompareResult, ZFCompareResult, {
        if(src == zfnull) {return zffalse;}
        if(zfsncmp(src, ZFTOKEN_ZFCompareTheSame, srcLen) == 0)
        {
            v = ZFCompareTheSame;
            return zftrue;
        }
        else if(zfsncmp(src, ZFTOKEN_ZFCompareSmaller, srcLen) == 0)
        {
            v = ZFCompareSmaller;
            return zftrue;
        }
        else if(zfsncmp(src, ZFTOKEN_ZFCompareGreater, srcLen) == 0)
        {
            v = ZFCompareGreater;
            return zftrue;
        }
        else if(zfsncmp(src, ZFTOKEN_ZFCompareUncomparable, srcLen) == 0)
        {
            v = ZFCompareUncomparable;
            return zftrue;
        }
        else
        {
            return zffalse;
        }
    }, {
        switch(v)
        {
            case ZFCompareUncomparable:
                s += ZFTOKEN_ZFCompareUncomparable;
                return zftrue;
            case ZFCompareSmaller:
                s += ZFTOKEN_ZFCompareSmaller;
                return zftrue;
            case ZFCompareTheSame:
                s += ZFTOKEN_ZFCompareTheSame;
                return zftrue;
            case ZFCompareGreater:
                s += ZFTOKEN_ZFCompareGreater;
                return zftrue;
            default:
                zfCoreCriticalShouldNotGoHere();
                return zffalse;
        }
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFSeekPos, ZFSeekPos, {
        const zfchar *tokens[] = ZFM_EXPAND({
            ZFTOKEN_ZFSeekPosBegin,
            ZFTOKEN_ZFSeekPosCur,
            ZFTOKEN_ZFSeekPosCurReversely,
            ZFTOKEN_ZFSeekPosEnd,
        });
        zfindex matched = zfsCheckMatch(tokens, ZFM_ARRAY_SIZE(tokens), src, srcLen);
        v = ZFSeekPosBegin;
        switch(matched)
        {
            case 0:
                v = ZFSeekPosBegin;
                return zftrue;
            case 1:
                v = ZFSeekPosCur;
                return zftrue;
            case 2:
                v = ZFSeekPosCurReversely;
                return zftrue;
            case 3:
                v = ZFSeekPosEnd;
                return zftrue;
            default:
                return zffalse;
        }
    }, {
        switch(v)
        {
            case ZFSeekPosBegin:
                s += ZFTOKEN_ZFSeekPosBegin;
                return zftrue;
            case ZFSeekPosCur:
                s += ZFTOKEN_ZFSeekPosCur;
                return zftrue;
            case ZFSeekPosCurReversely:
                s += ZFTOKEN_ZFSeekPosCurReversely;
                return zftrue;
            case ZFSeekPosEnd:
                s += ZFTOKEN_ZFSeekPosEnd;
                return zftrue;
            default:
                zfCoreCriticalShouldNotGoHere();
                return zffalse;
        }
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(zfindexRange, zfindexRange, {
        v = zfindexRangeZero();
        ZFCoreArrayPOD<zfindex> pair;
        if(!zfCoreDataPairSplitInt(pair, 2, src, srcLen))
        {
            return zffalse;
        }
        v.start = pair[0];
        v.count = pair[1];
        return zftrue;
    }, {
        zfstringAppend(s, zfText("(%zi, %zi)"), v.start, v.count);
        return zftrue;
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFLevel, ZFLevel, {
        const zfchar *tokens[] = ZFM_EXPAND({
            ZFTOKEN_ZFLevelZFFrameworkStatic,
            ZFTOKEN_ZFLevelZFFrameworkEssential,
            ZFTOKEN_ZFLevelZFFrameworkHigh,
            ZFTOKEN_ZFLevelZFFrameworkNormal,
            ZFTOKEN_ZFLevelZFFrameworkLow,

            ZFTOKEN_ZFLevelAppEssential,
            ZFTOKEN_ZFLevelAppHigh,
            ZFTOKEN_ZFLevelAppNormal,
            ZFTOKEN_ZFLevelAppLow,

            ZFTOKEN_ZFLevelZFFrameworkPostLow,
            ZFTOKEN_ZFLevelZFFrameworkPostNormal,
            ZFTOKEN_ZFLevelZFFrameworkPostHigh,
            ZFTOKEN_ZFLevelZFFrameworkPostEssential,
            ZFTOKEN_ZFLevelZFFrameworkPostStatic,
        });
        zfindex matched = zfsCheckMatch(tokens, ZFM_ARRAY_SIZE(tokens), src, srcLen);
        v = ZFLevelAppLow;
        switch(matched)
        {
            case 0:
                v = ZFLevelZFFrameworkStatic;
                return zftrue;
            case 1:
                v = ZFLevelZFFrameworkEssential;
                return zftrue;
            case 2:
                v = ZFLevelZFFrameworkHigh;
                return zftrue;
            case 3:
                v = ZFLevelZFFrameworkNormal;
                return zftrue;
            case 4:
                v = ZFLevelZFFrameworkLow;
                return zftrue;

            case 5:
                v = ZFLevelAppEssential;
                return zftrue;
            case 6:
                v = ZFLevelAppHigh;
                return zftrue;
            case 7:
                v = ZFLevelAppNormal;
                return zftrue;
            case 8:
                v = ZFLevelAppLow;
                return zftrue;

            case 9:
                v = ZFLevelZFFrameworkPostLow;
                return zftrue;
            case 10:
                v = ZFLevelZFFrameworkPostNormal;
                return zftrue;
            case 11:
                v = ZFLevelZFFrameworkPostHigh;
                return zftrue;
            case 12:
                v = ZFLevelZFFrameworkPostEssential;
                return zftrue;
            case 13:
                v = ZFLevelZFFrameworkPostStatic;
                return zftrue;

            default:
                return zffalse;
        }
    }, {
        switch(v)
        {
            case ZFLevelZFFrameworkStatic:
                s += ZFTOKEN_ZFLevelZFFrameworkStatic;
                return zftrue;
            case ZFLevelZFFrameworkEssential:
                s += ZFTOKEN_ZFLevelZFFrameworkEssential;
                return zftrue;
            case ZFLevelZFFrameworkHigh:
                s += ZFTOKEN_ZFLevelZFFrameworkHigh;
                return zftrue;
            case ZFLevelZFFrameworkNormal:
                s += ZFTOKEN_ZFLevelZFFrameworkNormal;
                return zftrue;
            case ZFLevelZFFrameworkLow:
                s += ZFTOKEN_ZFLevelZFFrameworkLow;
                return zftrue;

            case ZFLevelAppEssential:
                s += ZFTOKEN_ZFLevelAppEssential;
                return zftrue;
            case ZFLevelAppHigh:
                s += ZFTOKEN_ZFLevelAppHigh;
                return zftrue;
            case ZFLevelAppNormal:
                s += ZFTOKEN_ZFLevelAppNormal;
                return zftrue;
            case ZFLevelAppLow:
                s += ZFTOKEN_ZFLevelAppLow;
                return zftrue;

            case ZFLevelZFFrameworkPostLow:
                s += ZFTOKEN_ZFLevelZFFrameworkPostLow;
                return zftrue;
            case ZFLevelZFFrameworkPostNormal:
                s += ZFTOKEN_ZFLevelZFFrameworkPostNormal;
                return zftrue;
            case ZFLevelZFFrameworkPostHigh:
                s += ZFTOKEN_ZFLevelZFFrameworkPostHigh;
                return zftrue;
            case ZFLevelZFFrameworkPostEssential:
                s += ZFTOKEN_ZFLevelZFFrameworkPostEssential;
                return zftrue;
            case ZFLevelZFFrameworkPostStatic:
                s += ZFTOKEN_ZFLevelZFFrameworkPostStatic;
                return zftrue;

            default:
                return zffalse;
        }
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFFrameworkState, ZFFrameworkState, {
        const zfchar *tokens[] = ZFM_EXPAND({
            ZFTOKEN_ZFFrameworkStateNotAvailable,
            ZFTOKEN_ZFFrameworkStateInitProcessing,
            ZFTOKEN_ZFFrameworkStateAvailable,
            ZFTOKEN_ZFFrameworkStateCleanupProcessing,
        });
        zfindex matched = zfsCheckMatch(tokens, ZFM_ARRAY_SIZE(tokens), src, srcLen);
        v = ZFFrameworkStateNotAvailable;
        switch(matched)
        {
            case 0:
                v = ZFFrameworkStateNotAvailable;
                return zftrue;
            case 1:
                v = ZFFrameworkStateInitProcessing;
                return zftrue;
            case 2:
                v = ZFFrameworkStateAvailable;
                return zftrue;
            case 3:
                v = ZFFrameworkStateCleanupProcessing;
                return zftrue;
            default:
                return zffalse;
        }
    }, {
        switch(v)
        {
            case ZFFrameworkStateNotAvailable:
                s += ZFTOKEN_ZFFrameworkStateNotAvailable;
                return zftrue;
            case ZFFrameworkStateInitProcessing:
                s += ZFTOKEN_ZFFrameworkStateInitProcessing;
                return zftrue;
            case ZFFrameworkStateAvailable:
                s += ZFTOKEN_ZFFrameworkStateAvailable;
                return zftrue;
            case ZFFrameworkStateCleanupProcessing:
                s += ZFTOKEN_ZFFrameworkStateCleanupProcessing;
                return zftrue;
            default:
                return zffalse;
        }
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFFilterType, ZFFilterType, {
        const zfchar *tokens[] = ZFM_EXPAND({
            ZFTOKEN_ZFFilterTypeInclude,
            ZFTOKEN_ZFFilterTypeExclude,
        });
        zfindex matched = zfsCheckMatch(tokens, ZFM_ARRAY_SIZE(tokens), src, srcLen);
        v = ZFFilterTypeInclude;
        switch(matched)
        {
            case 0:
                v = ZFFilterTypeInclude;
                return zftrue;
            case 1:
                v = ZFFilterTypeExclude;
                return zftrue;
            default:
                return zffalse;
        }
    }, {
        switch(v)
        {
            case ZFFilterTypeInclude:
                s += ZFTOKEN_ZFFilterTypeInclude;
                return zftrue;
            case ZFFilterTypeExclude:
                s += ZFTOKEN_ZFFilterTypeExclude;
                return zftrue;
            default:
                zfCoreCriticalShouldNotGoHere();
                return zffalse;
        }
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFFilterCallbackResult, ZFFilterCallbackResult, {
        const zfchar *tokens[] = ZFM_EXPAND({
            ZFTOKEN_ZFFilterCallbackResultNotSpecified,
            ZFTOKEN_ZFFilterCallbackResultActive,
            ZFTOKEN_ZFFilterCallbackResultNotActive,
        });
        zfindex matched = zfsCheckMatch(tokens, ZFM_ARRAY_SIZE(tokens), src, srcLen);
        v = ZFFilterCallbackResultNotSpecified;
        switch(matched)
        {
            case 0:
                v = ZFFilterCallbackResultNotSpecified;
                return zftrue;
            case 1:
                v = ZFFilterCallbackResultActive;
                return zftrue;
            case 2:
                v = ZFFilterCallbackResultNotActive;
                return zftrue;
            default:
                return zffalse;
        }
    }, {
        switch(v)
        {
            case ZFFilterCallbackResultNotSpecified:
                s += ZFTOKEN_ZFFilterCallbackResultNotSpecified;
                return zftrue;
            case ZFFilterCallbackResultActive:
                s += ZFTOKEN_ZFFilterCallbackResultActive;
                return zftrue;
            case ZFFilterCallbackResultNotActive:
                s += ZFTOKEN_ZFFilterCallbackResultNotActive;
                return zftrue;
            default:
                zfCoreCriticalShouldNotGoHere();
                return zffalse;
        }
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_SERIALIZABLE_CONVERTER(ZFTokenForContainer, ZFTokenForContainer, {
        v.tokenLeft = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForContainer_tokenLeft);
        v.tokenRight = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForContainer_tokenRight);
        v.tokenSeparator = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForContainer_tokenSeparator);
        v.tokenValueLeft = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForContainer_tokenValueLeft);
        v.tokenValueRight = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForContainer_tokenValueRight);
        v.tokenEtc = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForContainer_tokenEtc);
        return zftrue;
    }, {
        if(!v.tokenLeft.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForContainer_tokenLeft, v.tokenLeft);}
        if(!v.tokenRight.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForContainer_tokenRight, v.tokenRight);}
        if(!v.tokenSeparator.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForContainer_tokenSeparator, v.tokenSeparator);}
        if(!v.tokenValueLeft.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForContainer_tokenValueLeft, v.tokenValueLeft);}
        if(!v.tokenValueRight.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForContainer_tokenValueRight, v.tokenValueRight);}
        if(!v.tokenEtc.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForContainer_tokenEtc, v.tokenEtc);}
        return zftrue;
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_SERIALIZABLE_CONVERTER(ZFTokenForKeyValueContainer, ZFTokenForKeyValueContainer, {
        v.tokenLeft = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenLeft);
        v.tokenRight = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenRight);
        v.tokenSeparator = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenSeparator);
        v.tokenPairLeft = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenPairLeft);
        v.tokenPairRight = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenPairRight);
        v.tokenPairSeparator = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenPairSeparator);
        v.tokenKeyLeft = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenKeyLeft);
        v.tokenKeyRight = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenKeyRight);
        v.tokenValueLeft = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenValueLeft);
        v.tokenValueRight = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenValueRight);
        v.tokenEtc = ZFSerializableUtil::checkAttribute(serializableData, ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenEtc);
        return zftrue;
    }, {
        if(!v.tokenLeft.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenLeft, v.tokenLeft);}
        if(!v.tokenRight.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenRight, v.tokenRight);}
        if(!v.tokenSeparator.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenSeparator, v.tokenSeparator);}
        if(!v.tokenPairLeft.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenPairLeft, v.tokenPairLeft);}
        if(!v.tokenPairRight.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenPairRight, v.tokenPairRight);}
        if(!v.tokenPairSeparator.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenPairSeparator, v.tokenPairSeparator);}
        if(!v.tokenKeyLeft.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenKeyLeft, v.tokenKeyLeft);}
        if(!v.tokenKeyRight.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenKeyRight, v.tokenKeyRight);}
        if(!v.tokenValueLeft.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenValueLeft, v.tokenValueLeft);}
        if(!v.tokenValueRight.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenValueRight, v.tokenValueRight);}
        if(!v.tokenEtc.isEmpty()) {serializableData.attributeSet(ZFSerializableKeyword_ZFTokenForKeyValueContainer_tokenEtc, v.tokenEtc);}
        return zftrue;
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFFilterForZFClassType, ZFFilterForZFClassType, {
        const zfchar *tokens[] = ZFM_EXPAND({
            ZFTOKEN_ZFFilterForZFClassTypeInclude,
            ZFTOKEN_ZFFilterForZFClassTypeExclude,
            ZFTOKEN_ZFFilterForZFClassTypeIncludeChildOf,
            ZFTOKEN_ZFFilterForZFClassTypeIncludeParentOf,
            ZFTOKEN_ZFFilterForZFClassTypeExcludeChildOf,
            ZFTOKEN_ZFFilterForZFClassTypeExcludeParentOf,
        });
        zfindex matched = zfsCheckMatch(tokens, ZFM_ARRAY_SIZE(tokens), src, srcLen);
        v = ZFFilterForZFClassTypeInclude;
        switch(matched)
        {
            case 0:
                v = ZFFilterForZFClassTypeInclude;
                return zftrue;
            case 1:
                v = ZFFilterForZFClassTypeExclude;
                return zftrue;
            case 2:
                v = ZFFilterForZFClassTypeIncludeChildOf;
                return zftrue;
            case 3:
                v = ZFFilterForZFClassTypeIncludeParentOf;
                return zftrue;
            case 4:
                v = ZFFilterForZFClassTypeExcludeChildOf;
                return zftrue;
            case 5:
                v = ZFFilterForZFClassTypeExcludeParentOf;
                return zftrue;
            default:
                return zffalse;
        }
    }, {
        switch(v)
        {
            case ZFFilterForZFClassTypeInclude:
                s += ZFTOKEN_ZFFilterForZFClassTypeInclude;
                return zftrue;
            case ZFFilterForZFClassTypeExclude:
                s += ZFTOKEN_ZFFilterForZFClassTypeExclude;
                return zftrue;
            case ZFFilterForZFClassTypeIncludeChildOf:
                s += ZFTOKEN_ZFFilterForZFClassTypeIncludeChildOf;
                return zftrue;
            case ZFFilterForZFClassTypeIncludeParentOf:
                s += ZFTOKEN_ZFFilterForZFClassTypeIncludeParentOf;
                return zftrue;
            case ZFFilterForZFClassTypeExcludeChildOf:
                s += ZFTOKEN_ZFFilterForZFClassTypeExcludeChildOf;
                return zftrue;
            case ZFFilterForZFClassTypeExcludeParentOf:
                s += ZFTOKEN_ZFFilterForZFClassTypeExcludeParentOf;
                return zftrue;
            default:
                zfCoreCriticalShouldNotGoHere();
                return zffalse;
        }
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFMethodPrivilegeType, ZFMethodPrivilegeType, {
        const zfchar *tokens[] = ZFM_EXPAND({
            ZFTOKEN_ZFMethodPrivilegeTypePublic,
            ZFTOKEN_ZFMethodPrivilegeTypeProtected,
            ZFTOKEN_ZFMethodPrivilegeTypePrivate,
        });
        zfindex matched = zfsCheckMatch(tokens, ZFM_ARRAY_SIZE(tokens), src, srcLen);
        v = ZFMethodPrivilegeTypePublic;
        switch(matched)
        {
            case 0:
                v = ZFMethodPrivilegeTypePublic;
                return zftrue;
            case 1:
                v = ZFMethodPrivilegeTypeProtected;
                return zftrue;
            case 2:
                v = ZFMethodPrivilegeTypePrivate;
                return zftrue;
            default:
                return zffalse;
        }
    }, {
        switch(v)
        {
            case ZFMethodPrivilegeTypePublic:
                s += ZFTOKEN_ZFMethodPrivilegeTypePublic;
                return zftrue;
            case ZFMethodPrivilegeTypeProtected:
                s += ZFTOKEN_ZFMethodPrivilegeTypeProtected;
                return zftrue;
            case ZFMethodPrivilegeTypePrivate:
                s += ZFTOKEN_ZFMethodPrivilegeTypePrivate;
                return zftrue;
            default:
                zfCoreCriticalShouldNotGoHere();
                return zffalse;
        }
    })

// ============================================================
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFComparerForZFObject, ZFComparer<ZFObject *>::Comparer)

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFObjectInstanceState, ZFObjectInstanceState, {
        const zfchar *tokens[] = ZFM_EXPAND({
            ZFTOKEN_ZFObjectInstanceStateOnInit,
            ZFTOKEN_ZFObjectInstanceStateOnInitFinish,
            ZFTOKEN_ZFObjectInstanceStateIdle,
            ZFTOKEN_ZFObjectInstanceStateOnDeallocPrepare,
            ZFTOKEN_ZFObjectInstanceStateOnDealloc,
        });
        zfindex matched = zfsCheckMatch(tokens, ZFM_ARRAY_SIZE(tokens), src, srcLen);
        v = ZFObjectInstanceStateOnInit;
        switch(matched)
        {
            case 0:
                v = ZFObjectInstanceStateOnInit;
                return zftrue;
            case 1:
                v = ZFObjectInstanceStateOnInitFinish;
                return zftrue;
            case 2:
                v = ZFObjectInstanceStateIdle;
                return zftrue;
            case 3:
                v = ZFObjectInstanceStateOnDeallocPrepare;
                return zftrue;
            case 4:
                v = ZFObjectInstanceStateOnDealloc;
                return zftrue;
            default:
                return zffalse;
        }
    }, {
        switch(v)
        {
            case ZFObjectInstanceStateOnInit:
                s += ZFTOKEN_ZFObjectInstanceStateOnInit;
                return zftrue;
            case ZFObjectInstanceStateOnInitFinish:
                s += ZFTOKEN_ZFObjectInstanceStateOnInitFinish;
                return zftrue;
            case ZFObjectInstanceStateIdle:
                s += ZFTOKEN_ZFObjectInstanceStateIdle;
                return zftrue;
            case ZFObjectInstanceStateOnDeallocPrepare:
                s += ZFTOKEN_ZFObjectInstanceStateOnDeallocPrepare;
                return zftrue;
            case ZFObjectInstanceStateOnDealloc:
                s += ZFTOKEN_ZFObjectInstanceStateOnDealloc;
                return zftrue;
            default:
                zfCoreCriticalShouldNotGoHere();
                return zffalse;
        }
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFCallbackType, ZFCallbackType, {
        const zfchar *tokens[] = ZFM_EXPAND({
            ZFTOKEN_ZFCallbackTypeDummy,
            ZFTOKEN_ZFCallbackTypeMethod,
            ZFTOKEN_ZFCallbackTypeMemberMethod,
            ZFTOKEN_ZFCallbackTypeRawFunction,
        });
        zfindex matched = zfsCheckMatch(tokens, ZFM_ARRAY_SIZE(tokens), src, srcLen);
        v = ZFCallbackTypeDummy;
        switch(matched)
        {
            case 0:
                v = ZFCallbackTypeDummy;
                return zftrue;
            case 1:
                v = ZFCallbackTypeMethod;
                return zftrue;
            case 2:
                v = ZFCallbackTypeMemberMethod;
                return zftrue;
            case 3:
                v = ZFCallbackTypeRawFunction;
                return zftrue;
            default:
                return zffalse;
        }
    }, {
        switch(v)
        {
            case ZFCallbackTypeDummy:
                s += ZFTOKEN_ZFCallbackTypeDummy;
                return zftrue;
            case ZFCallbackTypeMethod:
                s += ZFTOKEN_ZFCallbackTypeMethod;
                return zftrue;
            case ZFCallbackTypeMemberMethod:
                s += ZFTOKEN_ZFCallbackTypeMemberMethod;
                return zftrue;
            case ZFCallbackTypeRawFunction:
                s += ZFTOKEN_ZFCallbackTypeRawFunction;
                return zftrue;
            default:
                zfCoreCriticalShouldNotGoHere();
                return zffalse;
        }
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_SERIALIZABLE_CONVERTER(zfautoObject, zfautoObject, {
        return ZFObjectFromData(v, serializableData, outErrorHint, outErrorPos);
    }, {
        return ZFObjectToData(serializableData, v, outErrorHint);
    })
ZFOUTPUT_TYPE_DEFINE(zfautoObject, {
        output.execute(
            (v == zfautoObjectNull())
            ? ZFTOKEN_zfnull
            : v.toObject()->objectInfo()
        );
    })

// ============================================================
ZFPROPERTY_TYPE_DEFINE(ZFSerializableData, ZFSerializableData, {
        v = serializableData;
        return zftrue;
    }, {
        serializableData = v;
        return zftrue;
    }, {
        return ZFSerializableDataFromString(v, src, srcLen, zfnull);
    }, {
        return ZFSerializableDataToString(s, v, zfnull);
    })
ZFOUTPUT_TYPE_DEFINE(ZFSerializableData, {
        output.execute(v.objectInfo());
    })

// ============================================================
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFFuncAddrType, ZFFuncAddrType)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFMemberFuncAddrType, ZFMemberFuncAddrType)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE_UNCOMPARABLE(zfiterator, zfiterator)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFBuffer, ZFBuffer)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFFilterForNumber, ZFFilterForNumber)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFFilterForIndex, ZFFilterForIndex)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFFilterForIdentity, ZFFilterForIdentity)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFFilterForString, ZFFilterForString)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFIdentityGenerator, ZFIdentityGenerator)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFListenerData, ZFListenerData)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFObserverAddParam, ZFObserverAddParam)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFObserverHolder, ZFObserverHolder)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFFilterForZFClass, ZFFilterForZFClass)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFFilterForZFMethod, ZFFilterForZFMethod)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFFilterForZFProperty, ZFFilterForZFProperty)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFFilterForZFObject, ZFFilterForZFObject)
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFMethodGenericInvoker, ZFMethodGenericInvoker)

ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(VoidPointer, void *)
ZFPROPERTY_TYPE_ALIAS_DEFINE(VoidPointer, void *, VoidPointerConst, const void *)

ZF_NAMESPACE_GLOBAL_END

