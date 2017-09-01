/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFClassSerializable.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFClassInstanceObserverAddParam, ZFClassInstanceObserverAddParam)

ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFClass, const ZFClass *, {
        v = ZFClass::classForName((srcLen == zfindexMax()) ? src : zfstring(src, srcLen).cString());
        return (v != zfnull);
    }, {
        if(v)
        {
            s += v->className();
        }
        return zftrue;
    })

ZF_NAMESPACE_GLOBAL_END

