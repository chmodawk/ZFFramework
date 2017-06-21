/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZF2048Types.h"

ZF_NAMESPACE_GLOBAL_BEGIN

const ZF2048Point ZF2048PointZero = {0, 0};

ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZF2048Value, ZF2048Value, {
        return zfsToIntT(v, src, srcLen);
    }, {
        return zfsFromIntT(s, v);
    })

ZF_NAMESPACE_GLOBAL_END

