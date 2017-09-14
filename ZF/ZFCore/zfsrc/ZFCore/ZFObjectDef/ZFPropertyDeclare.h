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
#define ZFPropertyAccess(OwnerClass, Name) ((const ZFProperty *)OwnerClass::_ZFP_Prop_##Name())

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
#define _ZFP_ZFPROPERTY_DECLARE_REGISTER_RETAIN(Type, ZFPropertyTypeId_noneOrType, Name, \
                                                propertyClassOfRetainProperty) \
    public: \
        static ZFProperty *_ZFP_Prop_##Name(void) \
        { \
            static _ZFP_ZFPropertyRegisterHolder _propertyInfoHolder(zffalse \
                    , zfself::ClassData() \
                    , ZFM_TOSTRING(Name) \
                    , ZFM_TOSTRING(Type) \
                    , ZFPropertyTypeId_noneOrType \
                    , ZFMethodAccess(zfself, _ZFP_ZFPROPERTY_SETTER_NAME(Type, Name)) \
                    , ZFMethodAccess(zfself, _ZFP_ZFPROPERTY_GETTER_NAME(Type, Name)) \
                    , propertyClassOfRetainProperty \
                    , &zfself::_ZFP_propCbAccessed_##Name \
                    , &zfself::_ZFP_propCbIsInit_##Name \
                    , &ZFPropertyCallbackCompareDefault<Type> \
                    , &ZFPropertyCallbackCopyDefault<Type> \
                    , &ZFPropertyCallbackRetainSetDefault<Type> \
                    , &ZFPropertyCallbackRetainGetDefault<Type> \
                    , zfnull \
                    , zfnull \
                    , &ZFPropertyCallbackGetInfoDefault<Type> \
                    , zfnull \
                    , zfself::_ZFP_propCbDel_##Name \
                ); \
            return _propertyInfoHolder.propertyInfo; \
        }
#define _ZFP_ZFPROPERTY_DECLARE_REGISTER_ASSIGN(Type, ZFPropertyTypeId_noneOrType, Name, \
                                                propertyClassOfRetainProperty) \
    public: \
        static ZFProperty *_ZFP_Prop_##Name(void) \
        { \
            static _ZFP_ZFPropertyRegisterHolder _propertyInfoHolder(zffalse \
                    , zfself::ClassData() \
                    , ZFM_TOSTRING(Name) \
                    , ZFM_TOSTRING(Type) \
                    , ZFPropertyTypeId_noneOrType \
                    , ZFMethodAccess(zfself, _ZFP_ZFPROPERTY_SETTER_NAME(Type, Name)) \
                    , ZFMethodAccess(zfself, _ZFP_ZFPROPERTY_GETTER_NAME(Type, Name)) \
                    , propertyClassOfRetainProperty \
                    , zfself::_ZFP_propCbAccessed_##Name \
                    , zfself::_ZFP_propCbIsInit_##Name \
                    , &ZFPropertyCallbackCompareDefault<Type> \
                    , &ZFPropertyCallbackCopyDefault<Type> \
                    , zfnull \
                    , zfnull \
                    , &ZFPropertyCallbackAssignSetDefault<Type> \
                    , &ZFPropertyCallbackAssignGetDefault<Type> \
                    , &ZFPropertyCallbackGetInfoDefault<Type> \
                    , zfnull \
                    , zfself::_ZFP_propCbDel_##Name \
                ); \
            return _propertyInfoHolder.propertyInfo; \
        }

#define _ZFP_ZFPROPERTY_VALUE_DECLARE_RETAIN(Type, ZFPropertyTypeId_noneOrType, Name, \
                                             ZFPropertyInitValueOrNoInitValue) \
    public: \
        typedef Type _ZFP_PropVT_##Name; \
        typedef zfautoObject _ZFP_PropHT_##Name; \
    private: \
        zffinal zfclassNotPOD _ZFP_PropV_##Name \
        { \
        public: \
            _ZFP_PropV_##Name(void) \
            : value(zfnull), valueHolder() \
            { \
                zfself::_ZFP_Prop_##Name(); \
            } \
            ~_ZFP_PropV_##Name(void) \
            { \
                zfpoolDelete(this->value); \
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
                    owner->_ZFP_propL_OnInit_##Name(this->valueHolder, this->valueHolder); \
                    *(this->value) = this->valueHolder; \
                    if(needNotifyOwner) \
                    { \
                        const ZFProperty *property = zfself::_ZFP_Prop_##Name(); \
                        ZFObject *obj = owner->toObject(); \
                        owner->_ZFP_propL_OnAttach_##Name(this->valueHolder, this->valueHolder); \
                        obj->_ZFP_ZFObject_objectPropertyValueAttach(property, zftrue); \
                        owner->_ZFP_propL_OnUpdate_##Name(this->valueHolder, this->valueHolder); \
                        obj->_ZFP_ZFObject_objectPropertyValueOnUpdate(property, zfnull); \
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
                owner->_ZFP_propL_OnDetach_##Name(this->valueHolder, this->valueHolder); \
                owner->toObject()->_ZFP_ZFObject_objectPropertyValueDetach(zfself::_ZFP_Prop_##Name(), zffalse); \
                owner->_ZFP_propL_OnDealloc_##Name(this->valueHolder, this->valueHolder); \
                zfpoolDelete(this->value); \
                this->value = zfnull; \
            } \
        private: \
            zfself::_ZFP_PropVT_##Name *value; \
        public: \
            zfself::_ZFP_PropHT_##Name valueHolder; \
        }; \
        zfself::_ZFP_PropV_##Name Name##_PropV; \
    private: \
        static zfbool _ZFP_propCbIsInit_##Name(ZF_IN const ZFProperty *property, \
                                               ZF_IN ZFObject *ownerObj, \
                                               ZF_OUT_OPT void *outInitValue) \
        { \
            zfCoreMutexLocker(); \
            zfself *t = ZFCastZFObjectUnchecked(zfself *, ownerObj); \
            if(t->Name##_PropV.propertyAccessed()) \
            { \
                zfself::_ZFP_PropV_##Name _holder; \
                if(outInitValue != zfnull) \
                { \
                    *(zfself::_ZFP_PropHT_##Name *)outInitValue = zfautoObjectCreateWithoutLeakTest( \
                        ZFCastZFObjectUnchecked(ZFObject *, _holder.propertyInit(t, zffalse))); \
                } \
                return (ZFComparerDefault( \
                        t->_ZFP_ZFPROPERTY_GETTER_NAME(Type, Name)(), _holder.propertyInit(t, zffalse)) \
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
        typedef Type _ZFP_PropHT_##Name; \
    private: \
        zffinal zfclassNotPOD _ZFP_PropV_##Name \
        { \
        public: \
            _ZFP_PropV_##Name(void) \
            : value(zfnull) \
            { \
                zfself::_ZFP_Prop_##Name(); \
            } \
            ~_ZFP_PropV_##Name(void) \
            { \
                zfpoolDelete(this->value); \
            } \
        public: \
            zfself::_ZFP_PropVT_##Name &propertyInit(ZF_IN zfself *owner, \
                                                     ZF_IN_OPT zfbool needNotifyOwner = zftrue) \
            { \
                if(!(this->value)) \
                { \
                    this->value = zfpoolNew(zfself::_ZFP_PropVT_##Name, ZFPropertyInitValueOrNoInitValue); \
                    owner->_ZFP_propL_OnInit_##Name(*(this->value), *(this->value)); \
                    if(needNotifyOwner) \
                    { \
                        const ZFProperty *property = zfself::_ZFP_Prop_##Name(); \
                        ZFObject *obj = owner->toObject(); \
                        owner->_ZFP_propL_OnAttach_##Name(*(this->value), *(this->value)); \
                        obj->_ZFP_ZFObject_objectPropertyValueAttach(property, zftrue); \
                        owner->_ZFP_propL_OnUpdate_##Name(*(this->value), *(this->value)); \
                        obj->_ZFP_ZFObject_objectPropertyValueOnUpdate(property, zfnull); \
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
                owner->_ZFP_propL_OnDetach_##Name(*(this->value), *(this->value)); \
                owner->toObject()->_ZFP_ZFObject_objectPropertyValueDetach(zfself::_ZFP_Prop_##Name(), zffalse); \
                owner->_ZFP_propL_OnDealloc_##Name(*(this->value), *(this->value)); \
                zfpoolDelete(this->value); \
                this->value = zfnull; \
            } \
        private: \
            zfself::_ZFP_PropVT_##Name *value; \
        }; \
        zfself::_ZFP_PropV_##Name Name##_PropV; \
    private: \
        static zfbool _ZFP_propCbIsInit_##Name(ZF_IN const ZFProperty *property, \
                                               ZF_IN ZFObject *ownerObj, \
                                               ZF_OUT_OPT void *outInitValue) \
        { \
            zfCoreMutexLocker(); \
            zfself *t = ZFCastZFObjectUnchecked(zfself *, ownerObj); \
            if(t->Name##_PropV.propertyAccessed()) \
            { \
                zfself::_ZFP_PropV_##Name _holder; \
                if(outInitValue != zfnull) \
                { \
                    *(zfself::_ZFP_PropHT_##Name *)outInitValue = _holder.propertyInit(t, zffalse); \
                } \
                return (ZFComparerDefault( \
                        t->_ZFP_ZFPROPERTY_GETTER_NAME(Type, Name)(), _holder.propertyInit(t, zffalse)) \
                    == ZFCompareTheSame); \
            } \
            else \
            { \
                return zftrue; \
            } \
        } \
    public:

// ============================================================
#define _ZFP_ZFPROPERTY_DECLARE_CALLBACK(Type, Name) \
    private: \
        static zfbool _ZFP_propCbAccessed_##Name(ZF_IN const ZFProperty *property, \
                                                 ZF_IN ZFObject *ownerObj) \
        { \
            return ZFCastZFObjectUnchecked(zfself *, ownerObj)->Name##_PropV.propertyAccessed(); \
        } \
    private: \
        static void _ZFP_propCbDel_##Name(ZF_IN ZFObject *owner, ZF_IN const ZFProperty *property) \
        { \
            zfCoreMutexLocker(); \
            zfself *t = ZFCastZFObjectUnchecked(zfself *, owner); \
            t->Name##_PropV.propertyDealloc(t); \
        } \
    public:
#define _ZFP_ZFPROPERTY_LIFE_CYCLE_EVENTS(Type, Name) \
    private: \
        _ZFP_ZFPROPERTY_LIFE_CYCLE_WRAPPER(Type, Name, OnInit, ZFM_EMPTY) \
        _ZFP_ZFPROPERTY_LIFE_CYCLE_WRAPPER(Type, Name, OnDealloc, ZFM_EXPAND) \
        _ZFP_ZFPROPERTY_LIFE_CYCLE_WRAPPER(Type, Name, OnVerify, ZFM_EMPTY) \
        _ZFP_ZFPROPERTY_LIFE_CYCLE_WRAPPER(Type, Name, OnAttach, ZFM_EXPAND) \
        _ZFP_ZFPROPERTY_LIFE_CYCLE_WRAPPER(Type, Name, OnDetach, ZFM_EXPAND) \
        _ZFP_ZFPROPERTY_LIFE_CYCLE_WRAPPER(Type, Name, OnUpdate, ZFM_EXPAND) \
    public:

// ============================================================
#define _ZFP_ZFPROPERTY_DECLARE_RETAIN(Type, ZFPropertyTypeId_noneOrType, Name, \
                                       ZFPropertyInitValueOrNoInitValue) \
    _ZFP_ZFPROPERTY_DECLARE_REGISTER_RETAIN(Type, ZFPropertyTypeId_noneOrType, Name, \
                                            zftTraits<Type>::TrType::ClassData()) \
    _ZFP_ZFPROPERTY_VALUE_DECLARE_RETAIN(Type, ZFPropertyTypeId_noneOrType, Name, \
                                         ZFPropertyInitValueOrNoInitValue) \
    _ZFP_ZFPROPERTY_DECLARE_CALLBACK(Type, Name) \
    _ZFP_ZFPROPERTY_LIFE_CYCLE_EVENTS(Type, Name)
#define _ZFP_ZFPROPERTY_DECLARE_ASSIGN(Type, ZFPropertyTypeId_noneOrType, Name, \
                                       ZFPropertyInitValueOrNoInitValue) \
    _ZFP_ZFPROPERTY_DECLARE_REGISTER_ASSIGN(Type, ZFPropertyTypeId_noneOrType, Name, \
                                            zfnull) \
    _ZFP_ZFPROPERTY_VALUE_DECLARE_ASSIGN(Type, ZFPropertyTypeId_noneOrType, Name, \
                                         ZFPropertyInitValueOrNoInitValue) \
    _ZFP_ZFPROPERTY_DECLARE_CALLBACK(Type, Name) \
    _ZFP_ZFPROPERTY_LIFE_CYCLE_EVENTS(Type, Name)

// ============================================================
#define _ZFP_ZFPROPERTY_SETTER_NAME(Type, Name) Name##Set
#define _ZFP_ZFPROPERTY_GETTER_NAME(Type, Name) Name

// ============================================================
#define _ZFP_ZFPROPERTY_SETTER_RETAIN(AccessType, Type, Name) \
    AccessType: \
        ZFMETHOD_DECLARE_NO_AUTOREG_1( \
            AccessType, ZFMethodIsVirtual, \
            void, _ZFP_ZFPROPERTY_SETTER_NAME(Type, Name), \
            ZFMP_IN(Type const &, propertyValue)) \
        { \
            zfCoreMutexLock(); \
            const ZFProperty *property = zfself::_ZFP_Prop_##Name(); \
            ZFObject *obj = this->toObject(); \
            zfbool accessed = Name##_PropV.propertyAccessed(); \
            Type &valuePointerRef = Name##_PropV.propertyInit(this, zffalse); \
            zfself::_ZFP_PropHT_##Name &valueRef = this->Name##_PropV.valueHolder; \
            zfself::_ZFP_PropHT_##Name valueOld = valueRef; \
            zfself::_ZFP_PropHT_##Name valueNew = zflockfree_zfautoObjectCreate(ZFObjectToObject(propertyValue)); \
            if(accessed) \
            { \
                this->_ZFP_propL_OnDetach_##Name(valueNew, valueOld); \
                obj->_ZFP_ZFObject_objectPropertyValueDetach(property, zffalse); \
                this->_ZFP_propL_OnDealloc_##Name(valueNew, valueOld); \
            } \
            valueRef = valueNew; \
            valuePointerRef = propertyValue; \
            this->_ZFP_propL_OnVerify_##Name(valueRef, valueOld); \
            valuePointerRef = valueRef; \
            this->_ZFP_propL_OnAttach_##Name(valueRef, valueOld); \
            obj->_ZFP_ZFObject_objectPropertyValueAttach(property, zffalse); \
            this->_ZFP_propL_OnUpdate_##Name(valueRef, valueOld); \
            zfCoreMutexUnlock(); \
            obj->_ZFP_ZFObject_objectPropertyValueOnUpdate(property, &valueOld); \
        } \
    public:
#define _ZFP_ZFPROPERTY_SETTER_ASSIGN(AccessType, Type, Name) \
    AccessType: \
        ZFMETHOD_DECLARE_NO_AUTOREG_1( \
            AccessType, ZFMethodIsVirtual, \
            void, _ZFP_ZFPROPERTY_SETTER_NAME(Type, Name), \
            ZFMP_IN(Type const &, propertyValue)) \
        { \
            zfCoreMutexLock(); \
            const ZFProperty *property = zfself::_ZFP_Prop_##Name(); \
            ZFObject *obj = this->toObject(); \
            zfbool accessed = Name##_PropV.propertyAccessed(); \
            Type &valueRef = Name##_PropV.propertyInit(this, zffalse); \
            Type valueOld = valueRef; \
            if(accessed) \
            { \
                this->_ZFP_propL_OnDetach_##Name(propertyValue, valueOld); \
                obj->_ZFP_ZFObject_objectPropertyValueDetach(property, zffalse); \
                this->_ZFP_propL_OnDealloc_##Name(propertyValue, valueOld); \
            } \
            valueRef = propertyValue; \
            this->_ZFP_propL_OnVerify_##Name(valueRef, valueOld); \
            this->_ZFP_propL_OnAttach_##Name(valueRef, valueOld); \
            obj->_ZFP_ZFObject_objectPropertyValueAttach(property, zffalse); \
            this->_ZFP_propL_OnUpdate_##Name(valueRef, valueOld); \
            zfCoreMutexUnlock(); \
            obj->_ZFP_ZFObject_objectPropertyValueOnUpdate(property, &valueOld); \
        } \
    public:
#define _ZFP_ZFPROPERTY_GETTER(AccessType, Type, Name) \
    AccessType: \
        ZFMETHOD_DECLARE_NO_AUTOREG_0( \
            AccessType, ZFMethodIsVirtual, \
            Type const &, _ZFP_ZFPROPERTY_GETTER_NAME(Type, Name)) \
        { \
            zfCoreMutexLocker(); \
            return Name##_PropV.propertyInit(this); \
        } \
    public:

// ============================================================
#define _ZFP_ZFPROPERTY_LIFE_CYCLE_WRAPPER(Type, Name, lifeCycleName, constFix) \
    protected: \
        virtual void _ZFP_propL_##lifeCycleName##_##Name( \
            ZF_IN zfself::_ZFP_PropHT_##Name constFix(const) &propertyValue, \
            ZF_IN zfself::_ZFP_PropHT_##Name const &propertyValueOld) \
        { \
            const ZFProperty *property = zfself::_ZFP_Prop_##Name(); \
            if(property->_ZFP_ZFProperty_cbCustom##lifeCycleName) \
            { \
                return (this->*( \
                        (void (zfself::*)(ZF_IN zfself::_ZFP_PropHT_##Name constFix(const) &, ZF_IN zfself::_ZFP_PropHT_##Name const &)) \
                        property->_ZFP_ZFProperty_cbCustom##lifeCycleName \
                    ))(propertyValue, propertyValueOld); \
            } \
        } \
    public:
#define _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DECLARE(Type, Name, lifeCycleName, constFix) \
    private: \
        zfclassNotPOD _ZFP_propLReg_##lifeCycleName##_##Name \
        { \
        public: \
            _ZFP_propLReg_##lifeCycleName##_##Name(void) \
            { \
                zfself::_ZFP_Prop_##Name()->_ZFP_ZFProperty_cbCustom##lifeCycleName = \
                    (ZFMemberFuncAddrType)&zfself::_ZFP_propLC_##lifeCycleName##_##Name; \
            } \
        }; \
        _ZFP_propLReg_##lifeCycleName##_##Name _ZFP_propLRegH_##lifeCycleName##_##Name; \
    public: \
        zffinal void _ZFP_propLC_##lifeCycleName##_##Name( \
            ZF_IN zfself::_ZFP_PropHT_##Name constFix(const) &propertyValue, \
            ZF_IN zfself::_ZFP_PropHT_##Name const &propertyValueOld)
#define _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DEFINE(OwnerClass, Type, Name, lifeCycleName, constFix) \
    void OwnerClass::_ZFP_propLC_##lifeCycleName##_##Name( \
        ZF_IN zfself::_ZFP_PropHT_##Name constFix(const) &propertyValue, \
        ZF_IN zfself::_ZFP_PropHT_##Name const &propertyValueOld)

#define _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, lifeCycleName, constFix) \
    public: \
        virtual void _ZFP_propL_##lifeCycleName##_##Name( \
            ZF_IN zfself::_ZFP_PropHT_##Name constFix(const) &propertyValue, \
            ZF_IN zfself::_ZFP_PropHT_##Name const &propertyValueOld)
#define _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DEFINE(OwnerClass, Type, Name, lifeCycleName, constFix) \
    void OwnerClass::_ZFP_propL_##lifeCycleName##_##Name( \
        ZF_IN zfself::_ZFP_PropHT_##Name constFix(const) &propertyValue, \
        ZF_IN zfself::_ZFP_PropHT_##Name const &propertyValueOld)
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
 * -  to override a property in subclass, you may use ZFPROPERTY_OVERRIDE_ON_XXX
 *   @warning you must not declare two property with same name in child and base class
 *   @note overrided property won't be included in it's ZFClass,
 *     it's only a method override, no new ZFMethod or ZFProperty would be declared in child class
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
        /** @brief see @ref Name */ \
        _ZFP_ZFPROPERTY_SETTER_RETAIN(SetterAccessType, Type, Name) \
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
        /** @brief see @ref Name */ \
        _ZFP_ZFPROPERTY_SETTER_RETAIN(SetterAccessType, Type, Name) \
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
        /** @brief see @ref Name */ \
        _ZFP_ZFPROPERTY_SETTER_ASSIGN(SetterAccessType, Type, Name) \
        _ZFP_ZFPROPERTY_DECLARE_ASSIGN(Type, ZFPropertyTypeIdData<zftTraits<Type>::TrNoRef>::PropertyTypeId(), Name, \
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
        /** @brief see @ref Name */ \
        _ZFP_ZFPROPERTY_SETTER_ASSIGN(SetterAccessType, Type, Name) \
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
    ZF_STATIC_REGISTER_INIT(PropR_##OwnerClass##_##Name) \
    { \
        (void)OwnerClass::_ZFP_Prop_##Name(); \
    } \
    ZF_STATIC_REGISTER_END(PropR_##OwnerClass##_##Name) \
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
                    zfself::ClassData()->_ZFP_ZFClass_propertyAutoInitRegister(zfself::_ZFP_Prop_##Name()); \
                } \
            } \
        }; \
        _ZFP_PropMAI_##Name _ZFP_propMAI_##Name; \
    public:

// ============================================================
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
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DECLARE(Type, Name, OnInit, ZFM_EMPTY)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_INIT_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DEFINE(OwnerClass, Type, Name, OnInit, ZFM_EMPTY)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_DEALLOC_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DECLARE(Type, Name, OnDealloc, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_DEALLOC_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DEFINE(OwnerClass, Type, Name, OnDealloc, ZFM_EXPAND)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_VERIFY_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DECLARE(Type, Name, OnVerify, ZFM_EMPTY)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_VERIFY_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DEFINE(OwnerClass, Type, Name, OnVerify, ZFM_EMPTY)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_ATTACH_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DECLARE(Type, Name, OnAttach, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_ATTACH_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DEFINE(OwnerClass, Type, Name, OnAttach, ZFM_EXPAND)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_DETACH_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DECLARE(Type, Name, OnDetach, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_DETACH_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DEFINE(OwnerClass, Type, Name, OnDetach, ZFM_EXPAND)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DECLARE(Type, Name, OnUpdate, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_CUSTOM_DEFINE(OwnerClass, Type, Name, OnUpdate, ZFM_EXPAND)

// ============================================================
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
                    zfself::ClassData()->_ZFP_ZFClass_propertyInitStepRegister(zfself::_ZFP_Prop_##Name()); \
                } \
            } \
        }; \
        _ZFP_ZFPropertyInitStepRegister_##Name _ZFP_ZFPropertyInitStepRegisterDummy_##Name; \
    public:
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_INIT_DECLARE(Type, Name) \
    ZFPROPERTY_MARK_AUTO_INIT(Type, Name) \
    _ZFP_ZFPROPERTY_OVERRIDE_ON_INIT_REGISTER(Type, Name) \
    _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, OnInit, ZFM_EMPTY)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE, #ZFPROPERTY_MARK_AUTO_INIT */
#define ZFPROPERTY_OVERRIDE_ON_INIT_DECLARE_NO_AUTO_INIT(Type, Name) \
    _ZFP_ZFPROPERTY_OVERRIDE_ON_INIT_REGISTER(Type, Name) \
    _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, OnInit, ZFM_EMPTY)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_INIT_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DEFINE(OwnerClass, Type, Name, OnInit, ZFM_EMPTY)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_INIT_CALL_SUPER(SuperOwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_CALL_SUPER(SuperOwnerClass, Type, Name, OnInit, ZFM_EMPTY)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_DEALLOC_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, OnDealloc, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_DEALLOC_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DEFINE(OwnerClass, Type, Name, OnDealloc, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_DEALLOC_CALL_SUPER(SuperOwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_CALL_SUPER(SuperOwnerClass, Type, Name, OnDealloc, ZFM_EXPAND)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_VERIFY_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, OnVerify, ZFM_EMPTY)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_VERIFY_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DEFINE(OwnerClass, Type, Name, OnVerify, ZFM_EMPTY)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_VERIFY_CALL_SUPER(SuperOwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_CALL_SUPER(SuperOwnerClass, Type, Name, OnVerify, ZFM_EMPTY)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_ATTACH_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, OnAttach, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_ATTACH_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DEFINE(OwnerClass, Type, Name, OnAttach, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_ATTACH_CALL_SUPER(SuperOwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_CALL_SUPER(SuperOwnerClass, Type, Name, OnAttach, ZFM_EXPAND)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_DETACH_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, OnDetach, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_DETACH_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DEFINE(OwnerClass, Type, Name, OnDetach, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_DETACH_CALL_SUPER(SuperOwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_CALL_SUPER(SuperOwnerClass, Type, Name, OnDetach, ZFM_EXPAND)

/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_UPDATE_DECLARE(Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DECLARE(Type, Name, OnUpdate, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_UPDATE_DEFINE(OwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_DEFINE(OwnerClass, Type, Name, OnUpdate, ZFM_EXPAND)
/** @brief see #ZFPROPERTY_CUSTOM_ON_INIT_DECLARE */
#define ZFPROPERTY_OVERRIDE_ON_UPDATE_CALL_SUPER(SuperOwnerClass, Type, Name) \
     _ZFP_ZFPROPERTY_LIFE_CYCLE_OVERRIDE_CALL_SUPER(SuperOwnerClass, Type, Name, OnUpdate, ZFM_EXPAND)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFPropertyDeclare_h_

