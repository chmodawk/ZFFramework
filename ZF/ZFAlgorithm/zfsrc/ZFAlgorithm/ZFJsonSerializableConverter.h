/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFJsonSerializableConverter.h
 * @brief serializable convertion between json and serializalbe
 */

#ifndef _ZFI_ZFJsonSerializableConverter_h_
#define _ZFI_ZFJsonSerializableConverter_h_

#include "ZFJson.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFOUTPUT_TYPE(ZFJsonItem, {output << v.objectInfo();})

// ============================================================
// json serializable conversion

/**
 * @brief see #ZFSERIALIZABLEDATA_REFERENCE_TYPE_DEFINE
 *
 * format:
 * @code
 *   <Node refType="json" refData="file descriptor, see ZFInputCallbackForFileDescriptor" />
 * @endcode
 */
#define ZFSerializableDataRefTypeId_json json
/** @brief see #ZFSerializableDataRefTypeId_json */
#define ZFSerializableDataRefType_json ZFM_TOSTRING(ZFSerializableDataRefTypeId_json)

/**
 * @brief see #ZFOBJECT_CREATOR_DEFINE
 *
 * data:
 * @code
 *   "file descriptor, see ZFInputCallbackForFileDescriptor"
 * @endcode
 * data is a file descriptor to a json file,
 * which should contain a serializable object
 */
#define ZFObjectCreatorTypeId_json json
/** @brief see #ZFSerializableDataRefTypeId_json */
#define ZFObjectCreatorType_json ZFM_TOSTRING(ZFObjectCreatorTypeId_json)

// ============================================================
/**
 * @brief parse json formated data to serializable
 */
ZFMETHOD_FUNC_DECLARE_4(zfbool, ZFJsonParseToData,
                        ZFMP_OUT(ZFSerializableData &, serializableData),
                        ZFMP_IN(const ZFJsonItem &, jsonObject),
                        ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull),
                        ZFMP_OUT_OPT(ZFJsonItem *, outErrorPos, zfnull))
/**
 * @brief see #ZFJsonParseToData
 */
ZFMETHOD_FUNC_DECLARE_3(ZFSerializableData, ZFJsonParseToData,
                        ZFMP_IN(const ZFJsonItem &, jsonObject),
                        ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull),
                        ZFMP_OUT_OPT(ZFJsonItem *, outErrorPos, zfnull))
/**
 * @brief print serializable to json formated data
 */
ZFMETHOD_FUNC_DECLARE_4(zfbool, ZFJsonPrintFromData,
                        ZFMP_OUT(ZFJsonItem &, jsonObject),
                        ZFMP_IN(const ZFSerializableData &, serializableData),
                        ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull),
                        ZFMP_OUT_OPT(ZFSerializableData *, outErrorPos, zfnull))
/**
 * @brief see #ZFJsonPrintFromData
 */
ZFMETHOD_FUNC_DECLARE_3(ZFJsonItem, ZFJsonPrintFromData,
                        ZFMP_IN(const ZFSerializableData &, serializableData),
                        ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull),
                        ZFMP_OUT_OPT(ZFSerializableData *, outErrorPos, zfnull))

// ============================================================
/**
 * @brief util method to print serializable data in json format, usually for debug use only
 */
ZFMETHOD_FUNC_DECLARE_3(void, ZFJsonPrint,
                        ZFMP_IN(const ZFSerializableData &, serializableData),
                        ZFMP_IN_OPT(const ZFOutputCallback &, outputCallback, ZFOutputCallbackDefault()),
                        ZFMP_IN_OPT(const ZFJsonOutputFlags &, flags, ZFJsonOutputFlagsDefault()))
/** @brief see #ZFJsonPrint */
ZFMETHOD_FUNC_DECLARE_3(void, ZFJsonPrint,
                        ZFMP_IN(ZFObject *, obj),
                        ZFMP_IN_OPT(const ZFOutputCallback &, outputCallback, ZFOutputCallbackDefault()),
                        ZFMP_IN_OPT(const ZFJsonOutputFlags &, flags, ZFJsonOutputFlagsDefault()))

// ============================================================
/**
 * @brief util method to parse serializable data from input with json format
 */
ZFMETHOD_FUNC_DECLARE_2(zfbool, ZFJsonParse,
                        ZFMP_OUT(ZFSerializableData &, ret),
                        ZFMP_IN(const ZFInputCallback &, input))
/** @brief see #ZFJsonParse */
ZFMETHOD_FUNC_DECLARE_1(ZFSerializableData, ZFJsonParse,
                        ZFMP_IN(const ZFInputCallback &, input))

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFJsonSerializableConverter_h_

