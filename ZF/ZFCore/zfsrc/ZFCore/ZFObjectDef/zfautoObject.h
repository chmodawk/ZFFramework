/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file zfautoObject.h
 * @brief smart pointer for ZFObject
 */

#ifndef _ZFI_zfautoObject_h_
#define _ZFI_zfautoObject_h_

#include "ZFObjectCore.h"
#include "ZFObjectRetain.h"
#include "ZFAny.h"
#include "zfautoObjectFwd.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// sub type impl
#define _ZFP_ZFAUTOOBJECT_DECLARE_BEGIN(createFuncName, retainAction, releaseAction) \
    /** @cond ZFPrivateDoc */ \
    zfclassNotPOD ZF_ENV_EXPORT _ZFP_zfautoObjectPrivate_##createFuncName : zfextendsNotPOD _ZFP_zfautoObjectPrivateBase \
    { \
    public: \
        zfoverride \
        virtual _ZFP_zfautoObjectPrivateBase *onRetain(void) \
        { \
            if(this->_ZFP_obj) \
            { \
                ZFObject *p = this->_ZFP_obj; \
                { \
                    retainAction \
                } \
            } \
            return this; \
        } \
        zfoverride \
        virtual void onRelease(void) \
        { \
            if(this->_ZFP_obj) \
            { \
                ZFObject *p = this->_ZFP_obj; \
                this->_ZFP_obj = zfnull; \
                { \
                    releaseAction \
                } \
            } \
        }
#define _ZFP_ZFAUTOOBJECT_DECLARE_END(createFuncName) \
    }; \
    /** @endcond */

/**
 * @brief for impl to supply custom zfautoObject impl
 *
 * usage:
 * @code
 *   // declare in header file
 *   // params in retainAction and releaseAction:
 *   //   ZFObject *p
 *   //   const ZFCallerInfo &callerInfo
 *   ZFAUTOOBJECT_DECLARE_WITH_CALLER_INFO(myCreateFunc, {
 *           zfLogTrimT() << callerInfo.callerInfo();
 *           myRetain(p);
 *       }, {
 *           zfLogTrimT() << callerInfo.callerInfo();
 *           myRelease(p);
 *       })
 *
 *   // use it
 *   zfautoObject obj = myCreateFunc(someObject);
 * @endcode
 */
#define ZFAUTOOBJECT_DECLARE(createFuncName, retainAction, releaseAction) \
    _ZFP_ZFAUTOOBJECT_DECLARE_BEGIN(createFuncName, retainAction, releaseAction) \
    public: \
        _ZFP_zfautoObjectPrivate_##createFuncName(ZF_IN ZFObject *obj) \
        : _ZFP_zfautoObjectPrivateBase(obj) \
        { \
        } \
    _ZFP_ZFAUTOOBJECT_DECLARE_END(createFuncName) \
    inline zfautoObject createFuncName(ZF_IN ZFObject *obj) \
    { \
        return zfautoObject(zfnew(_ZFP_zfautoObjectPrivate_##createFuncName, obj)->onRetain()); \
    }
/**
 * @brief see #ZFAUTOOBJECT_DECLARE
 */
#define ZFAUTOOBJECT_DECLARE_WITH_CALLER_INFO(createFuncName, retainAction, releaseAction) \
    _ZFP_ZFAUTOOBJECT_DECLARE_BEGIN(createFuncName, retainAction, releaseAction) \
    public: \
        ZFCallerInfo callerInfo; \
    public: \
        _ZFP_zfautoObjectPrivate_##createFuncName(ZF_IN ZFObject *obj, \
                                                  ZF_IN const ZFCallerInfo &callerInfo) \
        : _ZFP_zfautoObjectPrivateBase(obj) \
        , callerInfo(callerInfo) \
        { \
        } \
    _ZFP_ZFAUTOOBJECT_DECLARE_END(createFuncName) \
    inline zfautoObject createFuncName(ZF_IN ZFObject *obj, \
                                       ZF_IN const ZFCallerInfo &callerInfo) \
    { \
        return zfautoObject(zfnew(_ZFP_zfautoObjectPrivate_##createFuncName, obj, callerInfo)->onRetain()); \
    }

// ============================================================
/** @brief see #zfautoObject */
ZFAUTOOBJECT_DECLARE(zfautoObjectCreateWithoutLeakTest, {
        zfRetainWithoutLeakTest(p);
    }, {
        zfReleaseWithoutLeakTest(p);
    })

/** @brief see #zfautoObject */
ZFAUTOOBJECT_DECLARE(zflockfree_zfautoObjectCreateWithoutLeakTest, {
        zflockfree_zfRetainWithoutLeakTest(p);
    }, {
        zfReleaseWithoutLeakTest(p);
    })

// ============================================================
/** @brief see #zfautoObject */
ZFAUTOOBJECT_DECLARE_WITH_CALLER_INFO(zfautoObjectCreateVerbose, {
        zfCoreMutexLock();
        zflockfree_zfRetainWithoutLeakTest(p);
        zflockfree_ZFLeakTestLogAfterRetainVerbose(p, callerInfo);
        zfCoreMutexUnlock();
    }, {
        zfCoreMutexLock();
        zflockfree_ZFLeakTestLogBeforeReleaseVerbose(p, callerInfo);
        zflockfree_zfReleaseWithoutLeakTest(p);
        zfCoreMutexUnlock();
    })
/** @brief see #zfautoObject */
#define zfautoObjectCreate(obj) \
    zfautoObjectCreateVerbose(obj, ZFCallerInfoMake())

/** @brief see #zfautoObject */
ZFAUTOOBJECT_DECLARE_WITH_CALLER_INFO(zflockfree_zfautoObjectCreateVerbose, {
        zflockfree_zfRetainWithoutLeakTest(p);
        zflockfree_ZFLeakTestLogAfterRetainVerbose(p, callerInfo);
    }, {
        zfCoreMutexLock();
        zflockfree_ZFLeakTestLogBeforeReleaseVerbose(p, callerInfo);
        zflockfree_zfReleaseWithoutLeakTest(p);
        zfCoreMutexUnlock();
    })
/** @brief see #zfautoObject */
#define zflockfree_zfautoObjectCreate(obj) \
    zflockfree_zfautoObjectCreateVerbose(obj, ZFCallerInfoMake())

// ============================================================
/** @brief see #zfautoObject */
ZFAUTOOBJECT_DECLARE(zfautoObjectCreateMarkCached, {
        zfCoreMutexLock();
        zflockfree_zfRetainWithoutLeakTest(p);
        p->objectCachedSet(zftrue);
        zfCoreMutexUnlock();
    }, {
        zfCoreMutexLock();
        p->objectCachedSet(zffalse);
        zflockfree_zfReleaseWithoutLeakTest(p);
        zfCoreMutexUnlock();
    })
/** @brief see #zfautoObject */
ZFAUTOOBJECT_DECLARE(zflockfree_zfautoObjectCreateMarkCached, {
        zflockfree_zfRetainWithoutLeakTest(p);
        p->objectCachedSet(zftrue);
    }, {
        zfCoreMutexLock();
        p->objectCachedSet(zffalse);
        zflockfree_zfReleaseWithoutLeakTest(p);
        zfCoreMutexUnlock();
    })

// ============================================================
ZFM_CLASS_HAS_MEMBER_DECLARE(zfautoObject, toObject, ZFObject *(T::*F)(void))
template<typename T, int T_isZFObject>
zfclassNotPOD _ZFP_zfautoObjectWrap
{
public:
    static void assign(ZF_IN_OUT zfautoObject &v, ZF_IN T const &p)
    {
        v.operator = (zfautoObjectCreate(ZFCastZFObjectUnchecked(ZFObject *, p)));
    }
    static zfbool equal(ZF_IN const zfautoObject &v, ZF_IN T const &p)
    {
        return (v.toObject() == ZFCastZFObjectUnchecked(ZFObject *, p));
    }
};
template<typename T>
zfclassNotPOD _ZFP_zfautoObjectWrap<T, 0>
{
public:
    static void assign(ZF_IN_OUT zfautoObject &v, ZF_IN T const &p)
    {
        if(p == 0)
        {
            v.operator = (zfautoObjectNull());
        }
    }
    static zfbool equal(ZF_IN const zfautoObject &v, ZF_IN T const &p)
    {
        return (v.toObject() == zfnull && p == 0);
    }
};
/** @cond ZFPrivateDoc */
template<typename T_ZFObject>
zfautoObject &zfautoObject::operator = (ZF_IN T_ZFObject const &p)
{
    _ZFP_zfautoObjectWrap<
            T_ZFObject,
            ZFM_CLASS_HAS_MEMBER(zfautoObject, toObject, typename zftTraitsType<T_ZFObject>::TraitsType) ? 1 : 0
        >::assign(*this, p);
    return *this;
}
template<typename T_ZFObject>
zfbool zfautoObject::operator == (ZF_IN T_ZFObject const &p) const
{
    return _ZFP_zfautoObjectWrap<
            T_ZFObject,
            ZFM_CLASS_HAS_MEMBER(zfautoObject, toObject, typename zftTraitsType<T_ZFObject>::TraitsType) ? 1 : 0
        >::equal(*this, p);
}
/** @endcond */

// ============================================================
// ZFCastZFObject fix for ZFAny
inline ZFObject *_ZFP_ZFCastZFObjectFromUnknown(zfautoObject const &obj)
{
    return obj.toObject();
}
inline void _ZFP_ZFCastZFObjectToUnknown(zfautoObject &ret,
                                         ZFObject * const &obj)
{
    ret = zfautoObjectCreateVerbose(obj, ZFCallerInfo(ZF_CALLER_FILE, zfTextA("ZFCastZFObject"), ZF_CALLER_LINE));
}

inline ZFObject *_ZFP_ZFCastZFObjectFromUnknownUnchecked(zfautoObject const &obj)
{
    return obj.toObject();
}
inline void _ZFP_ZFCastZFObjectToUnknownUnchecked(zfautoObject &ret,
                                                  ZFObject * const &obj)
{
    ret = zfautoObjectCreateVerbose(obj, ZFCallerInfo(ZF_CALLER_FILE, zfTextA("ZFCastZFObjectUnchecked"), ZF_CALLER_LINE));
}

ZF_NAMESPACE_GLOBAL_END

#endif // #ifndef _ZFI_zfautoObject_h_

