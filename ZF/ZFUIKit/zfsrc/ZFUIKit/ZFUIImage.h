/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFUIImage.h
 * @brief image
 */

#ifndef _ZFI_ZFUIImage_h_
#define _ZFI_ZFUIImage_h_

#include "ZFUITypeDef.h"
#include "ZFUIGlobalStyle.h"
ZF_NAMESPACE_GLOBAL_BEGIN

zfclassFwd ZFUIImage;

// ============================================================
/**
 * @brief internal use only, see #ZFUIImageSerializeTypeRegister
 */
typedef zfbool (*ZFUIImageSerializeFromCallback)(ZF_IN_OUT ZFUIImage *image,
                                                 ZF_IN const ZFSerializableData &imageData,
                                                 ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */,
                                                 ZF_OUT_OPT ZFSerializableData *outErrorPos /* = zfnull */);

/**
 * @brief register a serializable logic for ZFUIImage
 *
 * ZFUIImage can be loaded from many sources,
 * so we supply a dynamic serializable logic depending on image's load logic,
 * use this methods along with #ZFUIImageSerializeTypeUnregister and #ZF_GLOBAL_INITIALIZER_INIT
 * to register your own serialize logic,
 * such as load from file or load from color\n
 * \n
 * typically you should use #ZFUIIMAGE_SERIALIZE_TYPE_DEFINE to define your type for short:
 * @code
 *   // in header file
 *   #define ZFUIImageSerializeTypeId_yourType yourType
 *   #define ZFUIImageSerializeType_yourType ZFM_TOSTRING(ZFUIImageSerializeTypeId_yourType)
 *
 *   // in cpp file
 *   ZFUIIMAGE_SERIALIZE_TYPE_DEFINE(ZFUIImageSerializeTypeId_yourType)
 *   {
 *       // serialize callback from data
 *       return zftrue;
 *   }
 * @endcode
 * proto type:\n
 *   zfbool action(ZF_IN_OUT ZFUIImage *result,
 *                 ZF_IN const ZFSerializableData &serializableData,
 *                 ZF_OUT_OPT zfstring *outErrorHint,
 *                 ZF_OUT_OPT ZFSerializableData *outErrorPos);
 */
extern ZF_ENV_EXPORT void ZFUIImageSerializeTypeRegister(ZF_IN const zfchar *name,
                                                         ZF_IN ZFUIImageSerializeFromCallback fromCallback);
/**
 * @brief see #ZFUIImageSerializeTypeRegister
 */
extern ZF_ENV_EXPORT void ZFUIImageSerializeTypeUnregister(ZF_IN const zfchar *name);
#define _ZFP_ZFUIIMAGE_SERIALIZE_TYPE_DEFINE(type) \
    static zfbool _ZFP_ZFUIImageSerializeFromCallback_##type(ZF_IN_OUT ZFUIImage *result, \
                                                             ZF_IN const ZFSerializableData &serializableData, \
                                                             ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */, \
                                                             ZF_OUT_OPT ZFSerializableData *outErrorPos /* = zfnull */); \
    ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFUIImageSerializeCallbackRegister_##type, ZFLevelZFFrameworkNormal) \
    { \
        ZFUIImageSerializeTypeRegister(ZFUIImageSerializeType_##type, _ZFP_ZFUIImageSerializeFromCallback_##type); \
    } \
    ZF_GLOBAL_INITIALIZER_DESTROY(ZFUIImageSerializeCallbackRegister_##type) \
    { \
        ZFUIImageSerializeTypeUnregister(ZFUIImageSerializeType_##type); \
    } \
    ZF_GLOBAL_INITIALIZER_END(ZFUIImageSerializeCallbackRegister_##type) \
    static zfbool _ZFP_ZFUIImageSerializeFromCallback_##type(ZF_IN_OUT ZFUIImage *result, \
                                                             ZF_IN const ZFSerializableData &serializableData, \
                                                             ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */, \
                                                             ZF_OUT_OPT ZFSerializableData *outErrorPos /* = zfnull */)
/**
 * @brief see #ZFUIImageSerializeTypeRegister
 */
#define ZFUIIMAGE_SERIALIZE_TYPE_DEFINE(type) \
    _ZFP_ZFUIIMAGE_SERIALIZE_TYPE_DEFINE(type)

/**
 * @brief usually for debug use only
 */
extern ZF_ENV_EXPORT void ZFUIImageSerializeTypeGetAllT(ZF_OUT ZFCoreArray<const zfchar *> &ret);
/** @brief see #ZFUIImageSerializeTypeGetAll */
inline ZFCoreArrayPOD<const zfchar *> ZFUIImageSerializeTypeGetAll(void)
{
    ZFCoreArrayPOD<const zfchar *> ret;
    ZFUIImageSerializeTypeGetAllT(ret);
    return ret;
}

/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFUIImage_imageScale zfText("imageScale")

/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFUIImage_imageType zfText("imageType")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFUIImage_imageData zfText("imageData")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFUIImage_imageBin zfText("imageBin")

// ============================================================
// ZFUIImage
zfclassFwd _ZFP_ZFUIImagePrivate;
/**
 * @brief image storage
 * @note #ZFUIImage always use custom scale value, see #ZFUIGlobalStyle::imageScale
 *
 * \n
 * serializable data:
 * @code
 *   <ZFUIImage imageType="type name for ZFUIImageSerializeTypeRegister" >
 *       <anything category="imageData" ... /> // depends on load logic, see #ZFUIImageSerializeTypeRegister
 *
 *       // if nothing supplied, we will serialize by binary data
 *       <zfstring category="imageBin" value="image binary data, base64 encoded" />
 *
 *       // optional, custom scale for this image
 *       <zffloat category="imageScale" />
 *   </ZFUIImage>
 * @endcode
 */
zffinal zfclass ZF_ENV_EXPORT ZFUIImage : zfextends ZFObject, zfimplements ZFSerializable, zfimplements ZFCopyable
{
    ZFOBJECT_DECLARE(ZFUIImage, ZFObject)
    ZFIMPLEMENTS_DECLARE(ZFSerializable, ZFCopyable)

    /**
     * @brief see #ZFObject::observerNotify
     *
     * called when #imageScale or #ZFUIGlobalStyle::imageScale changed
     */
    ZFOBSERVER_EVENT(ImageScaleOnChange)

protected:
    zfoverride
    virtual zfbool serializableOnSerializeFromData(ZF_IN const ZFSerializableData &serializableData,
                                                   ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                   ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull);
    zfoverride
    virtual zfbool serializableOnSerializeToData(ZF_IN_OUT ZFSerializableData &serializableData,
                                                 ZF_IN ZFSerializable *referencedOwnerOrNull,
                                                 ZF_OUT_OPT zfstring *outErrorHint = zfnull);

protected:
    zfoverride
    virtual void copyableOnCopyFrom(ZF_IN ZFObject *anotherObj);

    // ============================================================
    // property
public:
    /**
     * @brief image's scale
     *
     * 0 or less means not set, and #ZFUIGlobalStyle::imageScale would be used
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(zffloat, imageScale, ZFPropertyInitValue(0))
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(zffloat, imageScale);
    /**
     * @brief nine patch described by a margin value, disabled if zero margin or margin exceeds image size
     * @note #ZFUIImage always use custom scale value, see #ZFUIGlobalStyle::imageScale
     */
    ZFPROPERTY_ASSIGN(ZFUIMargin, imageNinePatch)

    /**
     * @brief see #imageScale
     */
    ZFMETHOD_DECLARE_0(zffloat, imageScaleFixed)
    {
        return (this->imageScale() > 0 ? this->imageScale() : ZFUIGlobalStyle::DefaultStyle()->imageScale());
    }
    /**
     * @brief get size of the image
     * @note #ZFUIImage always use custom scale value, see #ZFUIGlobalStyle::imageScale
     */
    ZFMETHOD_DECLARE_0(const ZFUISize &, imageSize);
    /**
     * @brief get raw size of the image without scale (in pixel unit)
     */
    ZFMETHOD_DECLARE_0(const ZFUISize &, imageSizeFixed);

    // ============================================================
    // other
    ZFCLASS_PRIVATE_ALLOC("can only be created by ZFUIImageLoadXxx")
protected:
    zfoverride
    virtual void objectOnInit(void);
    zfoverride
    virtual void objectOnDealloc(void);
    zfoverride
    virtual void objectOnInitFinish(void);
    zfoverride
    virtual void objectOnDeallocPrepare(void);

    zfoverride
    virtual zfidentity objectHash(void);
    zfoverride
    virtual ZFCompareResult objectCompare(ZF_IN ZFObject *anotherObj);
protected:
    zfoverride
    virtual void objectInfoOnAppend(ZF_IN_OUT zfstring &ret);

public:
    /**
     * @brief get native image object
     */
    ZFMETHOD_DECLARE_0(void *, nativeImage);

public:
    zffinal void _ZFP_ZFUIImage_imageScaleOnChange(void);
protected:
    /** @brief see #EventImageScaleOnChange */
    virtual void imageScaleOnChange(void)
    {
        this->observerNotify(ZFUIImage::EventImageScaleOnChange());
    }

    // ============================================================
    // internal methods
public:
    /**
     * @brief internal use only, set the native image
     *
     * the image would be retained, actual retain logic is depending on the implementation
     */
    virtual void nativeImageSet(ZF_IN void *nativeImage);

    /**
     * @brief see #ZFUIImageSerializeTypeRegister
     */
    virtual void imageSerializableTypeSet(ZF_IN const zfchar *typeName);
    /**
     * @brief see #imageSerializableTypeSet
     */
    virtual const zfchar *imageSerializableType(void);
    /**
     * @brief see #ZFUIImageSerializeTypeRegister
     */
    virtual void imageSerializableDataSet(ZF_IN const ZFSerializableData *serializableData);
    /**
     * @brief see #imageSerializableDataSet
     */
    virtual const ZFSerializableData *imageSerializableData(void);

private:
    _ZFP_ZFUIImagePrivate *d;
};

// ============================================================
// image's binary load
/**
 * @brief load image from binary data (base64 encoded)
 * @note this method have no serialize logic,
 *   result image would be serialized by base64 value while serializing to data
 */
ZFMETHOD_FUNC_DECLARE_2(zfbool, ZFUIImageEncodeFromBase64,
                        ZFMP_IN_OUT(ZFUIImage *, image),
                        ZFMP_IN(const ZFInputCallback &, inputCallback))
/**
 * @brief see #ZFUIImageEncodeFromBase64
 */
ZFMETHOD_FUNC_DECLARE_1(zfautoObject, ZFUIImageEncodeFromBase64,
                        ZFMP_IN(const ZFInputCallback &, inputCallback))
/**
 * @brief save image as binary data (base64 encoded)
 * @note this method have no serialize logic,
 *   result image would be serialized by base64 value while serializing to data
 */
ZFMETHOD_FUNC_DECLARE_2(zfbool, ZFUIImageEncodeToBase64,
                        ZFMP_OUT(const ZFOutputCallback &, outputCallback),
                        ZFMP_IN(ZFUIImage *, image))

/**
 * @brief load image from binary data
 * @note this method have no serialize logic,
 *   result image would be serialized by base64 value while serializing to data
 */
ZFMETHOD_FUNC_DECLARE_2(zfbool, ZFUIImageEncodeFromBinary,
                        ZFMP_IN_OUT(ZFUIImage *, image),
                        ZFMP_IN(const ZFInputCallback &, inputCallback))
/**
 * @brief see #ZFUIImageEncodeFromBinary
 */
ZFMETHOD_FUNC_DECLARE_1(zfautoObject, ZFUIImageEncodeFromBinary,
                        ZFMP_IN(const ZFInputCallback &, inputCallback))
/**
 * @brief save image as binary data
 * @note this method have no serialize logic,
 *   result image would be serialized by base64 value while serializing to data
 */
ZFMETHOD_FUNC_DECLARE_2(zfbool, ZFUIImageEncodeToBinary,
                        ZFMP_OUT(const ZFOutputCallback &, outputCallback),
                        ZFMP_IN(ZFUIImage *, image))

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIImage_h_

#include "ZFUIImageCache.h"
#include "ZFUIImageCache_common.h"
#include "ZFUIImageIO.h"
#include "ZFUIImageRes.h"

