/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFSerializableDataIO_fileDescriptor.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_FUNC_DEFINE_1(zfstring, ZFSerializableDataIOFileDescriptorDetect,
                       ZFMP_IN(const zfchar *, fileDescriptor))
{
    return ZFFile::fileExtOf(fileDescriptor);
}

ZFMETHOD_FUNC_DEFINE_3(zfbool, ZFSerializableDataFromFileDescriptor,
                       ZFMP_OUT(ZFSerializableData &, serializableData),
                       ZFMP_IN(const zfchar *, fileDescriptor),
                       ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull))
{
    zfstring ioType = ZFSerializableDataIOFileDescriptorDetect(fileDescriptor);
    if(ioType.isEmpty())
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, zfText("unable to detect ioType for \"%s\""), fileDescriptor);
        return zffalse;
    }
    ZFInputCallback input = ZFInputCallbackForFileDescriptor(fileDescriptor);
    if(!input.callbackIsValid())
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, zfText("unable to open input for \"%s\""), fileDescriptor);
        return zffalse;
    }
    return ZFSerializableDataFromIO(serializableData, ioType, input, outErrorHint);
}
ZFMETHOD_FUNC_DEFINE_2(ZFSerializableData, ZFSerializableDataFromFileDescriptor,
                       ZFMP_IN(const zfchar *, fileDescriptor),
                       ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull))
{
    ZFSerializableData ret;
    if(ZFSerializableDataFromFileDescriptor(ret, fileDescriptor, outErrorHint))
    {
        return ret;
    }
    else
    {
        return ZFSerializableData();
    }
}
ZFMETHOD_FUNC_DEFINE_3(zfbool, ZFSerializableDataToFileDescriptor,
                       ZFMP_IN(const zfchar *, fileDescriptor),
                       ZFMP_IN(const ZFSerializableData &, serializableData),
                       ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull))
{
    zfstring ioType = ZFSerializableDataIOFileDescriptorDetect(fileDescriptor);
    if(ioType.isEmpty())
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, zfText("unable to detect ioType for \"%s\""), fileDescriptor);
        return zffalse;
    }
    ZFOutputCallback output = ZFOutputCallbackForFileDescriptor(fileDescriptor);
    if(!output.callbackIsValid())
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, zfText("unable to open output for \"%s\""), fileDescriptor);
        return zffalse;
    }
    return ZFSerializableDataToIO(output, ioType, serializableData, outErrorHint);
}

ZF_NAMESPACE_GLOBAL_END

