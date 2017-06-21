/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFFilterForZFMethod.h
 * @brief filter for ZFMethod types
 */

#ifndef _ZFI_ZFFilterForZFMethod_h_
#define _ZFI_ZFFilterForZFMethod_h_

#include "ZFFilterForZFClass.h"
ZF_NAMESPACE_GLOBAL_BEGIN

zfclassFwd ZFMethod;
// ============================================================
zfclassPOD ZF_ENV_EXPORT _ZFP_ZFFilterForZFMethodSetting
{
public:
    zfbool ignorePublic;
    zfbool ignoreProtected;
    zfbool ignorePrivate;
};
/**
 * @brief util class to filter ZFMethod
 */
zfclassLikePOD ZF_ENV_EXPORT ZFFilterForZFMethod : zfextendsLikePOD ZFFilterBasic<const ZFMethod *>
{
    ZFFILTER_DECLARE(ZFFilterForZFMethod, ZFFilterBasic<const ZFMethod *>)

public:
    /**
     * @brief see #ZFFilterBase
     */
    ZFFilterForZFMethod(void)
    : zfsuper()
    , classFilter()
    , d()
    {
        _ZFP_ZFFilterForZFMethodSetting *setting = zfnew(_ZFP_ZFFilterForZFMethodSetting);
        setting->ignorePublic = zffalse;
        setting->ignoreProtected = zffalse;
        setting->ignorePrivate = zffalse;
        d = setting;
    }
    /**
     * @brief see #ZFFilterBase
     */
    ZFFilterForZFMethod(ZF_IN const ZFFilterForZFMethod &ref)
    : zfsuper()
    , classFilter(ref.classFilter)
    , d(ref.d)
    {
    }
    /** @cond ZFPrivateDoc */
    virtual ZFFilterForZFMethod &operator = (ZF_IN const ZFFilterForZFMethod &ref)
    {
        zfsuper::operator = (ref);
        this->classFilter = ref.classFilter;
        this->d = ref.d;
        return *this;
    }
    virtual void copyFrom(ZF_IN ZFFilterForZFMethod const &ref)
    {
        zfsuper::copyFrom(ref);
        this->classFilter.copyFrom(ref.classFilter);
        _ZFP_ZFFilterForZFMethodSetting *setting = zfnew(_ZFP_ZFFilterForZFMethodSetting);
        zfmemcpy(setting, ref.d.pointerValueGet(), sizeof(_ZFP_ZFFilterForZFMethodSetting));
        d = setting;
    }
    /** @endcond */

public:
    /**
     * @brief filter the method's owner class
     */
    ZFFilterForZFClass classFilter;

public:
    /**
     * @brief ignore public method, false by default
     */
    virtual void ignorePublicSet(ZF_IN zfbool value)
    {
        d->ignorePublic = value;
    }
    /**
     * @brief see #ignorePublicSet
     */
    virtual zfbool ignorePublic(void) const
    {
        return d->ignorePublic;
    }

    /**
     * @brief ignore protected method, false by default
     */
    virtual void ignoreProtectedSet(ZF_IN zfbool value)
    {
        d->ignoreProtected = value;
    }
    /**
     * @brief see #ignoreProtectedSet
     */
    virtual zfbool ignoreProtected(void) const
    {
        return d->ignoreProtected;
    }

    /**
     * @brief ignore private method, false by default
     */
    virtual void ignorePrivateSet(ZF_IN zfbool value)
    {
        d->ignorePrivate = value;
    }
    /**
     * @brief see #ignorePrivateSet
     */
    virtual zfbool ignorePrivate(void) const
    {
        return d->ignorePrivate;
    }

public:
    zfoverride
    virtual void objectInfoT(ZF_IN_OUT zfstring &ret) const;

protected:
    /** @cond ZFPrivateDoc */ // ZFDoxygenBugFix: can't auto detect template specialization
    zfoverride
    virtual zfbool filterOnCheckValid(ZF_IN const ZFMethod * const &e) const
    {
        return (e != zfnull);
    }
    zfoverride
    virtual zfbool filterOnCheckActive(ZF_IN const ZFMethod * const &e) const;
    /** @endcond */

private:
    ZFCorePointerForPOD<_ZFP_ZFFilterForZFMethodSetting *> d;
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFFilterForZFMethod_h_

