/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFDebugLevel.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFENUM_DEFINE(ZFDebugLevel)

static ZFDebugLevelEnum _ZFP_ZFDebugLevelGlobal = ZFDebugLevel::EnumDefault();
void ZFDebugLevelSet(ZF_IN ZFDebugLevelEnum level)
{
    _ZFP_ZFDebugLevelGlobal = level;
}
ZFDebugLevelEnum ZFDebugLevelGet(void)
{
    return _ZFP_ZFDebugLevelGlobal;
}
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFDebugLevelReset, ZFLevelZFFrameworkEssential)
{
}
ZF_GLOBAL_INITIALIZER_DESTROY(ZFDebugLevelReset)
{
    _ZFP_ZFDebugLevelGlobal = ZFDebugLevel::EnumDefault();
}
ZF_GLOBAL_INITIALIZER_END(ZFDebugLevelReset)

ZF_NAMESPACE_GLOBAL_END

