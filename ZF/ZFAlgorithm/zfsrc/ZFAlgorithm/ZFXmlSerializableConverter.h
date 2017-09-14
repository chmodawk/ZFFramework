/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFXmlSerializableConverter.h
 * @brief serializable convertion between xml and serializalbe
 */

#ifndef _ZFI_ZFXmlSerializableConverter_h_
#define _ZFI_ZFXmlSerializableConverter_h_

#include "ZFXml.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFOUTPUT_TYPE(ZFXmlItem, {output << v.objectInfo();})

// ============================================================
// xml serializable conversion

/**
 * @brief see #ZFSERIALIZABLEDATA_REFERENCE_TYPE_DEFINE
 *
 * format:
 * @code
 *   <Node refType="xml" refData="file descriptor, see ZFInputCallbackForFileDescriptor" />
 * @endcode
 */
#define ZFSerializableDataRefTypeId_xml xml
/** @brief see #ZFSerializableDataRefTypeId_xml */
#define ZFSerializableDataRefType_xml ZFM_TOSTRING(ZFSerializableDataRefTypeId_xml)

/**
 * @brief see #ZFOBJECT_CREATOR_DEFINE
 *
 * data:
 * @code
 *   "file descriptor, see ZFInputCallbackForFileDescriptor"
 * @endcode
 * data is a file descriptor to a xml file,
 * which should contain a serializable object
 */
#define ZFObjectCreatorTypeId_xml xml
/** @brief see #ZFSerializableDataRefTypeId_xml */
#define ZFObjectCreatorType_xml ZFM_TOSTRING(ZFObjectCreatorTypeId_xml)

// ============================================================
/**
 * @brief parse xml formated data to serializable
 */
ZFMETHOD_FUNC_DECLARE_4(zfbool, ZFXmlParseToData,
                        ZFMP_OUT(ZFSerializableData &, serializableData),
                        ZFMP_IN(const ZFXmlItem &, xmlElement),
                        ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull),
                        ZFMP_OUT_OPT(ZFXmlItem *, outErrorPos, zfnull))
/**
 * @brief see #ZFXmlParseToData
 */
ZFMETHOD_FUNC_DECLARE_3(ZFSerializableData, ZFXmlParseToData,
                        ZFMP_IN(const ZFXmlItem &, xmlElement),
                        ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull),
                        ZFMP_OUT_OPT(ZFXmlItem *, outErrorPos, zfnull))
/**
 * @brief print serializable to xml formated data
 */
ZFMETHOD_FUNC_DECLARE_4(zfbool, ZFXmlPrintFromData,
                        ZFMP_OUT(ZFXmlItem &, xmlElement),
                        ZFMP_IN(const ZFSerializableData &, serializableData),
                        ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull),
                        ZFMP_OUT_OPT(ZFSerializableData *, outErrorPos, zfnull))
/**
 * @brief see #ZFXmlPrintFromData
 */
ZFMETHOD_FUNC_DECLARE_3(ZFXmlItem, ZFXmlPrintFromData,
                        ZFMP_IN(const ZFSerializableData &, serializableData),
                        ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull),
                        ZFMP_OUT_OPT(ZFSerializableData *, outErrorPos, zfnull))

// ============================================================
/**
 * @brief util method to convert serializable object to xml format
 */
ZFMETHOD_FUNC_DECLARE_3(void, ZFXmlPrint,
                        ZFMP_IN(const ZFSerializableData &, serializableData),
                        ZFMP_IN_OPT(const ZFOutputCallback &, outputCallback, ZFOutputCallbackDefault()),
                        ZFMP_IN_OPT(const ZFXmlOutputFlags &, flags, ZFXmlOutputFlagsDefault()))
/** @brief see #ZFXmlPrint */
ZFMETHOD_FUNC_DECLARE_3(void, ZFXmlPrint,
                        ZFMP_IN(ZFObject *, obj),
                        ZFMP_IN_OPT(const ZFOutputCallback &, outputCallback, ZFOutputCallbackDefault()),
                        ZFMP_IN_OPT(const ZFXmlOutputFlags &, flags, ZFXmlOutputFlagsDefault()))

// ============================================================
/**
 * @brief util method to parse serializable data from input with xml format
 *
 * this method would automatically setup
 * #ZFSerializableDataTagKeyword_filePath/#ZFSerializableDataTagKeyword_resPath
 */
ZFMETHOD_FUNC_DECLARE_2(zfbool, ZFXmlParse,
                        ZFMP_OUT(ZFSerializableData &, ret),
                        ZFMP_IN(const ZFInputCallback &, input))
/** @brief see #ZFXmlParse */
ZFMETHOD_FUNC_DECLARE_1(ZFSerializableData, ZFXmlParse,
                        ZFMP_IN(const ZFInputCallback &, input))

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFXmlSerializableConverter_h_

