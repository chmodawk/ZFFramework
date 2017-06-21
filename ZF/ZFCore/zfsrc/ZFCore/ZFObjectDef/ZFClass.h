/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFClass.h
 * @brief meta data for ZFObject
 */

#ifndef _ZFI_ZFClass_h_
#define _ZFI_ZFClass_h_

#include "ZFObjectClassTypeFwd.h"
#include "ZFObjectCast.h"
#include "ZFAny.h"
#include "zfautoObjectFwd.h"
#include "ZFObjectObserver.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
zfclassFwd ZFObject;
zfclassFwd ZFInterface;
zfclassFwd ZFMethod;
zfclassFwd ZFProperty;

typedef ZFObject *(* _ZFP_ZFObjectConstructor)(void);
typedef void (* _ZFP_ZFObjectDestructor)(ZF_IN ZFObject *obj);
typedef ZFInterface * (*_ZFP_ZFObjectToInterfaceCastCallback)(ZF_IN ZFObject * const &obj);

// ============================================================
zfclassFwd _ZFP_ZFClassPrivate;
/**
 * @brief ZFObject's class info
 * @see ZFObject
 */
zffinal zfclassNotPOD ZF_ENV_EXPORT ZFClass
{
    ZFCLASS_DISALLOW_COPY_CONSTRUCTOR(ZFClass)

    // ============================================================
    // static methods
public:
    /**
     * @brief get class info by name
     * @return class info or zfnull if not found
     *
     * typical usage:
     * @code
     *   const ZFClass *cls = ZFClass::classForName(zfText("MyObject"));
     *   zfautoObject objTmp = ((cls != zfnull) ? cls->newInstance() : zfautoObjectNull);
     *   MyObject *obj = objTmp.to<MyObject *>();
     * @endcode
     * @note the class to find must:
     *   -  inherit from ZFObject or its subclass
     *   -  have #ZFOBJECT_DECLARE declared in the class
     *   -  have #ZFOBJECT_REGISTER defined,
     *      or match the situation described in #ZFOBJECT_REGISTER
     *
     * @see ZFOBJECT_DECLARE, ZFOBJECT_REGISTER, newInstanceForName
     */
    static const ZFClass *classForName(ZF_IN const zfchar *className);

    /**
     * @brief convenient method to create a new instance by name
     * @return new instance or zfnull if class not found
     * @note must have ZFClass map set up,
     *   for more information, please refer to #classForName and #ZFOBJECT_REGISTER
     * @see ZFOBJECT_DECLARE, ZFOBJECT_REGISTER, classForName
     */
    static inline zfautoObject newInstanceForName(ZF_IN const zfchar *className)
    {
        return ZFClass::newInstanceForNameWithoutLeakTest(className);
    }
    /** @brief see #newInstanceForName */
    static zfautoObject newInstanceForName(ZF_IN const zfchar *className,
                                           ZF_IN const ZFCallerInfo &callerInfo);
    /** @brief see #newInstanceForName */
    static zfautoObject newInstanceForNameWithoutLeakTest(ZF_IN const zfchar *className);

    /**
     * @brief get all class currently registered
     */
    static void allClass(ZF_OUT ZFCoreArray<const ZFClass *> &ret);
    /** @brief see #allClass */
    static inline ZFCoreArrayPOD<const ZFClass *> allClass(void)
    {
        ZFCoreArrayPOD<const ZFClass *> ret;
        ZFClass::allClass(ret);
        return ret;
    }

    // ============================================================
    // instance observer
public:
    /** @brief see #ZFClass::instanceObserverAdd */
    zffinal zfclassLikePOD ZF_ENV_EXPORT InstanceObserverAddParam
    {
        ZFCORE_PARAM_DECLARE_SELF(InstanceObserverAddParam)

        /** @brief see #ZFClass::instanceObserverAdd */
        ZFCORE_PARAM(ZFListener, observer)

        /** @brief see #ZFClass::instanceObserverAdd */
        ZFCORE_PARAM_WITH_INIT(ZFObject *, userData, zfnull)

        /** @brief see #ZFClass::instanceObserverAdd */
        ZFCORE_PARAM_WITH_INIT(ZFObject *, owner, zfnull)

        /** @brief see #ZFClass::instanceObserverAdd */
        ZFCORE_PARAM_WITH_INIT(ZFLevel, observerLevel, ZFLevelAppNormal)

        /** @brief see #ZFClass::instanceObserverAdd */
        ZFCORE_PARAM_WITH_INIT(zfbool, observeAllChildType, zftrue)
    };
    /**
     * @brief add an observer which would be called if any of this class's instance created
     */
    void instanceObserverAdd(ZF_IN const ZFListener &observer,
                             ZF_IN_OPT ZFObject *userData = zfnull,
                             ZF_IN_OPT ZFObject *owner = zfnull,
                             ZF_IN_OPT ZFLevel observerLevel = ZFLevelAppNormal,
                             ZF_IN_OPT zfbool observeAllChildType = zftrue) const;
    /** @brief see #instanceObserverAdd */
    inline void instanceObserverAdd(ZF_IN const ZFClass::InstanceObserverAddParam &param) const
    {
        this->instanceObserverAdd(param.observer(), param.userData(), param.owner(), param.observerLevel(), param.observeAllChildType());
    }
    /** @brief see #instanceObserverAdd */
    void instanceObserverRemove(ZF_IN const ZFListener &observer) const;
    /** @brief see #instanceObserverAdd */
    void instanceObserverRemoveByOwner(ZF_IN ZFObject *owner) const;
    /**
     * @brief see #instanceObserverAdd
     *
     * @note it's unsafe to remove all observer manually,
     *   which may break unrelated modules' observer logic,
     *   remove only if necessary\n
     *   typically, you should remove exactly the one you have added
     */
    void instanceObserverRemoveAll(void) const;
    void _ZFP_ZFClass_instanceObserverNotify(ZF_IN ZFObject *obj) const;

    // ============================================================
    // class data change observer
public:
    void _ZFP_ZFClass_classDataChangeNotify(void) const;
    /**
     * @brief auto remove #classTagRemove when class meta data changed
     *
     * class meta data would change if:
     * -  method register or unregistered
     * -  property register or unregistered
     *
     *
     * this method is useful if you cached some data by #classTagSet
     * accorrding to class's method or property list,
     * and want to update it again if meta data changed\n
     * see also #ZFClassDataChangeObserver
     */
    void classDataChangeAutoRemoveTagAdd(ZF_IN const zfchar *tag) const;
    /** @brief see #classDataChangeAutoRemoveTagAdd */
    void classDataChangeAutoRemoveTagRemove(ZF_IN const zfchar *tag) const;

    // ============================================================
    // class info
public:
    /**
     * @brief return a short string describe the object
     */
    void objectInfoT(ZF_IN_OUT zfstring &ret) const;
    /** @brief see #objectInfoT */
    zfstring objectInfo(void) const
    {
        zfstring ret;
        this->objectInfoT(ret);
        return ret;
    }

    /**
     * @brief return a string describe the class inherit tree, debug use only
     */
    void objectInfoOfInheritTreeT(ZF_IN_OUT zfstring &ret) const;
    /** @brief see #objectInfoOfInheritTreeT */
    zfstring objectInfoOfInheritTree(void) const
    {
        zfstring ret;
        this->objectInfoOfInheritTreeT(ret);
        return ret;
    }

public:
    /**
     * @brief true if object is subclass of cls
     */
    zfbool classIsSubclassOf(ZF_IN const ZFClass *cls) const;
    /**
     * @brief true if class is subclass of cls, or implements cls
     */
    zfbool classIsTypeOf(ZF_IN const ZFClass *cls) const;

public:
    /**
     * @brief class name, e.g. "ZFObject"
     */
    inline const zfchar *className(void) const
    {
        return this->classNameCache;
    }

    /**
     * @brief class's parent, zfnull if none
     */
    inline const ZFClass *parentClass(void) const
    {
        return this->classParentCache;
    }

    /**
     * @brief true if the class is abstract class
     *
     * #newInstance would return zfnull if the class is abstract
     */
    zfbool classIsAbstract(void) const;
    /**
     * @brief true if the class is an interface
     */
    zfbool classIsInterface(void) const;
    /**
     * @brief whether the class is private class
     *
     * all class that have "_ZFP_" as prefix would be treated as private class\n
     * a private class should not be used publicly,
     * however, you may still apply leak test or alloc observer for it,
     * see #classIsInternal
     */
    zfbool classIsPrivate(void) const;
    /**
     * @brief whether the class is internal class
     *
     * all class that have "_ZFP_I_" as prefix would be treated as internal class\n
     * an internal class should not be used publicly,
     * also, it would be ignored from leak test or alloc observer,
     * see #classIsPrivate
     */
    zfbool classIsInternal(void) const;

    /**
     * @brief make a new instance of ZFObject dynamically, which is described by ZFClass
     *
     * typical usage:
     * @code
     *   ZFObject *myObj = zfAlloc(MyObject);
     *   ...
     *   // OK, newObj is a new instance of MyObject
     *   zfautoObject newObjTmp = myObj->classData()->newInstance();
     *   ZFObject *newObj = newObjTmp.toObject();
     * @endcode
     * @note object's no param version of objectOnInit would be called,
     *   ZFClass doesn't support newInstance with params
     */
    inline zfautoObject newInstance(void) const
    {
        return this->newInstanceWithoutLeakTest();
    }
    /** @brief see #newInstance */
    zfautoObject newInstance(ZF_IN const ZFCallerInfo &callerInfo) const;
    /** @brief see #newInstance */
    zfautoObject newInstanceWithoutLeakTest(void) const;

    /**
     * @brief get implemented interface count
     */
    zfindex implementedInterfaceCount(void) const;
    /**
     * @brief get implemented interface
     */
    const ZFClass *implementedInterfaceAtIndex(ZF_IN zfindex index) const;

    // ============================================================
    // ZFMethod
public:
    /**
     * @brief get the count of method registered to this ZFClass
     *
     * note that parent class's method won't be included\n
     * the order is ensured to be the same as ZFMethod declared
     * @see methodAtIndex
     * @note can be found only if it matches the condition described in #ZFMETHOD_REGISTER
     */
    zfindex methodCount(void) const;
    /**
     * @brief get the method at index, assert fail if out of bounds
     *
     * note that parent class's method won't be included\n
     * the order is ensured to be the same as ZFMethod declared
     * @see methodForNameIgnoreParent, methodForName
     * @note can be found only if it matches the condition described in #ZFMETHOD_REGISTER
     */
    const ZFMethod *methodAtIndex(ZF_IN zfindex index) const;
    /* ZFMETHOD_MAX_PARAM */
    /**
     * @brief get the method by name within this class only, or zfnull if not exists
     *
     * the following optional params are, type id of each param type
     * described by #ZFPropertyTypeIdData::PropertyTypeId,
     * if more than one method with same name (and or param type id) were found,
     * the first one would be returned
     *
     * @see methodAtIndex, methodForName
     * @note can be found only if it matches the condition described in #ZFMETHOD_REGISTER
     */
    const ZFMethod *methodForNameIgnoreParent(ZF_IN const zfchar *methodName
                                              , ZF_IN const zfchar *methodParamTypeId0
                                              , ZF_IN_OPT const zfchar *methodParamTypeId1 = zfnull
                                              , ZF_IN_OPT const zfchar *methodParamTypeId2 = zfnull
                                              , ZF_IN_OPT const zfchar *methodParamTypeId3 = zfnull
                                              , ZF_IN_OPT const zfchar *methodParamTypeId4 = zfnull
                                              , ZF_IN_OPT const zfchar *methodParamTypeId5 = zfnull
                                              , ZF_IN_OPT const zfchar *methodParamTypeId6 = zfnull
                                              , ZF_IN_OPT const zfchar *methodParamTypeId7 = zfnull
                                              ) const;
    /** @brief see #methodForNameIgnoreParent */
    const ZFMethod *methodForNameIgnoreParent(ZF_IN const zfchar *methodName) const;
    /**
     * @brief get the method by name hierarchically from class inherit tree, or zfnull if not exists
     *
     * searching from subclass to parent class, return the first matched
     * @see methodAtIndex, methodForNameIgnoreParent
     * @note can be found only if it matches the condition described in #ZFMETHOD_REGISTER
     * @note ensured breadth-first
     */
    const ZFMethod *methodForName(ZF_IN const zfchar *methodName
                                  , ZF_IN const zfchar *methodParamTypeId0
                                  , ZF_IN_OPT const zfchar *methodParamTypeId1 = zfnull
                                  , ZF_IN_OPT const zfchar *methodParamTypeId2 = zfnull
                                  , ZF_IN_OPT const zfchar *methodParamTypeId3 = zfnull
                                  , ZF_IN_OPT const zfchar *methodParamTypeId4 = zfnull
                                  , ZF_IN_OPT const zfchar *methodParamTypeId5 = zfnull
                                  , ZF_IN_OPT const zfchar *methodParamTypeId6 = zfnull
                                  , ZF_IN_OPT const zfchar *methodParamTypeId7 = zfnull
                                  ) const;
    /** @brief see #methodForName */
    const ZFMethod *methodForName(ZF_IN const zfchar *methodName) const;
    /**
     * @brief get all method with name, ignoring method id
     */
    void methodForNameGetAllT(ZF_IN_OUT ZFCoreArray<const ZFMethod *> &ret,
                              ZF_IN const zfchar *methodName) const;
    /**
     * @brief get all method with name, ignoring method id
     */
    ZFCoreArrayPOD<const ZFMethod *> methodForNameGetAll(ZF_IN const zfchar *methodName) const
    {
        ZFCoreArrayPOD<const ZFMethod *> ret;
        this->methodForNameGetAllT(ret, methodName);
        return ret;
    }

    // ============================================================
    // ZFProperty
public:
    /**
     * @brief get ZFProperty count registered to this class
     *
     * note that parent class's property won't be included\n
     * the order is ensured to be the same as property declared
     * @see propertyAtIndex
     * @note can be found only if it matches the condition described in #ZFPROPERTY_REGISTER
     */
    zfindex propertyCount(void) const;
    /**
     * @brief get ZFProperty at index
     *
     * note that parent class's property won't be included\n
     * the order is ensured to be the same as property declared
     * @see propertyForName
     * @note can be found only if it matches the condition described in #ZFPROPERTY_REGISTER
     */
    const ZFProperty *propertyAtIndex(ZF_IN zfindex index) const;

    /**
     * @brief get the property by name within this class only, or zfnull if not exists
     *
     * propertyName should be "Property" without "set" or "get"\n
     * note that parent class's property won't be included
     * @see propertyAtIndex, propertyForName
     * @note can be found only if it matches the condition described in #ZFPROPERTY_REGISTER
     */
    const ZFProperty *propertyForNameIgnoreParent(const zfchar *propertyName) const;
    /**
     * @brief get the property by name hierarchically from class inherit tree, or zfnull if not exists
     *
     * propertyName should be "Property" without "set" or "get"\n
     * searching from subclass to parent class, return the first matched
     * @see propertyAtIndex, propertyForName
     * @note can be found only if it matches the condition described in #ZFPROPERTY_REGISTER
     * @note ensured breadth-first
     */
    const ZFProperty *propertyForName(const zfchar *propertyName) const;
    /**
     * @brief whether the property has #ZFPROPERTY_OVERRIDE_ON_INIT_DECLARE
     */
    zfbool propertyHasOverrideInitStep(void) const;
    /**
     * @brief whether the property has #ZFPROPERTY_OVERRIDE_ON_INIT_DECLARE
     */
    zfbool propertyHasOverrideInitStep(ZF_IN const ZFProperty *property) const;

    // ============================================================
    // class instance methods
public:
    /**
     * @brief set a classTag for the class, internal use only
     *
     * @note this method is not thread-safe
     * @note all classTags would be removed during #ZFFrameworkCleanup
     *   as #ZFLevelZFFrameworkHigh and #ZFLevelZFFrameworkEssential,
     *   you must ensure the classTag is safe to be deleted at this time
     * @note the stored class tag should have no leak test enabled (use #zfAllocWithoutLeakTest, etc)
     * @note usually used to store meta-data for performance use only
     */
    void classTagSet(ZF_IN const zfchar *key,
                     ZF_IN ZFObject *tag,
                     ZF_IN_OPT zfbool autoMarkCached = zffalse) const;
    /**
     * @brief #classTagSet and automatically mark tag as #ZFObject::objectCached
     */
    inline void classTagSetMarkCached(ZF_IN const zfchar *key,
                                      ZF_IN ZFObject *tag) const
    {
        this->classTagSet(key, tag, zftrue);
    }
    /**
     * @brief see #classTagSet
     */
    ZFObject *classTagGet(ZF_IN const zfchar *key) const;
    /**
     * @brief see #classTagGet
     */
    template<typename T_ZFObject>
    T_ZFObject classTagGet(ZF_IN const zfchar *key) const
    {
        return ZFCastZFObjectUnchecked(T_ZFObject, this->classTagGet(key));
    }
    /** @brief see #classTagSet */
    zffinal void classTagGetAllKeyValue(ZF_IN_OUT ZFCoreArray<const zfchar *> &allKey,
                                        ZF_IN_OUT ZFCoreArray<ZFObject *> &allValue) const;
    /**
     * @brief remove tag, same as set tag to null
     */
    inline void classTagRemove(ZF_IN const zfchar *key) const
    {
        this->classTagSet(key, zfnull);
    }
    /**
     * @brief remove tag, return removed tag or #zfautoObjectNull if not exist
     */
    zffinal zfautoObject classTagRemoveAndGet(ZF_IN const zfchar *key) const;
    /**
     * @brief see #classTagSet
     *
     * @note it's unsafe to remove all tag manually,
     *   which may break unrelated modules' additional logic,
     *   remove only if necessary\n
     *   typically, you should remove exactly the one you have added
     */
    zffinal void classTagRemoveAll(void) const;

    // ============================================================
    // private
public:
    /** @cond ZFPrivateDoc */
    static ZFClass *_ZFP_ZFClassRegister(ZF_IN zfbool *ZFCoreLibDestroyFlag,
                                         ZF_IN const zfchar *name,
                                         ZF_IN const ZFClass *parent,
                                         ZF_IN _ZFP_ZFObjectConstructor constructor,
                                         ZF_IN _ZFP_ZFObjectDestructor destructor,
                                         ZF_IN_OPT zfbool isInterface = zffalse);
    static void _ZFP_ZFClassUnregister(ZF_IN zfbool *ZFCoreLibDestroyFlag, ZF_IN const zfchar *name);
    ZFClass(void);
    ~ZFClass(void);
    zfbool _ZFP_ZFClass_interfaceNeedRegister(void);
    void _ZFP_ZFClass_interfaceRegister(ZF_IN const ZFClass *cls,
                                        ...);
    void _ZFP_ZFClass_interfaceRegisterCastCallback(ZF_IN _ZFP_ZFObjectToInterfaceCastCallback callback,
                                                    ...);
    ZFInterface *_ZFP_ZFClass_interfaceCast(ZF_IN ZFObject * const &obj,
                                            ZF_IN const ZFClass *interfaceClass) const;

    static ZFClass *_ZFP_ZFClassInitFinish(ZF_IN ZFClass *cls);
    static void _ZFP_ZFClassInitFinish_parentListCache(ZF_IN ZFClass *cls);
    static void _ZFP_ZFClassInitFinish_parentInterfaceListCache(ZF_IN ZFClass *cls);
    static void _ZFP_ZFClassInitFinish_interfaceCastListCache(ZF_IN ZFClass *cls);
    static void _ZFP_ZFClassInitFinish_allParentAndChildrenCache(ZF_IN ZFClass *cls);
    static void _ZFP_ZFClassInitFinish_methodAndPropertyFindCache(ZF_IN ZFClass *cls);
    static void _ZFP_ZFClassInitFinish_propertyMetaDataCache(ZF_IN ZFClass *cls);
    static void _ZFP_ZFClassInitFinish_instanceObserverCache(ZF_IN ZFClass *cls);

    void _ZFP_ZFClass_objectDesctuct(ZF_IN ZFObject *obj) const;
    ZFClass *_ZFP_ZFClass_removeConst(void) const
    {
        return const_cast<ZFClass *>(this);
    }

    void _ZFP_ZFClass_methodAndPropertyAutoRegister(void) const;
    void _ZFP_ZFClass_methodRegister(ZF_IN const ZFMethod *method);
    void _ZFP_ZFClass_methodUnregister(ZF_IN const ZFMethod *method);
    zfbool _ZFP_ZFClass_propertyRegister(ZF_IN const ZFProperty *zfproperty);
    void _ZFP_ZFClass_propertyUnregister(ZF_IN const ZFProperty *zfproperty);
    void _ZFP_ZFClass_propertyAutoInitRegister(ZF_IN const ZFProperty *property) const;
    void _ZFP_ZFClass_propertyAutoInitAction(ZF_IN ZFObject *owner) const;
    void _ZFP_ZFClass_propertyInitStepRegister(ZF_IN const ZFProperty *property) const;
    zfbool _ZFP_ZFClass_propertyInitStepIsTheSame(ZF_IN const ZFProperty *property,
                                                  ZF_IN const ZFClass *refClass) const;
    /** @endcond */

public:
    zfbool _ZFP_ZFClassNeedInitImplementationList;
private:
    _ZFP_ZFClassPrivate *d;
    friend zfclassFwd _ZFP_ZFClassPrivate;
    const zfchar *classNameCache;
    const ZFClass *classParentCache;
};

zfclassLikePOD ZF_ENV_EXPORT _ZFP_ZFClassRegisterHolder
{
public:
    _ZFP_ZFClassRegisterHolder(ZF_IN zfbool *ZFCoreLibDestroyFlag, ZF_IN ZFClass *cls)
    : ZFCoreLibDestroyFlag(ZFCoreLibDestroyFlag)
    , cls(cls)
    {
    }
    ~_ZFP_ZFClassRegisterHolder(void)
    {
        if(!*(this->ZFCoreLibDestroyFlag))
        {
            ZFClass::_ZFP_ZFClassUnregister(this->ZFCoreLibDestroyFlag, this->cls->className());
        }
    }
public:
    zfbool *ZFCoreLibDestroyFlag;
    ZFClass *cls;
};

// ============================================================
ZF_NAMESPACE_BEGIN(ZFGlobalEvent)
/**
 * @brief notified when any class data changed, notified to #ZFClassDataChangeObserver,
 *   see #ZFObject::observerNotify
 *
 * param0 is a #ZFPointerHolder holds a (const #ZFClassDataChangeData *) value\n
 * called when:
 * -  class registered or unregistered
 * -  class's property registered or unregistered (including user registered property)
 * -  class's method or function method registered or unregistered (including user registered method)
 *
 *
 * \n
 * for each event call, #ZFClassDataChangeData::changedClass,
 * #ZFClassDataChangeData::changedProperty
 * and #ZFClassDataChangeData::changedMethod
 * are ensured only one not null\n
 * \n
 * \n
 * note this method would be notified only if #ZFFrameworkStateCheck with #ZFLevelZFFrameworkLow
 * returned #ZFFrameworkStateAvailable
 *
 * @warning app code can add observer to this event,
 *   but must not manually notify this event\n
 *   also, take care of performance
 */
ZFOBSERVER_EVENT_GLOBAL(ClassDataChange)
ZF_NAMESPACE_END(ZFGlobalEvent)

extern ZF_ENV_EXPORT ZFObserverHolder &_ZFP_ZFClassDataChangeObserverRef(void);
/**
 * @brief see #ZFGlobalEvent::EventClassDataChange
 *
 * @warning app code can add observer to this event,
 *   but must not manually notify this event\n
 *   also, take care of performance
 */
#define ZFClassDataChangeObserver (_ZFP_ZFClassDataChangeObserverRef())

// ============================================================
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCoreCriticalClassNotTypeOf
{
public:
    static zfstringA classInfo(ZF_IN const ZFClass *cls)
    {
        if(cls)
        {
            return zfsCoreZ2A(cls->className());
        }
        else
        {
            return zfsCoreZ2A(ZFTOKEN_zfnull);
        }
    }
};
/**
 * @brief log that likes "[file function (line)] class xxx not type of xxx"
 */
#define zfCoreCriticalClassNotTypeOf(cls, desired) \
    do { \
        zfCoreCriticalErrorPrepare(); \
        zfCoreLogCriticalMessage(zfTextA("class %s not type of %s"), \
            _ZFP_ZFCoreCriticalClassNotTypeOf::classInfo(cls).cString(), \
            _ZFP_ZFCoreCriticalClassNotTypeOf::classInfo(desired).cString()); \
        zfCoreCriticalError(); \
    } while(zffalse)
/**
 * @brief see #zfCoreCriticalClassNotTypeOf
 */
#define zfCoreCriticalClassNotTypeOfDetail(callerInfo, cls, desired) \
    do { \
        zfCoreCriticalErrorPrepare(); \
        zfCoreLogCriticalMessageDetail(callerInfo, zfTextA("class %s not type of %s"), \
            _ZFP_ZFCoreCriticalClassNotTypeOf::classInfo(cls).cString(), \
            _ZFP_ZFCoreCriticalClassNotTypeOf::classInfo(desired).cString()); \
        zfCoreCriticalError(); \
    } while(zffalse)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFClass_h_

#include "ZFFilterForZFClass.h"

