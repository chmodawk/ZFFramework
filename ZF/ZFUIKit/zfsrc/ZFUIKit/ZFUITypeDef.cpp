/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUITypeDef.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
ZFMETHOD_FUNC_DEFINE_3(void, ZFUISizeApplyScale,
                       ZFMP_OUT(zfint &, ret),
                       ZFMP_IN(zfint const &, v),
                       ZFMP_IN(zffloat, scale))
{
    if(v == 1)
    {
        ret = 1;
    }
    else
    {
        if(scale < 1 - zffloatEpsilon)
        {
            scale = v * scale;
            if(scale > (zfint)scale + 0.01f)
            {
                ret = (zfint)scale + 1;
            }
            else
            {
                ret = (zfint)scale;
            }
        }
        else
        {
            ret = (zfint)zfmRound(v * scale);
        }
    }
}
ZFMETHOD_FUNC_DEFINE_INLINE_2(zfint, ZFUISizeApplyScale,
                              ZFMP_IN(zfint const &, v),
                              ZFMP_IN(zffloat, scale))

ZFMETHOD_FUNC_DEFINE_3(void, ZFUISizeApplyScaleReversely,
                       ZFMP_OUT(zfint &, ret),
                       ZFMP_IN(zfint const &, v),
                       ZFMP_IN(zffloat, scale))
{
    if(v == 1)
    {
        ret = 1;
    }
    else
    {
        if(scale > 1 + zffloatEpsilon)
        {
            scale = v / scale;
            if(scale > (zfint)scale + 0.01f)
            {
                ret = (zfint)scale + 1;
            }
            else
            {
                ret = (zfint)scale;
            }
        }
        else
        {
            ret = (zfint)zfmRound(v / scale);
        }
    }
}
ZFMETHOD_FUNC_DEFINE_INLINE_2(zfint, ZFUISizeApplyScaleReversely,
                              ZFMP_IN(zfint const &, v),
                              ZFMP_IN(zffloat, scale))

// ============================================================
// ZFUIPoint
ZFEXPORT_VAR_READONLY_DEFINE(ZFUIPoint, ZFUIPointZero, ZFUIPointMake(0, 0))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIPoint, ZFUIPointMake,
                              ZFMP_IN(zfint const &, x),
                              ZFMP_IN(zfint const &, y))
ZFMETHOD_FUNC_DEFINE_INLINE_3(void, ZFUIPointApplyScale,
                              ZFMP_OUT(ZFUIPoint &, ret),
                              ZFMP_IN(const ZFUIPoint &, point),
                              ZFMP_IN(zffloat, scale))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIPoint, ZFUIPointApplyScale,
                              ZFMP_IN(const ZFUIPoint &, point),
                              ZFMP_IN(zffloat, scale))
ZFMETHOD_FUNC_DEFINE_INLINE_3(void, ZFUIPointApplyScaleReversely,
                              ZFMP_OUT(ZFUIPoint &, ret),
                              ZFMP_IN(const ZFUIPoint &, point),
                              ZFMP_IN(zffloat, scale))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIPoint, ZFUIPointApplyScaleReversely,
                              ZFMP_IN(const ZFUIPoint &, point),
                              ZFMP_IN(zffloat, scale))
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFUIPoint, ZFUIPoint, {
        zfCoreAssert(src != zfnull);
        ZFCoreArrayPOD<zfint> buf;
        if(!zfCoreDataPairSplitInt(buf, 2, src, srcLen))
        {
            return zffalse;
        }
        v.x = buf[0];
        v.y = buf[1];
        return zftrue;
    }, {
        zfstringAppend(s, zfText("(%d, %d)"), v.x, v.y);
        return zftrue;
    })

// ============================================================
// ZFUIMargin
ZFEXPORT_VAR_READONLY_DEFINE(ZFUIMargin, ZFUIMarginZero, ZFUIMarginMake(0, 0, 0, 0))
ZFMETHOD_FUNC_DEFINE_INLINE_4(ZFUIMargin, ZFUIMarginMake,
                              ZFMP_IN(zfint const &, left),
                              ZFMP_IN(zfint const &, top),
                              ZFMP_IN(zfint const &, right),
                              ZFMP_IN(zfint const &, bottom))
ZFMETHOD_FUNC_DEFINE_INLINE_1(ZFUIMargin, ZFUIMarginMake,
                              ZFMP_IN(zfint const &, margin))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIMargin, ZFUIMarginMake,
                              ZFMP_IN(zfint const &, x),
                              ZFMP_IN(zfint const &, y))
ZFMETHOD_FUNC_DEFINE_INLINE_3(void, ZFUIMarginApplyScale,
                              ZFMP_OUT(ZFUIMargin &, ret),
                              ZFMP_IN(const ZFUIMargin &, margin),
                              ZFMP_IN(zffloat, scale))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIMargin, ZFUIMarginApplyScale,
                              ZFMP_IN(const ZFUIMargin &, margin),
                              ZFMP_IN(zffloat, scale))
ZFMETHOD_FUNC_DEFINE_INLINE_3(void, ZFUIMarginApplyScaleReversely,
                              ZFMP_OUT(ZFUIMargin &, ret),
                              ZFMP_IN(const ZFUIMargin &, margin),
                              ZFMP_IN(zffloat, scale))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIMargin, ZFUIMarginApplyScaleReversely,
                              ZFMP_IN(const ZFUIMargin &, margin),
                              ZFMP_IN(zffloat, scale))
ZFMETHOD_FUNC_DEFINE_INLINE_1(zfint, ZFUIMarginGetX,
                              ZFMP_IN(const ZFUIMargin &, margin))
ZFMETHOD_FUNC_DEFINE_INLINE_1(zfint, ZFUIMarginGetY,
                              ZFMP_IN(const ZFUIMargin &, margin))
ZFMETHOD_FUNC_DEFINE_INLINE_3(void, ZFUIMarginInc,
                              ZFMP_IN_OUT(ZFUIMargin &, ret),
                              ZFMP_IN(const ZFUIMargin &, v0),
                              ZFMP_IN(const ZFUIMargin &, v1))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIMargin, ZFUIMarginInc,
                              ZFMP_IN(const ZFUIMargin &, v0),
                              ZFMP_IN(const ZFUIMargin &, v1))
ZFMETHOD_FUNC_DEFINE_INLINE_3(void, ZFUIMarginDec,
                              ZFMP_IN_OUT(ZFUIMargin &, ret),
                              ZFMP_IN(const ZFUIMargin &, v0),
                              ZFMP_IN(const ZFUIMargin &, v1))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIMargin, ZFUIMarginDec,
                              ZFMP_IN(const ZFUIMargin &, v0),
                              ZFMP_IN(const ZFUIMargin &, v1))
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFUIMargin, ZFUIMargin, {
        zfCoreAssert(src != zfnull);
        ZFCoreArrayPOD<zfint> buf;
        if(!zfCoreDataPairSplitInt(buf, 4, src, srcLen))
        {
            return zffalse;
        }
        v.left = buf[0];
        v.top = buf[1];
        v.right = buf[2];
        v.bottom = buf[3];
        return zftrue;
    }, {
        zfstringAppend(s, zfText("(%d, %d, %d, %d)"), v.left, v.top, v.right, v.bottom);
        return zftrue;
    })

// ============================================================
// ZFUISize
ZFEXPORT_VAR_READONLY_DEFINE(ZFUISize, ZFUISizeZero, ZFUISizeMake(0, 0))
ZFEXPORT_VAR_READONLY_DEFINE(ZFUISize, ZFUISizeInvalid, ZFUISizeMake(-1, -1))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUISize, ZFUISizeMake,
                              ZFMP_IN(zfint const &, width),
                              ZFMP_IN(zfint const &, height))
ZFMETHOD_FUNC_DEFINE_INLINE_1(ZFUISize, ZFUISizeMake,
                              ZFMP_IN(zfint const &, v))
ZFMETHOD_FUNC_DEFINE_INLINE_4(void, ZFUISizeApplyRange,
                              ZFMP_OUT(ZFUISize &, ret),
                              ZFMP_IN(const ZFUISize &, orgSize),
                              ZFMP_IN(const ZFUISize &, minSize),
                              ZFMP_IN(const ZFUISize &, maxSize))
ZFMETHOD_FUNC_DEFINE_INLINE_3(ZFUISize, ZFUISizeApplyRange,
                              ZFMP_IN(const ZFUISize &, orgSize),
                              ZFMP_IN(const ZFUISize &, minSize),
                              ZFMP_IN(const ZFUISize &, maxSize))
ZFMETHOD_FUNC_DEFINE_INLINE_3(void, ZFUISizeApplyScale,
                              ZFMP_OUT(ZFUISize &, ret),
                              ZFMP_IN(const ZFUISize &, size),
                              ZFMP_IN(zffloat, scale))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUISize, ZFUISizeApplyScale,
                              ZFMP_IN(const ZFUISize &, size),
                              ZFMP_IN(zffloat, scale))
ZFMETHOD_FUNC_DEFINE_INLINE_3(void, ZFUISizeApplyScaleReversely,
                              ZFMP_OUT(ZFUISize &, ret),
                              ZFMP_IN(const ZFUISize &, size),
                              ZFMP_IN(zffloat, scale))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUISize, ZFUISizeApplyScaleReversely,
                              ZFMP_IN(const ZFUISize &, size),
                              ZFMP_IN(zffloat, scale))
ZFMETHOD_FUNC_DEFINE_3(void, ZFUISizeApplyAspectRatio,
                       ZFMP_OUT(ZFUISize &, ret),
                       ZFMP_IN(const ZFUISize &, size),
                       ZFMP_IN(const ZFUISize &, refSize))
{
    if(size.width <= 0 || size.height <= 0
        || refSize.width == 0 || refSize.height == 0)
    {
        ret = ZFUISizeZero();
    }
    else if(refSize.width < 0 && refSize.height < 0)
    {
        ret = size;
    }
    else if(refSize.height < 0 || size.width * refSize.height > size.height * refSize.width)
    {
        ret = ZFUISizeMake(
            refSize.width,
            size.height * refSize.width / size.width
        );
    }
    else
    {
        ret = ZFUISizeMake(
            size.width * refSize.height / size.height,
            refSize.height
        );
    }
}
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUISize, ZFUISizeApplyAspectRatio,
                              ZFMP_IN(const ZFUISize &, size),
                              ZFMP_IN(const ZFUISize &, refSize))
ZFMETHOD_FUNC_DEFINE_INLINE_3(void, ZFUISizeApplyMargin,
                              ZFMP_OUT(ZFUISize &, ret),
                              ZFMP_IN(const ZFUISize &, size),
                              ZFMP_IN(const ZFUIMargin &, margin))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUISize, ZFUISizeApplyMargin,
                              ZFMP_IN(const ZFUISize &, size),
                              ZFMP_IN(const ZFUIMargin &, margin))
ZFMETHOD_FUNC_DEFINE_INLINE_3(void, ZFUISizeApplyMarginReversely,
                              ZFMP_OUT(ZFUISize &, ret),
                              ZFMP_IN(const ZFUISize &, size),
                              ZFMP_IN(const ZFUIMargin &, margin))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUISize, ZFUISizeApplyMarginReversely,
                              ZFMP_IN(const ZFUISize &, size),
                              ZFMP_IN(const ZFUIMargin &, margin))

ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFUISize, ZFUISize, {
        zfCoreAssert(src != zfnull);
        ZFCoreArrayPOD<zfint> buf;
        if(!zfCoreDataPairSplitInt(buf, 2, src, srcLen))
        {
            return zffalse;
        }
        v.width = buf[0];
        v.height = buf[1];
        return zftrue;
    }, {
        zfstringAppend(s, zfText("(%d, %d)"), v.width, v.height);
        return zftrue;
    })

// ============================================================
// ZFUIRect
ZFEXPORT_VAR_READONLY_DEFINE(ZFUIRect, ZFUIRectZero, ZFUIRectMake(0, 0, 0, 0))
ZFMETHOD_FUNC_DEFINE_INLINE_4(ZFUIRect, ZFUIRectMake,
                              ZFMP_IN(zfint const &, x),
                              ZFMP_IN(zfint const &, y),
                              ZFMP_IN(zfint const &, w),
                              ZFMP_IN(zfint const &, h))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIRect, ZFUIRectMake,
                              ZFMP_IN(const ZFUIPoint &, point),
                              ZFMP_IN(const ZFUISize &, size))
ZFMETHOD_FUNC_DEFINE_INLINE_1(zfbool, ZFUIRectIsEmpty,
                              ZFMP_IN(const ZFUIRect &, rect))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIRect, ZFUIRectUnion,
                              ZFMP_IN(const ZFUIRect &, rect1),
                              ZFMP_IN(const ZFUIRect &, rect2))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIRect, ZFUIRectIntersection,
                              ZFMP_IN(const ZFUIRect &, rect1),
                              ZFMP_IN(const ZFUIRect &, rect2))
ZFMETHOD_FUNC_DEFINE_INLINE_2(zfbool, ZFUIRectIsIntersectToRect,
                              ZFMP_IN(const ZFUIRect &, rect1),
                              ZFMP_IN(const ZFUIRect &, rect2))
ZFMETHOD_FUNC_DEFINE_INLINE_2(zfbool, ZFUIRectIsContainPoint,
                              ZFMP_IN(const ZFUIRect &, rect),
                              ZFMP_IN(const ZFUIPoint &, point))
ZFMETHOD_FUNC_DEFINE_INLINE_3(zfbool, ZFUIRectIsContainPoint,
                              ZFMP_IN(const ZFUIRect &, rect),
                              ZFMP_IN(const ZFUIPoint &, point),
                              ZFMP_IN(const ZFUIMargin &, margin))
ZFMETHOD_FUNC_DEFINE_INLINE_2(zfbool, ZFUIRectIsContainRect,
                              ZFMP_IN(const ZFUIRect &, rect1),
                              ZFMP_IN(const ZFUIRect &, rect2))
ZFMETHOD_FUNC_DEFINE_INLINE_3(zfbool, ZFUIRectIsContainRect,
                              ZFMP_IN(const ZFUIRect &, rect1),
                              ZFMP_IN(const ZFUIRect &, rect2),
                              ZFMP_IN(const ZFUIMargin &, margin))
ZFMETHOD_FUNC_DEFINE_INLINE_3(void, ZFUIRectApplyScale,
                              ZFMP_OUT(ZFUIRect &, ret),
                              ZFMP_IN(const ZFUIRect &, rect),
                              ZFMP_IN(zffloat, scale))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIRect, ZFUIRectApplyScale,
                              ZFMP_IN(const ZFUIRect &, rect),
                              ZFMP_IN(zffloat, scale))
ZFMETHOD_FUNC_DEFINE_INLINE_3(void, ZFUIRectApplyScaleReversely,
                              ZFMP_OUT(ZFUIRect &, ret),
                              ZFMP_IN(const ZFUIRect &, rect),
                              ZFMP_IN(zffloat, scale))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIRect, ZFUIRectApplyScaleReversely,
                              ZFMP_IN(const ZFUIRect &, rect),
                              ZFMP_IN(zffloat, scale))
ZFMETHOD_FUNC_DEFINE_INLINE_1(ZFUIRect, ZFUIRectGetBounds,
                              ZFMP_IN(const ZFUIRect &, rect))
ZFMETHOD_FUNC_DEFINE_INLINE_1(ZFUIPoint, ZFUIRectGetCenter,
                              ZFMP_IN(const ZFUIRect &, rect))
ZFMETHOD_FUNC_DEFINE_INLINE_1(zfint, ZFUIRectGetLeft,
                              ZFMP_IN(const ZFUIRect &, rect))
ZFMETHOD_FUNC_DEFINE_INLINE_1(zfint, ZFUIRectGetTop,
                              ZFMP_IN(const ZFUIRect &, rect))
ZFMETHOD_FUNC_DEFINE_INLINE_1(zfint, ZFUIRectGetRight,
                              ZFMP_IN(const ZFUIRect &, rect))
ZFMETHOD_FUNC_DEFINE_INLINE_1(zfint, ZFUIRectGetBottom,
                              ZFMP_IN(const ZFUIRect &, rect))
ZFMETHOD_FUNC_DEFINE_INLINE_3(void, ZFUIRectApplyMargin,
                              ZFMP_OUT(ZFUIRect &, ret),
                              ZFMP_IN(const ZFUIRect &, rect),
                              ZFMP_IN(const ZFUIMargin &, margin))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIRect, ZFUIRectApplyMargin,
                              ZFMP_IN(const ZFUIRect &, rect),
                              ZFMP_IN(const ZFUIMargin &, margin))
ZFMETHOD_FUNC_DEFINE_INLINE_3(void, ZFUIRectApplyMarginReversely,
                              ZFMP_OUT(ZFUIRect &, ret),
                              ZFMP_IN(const ZFUIRect &, rect),
                              ZFMP_IN(const ZFUIMargin &, margin))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIRect, ZFUIRectApplyMarginReversely,
                              ZFMP_IN(const ZFUIRect &, rect),
                              ZFMP_IN(const ZFUIMargin &, margin))
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFUIRect, ZFUIRect, {
        zfCoreAssert(src != zfnull);
        ZFCoreArrayPOD<zfint> buf;
        if(!zfCoreDataPairSplitInt(buf, 4, src, srcLen))
        {
            return zffalse;
        }
        v.point.x = buf[0];
        v.point.y = buf[1];
        v.size.width = buf[2];
        v.size.height = buf[3];
        return zftrue;
    }, {
        zfstringAppend(s, zfText("(%d, %d, %d, %d)"), v.point.x, v.point.y, v.size.width, v.size.height);
        return zftrue;
    })

// ============================================================
// ZFUIAlignFlags
ZFENUM_DEFINE(ZFUIAlign)
ZFENUM_FLAGS_DEFINE(ZFUIAlign, ZFUIAlignFlags)
static const ZFUIAlignFlags &_ZFP_ZFUIAlignMask(void)
{
    static ZFUIAlignFlags _alignMask = (0
        | ZFUIAlign::e_Center
        | ZFUIAlign::e_Left
        | ZFUIAlign::e_LeftInner
        | ZFUIAlign::e_Top
        | ZFUIAlign::e_TopInner
        | ZFUIAlign::e_Right
        | ZFUIAlign::e_RightInner
        | ZFUIAlign::e_Bottom
        | ZFUIAlign::e_BottomInner
        );
    return _alignMask;
}
ZFMETHOD_FUNC_DEFINE_1(zfbool, ZFUIAlignIsValid,
                       ZFMP_IN(const ZFUIAlignFlags &, align))
{
    return (
            ZFBitGet(align, ~(_ZFP_ZFUIAlignMask())) == 0
            && ((zfint)ZFBitTest(align, ZFUIAlign::e_Left)
                + (zfint)ZFBitTest(align, ZFUIAlign::e_LeftInner)
                + (zfint)ZFBitTest(align, ZFUIAlign::e_Right)
                + (zfint)ZFBitTest(align, ZFUIAlign::e_RightInner)
                ) <= 1
            && ((zfint)ZFBitTest(align, ZFUIAlign::e_Top)
                + (zfint)ZFBitTest(align, ZFUIAlign::e_TopInner)
                + (zfint)ZFBitTest(align, ZFUIAlign::e_Bottom)
                + (zfint)ZFBitTest(align, ZFUIAlign::e_BottomInner)
                ) <= 1
        );
}
ZFMETHOD_FUNC_DEFINE_5(void, ZFUIAlignApply,
                       ZFMP_OUT(ZFUIRect &, ret),
                       ZFMP_IN(const ZFUIAlignFlags &, align),
                       ZFMP_IN(const ZFUIRect &, refRect),
                       ZFMP_IN(const ZFUISize &, itemSize),
                       ZFMP_IN_OPT(const ZFUIMargin &, margin, ZFUIMarginZero()))
{
    ret = ZFUIRectZero();
    if(!ZFUIAlignIsValid(align))
    {
        return ;
    }
    ret.size = itemSize;

    if(ZFBitTest(align, ZFUIAlign::e_LeftInner))
    {
        ret.point.x = refRect.point.x + margin.left;
    }
    else if(ZFBitTest(align, ZFUIAlign::e_RightInner))
    {
        ret.point.x = refRect.point.x + refRect.size.width - margin.right - itemSize.width;
    }
    else if(ZFBitTest(align, ZFUIAlign::e_Left))
    {
        ret.point.x = refRect.point.x - margin.right - itemSize.width;
    }
    else if(ZFBitTest(align, ZFUIAlign::e_Right))
    {
        ret.point.x = refRect.point.x + refRect.size.width + margin.left;
    }
    else
    {
        ret.point.x = refRect.point.x + margin.left
            + (refRect.size.width - margin.left - margin.right - itemSize.width) / 2;
    }

    if(ZFBitTest(align, ZFUIAlign::e_TopInner))
    {
        ret.point.y = refRect.point.y + margin.top;
    }
    else if(ZFBitTest(align, ZFUIAlign::e_BottomInner))
    {
        ret.point.y = refRect.point.y + refRect.size.height - margin.bottom - itemSize.height;
    }
    else if(ZFBitTest(align, ZFUIAlign::e_Top))
    {
        ret.point.y = refRect.point.y - margin.bottom - itemSize.height;
    }
    else if(ZFBitTest(align, ZFUIAlign::e_Bottom))
    {
        ret.point.y = refRect.point.y + refRect.size.height + margin.top;
    }
    else
    {
        ret.point.y = refRect.point.y + margin.top
            + (refRect.size.height - margin.top - margin.bottom - itemSize.height) / 2;
    }
}
ZFMETHOD_FUNC_DEFINE_INLINE_4(ZFUIRect, ZFUIAlignApply,
                              ZFMP_IN(const ZFUIAlignFlags &, align),
                              ZFMP_IN(const ZFUIRect &, refRect),
                              ZFMP_IN(const ZFUISize &, itemSize),
                              ZFMP_IN_OPT(const ZFUIMargin &, margin, ZFUIMarginZero()))
ZFMETHOD_FUNC_DEFINE_1(ZFUIAlignEnum, ZFUIAlignGetX,
                       ZFMP_IN(const ZFUIAlignFlags &, align))
{
    if(!ZFUIAlignIsValid(align))
    {
        return ZFUIAlign::e_Center;
    }

    if(ZFBitTest(align, ZFUIAlign::e_Left))
    {
        return ZFUIAlign::e_Left;
    }
    if(ZFBitTest(align, ZFUIAlign::e_LeftInner))
    {
        return ZFUIAlign::e_LeftInner;
    }
    if(ZFBitTest(align, ZFUIAlign::e_Right))
    {
        return ZFUIAlign::e_Right;
    }
    if(ZFBitTest(align, ZFUIAlign::e_RightInner))
    {
        return ZFUIAlign::e_RightInner;
    }
    return ZFUIAlign::e_Center;
}
ZFMETHOD_FUNC_DEFINE_1(ZFUIAlignEnum, ZFUIAlignGetY,
                       ZFMP_IN(const ZFUIAlignFlags &, align))
{
    if(!ZFUIAlignIsValid(align))
    {
        return ZFUIAlign::e_Center;
    }

    if(ZFBitTest(align, ZFUIAlign::e_Top))
    {
        return ZFUIAlign::e_Top;
    }
    if(ZFBitTest(align, ZFUIAlign::e_TopInner))
    {
        return ZFUIAlign::e_TopInner;
    }
    if(ZFBitTest(align, ZFUIAlign::e_Bottom))
    {
        return ZFUIAlign::e_Bottom;
    }
    if(ZFBitTest(align, ZFUIAlign::e_BottomInner))
    {
        return ZFUIAlign::e_BottomInner;
    }
    return ZFUIAlign::e_Center;
}

// ============================================================
// ZFUIColor
ZFEXPORT_VAR_READONLY_DEFINE(ZFUIColor, ZFUIColorZero, ((ZFUIColor)0x00000000))
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFUIColor, ZFUIColor, {
        zft_zfuint32 c = 0;
        do
        {
            if(src == zfnull
                || (srcLen != zfindexMax() && srcLen != 9))
            {
                return zffalse;
            }
            if(*src != '#') {return zffalse;} ++src;
            zfuint tmp = 0;

            tmp = 0;
            if(!zfsToIntT(tmp, src, 2, 16)) {return zffalse;} src += 2;
            ZFBitSet(c, (tmp << 24));

            tmp = 0;
            if(!zfsToIntT(tmp, src, 2, 16)) {return zffalse;} src += 2;
            ZFBitSet(c, (tmp << 16));

            tmp = 0;
            if(!zfsToIntT(tmp, src, 2, 16)) {return zffalse;} src += 2;
            ZFBitSet(c, (tmp << 8));

            tmp = 0;
            if(!zfsToIntT(tmp, src, 2, 16)) {return zffalse;} src += 2;
            ZFBitSet(c, (tmp));

            ZFUNUSED(src);
        } while(zffalse);

        v = c;

        return zftrue;
    }, {
        zfstringAppend(s, zfText("#%02X%02X%02X%02X"),
            ZFUIColorGetA(v),
            ZFUIColorGetR(v),
            ZFUIColorGetG(v),
            ZFUIColorGetB(v));
        return zftrue;
    })

ZFMETHOD_FUNC_DEFINE_INLINE_2(zfbool, ZFUIColorIsEqual,
                              ZFMP_IN(ZFUIColor const &, v0),
                              ZFMP_IN(ZFUIColor const &, v1))

ZFMETHOD_FUNC_DEFINE_INLINE_4(ZFUIColor, ZFUIColorMake,
                              ZFMP_IN(zfuint, a),
                              ZFMP_IN(zfuint, r),
                              ZFMP_IN(zfuint, g),
                              ZFMP_IN(zfuint, b))

ZFMETHOD_FUNC_DEFINE_INLINE_1(zfuint, ZFUIColorGetA,
                              ZFMP_IN(ZFUIColor const &, c))
ZFMETHOD_FUNC_DEFINE_INLINE_1(zfuint, ZFUIColorGetR,
                              ZFMP_IN(ZFUIColor const &, c))
ZFMETHOD_FUNC_DEFINE_INLINE_1(zfuint, ZFUIColorGetG,
                              ZFMP_IN(ZFUIColor const &, c))
ZFMETHOD_FUNC_DEFINE_INLINE_1(zfuint, ZFUIColorGetB,
                              ZFMP_IN(ZFUIColor const &, c))

ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIColor &, ZFUIColorSetA,
                              ZFMP_IN_OUT(ZFUIColor &, c),
                              ZFMP_IN(zfuint, a))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIColor &, ZFUIColorSetR,
                              ZFMP_IN_OUT(ZFUIColor &, c),
                              ZFMP_IN(zfuint, r))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIColor &, ZFUIColorSetG,
                              ZFMP_IN_OUT(ZFUIColor &, c),
                              ZFMP_IN(zfuint, g))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIColor &, ZFUIColorSetB,
                              ZFMP_IN_OUT(ZFUIColor &, c),
                              ZFMP_IN(zfuint, b))

ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIColor, ZFUIColorChangeA,
                              ZFMP_IN(ZFUIColor const &, c),
                              ZFMP_IN(zfuint, a))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIColor, ZFUIColorChangeR,
                              ZFMP_IN(ZFUIColor const &, c),
                              ZFMP_IN(zfuint, r))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIColor, ZFUIColorChangeG,
                              ZFMP_IN(ZFUIColor const &, c),
                              ZFMP_IN(zfuint, g))
ZFMETHOD_FUNC_DEFINE_INLINE_2(ZFUIColor, ZFUIColorChangeB,
                              ZFMP_IN(ZFUIColor const &, c),
                              ZFMP_IN(zfuint, b))

// ============================================================
ZFENUM_DEFINE(ZFUIOrientation)
ZFENUM_FLAGS_DEFINE(ZFUIOrientation, ZFUIOrientationFlags)

ZFEXPORT_VAR_READONLY_DEFINE(ZFUIOrientationFlags, ZFUIOrientationFlagsAll, (ZFUIOrientation::e_Left | ZFUIOrientation::e_Top | ZFUIOrientation::e_Right | ZFUIOrientation::e_Bottom))
ZFEXPORT_VAR_READONLY_DEFINE(ZFUIOrientationFlags, ZFUIOrientationFlagsHorizontal, (ZFUIOrientation::e_Left | ZFUIOrientation::e_Right))
ZFEXPORT_VAR_READONLY_DEFINE(ZFUIOrientationFlags, ZFUIOrientationFlagsVertical, (ZFUIOrientation::e_Top | ZFUIOrientation::e_Bottom))

ZFMETHOD_FUNC_DEFINE_INLINE_1(zfbool, ZFUIOrientationIsVertical,
                              ZFMP_IN(ZFUIOrientationEnum, orientation))
ZFMETHOD_FUNC_DEFINE_INLINE_1(zfbool, ZFUIOrientationIsHorizontal,
                              ZFMP_IN(ZFUIOrientationEnum, orientation))

ZFENUM_DEFINE(ZFUITextAppearance)

ZFENUM_DEFINE(ZFUITextTruncateMode)

// ============================================================
ZFENUM_DEFINE(ZFUIContentScaleType)

static void _ZFP_ZFUIContentScaleTypeApply_Center(ZF_OUT ZFUIRect &ret, ZF_IN const ZFUIRect &bounds, ZF_IN const ZFUISize &contentSize)
{
    ret = ZFUIAlignApply(ZFUIAlign::e_Center, bounds, contentSize);
}
static void _ZFP_ZFUIContentScaleTypeApply_FillX(ZF_OUT ZFUIRect &ret, ZF_IN const ZFUIRect &bounds, ZF_IN const ZFUISize &contentSize)
{
    ret = ZFUIAlignApply(ZFUIAlign::e_Center, bounds, ZFUISizeMake(
        bounds.size.width,
        bounds.size.width * contentSize.height / contentSize.width
        ));
}
static void _ZFP_ZFUIContentScaleTypeApply_FillY(ZF_OUT ZFUIRect &ret, ZF_IN const ZFUIRect &bounds, ZF_IN const ZFUISize &contentSize)
{
    ret = ZFUIAlignApply(ZFUIAlign::e_Center, bounds, ZFUISizeMake(
        contentSize.width * bounds.size.height / contentSize.height,
        bounds.size.height
        ));
}
static void _ZFP_ZFUIContentScaleTypeApply_FillCenter(ZF_OUT ZFUIRect &ret, ZF_IN const ZFUIRect &bounds, ZF_IN const ZFUISize &contentSize)
{
    if(contentSize.width * bounds.size.height >= bounds.size.width * contentSize.height)
    {
        _ZFP_ZFUIContentScaleTypeApply_FillX(ret, bounds, contentSize);
    }
    else
    {
        _ZFP_ZFUIContentScaleTypeApply_FillY(ret, bounds, contentSize);
    }
}
static void _ZFP_ZFUIContentScaleTypeApply_FillCenterClipped(ZF_OUT ZFUIRect &ret, ZF_IN const ZFUIRect &bounds, ZF_IN const ZFUISize &contentSize)
{
    if(contentSize.width * bounds.size.height >= bounds.size.width * contentSize.height)
    {
        _ZFP_ZFUIContentScaleTypeApply_FillY(ret, bounds, contentSize);
    }
    else
    {
        _ZFP_ZFUIContentScaleTypeApply_FillX(ret, bounds, contentSize);
    }
}
ZFMETHOD_FUNC_DEFINE_4(void, ZFUIContentScaleTypeApply,
                       ZFMP_OUT(ZFUIRect &, ret),
                       ZFMP_IN(ZFUIContentScaleTypeEnum, scaleType),
                       ZFMP_IN(const ZFUIRect &, bounds),
                       ZFMP_IN(const ZFUISize &, contentSize))
{
    switch(scaleType)
    {
        case ZFUIContentScaleType::e_Fill:
            ret = bounds;
            break;
        case ZFUIContentScaleType::e_Center:
            _ZFP_ZFUIContentScaleTypeApply_Center(ret, bounds, contentSize);
            break;
        case ZFUIContentScaleType::e_FillCenter:
            _ZFP_ZFUIContentScaleTypeApply_FillCenter(ret, bounds, contentSize);
            break;
        case ZFUIContentScaleType::e_FillCenterClipped:
            _ZFP_ZFUIContentScaleTypeApply_FillCenterClipped(ret, bounds, contentSize);
            break;
        case ZFUIContentScaleType::e_FitCenter:
            if(contentSize.width <= bounds.size.width && contentSize.height <= bounds.size.height)
            {
                _ZFP_ZFUIContentScaleTypeApply_Center(ret, bounds, contentSize);
            }
            else
            {
                _ZFP_ZFUIContentScaleTypeApply_FillCenter(ret, bounds, contentSize);
            }
            break;
        case ZFUIContentScaleType::e_FillX:
            _ZFP_ZFUIContentScaleTypeApply_FillX(ret, bounds, contentSize);
            break;
        case ZFUIContentScaleType::e_FitX:
            if(contentSize.width <= bounds.size.width)
            {
                _ZFP_ZFUIContentScaleTypeApply_Center(ret, bounds, contentSize);
            }
            else
            {
                _ZFP_ZFUIContentScaleTypeApply_FillX(ret, bounds, contentSize);
            }
            break;
        case ZFUIContentScaleType::e_FillY:
            _ZFP_ZFUIContentScaleTypeApply_FillY(ret, bounds, contentSize);
            break;
        case ZFUIContentScaleType::e_FitY:
            if(contentSize.height <= bounds.size.height)
            {
                _ZFP_ZFUIContentScaleTypeApply_Center(ret, bounds, contentSize);
            }
            else
            {
                _ZFP_ZFUIContentScaleTypeApply_FillY(ret, bounds, contentSize);
            }
            break;
        default:
            zfCoreCriticalShouldNotGoHere();
            break;
    }
}
ZFMETHOD_FUNC_DEFINE_INLINE_3(ZFUIRect, ZFUIContentScaleTypeApply,
                              ZFMP_IN(ZFUIContentScaleTypeEnum, scaleType),
                              ZFMP_IN(const ZFUIRect &, bounds),
                              ZFMP_IN(const ZFUISize &, contentSize))

ZF_NAMESPACE_GLOBAL_END

