/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFEnumDeclare.h
 * @brief ZFEnum declare impl
 */

#ifndef _ZFI_ZFEnumDeclare_h_
#define _ZFI_ZFEnumDeclare_h_

#include "ZFObjectClassTypeFwd.h"
ZF_NAMESPACE_GLOBAL_BEGIN

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
    zfbool enumContainValue(ZF_IN zfuint value) const;
    zfuint enumValueForName(ZF_IN const zfchar *name) const;
    const zfchar *enumNameForValue(ZF_IN zfuint value) const;
private:
    _ZFP_ZFEnumDataPrivate *d;
};
extern ZF_ENV_EXPORT _ZFP_ZFEnumData *_ZFP_ZFEnumDataAccess(ZF_IN const ZFClass *ownerClass);

// ============================================================
#define _ZFP_ZFENUM_BEGIN(EnumName) \
    zfclass ZF_ENV_EXPORT EnumName : zfextends ZFEnum \
    { \
        ZFOBJECT_DECLARE(EnumName, ZFEnum) \
    public: \
        /** @brief see @ref EnumName */ \
        typedef enum \
        {

#define _ZFP_ZFENUM_VALUE(Value) /** \n */ e_##Value,
#define _ZFP_ZFENUM_VALUE_WITH_INIT(Value, initValue) /** @brief \n Value(initValue)\n */ e_##Value = initValue,

#define _ZFP_ZFENUM_SEPARATOR(EnumName, isEnableDuplicateValue_) \
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
        /** @brief get the index of enum value, or zfindexMax() if no such enum value */ \
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
            _ZFP_ZFEnumData *d = _ZFP_ZFEnumDataAccess(EnumName::ClassData()); \
            if(d->needInitFlag) \
            { \
                d->needInitFlag = zffalse; \
                zfbool isEnableDuplicateValue = isEnableDuplicateValue_;

#define _ZFP_ZFENUM_VALUE_REGISTER_WITH_NAME(Value, Name) \
                d->add(isEnableDuplicateValue, zfself::e_##Value, Name);

#define _ZFP_ZFENUM_END_EXTRA(EnumName) \
    /** @brief editable version of @ref EnumName */ \
    zfclass ZF_ENV_EXPORT EnumName##Editable : zfextends EnumName \
    { \
        ZFOBJECT_DECLARE(EnumName##Editable, EnumName) \
    public: \
        zfoverride \
        virtual void enumValueSet(ZF_IN zfuint value) \
        { \
            zfsuper::enumValueSet(value); \
        } \
    }; \
    /** @brief same as @ref EnumName##Enum, see @ref EnumName */ \
    typedef EnumName::ZFEnumType EnumName##Enum; \
    _ZFP_ZFENUM_CONVERTER_DECLARE(EnumName) \
    ZFPROPERTY_TYPE_DECLARE(EnumName##Enum, EnumName##Enum)
#define _ZFP_ZFENUM_END(EnumName) \
            } \
            return d; \
        } \
    public: \
        /** @brief default value for @ref EnumName */ \
        static inline EnumName::ZFEnumType EnumDefault(void) \
        { \
            return (EnumName::ZFEnumType)EnumName::EnumValueAtIndex(0); \
        } \
    }; \
    _ZFP_ZFENUM_END_EXTRA(EnumName)
#define _ZFP_ZFENUM_END_WITH_DEFAULT(EnumName, defaultEnum) \
            } \
            return d; \
        } \
    public: \
        /** @brief default value for @ref EnumName (defaultEnum) */ \
        static inline EnumName::ZFEnumType EnumDefault(void) \
        { \
            return EnumName::e_##defaultEnum; \
        } \
    }; \
    _ZFP_ZFENUM_END_EXTRA(EnumName)

#define _ZFP_ZFENUM_DEFINE(EnumName) \
    ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(EnumName##Enum, EnumName##Enum, { \
            if(zfsncmp(src, ZFEnumNameInvalid(), srcLen) == 0) \
            { \
                v = (EnumName##Enum)ZFEnumInvalid(); \
                return zftrue; \
            } \
            v = (EnumName##Enum)EnumName::EnumValueForName( \
                    (srcLen == zfindexMax()) ? src : zfstring(src, srcLen).cString() \
                ); \
            return ((zfuint)v != ZFEnumInvalid()); \
        }, { \
            s += EnumName::EnumNameForValue(v); \
            return zftrue; \
        }) \
    ZFMETHOD_USER_REGISTER_3({ \
            enumClass = EnumName::ClassData(); \
            enumValue = (zfuint)enumWrapper->to<v_##EnumName##Enum *>()->zfv; \
            return zftrue; \
        }, v_##EnumName##Enum, zfbool, _ZFP_ZFEnumWrapperInfo \
        , ZFMP_OUT(const ZFClass *&, enumClass) \
        , ZFMP_OUT(zfuint &, enumValue) \
        , ZFMP_IN(ZFPropertyTypeWrapper *, enumWrapper) \
        ) \
    _ZFP_ZFENUM_CONVERTER_DEFINE(EnumName) \
    ZFOBJECT_REGISTER(EnumName) \
    ZFOBJECT_REGISTER(EnumName##Editable) \
    ZF_STATIC_REGISTER_INIT(EnumReg_##EnumName) \
    { \
        for(zfindex i = 0; i < EnumName::EnumCount(); ++i) \
        { \
            ZFMethodUserRegisterDetail_0(resultMethod, &ivk_e, EnumName::ClassData(), \
                public, ZFMethodIsStatic, \
                EnumName##Enum, zfstringWithFormat(zfText("e_%s"), EnumName::EnumNameAtIndex(i))); \
            _m.add(resultMethod); \
        } \
        \
        { \
            ZFMethodUserRegisterDetail_0(resultMethod, &ivk_EnumDefault, EnumName::ClassData(), \
                public, ZFMethodIsStatic, \
                zfuint, zfText("EnumDefault")); \
            _m.add(resultMethod); \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &ivk_hashForValue, EnumName::ClassData(), \
                public, ZFMethodIsStatic, \
                zfidentity, zfText("hashForValue"), \
                ZFMP_IN(zfuint, value)); \
            _m.add(resultMethod); \
        } \
        { \
            ZFMethodUserRegisterDetail_0(resultMethod, &ivk_EnumCount, EnumName::ClassData(), \
                public, ZFMethodIsStatic, \
                zfindex, zfText("EnumCount")); \
            _m.add(resultMethod); \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &ivk_EnumIndexForValue, EnumName::ClassData(), \
                public, ZFMethodIsStatic, \
                zfindex, zfText("EnumIndexForValue"), \
                ZFMP_IN(zfuint, value)); \
            _m.add(resultMethod); \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &ivk_EnumValueAtIndex, EnumName::ClassData(), \
                public, ZFMethodIsStatic, \
                zfuint, zfText("EnumValueAtIndex"), \
                ZFMP_IN(zfindex, index)); \
            _m.add(resultMethod); \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &ivk_EnumNameAtIndex, EnumName::ClassData(), \
                public, ZFMethodIsStatic, \
                const zfchar *, zfText("EnumNameAtIndex"), \
                ZFMP_IN(zfindex, index)); \
            _m.add(resultMethod); \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &ivk_EnumContainValue, EnumName::ClassData(), \
                public, ZFMethodIsStatic, \
                zfbool, zfText("EnumContainValue"), \
                ZFMP_IN(zfuint, value)); \
            _m.add(resultMethod); \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &ivk_EnumValueForName, EnumName::ClassData(), \
                public, ZFMethodIsStatic, \
                zfuint, zfText("EnumValueForName"), \
                ZFMP_IN(const zfchar *, name)); \
            _m.add(resultMethod); \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &ivk_EnumNameForValue, EnumName::ClassData(), \
                public, ZFMethodIsStatic, \
                const zfchar *, zfText("EnumNameForValue"), \
                ZFMP_IN(zfuint, value)); \
            _m.add(resultMethod); \
        } \
        { \
            ZFMethodUserRegisterDetail_1(resultMethod, &ivk_enumValueSet, EnumName::ClassData(), \
                public, ZFMethodIsVirtual, \
                void, zfText("enumValueSet"), \
                ZFMP_IN(zfuint, value)); \
            _m.add(resultMethod); \
        } \
    } \
    ZF_STATIC_REGISTER_DESTROY(EnumReg_##EnumName) \
    { \
        for(zfindex i = 0; i < _m.count(); ++i) \
        { \
            ZFMethodUserUnregister(_m[i]); \
        } \
    } \
    ZFCoreArrayPOD<const ZFMethod *> _m; \
    \
    static EnumName##Enum ivk_e(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject) \
    {return (EnumName##Enum)EnumName::EnumValueForName(invokerMethod->methodName() + 2);} \
    \
    static zfuint ivk_EnumDefault(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject) \
    {return EnumName::EnumDefault();} \
    \
    static zfidentity ivk_hashForValue(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfuint value) \
    {return EnumName::hashForValue(value);} \
    \
    static zfindex ivk_EnumCount(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject) \
    {return EnumName::EnumCount();} \
    \
    static zfindex ivk_EnumIndexForValue(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfuint value) \
    {return EnumName::EnumIndexForValue(value);} \
    \
    static zfuint ivk_EnumValueAtIndex(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfindex index) \
    {return EnumName::EnumValueAtIndex(index);} \
    \
    static const zfchar *ivk_EnumNameAtIndex(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfindex index) \
    {return EnumName::EnumNameAtIndex(index);} \
    \
    static zfbool ivk_EnumContainValue(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfuint value) \
    {return EnumName::EnumContainValue(value);} \
    \
    static zfuint ivk_EnumValueForName(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN const zfchar *name) \
    {return EnumName::EnumValueForName(name);} \
    \
    static const zfchar *ivk_EnumNameForValue(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfuint value) \
    {return EnumName::EnumNameForValue(value);} \
    \
    static void ivk_enumValueSet(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject, ZF_IN zfuint value) \
    {return invokerObject->to<EnumName##Editable *>()->enumValueSet(value);} \
    \
    ZF_STATIC_REGISTER_END(EnumReg_##EnumName)

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
                                                     ZF_IN_OPT zfindex srcLen = zfindexMax()); \
    ZFOUTPUT_TYPE_DECLARE(EnumName##Enum)
#define _ZFP_ZFENUM_CONVERTER_DEFINE(EnumName) \
    zfbool EnumName##ToString(ZF_IN_OUT zfstring &ret, ZF_IN EnumName *const &value) \
    { \
        ret += ((value == zfnull) ? zfText("") : value->enumName()); \
        return zftrue; \
    } \
    zfbool EnumName##FromString(ZF_OUT zfautoObject &ret, \
                                ZF_IN const zfchar *src, \
                                ZF_IN_OPT zfindex srcLen /* = zfindexMax() */) \
    { \
        if(zfsncmp(src, ZFEnumNameInvalid(), srcLen) == 0) \
        { \
            ret = zfautoObjectCreate(zflineAlloc(EnumName, ZFEnumInvalid())); \
            return zftrue; \
        } \
        zfuint tmpValue = EnumName::EnumValueForName( \
            (srcLen == zfindexMax()) ? src : zfstring(src, srcLen).cString()); \
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
#define _ZFP_ZFENUM_FLAGS_DECLARE_EXPAND(EnumName, EnumFlagsName, defaultFix) \
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
    }; \
    ZFPROPERTY_TYPE_DECLARE(EnumFlagsName, EnumFlagsName) \
    ZFOUTPUT_TYPE_DECLARE(EnumFlagsName)
#define _ZFP_ZFENUM_FLAGS_DEFAULT_EXPAND(EnumName, EnumFlagsName, defaultValue) \
    public: \
        /** @brief default value for EnumFlagsName (defaultValue) */ \
        static inline zfuint EnumDefault(void) \
        { \
            return defaultValue; \
        }

#define _ZFP_ZFENUM_FLAGS_DECLARE(EnumName, EnumFlagsName) \
    _ZFP_ZFENUM_FLAGS_DECLARE_EXPAND(EnumName, EnumFlagsName, ZFM_EMPTY())
#define _ZFP_ZFENUM_FLAGS_DECLARE_WITH_DEFAULT(EnumName, EnumFlagsName, defaultValue) \
    _ZFP_ZFENUM_FLAGS_DECLARE_EXPAND(EnumName, EnumFlagsName, _ZFP_ZFENUM_FLAGS_DEFAULT_EXPAND(EnumName, EnumFlagsName, defaultValue))

#define _ZFP_ZFENUM_FLAGS_DEFINE(EnumName, EnumFlagsName) \
    ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(EnumFlagsName, EnumFlagsName, { \
            zfflags flags = zfflagsZero(); \
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
    ZFMETHOD_USER_REGISTER_3({ \
            enumClass = EnumName::ClassData(); \
            enumValue = (zfuint)enumWrapper->to<v_##EnumFlagsName *>()->zfv; \
            return zftrue; \
        }, v_##EnumFlagsName, zfbool, _ZFP_ZFEnumWrapperInfo \
        , ZFMP_OUT(const ZFClass *&, enumClass) \
        , ZFMP_OUT(zfuint &, enumValue) \
        , ZFMP_IN(ZFPropertyTypeWrapper *, enumWrapper) \
        ) \
    ZFOUTPUT_TYPE_DEFINE(EnumFlagsName, {output << v.objectInfo();}) \
    void EnumFlagsName::objectInfoT(ZF_IN_OUT zfstring &ret) const \
    { \
        zfflagsToString(ret, EnumName::ClassData(), (zfflags)this->enumValue()); \
    } \
    _ZFP_ZFENUM_FLAGS_VALUE_ACCESS(EnumName, EnumFlagsName)

#define _ZFP_ZFENUM_FLAGS_VALUE_ACCESS(EnumName, EnumFlagsName) \
    ZFPROPERTY_TYPE_VALUE_ACCESS_CALLBACK_DEFINE(EnumFlagsName, EnumName, { \
            return (ZFCastZFObject(v_##EnumName##Enum *, obj) != zfnull); \
        }, { \
            v_##EnumName##Enum *w = ZFCastZFObject(v_##EnumName##Enum *, obj); \
            v_##EnumFlagsName *vHolder = zfAllocWithoutLeakTest(v_##EnumFlagsName); \
            vHolder->zfv = w->zfv; \
            w->tagSetMarkCached(zfText("_ZFP_PropTVH_") ZFM_TOSTRING(EnumName##Enum), vHolder); \
            return &(vHolder->zfv); \
        })

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFEnumDeclare_h_

