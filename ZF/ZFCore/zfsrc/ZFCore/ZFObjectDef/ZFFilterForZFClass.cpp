/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFFilterForZFClass.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
ZFFilterForZFClass::ZFFilterForZFClass(void)
: _ZFP_ZFFilterForZFClass_filters()
, _ZFP_ZFFilterForZFClass_customFilterCallbacks()
{
}
ZFFilterForZFClass::ZFFilterForZFClass(ZF_IN const ZFFilterForZFClass &ref)
: _ZFP_ZFFilterForZFClass_filters(ref._ZFP_ZFFilterForZFClass_filters)
, _ZFP_ZFFilterForZFClass_customFilterCallbacks(ref._ZFP_ZFFilterForZFClass_customFilterCallbacks)
{
}
ZFFilterForZFClass &ZFFilterForZFClass::operator = (ZF_IN const ZFFilterForZFClass &ref)
{
    this->_ZFP_ZFFilterForZFClass_filters = ref._ZFP_ZFFilterForZFClass_filters;
    this->_ZFP_ZFFilterForZFClass_customFilterCallbacks = ref._ZFP_ZFFilterForZFClass_customFilterCallbacks;
    return *this;
}
/** @cond ZFPrivateDoc */
zfbool ZFFilterForZFClass::operator == (ZF_IN const ZFFilterForZFClass &ref) const
{
    return this->_ZFP_ZFFilterForZFClass_filters == ref._ZFP_ZFFilterForZFClass_filters;
}
/** @endcond */
ZFFilterForZFClass::~ZFFilterForZFClass(void)
{
}
void ZFFilterForZFClass::copyFrom(ZF_IN ZFFilterForZFClass const &ref)
{
    this->_ZFP_ZFFilterForZFClass_filters.copyFrom(ref._ZFP_ZFFilterForZFClass_filters);
    this->_ZFP_ZFFilterForZFClass_customFilterCallbacks.copyFrom(ref._ZFP_ZFFilterForZFClass_customFilterCallbacks);
}

ZFFilterForZFClass &ZFFilterForZFClass::filterAdd(ZF_IN const ZFClass * const &e,
                                                  ZF_IN_OPT ZFFilterForZFClassType filterType /* = ZFFilterForZFClassTypeExclude */)
{
    _ZFP_ZFFilterForZFClassData filterData;
    filterData.filterClass = e;
    filterData.filterType = filterType;
    this->_ZFP_ZFFilterForZFClass_filters.add(filterData);
    return *this;
}
ZFFilterForZFClass &ZFFilterForZFClass::filterRemove(ZF_IN const ZFClass * const &e,
                                                     ZF_IN_OPT ZFFilterForZFClassType filterType /* = ZFFilterForZFClassTypeExclude */)
{
    for(zfindex i = 0; i < this->_ZFP_ZFFilterForZFClass_filters.count(); ++i)
    {
        if(this->_ZFP_ZFFilterForZFClass_filters.get(i).filterClass == e && this->_ZFP_ZFFilterForZFClass_filters.get(i).filterType == filterType)
        {
            this->_ZFP_ZFFilterForZFClass_filters.remove(i);
            break;
        }
    }
    return *this;
}
ZFFilterForZFClass &ZFFilterForZFClass::filterRemoveAtIndex(ZF_IN zfindex index)
{
    this->_ZFP_ZFFilterForZFClass_filters.remove(index);
    return *this;
}
ZFFilterForZFClass &ZFFilterForZFClass::filterRemoveAll(void)
{
    this->_ZFP_ZFFilterForZFClass_filters.removeAll();
    return *this;
}

zfindex ZFFilterForZFClass::filterCount(void) const
{
    return this->_ZFP_ZFFilterForZFClass_filters.count();
}
const ZFClass *ZFFilterForZFClass::filterGet(ZF_IN zfindex index) const
{
    return this->_ZFP_ZFFilterForZFClass_filters.get(index).filterClass;
}
ZFFilterForZFClassType ZFFilterForZFClass::filterGetFilterType(ZF_IN zfindex index) const
{
    return this->_ZFP_ZFFilterForZFClass_filters.get(index).filterType;
}

ZFFilterForZFClass &ZFFilterForZFClass::customFilterCallbackAdd(ZF_IN ZFFilterForZFClass::CustomFilterCallback customFilterCallback)
{
    this->_ZFP_ZFFilterForZFClass_customFilterCallbacks.add(customFilterCallback);
    return *this;
}
ZFFilterForZFClass &ZFFilterForZFClass::customFilterCallbackRemove(ZF_IN ZFFilterForZFClass::CustomFilterCallback customFilterCallback)
{
    for(zfiterator it = this->_ZFP_ZFFilterForZFClass_customFilterCallbacks.iterator();
        this->_ZFP_ZFFilterForZFClass_customFilterCallbacks.iteratorIsValid(it);
        this->_ZFP_ZFFilterForZFClass_customFilterCallbacks.iteratorNext(it))
    {
        if(this->_ZFP_ZFFilterForZFClass_customFilterCallbacks.iteratorGet(it) == customFilterCallback)
        {
            this->_ZFP_ZFFilterForZFClass_customFilterCallbacks.iteratorRemove(it);
            break;
        }
    }
    return *this;
}
ZFFilterForZFClass &ZFFilterForZFClass::customFilterCallbackRemove(ZF_IN zfindex index)
{
    this->_ZFP_ZFFilterForZFClass_customFilterCallbacks.remove(index);
    return *this;
}
zfindex ZFFilterForZFClass::customFilterCallbackCount(void) const
{
    return this->_ZFP_ZFFilterForZFClass_customFilterCallbacks.count();
}
ZFFilterForZFClass::CustomFilterCallback ZFFilterForZFClass::customFilterCallbackAtIndex(ZF_IN zfindex index) const
{
    return this->_ZFP_ZFFilterForZFClass_customFilterCallbacks.get(index);
}

zfbool ZFFilterForZFClass::filterCheckActive(ZF_IN const ZFClass * const &e) const
{
    for(zfindex i = 0, count = this->_ZFP_ZFFilterForZFClass_customFilterCallbacks.count(); i < count; ++i)
    {
        switch(this->_ZFP_ZFFilterForZFClass_customFilterCallbacks.get(i)(e))
        {
            case ZFFilterCallbackResultNotSpecified:
                break;
            case ZFFilterCallbackResultActive:
                return zftrue;
            case ZFFilterCallbackResultNotActive:
                return zffalse;
            default:
                zfCoreCriticalShouldNotGoHere();
                break;
        }
    }

    zfbool hasIncludeMode = zffalse;
    zfbool included = zffalse;
    for(zfindex i = 0, count = this->_ZFP_ZFFilterForZFClass_filters.count(); i < count; ++i)
    {
        const _ZFP_ZFFilterForZFClassData &filter = this->_ZFP_ZFFilterForZFClass_filters.get(i);
        switch(filter.filterType)
        {
            case ZFFilterForZFClassTypeInclude:
                hasIncludeMode = zftrue;
                if(filter.filterClass == e)
                {
                    included = zftrue;
                }
                break;
            case ZFFilterForZFClassTypeExclude:
                if(filter.filterClass == e)
                {
                    return zffalse;
                }
                break;
            case ZFFilterForZFClassTypeIncludeChildOf:
                if(e == zfnull || !e->classIsTypeOf(filter.filterClass))
                {
                    return zffalse;
                }
                break;
            case ZFFilterForZFClassTypeIncludeParentOf:
                if(e == zfnull || !filter.filterClass->classIsTypeOf(e))
                {
                    return zffalse;
                }
                break;
            case ZFFilterForZFClassTypeExcludeChildOf:
                if(e != zfnull && e->classIsTypeOf(filter.filterClass))
                {
                    return zffalse;
                }
                break;
            case ZFFilterForZFClassTypeExcludeParentOf:
                if(e != zfnull && filter.filterClass->classIsTypeOf(e))
                {
                    return zffalse;
                }
                break;
            default:
                zfCoreCriticalShouldNotGoHere();
                return zffalse;
        }
    }
    return (!hasIncludeMode || included);
}

static void _ZFP_ZFFilterForZFClass_contentInfoGetter(ZF_IN_OUT zfstring &ret, ZF_IN const _ZFP_ZFFilterForZFClassData &v)
{
    ret += '(';
    ZFFilterForZFClassTypeToString(ret, v.filterType);
    ret += ' ';
    ret += v.filterClass->className();
    ret += ')';
}
void ZFFilterForZFClass::objectInfoT(ZF_IN_OUT zfstring &ret) const
{
    this->_ZFP_ZFFilterForZFClass_filters.objectInfoOfContentT(ret,
        _ZFP_ZFFilterForZFClass_contentInfoGetter,
        zfHint("max count")5,
        ZFTokenForContainerDefault());
}

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForZFClass, void, copyFrom, ZFMP_IN(ZFFilterForZFClass const &, ref))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFFilterForZFClass, void, filterAdd, ZFMP_IN(const ZFClass * const &, e), ZFMP_IN_OPT(ZFFilterForZFClassType, filterType, ZFFilterForZFClassTypeExclude))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFFilterForZFClass, void, filterRemove, ZFMP_IN(const ZFClass * const &, e), ZFMP_IN_OPT(ZFFilterForZFClassType, filterType, ZFFilterForZFClassTypeExclude))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForZFClass, void, filterRemoveAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFilterForZFClass, void, filterRemoveAll)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFilterForZFClass, zfindex, filterCount)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForZFClass, const ZFClass *, filterGet, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForZFClass, ZFFilterForZFClassType, filterGetFilterType, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForZFClass, zfbool, filterCheckActive, ZFMP_IN(const ZFClass * const &, e))

ZF_NAMESPACE_GLOBAL_END
#endif

