/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFObjectCore.h
 * @brief base class of all objects
 */

#ifndef _ZFI_ZFObjectCore_h_
#define _ZFI_ZFObjectCore_h_

#include "ZFObjectClassTypeFwd.h"
#include "ZFObjectCast.h"
#include "ZFAny.h"
#include "ZFCallback.h"
#include "ZFClass.h"
#include "ZFMethod.h"
#include "ZFObjectDeclare.h"
#include "ZFObjectInterface.h"
#include "ZFProperty.h"
#include "zfautoObjectFwd.h"
#include "ZFObjectMutex.h"
#include "ZFObjectObserver.h"

ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief left bracket when output ZFObject's info
 * @see ZFObject::objectInfo
 */
#define ZFTOKEN_ZFObjectInfoLeft zfText("<")
/**
 * @brief right bracket when output ZFObject's info
 * @see ZFObject::objectInfo
 */
#define ZFTOKEN_ZFObjectInfoRight zfText(">")

// ============================================================
/**
 * @brief object instance state for ZFObject
 */
typedef enum {
    ZFObjectInstanceStateOnInit = 0x01, /**< @brief object is under #objectOnInit */
    ZFObjectInstanceStateOnInitFinish = 0x03, /**< @brief object is under #objectOnInitFinish */
    ZFObjectInstanceStateIdle = 0, /**< @brief object is constructed successfully */
    ZFObjectInstanceStateOnDeallocPrepare = 0x30, /**< @brief object is under #objectOnDeallocPrepare */
    ZFObjectInstanceStateOnDealloc = 0x10, /**< @brief object is under #objectOnDealloc */
} ZFObjectInstanceState;
/** @brief string tokens */
#define ZFTOKEN_ZFObjectInstanceStateOnInit zfText("ZFObjectInstanceStateOnInit")
/** @brief string tokens */
#define ZFTOKEN_ZFObjectInstanceStateOnInitFinish zfText("ZFObjectInstanceStateOnInitFinish")
/** @brief string tokens */
#define ZFTOKEN_ZFObjectInstanceStateIdle zfText("ZFObjectInstanceStateIdle")
/** @brief string tokens */
#define ZFTOKEN_ZFObjectInstanceStateOnDeallocPrepare zfText("ZFObjectInstanceStateOnDeallocPrepare")
/** @brief string tokens */
#define ZFTOKEN_ZFObjectInstanceStateOnDealloc zfText("ZFObjectInstanceStateOnDealloc")

// ============================================================
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFObjectDummyParent
{
public:
    static const ZFClass *ClassData(void)
    {
        return zfnull;
    }
    static void _ZFP_ZFObjectInitImplementationList(ZFClass *cls) {}
};
zfclassFwd _ZFP_ZFObjectPrivate;
zfclassFwd ZFObjectHolder;
/**
 * @brief base class of all objects
 *
 * -  ZFObject is a Object-C-like class, using objectRetainCount to manage memory:
 *   @code
 *     ZFObject *myObj = zfAlloc(ZFObject); // objectRetainCount = 1
 *     anotherObj = zfRetain(myObj);        // objectRetainCount = 2
 *     zfRelease(myObj);                    // objectRetainCount = 1
 *     zfRelease(anotherObject);            // objectRetainCount = 0, delete
 *   @endcode
 *   you should always use #zfAlloc to create a ZFObject or its subclass,
 *   and use #zfRetain and #zfRelease to manage memory
 *   @see zfRetain, zfRelease, ZFAutoReleasePool
 *
 *   ADVANCED:\n
 *   we are trying hard to simulate the autorelease in Object-C world:
 *   -  #zfautoRelease:
 *     the most powerful and most similar one to autorelease in Object-C,
 *     however it depends on ZFThread,
 *     so most of functions won't use this to return a autoreleased object,
 *     see #zfautoRelease for more info
 *   -  #ZFAutoReleasePool:
 *     similar to NSAutoReleasePool, release after pool release,
 *     zfautoRelease depends on it, and all ZFThread has a pool internally
 *   -  #zflineRelease:
 *     release after code line end, usually used for temporary object
 *   -  #zflineAlloc:
 *     same as zflineRelease(zfAlloc(...)) defined for short
 *   -  #zfblockedRelease:
 *     release after nearest code block
 *   -  #zfblockedAlloc:
 *     declare a ZFObject which looks like allocated in stack,
 *     would be released after nearest code block
 *   -  #zfautoObject:
 *     declare a holder object which would release its content ZFObject when destroyed,
 *     much like the auto_ptr in C++ world
 * -  when inherit from ZFObject,
 *   you must add ZFOBJECT_DECLARE or ZFOBJECT_DECLARE_ABSTRACT to your subclass,
 *   and use zfextends:
 *   @code
 *     zfclass YourClassChild : zfextends YourClassBase
 *     {
 *         ZFOBJECT_DECLARE(YourClassChild, YourClassBase)
 *         // or ZFOBJECT_DECLARE_ABSTRACT if YourClassChild is abstract class
 *     };
 *   @endcode
 *   and, no multiple inheritance is allowed while using ZFObject\n
 *   additionally, you should add #ZFOBJECT_REGISTER if you want the ZFClass map function
 *   @see ZFOBJECT_DECLARE, zfextends
 * -  embeded class can be declared,
 *   however, you must make sure it's name is unique,
 *   we doesn't support class names with namespace
 *   @code
 *     zfclass YourOutterClass : zfextends ZFObject
 *     {
 *         ZFOBJECT_DECLARE(YourOutterClass, ZFObject)
 *
 *         // inner class is allowed,
 *         // but you must ensure it's class name is unique,
 *         // since no namespace qualifier is supported,
 *         // its full class name is "YourInnerClass" instead of "YourOutterClass::YourInnerClass"
 *         zfclass YourInnerClass : zfextends ZFObject
 *         {
 *             ZFOBJECT_DECLARE(YourInnerClass, ZFObject)
 *         };
 *     };
 *   @endcode
 * -  when inherit from ZFObject,
 *   member method is recommended declared as virtual method,
 *   unless you do want to prevent subclass to override,
 *   at this case, use #zffinal to mark the method is final and subclass should not try to override or shadow it
 * -  ZFObject use #objectOnInit and #objectOnDealloc to init and destory object,
 *   instead of constructors and destructors,
 *   for how to use it in subclass, see #objectOnInit
 * -  while override member method of ZFObject type,
 *   you should use zfsuper to call super's method:
 *   @code
 *     zfclass YourClass : zfextends Parent
 *     {
 *         ZFOBJECT_DECLARE(YourClass, Parent)
 *     public:
 *         zfoverride
 *         virtual void funcInParent(void)
 *         {
 *             // override and call super's method by zfsuper
 *             zfsuper::funcInParent();
 *         }
 *     };
 *   @endcode
 *   if overrided method is declared in super interface,
 *   you should use zfsuperI:
 *   @code
 *     zfclass Parent : zfextends ZFObject, zfimplements ParentInterface0
 *     {
 *         ZFOBJECT_DECLARE(Parent, ZFObject)
 *         ZFIMPLEMENTS_DECLARE(ParentInterface0)
 *     public:
 *         zfoverride
 *         virtual void funcInParentInterface0(void)
 *         {
 *             // would call ParentInterface0::funcInParentInterface0
 *             zfsuperI(ParentInterface0)::funcInParentInterface0();
 *         }
 *     };
 *     zfclass YourClass : zfextends Parent, zfimplements ParentInterface1
 *     {
 *         ZFOBJECT_DECLARE(YourClass, Parent)
 *         ZFIMPLEMENTS_DECLARE(ParentInterface1)
 *     public:
 *         zfoverride
 *         virtual void funcInParentInterface0(void)
 *         {
 *             // would call Parent::funcInParentInterface0
 *             zfsuperI(ParentInterface0)::funcInParentInterface0();
 *         }
 *         zfoverride
 *         virtual void funcInParentInterface1(void)
 *         {
 *             // would call ParentInterface1::funcInParentInterface1
 *             zfsuperI(ParentInterface1)::funcInParentInterface1();
 *         }
 *     };
 *   @endcode
 * -  due to some limitation, you should always use ZFObject as a pointer
 *   but without const qualifier,
 *   for const operations, use the const version objects,
 *   such as ZFArray instead of ZFArrayEditable
 *   for const arrays
 * -  you can access class info by:
 *   @code
 *     YourClass::ClassData();
 *     yourClassInstance->classData();
 *     ZFClass::classForName(name);
 *   @endcode
 * -  ZFObject is synchronizable object, you can make it mutable by:
 *   @code
 *     zfsynchronized(obj)
 *     {
 *         // mutable operation
 *     }
 *   @endcode
 *   for advanced mutable operation, use ZFMutex instead\n
 *   for global mutable operation, use #zfsynchronize instead
 *
 * \n
 * ADVANCED:\n
 * we use macros everywhere to achieve goals,
 * there are many types and functions and whatever-it-is,
 * which are generated by macros and are private,
 * you should never ever access it in your code\n
 * here's a list or them:
 * -  "_ZFP_*": shows it's private (maybe types or functions or anything)
 * -  "_ZFI_*": conditional code wrappers
 * -  "_ZFT_*": conditional type defines,
 *   must not be accessed by codes,
 *   but can be modified by adding precompile flags
 *   (usually have no need, and modify at your own risk)
 */
zfclass ZF_ENV_EXPORT ZFObject
{
    _ZFP_ZFOBJECT_DECLARE(ZFObject, _ZFP_ZFObjectDummyParent)
    _ZFP_ZFOBJECT_DECLARE_OBJECT(ZFObject, _ZFP_ZFObjectDummyParent)

public:
    static void _ZFP_ZFObjectInitImplementationList(ZFClass *cls) {}
    virtual inline void _ZFP_ZFObject_interfaceOnInit(void) {}
    virtual inline void _ZFP_ZFObject_interfaceOnDealloc(void) {}
protected:
    /** @cond ZFPrivateDoc */
    ZFObject(void)
    : d(zfnull)
    {
    }
    virtual ~ZFObject(void)
    {
    }
    /** @endcond */

    // ============================================================
    // observer events
public:
    /**
     * @brief see #ZFObject::observerNotify
     *
     * notified when object allocated (after #objectOnInitFinish\n
     * this event is only designed for convenient and for debug use only
     */
    ZFOBSERVER_EVENT(ObjectAfterAlloc)
    /**
     * @brief see #ZFObject::observerNotify
     */
    ZFOBSERVER_EVENT(ObjectBeforeDealloc)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * param0 is a #ZFPointerHolder holds a (const ZFProperty *) value\n
     * param1 is a #ZFPointerHolder holds the old property value,
     * or null if no old value:
     * -  for retain property, it points to (const zfautoObject *)
     * -  for assign property, it points to (const YourPropertyType *)
     *
     * called when first time accessed, and each time setter is called
     */
    ZFOBSERVER_EVENT(ObjectPropertyValueOnUpdate)
    /**
     * @brief see #ZFObject::observerNotify
     *
     * see #objectCachedSet
     */
    ZFOBSERVER_EVENT(ObjectCachedOnChange)

public:
    /**
     * @brief return the object's retain count
     * @see zfRetain, zfRelease
     */
    virtual zfindex objectRetainCount(void);

    /**
     * @brief return an object holder that hold this object without affecting retain count
     */
    virtual ZFObjectHolder *objectHolder(void);

    /**
     * @brief return a short string describe the object instance
     *
     * may looks like this:
     *   ClassName(0x123456)
     * @see objectInfo
     */
    virtual void objectInfoOfInstanceT(ZF_IN_OUT zfstring &ret);
    /** @brief see #objectInfoOfInstanceT */
    virtual inline zfstring objectInfoOfInstance(void)
    {
        zfstring ret;
        this->objectInfoOfInstanceT(ret);
        return ret;
    }

    /**
     * @brief return a short string describe the object
     */
    virtual void objectInfoT(ZF_IN_OUT zfstring &ret);
    /** @brief see #objectInfoT */
    virtual inline zfstring objectInfo(void)
    {
        zfstring ret;
        this->objectInfoT(ret);
        return ret;
    }

protected:
    /**
     * @brief called by #objectInfoT to append object info as a chain
     */
    virtual inline void objectInfoOnAppendTokenLeft(ZF_IN_OUT zfstring &ret)
    {
        ret += ZFTOKEN_ZFObjectInfoLeft;
    }
    /**
     * @brief called by #objectInfoT to append object info as a chain
     */
    virtual inline void objectInfoOnAppendTokenRight(ZF_IN_OUT zfstring &ret)
    {
        ret += ZFTOKEN_ZFObjectInfoRight;
    }
    /**
     * @brief called by #objectInfoT to append object info as a chain
     */
    virtual void objectInfoOnAppend(ZF_IN_OUT zfstring &ret);

public:
    /**
     * @brief get hash of this object
     *
     * by default, this method would return a hash value of the instance's pointer\n
     * \n
     * if you override this method, you must ensure
     * two objects have same hash if they are regarded as same
     * (i.e. #objectCompare return #ZFCompareTheSame)\n
     * this method may or may not be called frequently,
     * you should always try to make the implementation
     * have good performance
     */
    virtual zfidentity objectHash(void);
    /**
     * @brief compare with anotherObj
     * @return ZFCompareTheSame if this == anotherObj\n
     *         ZFCompareUncomparable otherwise
     * @warning if your override #objectCompare,
     *   you must also override #objectHash,
     *   and follow the rules described in #objectHash
     */
    virtual ZFCompareResult objectCompare(ZF_IN ZFObject *anotherObj);

public:
    /**
     * @brief see #tagSet, true if this object has tag,
     *   and tag can be checked by #tagGetAllKeyValue
     */
    virtual zfbool tagHasSet(void);
    /**
     * @brief used to hold a object for app's use, auto retained
     *
     * replace if existing, remove if tag is null
     */
    virtual void tagSet(ZF_IN const zfchar *key,
                        ZF_IN ZFObject *tag,
                        ZF_IN_OPT zfbool autoMarkCached = zffalse);
    /**
     * @brief #tagSet and automatically mark tag as #objectCached
     */
    virtual inline void tagSetMarkCached(ZF_IN const zfchar *key,
                                         ZF_IN ZFObject *tag)
    {
        this->tagSet(key, tag, zftrue);
    }
    /**
     * @brief see #tagSet
     */
    virtual ZFObject *tagGet(ZF_IN const zfchar *key);
    /**
     * @brief see #tagSet
     */
    template<typename T_ZFObject>
    T_ZFObject tagGet(ZF_IN const zfchar *key)
    {
        return ZFCastZFObjectUnchecked(T_ZFObject, this->tagGet(key));
    }
    /**
     * @brief get all key value
     */
    virtual void tagGetAllKeyValue(ZF_IN_OUT ZFCoreArray<const zfchar *> &allKey,
                                   ZF_IN_OUT ZFCoreArray<ZFObject *> &allValue);
    /**
     * @brief remove tag, same as set tag to null
     */
    virtual inline void tagRemove(ZF_IN const zfchar *key)
    {
        this->tagSet(key, zfnull);
    }
    /**
     * @brief remove tag, return removed tag or #zfautoObjectNull if not exist
     */
    virtual zfautoObject tagRemoveAndGet(ZF_IN const zfchar *key);
    /**
     * @brief remove all tag
     *
     * @note it's unsafe to remove all tag manually,
     *   which may break unrelated modules' additional logic,
     *   remove only if necessary\n
     *   typically, you should remove exactly the one you have added
     */
    virtual void tagRemoveAll(void);

public:
    /**
     * @brief internal observer holder,
     *   notifying to the holder is equivalent to notifying to the object
     */
    zffinal const ZFObserverHolder &observerHolder(void);
    /**
     * @brief see #observerNotify
     */
    zffinal void observerAdd(ZF_IN const zfidentity &eventId,
                             ZF_IN const ZFListener &observer,
                             ZF_IN_OPT ZFObject *userData = zfnull,
                             ZF_IN_OPT ZFObject *owner = zfnull,
                             ZF_IN_OPT zfbool autoRemoveAfterActivate = zffalse,
                             ZF_IN_OPT ZFLevel observerLevel = ZFLevelAppNormal);
    /**
     * @brief see #observerNotify
     */
    zffinal inline void observerAdd(ZF_IN const ZFObserverAddParam &param)
    {
        this->observerHolder().observerAdd(param);
    }
    /**
     * @brief see #observerNotify
     */
    zffinal inline void observerRemove(ZF_IN const zfidentity &eventId,
                                       ZF_IN const ZFListener &callback)
    {
        this->observerHolder().observerRemove(eventId, callback);
    }
    /**
     * @brief see #observerNotify
     */
    zffinal inline void observerRemove(ZF_IN const zfidentity &eventId,
                                       ZF_IN const ZFListener &callback,
                                       ZF_IN ZFObject *userData,
                                       ZF_IN_OPT ZFComparer<ZFObject *>::Comparer userDataComparer = zfnull)
    {
        this->observerHolder().observerRemove(eventId, callback, userData, userDataComparer);
    }
    /**
     * @brief see #observerNotify
     */
    zffinal inline void observerRemoveByOwner(ZF_IN ZFObject *owner)
    {
        this->observerHolder().observerRemoveByOwner(owner);
    }
    /**
     * @brief see #observerNotify
     *
     * @note it's unsafe to remove all observer manually,
     *   which may break unrelated modules' observer logic,
     *   remove only if necessary\n
     *   typically, you should remove exactly the one you have added
     */
    zffinal inline void observerRemoveAll(ZF_IN const zfidentity &eventId)
    {
        this->observerHolder().observerRemoveAll(eventId);
    }
    /**
     * @brief see #observerNotify
     *
     * @note it's unsafe to remove all observer manually,
     *   which may break unrelated modules' observer logic,
     *   remove only if necessary\n
     *   typically, you should remove exactly the one you have added
     */
    zffinal inline void observerRemoveAll(void)
    {
        this->observerHolder().observerRemoveAll();
    }
    /**
     * @brief true if any observer has been added
     */
    zffinal inline zfbool observerHasAdd(void)
    {
        return this->observerHolder().observerHasAdd();
    }
    /**
     * @brief true if any observer with eventId has been added
     */
    zffinal inline zfbool observerHasAdd(ZF_IN const zfidentity &eventId)
    {
        return this->observerHolder().observerHasAdd(eventId);
    }
    /**
     * @brief notify the observer with eventId
     *
     * the #ZFListener would be executed\n
     * it's ensured the first added observer would be executed first\n
     * use #ZFGlobalEventCenter or #ZFObjectGlobalEventObserver for global observer\n
     * for instance observer:
     * @code
     *   zfclass YourClass
     *   {
     *       // declare your event here,
     *       // which would generate a method:
     *       //   static const zfchar *EventYourEvent(void)
     *       ZFOBSERVER_EVENT(YourEvent)
     *   };
     *   // notify using declared event
     *   yourClass->observerNotify(YourClass::EventYourEvent(), params...);
     * @endcode
     * @note observers would be compared
     *   by #ZFCallback::objectCompareByInstance when add or remove
     *
     * \n
     * due to lack of lambda capture support,
     * it's hard to pass param outside of a standalone callback into it,
     * so it's recommended to pass by attaching tags to the userData:
     * @code
     *   ZFObject *paramToPass = ...;
     *   ZFObject *userData = ...;
     *   // store param as tag
     *   // make sure the tag name is unique and would be removed properly
     *   userData->tagSet(paramToPass, uniqueTagName);
     *   ZFListener yourStandaloneListener = SOME_CREATE_LOGIC {
     *       // here you can used the passed param
     *       ZFObject *paramPassed = userData->tagGet(uniqueTagName);
     *   };
     *   someEventSender->observerAdd(someEvent, yourStandaloneListener, userData);
     * @endcode
     */
    zffinal inline void observerNotify(ZF_IN const zfidentity &eventId,
                                       ZF_IN_OPT ZFObject *param0 = zfnull,
                                       ZF_IN_OPT ZFObject *param1 = zfnull)
    {
        this->observerHolder().observerNotify(eventId, param0, param1);
    }
    /**
     * @brief see #observerNotify
     */
    zffinal inline void observerNotifyWithCustomSender(ZF_IN ZFObject *customSender,
                                                       ZF_IN const zfidentity &eventId,
                                                       ZF_IN_OPT ZFObject *param0 = zfnull,
                                                       ZF_IN_OPT ZFObject *param1 = zfnull)
    {
        this->observerHolder().observerNotifyWithCustomSender(customSender, eventId, param0, param1);
    }
    zffinal void _ZFP_ZFObject_observerNotifyBegin(void);
    zffinal void _ZFP_ZFObject_observerNotifyEnd(void);

protected:
    /**
     * @brief called when add first observer
     */
    virtual void observerOnAdd(ZF_IN const zfidentity &eventId);
    /**
     * @brief called when remove last observer
     */
    virtual void observerOnRemove(ZF_IN const zfidentity &eventId);
    /**
     * @brief notified when #observerNotify
     *
     * ensured called before any other registered observer
     */
    virtual inline void observerOnEvent(ZF_IN const zfidentity &eventId,
                                        ZF_IN ZFObject *param0,
                                        ZF_IN ZFObject *param1)
    {
    }

public:
    zfbool _ZFP_ZFObjectLockIsAvailable(void);
    void _ZFP_ZFObjectLock(void);
    void _ZFP_ZFObjectUnlock(void);
    zfbool _ZFP_ZFObjectTryLock(void);

    static ZFObject *_ZFP_ZFObjectAlloc(ZFObject *obj);
    ZFObject *_ZFP_ZFObjectCheckOnInit(void);
    static void _ZFP_ZFObjectDealloc(ZFObject *obj);

public:
    /**
     * @brief override this to init your object
     *
     * subclass must call superclass's objectOnInit before any other code if override\n
     * due to the limitation of C++,
     * you must declare it as public function,
     * but never call it in your application manually\n
     * you may also declare objectOnInit with params like this:
     * @code
     *   zfclass Parent : ...
     *   {
     *       ...
     *       virtual ZFObject *objectOnInit(void) {...};
     *   };
     *   zfclass Child : Parent
     *   {
     *   public:
     *       virtual ZFObject *objectOnInit(void)
     *       {
     *           zfsuper::objectOnInit(); // since Parent1 doesn't override objectOnInit
     *           return this;
     *       }
     *       // init with params
     *       virtual ZFObject *objectOnInit(Params...)
     *       {
     *           this->objectOnInit(); // call objectOnInit with no params first
     *           // your init steps
     *           return this;
     *       }
     *   };
     * @endcode
     * @warning objectOnInit and objectOnDealloc is called as a virtual function,
     *   take good care of other virtual function call,
     *   use zfself::func() instead of this->func() if necessary,
     *   or use #objectOnInitFinish/#objectOnDeallocPrepare,
     *   or declare your own constructor with #ZFOBJECT_DECLARE_ALLOW_CUSTOM_CONSTRUCTOR
     * @note due to limitations of C++,
     *   if your parent type declared objectOnInit with different params,
     *   and your child type want to override part of those objectOnInit,
     *   then your child type must also override all objectOnInit that parent declared,
     *   otherwise, some may be hidden
     * @note you may declare objectOnInit as protected method
     *   while declaring subclass of ZFObject,
     *   which means the subclass should not be allocated normally,
     *   typically usage:
     *   @code
     *     zfclass MyObject : zfextends ZFObject
     *     {
     *         ZFOBJECT_DECLARE(MyObject, ZFObject)
     *
     *     public:
     *         static zfautoObject instanceForXxx(xxx)
     *         {
     *             return zfautoObjectCreate(zflineAlloc(MyObject));
     *         }
     *     protected:
     *         ZFCLASS_PRIVATE_ALLOC("should be created by MyObject::instanceForXxx only")
     *         zfoverride
     *         virtual ZFObject *objectOnInit(void) {...}
     *     };
     *     static void func(void)
     *     {
     *         // MyObject *obj = zfAlloc(MyObject); // would compile error
     *         zfautoObject obj = MyObject::instanceForXxx(xxx); // OK
     *     }
     *   @endcode
     */
    virtual ZFObject *objectOnInit(void);
    /**
     * @brief called after #objectOnInit, safe to call virtual functions here
     *
     * usually used to initialize independent resources other than self's internal resources
     */
    virtual void objectOnInitFinish(void);
    /**
     * @brief called before #objectOnDealloc, safe to call virtual functions here
     *
     * usually used to cleanup resources attached to this object other than self's internal resources
     */
    virtual void objectOnDeallocPrepare(void);
    /**
     * @brief override this to destroy your object
     *
     * subclass must call superclass's objectOnDealloc after any other code if override\n
     * see #objectOnInit for more info
     */
    virtual void objectOnDealloc(void);

    /**
     * @brief called to retain object
     *
     * subclass must call superclass's objectOnRetain before any other code if override\n
     * usually you should not override this method
     */
    virtual void objectOnRetain(void);
    /**
     * @brief called to release object
     *
     * subclass must call superclass's onRelase after any other code if override\n
     * usually you should not override this method
     */
    virtual void objectOnRelease(void);

public:
    /**
     * @brief object instance's state
     */
    virtual ZFObjectInstanceState objectInstanceState(void);

public:
    /**
     * @brief whether this object is private object or its class is #ZFClass::classIsPrivate
     *
     * if #objectIsInternal, then it is also #objectIsPrivate
     */
    virtual zfbool objectIsPrivate(void);
    /**
     * @brief see #objectIsPrivate
     */
    virtual void objectIsPrivateSet(ZF_IN zfbool value);
    /**
     * @brief whether this object is internal object or its class is #ZFClass::classIsInternal
     *
     * if #objectIsInternal, then it is also #objectIsPrivate
     */
    virtual zfbool objectIsInternal(void);
    /**
     * @brief see #objectIsInternal
     */
    virtual void objectIsInternalSet(ZF_IN zfbool value);

public:
    zffinal void _ZFP_ZFObject_objectPropertyValueAttach(ZF_IN const ZFProperty *property,
                                                         ZF_IN zfbool firstTimeAccess);
    zffinal void _ZFP_ZFObject_objectPropertyValueDetach(ZF_IN const ZFProperty *property);
    zffinal inline void _ZFP_ZFObject_objectPropertyValueOnUpdate(ZF_IN const ZFProperty *property, ZF_IN const void *oldValue)
    {
        this->objectPropertyValueOnUpdate(property, oldValue);
    }
protected:
    /**
     * @brief see #EventObjectPropertyValueOnUpdate
     */
    virtual void objectPropertyValueOnUpdate(ZF_IN const ZFProperty *property, ZF_IN const void *oldValue);

public:
    /**
     * @brief mark the object being cached or not, for leak test
     *
     * can be called more than once,
     * but must be paired\n
     * a cached object would be filtered from leak test\n
     * by default, all retain property would also be marked as cached
     * if its owner object is cached,
     * you may override #objectCachedOnChange to mark other internal content being cached or not
     */
    virtual void objectCachedSet(ZF_IN zfbool objectCached);
    /** @brief see #objectCachedSet */
    virtual zfbool objectCached(void);
    /** @brief see #objectCachedSet */
    virtual zfindex objectCachedCount(void);
protected:
    /** @brief see #EventObjectCachedOnChange */
    virtual void objectCachedOnChange(void);

private:
    _ZFP_ZFObjectPrivate *d;
    friend zfclassFwd ZFObserverHolder;
    friend zfclassFwd _ZFP_ZFObserverHolderPrivate;
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFObjectCore_h_

#include "ZFObjectRetain.h"
#include "ZFFilterForZFObject.h"
#include "zfnullObject.h"
#include "ZFObjectUtil.h"

