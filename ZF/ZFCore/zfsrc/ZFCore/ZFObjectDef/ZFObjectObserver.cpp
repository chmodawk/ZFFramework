/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFObjectCore.h"
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
    : eventId(zfidentityInvalid)
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
    _ZFP_ZFObserverMapType observerMap;
public:
    _ZFP_ZFObserverHolderPrivate(void)
    : observerMap()
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
: d(zfpoolNew(_ZFP_ZFObserverHolderPrivate))
, _observerOwner(zfnull)
{
}
ZFObserverHolder::~ZFObserverHolder(void)
{
    zfpoolDelete(d);
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

    if(!zfidentityIsValid(eventId)
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
    if(!zfidentityIsValid(eventId))
    {
        zfCoreMutexUnlock();
        return ;
    }

    _ZFP_ZFObserverListType toNotify;
    zfstlvector<ZFObject *> toRelease;

    d->observerNotifyPrepare(toNotify, toRelease, eventId, this->observerOwner());
    if(this->observerOwner() != zfnull)
    {
        this->observerOwner()->_ZFP_ZFObject_observerNotifyBegin();
        this->observerOwner()->observerOnEvent(eventId, param0, param1);
        ZFObjectGlobalEventObserver.d->observerNotifyPrepare(toNotify, toRelease, eventId, this->observerOwner());
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
    if(this->observerOwner() != zfnull)
    {
        this->observerOwner()->_ZFP_ZFObject_observerNotifyEnd();
    }
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

void ZFObserverHolder::_ZFP_ZFObserverHolder_observerOwnerSet(ZF_IN ZFObject *obj)
{
    /*
     * if observerOwner is not null,
     * means it belongs to a ZFObject, which would:
     * * also send all events to ZFObjectGlobalEventObserver
     * * notify events to owner ZFObject, such as observerOnAdd
     */
    this->_observerOwner = obj;
}

// ============================================================
ZFObserverHolder &_ZFP_ZFObjectGlobalEventObserverRef(void)
{
    static ZFObserverHolder d;
    return d;
}

ZF_NAMESPACE_GLOBAL_END

