/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFObjectHolder.h
 * @brief utilities for ZFObject
 */

#ifndef _ZFI_ZFObjectHolder_h_
#define _ZFI_ZFObjectHolder_h_

#include "ZFObjectCore.h"
#include "ZFObjectSmartPointer.h"
#include "ZFPropertyType.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// ZFObjectHolder
/**
 * @brief util object to hold a ZFObject but don't retain it
 *
 * most of classes and methods use auto-retain logic to hold a ZFObject,
 * so we supply this holder class that won't retain it's content,
 * use only if necessary\n
 * typically, you should use #ZFObject::objectHolder for most case
 */
zffinal zfclass ZF_ENV_EXPORT ZFObjectHolder : zfextends ZFObject
{
    ZFOBJECT_DECLARE(ZFObjectHolder, ZFObject)

protected:
    /** @brief see #ZFObject::objectOnInit */
    virtual void objectOnInit(ZF_IN ZFObject *obj)
    {
        this->objectOnInit();
        this->holdedObj = obj;
    }
    /** @brief see #ZFObject::objectOnInit */
    virtual void objectOnInit(ZF_IN const ZFAny &obj)
    {
        this->objectOnInit();
        this->holdedObj = obj;
    }
    /** @brief see #ZFObject::objectOnInit */
    template<typename T_ZFObject>
    void objectOnInit(ZF_IN const ZFAnyT<T_ZFObject> &obj)
    {
        this->objectOnInit();
        this->holdedObj = obj;
    }

    zfoverride
    virtual void objectOnInit(void)
    {
        zfsuper::objectOnInit();
    }

    zfoverride
    virtual void objectInfoOnAppend(ZF_IN_OUT zfstring &ret);

public:
    zfoverride
    virtual zfidentity objectHash(void);
    zfoverride
    virtual ZFCompareResult objectCompare(ZF_IN ZFObject *anotherObj);

public:
    /**
     * @brief the object, no retain, see #ZFObjectHolder
     */
    ZFAny holdedObj;
};

// ============================================================
/**
 * @brief util class to hold #ZFListener
 */
zfclass ZF_ENV_EXPORT ZFListenerHolder : zfextends ZFObject
{
    ZFOBJECT_DECLARE(ZFListenerHolder, ZFObject)

public:
    /** @brief see #ZFListener */
    ZFListener runnable;
    /** @brief see #ZFListener */
    ZFListenerData listenerData;
    /** @brief see #ZFListener */
    ZFPROPERTY_RETAIN(ZFObject *, userData)

protected:
    /** @brief see #ZFObject::objectOnInit */
    virtual void objectOnInit(ZF_IN const ZFListener &runnable,
                              ZF_IN const ZFListenerData &listenerData,
                              ZF_IN_OPT ZFObject *userData = zfnull)
    {
        this->objectOnInit();
        this->runnable = runnable;
        this->listenerData = listenerData;
        this->userDataSet(userData);
    }

    zfoverride
    virtual void objectOnInit(void)
    {
        zfsuper::objectOnInit();
    }
    zfoverride
    virtual void objectOnDealloc(void)
    {
        zfsuper::objectOnDealloc();
    }

protected:
    zfoverride
    virtual inline void objectInfoOnAppendTokenLeft(ZF_IN_OUT zfstring &ret)
    {
    }
    zfoverride
    virtual inline void objectInfoOnAppendTokenRight(ZF_IN_OUT zfstring &ret)
    {
    }
    zfoverride
    virtual inline void objectInfoOnAppend(ZF_IN_OUT zfstring &ret)
    {
        this->runnable.objectInfoT(ret);
    }
public:
    zfoverride
    virtual zfidentity objectHash(void);
    zfoverride
    virtual ZFCompareResult objectCompare(ZF_IN ZFObject *anotherObj);

public:
    /**
     * @brief execute the runnable or do nothing if callback invalid
     */
    virtual inline void runnableExecute(void)
    {
        if(this->runnable.callbackIsValid())
        {
            this->runnable.execute(this->listenerData, this->userData());
        }
    }
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFObjectHolder_h_

