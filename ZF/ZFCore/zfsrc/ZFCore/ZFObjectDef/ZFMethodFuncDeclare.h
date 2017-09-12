/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFMethodFuncDeclare.h
 * @brief ZFMethod declaration
 */

#ifndef _ZFI_ZFMethodFuncDeclare_h_
#define _ZFI_ZFMethodFuncDeclare_h_

#include "ZFMethod.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
extern ZF_ENV_EXPORT void _ZFP_ZFMethodFuncRegister(ZF_IN const ZFMethod *method);
extern ZF_ENV_EXPORT void _ZFP_ZFMethodFuncUnregister(ZF_IN const ZFMethod *method);

/**
 * @brief util method to find ZFMethod, return null if method not registered,
 *   see #ZFMETHOD_FUNC_DECLARE_0
 */
extern ZF_ENV_EXPORT const ZFMethod *ZFMethodFuncGet(ZF_IN const zfchar *methodNamespace,
                                                     ZF_IN const zfchar *methodName);
/** @brief see #ZFMethodFuncGet */
extern ZF_ENV_EXPORT const ZFMethod *ZFMethodFuncGet(ZF_IN const zfchar *methodNamespace,
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
 * @brief get all function type method currently registered, for debug use only
 */
extern ZF_ENV_EXPORT void ZFMethodFuncGetAllT(ZF_IN_OUT ZFCoreArray<const ZFMethod *> &ret,
                                              ZF_IN_OPT const ZFFilterForZFMethod *filter = zfnull);
/**
 * @brief get all function type method currently registered, for debug use only
 */
inline ZFCoreArrayPOD<const ZFMethod *> ZFMethodFuncGetAll(ZF_IN_OPT const ZFFilterForZFMethod *filter = zfnull)
{
    ZFCoreArrayPOD<const ZFMethod *> ret;
    ZFMethodFuncGetAllT(ret, filter);
    return ret;
}
/**
 * @brief get all function type method with specified methodNamespace and methodName
 */
extern ZF_ENV_EXPORT void ZFMethodFuncGetAllT(ZF_IN_OUT ZFCoreArray<const ZFMethod *> &ret,
                                              ZF_IN const zfchar *methodNamespace,
                                              ZF_IN const zfchar *methodName,
                                              ZF_IN_OPT const ZFFilterForZFMethod *filter = zfnull);
/**
 * @brief get all function type method with specified methodNamespace and methodName
 */
inline ZFCoreArrayPOD<const ZFMethod *> ZFMethodFuncGetAll(ZF_IN const zfchar *methodNamespace,
                                                           ZF_IN const zfchar *methodName,
                                                           ZF_IN_OPT const ZFFilterForZFMethod *filter = zfnull)
{
    ZFCoreArrayPOD<const ZFMethod *> ret;
    ZFMethodFuncGetAllT(ret, methodNamespace, methodName, filter);
    return ret;
}

// ============================================================
#define _ZFP_ZFMethodFuncAccess(MethodNamespace, MethodName) \
    _ZFP_ZFMethodFuncAccess_(MethodNamespace, MethodName)
#define _ZFP_ZFMethodFuncAccess_(MethodNamespace, MethodName) \
    (_ZFP_ZFMethodFuncAccess_##MethodNamespace##_##MethodName(zfnull))
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMethodFuncAccess(MethodName) \
    _ZFP_ZFMethodFuncAccess(ZFMethodFuncNamespaceGlobalId, MethodName)

#define _ZFP_ZFMethodFuncAccessDetail(MethodNamespace, MethodName \
        , ParamExpandOrEmpty0, ParamType0 \
        , ParamExpandOrEmpty1, ParamType1 \
        , ParamExpandOrEmpty2, ParamType2 \
        , ParamExpandOrEmpty3, ParamType3 \
        , ParamExpandOrEmpty4, ParamType4 \
        , ParamExpandOrEmpty5, ParamType5 \
        , ParamExpandOrEmpty6, ParamType6 \
        , ParamExpandOrEmpty7, ParamType7 \
    ) \
    (_ZFP_ZFMethodFuncAccess_##MethodNamespace##_##MethodName((void (*)( \
           ParamExpandOrEmpty0(ZFM_EMPTY() ParamType0) \
           ParamExpandOrEmpty1(ZFM_COMMA() ParamType1) \
           ParamExpandOrEmpty2(ZFM_COMMA() ParamType2) \
           ParamExpandOrEmpty3(ZFM_COMMA() ParamType3) \
           ParamExpandOrEmpty4(ZFM_COMMA() ParamType4) \
           ParamExpandOrEmpty5(ZFM_COMMA() ParamType5) \
           ParamExpandOrEmpty6(ZFM_COMMA() ParamType6) \
           ParamExpandOrEmpty7(ZFM_COMMA() ParamType7) \
        ))zfnull))
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMethodFuncAccessDetail_0(MethodNamespace, MethodName \
    ) \
    _ZFP_ZFMethodFuncAccessDetail(MethodNamespace, MethodName \
            , ZFM_EMPTY,  ParamType0 \
            , ZFM_EMPTY,  ParamType1 \
            , ZFM_EMPTY,  ParamType2 \
            , ZFM_EMPTY,  ParamType3 \
            , ZFM_EMPTY,  ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMethodFuncAccessDetail_1(MethodNamespace, MethodName \
        , ParamType0 \
    ) \
    _ZFP_ZFMethodFuncAccessDetail(MethodNamespace, MethodName \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EMPTY,  ParamType1 \
            , ZFM_EMPTY,  ParamType2 \
            , ZFM_EMPTY,  ParamType3 \
            , ZFM_EMPTY,  ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMethodFuncAccessDetail_2(MethodNamespace, MethodName \
        , ParamType0 \
        , ParamType1 \
    ) \
    _ZFP_ZFMethodFuncAccessDetail(MethodNamespace, MethodName \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EMPTY,  ParamType2 \
            , ZFM_EMPTY,  ParamType3 \
            , ZFM_EMPTY,  ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMethodFuncAccessDetail_3(MethodNamespace, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
    ) \
    _ZFP_ZFMethodFuncAccessDetail(MethodNamespace, MethodName \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EMPTY,  ParamType3 \
            , ZFM_EMPTY,  ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMethodFuncAccessDetail_4(MethodNamespace, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
        , ParamType3 \
    ) \
    _ZFP_ZFMethodFuncAccessDetail(MethodNamespace, MethodName \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EXPAND, ParamType3 \
            , ZFM_EMPTY,  ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMethodFuncAccessDetail_5(MethodNamespace, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
        , ParamType3 \
        , ParamType4 \
    ) \
    _ZFP_ZFMethodFuncAccessDetail(MethodNamespace, MethodName \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EXPAND, ParamType3 \
            , ZFM_EXPAND, ParamType4 \
            , ZFM_EMPTY,  ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMethodFuncAccessDetail_6(MethodNamespace, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
        , ParamType3 \
        , ParamType4 \
        , ParamType5 \
    ) \
    _ZFP_ZFMethodFuncAccessDetail(MethodNamespace, MethodName \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EXPAND, ParamType3 \
            , ZFM_EXPAND, ParamType4 \
            , ZFM_EXPAND, ParamType5 \
            , ZFM_EMPTY,  ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMethodFuncAccessDetail_7(MethodNamespace, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
        , ParamType3 \
        , ParamType4 \
        , ParamType5 \
        , ParamType6 \
    ) \
    _ZFP_ZFMethodFuncAccessDetail(MethodNamespace, MethodName \
            , ZFM_EXPAND, ParamType0 \
            , ZFM_EXPAND, ParamType1 \
            , ZFM_EXPAND, ParamType2 \
            , ZFM_EXPAND, ParamType3 \
            , ZFM_EXPAND, ParamType4 \
            , ZFM_EXPAND, ParamType5 \
            , ZFM_EXPAND, ParamType6 \
            , ZFM_EMPTY,  ParamType7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMethodFuncAccessDetail_8(MethodNamespace, MethodName \
        , ParamType0 \
        , ParamType1 \
        , ParamType2 \
        , ParamType3 \
        , ParamType4 \
        , ParamType5 \
        , ParamType6 \
        , ParamType7 \
    ) \
    _ZFP_ZFMethodFuncAccessDetail(MethodNamespace, MethodName \
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
/** @brief see #ZFMETHOD_FUNC_DECLARE_DETAIL_0 */
#define ZFMethodFuncIsInline isInline
/** @brief see #ZFMETHOD_FUNC_DECLARE_DETAIL_0 */
#define ZFMethodFuncNotInline notInline

#define _ZFP_ZFMETHOD_FUNC_DECLARE_inlinePrefix_isInline() inline
#define _ZFP_ZFMETHOD_FUNC_DECLARE_inlinePrefix_notInline() extern ZF_ENV_EXPORT
#define _ZFP_ZFMETHOD_FUNC_DECLARE_inlinePrefix(ZFMethodFuncIsInlineOrNotInline) _ZFP_ZFMETHOD_FUNC_DECLARE_inlinePrefix_##ZFMethodFuncIsInlineOrNotInline()

#define _ZFP_ZFMETHOD_FUNC_DECLARE_inlinePostfix_isInline()
#define _ZFP_ZFMETHOD_FUNC_DECLARE_inlinePostfix_notInline() ;
#define _ZFP_ZFMETHOD_FUNC_DECLARE_inlinePostfix(ZFMethodFuncIsInlineOrNotInline) _ZFP_ZFMETHOD_FUNC_DECLARE_inlinePostfix_##ZFMethodFuncIsInlineOrNotInline()

#define _ZFP_ZFMETHOD_FUNC_DEFINE_inlinePrefix_isInline() inline
#define _ZFP_ZFMETHOD_FUNC_DEFINE_inlinePrefix_notInline() extern ZF_ENV_EXPORT
#define _ZFP_ZFMETHOD_FUNC_DEFINE_inlinePrefix(ZFMethodFuncIsInlineOrNotInline) _ZFP_ZFMETHOD_FUNC_DEFINE_inlinePrefix_##ZFMethodFuncIsInlineOrNotInline()

#define _ZFP_ZFMETHOD_FUNC_DEFINE_inlinePostfix_isInline() ;
#define _ZFP_ZFMETHOD_FUNC_DEFINE_inlinePostfix_notInline()
#define _ZFP_ZFMETHOD_FUNC_DEFINE_inlinePostfix(ZFMethodFuncIsInlineOrNotInline) _ZFP_ZFMETHOD_FUNC_DEFINE_inlinePostfix_##ZFMethodFuncIsInlineOrNotInline()

// ============================================================
#define _ZFP_ZFMETHOD_FUNC_DECLARE(...) \
    ZFM_EXPAND(_ZFP_ZFMETHOD_FUNC_DECLARE_(__VA_ARGS__))
#define _ZFP_ZFMETHOD_FUNC_DECLARE_( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, DECLARE_LINE \
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
    extern ZF_ENV_EXPORT const ZFMethod *_ZFP_ZFMethodFuncAccess_##MethodNamespace##_##MethodName(void (*)( \
            ParamExpandOrEmpty0(ZFM_EMPTY() ParamType0) \
            ParamExpandOrEmpty1(ZFM_COMMA() ParamType1) \
            ParamExpandOrEmpty2(ZFM_COMMA() ParamType2) \
            ParamExpandOrEmpty3(ZFM_COMMA() ParamType3) \
            ParamExpandOrEmpty4(ZFM_COMMA() ParamType4) \
            ParamExpandOrEmpty5(ZFM_COMMA() ParamType5) \
            ParamExpandOrEmpty6(ZFM_COMMA() ParamType6) \
            ParamExpandOrEmpty7(ZFM_COMMA() ParamType7) \
        )); \
    /** @endcond */ \
    _ZFP_ZFMETHOD_FUNC_DECLARE_inlinePrefix(ZFMethodFuncIsInlineOrNotInline) ReturnType (MethodName)( \
        ParamExpandOrEmpty0(            ParamType0 param0 DefaultValueFix0()) \
        ParamExpandOrEmpty1(ZFM_COMMA() ParamType1 param1 DefaultValueFix1()) \
        ParamExpandOrEmpty2(ZFM_COMMA() ParamType2 param2 DefaultValueFix2()) \
        ParamExpandOrEmpty3(ZFM_COMMA() ParamType3 param3 DefaultValueFix3()) \
        ParamExpandOrEmpty4(ZFM_COMMA() ParamType4 param4 DefaultValueFix4()) \
        ParamExpandOrEmpty5(ZFM_COMMA() ParamType5 param5 DefaultValueFix5()) \
        ParamExpandOrEmpty6(ZFM_COMMA() ParamType6 param6 DefaultValueFix6()) \
        ParamExpandOrEmpty7(ZFM_COMMA() ParamType7 param7 DefaultValueFix7()) \
        ) _ZFP_ZFMETHOD_FUNC_DECLARE_inlinePostfix(ZFMethodFuncIsInlineOrNotInline)

#define _ZFP_ZFMETHOD_FUNC_DEFINE(...) \
    ZFM_EXPAND(_ZFP_ZFMETHOD_FUNC_DEFINE_(__VA_ARGS__))
#define _ZFP_ZFMETHOD_FUNC_DEFINE_( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, DECLARE_LINE \
    , ParamExpandOrEmpty0, ParamType0, param0, DefaultValueFix0 \
    , ParamExpandOrEmpty1, ParamType1, param1, DefaultValueFix1 \
    , ParamExpandOrEmpty2, ParamType2, param2, DefaultValueFix2 \
    , ParamExpandOrEmpty3, ParamType3, param3, DefaultValueFix3 \
    , ParamExpandOrEmpty4, ParamType4, param4, DefaultValueFix4 \
    , ParamExpandOrEmpty5, ParamType5, param5, DefaultValueFix5 \
    , ParamExpandOrEmpty6, ParamType6, param6, DefaultValueFix6 \
    , ParamExpandOrEmpty7, ParamType7, param7, DefaultValueFix7 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DEFINE_inlinePrefix(ZFMethodFuncIsInlineOrNotInline) ReturnType (MethodName)( \
        ParamExpandOrEmpty0(            ParamType0 param0) \
        ParamExpandOrEmpty1(ZFM_COMMA() ParamType1 param1) \
        ParamExpandOrEmpty2(ZFM_COMMA() ParamType2 param2) \
        ParamExpandOrEmpty3(ZFM_COMMA() ParamType3 param3) \
        ParamExpandOrEmpty4(ZFM_COMMA() ParamType4 param4) \
        ParamExpandOrEmpty5(ZFM_COMMA() ParamType5 param5) \
        ParamExpandOrEmpty6(ZFM_COMMA() ParamType6 param6) \
        ParamExpandOrEmpty7(ZFM_COMMA() ParamType7 param7) \
        ); \
    zfclassNotPOD ZF_ENV_EXPORT _ZFP_ZFMethodFuncHolder_##MethodNamespace##_##MethodName##_##DECLARE_LINE \
    { \
    public: \
        _ZFP_ZFMETHOD_GENERIC_INVOKER_DECLARE( \
            ReturnType, _ \
            , ParamExpandOrEmpty0, ParamType0, param0, DefaultValueFix0 \
            , ParamExpandOrEmpty1, ParamType1, param1, DefaultValueFix1 \
            , ParamExpandOrEmpty2, ParamType2, param2, DefaultValueFix2 \
            , ParamExpandOrEmpty3, ParamType3, param3, DefaultValueFix3 \
            , ParamExpandOrEmpty4, ParamType4, param4, DefaultValueFix4 \
            , ParamExpandOrEmpty5, ParamType5, param5, DefaultValueFix5 \
            , ParamExpandOrEmpty6, ParamType6, param6, DefaultValueFix6 \
            , ParamExpandOrEmpty7, ParamType7, param7, DefaultValueFix7 \
            ) \
        static ReturnType methodInvoker( \
            ZF_IN const ZFMethod *invokerMethod, \
            ZF_IN ZFObject *invokerObject \
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
            return (MethodName)( \
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
    }; \
    extern ZF_ENV_EXPORT const ZFMethod *_ZFP_ZFMethodFuncAccess_##MethodNamespace##_##MethodName(void (*)( \
            ParamExpandOrEmpty0(ZFM_EMPTY() ParamType0) \
            ParamExpandOrEmpty1(ZFM_COMMA() ParamType1) \
            ParamExpandOrEmpty2(ZFM_COMMA() ParamType2) \
            ParamExpandOrEmpty3(ZFM_COMMA() ParamType3) \
            ParamExpandOrEmpty4(ZFM_COMMA() ParamType4) \
            ParamExpandOrEmpty5(ZFM_COMMA() ParamType5) \
            ParamExpandOrEmpty6(ZFM_COMMA() ParamType6) \
            ParamExpandOrEmpty7(ZFM_COMMA() ParamType7) \
        )) \
    { \
        static _ZFP_ZFMethodRegisterHolder _methodHolder(zffalse \
                , ZFCastReinterpret(ZFFuncAddrType, &_ZFP_ZFMethodFuncHolder_##MethodNamespace##_##MethodName##_##DECLARE_LINE::methodInvoker) \
                , _ZFP_ZFMethodFuncHolder_##MethodNamespace##_##MethodName##_##DECLARE_LINE:: _ZFP_ZFMETHOD_GENERIC_INVOKER_ADDR(ReturnType, _) \
                , _ZFP_ZFMethodIsWhatTypeText(ZFMethodIsStatic) \
                , zfnull \
                , ZFMethodPrivilegeTypePublic \
                , ZFM_TOSTRING(MethodNamespace) \
                , ZFM_TOSTRING(DECLARE_LINE) \
                , ZFM_TOSTRING(MethodName) \
                , ZFPropertyTypeIdData<zftTraitsType<ReturnType>::TraitsRemoveReference>::PropertyTypeId() \
                , zfText(#ReturnType) \
                ParamExpandOrEmpty0(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraitsType<ParamType0>::TraitsRemoveReference>::PropertyTypeId() \
                        , _ZFP_ZFMethodFuncHolder_##MethodNamespace##_##MethodName##_##DECLARE_LINE:: _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_, 0) \
                    ) \
                ParamExpandOrEmpty1(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraitsType<ParamType1>::TraitsRemoveReference>::PropertyTypeId() \
                        , _ZFP_ZFMethodFuncHolder_##MethodNamespace##_##MethodName##_##DECLARE_LINE:: _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_, 1) \
                    ) \
                ParamExpandOrEmpty2(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraitsType<ParamType2>::TraitsRemoveReference>::PropertyTypeId() \
                        , _ZFP_ZFMethodFuncHolder_##MethodNamespace##_##MethodName##_##DECLARE_LINE:: _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_, 2) \
                    ) \
                ParamExpandOrEmpty3(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraitsType<ParamType3>::TraitsRemoveReference>::PropertyTypeId() \
                        , _ZFP_ZFMethodFuncHolder_##MethodNamespace##_##MethodName##_##DECLARE_LINE:: _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_, 3) \
                    ) \
                ParamExpandOrEmpty4(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraitsType<ParamType4>::TraitsRemoveReference>::PropertyTypeId() \
                        , _ZFP_ZFMethodFuncHolder_##MethodNamespace##_##MethodName##_##DECLARE_LINE:: _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_, 4) \
                    ) \
                ParamExpandOrEmpty5(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraitsType<ParamType5>::TraitsRemoveReference>::PropertyTypeId() \
                        , _ZFP_ZFMethodFuncHolder_##MethodNamespace##_##MethodName##_##DECLARE_LINE:: _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_, 5) \
                    ) \
                ParamExpandOrEmpty6(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraitsType<ParamType6>::TraitsRemoveReference>::PropertyTypeId() \
                        , _ZFP_ZFMethodFuncHolder_##MethodNamespace##_##MethodName##_##DECLARE_LINE:: _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_, 6) \
                    ) \
                ParamExpandOrEmpty7(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraitsType<ParamType7>::TraitsRemoveReference>::PropertyTypeId() \
                        , _ZFP_ZFMethodFuncHolder_##MethodNamespace##_##MethodName##_##DECLARE_LINE:: _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_, 7) \
                    ) \
                , zfnull \
            ); \
        return _methodHolder.method; \
    } \
    ZF_STATIC_REGISTER_INIT(MtdFR_##MethodNamespace##_##MethodName##_##DECLARE_LINE) \
    { \
        (_ZFP_ZFMethodFuncAccess_##MethodNamespace##_##MethodName((void (*)( \
               ParamExpandOrEmpty0(ZFM_EMPTY() ParamType0) \
               ParamExpandOrEmpty1(ZFM_COMMA() ParamType1) \
               ParamExpandOrEmpty2(ZFM_COMMA() ParamType2) \
               ParamExpandOrEmpty3(ZFM_COMMA() ParamType3) \
               ParamExpandOrEmpty4(ZFM_COMMA() ParamType4) \
               ParamExpandOrEmpty5(ZFM_COMMA() ParamType5) \
               ParamExpandOrEmpty6(ZFM_COMMA() ParamType6) \
               ParamExpandOrEmpty7(ZFM_COMMA() ParamType7) \
            ))zfnull)); \
    } \
    ZF_STATIC_REGISTER_END(MtdFR_##MethodNamespace##_##MethodName##_##DECLARE_LINE) \
    _ZFP_ZFMETHOD_FUNC_DEFINE_inlinePrefix(ZFMethodFuncIsInlineOrNotInline) ReturnType (MethodName)( \
        ParamExpandOrEmpty0(            ParamType0 param0) \
        ParamExpandOrEmpty1(ZFM_COMMA() ParamType1 param1) \
        ParamExpandOrEmpty2(ZFM_COMMA() ParamType2 param2) \
        ParamExpandOrEmpty3(ZFM_COMMA() ParamType3 param3) \
        ParamExpandOrEmpty4(ZFM_COMMA() ParamType4 param4) \
        ParamExpandOrEmpty5(ZFM_COMMA() ParamType5 param5) \
        ParamExpandOrEmpty6(ZFM_COMMA() ParamType6 param6) \
        ParamExpandOrEmpty7(ZFM_COMMA() ParamType7 param7) \
        ) _ZFP_ZFMETHOD_FUNC_DEFINE_inlinePostfix(ZFMethodFuncIsInlineOrNotInline)

// ============================================================
// 0 param method declare
/**
 * @brief declare function type of #ZFMethod
 *
 * usage:
 * @code
 *   // in header file
 *   ZFMETHOD_FUNC_DECLARE_0(void, myFunc)
 *
 *   // in source file
 *   ZFMETHOD_FUNC_DEFINE_0(void, myFunc)
 *   {
 *       // func body
 *   }
 * @endcode
 *
 * similar to #ZFMETHOD_DECLARE_0, but declared in global scope instead of class scope,
 * declared method can be reflected by #ZFMethodFuncGet,
 * and can be invoked by #ZFMethod::executeStatic
 * or by #ZFMethod::execute with null as first param\n
 * function type method support at most one level namespace,
 * or, use #ZFMethodFuncNamespaceGlobalId if your method has no namespace
 */
#define ZFMETHOD_FUNC_DECLARE_0( \
    ReturnType, MethodName \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_0( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_INLINE_0( \
    ReturnType, MethodName \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_0( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_WITH_NS_0( \
    MethodNamespace, ReturnType, MethodName \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_0( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_DETAIL_0( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    ) \
    _ZFP_ZFMETHOD_FUNC_DECLARE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EMPTY,  ParamType0, param0, DefaultValueFix0 \
        , ZFM_EMPTY,  ParamType1, param1, DefaultValueFix1 \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_0( \
    ReturnType, MethodName \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_0( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_INLINE_0( \
    ReturnType, MethodName \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_0( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_WITH_NS_0( \
    MethodNamespace, ReturnType, MethodName \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_0( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_DETAIL_0( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    ) \
    _ZFP_ZFMETHOD_FUNC_DEFINE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
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
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_1( \
    ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_1( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_INLINE_1( \
    ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_1( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_WITH_NS_1( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_1( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_DETAIL_1( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DECLARE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EMPTY,  ParamType1, param1, DefaultValueFix1 \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_1( \
    ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_1( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_INLINE_1( \
    ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_1( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_WITH_NS_1( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_1( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_DETAIL_1( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DEFINE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
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
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_2( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_2( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_INLINE_2( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_2( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_WITH_NS_2( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_2( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_DETAIL_2( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DECLARE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EMPTY,  ParamType2, param2, DefaultValueFix2 \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_2( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_2( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_INLINE_2( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_2( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_WITH_NS_2( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_2( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_DETAIL_2( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DEFINE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
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
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_3( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_3( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_INLINE_3( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_3( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_WITH_NS_3( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_3( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_DETAIL_3( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DECLARE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EMPTY,  ParamType3, param3, DefaultValueFix3 \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_3( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_3( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_INLINE_3( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_3( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_WITH_NS_3( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_3( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_DETAIL_3( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DEFINE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
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
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_4( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_4( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_INLINE_4( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_4( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_WITH_NS_4( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_4( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_DETAIL_4( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DECLARE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EMPTY,  ParamType4, param4, DefaultValueFix4 \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_4( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_4( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_INLINE_4( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_4( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_WITH_NS_4( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_4( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_DETAIL_4( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DEFINE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
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
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_5( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_5( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_INLINE_5( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_5( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_WITH_NS_5( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_5( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_DETAIL_5( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DECLARE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EMPTY,  ParamType5, param5, DefaultValueFix5 \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_5( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_5( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_INLINE_5( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_5( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_WITH_NS_5( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_5( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_DETAIL_5( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DEFINE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
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
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_6( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_6( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_INLINE_6( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_6( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_WITH_NS_6( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_6( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_DETAIL_6( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DECLARE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EMPTY,  ParamType6, param6, DefaultValueFix6 \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_6( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_6( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_INLINE_6( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_6( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_WITH_NS_6( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_6( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_DETAIL_6( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DEFINE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
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
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_7( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_7( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_INLINE_7( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_7( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_WITH_NS_7( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_7( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_DETAIL_7( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DECLARE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_6) \
        , ZFM_EMPTY,  ParamType7, param7, DefaultValueFix7 \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_7( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_7( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_INLINE_7( \
    ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_7( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_WITH_NS_7( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_7( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_DETAIL_7( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DEFINE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
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
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_8( \
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
    ZFMETHOD_FUNC_DECLARE_DETAIL_8( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_INLINE_8( \
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
    ZFMETHOD_FUNC_DECLARE_DETAIL_8( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_WITH_NS_8( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    ZFMETHOD_FUNC_DECLARE_DETAIL_8( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DECLARE_DETAIL_8( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DECLARE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND, ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_8( \
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
    ZFMETHOD_FUNC_DEFINE_DETAIL_8( \
        ZFMethodFuncNotInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_INLINE_8( \
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
    ZFMETHOD_FUNC_DEFINE_DETAIL_8( \
        ZFMethodFuncIsInline, ZFMethodFuncNamespaceGlobalId, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_WITH_NS_8( \
    MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    ZFMETHOD_FUNC_DEFINE_DETAIL_8( \
        ZFMethodFuncNotInline, MethodNamespace, ReturnType, MethodName \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMETHOD_FUNC_DEFINE_DETAIL_8( \
    ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    _ZFP_ZFMETHOD_FUNC_DEFINE( \
        ZFMethodFuncIsInlineOrNotInline, MethodNamespace, ReturnType, MethodName, ZF_CALLER_LINE \
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
#endif // #ifndef _ZFI_ZFMethodFuncDeclare_h_

