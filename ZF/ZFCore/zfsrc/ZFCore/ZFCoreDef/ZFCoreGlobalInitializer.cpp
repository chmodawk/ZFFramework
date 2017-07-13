/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFCoreGlobalInitializer.h"
#include "ZFCoreMutex.h"
#include "ZFCorePointer.h"
#include "ZFCoreArray.h"
#include "ZFCoreMap.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFCoreArrayPOD<ZFFrameworkStateChangeCallback> &_ZFP_ZFFrameworkInitFinishCallbacks(void)
{
    static ZFCoreArrayPOD<ZFFrameworkStateChangeCallback> d;
    return d;
}
ZFCoreArrayPOD<ZFFrameworkStateChangeCallback> &_ZFP_ZFFrameworkCleanupPrepareCallbacks(void)
{
    static ZFCoreArrayPOD<ZFFrameworkStateChangeCallback> d;
    return d;
}

zfclassNotPOD _ZFP_GI_Data
{
public:
    zfindex refCount;
    ZFCoreArrayPOD<zfbool *> ZFCoreLibDestroyFlag;
    ZFFrameworkState state;
    zfchar *name;
    ZFLevel level;
    _ZFP_GI_DummyBase *instance;
    _ZFP_GI_Constructor constructor;

public:
    _ZFP_GI_Data(void)
    : refCount(1)
    , ZFCoreLibDestroyFlag()
    , state(ZFFrameworkStateNotAvailable)
    , name(zfnull)
    , level(ZFLevelAppLow)
    , instance(zfnull)
    , constructor(zfnull)
    {
    }
    ~_ZFP_GI_Data(void)
    {
        for(zfindex i = 0; i < this->ZFCoreLibDestroyFlag.count(); ++i)
        {
            *(this->ZFCoreLibDestroyFlag[i]) = zftrue;
        }
        if(this->instance != zfnull)
        {
            zfdelete(this->instance);
            this->instance = zfnull;
        }
        zffree(this->name);
    }
};
#define _ZFP_GI_DataArrayType ZFCoreArrayPOD<_ZFP_GI_Data *>

static zfstring _ZFP_GI_keyForName(ZF_IN const zfchar *name,
                                   ZF_IN ZFLevel level)
{
    return zfstringWithFormat(zfText("%d_%s"), (zfint)level, name);
}

static void _ZFP_GI_instanceInit(_ZFP_GI_DataArrayType &list)
{
    if(!list.isEmpty())
    {
        // array may be changed during init step, copy it first
        _ZFP_GI_DataArrayType tmp;
        tmp.copyFrom(list);
        for(zfindex i = 0; i < tmp.count(); ++i)
        {
            _ZFP_GI_Data *data = tmp.get(i);
            if(data->instance == zfnull)
            {
                data->instance = data->constructor();
            }
        }
    }
}
static void _ZFP_GI_instanceDealloc(_ZFP_GI_DataArrayType &list)
{
    for(zfindex i = list.count() - 1; i != zfindexMax; --i)
    {
        _ZFP_GI_Data *data = list.get(i);
        if(data->instance != zfnull)
        {
            zfdelete(data->instance);
            data->instance = zfnull;
        }
    }
}

zfclassNotPOD _ZFP_GI_DataContainer
{
public:
    ZFFrameworkState state;

    ZFFrameworkState stateZFFrameworkStatic;
    _ZFP_GI_DataArrayType dataLevelZFFrameworkStatic;
    ZFCoreMap dataMapLevelZFFrameworkStatic; // _ZFP_GI_Data *

    ZFFrameworkState stateZFFrameworkEssential;
    _ZFP_GI_DataArrayType dataLevelZFFrameworkEssential;
    ZFCoreMap dataMapLevelZFFrameworkEssential; // _ZFP_GI_Data *

    ZFFrameworkState stateZFFrameworkHigh;
    _ZFP_GI_DataArrayType dataLevelZFFrameworkHigh;
    ZFCoreMap dataMapLevelZFFrameworkHigh; // _ZFP_GI_Data *

    ZFFrameworkState stateZFFrameworkNormal;
    _ZFP_GI_DataArrayType dataLevelZFFrameworkNormal;
    ZFCoreMap dataMapLevelZFFrameworkNormal; // _ZFP_GI_Data *

    ZFFrameworkState stateZFFrameworkLow;
    _ZFP_GI_DataArrayType dataLevelZFFrameworkLow;
    ZFCoreMap dataMapLevelZFFrameworkLow; // _ZFP_GI_Data *


    ZFFrameworkState stateAppEssential;
    _ZFP_GI_DataArrayType dataLevelAppEssential;
    ZFCoreMap dataMapLevelAppEssential; // _ZFP_GI_Data *

    ZFFrameworkState stateAppHigh;
    _ZFP_GI_DataArrayType dataLevelAppHigh;
    ZFCoreMap dataMapLevelAppHigh; // _ZFP_GI_Data *

    ZFFrameworkState stateAppNormal;
    _ZFP_GI_DataArrayType dataLevelAppNormal;
    ZFCoreMap dataMapLevelAppNormal; // _ZFP_GI_Data *

    ZFFrameworkState stateAppLow;
    _ZFP_GI_DataArrayType dataLevelAppLow;
    ZFCoreMap dataMapLevelAppLow; // _ZFP_GI_Data *


    ZFFrameworkState stateZFFrameworkPostLow;
    _ZFP_GI_DataArrayType dataLevelZFFrameworkPostLow;
    ZFCoreMap dataMapLevelZFFrameworkPostLow; // _ZFP_GI_Data *

    ZFFrameworkState stateZFFrameworkPostNormal;
    _ZFP_GI_DataArrayType dataLevelZFFrameworkPostNormal;
    ZFCoreMap dataMapLevelZFFrameworkPostNormal; // _ZFP_GI_Data *

    ZFFrameworkState stateZFFrameworkPostHigh;
    _ZFP_GI_DataArrayType dataLevelZFFrameworkPostHigh;
    ZFCoreMap dataMapLevelZFFrameworkPostHigh; // _ZFP_GI_Data *

    ZFFrameworkState stateZFFrameworkPostEssential;
    _ZFP_GI_DataArrayType dataLevelZFFrameworkPostEssential;
    ZFCoreMap dataMapLevelZFFrameworkPostEssential; // _ZFP_GI_Data *

    ZFFrameworkState stateZFFrameworkPostStatic;
    _ZFP_GI_DataArrayType dataLevelZFFrameworkPostStatic;
    ZFCoreMap dataMapLevelZFFrameworkPostStatic; // _ZFP_GI_Data *

public:
    _ZFP_GI_DataArrayType &dataListForLevel(ZF_IN ZFLevel level)
    {
        switch(level)
        {
            case ZFLevelZFFrameworkStatic:
                return this->dataLevelZFFrameworkStatic;
            case ZFLevelZFFrameworkEssential:
                return this->dataLevelZFFrameworkEssential;
            case ZFLevelZFFrameworkHigh:
                return this->dataLevelZFFrameworkHigh;
            case ZFLevelZFFrameworkNormal:
                return this->dataLevelZFFrameworkNormal;
            case ZFLevelZFFrameworkLow:
                return this->dataLevelZFFrameworkLow;

            case ZFLevelAppEssential:
                return this->dataLevelAppEssential;
            case ZFLevelAppHigh:
                return this->dataLevelAppHigh;
            case ZFLevelAppNormal:
                return this->dataLevelAppNormal;
            case ZFLevelAppLow:
                return this->dataLevelAppLow;

            case ZFLevelZFFrameworkPostLow:
                return this->dataLevelZFFrameworkPostLow;
            case ZFLevelZFFrameworkPostNormal:
                return this->dataLevelZFFrameworkPostNormal;
            case ZFLevelZFFrameworkPostHigh:
                return this->dataLevelZFFrameworkPostHigh;
            case ZFLevelZFFrameworkPostEssential:
                return this->dataLevelZFFrameworkPostEssential;
            case ZFLevelZFFrameworkPostStatic:
                return this->dataLevelZFFrameworkPostStatic;

            default:
                zfCoreCriticalShouldNotGoHere();
                return this->dataLevelAppLow;
        }
    }
    ZFCoreMap &dataMapForLevel(ZF_IN ZFLevel level)
    {
        switch(level)
        {
            case ZFLevelZFFrameworkStatic:
                return this->dataMapLevelZFFrameworkStatic;
            case ZFLevelZFFrameworkEssential:
                return this->dataMapLevelZFFrameworkEssential;
            case ZFLevelZFFrameworkHigh:
                return this->dataMapLevelZFFrameworkHigh;
            case ZFLevelZFFrameworkNormal:
                return this->dataMapLevelZFFrameworkNormal;
            case ZFLevelZFFrameworkLow:
                return this->dataMapLevelZFFrameworkLow;

            case ZFLevelAppEssential:
                return this->dataMapLevelAppEssential;
            case ZFLevelAppHigh:
                return this->dataMapLevelAppHigh;
            case ZFLevelAppNormal:
                return this->dataMapLevelAppNormal;
            case ZFLevelAppLow:
                return this->dataMapLevelAppLow;

            case ZFLevelZFFrameworkPostLow:
                return this->dataMapLevelZFFrameworkPostLow;
            case ZFLevelZFFrameworkPostNormal:
                return this->dataMapLevelZFFrameworkPostNormal;
            case ZFLevelZFFrameworkPostHigh:
                return this->dataMapLevelZFFrameworkPostHigh;
            case ZFLevelZFFrameworkPostEssential:
                return this->dataMapLevelZFFrameworkPostEssential;
            case ZFLevelZFFrameworkPostStatic:
                return this->dataMapLevelZFFrameworkPostStatic;

            default:
                zfCoreCriticalShouldNotGoHere();
                return this->dataMapLevelAppLow;
        }
    }

public:
    _ZFP_GI_DataContainer(void)
    : state(ZFFrameworkStateNotAvailable)

    , stateZFFrameworkStatic(ZFFrameworkStateNotAvailable)
    , dataLevelZFFrameworkStatic()
    , stateZFFrameworkEssential(ZFFrameworkStateNotAvailable)
    , dataLevelZFFrameworkEssential()
    , stateZFFrameworkHigh(ZFFrameworkStateNotAvailable)
    , dataLevelZFFrameworkHigh()
    , stateZFFrameworkNormal(ZFFrameworkStateNotAvailable)
    , dataLevelZFFrameworkNormal()
    , stateZFFrameworkLow(ZFFrameworkStateNotAvailable)
    , dataLevelZFFrameworkLow()

    , stateAppEssential(ZFFrameworkStateNotAvailable)
    , dataLevelAppEssential()
    , stateAppHigh(ZFFrameworkStateNotAvailable)
    , dataLevelAppHigh()
    , stateAppNormal(ZFFrameworkStateNotAvailable)
    , dataLevelAppNormal()
    , stateAppLow(ZFFrameworkStateNotAvailable)
    , dataLevelAppLow()

    , stateZFFrameworkPostLow(ZFFrameworkStateNotAvailable)
    , dataLevelZFFrameworkPostLow()
    , stateZFFrameworkPostNormal(ZFFrameworkStateNotAvailable)
    , dataLevelZFFrameworkPostNormal()
    , stateZFFrameworkPostHigh(ZFFrameworkStateNotAvailable)
    , dataLevelZFFrameworkPostHigh()
    , stateZFFrameworkPostEssential(ZFFrameworkStateNotAvailable)
    , dataLevelZFFrameworkPostEssential()
    , stateZFFrameworkPostStatic(ZFFrameworkStateNotAvailable)
    , dataLevelZFFrameworkPostStatic()
    {
    }
};
static _ZFP_GI_DataContainer &_ZFP_GI_dataContainerInstance_(void)
{
    static _ZFP_GI_DataContainer _instance;
    return _instance;
}
#define _ZFP_GI_dataContainerInstance (_ZFP_GI_dataContainerInstance_())

zfclassLikePOD _ZFP_ZFFrameworkAutoCleanupHolder
{
public:
    ~_ZFP_ZFFrameworkAutoCleanupHolder(void)
    {
        ZFFrameworkCleanup();
    }
};
void ZFFrameworkInit(void)
{
    static _ZFP_ZFFrameworkAutoCleanupHolder _holder;
    zfbool mutexAvailable = (ZFCoreMutexImplGet() != zfnull);
    if(mutexAvailable)
    {
        zfCoreMutexLock();
    }

    _ZFP_GI_DataContainer &d = _ZFP_GI_dataContainerInstance;
    if(d.state == ZFFrameworkStateNotAvailable)
    {
        d.state = ZFFrameworkStateInitProcessing;

        d.stateZFFrameworkStatic = ZFFrameworkStateInitProcessing;
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkStatic);
        d.stateZFFrameworkStatic = ZFFrameworkStateAvailable;

        d.stateZFFrameworkEssential = ZFFrameworkStateInitProcessing;
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkEssential);
        d.stateZFFrameworkEssential = ZFFrameworkStateAvailable;

        d.stateZFFrameworkHigh = ZFFrameworkStateInitProcessing;
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkHigh);
        d.stateZFFrameworkHigh = ZFFrameworkStateAvailable;

        d.stateZFFrameworkNormal = ZFFrameworkStateInitProcessing;
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkNormal);
        d.stateZFFrameworkNormal = ZFFrameworkStateAvailable;

        d.stateZFFrameworkLow = ZFFrameworkStateInitProcessing;
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkLow);
        d.stateZFFrameworkLow = ZFFrameworkStateAvailable;


        d.stateAppEssential = ZFFrameworkStateInitProcessing;
        _ZFP_GI_instanceInit(d.dataLevelAppEssential);
        d.stateAppEssential = ZFFrameworkStateAvailable;

        d.stateAppHigh = ZFFrameworkStateInitProcessing;
        _ZFP_GI_instanceInit(d.dataLevelAppHigh);
        d.stateAppHigh = ZFFrameworkStateAvailable;

        d.stateAppNormal = ZFFrameworkStateInitProcessing;
        _ZFP_GI_instanceInit(d.dataLevelAppNormal);
        d.stateAppNormal = ZFFrameworkStateAvailable;

        d.stateAppLow = ZFFrameworkStateInitProcessing;
        _ZFP_GI_instanceInit(d.dataLevelAppLow);
        d.stateAppLow = ZFFrameworkStateAvailable;


        d.stateZFFrameworkPostLow = ZFFrameworkStateInitProcessing;
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkPostLow);
        d.stateZFFrameworkPostLow = ZFFrameworkStateAvailable;

        d.stateZFFrameworkPostNormal = ZFFrameworkStateInitProcessing;
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkPostNormal);
        d.stateZFFrameworkPostNormal = ZFFrameworkStateAvailable;

        d.stateZFFrameworkPostHigh = ZFFrameworkStateInitProcessing;
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkPostHigh);
        d.stateZFFrameworkPostHigh = ZFFrameworkStateAvailable;

        d.stateZFFrameworkPostEssential = ZFFrameworkStateInitProcessing;
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkPostEssential);
        d.stateZFFrameworkPostEssential = ZFFrameworkStateAvailable;

        d.stateZFFrameworkPostStatic = ZFFrameworkStateInitProcessing;
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkPostStatic);
        d.stateZFFrameworkPostStatic = ZFFrameworkStateAvailable;


        d.state = ZFFrameworkStateAvailable;

        ZFCoreArrayPOD<ZFFrameworkStateChangeCallback> &m = ZFFrameworkInitFinishCallbacks;
        for(zfindex i = 0; i < m.count(); ++i)
        {
            m[i]();
        }
    }
    else
    {
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkStatic);
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkEssential);
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkHigh);
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkNormal);
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkLow);

        _ZFP_GI_instanceInit(d.dataLevelAppEssential);
        _ZFP_GI_instanceInit(d.dataLevelAppHigh);
        _ZFP_GI_instanceInit(d.dataLevelAppNormal);
        _ZFP_GI_instanceInit(d.dataLevelAppLow);

        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkPostLow);
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkPostNormal);
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkPostHigh);
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkPostEssential);
        _ZFP_GI_instanceInit(d.dataLevelZFFrameworkPostStatic);
    }

    if(mutexAvailable)
    {
        zfCoreMutexUnlock();
    }
}
void ZFFrameworkCleanup(void)
{
    _ZFP_GI_DataContainer &d = _ZFP_GI_dataContainerInstance;
    if(d.state == ZFFrameworkStateAvailable)
    {
        d.state = ZFFrameworkStateCleanupProcessing;

        ZFCoreArrayPOD<ZFFrameworkStateChangeCallback> &m = ZFFrameworkCleanupPrepareCallbacks;
        for(zfindex i = 0; i < m.count(); ++i)
        {
            m[i]();
        }

        d.stateZFFrameworkPostStatic = ZFFrameworkStateCleanupProcessing;
        _ZFP_GI_instanceDealloc(d.dataLevelZFFrameworkPostStatic);
        d.stateZFFrameworkPostStatic = ZFFrameworkStateNotAvailable;

        d.stateZFFrameworkPostEssential = ZFFrameworkStateCleanupProcessing;
        _ZFP_GI_instanceDealloc(d.dataLevelZFFrameworkPostEssential);
        d.stateZFFrameworkPostEssential = ZFFrameworkStateNotAvailable;

        d.stateZFFrameworkPostHigh = ZFFrameworkStateCleanupProcessing;
        _ZFP_GI_instanceDealloc(d.dataLevelZFFrameworkPostHigh);
        d.stateZFFrameworkPostHigh = ZFFrameworkStateNotAvailable;

        d.stateZFFrameworkPostNormal = ZFFrameworkStateCleanupProcessing;
        _ZFP_GI_instanceDealloc(d.dataLevelZFFrameworkPostNormal);
        d.stateZFFrameworkPostNormal = ZFFrameworkStateNotAvailable;

        d.stateZFFrameworkPostLow = ZFFrameworkStateCleanupProcessing;
        _ZFP_GI_instanceDealloc(d.dataLevelZFFrameworkPostLow);
        d.stateZFFrameworkPostLow = ZFFrameworkStateNotAvailable;


        d.stateAppLow = ZFFrameworkStateCleanupProcessing;
        _ZFP_GI_instanceDealloc(d.dataLevelAppLow);
        d.stateAppLow = ZFFrameworkStateNotAvailable;

        d.stateAppNormal = ZFFrameworkStateCleanupProcessing;
        _ZFP_GI_instanceDealloc(d.dataLevelAppNormal);
        d.stateAppNormal = ZFFrameworkStateNotAvailable;

        d.stateAppHigh = ZFFrameworkStateCleanupProcessing;
        _ZFP_GI_instanceDealloc(d.dataLevelAppHigh);
        d.stateAppHigh = ZFFrameworkStateNotAvailable;

        d.stateAppEssential = ZFFrameworkStateCleanupProcessing;
        _ZFP_GI_instanceDealloc(d.dataLevelAppEssential);
        d.stateAppEssential = ZFFrameworkStateNotAvailable;


        d.stateZFFrameworkLow = ZFFrameworkStateCleanupProcessing;
        _ZFP_GI_instanceDealloc(d.dataLevelZFFrameworkLow);
        d.stateZFFrameworkLow = ZFFrameworkStateNotAvailable;

        d.stateZFFrameworkNormal = ZFFrameworkStateCleanupProcessing;
        _ZFP_GI_instanceDealloc(d.dataLevelZFFrameworkNormal);
        d.stateZFFrameworkNormal = ZFFrameworkStateNotAvailable;

        d.stateZFFrameworkHigh = ZFFrameworkStateCleanupProcessing;
        _ZFP_GI_instanceDealloc(d.dataLevelZFFrameworkHigh);
        d.stateZFFrameworkHigh = ZFFrameworkStateNotAvailable;

        d.stateZFFrameworkEssential = ZFFrameworkStateCleanupProcessing;
        _ZFP_GI_instanceDealloc(d.dataLevelZFFrameworkEssential);
        d.stateZFFrameworkEssential = ZFFrameworkStateNotAvailable;

        d.stateZFFrameworkStatic = ZFFrameworkStateCleanupProcessing;
        _ZFP_GI_instanceDealloc(d.dataLevelZFFrameworkStatic);
        d.stateZFFrameworkStatic = ZFFrameworkStateNotAvailable;

        d.state = ZFFrameworkStateNotAvailable;
    }
}

void ZFFrameworkAssertInit(void)
{
    zfCoreAssertWithMessage(ZFFrameworkStateCheck() == ZFFrameworkStateAvailable, zfTextA("ZFFramework hasn't been initialized"));
}
ZFFrameworkState ZFFrameworkStateCheck(void)
{
    return _ZFP_GI_dataContainerInstance.state;
}
ZFFrameworkState ZFFrameworkStateCheck(ZF_IN ZFLevel level)
{
    switch(level)
    {
        case ZFLevelZFFrameworkStatic:
            return _ZFP_GI_dataContainerInstance.stateZFFrameworkStatic;
        case ZFLevelZFFrameworkEssential:
            return _ZFP_GI_dataContainerInstance.stateZFFrameworkEssential;
        case ZFLevelZFFrameworkHigh:
            return _ZFP_GI_dataContainerInstance.stateZFFrameworkHigh;
        case ZFLevelZFFrameworkNormal:
            return _ZFP_GI_dataContainerInstance.stateZFFrameworkNormal;
        case ZFLevelZFFrameworkLow:
            return _ZFP_GI_dataContainerInstance.stateZFFrameworkLow;

        case ZFLevelAppEssential:
            return _ZFP_GI_dataContainerInstance.stateAppEssential;
        case ZFLevelAppHigh:
            return _ZFP_GI_dataContainerInstance.stateAppHigh;
        case ZFLevelAppNormal:
            return _ZFP_GI_dataContainerInstance.stateAppNormal;
        case ZFLevelAppLow:
            return _ZFP_GI_dataContainerInstance.stateAppLow;

        case ZFLevelZFFrameworkPostLow:
            return _ZFP_GI_dataContainerInstance.stateZFFrameworkPostLow;
        case ZFLevelZFFrameworkPostNormal:
            return _ZFP_GI_dataContainerInstance.stateZFFrameworkPostNormal;
        case ZFLevelZFFrameworkPostHigh:
            return _ZFP_GI_dataContainerInstance.stateZFFrameworkPostHigh;
        case ZFLevelZFFrameworkPostEssential:
            return _ZFP_GI_dataContainerInstance.stateZFFrameworkPostEssential;
        case ZFLevelZFFrameworkPostStatic:
            return _ZFP_GI_dataContainerInstance.stateZFFrameworkPostStatic;

        default:
            zfCoreCriticalShouldNotGoHere();
            return _ZFP_GI_dataContainerInstance.stateAppLow;
    }
}

void _ZFP_GI_dataRegister(ZF_IN zfbool *ZFCoreLibDestroyFlag,
                          ZF_IN const zfchar *name,
                          ZF_IN ZFLevel level,
                          ZF_IN _ZFP_GI_Constructor constructor)
{
    _ZFP_GI_DataContainer &holder = _ZFP_GI_dataContainerInstance;
    _ZFP_GI_DataArrayType &dataList = holder.dataListForLevel(level);
    ZFCoreMap &dataMap = holder.dataMapForLevel(level);
    zfstring key = _ZFP_GI_keyForName(name, level);

    _ZFP_GI_Data *data = dataMap.get<_ZFP_GI_Data *>(key.cString());
    if(data != zfnull)
    {
        ++(data->refCount);
    }
    else
    {
        data = zfnew(_ZFP_GI_Data);
        data->name = zfsCopy(name);
        data->level = level;
        data->constructor = constructor;

        dataList.add(data);
        dataMap.set(key.cString(), ZFCorePointerForObject<_ZFP_GI_Data *>(data));
    }
    data->ZFCoreLibDestroyFlag.add(ZFCoreLibDestroyFlag);

    switch(ZFFrameworkStateCheck(level))
    {
        case ZFFrameworkStateNotAvailable:
            // this is the normal routine
            break;
        case ZFFrameworkStateInitProcessing:
            // static register during init processing,
            // may unable to detect dependency
            zfCoreCriticalMessageTrim(
                zfTextA("ZFGlobalInitializer %s attached during init processing, which is not allowed"),
                zfsCoreZ2A(name));
            break;
        case ZFFrameworkStateAvailable:
            // registered after init finish, manually load it
            _ZFP_GI_instanceHolderAccess(name, level);
            break;
        case ZFFrameworkStateCleanupProcessing:
            // static register during cleanup processing,
            // may cause wrong cleanup order
            zfCoreCriticalMessageTrim(
                zfTextA("ZFGlobalInitializer %s attached during cleanup processing, which is not allowed"),
                zfsCoreZ2A(name));
            break;
        default:
            zfCoreCriticalShouldNotGoHere();
            return ;
    }
}
void _ZFP_GI_dataUnregister(ZF_IN zfbool *ZFCoreLibDestroyFlag,
                            ZF_IN const zfchar *name,
                            ZF_IN ZFLevel level)
{
    if(*ZFCoreLibDestroyFlag)
    {
        return ;
    }
    _ZFP_GI_DataContainer &holder = _ZFP_GI_dataContainerInstance;
    _ZFP_GI_DataArrayType &dataList = holder.dataListForLevel(level);
    ZFCoreMap &dataMap = holder.dataMapForLevel(level);
    zfstring key = _ZFP_GI_keyForName(name, level);

    zfiterator it = dataMap.iteratorForKey(key.cString());
    if(!dataMap.iteratorIsValid(it))
    {
        zfCoreCriticalShouldNotGoHere();
        return ;
    }
    _ZFP_GI_Data *data = dataMap.iteratorGetValue<_ZFP_GI_Data *>(it);
    data->ZFCoreLibDestroyFlag.removeElement(ZFCoreLibDestroyFlag);
    --(data->refCount);
    if(data->refCount == 0)
    {
        for(zfiterator itList = dataList.iterator(); dataList.iteratorIsValid(itList); dataList.iteratorNext(itList))
        {
            if(dataList.iteratorGet(itList) == data)
            {
                dataList.iteratorRemove(itList);
                break;
            }
        }
        dataMap.iteratorRemove(it);
    }
}

static void _ZFP_GI_notifyInstanceCreated(ZF_IN const _ZFP_GI_Data *data);
_ZFP_GI_DummyBase *&_ZFP_GI_instanceHolderAccess(ZF_IN const zfchar *name,
                                                 ZF_IN ZFLevel level)
{
    static _ZFP_GI_DummyBase *dummy = zfnull;
    zfCoreMutexLocker();

    if(ZFFrameworkStateCheck(level) == ZFFrameworkStateCleanupProcessing)
    {
        zfCoreCriticalMessageTrim(
            zfTextA("try to reenter global initializer during ZFFrameworkCleanup, name: %s, ")
            zfTextA("typically due to invalid global initializer dependency"),
            zfsCoreZ2A(name));
        return dummy;
    }

    _ZFP_GI_DataContainer &holder = _ZFP_GI_dataContainerInstance;
    ZFCoreMap &dataMap = holder.dataMapForLevel(level);
    zfstring key = _ZFP_GI_keyForName(name, level);

    _ZFP_GI_Data *data = dataMap.get<_ZFP_GI_Data *>(key.cString());
    if(data == zfnull)
    {
        zfCoreCriticalShouldNotGoHere();
        return dummy;
    }

    if(data->instance == zfnull)
    {
        data->instance = data->constructor();
        _ZFP_GI_notifyInstanceCreated(data);
    }

    return data->instance;
}

static const _ZFP_GI_Data *_ZFP_GI_dependencyCheck(_ZFP_GI_DataArrayType &data)
{
    for(zfindex i = 0; i < data.count(); ++i)
    {
        if(data[i]->instance == zfnull)
        {
            return data[i];
        }
    }
    return zfnull;
}
void _ZFP_GI_notifyInstanceCreated(ZF_IN const _ZFP_GI_Data *data)
{
    _ZFP_GI_DataContainer &d = _ZFP_GI_dataContainerInstance;
    // check higher level initialized?
    const _ZFP_GI_Data *dependency = zfnull;
    do
    {
        if(data->level > ZFLevelZFFrameworkStatic)
        {
            if((dependency = _ZFP_GI_dependencyCheck(d.dataLevelZFFrameworkStatic)) != zfnull) {break;}
            if(data->level > ZFLevelZFFrameworkEssential)
            {
                if((dependency = _ZFP_GI_dependencyCheck(d.dataLevelZFFrameworkEssential)) != zfnull) {break;}
                if(data->level > ZFLevelZFFrameworkHigh)
                {
                    if((dependency = _ZFP_GI_dependencyCheck(d.dataLevelZFFrameworkHigh)) != zfnull) {break;}
                    if(data->level > ZFLevelZFFrameworkNormal)
                    {
                        if((dependency = _ZFP_GI_dependencyCheck(d.dataLevelZFFrameworkNormal)) != zfnull) {break;}
                        if(data->level > ZFLevelZFFrameworkLow)
                        {
                            if((dependency = _ZFP_GI_dependencyCheck(d.dataLevelZFFrameworkLow)) != zfnull) {break;}
                        }
                    }
                }
            }
        }
        if(data->level > ZFLevelAppEssential)
        {
            if((dependency = _ZFP_GI_dependencyCheck(d.dataLevelAppEssential)) != zfnull) {break;}
            if(data->level > ZFLevelAppHigh)
            {
                if((dependency = _ZFP_GI_dependencyCheck(d.dataLevelAppHigh)) != zfnull) {break;}
                if(data->level > ZFLevelAppNormal)
                {
                    if((dependency = _ZFP_GI_dependencyCheck(d.dataLevelAppNormal)) != zfnull) {break;}
                    if(data->level > ZFLevelAppLow)
                    {
                        if((dependency = _ZFP_GI_dependencyCheck(d.dataLevelAppLow)) != zfnull) {break;}
                    }
                }
            }
        }
        if(data->level > ZFLevelZFFrameworkPostLow)
        {
            if((dependency = _ZFP_GI_dependencyCheck(d.dataLevelZFFrameworkPostLow)) != zfnull) {break;}
            if(data->level > ZFLevelZFFrameworkPostNormal)
            {
                if((dependency = _ZFP_GI_dependencyCheck(d.dataLevelZFFrameworkPostNormal)) != zfnull) {break;}
                if(data->level > ZFLevelZFFrameworkPostHigh)
                {
                    if((dependency = _ZFP_GI_dependencyCheck(d.dataLevelZFFrameworkPostHigh)) != zfnull) {break;}
                    if(data->level > ZFLevelZFFrameworkPostEssential)
                    {
                        if((dependency = _ZFP_GI_dependencyCheck(d.dataLevelZFFrameworkPostEssential)) != zfnull) {break;}
                        if(data->level > ZFLevelZFFrameworkPostStatic)
                        {
                            if((dependency = _ZFP_GI_dependencyCheck(d.dataLevelZFFrameworkPostStatic)) != zfnull) {break;}
                        }
                    }
                }
            }
        }
    } while(zffalse);
    if(dependency != zfnull)
    {
        // dependency hasn't initialized
        zfCoreCriticalMessageTrim(
                zfTextA("ZFGlobalInitializer %s depends on or level lower than %s")
                zfTextA(", while it hasn't been initialized or already deallocated")
                zfTextA(", typically because of invalid dependency or invalid access")
            , zfsCoreZ2A(data->name), zfsCoreZ2A(dependency->name));
        return ;
    }

    // reorder in same level
    _ZFP_GI_DataArrayType &dataList = d.dataListForLevel(data->level);
    zfindex prevNull = zfindexMax;
    zfindex self = 0;
    for(zfindex i = 0; i < dataList.count(); ++i)
    {
        if(dataList[i] == data)
        {
            self = i;
        }
        else if(prevNull == zfindexMax && dataList[i]->instance == zfnull)
        {
            prevNull = i;
        }
    }
    if(prevNull < self)
    {
        dataList.add(prevNull, dataList[self]);
        dataList.remove(self + 1);
    }
}

ZF_NAMESPACE_GLOBAL_END

