/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFMethodFuncUserRegister.h
 * @brief user registered ZFMethod
 */

#ifndef _ZFI_ZFMethodFuncUserRegister_h_
#define _ZFI_ZFMethodFuncUserRegister_h_

#include "ZFMethod.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
#define _ZFP_ZFMethodFuncUserRegister_methodExtSig zfText("MtdFUR")

#define _ZFP_ZFMethodFuncUserRegister(...) \
    ZFM_EXPAND(_ZFP_ZFMethodFuncUserRegister_(__VA_ARGS__))
#define _ZFP_ZFMethodFuncUserRegister_(resultMethod, methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, DECLARE_LINE \
        , ParamExpandOrEmpty0, ParamType0, param0, DefaultExpandOrEmpty0, DefaultValueFix0 \
        , ParamExpandOrEmpty1, ParamType1, param1, DefaultExpandOrEmpty1, DefaultValueFix1 \
        , ParamExpandOrEmpty2, ParamType2, param2, DefaultExpandOrEmpty2, DefaultValueFix2 \
        , ParamExpandOrEmpty3, ParamType3, param3, DefaultExpandOrEmpty3, DefaultValueFix3 \
        , ParamExpandOrEmpty4, ParamType4, param4, DefaultExpandOrEmpty4, DefaultValueFix4 \
        , ParamExpandOrEmpty5, ParamType5, param5, DefaultExpandOrEmpty5, DefaultValueFix5 \
        , ParamExpandOrEmpty6, ParamType6, param6, DefaultExpandOrEmpty6, DefaultValueFix6 \
        , ParamExpandOrEmpty7, ParamType7, param7, DefaultExpandOrEmpty7, DefaultValueFix7 \
    ) \
    zfclassNotPOD _ZFP_MtdFURIvk_##methodNamespace##_##resultMethod##_##DECLARE_LINE \
    { \
    public: \
        static ReturnType invoker(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject \
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
            methodInvokerAction \
        } \
    }; \
    _ZFP_ZFMethodFuncUserRegisterDetail(resultMethod, \
            _ZFP_MtdFURIvk_##methodNamespace##_##resultMethod##_##DECLARE_LINE::invoker, \
            ZFM_TOSTRING(methodNamespace), \
            ReturnType, ZFM_TOSTRING(methodName) \
            , ParamExpandOrEmpty0, ParamType0, param0, DefaultExpandOrEmpty0, DefaultValueFix0 \
            , ParamExpandOrEmpty1, ParamType1, param1, DefaultExpandOrEmpty1, DefaultValueFix1 \
            , ParamExpandOrEmpty2, ParamType2, param2, DefaultExpandOrEmpty2, DefaultValueFix2 \
            , ParamExpandOrEmpty3, ParamType3, param3, DefaultExpandOrEmpty3, DefaultValueFix3 \
            , ParamExpandOrEmpty4, ParamType4, param4, DefaultExpandOrEmpty4, DefaultValueFix4 \
            , ParamExpandOrEmpty5, ParamType5, param5, DefaultExpandOrEmpty5, DefaultValueFix5 \
            , ParamExpandOrEmpty6, ParamType6, param6, DefaultExpandOrEmpty6, DefaultValueFix6 \
            , ParamExpandOrEmpty7, ParamType7, param7, DefaultExpandOrEmpty7, DefaultValueFix7 \
        )

#define _ZFP_ZFMethodFuncUserRegisterDetail(...) \
    ZFM_EXPAND(_ZFP_ZFMethodFuncUserRegisterDetail_(__VA_ARGS__))
#define _ZFP_ZFMethodFuncUserRegisterDetail_(resultMethod, methodInvoker, methodNamespaceString, \
        ReturnType, methodNameString \
        , ParamExpandOrEmpty0, ParamType0, param0, DefaultExpandOrEmpty0, DefaultValueFix0 \
        , ParamExpandOrEmpty1, ParamType1, param1, DefaultExpandOrEmpty1, DefaultValueFix1 \
        , ParamExpandOrEmpty2, ParamType2, param2, DefaultExpandOrEmpty2, DefaultValueFix2 \
        , ParamExpandOrEmpty3, ParamType3, param3, DefaultExpandOrEmpty3, DefaultValueFix3 \
        , ParamExpandOrEmpty4, ParamType4, param4, DefaultExpandOrEmpty4, DefaultValueFix4 \
        , ParamExpandOrEmpty5, ParamType5, param5, DefaultExpandOrEmpty5, DefaultValueFix5 \
        , ParamExpandOrEmpty6, ParamType6, param6, DefaultExpandOrEmpty6, DefaultValueFix6 \
        , ParamExpandOrEmpty7, ParamType7, param7, DefaultExpandOrEmpty7, DefaultValueFix7 \
    ) \
    const ZFMethod *resultMethod = zfnull; \
    { \
        zfclassNotPOD _ZFP_MtdFUR \
        { \
        public: \
            typedef ReturnType (*Ck)(const ZFMethod *, ZFObject * \
                    ParamExpandOrEmpty0(ZFM_COMMA() ParamType0) \
                    ParamExpandOrEmpty1(ZFM_COMMA() ParamType1) \
                    ParamExpandOrEmpty2(ZFM_COMMA() ParamType2) \
                    ParamExpandOrEmpty3(ZFM_COMMA() ParamType3) \
                    ParamExpandOrEmpty4(ZFM_COMMA() ParamType4) \
                    ParamExpandOrEmpty5(ZFM_COMMA() ParamType5) \
                    ParamExpandOrEmpty6(ZFM_COMMA() ParamType6) \
                    ParamExpandOrEmpty7(ZFM_COMMA() ParamType7) \
                ); \
            _ZFP_ZFMETHOD_GENERIC_INVOKER_DECLARE( \
                    ReturnType \
                    , ParamExpandOrEmpty0, ParamType0, param0, DefaultExpandOrEmpty0, DefaultValueFix0 \
                    , ParamExpandOrEmpty1, ParamType1, param1, DefaultExpandOrEmpty1, DefaultValueFix1 \
                    , ParamExpandOrEmpty2, ParamType2, param2, DefaultExpandOrEmpty2, DefaultValueFix2 \
                    , ParamExpandOrEmpty3, ParamType3, param3, DefaultExpandOrEmpty3, DefaultValueFix3 \
                    , ParamExpandOrEmpty4, ParamType4, param4, DefaultExpandOrEmpty4, DefaultValueFix4 \
                    , ParamExpandOrEmpty5, ParamType5, param5, DefaultExpandOrEmpty5, DefaultValueFix5 \
                    , ParamExpandOrEmpty6, ParamType6, param6, DefaultExpandOrEmpty6, DefaultValueFix6 \
                    , ParamExpandOrEmpty7, ParamType7, param7, DefaultExpandOrEmpty7, DefaultValueFix7 \
                ) \
        }; \
        \
        _ZFP_MtdFUR::Ck fn = methodInvoker; \
        resultMethod = _ZFP_ZFMethodRegister(zftrue \
                , ZFCastReinterpret(ZFFuncAddrType, fn) \
                , _ZFP_ZFMETHOD_GENERIC_INVOKER_ADDR(_ZFP_MtdFUR) \
                , _ZFP_ZFMethodIsWhatTypeText(ZFMethodIsStatic) \
                , zfnull \
                , ZFMethodPrivilegeTypePublic \
                , methodNamespaceString \
                , _ZFP_ZFMethodFuncUserRegister_methodExtSig \
                , methodNameString \
                , ZFPropertyTypeIdData<zftTraits<ReturnType>::TrNoRef>::PropertyTypeId() \
                , zfText(#ReturnType) \
                ParamExpandOrEmpty0(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraits<ParamType0>::TrNoRef>::PropertyTypeId() \
                        , ZFM_TOSTRING(ParamType0) \
                        , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_ZFP_MtdFUR, DefaultExpandOrEmpty0, 0) \
                    ) \
                ParamExpandOrEmpty1(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraits<ParamType1>::TrNoRef>::PropertyTypeId() \
                        , ZFM_TOSTRING(ParamType1) \
                        , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_ZFP_MtdFUR, DefaultExpandOrEmpty1, 1) \
                    ) \
                ParamExpandOrEmpty2(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraits<ParamType2>::TrNoRef>::PropertyTypeId() \
                        , ZFM_TOSTRING(ParamType2) \
                        , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_ZFP_MtdFUR, DefaultExpandOrEmpty2, 2) \
                    ) \
                ParamExpandOrEmpty3(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraits<ParamType3>::TrNoRef>::PropertyTypeId() \
                        , ZFM_TOSTRING(ParamType3) \
                        , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_ZFP_MtdFUR, DefaultExpandOrEmpty3, 3) \
                    ) \
                ParamExpandOrEmpty4(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraits<ParamType4>::TrNoRef>::PropertyTypeId() \
                        , ZFM_TOSTRING(ParamType4) \
                        , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_ZFP_MtdFUR, DefaultExpandOrEmpty4, 4) \
                    ) \
                ParamExpandOrEmpty5(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraits<ParamType5>::TrNoRef>::PropertyTypeId() \
                        , ZFM_TOSTRING(ParamType5) \
                        , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_ZFP_MtdFUR, DefaultExpandOrEmpty5, 5) \
                    ) \
                ParamExpandOrEmpty6(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraits<ParamType6>::TrNoRef>::PropertyTypeId() \
                        , ZFM_TOSTRING(ParamType6) \
                        , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_ZFP_MtdFUR, DefaultExpandOrEmpty6, 6) \
                    ) \
                ParamExpandOrEmpty7(ZFM_EMPTY() \
                        , ZFPropertyTypeIdData<zftTraits<ParamType7>::TrNoRef>::PropertyTypeId() \
                        , ZFM_TOSTRING(ParamType7) \
                        , _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(_ZFP_MtdFUR, DefaultExpandOrEmpty7, 7) \
                    ) \
                , zfnull \
            ); \
    } \
    ZFUNUSED(resultMethod)

#define _ZFP_ZFMETHOD_FUNC_USER_REGISTER(...) \
    ZFM_EXPAND(_ZFP_ZFMETHOD_FUNC_USER_REGISTER_(__VA_ARGS__))
#define _ZFP_ZFMETHOD_FUNC_USER_REGISTER_(methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, DECLARE_LINE \
        , ParamExpandOrEmpty0, ParamType0, param0, DefaultExpandOrEmpty0, DefaultValueFix0 \
        , ParamExpandOrEmpty1, ParamType1, param1, DefaultExpandOrEmpty1, DefaultValueFix1 \
        , ParamExpandOrEmpty2, ParamType2, param2, DefaultExpandOrEmpty2, DefaultValueFix2 \
        , ParamExpandOrEmpty3, ParamType3, param3, DefaultExpandOrEmpty3, DefaultValueFix3 \
        , ParamExpandOrEmpty4, ParamType4, param4, DefaultExpandOrEmpty4, DefaultValueFix4 \
        , ParamExpandOrEmpty5, ParamType5, param5, DefaultExpandOrEmpty5, DefaultValueFix5 \
        , ParamExpandOrEmpty6, ParamType6, param6, DefaultExpandOrEmpty6, DefaultValueFix6 \
        , ParamExpandOrEmpty7, ParamType7, param7, DefaultExpandOrEmpty7, DefaultValueFix7 \
    ) \
    zfclassNotPOD _ZFP_MtdFURIvk_##methodNamespace##_##methodName##_##DECLARE_LINE \
    { \
    public: \
        static ReturnType invoker(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject \
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
            methodInvokerAction \
        } \
    }; \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_DETAIL(methodNamespace##_##methodName##_##DECLARE_LINE, \
            _ZFP_MtdFURIvk_##methodNamespace##_##methodName##_##DECLARE_LINE::invoker, \
            ZFM_TOSTRING(methodNamespace), ReturnType, ZFM_TOSTRING(methodName) \
            , ParamExpandOrEmpty0, ParamType0, param0, DefaultExpandOrEmpty0, DefaultValueFix0 \
            , ParamExpandOrEmpty1, ParamType1, param1, DefaultExpandOrEmpty1, DefaultValueFix1 \
            , ParamExpandOrEmpty2, ParamType2, param2, DefaultExpandOrEmpty2, DefaultValueFix2 \
            , ParamExpandOrEmpty3, ParamType3, param3, DefaultExpandOrEmpty3, DefaultValueFix3 \
            , ParamExpandOrEmpty4, ParamType4, param4, DefaultExpandOrEmpty4, DefaultValueFix4 \
            , ParamExpandOrEmpty5, ParamType5, param5, DefaultExpandOrEmpty5, DefaultValueFix5 \
            , ParamExpandOrEmpty6, ParamType6, param6, DefaultExpandOrEmpty6, DefaultValueFix6 \
            , ParamExpandOrEmpty7, ParamType7, param7, DefaultExpandOrEmpty7, DefaultValueFix7 \
        )

#define _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC(...) \
    ZFM_EXPAND(_ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_(__VA_ARGS__))
#define _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_(methodNamespace, \
        ReturnType, methodName, DECLARE_LINE \
        , ParamExpandOrEmpty0, ParamType0, param0, DefaultExpandOrEmpty0, DefaultValueFix0 \
        , ParamExpandOrEmpty1, ParamType1, param1, DefaultExpandOrEmpty1, DefaultValueFix1 \
        , ParamExpandOrEmpty2, ParamType2, param2, DefaultExpandOrEmpty2, DefaultValueFix2 \
        , ParamExpandOrEmpty3, ParamType3, param3, DefaultExpandOrEmpty3, DefaultValueFix3 \
        , ParamExpandOrEmpty4, ParamType4, param4, DefaultExpandOrEmpty4, DefaultValueFix4 \
        , ParamExpandOrEmpty5, ParamType5, param5, DefaultExpandOrEmpty5, DefaultValueFix5 \
        , ParamExpandOrEmpty6, ParamType6, param6, DefaultExpandOrEmpty6, DefaultValueFix6 \
        , ParamExpandOrEmpty7, ParamType7, param7, DefaultExpandOrEmpty7, DefaultValueFix7 \
    ) \
    zfclassNotPOD _ZFP_MtdFURIvk_##methodNamespace##_##methodName##_##DECLARE_LINE \
    { \
    public: \
        static ReturnType invoker(ZF_IN const ZFMethod *invokerMethod, ZF_IN ZFObject *invokerObject \
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
            return (ReturnType)ZFM_EXPAND(methodName ZFM_BRACKET_L() \
                    ParamExpandOrEmpty0(ZFM_EMPTY() param0) \
                    ParamExpandOrEmpty1(ZFM_COMMA() param1) \
                    ParamExpandOrEmpty2(ZFM_COMMA() param2) \
                    ParamExpandOrEmpty3(ZFM_COMMA() param3) \
                    ParamExpandOrEmpty4(ZFM_COMMA() param4) \
                    ParamExpandOrEmpty5(ZFM_COMMA() param5) \
                    ParamExpandOrEmpty6(ZFM_COMMA() param6) \
                    ParamExpandOrEmpty7(ZFM_COMMA() param7) \
                ZFM_BRACKET_R()); \
        } \
    }; \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_DETAIL(methodNamespace##_##methodName##_##DECLARE_LINE, \
            _ZFP_MtdFURIvk_##methodNamespace##_##methodName##_##DECLARE_LINE::invoker, \
            ZFM_TOSTRING(methodNamespace), ReturnType, ZFM_TOSTRING(methodName) \
            , ParamExpandOrEmpty0, ParamType0, param0, DefaultExpandOrEmpty0, DefaultValueFix0 \
            , ParamExpandOrEmpty1, ParamType1, param1, DefaultExpandOrEmpty1, DefaultValueFix1 \
            , ParamExpandOrEmpty2, ParamType2, param2, DefaultExpandOrEmpty2, DefaultValueFix2 \
            , ParamExpandOrEmpty3, ParamType3, param3, DefaultExpandOrEmpty3, DefaultValueFix3 \
            , ParamExpandOrEmpty4, ParamType4, param4, DefaultExpandOrEmpty4, DefaultValueFix4 \
            , ParamExpandOrEmpty5, ParamType5, param5, DefaultExpandOrEmpty5, DefaultValueFix5 \
            , ParamExpandOrEmpty6, ParamType6, param6, DefaultExpandOrEmpty6, DefaultValueFix6 \
            , ParamExpandOrEmpty7, ParamType7, param7, DefaultExpandOrEmpty7, DefaultValueFix7 \
        )

#define _ZFP_ZFMETHOD_FUNC_USER_REGISTER_DETAIL(...) \
    ZFM_EXPAND(_ZFP_ZFMETHOD_FUNC_USER_REGISTER_DETAIL_(__VA_ARGS__))
#define _ZFP_ZFMETHOD_FUNC_USER_REGISTER_DETAIL_(registerSig, methodInvoker, \
        methodNamespaceString, ReturnType, methodNameString \
        , ParamExpandOrEmpty0, ParamType0, param0, DefaultExpandOrEmpty0, DefaultValueFix0 \
        , ParamExpandOrEmpty1, ParamType1, param1, DefaultExpandOrEmpty1, DefaultValueFix1 \
        , ParamExpandOrEmpty2, ParamType2, param2, DefaultExpandOrEmpty2, DefaultValueFix2 \
        , ParamExpandOrEmpty3, ParamType3, param3, DefaultExpandOrEmpty3, DefaultValueFix3 \
        , ParamExpandOrEmpty4, ParamType4, param4, DefaultExpandOrEmpty4, DefaultValueFix4 \
        , ParamExpandOrEmpty5, ParamType5, param5, DefaultExpandOrEmpty5, DefaultValueFix5 \
        , ParamExpandOrEmpty6, ParamType6, param6, DefaultExpandOrEmpty6, DefaultValueFix6 \
        , ParamExpandOrEmpty7, ParamType7, param7, DefaultExpandOrEmpty7, DefaultValueFix7 \
    ) \
    ZF_STATIC_REGISTER_INIT(MtdFURReg_##registerSig) \
    { \
        _ZFP_ZFMethodFuncUserRegisterDetail(resultMethod, methodInvoker, methodNamespaceString, \
                ReturnType, methodNameString \
                , ParamExpandOrEmpty0, ParamType0, param0, DefaultExpandOrEmpty0, DefaultValueFix0 \
                , ParamExpandOrEmpty1, ParamType1, param1, DefaultExpandOrEmpty1, DefaultValueFix1 \
                , ParamExpandOrEmpty2, ParamType2, param2, DefaultExpandOrEmpty2, DefaultValueFix2 \
                , ParamExpandOrEmpty3, ParamType3, param3, DefaultExpandOrEmpty3, DefaultValueFix3 \
                , ParamExpandOrEmpty4, ParamType4, param4, DefaultExpandOrEmpty4, DefaultValueFix4 \
                , ParamExpandOrEmpty5, ParamType5, param5, DefaultExpandOrEmpty5, DefaultValueFix5 \
                , ParamExpandOrEmpty6, ParamType6, param6, DefaultExpandOrEmpty6, DefaultValueFix6 \
                , ParamExpandOrEmpty7, ParamType7, param7, DefaultExpandOrEmpty7, DefaultValueFix7 \
            ); \
        this->_method = resultMethod; \
    } \
    ZF_STATIC_REGISTER_DESTROY(MtdFURReg_##registerSig) \
    { \
        ZFMethodFuncUserUnregister(this->_method); \
    } \
    const ZFMethod *_method; \
    ZF_STATIC_REGISTER_END(MtdFURReg_##registerSig)

// ============================================================
/** @brief see #ZFMethodFuncUserRegister_0 */
extern ZF_ENV_EXPORT void ZFMethodFuncUserUnregister(ZF_IN const ZFMethod *method);

// ============================================================
// 0 param
/**
 * @brief register a custom method to global scope, for advanced reflection use only
 *
 * example:
 * @code
 *   // declare your method invoker
 *   static ReturnType myInvoker(const ZFMethod *invokerMethod, ZFObject *invokerObject, ParamType0 param0, ParamType1 param0)
 *   {
 *      // ...
 *   }
 *
 *   // register it, using ZF_GLOBAL_INITIALIZER_INIT is recommended
 *   ZF_GLOBAL_INITIALIZER_INIT(MyMethodRegister)
 *   {
 *       ZFMethodFuncUserRegisterDetail_2(
 *           resultMethod, myInvoker, zfText("MyMethodNamespace"),
 *           ReturnType, zfText("myMethodName")
 *           , ZFMP_IN(ParamType0, param0)
 *           , ZFMP_IN(ParamType1, param1));
 *       _method = resultMethod;
 *       zfLogTrimT() << resultMethod;
 *   }
 *   ZF_GLOBAL_INITIALIZER_DESTROY(MyMethodRegister)
 *   {
 *       ZFMethodFuncUserUnregister(_method);
 *   }
 *   const ZFMethod *_method;
 *   ZF_GLOBAL_INITIALIZER_END(MyMethodRegister)
 *
 *   // or, you may use this macro for short, at cpp files only
 *   ZFMETHOD_FUNC_USER_REGISTER_DETAIL_2(
 *       myMethodRegisterSig, myInvoker, zfText("MyMethodNamespace"),
 *       ReturnType, zfText("myMethodName")
 *       , ZFMP_IN(ParamType0, param0)
 *       , ZFMP_IN(ParamType1, param1))
 *
 *   // or, for the short version
 *   ZFMETHOD_FUNC_USER_REGISTER_2({
 *           // invoker action
 *           return ReturnType();
 *       }, ReturnType, myMethodName
 *       , ZFMP_IN(ParamType0, param0)
 *       , ZFMP_IN(ParamType1, param1))
 * @endcode
 *
 * note:
 * -  if there is already a method exist with same method name and method id,
 *   register would fail
 * -  the registered method must be unregister manually at proper time,
 *   use #ZF_GLOBAL_INITIALIZER_INIT is recommeded
 * -  once registered, the method can be reflected by #ZFClass::methodForName,
 *   but there's no way to invoke the method directly,
 *   it can only be invoked by #ZFMethod::execute
 */
#define ZFMethodFuncUserRegister_0(resultMethod, methodInvokerAction, \
    ReturnType, methodName \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterWithNamespace_0(resultMethod, methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterDetail_0(resultMethod, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    ) \
    _ZFP_ZFMethodFuncUserRegisterDetail(resultMethod, methodInvoker, methodNamespaceString, \
        ReturnType, methodNameString \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_0(methodInvokerAction, \
    ReturnType, methodName \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_WITH_NS_0(methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_0( \
    ReturnType, methodName \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_WITH_NS_0( \
    methodNamespace, \
    ReturnType, methodName \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_DETAIL_0(registerSig, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_DETAIL(registerSig, methodInvoker, \
        methodNamespaceString, ReturnType, methodNameString \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )

// ============================================================
// 1 param
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegister_1(resultMethod, methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterWithNamespace_1(resultMethod, methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterDetail_1(resultMethod, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    ) \
    _ZFP_ZFMethodFuncUserRegisterDetail(resultMethod, methodInvoker, methodNamespaceString, \
        ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_1(methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_WITH_NS_1(methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1( \
    ReturnType, methodName \
    , ZFMP_0 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_WITH_NS_1( \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_DETAIL_1(registerSig, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_DETAIL(registerSig, methodInvoker, \
        methodNamespaceString, ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )

// ============================================================
// 2 param
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegister_2(resultMethod, methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterWithNamespace_2(resultMethod, methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterDetail_2(resultMethod, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    _ZFP_ZFMethodFuncUserRegisterDetail(resultMethod, methodInvoker, methodNamespaceString, \
        ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_2(methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_WITH_NS_2(methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2( \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_WITH_NS_2( \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_DETAIL_2(registerSig, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    , ZFMP_1 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_DETAIL(registerSig, methodInvoker, \
        methodNamespaceString, ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )

// ============================================================
// 3 param
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegister_3(resultMethod, methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterWithNamespace_3(resultMethod, methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterDetail_3(resultMethod, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    _ZFP_ZFMethodFuncUserRegisterDetail(resultMethod, methodInvoker, methodNamespaceString, \
        ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_3(methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_WITH_NS_3(methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_3( \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_WITH_NS_3( \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_DETAIL_3(registerSig, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_DETAIL(registerSig, methodInvoker, \
        methodNamespaceString, ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )

// ============================================================
// 4 param
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegister_4(resultMethod, methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterWithNamespace_4(resultMethod, methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterDetail_4(resultMethod, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    _ZFP_ZFMethodFuncUserRegisterDetail(resultMethod, methodInvoker, methodNamespaceString, \
        ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_4(methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_WITH_NS_4(methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_4( \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_WITH_NS_4( \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_DETAIL_4(registerSig, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_DETAIL(registerSig, methodInvoker, \
        methodNamespaceString, ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )

// ============================================================
// 5 param
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegister_5(resultMethod, methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterWithNamespace_5(resultMethod, methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterDetail_5(resultMethod, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    _ZFP_ZFMethodFuncUserRegisterDetail(resultMethod, methodInvoker, methodNamespaceString, \
        ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_5(methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_WITH_NS_5(methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_5( \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_WITH_NS_5( \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_DETAIL_5(registerSig, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_DETAIL(registerSig, methodInvoker, \
        methodNamespaceString, ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )

// ============================================================
// 6 param
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegister_6(resultMethod, methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterWithNamespace_6(resultMethod, methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterDetail_6(resultMethod, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    _ZFP_ZFMethodFuncUserRegisterDetail(resultMethod, methodInvoker, methodNamespaceString, \
        ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_6(methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_WITH_NS_6(methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_6( \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_WITH_NS_6( \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_DETAIL_6(registerSig, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_DETAIL(registerSig, methodInvoker, \
        methodNamespaceString, ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , _ZFP_ZFMP_DUMMY() \
        , _ZFP_ZFMP_DUMMY() \
        )

// ============================================================
// 7 param
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegister_7(resultMethod, methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterWithNamespace_7(resultMethod, methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterDetail_7(resultMethod, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    _ZFP_ZFMethodFuncUserRegisterDetail(resultMethod, methodInvoker, methodNamespaceString, \
        ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_7(methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_WITH_NS_7(methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_7( \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_WITH_NS_7( \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , _ZFP_ZFMP_DUMMY() \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_DETAIL_7(registerSig, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_DETAIL(registerSig, methodInvoker, \
        methodNamespaceString, ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , _ZFP_ZFMP_DUMMY() \
        )

// ============================================================
// 8 param
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegister_8(resultMethod, methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterWithNamespace_8(resultMethod, methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    _ZFP_ZFMethodFuncUserRegister(resultMethod, methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMethodFuncUserRegisterDetail_8(resultMethod, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    _ZFP_ZFMethodFuncUserRegisterDetail(resultMethod, methodInvoker, methodNamespaceString, \
        ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_8(methodInvokerAction, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_WITH_NS_8(methodInvokerAction, \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER(methodInvokerAction, \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_8( \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        ZFMethodFuncNamespaceGlobalId, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_WITH_NS_8( \
    methodNamespace, \
    ReturnType, methodName \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC( \
        methodNamespace, \
        ReturnType, methodName, ZF_CALLER_LINE \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/** @brief see #ZFMethodFuncUserRegister_0 */
#define ZFMETHOD_FUNC_USER_REGISTER_DETAIL_8(registerSig, methodInvoker, methodNamespaceString, \
    ReturnType, methodNameString \
    , ZFMP_0 \
    , ZFMP_1 \
    , ZFMP_2 \
    , ZFMP_3 \
    , ZFMP_4 \
    , ZFMP_5 \
    , ZFMP_6 \
    , ZFMP_7 \
    ) \
    _ZFP_ZFMETHOD_FUNC_USER_REGISTER_DETAIL(registerSig, methodInvoker, \
        methodNamespaceString, ReturnType, methodNameString \
        , ZFM_EXPAND(ZFMP_0) \
        , ZFM_EXPAND(ZFMP_1) \
        , ZFM_EXPAND(ZFMP_2) \
        , ZFM_EXPAND(ZFMP_3) \
        , ZFM_EXPAND(ZFMP_4) \
        , ZFM_EXPAND(ZFMP_5) \
        , ZFM_EXPAND(ZFMP_6) \
        , ZFM_EXPAND(ZFMP_7) \
        )
/* ZFMETHOD_MAX_PARAM */

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFMethodFuncUserRegister_h_

