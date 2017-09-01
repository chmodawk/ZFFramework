/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFUITypeDef.h
 * @brief necessary header file for all ZFUIKit member
 */

#ifndef _ZFI_ZFUITypeDef_h_
#define _ZFI_ZFUITypeDef_h_

#include "ZFUIKitDef.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// basic size
/**
 * @brief return a scaled int
 *
 * note, to suit most case, apply scale on 1 pixel would always result to 1 pixel
 */
ZFMETHOD_FUNC_DECLARE_3(void, ZFUISizeApplyScale,
                        ZFMP_OUT(zfint &, ret),
                        ZFMP_IN(zfint const &, v),
                        ZFMP_IN(zffloat, scale))
/**
 * @brief return a scaled int
 *
 * note, to suit most case, apply scale on 1 pixel would always result to 1 pixel
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(zfint, ZFUISizeApplyScale,
                               ZFMP_IN(zfint const &, v),
                               ZFMP_IN(zffloat, scale))
{
    zfint ret = 0;
    ZFUISizeApplyScale(ret, v, scale);
    return ret;
}
/**
 * @brief return a scaled int reversely
 *
 * note, to suit most case, apply scale on 1 pixel would always result to 1 pixel
 */
ZFMETHOD_FUNC_DECLARE_3(void, ZFUISizeApplyScaleReversely,
                        ZFMP_OUT(zfint &, ret),
                        ZFMP_IN(zfint const &, v),
                        ZFMP_IN(zffloat, scale))
/**
 * @brief return a scaled int reversely
 *
 * note, to suit most case, apply scale on 1 pixel would always result to 1 pixel
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(zfint, ZFUISizeApplyScaleReversely,
                               ZFMP_IN(zfint const &, v),
                               ZFMP_IN(zffloat, scale))
{
    zfint ret = 0;
    ZFUISizeApplyScaleReversely(ret, v, scale);
    return ret;
}

// ============================================================
// ZFUIPoint
/**
 * @brief 2D point
 */
zfclassPOD ZF_ENV_EXPORT ZFUIPoint
{
public:
    zfint x;   /**< @brief x */
    zfint y;   /**< @brief y */
};

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFUIPoint
 *       value="(0, 0)" // optional, 0 by default
 *   />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFUIPoint, ZFUIPoint)

ZFOUTPUT_TYPE(ZFUIPoint, {output << ZFUIPointToString(v);})

ZFCORE_POD_COMPARER_DECLARE(ZFUIPoint)

/**
 * @brief (0, 0)
 */
ZFEXPORT_VAR_READONLY_DECLARE(ZFUIPoint, ZFUIPointZero)

/**
 * @brief make a ZFUIPoint
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIPoint, ZFUIPointMake,
                               ZFMP_IN(zfint const &, x),
                               ZFMP_IN(zfint const &, y))
{
    ZFUIPoint ret = {x, y};
    return ret;
}

/**
 * @brief return a scaled point
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(void, ZFUIPointApplyScale,
                               ZFMP_OUT(ZFUIPoint &, ret),
                               ZFMP_IN(const ZFUIPoint &, point),
                               ZFMP_IN(zffloat, scale))
{
    ret = ZFUIPointMake(ZFUISizeApplyScale(point.x, scale), ZFUISizeApplyScale(point.y, scale));
}
/**
 * @brief return a scaled point
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIPoint, ZFUIPointApplyScale,
                               ZFMP_IN(const ZFUIPoint &, point),
                               ZFMP_IN(zffloat, scale))
{
    return ZFUIPointMake(ZFUISizeApplyScale(point.x, scale), ZFUISizeApplyScale(point.y, scale));
}
/**
 * @brief return a scaled point reversely
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(void, ZFUIPointApplyScaleReversely,
                               ZFMP_OUT(ZFUIPoint &, ret),
                               ZFMP_IN(const ZFUIPoint &, point),
                               ZFMP_IN(zffloat, scale))
{
    ret = ZFUIPointMake(ZFUISizeApplyScaleReversely(point.x, scale), ZFUISizeApplyScaleReversely(point.y, scale));
}
/**
 * @brief return a scaled point reversely
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIPoint, ZFUIPointApplyScaleReversely,
                               ZFMP_IN(const ZFUIPoint &, point),
                               ZFMP_IN(zffloat, scale))
{
    return ZFUIPointMake(ZFUISizeApplyScaleReversely(point.x, scale), ZFUISizeApplyScaleReversely(point.y, scale));
}

// ============================================================
// ZFUIMargin
/**
 * @brief margin
 */
zfclassPOD ZF_ENV_EXPORT ZFUIMargin
{
public:
    zfint left;    /**< @brief left margin */
    zfint top;     /**< @brief top margin */
    zfint right;   /**< @brief right margin */
    zfint bottom;  /**< @brief bottom margin */
};

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFUIMargin
 *       value="(0, 0, 0, 0)" // optional, 0 by default
 *   />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFUIMargin, ZFUIMargin)

ZFOUTPUT_TYPE(ZFUIMargin, {output << ZFUIMarginToString(v);})

ZFCORE_POD_COMPARER_DECLARE(ZFUIMargin)

/**
 * @brief (0, 0, 0, 0)
 */
ZFEXPORT_VAR_READONLY_DECLARE(ZFUIMargin, ZFUIMarginZero)

/**
 * @brief make a margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_4(ZFUIMargin, ZFUIMarginMake,
                               ZFMP_IN(zfint const &, left),
                               ZFMP_IN(zfint const &, top),
                               ZFMP_IN(zfint const &, right),
                               ZFMP_IN(zfint const &, bottom))
{
    ZFUIMargin ret = {left, top, right, bottom};
    return ret;
}
/**
 * @brief make a margin with all sides set to margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(ZFUIMargin, ZFUIMarginMake,
                               ZFMP_IN(zfint const &, margin))
{
    ZFUIMargin ret = {margin, margin, margin, margin};
    return ret;
}
/**
 * @brief make a margin with left/right to x and top/bottom to y
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIMargin, ZFUIMarginMake,
                               ZFMP_IN(zfint const &, x),
                               ZFMP_IN(zfint const &, y))
{
    ZFUIMargin ret = {x, y, x, y};
    return ret;
}

/**
 * @brief return a scaled margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(void, ZFUIMarginApplyScale,
                               ZFMP_OUT(ZFUIMargin &, ret),
                               ZFMP_IN(const ZFUIMargin &, margin),
                               ZFMP_IN(zffloat, scale))
{
    ret = ZFUIMarginMake(
        ZFUISizeApplyScale(margin.left, scale),
        ZFUISizeApplyScale(margin.top, scale),
        ZFUISizeApplyScale(margin.right, scale),
        ZFUISizeApplyScale(margin.bottom, scale)
        );
}
/**
 * @brief return a scaled margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIMargin, ZFUIMarginApplyScale,
                               ZFMP_IN(const ZFUIMargin &, margin),
                               ZFMP_IN(zffloat, scale))
{
    return ZFUIMarginMake(
        ZFUISizeApplyScale(margin.left, scale),
        ZFUISizeApplyScale(margin.top, scale),
        ZFUISizeApplyScale(margin.right, scale),
        ZFUISizeApplyScale(margin.bottom, scale)
        );
}
/**
 * @brief return a scaled margin reversely
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(void, ZFUIMarginApplyScaleReversely,
                               ZFMP_OUT(ZFUIMargin &, ret),
                               ZFMP_IN(const ZFUIMargin &, margin),
                               ZFMP_IN(zffloat, scale))
{
    ret = ZFUIMarginMake(ZFUISizeApplyScaleReversely(margin.left, scale),
        ZFUISizeApplyScaleReversely(margin.top, scale),
        ZFUISizeApplyScaleReversely(margin.right, scale),
        ZFUISizeApplyScaleReversely(margin.bottom, scale));
}
/**
 * @brief return a scaled margin reversely
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIMargin, ZFUIMarginApplyScaleReversely,
                               ZFMP_IN(const ZFUIMargin &, margin),
                               ZFMP_IN(zffloat, scale))
{
    return ZFUIMarginMake(ZFUISizeApplyScaleReversely(margin.left, scale),
        ZFUISizeApplyScaleReversely(margin.top, scale),
        ZFUISizeApplyScaleReversely(margin.right, scale),
        ZFUISizeApplyScaleReversely(margin.bottom, scale));
}
/**
 * @brief left + right margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(zfint, ZFUIMarginGetX,
                               ZFMP_IN(const ZFUIMargin &, margin))
{
    return margin.left + margin.right;
}
/**
 * @brief top + bottom margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(zfint, ZFUIMarginGetY,
                               ZFMP_IN(const ZFUIMargin &, margin))
{
    return margin.top + margin.bottom;
}
/**
 * @brief v0 + v1
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(void, ZFUIMarginInc,
                               ZFMP_IN_OUT(ZFUIMargin &, ret),
                               ZFMP_IN(const ZFUIMargin &, v0),
                               ZFMP_IN(const ZFUIMargin &, v1))
{
    ret.left = v0.left + v1.left;
    ret.top = v0.top + v1.top;
    ret.right = v0.right + v1.right;
    ret.bottom = v0.bottom + v1.bottom;
}
/**
 * @brief v0 + v1
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIMargin, ZFUIMarginInc,
                               ZFMP_IN(const ZFUIMargin &, v0),
                               ZFMP_IN(const ZFUIMargin &, v1))
{
    ZFUIMargin ret;
    ZFUIMarginInc(ret, v0, v1);
    return ret;
}
/**
 * @brief v0 + v1
 */
inline ZFUIMargin operator + (ZF_IN const ZFUIMargin &v0,
                              ZF_IN const ZFUIMargin &v1)
{
    return ZFUIMarginInc(v0, v1);
}
/**
 * @brief v0 += v1
 */
inline ZFUIMargin &operator += (ZF_IN_OUT ZFUIMargin &v0,
                                ZF_IN const ZFUIMargin &v1)
{
    v0.left += v1.left;
    v0.top += v1.top;
    v0.right += v1.right;
    v0.bottom += v1.bottom;
    return v0;
}
/**
 * @brief v0 - v1
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(void, ZFUIMarginDec,
                               ZFMP_IN_OUT(ZFUIMargin &, ret),
                               ZFMP_IN(const ZFUIMargin &, v0),
                               ZFMP_IN(const ZFUIMargin &, v1))
{
    ret.left = v0.left - v1.left;
    ret.top = v0.top - v1.top;
    ret.right = v0.right - v1.right;
    ret.bottom = v0.bottom - v1.bottom;
}
/**
 * @brief v0 - v1
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIMargin, ZFUIMarginDec,
                               ZFMP_IN(const ZFUIMargin &, v0),
                               ZFMP_IN(const ZFUIMargin &, v1))
{
    ZFUIMargin ret;
    ZFUIMarginDec(ret, v0, v1);
    return ret;
}
/**
 * @brief v0 - v1
 */
inline ZFUIMargin operator - (ZF_IN const ZFUIMargin &v0,
                              ZF_IN const ZFUIMargin &v1)
{
    return ZFUIMarginDec(v0, v1);
}
/**
 * @brief v0 -= v1
 */
inline ZFUIMargin &operator -= (ZF_IN_OUT ZFUIMargin &v0,
                                ZF_IN const ZFUIMargin &v1)
{
    v0.left -= v1.left;
    v0.top -= v1.top;
    v0.right -= v1.right;
    v0.bottom -= v1.bottom;
    return v0;
}

// ============================================================
// ZFUISize
/**
 * @brief 2D size
 */
zfclassPOD ZF_ENV_EXPORT ZFUISize
{
public:
    zfint width;   /**< @brief width */
    zfint height;  /**< @brief height */
};

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFUISize
 *       value="(0, 0)" // optional, 0 by default
 *   />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFUISize, ZFUISize)

ZFOUTPUT_TYPE(ZFUISize, {output << ZFUISizeToString(v);})

ZFCORE_POD_COMPARER_DECLARE(ZFUISize)

/**
 * @brief (0, 0)
 */
ZFEXPORT_VAR_READONLY_DECLARE(ZFUISize, ZFUISizeZero)
/**
 * @brief (-1, -1)
 *
 * since zero size is valid on some cases,
 * we supply -1 as special size to indicate an invalid size
 */
ZFEXPORT_VAR_READONLY_DECLARE(ZFUISize, ZFUISizeInvalid)

/**
 * @brief make a ZFUISize
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUISize, ZFUISizeMake,
                               ZFMP_IN(zfint const &, width),
                               ZFMP_IN(zfint const &, height))
{
    ZFUISize ret = {width, height};
    return ret;
}
/**
 * @brief make a ZFUISize
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(ZFUISize, ZFUISizeMake,
                               ZFMP_IN(zfint const &, v))
{
    ZFUISize ret = {v, v};
    return ret;
}

/**
 * @brief check and apply size range
 *
 * return value in range [minSize, maxSize] if minSize < maxSize,
 * or return value in range [minSize, infinite) minSize > maxSize
 */
ZFMETHOD_FUNC_DECLARE_INLINE_4(void, ZFUISizeApplyRange,
                               ZFMP_OUT(ZFUISize &, ret),
                               ZFMP_IN(const ZFUISize &, orgSize),
                               ZFMP_IN(const ZFUISize &, minSize),
                               ZFMP_IN(const ZFUISize &, maxSize))
{
    ret.width = zfmApplyRange(orgSize.width, minSize.width, maxSize.width);
    ret.height = zfmApplyRange(orgSize.height, minSize.height, maxSize.height);
}
/**
 * @brief check and apply size range
 *
 * return value in range [minSize, maxSize] if minSize < maxSize,
 * or return value in range [minSize, infinite) minSize > maxSize
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(ZFUISize, ZFUISizeApplyRange,
                               ZFMP_IN(const ZFUISize &, orgSize),
                               ZFMP_IN(const ZFUISize &, minSize),
                               ZFMP_IN(const ZFUISize &, maxSize))
{
    return ZFUISizeMake(
        zfmApplyRange(orgSize.width, minSize.width, maxSize.width),
        zfmApplyRange(orgSize.height, minSize.height, maxSize.height)
    );
}
/**
 * @brief return a scaled size
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(void, ZFUISizeApplyScale,
                               ZFMP_OUT(ZFUISize &, ret),
                               ZFMP_IN(const ZFUISize &, size),
                               ZFMP_IN(zffloat, scale))
{
    ret = ZFUISizeMake(ZFUISizeApplyScale(size.width, scale), ZFUISizeApplyScale(size.height, scale));
}
/**
 * @brief return a scaled size
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUISize, ZFUISizeApplyScale,
                               ZFMP_IN(const ZFUISize &, size),
                               ZFMP_IN(zffloat, scale))
{
    return ZFUISizeMake(ZFUISizeApplyScale(size.width, scale), ZFUISizeApplyScale(size.height, scale));
}
/**
 * @brief return a scaled size reversely
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(void, ZFUISizeApplyScaleReversely,
                               ZFMP_OUT(ZFUISize &, ret),
                               ZFMP_IN(const ZFUISize &, size),
                               ZFMP_IN(zffloat, scale))
{
    ret = ZFUISizeMake(ZFUISizeApplyScaleReversely(size.width, scale), ZFUISizeApplyScaleReversely(size.height, scale));
}
/**
 * @brief return a scaled size reversely
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUISize, ZFUISizeApplyScaleReversely,
                               ZFMP_IN(const ZFUISize &, size),
                               ZFMP_IN(zffloat, scale))
{
    return ZFUISizeMake(ZFUISizeApplyScaleReversely(size.width, scale), ZFUISizeApplyScaleReversely(size.height, scale));
}

/**
 * @brief scale size to fit refSize and keep aspect ratio
 *
 * input size must be valid, while negative refSize means no limit
 */
ZFMETHOD_FUNC_DECLARE_3(void, ZFUISizeApplyAspectRatio,
                        ZFMP_OUT(ZFUISize &, ret),
                        ZFMP_IN(const ZFUISize &, size),
                        ZFMP_IN(const ZFUISize &, refSize))
/**
 * @brief scale size to fit refSize and keep aspect ratio
 *
 * input size must be valid, while negative refSize means no limit
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUISize, ZFUISizeApplyAspectRatio,
                               ZFMP_IN(const ZFUISize &, size),
                               ZFMP_IN(const ZFUISize &, refSize))
{
    ZFUISize ret = ZFUISizeZero();
    ZFUISizeApplyAspectRatio(ret, size, refSize);
    return ret;
}

/**
 * @brief return a size excluding the margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(void, ZFUISizeApplyMargin,
                               ZFMP_OUT(ZFUISize &, ret),
                               ZFMP_IN(const ZFUISize &, size),
                               ZFMP_IN(const ZFUIMargin &, margin))
{
    ret = ZFUISizeMake(
        size.width - margin.left - margin.right,
        size.height - margin.top - margin.bottom);
}
/**
 * @brief return a size excluding the margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUISize, ZFUISizeApplyMargin,
                               ZFMP_IN(const ZFUISize &, size),
                               ZFMP_IN(const ZFUIMargin &, margin))
{
    return ZFUISizeMake(
        size.width - margin.left - margin.right,
        size.height - margin.top - margin.bottom);
}
/**
 * @brief revert excluding the margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(void, ZFUISizeApplyMarginReversely,
                               ZFMP_OUT(ZFUISize &, ret),
                               ZFMP_IN(const ZFUISize &, size),
                               ZFMP_IN(const ZFUIMargin &, margin))
{
    ret = ZFUISizeMake(
        size.width + margin.left + margin.right,
        size.height + margin.top + margin.bottom);
}
/**
 * @brief revert excluding the margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUISize, ZFUISizeApplyMarginReversely,
                               ZFMP_IN(const ZFUISize &, size),
                               ZFMP_IN(const ZFUIMargin &, margin))
{
    return ZFUISizeMake(
        size.width + margin.left + margin.right,
        size.height + margin.top + margin.bottom);
}

// ============================================================
// ZFUIRect
/**
 * @brief 2D rectangle
 */
zfclassPOD ZF_ENV_EXPORT ZFUIRect
{
public:
    ZFUIPoint point;      /**< @brief top-left point */
    ZFUISize size;        /**< @brief size of rect */
};

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFUIRect
 *       value="(0, 0, 0, 0)" // optional, 0 by default
 *   />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFUIRect, ZFUIRect)

ZFOUTPUT_TYPE(ZFUIRect, {output << ZFUIRectToString(v);})

ZFCORE_POD_COMPARER_DECLARE(ZFUIRect)

/**
 * @brief (0, 0, 0, 0)
 */
ZFEXPORT_VAR_READONLY_DECLARE(ZFUIRect, ZFUIRectZero)

/**
 * @brief make a ZFUIRect
 */
ZFMETHOD_FUNC_DECLARE_INLINE_4(ZFUIRect, ZFUIRectMake,
                               ZFMP_IN(zfint const &, x),
                               ZFMP_IN(zfint const &, y),
                               ZFMP_IN(zfint const &, w),
                               ZFMP_IN(zfint const &, h))
{
    ZFUIRect ret = {{x, y}, {w, h}};
    return ret;
}
/**
 * @brief make a ZFUIRect
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIRect, ZFUIRectMake,
                               ZFMP_IN(const ZFUIPoint &, point),
                               ZFMP_IN(const ZFUISize &, size))
{
    ZFUIRect ret = {point, size};
    return ret;
}

/**
 * @brief is rect empty
 *
 * rect is empty if width or height <= 0
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(zfbool, ZFUIRectIsEmpty,
                               ZFMP_IN(const ZFUIRect &, rect))
{
    return (rect.size.width <= 0 || rect.size.height <= 0);
}
/**
 * @brief union two rect, return a rect that contains both rect1 and rect2
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIRect, ZFUIRectUnion,
                               ZFMP_IN(const ZFUIRect &, rect1),
                               ZFMP_IN(const ZFUIRect &, rect2))
{
    ZFUIRect ret = {
        {(rect1.point.x < rect2.point.x) ? rect1.point.x : rect2.point.x,
        (rect1.point.y < rect2.point.y) ? rect1.point.y : rect2.point.y},
        {(rect1.point.x + rect1.size.width > rect2.point.x + rect2.size.width)
            ? (rect1.point.x + rect1.size.width)
            : (rect2.point.x + rect2.size.width),
        (rect1.point.y + rect1.size.height > rect2.point.y + rect2.size.height)
            ? (rect1.point.y + rect1.size.height)
            : (rect2.point.y + rect2.size.height)}
    };
    if(ZFUIRectIsEmpty(ret))
    {
        return ZFUIRectZero();
    }
    return ret;
}
/**
 * @brief intersect two rect, return #ZFUIRectZero if not intersected
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIRect, ZFUIRectIntersection,
                               ZFMP_IN(const ZFUIRect &, rect1),
                               ZFMP_IN(const ZFUIRect &, rect2))
{
    ZFUIRect ret = {
        {(rect1.point.x > rect2.point.x) ? rect1.point.x : rect2.point.x,
        (rect1.point.y > rect2.point.y) ? rect1.point.y : rect2.point.y},
        {(rect1.point.x + rect1.size.width < rect2.point.x + rect2.size.width)
            ? (rect1.point.x + rect1.size.width)
            : (rect2.point.x + rect2.size.width),
        (rect1.point.y + rect1.size.height < rect2.point.y + rect2.size.height)
            ? (rect1.point.y + rect1.size.height)
            : (rect2.point.y + rect2.size.height)}
    };
    if(ZFUIRectIsEmpty(ret))
    {
        return ZFUIRectZero();
    }
    return ret;
}
/**
 * @brief is two rect intersected,
 *   two tangented rect is not intersected
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(zfbool, ZFUIRectIsIntersectToRect,
                               ZFMP_IN(const ZFUIRect &, rect1),
                               ZFMP_IN(const ZFUIRect &, rect2))
{
    return !ZFUIRectIsEmpty(ZFUIRectIntersection(rect1, rect2));
}
/**
 * @brief is rect contains point
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(zfbool, ZFUIRectIsContainPoint,
                               ZFMP_IN(const ZFUIRect &, rect),
                               ZFMP_IN(const ZFUIPoint &, point))
{
    return (point.x >= rect.point.x
        && point.x <= rect.point.x + rect.size.width
        && point.y >= rect.point.y
        && point.y <= rect.point.y + rect.size.height);
}
/**
 * @brief see #ZFUIRectIsContainPoint
 *
 * if margin is positive, rect's area is reduced by margin,
 * if margin is negative, rect's area is increased by margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(zfbool, ZFUIRectIsContainPoint,
                               ZFMP_IN(const ZFUIRect &, rect),
                               ZFMP_IN(const ZFUIPoint &, point),
                               ZFMP_IN(const ZFUIMargin &, margin))
{
    return (point.x >= rect.point.x + margin.left
        && point.x <= rect.point.x + rect.size.width - margin.right
        && point.y >= rect.point.y + margin.top
        && point.y <= rect.point.y + rect.size.height - margin.bottom);
}
/**
 * @brief return true if rect2 is completely contained by rect1,
 *   two equal rect is regarded as contain each other
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(zfbool, ZFUIRectIsContainRect,
                               ZFMP_IN(const ZFUIRect &, rect1),
                               ZFMP_IN(const ZFUIRect &, rect2))
{
    return (rect2.point.x >= rect1.point.x
        && rect2.point.x + rect2.size.width <= rect1.point.x + rect1.size.width
        && rect2.point.y >= rect1.point.y
        && rect2.point.y + rect2.size.height <= rect1.point.y + rect1.size.height);
}
/**
 * @brief see #ZFUIRectIsContainRect
 *
 * if margin is positive, rect's area is reduced by margin,
 * if margin is negative, rect's area is increased by margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(zfbool, ZFUIRectIsContainRect,
                               ZFMP_IN(const ZFUIRect &, rect1),
                               ZFMP_IN(const ZFUIRect &, rect2),
                               ZFMP_IN(const ZFUIMargin &, margin))
{
    return (rect2.point.x >= rect1.point.x + margin.left
        && rect2.point.x + rect2.size.width <= rect1.point.x + rect1.size.width - margin.right
        && rect2.point.y >= rect1.point.y + margin.top
        && rect2.point.y + rect2.size.height <= rect1.point.y + rect1.size.height - margin.bottom);
}
/**
 * @brief return a scaled rect
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(void, ZFUIRectApplyScale,
                               ZFMP_OUT(ZFUIRect &, ret),
                               ZFMP_IN(const ZFUIRect &, rect),
                               ZFMP_IN(zffloat, scale))
{
    ret = ZFUIRectMake(ZFUISizeApplyScale(rect.point.x, scale),
        ZFUISizeApplyScale(rect.point.y, scale),
        ZFUISizeApplyScale(rect.size.width, scale),
        ZFUISizeApplyScale(rect.size.height, scale));
}
/**
 * @brief return a scaled rect
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIRect, ZFUIRectApplyScale,
                               ZFMP_IN(const ZFUIRect &, rect),
                               ZFMP_IN(zffloat, scale))
{
    return ZFUIRectMake(ZFUISizeApplyScale(rect.point.x, scale),
        ZFUISizeApplyScale(rect.point.y, scale),
        ZFUISizeApplyScale(rect.size.width, scale),
        ZFUISizeApplyScale(rect.size.height, scale));
}
/**
 * @brief return a scaled rect reversely
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(void, ZFUIRectApplyScaleReversely,
                               ZFMP_OUT(ZFUIRect &, ret),
                               ZFMP_IN(const ZFUIRect &, rect),
                               ZFMP_IN(zffloat, scale))
{
    ret = ZFUIRectMake(
        ZFUISizeApplyScaleReversely(rect.point.x, scale),
        ZFUISizeApplyScaleReversely(rect.point.y, scale),
        ZFUISizeApplyScaleReversely(rect.size.width, scale),
        ZFUISizeApplyScaleReversely(rect.size.height, scale)
        );
}
/**
 * @brief return a scaled rect reversely
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIRect, ZFUIRectApplyScaleReversely,
                               ZFMP_IN(const ZFUIRect &, rect),
                               ZFMP_IN(zffloat, scale))
{
    return ZFUIRectMake(
        ZFUISizeApplyScaleReversely(rect.point.x, scale),
        ZFUISizeApplyScaleReversely(rect.point.y, scale),
        ZFUISizeApplyScaleReversely(rect.size.width, scale),
        ZFUISizeApplyScaleReversely(rect.size.height, scale)
        );
}
/**
 * @brief get bounds for rect, i.e. (0, 0, width, height)
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(ZFUIRect, ZFUIRectGetBounds,
                               ZFMP_IN(const ZFUIRect &, rect))
{
    return ZFUIRectMake(0, 0, rect.size.width, rect.size.height);
}
/**
 * @brief get center point of the rect
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(ZFUIPoint, ZFUIRectGetCenter,
                               ZFMP_IN(const ZFUIRect &, rect))
{
    return ZFUIPointMake(rect.point.x + rect.size.width / 2, rect.point.y + rect.size.height / 2);
}
/**
 * @brief get left edge of the rect
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(zfint, ZFUIRectGetLeft,
                               ZFMP_IN(const ZFUIRect &, rect))
{
    return rect.point.x;
}
/**
 * @brief get top edge of the rect
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(zfint, ZFUIRectGetTop,
                               ZFMP_IN(const ZFUIRect &, rect))
{
    return rect.point.y;
}
/**
 * @brief get right edge of the rect
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(zfint, ZFUIRectGetRight,
                               ZFMP_IN(const ZFUIRect &, rect))
{
    return (rect.point.x + rect.size.width);
}
/**
 * @brief get bottom edge of the rect
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(zfint, ZFUIRectGetBottom,
                               ZFMP_IN(const ZFUIRect &, rect))
{
    return (rect.point.y + rect.size.height);
}

/**
 * @brief return a rect excluding the margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(void, ZFUIRectApplyMargin,
                               ZFMP_OUT(ZFUIRect &, ret),
                               ZFMP_IN(const ZFUIRect &, rect),
                               ZFMP_IN(const ZFUIMargin &, margin))
{
    ret = ZFUIRectMake(
        rect.point.x + margin.left,
        rect.point.y + margin.top,
        rect.size.width - margin.left - margin.right,
        rect.size.height - margin.top - margin.bottom);
}
/**
 * @brief return a rect excluding the margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIRect, ZFUIRectApplyMargin,
                               ZFMP_IN(const ZFUIRect &, rect),
                               ZFMP_IN(const ZFUIMargin &, margin))
{
    return ZFUIRectMake(
        rect.point.x + margin.left,
        rect.point.y + margin.top,
        rect.size.width - margin.left - margin.right,
        rect.size.height - margin.top - margin.bottom);
}
/**
 * @brief revert excluding the margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(void, ZFUIRectApplyMarginReversely,
                               ZFMP_OUT(ZFUIRect &, ret),
                               ZFMP_IN(const ZFUIRect &, rect),
                               ZFMP_IN(const ZFUIMargin &, margin))
{
    ret = ZFUIRectMake(
        rect.point.x - margin.left,
        rect.point.y - margin.top,
        rect.size.width + margin.left + margin.right,
        rect.size.height + margin.top + margin.bottom);
}
/**
 * @brief revert excluding the margin
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIRect, ZFUIRectApplyMarginReversely,
                               ZFMP_IN(const ZFUIRect &, rect),
                               ZFMP_IN(const ZFUIMargin &, margin))
{
    return ZFUIRectMake(
        rect.point.x - margin.left,
        rect.point.y - margin.top,
        rect.size.width + margin.left + margin.right,
        rect.size.height + margin.top + margin.bottom);
}

// ============================================================
// ZFUIAlignFlags
/**
 * @brief align types for UI in ZFFramework
 * @see ZFUIAlignFlags
 */
ZFENUM_BEGIN(ZFUIAlign)
    ZFENUM_VALUE_WITH_INIT(Center, 0) /**< @brief ensured 0 */
    ZFENUM_VALUE_WITH_INIT(Left, 1)
    ZFENUM_VALUE_WITH_INIT(LeftInner, 2)
    ZFENUM_VALUE_WITH_INIT(Top, 4)
    ZFENUM_VALUE_WITH_INIT(TopInner, 8)
    ZFENUM_VALUE_WITH_INIT(Right, 16)
    ZFENUM_VALUE_WITH_INIT(RightInner, 32)
    ZFENUM_VALUE_WITH_INIT(Bottom, 64)
    ZFENUM_VALUE_WITH_INIT(BottomInner, 128)
ZFENUM_SEPARATOR(ZFUIAlign)
    ZFENUM_VALUE_REGISTER(Center)
    ZFENUM_VALUE_REGISTER(Left)
    ZFENUM_VALUE_REGISTER(LeftInner)
    ZFENUM_VALUE_REGISTER(Top)
    ZFENUM_VALUE_REGISTER(TopInner)
    ZFENUM_VALUE_REGISTER(Right)
    ZFENUM_VALUE_REGISTER(RightInner)
    ZFENUM_VALUE_REGISTER(Bottom)
    ZFENUM_VALUE_REGISTER(BottomInner)
ZFENUM_END(ZFUIAlign)

ZFENUM_FLAGS_DECLARE(ZFUIAlign, ZFUIAlignFlags)

/**
 * @brief true if align is valid
 *
 * a align is valid only if:
 * -  only bits in #ZFUIAlign are set
 * -  x or y align type must not conflict, i.e.
 *   "Left, LeftInner, Right, RightInner" could only exist at most one,
 *   "Top, TopInner, Bottom, BottomInner" could only exist at most one
 */
ZFMETHOD_FUNC_DECLARE_1(zfbool, ZFUIAlignIsValid,
                        ZFMP_IN(const ZFUIAlignFlags &, align))
/**
 * @brief apply align and calculate result, or #ZFUIRectZero if error
 */
ZFMETHOD_FUNC_DECLARE_5(void, ZFUIAlignApply,
                        ZFMP_OUT(ZFUIRect &, ret),
                        ZFMP_IN(const ZFUIAlignFlags &, align),
                        ZFMP_IN(const ZFUIRect &, refRect),
                        ZFMP_IN(const ZFUISize &, itemSize),
                        ZFMP_IN_OPT(const ZFUIMargin &, margin, ZFUIMarginZero()))
/**
 * @brief apply align and calculate result, or #ZFUIRectZero if error
 */
ZFMETHOD_FUNC_DECLARE_INLINE_4(ZFUIRect, ZFUIAlignApply,
                               ZFMP_IN(const ZFUIAlignFlags &, align),
                               ZFMP_IN(const ZFUIRect &, refRect),
                               ZFMP_IN(const ZFUISize &, itemSize),
                               ZFMP_IN_OPT(const ZFUIMargin &, margin, ZFUIMarginZero()))
{
    ZFUIRect ret = ZFUIRectZero();
    ZFUIAlignApply(ret, align, refRect, itemSize, margin);
    return ret;
}
/**
 * @brief get horizontal align or #ZFUIAlign::e_Center if invalid
 */
ZFMETHOD_FUNC_DECLARE_1(ZFUIAlignEnum, ZFUIAlignGetX,
                        ZFMP_IN(const ZFUIAlignFlags &, align))
/**
 * @brief get vertical align or #ZFUIAlign::e_Center if invalid
 */
ZFMETHOD_FUNC_DECLARE_1(ZFUIAlignEnum, ZFUIAlignGetY,
                        ZFMP_IN(const ZFUIAlignFlags &, align))

// ============================================================
// ZFUIOrientation
/**
 * @brief orientation types for UI in ZFFramework
 *
 * for example, for a mobile phone,
 * Top means user hold the phone normally,
 * Left means user rotate the phone 90 degrees counter clockwise,
 * Right means user rotate the phone 90 degrees clockwise,
 * and Bottom means user rotate the phone 180 degrees
 */
ZFENUM_BEGIN(ZFUIOrientation)
    ZFENUM_VALUE_WITH_INIT(Left, 1)
    ZFENUM_VALUE_WITH_INIT(Top, 2)
    ZFENUM_VALUE_WITH_INIT(Right, 4)
    ZFENUM_VALUE_WITH_INIT(Bottom, 8)
ZFENUM_SEPARATOR(ZFUIOrientation)
    ZFENUM_VALUE_REGISTER(Left)
    ZFENUM_VALUE_REGISTER(Top)
    ZFENUM_VALUE_REGISTER(Right)
    ZFENUM_VALUE_REGISTER(Bottom)
ZFENUM_END(ZFUIOrientation)

ZFENUM_FLAGS_DECLARE(ZFUIOrientation, ZFUIOrientationFlags)

/** @brief (ZFUIOrientation::e_Left | ZFUIOrientation::e_Top | ZFUIOrientation::e_Right | ZFUIOrientation::e_Bottom) */
ZFEXPORT_VAR_READONLY_DECLARE(ZFUIOrientationFlags, ZFUIOrientationFlagsAll)
/** @brief (ZFUIOrientation::e_Left | ZFUIOrientation::e_Right) */
ZFEXPORT_VAR_READONLY_DECLARE(ZFUIOrientationFlags, ZFUIOrientationFlagsHorizontal)
/** @brief (ZFUIOrientation::e_Top | ZFUIOrientation::e_Bottom) */
ZFEXPORT_VAR_READONLY_DECLARE(ZFUIOrientationFlags, ZFUIOrientationFlagsVertical)

/**
 * @brief true if vertical orientation
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(zfbool, ZFUIOrientationIsVertical,
                               ZFMP_IN(ZFUIOrientationEnum, orientation))
{
    return (orientation == ZFUIOrientation::e_Top || orientation == ZFUIOrientation::e_Bottom);
}
/**
 * @brief true if vertical orientation
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(zfbool, ZFUIOrientationIsHorizontal,
                               ZFMP_IN(ZFUIOrientationEnum, orientation))
{
    return (orientation == ZFUIOrientation::e_Left || orientation == ZFUIOrientation::e_Right);
}

// ============================================================
// ZFUIColor
/**
 * @brief 32 bit color with (AARRGGBB) format
 */
ZFT_INT_STRONG_WITH_BIT(zft_zfuint32, ZFUIColor)

/** @brief 0x00000000 */
ZFEXPORT_VAR_READONLY_DECLARE(ZFUIColor, ZFUIColorZero)

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFUIColor
 *       value="value" // optional, 0 by default
 *   />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFUIColor, ZFUIColor)

ZFOUTPUT_TYPE(ZFUIColor, {output << ZFUIColorToString(v);})

/**
 * @brief true if two color is equal
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(zfbool, ZFUIColorIsEqual,
                               ZFMP_IN(ZFUIColor const &, v0),
                               ZFMP_IN(ZFUIColor const &, v1))
{
    return (v0 == v1);
}

/**
 * @brief make a color
 */
ZFMETHOD_FUNC_DECLARE_INLINE_4(ZFUIColor, ZFUIColorMake,
                               ZFMP_IN(zfuint, a),
                               ZFMP_IN(zfuint, r),
                               ZFMP_IN(zfuint, g),
                               ZFMP_IN(zfuint, b))
{
    return ZFUIColor(((a & 0xFF) << 24) | ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

/**
 * @brief get alpha from a #ZFUIColor as zfuint
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(zfuint, ZFUIColorGetA,
                               ZFMP_IN(ZFUIColor const &, c))
{
    return (zfuint)((c >> 24) & 0xFF);
}
/**
 * @brief get red from a #ZFUIColor as zfuint
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(zfuint, ZFUIColorGetR,
                               ZFMP_IN(ZFUIColor const &, c))
{
    return (zfuint)((c >> 16) & 0xFF);
}
/**
 * @brief get green from a #ZFUIColor as zfuint
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(zfuint, ZFUIColorGetG,
                               ZFMP_IN(ZFUIColor const &, c))
{
    return (zfuint)((c >> 8) & 0xFF);
}
/**
 * @brief get blue from a #ZFUIColor as zfuint
 */
ZFMETHOD_FUNC_DECLARE_INLINE_1(zfuint, ZFUIColorGetB,
                               ZFMP_IN(ZFUIColor const &, c))
{
    return (zfuint)(c & 0xFF);
}

/**
 * @brief set alpha to a #ZFUIColor
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIColor &, ZFUIColorSetA,
                               ZFMP_IN_OUT(ZFUIColor &, c),
                               ZFMP_IN(zfuint, a))
{
    c = (zft_zfuint32)((c & 0x00FFFFFF) | ((a & 0xFF) << 24));
    return c;
}
/**
 * @brief set red from a #ZFUIColor
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIColor &, ZFUIColorSetR,
                               ZFMP_IN_OUT(ZFUIColor &, c),
                               ZFMP_IN(zfuint, r))
{
    c = (zft_zfuint32)((c & 0xFF00FFFF) | ((r & 0xFF) << 16));
    return c;
}
/**
 * @brief set green from a #ZFUIColor
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIColor &, ZFUIColorSetG,
                               ZFMP_IN_OUT(ZFUIColor &, c),
                               ZFMP_IN(zfuint, g))
{
    c = (zft_zfuint32)((c & 0xFFFF00FF) | ((g & 0xFF) << 8));
    return c;
}
/**
 * @brief set blue from a #ZFUIColor
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIColor &, ZFUIColorSetB,
                               ZFMP_IN_OUT(ZFUIColor &, c),
                               ZFMP_IN(zfuint, b))
{
    c = (zft_zfuint32)((c & 0xFFFFFF00) | (b & 0xFF));
    return c;
}

/**
 * @brief return a copy of color with changed alpha
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIColor, ZFUIColorChangeA,
                               ZFMP_IN(ZFUIColor const &, c),
                               ZFMP_IN(zfuint, a))
{
    return ZFUIColor((c & 0x00FFFFFF) | ((a & 0xFF) << 24));
}
/**
 * @brief return a copy of color with changed red
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIColor, ZFUIColorChangeR,
                               ZFMP_IN(ZFUIColor const &, c),
                               ZFMP_IN(zfuint, r))
{
    return ZFUIColor((c & 0xFF00FFFF) | ((r & 0xFF) << 16));
}
/**
 * @brief return a copy of color with changed green
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIColor, ZFUIColorChangeG,
                               ZFMP_IN(ZFUIColor const &, c),
                               ZFMP_IN(zfuint, g))
{
    return ZFUIColor((c & 0xFFFF00FF) | ((g & 0xFF) << 8));
}
/**
 * @brief return a copy of color with changed blue
 */
ZFMETHOD_FUNC_DECLARE_INLINE_2(ZFUIColor, ZFUIColorChangeB,
                               ZFMP_IN(ZFUIColor const &, c),
                               ZFMP_IN(zfuint, b))
{
    return ZFUIColor((c & 0xFFFFFF00) | (b & 0xFF));
}

// ============================================================
// ZFUITextAppearance
/**
 * @brief text appearance type, normal, bold or italic
 */
ZFENUM_BEGIN(ZFUITextAppearance)
    ZFENUM_VALUE(Normal) /**< @brief normal */
    ZFENUM_VALUE(Bold) /**< @brief bold */
    ZFENUM_VALUE(Italic) /**< @brief italic */
    ZFENUM_VALUE(BoldItalic) /**< @brief bold and italic */
ZFENUM_SEPARATOR(ZFUITextAppearance)
    ZFENUM_VALUE_REGISTER(Normal)
    ZFENUM_VALUE_REGISTER(Bold)
    ZFENUM_VALUE_REGISTER(Italic)
    ZFENUM_VALUE_REGISTER(BoldItalic)
ZFENUM_END_WITH_DEFAULT(ZFUITextAppearance, Normal)

// ============================================================
// ZFUITextTruncateMode
/**
 * @brief text truncate mode
 */
ZFENUM_BEGIN(ZFUITextTruncateMode)
    ZFENUM_VALUE(Disable) /**< @brief never truncate */
    ZFENUM_VALUE(Head) /**< @brief truncate at head */
    ZFENUM_VALUE(Middle) /**< @brief truncate at middle */
    ZFENUM_VALUE(Tail) /**< @brief truncate at end */
ZFENUM_SEPARATOR(ZFUITextTruncateMode)
    ZFENUM_VALUE_REGISTER(Disable)
    ZFENUM_VALUE_REGISTER(Head)
    ZFENUM_VALUE_REGISTER(Middle)
    ZFENUM_VALUE_REGISTER(Tail)
ZFENUM_END_WITH_DEFAULT(ZFUITextTruncateMode, Disable)

// ============================================================
/**
 * @brief scale type when stretch items
 */
ZFENUM_BEGIN(ZFUIContentScaleType)
    /**
     * @brief simply fill to parent
     */
    ZFENUM_VALUE(Fill = 0)
    /**
     * @brief simply center the content without scale,
     *   may clip if content too large
     */
    ZFENUM_VALUE(Center)
    /**
     * @brief always keep aspect ratio and fill to min bounds,
     *   may leave blank area if aspect ratio differs from parent
     */
    ZFENUM_VALUE(FillCenter)
    /**
     * @brief always keep aspect ratio and fill to max bounds,
     *   may clip if aspect ratio differs from parent
     */
    ZFENUM_VALUE(FillCenterClipped)
    /**
     * @brief same as #e_Center if content not exceeds parent,
     *   same as #e_FillCenter if content exceeds parent
     */
    ZFENUM_VALUE(FitCenter)
    /**
     * @brief always fill x, may clip or leave blank if aspect ratio differs from parent
     */
    ZFENUM_VALUE(FillX)
    /**
     * @brief same as #e_Center if x not exceeds parent,
     *   same as #e_FillX if x exceeds parent
     */
    ZFENUM_VALUE(FitX)
    /**
     * @brief always fill y, may clip or leave blank if aspect ratio differs from parent
     */
    ZFENUM_VALUE(FillY)
    /**
     * @brief same as #e_Center if y not exceeds parent,
     *   same as #e_FillY if y exceeds parent
     */
    ZFENUM_VALUE(FitY)
ZFENUM_SEPARATOR(ZFUIContentScaleType)
    ZFENUM_VALUE_REGISTER(Fill)
    ZFENUM_VALUE_REGISTER(Center)
    ZFENUM_VALUE_REGISTER(FillCenter)
    ZFENUM_VALUE_REGISTER(FillCenterClipped)
    ZFENUM_VALUE_REGISTER(FitCenter)
    ZFENUM_VALUE_REGISTER(FillX)
    ZFENUM_VALUE_REGISTER(FitX)
    ZFENUM_VALUE_REGISTER(FillY)
    ZFENUM_VALUE_REGISTER(FitY)
ZFENUM_END_WITH_DEFAULT(ZFUIContentScaleType, Fill)

/**
 * @brief apply scale for #ZFUIContentScaleType
 */
ZFMETHOD_FUNC_DECLARE_4(void, ZFUIContentScaleTypeApply,
                        ZFMP_OUT(ZFUIRect &, ret),
                        ZFMP_IN(ZFUIContentScaleTypeEnum, scaleType),
                        ZFMP_IN(const ZFUIRect &, bounds),
                        ZFMP_IN(const ZFUISize &, contentSize))
/**
 * @brief apply scale for #ZFUIContentScaleType
 */
ZFMETHOD_FUNC_DECLARE_INLINE_3(ZFUIRect, ZFUIContentScaleTypeApply,
                               ZFMP_IN(ZFUIContentScaleTypeEnum, scaleType),
                               ZFMP_IN(const ZFUIRect &, bounds),
                               ZFMP_IN(const ZFUISize &, contentSize))
{
    ZFUIRect ret = ZFUIRectZero();
    ZFUIContentScaleTypeApply(ret, scaleType, bounds, contentSize);
    return ret;
}

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUITypeDef_h_

#include "ZFUIColor_common.h"

