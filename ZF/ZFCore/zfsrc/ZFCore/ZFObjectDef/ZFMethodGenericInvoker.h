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
                                         , ZF_IN_OPT ZFObject *param0 /* = ZFMethodGenericInvokerDefaultParam */
                                         , ZF_IN_OPT ZFObject *param1 /* = ZFMethodGenericInvokerDefaultParam */
                                         , ZF_IN_OPT ZFObject *param2 /* = ZFMethodGenericInvokerDefaultParam */
                                         , ZF_IN_OPT ZFObject *param3 /* = ZFMethodGenericInvokerDefaultParam */
                                         , ZF_IN_OPT ZFObject *param4 /* = ZFMethodGenericInvokerDefaultParam */
                                         , ZF_IN_OPT ZFObject *param5 /* = ZFMethodGenericInvokerDefaultParam */
                                         , ZF_IN_OPT ZFObject *param6 /* = ZFMethodGenericInvokerDefaultParam */
                                         , ZF_IN_OPT ZFObject *param7 /* = ZFMethodGenericInvokerDefaultParam */
                                         );

extern ZF_ENV_EXPORT ZFObject *_ZFP_ZFMethodGenericInvokerDefaultParamRef;
inline ZFObject *_ZFP_ZFMethodGenericInvokerDefaultParam(void)
{
    return _ZFP_ZFMethodGenericInvokerDefaultParamRef;
}
/**
 * @brief mark the object as default param
 */
#define ZFMethodGenericInvokerDefaultParam _ZFP_ZFMethodGenericInvokerDefaultParam()

extern ZF_ENV_EXPORT zfautoObject _ZFP_ZFMethodGenericInvokerDefaultParamHolderRef;
inline const zfautoObject &_ZFP_ZFMethodGenericInvokerDefaultParamHolder(void)
{
    return _ZFP_ZFMethodGenericInvokerDefaultParamHolderRef;
}
/**
 * @brief holder of #ZFMethodGenericInvokerDefaultParam
 */
#define ZFMethodGenericInvokerDefaultParamHolder _ZFP_ZFMethodGenericInvokerDefaultParamHolder()

// ============================================================
template<typename T_Dummy, int n>
zfclassNotPOD _ZFP_MtdGICk
{
};
template<typename T_Dummy>
zfclassNotPOD _ZFP_MtdGICk<T_Dummy, 1>
{
public:
    typedef int TypeMustRegisterByZFPROPERTY;
};
extern ZF_ENV_EXPORT void _ZFP_MtdGIParamError(ZF_OUT_OPT zfstring *errorHint,
                                               ZF_IN zfindex paramIndex,
                                               ZF_IN const zfchar *paramTypeId,
                                               ZF_IN ZFObject *param);
#define _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(N, ParamType) \
    typedef ParamType _T##N; \
    typedef zftTraitsType<ParamType>::TraitsRemoveReference _TR##N; \
    typedef _ZFP_MtdGICk< \
            _TR##N, \
            ZFPropertyTypeIdData<_TR##N>::PropertyRegistered \
        >::TypeMustRegisterByZFPROPERTY _Ck##N;
#define _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(N, ParamType, param) \
    if(!(N >= invokerMethod->methodParamDefaultBeginIndex() && param == ZFMethodGenericInvokerDefaultParam) \
        && !ZFPropertyTypeIdData<_TR##N>::Value<_TR##N>::accessAvailable(param)) \
    { \
        _ZFP_MtdGIParamError(errorHint, (zfindex)N, ZFPropertyTypeIdData<_TR##N>::PropertyTypeId(), param); \
        return zffalse; \
    }
#define _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_ACCESS_EXPAND(N, ParamType, param) \
    ZFPropertyTypeIdData<_TR##N>::Value<_T##N>::access( \
            (param != ZFMethodGenericInvokerDefaultParam) \
            ? param \
            : pDef##N().toObject() \
        )
#define _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(N, ParamType, DefaultValueFix) \
    static zfautoObject pDef##N(void) \
    { \
        zftValue<zftTraitsType<ParamType>::TraitsRemoveReference> paramDefault; \
        zfautoObject ret; \
        ZFPropertyTypeIdData<zftTraitsType<ParamType>::TraitsRemoveReference>::ValueStore( \
            ret, \
            (paramDefault.zfv DefaultValueFix())); \
        return ret; \
    }

// ============================================================
extern ZF_ENV_EXPORT void _ZFP_MtdGIRetError(ZF_OUT_OPT zfstring *errorHint,
                                             ZF_IN const zfchar *returnTypeId,
                                             ZF_IN const zfchar *returnValueInfo);

template<typename T_ReturnType>
zfclassNotPOD _ZFP_ZFMethodGenericInvokerReturnFix
{
public:
    typedef T_ReturnType (*Ivk)(ZF_IN const ZFMethod *invokerMethod
                                , ZF_IN ZFObject *invokerObject
                                , ZF_IN ZFObject *param0
                                , ZF_IN ZFObject *param1
                                , ZF_IN ZFObject *param2
                                , ZF_IN ZFObject *param3
                                , ZF_IN ZFObject *param4
                                , ZF_IN ZFObject *param5
                                , ZF_IN ZFObject *param6
                                , ZF_IN ZFObject *param7
                                );
public:
    static zfbool action(ZF_IN Ivk invoke
                         , ZF_IN const ZFMethod *invokerMethod
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
        T_ReturnType retTmp = invoke(invokerMethod, invokerObject
                , param0
                , param1
                , param2
                , param3
                , param4
                , param5
                , param6
                , param7
            );
        if(ZFPropertyTypeIdData<typename zftTraitsType<T_ReturnType>::TraitsRemoveReference>::ValueStore(ret, retTmp))
        {
            return zftrue;
        }
        else
        {
            zfstring info;
            ZFCoreElementInfoGetter<typename zftTraitsType<T_ReturnType>::TraitsRemoveReference>::elementInfoGetter(info, retTmp);
            _ZFP_MtdGIRetError(errorHint,
                ZFPropertyTypeIdData<typename zftTraitsType<T_ReturnType>::TraitsRemoveReference>::PropertyTypeId(),
                info);
            return zffalse;
        }
    }
};
template<>
zfclassNotPOD _ZFP_ZFMethodGenericInvokerReturnFix<void>
{
public:
    typedef void (*Ivk)(ZF_IN const ZFMethod *invokerMethod
                        , ZF_IN ZFObject *invokerObject
                        , ZF_IN ZFObject *param0
                        , ZF_IN ZFObject *param1
                        , ZF_IN ZFObject *param2
                        , ZF_IN ZFObject *param3
                        , ZF_IN ZFObject *param4
                        , ZF_IN ZFObject *param5
                        , ZF_IN ZFObject *param6
                        , ZF_IN ZFObject *param7
                        );
public:
    static zfbool action(ZF_IN Ivk invoke
                         , ZF_IN const ZFMethod *invokerMethod
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
        invoke(invokerMethod, invokerObject
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
#define _ZFP_ZFMETHOD_GENERIC_INVOKER_DECLARE( \
    ReturnType, methodSig \
    , ParamExpandOrEmpty0, ParamType0, param0_, DefaultValueFix0 \
    , ParamExpandOrEmpty1, ParamType1, param1_, DefaultValueFix1 \
    , ParamExpandOrEmpty2, ParamType2, param2_, DefaultValueFix2 \
    , ParamExpandOrEmpty3, ParamType3, param3_, DefaultValueFix3 \
    , ParamExpandOrEmpty4, ParamType4, param4_, DefaultValueFix4 \
    , ParamExpandOrEmpty5, ParamType5, param5_, DefaultValueFix5 \
    , ParamExpandOrEmpty6, ParamType6, param6_, DefaultValueFix6 \
    , ParamExpandOrEmpty7, ParamType7, param7_, DefaultValueFix7 \
    ) \
    public: \
    zfclassNotPOD _ZFP_MtdGI_##methodSig \
    { \
    private: \
        ParamExpandOrEmpty0(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(0, ParamType0)) \
        ParamExpandOrEmpty1(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(1, ParamType1)) \
        ParamExpandOrEmpty2(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(2, ParamType2)) \
        ParamExpandOrEmpty3(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(3, ParamType3)) \
        ParamExpandOrEmpty4(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(4, ParamType4)) \
        ParamExpandOrEmpty5(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(5, ParamType5)) \
        ParamExpandOrEmpty6(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(6, ParamType6)) \
        ParamExpandOrEmpty7(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_DECLARE_EXPAND(7, ParamType7)) \
    public: \
        ParamExpandOrEmpty0(_ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(0, ParamType0, DefaultValueFix0)) \
        ParamExpandOrEmpty1(_ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(1, ParamType1, DefaultValueFix1)) \
        ParamExpandOrEmpty2(_ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(2, ParamType2, DefaultValueFix2)) \
        ParamExpandOrEmpty3(_ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(3, ParamType3, DefaultValueFix3)) \
        ParamExpandOrEmpty4(_ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(4, ParamType4, DefaultValueFix4)) \
        ParamExpandOrEmpty5(_ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(5, ParamType5, DefaultValueFix5)) \
        ParamExpandOrEmpty6(_ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(6, ParamType6, DefaultValueFix6)) \
        ParamExpandOrEmpty7(_ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS(7, ParamType7, DefaultValueFix7)) \
    public: \
        static zfbool GI(ZF_IN const ZFMethod *invokerMethod \
                         , ZF_IN ZFObject *invokerObject \
                         , ZF_OUT_OPT zfstring *errorHint \
                         , ZF_OUT_OPT zfautoObject &ret \
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
            ParamExpandOrEmpty0(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(0, ParamType0, param0)) \
            ParamExpandOrEmpty1(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(1, ParamType1, param1)) \
            ParamExpandOrEmpty2(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(2, ParamType2, param2)) \
            ParamExpandOrEmpty3(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(3, ParamType3, param3)) \
            ParamExpandOrEmpty4(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(4, ParamType4, param4)) \
            ParamExpandOrEmpty5(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(5, ParamType5, param5)) \
            ParamExpandOrEmpty6(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(6, ParamType6, param6)) \
            ParamExpandOrEmpty7(_ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_PREPARE_EXPAND(7, ParamType7, param7)) \
            return _ZFP_ZFMethodGenericInvokerReturnFix<ReturnType>::action(I, invokerMethod, invokerObject, errorHint, ret \
                    , param0 \
                    , param1 \
                    , param2 \
                    , param3 \
                    , param4 \
                    , param5 \
                    , param6 \
                    , param7 \
                ); \
        } \
        static ReturnType I(ZF_IN const ZFMethod *invokerMethod \
                            , ZF_IN ZFObject *invokerObject \
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
            return invokerMethod->execute<ReturnType \
                    ParamExpandOrEmpty0(ZFM_COMMA() ParamType0) \
                    ParamExpandOrEmpty1(ZFM_COMMA() ParamType1) \
                    ParamExpandOrEmpty2(ZFM_COMMA() ParamType2) \
                    ParamExpandOrEmpty3(ZFM_COMMA() ParamType3) \
                    ParamExpandOrEmpty4(ZFM_COMMA() ParamType4) \
                    ParamExpandOrEmpty5(ZFM_COMMA() ParamType5) \
                    ParamExpandOrEmpty6(ZFM_COMMA() ParamType6) \
                    ParamExpandOrEmpty7(ZFM_COMMA() ParamType7) \
                >(invokerObject \
                    ParamExpandOrEmpty0(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_ACCESS_EXPAND(0, ParamType0, param0)) \
                    ParamExpandOrEmpty1(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_ACCESS_EXPAND(1, ParamType1, param1)) \
                    ParamExpandOrEmpty2(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_ACCESS_EXPAND(2, ParamType2, param2)) \
                    ParamExpandOrEmpty3(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_ACCESS_EXPAND(3, ParamType3, param3)) \
                    ParamExpandOrEmpty4(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_ACCESS_EXPAND(4, ParamType4, param4)) \
                    ParamExpandOrEmpty5(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_ACCESS_EXPAND(5, ParamType5, param5)) \
                    ParamExpandOrEmpty6(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_ACCESS_EXPAND(6, ParamType6, param6)) \
                    ParamExpandOrEmpty7(ZFM_COMMA() _ZFP_ZFMETHOD_GENERIC_INVOKER_PARAM_ACCESS_EXPAND(7, ParamType7, param7)) \
                ); \
        } \
    };
/* ZFMETHOD_MAX_PARAM */
#define _ZFP_ZFMETHOD_GENERIC_INVOKER_ADDR(ReturnType, methodSig) \
    _ZFP_MtdGI_##methodSig::GI
#define _ZFP_ZFMETHOD_GENERIC_PARAM_DEFAULT_ACCESS_ADDR(methodSig, N) \
    _ZFP_MtdGI_##methodSig::pDef##N

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFMethodGenericInvoker_h_

