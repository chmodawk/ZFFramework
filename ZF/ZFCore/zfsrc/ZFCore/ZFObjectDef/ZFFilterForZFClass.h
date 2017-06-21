/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFFilterForZFClass.h
 * @brief filter for ZFClass types
 */

#ifndef _ZFI_ZFFilterForZFClass_h_
#define _ZFI_ZFFilterForZFClass_h_

#include "ZFObjectClassTypeFwd.h"
ZF_NAMESPACE_GLOBAL_BEGIN

zfclassFwd ZFClass;
// ============================================================
/**
 * @brief filter type for #ZFFilterForZFClass
 */
typedef enum {
    /**
     * @brief exactly the same
     */
    ZFFilterForZFClassTypeInclude,
    /**
     * @brief exactly not the same
     */
    ZFFilterForZFClassTypeExclude,

    /**
     * @brief cls->classIsSubclassOf(clsToCheck)
     */
    ZFFilterForZFClassTypeIncludeChildOf,
    /**
     * @brief cls->classIsTypeOf(clsToCheck)
     */
    ZFFilterForZFClassTypeIncludeChildTypeOf,
    /**
     * @brief clsToCheck->classIsSubclassOf(cls)
     */
    ZFFilterForZFClassTypeIncludeParentOf,
    /**
     * @brief clsToCheck->classIsTypeOf(cls)
     */
    ZFFilterForZFClassTypeIncludeParentTypeOf,

    /**
     * @brief !cls->classIsSubclassOf(clsToCheck)
     */
    ZFFilterForZFClassTypeExcludeChildOf,
    /**
     * @brief !cls->classIsTypeOf(clsToCheck)
     */
    ZFFilterForZFClassTypeExcludeChildTypeOf,
    /**
     * @brief !clsToCheck->classIsSubclassOf(cls)
     */
    ZFFilterForZFClassTypeExcludeParentOf,
    /**
     * @brief !clsToCheck->classIsTypeOf(cls)
     */
    ZFFilterForZFClassTypeExcludeParentTypeOf,
} ZFFilterForZFClassType;
/** @brief string tokens */
#define ZFTOKEN_ZFFilterForZFClassTypeInclude zfText("Include")
/** @brief string tokens */
#define ZFTOKEN_ZFFilterForZFClassTypeExclude zfText("Exclude")
/** @brief string tokens */
#define ZFTOKEN_ZFFilterForZFClassTypeIncludeChildOf zfText("IncludeChildOf")
/** @brief string tokens */
#define ZFTOKEN_ZFFilterForZFClassTypeIncludeChildTypeOf zfText("IncludeChildTypeOf")
/** @brief string tokens */
#define ZFTOKEN_ZFFilterForZFClassTypeIncludeParentOf zfText("IncludeParentOf")
/** @brief string tokens */
#define ZFTOKEN_ZFFilterForZFClassTypeIncludeParentTypeOf zfText("IncludeParentTypeOf")
/** @brief string tokens */
#define ZFTOKEN_ZFFilterForZFClassTypeExcludeChildOf zfText("ExcludeChildOf")
/** @brief string tokens */
#define ZFTOKEN_ZFFilterForZFClassTypeExcludeChildTypeOf zfText("ExcludeChildTypeOf")
/** @brief string tokens */
#define ZFTOKEN_ZFFilterForZFClassTypeExcludeParentOf zfText("ExcludeParentOf")
/** @brief string tokens */
#define ZFTOKEN_ZFFilterForZFClassTypeExcludeParentTypeOf zfText("ExcludeParentTypeOf")

ZFCOMPARER_DEFAULT_DECLARE(ZFFilterForZFClassType, ZFFilterForZFClassType, {
        return ((v0 == v1) ? ZFCompareTheSame : ZFCompareUncomparable);
    })

// ============================================================
zfclassPOD ZF_ENV_EXPORT _ZFP_ZFFilterForZFClassData
{
public:
    const ZFClass *filterClass;
    ZFFilterForZFClassType filterType;
};
/**
 * @brief util class to filter ZFClass
 */
zfclassLikePOD ZF_ENV_EXPORT ZFFilterForZFClass
{
public:
    /**
     * @brief see #ZFFilterBase::CustomFilterCallback
     */
    typedef ZFFilterCallbackResult (*CustomFilterCallback)(ZF_IN const ZFClass * const &e);

public:
    /**
     * @brief main constructor
     */
    ZFFilterForZFClass(void);
    /**
     * @brief constructor from another filter, retain only, use #copyFrom if you want copy
     */
    ZFFilterForZFClass(ZF_IN const ZFFilterForZFClass &ref);
    /**
     * @brief retain only, use #copyFrom if you want copy
     */
    virtual ZFFilterForZFClass &operator = (ZF_IN const ZFFilterForZFClass &ref);
    /** @cond ZFPrivateDoc */
    zfbool operator == (ZF_IN const ZFFilterForZFClass &ref) const;
    zfbool operator != (ZF_IN const ZFFilterForZFClass &ref) const;
    /** @endcond */
    virtual ~ZFFilterForZFClass(void);
    /**
     * @brief copy from another filter
     */
    virtual void copyFrom(ZF_IN ZFFilterForZFClass const &ref);

public:
    /**
     * @brief add a filter
     */
    virtual ZFFilterForZFClass &filterAdd(ZF_IN const ZFClass * const &e,
                                          ZF_IN_OPT ZFFilterForZFClassType filterType = ZFFilterForZFClassTypeExclude);
    /**
     * @brief remove a filter (remove first only, if duplicated filter added)
     */
    virtual ZFFilterForZFClass &filterRemove(ZF_IN const ZFClass * const &e,
                                             ZF_IN_OPT ZFFilterForZFClassType filterType = ZFFilterForZFClassTypeExclude);
    /**
     * @brief remove
     */
    virtual ZFFilterForZFClass &filterRemoveAtIndex(ZF_IN zfindex index);

public:
    /**
     * @brief get filter count
     */
    virtual zfindex filterCount(void) const;
    /**
     * @brief get filter class at index
     */
    virtual const ZFClass *filterGetFilterClass(ZF_IN zfindex index) const;
    /**
     * @brief get filter type at index
     */
    virtual ZFFilterForZFClassType filterGetFilterType(ZF_IN zfindex index) const;
    /**
     * @brief add a custom filter callback
     */
    virtual ZFFilterForZFClass &customFilterCallbackAdd(ZF_IN ZFFilterForZFClass::CustomFilterCallback customFilterCallback);
    /**
     * @brief remove custom filter callback
     */
    virtual ZFFilterForZFClass &customFilterCallbackRemove(ZF_IN ZFFilterForZFClass::CustomFilterCallback customFilterCallback);
    /**
     * @brief remove custom filter callback
     */
    virtual ZFFilterForZFClass &customFilterCallbackRemove(ZF_IN zfindex index);
    /**
     * @brief get custom filter callback count
     */
    virtual zfindex customFilterCallbackCount(void) const;
    /**
     * @brief get custom filter callback
     */
    virtual ZFFilterForZFClass::CustomFilterCallback customFilterCallbackAtIndex(ZF_IN zfindex index) const;

public:
    /**
     * @brief return true if e not filtered out
     */
    virtual zfbool filterCheckActive(ZF_IN const ZFClass * const &e) const;

public:
    /**
     * @brief get a short info about the filter
     */
    virtual void objectInfoT(ZF_IN_OUT zfstring &ret) const;
    /** @brief see #objectInfoT */
    virtual inline zfstring objectInfo(void) const
    {
        zfstring ret;
        this->objectInfoT(ret);
        return ret;
    }

private:
    ZFCoreArrayPOD<_ZFP_ZFFilterForZFClassData> _ZFP_ZFFilterForZFClass_filters;
    ZFCoreArrayPOD<ZFFilterForZFClass::CustomFilterCallback> _ZFP_ZFFilterForZFClass_customFilterCallbacks;
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFFilterForZFClass_h_

