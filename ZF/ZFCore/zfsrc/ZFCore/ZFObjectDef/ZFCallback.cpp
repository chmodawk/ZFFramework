/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFCallback.h"
#include "ZFObjectImpl.h"

#include "ZFCore/ZFSTLWrapper/zfstl_string.h"
#include "ZFCore/ZFSTLWrapper/zfstl_map.h"
#include "ZFCore/ZFSTLWrapper/zfstl_vector.h"

ZF_NAMESPACE_GLOBAL_BEGIN

void _ZFP_ZFCallback_executeNullCallback(ZF_IN const ZFCallerInfo &callerInfo)
{
    zfCoreCriticalMessageTrim(zfTextA("try execute a null callback, created at: %s"),
        callerInfo.callerInfoA().cString());
}

// ============================================================
// _ZFP_ZFCallbackPrivate
typedef zfstlmap<zfstlstringZ, zfautoObject> _ZFP_ZFCallbackTagMap;
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCallbackPrivate
{
public:
    zfindex refCount;
    zfchar *callbackId;
    _ZFP_ZFCallbackTagMap callbackTagMap;
    ZFCallbackType callbackType;
    ZFObject *callbackOwnerObj; // assign only
    zfbool callbackOwnerObjectRetainFlag;
    const ZFMethod *callbackMethod;
    ZFFuncAddrType callbackRawFunc;
    ZFCallerInfo callbackCallerInfo;
    zfchar *serializableCustomType;
    ZFSerializableData *serializableCustomData;

public:
    _ZFP_ZFCallbackPrivate(void)
    : refCount(1)
    , callbackId(zfnull)
    , callbackTagMap()
    , callbackType(ZFCallbackTypeDummy)
    , callbackOwnerObj(zfnull)
    , callbackOwnerObjectRetainFlag(zffalse)
    , callbackMethod(zfnull)
    , callbackRawFunc(zfnull)
    , callbackCallerInfo()
    , serializableCustomType(zfnull)
    , serializableCustomData(zfnull)
    {
    }
    ~_ZFP_ZFCallbackPrivate(void)
    {
        zffree(this->callbackId);
        if(this->callbackOwnerObjectRetainFlag)
        {
            zfRelease(this->callbackOwnerObj);
        }
        zffree(this->serializableCustomType);
        zfdelete(this->serializableCustomData);
    }
};

// ============================================================
// global
static _ZFP_ZFCallbackPrivate &_ZFP_ZFCallbackNullPrivateDataRef(void)
{
    static _ZFP_ZFCallbackPrivate d;
    return d;
}
#define _ZFP_ZFCallbackNullPrivateData (&(_ZFP_ZFCallbackNullPrivateDataRef()))

static void _ZFP_ZFCallbackPrivateDataChange(_ZFP_ZFCallbackPrivate *&oldData, _ZFP_ZFCallbackPrivate *newData)
{
    _ZFP_ZFCallbackPrivate *dTmp = oldData;
    oldData = newData;
    if(newData != zfnull)
    {
        ++newData->refCount;
    }
    if(dTmp != zfnull)
    {
        --dTmp->refCount;
        if(dTmp->refCount == 0)
        {
            zfdelete(dTmp);
        }
    }
}
static void _ZFP_ZFCallbackPrivateDataReadyUpdate(_ZFP_ZFCallbackPrivate *&d)
{
    if(d == zfnull)
    {
        d = zfnew(_ZFP_ZFCallbackPrivate);
    }
    else if(d->refCount != 1)
    {
        --d->refCount;
        d = zfnew(_ZFP_ZFCallbackPrivate);
    }
}

// ============================================================
// ZFCallback
/** @cond ZFPrivateDoc */
ZFCallback::ZFCallback(void)
: d(_ZFP_ZFCallbackNullPrivateData)
{
    ++(d->refCount);
    _ZFP_ZFCallbackCachedDataSetup(*this, d);
}
ZFCallback::ZFCallback(ZF_IN const ZFCallback &ref)
: d(zfnull)
{
    this->operator =(ref);
}
ZFCallback &ZFCallback::operator =(ZF_IN const ZFCallback &ref)
{
    _ZFP_ZFCallbackPrivateDataChange(d, ref.d);
    _ZFP_ZFCallbackCachedDataSetup(*this, d);
    return *this;
}
ZFCallback::~ZFCallback(void)
{
    _ZFP_ZFCallbackPrivateDataChange(d, zfnull);
}
ZFCallback ZFCallback::_ZFP_ZFCallbackCreate(ZF_IN ZFCallbackType callbackType,
                                             ZF_IN ZFObject *callbackOwnerObj,
                                             ZF_IN const ZFMethod *callbackMethod,
                                             ZF_IN ZFFuncAddrType callbackRawFunc,
                                             ZF_IN const ZFCallerInfo &callerInfo)
{
    ZFCallback callback;
    _ZFP_ZFCallbackPrivateDataReadyUpdate(callback.d);
    callback.d->callbackCallerInfo = callerInfo;
    switch(callbackType)
    {
        case ZFCallbackTypeDummy:
            callback.d->callbackType = callbackType;
            break;
        case ZFCallbackTypeMethod:
            zfCoreAssertWithMessageTrim(callbackMethod != zfnull, zfTextA("%s method is null"),
                callerInfo.callerInfoA().cString());
            zfCoreAssertWithMessageTrim(callbackMethod->methodIsStatic(),
                zfTextA("%s method \"%s\" is not class static member type"),
                callerInfo.callerInfoA().cString(),
                zfsCoreZ2A(callbackMethod->objectInfo().cString()));
            callback.d->callbackType = callbackType;
            callback.d->callbackMethod = callbackMethod;
            break;
        case ZFCallbackTypeMemberMethod:
            zfCoreAssertWithMessageTrim(callbackOwnerObj != zfnull && callbackMethod != zfnull,
                zfTextA("%s invalid callback, ownerObj: %s, method: %s"),
                callerInfo.callerInfoA().cString(),
                zfsFromPointer<zfstringA>(callbackOwnerObj).cString(),
                zfsFromPointer<zfstringA>(callbackMethod).cString());
            zfCoreAssertWithMessageTrim(!callbackMethod->methodIsStatic(),
                zfTextA("%s method \"%s\" is not class member type"),
                callerInfo.callerInfoA().cString(),
                zfsCoreZ2A(callbackMethod->objectInfo().cString()));
            zfCoreAssertWithMessageTrim(callbackOwnerObj->classData()->classIsTypeOf(callbackMethod->methodOwnerClass()),
                zfTextA("%s object %s has no such method \"%s\""),
                callerInfo.callerInfoA().cString(),
                zfsCoreZ2A(callbackOwnerObj->objectInfoOfInstance().cString()),
                zfsCoreZ2A(callbackMethod->objectInfo().cString()));
            callback.d->callbackType = callbackType;
            callback.d->callbackOwnerObj = callbackOwnerObj;
            callback.d->callbackMethod = callbackMethod;
            break;
        case ZFCallbackTypeRawFunction:
            zfCoreAssertWithMessageTrim(callbackRawFunc != zfnull, zfTextA("%s invalid function address"),
                callerInfo.callerInfoA().cString());
            callback.d->callbackType = callbackType;
            callback.d->callbackRawFunc = callbackRawFunc;
            break;
        default:
            zfCoreCriticalShouldNotGoHere();
            break;
    }
    _ZFP_ZFCallbackCachedDataSetup(callback, callback.d);
    return callback;
}
/** @endcond */

zfindex ZFCallback::objectRetainCount(void) const
{
    return d->refCount;
}

void ZFCallback::objectInfoT(ZF_IN_OUT zfstring &ret) const
{
    switch(this->callbackType())
    {
        case ZFCallbackTypeDummy:
            ret += zfText("ZFCallbackNull");
            break;
        case ZFCallbackTypeMethod:
        case ZFCallbackTypeMemberMethod:
            this->callbackMethod()->objectInfoT(ret);
            break;
        case ZFCallbackTypeRawFunction:
            ret += ZFTOKEN_ZFObjectInfoLeft;
            ret += zfText("ZFCallback func: ");
            zfsFromPointerT(ret, ZFCastReinterpret(const void *, this->callbackFunctionAddr()));
            ret += ZFTOKEN_ZFObjectInfoRight;
            break;
        default:
            zfCoreCriticalShouldNotGoHere();
            break;
    }
}

ZFCompareResult ZFCallback::objectCompare(ZF_IN const ZFCallback &ref) const
{
    return ((d == ref.d || (
            this->callbackType() == ref.callbackType()
            && this->callbackOwnerObject() == ref.callbackOwnerObject()
            && this->callbackMethod() == ref.callbackMethod()
            && this->callbackFunctionAddr() == ref.callbackFunctionAddr()
            ))
        ? ZFCompareTheSame : ZFCompareUncomparable);
}
ZFCompareResult ZFCallback::objectCompareByInstance(ZF_IN const ZFCallback &ref) const
{
    return ((d == ref.d) ? ZFCompareTheSame : ZFCompareUncomparable);
}

void ZFCallback::callbackIdSet(ZF_IN const zfchar *callbackId)
{
    if(callbackId != zfnull && *callbackId == '\0')
    {
        callbackId = zfnull;
    }
    zfsChange(d->callbackId, callbackId);
}
const zfchar *ZFCallback::callbackId(void) const
{
    return d->callbackId;
}

void ZFCallback::callbackTagSet(ZF_IN const zfchar *key,
                                ZF_IN ZFObject *tag,
                                ZF_IN_OPT zfbool autoMarkCached /* = zffalse */)
{
    if(key == zfnull)
    {
        return ;
    }
    // not allowed to add to global null callback,
    // check and create new one if necessary
    if(d == _ZFP_ZFCallbackNullPrivateData)
    {
        _ZFP_ZFCallbackPrivateDataReadyUpdate(d);
    }

    _ZFP_ZFCallbackTagMap &m = d->callbackTagMap;
    _ZFP_ZFCallbackTagMap::iterator it = m.find(key);
    if(it == m.end())
    {
        if(tag != zfnull)
        {
            if(autoMarkCached)
            {
                m[key] = zfautoObjectCreateMarkCached(tag);
            }
            else
            {
                m[key] = zfautoObjectCreate(tag);
            }
        }
    }
    else
    {
        if(tag == zfnull)
        {
            zfautoObject holder = it->second;
            ZFUNUSED(holder);
            m.erase(it);
        }
        else
        {
            zfautoObject holder = it->second;
            ZFUNUSED(holder);
            if(autoMarkCached)
            {
                it->second = zfautoObjectCreateMarkCached(tag);
            }
            else
            {
                it->second = zfautoObjectCreate(tag);
            }
        }
    }
}
ZFObject *ZFCallback::callbackTagGet(ZF_IN const zfchar *key) const
{
    if(key != zfnull)
    {
        _ZFP_ZFCallbackTagMap &m = d->callbackTagMap;
        _ZFP_ZFCallbackTagMap::iterator it = m.find(key);
        if(it != m.end())
        {
            return it->second.toObject();
        }
    }
    return zfnull;
}
void ZFCallback::callbackTagGetAllKeyValue(ZF_IN_OUT ZFCoreArray<const zfchar *> &allKey,
                                           ZF_IN_OUT ZFCoreArray<ZFObject *> &allValue) const
{
    _ZFP_ZFCallbackTagMap &m = d->callbackTagMap;
    allKey.capacitySet(allKey.count() + m.size());
    allValue.capacitySet(allValue.count() + m.size());
    for(_ZFP_ZFCallbackTagMap::iterator it = m.begin(); it != m.end(); ++it)
    {
        allKey.add(it->first.c_str());
        allValue.add(it->second.toObject());
    }
}
zfautoObject ZFCallback::callbackTagRemoveAndGet(ZF_IN const zfchar *key)
{
    if(key != zfnull)
    {
        _ZFP_ZFCallbackTagMap &m = d->callbackTagMap;
        _ZFP_ZFCallbackTagMap::iterator it = m.find(key);
        if(it != m.end())
        {
            zfautoObject ret = zfautoObjectCreate(it->second.toObject());
            m.erase(it);
            return ret;
        }
    }
    return zfautoObjectNull;
}
void ZFCallback::callbackTagRemoveAll(void)
{
    if(!d->callbackTagMap.empty())
    {
        _ZFP_ZFCallbackTagMap tmp;
        tmp.swap(d->callbackTagMap);
    }
}

ZFCallbackType ZFCallback::callbackType(void) const
{
    return d->callbackType;
}

ZFObject *ZFCallback::callbackOwnerObject(void) const
{
    return d->callbackOwnerObj;
}

const ZFMethod *ZFCallback::callbackMethod(void) const
{
    return d->callbackMethod;
}

ZFFuncAddrType ZFCallback::callbackFunctionAddr(void) const
{
    return d->callbackRawFunc;
}

void ZFCallback::callbackCallerInfoSet(ZF_IN const ZFCallerInfo &callerInfo)
{
    d->callbackCallerInfo = callerInfo;
}

const ZFCallerInfo &ZFCallback::callbackCallerInfo(void) const
{
    return d->callbackCallerInfo;
}

void ZFCallback::callbackClear(void)
{
    _ZFP_ZFCallbackPrivateDataChange(d, _ZFP_ZFCallbackNullPrivateData);
}

void ZFCallback::callbackOwnerObjectRetain(void) const
{
    if(d->callbackOwnerObj != zfnull && !d->callbackOwnerObjectRetainFlag)
    {
        zfRetain(d->callbackOwnerObj);
        d->callbackOwnerObjectRetainFlag = zftrue;
    }
}
void ZFCallback::callbackOwnerObjectRelease(void) const
{
    if(d->callbackOwnerObjectRetainFlag)
    {
        d->callbackOwnerObjectRetainFlag = zffalse;
        zfRelease(d->callbackOwnerObj);
    }
}

void ZFCallback::callbackSerializeCustomTypeSet(ZF_IN const zfchar *customType)
{
    zfsChange(d->serializableCustomType, customType);
}
const zfchar *ZFCallback::callbackSerializeCustomType(void) const
{
    return d->serializableCustomType;
}
void ZFCallback::callbackSerializeCustomDataSet(ZF_IN const ZFSerializableData *customData)
{
    if(customData == zfnull)
    {
        if(d->serializableCustomData != zfnull)
        {
            zfdelete(d->serializableCustomData);
            d->serializableCustomData = zfnull;
        }
    }
    else
    {
        if(d->serializableCustomData != zfnull)
        {
            *(d->serializableCustomData) = *customData;
        }
        else
        {
            d->serializableCustomData = zfnew(ZFSerializableData, *customData);
        }
    }
}
const ZFSerializableData *ZFCallback::callbackSerializeCustomData(void) const
{
    return d->serializableCustomData;
}

void ZFCallback::_ZFP_ZFCallbackCachedDataSetup(ZF_IN_OUT ZFCallback &c, _ZFP_ZFCallbackPrivate *d)
{
    switch(d->callbackType)
    {
        case ZFCallbackTypeDummy:
            c._ZFP_ZFCallbackCached_callbackType = _ZFP_ZFCallbackCachedTypeDummy;
            c._ZFP_ZFCallbackCached_callbackOwnerObj = zfnull;
            break;
        case ZFCallbackTypeMethod:
            c._ZFP_ZFCallbackCached_callbackType = _ZFP_ZFCallbackCachedTypeClassMember;
            c._ZFP_ZFCallbackCached_callbackOwnerObj = zfnull;
            break;
        case ZFCallbackTypeMemberMethod:
            c._ZFP_ZFCallbackCached_callbackType = _ZFP_ZFCallbackCachedTypeClassMember;
            c._ZFP_ZFCallbackCached_callbackOwnerObj = d->callbackOwnerObj;
            break;
        case ZFCallbackTypeRawFunction:
            c._ZFP_ZFCallbackCached_callbackType = _ZFP_ZFCallbackCachedTypeRawFunction;
            c._ZFP_ZFCallbackCached_callbackOwnerObj = zfnull;
            break;
        default:
            zfCoreCriticalShouldNotGoHere();
            break;
    }
}
ZFFuncAddrType ZFCallback::_ZFP_ZFCallbackCached_callbackInvoker_method(void) const
{
    return d->callbackMethod->methodInvoker();
}
ZFFuncAddrType ZFCallback::_ZFP_ZFCallbackCached_callbackInvoker_rawFunction(void) const
{
    return d->callbackRawFunc;
}

ZF_NAMESPACE_GLOBAL_END

#if 1 // ZFObject related method register
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFCallback, void, callbackIdSet, ZFMP_IN(const zfchar *, callbackId))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFCallback, const zfchar *, callbackId)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_3(v_ZFCallback, void, callbackTagSet, ZFMP_IN(const zfchar *, key), ZFMP_IN(ZFObject *, tag), ZFMP_IN_OPT(zfbool, autoMarkCached, zffalse))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFCallback, void, callbackTagSetMarkCached, ZFMP_IN(const zfchar *, key), ZFMP_IN(ZFObject *, tag))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFCallback, ZFObject *, callbackTagGet, ZFMP_IN(const zfchar *, key))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFCallback, void, callbackTagGetAllKeyValue, ZFMP_IN_OUT(ZFCoreArray<const zfchar *> &, allKey), ZFMP_IN_OUT(ZFCoreArray<ZFObject *> &, allValue))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFCallback, void, callbackTagRemove, ZFMP_IN(const zfchar *, key))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFCallback, zfautoObject, callbackTagRemoveAndGet, ZFMP_IN(const zfchar *, key))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFCallback, void, callbackTagRemoveAll)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFCallback, zfbool, callbackIsValid)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFCallback, ZFCallbackType, callbackType)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFCallback, ZFObject *, callbackOwnerObject)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFCallback, const ZFMethod *, callbackMethod)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFCallback, ZFFuncAddrType, callbackFunctionAddr)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFCallback, void, callbackCallerInfoSet, ZFMP_IN(const ZFCallerInfo &, callerInfo))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFCallback, const ZFCallerInfo &, callbackCallerInfo)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFCallback, void, callbackClear)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFCallback, void, callbackOwnerObjectRetain)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFCallback, void, callbackOwnerObjectRelease)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFCallback, void, callbackSerializeCustomTypeSet, ZFMP_IN(const zfchar *, customType))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFCallback, const zfchar *, callbackSerializeCustomType)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFCallback, void, callbackSerializeCustomDataSet, ZFMP_IN(const ZFSerializableData &, customData))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFCallback, const ZFSerializableData *, callbackSerializeCustomData)

// ============================================================
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(ZFCallback, ZFCallbackNullDetail, ZFMP_IN(const ZFCallerInfo &, callerInfo))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_0(ZFCallback, ZFCallbackNull)
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(ZFCallback, ZFCallbackForMethodDetail, ZFMP_IN(const ZFMethod *, zfmethod), ZFMP_IN(const ZFCallerInfo &, callerInfo))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(ZFCallback, ZFCallbackForMethod, ZFMP_IN(const ZFMethod *, zfmethod))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_3(ZFCallback, ZFCallbackForMemberMethodDetail, ZFMP_IN(ZFObject *, obj), ZFMP_IN(const ZFMethod *, zfmethod), ZFMP_IN(const ZFCallerInfo &, callerInfo))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(ZFCallback, ZFCallbackForMemberMethod, ZFMP_IN(ZFObject *, obj), ZFMP_IN(const ZFMethod *, zfmethod))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(ZFCallback, ZFCallbackForRawFunctionDetail, ZFMP_IN(ZFFuncAddrType, callbackRawFunc), ZFMP_IN(const ZFCallerInfo &, callerInfo))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(ZFCallback, ZFCallbackForRawFunction, ZFMP_IN(ZFFuncAddrType, callbackRawFunc))

ZF_NAMESPACE_GLOBAL_END
#endif

