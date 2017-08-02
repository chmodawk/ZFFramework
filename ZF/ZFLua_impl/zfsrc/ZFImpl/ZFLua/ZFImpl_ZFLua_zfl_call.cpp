/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFImpl_ZFLua.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
static void _ZFP_ZFImpl_ZFLua_zfl_callStatic_methodScopeFix(ZF_IN_OUT zfstring &methodScope)
{
    if(methodScope.compare(zfText(ZFLuaFuncNamespaceGlobal)) == 0
        || methodScope.compare(ZFMethodFuncNamespaceGlobal) == 0)
    {
        methodScope.removeAll();
    }
}
static int _ZFP_ZFImpl_ZFLua_zfl_call_invoker(ZF_IN lua_State *L,
                                              ZF_IN const zfautoObject *paramList,
                                              ZF_IN zfindex paramCount,
                                              ZF_IN const ZFCoreArrayPOD<const ZFMethod *> &methodList,
                                              ZF_IN ZFObject *obj)
{
    zfstring errorHint;
    zfautoObject ret;
    zfautoObject paramListTmp[ZFMETHOD_MAX_PARAM] = {
              paramList[0]
            , paramList[1]
            , paramList[2]
            , paramList[3]
            , paramList[4]
            , paramList[5]
            , paramList[6]
            , paramList[7]
        };
    for(zfindex iMethod = 0; iMethod < methodList.count(); ++iMethod)
    {
        const ZFMethod *method = methodList[iMethod];
        if(method->methodPrivilegeType() != ZFMethodPrivilegeTypePublic
            || paramCount > method->methodParamCount())
        {
            continue;
        }

        errorHint.removeAll();

        /* ZFMETHOD_MAX_PARAM */
        zfbool parseParamSuccess = zftrue;
        for(zfindex i = 0; i < paramCount; ++i)
        {
            ZFImpl_ZFLua_UnknownParamHolder *t = ZFCastZFObject(ZFImpl_ZFLua_UnknownParamHolder *, paramList[i].toObject());
            if(t != zfnull)
            {
                const ZFPropertyTypeIdDataBase *typeIdData = ZFPropertyTypeIdDataGet(method->methodParamTypeIdAtIndex(i));
                if(typeIdData == zfnull)
                {
                    zfstringAppend(errorHint, zfText("param %zi (%s) can not be converted from string automatically"),
                            i,
                            method->methodParamTypeIdAtIndex(i)
                        );
                    parseParamSuccess = zffalse;
                    break;
                }
                if(!typeIdData->propertyWrapperFromString(paramListTmp[i], t->zfv, t->zfv.length()))
                {
                    zfstringAppend(errorHint, zfText("param %zi (%s) can not be converted from string \"%s\""),
                            i,
                            method->methodParamTypeIdAtIndex(i),
                            t->zfv.cString()
                        );
                    parseParamSuccess = zffalse;
                    break;
                }
            }
        }
        if(!parseParamSuccess)
        {
            continue;
        }

        ret = zfautoObjectNull;
        if(method->methodGenericInvoker()(method, obj, &errorHint, ret
                , paramListTmp[0]
                , paramListTmp[1]
                , paramListTmp[2]
                , paramListTmp[3]
                , paramListTmp[4]
                , paramListTmp[5]
                , paramListTmp[6]
                , paramListTmp[7]
            ))
        {
            ZFImpl_ZFLua_luaPush(L, ret);
            ZFImpl_ZFLua_implSetupObject(L);
            return 1;
        }
    }

    if(methodList.count() == 1)
    {
        zfstring err;
        zfstringAppend(err,
            zfText("[zfl_call] failed to perform generic invoke for method: %s, obj: \"%s\", params: "),
            methodList[0]->objectInfo().cString(),
            ZFObjectInfo(obj).cString()
            );
        err += zfText("[");
        for(zfindex i = 0; i < paramCount; ++i)
        {
            if(i != 0)
            {
                err += zfText(", ");
            }
            err += ZFObjectInfo(paramList[i].toObject());
        }
        err += zfText("]");
        err += zfText(", reason: ");
        err += errorHint;
        ZFLuaErrorOccurredTrim(zfText("%s"), err.cString());
    }
    else
    {
        zfstring err;
        zfstringAppend(err,
            zfText("[zfl_call] no matching method to call, obj: \"%s\", params: "),
            ZFObjectInfo(obj).cString()
            );
        err += zfText("[");
        for(zfindex i = 0; i < paramCount; ++i)
        {
            if(i != 0)
            {
                err += zfText(", ");
            }
            err += ZFObjectInfo(paramList[i].toObject());
        }
        err += zfText("]");
        err += zfText(", last error reason: ");
        err += errorHint;

        err += zfText(", candidate methods:");
        for(zfindex i = 0; i < methodList.count(); ++i)
        {
            err += zfText("\n    ");
            methodList[i]->objectInfoT(err);
        }

        ZFLuaErrorOccurredTrim(zfText("%s"), err.cString());
    }
    return luaL_error(L, "");
}

#define _ZFP_ZFImpl_ZFLua_zfl_call_implDispatch( \
        isStatic, classOrNamespace, classOrNull, objectOrNull, \
        methodName \
    ) \
    ZFImpl_ZFLua_ImplDispatchInfo dispatchInfo( \
            L, \
            isStatic, classOrNamespace, classOrNull, objectOrNull, \
            methodName, \
            paramList, paramCount \
        ); \
    ZFImpl_ZFLua_implDispatch(dispatchInfo); \
    switch(dispatchInfo.dispatchResult) \
    { \
        case ZFImpl_ZFLua_ImplDispatchResultSuccess: \
            if(dispatchInfo.returnValueCustom != -1) \
            { \
                return dispatchInfo.returnValueCustom; \
            } \
            else \
            { \
                if(dispatchInfo.returnValue != ZFImpl_ZFLua_implDispatchReturnValueNotSet) \
                { \
                    ZFImpl_ZFLua_luaPush(L, dispatchInfo.returnValue); \
                    ZFImpl_ZFLua_implSetupObject(L); \
                    return 1; \
                } \
                else \
                { \
                    return 0; \
                } \
            } \
        case ZFImpl_ZFLua_ImplDispatchResultError: \
            ZFLuaErrorOccurredTrim(zfText("[ImplDispatch] %s"), dispatchInfo.errorHint.cString()); \
            return luaL_error(L, ""); \
        case ZFImpl_ZFLua_ImplDispatchResultForward: \
        default: \
            break; \
    }

/*
 * zfl_call(obj, "classInstanceMethodName", param0, param1, ...)
 */
static int _ZFP_ZFImpl_ZFLua_zfl_call(ZF_IN lua_State *L)
{
    static const zfint luaParamOffset = 2;
    zfint count = (zfint)lua_gettop(L);
    if(count < luaParamOffset || count > ZFMETHOD_MAX_PARAM + luaParamOffset)
    {
        ZFLuaErrorOccurredTrim(
            zfText("[zfl_call] invalid param, expect zfl_call(obj, \"methodName\", param0, param1, ...), got %zi param"),
            (zfindex)count);
        return luaL_error(L, "");
    }
    zfint paramCount = count - luaParamOffset;

    zfautoObject obj;
    if(!ZFImpl_ZFLua_toObject(obj, L, 1))
    {
        ZFLuaErrorOccurredTrim(zfText("[zfl_call] failed to access caller object, expect zfautoObject, got %s"),
            ZFImpl_ZFLua_luaObjectInfo(L, 1).cString());
        return luaL_error(L, "");
    }

    zfautoObject paramList[ZFMETHOD_MAX_PARAM] = {
              ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
        };
    for(zfint i = 0; i < paramCount; ++i)
    {
        if(!ZFImpl_ZFLua_toObject(paramList[i], L, luaParamOffset + i + 1))
        {
            zfblockedAllocWithoutLeakTest(ZFImpl_ZFLua_UnknownParamHolder, t);
            if(!ZFImpl_ZFLua_toString(t->zfv, L, luaParamOffset + i + 1))
            {
                ZFLuaErrorOccurredTrim(zfText("[zfl_call] failed to get param%d, expect zfautoObject, got %s"),
                    i,
                    ZFImpl_ZFLua_luaObjectInfo(L, luaParamOffset + i + 1).cString());
                return luaL_error(L, "");
            }
            paramList[i] = zfautoObjectCreateWithoutLeakTest(t);
        }
    }

    ZFCoreArrayPOD<const ZFMethod *> methodList;
    do
    {
        zfautoObject methodHolder;
        if(ZFImpl_ZFLua_toObject(methodHolder, L, 2))
        {
            v_ZFMethod *methodWrapper = ZFCastZFObject(v_ZFMethod *, methodHolder);
            if(methodWrapper != zfnull)
            {
                if(methodWrapper->zfv == zfnull)
                {
                    ZFLuaErrorOccurredTrim(zfText("[zfl_call] null method"));
                    return luaL_error(L, "");
                }
                methodList.add(methodWrapper->zfv);
                break;
            }
        }

        zfstring methodSig;
        if(!ZFImpl_ZFLua_toString(methodSig, L, 2))
        {
            ZFLuaErrorOccurredTrim(zfText("[zfl_call] failed to access function name, expect string type, got %s"),
                ZFImpl_ZFLua_luaObjectInfo(L, 2).cString());
            return luaL_error(L, "");
        }
        if(methodSig.isEmpty())
        {
            ZFLuaErrorOccurredTrim(zfText("[zfl_call] method sig must not be null"));
            return luaL_error(L, "");
        }

        _ZFP_ZFImpl_ZFLua_zfl_call_implDispatch(
            zffalse, obj->classData()->className(), obj->classData(), obj,
            methodSig)

        obj.toObject()->classData()->methodForNameGetAllT(methodList, methodSig);

        if(methodList.isEmpty())
        {
            ZFLuaErrorOccurredTrim(
                zfText("[zfl_call] no such method \"%s\" in class \"%s\""),
                methodSig.cString(),
                obj.toObject()->classData()->className());
            return luaL_error(L, "");
        }
    } while(zffalse);

    if(obj.toObject() == zfnull)
    {
        ZFLuaErrorOccurredTrim(zfText("[zfl_call] caller object must not be null"));
        return luaL_error(L, "");
    }

    return _ZFP_ZFImpl_ZFLua_zfl_call_invoker(L, paramList, paramCount, methodList, obj);
}

/*
 * zfl_callStatic("[Scope]::classInstanceMethodName", param0, param1, ...)
 */
static int _ZFP_ZFImpl_ZFLua_zfl_callStatic(ZF_IN lua_State *L)
{
    static const zfint luaParamOffset = 1;
    zfint count = (zfint)lua_gettop(L);
    if(count < luaParamOffset || count > ZFMETHOD_MAX_PARAM + luaParamOffset)
    {
        ZFLuaErrorOccurredTrim(
            zfText("[zfl_callStatic] invalid param, expect zfl_callStatic(\"Scope::methodName\", param0, param1, ...), got %zi param"),
            (zfindex)count);
        return luaL_error(L, "");
    }
    zfint paramCount = count - luaParamOffset;

    zfautoObject paramList[ZFMETHOD_MAX_PARAM] = {
              ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
        };
    for(zfint i = 0; i < paramCount; ++i)
    {
        if(!ZFImpl_ZFLua_toObject(paramList[i], L, luaParamOffset + i + 1))
        {
            zfblockedAllocWithoutLeakTest(ZFImpl_ZFLua_UnknownParamHolder, t);
            if(!ZFImpl_ZFLua_toString(t->zfv, L, luaParamOffset + i + 1))
            {
                ZFLuaErrorOccurredTrim(zfText("[zfl_callStatic] failed to get param%d, expect zfautoObject, got %s"),
                    i,
                    ZFImpl_ZFLua_luaObjectInfo(L, luaParamOffset + i + 1).cString());
                return luaL_error(L, "");
            }
            paramList[i] = zfautoObjectCreateWithoutLeakTest(t);
        }
    }

    ZFCoreArrayPOD<const ZFMethod *> methodList;
    do
    {
        zfautoObject methodHolder;
        if(ZFImpl_ZFLua_toObject(methodHolder, L, 1))
        {
            v_ZFMethod *methodWrapper = ZFCastZFObject(v_ZFMethod *, methodHolder);
            if(methodWrapper != zfnull)
            {
                if(methodWrapper->zfv == zfnull)
                {
                    ZFLuaErrorOccurredTrim(zfText("[zfl_callStatic] null method"));
                    return luaL_error(L, "");
                }
                methodList.add(methodWrapper->zfv);
                break;
            }
        }

        zfstring methodSig;
        if(!ZFImpl_ZFLua_toString(methodSig, L, 1))
        {
            ZFLuaErrorOccurredTrim(zfText("[zfl_callStatic] failed to access function name, expect string type, got %s"),
                ZFImpl_ZFLua_luaObjectInfo(L, 1).cString());
            return luaL_error(L, "");
        }

        ZFCoreArrayPOD<zfindexRange> methodSigPos;
        if(!ZFMethodSigSplit(methodSigPos, methodSig.cString(), methodSig.length()))
        {
            ZFLuaErrorOccurredTrim(
                zfText("[zfl_callStatic] failed to parse method sig \"%s\""),
                methodSig.cString());
            return luaL_error(L, "");
        }

        zfstring methodScope(methodSig.cString() + methodSigPos[0].start, methodSigPos[0].count);
        _ZFP_ZFImpl_ZFLua_zfl_callStatic_methodScopeFix(methodScope);
        zfstring methodName(methodSig.cString() + methodSigPos[1].start, methodSigPos[1].count);
        const ZFClass *cls = ZFClass::classForName(methodScope);

        _ZFP_ZFImpl_ZFLua_zfl_call_implDispatch(
            zftrue, methodScope, cls, zfnull,
            methodName)

        if(cls != zfnull)
        {
            cls->methodForNameGetAllT(methodList, methodName);
        }
        else
        {
            ZFMethodFuncGetAllT(methodList, methodScope, methodName);
        }

        if(methodList.isEmpty())
        {
            ZFLuaErrorOccurredTrim(
                zfText("[zfl_callStatic] no such method \"%s\""),
                methodSig.cString());
            return luaL_error(L, "");
        }
    } while(zffalse);

    return _ZFP_ZFImpl_ZFLua_zfl_call_invoker(L, paramList, paramCount, methodList, zfnull);
}

/*
 * zfl_callStatic2("Scope", "methodName", param0, param1, ...)
 */
static int _ZFP_ZFImpl_ZFLua_zfl_callStatic2(ZF_IN lua_State *L)
{
    static zfint luaParamOffset = 2;
    zfint count = (zfint)lua_gettop(L);
    if(count < luaParamOffset || count > ZFMETHOD_MAX_PARAM + luaParamOffset)
    {
        ZFLuaErrorOccurredTrim(
            zfText("[zfl_callStatic2] invalid param, expect zfl_callStatic2(\"Scope\", \"methodName\", param0, param1, ...), got %zi param"),
            (zfindex)count);
        return luaL_error(L, "");
    }
    zfint paramCount = count - luaParamOffset;

    zfautoObject paramList[ZFMETHOD_MAX_PARAM] = {
              ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
            , ZFMethodGenericInvokerDefaultParamHolder
        };
    for(zfint i = 0; i < paramCount; ++i)
    {
        if(!ZFImpl_ZFLua_toObject(paramList[i], L, luaParamOffset + i + 1))
        {
            zfblockedAllocWithoutLeakTest(ZFImpl_ZFLua_UnknownParamHolder, t);
            if(!ZFImpl_ZFLua_toString(t->zfv, L, luaParamOffset + i + 1))
            {
                ZFLuaErrorOccurredTrim(zfText("[zfl_callStatic2] failed to get param%d, expect zfautoObject, got %s"),
                    i,
                    ZFImpl_ZFLua_luaObjectInfo(L, luaParamOffset + i + 1).cString());
                return luaL_error(L, "");
            }
            paramList[i] = zfautoObjectCreateWithoutLeakTest(t);
        }
    }

    ZFCoreArrayPOD<const ZFMethod *> methodList;
    do
    {
        zfstring methodScope;
        if(!ZFImpl_ZFLua_toString(methodScope, L, 1))
        {
            ZFLuaErrorOccurredTrim(zfText("[zfl_callStatic2] failed to access method scope, expect string type, got %s"),
                ZFImpl_ZFLua_luaObjectInfo(L, 1).cString());
            return luaL_error(L, "");
        }
        _ZFP_ZFImpl_ZFLua_zfl_callStatic_methodScopeFix(methodScope);

        zfstring methodName;
        if(!ZFImpl_ZFLua_toString(methodName, L, 2))
        {
            ZFLuaErrorOccurredTrim(zfText("[zfl_callStatic2] failed to access method name, expect string type, got %s"),
                ZFImpl_ZFLua_luaObjectInfo(L, 2).cString());
            return luaL_error(L, "");
        }

        const ZFClass *cls = ZFClass::classForName(methodScope);

        _ZFP_ZFImpl_ZFLua_zfl_call_implDispatch(
            zftrue, methodScope, cls, zfnull,
            methodName)

        if(cls != zfnull)
        {
            cls->methodForNameGetAllT(methodList, methodName);
        }
        else
        {
            ZFMethodFuncGetAllT(methodList, methodScope, methodName);
        }

        if(methodList.isEmpty())
        {
            ZFLuaErrorOccurredTrim(
                zfText("[zfl_callStatic2] no such method \"%s.%s\""),
                methodScope.cString(),
                methodName.cString());
            return luaL_error(L, "");
        }
    } while(zffalse);

    return _ZFP_ZFImpl_ZFLua_zfl_call_invoker(L, paramList, paramCount, methodList, zfnull);
}

// ============================================================
ZFImpl_ZFLua_implSetupCallback_DEFINE(zfl_call, {
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("zfl_call"), _ZFP_ZFImpl_ZFLua_zfl_call);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("zfl_callStatic"), _ZFP_ZFImpl_ZFLua_zfl_callStatic);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("zfl_callStatic2"), _ZFP_ZFImpl_ZFLua_zfl_callStatic2);
    }, {
    })

ZF_NAMESPACE_GLOBAL_END

