/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFCallback.h
 * @brief header for ZFCallback
 */

#ifndef _ZFI_ZFCallback_h_
#define _ZFI_ZFCallback_h_

#include "ZFMethod.h"
#include "ZFObjectCast.h"
#include "ZFAny.h"
#include "zfautoObjectFwd.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief callback type of ZFCallback
 */
typedef enum
{
    ZFCallbackTypeDummy, /**< @brief dummy that must not be executed */
    ZFCallbackTypeMethod, /**< @brief class static member method described by #ZFMethod */
    ZFCallbackTypeMemberMethod, /**< @brief class memeber method that need a object instance to execute, described by #ZFMethod */
    ZFCallbackTypeRawFunction, /**< @brief static function without #ZFMethod */
} ZFCallbackType;
/** @brief string tokens */
#define ZFTOKEN_ZFCallbackTypeDummy zfText("TypeDummy")
/** @brief string tokens */
#define ZFTOKEN_ZFCallbackTypeMethod zfText("TypeMethod")
/** @brief string tokens */
#define ZFTOKEN_ZFCallbackTypeMemberMethod zfText("TypeMemeberMethod")
/** @brief string tokens */
#define ZFTOKEN_ZFCallbackTypeRawFunction zfText("TypeRawFunction")

// ============================================================
// callback invoker
extern ZF_ENV_EXPORT void _ZFP_ZFCallback_executeNullCallback(ZF_IN const ZFCallerInfo &callerInfo);
/**
 * @brief dummy type for function type pointer for ZFCallback
 */
#define _ZFP_ZFCALLBACK_INVOKER(N) \
    /** @brief see #ZFCallback, you must assign the exact return type and param types for safe */ \
    template<typename T_ReturnType ZFM_REPEAT(N, ZFM_REPEAT_TEMPLATE, ZFM_COMMA)> \
    T_ReturnType executeExact(ZFM_REPEAT(N, ZFM_REPEAT_PARAM, ZFM_EMPTY)) const \
    { \
        switch(_ZFP_ZFCallbackCached_callbackType) \
        { \
            case _ZFP_ZFCallbackCachedTypeDummy: \
                _ZFP_ZFCallback_executeNullCallback(this->callbackCallerInfo()); \
                break; \
            case _ZFP_ZFCallbackCachedTypeClassMember: \
                return ((T_ReturnType (*)(const ZFMethod *, ZFObject * ZFM_REPEAT(N, ZFM_REPEAT_TYPE, ZFM_COMMA)))( \
                    this->_ZFP_ZFCallbackCached_callbackInvoker_method())) \
                        (this->callbackMethod(), _ZFP_ZFCallbackCached_callbackOwnerObj ZFM_REPEAT(N, ZFM_REPEAT_NAME, ZFM_COMMA)); \
            case _ZFP_ZFCallbackCachedTypeRawFunction: \
                return ((T_ReturnType (*)(ZFM_REPEAT(N, ZFM_REPEAT_TYPE, ZFM_EMPTY)))(this->_ZFP_ZFCallbackCached_callbackInvoker_rawFunction())) \
                    (ZFM_REPEAT(N, ZFM_REPEAT_NAME, ZFM_EMPTY)); \
            default: \
                break; \
        } \
        /* typically should not go here */ \
        return ((T_ReturnType (*)(void))(zfnull)) (); \
    }

// ============================================================
// child callback declare
#define _ZFP_ZFCALLBACK_DECLARE_BEGIN(CallbackTypeName, ParentType) \
    zfclassLikePOD ZF_ENV_EXPORT CallbackTypeName : zfextendsLikePOD /* must not virtual inheritance */ ParentType \
    { \
        _ZFP_ZFCALLBACK_DECLARE_CONSTRUCTORS(CallbackTypeName, ParentType) \
    public:
#define _ZFP_ZFCALLBACK_DECLARE_END(CallbackTypeName, ParentType) \
    };
#define _ZFP_ZFCALLBACK_DECLARE_CONSTRUCTORS(CallbackTypeName, ParentType) \
    public: \
        /** @cond ZFPrivateDoc */ \
        CallbackTypeName(void) \
        : ParentType() \
        { \
        } \
        CallbackTypeName(ZF_IN const ZFCallback &ref) \
        : ParentType(ref) \
        { \
        } \
        virtual CallbackTypeName &operator =(ZF_IN const ZFCallback &ref) \
        { \
            ParentType::operator =(ref); \
            return *this; \
        } \
        /** @endcond */
/**
 * @brief see #ZFCALLBACK_DECLARE_BEGIN
 */
#define ZFCALLBACK_DECLARE_END(CallbackTypeName, ParentType) \
    _ZFP_ZFCALLBACK_DECLARE_END(CallbackTypeName, ParentType) \
    ZFPROPERTY_TYPE_ALIAS_DECLARE(ZFCallback, ZFCallback, CallbackTypeName, CallbackTypeName)
#define _ZFP_ZFCALLBACK_DECLARE_END_NO_ALIAS(CallbackTypeName, ParentType) \
    _ZFP_ZFCALLBACK_DECLARE_END(CallbackTypeName, ParentType)
/**
 * @brief util macro to declare a child type of ZFCallback
 *
 * declaration:
 * @code
 *   // in header file
 *   // declare by default:
 *   ZFCALLBACK_DECLARE(CallbackTypeName, ParentType)
 *
 *   // if you need extra functions
 *   ZFCALLBACK_DECLARE_BEGIN(CallbackTypeName, ParentType)
 *       // your extra functions here
 *       // it's not allowed to add member variables
 *   ZFCALLBACK_DECLARE_END(CallbackTypeName, ParentType)
 *
 *   // in source file
 *   ZFCALLBACK_DEFINE(CallbackTypeName, ParentType)
 * @endcode
 */
#define ZFCALLBACK_DECLARE_BEGIN(CallbackTypeName, ParentType) \
    _ZFP_ZFCALLBACK_DECLARE_BEGIN(CallbackTypeName, ParentType)
/**
 * @brief see #ZFCALLBACK_DECLARE_BEGIN
 */
#define ZFCALLBACK_DECLARE(CallbackTypeName, ParentType) \
    ZFCALLBACK_DECLARE_BEGIN(CallbackTypeName, ParentType) \
    ZFCALLBACK_DECLARE_END(CallbackTypeName, ParentType)

/**
 * @brief see #ZFCALLBACK_DECLARE_BEGIN
 */
#define ZFCALLBACK_DEFINE(CallbackTypeName, ParentType) \
    ZFPROPERTY_TYPE_ALIAS_DEFINE(ZFCallback, ZFCallback, CallbackTypeName, CallbackTypeName)

// ============================================================
// ZFCallback
zfclassFwd ZFSerializableData;
zfclassFwd _ZFP_ZFCallbackPrivate;
/**
 * @brief callback used by ZFFramework
 *
 * a callback may be a class member or static member declared as #ZFMethod,
 * or static raw function,
 * it's a ZFMethod pointer container in fact\n
 * use ZFCallbackForXXX to create a callback,
 * then you may pass it as param or store it for future use\n
 * to execute callback, use #executeExact similar to ZFMethod::execute,
 * while you have no need to take care of the owner object
 * @warning before execute, you must check whether the callback is valid,
 *   by #callbackIsValid, otherwise, assert fail
 * @warning while execute, similar to ZFMethod,
 *   you must explicitly assign the ReturnType
 *   and each ParamType for the template param
 *
 * @note you may also declare a child class of ZFCallback,
 *   by ZFCALLBACK_DECLARE_XXX, see #ZFCALLBACK_DECLARE_BEGIN
 */
zfclassLikePOD ZF_ENV_EXPORT ZFCallback
{
public:
    /** @cond ZFPrivateDoc */
    ZFCallback(void);
    ZFCallback(const ZFCallback &ref);
    virtual ZFCallback &operator =(const ZFCallback &ref);
    virtual ~ZFCallback(void);
    zfbool operator == (ZF_IN const ZFCallback &ref) const {return (this->objectCompare(ref) == ZFCompareTheSame);}
    zfbool operator != (ZF_IN const ZFCallback &ref) const {return (this->objectCompare(ref) != ZFCompareTheSame);}
    static ZFCallback _ZFP_ZFCallbackCreate(ZF_IN ZFCallbackType callbackType,
                                            ZF_IN ZFObject *callbackOwnerObj,
                                            ZF_IN const ZFMethod *callbackMethod,
                                            ZF_IN ZFFuncAddrType callbackRawFunc,
                                            ZF_IN const ZFCallerInfo &callerInfo);
    /** @endcond */

    _ZFP_ZFCALLBACK_INVOKER(0)
    _ZFP_ZFCALLBACK_INVOKER(1)
    _ZFP_ZFCALLBACK_INVOKER(2)
    _ZFP_ZFCALLBACK_INVOKER(3)
    _ZFP_ZFCALLBACK_INVOKER(4)
    _ZFP_ZFCALLBACK_INVOKER(5)
    _ZFP_ZFCALLBACK_INVOKER(6)
    _ZFP_ZFCALLBACK_INVOKER(7)
    _ZFP_ZFCALLBACK_INVOKER(8)
    /* ZFMETHOD_MAX_PARAM */

public:
    /**
     * @brief get current retain count
     */
    zffinal zfindex objectRetainCount(void) const;

    /**
     * @brief get a short info about the callback
     */
    virtual void objectInfoT(ZF_IN_OUT zfstring &ret) const;
    /** @brief see #objectInfoT */
    zffinal inline zfstring objectInfo(void) const
    {
        zfstring ret;
        this->objectInfoT(ret);
        return ret;
    }

    /**
     * @brief compare with another callback
     *
     * two callback is considered the same if all of these are same:
     * -  #callbackType
     * -  #callbackOwnerObject
     * -  #callbackMethod
     * -  #callbackFunctionAddr
     */
    zffinal ZFCompareResult objectCompare(ZF_IN const ZFCallback &ref) const;
    /**
     * @brief compare callback by instance only (same callback contents not necessarily to be same instance)
     */
    zffinal ZFCompareResult objectCompareByInstance(ZF_IN const ZFCallback &ref) const;

public:
    /**
     * @brief an unique id for the callback, used for cache logic
     *
     * two callback with same callback id is treated as same callback,
     * which is useful to achieve cache logic\n
     * you must ensure the callback id is unique and verbose enough to describe the callback,
     * otherwise, leave it empty
     */
    zffinal void callbackIdSet(ZF_IN const zfchar *callbackId);
    /**
     * @brief see #callbackIdSet
     */
    zffinal const zfchar *callbackId(void) const;

    /**
     * @brief retain and store a autoreleased object attached to this callback,
     *   or set null to remove
     *
     * recommended to have "ZFCallbackTagKeyword_" as prefix for key name\n
     * usually used to store the owner object,
     * so that it'll be released automatically when all the callback's
     * references were deleted,
     * you can also retain the owner by #callbackOwnerObjectRetain\n
     * you can also save state for the callback as the auto released data
     */
    zffinal void callbackTagSet(ZF_IN const zfchar *key,
                                ZF_IN ZFObject *tag,
                                ZF_IN_OPT zfbool autoMarkCached = zffalse);
    /**
     * @brief #callbackTagSet and automatically mark tag as #ZFObject::objectCached
     */
    zffinal inline void callbackTagSetMarkCached(ZF_IN const zfchar *key,
                                                 ZF_IN ZFObject *tag)
    {
        this->callbackTagSet(key, tag, zftrue);
    }
    /** @brief see #callbackTagSet */
    zffinal ZFObject *callbackTagGet(ZF_IN const zfchar *key) const;
    /** @brief see #callbackTagSet */
    template<typename T_ZFObject>
    T_ZFObject callbackTagGet(ZF_IN const zfchar *key) const
    {
        return ZFCastZFObjectUnchecked(T_ZFObject, this->callbackTagGet(key));
    }
    /** @brief see #callbackTagSet */
    zffinal void callbackTagGetAllKeyValue(ZF_IN_OUT ZFCoreArray<const zfchar *> &allKey,
                                           ZF_IN_OUT ZFCoreArray<ZFObject *> &allValue) const;
    /**
     * @brief remove tag, same as set tag to null
     */
    inline void callbackTagRemove(ZF_IN const zfchar *key)
    {
        this->callbackTagSet(key, zfnull);
    }
    /**
     * @brief remove tag, return removed tag or #zfautoObjectNull if not exist
     */
    zffinal zfautoObject callbackTagRemoveAndGet(ZF_IN const zfchar *key);
    /**
     * @brief see #callbackTagSet
     *
     * @note it's unsafe to remove all tag manually,
     *   which may break unrelated modules' additional logic,
     *   remove only if necessary\n
     *   typically, you should remove exactly the one you have added
     */
    zffinal void callbackTagRemoveAll(void);

    /**
     * @brief return true if callback is valid
     */
    zffinal inline zfbool callbackIsValid(void) const
    {
        return (_ZFP_ZFCallbackCached_callbackType != _ZFP_ZFCallbackCachedTypeDummy);
    }

    /**
     * @brief get the type of callback
     */
    zffinal ZFCallbackType callbackType(void) const;

    /**
     * @brief get the owner object,
     *   valid only if type is class member method
     */
    zffinal ZFObject *callbackOwnerObject(void) const;

    /**
     * @brief get the method or null if not declared by ZFMethod
     */
    zffinal const ZFMethod *callbackMethod(void) const;

    /**
     * @brief get static function, valid only if type is #ZFCallbackTypeRawFunction
     */
    zffinal ZFFuncAddrType callbackFunctionAddr(void) const;

    /**
     * @brief internal use only
     */
    zffinal void callbackCallerInfoSet(ZF_IN const ZFCallerInfo &callerInfo);

    /**
     * @brief get the caller info
     */
    zffinal const ZFCallerInfo &callbackCallerInfo(void) const;

    /**
     * @brief clear and reset to dummy callback,
     *   as well as all attached tags
     *
     * release reference count only,
     * if other callback is refering to the internal data,
     * the data won't be deleted
     */
    zffinal void callbackClear(void);

    /**
     * @brief retain owner object and auto release it
     *   after callback's retain count reduced to 0
     *
     * by default, owner won't be retained,
     * you may use this method to retain owner,
     * or use #callbackTagSet to store owner
     */
    zffinal void callbackOwnerObjectRetain(void) const;
    /**
     * @brief manually release the owner, see #callbackOwnerObjectRetain
     */
    zffinal void callbackOwnerObjectRelease(void) const;

    // ============================================================
    // callback serialize logic
public:
    /**
     * @brief see #ZFPropertyTypeId_ZFCallback
     */
    zffinal void callbackSerializeCustomTypeSet(ZF_IN const zfchar *customType);
    /**
     * @brief see #ZFPropertyTypeId_ZFCallback
     */
    zffinal const zfchar *callbackSerializeCustomType(void) const;
    /**
     * @brief see #ZFPropertyTypeId_ZFCallback
     */
    zffinal void callbackSerializeCustomDataSet(ZF_IN const ZFSerializableData *customData);
    /**
     * @brief see #ZFPropertyTypeId_ZFCallback
     */
    zffinal void callbackSerializeCustomDataSet(ZF_IN const ZFSerializableData &customData)
    {
        this->callbackSerializeCustomDataSet(&customData);
    }
    /**
     * @brief see #ZFPropertyTypeId_ZFCallback
     */
    zffinal const ZFSerializableData *callbackSerializeCustomData(void) const;

    // ============================================================
    // local path logic
public:
    /** @brief see #pathInfo */
    zffinal const zfchar *pathType(void) const;
    /**
     * @brief used for impl to store path related info
     */
    zffinal const zfchar *pathInfo(void) const;
    /** @brief see #pathInfo */
    zffinal void pathInfoSet(ZF_IN const zfchar *pathType, ZF_IN const zfchar *pathInfo);

private:
    _ZFP_ZFCallbackPrivate *d;
    static void _ZFP_ZFCallbackCachedDataSetup(ZF_IN_OUT ZFCallback &c, _ZFP_ZFCallbackPrivate *d);
    typedef enum {
        _ZFP_ZFCallbackCachedTypeDummy,
        _ZFP_ZFCallbackCachedTypeClassMember,
        _ZFP_ZFCallbackCachedTypeRawFunction,
    } _ZFP_ZFCallbackCachedType;
    _ZFP_ZFCallbackCachedType _ZFP_ZFCallbackCached_callbackType;
    ZFFuncAddrType _ZFP_ZFCallbackCached_callbackInvoker_method(void) const;
    ZFFuncAddrType _ZFP_ZFCallbackCached_callbackInvoker_rawFunction(void) const;
    ZFObject *_ZFP_ZFCallbackCached_callbackOwnerObj;
};

// ============================================================
// ZFCallback create
/**
 * @brief see #ZFCallbackNull
 */
#define ZFCallbackNullDetail(callerInfo) \
    ZFCallback::_ZFP_ZFCallbackCreate( \
        ZFCallbackTypeDummy, \
        zfnull, \
        zfnull, \
        zfnull, \
        callerInfo)
/**
 * @brief an empty callback
 */
#define ZFCallbackNull() \
    ZFCallbackNullDetail(ZFCallerInfoMake())

/**
 * @brief see #ZFCallbackForMethod
 */
#define ZFCallbackForMethodDetail(zfmethod, callerInfo) \
    ZFCallback::_ZFP_ZFCallbackCreate( \
        ZFCallbackTypeMethod, \
        zfnull, \
        zfmethod, \
        zfnull, \
        callerInfo)
/**
 * @brief create a callback from ZFMethod
 *
 * assert fail if method not valid\n
 * method can be local method or class static member method
 */
#define ZFCallbackForMethod(zfmethod) \
    ZFCallbackForMethodDetail(zfmethod, ZFCallerInfoMake())

/**
 * @brief see #ZFCallbackForMemberMethod
 */
#define ZFCallbackForMemberMethodDetail(obj, zfmethod, callerInfo) \
    ZFCallback::_ZFP_ZFCallbackCreate( \
        ZFCallbackTypeMemberMethod, \
        obj, \
        zfmethod, \
        zfnull, \
        callerInfo)
/**
 * @brief create a callback from ZFMethod of an object
 *
 * assert fail if method not valid or obj has no such method\n
 * obj won't be retained unless #ZFCallback::callbackOwnerObjectRetain is called,
 * so you must make sure the obj is alive during callback's invocation
 */
#define ZFCallbackForMemberMethod(obj, zfmethod) \
    ZFCallbackForMemberMethodDetail(obj, zfmethod, ZFCallerInfoMake())

/**
 * @brief see #ZFCallbackForRawFunction
 */
#define ZFCallbackForRawFunctionDetail(callbackRawFunc, callerInfo) \
    ZFCallback::_ZFP_ZFCallbackCreate( \
        ZFCallbackTypeRawFunction, \
        zfnull, \
        zfnull, \
        (ZFFuncAddrType)callbackRawFunc, \
        callerInfo)
/**
 * @brief create a callback from static function
 *
 * assert fail if function address not valid
 */
#define ZFCallbackForRawFunction(callbackRawFunc) \
    ZFCallbackForRawFunctionDetail(callbackRawFunc, ZFCallerInfoMake())

/**
 * @brief declare callback from a local declared function
 *
 * usage:
 * @code
 *   // declare
 *   ZFCALLBACK_LOCAL_BEGIN_1(ReturnType, callback, ParamType0, paramName0)
 *   {
 *       // your code here
 *       return ReturnType();
 *   }
 *   ZFCALLBACK_LOCAL_END(callback)
 *   // run
 *   ReturnType ret = callback.executeExact<ReturnType, ParamType0>(param0);
 * @endcode
 *
 * note, this method is used for convenient only,
 * it's not reflectable
 */
#define ZFCALLBACK_LOCAL_BEGIN_0(ReturnType, callbackName) \
    zfclassNotPOD ZFM_CAT(_ZFP_ZFCallbackLocal_, callbackName) \
    { \
    public: \
        static ReturnType callbackName(void)

/** @brief see #ZFCALLBACK_LOCAL_BEGIN_0 */
#define ZFCALLBACK_LOCAL_BEGIN_1(ReturnType, callbackName, ParamType0, paramName0) \
    zfclassNotPOD ZFM_CAT(_ZFP_ZFCallbackLocal_, callbackName) \
    { \
    public: \
        static ReturnType callbackName(ParamType0 paramName0)

/** @brief see #ZFCALLBACK_LOCAL_BEGIN_0 */
#define ZFCALLBACK_LOCAL_BEGIN_2(ReturnType, callbackName, ParamType0, paramName0, ParamType1, paramName1) \
    zfclassNotPOD ZFM_CAT(_ZFP_ZFCallbackLocal_, callbackName) \
    { \
    public: \
        static ReturnType callbackName(ParamType0 paramName0, ParamType1 paramName1)

/** @brief see #ZFCALLBACK_LOCAL_BEGIN_0 */
#define ZFCALLBACK_LOCAL_BEGIN_3(ReturnType, callbackName, ParamType0, paramName0, ParamType1, paramName1, ParamType2, paramName2) \
    zfclassNotPOD ZFM_CAT(_ZFP_ZFCallbackLocal_, callbackName) \
    { \
    public: \
        static ReturnType callbackName(ParamType0 paramName0, ParamType1 paramName1, ParamType2 paramName2)

/** @brief see #ZFCALLBACK_LOCAL_BEGIN_0 */
#define ZFCALLBACK_LOCAL_BEGIN_4(ReturnType, callbackName, ParamType0, paramName0, ParamType1, paramName1, ParamType2, paramName2, ParamType3, paramName3) \
    zfclassNotPOD ZFM_CAT(_ZFP_ZFCallbackLocal_, callbackName) \
    { \
    public: \
        static ReturnType callbackName(ParamType0 paramName0, ParamType1 paramName1, ParamType2 paramName2, ParamType3 paramName3)

/** @brief see #ZFCALLBACK_LOCAL_BEGIN_0 */
#define ZFCALLBACK_LOCAL_BEGIN_5(ReturnType, callbackName, ParamType0, paramName0, ParamType1, paramName1, ParamType2, paramName2, ParamType3, paramName3, ParamType4, paramName4) \
    zfclassNotPOD ZFM_CAT(_ZFP_ZFCallbackLocal_, callbackName) \
    { \
    public: \
        static ReturnType callbackName(ParamType0 paramName0, ParamType1 paramName1, ParamType2 paramName2, ParamType3 paramName3, ParamType4 paramName4)

/** @brief see #ZFCALLBACK_LOCAL_BEGIN_0 */
#define ZFCALLBACK_LOCAL_BEGIN_6(ReturnType, callbackName, ParamType0, paramName0, ParamType1, paramName1, ParamType2, paramName2, ParamType3, paramName3, ParamType4, paramName4, ParamType5, paramName5) \
    zfclassNotPOD ZFM_CAT(_ZFP_ZFCallbackLocal_, callbackName) \
    { \
    public: \
        static ReturnType callbackName(ParamType0 paramName0, ParamType1 paramName1, ParamType2 paramName2, ParamType3 paramName3, ParamType4 paramName4, ParamType5 paramName5)

/** @brief see #ZFCALLBACK_LOCAL_BEGIN_0 */
#define ZFCALLBACK_LOCAL_BEGIN_7(ReturnType, callbackName, ParamType0, paramName0, ParamType1, paramName1, ParamType2, paramName2, ParamType3, paramName3, ParamType4, paramName4, ParamType5, paramName5, ParamType6, paramName6) \
    zfclassNotPOD ZFM_CAT(_ZFP_ZFCallbackLocal_, callbackName) \
    { \
    public: \
        static ReturnType callbackName(ParamType0 paramName0, ParamType1 paramName1, ParamType2 paramName2, ParamType3 paramName3, ParamType4 paramName4, ParamType5 paramName5, ParamType6 paramName6)

/** @brief see #ZFCALLBACK_LOCAL_BEGIN_0 */
#define ZFCALLBACK_LOCAL_BEGIN_8(ReturnType, callbackName, ParamType0, paramName0, ParamType1, paramName1, ParamType2, paramName2, ParamType3, paramName3, ParamType4, paramName4, ParamType5, paramName5, ParamType6, paramName6, ParamType7, paramName7) \
    zfclassNotPOD ZFM_CAT(_ZFP_ZFCallbackLocal_, callbackName) \
    { \
    public: \
        static ReturnType callbackName(ParamType0 paramName0, ParamType1 paramName1, ParamType2 paramName2, ParamType3 paramName3, ParamType4 paramName4, ParamType5 paramName5, ParamType6 paramName6, ParamType7 paramName7)
/* ZFMETHOD_MAX_PARAM */

/** @brief see #ZFCALLBACK_LOCAL_BEGIN_0 */
#define ZFCALLBACK_LOCAL_END(callbackName) \
    ZFCALLBACK_LOCAL_END_WITH_TYPE(ZFCallback, callbackName)
/** @brief see #ZFCALLBACK_LOCAL_BEGIN_0 */
#define ZFCALLBACK_LOCAL_END_WITH_TYPE(CallbackType, callbackName) \
    }; \
    CallbackType callbackName = ZFCallbackForRawFunction((ZFFuncAddrType)(ZFM_CAT(_ZFP_ZFCallbackLocal_, callbackName)::callbackName));

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFCallback_h_

#include "ZFCallback_common.h"
#include "ZFCallback_template.h"

