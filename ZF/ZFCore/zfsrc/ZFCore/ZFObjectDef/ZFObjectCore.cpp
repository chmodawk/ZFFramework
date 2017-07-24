/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFObjectSmartPointer.h"
#include "ZFObjectImpl.h"
#include "ZFSynchronize.h"

#include "ZFCore/ZFSTLWrapper/zfstl_string.h"
#include "ZFCore/ZFSTLWrapper/zfstl_map.h"
#include "ZFCore/ZFSTLWrapper/zfstl_vector.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// _ZFP_ZFObjectPrivate
typedef zfstlmap<zfstlstringZ, zfautoObject> _ZFP_ZFObjectTagMapType;
zfclassNotPOD _ZFP_ZFObjectPrivate
{
public:
    zfuint objectRetainCount;
    ZFObjectInstanceState objectInstanceState;
    ZFObjectHolder *objectHolder;
    zfbool mutexImplAvailable;
    ZFObjectMutexImpl *mutexImpl;
    _ZFP_ZFObjectTagMapType tagMap;
    ZFObserverHolder observerHolder;
    zfuint observerNotifyingFlag;
    zfbool objectIsPrivate;
    zfbool objectIsInternal;
    zfuint objectCachedFlag;
    zfstlvector<const ZFProperty *> propertyAccessed;
    zfbool observerHasAddFlag_objectAfterAlloc;
    zfbool observerHasAddFlag_objectBeforeDealloc;
    zfbool observerHasAddFlag_objectPropertyValueOnUpdate;
    zfbool observerHasAddFlag_objectCachedOnChange;

public:
    _ZFP_ZFObjectPrivate(void)
    : objectRetainCount(1)
    , objectInstanceState(ZFObjectInstanceStateOnInit)
    , objectHolder(zfnull)
    , mutexImplAvailable(_ZFP_ZFObjectMutexImplCheckCallbackRef != zfnull && _ZFP_ZFObjectMutexImplCheckCallbackRef())
    , mutexImpl(zfnull)
    , tagMap()
    , observerHolder()
    , observerNotifyingFlag(0)
    , objectIsPrivate(zffalse)
    , objectIsInternal(zffalse)
    , objectCachedFlag(0)
    , propertyAccessed()
    , observerHasAddFlag_objectAfterAlloc(zffalse)
    , observerHasAddFlag_objectBeforeDealloc(zffalse)
    , observerHasAddFlag_objectPropertyValueOnUpdate(zffalse)
    , observerHasAddFlag_objectCachedOnChange(zffalse)
    {
    }
};

// ============================================================
// ZFObject
ZFOBJECT_REGISTER(ZFObject)

ZFOBSERVER_EVENT_REGISTER(ZFObject, ObjectAfterAlloc)
ZFOBSERVER_EVENT_REGISTER(ZFObject, ObjectBeforeDealloc)
ZFOBSERVER_EVENT_REGISTER(ZFObject, ObjectPropertyValueOnUpdate)
ZFOBSERVER_EVENT_REGISTER(ZFObject, ObjectCachedOnChange)

zfindex ZFObject::objectRetainCount(void)
{
    return (zfindex)d->objectRetainCount;
}

ZFObjectHolder *ZFObject::objectHolder(void)
{
    if(d->objectHolder == zfnull)
    {
        d->objectHolder = zfAllocWithoutLeakTest(ZFObjectHolder, this);
        d->objectHolder->objectCachedSet(zftrue);
    }
    return d->objectHolder;
}

void ZFObject::objectInfoOfInstanceT(ZF_IN_OUT zfstring &ret)
{
    ret += this->classData()->className();
    ret += zfText("(");
    zfsFromPointerT(ret, this);
    ret += zfText(")");
}
void ZFObject::objectInfoT(ZF_IN_OUT zfstring &ret)
{
    this->objectInfoOnAppendTokenLeft(ret);
    this->objectInfoOnAppend(ret);
    this->objectInfoOnAppendTokenRight(ret);
}
void ZFObject::objectInfoOnAppend(ZF_IN_OUT zfstring &ret)
{
    this->objectInfoOfInstanceT(ret);
}
zfidentity ZFObject::objectHash(void)
{
    return zfidentityCalcPointer(this);
}
ZFCompareResult ZFObject::objectCompare(ZF_IN ZFObject *anotherObj)
{
    return ((this == anotherObj) ? ZFCompareTheSame : ZFCompareUncomparable);
}

zfbool ZFObject::tagHasSet(void)
{
    zfCoreMutexLocker();
    return !(d->tagMap.empty());
}
void ZFObject::tagSet(ZF_IN const zfchar *key,
                      ZF_IN ZFObject *tag,
                      ZF_IN_OPT zfbool autoMarkCached /* = zffalse */)
{
    zfCoreMutexLocker();
    if(ZFBitTest(d->objectInstanceState, ZFObjectInstanceStateOnDealloc) && tag != zfnull)
    {
        zfCoreCriticalMessageTrim(zfTextA("[ZFObject] you must not set tag while object is deallocating, class: %s, tag: %s"),
            zfsCoreZ2A(this->classData()->className()),
            zfsCoreZ2A(key));
        return ;
    }
    if(key == zfnull)
    {
        return ;
    }

    if(this->objectCached() && tag != zfnull)
    {
        tag->objectCachedSet(zftrue);
    }

    _ZFP_ZFObjectTagMapType &m = d->tagMap;
    _ZFP_ZFObjectTagMapType::iterator it = m.find(key);
    if(it == m.end())
    {
        if(tag != zfnull)
        {
            if(autoMarkCached)
            {
                m[key] = zflockfree_zfautoObjectCreateMarkCached(tag);
            }
            else
            {
                m[key] = zflockfree_zfautoObjectCreate(tag);
            }
        }
    }
    else
    {
        zfautoObject holder = it->second;
        if(tag == zfnull)
        {
            m.erase(it);
        }
        else
        {
            if(autoMarkCached)
            {
                it->second = zflockfree_zfautoObjectCreateMarkCached(tag);
            }
            else
            {
                it->second = zflockfree_zfautoObjectCreate(tag);
            }
        }
        if(this->objectCached())
        {
            holder.toObject()->objectCachedSet(zffalse);
        }
    }
}
ZFObject *ZFObject::tagGet(ZF_IN const zfchar *key)
{
    if(key == zfnull)
    {
        return zfnull;
    }
    zfCoreMutexLocker();
    _ZFP_ZFObjectTagMapType::iterator it = d->tagMap.find(key);
    if(it != d->tagMap.end())
    {
        return it->second.toObject();
    }
    else
    {
        return zfnull;
    }
}
void ZFObject::tagGetAllKeyValue(ZF_IN_OUT ZFCoreArray<const zfchar *> &allKey,
                                 ZF_IN_OUT ZFCoreArray<ZFObject *> &allValue)
{
    zfCoreMutexLocker();
    _ZFP_ZFObjectTagMapType &m = d->tagMap;
    allKey.capacitySet(allKey.count() + m.size());
    allValue.capacitySet(allValue.count() + m.size());
    for(_ZFP_ZFObjectTagMapType::iterator it = m.begin(); it != m.end(); ++it)
    {
        allKey.add(it->first.c_str());
        allValue.add(it->second.toObject());
    }
}
zfautoObject ZFObject::tagRemoveAndGet(ZF_IN const zfchar *key)
{
    if(key != zfnull)
    {
        zfCoreMutexLocker();
        _ZFP_ZFObjectTagMapType::iterator it = d->tagMap.find(key);
        if(it != d->tagMap.end())
        {
            zfautoObject ret = zfautoObjectCreate(it->second.toObject());
            d->tagMap.erase(it);
            return ret;
        }
    }
    return zfautoObjectNull;
}
void ZFObject::tagRemoveAll(void)
{
    zfCoreMutexLocker();
    if(!d->tagMap.empty())
    {
        _ZFP_ZFObjectTagMapType tmp;
        tmp.swap(d->tagMap);
    }
}

const ZFObserverHolder &ZFObject::observerHolder(void)
{
    return d->observerHolder;
}
void ZFObject::observerAdd(ZF_IN const zfidentity &eventId,
                           ZF_IN const ZFListener &observer,
                           ZF_IN_OPT ZFObject *userData /* = zfnull */,
                           ZF_IN_OPT ZFObject *owner /* = zfnull */,
                           ZF_IN_OPT zfbool autoRemoveAfterActivate /* = zffalse */,
                           ZF_IN_OPT ZFLevel observerLevel /* = ZFLevelAppNormal */)
{
    zfCoreMutexLocker();
    if(ZFBitTest(d->objectInstanceState, ZFObjectInstanceStateOnDealloc))
    {
        zfCoreCriticalMessageTrim(zfTextA("[ZFObject] you must not add observer while object is deallocating, class: %s, event: %s"),
            zfsCoreZ2A(this->classData()->className()),
            ZFObserverEventGetName(eventId));
        return ;
    }

    this->observerHolder().observerAdd(eventId, observer, userData, owner, autoRemoveAfterActivate, observerLevel);
}

void ZFObject::_ZFP_ZFObject_observerNotifyBegin(void)
{
    ++(d->observerNotifyingFlag);
}
void ZFObject::_ZFP_ZFObject_observerNotifyEnd(void)
{
    --(d->observerNotifyingFlag);
}

void ZFObject::observerOnAdd(ZF_IN const zfidentity &eventId)
{
    if(zffalse)
    {
    }
    else if(eventId == ZFObject::EventObjectAfterAlloc())
    {
        d->observerHasAddFlag_objectAfterAlloc = zftrue;
    }
    else if(eventId == ZFObject::EventObjectBeforeDealloc())
    {
        d->observerHasAddFlag_objectBeforeDealloc = zftrue;
    }
    else if(eventId == ZFObject::EventObjectPropertyValueOnUpdate())
    {
        d->observerHasAddFlag_objectPropertyValueOnUpdate = zftrue;
    }
    else if(eventId == ZFObject::EventObjectCachedOnChange())
    {
        d->observerHasAddFlag_objectCachedOnChange = zftrue;
    }
}
void ZFObject::observerOnRemove(ZF_IN const zfidentity &eventId)
{
    if(zffalse)
    {
    }
    else if(eventId == ZFObject::EventObjectAfterAlloc())
    {
        d->observerHasAddFlag_objectAfterAlloc = zffalse;
    }
    else if(eventId == ZFObject::EventObjectBeforeDealloc())
    {
        d->observerHasAddFlag_objectBeforeDealloc = zffalse;
    }
    else if(eventId == ZFObject::EventObjectPropertyValueOnUpdate())
    {
        d->observerHasAddFlag_objectPropertyValueOnUpdate = zffalse;
    }
    else if(eventId == ZFObject::EventObjectCachedOnChange())
    {
        d->observerHasAddFlag_objectCachedOnChange = zffalse;
    }
}

zfbool ZFObject::_ZFP_ZFObjectLockIsAvailable(void)
{
    return d->mutexImplAvailable;
}
void ZFObject::_ZFP_ZFObjectLock(void)
{
    if(d->mutexImpl)
    {
        d->mutexImpl->mutexImplLock();
    }
    else if(d->mutexImplAvailable)
    {
        zfCoreMutexLock();
        if(d->mutexImpl == zfnull)
        {
            d->mutexImpl = _ZFP_ZFObjectMutexImplInitCallbackRef();
        }
        zfCoreMutexUnlock();
        d->mutexImpl->mutexImplLock();
    }
}
void ZFObject::_ZFP_ZFObjectUnlock(void)
{
    if(d->mutexImpl)
    {
        d->mutexImpl->mutexImplUnlock();
    }
    // else should not go here
}
zfbool ZFObject::_ZFP_ZFObjectTryLock(void)
{
    if(d->mutexImpl)
    {
        return d->mutexImpl->mutexImplTryLock();
    }
    else if(d->mutexImplAvailable)
    {
        zfCoreMutexLock();
        if(d->mutexImpl == zfnull)
        {
            d->mutexImpl = _ZFP_ZFObjectMutexImplInitCallbackRef();
        }
        zfCoreMutexUnlock();
        return d->mutexImpl->mutexImplTryLock();
    }
    else
    {
        return zffalse;
    }
}

ZFObject *ZFObject::_ZFP_ZFObjectAlloc(ZFObject *obj)
{
    // called when object constructed
    // no use for now, paired with _ZFP_ZFObjectDealloc
    return obj;
}
ZFObject *ZFObject::_ZFP_ZFObjectCheckOnInit(void)
{
    if(d == zfnull)
    {
        zfCoreCriticalMessageTrim(zfTextA("[ZFObject] ZFObject::objectOnInit() not called"));
        return zfnull;
    }

    d->objectInstanceState = ZFObjectInstanceStateOnInitFinish;
    this->classData()->_ZFP_ZFClass_propertyAutoInitAction(this);
    this->_ZFP_ZFObject_interfaceOnInit();
    this->objectOnInitFinish();
    d->objectInstanceState = ZFObjectInstanceStateIdle;

    if(!this->objectIsInternal())
    {
        this->classData()->_ZFP_ZFClass_instanceObserverNotify(this);
        if(d->observerHasAddFlag_objectAfterAlloc)
        {
            this->observerNotify(ZFObject::EventObjectAfterAlloc());
        }
    }

    return this;
}
void ZFObject::_ZFP_ZFObjectDealloc(ZFObject *obj)
{
    if(!obj->objectIsInternal())
    {
        if(obj->d->observerHasAddFlag_objectBeforeDealloc)
        {
            obj->observerNotify(ZFObject::EventObjectBeforeDealloc());
        }
    }
    if(obj->d->observerNotifyingFlag > 0)
    {
        zfCoreCriticalMessageTrim(zfTextA("[ZFObject] deallocating an object during observerNotify, you may want to use zfautoRelease?"));
        return ;
    }
    obj->d->objectInstanceState = ZFObjectInstanceStateOnDeallocPrepare;
    obj->objectOnDeallocPrepare();
    obj->_ZFP_ZFObject_interfaceOnDealloc();
    for(zfstlsize i = obj->d->propertyAccessed.size() - 1; i != (zfstlsize)-1; --i)
    {
        const ZFProperty *property = obj->d->propertyAccessed[i];
        property->_ZFP_ZFProperty_callbackDealloc(obj, property);
    }
    obj->d->objectInstanceState = ZFObjectInstanceStateOnDealloc;
    zflockfree_ZFLeakTestLogBeforeDealloc(obj);
    obj->objectOnDealloc();
    if(obj->d != zfnull)
    {
        zfCoreCriticalMessageTrim(zfTextA("[ZFObject] ZFObject::objectOnDealloc() not called"));
        return ;
    }
    obj->classData()->_ZFP_ZFClass_objectDesctuct(obj);
}

ZFObject *ZFObject::objectOnInit(void)
{
    if(d != zfnull)
    {
        zfCoreCriticalMessageTrim(zfTextA("[ZFObject] ZFObject::objectOnInit() called twice"));
        return zfnull;
    }

    // note that (d != zfnull) is also used to check whether ZFObject::objectOnInit() is called
    d = zfpoolNew(_ZFP_ZFObjectPrivate);
    d->observerHolder._ZFP_ZFObserverHolder_observerOwnerSet(this);

    d->objectIsPrivate = this->classData()->classIsPrivate();
    d->objectIsInternal = this->classData()->classIsInternal();

    return this;
}
void ZFObject::objectOnDealloc(void)
{
    if(d == zfnull)
    {
        zfCoreCriticalMessageTrim(zfTextA("[ZFObject] ZFObject::objectOnDealloc() called twice"));
        return ;
    }

    if(d->mutexImpl)
    {
        _ZFP_ZFObjectMutexImplCleanupCallbackRef(d->mutexImpl);
        d->mutexImpl = zfnull;
    }

    if(d->objectHolder)
    {
        d->objectHolder->holdedObj = (ZFObject *)zfnull;
        d->objectHolder->objectCachedSet(zffalse);
        zfReleaseWithoutLeakTest(d->objectHolder);
    }

    zfpoolDelete(d);
    // note that (d == zfnull) is also used to check whether ZFObject::objectOnDealloc() is called
    d = zfnull;
}
void ZFObject::objectOnInitFinish(void)
{
}
void ZFObject::objectOnDeallocPrepare(void)
{
    this->tagRemoveAll();
    this->observerRemoveAll();
}
void ZFObject::objectOnRetain(void)
{
    zfCoreAssertWithMessageTrim(d->objectRetainCount > 0,
        zfTextA("retain an object while deallocating: %s"), zfsCoreZ2A(this->objectInfoOfInstance().cString()));
    ++(d->objectRetainCount);
}
void ZFObject::objectOnRelease(void)
{
    --(d->objectRetainCount);
}

ZFObjectInstanceState ZFObject::objectInstanceState(void)
{
    return d->objectInstanceState;
}

zfbool ZFObject::objectIsPrivate(void)
{
    return d->objectIsPrivate || d->objectIsInternal;
}
void ZFObject::objectIsPrivateSet(ZF_IN zfbool value)
{
    d->objectIsPrivate = value;
}
zfbool ZFObject::objectIsInternal(void)
{
    return d->objectIsInternal;
}
void ZFObject::objectIsInternalSet(ZF_IN zfbool value)
{
    d->objectIsInternal = value;
}

void ZFObject::_ZFP_ZFObject_objectPropertyValueAttach(ZF_IN const ZFProperty *property,
                                                       ZF_IN zfbool firstTimeAccess)
{
    if(this->objectCached() && property->propertyIsRetainProperty())
    {
        ZFObject *value = property->callbackRetainGet(property, this);
        if(value != zfnull)
        {
            value->objectCachedSet(zftrue);
        }
    }

    if(firstTimeAccess)
    {
        d->propertyAccessed.push_back(property);
    }
}
void ZFObject::_ZFP_ZFObject_objectPropertyValueDetach(ZF_IN const ZFProperty *property,
                                                       ZF_IN zfbool completeDetach)
{
    if(completeDetach)
    {
        for(zfstlsize i = d->propertyAccessed.size() - 1; i != (zfstlsize)-1; --i)
        {
            if(d->propertyAccessed[i] == property)
            {
                d->propertyAccessed.erase(d->propertyAccessed.begin() + i);
            }
        }
    }
    if(this->objectCached() && property->propertyIsRetainProperty())
    {
        ZFObject *value = property->callbackRetainGet(property, this);
        if(value != zfnull)
        {
            value->objectCachedSet(zffalse);
        }
    }
}

void ZFObject::objectPropertyValueOnUpdate(ZF_IN const ZFProperty *property, ZF_IN const void *oldValue)
{
    if(d->observerHasAddFlag_objectPropertyValueOnUpdate)
    {
        ZFPointerHolder *param0 = ZFPointerHolder::cacheAccess();
        param0->holdedData = property;
        ZFPointerHolder *param1 = ZFPointerHolder::cacheAccess();
        param1->holdedData = oldValue;
        this->observerNotify(ZFObject::EventObjectPropertyValueOnUpdate(), param0, param1);
        ZFPointerHolder::cacheRelease(param0);
        ZFPointerHolder::cacheRelease(param1);
    }
}

void ZFObject::objectCachedSet(ZF_IN zfbool objectCached)
{
    zfCoreMutexLocker();
    if(objectCached)
    {
        ++(d->objectCachedFlag);
        _ZFP_ZFLeakTestLogCacheAdd(this);

        if(d->objectCachedFlag == 1)
        {
            this->objectCachedOnChange();
        }
    }
    else if(d->objectCachedFlag > 0)
    {
        --(d->objectCachedFlag);
        _ZFP_ZFLeakTestLogCacheRemove(this);

        if(d->objectCachedFlag == 0)
        {
            this->objectCachedOnChange();
        }
    }
}
zfbool ZFObject::objectCached(void)
{
    return (d->objectCachedFlag > 0);
}
zfindex ZFObject::objectCachedCount(void)
{
    return (zfindex)d->objectCachedFlag;
}
void ZFObject::objectCachedOnChange(void)
{
    if(d->observerHasAddFlag_objectCachedOnChange)
    {
        this->observerNotify(ZFObject::EventObjectCachedOnChange());
    }
}

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFEXPORT_ENUM_DEFINE(ZFObjectInstanceState, ZFObjectInstanceStateOnInit, ZFObjectInstanceStateOnInitFinish, ZFObjectInstanceStateIdle, ZFObjectInstanceStateOnDeallocPrepare, ZFObjectInstanceStateOnDealloc)

ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFObject, const ZFClass *, classData)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFObject, ZFObjectHolder *, objectHolder)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFObject, void, objectInfoOfInstanceT, ZFMP_IN_OUT(zfstring &, ret))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFObject, zfstring, objectInfoOfInstance)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFObject, void, objectInfoT, ZFMP_IN_OUT(zfstring &, ret))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFObject, zfstring, objectInfo)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFObject, zfidentity, objectHash)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFObject, ZFCompareResult, objectCompare, ZFMP_IN(ZFObject *, anotherObj))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFObject, zfbool, tagHasSet)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_3(ZFObject, void, tagSet, ZFMP_IN(const zfchar *, key), ZFMP_IN(ZFObject *, tag), ZFMP_IN_OPT(zfbool, autoMarkCached, zffalse))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_2(ZFObject, void, tagSetMarkCached, ZFMP_IN(const zfchar *, key), ZFMP_IN(ZFObject *, tag))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFObject, ZFObject *, tagGet, ZFMP_IN(const zfchar *, key))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_2(ZFObject, void, tagGetAllKeyValue, ZFMP_IN_OUT(ZFCoreArray<const zfchar *> &, allKey), ZFMP_IN_OUT(ZFCoreArray<ZFObject *> &, allValue))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFObject, void, tagRemove, ZFMP_IN(const zfchar *, key))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFObject, zfautoObject, tagRemoveAndGet, ZFMP_IN(const zfchar *, key))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFObject, void, tagRemoveAll)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFObject, const ZFObserverHolder &, observerHolder)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_6(ZFObject, void, observerAdd, ZFMP_IN(const zfidentity &, eventId), ZFMP_IN(const ZFListener &, observer), ZFMP_IN_OPT(ZFObject *, userData, zfnull), ZFMP_IN_OPT(ZFObject *, owner, zfnull), ZFMP_IN_OPT(zfbool, autoRemoveAfterActivate, zffalse), ZFMP_IN_OPT(ZFLevel, observerLevel, ZFLevelAppNormal))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFObject, void, observerAdd, ZFMP_IN(const ZFObserverAddParam &, param))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_2(ZFObject, void, observerRemove, ZFMP_IN(const zfidentity &, eventId), ZFMP_IN(const ZFListener &, callback))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_3(ZFObject, void, observerRemove, ZFMP_IN(const zfidentity &, eventId), ZFMP_IN(const ZFListener &, callback), ZFMP_IN(ZFObject *, userData))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFObject, void, observerRemoveByOwner, ZFMP_IN(ZFObject *, owner))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFObject, void, observerRemoveAll, ZFMP_IN(const zfidentity &, eventId))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFObject, void, observerRemoveAll)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFObject, zfbool, observerHasAdd)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFObject, zfbool, observerHasAdd, ZFMP_IN(const zfidentity &, eventId))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_3(ZFObject, void, observerNotify, ZFMP_IN(const zfidentity &, eventId), ZFMP_IN_OPT(ZFObject *, param0, zfnull), ZFMP_IN_OPT(ZFObject *, param1, zfnull))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_4(ZFObject, void, observerNotifyWithCustomSender, ZFMP_IN(ZFObject *, customSender), ZFMP_IN(const zfidentity &, eventId), ZFMP_IN_OPT(ZFObject *, param0, zfnull), ZFMP_IN_OPT(ZFObject *, param1, zfnull))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFObject, ZFObjectInstanceState, objectInstanceState)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFObject, zfbool, objectIsPrivate)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFObject, void, objectIsPrivateSet, ZFMP_IN(zfbool, value))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFObject, zfbool, objectIsInternal)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFObject, void, objectIsInternalSet, ZFMP_IN(zfbool, value))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFObject, void, objectIsInternalSet, ZFMP_IN(zfbool, value))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_1(ZFObject, void, objectCachedSet, ZFMP_IN(zfbool, objectCached))
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFObject, zfbool, objectCached)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_FUNC_0(ZFObject, zfindex, objectCachedCount)

ZF_NAMESPACE_GLOBAL_END
#endif

