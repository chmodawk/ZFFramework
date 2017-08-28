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

static int _ZFP_ZFImpl_ZFLua_zfAlloc(ZF_IN lua_State *L)
{
    zfint count = (zfint)lua_gettop(L);
    if(count != 1)
    {
        ZFLuaErrorOccurredTrim(
            zfText("[zfAlloc] takes only one param, got %zi"),
            (zfindex)count);
        return luaL_error(L, "");
    }

    {
        zfautoObject clsHolder;
        if(ZFImpl_ZFLua_toObject(clsHolder, L, 1))
        {
            v_ZFClass *clsWrapper = ZFCastZFObject(v_ZFClass *, clsHolder);
            if(clsWrapper != zfnull)
            {
                if(clsWrapper->zfv == zfnull)
                {
                    ZFImpl_ZFLua_luaPush(L, zfautoObjectNull);
                    ZFImpl_ZFLua_implSetupObject(L);
                    return 1;
                }
                ZFImpl_ZFLua_luaPush(L, clsWrapper->zfv->newInstance());
                ZFImpl_ZFLua_implSetupObject(L);
                return 1;
            }
        }
    }

    zfstring className;
    if(!ZFImpl_ZFLua_toString(className, L, 1))
    {
        ZFLuaErrorOccurredTrim(zfText("[zfAlloc] unknown param type: %s"),
            ZFImpl_ZFLua_luaObjectInfo(L, 1).cString());
        return luaL_error(L, "");
    }

    const ZFClass *cls = ZFClass::classForName(className);
    if(cls == zfnull)
    {
        zfstring classNameTmp = ZFImpl_ZFLua_PropTypePrefix;
        classNameTmp += className;
        cls = ZFClass::classForName(classNameTmp);
    }
    if(cls == zfnull)
    {
        ZFImpl_ZFLua_luaPush(L, zfautoObjectNull);
        ZFImpl_ZFLua_implSetupObject(L);
        return 1;
    }
    if(cls->classIsAbstract())
    {
        ZFImpl_ZFLua_luaPush(L, zfautoObjectNull);
        ZFImpl_ZFLua_implSetupObject(L);
        return 1;
    }
    zfautoObject ret = cls->newInstance(ZFCallerInfo(ZF_CALLER_FILE, zfTextA("zfAlloc"), ZF_CALLER_LINE));
    if(ret == zfautoObjectNull)
    {
        ZFImpl_ZFLua_luaPush(L, zfautoObjectNull);
        ZFImpl_ZFLua_implSetupObject(L);
        return 1;
    }
    ZFImpl_ZFLua_luaPush(L, ret);
    ZFImpl_ZFLua_implSetupObject(L);

    return 1;
}

// ============================================================
ZFImpl_ZFLua_implSetupCallback_DEFINE(zfAlloc, {
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("zfAlloc"), _ZFP_ZFImpl_ZFLua_zfAlloc);
    }, {
    })

// ============================================================
ZFImpl_ZFLua_implDispatch_DEFINE(ZFClass_zfAlloc, ZFImpl_ZFLua_implDispatchAll, zfText("zfAlloc"), {
        ZFImpl_ZFLua_implDispatch_AssertClassExist();
        ZFImpl_ZFLua_implDispatch_AssertParamCount(0);
        ZFImpl_ZFLua_implDispatch_AssertIsStaticMethod();

        dispatchInfo.returnValue = dispatchInfo.classOrNull->newInstance();
        return dispatchInfo.dispatchSuccess();
    })

ZF_NAMESPACE_GLOBAL_END

