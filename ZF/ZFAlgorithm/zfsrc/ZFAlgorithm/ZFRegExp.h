/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFRegExp.h
 * @brief regular expression utils
 */

#ifndef _ZFI_ZFRegExp_h_
#define _ZFI_ZFRegExp_h_

#include "ZFAlgorithmDef.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief compile flags for ZFRegExp
 */
ZFENUM_BEGIN(ZFRegExpOption)
    /**
     * @brief no flags
     *
     * default is case sensitive,
     * no single line mode,
     * no multi line mode
     */
    ZFENUM_VALUE_WITH_INIT(None, 0)
    /**
     * @brief ignore case
     */
    ZFENUM_VALUE_WITH_INIT(IgnoreCase, 1)
    /**
     * @brief single line mode
     *
     * if single line mode,
     * '.' matches any chars including '\\n'\n
     * otherwise,
     * '.' doesn't match '\\n' (while '\\r' is also matched)
     */
    ZFENUM_VALUE_WITH_INIT(SingleLine, 2)
    /**
     * @brief multi line mode
     *
     * if multi line mode,
     * '^' matches string's begin and line's begin (after '\\n'),
     * '$' matches string's end and line's end (before '\\n')\n
     * otherwise,
     * '^' matches string's begin only,
     * '$' matches string's end only
     */
    ZFENUM_VALUE_WITH_INIT(MultiLine, 4)
ZFENUM_SEPARATOR(ZFRegExpOption)
    ZFENUM_VALUE_REGISTER(None)
    ZFENUM_VALUE_REGISTER(IgnoreCase)
    ZFENUM_VALUE_REGISTER(SingleLine)
    ZFENUM_VALUE_REGISTER(MultiLine)
ZFENUM_END(ZFRegExpOption)

ZFENUM_FLAGS_DECLARE_WITH_DEFAULT(ZFRegExpOption, ZFRegExpOptionFlags, ZFRegExpOption::e_None)

// ============================================================
/**
 * @brief match result info for ZFRegExp
 */
zfclassLikePOD ZF_ENV_EXPORT ZFRegExpResult
{
public:
    /**
     * @brief true if matched
     */
    zfbool matched;
    /**
     * @brief first matched index
     *
     * would be #zfindexRangeZero if not supported
     */
    zfindexRange matchedRange;
    /**
     * @brief matched name groups
     *
     * would be empty if not supported
     */
    ZFCoreArrayPOD<zfindexRange> namedGroups;

public:
    /**
     * @brief get a short info
     */
    void objectInfoT(ZF_IN_OUT zfstring &ret) const;
    /** @brief see #objectInfoT */
    inline zfstring objectInfo(void) const
    {
        zfstring ret;
        this->objectInfoT(ret);
        return ret;
    }

public:
    /** @cond ZFPrivateDoc */
    zfbool operator == (ZF_IN const ZFRegExpResult &ref) const
    {
        return (this->matched == ref.matched
                && this->matchedRange == ref.matchedRange
                && this->namedGroups.objectCompare(ref.namedGroups) == ZFCompareTheSame);
    }
    inline zfbool operator != (ZF_IN const ZFRegExpResult &ref) const {return !this->operator == (ref);}
    /** @endcond */
};

/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFRegExpResult_matched zfText("matched")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFRegExpResult_matchedRange zfText("matchedRange")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFRegExpResult_namedGroups zfText("namedGroups")

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFRegExpResult>
 *       <zfbool name="matched" value="xxx" /> // optional, false by default
 *       <zfindexRange name="matchedRange" value="xxx" /> // optional, zfindexRangeZero by default
 *       <ZFCoreArray name="namedGroups"> // optional, empty by default
 *           <zfindexRange /> // each namedGroups
 *       </ZFCoreArray>
 *   </ZFRegExpResult>
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFRegExpResult, ZFRegExpResult)
ZFOUTPUT_TYPE(ZFRegExpResult, {output << v.objectInfo();})

// ============================================================
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFRegExp_pattern zfText("pattern")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFRegExp_flag zfText("flag")

zfclassFwd _ZFP_ZFRegExpPrivate;
/**
 * @brief regular expression utils
 *
 * serializable data:
 * @code
 *   <ZFRegExp
 *       partten="regExpPattern" // optional
 *       flag="ZFRegExpOptionFlags" // optional
 *   />
 * @endcode
 */
zfclass ZF_ENV_EXPORT ZFRegExp : zfextends ZFObject, zfimplements ZFSerializable, zfimplements ZFCopyable
{
    ZFOBJECT_DECLARE(ZFRegExp, ZFObject)
    ZFIMPLEMENTS_DECLARE(ZFSerializable, ZFCopyable)

protected:
    zfoverride
    virtual zfbool serializableOnSerializeFromData(ZF_IN const ZFSerializableData &serializableData,
                                                   ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                   ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull);
    zfoverride
    virtual zfbool serializableOnSerializeToData(ZF_IN_OUT ZFSerializableData &serializableData,
                                                 ZF_IN ZFSerializable *referencedOwnerOrNull,
                                                 ZF_OUT_OPT zfstring *outErrorHint = zfnull);

protected:
    zfoverride
    virtual void copyableOnCopyFrom(ZF_IN ZFObject *anotherObj)
    {
        zfsuperI(ZFCopyable)::copyableOnCopyFrom(anotherObj);
        ZFRegExp *another = ZFCastZFObjectUnchecked(zfself *, anotherObj);
        this->regExpCompile(another->regExpPattern(), another->regExpFlag());
    }

protected:
    /**
     * @brief init with pattern, see #regExpCompile
     */
    ZFMETHOD_DECLARE_PROTECTED_2(void, objectOnInit,
                                 ZFMP_IN(const zfchar *, pattern),
                                 ZFMP_IN_OPT(ZFRegExpOptionFlags, flag, ZFRegExpOptionFlags::EnumDefault)());

    zfoverride
    virtual void objectOnInit(void);
    zfoverride
    virtual void objectOnDealloc(void);

    zfoverride
    virtual void objectInfoOnAppend(ZF_IN_OUT zfstring &ret);

public:
    zfoverride
    virtual zfidentity objectHash(void);
    /**
     * @brief ZFCompareTheSame if pattern and flag both the same,
     *   ZFCompareUncomparable otherwise
     */
    zfoverride
    virtual ZFCompareResult objectCompare(ZF_IN ZFObject *anotherObj);

public:
    /**
     * @brief for internal use only
     */
    ZFMETHOD_DECLARE_0(void *, nativeRegExp);

public:
    /**
     * @brief get current pattern or null if not set, use #regExpCompile to change
     */
    ZFMETHOD_DECLARE_0(const zfchar *, regExpPattern);
    /**
     * @brief get current flag or ZFRegExpOptionNone if not set, use #regExpCompile to change
     */
    ZFMETHOD_DECLARE_0(ZFRegExpOptionFlags, regExpFlag);
    /**
     * @brief get named group's number which can be used as "$n" while #regExpReplace, or zfindexMax() if no such group
     */
    ZFMETHOD_DECLARE_1(zfindex, regExpNamedGroupIndexForName, ZFMP_IN(const zfchar *, name));

public:
    /**
     * @brief regExpCompile the pattern
     */
    ZFMETHOD_DECLARE_2(void, regExpCompile,
                       ZFMP_IN(const zfchar *, pattern),
                       ZFMP_IN_OPT(ZFRegExpOptionFlags, flag, ZFRegExpOptionFlags::EnumDefault()));

    /**
     * @brief test the src with this compiled pattern, see #regExpMatchExact
     */
    ZFMETHOD_DECLARE_3(void, regExpMatch,
                       ZFMP_OUT(ZFRegExpResult &, result),
                       ZFMP_IN(const zfchar *, src),
                       ZFMP_IN_OPT(zfindex, srcLength, zfindexMax()));
    /**
     * @brief test the src which must match the pattern exactly, see #regExpMatch
     */
    ZFMETHOD_DECLARE_3(void, regExpMatchExact,
                       ZFMP_OUT(ZFRegExpResult &, result),
                       ZFMP_IN(const zfchar *, src),
                       ZFMP_IN_OPT(zfindex, srcLength, zfindexMax()));

    /**
     * @brief replace src with this pattern and replacePattern
     */
    ZFMETHOD_DECLARE_6(void, regExpReplace,
                       ZFMP_OUT(zfstring &, ret),
                       ZFMP_OUT(ZFRegExpResult &, result),
                       ZFMP_IN(const zfchar *, src),
                       ZFMP_IN(const zfchar *, replacePattern),
                       ZFMP_IN_OPT(zfindex, maxReplaceCount, zfindexMax()),
                       ZFMP_IN_OPT(zfindex, srcLength, zfindexMax()));

private:
    _ZFP_ZFRegExpPrivate *d;
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFRegExp_h_

