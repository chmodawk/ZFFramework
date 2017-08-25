/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFFileCallback.h
 * @brief callback for file
 */

#ifndef _ZFI_ZFFileCallback_h_
#define _ZFI_ZFFileCallback_h_

#include "ZFFile.h"
#include "ZFFileBOM.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// keys
/**
 * @brief for io callback only, the file path of the target
 *
 * stored as #ZFString within #ZFCallback::callbackTagSet
 */
#define ZFCallbackTagKeyword_filePath zfText("ZFCallbackTagKeyword_filePath")
/**
 * @brief for io callback only, the resource file path of the target
 *
 * stored as #ZFString within #ZFCallback::callbackTagSet
 */
#define ZFCallbackTagKeyword_resPath zfText("ZFCallbackTagKeyword_resPath")

/**
 * @brief used to impl #ZFOutputCallbackForLocalFile/#ZFInputCallbackForLocalFile
 *
 * stored as #ZFString within #ZFSerializableData::serializableDataTagSet\n
 * holds the parent serializable data's logic file path,
 * while creating #ZFOutputCallbackForLocalFile/#ZFInputCallbackForLocalFile,
 * we will try to find the proper parent path recursively from child to parent,
 * and concatenate to make the final file path
 */
#define ZFSerializableDataTagKeyword_filePath zfText("ZFSerializableDataTagKeyword_filePath")
/**
 * @brief see #ZFSerializableDataTagKeyword_filePath
 */
#define ZFSerializableDataTagKeyword_resPath zfText("ZFSerializableDataTagKeyword_resPath")

/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFFileCallback_filePath zfText("filePath")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFFileCallback_flags zfText("flags")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFFileCallback_autoFlushSize zfText("autoFlushSize")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFFileCallback_autoSkipBOMTable zfText("autoSkipBOMTable")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFFileCallback_localPath zfText("localPath")

// ============================================================
// ZFOutputCallbackForFile
extern ZF_ENV_EXPORT ZFOutputCallback _ZFP_ZFOutputCallbackForFile(ZF_IN const ZFCallerInfo &callerInfo,
                                                                   ZF_IN const zfchar *filePath,
                                                                   ZF_IN_OPT ZFFileOpenOptionFlags flags = ZFFileOpenOption::e_Create,
                                                                   ZF_IN_OPT zfindex autoFlushSize = zfindexMax);
/**
 * @brief see #ZFCALLBACK_SERIALIZE_CUSTOM_TYPE_DEFINE
 *
 * serializable data:
 * @code
 *   <node>
 *       <zfstring category="filePath" ... />
 *       <ZFFileOpenOptionFlags category="flags" ... /> // optional, ZFFileOpenOption::e_Create by default
 *       <zfindex category="autoFlushSize" ... /> // optional, zfindexMax by default
 *   </node>
 * @endcode
 */
#define ZFCallbackSerializeCustomTypeId_ZFOutputCallbackForFile ZFOutputCallbackForFile
/** @brief see #ZFCallbackSerializeCustomTypeRegister */
#define ZFCallbackSerializeCustomType_ZFOutputCallbackForFile ZFM_TOSTRING(ZFCallbackSerializeCustomTypeId_ZFOutputCallbackForFile)

/** @cond ZFPrivateDoc */
#define ZFOutputCallbackForFile(filePath, ...) \
    _ZFP_ZFOutputCallbackForFile(ZFCallerInfoMake(), filePath, ##__VA_ARGS__)
/** @endcond */
/**
 * @brief util to create a file output callback
 *
 * param:
 * -  (const zfchar *)filePath: file path to use
 * -  (ZFFileOpenOption)flags: flags to open file
 * -  (zfindex)autoFlushSize: ensure to flush file after how much size written,
 *   use zfindexMax to disable or 0 to flush every time
 *
 * auto open and auto close files, may return a null callback if open file error
 */
ZFMETHOD_FUNC_DECLARE_3(ZFOutputCallback, ZFOutputCallbackForFile,
                        ZFMP_IN(const zfchar *, filePath),
                        ZFMP_IN_OPT(ZFFileOpenOptionFlags, flags, ZFFileOpenOption::e_Create),
                        ZFMP_IN_OPT(zfindex, autoFlushSize, zfindexMax))

// ============================================================
// ZFInputCallbackForFile
extern ZF_ENV_EXPORT ZFInputCallback _ZFP_ZFInputCallbackForFile(ZF_IN const ZFCallerInfo &callerInfo,
                                                                 ZF_IN const zfchar *filePath,
                                                                 ZF_IN_OPT ZFFileOpenOptionFlags flags = ZFFileOpenOption::e_Read,
                                                                 ZF_IN_OPT const ZFFileBOMList &autoSkipBOMTable = ZFFileBOMListDefault());
/**
 * @brief see #ZFCALLBACK_SERIALIZE_CUSTOM_TYPE_DEFINE
 *
 * serializable data:
 * @code
 *   <node>
 *       <zfstring category="filePath" ... />
 *       <ZFFileOpenOptionFlags category="flags" ... /> // optional, ZFFileOpenOption::e_Read by default
 *       <zfstring category="autoSkipBOMTable" ... /> // optional, ZFFileBOMListDefault by default
 *   </node>
 * @endcode
 */
#define ZFCallbackSerializeCustomTypeId_ZFInputCallbackForFile ZFInputCallbackForFile
/** @brief see #ZFCallbackSerializeCustomTypeRegister */
#define ZFCallbackSerializeCustomType_ZFInputCallbackForFile ZFM_TOSTRING(ZFCallbackSerializeCustomTypeId_ZFInputCallbackForFile)

/** @cond ZFPrivateDoc */
#define ZFInputCallbackForFile(filePath, ...) \
    _ZFP_ZFInputCallbackForFile(ZFCallerInfoMake(), filePath, ##__VA_ARGS__)
/** @endcond */
/**
 * @brief util to create a file input callback
 *
 * param:
 * -  (const zfchar *)filePath: file path to use
 * -  (ZFFileOpenOption)flags: flags to open file
 * -  (const ZFFileBOMList &)autoSkipBOMTable: BOM to skip,
 *   if not empty, BOM would be discarded and BOM's size would be ignored while calculating the file's size
 *
 * auto open and auto close files, may return a null callback if open file error\n
 * auto setup callback cache id with res file path
 */
ZFMETHOD_FUNC_DECLARE_3(ZFInputCallback, ZFInputCallbackForFile,
                        ZFMP_IN(const zfchar *, filePath),
                        ZFMP_IN_OPT(ZFFileOpenOptionFlags, flags, ZFFileOpenOption::e_Read),
                        ZFMP_IN_OPT(const ZFFileBOMList &, autoSkipBOMTable, ZFFileBOMListDefault()))

// ============================================================
// ZFInputCallbackForResFile
extern ZF_ENV_EXPORT ZFInputCallback _ZFP_ZFInputCallbackForResFile(ZF_IN const ZFCallerInfo &callerInfo,
                                                                    ZF_IN const zfchar *resFilePath,
                                                                    ZF_IN_OPT const ZFFileBOMList &autoSkipBOMTable = ZFFileBOMListDefault());
/**
 * @brief see #ZFCALLBACK_SERIALIZE_CUSTOM_TYPE_DEFINE
 *
 * serializable data:
 * @code
 *   <node>
 *       <zfstring category="filePath" ... />
 *       <ZFFileOpenOptionFlags category="flags" ... /> // optional, ZFFileOpenOption::e_Read by default
 *       <zfstring category="autoSkipBOMTable" ... /> // optional, ZFFileBOMListDefault by default
 *   </node>
 * @endcode
 */
#define ZFCallbackSerializeCustomTypeId_ZFInputCallbackForResFile ZFInputCallbackForResFile
/** @brief see #ZFCallbackSerializeCustomTypeRegister */
#define ZFCallbackSerializeCustomType_ZFInputCallbackForResFile ZFM_TOSTRING(ZFCallbackSerializeCustomTypeId_ZFInputCallbackForResFile)

/** @cond ZFPrivateDoc */
#define ZFInputCallbackForResFile(resFilePath, ...) \
    _ZFP_ZFInputCallbackForResFile(ZFCallerInfoMake(), resFilePath, ##__VA_ARGS__)
/** @endcond */
/**
 * @brief util to create a resource file input callback,
 *   see #ZFFile::resOpen for what resource file is
 *
 * param:
 * -  (const zfchar *)resFilePath: resource file path to use
 * -  (const ZFFileBOMList &)autoSkipBOMTable: BOM to skip,
 *   if not empty, BOM would be discarded and BOM's size would be ignored while calculating the file's size
 *
 * auto open and auto close files, may return a null callback if open file error
 */
ZFMETHOD_FUNC_DECLARE_2(ZFInputCallback, ZFInputCallbackForResFile,
                        ZFMP_IN(const zfchar *, resFilePath),
                        ZFMP_IN_OPT(const ZFFileBOMList &, autoSkipBOMTable, ZFFileBOMListDefault()))

// ============================================================
// ZFOutputCallbackForLocalFile
extern ZF_ENV_EXPORT ZFOutputCallback _ZFP_ZFOutputCallbackForLocalFile(ZF_IN const ZFCallerInfo &callerInfo,
                                                                        ZF_IN const ZFSerializableData &dataToCheckParentPath,
                                                                        ZF_IN const zfchar *localPath,
                                                                        ZF_IN_OPT ZFFileOpenOptionFlags flags = ZFFileOpenOption::e_Create,
                                                                        ZF_IN_OPT zfindex autoFlushSize = zfindexMax);
/**
 * @brief see #ZFCALLBACK_SERIALIZE_CUSTOM_TYPE_DEFINE
 *
 * serializable data:
 * @code
 *   <node>
 *       <zfstring category="localPath" ... />
 *       <ZFFileOpenOptionFlags category="flags" ... /> // optional, ZFFileOpenOption::e_Create by default
 *       <zfindex category="autoFlushSize" ... /> // optional, zfindexMax by default
 *   </node>
 * @endcode
 */
#define ZFCallbackSerializeCustomTypeId_ZFOutputCallbackForLocalFile ZFOutputCallbackForLocalFile
/** @brief see #ZFCallbackSerializeCustomTypeRegister */
#define ZFCallbackSerializeCustomType_ZFOutputCallbackForLocalFile ZFM_TOSTRING(ZFCallbackSerializeCustomTypeId_ZFOutputCallbackForLocalFile)

/** @cond ZFPrivateDoc */
#define ZFOutputCallbackForLocalFile(dataToCheckParentPath, filePath, ...) \
    _ZFP_ZFOutputCallbackForLocalFile(ZFCallerInfoMake(), dataToCheckParentPath, filePath, ##__VA_ARGS__)
/** @endcond */
/**
 * @brief util to create a file output callback
 *
 * param:
 * -  (const ZFSerializableData &)dataToCheckParentPath: see #ZFSerializableDataTagKeyword_filePath
 * -  (const zfchar *)localPath: local file path to use
 * -  (ZFFileOpenOption)flags: flags to open file
 * -  (zfindex)autoFlushSize: ensure to flush file after how much size written,
 *   use zfindexMax to disable or 0 to flush every time
 *
 * auto open and auto close files, may return a null callback if open file error
 */
ZFMETHOD_FUNC_DECLARE_4(ZFOutputCallback, ZFOutputCallbackForLocalFile,
                        ZFMP_IN(const ZFSerializableData &, dataToCheckParentPath),
                        ZFMP_IN(const zfchar *, localPath),
                        ZFMP_IN_OPT(ZFFileOpenOptionFlags, flags, ZFFileOpenOption::e_Create),
                        ZFMP_IN_OPT(zfindex, autoFlushSize, zfindexMax))

// ============================================================
// ZFInputCallbackForLocalFile
extern ZF_ENV_EXPORT ZFInputCallback _ZFP_ZFInputCallbackForLocalFile(ZF_IN const ZFCallerInfo &callerInfo,
                                                                      ZF_IN const ZFSerializableData &dataToCheckParentPath,
                                                                      ZF_IN const zfchar *filePath,
                                                                      ZF_IN_OPT ZFFileOpenOptionFlags flags = ZFFileOpenOption::e_Read,
                                                                      ZF_IN_OPT const ZFFileBOMList &autoSkipBOMTable = ZFFileBOMListDefault());
/**
 * @brief see #ZFCALLBACK_SERIALIZE_CUSTOM_TYPE_DEFINE
 *
 * serializable data:
 * @code
 *   <node>
 *       <zfstring category="localPath" ... />
 *       <ZFFileOpenOptionFlags category="flags" ... /> // optional, ZFFileOpenOption::e_Read by default
 *       <zfstring category="autoSkipBOMTable" ... /> // optional, ZFFileBOMListDefault by default
 *   </node>
 * @endcode
 */
#define ZFCallbackSerializeCustomTypeId_ZFInputCallbackForLocalFile ZFInputCallbackForLocalFile
/** @brief see #ZFCallbackSerializeCustomTypeRegister */
#define ZFCallbackSerializeCustomType_ZFInputCallbackForLocalFile ZFM_TOSTRING(ZFCallbackSerializeCustomTypeId_ZFInputCallbackForLocalFile)

/** @cond ZFPrivateDoc */
#define ZFInputCallbackForLocalFile(dataToCheckParentPath, filePath, ...) \
    _ZFP_ZFInputCallbackForLocalFile(ZFCallerInfoMake(), dataToCheckParentPath, filePath, ##__VA_ARGS__)
/** @endcond */
/**
 * @brief util to create a file input callback
 *
 * param:
 * -  (const ZFSerializableData &)dataToCheckParentPath: see #ZFSerializableDataTagKeyword_filePath
 * -  (const zfchar *)localPath: local file path to use
 * -  (ZFFileOpenOption)flags: flags to open file
 * -  (const ZFFileBOMList &)autoSkipBOMTable: BOM to skip,
 *   if not empty, BOM would be discarded and BOM's size would be ignored while calculating the file's size
 *
 * auto open and auto close files, may return a null callback if open file error\n
 * auto setup callback cache id with res file path
 */
ZFMETHOD_FUNC_DECLARE_4(ZFInputCallback, ZFInputCallbackForLocalFile,
                        ZFMP_IN(const ZFSerializableData &, dataToCheckParentPath),
                        ZFMP_IN(const zfchar *, filePath),
                        ZFMP_IN_OPT(ZFFileOpenOptionFlags, flags, ZFFileOpenOption::e_Read),
                        ZFMP_IN_OPT(const ZFFileBOMList &, autoSkipBOMTable, ZFFileBOMListDefault()))

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFFileCallback_h_

#include "ZFFileCallback_ZFIOBridgeCallbackUsingTmpFile.h"

