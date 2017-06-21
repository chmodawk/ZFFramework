/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFLuaExecute.h
 * @brief execute lua script
 */

#ifndef _ZFI_ZFLuaExecute_h_
#define _ZFI_ZFLuaExecute_h_

#include "ZFLuaDef.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief main entry for lua module, execute lua code
 *
 * thanks to powerful reflection mechanism in ZFFramework,
 * most of components are registered to lua by reflection automatically\n
 * \n
 * all types of ZFFramework are wrapped as #zfautoObject in lua world,
 * including: #ZFObject types (wrapped directly)
 * and non-ZFObject normal C++ types (wrapped by #ZFPropertyTypeWrapper)\n
 * then, all reflectable #ZFMethod supply #ZFMethodGenericInvoker
 * to invoke the method without knowing all actual types\n
 * \n
 * here is a list of functions available in lua to communicate with ZFFramework:
 * -  `zfAlloc("ClassName")`
 *   or `ClassName.zfAlloc()`\n
 *   alloc a ZFObject type (no extra init param supported)\n
 *   "ClassName" can be #v_ZFClass, or converted by #ZFImpl_ZFLua_toString
 * -  invoker
 *   -  `ret = zfl_call(obj, "functionName", param0, param1, ...)`
 *     or `obj:functionName(param0, param1, ...)`\n
 *     call object's instance method, params are optional\n
 *     for "functionName", see #ZFPropertyTypeId_ZFMethod\n
 *     "functionName" can be #v_ZFMethod, or converted by #ZFImpl_ZFLua_toString,
 *     while other types must exactly match the original types
 *   -  `ret = zfl_callStatic("::methodName", param0, param1, ...)`
 *     or `ret = zfl_callStatic("ClassOrNamespace::methodName", param0, param1, ...)`
 *     or `ret = zfl_callStatic2("ClassOrNamespace", "methodName", param0, param1, ...)`
 *     or `ret = ClassOrNamespace.methodName(param0, param1, ...)`\n
 *     call global function or static class member method, params are optional\n
 *     for "functionName", see #ZFPropertyTypeId_ZFMethod\n
 *     "functionName" can be #v_ZFMethod, or converted by #ZFImpl_ZFLua_toString,
 *     while other types must exactly match the original types\n
 *     these namespace are considered as the same:
 *     -  #ZFMethodFuncNamespaceGlobal
 *     -  #ZFLuaGlobalFuncNamespace
 *     -  empty string
 * -  value holder
 *   -  `value = v_YourTypeName("yourTypeData")`
 *     or `value = v_YourTypeName()`\n
 *     create a non-ZFObject type registered by #ZFPROPERTY_TYPE_DECLARE,
 *     return the associated `v_YourTypeName` that holds the value\n
 *     "YourTypeName" represents the type name in #ZFPROPERTY_TYPE_DECLARE\n
 *     "yourTypeData" store string datas that would be decoded by YourTypeNameFromString\n
 *     "yourTypeData" are converted by #ZFImpl_ZFLua_toString
 *   -  `value:yourFunc()`
 *     or `v_YourTypeName.YourFunc()`\n
 *     for non-ZFObject types that wrapped by #ZFPROPERTY_TYPE_DECLARE,
 *     you may use #ZFMETHOD_USER_REGISTER_0 series to register methods
 *     to its wrapper type `v_YourTypeName`,
 *     then the methods can be invoked directly to your value type
 * -  value converter
 *   -  `zfl_toValue(v)`\n
 *     convert a value to lua's normal value, by #ZFImpl_ZFLua_toValue
 *   -  `zfl_toString(v)`\n
 *     convert a value to lua's normal string, by #ZFImpl_ZFLua_toString
 *   -  `zfl_toNumber(v)`\n
 *     convert a value to lua's normal number, by #ZFImpl_ZFLua_toNumber
 * -  callback
 *   -  `ZFCallbackForLua(luaFunc)`\n
 *     create a #ZFListener from lua function\n
 *     the lua function's proto type must be:
 *     @code
 *       function myLuaCallback(listenerData, userData)
 *       endfunction
 *     @endcode
 * -  debug helper
 *   -  `zfLog(fmt, ...)`\n
 *     same as #zfLogTrim, fmt would be converted by #ZFImpl_ZFLua_toString,
 *     while only "%s" supported\n
 *     following va_args support:
 *     -  #ZFObject, would be converted by #ZFObject::objectInfo
 *     -  lua string type, converted by #ZFImpl_ZFLua_toString
 *     -  any lua type, converted by #ZFImpl_ZFLua_luaObjectInfo
 *   -  `zfl_tableInfo(v)`
 *     or `zfl_tableInfoPrint`\n
 *     return string that represents the table
 *
 *
 * note:
 * -  all types would be registered automatically,
 * -  for dynamically loaded library, all types would also be registered normally,
 *   however, won't be automatically unregistered when unloaded
 */
extern ZF_ENV_EXPORT zfbool ZFLuaExecute(ZF_IN const ZFInputCallback &input);
/** @brief see #ZFLuaExecute */
extern ZF_ENV_EXPORT zfbool ZFLuaExecute(ZF_IN const zfchar *buf,
                                         ZF_IN_OPT zfindex bufLen = zfindexMax);

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFLuaExecute_h_

