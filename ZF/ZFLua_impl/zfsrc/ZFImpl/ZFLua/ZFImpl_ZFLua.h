/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFImpl_ZFLua.h
 * @brief global header for lua impl
 */

#ifndef _ZFI_ZFImpl_ZFLua_h_
#define _ZFI_ZFImpl_ZFLua_h_

#include "ZFLua.h"

#include "../../../zfsrc_ext/ZFImpl/_repo/ELuna.h"

ZF_NAMESPACE_GLOBAL_BEGIN

extern ZF_ENV_EXPORT lua_State *_ZFP_ZFImpl_ZFLua_luaState(void);
/**
 * @brief global lua state for lua impl
 *
 * lua state would be initialized during #ZFFrameworkInit as level #ZFLevelAppEssential\n
 * \n
 * if you want to setup existing lua_State instead of #ZFImpl_ZFLua_luaState,
 * you must first invoke #ZFImpl_ZFLua_luaStateAttach\n
 * \n
 * \n
 * ADVANCED: how the impl works:
 * -  all attach steps can be registered by #ZFImpl_ZFLua_implSetupCallbackRegister,
 *   when #ZFImpl_ZFLua_luaStateAttach,
 *   all necessary register steps would be performed
 * -  in ZFLua, all types are wrapped by #zfautoObject
 *   (wrapped directly for ZFObject type,
 *   wrapped by #ZFPropertyTypeWrapper for non-ZFObject type)
 * -  all global variables are also wrapped by #zfautoObject
 * -  class and namespace are wrapped by lua raw string value as a global variable,
 *   and should be registered by #ZFImpl_ZFLua_implSetupScope\n
 *   these things are equal:
 *   -  `MyClass.myFunc(param);`
 *   -  `zfl_callStatic("MyClass::myFunc", param);`
 *   -  `var cls = MyClass; cls.myFunc(param);`
 * -  member functions are dispatched as `obj:myFunc(param)`,
 *   which equals to `obj.myFunc(obj, param)`
 * -  the method dispatch can be modified by registering #ZFImpl_ZFLua_implDispatchRegister,
 *   if registered, zfl_call and zfl_callStatic would first check #ZFImpl_ZFLua_implDispatch
 * -  all #zfautoObject must be registered by #ZFImpl_ZFLua_implSetupObject,
 *   and all methods would be dispatched internally,
 *   you should not modify #zfautoObject's "__index" by other lua bind tools
 */
#define ZFImpl_ZFLua_luaState _ZFP_ZFImpl_ZFLua_luaState()

/**
 * @brief see #ZFImpl_ZFLua_luaState
 *
 * must not be attached more than one time
 */
extern ZF_ENV_EXPORT void ZFImpl_ZFLua_luaStateAttach(ZF_IN lua_State *L);
/**
 * @brief see #ZFImpl_ZFLua_luaStateAttach
 *
 * note, this method only detach L from ZFFramework,
 * all methods registered to L can not be undo
 */
extern ZF_ENV_EXPORT void ZFImpl_ZFLua_luaStateDetach(ZF_IN lua_State *L);
/**
 * @brief return all lua_State that currently registered, for impl or debug use only
 */
extern ZF_ENV_EXPORT const ZFCoreArrayPOD<lua_State *> &ZFImpl_ZFLua_luaStateAttached(void);

// ============================================================
/** @brief see #ZFImpl_ZFLua_implSetupCallbackRegister */
typedef void (*ZFImpl_ZFLua_ImplSetupCallback)(ZF_IN_OUT lua_State *L);
/**
 * @brief for impl to register custom setup callback
 *
 * must be registered as #ZFLevelZFFrameworkLow,
 * using #ZFImpl_ZFLua_implSetupCallback_DEFINE to register is recommended
 */
extern ZF_ENV_EXPORT void ZFImpl_ZFLua_implSetupCallbackRegister(ZF_IN ZFImpl_ZFLua_ImplSetupCallback setupAttachCallback,
                                                                 ZF_IN ZFImpl_ZFLua_ImplSetupCallback setupDetachCallback);
/** @brief see #ZFImpl_ZFLua_implSetupCallbackRegister */
extern ZF_ENV_EXPORT void ZFImpl_ZFLua_implSetupCallbackUnregister(ZF_IN ZFImpl_ZFLua_ImplSetupCallback setupAttachCallback,
                                                                   ZF_IN ZFImpl_ZFLua_ImplSetupCallback setupDetachCallback);

/**
 * @brief util macro to #ZFImpl_ZFLua_implSetupCallbackRegister
 *
 * usage:
 * @code
 *   ZFImpl_ZFLua_implSetupCallback_DEFINE(YourSetupSig, {
 *           // your own attach action, callback proto type:
 *           //   zfbool implSetupAttach(ZF_IN_OUT lua_State *L);
 *       }, {
 *           // your own detach action, callback proto type:
 *           //   zfbool implSetupDetach(ZF_IN_OUT lua_State *L);
 *       })
 * @endcode
 */
#define ZFImpl_ZFLua_implSetupCallback_DEFINE(SetupSig, setupAttachAction, setupDetachAction) \
    ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFImpl_ZFLua_implSetupAction_##SetupSig, ZFLevelZFFrameworkLow) \
    { \
        ZFImpl_ZFLua_implSetupCallbackRegister(zfself::implSetupAttach, zfself::implSetupDetach); \
    } \
    ZF_GLOBAL_INITIALIZER_DESTROY(ZFImpl_ZFLua_implSetupAction_##SetupSig) \
    { \
        ZFImpl_ZFLua_implSetupCallbackUnregister(zfself::implSetupAttach, zfself::implSetupDetach); \
    } \
    public: \
        static void implSetupAttach(ZF_IN_OUT lua_State *L) \
        { \
            setupAttachAction \
        } \
        static void implSetupDetach(ZF_IN_OUT lua_State *L) \
        { \
            setupDetachAction \
        } \
    ZF_GLOBAL_INITIALIZER_END(ZFImpl_ZFLua_implSetupAction_##SetupSig)

// ============================================================
/** @brief see #ZFImpl_ZFLua_luaState */
extern ZF_ENV_EXPORT void ZFImpl_ZFLua_implSetupScope(ZF_IN_OUT lua_State *L, ZF_IN const zfchar *scopeName);
/** @brief see #ZFImpl_ZFLua_luaState */
extern ZF_ENV_EXPORT void ZFImpl_ZFLua_implSetupScope(ZF_IN_OUT lua_State *L, ZF_IN const zfchar **scopeNameList);
/** @brief see #ZFImpl_ZFLua_luaState */
extern ZF_ENV_EXPORT void ZFImpl_ZFLua_implSetupObject(ZF_IN_OUT lua_State *L, ZF_IN_OPT zfint objIndex = -1);

// ============================================================
/**
 * @brief used to hold unknown lua param as string
 */
zfclass ZF_ENV_EXPORT ZFImpl_ZFLua_UnknownParamHolder : zfextends ZFObject
{
    ZFOBJECT_DECLARE(ZFImpl_ZFLua_UnknownParamHolder, ZFObject)

public:
    /** @brief the value */
    zfstring zfv;
};

// ============================================================
/** @brief see #ZFImpl_ZFLua_implDispatchRegister */
typedef enum {
    ZFImpl_ZFLua_ImplDispatchResultForward, /**< @brief not dispatched, function should be further dispatched */
    ZFImpl_ZFLua_ImplDispatchResultSuccess, /**< @brief successfully dispatched, function call end */
    ZFImpl_ZFLua_ImplDispatchResultError, /**< @brief error occurred, #ZFImpl_ZFLua_ImplDispatchInfo::errorHint should be set */
} ZFImpl_ZFLua_ImplDispatchResult;

extern ZF_ENV_EXPORT const zfautoObject &_ZFP_ZFImpl_ZFLua_implDispatchReturnValueNotSet(void);
/**
 * @brief dummy object to indicate whether the dispatch has return value, see #ZFImpl_ZFLua_implDispatchRegister
 */
#define ZFImpl_ZFLua_implDispatchReturnValueNotSet _ZFP_ZFImpl_ZFLua_implDispatchReturnValueNotSet()

/** @brief see #ZFImpl_ZFLua_implDispatchRegister */
zfclassLikePOD ZF_ENV_EXPORT ZFImpl_ZFLua_ImplDispatchInfo
{
public:
    lua_State *L; /**< @brief the lua state */
    zfbool isStatic; /**< @brief whether the method called as static method */
    const zfchar *classOrNamespace; /**< @brief class or namespace text */
    const ZFClass *classOrNull; /**< @brief class if able to find */
    ZFObject *objectOrNull; /**< @brief null for static method or non-null for instance method */
    const zfchar *methodName; /**< @brief method name */
    const zfautoObject *paramList; /**< @brief param list */
    zfindex paramCount; /**< @brief param count */
    zfautoObject returnValue; /**< @brief #ZFImpl_ZFLua_implDispatchReturnValueNotSet if no return value, see #returnValueCustom */
    int returnValueCustom; /**< @brief -1 by default, set non-negative to show custom return value specified, see #returnValue */
    zfstring errorHint; /**< @brief optional error hint to append */
    ZFImpl_ZFLua_ImplDispatchResult dispatchResult; /**< @brief dispatch result */
public:
    /** @brief main constructor */
    explicit ZFImpl_ZFLua_ImplDispatchInfo(ZF_IN_OUT lua_State *L,
                                           ZF_IN zfbool isStatic,
                                           ZF_IN const zfchar *classOrNamespace,
                                           ZF_IN const ZFClass *classOrNull,
                                           ZF_IN ZFObject *objectOrNull,
                                           ZF_IN const zfchar *methodName,
                                           ZF_IN const zfautoObject *paramList,
                                           ZF_IN zfindex paramCount)
    : L(L)
    , isStatic(isStatic)
    , classOrNamespace(classOrNamespace)
    , classOrNull(classOrNull)
    , objectOrNull(objectOrNull)
    , methodName(methodName)
    , paramList(paramList)
    , paramCount(paramCount)
    , returnValue(ZFImpl_ZFLua_implDispatchReturnValueNotSet)
    , returnValueCustom(-1)
    , errorHint()
    , dispatchResult(ZFImpl_ZFLua_ImplDispatchResultForward)
    {
    }
public:
    void dispatchForward(void)
    {
        this->dispatchResult = ZFImpl_ZFLua_ImplDispatchResultForward;
    }
    void dispatchSuccess(void)
    {
        this->dispatchResult = ZFImpl_ZFLua_ImplDispatchResultSuccess;
    }
    void dispatchError(ZF_IN const zfchar *fmt, ...)
    {
        va_list vaList;
        va_start(vaList, fmt);
        zfstringAppendV(this->errorHint, fmt, vaList);
        va_end(vaList);

        this->dispatchResult = ZFImpl_ZFLua_ImplDispatchResultError;
    }
};

/** @brief see #ZFImpl_ZFLua_implDispatchRegister */
typedef void (*ZFImpl_ZFLua_ImplDispatchCallback)(ZF_IN_OUT ZFImpl_ZFLua_ImplDispatchInfo &dispatchInfo);

/**
 * @brief see #ZFImpl_ZFLua_implDispatchRegister
 */
#define ZFImpl_ZFLua_implDispatchAll zfText("-")

/**
 * @brief register custom method dispatch callback
 *
 * using #ZFImpl_ZFLua_implDispatch_DEFINE to register is recommended\n
 * \n
 * by default, all method would be dispatched by #ZFMethod reflection for #ZFObject type\n
 * for non-ZFObject type, you may want to register custom dispatch callback
 * to implement `obj:myFunc()` or `MyClass.myStaticFunc()`\n
 * to achieve this, the object or namespace must first be registered by
 * #ZFImpl_ZFLua_implSetupObject or #ZFImpl_ZFLua_implSetupScope,
 * then register the callback by this method\n
 * \n
 * params:
 * -  classOrNamespace : null or empty or #ZFMethodFuncNamespaceGlobal for global scope function,
 *   otherwise, should be the class name or namespace
 *   registered by #ZFImpl_ZFLua_implSetupScope
 * -  methodName : the method name
 *
 * there are different methods to register the dispatch callback:
 * -  methodName is null
 *   -  classOrNamespace is #ZFImpl_ZFLua_implDispatchAll : all method would be dispatch to this
 *   -  classOrNamespace is not #ZFImpl_ZFLua_implDispatchAll : all method with the specified scope name would be dispatched
 * -  methodName is not null
 *   -  classOrNamespace is #ZFImpl_ZFLua_implDispatchAll : dispatch specified methodName to all class
 *   -  classOrNamespace is not #ZFImpl_ZFLua_implDispatchAll : exactly dispatch (note that there may be overloaded methods)
 *
 * \n
 * the dispatch callback:\n
 * return false if not dispatched, and should be further dispatch by default #ZFMethod reflection,
 * return true if successfully processed
 */
extern ZF_ENV_EXPORT void ZFImpl_ZFLua_implDispatchRegister(ZF_IN ZFImpl_ZFLua_ImplDispatchCallback invokerCallback,
                                                            ZF_IN_OPT const zfchar *classOrNamespace = zfnull,
                                                            ZF_IN_OPT const zfchar *methodName = zfnull);
/** @brief see #ZFImpl_ZFLua_implDispatchRegister */
extern ZF_ENV_EXPORT void ZFImpl_ZFLua_implDispatchUnregister(ZF_IN ZFImpl_ZFLua_ImplDispatchCallback invokerCallback,
                                                              ZF_IN_OPT const zfchar *classOrNamespace = zfnull,
                                                              ZF_IN_OPT const zfchar *methodName = zfnull);
/** @brief see #ZFImpl_ZFLua_implDispatchRegister */
extern ZF_ENV_EXPORT void ZFImpl_ZFLua_implDispatch(ZF_IN_OUT ZFImpl_ZFLua_ImplDispatchInfo &dispatchInfo);

/**
 * @brief util macro to define #ZFImpl_ZFLua_implDispatchRegister
 *
 * usage:
 * @code
 *   ZFImpl_ZFLua_implDispatch_DEFINE(YourRegisterSig, yourClassOrNamespace, yourMethodName, {
 *           // dispatch by your own logic, callback proto type:
 *           //   void implDispatch(ZF_IN_OUT ZFImpl_ZFLua_ImplDispatchInfo &dispatchInfo);
 *           if(someErrorCond)
 *           {
 *               return dispatchInfo.dispatchError(yourErrorHint);
 *           }
 *           if(someCond)
 *           {
 *               dispatchInfo.returnValue = yourRet; // specify return value if exist
 *               return dispatchInfo.dispatchSuccess();
 *           }
 *           return dispatchInfo.dispatchForward();
 *       })
 * @endcode
 */
#define ZFImpl_ZFLua_implDispatch_DEFINE(RegisterSig, classOrNamespace_, methodName_, dispatchAction) \
    ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFImpl_ZFLua_implDispatchDefine_##RegisterSig, ZFLevelZFFrameworkLow) \
    { \
        ZFImpl_ZFLua_implDispatchRegister(zfself::implDispatch, \
            classOrNamespace_, \
            methodName_); \
    } \
    ZF_GLOBAL_INITIALIZER_DESTROY(ZFImpl_ZFLua_implDispatchDefine_##RegisterSig) \
    { \
        ZFImpl_ZFLua_implDispatchUnregister(zfself::implDispatch, \
            classOrNamespace_, \
            methodName_); \
    } \
    static void implDispatch(ZF_IN_OUT ZFImpl_ZFLua_ImplDispatchInfo &dispatchInfo) \
    { \
        dispatchAction \
    } \
    ZF_GLOBAL_INITIALIZER_END(ZFImpl_ZFLua_implDispatchDefine_##RegisterSig)
/** @brief util macro to #ZFImpl_ZFLua_implDispatch_DEFINE for short */
#define ZFImpl_ZFLua_implDispatch_DEFINE_DEFAULT(ClassSig, methodNameSig, dispatchAction) \
    ZFImpl_ZFLua_implDispatch_DEFINE( \
        ClassSig##_##methodNameSig, \
        ZFM_TOSTRING(ClassSig), \
        ZFM_TOSTRING(methodNameSig), \
        dispatchAction)

/** @brief util macro for impl */
#define ZFImpl_ZFLua_implDispatch_AssertParamCount(N) \
    do { \
        if(dispatchInfo.paramCount != N) \
        { \
            return dispatchInfo.dispatchError( \
                zfText("%s::%s expect %zi param, got %zi"), \
                dispatchInfo.classOrNamespace, dispatchInfo.methodName, \
                N, dispatchInfo.paramCount); \
        } \
    } while(zffalse)
/** @brief util macro for impl */
#define ZFImpl_ZFLua_implDispatch_AssertParamCountRange(N0, N1) \
    do { \
        if(dispatchInfo.paramCount < N0 || dispatchInfo.paramCount > N1) \
        { \
            return dispatchInfo.dispatchError( \
                zfText("%s::%s expect %zi ~ %zi param, got %zi"), \
                dispatchInfo.classOrNamespace, dispatchInfo.methodName, \
                N0, N1, dispatchInfo.paramCount); \
        } \
    } while(zffalse)
/** @brief util macro for impl */
#define ZFImpl_ZFLua_implDispatch_AssertIsStaticMethod() \
    do { \
        if(!dispatchInfo.isStatic) \
        { \
            return dispatchInfo.dispatchError( \
                zfText("%s::%s is static method, called as object instance method"), \
                dispatchInfo.classOrNamespace, dispatchInfo.methodName); \
        } \
    } while(zffalse)
/** @brief util macro for impl */
#define ZFImpl_ZFLua_implDispatch_AssertClassExist() \
    do { \
        if(dispatchInfo.classOrNull == zfnull) \
        { \
            return dispatchInfo.dispatchError( \
                zfText("%s::%s no such class"), \
                dispatchInfo.classOrNamespace, dispatchInfo.methodName); \
        } \
    } while(zffalse)
/** @brief util macro for impl */
#define ZFImpl_ZFLua_implDispatch_AccessParamAllowEmpty(N, desiredClass, paramName) \
    desiredClass *paramName = ZFCastZFObject(desiredClass *, dispatchInfo.paramList[N]->toObject()); \
    zfautoObject _ZFP_##paramName; \
    do { \
        if(paramName == zfnull && dispatchInfo.paramList[N]->toObject() != zfnull) \
        { \
            ZFImpl_ZFLua_UnknownParamHolder *t = ZFCastZFObject(ZFImpl_ZFLua_UnknownParamHolder *, dispatchInfo.paramList[N]->toObject()); \
            if(t != zfnull && desiredClass::ClassData()->classIsSubclassOf(ZFPropertyTypeWrapper::ClassData())) \
            { \
                zfblockedAllocWithoutLeakTest(desiredClass, t2); \
                if(t2->to<ZFPropertyTypeWrapper *>()->wrappedValueFromString(t->zfv)) \
                { \
                    _ZFP_##paramName = zfautoObjectCreateWithoutLeakTest(t2); \
                    paramName = t2; \
                    break; \
                } \
            } \
            return dispatchInfo.dispatchError( \
                zfText("%s::%s param type mismatch, expect %s, got %s"), \
                dispatchInfo.classOrNamespace, dispatchInfo.methodName, \
                desiredClass::ClassData()->className(), \
                ZFObjectInfo(dispatchInfo.paramList[N]->toObject()).cString()); \
        } \
    } while(zffalse)
/** @brief util macro for impl */
#define ZFImpl_ZFLua_implDispatch_AccessParam(N, desiredClass, paramName) \
    desiredClass *paramName = ZFCastZFObject(desiredClass *, dispatchInfo.paramList[N]->toObject()); \
    zfautoObject _ZFP_##paramName; \
    do { \
        if(paramName == zfnull) \
        { \
            ZFImpl_ZFLua_UnknownParamHolder *t = ZFCastZFObject(ZFImpl_ZFLua_UnknownParamHolder *, dispatchInfo.paramList[N]->toObject()); \
            if(t != zfnull && desiredClass::ClassData()->classIsSubclassOf(ZFPropertyTypeWrapper::ClassData())) \
            { \
                zfblockedAllocWithoutLeakTest(desiredClass, t2); \
                if(t2->to<ZFPropertyTypeWrapper *>()->wrappedValueFromString(t->zfv)) \
                { \
                    _ZFP_##paramName = zfautoObjectCreateWithoutLeakTest(t2); \
                    paramName = t2; \
                    break; \
                } \
            } \
            return dispatchInfo.dispatchError( \
                zfText("%s::%s param type mismatch, expect %s, got %s"), \
                dispatchInfo.classOrNamespace, dispatchInfo.methodName, \
                desiredClass::ClassData()->className(), \
                ZFObjectInfo(dispatchInfo.paramList[N]->toObject()).cString()); \
        } \
    } while(zffalse)
#define _ZFP_ZFImpl_ZFLua_implDispatch_AssertIsInstanceMethod() \
    if(dispatchInfo.isStatic) \
    { \
        return dispatchInfo.dispatchError( \
            zfText("%s::%s is object instance method, called as static method"), \
            dispatchInfo.classOrNamespace, dispatchInfo.methodName); \
    }
/** @brief util macro for impl */
#define ZFImpl_ZFLua_implDispatch_AccessOwnerObject(OwnerObjectType, WrapperType, objName) \
    _ZFP_ZFImpl_ZFLua_implDispatch_AssertIsInstanceMethod() \
    WrapperType *_ZFP_##objName = ZFCastZFObject(WrapperType *, dispatchInfo.objectOrNull); \
    if(_ZFP_##objName == zfnull) \
    { \
        return dispatchInfo.dispatchError( \
            zfText("%s::%s owner object type mismatch, expect %s, got %s"), \
            dispatchInfo.classOrNamespace, dispatchInfo.methodName, \
            WrapperType::ClassData()->className(), \
            ZFObjectInfo(dispatchInfo.objectOrNull).cString()); \
    } \
    OwnerObjectType objName = _ZFP_##objName->zfv
/** @brief util macro for impl */
#define ZFImpl_ZFLua_implDispatch_AccessOwnerZFObject(OwnerZFObjectType, objName) \
    _ZFP_ZFImpl_ZFLua_implDispatch_AssertIsInstanceMethod() \
    OwnerZFObjectType *objName = ZFCastZFObject(OwnerZFObjectType *, dispatchInfo.objectOrNull); \
    do { \
        if(objName == zfnull) \
        { \
            return dispatchInfo.dispatchError( \
                zfText("%s::%s owner object type mismatch, expect %s, got %s"), \
                dispatchInfo.classOrNamespace, dispatchInfo.methodName, \
                OwnerZFObjectType::ClassData()->className(), \
                ZFObjectInfo(dispatchInfo.objectOrNull).cString()); \
        } \
    } while(zffalse)

// ============================================================
#define ZFImpl_ZFLua_PropTypePrefix zfText("v_")
#define ZFImpl_ZFLua_PropTypePrefixLen 2

// ============================================================
/**
 * @brief run lua code, L must be first initialized by #ZFImpl_ZFLua_luaStateAttach
 */
extern ZF_ENV_EXPORT zfbool ZFImpl_ZFLua_execute(ZF_IN lua_State *L,
                                                 ZF_IN const zfchar *buf,
                                                 ZF_IN_OPT zfindex bufLen = zfindexMax(),
                                                 ZF_OUT_OPT zfstring *errHint = zfnull);

// ============================================================
// utils
/**
 * @brief get raw lua object info
 */
extern ZF_ENV_EXPORT void ZFImpl_ZFLua_luaObjectInfoT(ZF_OUT zfstring &ret,
                                                      ZF_IN lua_State *L,
                                                      ZF_IN zfint luaStackOffset,
                                                      ZF_IN_OPT zfbool printLuaType = zffalse);
/**
 * @brief get raw lua object info
 */
inline zfstring ZFImpl_ZFLua_luaObjectInfo(ZF_IN lua_State *L,
                                           ZF_IN zfint luaStackOffset,
                                           ZF_IN_OPT zfbool printLuaType = zffalse)
{
    zfstring ret;
    ZFImpl_ZFLua_luaObjectInfoT(ret, L, luaStackOffset, printLuaType);
    return ret;
}
/**
 * @brief get params from lua
 */
extern ZF_ENV_EXPORT zfbool ZFImpl_ZFLua_toObject(ZF_OUT zfautoObject &param,
                                                  ZF_IN lua_State *L,
                                                  ZF_IN zfint luaStackOffset);
/**
 * @brief for lua code to convert zfautoObject to lua's value type (string or number)
 *
 * support all type that #ZFImpl_ZFLua_toString and #ZFImpl_ZFLua_toNumber supported\n
 * support all #ZFPropertyTypeWrapper, which would serialize the internal value to string
 * and return the string value
 */
extern ZF_ENV_EXPORT zfbool ZFImpl_ZFLua_toValue(ZF_IN_OUT zfstring &s,
                                                 ZF_IN lua_State *L,
                                                 ZF_IN zfint luaStackOffset,
                                                 ZF_IN_OPT zfbool allowEmpty = zffalse);

/**
 * @brief get params from lua
 *
 * support types:
 * -  normal lua string
 * -  #ZFString
 * -  #v_zfstring
 */
extern ZF_ENV_EXPORT zfbool ZFImpl_ZFLua_toString(ZF_IN_OUT zfstring &s,
                                                  ZF_IN lua_State *L,
                                                  ZF_IN zfint luaStackOffset,
                                                  ZF_IN_OPT zfbool allowEmpty = zffalse);

/**
 * @brief get params from lua
 *
 * support types:
 * -  normal lua number
 * -  #ZFValue
 * -  #v_zfbool
 * -  #v_zfindex
 * -  #v_zfint
 * -  #v_zfuint
 * -  #v_zffloat
 * -  #v_zfdouble
 * -  #v_zflongdouble
 * -  #v_zfbyte
 * -  #v_zftimet
 * -  #v_zfflags
 * -  #v_zfidentity
 *
 * return proper #ZFValue if success, or empty if fail\n
 * if allowEmpty, a #ZFValue::intValueCreate would be returned
 */
extern ZF_ENV_EXPORT zfbool ZFImpl_ZFLua_toNumber(ZF_OUT zfautoObject &ret,
                                                  ZF_IN lua_State *L,
                                                  ZF_IN zfint luaStackOffset,
                                                  ZF_IN_OPT zfbool allowEmpty = zffalse);
/** @brief see #ZFImpl_ZFLua_toNumber */
inline zfautoObject ZFImpl_ZFLua_toNumber(ZF_IN lua_State *L,
                                          ZF_IN zfint luaStackOffset,
                                          ZF_IN_OPT zfbool allowEmpty = zffalse)
{
    zfautoObject ret;
    ZFImpl_ZFLua_toNumber(ret, L, luaStackOffset, allowEmpty);
    return ret;
}
/** @brief see #ZFImpl_ZFLua_toNumber */
extern ZF_ENV_EXPORT zfbool ZFImpl_ZFLua_toNumber(ZF_OUT lua_Number &ret,
                                                  ZF_IN lua_State *L,
                                                  ZF_IN zfint luaStackOffset,
                                                  ZF_IN_OPT zfbool allowEmpty = zffalse);

// ============================================================
// wrapper for impl
inline lua_State *ZFImpl_ZFLua_luaOpen(void)
{
    return ELuna::openLua();
}
inline void ZFImpl_ZFLua_luaClose(ZF_IN lua_State *L)
{
    ELuna::closeLua(L);
}

template<typename T>
inline void ZFImpl_ZFLua_luaClassRegister(ZF_IN lua_State *L, ZF_IN const zfchar *name)
{
    ELuna::registerClass<T>(L, zfsCoreZ2A(name), ELuna::constructor<zfautoObject>);
}
template<typename F>
inline void ZFImpl_ZFLua_luaFunctionRegister(ZF_IN lua_State *L, ZF_IN const zfchar *name, ZF_IN F f)
{
    ELuna::registerFunction(L, zfsCoreZ2A(name), f);
}
inline void ZFImpl_ZFLua_luaCFunctionRegister(ZF_IN lua_State *L, ZF_IN const zfchar *name, ZF_IN int (*f)(lua_State *))
{
    lua_register(L, zfsCoreZ2A(name), f);
}

inline void ZFImpl_ZFLua_luaPush(ZF_IN lua_State *L, ZF_IN zfautoObject &v)
{
    ELuna::convert2LuaType<zfautoObject>::convertType(L, v);
}
inline void ZFImpl_ZFLua_luaPush(ZF_IN lua_State *L, ZF_IN const zfautoObject &v)
{
    zfautoObject t = v;
    ELuna::convert2LuaType<zfautoObject>::convertType(L, t);
}
inline const zfautoObject &ZFImpl_ZFLua_luaGet(ZF_IN lua_State *L, ZF_IN zfint luaStackOffset)
{
    return ELuna::convert2CppType<zfautoObject const &>::convertType(L, luaStackOffset);
}

ZF_NAMESPACE_GLOBAL_END

#endif // #ifndef _ZFI_ZFImpl_ZFLua_h_

