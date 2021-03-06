/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFObjectCore.h"
#include "ZFObjectImpl.h"

#include "ZFCore/ZFSTLWrapper/zfstl_map.h"
#include "ZFCore/ZFSTLWrapper/zfstl_vector.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// ZFListenerData
void ZFListenerData::objectInfoT(ZF_IN_OUT zfstring &ret) const
{
    ret += ZFTOKEN_ZFObjectInfoLeft;
    zfstringAppend(ret, zfText("ZFListenerData(%p)"), this);
    const zfchar *eventName = ZFObserverEventGetName(this->eventId);
    if(eventName != zfnull)
    {
        ret += zfText(", event: ");
        ret += eventName;
    }
    if(this->sender != zfnull)
    {
        ret += zfText(", sender: ");
        ZFObjectInfoT(ret, this->sender);
    }
    if(this->param0 != zfnull)
    {
        ret += zfText(", param0: ");
        ZFObjectInfoT(ret, this->param0);
    }
    if(this->param1 != zfnull)
    {
        ret += zfText(", param1: ");
        ZFObjectInfoT(ret, this->param1);
    }
    ret += ZFTOKEN_ZFObjectInfoRight;
}

// ============================================================
// ZFObserverHolder types
zfclassLikePOD _ZFP_ZFObserverData
{
public:
    zfidentity eventId;
    ZFListener observer;
    ZFObject *userData; // no auto retain, manually retain or release for readable leak test
    ZFObject *owner;
    zfbool autoRemoveAfterActivate;
    ZFLevel observerLevel;

public:
    _ZFP_ZFObserverData(void)
    : eventId(zfidentityInvalid())
    , observer()
    , userData(zfnull)
    , owner(zfnull)
    , autoRemoveAfterActivate(zffalse)
    , observerLevel(ZFLevelAppNormal)
    {
    }
    _ZFP_ZFObserverData(ZF_IN zfidentity eventId,
                        ZF_IN const ZFListener &observer,
                        ZF_IN_OPT ZFObject *userData = zfnull,
                        ZF_IN_OPT ZFObject *owner = zfnull,
                        ZF_IN_OPT zfbool autoRemoveAfterActivate = zffalse,
                        ZF_IN_OPT ZFLevel observerLevel = ZFLevelAppNormal)
    : eventId(eventId)
    , observer(observer)
    , userData(userData)
    , owner(owner)
    , autoRemoveAfterActivate(autoRemoveAfterActivate)
    , observerLevel(observerLevel)
    {
    }
private:
    _ZFP_ZFObserverData(ZF_IN const _ZFP_ZFObserverData &ref);
    _ZFP_ZFObserverData &operator = (ZF_IN const _ZFP_ZFObserverData &ref);
};
typedef zfstlvector<ZFCorePointerForObject<_ZFP_ZFObserverData *> > _ZFP_ZFObserverListType;
typedef zfstlmap<zfidentity, _ZFP_ZFObserverListType> _ZFP_ZFObserverMapType;

zfclassNotPOD _ZFP_ZFObserverHolderPrivate
{
public:
    zfuint refCount;
    ZFObject *observerOwner;
    _ZFP_ZFObserverMapType observerMap;
public:
    _ZFP_ZFObserverHolderPrivate(void)
    : refCount(1)
    , observerOwner(zfnull)
    , observerMap()
    {
    }

public:
    void observerNotifyPrepare(ZF_IN_OUT _ZFP_ZFObserverListType &toNotify,
                               ZF_IN_OUT zfstlvector<ZFObject *> &toRelease,
                               ZF_IN const zfidentity &eventId,
                               ZF_IN ZFObject *observerOwner)
    {
        if(this->observerMap.empty())
        {
            return ;
        }

        _ZFP_ZFObserverMapType::iterator it = this->observerMap.find(eventId);
        if(it != this->observerMap.end())
        {
            for(zfstlsize i = 0; i < it->second.size(); ++i)
            {
                ZFCorePointerForObject<_ZFP_ZFObserverData *> &observerDataHolder = it->second[i];
                _ZFP_ZFObserverData &observerData = *(observerDataHolder.pointerValueGet());
                toNotify.push_back(observerDataHolder);
                if(observerData.autoRemoveAfterActivate)
                {
                    if(observerData.userData != zfnull)
                    {
                        toRelease.push_back(observerData.userData);
                    }
                    it->second.erase(it->second.begin() + i);
                    --i;
                }
            }
            if(it->second.empty())
            {
                this->observerMap.erase(it);
                if(observerOwner)
                {
                    observerOwner->observerOnRemove(eventId);
                }
            }
        }
    }
};

// ============================================================
// ZFObserverHolder
/** @cond ZFPrivateDoc */
ZFObserverHolder::ZFObserverHolder(void)
{
    zfCoreMutexLocker();
    d = zfpoolNew(_ZFP_ZFObserverHolderPrivate);
}
ZFObserverHolder::ZFObserverHolder(ZF_IN ZFObserverHolder const &ref)
{
    zfCoreMutexLocker();
    d = ref.d;
    ++(d->refCount);
}
ZFObserverHolder::~ZFObserverHolder(void)
{
    zfCoreMutexLocker();
    zfpoolDelete(d);
}
ZFObserverHolder &ZFObserverHolder::operator = (ZF_IN ZFObserverHolder const &ref)
{
    zfCoreMutexLocker();
    ++(ref.d->refCount);
    --(d->refCount);
    if(d->refCount == 0)
    {
        zfpoolDelete(d);
    }
    d = ref.d;
    return *this;
}
zfbool ZFObserverHolder::operator == (ZF_IN ZFObserverHolder const &ref) const
{
    zfCoreMutexLocker();
    return (d == ref.d);
}
/** @endcond */

void ZFObserverHolder::observerAdd(ZF_IN const zfidentity &eventId,
                                   ZF_IN const ZFListener &observer,
                                   ZF_IN_OPT ZFObject *userData /* = zfnull */,
                                   ZF_IN_OPT ZFObject *owner /* = zfnull */,
                                   ZF_IN_OPT zfbool autoRemoveAfterActivate /* = zffalse */,
                                   ZF_IN_OPT ZFLevel observerLevel /* = ZFLevelAppNormal */) const
{
    zfCoreMutexLocker();

    if(eventId == zfidentityInvalid()
        || !observer.callbackIsValid())
    {
        return ;
    }

    if(userData != zfnull)
    {
        userData->objectCachedSet(zftrue);
    }

    _ZFP_ZFObserverListType &observerList = d->observerMap[eventId];
    zfstlsize index = observerList.size();
    while(index > 0 && observerList.at(index - 1).pointerValueGet()->observerLevel > observerLevel)
    {
        --index;
    }
    _ZFP_ZFObserverData *observerData = zfnew(_ZFP_ZFObserverData
            , eventId
            , observer
            , zflockfree_zfRetain(userData)
            , owner
            , autoRemoveAfterActivate
            , observerLevel
        );
    observerList.insert(observerList.begin() + index,
        ZFCorePointerForObject<_ZFP_ZFObserverData *>(observerData));
    if(this->observerOwner())
    {
        if(observerList.size() == 1)
        {
            this->observerOwner()->observerOnAdd(eventId);
        }
    }
}
void ZFObserverHolder::observerRemove(ZF_IN const zfidentity &eventId,
                                      ZF_IN const ZFListener &callback,
                                      ZF_IN_OPT ZFObject *userData /* = zfnull */,
                                      ZF_IN_OPT ZFComparer<ZFObject *>::Comparer userDataComparer /* = zfnull */) const
{
    zfCoreMutexLocker();

    _ZFP_ZFObserverMapType::iterator it = d->observerMap.find(eventId);
    if(it != d->observerMap.end())
    {
        for(zfstlsize iObserver = 0; iObserver < it->second.size(); ++iObserver)
        {
            _ZFP_ZFObserverData *observerData = it->second[iObserver].pointerValueGet();
            if(observerData->observer.objectCompareByInstance(callback) == ZFCompareTheSame
                && (userDataComparer == zfnull || userDataComparer(userData, observerData->userData) == ZFCompareTheSame))
            {
                ZFObject *toRemove = observerData->userData;
                it->second.erase(it->second.begin() + iObserver);

                zfbool removedLast = zffalse;
                if(it->second.empty())
                {
                    d->observerMap.erase(it);
                    removedLast = zftrue;
                }
                if(this->observerOwner())
                {
                    if(removedLast)
                    {
                        this->observerOwner()->observerOnRemove(eventId);
                    }
                }
                if(toRemove != zfnull)
                {
                    toRemove->objectCachedSet(zffalse);
                    zflockfree_zfRelease(toRemove);
                }
                break;
            }
        }
    }
}
void ZFObserverHolder::observerRemoveByOwner(ZF_IN ZFObject *owner) const
{
    zfCoreMutexLocker();
    if(owner == zfnull || d->observerMap.empty())
    {
        return ;
    }

    zfstlvector<ZFCorePointerForObject<_ZFP_ZFObserverData *> > removed;
    zfstlvector<zfidentity> removedLast;
    for(_ZFP_ZFObserverMapType::iterator it = d->observerMap.begin();
        it != d->observerMap.end();)
    {
        for(zfstlsize iObserver = 0; iObserver < it->second.size(); ++iObserver)
        {
            if(it->second[iObserver].pointerValueGet()->owner == owner)
            {
                removed.push_back(it->second[iObserver]);
                it->second.erase(it->second.begin() + iObserver);
                --iObserver;
            }
        }
        if(it->second.empty())
        {
            removedLast.push_back(it->first);
            d->observerMap.erase(it++);
        }
        else
        {
            ++it;
        }
    }
    if(this->observerOwner())
    {
        for(zfstlsize i = 0; i < removedLast.size(); ++i)
        {
            this->observerOwner()->observerOnRemove(removedLast[i]);
        }
    }
    if(!removed.empty())
    {
        for(zfstlsize i = 0; i < removed.size(); ++i)
        {
            ZFObject *userDataTmp = removed[i].pointerValueGet()->userData;
            if(userDataTmp != zfnull)
            {
                userDataTmp->objectCachedSet(zffalse);
                zflockfree_zfRelease(userDataTmp);
            }
        }
    }
}
void ZFObserverHolder::observerRemoveAll(ZF_IN const zfidentity &eventId) const
{
    zfCoreMutexLocker();
    if(d->observerMap.empty())
    {
        return ;
    }

    _ZFP_ZFObserverMapType::iterator it = d->observerMap.find(eventId);
    if(it != d->observerMap.end())
    {
        _ZFP_ZFObserverListType removed = it->second;
        d->observerMap.erase(it);
        if(this->observerOwner())
        {
            this->observerOwner()->observerOnRemove(eventId);
        }
        if(!removed.empty())
        {
            for(zfstlsize i = 0; i < removed.size(); ++i)
            {
                ZFObject *userDataTmp = removed[i].pointerValueGet()->userData;
                if(userDataTmp != zfnull)
                {
                    userDataTmp->objectCachedSet(zffalse);
                    zflockfree_zfRelease(userDataTmp);
                }
            }
        }
    }
}
void ZFObserverHolder::observerRemoveAll(void) const
{
    zfCoreMutexLocker();
    if(d->observerMap.empty())
    {
        return ;
    }

    _ZFP_ZFObserverMapType tmp;
    tmp.swap(d->observerMap);

    if(this->observerOwner())
    {
        for(_ZFP_ZFObserverMapType::iterator it = tmp.begin();
            it != tmp.end();
            ++it)
        {
            this->observerOwner()->observerOnRemove(it->first);
        }
    }

    for(_ZFP_ZFObserverMapType::iterator it = tmp.begin();
        it != tmp.end();
        ++it)
    {
        for(zfstlsize iObserver = 0; iObserver < it->second.size(); ++iObserver)
        {
            ZFObject *userDataTmp = it->second[iObserver].pointerValueGet()->userData;
            if(userDataTmp != zfnull)
            {
                userDataTmp->objectCachedSet(zffalse);
                zflockfree_zfRelease(userDataTmp);
            }
        }
    }
}
zfbool ZFObserverHolder::observerHasAdd(void) const
{
    zfCoreMutexLocker();
    return !d->observerMap.empty();
}
zfbool ZFObserverHolder::observerHasAdd(ZF_IN const zfidentity &eventId) const
{
    zfCoreMutexLocker();
    return (d->observerMap.find(eventId) != d->observerMap.end());
}

void ZFObserverHolder::observerNotifyWithCustomSender(ZF_IN ZFObject *customSender,
                                                      ZF_IN const zfidentity &eventId,
                                                      ZF_IN_OPT ZFObject *param0 /* = zfnull */,
                                                      ZF_IN_OPT ZFObject *param1 /* = zfnull */) const
{
    zfCoreMutexLock();
    if(eventId == zfidentityInvalid())
    {
        zfCoreMutexUnlock();
        return ;
    }

    _ZFP_ZFObserverListType toNotify;
    zfstlvector<ZFObject *> toRelease;

    d->observerNotifyPrepare(toNotify, toRelease, eventId, this->observerOwner());
    if(this->observerOwner() != zfnull)
    {
        this->observerOwner()->observerOnEvent(eventId, param0, param1);
        ZFObjectGlobalEventObserver().d->observerNotifyPrepare(toNotify, toRelease, eventId, this->observerOwner());
    }
    zfCoreMutexUnlock();

    if(!toNotify.empty())
    {
        ZFListenerData listenerData(eventId, customSender, param0, param1);
        for(zfstlsize i = 0; i < toNotify.size(); ++i)
        {
            const _ZFP_ZFObserverData &observerData = *(toNotify[i].pointerValueGet());
            observerData.observer.execute(listenerData, observerData.userData);
        }
    }

    zfCoreMutexLock();
    for(zfstlsize i = 0; i < toRelease.size(); ++i)
    {
        ZFObject *userDataTmp = toRelease[i];
        userDataTmp->objectCachedSet(zffalse);
        zflockfree_zfRelease(userDataTmp);
    }
    toNotify.clear(); // must be cleared within mutex to ensure thread safe for callback desctruction
    zfCoreMutexUnlock();
}

void ZFObserverHolder::objectInfoT(ZF_OUT zfstring &ret) const
{
    ret += zfText("<ZFObserverHolder");

    if(this->observerOwner() != zfnull)
    {
        ret += zfText(" ");
        this->observerOwner()->objectInfoT(ret);
    }

    if(d->observerMap.empty())
    {
        ret += zfText(">");
    }
    else
    {
        for(_ZFP_ZFObserverMapType::iterator it = d->observerMap.begin();
            it != d->observerMap.end();
            ++it)
        {
            ret += zfText("\n  ");
            ret += ZFObserverEventGetName(it->first);
            ret += zfText(":");

            for(zfstlsize iObserver = 0; iObserver < it->second.size(); ++iObserver)
            {
                ret += zfText("\n    ");
                ret += it->second[iObserver].pointerValueGet()->observer.objectInfo();
            }
        }

        ret += zfText("\n  >");
    }
}

ZFObject *ZFObserverHolder::observerOwner(void) const
{
    return d->observerOwner;
}
void ZFObserverHolder::_ZFP_ZFObserverHolder_observerOwnerSet(ZF_IN ZFObject *obj)
{
    /*
     * if observerOwner is not null,
     * means it belongs to a ZFObject, which would:
     * * also send all events to ZFObjectGlobalEventObserver
     * * notify events to owner ZFObject, such as observerOnAdd
     */
    d->observerOwner = obj;
}

// ============================================================
ZFObserverHolder &_ZFP_ZFObjectGlobalEventObserverRef(void)
{
    static ZFObserverHolder d;
    return d;
}

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFListenerData, zfidentity, eventId)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFListenerData, ZFObject *, sender)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFListenerData, ZFObject *, param0)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFListenerData, ZFObject *, param1)

ZFMETHOD_USER_REGISTER_2({return ZFListener(invokerObject->to<v_ZFCallback *>()->zfv).execute(listenerData, userData);}, v_ZFCallback, void, execute, ZFMP_IN(const ZFListenerData &, listenerData), ZFMP_IN_OPT(ZFObject *, userData, zfnull))

ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFObserverAddParam, zfidentity const &, eventId)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFObserverAddParam, void, eventIdSet, ZFMP_IN(zfidentity const &, v))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFObserverAddParam, ZFListener const &, observer)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFObserverAddParam, void, observerSet, ZFMP_IN(ZFListener const &, v))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFObserverAddParam, ZFObject * const &, userData)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFObserverAddParam, void, userDataSet, ZFMP_IN(ZFObject * const &, v))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFObserverAddParam, ZFObject * const &, owner)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFObserverAddParam, void, ownerSet, ZFMP_IN(ZFObject * const &, v))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFObserverAddParam, zfbool const &, autoRemoveAfterActivate)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFObserverAddParam, void, autoRemoveAfterActivateSet, ZFMP_IN(zfbool const &, v))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFObserverAddParam, ZFLevel const &, observerLevel)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFObserverAddParam, void, observerLevelSet, ZFMP_IN(ZFLevel const &, v))

ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_6(v_ZFObserverHolder, void, observerAdd, ZFMP_IN(const zfidentity &, eventId), ZFMP_IN(const ZFListener &, observer), ZFMP_IN_OPT(ZFObject *, userData, zfnull), ZFMP_IN_OPT(ZFObject *, owner, zfnull), ZFMP_IN_OPT(zfbool, autoRemoveAfterActivate, zffalse), ZFMP_IN_OPT(ZFLevel, observerLevel, ZFLevelAppNormal))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFObserverHolder, void, observerAdd, ZFMP_IN(const ZFObserverAddParam &, param))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_4(v_ZFObserverHolder, void, observerRemove, ZFMP_IN(const zfidentity &, eventId), ZFMP_IN(const ZFListener &, callback), ZFMP_IN_OPT(ZFObject *, userData, zfnull), ZFMP_IN_OPT(ZFComparer<ZFObject *>::Comparer, userDataComparer, zfnull))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFObserverHolder, void, observerRemoveByOwner, ZFMP_IN(ZFObject *, owner))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFObserverHolder, void, observerRemoveAll, ZFMP_IN(const zfidentity &, eventId))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFObserverHolder, void, observerRemoveAll)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFObserverHolder, zfbool, observerHasAdd)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFObserverHolder, zfbool, observerHasAdd, ZFMP_IN(const zfidentity &, eventId))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_3(v_ZFObserverHolder, void, observerNotify, ZFMP_IN(const zfidentity &, eventId), ZFMP_IN_OPT(ZFObject *, param0, zfnull), ZFMP_IN_OPT(ZFObject *, param1, zfnull))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_4(v_ZFObserverHolder, void, observerNotifyWithCustomSender, ZFMP_IN(ZFObject *, customSender), ZFMP_IN(const zfidentity &, eventId), ZFMP_IN_OPT(ZFObject *, param0, zfnull), ZFMP_IN_OPT(ZFObject *, param1, zfnull))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFObserverHolder, ZFObject *, observerOwner)

ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_0(ZFObserverHolder &, ZFObjectGlobalEventObserver)

ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(const zfchar *, ZFObserverEventGetName, ZFMP_IN(const zfidentity &, eventId))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(zfidentity, ZFObserverEventGetId, ZFMP_IN(const zfchar *, name))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(void, ZFObserverEventGetId, ZFMP_OUT(ZFCoreArrayPOD<zfidentity> &, idValues), ZFMP_OUT(ZFCoreArrayPOD<const zfchar *> &, idNames))

ZF_NAMESPACE_GLOBAL_END
#endif

