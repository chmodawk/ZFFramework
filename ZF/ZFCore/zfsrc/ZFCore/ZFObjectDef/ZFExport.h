/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFExport.h
 * @brief util to export global variable
 */

#ifndef _ZFI_ZFExport_h_
#define _ZFI_ZFExport_h_

#include "ZFMethodFuncDeclare.h"
#include "ZFMethodFuncUserRegister.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief util to export global variable
 *
 * the variable are exported as #ZFMETHOD_FUNC_DECLARE_0,
 * and can only be exported to global #ZFMethodFuncNamespaceGlobal namespace\n
 * usage:
 * @code
 *   // in header file
 *   ZFEXPORT_VAR_DECLARE(YourType, yourName)
 *
 *   // in source file
 *   ZFEXPORT_VAR_DEFINE(YourType, yourName, yourInitValue)
 *
 *   // access
 *   YourType &v = yourName();
 *   // modify
 *   yourNameSet(v);
 * @endcode
 *
 * for readonly var, use #ZFEXPORT_VAR_READONLY_DECLARE\n
 * to alias existing var, use #ZFEXPORT_VAR_DEFINE_ALIAS/#ZFEXPORT_VAR_READONLY_DEFINE_ALIAS
 */
#define ZFEXPORT_VAR_DECLARE(Type, Name) \
    /** \n */ \
    ZFMETHOD_FUNC_DECLARE_0(Type &, Name) \
    /** @brief see @ref Name */ \
    ZFMETHOD_FUNC_DECLARE_1(void, ZFM_CAT(Name, Set), ZFMP_IN(Type const &, v))
/** @brief see #ZFEXPORT_VAR_DECLARE */
#define ZFEXPORT_VAR_DEFINE(Type, Name, initValue) \
    ZFEXPORT_VAR_DEFINE_DETAIL(Type, Name, ZFLevelZFFrameworkHigh, {v = initValue;}, {})
/** @brief see #ZFEXPORT_VAR_DECLARE */
#define ZFEXPORT_VAR_DEFINE_DETAIL(Type, Name, ZFLevel_, initAction, deallocAction) \
    _ZFP_ZFEXPORT_VAR_DEFINE(Type, Name, ZFLevel_, initAction, deallocAction)
/** @brief see #ZFEXPORT_VAR_DECLARE */
#define ZFEXPORT_VAR_DEFINE_ALIAS(Type, Name, AliasName) \
    ZFMETHOD_FUNC_DEFINE_0(Type &, Name) \
    { \
        return (AliasName)(); \
    } \
    ZFMETHOD_FUNC_DEFINE_1(void, ZFM_CAT(Name, Set), ZFMP_IN(Type const &, v)) \
    { \
        (ZFM_CAT(AliasName, Set))(v); \
    }

#define _ZFP_ZFEXPORT_VAR_DEFINE(Type, Name, ZFLevel_, initAction, deallocAction) \
    ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(GlobV_##Name, ZFLevel_) \
    { \
        initAction \
    } \
    ZF_GLOBAL_INITIALIZER_DESTROY(GlobV_##Name) \
    { \
        deallocAction \
    } \
    Type v; \
    ZF_GLOBAL_INITIALIZER_END(GlobV_##Name) \
    ZFMETHOD_FUNC_DEFINE_0(Type &, Name) \
    { \
        return ZF_GLOBAL_INITIALIZER_INSTANCE(GlobV_##Name)->v; \
    } \
    ZFMETHOD_FUNC_DEFINE_1(void, ZFM_CAT(Name, Set), ZFMP_IN(Type const &, v)) \
    { \
        ZF_GLOBAL_INITIALIZER_INSTANCE(GlobV_##Name)->v = v; \
    }

// ============================================================
/** @brief see #ZFEXPORT_VAR_DECLARE */
#define ZFEXPORT_VAR_READONLY_DECLARE(Type, Name) \
    /** \n */ \
    ZFMETHOD_FUNC_DECLARE_0(Type const &, Name)
/** @brief see #ZFEXPORT_VAR_DECLARE */
#define ZFEXPORT_VAR_READONLY_DEFINE(Type, Name, initValue) \
    ZFEXPORT_VAR_READONLY_DEFINE_DETAIL(Type, Name, ZFLevelZFFrameworkHigh, {v = initValue;}, {})
/** @brief see #ZFEXPORT_VAR_DECLARE */
#define ZFEXPORT_VAR_READONLY_DEFINE_DETAIL(Type, Name, ZFLevel_, initAction, deallocAction) \
    _ZFP_ZFEXPORT_VAR_READONLY_DEFINE(Type, Name, ZFLevel_, initAction, deallocAction)
/** @brief see #ZFEXPORT_VAR_DECLARE */
#define ZFEXPORT_VAR_READONLY_DEFINE_ALIAS(Type, Name, AliasName) \
    ZFMETHOD_FUNC_DEFINE_0(Type const &, Name) \
    { \
        return AliasName(); \
    }

#define _ZFP_ZFEXPORT_VAR_READONLY_DEFINE(Type, Name, ZFLevel_, initAction, deallocAction) \
    ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(GlobV_##Name, ZFLevel_) \
    { \
        initAction \
    } \
    ZF_GLOBAL_INITIALIZER_DESTROY(GlobV_##Name) \
    { \
        deallocAction \
    } \
    Type v; \
    ZF_GLOBAL_INITIALIZER_END(GlobV_##Name) \
    ZFMETHOD_FUNC_DEFINE_0(Type const &, Name) \
    { \
        return ZF_GLOBAL_INITIALIZER_INSTANCE(GlobV_##Name)->v; \
    }

// ============================================================
/**
 * @brief util macro to export raw enum value as zfint
 *
 * for normal enum, use #ZFENUM_BEGIN is recommended\n
 * this macro is used to export low level enum values by #ZFMETHOD_FUNC_USER_REGISTER_0,
 * with this proto type:
 * @code
 *   zfint YourRawEnumValueName(void);
 * @endcode
 */
#define ZFEXPORT_ENUM_DEFINE(EnumName, enumValues, ...) \
    _ZFP_ZFEXPORT_ENUM_DEFINE(ZF_CALLER_LINE, EnumName, enumValues, ##__VA_ARGS__)

#define _ZFP_ZFEXPORT_ENUM_DEFINE(...) \
    ZFM_EXPAND(_ZFP_ZFEXPORT_ENUM_DEFINE_(__VA_ARGS__))
#define _ZFP_ZFEXPORT_ENUM_DEFINE_(DECLARE_LINE, EnumName, enumValues, ...) \
    ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFEXPORT_ENUM_##EnumName##_##DECLARE_LINE, ZFLevelZFFrameworkNormal) \
    { \
        ZFM_FIX_PARAM(_ZFP_ZFEXPORT_ENUM_EXPAND, ZFM_EMPTY, enumValues, ##__VA_ARGS__) \
    } \
    ZF_GLOBAL_INITIALIZER_DESTROY(ZFEXPORT_ENUM_##EnumName##_##DECLARE_LINE) \
    { \
        for(zfindex i = 0; i < m.count(); ++i) \
        { \
            ZFMethodFuncUserUnregister(m[i]); \
        } \
    } \
    ZFCoreArrayPOD<const ZFMethod *> m; \
    ZF_GLOBAL_INITIALIZER_END(ZFEXPORT_ENUM_##EnumName##_##DECLARE_LINE)
#define _ZFP_ZFEXPORT_ENUM_EXPAND(v) \
    { \
        ZFMethodFuncUserRegister_0(resultMethod, {return v;}, zfint, v); \
        m.add(resultMethod); \
    }

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFExport_h_

