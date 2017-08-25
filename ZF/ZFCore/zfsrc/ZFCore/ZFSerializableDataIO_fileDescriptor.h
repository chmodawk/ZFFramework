/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFSerializableDataIO_fileDescriptor.h
 * @brief util method to load #ZFSerializableDataFromIO
 *   as file descriptor
 */

#ifndef _ZFI_ZFSerializableDataIO_fileDescriptor_h_
#define _ZFI_ZFSerializableDataIO_fileDescriptor_h_

#include "ZFSerializableDataIO.h"
#include "ZFFileDescriptor.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief detect file extension accorrding to file descriptor
 *
 * detect by #ZFFile::fileExtOf
 */
ZFMETHOD_FUNC_DECLARE_1(zfstring, ZFSerializableDataIOFileDescriptorDetect,
                        ZFMP_IN(const zfchar *, fileDescriptor))

/**
 * @brief see #ZFSerializableDataFromIO, #ZFInputCallbackForFileDescriptor
 *
 * this method would:
 * -# check ioType by #ZFSerializableDataIOFileDescriptorDetect
 * -# open input by #ZFInputCallbackForFileDescriptor
 * -# load serializableData by #ZFSerializableDataFromIO
 */
ZFMETHOD_FUNC_DECLARE_3(zfbool, ZFSerializableDataFromFileDescriptor,
                        ZFMP_OUT(ZFSerializableData &, serializableData),
                        ZFMP_IN(const zfchar *, fileDescriptor),
                        ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull))
/** @brief see #ZFSerializableDataFromFileDescriptor */
ZFMETHOD_FUNC_DECLARE_2(ZFSerializableData, ZFSerializableDataFromFileDescriptor,
                        ZFMP_IN(const zfchar *, fileDescriptor),
                        ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull))
/**
 * @brief see #ZFSerializableDataToFileDescriptor
 *
 * this method would:
 * -# check ioType by #ZFSerializableDataIOFileDescriptorDetect
 * -# open output by #ZFOutputCallbackForFileDescriptor
 * -# write serializableData to output by #ZFSerializableDataToIO
 */
ZFMETHOD_FUNC_DECLARE_3(zfbool, ZFSerializableDataToFileDescriptor,
                        ZFMP_IN(const zfchar *, fileDescriptor),
                        ZFMP_IN(const ZFSerializableData &, serializableData),
                        ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull))

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFSerializableDataIO_fileDescriptor_h_

