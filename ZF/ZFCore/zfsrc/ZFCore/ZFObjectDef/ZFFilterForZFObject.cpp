/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFFilterForZFObject.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
ZFFilterForZFObject::ZFFilterForZFObject(void)
: zfsuper()
, classFilter()
{
}
ZFFilterForZFObject::ZFFilterForZFObject(ZF_IN const ZFFilterForZFObject &ref)
: zfsuper(ref)
, classFilter(ref.classFilter)
{
}
ZFFilterForZFObject &ZFFilterForZFObject::operator =(ZF_IN const ZFFilterForZFObject &ref)
{
    zfsuper::operator =(ref);
    this->classFilter = ref.classFilter;
    return *this;
}
ZFFilterForZFObject::~ZFFilterForZFObject(void)
{
    for(zfindex i = 0; i < this->filterCount(); ++i)
    {
        zfRelease(this->filterGetInternal(i));
    }
}

/** @cond ZFPrivateDoc */
void ZFFilterForZFObject::copyFrom(ZF_IN ZFFilterForZFObject const &ref)
{
    zfsuper::copyFrom(ref);
    for(zfindex i = 0; i < this->filterCount(); ++i)
    {
        zfRetain(this->filterGetInternal(i));
    }
    this->classFilter.copyFrom(ref.classFilter);
}
/** @endcond */

/** @cond ZFPrivateDoc */ // ZFDoxygenBugFix: can't auto detect template specialization
void ZFFilterForZFObject::filterOnStore(ZF_IN_OUT ZFObject * &to,
                                        ZF_IN ZFObject * const &from) const
{
    to = zfRetain(from);
}
void ZFFilterForZFObject::filterOnRemove(ZF_IN_OUT ZFObject * &value) const
{
    zfRelease(value);
}
zfbool ZFFilterForZFObject::filterOnCheckEqual(ZF_IN ZFObject * const &e1,
                                               ZF_IN ZFObject * const &e2) const
{
    return (ZFObjectCompare(e1, e2) == ZFCompareTheSame);
}
zfbool ZFFilterForZFObject::filterOnCheckActive(ZF_IN ZFObject * const &e) const
{
    if(!zfsuper::filterOnCheckActive(e))
    {
        return zffalse;
    }
    return this->classFilter.filterCheckActive(e ? e->classData() : zfnull);
}
/** @endcond */

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForZFObject, void, copyFrom, ZFMP_IN(ZFFilterForZFObject const &, ref))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFFilterForZFObject, void, filterAdd, ZFMP_IN(ZFObject * const &, e), ZFMP_IN_OPT(ZFFilterType, filterType, ZFFilterTypeExclude))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFFilterForZFObject, void, filterRemove, ZFMP_IN(ZFObject * const &, e), ZFMP_IN_OPT(ZFFilterType, filterType, ZFFilterTypeExclude))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForZFObject, void, filterRemoveAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFilterForZFObject, void, filterRemoveAll)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFilterForZFObject, zfindex, filterCount)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForZFObject, ZFObject *, filterGet, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForZFObject, ZFFilterType, filterGetFilterType, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForZFObject, zfbool, filterCheckActive, ZFMP_IN(ZFObject * const &, e))

ZF_NAMESPACE_GLOBAL_END
#endif

