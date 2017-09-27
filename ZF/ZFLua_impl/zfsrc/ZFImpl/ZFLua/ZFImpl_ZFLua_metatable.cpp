/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFImpl_ZFLua.h"

#include "ZFCore/ZFSTLWrapper/zfstl_string.h"

ZF_NAMESPACE_GLOBAL_BEGIN

#define _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(param, luaStackOffset) \
    zfautoObject _##param = 0; \
    const ZFClass *param##Cls = zfnull; \
    if(!ZFImpl_ZFLua_toNumber(_##param, L, luaStackOffset, zftrue, &param##Cls)) \
    { \
        ZFLuaErrorOccurredTrim(zfText("[LuaMetatable] unknown param type: %s"), \
            ZFImpl_ZFLua_luaObjectInfo(L, luaStackOffset, zftrue).cString()); \
        return luaL_error(L, ""); \
    } \
    ZFValue *param = _##param.to<ZFValue *>()

// ============================================================
static int _ZFP_ZFImpl_ZFLua_metatableStoreResult(ZF_IN lua_State *L,
                                                  ZF_IN lua_Number const &n,
                                                  ZF_IN ZFValue *param0,
                                                  ZF_IN const ZFClass *paramClass0,
                                                  ZF_IN ZFValue *param1,
                                                  ZF_IN const ZFClass *paramClass1);

// ============================================================
static int _ZFP_ZFImpl_ZFLua_metatable_add(ZF_IN lua_State *L)
{
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v1, 1);
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v2, 2);
    return _ZFP_ZFImpl_ZFLua_metatableStoreResult(L,
        (lua_Number)(v1->doubleValue() + v2->doubleValue()),
        v1, v1Cls, v2, v2Cls);
}
static int _ZFP_ZFImpl_ZFLua_metatable_sub(ZF_IN lua_State *L)
{
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v1, 1);
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v2, 2);
    return _ZFP_ZFImpl_ZFLua_metatableStoreResult(L,
        (lua_Number)(v1->doubleValue() - v2->doubleValue()),
        v1, v1Cls, v2, v2Cls);
}
static int _ZFP_ZFImpl_ZFLua_metatable_mul(ZF_IN lua_State *L)
{
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v1, 1);
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v2, 2);
    return _ZFP_ZFImpl_ZFLua_metatableStoreResult(L,
        (lua_Number)(v1->doubleValue() * v2->doubleValue()),
        v1, v1Cls, v2, v2Cls);
}
static int _ZFP_ZFImpl_ZFLua_metatable_div(ZF_IN lua_State *L)
{
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v1, 1);
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v2, 2);
    return _ZFP_ZFImpl_ZFLua_metatableStoreResult(L,
        (lua_Number)(v1->doubleValue() / v2->doubleValue()),
        v1, v1Cls, v2, v2Cls);
}
static int _ZFP_ZFImpl_ZFLua_metatable_mod(ZF_IN lua_State *L)
{
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v1, 1);
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v2, 2);
    return _ZFP_ZFImpl_ZFLua_metatableStoreResult(L,
        (lua_Number)(v1->intValue() % v2->intValue()),
        v1, v1Cls, v2, v2Cls);
}
static int _ZFP_ZFImpl_ZFLua_metatable_unm(ZF_IN lua_State *L)
{
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v1, 1);
    return _ZFP_ZFImpl_ZFLua_metatableStoreResult(L,
        (lua_Number)(-(v1->doubleValue())),
        v1, v1Cls, zfnull, zfnull);
}
static int _ZFP_ZFImpl_ZFLua_metatable_band(ZF_IN lua_State *L)
{
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v1, 1);
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v2, 2);
    return _ZFP_ZFImpl_ZFLua_metatableStoreResult(L,
        (lua_Number)(v1->flagsValue() & v2->flagsValue()),
        v1, v1Cls, v2, v2Cls);
}
static int _ZFP_ZFImpl_ZFLua_metatable_bor(ZF_IN lua_State *L)
{
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v1, 1);
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v2, 2);
    return _ZFP_ZFImpl_ZFLua_metatableStoreResult(L,
        (lua_Number)(v1->flagsValue() | v2->flagsValue()),
        v1, v1Cls, v2, v2Cls);
}
static int _ZFP_ZFImpl_ZFLua_metatable_bxor(ZF_IN lua_State *L)
{
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v1, 1);
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v2, 2);
    return _ZFP_ZFImpl_ZFLua_metatableStoreResult(L,
        (lua_Number)(v1->flagsValue() ^ v2->flagsValue()),
        v1, v1Cls, v2, v2Cls);
}
static int _ZFP_ZFImpl_ZFLua_metatable_bnot(ZF_IN lua_State *L)
{
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v1, 1);
    return _ZFP_ZFImpl_ZFLua_metatableStoreResult(L,
        (lua_Number)(~(v1->flagsValue())),
        v1, v1Cls, zfnull, zfnull);
}
static int _ZFP_ZFImpl_ZFLua_metatable_shl(ZF_IN lua_State *L)
{
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v1, 1);
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v2, 2);
    return _ZFP_ZFImpl_ZFLua_metatableStoreResult(L,
        (lua_Number)(v1->intValue() << v2->intValue()),
        v1, v1Cls, v2, v2Cls);
}
static int _ZFP_ZFImpl_ZFLua_metatable_shr(ZF_IN lua_State *L)
{
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v1, 1);
    _ZFP_ZFImpl_ZFLua_metatable_PrepareParam(v2, 2);
    return _ZFP_ZFImpl_ZFLua_metatableStoreResult(L,
        (lua_Number)(v1->intValue() >> v2->intValue()),
        v1, v1Cls, v2, v2Cls);
}
static int _ZFP_ZFImpl_ZFLua_metatable_concat(ZF_IN lua_State *L)
{
    zfstring v;
    if(!ZFImpl_ZFLua_toString(v, L, 1, zftrue))
    {
        ZFLuaErrorOccurredTrim(zfText("[LuaMetatable] unknown param type: %s"),
            ZFImpl_ZFLua_luaObjectInfo(L, 1, zftrue).cString());
        return luaL_error(L, "");
    }
    if(!ZFImpl_ZFLua_toString(v, L, 2, zftrue))
    {
        ZFLuaErrorOccurredTrim(zfText("[LuaMetatable] unknown param type: %s"),
            ZFImpl_ZFLua_luaObjectInfo(L, 2, zftrue).cString());
        return luaL_error(L, "");
    }
    ZFSTRINGENCODING_ASSERT(ZFStringEncoding::e_UTF8)
    lua_pushstring(L, v.cString());
    return 1;
}
static int _ZFP_ZFImpl_ZFLua_metatable_len(ZF_IN lua_State *L)
{
    zfstring v;
    if(!ZFImpl_ZFLua_toString(v, L, 1, zftrue))
    {
        ZFLuaErrorOccurredTrim(zfText("[LuaMetatable] unknown param type: %s"),
            ZFImpl_ZFLua_luaObjectInfo(L, 1, zftrue).cString());
        return luaL_error(L, "");
    }
    lua_pushinteger(L, (lua_Integer)v.length());
    return 1;
}
static zfbool _ZFP_ZFImpl_ZFLua_metatable_cmp(ZF_OUT ZFCompareResult &ret, ZF_IN lua_State *L)
{
    if(lua_isuserdata(L, 1) && lua_isuserdata(L, 2))
    {
        zfautoObject v1;
        if(!ZFImpl_ZFLua_toObject(v1, L, 1))
        {
            ZFLuaErrorOccurredTrim(zfText("[LuaMetatable] unknown param type: %s"),
                ZFImpl_ZFLua_luaObjectInfo(L, 1, zftrue).cString());
            return zffalse;
        }
        zfautoObject v2;
        if(!ZFImpl_ZFLua_toObject(v2, L, 2))
        {
            ZFLuaErrorOccurredTrim(zfText("[LuaMetatable] unknown param type: %s"),
                ZFImpl_ZFLua_luaObjectInfo(L, 2, zftrue).cString());
            return zffalse;
        }
        ret = ZFComparerDefault(v1, v2);
        return zftrue;
    }
    else
    {
        if(lua_isnumber(L, 1) || lua_isnumber(L, 2))
        {
            zfautoObject v1;
            zfautoObject v2;
            if(ZFImpl_ZFLua_toNumber(v1, L, 1)
                && ZFImpl_ZFLua_toNumber(v2, L, 2))
            {
                ret = ZFComparerDefault(v1, v2);
                return zftrue;
            }
        }
        if(lua_isstring(L, 1) || lua_isstring(L, 2))
        {
            zfstring v1;
            zfstring v2;
            if(ZFImpl_ZFLua_toString(v1, L, 1, zftrue)
               && ZFImpl_ZFLua_toString(v2, L, 2, zftrue))
            {
                ret = ZFComparerDefault(v1, v2);
                return zftrue;
            }
        }
    }

    ZFLuaErrorOccurredTrim(zfText("[LuaMetatable] unknown param type: %s and %s"),
        ZFImpl_ZFLua_luaObjectInfo(L, 1, zftrue).cString(),
        ZFImpl_ZFLua_luaObjectInfo(L, 2, zftrue).cString());
    return zffalse;
}
static int _ZFP_ZFImpl_ZFLua_metatable_eq(ZF_IN lua_State *L)
{
    ZFCompareResult result = ZFCompareUncomparable;
    if(!_ZFP_ZFImpl_ZFLua_metatable_cmp(result, L))
    {
        return luaL_error(L, "");
    }
    lua_pushboolean(L, (result == ZFCompareTheSame));
    return 1;
}
static int _ZFP_ZFImpl_ZFLua_metatable_lt(ZF_IN lua_State *L)
{
    ZFCompareResult result = ZFCompareUncomparable;
    if(!_ZFP_ZFImpl_ZFLua_metatable_cmp(result, L))
    {
        return luaL_error(L, "");
    }
    lua_pushboolean(L, (result == ZFCompareSmaller));
    return 1;
}
static int _ZFP_ZFImpl_ZFLua_metatable_le(ZF_IN lua_State *L)
{
    ZFCompareResult result = ZFCompareUncomparable;
    if(!_ZFP_ZFImpl_ZFLua_metatable_cmp(result, L))
    {
        return luaL_error(L, "");
    }
    lua_pushboolean(L, (result == ZFCompareSmaller || result == ZFCompareTheSame));
    return 1;
}
static int _ZFP_ZFImpl_ZFLua_metatable_tostring(ZF_IN lua_State *L)
{
    zfautoObject obj;
    if(!ZFImpl_ZFLua_toObject(obj, L, 1))
    {
        ZFLuaErrorOccurredTrim(zfText("[__tostring] unknown object type: %s"),
            ZFImpl_ZFLua_luaObjectInfo(L, 1, zftrue).cString());
        return luaL_error(L, "");
    }

    zfstring ret;
    ZFObjectInfoT(ret, obj.toObject());
    ZFSTRINGENCODING_ASSERT(ZFStringEncoding::e_UTF8)
    lua_pushstring(L, ret.cString());
    return 1;
}

// ============================================================
void ZFImpl_ZFLua_implSetupObject_metatable(ZF_IN_OUT lua_State *L, ZF_IN_OPT zfint objIndex /* = -1 */)
{
    lua_getglobal(L, zfTextA("_ZFP_ZFImpl_ZFLua_implSetupObject"));
    if(!lua_isfunction(L, -1))
    {
        lua_pop(L, 1);

        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_add"), _ZFP_ZFImpl_ZFLua_metatable_add);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_sub"), _ZFP_ZFImpl_ZFLua_metatable_sub);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_mul"), _ZFP_ZFImpl_ZFLua_metatable_mul);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_div"), _ZFP_ZFImpl_ZFLua_metatable_div);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_mod"), _ZFP_ZFImpl_ZFLua_metatable_mod);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_unm"), _ZFP_ZFImpl_ZFLua_metatable_unm);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_band"), _ZFP_ZFImpl_ZFLua_metatable_band);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_bor"), _ZFP_ZFImpl_ZFLua_metatable_bor);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_bxor"), _ZFP_ZFImpl_ZFLua_metatable_bxor);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_bnot"), _ZFP_ZFImpl_ZFLua_metatable_bnot);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_shl"), _ZFP_ZFImpl_ZFLua_metatable_shl);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_shr"), _ZFP_ZFImpl_ZFLua_metatable_shr);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_concat"), _ZFP_ZFImpl_ZFLua_metatable_concat);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_len"), _ZFP_ZFImpl_ZFLua_metatable_len);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_eq"), _ZFP_ZFImpl_ZFLua_metatable_eq);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_lt"), _ZFP_ZFImpl_ZFLua_metatable_lt);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_le"), _ZFP_ZFImpl_ZFLua_metatable_le);
        ZFImpl_ZFLua_luaCFunctionRegister(L, zfText("_ZFP_ZFImpl_ZFLua_metatable_tostring"), _ZFP_ZFImpl_ZFLua_metatable_tostring);

        ZFImpl_ZFLua_execute(L, zfText(
                "function _ZFP_ZFImpl_ZFLua_implSetupObject_index(obj, k)\n"
                "    return function(obj, ...)\n"
                "        return zfl_call(obj, k, ...)\n"
                "    end\n"
                "end\n"
                "\n"
                "function _ZFP_ZFImpl_ZFLua_implSetupObject(obj)\n"
                "    local tbl = debug.getmetatable(obj)\n"
                "    tbl.__index = _ZFP_ZFImpl_ZFLua_implSetupObject_index\n"
                "    \n"
                "    tbl.__add = _ZFP_ZFImpl_ZFLua_metatable_add\n"
                "    tbl.__sub = _ZFP_ZFImpl_ZFLua_metatable_sub\n"
                "    tbl.__mul = _ZFP_ZFImpl_ZFLua_metatable_mul\n"
                "    tbl.__div = _ZFP_ZFImpl_ZFLua_metatable_div\n"
                "    tbl.__mod = _ZFP_ZFImpl_ZFLua_metatable_mod\n"
                "    tbl.__unm = _ZFP_ZFImpl_ZFLua_metatable_unm\n"
                "    tbl.__band = _ZFP_ZFImpl_ZFLua_metatable_band\n"
                "    tbl.__bor = _ZFP_ZFImpl_ZFLua_metatable_bor\n"
                "    tbl.__bxor = _ZFP_ZFImpl_ZFLua_metatable_bxor\n"
                "    tbl.__bnot = _ZFP_ZFImpl_ZFLua_metatable_bnot\n"
                "    tbl.__shl = _ZFP_ZFImpl_ZFLua_metatable_shl\n"
                "    tbl.__shr = _ZFP_ZFImpl_ZFLua_metatable_shr\n"
                "    tbl.__concat = _ZFP_ZFImpl_ZFLua_metatable_concat\n"
                "    tbl.__len = _ZFP_ZFImpl_ZFLua_metatable_len\n"
                "    tbl.__eq = _ZFP_ZFImpl_ZFLua_metatable_eq\n"
                "    tbl.__lt = _ZFP_ZFImpl_ZFLua_metatable_lt\n"
                "    tbl.__le = _ZFP_ZFImpl_ZFLua_metatable_le\n"
                "    tbl.__tostring = _ZFP_ZFImpl_ZFLua_metatable_tostring\n"
                "    \n"
                "    debug.setmetatable(obj, tbl)\n"
                "end\n"
            ));

        lua_getglobal(L, zfTextA("_ZFP_ZFImpl_ZFLua_implSetupObject"));
    }

    lua_pushvalue(L, (objIndex > 0) ? objIndex : (objIndex - 1));

    int error = lua_pcall(L, 1, 0, 0);
    if(error)
    {
        zfstring errorHint = zfsCoreA2Z(lua_tostring(L, -1));
        lua_pop(L, 1);

        ZFLuaErrorOccurredTrim(
            zfText("[ZFLua] failed to setup object metatable: %s"),
            errorHint.cString());
    }
}

// ============================================================
static int _ZFP_ZFImpl_ZFLua_metatableStoreResult(ZF_IN lua_State *L,
                                                  ZF_IN lua_Number const &n,
                                                  ZF_IN ZFValue *param0,
                                                  ZF_IN const ZFClass *paramClass0,
                                                  ZF_IN ZFValue *param1,
                                                  ZF_IN const ZFClass *paramClass1)
{
    if(paramClass0 == zfnull)
    {
        paramClass0 = paramClass1;
    }
    if(paramClass0 == zfnull)
    {
        lua_pushnumber(L, n);
        return 1;
    }
    if(paramClass1 == zfnull)
    {
        paramClass1 = paramClass0;
    }
    if(param1 == zfnull)
    {
        param1 = param0;
    }

    if(zffalse
        || paramClass0->classIsTypeOf(v_zffloat::ClassData())
        || paramClass1->classIsTypeOf(v_zffloat::ClassData())
        || paramClass0->classIsTypeOf(v_zfdouble::ClassData())
        || paramClass1->classIsTypeOf(v_zfdouble::ClassData())
        || paramClass0->classIsTypeOf(v_zflongdouble::ClassData())
        || paramClass1->classIsTypeOf(v_zflongdouble::ClassData())
        )
    {
        zfblockedAllocWithoutLeakTest(v_zfdouble, ret, (zfdouble)n);
        ZFImpl_ZFLua_luaPush(L, zfautoObjectCreateWithoutLeakTest(ret));
        return 1;
    }
    else if(paramClass0->classIsTypeOf(ZFValue::ClassData()) || paramClass1->classIsTypeOf(ZFValue::ClassData()))
    {
        ZFImpl_ZFLua_luaPush(L, ZFValue::doubleValueCreate((zfdouble)n));
        return 1;
    }
    else if(paramClass0->classIsTypeOf(v_zfflags::ClassData()) || paramClass1->classIsTypeOf(v_zfflags::ClassData()))
    {
        zfblockedAllocWithoutLeakTest(v_zfflags, ret, (zfflags)n);
        ZFImpl_ZFLua_luaPush(L, zfautoObjectCreateWithoutLeakTest(ret));
        return 1;
    }
    else if(paramClass0->classIsTypeOf(v_zfidentity::ClassData()) || paramClass1->classIsTypeOf(v_zfidentity::ClassData()))
    {
        zfblockedAllocWithoutLeakTest(v_zfidentity, ret, (zfidentity)n);
        ZFImpl_ZFLua_luaPush(L, zfautoObjectCreateWithoutLeakTest(ret));
        return 1;
    }
    else if(paramClass0->classIsTypeOf(v_zfindex::ClassData()) || paramClass1->classIsTypeOf(v_zfindex::ClassData()))
    {
        zfblockedAllocWithoutLeakTest(v_zfindex, ret, (zfindex)n);
        ZFImpl_ZFLua_luaPush(L, zfautoObjectCreateWithoutLeakTest(ret));
        return 1;
    }
    else if(paramClass0->classIsTypeOf(v_zftimet::ClassData()) || paramClass1->classIsTypeOf(v_zftimet::ClassData()))
    {
        zfblockedAllocWithoutLeakTest(v_zftimet, ret, (zftimet)n);
        ZFImpl_ZFLua_luaPush(L, zfautoObjectCreateWithoutLeakTest(ret));
        return 1;
    }

    if(paramClass0->classIsTypeOf(ZFEnum::ClassData()))
    {
        zfautoObject ret;
        if(ZFEnumInfoToWrapper(ret, paramClass0, (zfuint)n, zftrue)
            || ZFEnumInfoToWrapper(ret, paramClass0, (zfuint)n, zffalse))
        {
            ZFImpl_ZFLua_luaPush(L, ret);
            return zftrue;
        }
    }
    if(paramClass1->classIsTypeOf(ZFEnum::ClassData()))
    {
        zfautoObject ret;
        if(ZFEnumInfoToWrapper(ret, paramClass1, (zfuint)n, zftrue)
            || ZFEnumInfoToWrapper(ret, paramClass1, (zfuint)n, zffalse))
        {
            ZFImpl_ZFLua_luaPush(L, ret);
            return zftrue;
        }
    }

    zfblockedAllocWithoutLeakTest(v_zfint, ret, (zfint)n);
    ZFImpl_ZFLua_luaPush(L, zfautoObjectCreateWithoutLeakTest(ret));
    return 1;
}

ZF_NAMESPACE_GLOBAL_END

