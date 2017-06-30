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
extern ZF_ENV_EXPORT zfbool ZFJsonParseToSerializableData(ZF_OUT ZFSerializableData &serializableData,
                                                          ZF_IN const ZFJsonItem &jsonObject,
                                                          ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                          ZF_OUT_OPT ZFJsonItem *outErrorPos = zfnull);
/**
 * @brief see #ZFJsonParseToSerializableData
 */
extern ZF_ENV_EXPORT ZFSerializableData ZFJsonParseToSerializableData(ZF_IN const ZFJsonItem &jsonObject,
                                                                      ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                                      ZF_OUT_OPT ZFJsonItem *outErrorPos = zfnull);
/**
 * @brief print serializable to json formated data
 */
extern ZF_ENV_EXPORT zfbool ZFJsonPrintFromSerializableData(ZF_OUT ZFJsonItem &jsonObject,
                                                            ZF_IN const ZFSerializableData &serializableData,
                                                            ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                            ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull);
/**
 * @brief see #ZFJsonPrintFromSerializableData
 */
extern ZF_ENV_EXPORT ZFJsonItem ZFJsonPrintFromSerializableData(ZF_IN const ZFSerializableData &serializableData,
                                                                ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                                ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull);

// ============================================================
/**
 * @brief util method to print serializable data in json format, usually for debug use only
 */
extern ZF_ENV_EXPORT void ZFJsonPrint(ZF_IN const ZFSerializableData &serializableData,
                                      ZF_IN_OPT const ZFOutputCallback &outputCallback = ZFOutputCallbackDefault(),
                                      ZF_IN_OPT const ZFJsonOutputFlags &flags = ZFJsonOutputFlagsDefault);
/** @brief see #ZFJsonPrint */
extern ZF_ENV_EXPORT void ZFJsonPrint(ZF_IN ZFObject *obj,
                                      ZF_IN_OPT const ZFOutputCallback &outputCallback = ZFOutputCallbackDefault(),
                                      ZF_IN_OPT const ZFJsonOutputFlags &flags = ZFJsonOutputFlagsDefault);

// ============================================================
/**
 * @brief util method to parse serializable data from input with json format
 *
 * this method would automatically setup
 * #ZFSerializableDataTagKeyword_filePath/#ZFSerializableDataTagKeyword_resPath
 */
extern ZF_ENV_EXPORT zfbool ZFJsonParse(ZF_OUT ZFSerializableData &ret, ZF_IN const ZFInputCallback &input);
/** @brief see #ZFJsonParse */
extern ZF_ENV_EXPORT ZFSerializableData ZFJsonParse(ZF_IN const ZFInputCallback &input);

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFJsonSerializableConverter_h_

