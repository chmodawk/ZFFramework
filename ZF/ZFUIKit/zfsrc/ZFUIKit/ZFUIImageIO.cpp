/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIImageIO.h"
#include "protocol/ZFProtocolZFUIImage.h"
#include "protocol/ZFProtocolZFUIImageIO.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// ZFUIImageScale
ZFMETHOD_FUNC_DEFINE_3(zfautoObject, ZFUIImageScale,
                       ZFMP_IN(ZFUIImage *, image),
                       ZFMP_IN(const ZFUISize &, newSize),
                       ZFMP_IN_OPT(zfbool, newSizeInPixelUnit, zffalse))
{
    if(image == zfnull || image->nativeImage() == zfnull)
    {
        return zfautoObjectNull();
    }
    zffloat scale = image->imageScaleFixed();
    void *nativeImage = ZFPROTOCOL_ACCESS(ZFUIImageIO)->imageApplyScale(
        scale,
        image->nativeImage(),
        newSizeInPixelUnit ? newSize : ZFUISizeApplyScale(newSize, scale),
        ZFUIMarginApplyScale(image->imageNinePatch(), scale));
    if(nativeImage == zfnull)
    {
        return zfautoObjectNull();
    }
    zfautoObject ret = ZFUIImage::ClassData()->newInstance(ZFCallerInfoMake());
    ret.to<ZFUIImage *>()->nativeImageSet(nativeImage);
    ZFPROTOCOL_ACCESS(ZFUIImage)->nativeImageRelease(nativeImage);
    return ret;
}

// ============================================================
// ZFUIImageLoadFromNativeImage
ZFMETHOD_FUNC_DEFINE_1(zfautoObject, ZFUIImageLoadFromNativeImage,
                       ZFMP_IN(void *, nativeImage))
{
    if(nativeImage == zfnull)
    {
        return zfautoObjectNull();
    }
    zfautoObject ret = ZFUIImage::ClassData()->newInstance(ZFCallerInfoMake());
    ret.to<ZFUIImage *>()->nativeImageSet(nativeImage);
    return ret;
}

// ============================================================
// input
ZFUIIMAGE_SERIALIZE_TYPE_DEFINE(ZFUIImageSerializeTypeId_input)
{
    ZFCallback input;
    if(!ZFCallbackFromData(input, serializableData, outErrorHint, outErrorPos))
    {
        return zffalse;
    }
    if(!input.callbackIsValid())
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("invalid callback"));
        return zffalse;
    }
    if(!ZFUIImageEncodeFromBinary(result, input))
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("load image failed"));
        return zffalse;
    }
    return zftrue;
}

ZFMETHOD_FUNC_DEFINE_1(zfautoObject, ZFUIImageLoadFromInput,
                       ZFMP_IN(const ZFInputCallback &, input))
{
    zfautoObject ret = ZFUIImage::ClassData()->newInstance(ZFCallerInfoMake());
    ZFUIImage *image = ret;
    if(!ZFUIImageEncodeFromBinary(image, input))
    {
        return zfautoObjectNull();
    }

    if(input.callbackSerializeCustomType() != zfnull)
    {
        ZFSerializableData inputData;
        if(ZFCallbackToData(inputData, input))
        {
            image->imageSerializableTypeSet(ZFUIImageSerializeType_input);
            image->imageSerializableDataSet(&inputData);
        }
    }

    return ret;
}

// ============================================================
// color
ZFUIIMAGE_SERIALIZE_TYPE_DEFINE(ZFUIImageSerializeTypeId_color)
{
    ZFUIColor color = ZFUIColorTransparent();
    { // color
        const ZFSerializableData *categoryData = ZFSerializableUtil::checkElementByCategory(serializableData, ZFSerializableKeyword_ZFUIImageIO_color);
        if(categoryData != zfnull)
        {
            if(!ZFUIColorFromData(color, *categoryData, outErrorHint, outErrorPos))
            {
                return zffalse;
            }
        }
    }

    ZFUISize size = ZFUISizeMake(1);
    { // size
        const ZFSerializableData *categoryData = ZFSerializableUtil::checkElementByCategory(serializableData, ZFSerializableKeyword_ZFUIImageIO_color_size);
        if(categoryData != zfnull)
        {
            if(!ZFUISizeFromData(size, *categoryData, outErrorHint, outErrorPos))
            {
                return zffalse;
            }
            if(size.width <= 0 || size.height <= 0)
            {
                ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, *categoryData,
                    zfText("invalid size: %s"), ZFUISizeToString(size).cString());
                return zffalse;
            }
        }
    }

    ZFSerializableData imageData;
    {
        if(!ZFUIColorIsEqual(color, ZFUIColorTransparent()))
        {
            ZFSerializableData categoryData;
            if(!ZFUIColorToData(categoryData, color, outErrorHint))
            {
                return zffalse;
            }
            categoryData.categorySet(ZFSerializableKeyword_ZFUIImageIO_color);
            imageData.elementAdd(categoryData);
        }
        if(!ZFUISizeIsEqual(size, ZFUISizeMake(1, 1)))
        {
            ZFSerializableData categoryData;
            if(!ZFUISizeToData(categoryData, size, outErrorHint))
            {
                return zffalse;
            }
            categoryData.categorySet(ZFSerializableKeyword_ZFUIImageIO_color_size);
            imageData.elementAdd(categoryData);
        }
    }

    void *nativeImage = ZFPROTOCOL_ACCESS(ZFUIImageIO)->imageLoadFromColor(ZFUIGlobalStyle::DefaultStyle()->imageScale(), color, size);
    result->nativeImageSet(nativeImage);
    result->imageSerializableDataSet(&imageData);
    ZFPROTOCOL_ACCESS(ZFUIImage)->nativeImageRelease(nativeImage);

    return zftrue;
}
ZFMETHOD_FUNC_DEFINE_2(zfautoObject, ZFUIImageLoadFromColor,
                       ZFMP_IN(const ZFUIColor &, color),
                       ZFMP_IN_OPT(const ZFUISize &, size, ZFUISizeZero()))
{
    ZFUISize sizeTmp = ZFUISizeMake(zfmMax(1, size.width), zfmMax(1, size.height));
    void *nativeImage = ZFPROTOCOL_ACCESS(ZFUIImageIO)->imageLoadFromColor(
        ZFUIGlobalStyle::DefaultStyle()->imageScale(),
        color,
        ZFUISizeApplyScale(sizeTmp, ZFUIGlobalStyle::DefaultStyle()->imageScale()));
    if(nativeImage == zfnull)
    {
        return zfautoObjectNull();
    }

    zfautoObject ret = ZFUIImage::ClassData()->newInstance(ZFCallerInfoMake());
    ZFUIImage *image = ret;
    image->nativeImageSet(nativeImage);
    ZFPROTOCOL_ACCESS(ZFUIImage)->nativeImageRelease(nativeImage);

    ZFSerializableData imageData;

    do
    {
        // color
        if(color != ZFUIColorTransparent())
        {
            ZFSerializableData categoryData;
            if(!ZFUIColorToData(categoryData, color))
            {
                break;
            }
            categoryData.categorySet(ZFSerializableKeyword_ZFUIImageIO_color);
            imageData.elementAdd(categoryData);
        }

        // size
        if(!ZFUISizeIsEqual(sizeTmp, ZFUISizeMake(1, 1)))
        {
            ZFSerializableData categoryData;
            if(!ZFUISizeToData(categoryData, sizeTmp))
            {
                break;
            }
            categoryData.categorySet(ZFSerializableKeyword_ZFUIImageIO_color_size);
            imageData.elementAdd(categoryData);
        }

        imageData.itemClassSet(ZFSerializableKeyword_node);
    } while(zffalse);

    if(imageData.itemClass() != zfnull)
    {
        image->imageSerializableTypeSet(ZFUIImageSerializeType_color);
        image->imageSerializableDataSet(&imageData);
    }

    return ret;
}

ZF_NAMESPACE_GLOBAL_END

