/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFEnum.h
 * @brief enum utility
 */

#ifndef _ZFI_ZFEnum_h_
#define _ZFI_ZFEnum_h_

#include "ZFSerializable.h"
#include "ZFCopyable.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief invalid value for ZFEnum
 */
#define ZFEnumInvalid() ((zfuint)-1)
/**
 * @brief invalid value's name for ZFEnum
 */
#define ZFEnumNameInvalid() zfText("ZFEnumInvalid")

// ============================================================
/**
 * @brief abstract base class of all enum type of ZFFramework
 *
 * please refer to #ZFENUM_BEGIN to see how to use enum type\n
 * \n
 * serializable data:
 * @code
 *   <EnumClass
 *       value="EmunValueName" // optional, #ZFEnumNameInvalid by default
 *   />
 * @endcode
 */
zfabstract ZF_ENV_EXPORT ZFEnum : zfextends ZFObject, zfimplements ZFSerializable, zfimplements ZFCopyable
{
    ZFOBJECT_DECLARE_ABSTRACT(ZFEnum, ZFObject)
    ZFIMPLEMENTS_DECLARE(ZFSerializable, ZFCopyable)

protected:
    zfoverride
    virtual zfbool serializableOnSerializeFromData(ZF_IN const ZFSerializableData &serializableData,
                                                   ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                   ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull);
    zfoverride
    virtual zfbool serializableOnSerializeToData(ZF_IN_OUT ZFSerializableData &serializableData,
                                                 ZF_IN ZFSerializable *referencedOwnerOrNull,
                                                 ZF_OUT_OPT zfstring *outErrorHint = zfnull);

protected:
    zfoverride
    virtual void copyableOnCopyFrom(ZF_IN ZFObject *anotherObj)
    {
        zfsuperI(ZFCopyable)::copyableOnCopyFrom(anotherObj);
        this->enumValueSet(ZFCastZFObjectUnchecked(zfself *, anotherObj)->enumValue());
    }

public:
    /**
     * @brief init with value or ZFEnumInvalid if invalid
     */
    virtual ZFObject *objectOnInit(ZF_IN zfuint value);
    /**
     * @brief init with ZFEnum
     */
    virtual ZFObject *objectOnInit(ZF_IN ZFEnum *another);
public:
    zfoverride
    virtual ZFObject *objectOnInit(void);
    zfoverride
    virtual void objectOnDealloc(void);

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
    virtual void objectInfoOnAppend(ZF_IN_OUT zfstring &ret);

public:
    /**
     * @brief compare result of two enum values as int,
     *   or return ZFCompareUncomparable if any of them are ZFEnumInvalid
     */
    zfoverride
    virtual ZFCompareResult objectCompare(ZF_IN ZFObject *anotherObj);

public:
    /**
     * @brief get value num
     */
    virtual zfindex enumCount(void) zfpurevirtual;
    /**
     * @brief get the index of enum value, or zfindexMax if no such enum value
     */
    virtual zfindex enumIndexForValue(ZF_IN zfuint value) zfpurevirtual;
    /**
     * @brief get the value at index, or ZFEnumInvalid if not exist
     */
    virtual zfuint enumValueAtIndex(ZF_IN zfindex index) zfpurevirtual;
    /**
     * @brief get the name at index, or ZFEnumNameInvalid if not exist
     */
    virtual const zfchar *enumNameAtIndex(ZF_IN zfindex index) zfpurevirtual;
    /**
    * @brief get the full name (EnumType::EnumValueName) at index, or ZFEnumNameInvalid if not exist
     */
    virtual const zfchar *enumFullNameAtIndex(ZF_IN zfindex index) zfpurevirtual;
    /**
     * @brief return true if contain the specified value
     */
    virtual zfbool enumContainValue(ZF_IN zfuint value) zfpurevirtual;

    /**
     * @brief get the value with specified name, or ZFEnumInvalid if not exist
     */
    virtual zfuint enumValueForName(ZF_IN const zfchar *name) zfpurevirtual;
    /**
     * @brief get the name with specified value, or ZFEnumNameInvalid if not exist
     */
    virtual const zfchar *enumNameForValue(ZF_IN zfuint value) zfpurevirtual;

    /**
     * @brief get the enum value, or #ZFEnumInvalid if invalid
     */
    virtual zfuint enumValue(void)
    {
        return _ZFP_ZFEnum_value;
    }
    /**
     * @brief get the enum value and cast to desired type,
     *   you must ensure it's not #ZFEnumInvalid
     */
    template<typename T_EnumType>
    inline T_EnumType enumValue(void)
    {
        return ZFCastStatic(T_EnumType, _ZFP_ZFEnum_value);
    }
    /**
     * @brief get current value's name, or ZFEnumNameInvalid if invalid
     */
    virtual const zfchar *enumName(void)
    {
        return this->enumNameForValue(_ZFP_ZFEnum_value);
    }

protected:
    /**
     * @brief set the enum value
     *
     * must be the enum's value or ZFEnumInvalid
     */
    virtual void enumValueSet(ZF_IN zfuint value)
    {
        if(!this->enumContainValue(value))
        {
            _ZFP_ZFEnum_value = ZFEnumInvalid();
            return ;
        }
        _ZFP_ZFEnum_value = value;
    }
public:
    void _ZFP_ZFEnum_enumValueSet(ZF_IN zfuint value)
    {
        this->enumValueSet(value);
    }

private:
    zfuint _ZFP_ZFEnum_value;
};

// ============================================================
zfclassFwd _ZFP_ZFEnumDataPrivate;
zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFEnumData
{
public:
    _ZFP_ZFEnumData(void);
    ~_ZFP_ZFEnumData(void);
public:
    zfbool needInitFlag;
    const ZFClass *ownerClass;
    void add(ZF_IN zfbool isEnableDuplicateValue,
             ZF_IN zfuint value,
             ZF_IN const zfchar *name);
    zfindex enumCount(void) const;
    zfindex enumIndexForValue(ZF_IN zfuint value) const;
    zfuint enumValueAtIndex(ZF_IN zfindex index) const;
    const zfchar *enumNameAtIndex(ZF_IN zfindex index) const;
    const zfchar *enumFullNameAtIndex(ZF_IN zfindex index) const;
    zfbool enumContainValue(ZF_IN zfuint value) const;
    zfuint enumValueForName(ZF_IN const zfchar *name) const;
    const zfchar *enumNameForValue(ZF_IN zfuint value) const;
private:
    _ZFP_ZFEnumDataPrivate *d;
};
extern ZF_ENV_EXPORT _ZFP_ZFEnumData *_ZFP_ZFEnumDataAccess(ZF_IN const ZFClass *ownerClass);

// ============================================================
/**
 * @brief macros to define a key-value map for enum type
 *
 * usage:
 * @code
 *   // ============================================================
 *   // in h file
 *  / **
 *    * you can add Doxygen docs for EnumName (as a ZFObject) here
 *    * /
 *   ZFENUM_BEGIN(EnumName)
 *      / **
 *        * you can add Doxygen docs for Value1 here
 *        * /
 *       ZFENUM_VALUE(Value1)
 *       ZFENUM_VALUE(Value2) // /< you can add Doxygen docs for Value2 here
 *       ZFENUM_VALUE_WITH_INIT(Value3, 33) // you can assign the value for enum item
 *       ZFENUM_VALUE_WITH_INIT(Value4, e_Value2) // you can assign a same value with old value
 *   ZFENUM_SEPARATOR(EnumName)
 *       // you must use ZFENUM_VALUE_REGISTER to map the value and name
 *       ZFENUM_VALUE_REGISTER(Value1)
 *       ZFENUM_VALUE_REGISTER(Value2)
 *       // you can set a custom name by ZFENUM_VALUE_REGISTER_WITH_NAME
 *       ZFENUM_VALUE_REGISTER_WITH_NAME(Value3, zfText("CustomNameValue3"))
 *       // (here Value4 is equal to Value2)
 *       // when register a new name for a existing value,
 *       // old name would be overrided,
 *       // as well as the value-name map
 *       ZFENUM_VALUE_REGISTER_WITH_NAME(Value4, zfText("Value4 override Value2"))
 *   ZFENUM_END(EnumName)
 *
 *   // ============================================================
 *   // in cpp file
 *   // add this macro for necessary code expansion
 *   ZFENUM_DEFINE(EnumName)
 * @endcode
 * @note if there are more than one enum with same value,
 *   only the last registered one would be mapped
 * once defined, you can:
 * -  use EnumName to access the enum value and name
 *   @code
 *     zfuint value;
 *     const zfchar *name;
 *     value = EnumName::e_Value1;
 *     value = EnumName::EnumValueForName(zfText("Value1"));
 *     name = EnumName::EnumNameForValue(value);
 *   @endcode
 * -  use EnumName to store the enum value as a ZFObject
 *   @code
 *     EnumName *e = zfAlloc(EnumName());
 *     e->enumValueSet(EnumName::e_Value1);
 *     zfuint value = e->enumValue();
 *     const zfchar *name = e->enumName();
 *     zfRelease(e);
 *   @endcode
 * -  use base class ZFEnum to achieve dynamic binding
 *   @code
 *     zfuint value;
 *     const zfchar *name;
 *
 *     ZFEnum *e = zfAlloc(EnumName, EnumName::e_Value1);
 *     value = e->enumValue(); // return the value stored as EnumName
 *     zfRelease(e);
 *
 *     zfautoObject tmp = ZFClass::newInstanceForName(zfText("EnumName")); // see #ZFOBJECT_REGISTER for more info
 *     e = tmp.to<ZFEnum *>();
 *     for(zfindex i = 0; i < e->enumCount(); ++i)
 *     { // OK, list all the value and name for e, which is EnumName type
 *         value = e->enumValueAtIndex(i);
 *         name = e->enumNameAtIndex(i);
 *     }
 *     value = e->enumValueForName(zfText("Value1")); // OK, value from EnumName
 *     name = e->enumNameForValue(value); // OK, name from EnumName
 *     zfRelease(e);
 *   @endcode
 * -  you can access the internal enum type by EnumNameEnum
 * -  usually, it's highly recommended to use the internal enum type for performance:
 *   @code
 *     // pass by EnumNameEnum value, which is actually a int value
 *     void func1(MyEnumEnum e) {...}
 *   @endcode
 */
#define ZFENUM_BEGIN(ChildEnum) \
    zfclass ZF_ENV_EXPORT ChildEnum : zfextends ZFEnum \
    { \
        ZFOBJECT_DECLARE(ChildEnum, ZFEnum) \
    public: \
        /** @brief see @ref ChildEnum */ \
        typedef enum \
        {
/**
 * @brief see #ZFENUM_BEGIN
 */
#define ZFENUM_VALUE(Value) /** \n */ e_##Value,
/**
 * @brief see #ZFENUM_BEGIN
 */
#define ZFENUM_VALUE_WITH_INIT(Value, initValue) /** @brief \n Value(initValue)\n */ e_##Value = initValue,
#define _ZFP_ZFENUM_SEPARATOR(ChildEnum, isEnableDuplicateValue_) \
        } ZFEnumType; \
    public: \
        /** @brief calculate hash for value */ \
        static zfidentity hashForValue(ZF_IN zfuint value) \
        { \
            return zfidentityHash( \
                zfidentityCalcString(zfself::ClassData()->className()), \
                zfidentityCalcString(zfself::EnumNameForValue(value))); \
        } \
        /** @brief see #ZFObject::objectHash */ \
        virtual zfidentity objectHash(void) \
        { \
            return zfself::hashForValue(this->enumValue()); \
        } \
    public: \
        /** @brief get the count of enum value */ \
        static zfindex EnumCount(void) \
        { \
            return zfself::_ZFP_ZFEnumDataRef()->enumCount(); \
        } \
        /** @brief get the index of enum value, or zfindexMax if no such enum value */ \
        static zfindex EnumIndexForValue(ZF_IN zfuint value) \
        { \
            return zfself::_ZFP_ZFEnumDataRef()->enumIndexForValue(value); \
        } \
        /** @brief get the value at index, or ZFEnumInvalid if not exist */ \
        static zfuint EnumValueAtIndex(ZF_IN zfindex index) \
        { \
            return zfself::_ZFP_ZFEnumDataRef()->enumValueAtIndex(index); \
        } \
        /** @brief get the name at index, or ZFEnumNameInvalid if not exist */ \
        static const zfchar *EnumNameAtIndex(ZF_IN zfindex index) \
        { \
            return zfself::_ZFP_ZFEnumDataRef()->enumNameAtIndex(index); \
        } \
        /** @brief get the name at index, or ZFEnumNameInvalid if not exist */ \
        static const zfchar *EnumFullNameAtIndex(ZF_IN zfindex index) \
        { \
            return zfself::_ZFP_ZFEnumDataRef()->enumFullNameAtIndex(index); \
        } \
        /** @brief return true if contain the specified value */ \
        static zfbool EnumContainValue(ZF_IN zfuint value) \
        { \
            return zfself::_ZFP_ZFEnumDataRef()->enumContainValue(value); \
        } \
        /** @brief get value with name, or ZFEnumInvalid if not exist */ \
        static zfuint EnumValueForName(ZF_IN const zfchar *name) \
        { \
            return zfself::_ZFP_ZFEnumDataRef()->enumValueForName(name); \
        } \
        /** @brief get name with value, or ZFEnumNameInvalid if not exist */ \
        static const zfchar *EnumNameForValue(ZF_IN zfuint value) \
        { \
            return zfself::_ZFP_ZFEnumDataRef()->enumNameForValue(value); \
        } \
    public: \
        zfoverride \
        virtual zfindex enumCount(void) \
        { \
            return zfself::EnumCount(); \
        } \
        zfoverride \
        virtual zfindex enumIndexForValue(ZF_IN zfuint value) \
        { \
            return zfself::EnumIndexForValue(value); \
        } \
        zfoverride \
        virtual zfuint enumValueAtIndex(ZF_IN zfindex index) \
        { \
            return zfself::EnumValueAtIndex(index); \
        } \
        zfoverride \
        virtual const zfchar *enumNameAtIndex(ZF_IN zfindex index) \
        { \
            return zfself::EnumNameAtIndex(index); \
        } \
        zfoverride \
        virtual const zfchar *enumFullNameAtIndex(ZF_IN zfindex index) \
        { \
            return zfself::EnumFullNameAtIndex(index); \
        } \
        zfoverride \
        virtual zfbool enumContainValue(ZF_IN zfuint value) \
        { \
            return zfself::EnumContainValue(value); \
        } \
        zfoverride \
        virtual zfuint enumValueForName(ZF_IN const zfchar *name) \
        { \
            return zfself::EnumValueForName(name); \
        } \
        zfoverride \
        virtual const zfchar *enumNameForValue(ZF_IN zfuint value) \
        { \
            return zfself::EnumNameForValue(value); \
        } \
    private: \
        static const _ZFP_ZFEnumData *_ZFP_ZFEnumDataRef(void) \
        { \
            static const _ZFP_ZFEnumData *d = _ZFP_ZFEnumDataInit(); \
            return d; \
        } \
        static const _ZFP_ZFEnumData *_ZFP_ZFEnumDataInit(void) \
        { \
            zfCoreMutexLocker(); \
            _ZFP_ZFEnumData *d = _ZFP_ZFEnumDataAccess(ChildEnum::ClassData()); \
            if(d->needInitFlag) \
            { \
                d->needInitFlag = zffalse; \
                zfbool isEnableDuplicateValue = isEnableDuplicateValue_;
/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_SEPARATOR(ChildEnum) _ZFP_ZFENUM_SEPARATOR(ChildEnum, zffalse)
/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_SEPARATOR_ALLOW_DUPLICATE_VALUE(ChildEnum) _ZFP_ZFENUM_SEPARATOR(ChildEnum, zftrue)

/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_VALUE_REGISTER_WITH_NAME(Value, Name) \
                d->add(isEnableDuplicateValue, zfself::e_##Value, Name);
/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_VALUE_REGISTER(Value) \
                ZFENUM_VALUE_REGISTER_WITH_NAME(Value, zfText(#Value))
#define _ZFP_ZFENUM_END_EXTRA(ChildEnum) \
    /** @brief editable version of @ref ChildEnum */ \
    zfclass ZF_ENV_EXPORT ChildEnum##Editable : zfextends ChildEnum \
    { \
        ZFOBJECT_DECLARE(ChildEnum##Editable, ChildEnum) \
    public: \
        zfoverride \
        virtual void enumValueSet(ZF_IN zfuint value) \
        { \
            zfsuper::enumValueSet(value); \
        } \
    }; \
    /** @brief same as @ref ChildEnum##Enum, see @ref ChildEnum */ \
    typedef ChildEnum::ZFEnumType ChildEnum##Enum; \
    _ZFP_ZFENUM_CONVERTER_DECLARE(ChildEnum) \
    ZFPROPERTY_TYPE_DECLARE(ChildEnum##Enum, ChildEnum##Enum)
/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_END(ChildEnum) \
            } \
            return d; \
        } \
    public: \
        /** @brief default value for @ref ChildEnum */ \
        static inline ChildEnum::ZFEnumType EnumDefault(void) \
        { \
            return (ChildEnum::ZFEnumType)ChildEnum::EnumValueAtIndex(0); \
        } \
    }; \
    _ZFP_ZFENUM_END_EXTRA(ChildEnum)
/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_END_WITH_DEFAULT(ChildEnum, defaultEnum) \
            } \
            return d; \
        } \
    public: \
        /** @brief default value for @ref ChildEnum (defaultEnum) */ \
        static inline ChildEnum::ZFEnumType EnumDefault(void) \
        { \
            return ChildEnum::e_##defaultEnum; \
        } \
    }; \
    _ZFP_ZFENUM_END_EXTRA(ChildEnum)

/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_DEFINE(ChildEnum) \
    ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ChildEnum##Enum, ChildEnum##Enum, { \
            if(zfsncmp(src, ZFEnumNameInvalid(), srcLen) == 0) \
            { \
                v = (ChildEnum##Enum)ZFEnumInvalid(); \
                return zftrue; \
            } \
            v = (ChildEnum##Enum)ChildEnum::EnumValueForName( \
                    (srcLen == zfindexMax) ? src : zfstring(src, srcLen).cString() \
                ); \
            return ((zfuint)v != ZFEnumInvalid()); \
        }, { \
            s += ChildEnum::EnumNameForValue(v); \
            return zftrue; \
        }) \
    _ZFP_ZFENUM_CONVERTER_DEFINE(ChildEnum) \
    ZFOBJECT_REGISTER(ChildEnum) \
    ZFOBJECT_REGISTER(ChildEnum##Editable) \
    ZF_STATIC_REGISTER_INIT(EnumReg_##ChildEnum) \
    { \
        { \
            ZFMethodUserRegisterDetail_0(resultMethod, &i_EnumDefault, ChildEnum::ClassData(), \
                public, ZFMethodIsStatic, \
                zfuint, zfText("EnumDefault")); \
            this->m_EnumDefault = resultMethod; \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &i_hashForValue, ChildEnum::ClassData(), \
                public, ZFMethodIsStatic, \
                zfidentity, zfText("hashForValue"), \
                ZFMP_IN(zfuint, value)); \
            this->m_hashForValue = resultMethod; \
        } \
        { \
            ZFMethodUserRegisterDetail_0(resultMethod, &i_EnumCount, ChildEnum::ClassData(), \
                public, ZFMethodIsStatic, \
                zfindex, zfText("EnumCount")); \
            this->m_EnumCount = resultMethod; \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &i_EnumIndexForValue, ChildEnum::ClassData(), \
                public, ZFMethodIsStatic, \
                zfindex, zfText("EnumIndexForValue"), \
                ZFMP_IN(zfuint, value)); \
            this->m_EnumIndexForValue = resultMethod; \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &i_EnumValueAtIndex, ChildEnum::ClassData(), \
                public, ZFMethodIsStatic, \
                zfuint, zfText("EnumValueAtIndex"), \
                ZFMP_IN(zfindex, index)); \
            this->m_EnumValueAtIndex = resultMethod; \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &i_EnumNameAtIndex, ChildEnum::ClassData(), \
                public, ZFMethodIsStatic, \
                const zfchar *, zfText("EnumNameAtIndex"), \
                ZFMP_IN(zfindex, index)); \
            this->m_EnumNameAtIndex = resultMethod; \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &i_EnumFullNameAtIndex, ChildEnum::ClassData(), \
                public, ZFMethodIsStatic, \
                const zfchar *, zfText("EnumFullNameAtIndex"), \
                ZFMP_IN(zfindex, index)); \
            this->m_EnumFullNameAtIndex = resultMethod; \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &i_EnumContainValue, ChildEnum::ClassData(), \
                public, ZFMethodIsStatic, \
                zfbool, zfText("EnumContainValue"), \
                ZFMP_IN(zfuint, value)); \
            this->m_EnumContainValue = resultMethod; \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &i_EnumValueForName, ChildEnum::ClassData(), \
                public, ZFMethodIsStatic, \
                zfuint, zfText("EnumValueForName"), \
                ZFMP_IN(const zfchar *, name)); \
            this->m_EnumValueForName = resultMethod; \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &i_EnumNameForValue, ChildEnum::ClassData(), \
                public, ZFMethodIsStatic, \
                const zfchar *, zfText("EnumNameForValue"), \
                ZFMP_IN(zfuint, value)); \
            this->m_EnumNameForValue = resultMethod; \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &i_enumValueSet, ChildEnum::ClassData(), \
                public, ZFMethodIsVirtual, \
                void, zfText("enumValueSet"), \
                ZFMP_IN(zfuint, value)); \
            this->m_enumValueSet = resultMethod; \
        } \
    } \
    ZF_STATIC_REGISTER_DESTROY(EnumReg_##ChildEnum) \
    { \
        ZFMethodUserUnregister(this->m_EnumDefault); \
        ZFMethodUserUnregister(this->m_hashForValue); \
        ZFMethodUserUnregister(this->m_EnumCount); \
        ZFMethodUserUnregister(this->m_EnumIndexForValue); \
        ZFMethodUserUnregister(this->m_EnumValueAtIndex); \
        ZFMethodUserUnregister(this->m_EnumNameAtIndex); \
        ZFMethodUserUnregister(this->m_EnumFullNameAtIndex); \
        ZFMethodUserUnregister(this->m_EnumContainValue); \
        ZFMethodUserUnregister(this->m_EnumValueForName); \
        ZFMethodUserUnregister(this->m_EnumNameForValue); \
        ZFMethodUserUnregister(this->m_enumValueSet); \
    } \
    \
    const ZFMethod *m_EnumDefault; \
    static zfuint i_EnumDefault(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject) \
    {return ChildEnum::EnumDefault();} \
    \
    const ZFMethod *m_hashForValue; \
    static zfidentity i_hashForValue(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfuint value) \
    {return ChildEnum::hashForValue(value);} \
    \
    const ZFMethod *m_EnumCount; \
    static zfindex i_EnumCount(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject) \
    {return ChildEnum::EnumCount();} \
    \
    const ZFMethod *m_EnumIndexForValue; \
    static zfindex i_EnumIndexForValue(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfuint value) \
    {return ChildEnum::EnumIndexForValue(value);} \
    \
    const ZFMethod *m_EnumValueAtIndex; \
    static zfuint i_EnumValueAtIndex(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfindex index) \
    {return ChildEnum::EnumValueAtIndex(index);} \
    \
    const ZFMethod *m_EnumNameAtIndex; \
    static const zfchar *i_EnumNameAtIndex(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfindex index) \
    {return ChildEnum::EnumNameAtIndex(index);} \
    \
    const ZFMethod *m_EnumFullNameAtIndex; \
    static const zfchar *i_EnumFullNameAtIndex(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfindex index) \
    {return ChildEnum::EnumFullNameAtIndex(index);} \
    \
    const ZFMethod *m_EnumContainValue; \
    static zfbool i_EnumContainValue(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfuint value) \
    {return ChildEnum::EnumContainValue(value);} \
    \
    const ZFMethod *m_EnumValueForName; \
    static zfuint i_EnumValueForName(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN const zfchar *name) \
    {return ChildEnum::EnumValueForName(name);} \
    \
    const ZFMethod *m_EnumNameForValue; \
    static const zfchar *i_EnumNameForValue(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfuint value) \
    {return ChildEnum::EnumNameForValue(value);} \
    \
    const ZFMethod *m_enumValueSet; \
    static void i_enumValueSet(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfuint value) \
    {return invokerObject->to<ChildEnum##Editable *>()->enumValueSet(value);} \
    \
    ZF_STATIC_REGISTER_END(EnumReg_##ChildEnum)

// ============================================================
// zfflags conversion
/**
 * @brief zfflags conversion using ZFEnum as source, see #zfflagsToString
 */
extern ZF_ENV_EXPORT zfbool zfflagsToString(ZF_IN_OUT zfstring &ret,
                                            ZF_IN const ZFClass *enumClass,
                                            ZF_IN zfflags const &value,
                                            ZF_IN_OPT zfbool includeNotConverted = zftrue,
                                            ZF_IN_OPT zfbool exclusiveMode = zffalse,
                                            ZF_OUT_OPT zfflags *notConverted = zfnull,
                                            ZF_IN_OPT zfchar separatorToken = '|');
/** @brief see #zfflagsToString */
inline zfstring zfflagsToString(ZF_IN const ZFClass *enumClass,
                                ZF_IN zfflags const &value,
                                ZF_IN_OPT zfbool includeNotConverted = zftrue,
                                ZF_IN_OPT zfbool exclusiveMode = zffalse,
                                ZF_OUT_OPT zfflags *notConverted = zfnull,
                                ZF_IN_OPT zfchar separatorToken = '|')
{
    zfstring ret;
    zfflagsToString(ret, enumClass, value, includeNotConverted, exclusiveMode, notConverted, separatorToken);
    return ret;
}
/**
 * @brief zfflags conversion using ZFEnum as source, see #zfflagsFromString
 */
extern ZF_ENV_EXPORT zfbool zfflagsFromString(ZF_OUT zfflags &ret,
                                              ZF_IN const ZFClass *enumClass,
                                              ZF_IN const zfchar *src,
                                              ZF_IN_OPT zfindex srcLen = zfindexMax,
                                              ZF_IN_OPT zfchar separatorToken = '|',
                                              ZF_OUT_OPT const zfchar **outErrorPos = zfnull);

// ============================================================
#define _ZFP_ZFENUM_CONVERTER_DECLARE(EnumName) \
    /** @brief see @ref EnumName, return empty string if error */ \
    extern ZF_ENV_EXPORT zfbool EnumName##ToString(ZF_IN_OUT zfstring &ret, ZF_IN EnumName *const &value); \
    /** @brief see @ref EnumName, return empty string if error */ \
    inline zfstring EnumName##ToString(ZF_IN EnumName *const &value) \
    { \
        zfstring ret; \
        EnumName##ToString(ret, value); \
        return ret; \
    } \
    /** @brief see @ref EnumName, return enum object if success */ \
    extern ZF_ENV_EXPORT zfbool EnumName##FromString(ZF_OUT zfautoObject &ret, \
                                                     ZF_IN const zfchar *src, \
                                                     ZF_IN_OPT zfindex srcLen = zfindexMax); \
    ZFOUTPUT_TYPE_DECLARE(EnumName##Enum)
#define _ZFP_ZFENUM_CONVERTER_DEFINE(EnumName) \
    zfbool EnumName##ToString(ZF_IN_OUT zfstring &ret, ZF_IN EnumName *const &value) \
    { \
        ret += ((value == zfnull) ? zfText("") : value->enumName()); \
        return zftrue; \
    } \
    zfbool EnumName##FromString(ZF_OUT zfautoObject &ret, \
                                ZF_IN const zfchar *src, \
                                ZF_IN_OPT zfindex srcLen /* = zfindexMax */) \
    { \
        if(zfsncmp(src, ZFEnumNameInvalid(), srcLen) == 0) \
        { \
            ret = zfautoObjectCreate(zflineAlloc(EnumName, ZFEnumInvalid())); \
            return zftrue; \
        } \
        zfuint tmpValue = EnumName::EnumValueForName( \
            (srcLen == zfindexMax) ? src : zfstring(src, srcLen).cString()); \
        if(tmpValue == ZFEnumInvalid()) \
        { \
            return zffalse; \
        } \
        else \
        { \
            ret = zfautoObjectCreate(zflineAlloc(EnumName, tmpValue)); \
            return zftrue; \
        } \
    } \
    ZFOUTPUT_TYPE_DEFINE(EnumName##Enum, {output << EnumName::EnumNameForValue(v);})

// ============================================================
#define _ZFP_ZFENUM_FLAGS_DECLARE(EnumName, EnumFlagsName, defaultFix) \
    /** @brief EnumName as #zfflags, see @ref EnumName, @ref EnumFlagsName##ToString, @ref EnumFlagsName##FromString */ \
    zffinal zfclassLikePOD ZF_ENV_EXPORT EnumFlagsName : zfextendsLikePOD ZFEnumFlagsBase \
    { \
        defaultFix \
    public: \
        /** @cond ZFPrivateDoc */ \
        EnumFlagsName(void) : flags(0) {} \
        EnumFlagsName(ZF_IN const zfuint &flags) : flags(flags) {} \
        EnumFlagsName(ZF_IN const EnumName##Enum &flags) : flags((zfuint)flags) {} \
        EnumFlagsName(ZF_IN const EnumFlagsName &ref) : flags(ref.flags) {} \
        virtual ~EnumFlagsName(void) {} \
    public: \
        const zfuint &enumValue(void) const {return this->flags;} \
        void enumValueSet(ZF_IN const zfuint &flags) {this->flags = flags;} \
        void enumValueSet(ZF_IN const EnumName##Enum &flags) {this->flags = (zfuint)flags;} \
    public: \
        operator const zfuint &(void) const {return this->flags;} \
        EnumFlagsName &operator = (ZF_IN const zfuint &flags) {this->flags = flags; return *this;} \
        EnumFlagsName &operator = (ZF_IN const EnumName##Enum &flags) {this->flags = (zfuint)flags; return *this;} \
        EnumFlagsName &operator = (ZF_IN const EnumFlagsName &ref) {this->flags = ref.flags; return *this;} \
        zfbool operator == (ZF_IN const zfuint &flags) const {return (this->flags == flags);} \
        zfbool operator == (ZF_IN const EnumName##Enum &flags) const {return (this->flags == (zfuint)flags);} \
        zfbool operator == (ZF_IN const EnumFlagsName &ref) const {return (this->flags == ref.flags);} \
        zfbool operator != (ZF_IN const zfuint &flags) const {return (this->flags != flags);} \
        zfbool operator != (ZF_IN const EnumName##Enum &flags) const {return (this->flags != (zfuint)flags);} \
        zfbool operator != (ZF_IN const EnumFlagsName &ref) const {return (this->flags != ref.flags);} \
        EnumFlagsName &operator |= (ZF_IN const zfuint &flags) {this->flags |= flags; return *this;} \
        EnumFlagsName &operator |= (ZF_IN const EnumName##Enum &flags) {this->flags |= (zfuint)flags; return *this;} \
        EnumFlagsName &operator |= (ZF_IN const EnumFlagsName &ref) {this->flags |= ref.flags; return *this;} \
        EnumFlagsName &operator &= (ZF_IN const zfuint &flags) {this->flags &= flags; return *this;} \
        EnumFlagsName &operator &= (ZF_IN const EnumName##Enum &flags) {this->flags &= (zfuint)flags; return *this;} \
        EnumFlagsName &operator &= (ZF_IN const EnumFlagsName &ref) {this->flags &= ref.flags; return *this;} \
    public: \
        virtual void objectInfoT(ZF_IN_OUT zfstring &ret) const; \
        virtual inline zfstring objectInfo(void) const \
        { \
            zfstring ret; \
            this->objectInfoT(ret); \
            return ret; \
        } \
        /** @endcond */ \
    private: \
        zfuint flags; \
    };
#define _ZFP_ZFENUM_FLAGS_CONVERTER_DECLARE(EnumName, EnumFlagsName) \
    ZFOUTPUT_TYPE_DECLARE(EnumFlagsName)
#define _ZFP_ZFENUM_FLAGS_CONVERTER_DEFINE(EnumName, EnumFlagsName) \
    ZFOUTPUT_TYPE_DEFINE(EnumFlagsName, {output << v.objectInfo();})
/**
 * @brief util macro to declare a flag set type for a ZFEnum type
 *
 * usage:
 * @code
 *   // in .h file
 *   ZFENUM_FLAGS_DECLARE(YourEnumType, YourEnumFlagsType)
 *
 *   // in cpp file
 *   ZFENUM_FLAGS_DEFINE(YourEnumType, YourEnumFlagsType)
 * @endcode
 */
#define ZFENUM_FLAGS_DECLARE(EnumName, EnumFlagsName) \
    _ZFP_ZFENUM_FLAGS_DECLARE(EnumName, EnumFlagsName, ZFM_EMPTY()) \
    ZFPROPERTY_TYPE_DECLARE(EnumFlagsName, EnumFlagsName) \
    _ZFP_ZFENUM_FLAGS_CONVERTER_DECLARE(EnumName, EnumFlagsName)
#define _ZFP_ZFENUM_FLAGS_DEFAULT_EXPAND(EnumName, EnumFlagsName, defaultValue) \
    public: \
        /** @brief default value for EnumFlagsName (defaultValue) */ \
        static inline zfuint EnumDefault(void) \
        { \
            return defaultValue; \
        }
/**
 * @brief see #ZFENUM_FLAGS_DECLARE, declare with default value,
 *   which can be accessed by YourEnumFlagsType::EnumDefault()
 */
#define ZFENUM_FLAGS_DECLARE_WITH_DEFAULT(EnumName, EnumFlagsName, defaultValue) \
    _ZFP_ZFENUM_FLAGS_DECLARE(EnumName, EnumFlagsName, _ZFP_ZFENUM_FLAGS_DEFAULT_EXPAND(EnumName, EnumFlagsName, defaultValue)) \
    ZFPROPERTY_TYPE_DECLARE(EnumFlagsName, EnumFlagsName) \
    _ZFP_ZFENUM_FLAGS_CONVERTER_DECLARE(EnumName, EnumFlagsName)

/** @brief see #ZFENUM_FLAGS_DECLARE */
#define ZFENUM_FLAGS_DEFINE(EnumName, EnumFlagsName) \
    ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(EnumFlagsName, EnumFlagsName, { \
            zfflags flags = zfflagsZero; \
            if(!zfflagsFromString(flags, \
                EnumName::ClassData(), \
                src, srcLen)) \
            { \
                return zffalse; \
            } \
            v.enumValueSet((zfuint)flags); \
            return zftrue; \
        }, { \
            return zfflagsToString(s, EnumName::ClassData(), (zfflags)v.enumValue()); \
        }) \
    _ZFP_ZFENUM_FLAGS_CONVERTER_DEFINE(EnumName, EnumFlagsName) \
    void EnumFlagsName::objectInfoT(ZF_IN_OUT zfstring &ret) const \
    { \
        zfflagsToString(ret, EnumName::ClassData(), (zfflags)this->enumValue()); \
    }

// ============================================================
// ZFEnumFlagsBase
/**
 * @brief base class of enum flags
 */
zfclassLikePOD ZF_ENV_EXPORT ZFEnumFlagsBase
{
public:
    /** @cond ZFPrivateDoc */
    ZFEnumFlagsBase(void)
    {
    }
    virtual ~ZFEnumFlagsBase(void)
    {
    }
    /** @endcond */

public:
    /**
     * @brief get a short info
     */
    virtual zfstring objectInfo(void) const zfpurevirtual;
};

ZFOUTPUT_TYPE_DECLARE(ZFEnumFlagsBase)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFEnum_h_

#include "ZFPropertyType.h"

