/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFMethodDeclare.h
 * @brief ZFMethod declaration
 */

#ifndef _ZFI_ZFMethodDeclare_h_
#define _ZFI_ZFMethodDeclare_h_

#include "ZFMethod.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
zfclassFwd ZFClass;
/* ZFMETHOD_MAX_PARAM */
/**
 * @brief util method to find ZFMethod, return null if method not registered
 */
extern ZF_ENV_EXPORT const ZFMethod *ZFMethodGet(ZF_IN const zfchar *className,
                                                 ZF_IN const zfchar *methodName);
/** @brief see #ZFMethodGet */
extern ZF_ENV_EXPORT const ZFMethod *ZFMethodGet(ZF_IN const zfchar *className,
                                                 ZF_IN const zfchar *methodName
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId0
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId1 = zfnull
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId2 = zfnull
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId3 = zfnull
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId4 = zfnull
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId5 = zfnull
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId6 = zfnull
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId7 = zfnull
                                                 );
/**
 * @brief util method to find ZFMethod, return null if method not registered
 */
extern ZF_ENV_EXPORT const ZFMethod *ZFMethodGet(ZF_IN const ZFClass *cls,
                                                 ZF_IN const zfchar *methodName);
/** @brief see #ZFMethodGet */
extern ZF_ENV_EXPORT const ZFMethod *ZFMethodGet(ZF_IN const ZFClass *cls,
                                                 ZF_IN const zfchar *methodName
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId0
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId1 = zfnull
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId2 = zfnull
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId3 = zfnull
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId4 = zfnull
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId5 = zfnull
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId6 = zfnull
                                                 , ZF_IN_OPT const zfchar *methodParamTypeId7 = zfnull
                                                 );

// ============================================================
#define _ZFP_ZFMethodAccess(OwnerClass, MethodName) \
    (OwnerClass::_ZFP_Mtd_##MethodName(zfnull))
/** @brief see #ZFMethod */
#define ZFMethodAccess(OwnerClass, MethodName) \
    _ZFP_ZFMethodAccess(OwnerClass, MethodName)

#define _ZFP_ZFMethodAccessDetail(OwnerClass, MethodName \
        , ParamExpandOrEmpty0, ParamType0 \
        , ParamExpandOrEmpty1, ParamType1 \
        , ParamExpandOrEmpty2, ParamType2 \
        , ParamExpandOrEmpty3, ParamType3 \
        , ParamExpandOrEmpty4, ParamType4 \
        , ParamExpandOrEmpty5, ParamType5 \
        , ParamExpandOrEmpty6, ParamType6 \
        , ParamExpandOrEmpty7, ParamType7 \
    ) \
    (OwnerClass::_ZFP_Mtd_##MethodName((void (*)( \
           ParamExpandOrEmpty0(ZFM_EMPTY() ParamType0) \
           ParamExpandOrEmpty1(ZFM_COMMA() ParamType1) \
           ParamExpandOrEmpty2(ZFM_COMMA() ParamType2) \
           ParamExpandOrEmpty3(ZFM_COMMA() ParamType3) \
           ParamExpandOrEmpty4(ZFM_COMMA() ParamType4) \
           ParamExpandOrEmpty5(ZFM_COMMA() ParamType5) \
           ParamExpandOrEmpty6(ZFM_COMMA() ParamType6) \
           ParamExpandOrEmpty7(ZFM_COMMA() ParamType7) \
       ))zfnull))
/** @brief see #ZFMethod */
#define ZFMethodAccessDetail_0(OwnerClass, MethodName \
    ) \
    _ZFP_ZFMethodAccessDetail(OwnerClass, MethodName \
            , ZFM_EMPTY,  ParamType0 \
            , ZFM_EMPTY,  ParamType1 \
            , ZFM_EMPTY,  ParamType2 \
            , ZFM_EMPTY,  ParamType3 \
            , ZFM_EMPTY,  ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod */
#define ZFMethodAccessDetail_1(OwnerClass, MethodName \
        , ParamType0 \
    ) \
    _ZFP_ZFMethodAccessDetail(OwnerClass, MethodName \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EMPTY,  ParamType1 \
            , ZFM_EMPTY,  ParamType2 \
            , ZFM_EMPTY,  ParamType3 \
            , ZFM_EMPTY,  ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod */
#define ZFMethodAccessDetail_2(OwnerClass, MethodName \
        , ParamType0 \
        , ParamType1 \
    ) \
    _ZFP_ZFMethodAccessDetail(OwnerClass, MethodName \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EMPTY,  ParamType2 \
            , ZFM_EMPTY,  ParamType3 \
            , ZFM_EMPTY,  ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod */
#define ZFMethodAccessDetail_3(OwnerClass, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
    ) \
    _ZFP_ZFMethodAccessDetail(OwnerClass, MethodName \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EMPTY,  ParamType3 \
            , ZFM_EMPTY,  ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod */
#define ZFMethodAccessDetail_4(OwnerClass, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
        , ParamType3 \
    ) \
    _ZFP_ZFMethodAccessDetail(OwnerClass, MethodName \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EXPAND, ParamType3 \
            , ZFM_EMPTY,  ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod */
#define ZFMethodAccessDetail_5(OwnerClass, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
        , ParamType3 \
        , ParamType4 \
    ) \
    _ZFP_ZFMethodAccessDetail(OwnerClass, MethodName \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EXPAND, ParamType3 \
            , ZFM_EXPAND, ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod */
#define ZFMethodAccessDetail_6(OwnerClass, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
        , ParamType3 \
        , ParamType4 \
        , ParamType5 \
    ) \
    _ZFP_ZFMethodAccessDetail(OwnerClass, MethodName \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EXPAND, ParamType3 \
            , ZFM_EXPAND, ParamType4 \
            , ZFM_EXPAND, ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod */
#define ZFMethodAccessDetail_7(OwnerClass, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
        , ParamType3 \
        , ParamType4 \
        , ParamType5 \
        , ParamType6 \
    ) \
    _ZFP_ZFMethodAccessDetail(OwnerClass, MethodName \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EXPAND, ParamType3 \
            , ZFM_EXPAND, ParamType4 \
            , ZFM_EXPAND, ParamType5 \
            , ZFM_EXPAND, ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod */
#define ZFMethodAccessDetail_8(OwnerClass, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
        , ParamType3 \
        , ParamType4 \
        , ParamType5 \
        , ParamType6 \
        , ParamType7 \
    ) \
    _ZFP_ZFMethodAccessDetail(OwnerClass, MethodName \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EXPAND, ParamType3 \
            , ZFM_EXPAND, ParamType4 \
            , ZFM_EXPAND, ParamType5 \
            , ZFM_EXPAND, ParamType6 \
            , ZFM_EXPAND, ParamType7 \
        )

// ============================================================
#define _ZFP_ZFMethod_AutoRegister_isAutoRegister(MethodName, DECLARE_LINE) \
    private: \
        zfclassNotPOD _ZFP_MtdReg_##MethodName##_##DECLARE_LINE \
        { \
        public: \
            _ZFP_MtdReg_##MethodName##_##DECLARE_LINE(void) \
            { \
                zfself::_ZFP_Mtd_##MethodName##_##DECLARE_LINE(); \
            } \
        } _ZFP_MtdReg_##MethodName##_##DECLARE_LINE##_; \
    public:
#define _ZFP_ZFMethod_AutoRegister_notAutoRegister(MethodName, DECLARE_LINE)
#define _ZFP_ZFMethod_AutoRegister(autoRegisterOrNot, MethodName, DECLARE_LINE) \
    _ZFP_ZFMethod_AutoRegister_##autoRegisterOrNot(MethodName, DECLARE_LINE)

#define _ZFP_ZFMethod_initClassMemberType_privilege_public ZFMethodPrivilegeTypePublic
#define _ZFP_ZFMethod_initClassMemberType_privilege_protected ZFMethodPrivilegeTypeProtected
#define _ZFP_ZFMethod_initClassMemberType_privilege_private ZFMethodPrivilegeTypePrivate
#define _ZFP_ZFMethod_initClassMemberType_privilege(privilege) _ZFP_ZFMethod_initClassMemberType_privilege_##privilege

#define _ZFP_ZFMETHOD_DECLARE(...) \
    ZFM_EXPAND(_ZFP_ZFMETHOD_DECLARE_(__VA_ARGS__))
#define _ZFP_ZFMETHOD_DECLARE_( \
    autoRegisterOrNot, \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName, DECLARE_LINE \
    , ParamExpandOrEmpty0, ParamType0, param0, DefaultValueFix0 \
    , ParamExpandOrEmpty1, ParamType1, param1, DefaultValueFix1 \
    , ParamExpandOrEmpty2, ParamType2, param2, DefaultValueFix2 \
    , ParamExpandOrEmpty3, ParamType3, param3, DefaultValueFix3 \
    , ParamExpandOrEmpty4, ParamType4, param4, DefaultValueFix4 \
    , ParamExpandOrEmpty5, ParamType5, param5, DefaultValueFix5 \
    , ParamExpandOrEmpty6, ParamType6, param6, DefaultValueFix6 \
    , ParamExpandOrEmpty7, ParamType7, param7, DefaultValueFix7 \
    ) \
    /** @cond ZFPrivateDoc */ \
    public: \
        _ZFP_ZFMethod_AutoRegister(autoRegisterOrNot, MethodName, DECLARE_LINE) \
        _ZFP_ZFMETHOD_GENERIC_INVOKER_DECLARE( \
            ReturnType, MethodName##_##DECLARE_LINE \
            , ParamExpandOrEmpty0, ParamType0, param0, DefaultValueFix0 \
            , ParamExpandOrEmpty1, ParamType1, param1, DefaultValueFix1 \
            , ParamExpandOrEmpty2, ParamType2, param2, DefaultValueFix2 \
            , ParamExpandOrEmpty3, ParamType3, param3, DefaultValueFix3 \
            , ParamExpandOrEmpty4, ParamType4, param4, DefaultValueFix4 \
            , ParamExpandOrEmpty5, ParamType5, param5, DefaultValueFix5 \
            , ParamExpandOrEmpty6, ParamType6, param6, DefaultValueFix6 \
            , ParamExpandOrEmpty7, ParamType7, param7, DefaultValueFix7 \
            ) \
    public: \
        static const ZFMethod *_ZFP_Mtd_##MethodName##_##DECLARE_LINE(void) \
        { \
            static _ZFP_ZFMethodRegisterHolder _methodHolder(zffalse \
                    , ZFCastReinterpret(ZFFuncAddrType, &zfself::_ZFP_MtdI_##MethodName##_##DECLARE_LINE) \
                    , _ZFP_ZFMETHOD_GENERIC_INVOKER_ADDR(ReturnType, MethodName##_##DECLARE_LINE) \
                    , _ZFP_ZFMethodIsWhatTypeText(ZFMethodIsWhatType) \
                    , zfself::ClassData() \
                    , _ZFP_ZFMethod_initClassMemberType_privilege(PublicOrProtectedOrPrivate) \
                    , zfnull \
                    , ZFM_TOSTRING(DECLARE_LINE) \
                    , ZFM_TOSTRING(MethodName) \
                    , ZFPropertyTypeIdData<typename zftTraitsType<ReturnType>::TraitsRemoveReference>::PropertyTypeId() \
                    , zfText(#ReturnType) \
                    ParamExpandOrEmpty0(ZFM_EMPTY() \
                            , ZFPropertyTypeIdData<typename zftTraitsType<ParamType0>::TraitsRemoveReference>::PropertyTypeId() \
                            , zfText(#ParamType0) \
                            , ZFM_TOSTRING_DIRECT(DefaultValueFix0()) \
                            , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(MethodName##_##DECLARE_LINE, 0) \
                        ) \
                    ParamExpandOrEmpty1(ZFM_EMPTY() \
                            , ZFPropertyTypeIdData<typename zftTraitsType<ParamType1>::TraitsRemoveReference>::PropertyTypeId() \
                            , zfText(#ParamType1) \
                            , ZFM_TOSTRING_DIRECT(DefaultValueFix1()) \
                            , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(MethodName##_##DECLARE_LINE, 1) \
                        ) \
                    ParamExpandOrEmpty2(ZFM_EMPTY() \
                            , ZFPropertyTypeIdData<typename zftTraitsType<ParamType2>::TraitsRemoveReference>::PropertyTypeId() \
                            , zfText(#ParamType2) \
                            , ZFM_TOSTRING_DIRECT(DefaultValueFix2()) \
                            , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(MethodName##_##DECLARE_LINE, 2) \
                        ) \
                    ParamExpandOrEmpty3(ZFM_EMPTY() \
                            , ZFPropertyTypeIdData<typename zftTraitsType<ParamType3>::TraitsRemoveReference>::PropertyTypeId() \
                            , zfText(#ParamType3) \
                            , ZFM_TOSTRING_DIRECT(DefaultValueFix3()) \
                            , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(MethodName##_##DECLARE_LINE, 3) \
                        ) \
                    ParamExpandOrEmpty4(ZFM_EMPTY() \
                            , ZFPropertyTypeIdData<typename zftTraitsType<ParamType4>::TraitsRemoveReference>::PropertyTypeId() \
                            , zfText(#ParamType4) \
                            , ZFM_TOSTRING_DIRECT(DefaultValueFix4()) \
                            , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(MethodName##_##DECLARE_LINE, 4) \
                        ) \
                    ParamExpandOrEmpty5(ZFM_EMPTY() \
                            , ZFPropertyTypeIdData<typename zftTraitsType<ParamType5>::TraitsRemoveReference>::PropertyTypeId() \
                            , zfText(#ParamType5) \
                            , ZFM_TOSTRING_DIRECT(DefaultValueFix5()) \
                            , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(MethodName##_##DECLARE_LINE, 5) \
                        ) \
                    ParamExpandOrEmpty6(ZFM_EMPTY() \
                            , ZFPropertyTypeIdData<typename zftTraitsType<ParamType6>::TraitsRemoveReference>::PropertyTypeId() \
                            , zfText(#ParamType6) \
                            , ZFM_TOSTRING_DIRECT(DefaultValueFix6()) \
                            , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(MethodName##_##DECLARE_LINE, 6) \
                        ) \
                    ParamExpandOrEmpty7(ZFM_EMPTY() \
                            , ZFPropertyTypeIdData<typename zftTraitsType<ParamType7>::TraitsRemoveReference>::PropertyTypeId() \
                            , zfText(#ParamType7) \
                            , ZFM_TOSTRING_DIRECT(DefaultValueFix7()) \
                            , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(MethodName##_##DECLARE_LINE, 7) \
                        ) \
                    , zfnull \
                ); \
            return _methodHolder.method; \
        } \
        static const ZFMethod *_ZFP_Mtd_##MethodName(void (*)( \
            ParamExpandOrEmpty0(ZFM_EMPTY() ParamType0) \
            ParamExpandOrEmpty1(ZFM_COMMA() ParamType1) \
            ParamExpandOrEmpty2(ZFM_COMMA() ParamType2) \
            ParamExpandOrEmpty3(ZFM_COMMA() ParamType3) \
            ParamExpandOrEmpty4(ZFM_COMMA() ParamType4) \
            ParamExpandOrEmpty5(ZFM_COMMA() ParamType5) \
            ParamExpandOrEmpty6(ZFM_COMMA() ParamType6) \
            ParamExpandOrEmpty7(ZFM_COMMA() ParamType7) \
            )) /* tricks to support overload method */ \
        { \
            return _ZFP_Mtd_##MethodName##_##DECLARE_LINE(); \
        } \
        static inline ReturnType _ZFP_MtdI_##MethodName##_##DECLARE_LINE( \
            ZF_IN const ZFMethod *method, \
            ZF_IN ZFObject *obj \
            ParamExpandOrEmpty0(ZFM_COMMA() ParamType0 param0) \
            ParamExpandOrEmpty1(ZFM_COMMA() ParamType1 param1) \
            ParamExpandOrEmpty2(ZFM_COMMA() ParamType2 param2) \
            ParamExpandOrEmpty3(ZFM_COMMA() ParamType3 param3) \
            ParamExpandOrEmpty4(ZFM_COMMA() ParamType4 param4) \
            ParamExpandOrEmpty5(ZFM_COMMA() ParamType5 param5) \
            ParamExpandOrEmpty6(ZFM_COMMA() ParamType6 param6) \
            ParamExpandOrEmpty7(ZFM_COMMA() ParamType7 param7) \
            ) \
        { \
            return ZFCastZFObjectUnchecked(zfself *, obj)->MethodName( \
                ParamExpandOrEmpty0(            param0) \
                ParamExpandOrEmpty1(ZFM_COMMA() param1) \
                ParamExpandOrEmpty2(ZFM_COMMA() param2) \
                ParamExpandOrEmpty3(ZFM_COMMA() param3) \
                ParamExpandOrEmpty4(ZFM_COMMA() param4) \
                ParamExpandOrEmpty5(ZFM_COMMA() param5) \
                ParamExpandOrEmpty6(ZFM_COMMA() param6) \
                ParamExpandOrEmpty7(ZFM_COMMA() param7) \
                ); \
        } \
    /** @endcond */ \
    PublicOrProtectedOrPrivate: \
        ZFMethodIsWhatType() ReturnType MethodName( \
            ParamExpandOrEmpty0(            ParamType0 param0 DefaultValueFix0()) \
            ParamExpandOrEmpty1(ZFM_COMMA() ParamType1 param1 DefaultValueFix1()) \
            ParamExpandOrEmpty2(ZFM_COMMA() ParamType2 param2 DefaultValueFix2()) \
            ParamExpandOrEmpty3(ZFM_COMMA() ParamType3 param3 DefaultValueFix3()) \
            ParamExpandOrEmpty4(ZFM_COMMA() ParamType4 param4 DefaultValueFix4()) \
            ParamExpandOrEmpty5(ZFM_COMMA() ParamType5 param5 DefaultValueFix5()) \
            ParamExpandOrEmpty6(ZFM_COMMA() ParamType6 param6 DefaultValueFix6()) \
            ParamExpandOrEmpty7(ZFM_COMMA() ParamType7 param7 DefaultValueFix7()) \
            )

#define _ZFP_ZFMETHOD_DEFINE(...) \
    ZFM_EXPAND(_ZFP_ZFMETHOD_DEFINE_(__VA_ARGS__))
#define _ZFP_ZFMETHOD_DEFINE_(OwnerClass, ReturnType, MethodName \
    , ParamExpandOrEmpty0, ParamType0, param0, DefaultValueFix0 \
    , ParamExpandOrEmpty1, ParamType1, param1, DefaultValueFix1 \
    , ParamExpandOrEmpty2, ParamType2, param2, DefaultValueFix2 \
    , ParamExpandOrEmpty3, ParamType3, param3, DefaultValueFix3 \
    , ParamExpandOrEmpty4, ParamType4, param4, DefaultValueFix4 \
    , ParamExpandOrEmpty5, ParamType5, param5, DefaultValueFix5 \
    , ParamExpandOrEmpty6, ParamType6, param6, DefaultValueFix6 \
    , ParamExpandOrEmpty7, ParamType7, param7, DefaultValueFix7 \
    ) \
    ReturnType OwnerClass::MethodName( \
        ParamExpandOrEmpty0(            ParamType0 param0) \
        ParamExpandOrEmpty1(ZFM_COMMA() ParamType1 param1) \
        ParamExpandOrEmpty2(ZFM_COMMA() ParamType2 param2) \
        ParamExpandOrEmpty3(ZFM_COMMA() ParamType3 param3) \
        ParamExpandOrEmpty4(ZFM_COMMA() ParamType4 param4) \
        ParamExpandOrEmpty5(ZFM_COMMA() ParamType5 param5) \
        ParamExpandOrEmpty6(ZFM_COMMA() ParamType6 param6) \
        ParamExpandOrEmpty7(ZFM_COMMA() ParamType7 param7) \
        )

#define _ZFP_ZFMETHOD_OVERRIDE_DECLARE(...) \
    ZFM_EXPAND(_ZFP_ZFMETHOD_OVERRIDE_DECLARE_(__VA_ARGS__))
#define _ZFP_ZFMETHOD_OVERRIDE_DECLARE_( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ParamExpandOrEmpty0, ParamType0, param0, DefaultValueFix0 \
    , ParamExpandOrEmpty1, ParamType1, param1, DefaultValueFix1 \
    , ParamExpandOrEmpty2, ParamType2, param2, DefaultValueFix2 \
    , ParamExpandOrEmpty3, ParamType3, param3, DefaultValueFix3 \
    , ParamExpandOrEmpty4, ParamType4, param4, DefaultValueFix4 \
    , ParamExpandOrEmpty5, ParamType5, param5, DefaultValueFix5 \
    , ParamExpandOrEmpty6, ParamType6, param6, DefaultValueFix6 \
    , ParamExpandOrEmpty7, ParamType7, param7, DefaultValueFix7 \
    ) \
    PublicOrProtectedOrPrivate: \
        ZFMethodIsWhatType() ReturnType MethodName( \
            ParamExpandOrEmpty0(            ParamType0 param0 DefaultValueFix0()) \
            ParamExpandOrEmpty1(ZFM_COMMA() ParamType1 param1 DefaultValueFix1()) \
            ParamExpandOrEmpty2(ZFM_COMMA() ParamType2 param2 DefaultValueFix2()) \
            ParamExpandOrEmpty3(ZFM_COMMA() ParamType3 param3 DefaultValueFix3()) \
            ParamExpandOrEmpty4(ZFM_COMMA() ParamType4 param4 DefaultValueFix4()) \
            ParamExpandOrEmpty5(ZFM_COMMA() ParamType5 param5 DefaultValueFix5()) \
            ParamExpandOrEmpty6(ZFM_COMMA() ParamType6 param6 DefaultValueFix6()) \
            ParamExpandOrEmpty7(ZFM_COMMA() ParamType7 param7 DefaultValueFix7()) \
            )

#define _ZFP_ZFMETHOD_OVERRIDE_DEFINE(...) \
    ZFM_EXPAND(_ZFP_ZFMETHOD_OVERRIDE_DEFINE_(__VA_ARGS__))
#define _ZFP_ZFMETHOD_OVERRIDE_DEFINE_(OwnerClass, ReturnType, MethodName \
    , ParamExpandOrEmpty0, ParamType0, param0, DefaultValueFix0 \
    , ParamExpandOrEmpty1, ParamType1, param1, DefaultValueFix1 \
    , ParamExpandOrEmpty2, ParamType2, param2, DefaultValueFix2 \
    , ParamExpandOrEmpty3, ParamType3, param3, DefaultValueFix3 \
    , ParamExpandOrEmpty4, ParamType4, param4, DefaultValueFix4 \
    , ParamExpandOrEmpty5, ParamType5, param5, DefaultValueFix5 \
    , ParamExpandOrEmpty6, ParamType6, param6, DefaultValueFix6 \
    , ParamExpandOrEmpty7, ParamType7, param7, DefaultValueFix7 \
    ) \
    ReturnType OwnerClass::MethodName( \
        ParamExpandOrEmpty0(            ParamType0 param0) \
        ParamExpandOrEmpty1(ZFM_COMMA() ParamType1 param1) \
        ParamExpandOrEmpty2(ZFM_COMMA() ParamType2 param2) \
        ParamExpandOrEmpty3(ZFM_COMMA() ParamType3 param3) \
        ParamExpandOrEmpty4(ZFM_COMMA() ParamType4 param4) \
        ParamExpandOrEmpty5(ZFM_COMMA() ParamType5 param5) \
        ParamExpandOrEmpty6(ZFM_COMMA() ParamType6 param6) \
        ParamExpandOrEmpty7(ZFM_COMMA() ParamType7 param7) \
        )

#define _ZFP_ZFMETHOD_REGISTER(...) \
    _ZFP_ZFMETHOD_REGISTER_(__VA_ARGS__)
#define _ZFP_ZFMETHOD_REGISTER_(OwnerClass, MethodName, DECLARE_LINE) \
    ZF_STATIC_INITIALIZER_INIT(MtdR_##OwnerClass##_##MethodName##_##DECLARE_LINE) \
    { \
        (void)OwnerClass::_ZFP_Mtd_##MethodName(zfnull); \
    } \
    ZF_STATIC_INITIALIZER_END(MtdR_##OwnerClass##_##MethodName##_##DECLARE_LINE)
#define _ZFP_ZFMETHOD_REGISTER_DETAIL(...) \
    _ZFP_ZFMETHOD_REGISTER_DETAIL_(__VA_ARGS__)
#define _ZFP_ZFMETHOD_REGISTER_DETAIL_(OwnerClass, MethodName, DECLARE_LINE \
        , ParamExpandOrEmpty0, ParamType0 \
        , ParamExpandOrEmpty1, ParamType1 \
        , ParamExpandOrEmpty2, ParamType2 \
        , ParamExpandOrEmpty3, ParamType3 \
        , ParamExpandOrEmpty4, ParamType4 \
        , ParamExpandOrEmpty5, ParamType5 \
        , ParamExpandOrEmpty6, ParamType6 \
        , ParamExpandOrEmpty7, ParamType7 \
    ) \
    ZF_STATIC_INITIALIZER_INIT(MtdR_##OwnerClass##_##MethodName##_##DECLARE_LINE) \
    { \
        (void)OwnerClass::_ZFP_Mtd_##MethodName((void (*)( \
               ParamExpandOrEmpty0(ZFM_EMPTY() ParamType0) \
               ParamExpandOrEmpty1(ZFM_COMMA() ParamType1) \
               ParamExpandOrEmpty2(ZFM_COMMA() ParamType2) \
               ParamExpandOrEmpty3(ZFM_COMMA() ParamType3) \
               ParamExpandOrEmpty4(ZFM_COMMA() ParamType4) \
               ParamExpandOrEmpty5(ZFM_COMMA() ParamType5) \
               ParamExpandOrEmpty6(ZFM_COMMA() ParamType6) \
               ParamExpandOrEmpty7(ZFM_COMMA() ParamType7) \
           ))zfnull); \
    } \
    ZF_STATIC_INITIALIZER_END(MtdR_##OwnerClass##_##MethodName##_##DECLARE_LINE)

/**
 * @brief see #ZFMethod
 *
 * statically register a method\n
 * you can find the method in its owner class only if it's registered,
 * which can be achieved by any of these:
 * -  any instance of owner class has ever been created,
 *   by default, #ZFClass would do the registration work for you
 *   if the owner class is not an abstract class
 * -  ZFMETHOD_REGISTER is declared
 */
#define ZFMETHOD_REGISTER(OwnerClass, MethodName) \
    _ZFP_ZFMETHOD_REGISTER(OwnerClass, MethodName, ZF_CALLER_LINE)

/** @brief see #ZFMethod, #ZFMETHOD_REGISTER */
#define ZFMETHOD_REGISTER_DETAIL_0(OwnerClass, MethodName \
    ) \
    _ZFP_ZFMETHOD_REGISTER_DETAIL(OwnerClass, MethodName, ZF_CALLER_LINE \
            , ZFM_EMPTY,  ParamType0 \
            , ZFM_EMPTY,  ParamType1 \
            , ZFM_EMPTY,  ParamType2 \
            , ZFM_EMPTY,  ParamType3 \
            , ZFM_EMPTY,  ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod, #ZFMETHOD_REGISTER */
#define ZFMETHOD_REGISTER_DETAIL_1(OwnerClass, MethodName \
        , ParamType0 \
    ) \
    _ZFP_ZFMETHOD_REGISTER_DETAIL(OwnerClass, MethodName, ZF_CALLER_LINE \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EMPTY,  ParamType1 \
            , ZFM_EMPTY,  ParamType2 \
            , ZFM_EMPTY,  ParamType3 \
            , ZFM_EMPTY,  ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod, #ZFMETHOD_REGISTER */
#define ZFMETHOD_REGISTER_DETAIL_2(OwnerClass, MethodName \
        , ParamType0 \
        , ParamType1 \
    ) \
    _ZFP_ZFMETHOD_REGISTER_DETAIL(OwnerClass, MethodName, ZF_CALLER_LINE \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EMPTY,  ParamType2 \
            , ZFM_EMPTY,  ParamType3 \
            , ZFM_EMPTY,  ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod, #ZFMETHOD_REGISTER */
#define ZFMETHOD_REGISTER_DETAIL_3(OwnerClass, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
    ) \
    _ZFP_ZFMETHOD_REGISTER_DETAIL(OwnerClass, MethodName, ZF_CALLER_LINE \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EMPTY,  ParamType3 \
            , ZFM_EMPTY,  ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod, #ZFMETHOD_REGISTER */
#define ZFMETHOD_REGISTER_DETAIL_4(OwnerClass, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
        , ParamType3 \
    ) \
    _ZFP_ZFMETHOD_REGISTER_DETAIL(OwnerClass, MethodName, ZF_CALLER_LINE \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EXPAND, ParamType3 \
            , ZFM_EMPTY,  ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod, #ZFMETHOD_REGISTER */
#define ZFMETHOD_REGISTER_DETAIL_5(OwnerClass, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
        , ParamType3 \
        , ParamType4 \
    ) \
    _ZFP_ZFMETHOD_REGISTER_DETAIL(OwnerClass, MethodName, ZF_CALLER_LINE \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EXPAND, ParamType3 \
            , ZFM_EXPAND, ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod, #ZFMETHOD_REGISTER */
#define ZFMETHOD_REGISTER_DETAIL_6(OwnerClass, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
        , ParamType3 \
        , ParamType4 \
        , ParamType5 \
    ) \
    _ZFP_ZFMETHOD_REGISTER_DETAIL(OwnerClass, MethodName, ZF_CALLER_LINE \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EXPAND, ParamType3 \
            , ZFM_EXPAND, ParamType4 \
            , ZFM_EXPAND, ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod, #ZFMETHOD_REGISTER */
#define ZFMETHOD_REGISTER_DETAIL_7(OwnerClass, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
        , ParamType3 \
        , ParamType4 \
        , ParamType5 \
        , ParamType6 \
    ) \
    _ZFP_ZFMETHOD_REGISTER_DETAIL(OwnerClass, MethodName, ZF_CALLER_LINE \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EXPAND, ParamType3 \
            , ZFM_EXPAND, ParamType4 \
            , ZFM_EXPAND, ParamType5 \
            , ZFM_EXPAND, ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMethod, #ZFMETHOD_REGISTER */
#define ZFMETHOD_REGISTER_DETAIL_8(OwnerClass, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
        , ParamType3 \
        , ParamType4 \
        , ParamType5 \
        , ParamType6 \
        , ParamType7 \
    ) \
    _ZFP_ZFMETHOD_REGISTER_DETAIL(OwnerClass, MethodName, ZF_CALLER_LINE \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EXPAND, ParamType3 \
            , ZFM_EXPAND, ParamType4 \
            , ZFM_EXPAND, ParamType5 \
            , ZFM_EXPAND, ParamType6 \
            , ZFM_EXPAND, ParamType7 \
        )

// ============================================================
// 0 param method declare
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_0(ReturnType, MethodName \
    ) \
    ZFMETHOD_DECLARE_DETAIL_0( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_STATIC_0(ReturnType, MethodName \
    ) \
    ZFMETHOD_DECLARE_DETAIL_0( \
        public, ZFMethodIsStatic, \
        ReturnType, MethodName \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_DETAIL_0( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        isAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EMPTY,  ParamType0, param0, DefaultValueFix0 \
        , ZFM_EMPTY,  ParamType1, param1, DefaultValueFix1 \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_NO_AUTOREGISTER_0( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        notAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EMPTY,  ParamType0, param0, DefaultValueFix0 \
        , ZFM_EMPTY,  ParamType1, param1, DefaultValueFix1 \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DEFINE_0(OwnerClass, ReturnType, MethodName \
    ) \
    _ZFP_ZFMETHOD_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EMPTY,  ParamType0, param0, DefaultValueFix0 \
        , ZFM_EMPTY,  ParamType1, param1, DefaultValueFix1 \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
// ============================================================
// 0 param method override declare
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_0(ReturnType, MethodName \
    ) \
    ZFMETHOD_OVERRIDE_DECLARE_DETAIL_0( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_DETAIL_0( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DECLARE( \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName \
        , ZFM_EMPTY,  ParamType0, param0, DefaultValueFix0 \
        , ZFM_EMPTY,  ParamType1, param1, DefaultValueFix1 \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DEFINE_0(OwnerClass, ReturnType, MethodName \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EMPTY,  ParamType0, param0, DefaultValueFix0 \
        , ZFM_EMPTY,  ParamType1, param1, DefaultValueFix1 \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )

// ============================================================
// 1 param method declare
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_1(ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_1( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_STATIC_1(ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_1( \
        public, ZFMethodIsStatic, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_DETAIL_1( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        isAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EMPTY,  ParamType1, param1, DefaultValueFix1 \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_NO_AUTOREGISTER_1( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        notAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EMPTY,  ParamType1, param1, DefaultValueFix1 \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DEFINE_1(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    _ZFP_ZFMETHOD_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EMPTY,  ParamType1, param1, DefaultValueFix1 \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
// ============================================================
// 1 param method override declare
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_1(ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    ZFMETHOD_OVERRIDE_DECLARE_DETAIL_1( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_DETAIL_1( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DECLARE( \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EMPTY,  ParamType1, param1, DefaultValueFix1 \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DEFINE_1(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EMPTY,  ParamType1, param1, DefaultValueFix1 \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )

// ============================================================
// 2 param method declare
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_2(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_2( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_STATIC_2(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_2( \
        public, ZFMethodIsStatic, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_DETAIL_2( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        isAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_NO_AUTOREGISTER_2( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        notAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DEFINE_2(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    _ZFP_ZFMETHOD_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
// ============================================================
// 2 param method override declare
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_2(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    ZFMETHOD_OVERRIDE_DECLARE_DETAIL_2( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_DETAIL_2( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DECLARE( \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DEFINE_2(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )

// ============================================================
// 3 param method declare
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_3(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_3( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_STATIC_3(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_3( \
        public, ZFMethodIsStatic, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_DETAIL_3( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        isAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_NO_AUTOREGISTER_3( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        notAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DEFINE_3(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    _ZFP_ZFMETHOD_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
// ============================================================
// 3 param method override declare
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_3(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    ZFMETHOD_OVERRIDE_DECLARE_DETAIL_3( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_DETAIL_3( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DECLARE( \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DEFINE_3(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )

// ============================================================
// 4 param method declare
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_4(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_4( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_STATIC_4(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_4( \
        public, ZFMethodIsStatic, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_DETAIL_4( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        isAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_NO_AUTOREGISTER_4( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        notAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DEFINE_4(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    _ZFP_ZFMETHOD_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )

// ============================================================
// 4 param method override declare
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_4(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    ZFMETHOD_OVERRIDE_DECLARE_DETAIL_4( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_DETAIL_4( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DECLARE( \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DEFINE_4(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )

// ============================================================
// 5 param method declare
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_5(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_5( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_STATIC_5(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_5( \
        public, ZFMethodIsStatic, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_DETAIL_5( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        isAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_NO_AUTOREGISTER_5( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        notAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DEFINE_5(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    _ZFP_ZFMETHOD_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )

// ============================================================
// 5 param method override declare
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_5(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    ZFMETHOD_OVERRIDE_DECLARE_DETAIL_5( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_DETAIL_5( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DECLARE( \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DEFINE_5(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )

// ============================================================
// 6 param method declare
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_6(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_6( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_STATIC_6(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_6( \
        public, ZFMethodIsStatic, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_DETAIL_6( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        isAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_NO_AUTOREGISTER_6( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        notAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DEFINE_6(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    _ZFP_ZFMETHOD_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )

// ============================================================
// 6 param method override declare
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_6(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    ZFMETHOD_OVERRIDE_DECLARE_DETAIL_6( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_DETAIL_6( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DECLARE( \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DEFINE_6(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )

// ============================================================
// 7 param method declare
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_7(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_7( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_STATIC_7(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_7( \
        public, ZFMethodIsStatic, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_DETAIL_7( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        isAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_6) \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_NO_AUTOREGISTER_7( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        notAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_6) \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DEFINE_7(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    _ZFP_ZFMETHOD_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_6) \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )

// ============================================================
// 7 param method override declare
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_7(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    ZFMETHOD_OVERRIDE_DECLARE_DETAIL_7( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_DETAIL_7( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DECLARE( \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_6) \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DEFINE_7(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_6) \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )

// ============================================================
// 8 param method declare
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_8(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_8( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_STATIC_8(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    ZFMETHOD_DECLARE_DETAIL_8( \
        public, ZFMethodIsStatic, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_DETAIL_8( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        isAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DECLARE_NO_AUTOREGISTER_8( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    _ZFP_ZFMETHOD_DECLARE( \
        notAutoRegister, \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_DEFINE_8(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    _ZFP_ZFMETHOD_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_7) \
        )

// ============================================================
// 8 param method override declare
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_8(ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    ZFMETHOD_OVERRIDE_DECLARE_DETAIL_8( \
        public, ZFMethodIsVirtual, \
        ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DECLARE_DETAIL_8( \
    PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DECLARE( \
        PublicOrProtectedOrPrivate, ZFMethodIsWhatType, \
        ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMethod */
#define ZFMETHOD_OVERRIDE_DEFINE_8(OwnerClass, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    _ZFP_ZFMETHOD_OVERRIDE_DEFINE(OwnerClass, ReturnType, MethodName \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_7) \
        )
/* ZFMETHOD_MAX_PARAM */

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFMethodDeclare_h_

