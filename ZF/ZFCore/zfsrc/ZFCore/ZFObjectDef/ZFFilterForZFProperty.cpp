/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFFilterForZFProperty.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

static void _ZFP_ZFFilterForZFPropertyGetSettingInfo(ZF_OUT zfstring &ret,
                                                     ZF_IN const ZFFilterForZFProperty *filter)
{
    ret += '(';
    zfindex flagsCount = 0;
    if(filter->ignorePublicSetter())
    {
        ++flagsCount;
        ret += zfText("ignorePublicSetter, ");
    }
    if(filter->ignoreProtectedSetter())
    {
        ++flagsCount;
        ret += zfText("ignoreProtectedSetter, ");
    }
    if(filter->ignorePrivateSetter())
    {
        ++flagsCount;
        ret += zfText("ignorePrivateSetter, ");
    }
    if(filter->ignorePublicGetter())
    {
        ++flagsCount;
        ret += zfText("ignorePublicGetter, ");
    }
    if(filter->ignoreProtectedGetter())
    {
        ++flagsCount;
        ret += zfText("ignoreProtectedGetter, ");
    }
    if(filter->ignorePrivateGetter())
    {
        ++flagsCount;
        ret += zfText("ignorePrivateGetter, ");
    }

    if(flagsCount == 0)
    {
        ret.remove(ret.length() - 1);
    }
    else
    {
        ret.remove(ret.length() - 2);
        ret += ')';
    }
}
void ZFFilterForZFProperty::objectInfoT(ZF_IN_OUT zfstring &ret) const
{
    _ZFP_ZFFilterForZFPropertyGetSettingInfo(ret, this);
    zfsuper::objectInfoT(ret);
}

/** @cond ZFPrivateDoc */ // ZFDoxygenBugFix: can't auto detect template specialization
zfbool ZFFilterForZFProperty::filterOnCheckActive(ZF_IN const ZFProperty * const &e) const
{
    if(!zfsuper::filterOnCheckActive(e)
       || !this->classFilter.filterCheckActive(e->propertyOwnerClass()))
    {
        return zffalse;
    }

    if((e->setterMethod()->methodPrivilegeType() == ZFMethodPrivilegeTypePrivate && this->ignorePrivateSetter())
       || (e->setterMethod()->methodPrivilegeType() == ZFMethodPrivilegeTypeProtected && this->ignoreProtectedSetter())
       || (e->setterMethod()->methodPrivilegeType() == ZFMethodPrivilegeTypePublic && this->ignorePublicSetter())
       || (e->getterMethod()->methodPrivilegeType() == ZFMethodPrivilegeTypePrivate && this->ignorePrivateGetter())
       || (e->getterMethod()->methodPrivilegeType() == ZFMethodPrivilegeTypeProtected && this->ignoreProtectedGetter())
       || (e->getterMethod()->methodPrivilegeType() == ZFMethodPrivilegeTypePublic && this->ignorePublicGetter()))
    {
        return zffalse;
    }

    return zftrue;
}
/** @endcond */

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForZFProperty, void, copyFrom, ZFMP_IN(ZFFilterForZFProperty const &, ref))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFFilterForZFProperty, void, filterAdd, ZFMP_IN(const ZFProperty * const &, e), ZFMP_IN_OPT(ZFFilterType, filterType, ZFFilterTypeExclude))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFFilterForZFProperty, void, filterRemove, ZFMP_IN(const ZFProperty * const &, e), ZFMP_IN_OPT(ZFFilterType, filterType, ZFFilterTypeExclude))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForZFProperty, void, filterRemoveAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFilterForZFProperty, void, filterRemoveAll)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFilterForZFProperty, zfindex, filterCount)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForZFProperty, const ZFProperty *, filterGet, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForZFProperty, ZFFilterType, filterGetFilterType, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForZFProperty, zfbool, filterCheckActive, ZFMP_IN(const ZFProperty * const &, e))

ZF_NAMESPACE_GLOBAL_END
#endif

