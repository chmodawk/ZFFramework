/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFMethodGenericInvoker.h
 * @brief generic invoker declare for #ZFMethod::methodGenericInvoker
 */

#ifndef _ZFI_ZFMethodGenericInvoker_h_
#define _ZFI_ZFMethodGenericInvoker_h_

#include "ZFObjectClassTypeFwd.h"
#include "zfautoObjectFwd.h"
#include "ZFPropertyTypeFwd.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
zfclassFwd ZFMethod;
/**
 * @brief generic invoker for advanced reflection, see #ZFMethod::methodGenericInvoker
 */
typedef zfbool (*ZFMethodGenericInvoker)(ZF_IN const ZFMethod *invokerMethod
                                         , ZF_IN ZFObject *invokerObjectOrNullForStaticFunc
                                         , ZF_OUT_OPT zfstring *errorHint
                                         , ZF_OUT_OPT zfautoObject &ret
                                         , ZF_IN_OPT ZFObject *param0 /* = ZFMethodGenericInvokeraultParam */
                                         , ZF_IN_OPT ZFObject *param1 /* = ZFMethodGenericInvokeraultParam */
                                         , ZF_IN_OPT ZFObject *param2 /* = ZFMethodGenericInvokeraultParam */
                                         , ZF_IN_OPT ZFObject *param3 /* = ZFMethodGenericInvokeraultParam */
                                         , ZF_IN_OPT ZFObject *param4 /* = ZFMethodGenericInvokeraultParam */
                                         , ZF_IN_OPT ZFObject *param5 /* = ZFMethodGenericInvokeraultParam */
                                         , ZF_IN_OPT ZFObject *param6 /* = ZFMethodGenericInvokeraultParam */
                                         , ZF_IN_OPT ZFObject *param7 /* = ZFMethodGenericInvokeraultParam */
                                         );
/**
 * @brief used for generic invoker to check whether it's able to invoke from specified params,
 *   see #ZFMethod::methodGenericInvokerChecker
 */
typedef zfbool (*ZFMethodGenericInvokerChecker)(ZF_IN const ZFMethod *invokerMethod
                                                , ZF_OUT_OPT zfstring *errorHint
                                                , ZF_IN_OPT ZFObject *param0 /* = ZFMethodGenericInvokeraultParam */
                                                , ZF_IN_OPT ZFObject *param1 /* = ZFMethodGenericInvokeraultParam */
                                                , ZF_IN_OPT ZFObject *param2 /* = ZFMethodGenericInvokeraultParam */
                                                , ZF_IN_OPT ZFObject *param3 /* = ZFMethodGenericInvokeraultParam */
                                                , ZF_IN_OPT ZFObject *param4 /* = ZFMethodGenericInvokeraultParam */
                                                , ZF_IN_OPT ZFObject *param5 /* = ZFMethodGenericInvokeraultParam */
                                                , ZF_IN_OPT ZFObject *param6 /* = ZFMethodGenericInvokeraultParam */
                                                , ZF_IN_OPT ZFObject *param7 /* = ZFMethodGenericInvokeraultParam */
                                                );

extern ZF_ENV_EXPORT ZFObject *_ZFP_ZFMethodGenericInvokeraultParamRef;
inline ZFObject *_ZFP_ZFMethodGenericInvokeraultParam(void)
{
    return _ZFP_ZFMethodGenericInvokeraultParamRef;
}
/**
 * @brief mark the object as default param
 */
#define ZFMethodGenericInvokeraultParam _ZFP_ZFMethodGenericInvokeraultParam()

extern ZF_ENV_EXPORT zfautoObject _ZFP_ZFMethodGenericInvokeraultParamHolderRef;
inline const zfautoObject &_ZFP_ZFMethodGenericInvokeraultParamHolder(void)
{
    return _ZFP_ZFMethodGenericInvokeraultParamHolderRef;
}
/**
 * @brief holder of #ZFMethodGenericInvokeraultParam
 */
#define ZFMethodGenericInvokeraultParamHolder _ZFP_ZFMethodGenericInvokeraultParamHolder()

// ============================================================
template<typename T_Dummy, int n>
zfclassNotPOD _ZFP_ZFMethodGenericInvokerTypeCheck
{
};
template<typename T_Dummy>
zfclassNotPOD _ZFP_ZFMethodGenericInvokerTypeCheck<T_Dummy, 1>
{
public:
    typedef int AllTypeMustBeRegisteredBy_ZFPROPERTY_TYPE_XXX;
};
#define _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(ParamType, param, N) \
    typedef ParamType _ParamType##N; \
    typedef zftTraitsType<ParamType>::TraitsRemoveReference _ParamTypeTraits##N; \
    typedef _ZFP_ZFMethodGenericInvokerTypeCheck< \
            _ParamTypeTraits##N, \
            ZFPropertyTypeIdData<_ParamTypeTraits##N>::PropertyRegistered \
        >::AllTypeMustBeRegisteredBy_ZFPROPERTY_TYPE_XXX _ParamTypeCheck##N;
#define _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(ParamType, param, N) \
    if(!(N >= invokerMethod->methodParamDefaultBeginIndex() && param == ZFMethodGenericInvokeraultParam) \
        && !ZFPropertyTypeIdData<_ParamTypeTraits##N>::Value<_ParamTypeTraits##N>::accessAvailable(param)) \
    { \
        zfstringAppend(errorHint, \
                zfText("[ZFMethodGenericInvoker] unable to access param%zi as type %s: %s"), \
                (zfindex)N, \
                ZFPropertyTypeIdData<_ParamTypeTraits##N>::PropertyTypeId(), \
                ZFObjectInfo(param).cString() \
            ); \
        return zffalse; \
    }
#define _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(paramDefaultAccess, ParamType, param, N) \
    ZFPropertyTypeIdData<_ParamTypeTraits##N>::Value<_ParamType##N>::access( \
            (param != ZFMethodGenericInvokeraultParam) \
            ? param \
            : paramDefaultAccess().toObject() \
        )
#define _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(N, ParamExpandOrEmpty, ParamType, DefaultValueFix) \
    static zfautoObject paramDefaultAccess##N(void) \
    { \
        ParamExpandOrEmpty( \
                zftValue<zftTraitsType<ParamType>::TraitsRemoveReference> paramDefault; \
                zfautoObject ret; \
                ZFPropertyTypeIdData<zftTraitsType<ParamType>::TraitsRemoveReference>::PropertyConvertToZFObject( \
                    ret, \
                    (paramDefault.zfv DefaultValueFix())); \
                return ret; \
            ) \
        return zfautoObjectNull; \
    }

// ============================================================
template<typename T_Invoker, typename T_ReturnType>
zfclassNotPOD _ZFP_ZFMethodGenericInvokerWrapper
{
public:
    typedef typename _ZFP_ZFMethodGenericInvokerTypeCheck<
            typename zftTraitsType<T_ReturnType>::TraitsRemoveReference, \
            ZFPropertyTypeIdData<typename zftTraitsType<T_ReturnType>::TraitsRemoveReference>::PropertyRegistered
        >::AllTypeMustBeRegisteredBy_ZFPROPERTY_TYPE_XXX _ReturnTypeCheck;
public:
    static zfbool wrap(ZF_IN const ZFMethod *invokerMethod
                       , ZF_IN ZFObject *invokerObject
                       , ZF_OUT_OPT zfstring *errorHint
                       , ZF_OUT_OPT zfautoObject &ret
                       , ZF_IN ZFObject *param0
                       , ZF_IN ZFObject *param1
                       , ZF_IN ZFObject *param2
                       , ZF_IN ZFObject *param3
                       , ZF_IN ZFObject *param4
                       , ZF_IN ZFObject *param5
                       , ZF_IN ZFObject *param6
                       , ZF_IN ZFObject *param7
                       )
    {
        if(!T_Invoker::invokeCheck(
                  invokerMethod
                , errorHint
                , param0
                , param1
                , param2
                , param3
                , param4
                , param5
                , param6
                , param7
            ))
        {
            return zffalse;
        }
        T_ReturnType retTmp = T_Invoker::invoke(invokerMethod, invokerObject
                , param0
                , param1
                , param2
                , param3
                , param4
                , param5
                , param6
                , param7
            );
        zfbool success = ZFPropertyTypeIdData<typename zftTraitsType<T_ReturnType>::TraitsRemoveReference>::PropertyConvertToZFObject(ret, retTmp);
        if(!success)
        {
            zfstring retValueInfo;
            ZFCoreElementInfoGetter<typename zftTraitsType<T_ReturnType>::TraitsRemoveReference>::elementInfoGetter(retValueInfo, retTmp);
            zfstringAppend(errorHint,
                zfText("[ZFMethodGenericInvoker] unable to convert return value %s to type %s"),
                retValueInfo.cString(),
                ZFPropertyTypeIdData<typename zftTraitsType<T_ReturnType>::TraitsRemoveReference>::PropertyTypeId());
        }
        return success;
    }
};
template<typename T_Invoker>
zfclassNotPOD _ZFP_ZFMethodGenericInvokerWrapper<T_Invoker, void>
{
public:
    static zfbool wrap(ZF_IN const ZFMethod *invokerMethod
                       , ZF_IN ZFObject *invokerObject
                       , ZF_OUT_OPT zfstring *errorHint
                       , ZF_OUT_OPT zfautoObject &ret
                       , ZF_IN ZFObject *param0
                       , ZF_IN ZFObject *param1
                       , ZF_IN ZFObject *param2
                       , ZF_IN ZFObject *param3
                       , ZF_IN ZFObject *param4
                       , ZF_IN ZFObject *param5
                       , ZF_IN ZFObject *param6
                       , ZF_IN ZFObject *param7
                       )
    {
        if(!T_Invoker::invokeCheck(
                  invokerMethod
                , errorHint
                , param0
                , param1
                , param2
                , param3
                , param4
                , param5
                , param6
                , param7
            ))
        {
            return zffalse;
        }
        T_Invoker::invoke(invokerMethod, invokerObject
                , param0
                , param1
                , param2
                , param3
                , param4
                , param5
                , param6
                , param7
            );
        return zftrue;
    }
};

// ============================================================
#define _ZFP_ZFMETHOD_GENERIC_INVOKER_DECLARE_BEGIN( \
    ReturnType, methodSig \
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
    zfclassNotPOD _ZFP_ZFMethodGenericInvoker_##methodSig \
    { \
    private: \
         ParamExpandOrEmpty0(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(ParamType0, param0, 0)) \
         ParamExpandOrEmpty1(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(ParamType1, param1, 1)) \
         ParamExpandOrEmpty2(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(ParamType2, param2, 2)) \
         ParamExpandOrEmpty3(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(ParamType3, param3, 3)) \
         ParamExpandOrEmpty4(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(ParamType4, param4, 4)) \
         ParamExpandOrEmpty5(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(ParamType5, param5, 5)) \
         ParamExpandOrEmpty6(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(ParamType6, param6, 6)) \
         ParamExpandOrEmpty7(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(ParamType7, param7, 7)) \
    public: \
        _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(0, ParamExpandOrEmpty0, ParamType0, DefaultValueFix0) \
        _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(1, ParamExpandOrEmpty1, ParamType1, DefaultValueFix1) \
        _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(2, ParamExpandOrEmpty2, ParamType2, DefaultValueFix2) \
        _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(3, ParamExpandOrEmpty3, ParamType3, DefaultValueFix3) \
        _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(4, ParamExpandOrEmpty4, ParamType4, DefaultValueFix4) \
        _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(5, ParamExpandOrEmpty5, ParamType5, DefaultValueFix5) \
        _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(6, ParamExpandOrEmpty6, ParamType6, DefaultValueFix6) \
        _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(7, ParamExpandOrEmpty7, ParamType7, DefaultValueFix7) \
    public: \
        static zfbool invokeCheck( \
                                    ZF_IN const ZFMethod *invokerMethod \
                                  , ZF_OUT_OPT zfstring *errorHint \
                                  , ZF_IN ZFObject *param0 \
                                  , ZF_IN ZFObject *param1 \
                                  , ZF_IN ZFObject *param2 \
                                  , ZF_IN ZFObject *param3 \
                                  , ZF_IN ZFObject *param4 \
                                  , ZF_IN ZFObject *param5 \
                                  , ZF_IN ZFObject *param6 \
                                  , ZF_IN ZFObject *param7 \
                                  ) \
        { \
            ParamExpandOrEmpty0(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(ParamType0, param0, 0)) \
            ParamExpandOrEmpty1(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(ParamType1, param1, 1)) \
            ParamExpandOrEmpty2(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(ParamType2, param2, 2)) \
            ParamExpandOrEmpty3(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(ParamType3, param3, 3)) \
            ParamExpandOrEmpty4(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(ParamType4, param4, 4)) \
            ParamExpandOrEmpty5(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(ParamType5, param5, 5)) \
            ParamExpandOrEmpty6(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(ParamType6, param6, 6)) \
            ParamExpandOrEmpty7(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(ParamType7, param7, 7)) \
            return zftrue; \
        } \
        static inline ReturnType invoke(ZF_IN const ZFMethod *invokerMethod, \
                                        ZF_IN ZFObject *invokerObject \
                                        , ZF_IN ZFObject *param0 \
                                        , ZF_IN ZFObject *param1 \
                                        , ZF_IN ZFObject *param2 \
                                        , ZF_IN ZFObject *param3 \
                                        , ZF_IN ZFObject *param4 \
                                        , ZF_IN ZFObject *param5 \
                                        , ZF_IN ZFObject *param6 \
                                        , ZF_IN ZFObject *param7 \
                                        ) \
        {
#define _ZFP_ZFMETHOD_GENERIC_INVOKER_DECLARE_END() \
        } \
    };
#define _ZFP_ZFMETHOD_GENERIC_INVOKER_DECLARE_METHOD_TYPE( \
    ReturnType, methodName, methodSig \
    , ParamExpandOrEmpty0, ParamType0, param0, DefaultValueFix0 \
    , ParamExpandOrEmpty1, ParamType1, param1, DefaultValueFix1 \
    , ParamExpandOrEmpty2, ParamType2, param2, DefaultValueFix2 \
    , ParamExpandOrEmpty3, ParamType3, param3, DefaultValueFix3 \
    , ParamExpandOrEmpty4, ParamType4, param4, DefaultValueFix4 \
    , ParamExpandOrEmpty5, ParamType5, param5, DefaultValueFix5 \
    , ParamExpandOrEmpty6, ParamType6, param6, DefaultValueFix6 \
    , ParamExpandOrEmpty7, ParamType7, param7, DefaultValueFix7 \
    ) \
    _ZFP_ZFMETHOD_GENERIC_INVOKER_DECLARE_BEGIN( \
        ReturnType, methodSig \
        , ParamExpandOrEmpty0, ParamType0, param0, DefaultValueFix0 \
        , ParamExpandOrEmpty1, ParamType1, param1, DefaultValueFix1 \
        , ParamExpandOrEmpty2, ParamType2, param2, DefaultValueFix2 \
        , ParamExpandOrEmpty3, ParamType3, param3, DefaultValueFix3 \
        , ParamExpandOrEmpty4, ParamType4, param4, DefaultValueFix4 \
        , ParamExpandOrEmpty5, ParamType5, param5, DefaultValueFix5 \
        , ParamExpandOrEmpty6, ParamType6, param6, DefaultValueFix6 \
        , ParamExpandOrEmpty7, ParamType7, param7, DefaultValueFix7 \
        ) \
        return ZFCastZFObject(zfself *, invokerObject)->methodName( \
                ParamExpandOrEmpty0(ZFM_EMPTY() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess0, ParamType0, param0, 0)) \
                ParamExpandOrEmpty1(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess1, ParamType1, param1, 1)) \
                ParamExpandOrEmpty2(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess2, ParamType2, param2, 2)) \
                ParamExpandOrEmpty3(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess3, ParamType3, param3, 3)) \
                ParamExpandOrEmpty4(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess4, ParamType4, param4, 4)) \
                ParamExpandOrEmpty5(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess5, ParamType5, param5, 5)) \
                ParamExpandOrEmpty6(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess6, ParamType6, param6, 6)) \
                ParamExpandOrEmpty7(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess7, ParamType7, param7, 7)) \
            ); \
    _ZFP_ZFMETHOD_GENERIC_INVOKER_DECLARE_END() \
    friend zfclassFwd _ZFP_ZFMethodGenericInvoker_##methodSig;
#define _ZFP_ZFMETHOD_GENERIC_INVOKER_DECLARE_FUNC_TYPE( \
    ReturnType, funcAddr, methodSig \
    , ParamExpandOrEmpty0, ParamType0, param0, DefaultValueFix0 \
    , ParamExpandOrEmpty1, ParamType1, param1, DefaultValueFix1 \
    , ParamExpandOrEmpty2, ParamType2, param2, DefaultValueFix2 \
    , ParamExpandOrEmpty3, ParamType3, param3, DefaultValueFix3 \
    , ParamExpandOrEmpty4, ParamType4, param4, DefaultValueFix4 \
    , ParamExpandOrEmpty5, ParamType5, param5, DefaultValueFix5 \
    , ParamExpandOrEmpty6, ParamType6, param6, DefaultValueFix6 \
    , ParamExpandOrEmpty7, ParamType7, param7, DefaultValueFix7 \
    ) \
    _ZFP_ZFMETHOD_GENERIC_INVOKER_DECLARE_BEGIN( \
        ReturnType, methodSig \
        , ParamExpandOrEmpty0, ParamType0, param0, DefaultValueFix0 \
        , ParamExpandOrEmpty1, ParamType1, param1, DefaultValueFix1 \
        , ParamExpandOrEmpty2, ParamType2, param2, DefaultValueFix2 \
        , ParamExpandOrEmpty3, ParamType3, param3, DefaultValueFix3 \
        , ParamExpandOrEmpty4, ParamType4, param4, DefaultValueFix4 \
        , ParamExpandOrEmpty5, ParamType5, param5, DefaultValueFix5 \
        , ParamExpandOrEmpty6, ParamType6, param6, DefaultValueFix6 \
        , ParamExpandOrEmpty7, ParamType7, param7, DefaultValueFix7 \
        ) \
        return (funcAddr)( \
                ParamExpandOrEmpty0(ZFM_EMPTY() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess0, ParamType0, param0, 0)) \
                ParamExpandOrEmpty1(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess1, ParamType1, param1, 1)) \
                ParamExpandOrEmpty2(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess2, ParamType2, param2, 2)) \
                ParamExpandOrEmpty3(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess3, ParamType3, param3, 3)) \
                ParamExpandOrEmpty4(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess4, ParamType4, param4, 4)) \
                ParamExpandOrEmpty5(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess5, ParamType5, param5, 5)) \
                ParamExpandOrEmpty6(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess6, ParamType6, param6, 6)) \
                ParamExpandOrEmpty7(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess7, ParamType7, param7, 7)) \
            ); \
    _ZFP_ZFMETHOD_GENERIC_INVOKER_DECLARE_END()
#define _ZFP_ZFMETHOD_GENERIC_INVOKER_DECLARE_USER_REGISTER( \
    ReturnType, methodInvoker, methodSig \
    , ParamExpandOrEmpty0, ParamType0, param0, DefaultValueFix0 \
    , ParamExpandOrEmpty1, ParamType1, param1, DefaultValueFix1 \
    , ParamExpandOrEmpty2, ParamType2, param2, DefaultValueFix2 \
    , ParamExpandOrEmpty3, ParamType3, param3, DefaultValueFix3 \
    , ParamExpandOrEmpty4, ParamType4, param4, DefaultValueFix4 \
    , ParamExpandOrEmpty5, ParamType5, param5, DefaultValueFix5 \
    , ParamExpandOrEmpty6, ParamType6, param6, DefaultValueFix6 \
    , ParamExpandOrEmpty7, ParamType7, param7, DefaultValueFix7 \
    ) \
    _ZFP_ZFMETHOD_GENERIC_INVOKER_DECLARE_BEGIN( \
        ReturnType, methodSig \
        , ParamExpandOrEmpty0, ParamType0, param0, DefaultValueFix0 \
        , ParamExpandOrEmpty1, ParamType1, param1, DefaultValueFix1 \
        , ParamExpandOrEmpty2, ParamType2, param2, DefaultValueFix2 \
        , ParamExpandOrEmpty3, ParamType3, param3, DefaultValueFix3 \
        , ParamExpandOrEmpty4, ParamType4, param4, DefaultValueFix4 \
        , ParamExpandOrEmpty5, ParamType5, param5, DefaultValueFix5 \
        , ParamExpandOrEmpty6, ParamType6, param6, DefaultValueFix6 \
        , ParamExpandOrEmpty7, ParamType7, param7, DefaultValueFix7 \
        ) \
        return (methodInvoker)(invokerMethod, invokerObject \
                ParamExpandOrEmpty0(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess0, ParamType0, param0, 0)) \
                ParamExpandOrEmpty1(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess1, ParamType1, param1, 1)) \
                ParamExpandOrEmpty2(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess2, ParamType2, param2, 2)) \
                ParamExpandOrEmpty3(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess3, ParamType3, param3, 3)) \
                ParamExpandOrEmpty4(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess4, ParamType4, param4, 4)) \
                ParamExpandOrEmpty5(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess5, ParamType5, param5, 5)) \
                ParamExpandOrEmpty6(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess6, ParamType6, param6, 6)) \
                ParamExpandOrEmpty7(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_INVOKE_EXPAND(_ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess7, ParamType7, param7, 7)) \
            ); \
    _ZFP_ZFMETHOD_GENERIC_INVOKER_DECLARE_END()
/* ZFMETHOD_MAX_PARAM */
#define _ZFP_ZFMETHOD_GENERIC_INVOKER_ADDR(ReturnType, methodSig) \
    _ZFP_ZFMethodGenericInvokerWrapper<_ZFP_ZFMethodGenericInvoker_##methodSig, ReturnType>::wrap
#define _ZFP_ZFMETHOD_GENERIC_INVOKER_CHECKER_ADDR(methodSig) \
    _ZFP_ZFMethodGenericInvoker_##methodSig::invokeCheck
#define _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(methodSig, N) \
    _ZFP_ZFMethodGenericInvoker_##methodSig::paramDefaultAccess##N

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFMethodGenericInvoker_h_

