/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFFilterForZFMethod.h"
#include "ZFMethod.h"

ZF_NAMESPACE_GLOBAL_BEGIN

static void _ZFP_ZFFilterForZFMethodGetSettingInfo(ZF_OUT zfstring &ret,
                                                   ZF_IN const ZFFilterForZFMethod *filter)
{
    ret += '(';
    zfindex flagsCount = 0;
    if(filter->ignorePublic())
    {
        ++flagsCount;
        ret += zfText("ignorePublic, ");
    }
    if(filter->ignoreProtected())
    {
        ++flagsCount;
        ret += zfText("ignoreProtected, ");
    }
    if(filter->ignorePrivate())
    {
        ++flagsCount;
        ret += zfText("ignorePrivate, ");
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
void ZFFilterForZFMethod::objectInfoT(ZF_IN_OUT zfstring &ret) const
{
    _ZFP_ZFFilterForZFMethodGetSettingInfo(ret, this);
    zfsuper::objectInfoT(ret);
}

/** @cond ZFPrivateDoc */ // ZFDoxygenBugFix: can't auto detect template specialization
zfbool ZFFilterForZFMethod::filterOnCheckActive(ZF_IN const ZFMethod * const &e) const
{
    if(!zfsuper::filterOnCheckActive(e)
       || !this->classFilter.filterCheckActive(e->methodOwnerClass()))
    {
        return zffalse;
    }

    if((e->methodPrivilegeType() == ZFMethodPrivilegeTypePrivate && this->ignorePrivate())
       || (e->methodPrivilegeType() == ZFMethodPrivilegeTypeProtected && this->ignoreProtected())
       || (e->methodPrivilegeType() == ZFMethodPrivilegeTypePublic && this->ignorePublic()))
    {
        return zffalse;
    }

    return zftrue;
}
/** @endcond */

ZF_NAMESPACE_GLOBAL_END

