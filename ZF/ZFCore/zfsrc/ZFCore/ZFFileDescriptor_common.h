/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFFileDescriptor_common.h
 * @brief file io from a string descriptor
 */

#ifndef _ZFI_ZFFileDescriptor_common_h_
#define _ZFI_ZFFileDescriptor_common_h_

#include "ZFFileDescriptor.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief see #ZFFileDescriptorTypeRegister, data is file's local path (relative or absolute, depending on runtime)
 */
#define ZFFileDescriptorType_NativeLocal zfText("NativeLocal")
/**
 * @brief see #ZFFileDescriptorTypeRegister, data is file's relative path within resource folder
 */
#define ZFFileDescriptorType_Res zfText("Res")
/**
 * @brief see #ZFFileDescriptorTypeRegister, data is file's relative path within #ZFFile::modulePath
 */
#define ZFFileDescriptorType_ModulePath zfText("ModulePath")
/**
 * @brief see #ZFFileDescriptorTypeRegister, data is file's relative path within #ZFFile::settingPath
 */
#define ZFFileDescriptorType_SettingPath zfText("SettingPath")
/**
 * @brief see #ZFFileDescriptorTypeRegister, data is file's relative path within #ZFFile::storagePath
 */
#define ZFFileDescriptorType_StoragePath zfText("StoragePath")
/**
 * @brief see #ZFFileDescriptorTypeRegister, data is file's relative path within #ZFFile::storageSharedPath
 */
#define ZFFileDescriptorType_StorageSharedPath zfText("StorageSharedPath")
/**
 * @brief see #ZFFileDescriptorTypeRegister, data is file's relative path within #ZFFile::cachePath
 *
 * note, the cache path's content would be removed accorrding to #ZFFile::cachePathClear
 */
#define ZFFileDescriptorType_CachePath zfText("CachePath")
/**
 * @brief see #ZFFileDescriptorTypeRegister, data is plain text
 */
#define ZFFileDescriptorType_Text zfText("Text")

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFFileDescriptor_common_h_

