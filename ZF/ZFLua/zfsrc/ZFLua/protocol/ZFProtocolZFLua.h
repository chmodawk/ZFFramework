/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFProtocolZFLua.h
 * @brief protocol for ZFLua
 */

#ifndef _ZFI_ZFProtocolZFLua_h_
#define _ZFI_ZFProtocolZFLua_h_

#include "ZFCore/ZFProtocol.h"
#include "ZFLua/ZFLuaDef.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief protocol for ZFLua
 *
 * impl must supply all protocol described by #ZFLuaExecute
 */
ZFPROTOCOL_INTERFACE_BEGIN(ZFLua)
public:
    /** @brief see #ZFLuaExecute */
    virtual zfbool luaExecute(ZF_IN const zfchar *src,
                              ZF_IN_OPT zfindex srcLen = zfindexMax(),
                              ZF_IN_OPT zfbool luaResultRequire = zffalse,
                              ZF_OUT_OPT zfautoObject *luaResult = zfnull,
                              ZF_OUT_OPT zfstring *errorHint = zfnull) zfpurevirtual;
    /** @brief see #ZFLuaGC */
    virtual void luaGC(void) zfpurevirtual;
ZFPROTOCOL_INTERFACE_END(ZFLua)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFProtocolZFLua_h_

