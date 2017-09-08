/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFCacheable.h
 * @brief cacheable object
 */

#ifndef _ZFI_ZFCacheable_h_
#define _ZFI_ZFCacheable_h_

#include "ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief cacheable object
 */
zfinterface ZF_ENV_EXPORT ZFCacheable : zfextends ZFInterface
{
    ZFINTERFACE_DECLARE(ZFCacheable, ZFInterface)

protected:
    /**
     * @brief used to clear status when access the cache,
     *   see #ZFCACHEABLE_DECLARE
     */
    virtual void cacheableOnReset(void)
    {
        this->toObject()->tagRemoveAll();
    }
public:
    inline void _ZFP_ZFCacheable_cacheableOnReset(void)
    {
        this->cacheableOnReset();
    }
};

template<typename T_ZFCacheable>
zffinal zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCacheableCacheHolder
{
public:
    ZFCoreArrayPOD<T_ZFCacheable *> cache;
public:
    ~_ZFP_ZFCacheableCacheHolder(void)
    {
        zfCoreMutexLock();
        for(zfindex i = 0; i < this->cache.count(); ++i)
        {
            this->cache[i]->objectCachedSet(zffalse);
            zflockfree_zfRelease(this->cache[i]);
        }
        zfCoreMutexUnlock();
    }
};

/**
 * @brief macro to declare access method for #ZFCacheable
 *
 * usage:
 * @code
 *   // in *.h file
 *   zfclass MyCacheable : zfextends ParentObject, zfimplements ZFCacheable
 *   {
 *       ZFOBJECT_DECLARE(MyCacheable, ParentObject)
 *       ZFIMPLEMENTS_DECLARE(ZFCacheable)
 *       ZFCACHEABLE_DECLARE(MyCacheable)
 *   protected:
 *       zfoverride
 *       virtual void cacheableOnReset(void)
 *       {
 *           // call super is required
 *           zfsuper::cacheableOnReset();
 *           // optional
 *           // declare your own method to reset status when add to cache
 *       }
 *   };
 *   // in *.cpp file
 *   ZFCACHEABLE_DEFINE(MyCacheable, MyCacheable)
 *
 *   // for caller
 *   {
 *       ZFCACHEABLE_ACCESS(MyCacheable, MyCacheable, cachedObject);
 *       (void)cachedObject; // now you can use the cachedObject
 *   } // cachedObject would be auto recycled and cached after code block
 *
 *   // or, you may manually manage the cache
 *   MyCacheable *cache = MyCacheable::cacheGet(void);
 *   MyCacheable::cacheAdd(cache);
 *   // note that the cacheGet and cacheAdd must be paired
 * @endcode
 */
#define ZFCACHEABLE_DECLARE(T_ZFCacheable) \
    ZFCACHEABLE_DECLARE_DETAIL(T_ZFCacheable, cacheGet, cacheAdd)
/** @brief see #ZFCACHEABLE_DECLARE */
#define ZFCACHEABLE_DECLARE_DETAIL(T_ZFCacheable, cacheGetMethod, cacheAddMethod) \
    ZFCLASS_SINGLETON_DECLARE(_ZFP_ZFCacheableCacheHolder<T_ZFCacheable>, _ZFP_ZFCacheableCacheHolderRef) \
    public: \
        /** @brief see #ZFCACHEABLE_DECLARE, access the cache */ \
        static T_ZFCacheable *cacheGetMethod(void); \
        /** @brief see #ZFCACHEABLE_DECLARE, release the cache */ \
        static void cacheAddMethod(ZF_IN T_ZFCacheable *cachedObject); \
    public: \
        zffinal zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFCacheableVisitor_##cacheGetMethod \
        { \
        public: \
            _ZFP_ZFCacheableVisitor_##cacheGetMethod(void) \
            : cachedObject(cacheGetMethod()) \
            { \
            } \
            ~_ZFP_ZFCacheableVisitor_##cacheGetMethod(void) \
            { \
                cacheAddMethod(this->cachedObject); \
            } \
        public: \
            T_ZFCacheable *cachedObject; \
        };

/** @brief see #ZFCACHEABLE_DECLARE */
#define ZFCACHEABLE_DEFINE(OwnerClass, T_ZFCacheable) \
    ZFCACHEABLE_DEFINE_DETAIL(OwnerClass, T_ZFCacheable, cacheGet, cacheAdd, 5, ZFLevelZFFrameworkHigh)
/** @brief see #ZFCACHEABLE_DECLARE */
#define ZFCACHEABLE_DEFINE_WITH_MAX(OwnerClass, T_ZFCacheable, MaxSize) \
    ZFCACHEABLE_DEFINE_DETAIL(OwnerClass, T_ZFCacheable, cacheGet, cacheAdd, MaxSize, ZFLevelZFFrameworkHigh)
/** @brief see #ZFCACHEABLE_DECLARE */
#define ZFCACHEABLE_DEFINE_DETAIL(OwnerClass, T_ZFCacheable, cacheGetMethod, cacheAddMethod, \
                                  MaxSize, \
                                  ZFLevel_) \
    ZFCLASS_SINGLETON_DEFINE_DETAIL(OwnerClass, \
                                    _ZFP_ZFCacheableCacheHolder<T_ZFCacheable>, \
                                    _ZFP_ZFCacheableCacheHolder<T_ZFCacheable>, \
                                    _ZFP_ZFCacheableCacheHolderRef, \
                                    ZFLevel_) \
    T_ZFCacheable *OwnerClass::cacheGetMethod(void) \
    { \
        zfCoreMutexLocker(); \
        _ZFP_ZFCacheableCacheHolder<T_ZFCacheable> *holder = OwnerClass::_ZFP_ZFCacheableCacheHolderRef(); \
        T_ZFCacheable *ret = zfnull; \
        if(holder->cache.isEmpty()) \
        { \
            ret = zflockfree_zfAlloc(T_ZFCacheable); \
            ret->objectCachedSet(zftrue); \
        } \
        else \
        { \
            ret = holder->cache.removeLastAndGet(); \
        } \
        return ret; \
    } \
    void OwnerClass::cacheAddMethod(ZF_IN T_ZFCacheable *cachedObject) \
    { \
        zfCoreMutexLocker(); \
        if(cachedObject != zfnull) \
        { \
            _ZFP_ZFCacheableCacheHolder<T_ZFCacheable> *holder = OwnerClass::_ZFP_ZFCacheableCacheHolderRef(); \
            if(holder->cache.count() >= MaxSize) \
            { \
                cachedObject->objectCachedSet(zffalse); \
                zflockfree_zfRelease(cachedObject); \
            } \
            else \
            { \
                cachedObject->_ZFP_ZFCacheable_cacheableOnReset(); \
                holder->cache.add(cachedObject); \
            } \
        } \
    }
/** @brief see #ZFCACHEABLE_DECLARE */
#define ZFCACHEABLE_ACCESS(OwnerClass, T_ZFCacheable, name) \
    ZFCACHEABLE_ACCESS_DETAIL(OwnerClass, T_ZFCacheable, cacheGet, name)
/** @brief see #ZFCACHEABLE_DECLARE */
#define ZFCACHEABLE_ACCESS_DETAIL(T_OwnerClass, T_ZFCacheable, cacheGetMethod, name) \
    T_OwnerClass::_ZFP_ZFCacheableVisitor_##cacheGetMethod _ZFP_ZFCacheableAccess_##name; \
    T_ZFCacheable *name = _ZFP_ZFCacheableAccess_##name.cachedObject

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFCacheable_h_

