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

#include "ZFCore/ZFSTLWrapper/zfstl_string.h"
#include "ZFCore/ZFSTLWrapper/zfstl_vector.h"
#include "ZFCore/ZFSTLWrapper/zfstl_deque.h"
#include "ZFCore/ZFSTLWrapper/zfstl_map.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// ZFClass's global data
ZF_STATIC_INITIALIZER_INIT(ZFClassDataHolder)
{
}
ZF_STATIC_INITIALIZER_DESTROY(ZFClassDataHolder)
{
    ZFCoreArrayPOD<ZFClass *> allClassDelayed;
    this->delayDeleteMap.allValueT(allClassDelayed);
    this->delayDeleteMap.removeAll();

    ZFCoreArrayPOD<ZFClass *> allClass;
    this->classMap.allValueT(allClass);
    this->classMap.removeAll();

    for(zfindex i = 0; i < allClassDelayed.count(); ++i)
    {
        zfdelete(allClassDelayed[i]);
    }
    for(zfindex i = 0; i < allClass.count(); ++i)
    {
        zfdelete(allClass[i]);
    }
}
ZFCoreMap classMap; // ZFClass *
ZFCoreMap delayDeleteMap; // ZFClass *
/*
 * delay delete a class
 * ZFClass may be registered by different module,
 * while unloading a module,
 * _ZFP_ZFClassUnregister would be called to unload the class,
 * however, it may be called earlier than object instance's dealloc step,
 * so we cache the ZFClass object,
 * remove from the activating classMap,
 * and delete them all during ZFClassDataHolder's dealloc step
 *
 * this can't resolve the problem perfectly,
 * but did resolve most cases
 */
ZF_STATIC_INITIALIZER_END(ZFClassDataHolder)
#define _ZFP_ZFClassMap (ZF_STATIC_INITIALIZER_INSTANCE(ZFClassDataHolder)->classMap)
#define _ZFP_ZFClassDelayDeleteMap (ZF_STATIC_INITIALIZER_INSTANCE(ZFClassDataHolder)->delayDeleteMap)

// ============================================================
// _ZFP_ZFClassPrivate
typedef zfstlmap<zfstlstringZ, zfautoObject> _ZFP_ZFClassTagMapType;
typedef zfstlmap<const ZFProperty *, zfstlmap<const ZFClass *, zfbool> > _ZFP_ZFClassPropertyInitStepMapType;
zfclassNotPOD _ZFP_ZFClassPrivate
{
public:
    zfindex refCount;
    /*
     * here's a memo for ZFCoreLibDestroyFlag:
     *
     * ZFFramework is designed as plugin type framework,
     * which can be load dynamically
     *
     * it's all right for most case if use
     * ZF_GLOBAL_INITIALIZER_INIT/ZF_STATIC_INITIALIZER_INIT,
     * however, for core meta-object types (class map, method map, etc),
     * it require additional register and unregister steps
     * to ensure initialize and destroy order
     *
     * here's a typical case of the questions mentioned above:
     *
     * * libraries that depends on ZFFramework needs to be load and unload at runtime
     *
     *   at this case, we need some static holder object, to unregister class map from ZFFramework,
     *   during the library being unloaded
     *
     * * ZFFramework would be unloaded before app's destruction,
     *   this is typical if under Qt using QLibrary
     *
     *   at this case, simply use static holder object would cause crash during app's destruction,
     *   since ZFFramework already unloaded when the holder object try to unregister class map
     */
    ZFCoreArrayPOD<zfbool *> ZFCoreLibDestroyFlag;
    ZFClass *pimplOwner;
    _ZFP_ZFObjectConstructor constructor;
    _ZFP_ZFObjectDestructor destructor;
    zfstring className;
    const ZFClass *classParent;
    zfbool isInterface;
    zfbool isPrivateClass;
    zfbool isInternalClass;

public:
    zfbool needRegisterImplementedInterface;
    zfbool internalTypesNeedAutoRegister; // used to register ZFMethod and ZFProperty
    zfbool needFinalInit;
    ZFCoreArrayPOD<const ZFClass *> implementedInterface;
    zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> > methodMap;
    ZFCoreArrayPOD<const ZFMethod *> methodList;
    ZFCoreArrayPOD<const ZFProperty *> propertyList;
    ZFCoreMap propertyMap; // map to const ZFProperty *
    /*
     * store all property declared by #ZFPROPERTY_MARK_AUTO_INIT
     * including self and all parent
     */
    zfstlmap<const ZFProperty *, zfbool> propertyAutoInitMap;
    /*
     * all property that has override init step by #ZFPROPERTY_OVERRIDE_ON_INIT_DECLARE
     * (including self and all parent),
     * used to check whether two class has same property init step
     */
    _ZFP_ZFClassPropertyInitStepMapType propertyInitStepMap;

public:
    _ZFP_ZFClassTagMapType classTagMap;

public:
    zfstlmap<zfstlstringZ, zfbool> classDataChangeAutoRemoveTagList;

public:
    const ZFClass **parentListCache; // all parent including self
    const ZFClass **parentInterfaceListCache; // all parent interface, count may differ from interfaceCastListCache
    const ZFClass **interfaceCastListCache; // all parent implemented interface, for interface cast
    _ZFP_ZFObjectToInterfaceCastCallback *interfaceCastCallbackListCache;

public:
    /*
     * cache all parent and children for future use
     */
    zfstlmap<const ZFClass *, zfbool> allParent; // all parent and interface excluding self
    zfstlmap<const ZFClass *, zfbool> allChildren; // all children excluding self

public:
    /*
     * cache all parent to search method and property for performance
     *
     * unlike allParent, this array ensured ordered by: self > parent interface > parent
     */
    zfstlvector<const ZFClass *> methodAndPropertyFindCache;

public:
    zfclassLikePOD InstanceObserverData
    {
    public:
        ZFListener observer;
        zfautoObject userData;
        ZFObject *owner;
        ZFLevel observerLevel;
    };
    zfstldeque<ZFCorePointerForObject<_ZFP_ZFClassPrivate::InstanceObserverData *> > instanceObserver;
    zfstldeque<_ZFP_ZFClassPrivate::InstanceObserverData *> instanceObserverCached;
    void _instanceObserverDoAdd(ZF_IN_OUT zfstldeque<_ZFP_ZFClassPrivate::InstanceObserverData *> &buf,
                                ZF_IN _ZFP_ZFClassPrivate::InstanceObserverData *data)
    {
        zfstlsize index = buf.size();
        while(index > 0 && buf[index - 1]->observerLevel > data->observerLevel)
        {
            --index;
        }
        buf.insert(buf.begin() + index, data);
    }
    void instanceObserverDoAdd(ZF_IN _ZFP_ZFClassPrivate::InstanceObserverData *data,
                               ZF_IN zfbool observeAllChildType)
    {
        this->_instanceObserverDoAdd(this->instanceObserverCached, data);
        if(!observeAllChildType)
        {
            return ;
        }

        for(zfstlmap<const ZFClass *, zfbool>::iterator childIt = this->allChildren.begin(); childIt != this->allChildren.end(); ++childIt)
        {
            if(!childIt->first->classIsInternal())
            {
                this->_instanceObserverDoAdd(childIt->first->d->instanceObserverCached, data);
            }
        }
    }
    void instanceObserverDoRemove(ZF_IN _ZFP_ZFClassPrivate::InstanceObserverData *data)
    {
        const ZFClass *cls = this->pimplOwner;
        zfstlmap<const ZFClass *, zfbool>::iterator childIt = this->allChildren.begin();
        do
        {
            for(zfstlsize i = 0; i < cls->d->instanceObserverCached.size(); ++i)
            {
                if(cls->d->instanceObserverCached[i] == data)
                {
                    cls->d->instanceObserverCached.erase(cls->d->instanceObserverCached.begin() + i);
                    break;
                }
            }

            if(childIt != this->allChildren.end())
            {
                cls = childIt->first;
                ++childIt;
            }
            else
            {
                break;
            }
        } while(zftrue);
    }

public:
    _ZFP_ZFClassPrivate(void)
    : refCount(1)
    , ZFCoreLibDestroyFlag()
    , pimplOwner(zfnull)
    , constructor(zfnull)
    , destructor(zfnull)
    , className()
    , classParent(zfnull)
    , isInterface(zffalse)
    , isPrivateClass(zffalse)
    , isInternalClass(zffalse)
    , needRegisterImplementedInterface(zftrue)
    , internalTypesNeedAutoRegister(zftrue)
    , needFinalInit(zftrue)
    , implementedInterface()
    , methodMap()
    , methodList()
    , propertyList()
    , propertyMap()
    , propertyAutoInitMap()
    , propertyInitStepMap()
    , classTagMap()
    , classDataChangeAutoRemoveTagList()
    , parentListCache(zfnull)
    , parentInterfaceListCache(zfnull)
    , interfaceCastListCache(zfnull)
    , interfaceCastCallbackListCache(zfnull)
    , allParent()
    , allChildren()
    , methodAndPropertyFindCache()
    , instanceObserver()
    , instanceObserverCached()
    {
    }
    ~_ZFP_ZFClassPrivate(void)
    {
        for(zfindex i = 0; i < this->ZFCoreLibDestroyFlag.count(); ++i)
        {
            *(this->ZFCoreLibDestroyFlag[i]) = zftrue;
        }
        zffree(this->parentListCache);
        this->parentListCache = zfnull;
        zffree(this->parentInterfaceListCache);
        this->parentInterfaceListCache = zfnull;
        zffree(this->interfaceCastListCache);
        this->interfaceCastListCache = zfnull;
        zffree(this->interfaceCastCallbackListCache);
        this->interfaceCastCallbackListCache = zfnull;
    }
};

// ============================================================
// clear class tag both in ZFLevelZFFrameworkEssential and ZFLevelZFFrameworkHigh
static void _ZFP_ZFClass_classTagClear(void)
{
    ZFCoreArrayPOD<const ZFClass *> allClass;
    _ZFP_ZFClassMap.allValueT(allClass);
    for(zfindex i = 0; i < allClass.count(); ++i)
    {
        allClass.get(i)->classTagRemoveAll();
    }
}
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFClassTagClearLevelEssential, ZFLevelZFFrameworkEssential)
{
}
ZF_GLOBAL_INITIALIZER_DESTROY(ZFClassTagClearLevelEssential)
{
    _ZFP_ZFClass_classTagClear();
}
ZF_GLOBAL_INITIALIZER_END(ZFClassTagClearLevelEssential)
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFClassTagClearLevelHigh, ZFLevelZFFrameworkHigh)
{
}
ZF_GLOBAL_INITIALIZER_DESTROY(ZFClassTagClearLevelHigh)
{
    _ZFP_ZFClass_classTagClear();
}
ZF_GLOBAL_INITIALIZER_END(ZFClassTagClearLevelHigh)

// ============================================================
// static methods
const ZFClass *ZFClass::classForName(ZF_IN const zfchar *className)
{
    zfCoreMutexLocker();
    return _ZFP_ZFClassMap.get<const ZFClass *>(className);
}
zfautoObject ZFClass::newInstanceForName(ZF_IN const zfchar *className,
                                         ZF_IN const ZFCallerInfo &callerInfo)
{
    const ZFClass *cls = ZFClass::classForName(className);
    return ((cls != zfnull) ? cls->newInstance(callerInfo) : zfautoObjectNull);
}
zfautoObject ZFClass::newInstanceForNameWithoutLeakTest(ZF_IN const zfchar *className)
{
    const ZFClass *cls = ZFClass::classForName(className);
    return ((cls != zfnull) ? cls->newInstanceWithoutLeakTest() : zfautoObjectNull);
}
void ZFClass::allClass(ZF_OUT ZFCoreArray<const ZFClass *> &ret)
{
    zfCoreMutexLocker();
    _ZFP_ZFClassMap.allValueT(ret);
}

// ============================================================
// instance observer
void ZFClass::instanceObserverAdd(ZF_IN const ZFListener &observer,
                                  ZF_IN_OPT ZFObject *userData /* = zfnull */,
                                  ZF_IN_OPT ZFObject *owner /* = zfnull */,
                                  ZF_IN_OPT ZFLevel observerLevel /* = ZFLevelAppNormal */,
                                  ZF_IN_OPT zfbool observeAllChildType /* = zftrue */) const
{
    if(this->classIsInternal())
    {
        return ;
    }

    _ZFP_ZFClassPrivate::InstanceObserverData *data = zfnew(_ZFP_ZFClassPrivate::InstanceObserverData);
    data->observer = observer;
    data->userData = zfautoObjectCreateMarkCached(userData);
    data->owner = owner;
    data->observerLevel = observerLevel;
    d->instanceObserver.push_back(ZFCorePointerForObject<_ZFP_ZFClassPrivate::InstanceObserverData *>(data));
    d->instanceObserverDoAdd(data, observeAllChildType);
}
void ZFClass::instanceObserverRemove(ZF_IN const ZFListener &observer) const
{
    zfCoreMutexLocker();
    for(zfstlsize i = 0; i < d->instanceObserver.size(); ++i)
    {
        _ZFP_ZFClassPrivate::InstanceObserverData *data = d->instanceObserver[i];
        if(data->observer == observer)
        {
            d->instanceObserverDoRemove(data);
            d->instanceObserver.erase(d->instanceObserver.begin() + i);
            break;
        }
    }
}
void ZFClass::instanceObserverRemoveByOwner(ZF_IN ZFObject *owner) const
{
    zfCoreMutexLocker();
    for(zfstlsize i = 0; i < d->instanceObserver.size(); ++i)
    {
        _ZFP_ZFClassPrivate::InstanceObserverData *data = d->instanceObserver[i];
        if(data->owner == owner)
        {
            d->instanceObserverDoRemove(data);
            d->instanceObserver.erase(d->instanceObserver.begin() + i);
            --i;
        }
    }
}
void ZFClass::instanceObserverRemoveAll(void) const
{
    zfCoreMutexLocker();
    while(!d->instanceObserver.empty())
    {
        _ZFP_ZFClassPrivate::InstanceObserverData *data = d->instanceObserver[0];
        d->instanceObserverDoRemove(data);
        d->instanceObserver.erase(d->instanceObserver.begin());
    }
}
void ZFClass::_ZFP_ZFClass_instanceObserverNotify(ZF_IN ZFObject *obj) const
{
    if(!d->instanceObserverCached.empty())
    {
        ZFListenerData listenerData(zfidentityInvalid, obj);
        for(zfstlsize i = 0; i < d->instanceObserverCached.size(); ++i)
        {
            _ZFP_ZFClassPrivate::InstanceObserverData &data = *(d->instanceObserverCached[i]);
            data.observer.execute(listenerData, data.userData.toObject());
        }
    }
}

// ============================================================
// class data change observer
void ZFClass::_ZFP_ZFClass_classDataChangeNotify(void) const
{
    if(!d->classDataChangeAutoRemoveTagList.empty())
    {
        zfstlmap<zfstlstringZ, zfbool> t = d->classDataChangeAutoRemoveTagList;
        for(zfstlmap<zfstlstringZ, zfbool>::iterator it = t.begin(); it != t.end(); ++it)
        {
            this->classTagRemove(it->first.c_str());
        }
    }
}
void ZFClass::classDataChangeAutoRemoveTagAdd(ZF_IN const zfchar *tag) const
{
    zfCoreAssert(tag != zfnull);
    d->classDataChangeAutoRemoveTagList[tag] = zftrue;
}
void ZFClass::classDataChangeAutoRemoveTagRemove(ZF_IN const zfchar *tag) const
{
    zfCoreAssert(tag != zfnull);
    d->classDataChangeAutoRemoveTagList.erase(tag);
}

// ============================================================
// class info
static void _ZFP_ZFClassGetInfo(ZF_IN_OUT zfstring &s,
                                ZF_IN const ZFClass *cls)
{
    if(cls->classIsAbstract() && !cls->classIsInterface())
    {
        s += zfText("(abstract)");
    }
    s += cls->className();
}
void ZFClass::objectInfoT(ZF_IN_OUT zfstring &ret) const
{
    _ZFP_ZFClassGetInfo(ret, this);
    if(this->implementedInterfaceCount() > 0)
    {
        ret += '<';
        for(zfindex i = 0; i < this->implementedInterfaceCount(); ++i)
        {
            if(i != 0)
            {
                ret += zfText(", ");
            }
            ret += this->implementedInterfaceAtIndex(i)->className();
        }
        ret += '>';
    }
}
void ZFClass::objectInfoOfInheritTreeT(ZF_IN_OUT zfstring &ret) const
{
    const ZFClass *cls = this;
    while(cls != zfnull)
    {
        if(cls != this)
        {
            ret += zfText(" : ");
        }

        _ZFP_ZFClassGetInfo(ret, cls);

        if(cls->implementedInterfaceCount() > 0)
        {
            ret += '<';
            for(zfindex i = 0; i < cls->implementedInterfaceCount(); ++i)
            {
                if(i != 0)
                {
                    ret += zfText(", ");
                }
                cls->implementedInterfaceAtIndex(i)->objectInfoOfInheritTreeT(ret);
            }
            ret += '>';
        }

        cls = cls->parentClass();
    }
}

zfbool ZFClass::classIsSubclassOf(ZF_IN const ZFClass *cls) const
{
    const ZFClass **p = d->parentListCache;
    do
    {
        if(*p == cls)
        {
            return zftrue;
        }
        ++p;
    } while(*p);
    return zffalse;
}
zfbool ZFClass::classIsTypeOf(ZF_IN const ZFClass *cls) const
{
    const ZFClass **p = (cls->d->isInterface ? d->parentInterfaceListCache : d->parentListCache);
    do
    {
        if(*p == cls)
        {
            return zftrue;
        }
        ++p;
    } while(*p);
    return zffalse;
}

zfbool ZFClass::classIsAbstract(void) const
{
    return (d->constructor == zfnull);
}

zfbool ZFClass::classIsInterface(void) const
{
    return d->isInterface;
}

zfbool ZFClass::classIsPrivate(void) const
{
    return d->isPrivateClass;
}
zfbool ZFClass::classIsInternal(void) const
{
    return d->isInternalClass;
}

zfautoObject ZFClass::newInstance(ZF_IN const ZFCallerInfo &callerInfo) const
{
    if(callerInfo.callerFile() != zfnull)
    {
        zfCoreMutexLocker();
        ZFObject *obj = zfnull;
        if(d->constructor != zfnull)
        {
            obj = d->constructor();
        }
        if(obj != zfnull)
        {
            ZFObject::_ZFP_ZFObjectAlloc(obj);
            obj->objectOnInit();
            obj->_ZFP_ZFObjectCheckOnInit();
            zflockfree_ZFLeakTestLogAfterAllocVerbose(obj, callerInfo);
        }
        zfautoObject ret = zflockfree_zfautoObjectCreateVerbose(obj, callerInfo);
        zflockfree_ZFLeakTestLogBeforeReleaseVerbose(obj, callerInfo);
        zflockfree_zfReleaseWithoutLeakTest(obj);
        return ret;
    }
    else
    {
        return this->newInstanceWithoutLeakTest();
    }
}
zfautoObject ZFClass::newInstanceWithoutLeakTest(void) const
{
    zfCoreMutexLocker();
    ZFObject *obj = zfnull;
    if(d->constructor != zfnull)
    {
        obj = d->constructor();
    }
    if(obj != zfnull)
    {
        ZFObject::_ZFP_ZFObjectAlloc(obj);
        obj->objectOnInit();
        obj->_ZFP_ZFObjectCheckOnInit();
    }
    zflockfree_zfblockedReleaseWithoutLeakTest(obj);
    return zflockfree_zfautoObjectCreateWithoutLeakTest(obj);
}

zfindex ZFClass::implementedInterfaceCount(void) const
{
    return d->implementedInterface.count();
}
const ZFClass *ZFClass::implementedInterfaceAtIndex(ZF_IN zfindex index) const
{
    return d->implementedInterface.get(index);
}

// ============================================================
// ZFMethod
zfindex ZFClass::methodCount(void) const
{
    this->_ZFP_ZFClass_methodAndPropertyAutoRegister();
    return d->methodList.count();
}
const ZFMethod *ZFClass::methodAtIndex(ZF_IN zfindex index) const
{
    this->_ZFP_ZFClass_methodAndPropertyAutoRegister();
    if(index >= d->methodList.count())
    {
        zfCoreCriticalIndexOutOfRange(index, this->methodCount());
        return zfnull;
    }
    return d->methodList[index];
}
/* ZFMETHOD_MAX_PARAM */
const ZFMethod *ZFClass::methodForNameIgnoreParent(ZF_IN const zfchar *methodName
                                                   , ZF_IN const zfchar *methodParamTypeId0
                                                   , ZF_IN_OPT const zfchar *methodParamTypeId1 /* = zfnull */
                                                   , ZF_IN_OPT const zfchar *methodParamTypeId2 /* = zfnull */
                                                   , ZF_IN_OPT const zfchar *methodParamTypeId3 /* = zfnull */
                                                   , ZF_IN_OPT const zfchar *methodParamTypeId4 /* = zfnull */
                                                   , ZF_IN_OPT const zfchar *methodParamTypeId5 /* = zfnull */
                                                   , ZF_IN_OPT const zfchar *methodParamTypeId6 /* = zfnull */
                                                   , ZF_IN_OPT const zfchar *methodParamTypeId7 /* = zfnull */
                                                   ) const
{
    this->_ZFP_ZFClass_methodAndPropertyAutoRegister();

    if(!d->methodMap.empty())
    {
        zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> >::iterator itName = d->methodMap.find(methodName);
        if(itName != d->methodMap.end())
        {
            zfstlvector<const ZFMethod *> &l = itName->second;
            for(zfstlsize i = 0; i < l.size(); ++i)
            {
                const ZFMethod *m = l[i];

                #define _ZFP_ZFClass_paramLoop(N) \
                    if(zfscmpTheSame(methodParamTypeId##N, (const zfchar *)zfnull)) {return m;} \
                    if(m->methodParamCount() <= N || !zfscmpTheSame(m->methodParamTypeIdAtIndex(N), methodParamTypeId##N)) {continue;}
                _ZFP_ZFClass_paramLoop(0)
                _ZFP_ZFClass_paramLoop(1)
                _ZFP_ZFClass_paramLoop(2)
                _ZFP_ZFClass_paramLoop(3)
                _ZFP_ZFClass_paramLoop(4)
                _ZFP_ZFClass_paramLoop(5)
                _ZFP_ZFClass_paramLoop(6)
                _ZFP_ZFClass_paramLoop(7)
                #undef _ZFP_ZFClass_paramLoop
                return m;
            }
        }
    }
    return zfnull;
}
const ZFMethod *ZFClass::methodForNameIgnoreParent(ZF_IN const zfchar *methodName) const
{
    this->_ZFP_ZFClass_methodAndPropertyAutoRegister();

    if(!d->methodMap.empty())
    {
        zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> >::iterator itName = d->methodMap.find(methodName);
        if(itName != d->methodMap.end())
        {
            return itName->second[0];
        }
    }
    return zfnull;
}
const ZFMethod *ZFClass::methodForName(ZF_IN const zfchar *methodName
                                       , ZF_IN const zfchar *methodParamTypeId0
                                       , ZF_IN_OPT const zfchar *methodParamTypeId1 /* = zfnull */
                                       , ZF_IN_OPT const zfchar *methodParamTypeId2 /* = zfnull */
                                       , ZF_IN_OPT const zfchar *methodParamTypeId3 /* = zfnull */
                                       , ZF_IN_OPT const zfchar *methodParamTypeId4 /* = zfnull */
                                       , ZF_IN_OPT const zfchar *methodParamTypeId5 /* = zfnull */
                                       , ZF_IN_OPT const zfchar *methodParamTypeId6 /* = zfnull */
                                       , ZF_IN_OPT const zfchar *methodParamTypeId7 /* = zfnull */
                                       ) const
{
    this->_ZFP_ZFClass_methodAndPropertyAutoRegister();
    for(zfstlsize i = 0; i < d->methodAndPropertyFindCache.size(); ++i)
    {
        const ZFMethod *ret = d->methodAndPropertyFindCache[i]->methodForNameIgnoreParent(methodName
                , methodParamTypeId0
                , methodParamTypeId1
                , methodParamTypeId2
                , methodParamTypeId3
                , methodParamTypeId4
                , methodParamTypeId5
                , methodParamTypeId6
                , methodParamTypeId7
            );
        if(ret != zfnull)
        {
            return ret;
        }
    }
    return zfnull;
}
const ZFMethod *ZFClass::methodForName(ZF_IN const zfchar *methodName) const
{
    this->_ZFP_ZFClass_methodAndPropertyAutoRegister();
    for(zfstlsize i = 0; i < d->methodAndPropertyFindCache.size(); ++i)
    {
        const ZFMethod *ret = d->methodAndPropertyFindCache[i]->methodForNameIgnoreParent(methodName);
        if(ret != zfnull)
        {
            return ret;
        }
    }
    return zfnull;
}
void ZFClass::methodForNameGetAllT(ZF_IN_OUT ZFCoreArray<const ZFMethod *> &ret,
                                   ZF_IN const zfchar *methodName) const
{
    if(methodName == zfnull)
    {
        return ;
    }

    this->_ZFP_ZFClass_methodAndPropertyAutoRegister();
    for(zfstlsize i = 0; i < d->methodAndPropertyFindCache.size(); ++i)
    {
        zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> > &methodMap
            = d->methodAndPropertyFindCache[i]->d->methodMap;
        zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> >::iterator itName = methodMap.find(methodName);
        if(itName != methodMap.end())
        {
            zfstlvector<const ZFMethod *> &l = itName->second;
            for(zfstlsize i = 0; i < l.size(); ++i)
            {
                ret.add(l[i]);
            }
        }
    }
}

// ============================================================
// ZFProperty
zfindex ZFClass::propertyCount(void) const
{
    this->_ZFP_ZFClass_methodAndPropertyAutoRegister();
    return d->propertyList.count();
}
const ZFProperty *ZFClass::propertyAtIndex(ZF_IN zfindex index) const
{
    this->_ZFP_ZFClass_methodAndPropertyAutoRegister();
    if(index >= d->propertyList.count())
    {
        zfCoreCriticalIndexOutOfRange(index, this->propertyCount());
        return zfnull;
    }
    return d->propertyList.get(index);
}
const ZFProperty *ZFClass::propertyForNameIgnoreParent(const zfchar *propertyName) const
{
    this->_ZFP_ZFClass_methodAndPropertyAutoRegister();
    if(!d->propertyMap.isEmpty())
    {
        const ZFProperty *t = d->propertyMap.get<const ZFProperty *>(propertyName);
        return t;
    }
    return zfnull;
}
const ZFProperty *ZFClass::propertyForName(const zfchar *propertyName) const
{
    this->_ZFP_ZFClass_methodAndPropertyAutoRegister();
    const ZFProperty *ret = zfnull;
    for(zfstlsize i = 0; i < d->methodAndPropertyFindCache.size() && ret == zfnull; ++i)
    {
        ret = d->methodAndPropertyFindCache[i]->propertyForNameIgnoreParent(propertyName);
    }
    return ret;
}
zfbool ZFClass::propertyHasOverrideInitStep(void) const
{
    return !(d->propertyInitStepMap.empty());
}
zfbool ZFClass::propertyHasOverrideInitStep(ZF_IN const ZFProperty *property) const
{
    return (d->propertyInitStepMap.find(property) != d->propertyInitStepMap.end());
}

// ============================================================
// class instance methods
void ZFClass::classTagSet(ZF_IN const zfchar *key,
                          ZF_IN ZFObject *tag,
                          ZF_IN_OPT zfbool autoMarkCached /* = zffalse */) const
{
    if(key == zfnull)
    {
        return ;
    }
    if(tag != zfnull && ZFFrameworkStateCheck(ZFLevelZFFrameworkEssential) != ZFFrameworkStateAvailable)
    {
        // must not store any new tags during cleanup
        abort();
    }
    zfCoreMutexLocker();
    _ZFP_ZFClassTagMapType &m = d->classTagMap;
    _ZFP_ZFClassTagMapType::iterator it = m.find(key);
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
                m[key] = zflockfree_zfautoObjectCreateWithoutLeakTest(tag);
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
                it->second = zflockfree_zfautoObjectCreateMarkCached(tag);
            }
            else
            {
                it->second = zflockfree_zfautoObjectCreateWithoutLeakTest(tag);
            }
        }
    }
}
ZFObject *ZFClass::classTagGet(ZF_IN const zfchar *key) const
{
    if(key != zfnull)
    {
        zfCoreMutexLocker();
        _ZFP_ZFClassTagMapType::iterator it = d->classTagMap.find(key);
        if(it != d->classTagMap.end())
        {
            return it->second.toObject();
        }
    }
    return zfnull;
}
void ZFClass::classTagGetAllKeyValue(ZF_IN_OUT ZFCoreArray<const zfchar *> &allKey,
                                     ZF_IN_OUT ZFCoreArray<ZFObject *> &allValue) const
{
    _ZFP_ZFClassTagMapType &m = d->classTagMap;
    allKey.capacitySet(allKey.count() + m.size());
    allValue.capacitySet(allValue.count() + m.size());
    for(_ZFP_ZFClassTagMapType::iterator it = m.begin(); it != m.end(); ++it)
    {
        allKey.add(it->first.c_str());
        allValue.add(it->second.toObject());
    }
}
zfautoObject ZFClass::classTagRemoveAndGet(ZF_IN const zfchar *key) const
{
    if(key != zfnull)
    {
        _ZFP_ZFClassTagMapType &m = d->classTagMap;
        _ZFP_ZFClassTagMapType::iterator it = m.find(key);
        if(it != m.end())
        {
            zfautoObject ret = zfautoObjectCreate(it->second.toObject());
            m.erase(it);
            return ret;
        }
    }
    return zfautoObjectNull;
}
void ZFClass::classTagRemoveAll(void) const
{
    if(!d->classTagMap.empty())
    {
        _ZFP_ZFClassTagMapType tmp;
        tmp.swap(d->classTagMap);
    }
}

// ============================================================
// private
/** @cond ZFPrivateDoc */
ZFClass::ZFClass(void)
: d(zfnull)
{
    d = zfnew(_ZFP_ZFClassPrivate);
    d->pimplOwner = this;
    this->_ZFP_ZFClassNeedInitImplementationList = zftrue;
}
ZFClass::~ZFClass(void)
{
    if(!d->classTagMap.empty())
    {
        // class tags must be removed before destroying a ZFClass
        abort();
    }

    for(zfstlmap<const ZFClass *, zfbool>::iterator it = d->allChildren.begin(); it != d->allChildren.end(); ++it)
    {
        it->first->d->allParent.erase(this);
    }
    for(zfstlmap<const ZFClass *, zfbool>::iterator it = d->allParent.begin(); it != d->allParent.end(); ++it)
    {
        it->first->d->allChildren.erase(this);
    }

    zfdelete(d);
    d = zfnull;
}
ZFClass *ZFClass::_ZFP_ZFClassRegister(ZF_IN zfbool *ZFCoreLibDestroyFlag,
                                       ZF_IN const zfchar *name,
                                       ZF_IN const ZFClass *parent,
                                       ZF_IN _ZFP_ZFObjectConstructor constructor,
                                       ZF_IN _ZFP_ZFObjectDestructor destructor,
                                       ZF_IN_OPT zfbool isInterface /* = zffalse */)
{
    zfCoreMutexLocker();
    ZFCorePointerBase *d = _ZFP_ZFClassMap.get(name);
    ZFClass *cls = zfnull;
    if(d == zfnull)
    {
        cls = zfnew(ZFClass);
        _ZFP_ZFClassMap.set(name, ZFCorePointerForPointerRef<ZFClass *>(cls));
    }
    else
    {
        cls = d->pointerValueT<ZFClass *>();
        if(cls->d->isInterface != isInterface || cls->d->classParent != parent)
        {
            zfCoreCriticalMessageTrim(zfTextA("[ZFClass] register a class that already registered: %s"), zfsCoreZ2A(name));
            return zfnull;
        }
        ++(cls->d->refCount);
        return cls;
    }

    cls->d->ZFCoreLibDestroyFlag.add(ZFCoreLibDestroyFlag);

    cls->d->constructor = constructor;
    cls->d->destructor = destructor;

    cls->d->className = name;
    cls->classNameCache = cls->d->className.cString();

    cls->d->classParent = parent;
    cls->classParentCache = parent;

    cls->d->isInterface = isInterface;

    {
        const zfchar *filter = zfText("_ZFP_");
        const zfindex filterLen = zfslen(filter);
        cls->d->isPrivateClass = (zfsncmp(name, filter, filterLen) == 0);
    }
    {
        const zfchar *filter = zfText("_ZFP_I_");
        const zfindex filterLen = zfslen(filter);
        cls->d->isInternalClass = (zfsncmp(name, filter, filterLen) == 0);
    }

    return cls;
}
void ZFClass::_ZFP_ZFClassUnregister(ZF_IN zfbool *ZFCoreLibDestroyFlag, ZF_IN const zfchar *name)
{
    zfCoreMutexLocker();

    zfiterator it = _ZFP_ZFClassMap.iteratorForKey(name);
    if(!_ZFP_ZFClassMap.iteratorIsValid(it))
    {
        zfCoreCriticalShouldNotGoHere();
        return ;
    }
    ZFClass *cls = _ZFP_ZFClassMap.iteratorGetValue<ZFClass *>(it);

    _ZFP_ZFClassDataChangeNotify(ZFClassDataChangeTypeDetach, cls, zfnull, zfnull);

    cls->d->ZFCoreLibDestroyFlag.removeElement(ZFCoreLibDestroyFlag);
    --(cls->d->refCount);
    if(cls->d->refCount == 0)
    {
        _ZFP_ZFClassMap.iteratorRemove(it);
        _ZFP_ZFClassDelayDeleteMap.set(name, ZFCorePointerForPointerRef<ZFClass *>(cls));
    }
}

zfbool ZFClass::_ZFP_ZFClass_interfaceNeedRegister(void)
{
    return d->needRegisterImplementedInterface;
}
void ZFClass::_ZFP_ZFClass_interfaceRegister(ZF_IN const ZFClass *cls,
                                             ...)
{
    va_list vaList;
    va_start(vaList, cls);
    const ZFClass *tmp = cls;
    while(tmp != zfnull)
    {
        d->implementedInterface.add(tmp);
        tmp = va_arg(vaList, const ZFClass *);
    }
    va_end(vaList);
}
void ZFClass::_ZFP_ZFClass_interfaceRegisterCastCallback(ZF_IN _ZFP_ZFObjectToInterfaceCastCallback callback,
                                                         ...)
{
    va_list vaList;
    va_start(vaList, callback);
    _ZFP_ZFObjectToInterfaceCastCallback callbackTmp = callback;
    ZFCoreArrayPOD<_ZFP_ZFObjectToInterfaceCastCallback> parentInterfaceCastList;
    while(callbackTmp != zfnull)
    {
        parentInterfaceCastList.add(callbackTmp);
        callbackTmp = va_arg(vaList, _ZFP_ZFObjectToInterfaceCastCallback);
    }
    va_end(vaList);

    // remove ZFInterface
    for(zfindex i = 0; i < d->implementedInterface.count(); ++i)
    {
        if(d->implementedInterface[i] == ZFInterface::ClassData())
        {
            d->implementedInterface.remove(i);
            parentInterfaceCastList.remove(i);
            --i;
        }
    }

    d->interfaceCastListCache = (const ZFClass **)zfrealloc(d->interfaceCastListCache, sizeof(const ZFClass *) * (d->implementedInterface.count() + 1));
    zfmemcpy(d->interfaceCastListCache, d->implementedInterface.arrayBuf(), sizeof(const ZFClass *) * d->implementedInterface.count());
    d->interfaceCastListCache[d->implementedInterface.count()] = zfnull;

    d->interfaceCastCallbackListCache = (_ZFP_ZFObjectToInterfaceCastCallback *)zfrealloc(
        d->interfaceCastCallbackListCache, sizeof(_ZFP_ZFObjectToInterfaceCastCallback) * (parentInterfaceCastList.count() + 1));
    zfmemcpy(d->interfaceCastCallbackListCache, parentInterfaceCastList.arrayBuf(), sizeof(_ZFP_ZFObjectToInterfaceCastCallback) * parentInterfaceCastList.count());
    d->interfaceCastCallbackListCache[parentInterfaceCastList.count()] = zfnull;
}
ZFInterface *ZFClass::_ZFP_ZFClass_interfaceCast(ZF_IN ZFObject * const &obj,
                                                 ZF_IN const ZFClass *interfaceClass) const
{
    if(obj)
    {
        const ZFClass **parentInterfaceListTmp = d->interfaceCastListCache;
        _ZFP_ZFObjectToInterfaceCastCallback *parentInterfaceCastListTmp = d->interfaceCastCallbackListCache;
        do
        {
            if(*parentInterfaceListTmp == interfaceClass)
            {
                return (*parentInterfaceCastListTmp)(obj);
            }
            ++parentInterfaceListTmp;
            ++parentInterfaceCastListTmp;
        } while(*parentInterfaceListTmp);
    }
    return zfnull;
}

ZFClass *ZFClass::_ZFP_ZFClassInitFinish(ZF_IN ZFClass *cls)
{
    zfCoreMutexLocker();
    if(cls->d->needFinalInit)
    {
        cls->d->needFinalInit = zffalse;

        ZFClass::_ZFP_ZFClassInitFinish_parentListCache(cls);
        ZFClass::_ZFP_ZFClassInitFinish_parentInterfaceListCache(cls);
        ZFClass::_ZFP_ZFClassInitFinish_interfaceCastListCache(cls);
        ZFClass::_ZFP_ZFClassInitFinish_allParentAndChildrenCache(cls);
        ZFClass::_ZFP_ZFClassInitFinish_methodAndPropertyFindCache(cls);
        ZFClass::_ZFP_ZFClassInitFinish_propertyMetaDataCache(cls);
        ZFClass::_ZFP_ZFClassInitFinish_instanceObserverCache(cls);

        _ZFP_ZFClassDataChangeNotify(ZFClassDataChangeTypeAttach, cls, zfnull, zfnull);
    }
    return cls;
}
void ZFClass::_ZFP_ZFClassInitFinish_parentListCache(ZF_IN ZFClass *cls)
{ // init parent list for better search performance
    ZFCoreArrayPOD<const ZFClass *> parentList;
    {
        parentList.add(cls);
        const ZFClass *parentTmp = cls->parentClass();
        while(parentTmp != zfnull)
        {
            parentList.add(parentTmp);
            parentTmp = parentTmp->parentClass();
        }
    }
    cls->d->parentListCache = (const ZFClass **)zfmalloc(sizeof(const ZFClass *) * (parentList.count() + 1));
    zfmemcpy(cls->d->parentListCache, parentList.arrayBuf(), sizeof(const ZFClass *) * parentList.count());
    cls->d->parentListCache[parentList.count()] = zfnull;
}
void ZFClass::_ZFP_ZFClassInitFinish_parentInterfaceListCache(ZF_IN ZFClass *cls)
{ // init parent type list for better search performance
    ZFCoreArrayPOD<const ZFClass *> parentList;
    {
        ZFCoreArrayPOD<const ZFClass *> clsToCheck;
        clsToCheck.add(cls);
        do
        {
            const ZFClass *clsTmp = clsToCheck.getFirst();
            clsToCheck.removeFirst();
            if(parentList.find(clsTmp) == zfindexMax)
            {
                parentList.add(clsTmp);

                if(clsTmp->parentClass() != zfnull)
                {
                    clsToCheck.add(clsTmp->parentClass());
                }
                clsToCheck.addFrom(clsTmp->d->implementedInterface);
            }
        } while(!clsToCheck.isEmpty());
        for(zfindex i = 0; i < parentList.count(); ++i)
        {
            if(!parentList[i]->classIsInterface())
            {
                parentList.remove(i);
                --i;
            }
        }
    }
    cls->d->parentInterfaceListCache = (const ZFClass **)zfmalloc(sizeof(const ZFClass *) * (parentList.count() + 1));
    zfmemcpy(cls->d->parentInterfaceListCache, parentList.arrayBuf(), sizeof(const ZFClass *) * parentList.count());
    cls->d->parentInterfaceListCache[parentList.count()] = zfnull;
}
void ZFClass::_ZFP_ZFClassInitFinish_interfaceCastListCache(ZF_IN ZFClass *cls)
{ // copy parent's interface cast datas
    ZFCoreArrayPOD<const ZFClass *> parentInterfaceList;
    if(cls->parentClass() != zfnull)
    {
        for(const ZFClass **p = cls->parentClass()->d->interfaceCastListCache; *p != zfnull; ++p)
        {
            if(parentInterfaceList.find(*p, ZFComparerCheckEqual) == zfindexMax)
            {
                parentInterfaceList.add(*p);
            }
        }
    }
    if(cls->d->interfaceCastListCache != zfnull)
    {
        for(const ZFClass **p = cls->d->interfaceCastListCache; *p != zfnull; ++p)
        {
            if(parentInterfaceList.find(*p, ZFComparerCheckEqual) == zfindexMax)
            {
                parentInterfaceList.add(*p);
            }
        }
    }
    cls->d->interfaceCastListCache = (const ZFClass **)zfrealloc(cls->d->interfaceCastListCache, sizeof(const ZFClass *) * (parentInterfaceList.count() + 1));
    zfmemcpy(cls->d->interfaceCastListCache, parentInterfaceList.arrayBuf(), sizeof(const ZFClass *) * parentInterfaceList.count());
    cls->d->interfaceCastListCache[parentInterfaceList.count()] = zfnull;

    ZFCoreArrayPOD<_ZFP_ZFObjectToInterfaceCastCallback> parentInterfaceCastList;
    if(cls->parentClass() != zfnull)
    {
        for(_ZFP_ZFObjectToInterfaceCastCallback *p = cls->parentClass()->d->interfaceCastCallbackListCache; *p != zfnull; ++p)
        {
            if(parentInterfaceCastList.find(*p, ZFComparerCheckEqual) == zfindexMax)
            {
                parentInterfaceCastList.add(*p);
            }
        }
    }
    if(cls->d->interfaceCastCallbackListCache != zfnull)
    {
        for(_ZFP_ZFObjectToInterfaceCastCallback *p = cls->d->interfaceCastCallbackListCache; *p != zfnull; ++p)
        {
            if(parentInterfaceCastList.find(*p, ZFComparerCheckEqual) == zfindexMax)
            {
                parentInterfaceCastList.add(*p);
            }
        }
    }
    cls->d->interfaceCastCallbackListCache = (_ZFP_ZFObjectToInterfaceCastCallback *)zfrealloc(
        cls->d->interfaceCastCallbackListCache, sizeof(_ZFP_ZFObjectToInterfaceCastCallback) * (parentInterfaceCastList.count() + 1));
    zfmemcpy(cls->d->interfaceCastCallbackListCache, parentInterfaceCastList.arrayBuf(), sizeof(_ZFP_ZFObjectToInterfaceCastCallback) * parentInterfaceCastList.count());
    cls->d->interfaceCastCallbackListCache[parentInterfaceCastList.count()] = zfnull;
}
void ZFClass::_ZFP_ZFClassInitFinish_allParentAndChildrenCache(ZF_IN ZFClass *cls)
{ // all parent and children
    ZFCoreArrayPOD<const ZFClass *> clsToCheck;
    clsToCheck.add(cls);
    do
    {
        const ZFClass *clsTmp = clsToCheck.getFirst();
        clsToCheck.removeFirst();
        if(cls->d->allParent.find(clsTmp) == cls->d->allParent.end())
        {
            cls->d->allParent[clsTmp] = zftrue;
            clsTmp->d->allChildren[cls] = zftrue;

            if(clsTmp->parentClass() != zfnull)
            {
                clsToCheck.add(clsTmp->parentClass());
            }
            clsToCheck.addFrom(clsTmp->d->implementedInterface);
        }
    } while(!clsToCheck.isEmpty());
}
void ZFClass::_ZFP_ZFClassInitFinish_methodAndPropertyFindCache(ZF_IN ZFClass *cls)
{ // all class to find property and method
    zfstldeque<const ZFClass *> clsToCheck;
    zfstlmap<const ZFClass *, zfbool> alreadyChecked;
    clsToCheck.push_back(cls);
    do
    {
        const ZFClass *clsTmp = clsToCheck.front();
        clsToCheck.pop_front();
        if(alreadyChecked.find(clsTmp) != alreadyChecked.end())
        {
            continue;
        }
        cls->d->methodAndPropertyFindCache.push_back(clsTmp);
        alreadyChecked[clsTmp] = zftrue;

        for(zfindex i = clsTmp->implementedInterfaceCount() - 1; i != zfindexMax; --i)
        {
            clsToCheck.push_back(clsTmp->implementedInterfaceAtIndex(i));
        }
        if(clsTmp->parentClass())
        {
            clsToCheck.push_back(clsTmp->parentClass());
        }
    } while(!clsToCheck.empty());
}
void ZFClass::_ZFP_ZFClassInitFinish_propertyMetaDataCache(ZF_IN ZFClass *cls)
{ // property init step
    for(zfstlmap<const ZFClass *, zfbool>::iterator itParent = cls->d->allParent.begin();
        itParent != cls->d->allParent.end();
        ++itParent)
    {
        cls->d->propertyAutoInitMap.insert(itParent->first->d->propertyAutoInitMap.begin(), itParent->first->d->propertyAutoInitMap.end());

        for(_ZFP_ZFClassPropertyInitStepMapType::iterator itProperty = itParent->first->d->propertyInitStepMap.begin();
            itProperty != itParent->first->d->propertyInitStepMap.end();
            ++itProperty)
        {
            cls->d->propertyInitStepMap[itProperty->first].insert(itProperty->second.begin(), itProperty->second.end());
        }
    }
}
void ZFClass::_ZFP_ZFClassInitFinish_instanceObserverCache(ZF_IN ZFClass *cls)
{ // copy all parent's instance observer to self
    for(zfstlmap<const ZFClass *, zfbool>::iterator it = cls->d->allParent.begin(); it != cls->d->allParent.end(); ++it)
    {
        zfstldeque<ZFCorePointerForObject<_ZFP_ZFClassPrivate::InstanceObserverData *> > &parentInstanceObserver = it->first->d->instanceObserver;
        for(zfstlsize i = 0; i < parentInstanceObserver.size(); ++i)
        {
            cls->d->instanceObserverCached.push_back(parentInstanceObserver[i].pointerValueGet());
        }
    }
}

void ZFClass::_ZFP_ZFClass_objectDesctuct(ZF_IN ZFObject *obj) const
{
    d->destructor(obj);
}


void ZFClass::_ZFP_ZFClass_methodAndPropertyAutoRegister(void) const
{
    if(d->internalTypesNeedAutoRegister)
    {
        zfCoreMutexLocker();
        if(d->internalTypesNeedAutoRegister)
        {
            d->internalTypesNeedAutoRegister = zffalse;

            // create dummy instance to ensure static init of the object would take effect
            // including method and property register
            if(d->constructor != zfnull)
            {
                d->destructor(d->constructor());
            }
        }
    }
}

void ZFClass::_ZFP_ZFClass_methodRegister(ZF_IN const ZFMethod *method)
{
    zfstlvector<const ZFMethod *> &methodList = d->methodMap[method->methodName()];
    methodList.push_back(method);
    d->methodList.add(method);
}
void ZFClass::_ZFP_ZFClass_methodUnregister(ZF_IN const ZFMethod *method)
{
    zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> >::iterator itName = d->methodMap.find(method->methodName());
    if(itName != d->methodMap.end())
    {
        zfstlvector<const ZFMethod *> &l = itName->second;
        for(zfstlsize i = 0; i < l.size(); ++i)
        {
            if(method == l[i])
            {
                l.erase(l.begin() + i);
                if(l.empty())
                {
                    d->methodMap.erase(itName);
                }
                d->methodList.removeElement(method);
            }
        }
    }
}

zfbool ZFClass::_ZFP_ZFClass_propertyRegister(ZF_IN const ZFProperty *zfproperty)
{
    if(d->propertyMap.isContain(zfproperty->propertyName()))
    {
        return zffalse;
    }
    else
    {
        d->propertyMap.set(zfproperty->propertyName(), ZFCorePointerForPointerRef<const ZFProperty *>(zfproperty));
        d->propertyList.add(zfproperty);
        return zftrue;
    }
}
void ZFClass::_ZFP_ZFClass_propertyUnregister(ZF_IN const ZFProperty *zfproperty)
{
    d->propertyMap.remove(zfproperty->propertyName());
    d->propertyList.removeElement(zfproperty);
}

void ZFClass::_ZFP_ZFClass_propertyAutoInitRegister(ZF_IN const ZFProperty *property) const
{
    d->propertyAutoInitMap[property] = zftrue;

    for(zfstlmap<const ZFClass *, zfbool>::iterator it = d->allChildren.begin(); it != d->allChildren.end(); ++it)
    {
        it->first->d->propertyAutoInitMap[property] = zftrue;
    }
}
void ZFClass::_ZFP_ZFClass_propertyAutoInitAction(ZF_IN ZFObject *owner) const
{
    // access getter to ensure property value created
    for(zfstlmap<const ZFProperty *, zfbool>::iterator it = d->propertyAutoInitMap.begin(); it != d->propertyAutoInitMap.end(); ++it)
    {
        const ZFProperty *property = it->first;
        if(property->propertyIsRetainProperty())
        {
            property->callbackRetainGet(property, owner);
        }
        else
        {
            property->callbackAssignGet(property, owner);
        }
    }
}
void ZFClass::_ZFP_ZFClass_propertyInitStepRegister(ZF_IN const ZFProperty *property) const
{
    d->propertyInitStepMap[property][this] = zftrue;

    for(zfstlmap<const ZFClass *, zfbool>::iterator it = d->allChildren.begin(); it != d->allChildren.end(); ++it)
    {
        it->first->d->propertyInitStepMap[property][this] = zftrue;
    }
}
zfbool ZFClass::_ZFP_ZFClass_propertyInitStepIsTheSame(ZF_IN const ZFProperty *property,
                                                       ZF_IN const ZFClass *refClass) const
{
    if(this == refClass)
    {
        return zftrue;
    }
    _ZFP_ZFClassPropertyInitStepMapType::iterator data = d->propertyInitStepMap.find(property);
    _ZFP_ZFClassPropertyInitStepMapType::iterator dataRef = refClass->d->propertyInitStepMap.find(property);
    if(data == d->propertyInitStepMap.end())
    {
        return (dataRef == refClass->d->propertyInitStepMap.end());
    }
    if(dataRef == refClass->d->propertyInitStepMap.end())
    {
        return (data == d->propertyInitStepMap.end());
    }

    if(data->second.size() != dataRef->second.size())
    {
        return zffalse;
    }
    if(this->classIsTypeOf(refClass) || refClass->classIsTypeOf(this))
    {
        return zftrue;
    }

    for(zfstlmap<const ZFClass *, zfbool>::iterator it = data->second.begin(), itRef = dataRef->second.begin();
        it != data->second.end();
        ++it, ++itRef)
    {
        if(it->first != itRef->first)
        {
            return zffalse;
        }
    }
    return zftrue;
}
/** @endcond */

// ============================================================
ZFOBSERVER_EVENT_GLOBAL_REGISTER(ZFGlobalEvent, ClassDataChange)
ZFObserverHolder &_ZFP_ZFClassDataChangeObserverRef(void)
{
    static ZFObserverHolder d;
    return d;
}
void _ZFP_ZFClassDataChangeNotify(ZF_IN ZFClassDataChangeType changeType,
                                  ZF_IN const ZFClass *changedClass,
                                  ZF_IN const ZFProperty *changedProperty,
                                  ZF_IN const ZFMethod *changedMethod)
{
    zfCoreMutexLocker();
    if(ZFFrameworkStateCheck(ZFLevelZFFrameworkLow) == ZFFrameworkStateAvailable)
    {
        if(changedProperty != zfnull)
        {
            changedProperty->propertyOwnerClass()->_ZFP_ZFClass_classDataChangeNotify();
        }
        else if(changedMethod != zfnull)
        {
            changedMethod->methodOwnerClass()->_ZFP_ZFClass_classDataChangeNotify();
        }

        ZFClassDataChangeData data;
        data.changeType = changeType;
        data.changedClass = changedClass;
        data.changedProperty = changedProperty;
        data.changedMethod = changedMethod;

        ZFPointerHolder *holder = ZFPointerHolder::cacheAccess();
        holder->holdedData = &data;
        ZFClassDataChangeObserver.observerNotify(ZFGlobalEvent::EventClassDataChange(), holder);
        ZFPointerHolder::cacheRelease(holder);
    }
}

ZF_NAMESPACE_GLOBAL_END

#if 1 // ZFObject related method register
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_STATIC_1(ZFClass, v_ZFClass, const ZFClass *, classForName, ZFMP_IN(const zfchar *, className))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_STATIC_2(ZFClass, v_ZFClass, zfautoObject, newInstanceForName, ZFMP_IN(const zfchar *, className), ZFMP_IN_OPT(const ZFCallerInfo &, callerInfo, ZFCallerInfo()))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_STATIC_1(ZFClass, v_ZFClass, zfautoObject, newInstanceForNameWithoutLeakTest, ZFMP_IN(const zfchar *, className))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_STATIC_1(ZFClass, v_ZFClass, void, allClass, ZFMP_OUT(ZFCoreArray<const ZFClass *> &, ret))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_STATIC_0(ZFClass, v_ZFClass, ZFCoreArrayPOD<const ZFClass *>, allClass)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, void, classDataChangeAutoRemoveTagAdd, ZFMP_IN(const zfchar *, tag))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, void, classDataChangeAutoRemoveTagRemove, ZFMP_IN(const zfchar *, tag))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, void, objectInfoOfInheritTreeT, ZFMP_IN_OUT(zfstring &, ret))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFClass, zfstring, objectInfoOfInheritTree)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, zfbool, classIsSubclassOf, ZFMP_IN(const ZFClass *, cls))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, zfbool, classIsTypeOf, ZFMP_IN(const ZFClass *, cls))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFClass, const zfchar *, className)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFClass, const ZFClass *, parentClass)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFClass, zfbool, classIsAbstract)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFClass, zfbool, classIsInterface)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFClass, zfbool, classIsPrivate)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFClass, zfbool, classIsInternal)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, zfautoObject, newInstance, ZFMP_IN_OPT(const ZFCallerInfo &, callerInfo, ZFCallerInfo()))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFClass, zfautoObject, newInstanceWithoutLeakTest)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFClass, zfindex, implementedInterfaceCount)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, const ZFClass *, implementedInterfaceAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFClass, zfindex, methodCount)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, const ZFMethod *, methodAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_8(v_ZFClass, const ZFMethod *, methodForNameIgnoreParent, ZFMP_IN(const zfchar *, methodName)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId0, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId1, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId2, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId3, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId4, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId5, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId6, zfnull)
    // , ZFMP_IN_OPT(const zfchar *, methodParamTypeId7, zfnull)
    )
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_8(v_ZFClass, const ZFMethod *, methodForName, ZFMP_IN(const zfchar *, methodName)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId0, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId1, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId2, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId3, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId4, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId5, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId6, zfnull)
    // , ZFMP_IN_OPT(const zfchar *, methodParamTypeId7, zfnull)
    )
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFClass, void, methodForNameGetAllT, ZFMP_IN_OUT(ZFCoreArray<const ZFMethod *> &, ret), ZFMP_IN(const zfchar *, methodName))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, ZFCoreArrayPOD<const ZFMethod *>, methodForNameGetAll, ZFMP_IN(const zfchar *, methodName))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFClass, zfindex, propertyCount)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, const ZFProperty *, propertyAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, const ZFProperty *, propertyForNameIgnoreParent, ZFMP_IN(const zfchar *, propertyName))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, const ZFProperty *, propertyForName, ZFMP_IN(const zfchar *, propertyName))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFClass, zfbool, propertyHasOverrideInitStep)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, zfbool, propertyHasOverrideInitStep, ZFMP_IN(const ZFProperty *, property))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_3(v_ZFClass, void, classTagSet, ZFMP_IN(const zfchar *, key), ZFMP_IN(ZFObject *, tag), ZFMP_IN_OPT(zfbool, autoMarkCached, zffalse))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFClass, void, classTagSetMarkCached, ZFMP_IN(const zfchar *, key), ZFMP_IN(ZFObject *, tag))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, ZFObject *, classTagGet, ZFMP_IN(const zfchar *, key))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFClass, void, classTagGetAllKeyValue, ZFMP_IN_OUT(ZFCoreArray<const zfchar *> &, allKey), ZFMP_IN_OUT(ZFCoreArray<ZFObject *> &, allValue))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, void, classTagRemove, ZFMP_IN(const zfchar *, key))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFClass, zfautoObject, classTagRemoveAndGet, ZFMP_IN(const zfchar *, key))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFClass, void, classTagRemoveAll)

ZF_NAMESPACE_GLOBAL_END
#endif

