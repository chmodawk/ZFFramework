/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFMethod.h
 * @brief reflectable method definination for ZFFramework
 */

#ifndef _ZFI_ZFMethod_h_
#define _ZFI_ZFMethod_h_

#include "ZFObjectClassTypeFwd.h"
#include "ZFMethodGenericInvoker.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief access type for ZFMethod
 */
typedef enum
{
    ZFMethodPrivilegeTypePublic, /**< @brief public */
    ZFMethodPrivilegeTypeProtected, /**< @brief protected */
    ZFMethodPrivilegeTypePrivate, /**< @brief private */
} ZFMethodPrivilegeType;
/** @brief string tokens */
#define ZFTOKEN_ZFMethodPrivilegeTypePublic zfText("public")
/** @brief string tokens */
#define ZFTOKEN_ZFMethodPrivilegeTypeProtected zfText("protected")
/** @brief string tokens */
#define ZFTOKEN_ZFMethodPrivilegeTypePrivate zfText("private")

// ============================================================
zfclassFwd ZFObject;
zfclassFwd ZFClass;
#define _ZFP_ZFMETHOD_INVOKER(N) \
    /** @brief see #ZFMethod */ \
    template<typename T_ReturnType ZFM_REPEAT(N, ZFMARCO_REPEAT_TEMPLATE, ZFM_COMMA)> \
    inline T_ReturnType execute(ZFObject *obj ZFM_REPEAT(N, ZFM_REPEAT_PARAM, ZFM_COMMA)) const \
    { \
        return ZFCastReinterpret( \
                T_ReturnType (*)(const ZFMethod *, ZFObject * ZFM_REPEAT(N, ZFM_REPEAT_PARAM, ZFM_COMMA)), \
                this->_ZFP_ZFMethod_invoker) \
            (this, obj ZFM_REPEAT(N, ZFM_REPEAT_NAME, ZFM_COMMA)); \
    } \
    /** @brief see #ZFMethod */ \
    template<typename T_ReturnType ZFM_REPEAT(N, ZFMARCO_REPEAT_TEMPLATE, ZFM_COMMA)> \
    inline T_ReturnType executeStatic(ZFM_REPEAT(N, ZFM_REPEAT_PARAM, ZFM_EMPTY)) const \
    { \
        return ZFCastReinterpret( \
                T_ReturnType (*)(const ZFMethod *, ZFObject * ZFM_REPEAT(N, ZFM_REPEAT_PARAM, ZFM_COMMA)), \
                this->_ZFP_ZFMethod_invoker) \
            (this, zfnull ZFM_REPEAT(N, ZFM_REPEAT_NAME, ZFM_COMMA)); \
    }

/**
 * @brief max param supported by ZFMethod
 */
#define ZFMETHOD_MAX_PARAM 8

// ============================================================
#define _ZFP_ZFMethodIsStatic() static
#define _ZFP_ZFMethodIsVirtual() virtual
#define _ZFP_ZFMethodIsNormal()
#define _ZFP_ZFMethodIsWhatTypeText(t) (ZFM_TOSTRING(ZFM_CAT(_, t())) + 1)
/** @brief see #ZFMethod */
#define ZFMethodIsStatic _ZFP_ZFMethodIsStatic
/** @brief see #ZFMethod */
#define ZFMethodIsVirtual _ZFP_ZFMethodIsVirtual
/** @brief see #ZFMethod */
#define ZFMethodIsNormal _ZFP_ZFMethodIsNormal

// ============================================================
#define _ZFP_ZFMethodNoDefaultParam ZFM_EMPTY
#define _ZFP_ZFMethodDefaultParam(DefaultValue) \
    = (DefaultValue) ZFM_EMPTY

// tricks to solve empty macro expansion when cross platform
// default param would be expanded by
//   ZFM_TOSTRING_DIRECT(DefaultValueFix())
// which would be expanded to
//   "= (DefaultValue) ZFM_EMPTY()"
#define _ZFP_ZFMethodHasDefaultParam(text) \
    (zfslen(text) > 16) /* length of "= () ZFM_EMPTY()" */
#define _ZFP_ZFMethodDefaultParamText(text) \
    zfstring( \
            text + 3, /* length of "= (" */ \
            zfslen(text) - 16 /* length of "= () ZFM_EMPTY()" */ \
            )

/**
 * @brief macro to wrap param types for #ZFMETHOD_DECLARE_0 series
 *
 * similar to #ZF_IN for normal methods,
 * here's a list of these macros used for #ZFMETHOD_DECLARE_0 series:
 * -  #ZFMP_IN
 * -  #ZFMP_IN_OPT
 * -  #ZFMP_OUT
 * -  #ZFMP_OUT_OPT
 * -  #ZFMP_IN_OUT
 * -  #ZFMP_IN_OUT_OPT
 */
#define ZFMP_IN(ParamType, paramName) \
    ParamType, paramName, _ZFP_ZFMethodNoDefaultParam
/** @brief see #ZFMP_IN */
#define ZFMP_IN_OPT(ParamType, paramName, DefaultValue) \
    ParamType, paramName, _ZFP_ZFMethodDefaultParam(DefaultValue)
/** @brief see #ZFMP_IN */
#define ZFMP_OUT(ParamType, paramName) \
    ParamType, paramName, _ZFP_ZFMethodNoDefaultParam
/** @brief see #ZFMP_IN */
#define ZFMP_OUT_OPT(ParamType, paramName, DefaultValue) \
    ParamType, paramName, _ZFP_ZFMethodDefaultParam(DefaultValue)
/** @brief see #ZFMP_IN */
#define ZFMP_IN_OUT(ParamType, paramName) \
    ParamType, paramName, _ZFP_ZFMethodNoDefaultParam
/** @brief see #ZFMP_IN */
#define ZFMP_IN_OUT_OPT(ParamType, paramName, DefaultValue) \
    ParamType, paramName, _ZFP_ZFMethodDefaultParam(DefaultValue)

/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMethodFuncNamespaceGlobalId ZF_NAMESPACE_GLOBAL_ID
/** @brief see #ZFMETHOD_FUNC_DECLARE_0 */
#define ZFMethodFuncNamespaceGlobal ZFM_TOSTRING(ZFMethodFuncNamespaceGlobalId)

typedef zfautoObject (*_ZFP_ZFMethodParamDefaultValueAccessCallback)(void);

// ============================================================
/**
 * @brief reflectable method for ZFObject
 *
 * (for function type of ZFMethod, please refer to #ZFMETHOD_FUNC_DECLARE_0)\n
 * \n
 * to use ZFMethod, you must first declare it in your class:
 * @code
 *   zfclass YourClass : zfextends ZFObject
 *   {
 *       ZFOBJECT_DECLARE(YourClass, ZFObject)
 *      / **
 *        * you can add doxygen docs here
 *        * /
 *       ZFMETHOD_DECLARE_0(void, yourMethod)
 *       {
 *           // method code here
 *       }
 *   };
 * @endcode
 * or you may want to declare in header and define in cpp file:
 * @code
 *   // YourClass.h
 *   zfclass YourClass : zfextends ZFObject
 *   {
 *       ZFOBJECT_DECLARE(YourClass, ZFObject)
 *       ZFMETHOD_DECLARE_0(void, yourMethod); // declare only
 *   };
 *
 *   // YourClass.cpp
 *   ZFMETHOD_DEFINE_0(YourClass, void, yourMethod)
 *   {
 *       // method code here
 *   }
 * @endcode
 * you can use any types for return value and param, including reference type,
 * while the param's num is limited to #ZFMETHOD_MAX_PARAM\n
 * \n
 * the ZFMETHOD_DECLARE_XXX macro takes many params,
 * to walk through it, let's take a example:
 * @code
 *   ZFMETHOD_DECLARE_DETAIL_2(
 *       PublicOrProtectedOrPrivate, ZFMethodIsWhatType,
 *       ReturnType, MethodName
 *       , ZFMP_IN(ParamType0, param0)
 *       , ZFMP_IN_OPT(ParamType1, param1, DefaultValue1)
 *       )
 * @endcode
 * -  PublicOrProtectedOrPrivate is the access type for the method,
 *   could be: public, protected, private
 * -  ZFMethodIsWhatType indicates the method's type,
 *   could be: ZFMethodIsStatic, ZFMethodIsVirtual, ZFMethodIsNormal
 * -  ReturnType is the method's return value's type,
 *   could be any types
 * -  MethodName is the method's name
 * -  ParamTypeN is the type of param at index N,
 *   could be any types
 * -  paramN is the name of param at index N,
 *   could be any string valid for a variable name
 * -  DefaultValueN is the default value for the param
 *
 * to override a method declared in parent,
 * subclass should use ZFMETHOD_OVERRIDE_DECLARE_XXX/ZFMETHOD_OVERRIDE_DEFINE_XXX,
 * which is similar to ZFMETHOD_DECLARE_XXX/ZFMETHOD_DEFINE_XXX\n
 * overrided method isn't belong to subclass,
 * they still can only be found by parent's ZFClass\n
 * \n
 * once declared, the method would be automatically registered to
 * it's owner class when at least one instance created\n
 * also, similar to #ZFOBJECT_REGISTER,
 * you can add ZFMETHOD_REGISTER to your header file or cpp file to
 * statically register ZFMethod, so that you may access the method
 * even if none of instance ever created\n
 * \n
 * to access the method, use ZFMethodAccess/ZFMethodAccessDetail_0 is recommended:
 * @code
 *   const ZFMethod *method = ZFMethodAccess(YourClassType, yourMethodName);
 * @endcode
 * also, you may use ZFClass's member function to reflect from string,
 * such as methodForName (see #ZFClass for more info)\n
 * \n
 * once you have successfully get the ZFMethod data,
 * you can execute it without knowing the owner's class type:
 * @code
 *   const ZFClass *cls = ...; // we may not know the actual class type
 *   const ZFMethod *method = cls->methodForName(zfText("someMethod"));
 *   zfautoObject objTmp = cls->newInstance();
 *   ZFObject *obj = objTmp.toObject();
 *
 *   if(!method->methodIsStatic())
 *   { // execute
 *       YourReturnType result = method->execute<YourReturnType, ParamType...>(obj, someParam...);
 *   }
 *   else
 *   { // or executeStatic if the method is static
 *       YourReturnType result = method->executeStatic<YourReturnType, ParamType...>(someParam...);
 *   }
 *
 *   // or, you may use generic version:
 *   method->execute<YourReturnType, ParamType...>(obj, someParam...);
 * @endcode
 * @warning you take the full responsibility to make sure
 *   the ReturnType and ParamType exactly match the method,
 *   if not, no compile error would occurred,
 *   but app may (or may not) crash at runtime
 *
 * \n
 * if you want to reflect overloaded method, use both methodName and param's type id
 * @code
 *   cls->methodForName(zfText("methodName"), ZFPropertyTypeIdData<Param0>::PropertyTypeId());
 * @endcode
 *
 * @warning in subclass, you may declare a method with the same name of parent's one,
 *   but the behavior may be unexpected in some situations,
 *   so it's highly deprecated to do so
 * @note it's thread-safe to execute ZFMethod,
 *   but whether the actual run code (the code in the method body)
 *   is thread-safe, is depends on you
 */
zffinal zfclassNotPOD ZF_ENV_EXPORT ZFMethod
{
    ZFCLASS_DISALLOW_COPY_CONSTRUCTOR(ZFMethod)

public:
    zfbool _ZFP_ZFMethodNeedInit;
    void _ZFP_ZFMethod_init(ZF_IN zfbool methodIsUserRegister,
                            ZF_IN ZFFuncAddrType invoker,
                            ZF_IN ZFMethodGenericInvoker methodGenericInvoker,
                            ZF_IN const zfchar *methodIsWhatType,
                            ZF_IN const zfchar *methodName,
                            ZF_IN const zfchar *returnTypeId,
                            ZF_IN const zfchar *returnTypeName,
                            /* ParamTypeIdString, ParamTypeString, DefaultValueString, DefaultValueAccessCallback, end with zfnull */
                            ...);
    void _ZFP_ZFMethod_initClassMemberType(ZF_IN const ZFClass *methodOwnerClass,
                                           ZF_IN ZFMethodPrivilegeType privilegeType);
    void _ZFP_ZFMethod_initFuncType(ZF_IN const zfchar *methodNamespace);
    /** @cond ZFPrivateDoc */
    ZFMethod(void);
    /** @endcond */
    ~ZFMethod(void);

public:
    _ZFP_ZFMETHOD_INVOKER(0)
    _ZFP_ZFMETHOD_INVOKER(1)
    _ZFP_ZFMETHOD_INVOKER(2)
    _ZFP_ZFMETHOD_INVOKER(3)
    _ZFP_ZFMETHOD_INVOKER(4)
    _ZFP_ZFMETHOD_INVOKER(5)
    _ZFP_ZFMETHOD_INVOKER(6)
    _ZFP_ZFMETHOD_INVOKER(7)
    _ZFP_ZFMETHOD_INVOKER(8)
    /* ZFMETHOD_MAX_PARAM */

public:
    /**
     * @brief get a short info about the method
     *
     * may look like this: \n
     *   OwnerClass::MethodName
     */
    void objectInfoT(ZF_IN_OUT zfstring &ret) const;
    /** @brief see #objectInfoT */
    zfstring objectInfo(void) const
    {
        zfstring ret;
        this->objectInfoT(ret);
        return ret;
    }

    // ============================================================
    // general
public:
    /**
     * @brief internal method id, for debug use only
     */
    inline const zfchar *methodInternalId(void) const
    {
        return this->_ZFP_ZFMethod_methodInternalId;
    }
    /**
     * @brief whether the method is registered by #ZFMethodUserRegister_0
     */
    inline zfbool methodIsUserRegister(void) const
    {
        return this->_ZFP_ZFMethod_methodIsUserRegister;
    }
    /**
     * @brief get the method's name
     */
    inline const zfchar *methodName(void) const
    {
        return this->_ZFP_ZFMethod_methodName.cString();
    }

    /**
     * @brief get the method's return value's type id
     */
    inline const zfchar *methodReturnTypeId(void) const
    {
        return this->_ZFP_ZFMethod_returnTypeId.cString();
    }
    /**
     * @brief get the method's return value's type name
     */
    inline const zfchar *methodReturnTypeName(void) const
    {
        return this->_ZFP_ZFMethod_returnTypeName.cString();
    }

    /**
     * @brief get the method's param num
     */
    inline zfindex methodParamCount(void) const
    {
        return this->_ZFP_ZFMethod_paramCount;
    }
    /**
     * @brief get the method's param type id at index
     */
    inline const zfchar *methodParamTypeIdAtIndex(ZF_IN zfindex index) const
    {
        zfCoreAssert(index < this->methodParamCount());
        return this->_ZFP_ZFMethod_paramTypeIdList[index];
    }
    /**
     * @brief get the method's param type name at index
     */
    inline const zfchar *methodParamTypeNameAtIndex(ZF_IN zfindex index) const
    {
        zfCoreAssert(index < this->methodParamCount());
        return this->_ZFP_ZFMethod_paramTypeNameList[index];
    }
    /**
     * @brief get the method's param default name at index, null if no default param
     */
    inline const zfchar *methodParamDefaultNameAtIndex(ZF_IN zfindex index) const
    {
        zfCoreAssert(index < this->methodParamCount());
        return (this->_ZFP_ZFMethod_paramDefaultNameList[index].isEmpty()
                ? zfnull
                : this->_ZFP_ZFMethod_paramDefaultNameList[index].cString()
            );
    }
    /**
     * @brief get the method's param default value at index, #zfautoObjectNull if no default param
     */
    inline zfautoObject methodParamDefaultValueAtIndex(ZF_IN zfindex index) const
    {
        zfCoreAssert(index < this->methodParamCount());
        if(index < this->methodParamDefaultBeginIndex())
        {
            return zfautoObjectNull;
        }
        else
        {
            return this->_ZFP_ZFMethod_paramDefaultValueAccessCallbackList[index]();
        }
    }
    /**
     * @brief return the first default param's index, or #zfindexMax if no default param
     */
    inline zfindex methodParamDefaultBeginIndex(void) const
    {
        return this->_ZFP_ZFMethod_paramDefaultBeginIndex;
    }

    /**
     * @brief invoker function address for both class member type and function type
     *
     * proto type:
     * @code
     *   ReturnType methodInvoker(ZF_IN const ZFMethod *method,
     *                            ZF_IN ZFObject *ownerObjectOrNull,
     *                            ZF_IN ParamType0 param0,
     *                            ZF_IN ParamType1 param1
     *                            / * ... * /);
     * @endcode
     */
    inline ZFFuncAddrType methodInvoker(void) const
    {
        return this->_ZFP_ZFMethod_invoker;
    }
    /**
     * @brief override original #methodInvoker
     *
     * set null to remove the overrided value,
     * the original invoker can be accessed by #methodInvokerOrg
     * @note no safe check for the method's proto type,
     *   you must ensure it's valid and safe to be called
     * @note assume the original method's proto type is:
     *   @code
     *     ReturnType method(ParamType0, ParamType1, ...);
     *   @endcode
     *   then the invoker's proto type must be:
     *   @code
     *     ReturnType method(ZFObject *, ParamType0, ParamType1, ...);
     *   @endcode
     * @note overriding the invoker only affect methods when they are reflected,
     *   calling it directly won't be affected
     *   @code
     *     obj->myMethod(); // won't be affected
     *     method->execute<void>(obj); // would be affected
     *   @endcode
     */
    void methodInvokerSet(ZF_IN ZFFuncAddrType methodInvoker) const;
    /**
     * @brief see #methodInvokerSet
     */
    inline ZFFuncAddrType methodInvokerOrg(void) const
    {
        return this->_ZFP_ZFMethod_invokerOrg;
    }

    /**
     * @brief generic invoker for advanced reflection
     *
     * as a static language, C++'s function invoking require explicit type declaration,
     * which is a pain when binding with script languages\n
     * since ZFFramework supply reflection (though limited),
     * we are trying to solve the dynamic script binding, how it works:
     * -  #ZFPropertyTypeIdData::Value\n
     *   to supply type conversion to ZFObject types without knowing actual type
     * -  #ZFMethodGenericInvoker\n
     *   to invoke the reflectable method without static type binding
     *   (all params and result are #ZFObject types)
     *
     * \n
     * typical steps for users:
     * -# have all methods you need to bind been declared by #ZFMETHOD_DECLARE_0 series
     * -# supply wrapper class to hold the type
     * -# ensure all params can be converted to ZFObject types,
     *   by declaring them by #ZFPROPERTY_TYPE_DECLARE
     * -# all done, all binding works should be done by impl
     *
     * \n
     * typical steps for impl:
     * -# supply type convert methods to bind #ZFPropertyTypeIdData::Value types to script languages
     * -# using reflection of #ZFClass and #ZFMethod,
     *   to bind all class and methods to script languages
     *
     * \n
     * the final script that calling ZFFFramework, should look like:
     * @code
     *   var obj = MyZFObjectType::newInstance();
     *   var objParam = SomeType::newInstance();
     *   var result = obj.myFunc(v_zfnumber(1), v_zfstring("2"), objParam)
     * @endcode
     */
    inline ZFMethodGenericInvoker methodGenericInvoker(void) const
    {
        return this->_ZFP_ZFMethod_methodGenericInvoker;
    }
    /**
     * @brief util method to invoke #methodGenericInvoker
     */
    inline zfautoObject methodGenericInvoke(ZF_IN_OPT ZFObject *ownerObjOrNull = zfnull
                                            , ZF_IN_OPT ZFObject *param0 = ZFMethodGenericInvokerDefaultParam
                                            , ZF_IN_OPT ZFObject *param1 = ZFMethodGenericInvokerDefaultParam
                                            , ZF_IN_OPT ZFObject *param2 = ZFMethodGenericInvokerDefaultParam
                                            , ZF_IN_OPT ZFObject *param3 = ZFMethodGenericInvokerDefaultParam
                                            , ZF_IN_OPT ZFObject *param4 = ZFMethodGenericInvokerDefaultParam
                                            , ZF_IN_OPT ZFObject *param5 = ZFMethodGenericInvokerDefaultParam
                                            , ZF_IN_OPT ZFObject *param6 = ZFMethodGenericInvokerDefaultParam
                                            , ZF_IN_OPT ZFObject *param7 = ZFMethodGenericInvokerDefaultParam
                                            , ZF_OUT_OPT zfstring *errorHint = zfnull
                                            ) const
    {
        zfautoObject ret;
        this->methodGenericInvoker()(this, ownerObjOrNull, errorHint, ret
                , param0
                , param1
                , param2
                , param3
                , param4
                , param5
                , param6
                , param7
            );
        return ret;
    }
    /* ZFMETHOD_MAX_PARAM */
    /**
     * @brief see #methodGenericInvokerSet
     */
    inline ZFMethodGenericInvoker methodGenericInvokerOrg(void) const
    {
        return this->_ZFP_ZFMethod_methodGenericInvokerOrg;
    }

    /**
     * @brief change default impl for #methodGenericInvoker
     *
     * the original invoker can be accessed by #methodGenericInvokerOrg
     */
    void methodGenericInvokerSet(ZF_IN ZFMethodGenericInvoker methodGenericInvoker) const;

    // ============================================================
    // class member type
public:
    /**
     * @brief get the owner's class info
     */
    inline const ZFClass *methodOwnerClass(void) const
    {
        return this->_ZFP_ZFMethod_methodOwnerClass;
    }

    /**
     * @brief get the method's access type
     */
    inline ZFMethodPrivilegeType methodPrivilegeType(void) const
    {
        return this->_ZFP_ZFMethod_privilegeType;
    }

    /**
     * @brief true if method is static
     */
    inline zfbool methodIsStatic(void) const
    {
        return this->_ZFP_ZFMethod_methodIsStatic;
    }

    /**
     * @brief true if method is virtual
     */
    inline zfbool methodIsVirtual(void) const
    {
        return this->_ZFP_ZFMethod_methodIsVirtual;
    }

    // ============================================================
    // func type
public:
    /**
     * @brief true if this method is function type (declared by ZFMETHOD_FUNC_DECLARE_XXX series)
     */
    inline zfbool methodIsFunctionType(void) const
    {
        return (this->_ZFP_ZFMethod_methodOwnerClass == zfnull);
    }
    /**
     * @brief get the method namespace, for func type only
     */
    inline const zfchar *methodNamespace(void) const
    {
        return this->_ZFP_ZFMethod_methodNamespace.cString();
    }

public:
    ZFMethod *_ZFP_ZFMethod_removeConst(void) const
    {
        return const_cast<ZFMethod *>(this);
    }

public:
    // general
    zfstring _ZFP_ZFMethod_methodInternalId;
    zfbool _ZFP_ZFMethod_methodIsUserRegister;
    ZFFuncAddrType _ZFP_ZFMethod_invoker;
    ZFFuncAddrType _ZFP_ZFMethod_invokerOrg;
    ZFMethodGenericInvoker _ZFP_ZFMethod_methodGenericInvoker;
    ZFMethodGenericInvoker _ZFP_ZFMethod_methodGenericInvokerOrg;
    zfstring _ZFP_ZFMethod_methodName;
    zfstring _ZFP_ZFMethod_returnTypeId;
    zfstring _ZFP_ZFMethod_returnTypeName;
    zfindex _ZFP_ZFMethod_paramCount;
    zfstring _ZFP_ZFMethod_paramTypeIdList[ZFMETHOD_MAX_PARAM];
    zfstring _ZFP_ZFMethod_paramTypeNameList[ZFMETHOD_MAX_PARAM];
    zfstring _ZFP_ZFMethod_paramDefaultNameList[ZFMETHOD_MAX_PARAM];
    _ZFP_ZFMethodParamDefaultValueAccessCallback _ZFP_ZFMethod_paramDefaultValueAccessCallbackList[ZFMETHOD_MAX_PARAM];
    zfindex _ZFP_ZFMethod_paramDefaultBeginIndex;

    // for class member type
    const ZFClass *_ZFP_ZFMethod_methodOwnerClass;
    ZFMethodPrivilegeType _ZFP_ZFMethod_privilegeType;
    zfbool _ZFP_ZFMethod_methodIsStatic;
    zfbool _ZFP_ZFMethod_methodIsVirtual;

    // for func type
    zfstring _ZFP_ZFMethod_methodNamespace;
};

// ============================================================
extern ZF_ENV_EXPORT ZFMethod *_ZFP_ZFMethodRegister(ZF_IN zfbool methodIsUserRegister
                                                     , ZF_IN ZFFuncAddrType methodInvoker
                                                     , ZF_IN ZFMethodGenericInvoker methodGenericInvoker
                                                     , ZF_IN const zfchar *methodIsWhatType
                                                     , ZF_IN const ZFClass *methodOwnerClass
                                                     , ZF_IN ZFMethodPrivilegeType methodPrivilegeType
                                                     , ZF_IN const zfchar *methodNamespace
                                                     , ZF_IN const zfchar *methodExtSig
                                                     , ZF_IN const zfchar *methodName
                                                     , ZF_IN const zfchar *returnTypeId
                                                     , ZF_IN const zfchar *returnTypeName
                                                     /* ParamTypeIdString, ParamTypeString, DefaultValueString, DefaultValueAccessCallback, end with zfnull */
                                                     , ...
                                                     );
extern ZF_ENV_EXPORT ZFMethod *_ZFP_ZFMethodRegisterV(ZF_IN zfbool methodIsUserRegister
                                                      , ZF_IN ZFFuncAddrType methodInvoker
                                                      , ZF_IN ZFMethodGenericInvoker methodGenericInvoker
                                                      , ZF_IN const zfchar *methodIsWhatType
                                                      , ZF_IN const ZFClass *methodOwnerClass
                                                      , ZF_IN ZFMethodPrivilegeType methodPrivilegeType
                                                      , ZF_IN const zfchar *methodNamespace
                                                      , ZF_IN const zfchar *methodExtSig
                                                      , ZF_IN const zfchar *methodName
                                                      , ZF_IN const zfchar *returnTypeId
                                                      , ZF_IN const zfchar *returnTypeName
                                                      /* ParamTypeIdString, ParamTypeString, DefaultValueString, DefaultValueAccessCallback, end with zfnull */
                                                      , ZF_IN va_list vaList
                                                      );
extern ZF_ENV_EXPORT void _ZFP_ZFMethodUnregister(ZF_IN const ZFMethod *method);

zfclassLikePOD ZF_ENV_EXPORT _ZFP_ZFMethodRegisterHolder
{
public:
    _ZFP_ZFMethodRegisterHolder(ZF_IN zfbool methodIsUserRegister
                                , ZF_IN ZFFuncAddrType methodInvoker
                                , ZF_IN ZFMethodGenericInvoker methodGenericInvoker
                                , ZF_IN const zfchar *methodIsWhatType
                                , ZF_IN const ZFClass *methodOwnerClass
                                , ZF_IN ZFMethodPrivilegeType methodPrivilegeType
                                , ZF_IN const zfchar *methodNamespace
                                , ZF_IN const zfchar *methodExtSig
                                , ZF_IN const zfchar *methodName
                                , ZF_IN const zfchar *returnTypeId
                                , ZF_IN const zfchar *returnTypeName
                                /* ParamTypeIdString, ParamTypeString, DefaultValueString, DefaultValueAccessCallback, end with zfnull */
                                , ...
                                );
    _ZFP_ZFMethodRegisterHolder(ZF_IN zfbool dummy
                                , ZF_IN zfbool methodIsUserRegister
                                , ZF_IN ZFFuncAddrType methodInvoker
                                , ZF_IN ZFMethodGenericInvoker methodGenericInvoker
                                , ZF_IN const zfchar *methodIsWhatType
                                , ZF_IN const ZFClass *methodOwnerClass
                                , ZF_IN ZFMethodPrivilegeType methodPrivilegeType
                                , ZF_IN const zfchar *methodNamespace
                                , ZF_IN const zfchar *methodExtSig
                                , ZF_IN const zfchar *methodName
                                , ZF_IN const zfchar *returnTypeId
                                , ZF_IN const zfchar *returnTypeName
                                /* ParamTypeIdString, ParamTypeString, DefaultValueString, DefaultValueAccessCallback, end with zfnull */
                                , ZF_IN va_list vaList
                                );
    ~_ZFP_ZFMethodRegisterHolder(void);
public:
    ZFMethod *method;
};

// ============================================================
zfclassFwd ZFFilterForZFMethod;
/**
 * @brief get all method currently registered, for debug use only
 */
extern ZF_ENV_EXPORT void ZFMethodGetAll(ZF_OUT ZFCoreArray<const ZFMethod *> &ret,
                                         ZF_IN_OPT const ZFFilterForZFMethod *methodFilter = zfnull);
/**
 * @brief get all method currently registered, for debug use only
 */
inline ZFCoreArrayPOD<const ZFMethod *> ZFMethodGetAll(ZF_IN_OPT const ZFFilterForZFMethod *methodFilter = zfnull)
{
    ZFCoreArrayPOD<const ZFMethod *> ret;
    ZFMethodGetAll(ret, methodFilter);
    return ret;
}

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFMethod_h_

#include "ZFMethodDeclare.h"
#include "ZFMethodFuncDeclare.h"
#include "ZFFilterForZFMethod.h"

