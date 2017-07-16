/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFPropertyUserRegister.h
 * @brief user registered ZFProperty
 */

#ifndef _ZFI_ZFPropertyUserRegister_h_
#define _ZFI_ZFPropertyUserRegister_h_

#include "ZFMethodUserRegister.h"
#include "ZFProperty.h"
#include "ZFObjectSmartPointer.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
zfclass ZF_ENV_EXPORT _ZFP_I_ZFPropertyUserRegisterDefaultImplValueHolder : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_I_ZFPropertyUserRegisterDefaultImplValueHolder, ZFObject)
public:
    ZFCorePointerBase *v;
public:
    static zfautoObject create(ZF_IN const ZFCorePointerBase &p);
public:
    zfoverride
    virtual void objectOnDealloc(void)
    {
        if(this->v)
        {
            this->v->refDelete();
        }
        zfsuper::objectOnDealloc();
    }
};

// ============================================================
/** @brief default impl for #ZFPropertyUserRegisterRetain */
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT ZFPropertyUserRegisterDefaultImplRetain
{
public:
    /** @brief default impl for #ZFPropertyUserRegisterRetain */
    static void callbackSet(ZF_IN const ZFProperty *property, ZF_IN ZFObject *ownerObj, ZF_IN ZFObject *v)
    {
        zfCoreMutexLocker();
        ownerObj->tagSet(
                zfsConnectLineFree(zfText("ZFPropertyUserRegisterDefaultImplRetain_"), property->propertyName()),
                _ZFP_I_ZFPropertyUserRegisterDefaultImplValueHolder::create(
                    ZFCorePointerForZFObject<T_Type>(ZFCastZFObject(T_Type, v))
                )
            );
    }
    /** @brief default impl for #ZFPropertyUserRegisterRetain */
    static ZFObject *callbackGet(ZF_IN const ZFProperty *property, ZF_IN ZFObject *ownerObj)
    {
        zfCoreMutexLocker();
        _ZFP_I_ZFPropertyUserRegisterDefaultImplValueHolder *holder =
            ownerObj->tagGet<_ZFP_I_ZFPropertyUserRegisterDefaultImplValueHolder *>(
                zfsConnectLineFree(zfText("ZFPropertyUserRegisterDefaultImplRetain_"), property->propertyName()));
        if(holder == zfnull)
        {
            zfautoObject tmp;
            property->userRegisterInitValueSetupCallback((void *)&tmp);

            zfautoObject holderTmp = _ZFP_I_ZFPropertyUserRegisterDefaultImplValueHolder::create(
                    ZFCorePointerForZFObject<T_Type>(tmp.to<T_Type>())
                );
            ownerObj->tagSet(
                zfsConnectLineFree(zfText("ZFPropertyUserRegisterDefaultImplRetain_"), property->propertyName()),
                holderTmp);
            holder = holderTmp.to<_ZFP_I_ZFPropertyUserRegisterDefaultImplValueHolder *>();
        }
        T_Type ret = holder->v->pointerValueT<T_Type>();
        if(ret == zfnull)
        {
            return ret;
        }
        else
        {
            return ret->toObject();
        }
    }
    /** @brief default impl for #ZFPropertyUserRegisterRetain */
    static zfbool callbackIsValueAccessed(ZF_IN const ZFProperty *property, ZF_IN ZFObject *ownerObj)
    {
        return (ownerObj->tagGet(
                zfsConnectLineFree(zfText("ZFPropertyUserRegisterDefaultImplRetain_"), property->propertyName())
            ) != zfnull);
    }
    /** @brief default impl for #ZFPropertyUserRegisterRetain */
    static zfbool callbackIsInitValue(ZF_IN const ZFProperty *property, ZF_IN ZFObject *ownerObj, ZF_OUT_OPT void *outInitValue)
    {
        zfCoreMutexLocker();
        if(!callbackIsValueAccessed(property, ownerObj))
        {
            return zftrue;
        }
        zfautoObject tmp;
        property->userRegisterInitValueSetupCallback((void *)&tmp);
        if(outInitValue != zfnull)
        {
            *(zfautoObject *)outInitValue = tmp;
        }
        T_Type cur = property->getterMethod()->execute<T_Type const &>(ownerObj);
        T_Type initValueTmp = tmp.to<T_Type>();
        if(cur == initValueTmp)
        {
            return zftrue;
        }
        else if(cur == zfnull || initValueTmp == zfnull)
        {
            return zffalse;
        }
        else
        {
            return (cur->toObject()->objectCompare(initValueTmp->toObject()) == ZFCompareTheSame);
        }
    }
    /** @brief default impl for #ZFPropertyUserRegisterRetain */
    static ZFCompareResult callbackCompare(ZF_IN const ZFProperty *property, ZF_IN ZFObject *obj0, ZF_IN ZFObject *obj1)
    {
        return ZFComparerDefault(
            property->getterMethod()->execute<T_Type const &>(obj0),
            property->getterMethod()->execute<T_Type const &>(obj1));
    }
    /** @brief default impl for #ZFPropertyUserRegisterRetain */
    static void callbackCopy(ZF_IN const ZFProperty *property, ZF_IN ZFObject *dstObj, ZF_IN ZFObject *srcObj)
    {
        property->setterMethod()->execute<void, T_Type const &>(dstObj,
            property->getterMethod()->execute<T_Type const &>(srcObj));
    }
    /** @brief default impl for #ZFPropertyUserRegisterRetain */
    static void callbackGetInfo(ZF_IN const ZFProperty *property, ZF_IN ZFObject *ownerObj, ZF_OUT zfstring &ret)
    {
        ZFCoreElementInfoGetter<T_Type>::elementInfoGetter(ret, \
            property->getterMethod()->execute<T_Type const &>(ownerObj)); \
    }
};

// ============================================================
/** @brief default impl for #ZFPropertyUserRegisterAssign */
template<typename T_Type>
zfclassNotPOD ZF_ENV_EXPORT ZFPropertyUserRegisterDefaultImplAssign
{
public:
    /** @brief default impl for #ZFPropertyUserRegisterAssign */
    static void callbackSet(ZF_IN const ZFProperty *property, ZF_IN ZFObject *ownerObj, ZF_IN void *v)
    {
        zfCoreMutexLocker();
        ownerObj->tagSet(
                zfsConnectLineFree(zfText("ZFPropertyUserRegisterDefaultImplAssign_"), property->propertyName()),
                _ZFP_I_ZFPropertyUserRegisterDefaultImplValueHolder::create(
                    ZFCorePointerForObject<T_Type *>(zfnew(T_Type, *(T_Type *)v))
                )
            );
    }
    /** @brief default impl for #ZFPropertyUserRegisterAssign */
    static const void *callbackGet(ZF_IN const ZFProperty *property, ZF_IN ZFObject *ownerObj)
    {
        zfCoreMutexLocker();
        _ZFP_I_ZFPropertyUserRegisterDefaultImplValueHolder *holder =
            ownerObj->tagGet<_ZFP_I_ZFPropertyUserRegisterDefaultImplValueHolder *>(
                zfsConnectLineFree(zfText("ZFPropertyUserRegisterDefaultImplAssign_"), property->propertyName()));
        if(holder == zfnull)
        {
            T_Type tmp = T_Type();
            property->userRegisterInitValueSetupCallback((void *)&tmp);

            zfautoObject holderTmp = _ZFP_I_ZFPropertyUserRegisterDefaultImplValueHolder::create(
                    ZFCorePointerForObject<T_Type *>(zfnew(T_Type, tmp))
                );
            ownerObj->tagSet(
                zfsConnectLineFree(zfText("ZFPropertyUserRegisterDefaultImplAssign_"), property->propertyName()),
                holderTmp);
            holder = holderTmp.to<_ZFP_I_ZFPropertyUserRegisterDefaultImplValueHolder *>();
        }
        return holder->v->pointerValueT<T_Type *>();
    }
    /** @brief default impl for #ZFPropertyUserRegisterAssign */
    static zfbool callbackIsValueAccessed(ZF_IN const ZFProperty *property, ZF_IN ZFObject *ownerObj)
    {
        return (ownerObj->tagGet(
                zfsConnectLineFree(zfText("ZFPropertyUserRegisterDefaultImplAssign_"), property->propertyName())
            ) != zfnull);
    }
    /** @brief default impl for #ZFPropertyUserRegisterAssign */
    static zfbool callbackIsInitValue(ZF_IN const ZFProperty *property, ZF_IN ZFObject *ownerObj, ZF_OUT_OPT void *outInitValue)
    {
        zfCoreMutexLocker();
        if(!callbackIsValueAccessed(property, ownerObj))
        {
            return zftrue;
        }
        T_Type tmp = T_Type();
        property->userRegisterInitValueSetupCallback((void *)&tmp);
        if(outInitValue != zfnull)
        {
            *(T_Type *)outInitValue = tmp;
        }
        return (property->getterMethod()->execute<T_Type const &>(ownerObj) == tmp);
    }
    /** @brief default impl for #ZFPropertyUserRegisterAssign */
    static ZFCompareResult callbackCompare(ZF_IN const ZFProperty *property, ZF_IN ZFObject *obj0, ZF_IN ZFObject *obj1)
    {
        return ZFComparerDefault(
            property->getterMethod()->execute<T_Type const &>(obj0),
            property->getterMethod()->execute<T_Type const &>(obj1));
    }
    /** @brief default impl for #ZFPropertyUserRegisterAssign */
    static void callbackCopy(ZF_IN const ZFProperty *property, ZF_IN ZFObject *dstObj, ZF_IN ZFObject *srcObj)
    {
        property->setterMethod()->execute<void, T_Type const &>(dstObj,
            property->getterMethod()->execute<T_Type const &>(srcObj));
    }
    /** @brief default impl for #ZFPropertyUserRegisterAssign */
    static void callbackGetInfo(ZF_IN const ZFProperty *property, ZF_IN ZFObject *ownerObj, ZF_OUT zfstring &ret)
    {
        ZFCoreElementInfoGetter<T_Type>::elementInfoGetter(ret, \
            property->getterMethod()->execute<T_Type const &>(ownerObj)); \
    }
};

// ============================================================
zfclass ZF_ENV_EXPORT _ZFP_I_ZFPropertyUserRegisterValueAccessorHolder : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_I_ZFPropertyUserRegisterValueAccessorHolder, ZFObject)
public:
    void *v;
};
#define _ZFP_ZFPropertyUserRegisterValueAccessor_Retain(Type, ZFPropertyInitValueOrNoInitValue) \
    public: \
        static void propertySetter(ZF_IN const ZFMethod *method, ZF_IN ZFObject *obj, ZF_IN Type const &v) \
        { \
            zfCoreMutexLocker(); \
            const ZFProperty *property = obj->classData()->propertyForNameIgnoreParent( \
                    zfstring(method->methodName(), zfslen(method->methodName()) - zfslen(zfText("Set"))) \
                ); \
            property->callbackRetainSet(property, obj, ZFObjectToObject(v)); \
        } \
        static Type const &propertyGetter(ZF_IN const ZFMethod *method, ZF_IN ZFObject *obj) \
        { \
            zfCoreMutexLocker(); \
            const ZFProperty *property = obj->classData()->propertyForNameIgnoreParent(method->methodName()); \
            Type v = ZFCastZFObject(Type, property->callbackRetainGet(property, obj)); \
            \
            zfstring tagName = _ZFP_I_ZFPropertyUserRegisterValueAccessorHolder::ClassData()->className(); \
            tagName += method->methodName(); \
            _ZFP_I_ZFPropertyUserRegisterValueAccessorHolder *holder = \
                obj->tagGet<_ZFP_I_ZFPropertyUserRegisterValueAccessorHolder *>(tagName); \
            if(holder == zfnull) \
            { \
                holder = zfAllocWithoutLeakTest(_ZFP_I_ZFPropertyUserRegisterValueAccessorHolder); \
                holder->v = v; \
                obj->tagSet(tagName, holder); \
                zfReleaseWithoutLeakTest(holder); \
            } \
            return *(Type *)(&(holder->v)); \
        } \
        static void propertyInit(ZF_IN_OUT void *p) \
        { \
            typedef Type T_Type; \
            T_Type *valueTmp = zfnull; \
            zflockfree_zfRetain(*(valueTmp = zfpoolNew(T_Type, ZFPropertyInitValueOrNoInitValue))); \
            *(zfautoObject *)p = zfautoObjectCreateWithoutLeakTest(*valueTmp); \
            zfpoolDelete(valueTmp); \
        }
#define _ZFP_ZFPropertyUserRegisterValueAccessor_Assign(Type, ZFPropertyInitValueOrNoInitValue) \
    public: \
        static void propertySetter(ZF_IN const ZFMethod *method, ZF_IN ZFObject *obj, ZF_IN Type const &v) \
        { \
            const ZFProperty *property = obj->classData()->propertyForNameIgnoreParent( \
                    zfstring(method->methodName(), zfslen(method->methodName()) - zfslen(zfText("Set"))) \
                ); \
            Type t = v; \
            property->callbackAssignSet(property, obj, &t); \
        } \
        static Type const &propertyGetter(ZF_IN const ZFMethod *method, ZF_IN ZFObject *obj) \
        { \
            const ZFProperty *property = obj->classData()->propertyForNameIgnoreParent(method->methodName()); \
            const void *p = property->callbackAssignGet(property, obj); \
            return *(zftTraitsType<Type>::TraitsConstPointer)p; \
        } \
        static void propertyInit(ZF_IN_OUT void *p) \
        { \
            typedef Type T_Type; \
            T_Type *valueTmp = zfpoolNew(T_Type, ZFPropertyInitValueOrNoInitValue); \
            *(T_Type *)p = *valueTmp; \
            zfpoolDelete(valueTmp); \
        }
#define _ZFP_ZFPropertyUserRegisterValueAccessor(RetainOrAssign, Type, ZFPropertyInitValueOrNoInitValue) \
    _ZFP_ZFPropertyUserRegisterValueAccessor_##RetainOrAssign(Type, ZFPropertyInitValueOrNoInitValue)
#define _ZFP_ZFPropertyUserRegister(resultProperty, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType, \
        RetainOrAssign, \
        ZFPropertyTypeId_noneOrType, \
        propertyClassOfRetainProperty, \
        Func_ZFPropertyCallbackRetainOrAssignSet, \
        Func_ZFPropertyCallbackRetainOrAssignGet, \
        Func_ZFPropertyCallbackIsValueAccessed, \
        Func_ZFPropertyCallbackIsInitValue, \
        Func_ZFPropertyCallbackCompare, \
        Func_ZFPropertyCallbackCopy, \
        Func_ZFPropertyCallbackGetInfo \
    ) \
    const ZFProperty *resultProperty = zfnull; \
    { \
        zfclassNotPOD _ZFP_ZFPropertyUserRegisterHolder \
        { \
        public: \
            const ZFClass *_ownerClass; \
            zfstring _propertyName; \
            zfstring _propertyInternalId; \
            zfstring _propertyTypeId; \
            const ZFClass *_propertyClassOfRetainProperty; \
            ZFPropertyCallback##RetainOrAssign##Set _callbackSet; \
            ZFPropertyCallback##RetainOrAssign##Get _callbackGet; \
            ZFPropertyCallbackIsValueAccessed _callbackIsValueAccessed; \
            ZFPropertyCallbackIsInitValue _callbackIsInitValue; \
            ZFPropertyCallbackCompare _callbackCompare; \
            ZFPropertyCallbackCopy _callbackCopy; \
            ZFPropertyCallbackGetInfo _callbackGetInfo; \
        public: \
            _ZFP_ZFPropertyUserRegisterHolder(ZF_IN const ZFClass *ownerClass_ \
                , ZF_IN zfstring propertyName_ \
                , ZF_IN zfstring propertyTypeId_ \
                , ZF_IN const ZFClass *propertyClassOfRetainProperty_ \
                , ZF_IN ZFPropertyCallback##RetainOrAssign##Set callbackSet_ \
                , ZF_IN ZFPropertyCallback##RetainOrAssign##Get callbackGet_ \
                , ZF_IN ZFPropertyCallbackIsValueAccessed callbackIsValueAccessed_ \
                , ZF_IN ZFPropertyCallbackIsInitValue callbackIsInitValue_ \
                , ZF_IN ZFPropertyCallbackCompare callbackCompare_ \
                , ZF_IN ZFPropertyCallbackCopy callbackCopy_ \
                , ZF_IN ZFPropertyCallbackGetInfo callbackGetInfo_ \
                ) \
            : _ownerClass(ownerClass_) \
            , _propertyName(propertyName_) \
            , _propertyInternalId() \
            , _propertyTypeId(propertyTypeId_) \
            , _propertyClassOfRetainProperty(propertyClassOfRetainProperty_) \
            , _callbackSet(callbackSet_) \
            , _callbackGet(callbackGet_) \
            , _callbackIsValueAccessed(callbackIsValueAccessed_) \
            , _callbackIsInitValue(callbackIsInitValue_) \
            , _callbackCompare(callbackCompare_) \
            , _callbackCopy(callbackCopy_) \
            , _callbackGetInfo(callbackGetInfo_) \
            { \
                zfCoreAssert(_ownerClass != zfnull); \
                zfCoreAssert(!_propertyName.isEmpty()); \
                _ZFP_ZFPropertyInstanceSig(_propertyInternalId, \
                    _ownerClass->className(), \
                    _propertyName.cString() \
                ); \
                zfCoreAssert(_callbackSet != zfnull); \
                zfCoreAssert(_callbackGet != zfnull); \
                zfCoreAssert(_callbackIsValueAccessed != zfnull); \
                zfCoreAssert(_callbackIsInitValue != zfnull); \
                zfCoreAssert(_callbackCompare != zfnull); \
                zfCoreAssert(_callbackCopy != zfnull); \
                zfCoreAssert(_callbackGetInfo != zfnull); \
            } \
        public: \
            const ZFProperty *propertyRegister(void) \
            { \
                zfCoreMutexLocker(); \
                ZFMethodUserRegisterDetail_1(setterMethod, _ZFP_ZFPropertyUserRegisterHolder::propertySetter, _ownerClass, \
                    SetterAccessType, ZFMethodIsVirtual, \
                    void, zfstringWithFormat(zfText("%sSet"), _propertyName.cString()), \
                    ZFMP_IN(Type const &, value)); \
                zfCoreAssert(setterMethod != zfnull); \
                ZFMethodUserRegisterDetail_0(getterMethod, _ZFP_ZFPropertyUserRegisterHolder::propertyGetter, _ownerClass, \
                    GetterAccessType, ZFMethodIsVirtual, \
                    Type const &, _propertyName); \
                zfCoreAssert(getterMethod != zfnull); \
                \
                ZFProperty *_propertyInfo = _ZFP_ZFPropertyInstanceFind(_propertyInternalId); \
                zfCoreAssertWithMessageTrim(_propertyInfo == zfnull, \
                    zfTextA("[ZFPropertyUserRegister] registering a property that already registered, class: %s, propertyName: %s"), \
                    zfsCoreZ2A(_ownerClass->className()), \
                    zfsCoreZ2A(_propertyName.cString())); \
                _propertyInfo = _ZFP_ZFPropertyInstanceAccess(_propertyInternalId); \
                \
                if(_propertyInfo->_ZFP_ZFPropertyNeedInit) \
                { \
                    _propertyInfo->_ZFP_ZFPropertyNeedInit = zffalse; \
                    _propertyInfo->_ZFP_ZFPropertyInit( \
                        zftrue, \
                        _ownerClass, \
                        _propertyName, \
                        ZFM_TOSTRING(Type), \
                        _propertyTypeId, \
                        setterMethod, \
                        getterMethod, \
                        _propertyClassOfRetainProperty); \
                    _propertyInfo->callbackIsValueAccessed = _callbackIsValueAccessed; \
                    _propertyInfo->callbackIsInitValue = _callbackIsInitValue; \
                    _propertyInfo->callbackCompare = _callbackCompare; \
                    _propertyInfo->callbackCopy = _callbackCopy; \
                    _propertyInfo->callbackGetInfo = _callbackGetInfo; \
                    _propertyInfo->callback##RetainOrAssign##Set = _callbackSet; \
                    _propertyInfo->callback##RetainOrAssign##Get = _callbackGet; \
                    _ownerClass->_ZFP_ZFClass_removeConst()->_ZFP_ZFClass_propertyRegister(_propertyInfo); \
                    _propertyInfo->userRegisterInitValueSetupCallback= _ZFP_ZFPropertyUserRegisterHolder::propertyInit; \
                    _ZFP_ZFClassDataChangeNotify(ZFClassDataChangeTypeAttach, zfnull, _propertyInfo, zfnull); \
                } \
                return _propertyInfo; \
            } \
            _ZFP_ZFPropertyUserRegisterValueAccessor(RetainOrAssign, Type, ZFPropertyInitValueOrNoInitValue) \
        }; \
        const ZFProperty *_##resultProperty = _ZFP_ZFPropertyUserRegisterHolder( \
                  ownerClass \
                , propertyNameString \
                , ZFPropertyTypeId_noneOrType \
                , propertyClassOfRetainProperty \
                , Func_ZFPropertyCallbackRetainOrAssignSet \
                , Func_ZFPropertyCallbackRetainOrAssignGet \
                , Func_ZFPropertyCallbackIsValueAccessed \
                , Func_ZFPropertyCallbackIsInitValue \
                , Func_ZFPropertyCallbackCompare \
                , Func_ZFPropertyCallbackCopy \
                , Func_ZFPropertyCallbackGetInfo \
            ).propertyRegister(); \
        resultProperty = _##resultProperty; \
    } \
    ZFUNUSED(resultProperty)
#define _ZFP_ZFPROPERTY_USER_REGISTER(registerSig, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType, \
        RetainOrAssign, \
        ZFPropertyTypeId_noneOrType, \
        propertyClassOfRetainProperty, \
        Func_ZFPropertyCallbackRetainOrAssignSet, \
        Func_ZFPropertyCallbackRetainOrAssignGet, \
        Func_ZFPropertyCallbackIsValueAccessed, \
        Func_ZFPropertyCallbackIsInitValue, \
        Func_ZFPropertyCallbackCompare, \
        Func_ZFPropertyCallbackCopy, \
        Func_ZFPropertyCallbackGetInfo \
    ) \
    ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(PropReg_##registerSig, ZFLevelZFFrameworkNormal) \
    { \
        _ZFP_ZFPropertyUserRegister(result, ownerClass, \
            Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
            SetterAccessType, GetterAccessType, \
            RetainOrAssign, \
            ZFPropertyTypeId_noneOrType, \
            propertyClassOfRetainProperty, \
            Func_ZFPropertyCallbackRetainOrAssignSet, \
            Func_ZFPropertyCallbackRetainOrAssignGet, \
            Func_ZFPropertyCallbackIsValueAccessed, \
            Func_ZFPropertyCallbackIsInitValue, \
            Func_ZFPropertyCallbackCompare, \
            Func_ZFPropertyCallbackCopy, \
            Func_ZFPropertyCallbackGetInfo \
            ); \
        this->_property = result; \
    } \
    ZF_GLOBAL_INITIALIZER_DESTROY(PropReg_##registerSig) \
    { \
        ZFPropertyUserUnregister(this->_property); \
    } \
    const ZFProperty *_property; \
    ZF_GLOBAL_INITIALIZER_END(PropReg_##registerSig)

// ============================================================
/**
 * @brief register a custom property to existing class, for advanced reflection use only
 *
 * example:
 * @code
 *   // declare each callback for ZFProperty
 *   static void myCallbackRetainSet(ZF_IN const ZFProperty *, ZF_IN ZFObject *ownerObj, ZF_IN ZFObject *v) {...}
 *   static ZFObject *myCallbackRetainGet(ZF_IN const ZFProperty *property, ZF_IN ZFObject *ownerObj) {...}
 *   static zfbool myCallbackIsValueAccessed(ZF_IN const ZFProperty *, ZF_IN ZFObject *ownerObj) {...}
 *   static zfbool myCallbackIsInitValue(ZF_IN const ZFProperty *property, ZF_IN ZFObject *ownerObj, ZF_OUT_OPT void *outInitValue) {...}
 *   static ZFCompareResult myCallbackCompare(ZF_IN const ZFProperty *property, ZF_IN ZFObject *obj0, ZF_IN ZFObject *obj1) {...}
 *   static void myCallbackCopy(ZF_IN const ZFProperty *property, ZF_IN ZFObject *dstObj, ZF_IN ZFObject *srcObj) {...}
 *   static void myCallbackGetInfo(ZF_IN const ZFProperty *property, ZF_IN ZFObject *ownerObj, ZF_OUT zfstring &ret) {...}
 *
 *   // register it, using ZF_GLOBAL_INITIALIZER_INIT is recommended
 *   ZF_GLOBAL_INITIALIZER_INIT(MyPropertyRegister)
 *   {
 *       ZFPropertyUserRegisterRetain(resultProperty, MyClassToAttachTheProperty::ClassData(),
 *           Type, zfText("propertyName"), ZFPropertyNoInitValue,
 *           public, public,
 *           myCallbackRetainSet,
 *           myCallbackRetainGet,
 *           myCallbackIsValueAccessed,
 *           myCallbackIsInitValue,
 *           myCallbackCompare,
 *           myCallbackCopy,
 *           myCallbackGetInfo);
 *       _property = resultProperty;
 *       zfLogTrimT() << resultProperty;
 *   }
 *   ZF_GLOBAL_INITIALIZER_DESTROY(MyPropertyRegister)
 *   {
 *       ZFPropertyUserUnregister(_property);
 *   }
 *   const ZFProperty *_property;
 *   ZF_GLOBAL_INITIALIZER_END(MyPropertyRegister)
 *
 *   // or, you may use this macro for short, at cpp files only
 *   ZFPROPERTY_USER_REGISTER_RETAIN(MyClassToAttachTheProperty, MyClassToAttachTheProperty::ClassData(),
 *       Type, zfText("propertyName"), ZFPropertyNoInitValue,
 *       public, public,
 *       myCallbackRetainSet,
 *       myCallbackRetainGet,
 *       myCallbackIsValueAccessed,
 *       myCallbackIsInitValue,
 *       myCallbackCompare,
 *       myCallbackCopy,
 *       myCallbackGetInfo)
 *
 *   // or, if you simply want to register a raw value,
 *   // you may use ZFPropertyUserRegisterDefaultImplRetain or ZFPropertyUserRegisterDefaultImplAssign as default impl
 *   ZFPROPERTY_USER_REGISTER_RETAIN(MyClassToAttachTheProperty, MyClassToAttachTheProperty::ClassData(),
 *       Type, zfText("propertyName"), ZFPropertyNoInitValue,
 *       public, public,
 *       ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackSet,
 *       ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackGet,
 *       ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackIsValueAccessed,
 *       ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackIsInitValue,
 *       ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackCompare,
 *       ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackCopy,
 *       ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackGetInfo)
 * @endcode
 *
 * note:
 * -  if there is already a property exist with same property name,
 *   register would fail
 * -  the registered property must be unregister manually at proper time,
 *   use #ZF_GLOBAL_INITIALIZER_INIT is recommeded
 * -  once registered, the property can be reflected by #ZFClass::propertyForName,
 *   but there's no way to access the property by object directly,
 *   it can only be accessed by #ZFProperty's method
 */
#define ZFPropertyUserRegisterRetain(resultProperty, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType \
    ) \
    ZFPropertyUserRegisterRetainDetail(resultProperty, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType, \
        ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackSet, \
        ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackGet, \
        ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackIsValueAccessed, \
        ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackIsInitValue, \
        ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackCompare, \
        ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackCopy, \
        ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackGetInfo \
    )
/** @brief see #ZFPropertyUserRegisterRetain */
#define ZFPropertyUserRegisterRetainDetail(resultProperty, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType, \
        Func_ZFPropertyCallbackRetainSet, \
        Func_ZFPropertyCallbackRetainGet, \
        Func_ZFPropertyCallbackIsValueAccessed, \
        Func_ZFPropertyCallbackIsInitValue, \
        Func_ZFPropertyCallbackCompare, \
        Func_ZFPropertyCallbackCopy, \
        Func_ZFPropertyCallbackGetInfo \
    ) \
    _ZFP_ZFPropertyUserRegister(resultProperty, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType, \
        Retain, \
        ZFPropertyTypeId_ZFObject, \
        zftTraitsType<Type>::TraitsType::ClassData(), \
        Func_ZFPropertyCallbackRetainSet, \
        Func_ZFPropertyCallbackRetainGet, \
        Func_ZFPropertyCallbackIsValueAccessed, \
        Func_ZFPropertyCallbackIsInitValue, \
        Func_ZFPropertyCallbackCompare, \
        Func_ZFPropertyCallbackCopy, \
        Func_ZFPropertyCallbackGetInfo \
    )
/** @brief see #ZFPropertyUserRegisterRetain */
#define ZFPROPERTY_USER_REGISTER_RETAIN(registerSig, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType \
    ) \
    ZFPROPERTY_USER_REGISTER_RETAIN_DETAIL(registerSig, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType, \
        ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackSet, \
        ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackGet, \
        ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackIsValueAccessed, \
        ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackIsInitValue, \
        ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackCompare, \
        ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackCopy, \
        ZFPropertyUserRegisterDefaultImplRetain<Type>::callbackGetInfo \
    )
/** @brief see #ZFPropertyUserRegisterRetain */
#define ZFPROPERTY_USER_REGISTER_RETAIN_DETAIL(registerSig, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType, \
        Func_ZFPropertyCallbackRetainSet, \
        Func_ZFPropertyCallbackRetainGet, \
        Func_ZFPropertyCallbackIsValueAccessed, \
        Func_ZFPropertyCallbackIsInitValue, \
        Func_ZFPropertyCallbackCompare, \
        Func_ZFPropertyCallbackCopy, \
        Func_ZFPropertyCallbackGetInfo \
    ) \
    _ZFP_ZFPROPERTY_USER_REGISTER(registerSig, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType, \
        Retain, \
        ZFPropertyTypeId_ZFObject, \
        zftTraitsType<Type>::TraitsType::ClassData(), \
        Func_ZFPropertyCallbackRetainSet, \
        Func_ZFPropertyCallbackRetainGet, \
        Func_ZFPropertyCallbackIsValueAccessed, \
        Func_ZFPropertyCallbackIsInitValue, \
        Func_ZFPropertyCallbackCompare, \
        Func_ZFPropertyCallbackCopy, \
        Func_ZFPropertyCallbackGetInfo \
    )

// ============================================================
/** @brief see #ZFPropertyUserRegisterRetain */
#define ZFPropertyUserRegisterAssign(resultProperty, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType \
    ) \
    ZFPropertyUserRegisterAssignDetail(resultProperty, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType, \
        ZFPropertyUserRegisterDefaultImplAssign<Type>::callbackSet, \
        ZFPropertyUserRegisterDefaultImplAssign<Type>::callbackGet, \
        ZFPropertyUserRegisterDefaultImplAssign<Type>::callbackIsValueAccessed, \
        ZFPropertyUserRegisterDefaultImplAssign<Type>::callbackIsInitValue, \
        ZFPropertyUserRegisterDefaultImplAssign<Type>::callbackCompare, \
        ZFPropertyUserRegisterDefaultImplAssign<Type>::callbackCopy, \
        ZFPropertyUserRegisterDefaultImplAssign<Type>::callbackGetInfo \
    )
/** @brief see #ZFPropertyUserRegisterRetain */
#define ZFPropertyUserRegisterAssignDetail(resultProperty, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType, \
        Func_ZFPropertyCallbackAssignSet, \
        Func_ZFPropertyCallbackAssignGet, \
        Func_ZFPropertyCallbackIsValueAccessed, \
        Func_ZFPropertyCallbackIsInitValue, \
        Func_ZFPropertyCallbackCompare, \
        Func_ZFPropertyCallbackCopy, \
        Func_ZFPropertyCallbackGetInfo \
    ) \
    _ZFP_ZFPropertyUserRegister(resultProperty, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType, \
        Assign, \
        ZFPropertyTypeIdData<zftTraitsType<Type>::TraitsRemoveReference>::PropertyTypeId(), \
        zfnull, \
        Func_ZFPropertyCallbackAssignSet, \
        Func_ZFPropertyCallbackAssignGet, \
        Func_ZFPropertyCallbackIsValueAccessed, \
        Func_ZFPropertyCallbackIsInitValue, \
        Func_ZFPropertyCallbackCompare, \
        Func_ZFPropertyCallbackCopy, \
        Func_ZFPropertyCallbackGetInfo \
    )
/** @brief see #ZFPropertyUserRegisterAssign */
#define ZFPROPERTY_USER_REGISTER_ASSIGN(registerSig, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType \
    ) \
    ZFPROPERTY_USER_REGISTER_ASSIGN_DETAIL(registerSig, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType, \
        ZFPropertyUserRegisterDefaultImplAssign<Type>::callbackSet, \
        ZFPropertyUserRegisterDefaultImplAssign<Type>::callbackGet, \
        ZFPropertyUserRegisterDefaultImplAssign<Type>::callbackIsValueAccessed, \
        ZFPropertyUserRegisterDefaultImplAssign<Type>::callbackIsInitValue, \
        ZFPropertyUserRegisterDefaultImplAssign<Type>::callbackCompare, \
        ZFPropertyUserRegisterDefaultImplAssign<Type>::callbackCopy, \
        ZFPropertyUserRegisterDefaultImplAssign<Type>::callbackGetInfo \
    )
/** @brief see #ZFPropertyUserRegisterAssign */
#define ZFPROPERTY_USER_REGISTER_ASSIGN_DETAIL(registerSig, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType, \
        Func_ZFPropertyCallbackAssignSet, \
        Func_ZFPropertyCallbackAssignGet, \
        Func_ZFPropertyCallbackIsValueAccessed, \
        Func_ZFPropertyCallbackIsInitValue, \
        Func_ZFPropertyCallbackCompare, \
        Func_ZFPropertyCallbackCopy, \
        Func_ZFPropertyCallbackGetInfo \
    ) \
    _ZFP_ZFPROPERTY_USER_REGISTER(registerSig, ownerClass, \
        Type, propertyNameString, ZFPropertyInitValueOrNoInitValue, \
        SetterAccessType, GetterAccessType, \
        Assign, \
        ZFPropertyTypeIdData<zftTraitsType<Type>::TraitsRemoveReference>::PropertyTypeId(), \
        zfnull, \
        Func_ZFPropertyCallbackAssignSet, \
        Func_ZFPropertyCallbackAssignGet, \
        Func_ZFPropertyCallbackIsValueAccessed, \
        Func_ZFPropertyCallbackIsInitValue, \
        Func_ZFPropertyCallbackCompare, \
        Func_ZFPropertyCallbackCopy, \
        Func_ZFPropertyCallbackGetInfo \
    )

// ============================================================
/** @brief see #ZFPropertyUserRegisterRetain */
extern ZF_ENV_EXPORT void ZFPropertyUserUnregister(ZF_IN const ZFProperty *zfproperty);

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFPropertyUserRegister_h_

