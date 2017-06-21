/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUILayoutParam.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFENUM_DEFINE(ZFUISizeType)

// ============================================================
// ZFUISizeParam
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFUISizeParam, ZFUISizeParam, {
        zfCoreAssert(src != zfnull);
        ZFCoreArrayPOD<zfindexRange> pos;
        if(!zfCoreDataPairSplitString(pos, 2, src, srcLen))
        {
            return zffalse;
        }

        if(!ZFUISizeTypeEnumFromString(v.width, src + pos[0].start, pos[0].count))
        {
            return zffalse;
        }

        if(!ZFUISizeTypeEnumFromString(v.height, src + pos[1].start, pos[1].count))
        {
            return zffalse;
        }

        return zftrue;
    }, {
        s += zfText("(");
        ZFUISizeTypeEnumToString(s, v.width);
        s += zfText(", ");
        ZFUISizeTypeEnumToString(s, v.height);
        s += zfText(")");
        return zftrue;
    })

const ZFUISizeParam ZFUISizeParamWrapWidthWrapHeight = ZFUISizeParamMake(ZFUISizeType::e_Wrap, ZFUISizeType::e_Wrap);
const ZFUISizeParam ZFUISizeParamFillWidthWrapHeight = ZFUISizeParamMake(ZFUISizeType::e_Fill, ZFUISizeType::e_Wrap);
const ZFUISizeParam ZFUISizeParamWrapWidthFillHeight = ZFUISizeParamMake(ZFUISizeType::e_Wrap, ZFUISizeType::e_Fill);
const ZFUISizeParam ZFUISizeParamFillWidthFillHeight = ZFUISizeParamMake(ZFUISizeType::e_Fill, ZFUISizeType::e_Fill);

// ============================================================
ZFOBJECT_REGISTER(ZFUILayoutParam)

ZFOBSERVER_EVENT_REGISTER(ZFUILayoutParam, LayoutParamOnChange)

ZF_NAMESPACE_GLOBAL_END

