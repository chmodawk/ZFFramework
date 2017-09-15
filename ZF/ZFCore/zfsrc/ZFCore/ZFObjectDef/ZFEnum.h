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
#include "ZFEnumDeclare.h"
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
     * @brief get the index of enum value, or zfindexMax() if no such enum value
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
#define ZFENUM_BEGIN(EnumName) _ZFP_ZFENUM_BEGIN(EnumName)

/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_VALUE(Value) _ZFP_ZFENUM_VALUE(Value)
/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_VALUE_WITH_INIT(Value, initValue) _ZFP_ZFENUM_VALUE_WITH_INIT(Value, initValue)

/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_SEPARATOR(EnumName) _ZFP_ZFENUM_SEPARATOR(EnumName, zffalse)
/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_SEPARATOR_ALLOW_DUPLICATE_VALUE(EnumName) _ZFP_ZFENUM_SEPARATOR(EnumName, zftrue)

/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_VALUE_REGISTER_WITH_NAME(Value, Name) _ZFP_ZFENUM_VALUE_REGISTER_WITH_NAME(Value, Name)
/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_VALUE_REGISTER(Value) _ZFP_ZFENUM_VALUE_REGISTER_WITH_NAME(Value, zfText(#Value))

/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_END(EnumName) _ZFP_ZFENUM_END(EnumName)
/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_END_WITH_DEFAULT(EnumName, defaultEnum) _ZFP_ZFENUM_END_WITH_DEFAULT(EnumName, defaultEnum)

/** @brief see #ZFENUM_BEGIN */
#define ZFENUM_DEFINE(EnumName) _ZFP_ZFENUM_DEFINE(EnumName)

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
                                              ZF_IN_OPT zfindex srcLen = zfindexMax(),
                                              ZF_IN_OPT zfchar separatorToken = '|',
                                              ZF_OUT_OPT const zfchar **outErrorPos = zfnull);

// ============================================================
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
#define ZFENUM_FLAGS_DECLARE(EnumName, EnumFlagsName) _ZFP_ZFENUM_FLAGS_DECLARE(EnumName, EnumFlagsName)
/**
 * @brief see #ZFENUM_FLAGS_DECLARE, declare with default value,
 *   which can be accessed by YourEnumFlagsType::EnumDefault()
 */
#define ZFENUM_FLAGS_DECLARE_WITH_DEFAULT(EnumName, EnumFlagsName, defaultValue) _ZFP_ZFENUM_FLAGS_DECLARE_WITH_DEFAULT(EnumName, EnumFlagsName, defaultValue)

/** @brief see #ZFENUM_FLAGS_DECLARE */
#define ZFENUM_FLAGS_DEFINE(EnumName, EnumFlagsName) _ZFP_ZFENUM_FLAGS_DEFINE(EnumName, EnumFlagsName)

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

// ============================================================
zfclassFwd ZFPropertyTypeWrapper;
/**
 * @brief access enum info from enum wrapper class
 */
extern ZF_ENV_EXPORT zfbool ZFEnumWrapperInfo(ZF_OUT const ZFClass *&enumClass,
                                              ZF_OUT zfuint &enumValue,
                                              ZF_IN ZFPropertyTypeWrapper *enumWrapper);

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFEnum_h_

#include "ZFPropertyType.h"

