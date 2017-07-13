/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFCoreUtilCallerInfo.h"

ZF_NAMESPACE_GLOBAL_BEGIN

const ZFCallerInfo &_ZFP_ZFCallerInfoEmpty(void)
{
    static ZFCallerInfo d;
    return d;
}

ZF_NAMESPACE_GLOBAL_END

