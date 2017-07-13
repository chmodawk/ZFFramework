/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFPropertyDeclare.h
 * @brief macros to declare ZFProperty
 */

#ifndef _ZFI_ZFPropertyDeclare_h_
#define _ZFI_ZFPropertyDeclare_h_

#include "ZFProperty.h"
#include "zfautoObjectFwd.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfclassFwd ZFClass;
// ============================================================
/**
 * @brief access the property directly, compile error if not declared
 */
#define ZFPropertyAccess(OwnerClass, Name) ((const ZFProperty *)OwnerClass::_ZFP_Prop##Name())

/**
 * @brief get property by name, or null if not registered
 */
extern ZF_ENV_EXPORT const ZFProperty *ZFPropertyGet(ZF_IN const zfchar *clsName,
                                                     ZF_IN const zfchar *propertyName);
/**
 * @brief get property by name, or null if not registered
 */
extern ZF_ENV_EXPORT const ZFProperty *ZFPropertyGet(ZF_IN const ZFClass *cls,
                                                     ZF_IN const zfchar *propertyName);

// ============================================================
extern ZF_ENV_EXPORT void _ZFP_ZFPropertyCallbackGetInfoRetainDefault(ZF_IN const ZFProperty *property,
                                                                      ZF_IN ZFObject *ownerObj,
                                                                      ZF_IN_OUT zfstring &ret);

#define _ZFP_ZFPROPERTY_DECLARE(Type, ZFPropertyTypeId_noneOrType, Name, \
                                propertyClassOfRetainProperty) \
    public: \
        static ZFProperty *_ZFP_PropInit##Name(void) \
        { \
            zfCoreMutexLocker(); \
            static _ZFP_ZFPropertyInstanceHolder _propertyInfoHolder( \
                _ZFP_ZFPropertyInstanceSig(zfself::ClassData()->className(), ZFM_TOSTRING(Name))); \
            ZFProperty *_propertyInfo = _propertyInfoHolder.propertyInfo; \
            if(_propertyInfo->_ZFP_ZFPropertyNeedInit) \
            { \
                _propertyInfo->_ZFP_ZFPropertyNeedInit = zffalse; \
                _propertyInfo->_ZFP_ZFPropertyInit( \
                    zffalse, \
                    zfself::ClassData(), \
                    ZFM_TOSTRING(Name), \
                    ZFM_TOSTRING(Type), \
                    ZFPropertyTypeId_noneOrType, \
                    ZFMethodAccess(zfself, _ZFP_ZFPROPERTY_SETTER_NAME(Type, Name)), \
                    ZFMethodAccess(zfself, _ZFP_ZFPROPERTY_GETTER_NAME(Type, Name)), \
                    propertyClassOfRetainProperty); \
                _propertyInfo->callbackIsValueAccessed = zfself::_ZFP_propCbAccessed_##Name; \
                _propertyInfo->callbackIsInitValue = zfself::_ZFP_propCbIsInit_##Name; \
                _propertyInfo->callbackCompare = zfself::_ZFP_propCbCmp_##Name; \
                _propertyInfo->callbackCopy = zfself::_ZFP_propCbCp_##Name; \
                _propertyInfo->_ZFP_ZFPropertyDeallocCallbackFunc = zfself::_ZFP_propCbDel_##Name; \
                zfself::_ZFP_propCbSetup_##Name(_propertyInfo); \
                zfself::_ZFP_ZFObjectGetClass()->_ZFP_ZFClass_propertyRegister(_propertyInfo); \
                _ZFP_ZFClassDataChangeNotify(ZFClassDataChangeTypeAttach, zfnull, _propertyInfo, zfnull); \
            } \
            return _propertyInfo; \
        } \
        static ZFProperty *_ZFP_Prop##Name(void) \
        { \
            static ZFProperty *_propertyInfo = zfself::_ZFP_PropInit##Name(); \
            return _propertyInfo; \
        } \
    private: \
        _ZFP_ZFPROPERTY_DECLARE_CALLBACK_IS_INIT_VALUE(Type, Name) \
        _ZFP_ZFPROPERTY_DECLARE_CALLBACK_COMPARE(Type, Name) \
        _ZFP_ZFPROPERTY_DECLARE_CALLBACK_COPY(Type, Name) \
    public:
#define _ZFP_ZFPROPERTY_VALUE_DECLARE_RETAIN(Type, ZFPropertyTypeId_noneOrType, Name, \
                                             ZFPropertyInitValueOrNoInitValue) \
    public: \
        typedef Type _ZFP_PropVT_##Name; \
        typedef zfautoObject _ZFP_PropAT_##Name; \
    private: \
        zffinal zfclassNotPOD _ZFP_PropV_##Name \
        { \
        public: \
            _ZFP_PropV_##Name(void) \
            : value(zfnull), valueHolder() \
            { \
                static zftValue<const ZFProperty *> _dummy(zfself::_ZFP_Prop##Name()); \
            } \
        public: \
            zfself::_ZFP_PropVT_##Name &propertyInit(ZF_IN zfself *owner, \
                                                     ZF_IN_OPT zfbool needNotifyOwner = zftrue) \
            { \
                if(!(this->value)) \
                { \
                    zflockfree_zfRetain(*(this->value = zfpoolNew(zfself::_ZFP_PropVT_##Name, ZFPropertyInitValueOrNoInitValue))); \
                    this->valueHolder = zflockfree_zfautoObjectCreate(ZFObjectToObject(*(this->value))); \
                    zflockfree_zfRelease(*(this->value)); \
                    owner->_ZFP_propL_onInit_##Name(this->valueHolder, this->valueHolder); \
                    *(this->value) = this->valueHolder; \
                    if(needNotifyOwner) \
                    { \
                        owner->_ZFP_propL_onAttach_##Name(this->valueHolder, this->valueHolder); \
                        owner->toObject()->_ZFP_ZFObject_objectPropertyValueAttach(zfself::_ZFP_Prop##Name(), zftrue); \
                        owner->_ZFP_propL_onUpdate_##Name(this->valueHolder, this->valueHolder); \
                        owner->toObject()->_ZFP_ZFObject_objectPropertyValueOnUpdate(zfself::_ZFP_Prop##Name(), zfnull); \
                    } \
                } \
                return (*(this->value)); \
            } \
            inline zfbool propertyAccessed(void) const \
            { \
                return (this->value != zfnull); \
            } \
            void propertyDealloc(zfself *owner) \
            { \
                owner->_ZFP_propL_onDetach_##Name(this->valueHolder, this->valueHolder); \
                owner->toObject()->_ZFP_ZFObject_objectPropertyValueDetach(zfself::_ZFP_Prop##Name()); \
                owner->_ZFP_propL_onDealloc_##Name(this->valueHolder, this->valueHolder); \
                zfpoolDelete(this->value); \
                this->value = zfnull; \
            } \
        private: \
            zfself::_ZFP_PropVT_##Name *value; \
        public: \
            zfautoObject valueHolder; \
        }; \
        zfself::_ZFP_PropV_##Name Name##_ZFPropertyValue; \
    public: \
        zfbool _ZFP_propCbIsInitAI_##Name(ZF_OUT_OPT void *outInitValue) \
        { \
            if(Name##_ZFPropertyValue.propertyAccessed()) \
            { \
                zfself::_ZFP_PropV_##Name _holder; \
                if(outInitValue != zfnull) \
                { \
                    *(zfautoObject *)outInitValue = zfautoObjectCreateWithoutLeakTest( \
                        ZFCastZFObjectUnchecked(ZFObject *, _holder.propertyInit(this, zffalse))); \
                } \
                return (ZFComparerDefault( \
                        this->_ZFP_ZFPROPERTY_GETTER_NAME_INTERNAL(Type, Name)(), _holder.propertyInit(this, zffalse)) \
                    == ZFCompareTheSame); \
            } \
            else \
            { \
                return zftrue; \
            } \
        } \
    public:
#define _ZFP_ZFPROPERTY_VALUE_DECLARE_ASSIGN(Type, ZFPropertyTypeId_noneOrType, Name, \
                                             ZFPropertyInitValueOrNoInitValue) \
    public: \
        typedef Type _ZFP_PropVT_##Name; \
        typedef Type _ZFP_PropAT_##Name; \
    private: \
        zffinal zfclassNotPOD _ZFP_PropV_##Name \
        { \
        public: \
            _ZFP_PropV_##Name(void) \
            : value(zfnull) \
            { \
                static zftValue<const ZFProperty *> _dummy(zfself::_ZFP_Prop##Name()); \
            } \
        public: \
            zfself::_ZFP_PropVT_##Name &propertyInit(ZF_IN zfself *owner, \
                                                     ZF_IN_OPT zfbool needNotifyOwner = zftrue) \
            { \
                if(!(this->value)) \
                { \
                    this->value = zfpoolNew(zfself::_ZFP_PropVT_##Name, ZFPropertyInitValueOrNoInitValue); \
                    owner->_ZFP_propL_onInit_##Name(*(this->value), *(this->value)); \
                    if(needNotifyOwner) \
                    { \
                        owner->_ZFP_propL_onAttach_##Name(*(this->value), *(this->value)); \
                        owner->toObject()->_ZFP_ZFObject_objectPropertyValueAttach(zfself::_ZFP_Prop##Name(), zftrue); \
                        owner->_ZFP_propL_onUpdate_##Name(*(this->value), *(this->value)); \
                        owner->toObject()->_ZFP_ZFObject_objectPropertyValueOnUpdate(zfself::_ZFP_Prop##Name(), zfnull); \
                    } \
                } \
                return (*(this->value)); \
            } \
            inline zfbool propertyAccessed(void) const \
            { \
                return (this->value != zfnull); \
            } \
            void propertyDealloc(zfself *owner) \
            { \
                owner->_ZFP_propL_onDetach_##Name(*(this->value), *(this->value)); \
                owner->toObject()->_ZFP_ZFObject_objectPropertyValueDetach(zfself::_ZFP_Prop##Name()); \
                owner->_ZFP_propL_onDealloc_##Name(*(this->value), *(this->value)); \
                zfpoolDelete(this->value); \
                this->value = zfnull; \
            } \
        private: \
            zfself::_ZFP_PropVT_##Name *value; \
        }; \
        zfself::_ZFP_PropV_##Name Name##_ZFPropertyValue; \
    public: \
        zfbool _ZFP_propCbIsInitAI_##Name(ZF_OUT_OPT void *outInitValue) \
        { \
            if(Name##_ZFPropertyValue.propertyAccessed()) \
            { \
                zfself::_ZFP_PropV_##Name _holder; \
                if(outInitValue != zfnull) \
                { \
                    *(Type *)outInitValue = _holder.propertyInit(this, zffalse); \
                } \
                return (ZFComparerDefault( \
                        this->_ZFP_ZFPROPERTY_GETTER_NAME_INTERNAL(Type, Name)(), _holder.propertyInit(this, zffalse)) \
                    == ZFCompareTheSame); \
            } \
            else \
            { \
                return zftrue; \
            } \
        } \
    public:

// ============================================================
#define _ZFP_ZFPROPERTY_DECLARE_CALLBACK_IS_INIT_VALUE(Type, Name) \
    private: \
        static zfbool _ZFP_propCbAccessed_##Name(ZF_IN const ZFProperty *property, \
                                                 ZF_IN ZFObject *ownerObj) \
        { \
            return ZFCastZFObjectUnchecked(zfself *, ownerObj)->Name##_ZFPropertyValue.propertyAccessed(); \
        } \
    private: \
        static zfbool _ZFP_propCbIsInit_##Name(ZF_IN const ZFProperty *property, \
                                               ZF_IN ZFObject *ownerObj, \
                                               ZF_OUT_OPT void *outInitValue) \
        { \
            return ZFCastZFObjectUnchecked(zfself *, ownerObj)->_ZFP_propCbIsInitA_##Name(outInitValue); \
        } \
        ZFM_CLASS_HAS_MEMBER_DECLARE(_, _ZFP_propCbIsInitAC_##Name, zfbool (T::*F)(void *)) \
        template<typename T_Owner, int hasCustom> \
        zfclassNotPOD _ZFP_PropCbIsInitAW_##Name \
        { \
        public: \
            static inline zfbool action(ZF_IN T_Owner *owner, ZF_OUT_OPT void *outInitValue) \
            { \
                return owner->_ZFP_propCbIsInitAI_##Name(outInitValue); \
            } \
        }; \
        template<typename T_Owner> \
        zfclassNotPOD _ZFP_PropCbIsInitAW_##Name<T_Owner, 1> \
        { \
        public: \
            static inline zfbool action(ZF_IN T_Owner *owner, ZF_OUT_OPT void *outInitValue) \
            { \
                return owner->_ZFP_propCbIsInitAC_##Name(outInitValue); \
            } \
        }; \
    public: \
        virtual zfbool _ZFP_propCbIsInitA_##Name(ZF_OUT_OPT void *outInitValue) \
        { \
            zfCoreMutexLocker(); \
            return _ZFP_PropCbIsInitAW_##Name<zfself, \
                    ZFM_CLASS_HAS_MEMBER(_, _ZFP_propCbIsInitAC_##Name, zfself) \
                >::action(this, outInitValue); \
        }

#define _ZFP_ZFPROPERTY_DECLARE_CALLBACK_COMPARE(Type, Name) \
    private: \
        static ZFCompareResult _ZFP_propCbCmp_##Name(ZF_IN const ZFProperty *property, \
                                                     ZF_IN ZFObject *obj0, \
                                                     ZF_IN ZFObject *obj1) \
        { \
            return ZFCastZFObjectUnchecked(zfself *, obj0)->_ZFP_propCbCmpA_##Name(obj1); \
        } \
        ZFM_CLASS_HAS_MEMBER_DECLARE(_, _ZFP_propCbCmpAC_##Name, ZFCompareResult (T::*F)(ZF_IN ZFObject *)) \
        template<typename T_Owner, int hasCustom> \
        zfclassNotPOD _ZFP_WropCbCmpAW_##Name \
        { \
        public: \
            static inline ZFCompareResult action(ZF_IN T_Owner *owner, ZF_IN ZFObject *anotherObj) \
            { \
                return owner->_ZFP_propCbCmpAI_##Name(anotherObj); \
            } \
        }; \
        template<typename T_Owner> \
        zfclassNotPOD _ZFP_WropCbCmpAW_##Name<T_Owner, 1> \
        { \
        public: \
            static inline ZFCompareResult action(ZF_IN T_Owner *owner, ZF_IN ZFObject *anotherObj) \
            { \
                return owner->_ZFP_propCbCmpAC_##Name(anotherObj); \
            } \
        }; \
    public: \
        virtual ZFCompareResult _ZFP_propCbCmpA_##Name(ZF_IN ZFObject *anotherObj) \
        { \
            return _ZFP_WropCbCmpAW_##Name<zfself, \
                    ZFM_CLASS_HAS_MEMBER(_, _ZFP_propCbCmpAC_##Name, zfself) \
                >::action(this, anotherObj); \
        } \
        virtual ZFCompareResult _ZFP_propCbCmpAI_##Name(ZF_IN ZFObject *anotherObj) \
        { \
            return ZFComparerDefault( \
                this->_ZFP_ZFPROPERTY_GETTER_NAME(Type, Name)(), \
                ZFCastZFObjectUnchecked(zfself *, anotherObj)->_ZFP_ZFPROPERTY_GETTER_NAME(Type, Name)()); \
        }

#define _ZFP_ZFPROPERTY_DECLARE_CALLBACK_COPY(Type, Name) \
    private: \
        static void _ZFP_propCbCp_##Name(ZF_IN const ZFProperty *property, \
                                         ZF_IN ZFObject *dstObj, \
                                         ZF_IN ZFObject *srcObj) \
        { \
            property->setterMethod()->execute<void, Type const &>(dstObj, \
                property->getterMethod()->execute<Type const &>(srcObj)); \
        } \
    public:
#define _ZFP_ZFPROPERTY_DECLARE_CALLBACK_RETAIN(Type, Name) \
    private: \
        static void _ZFP_propCbRS_##Name(ZF_IN const ZFProperty *property, \
                                         ZF_IN ZFObject *dstObj, \
                                         ZF_IN ZFObject *src) \
        { \
            property->setterMethod()->execute<void, Type const &>(dstObj, ZFCastZFObjectUnchecked(Type, src)); \
        } \
        static ZFObject *_ZFP_propCbRG_##Name(ZF_IN const ZFProperty *property, \
                                                                 ZF_IN ZFObject *ownerObj) \
        { \
            return ZFCastZFObjectUnchecked(ZFObject *, property->getterMethod()->execute<Type const &>(ownerObj)); \
        } \
        static void _ZFP_propCbSetup_##Name(ZFProperty *propertyInfo) \
        { \
            propertyInfo->callbackRetainSet = zfself::_ZFP_propCbRS_##Name; \
            propertyInfo->callbackRetainGet = zfself::_ZFP_propCbRG_##Name; \
            propertyInfo->callbackGetInfo = _ZFP_ZFPropertyCallbackGetInfoRetainDefault; \
        } \
    public:
#define _ZFP_ZFPROPERTY_DECLARE_CALLBACK_ASSIGN(Type, Name) \
    private: \
        static void _ZFP_propCbAS_##Name(ZF_IN const ZFProperty *property, \
                                                            ZF_IN ZFObject *dstObj, \
                                                            ZF_IN void *src) \
        { \
            property->setterMethod()->execute<void, Type const &>(dstObj, *(ZFCastStatic(Type *, src))); \
        } \
        static const void *_ZFP_propCbAG_##Name(ZF_IN const ZFProperty *property, \
                                                                   ZF_IN ZFObject *ownerObj) \
        { \
            return &(property->getterMethod()->execute<Type const &>(ownerObj)); \
        } \
        static void _ZFP_propCbAGI_##Name(ZF_IN const ZFProperty *property, \
                                                                ZF_IN ZFObject *ownerObj, \
                                                                ZF_IN_OUT zfstring &ret) \
        { \
            ZFCoreElementInfoGetter<Type>::elementInfoGetter(ret, \
                property->getterMethod()->execute<Type const &>(ownerObj)); \
        } \
        static void _ZFP_propCbSetup_##Name(ZFProperty *propertyInfo) \
        { \
            propertyInfo->callbackAssignSet = zfself::_ZFP_propCbAS_##Name; \
            propertyInfo->callbackAssignGet = zfself::_ZFP_propCbAG_##Name; \
            propertyInfo->callbackGetInfo = zfself::_ZFP_propCbAGI_##Name; \
        } \
    public:

// ============================================================
#define _ZFP_ZFPROPERTY_LIFE_CYCLE_EVENTS(Type, Name) \
    private: \
        _ZFP_ZFPROPERTY_LIFE_CYCLE_WRAPPER(Type, Name, onInit, ZFM_EMPTY) \
        _ZFP_ZFPROPERTY_LIFE_CYCLE_WRAPPER(Type, Name, onDealloc, ZFM_EXPAND) \
        _ZFP_ZFPROPERTY_LIFE_CYCLE_WRAPPER(Type, Name, onVerify, ZFM_EMPTY) \
        _ZFP_ZFPROPERTY_LIFE_CYCLE_WRAPPER(Type, Name, onAttach, ZFM_EXPAND) \
        _ZFP_ZFPROPERTY_LIFE_CYCLE_WRAPPER(Type, Name, onDetach, ZFM_EXPAND) \
        _ZFP_ZFPROPERTY_LIFE_CYCLE_WRAPPER(Type, Name, onUpdate, ZFM_EXPAND) \
        static void _ZFP_propCbDel_##Name(ZF_IN ZFObject *owner, ZF_IN const ZFProperty *property) \
        { \
            zfself *t = ZFCastZFObjectUnchecked(zfself *, owner); \
            t->Name##_ZFPropertyValue.propertyDealloc(t); \
        } \
    public:
#define _ZFP_ZFPROPERTY_DECLARE_RETAIN(Type, ZFPropertyTypeId_noneOrType, Name, \
                                       ZFPropertyInitValueOrNoInitValue) \
    _ZFP_ZFPROPERTY_DECLARE(Type, ZFPropertyTypeId_noneOrType, Name, \
                            zftTraitsType<Type>::TraitsType::ClassData()) \
    _ZFP_ZFPROPERTY_VALUE_DECLARE_RETAIN(Type, ZFPropertyTypeId_noneOrType, Name, \
                                         ZFPropertyInitValueOrNoInitValue) \
    _ZFP_ZFPROPERTY_DECLARE_CALLBACK_RETAIN(Type, Name) \
    _ZFP_ZFPROPERTY_LIFE_CYCLE_EVENTS(Type, Name)
#define _ZFP_ZFPROPERTY_DECLARE_ASSIGN(Type, ZFPropertyTypeId_noneOrType, Name, \
                                       ZFPropertyInitValueOrNoInitValue) \
    _ZFP_ZFPROPERTY_DECLARE(Type, ZFPropertyTypeId_noneOrType, Name, \
                            zfnull) \
    _ZFP_ZFPROPERTY_VALUE_DECLARE_ASSIGN(Type, ZFPropertyTypeId_noneOrType, Name, \
                                         ZFPropertyInitValueOrNoInitValue) \
    _ZFP_ZFPROPERTY_DECLARE_CALLBACK_ASSIGN(Type, Name) \
    _ZFP_ZFPROPERTY_LIFE_CYCLE_EVENTS(Type, Name)

// ============================================================
#define _ZFP_ZFPROPERTY_VALUE_REF(Name) \
    (Name##_ZFPropertyValue.propertyInit(this))

#define _ZFP_ZFPROPERTY_SETTER_NAME(Type, Name) \
    Name##Set
#define _ZFP_ZFPROPERTY_SETTER_NAME_INTERNAL(Type, Name) \
    Name##SetInternal

#define _ZFP_ZFPROPERTY_GETTER_NAME(Type, Name) \
    Name
#define _ZFP_ZFPROPERTY_GETTER_NAME_INTERNAL(Type, Name) \
    Name##Internal

// ============================================================
#define _ZFP_ZFPROPERTY_INTERNAL_ACCESSTYPE_public protected
#define _ZFP_ZFPROPERTY_INTERNAL_ACCESSTYPE_protected protected
#define _ZFP_ZFPROPERTY_INTERNAL_ACCESSTYPE_private private
#define _ZFP_ZFPROPERTY_INTERNAL_ACCESSTYPE_(ForAccessType) \
    _ZFP_ZFPROPERTY_INTERNAL_ACCESSTYPE_##ForAccessType
#define _ZFP_ZFPROPERTY_INTERNAL_ACCESSTYPE(ForAccessType) \
    _ZFP_ZFPROPERTY_INTERNAL_ACCESSTYPE_(ForAccessType)

// ============================================================
#define _ZFP_ZFPROPERTY_SETTER_INTERNAL_RETAIN(AccessType, Type, Name) \
    AccessType: \
        inline void _ZFP_ZFPROPERTY_SETTER_NAME_INTERNAL(Type, Name)(Type const &propertyValue) \
        { \
            zfCoreMutexLock(); \
            Type &valuePointerRef = _ZFP_ZFPROPERTY_VALUE_REF(Name); /* must access first */ \
            zfautoObject &valueRef = this->Name##_ZFPropertyValue.valueHolder; \
            zfautoObject valueOld = valueRef; \
            zfautoObject valueNew = zflockfree_zfautoObjectCreate(ZFObjectToObject(propertyValue)); \
            this->_ZFP_propL_onDetach_##Name(valueNew, valueOld); \
            toObject()->_ZFP_ZFObject_objectPropertyValueDetach(zfself::_ZFP_Prop##Name()); \
            this->_ZFP_propL_onDealloc_##Name(valueNew, valueOld); \
            valueRef = valueNew; \
            valuePointerRef = propertyValue; \
            this->_ZFP_propL_onVerify_##Name(valueRef, valueOld); \
            valuePointerRef = valueRef; \
            this->_ZFP_propL_onAttach_##Name(valueRef, valueOld); \
            toObject()->_ZFP_ZFObject_objectPropertyValueAttach(zfself::_ZFP_Prop##Name(), zffalse); \
            this->_ZFP_propL_onUpdate_##Name(valueRef, valueOld); \
            zfCoreMutexUnlock(); \
            toObject()->_ZFP_ZFObject_objectPropertyValueOnUpdate(zfself::_ZFP_Prop##Name(), &valueOld); \
        }
#define _ZFP_ZFPROPERTY_SETTER_INTERNAL_ASSIGN(AccessType, Type, Name) \
    AccessType: \
        inline void _ZFP_ZFPROPERTY_SETTER_NAME_INTERNAL(Type, Name)(Type const &propertyValue) \
        { \
            zfCoreMutexLock(); \
            Type &valueRef = _ZFP_ZFPROPERTY_VALUE_REF(Name); \
            Type valueOld = valueRef; \
            this->_ZFP_propL_onDetach_##Name(propertyValue, valueOld); \
            toObject()->_ZFP_ZFObject_objectPropertyValueDetach(zfself::_ZFP_Prop##Name()); \
            this->_ZFP_propL_onDealloc_##Name(propertyValue, valueOld); \
            valueRef = propertyValue; \
            this->_ZFP_propL_onVerify_##Name(valueRef, valueOld); \
            this->_ZFP_propL_onAttach_##Name(valueRef, valueOld); \
            toObject()->_ZFP_ZFObject_objectPropertyValueAttach(zfself::_ZFP_Prop##Name(), zffalse); \
            this->_ZFP_propL_onUpdate_##Name(valueRef, valueOld); \
            zfCoreMutexUnlock(); \
            toObject()->_ZFP_ZFObject_objectPropertyValueOnUpdate(zfself::_ZFP_Prop##Name(), &valueOld); \
        }
#define _ZFP_ZFPROPERTY_GETTER_INTERNAL(AccessType, Type, Name) \
    AccessType: \
        inline Type const &_ZFP_ZFPROPERTY_GETTER_NAME_INTERNAL(Type, Name)(void) \
        { \
            zfCoreMutexLocker(); \
            return _ZFP_ZFPROPERTY_VALUE_REF(Name); \
        }

// ============================================================
#define _ZFP_ZFPROPERTY_SETTER(AccessType, Type, Name) \
    AccessType: \
        ZFMETHOD_DECLARE_NO_AUTOREGISTER_1( \
            AccessType, ZFMethodIsVirtual, \
            void, _ZFP_ZFPROPERTY_SETTER_NAME(Type, Name), \
            ZFMP_IN(Type const &, propertyValue)) \
        { \
            _ZFP_PropSetterW_##Name<zfself, \
                    ZFM_CLASS_HAS_MEMBER(_, _ZFP_propSetterC_##Name, zfself) \
                >::action(this, propertyValue); \
        } \
    private: \
        ZFM_CLASS_HAS_MEMBER_DECLARE(_, _ZFP_propSetterC_##Name, void (T::*F)(ZF_IN Type const &)) \
        template<typename T_Owner, int hasCustom> \
        zfclassNotPOD _ZFP_PropSetterW_##Name \
        { \
        public: \
            static inline void action(ZF_IN T_Owner *owner, ZF_IN Type const &propertyValue) \
            { \
                owner->_ZFP_propSetterI_##Name(propertyValue); \
            } \
        }; \
        template<typename T_Owner> \
        zfclassNotPOD _ZFP_PropSetterW_##Name<T_Owner, 1> \
        { \
        public: \
            static inline void action(ZF_IN T_Owner *owner, ZF_IN Type const &propertyValue) \
            { \
                owner->_ZFP_propSetterC_##Name(propertyValue); \
            } \
        }; \
    public: \
        inline void _ZFP_propSetterI_##Name(ZF_IN Type const &propertyValue) \
        { \
            this->_ZFP_ZFPROPERTY_SETTER_NAME_INTERNAL(Type, Name)(propertyValue); \
        }
#define _ZFP_ZFPROPERTY_GETTER(AccessType, Type, Name) \
    AccessType: \
        ZFMETHOD_DECLARE_NO_AUTOREGISTER_0( \
            AccessType, ZFMethodIsVirtual, \
            Type const &, _ZFP_ZFPROPERTY_GETTER_NAME(Type, Name)) \
        { \
            return _ZFP_PropGetterW_##Name<zfself, \
                    ZFM_CLASS_HAS_MEMBER(_, _ZFP_propGetterC_##Name, zfself) \
                >::action(this); \
        } \
    private: \
        ZFM_CLASS_HAS_MEMBER_DECLARE(_, _ZFP_propGetterC_##Name, Type const & (T::*F)(void)) \
        template<typename T_Owner, int hasCustom> \
        zfclassNotPOD _ZFP_PropGetterW_##Name \
        { \
        public: \
            static inline Type const &action(ZF_IN T_Owner *owner) \
            { \
                return owner->_ZFP_propGetterI_##Name(); \
            } \
        }; \
        template<typename T_Owner> \
        zfclassNotPOD _ZFP_PropGetterW_##Name<T_Owner, 1> \
        { \
        public: \
            static inline Type const &action(ZF_IN T_Owner *owner) \
            { \
                return owner->_ZFP_propGetterC_##Name(); \
            } \
        }; \
    public: \
        inline Type const &_ZFP_propGetterI_##Name(void) \
        { \
            return this->_ZFP_ZFPROPERTY_GETTER_NAME_INTERNAL(Type, Name)(); \
        }

// ============================================================
#define _ZFP_ZFPROPERTY_LIFE_CYCLE_WRAPPER(Type, Name, lifeCycleName, constFix) \
    private: \
        ZFM_CLASS_HAS_MEMBER_DECLARE(_, _ZFP_propLAC_##lifeCycleName##_##Name, \
                void (T::*F)( \
                        ZF_IN_OUT zfself::_ZFP_PropAT_##Name constFix(const) &propertyValue, \
                        ZF_IN zfself::_ZFP_PropAT_##Name const &propertyValueOld \
                    ) \
            ) \
        template<typename T_Owner, int hasCustom> \
        zfclassNotPOD _ZFP_PropLAW_##lifeCycleName##_##Name \
        { \
        public: \
            static inline void action( \
                ZF_IN T_Owner *owner, \
                ZF_IN_OUT _ZFP_PropAT_##Name constFix(const) &propertyValue, \
                ZF_IN zfself::_ZFP_PropAT_##Name const &propertyValueOld) \
            { \
            } \
        }; \
        template<typename T_Owner> \
        zfclassNotPOD _ZFP_PropLAW_##lifeCycleName##_##Name<T_Owner, 1> \
        { \
        public: \
            static inline void action( \
                ZF_IN T_Owner *owner, \
                ZF_IN_OUT _ZFP_PropAT_##Name constFix(const) &propertyValue, \
                ZF_IN zfself::_ZFP_PropAT_##Name const &propertyValueOld) \
            { \
                owner->_ZFP_propLAC_##lifeCycleName##_##Name(propertyValue, propertyValueOld); \
            } \
        }; \
    public: \
        virtual inline void _ZFP_propL_##lifeCycleName##_##Name( \
            ZF_IN_OUT _ZFP_PropAT_##Name constFix(const) &propertyValue, \
            ZF_IN zfself::_ZFP_PropAT_##Name const &propertyValueOld) \
        { \
            _ZFP_PropLAW_##lifeCycleName##_##Name<zfself, \
                    ZFM_CLASS_HAS_MEMBER(_, _ZFP_propLAC_##lifeCycleName##_##Name, zfself) \
                >::action(this, propertyValue, propertyValueOld); \
        }

#define _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DECLARE(Type, Name, lifeCycleName, constFix) \
    public: \
        void _ZFP_propLAC_##lifeCycleName##_##Name( \
            ZF_IN_OUT _ZFP_PropAT_##Name constFix(const) &propertyValue, \
            ZF_IN zfself::_ZFP_PropAT_##Name const &propertyValueOld)
#define _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DEFINE(OwnerClass, Type, Name, lifeCycleName, constFix) \
    void OwnerClass::_ZFP_propLAC_##lifeCycleName##_##Name( \
        ZF_IN_OUT _ZFP_PropAT_##Name constFix(const) &propertyValue, \
        ZF_IN zfself::_ZFP_PropAT_##Name const &propertyValueOld)

#define _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, lifeCycleName, constFix) \
    public: \
        virtual void _ZFP_propL_##lifeCycleName##_##Name( \
            ZF_IN_OUT _ZFP_PropAT_##Name constFix(const) &propertyValue, \
            ZF_IN zfself::_ZFP_PropAT_##Name const &propertyValueOld)
#define _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DEFINE(OwnerClass, Type, Name, lifeCycleName, constFix) \
    void OwnerClass::_ZFP_propL_##lifeCycleName##_##Name( \
        ZF_IN_OUT _ZFP_PropAT_##Name constFix(const) &propertyValue, \
        ZF_IN zfself::_ZFP_PropAT_##Name const &propertyValueOld)
#define _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_CALL_SUPER(SuperOwnerClass, Type, Name, lifeCycleName, constFix) \
    SuperOwnerClass::_ZFP_propL_##lifeCycleName##_##Name(propertyValue, propertyValueOld)

// ============================================================
/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPropertyNoInitValue
/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPropertyInitValue(v) v

// ============================================================
/**
 * @brief declare a retain property
 *
 * -  ZFPROPERTY_XXX is similar to \@property in Object-C,
 *   which would automatically generate setter and getter for you\n
 *   here's a list of what they'll generate
 *   (assume property's type is Type and property's name is Name):
 *   -  ZFPROPERTY_RETAIN / ZFPROPERTY_ASSIGN:
 *     -  public:\n
 *       virtual void NameSet(Type const &propertyValue); // (reflectable)\n
 *       virtual Type const &Name(void); // (reflectable)
 *     -  protected:\n
 *       inline void NameSetInternal(Type const &propertyValue);\n
 *       inline Type const &NameInternal(void);
 *   -  for a retain property, Type must be ZFObject or ZFObject's subclass,
 *     and value is set by #ZFPropertyChange
 *   -  for a assign property, Type could be any type except for const type
 * -  ZFProperty support those type only:
 *   -  base type, such as zfcharA, int, const zfcharA *
 *   -  ZFObject *
 *   -  classes that have constructor with no argument and have operator= support
 * -  ZFProperty is also reflectable,
 *   you may reflect the ZFProperty itself by #ZFClass::propertyForName,
 *   or reflect the setter and getter as ZFMethod,
 *   for how to reflect, see #ZFMethod\n
 *   also, similar to ZFMethod, if you want the static binding for ZFProperty,
 *   use ZFPROPERTY_REGISTER,
 *   however, since a property is valid only if a instance has created,
 *   it's not quite necessary to register it
 * -  you may customize the accessibility for getter and setter,
 *   or add default value for setter,
 *   or set your custom setter,
 *   by using ZFPROPERTY_XXX_DETAIL:\n
 *   ZFPROPERTY_RETAIN_DETAIL(
 *       Type, Name, ZFPropertyInitValueOrNoInitValue,
 *       SetterAccessType,
 *       GetterAccessType)\n
 *   the ZFPropertyInitValueOrNoInitValue is the init value for the property,
 *     could be ZFPropertyInitValue(your_value) or ZFPropertyNoInitValue,
 *     if not set, the built-in value would be set,
 *     e.g. zffalse for zfbool, empty string for zfstring
 *     (for retain property, the init value must be auto released object,
 *     use #zfautoObject or #zflineAlloc or #zflineRelease is recommended)\n
 *   the SetterAccessType/GetterAccessType could be
 *     public/protected/private\n
 *   for example:
 *   @code
 *     zfclass OwnerClass : zfextends Base
 *     {
 *         ZFOBJECT_DECLARE(OwnerClass, Base)
 *
 *         ZFPROPERTY_RETAIN_DETAIL(
 *             zfstring, ZFPropertyTypeId_zfstring(), StringProperty, \
 *             ZFPropertyNoInitValue,
 *             public,
 *             public)
 *     };
 *   @endcode
 *   @note for a retain property, it'll be released automatically when it's owner is dealloced
 * -  to override a property in subclass, you should use
 *   #ZFPROPERTY_OVERRIDE_SETTER_DECLARE and/or #ZFPROPERTY_OVERRIDE_GETTER_DECLARE
 *   @code
 *     // OwnerClass.h
 *     zfclass OwnerClass : zfextends Base
 *     {
 *         ...
 *         ZFPROPERTY_OVERRIDE_SETTER_DECLARE(zfcharA, OverridePropertyInHeader)
 *         { // actual setter here, defined in header file
 *             // use zfsuper::XXXSet to set
 *             zfsuper::OverridePropertyInHeaderSet(propertyValue);
 *         }
 *         ZFPROPERTY_OVERRIDE_SETTER_DECLARE(zfcharA, OverridePropertyInCppFile);
 *     };
 *
 *     // OwnerClass.cpp
 *     ZFPROPERTY_OVERRIDE_SETTER_DEFINE(OwnerClass, zfcharA, OverridePropertyInCppFile)
 *     {
 *         // setter that defined in cpp file
 *         OverridePropertyInCppFileSet(propertyValue);
 *     }
 *   @endcode
 *   @warning you must not declare two property with same name in child and base class
 *   @note overrided property won't be included in it's ZFClass,
 *     it's only a method override, no new ZFMethod or ZFProperty would be declared in child class
 *   @warning AccessType and Type for the overrided property must be the same
 *     declared in base class
 *   @warning you should never override a property's getter and setter except by
 *     ZFPROPERTY_OVERRIDE_XXX
 * -  to add Doxygen docs, you should:
 *   @code
 *    / **
 *      * @brief without fn defines, doc for getters only (ie. Name)
 *      *
 *      * setters' docs would be auto generated,
 *      * which is referencing to getters
 *      * /
 *     ZFPROPERTY_RETAIN(Type, Name)
 *   @endcode
 *   or:
 *   @code
 *    / **
 *      * @fn NameSet
 *      * @brief doc for NameSet
 *      * @fn Name
 *      * @brief doc for Name
 *      * /
 *     ZFPROPERTY_RETAIN(Type, Name)
 *   @endcode
 */
#define ZFPROPERTY_RETAIN(Type, Name) \
    ZFPROPERTY_RETAIN_DETAIL( \
        Type, Name, ZFPropertyNoInitValue, \
        public, public)

/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_RETAIN_WITH_INIT(Type, Name, ZFPropertyInitValueOrNoInitValue) \
    ZFPROPERTY_RETAIN_DETAIL( \
        Type, Name, ZFPropertyInitValueOrNoInitValue, \
        public, public)

/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_RETAIN_READONLY(Type, Name, ZFPropertyInitValueOrNoInitValue) \
    ZFPROPERTY_RETAIN_DETAIL( \
        Type, Name, ZFPropertyInitValueOrNoInitValue, \
        private, public)

/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_RETAIN_DETAIL( \
    Type, Name, ZFPropertyInitValueOrNoInitValue, \
    SetterAccessType, GetterAccessType) \
        _ZFP_ZFPROPERTY_GETTER(GetterAccessType, Type, Name) \
        /** @brief internal getter, see @ref Name */ \
        _ZFP_ZFPROPERTY_GETTER_INTERNAL(_ZFP_ZFPROPERTY_INTERNAL_ACCESSTYPE(GetterAccessType), Type, Name) \
        /** @brief see @ref Name */ \
        _ZFP_ZFPROPERTY_SETTER(SetterAccessType, Type, Name) \
        /** @brief internal getter, see @ref Name */ \
        _ZFP_ZFPROPERTY_SETTER_INTERNAL_RETAIN(_ZFP_ZFPROPERTY_INTERNAL_ACCESSTYPE(SetterAccessType), Type, Name) \
        _ZFP_ZFPROPERTY_DECLARE_RETAIN(Type, ZFPropertyTypeId_ZFObject, Name, \
                                       ZFPropertyInitValueOrNoInitValue) \
    public:

/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_RETAIN_NOT_SERIALIZABLE(Type, Name) \
    ZFPROPERTY_RETAIN_NOT_SERIALIZABLE_DETAIL( \
        Type, Name, ZFPropertyNoInitValue, \
        public, public)

/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_RETAIN_NOT_SERIALIZABLE_DETAIL( \
    Type, Name, ZFPropertyInitValueOrNoInitValue, \
    SetterAccessType, GetterAccessType) \
        _ZFP_ZFPROPERTY_GETTER(GetterAccessType, Type, Name) \
        /** @brief internal getter, see @ref Name */ \
        _ZFP_ZFPROPERTY_GETTER_INTERNAL(_ZFP_ZFPROPERTY_INTERNAL_ACCESSTYPE(GetterAccessType), Type, Name) \
        /** @brief see @ref Name */ \
        _ZFP_ZFPROPERTY_SETTER(SetterAccessType, Type, Name) \
        /** @brief internal getter, see @ref Name */ \
        _ZFP_ZFPROPERTY_SETTER_INTERNAL_RETAIN(_ZFP_ZFPROPERTY_INTERNAL_ACCESSTYPE(SetterAccessType), Type, Name) \
        _ZFP_ZFPROPERTY_DECLARE_RETAIN(Type, ZFPropertyTypeId_none, Name, \
                                       ZFPropertyInitValueOrNoInitValue) \
    public:

// ============================================================
/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_ASSIGN(Type, Name) \
    ZFPROPERTY_ASSIGN_DETAIL( \
        Type, Name, ZFPropertyNoInitValue, \
        public, public)

/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_ASSIGN_WITH_INIT(Type, Name, ZFPropertyInitValueOrNoInitValue) \
    ZFPROPERTY_ASSIGN_DETAIL( \
        Type, Name, ZFPropertyInitValueOrNoInitValue, \
        public, public)

/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_ASSIGN_READONLY(Type, Name, ZFPropertyInitValueOrNoInitValue) \
    ZFPROPERTY_ASSIGN_DETAIL( \
        Type, Name, ZFPropertyInitValueOrNoInitValue, \
        private, public)

/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_ASSIGN_DETAIL( \
    Type, Name, ZFPropertyInitValueOrNoInitValue, \
    SetterAccessType, GetterAccessType) \
        _ZFP_ZFPROPERTY_GETTER(GetterAccessType, Type, Name) \
        /** @brief internal getter, see @ref Name */ \
        _ZFP_ZFPROPERTY_GETTER_INTERNAL(_ZFP_ZFPROPERTY_INTERNAL_ACCESSTYPE(GetterAccessType), Type, Name) \
        /** @brief see @ref Name */ \
        _ZFP_ZFPROPERTY_SETTER(SetterAccessType, Type, Name) \
        /** @brief internal setter, see @ref Name */ \
        _ZFP_ZFPROPERTY_SETTER_INTERNAL_ASSIGN(_ZFP_ZFPROPERTY_INTERNAL_ACCESSTYPE(SetterAccessType), Type, Name) \
        _ZFP_ZFPROPERTY_DECLARE_ASSIGN(Type, ZFPropertyTypeIdData<zftTraitsType<Type>::TraitsRemoveReference>::PropertyTypeId(), Name, \
                                       ZFPropertyInitValueOrNoInitValue) \
    public:

/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_ASSIGN_NOT_SERIALIZABLE(Type, Name) \
    ZFPROPERTY_ASSIGN_NOT_SERIALIZABLE_DETAIL( \
        Type, Name, ZFPropertyNoInitValue, \
        public, public)

/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_ASSIGN_NOT_SERIALIZABLE_DETAIL( \
    Type, Name, ZFPropertyInitValueOrNoInitValue, \
    SetterAccessType, GetterAccessType) \
        _ZFP_ZFPROPERTY_GETTER(GetterAccessType, Type, Name) \
        /** @brief internal getter, see @ref Name */ \
        _ZFP_ZFPROPERTY_GETTER_INTERNAL(_ZFP_ZFPROPERTY_INTERNAL_ACCESSTYPE(GetterAccessType), Type, Name) \
        /** @brief see @ref Name */ \
        _ZFP_ZFPROPERTY_SETTER(SetterAccessType, Type, Name) \
        /** @brief internal setter, see @ref Name */ \
        _ZFP_ZFPROPERTY_SETTER_INTERNAL_ASSIGN(_ZFP_ZFPROPERTY_INTERNAL_ACCESSTYPE(SetterAccessType), Type, Name) \
        _ZFP_ZFPROPERTY_DECLARE_ASSIGN(Type, ZFPropertyTypeId_none, Name, \
                                       ZFPropertyInitValueOrNoInitValue) \
    public:

// ============================================================
/**
 * @brief see #ZFPROPERTY_RETAIN
 *
 * statically register a property\n
 * you can find the property in its owner class only if it's registered,
 * which can be achieved by any of these:
 * -  any instance of owner class has ever been created,
 *   by default, #ZFClass would do the registration work for you automatically
 *   if the owner class is not an abstract class
 * -  ZFPROPERTY_REGISTER is declared
 */
#define ZFPROPERTY_REGISTER(OwnerClass, Type, Name) \
    ZF_STATIC_INITIALIZER_INIT(PropR_##OwnerClass##_##Name) \
    { \
        (void)OwnerClass::_ZFP_Prop##Name(); \
    } \
    ZF_STATIC_INITIALIZER_END(PropR_##OwnerClass##_##Name) \
    ZFMETHOD_REGISTER(OwnerClass, _ZFP_ZFPROPERTY_SETTER_NAME(Type, Name)) \
    ZFMETHOD_REGISTER(OwnerClass, _ZFP_ZFPROPERTY_GETTER_NAME(Type, Name))

// ============================================================
/**
 * @brief mark the property should be initialized automatically
 *
 * by default, property's value would be created only when accessed (by setter or getter),
 * for some condition, you may want to ensure the property's value being created,
 * you may use this macro to force it being accessed by getter when owner object created\n
 * the auto init step would be applied after #ZFObject::objectOnInit and before #ZFObject::objectOnInitFinish
 */
#define ZFPROPERTY_MARK_AUTO_INIT(Type, Name) \
    private: \
        zfclassNotPOD _ZFP_PropMAI_##Name \
        { \
        public: \
            _ZFP_PropMAI_##Name(void) \
            { \
                static zfbool needRegister = zftrue; \
                if(needRegister) \
                { \
                    needRegister = zffalse; \
                    zfself::ClassData()->_ZFP_ZFClass_propertyAutoInitRegister(zfself::_ZFP_Prop##Name()); \
                } \
            } \
        }; \
        _ZFP_PropMAI_##Name _ZFP_propMAI_##Name; \
    public:

// ============================================================
/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_CUSTOM_SETTER_DECLARE(Type, Name) \
    public: \
        void _ZFP_propSetterC_##Name(ZF_IN Type const &propertyValue)
/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_CUSTOM_SETTER_DEFINE(OwnerClass, Type, Name) \
    void OwnerClass::_ZFP_propSetterC_##Name(ZF_IN Type const &propertyValue)

/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_CUSTOM_GETTER_DECLARE(Type, Name) \
    public: \
        Type const &_ZFP_propGetterC_##Name(void)
/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_CUSTOM_GETTER_DEFINE(OwnerClass, Type, Name) \
    Type const &OwnerClass::_ZFP_propGetterC_##Name(void)

/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_CUSTOM_INIT_VALUE_CHECKER_DECLARE(Type, Name) \
    public: \
        zfbool _ZFP_propCbIsInitAC_##Name(ZF_OUT_OPT void *outInitValue)
/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_CUSTOM_INIT_VALUE_CHECKER_DEFINE(OwnerClass, Type, Name) \
    zfbool OwnerClass::_ZFP_propCbIsInitAC_##Name(ZF_OUT_OPT void *outInitValue)

/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_CUSTOM_VALUE_COMPARER_DECLARE(Type, Name) \
    public: \
        virtual ZFCompareResult _ZFP_propCbCmpAC_##Name(ZF_IN ZFObject *anotherObj)
/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_CUSTOM_VALUE_COMPARER_DEFINE(OwnerClass, Type, Name) \
    ZFCompareResult OwnerClass::_ZFP_propCbCmpAC_##Name(ZF_IN ZFObject *anotherObj)
/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_CUSTOM_VALUE_COMPARER_REF_VALUE(Type, Name) \
    (ZFCastZFObjectUnchecked(zfself *, anotherObj)->_ZFP_ZFPROPERTY_GETTER_NAME(Type, Name)())

/**
 * @brief declare custom life cycle callback for the property
 *
 * proto type:
 * @code
 *   // for retain property
 *   void propertyOnInit(
 *       ZF_IN_OUT zfautoObject [const] &propertyValue,
 *       ZF_IN zfautoObject const &propertyValueOld);
 *
 *   // for assign property
 *   void propertyOnInit(
 *       ZF_IN_OUT YourPropertyType [const] &propertyValue,
 *       ZF_IN YourPropertyType const &propertyValueOld);
 * @endcode
 *
 * we have these property life cycle events:
 * -  propertyOnInit: called when property first accessed\n
 *   you may change the propertyValue during this step
 *   to modify the property's init value
 * -  propertyOnDealloc: called when owner object deallocated
 *   (after #ZFObject::objectOnDeallocPrepare and before #ZFObject::objectOnDealloc)\n
 *   you may do additional cleanup steps here
 * -  propertyOnVerify: called when setter called\n
 *   you may verify the property value, and modify propertyValue to correct one
 * -  propertyOnAttach: called when property first accessed or setter called\n
 *   you may do additional attach steps here
 * -  propertyOnDetach: called when property setter called or owner object deallocated\n
 *   you may do additional detach steps here
 * -  propertyOnUpdate: called after property first accessed or setter called\n
 *   you may apply your impl accorrding to the property's new value
 *
 *
 * you may use ZFPROPERTY_CUSTOM_ON_XXX to supply custom life cycle callback
 * for property owner class,
 * or use ZFPROPERTY_OVERRIDE_ON_XXX to override for subclass\n
 * when override, make sure not to forget ZFPROPERTY_OVERRIDE_ON_XXX_CALL_SUPER to call super\n
 * \n
 * \n
 * here's a simple hint for the property's life cycle:
 * -  property first time accessed:
 *   -# store raw init value, decalred by #ZFPropertyInitValue
 *   -# propertyOnInit
 *   -# propertyOnAttach
 *   -# propertyOnUpdate
 * -  property's setter called:
 *   -# propertyOnDetach
 *   -# propertyOnDealloc
 *   -# store raw value
 *   -# propertyOnVerify
 *   -# propertyOnAttach
 *   -# #ZFObject::EventObjectPropertyValueOnUpdate
 *   -# propertyOnUpdate
 * -  property's owner object deallocated:
 *   -# propertyOnDetach
 *   -# propertyOnDealloc
 */
#define ZFPROPERTY_CUSTOM_ON_INIT_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DECLARE(Type, Name, onInit, ZFM_EMPTY)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_INIT_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DEFINE(OwnerClass, Type, Name, onInit, ZFM_EMPTY)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_DEALLOC_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DECLARE(Type, Name, onDealloc, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_DEALLOC_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DEFINE(OwnerClass, Type, Name, onDealloc, ZFM_EXPAND)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_VERIFY_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DECLARE(Type, Name, onVerify, ZFM_EMPTY)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_VERIFY_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DEFINE(OwnerClass, Type, Name, onVerify, ZFM_EMPTY)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_ATTACH_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DECLARE(Type, Name, onAttach, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_ATTACH_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DEFINE(OwnerClass, Type, Name, onAttach, ZFM_EXPAND)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_DETACH_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DECLARE(Type, Name, onDetach, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_DETACH_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DEFINE(OwnerClass, Type, Name, onDetach, ZFM_EXPAND)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DECLARE(Type, Name, onUpdate, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DEFINE(OwnerClass, Type, Name, onUpdate, ZFM_EXPAND)

// ============================================================
/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_OVERRIDE_SETTER_DECLARE(AccessType, Type, Name) \
    ZFMETHOD_OVERRIDE_DECLARE_DETAIL_1( \
        AccessType, ZFMethodIsVirtual, \
        void, _ZFP_ZFPROPERTY_SETTER_NAME(Type, Name), \
        ZFMP_IN(Type const &, propertyValue))
/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_OVERRIDE_SETTER_DEFINE(OwnerClass, Type, Name) \
    ZFMETHOD_OVERRIDE_DEFINE_1( \
        OwnerClass, void, _ZFP_ZFPROPERTY_SETTER_NAME(Type, Name), \
        ZFMP_IN(Type const &, propertyValue))
/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_OVERRIDE_SETTER_CALL_SUPER(SuperOwnerClass, Type, Name) \
    SuperOwnerClass::_ZFP_ZFPROPERTY_SETTER_NAME(Type, Name)(propertyValue)

/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_OVERRIDE_GETTER_DECLARE(AccessType, Type, Name) \
    ZFMETHOD_OVERRIDE_DECLARE_DETAIL_0( \
        AccessType, ZFMethodIsVirtual, \
        Type const &, _ZFP_ZFPROPERTY_GETTER_NAME(Type, Name))
/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_OVERRIDE_GETTER_DEFINE(OwnerClass, Type, Name) \
    ZFMETHOD_OVERRIDE_DEFINE_0( \
        OwnerClass, Type const &, _ZFP_ZFPROPERTY_GETTER_NAME(Type, Name))
/** @brief see #ZFPROPERTY_RETAIN */
#define ZFPROPERTY_OVERRIDE_GETTER_CALL_SUPER(SuperOwnerClass, Type, Name) \
    SuperOwnerClass::_ZFP_ZFPROPERTY_GETTER_NAME(Type, Name)()

/**
 * @brief override property's init value checker
 *
 * proto type:\n
 *   zfbool isInitValue(void)
 */
#define ZFPROPERTY_OVERRIDE_INIT_VALUE_CHECKER_DECLARE(Type, Name) \
    public: \
        virtual zfbool _ZFP_propCbIsInitA_##Name(ZF_OUT_OPT void *outInitValue)
/** @brief see #ZFPROPERTY_OVERRIDE_INIT_VALUE_CHECKER_DECLARE */
#define ZFPROPERTY_OVERRIDE_INIT_VALUE_CHECKER_DEFINE(OwnerClass, Type, Name) \
    zfbool OwnerClass::_ZFP_propCbIsInitA_##Name(ZF_OUT_OPT void *outInitValue)
/** @brief see #ZFPROPERTY_OVERRIDE_INIT_VALUE_CHECKER_DECLARE */
#define ZFPROPERTY_OVERRIDE_INIT_VALUE_CHECKER_CALL_SUPER(SuperOwnerClass, Type, Name) \
    SuperOwnerClass::_ZFP_propCbIsInitA_##Name(outInitValue)

/**
 * @brief override property's value comparer
 */
#define ZFPROPERTY_OVERRIDE_VALUE_COMPARER_DECLARE(Type, Name) \
    public: \
        virtual ZFCompareResult _ZFP_propCbCmpA_##Name(ZF_IN ZFObject *anotherObj)
/** @brief see #ZFPROPERTY_OVERRIDE_VALUE_COMPARER_DECLARE */
#define ZFPROPERTY_OVERRIDE_VALUE_COMPARER_DEFINE(OwnerClass, Type, Name) \
    ZFCompareResult OwnerClass::_ZFP_propCbCmpA_##Name(ZF_IN ZFObject *anotherObj)
/** @brief see #ZFPROPERTY_OVERRIDE_VALUE_COMPARER_DECLARE */
#define ZFPROPERTY_OVERRIDE_VALUE_COMPARER_CALL_SUPER(SuperOwnerClass, Type, Name) \
    SuperOwnerClass::_ZFP_propCbCmpA_##Name(anotherObj)
/** @brief see #ZFPROPERTY_OVERRIDE_VALUE_COMPARER_DECLARE */
#define ZFPROPERTY_OVERRIDE_VALUE_COMPARER_REF_VALUE(Type, Name) \
    (ZFCastZFObjectUnchecked(zfself *, anotherObj)->_ZFP_ZFPROPERTY_GETTER_NAME(Type, Name)())

#define _ZFP_ZFPROPERTY_OVERRIDE_ON_INIT_REGISTER(Type, Name) \
    private: \
        zfclassNotPOD _ZFP_ZFPropertyInitStepRegister_##Name \
        { \
        public: \
            _ZFP_ZFPropertyInitStepRegister_##Name(void) \
            { \
                static zfbool needRegister = zftrue; \
                if(needRegister) \
                { \
                    needRegister = zffalse; \
                    zfself::ClassData()->_ZFP_ZFClass_propertyInitStepRegister(zfself::_ZFP_Prop##Name()); \
                } \
            } \
        }; \
        _ZFP_ZFPropertyInitStepRegister_##Name _ZFP_ZFPropertyInitStepRegisterDummy_##Name; \
    public:
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_INIT_DECLARE(Type, Name) \
    ZFPROPERTY_MARK_AUTO_INIT(Type, Name) \
    _ZFP_ZFPROPERTY_OVERRIDE_ON_INIT_REGISTER(Type, Name) \
    _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, onInit, ZFM_EMPTY)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE, #ZFPROPERTY_MARK_AUTO_INIT */
#define ZFPROPERTY_OVERRIDE_ON_INIT_DECLARE_NO_AUTO_INIT(Type, Name) \
    _ZFP_ZFPROPERTY_OVERRIDE_ON_INIT_REGISTER(Type, Name) \
    _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, onInit, ZFM_EMPTY)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_INIT_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DEFINE(OwnerClass, Type, Name, onInit, ZFM_EMPTY)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_INIT_CALL_SUPER(SuperOwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_CALL_SUPER(SuperOwnerClass, Type, Name, onInit, ZFM_EMPTY)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_DEALLOC_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, onDealloc, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_DEALLOC_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DEFINE(OwnerClass, Type, Name, onDealloc, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_DEALLOC_CALL_SUPER(SuperOwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_CALL_SUPER(SuperOwnerClass, Type, Name, onDealloc, ZFM_EXPAND)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_VERIFY_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, onVerify, ZFM_EMPTY)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_VERIFY_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DEFINE(OwnerClass, Type, Name, onVerify, ZFM_EMPTY)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_VERIFY_CALL_SUPER(SuperOwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_CALL_SUPER(SuperOwnerClass, Type, Name, onVerify, ZFM_EMPTY)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_ATTACH_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, onAttach, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_ATTACH_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DEFINE(OwnerClass, Type, Name, onAttach, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_ATTACH_CALL_SUPER(SuperOwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_CALL_SUPER(SuperOwnerClass, Type, Name, onAttach, ZFM_EXPAND)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_DETACH_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, onDetach, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_DETACH_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DEFINE(OwnerClass, Type, Name, onDetach, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_DETACH_CALL_SUPER(SuperOwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_CALL_SUPER(SuperOwnerClass, Type, Name, onDetach, ZFM_EXPAND)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_UPDATE_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, onUpdate, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_UPDATE_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DEFINE(OwnerClass, Type, Name, onUpdate, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_UPDATE_CALL_SUPER(SuperOwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_CALL_SUPER(SuperOwnerClass, Type, Name, onUpdate, ZFM_EXPAND)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFPropertyDeclare_h_

