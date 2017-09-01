/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFObjectObserver.h
 * @brief observer types for #ZFObject
 */

#ifndef _ZFI_ZFObjectObserver_h_
#define _ZFI_ZFObjectObserver_h_

#include "ZFObjectClassTypeFwd.h"
#include "ZFCallback.h"
#include "ZFIdMap.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// ZFListenerData
/**
 * @brief listener data used by #ZFListener
 *
 * @note this object only hold the necessary datas as pointer,
 *   without auto retain or release logic
 */
zffinal zfclassLikePOD ZF_ENV_EXPORT ZFListenerData
{
public:
    /**
     * @brief event id, may be #zfidentityInvalid
     */
    zfidentity eventId;
    /**
     * @brief who notified the listener event, may be null
     */
    ZFObject *sender;
    /**
     * @brief params, may be null
     */
    ZFObject *param0;
    /**
     * @brief params, may be null
     */
    ZFObject *param1;

public:
    /**
     * @brief main constructor
     */
    ZFListenerData(void)
    : eventId(zfidentityInvalid())
    , sender(zfnull)
    , param0(zfnull)
    , param1(zfnull)
    {
    }
    /**
     * @brief construct with sender and params
     */
    ZFListenerData(ZF_IN zfidentity eventId,
                   ZF_IN ZFObject *sender,
                   ZF_IN_OPT ZFObject *param0 = zfnull,
                   ZF_IN_OPT ZFObject *param1 = zfnull)
    : eventId(eventId)
    , sender(sender)
    , param0(param0)
    , param1(param1)
    {
    }
    /**
     * @brief construct with another data
     */
    ZFListenerData(ZF_IN const ZFListenerData &ref)
    : eventId(ref.eventId)
    , sender(ref.sender)
    , param0(ref.param0)
    , param1(ref.param1)
    {
    }
public:
    /** @cond ZFPrivateDoc */
    ZFListenerData &operator = (ZF_IN const ZFListenerData &ref)
    {
        this->eventId = ref.eventId;
        this->sender = ref.sender;
        this->param0 = ref.param0;
        this->param1 = ref.param1;
        return *this;
    }
    zfbool operator == (ZF_IN const ZFListenerData &ref) const
    {
        return (this->eventId == ref.eventId
            && this->sender == ref.sender
            && this->param0 == ref.param0
            && this->param1 == ref.param1
            );
    }
    inline zfbool operator != (ZF_IN const ZFListenerData &ref) const {return !this->operator == (ref);}
    /** @endcond */
public:
    /**
     * @brief get a short info of this object
     */
    void objectInfoT(ZF_IN_OUT zfstring &ret) const;
    /** @brief see #objectInfoT */
    zfstring objectInfo(void) const
    {
        zfstring ret;
        this->objectInfoT(ret);
        return ret;
    }

public:
    /**
     * @brief util method to set #eventId
     */
    ZFListenerData &eventIdSet(ZF_IN zfidentity eventId)
    {
        this->eventId = eventId;
        return *this;
    }
    /**
     * @brief util method to set #sender (no auto retain)
     */
    ZFListenerData &senderSet(ZF_IN ZFObject *sender)
    {
        this->sender = sender;
        return *this;
    }
    /**
     * @brief util method to set #param0 (no auto retain)
     */
    ZFListenerData &param0Set(ZF_IN ZFObject *param0)
    {
        this->param0 = param0;
        return *this;
    }
    /**
     * @brief util method to set #param1 (no auto retain)
     */
    ZFListenerData &param1Set(ZF_IN ZFObject *param1)
    {
        this->param1 = param1;
        return *this;
    }
};

// ============================================================
/**
 * @brief listener as ZFCallback, mostly used by #ZFObject::observerNotify
 *
 * listeners usually achieved by observer logic in ZFObject,
 * see #ZFObject::observerNotify for more info\n
 * \n
 * what params means, is determined by invoker of the listener,
 * see each listener's comments before use it
 */
ZFCALLBACK_DECLARE_BEGIN(ZFListener, ZFCallback)
public:
    /** @brief see #ZFListener */
    inline void execute(ZF_IN const ZFListenerData &listenerData,
                        ZF_IN_OPT ZFObject *userData = zfnull) const
    {
        ZFCallback::executeExact<void, const ZFListenerData &, ZFObject *>(listenerData, userData);
    }
    /** @brief see #ZFListener */
    inline void operator()(ZF_IN const ZFListenerData &listenerData,
                           ZF_IN_OPT ZFObject *userData = zfnull) const
    {
        ZFCallback::executeExact<void, const ZFListenerData &, ZFObject *>(listenerData, userData);
    }
_ZFP_ZFCALLBACK_DECLARE_END_NO_ALIAS(ZFListener, ZFCallback)

// ============================================================
// ZFObserverHolder
/** @brief see #ZFObject::observerNotify */
zffinal zfclassLikePOD ZF_ENV_EXPORT ZFObserverAddParam
{
    ZFCORE_PARAM_DECLARE_SELF(ZFObserverAddParam)

    /** @brief see #ZFObject::observerNotify */
    ZFCORE_PARAM_WITH_INIT(zfidentity, eventId, zfidentityInvalid())

    /** @brief see #ZFObject::observerNotify */
    ZFCORE_PARAM(ZFListener, observer)

    /** @brief see #ZFObject::observerNotify */
    ZFCORE_PARAM_WITH_INIT(ZFObject *, userData, zfnull)

    /** @brief see #ZFObject::observerNotify */
    ZFCORE_PARAM_WITH_INIT(ZFObject *, owner, zfnull)

    /** @brief see #ZFObject::observerNotify */
    ZFCORE_PARAM_WITH_INIT(zfbool, autoRemoveAfterActivate, zffalse)

    /** @brief see #ZFObject::observerNotify */
    ZFCORE_PARAM_WITH_INIT(ZFLevel, observerLevel, ZFLevelAppNormal)

public:
    /** @cond ZFPrivateDoc */
    zfbool operator == (ZF_IN ZFObserverAddParam const &ref) const
    {
        return (this->eventId() == ref.eventId()
            && this->observer() == ref.observer()
            && this->userData() == ref.userData()
            && this->owner() == ref.owner()
            && this->autoRemoveAfterActivate() == ref.autoRemoveAfterActivate()
            && this->observerLevel() == ref.observerLevel()
            );
    }
    inline zfbool operator != (ZF_IN ZFObserverAddParam const &ref) const {return !this->operator == (ref);}
    /** @endcond */
};

zfclassFwd _ZFP_ZFObserverHolderPrivate;
/**
 * @brief holder object for observer logic, see #ZFObject::observerNotify
 */
zffinal zfclassLikePOD ZF_ENV_EXPORT ZFObserverHolder
{
public:
    /** @cond ZFPrivateDoc */
    ZFObserverHolder(void);
    ZFObserverHolder(ZF_IN ZFObserverHolder const &ref);
    ~ZFObserverHolder(void);
    ZFObserverHolder &operator = (ZF_IN ZFObserverHolder const &ref);
    zfbool operator == (ZF_IN ZFObserverHolder const &ref) const;
    inline zfbool operator != (ZF_IN ZFObserverHolder const &ref) const {return !this->operator == (ref);}
    /** @endcond */

public:
    /** @brief see #ZFObject::observerNotify */
    zffinal void observerAdd(ZF_IN const zfidentity &eventId,
                             ZF_IN const ZFListener &observer,
                             ZF_IN_OPT ZFObject *userData = zfnull,
                             ZF_IN_OPT ZFObject *owner = zfnull,
                             ZF_IN_OPT zfbool autoRemoveAfterActivate = zffalse,
                             ZF_IN_OPT ZFLevel observerLevel = ZFLevelAppNormal) const;
    /** @brief see #ZFObject::observerNotify */
    zffinal inline void observerAdd(ZF_IN const ZFObserverAddParam &param) const
    {
        this->observerAdd(param.eventId(), param.observer(), param.userData(), param.owner(), param.autoRemoveAfterActivate(), param.observerLevel());
    }
    /** @brief see #ZFObject::observerNotify */
    zffinal void observerRemove(ZF_IN const zfidentity &eventId,
                                ZF_IN const ZFListener &callback,
                                ZF_IN_OPT ZFObject *userData = zfnull,
                                ZF_IN_OPT ZFComparer<ZFObject *>::Comparer userDataComparer = zfnull) const;
    /** @brief see #ZFObject::observerNotify */
    zffinal void observerRemoveByOwner(ZF_IN ZFObject *owner) const;
    /** @brief see #ZFObject::observerNotify */
    zffinal void observerRemoveAll(ZF_IN const zfidentity &eventId) const;
    /** @brief see #ZFObject::observerNotify */
    zffinal void observerRemoveAll(void) const;
    /** @brief see #ZFObject::observerNotify */
    zffinal zfbool observerHasAdd(void) const;
    /** @brief see #ZFObject::observerNotify */
    zffinal zfbool observerHasAdd(ZF_IN const zfidentity &eventId) const;
    /** @brief see #ZFObject::observerNotify */
    zffinal inline void observerNotify(ZF_IN const zfidentity &eventId,
                                       ZF_IN_OPT ZFObject *param0 = zfnull,
                                       ZF_IN_OPT ZFObject *param1 = zfnull) const
    {
        this->observerNotifyWithCustomSender(this->observerOwner(), eventId, param0, param1);
    }
    /** @brief see #ZFObject::observerNotify */
    zffinal void observerNotifyWithCustomSender(ZF_IN ZFObject *customSender,
                                                ZF_IN const zfidentity &eventId,
                                                ZF_IN_OPT ZFObject *param0 = zfnull,
                                                ZF_IN_OPT ZFObject *param1 = zfnull) const;

public:
    /**
     * @brief return a short string describe the object
     */
    void objectInfoT(ZF_OUT zfstring &ret) const;
    /**
     * @brief return a short string describe the object
     */
    zfstring objectInfo(void) const
    {
        zfstring ret;
        this->objectInfoT(ret);
        return ret;
    }

public:
    /** @brief owner object of this observer holder, or null if none */
    ZFObject *observerOwner(void) const;
    zffinal void _ZFP_ZFObserverHolder_observerOwnerSet(ZF_IN ZFObject *obj);

private:
    _ZFP_ZFObserverHolderPrivate *d;
};

// ============================================================
extern ZF_ENV_EXPORT ZFObserverHolder &_ZFP_ZFObjectGlobalEventObserverRef(void);
/**
 * @brief all event notified by #ZFObject::observerNotify would also be notified to the observers added by this method,
 *   see #ZFObject::observerNotify
 *
 * use only if necessary, which may cause performance issue
 */
#define ZFObjectGlobalEventObserver() (_ZFP_ZFObjectGlobalEventObserverRef())

// ============================================================
// observer
/**
 * @brief see #ZFOBSERVER_EVENT
 *
 * get name from event id, or null if no such event id
 * @note can be found only if accessed or registered by #ZFOBSERVER_EVENT_REGISTER
 */
inline const zfchar *ZFObserverEventGetName(ZF_IN const zfidentity &eventId)
{
    return ZFIdMapGetName(zfText("ZFObserverEvent"), eventId);
}
/**
 * @brief see #ZFOBSERVER_EVENT
 *
 * get event id from name, or #zfidentityInvalid if no such event name
 * @note can be found only if accessed or registered by #ZFOBSERVER_EVENT_REGISTER
 */
inline zfidentity ZFObserverEventGetId(ZF_IN const zfchar *name)
{
    return ZFIdMapGetId(zfText("ZFObserverEvent"), name);
}
/**
 * @brief see #ZFOBSERVER_EVENT
 *
 * get all registered id data, for debug use only
 * @note can be found only if accessed or registered by #ZFOBSERVER_EVENT_REGISTER
 */
inline void ZFObserverEventGetId(ZF_OUT ZFCoreArrayPOD<zfidentity> &idValues, ZF_OUT ZFCoreArrayPOD<const zfchar *> &idNames)
{
    ZFIdMapGetAll(zfText("ZFObserverEvent"), idValues, idNames);
}

/**
 * @brief see #ZFObject::observerNotify
 *
 * usage:
 * @code
 *   zfclass YourClass ...
 *   {
 *       ZFOBSERVER_EVENT(YourEvent)
 *   };
 *
 *   // optional, in cpp files only, required only if you need ZFObserverEventGetId/ZFObserverEventGetName
 *   ZFOBSERVER_EVENT_REGISTER(YourClass, YourEvent)
 * @endcode
 * declare a event for ZFObject's observer logic,
 * declared event name can be accessed by:
 * @code
 *   zfidentity eventId = YourClass::EventYourEvent();
 *   const zfchar *eventName = YourClass::EventYourEvent_name();
 * @endcode
 * note that subclass may declare a event same as parent,
 * while the final event name is different:\n
 *   ParentClass::EventYourEvent() => "ParentClassEventYourEvent"\n
 *   ChildClass::EventYourEvent() => "ChildClassEventYourEvent"\n
 * \n
 * @note we declare the event id as int types for performance,
 *   it's ensured each event has different event id,
 *   but it's only ensured while app is running,
 *   after relaunching the app,
 *   the event id is not ensured the same,
 *   you should use the name of the event to store or pass between apps,
 *   and you can use #ZFObserverEventGetId or #ZFObserverEventGetName
 *   to convert them easily
 */
#define ZFOBSERVER_EVENT(YourEvent) \
    ZFIDMAP_DETAIL(ZFObserverEvent, Event, YourEvent)

/**
 * @brief declare a observer event in global scope, see #ZFOBSERVER_EVENT
 *
 * usage:
 * @code
 *   // in header files
 *   ZF_NAMESPACE_BEGIN(YourNamespace)
 *   / ** @brief you can add doxygen docs here * /
 *   ZFOBSERVER_EVENT_GLOBAL_WITH_NS(YourNamespace, YourEvent)
 *   ZF_NAMESPACE_END(YourNamespace)
 *
 *   // optional, in cpp files only, required only if you need ZFObserverEventGetId/ZFObserverEventGetName
 *   ZFOBSERVER_EVENT_GLOBAL_REGISTER(YourNamespace, YourEvent)
 *
 *   // use the event
 *   zfidentity eventId = YourNamespace::EventYourEvent();
 * @endcode
 * unlike #ZFOBSERVER_EVENT, this macro would declare event outside of class scope,
 * typically you should use #ZFOBSERVER_EVENT_GLOBAL which have "ZFGlobalEvent" as namespace
 */
#define ZFOBSERVER_EVENT_GLOBAL_WITH_NS(GlobalNamespace, YourEvent) \
    ZFIDMAP_GLOBAL_DETAIL(ZFObserverEvent, GlobalNamespace, Event, YourEvent)

/**
 * @brief global event with namespace "ZFGlobalEvent", see #ZFOBSERVER_EVENT_GLOBAL_WITH_NS
 */
#define ZFOBSERVER_EVENT_GLOBAL(YourEvent) \
    ZFOBSERVER_EVENT_GLOBAL_WITH_NS(ZFGlobalEvent, YourEvent)

/** @brief see #ZFOBSERVER_EVENT */
#define ZFOBSERVER_EVENT_REGISTER(Scope, YourEvent) \
    ZFIDMAP_DETAIL_REGISTER(ZFObserverEvent, Scope, Event, YourEvent)

/** @brief see #ZFOBSERVER_EVENT */
#define ZFOBSERVER_EVENT_GLOBAL_REGISTER(Scope, YourEvent) \
    ZFIDMAP_GLOBAL_DETAIL_REGISTER(ZFObserverEvent, Scope, Event, YourEvent)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFObjectObserver_h_

