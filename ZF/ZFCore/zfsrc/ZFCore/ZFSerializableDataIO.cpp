/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFSerializableDataIO.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfclassPOD _ZFP_ZFSerializableDataIOData
{
public:
    ZFSerializableDataFromIOCallback fromCallback;
    ZFSerializableDataToIOCallback toCallback;
};

ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFSerializableDataIODataHolder, ZFLevelZFFrameworkStatic)
{
}
public:
    ZFCoreMap dataMap; // _ZFP_ZFSerializableDataIOData
ZF_GLOBAL_INITIALIZER_END(ZFSerializableDataIODataHolder)

// ============================================================
ZFMETHOD_FUNC_DEFINE_4(zfbool, ZFSerializableDataFromIO,
                       ZFMP_OUT(ZFSerializableData &, serializableData),
                       ZFMP_IN(const zfchar *, ioType),
                       ZFMP_IN(const ZFInputCallback &, input),
                       ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull))
{
    if(!input.callbackIsValid())
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, zfText("invalid callback"));
        return zffalse;
    }
    ZFSerializableDataFromIOCallback fromCallback = ZFSerializableDataFromIOCallbackGet(ioType);
    if(fromCallback == zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, zfText("no such ioType: \"%s\""), ioType);
        return zffalse;
    }
    return fromCallback(serializableData, input, outErrorHint);
}
ZFMETHOD_FUNC_DEFINE_3(ZFSerializableData, ZFSerializableDataFromIO,
                       ZFMP_IN(const zfchar *, ioType),
                       ZFMP_IN(const ZFInputCallback &, input),
                       ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull))
{
    ZFSerializableData ret;
    if(ZFSerializableDataFromIO(ret, ioType, input, outErrorHint))
    {
        return ret;
    }
    else
    {
        return ZFSerializableData();
    }
}
ZFMETHOD_FUNC_DEFINE_4(zfbool, ZFSerializableDataToIO,
                       ZFMP_IN_OUT(const ZFOutputCallback &, output),
                       ZFMP_IN(const zfchar *, ioType),
                       ZFMP_IN(const ZFSerializableData &, serializableData),
                       ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull))
{
    if(!output.callbackIsValid())
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, zfText("invalid callback"));
        return zffalse;
    }
    ZFSerializableDataToIOCallback toCallback = ZFSerializableDataToIOCallbackGet(ioType);
    if(toCallback == zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, zfText("no such ioType: \"%s\""), ioType);
        return zffalse;
    }
    return toCallback(output, serializableData, outErrorHint);
}

void ZFSerializableDataIORegister(ZF_IN const zfchar *ioType,
                                  ZF_IN ZFSerializableDataFromIOCallback fromCallback,
                                  ZF_IN ZFSerializableDataToIOCallback toCallback)
{
    zfCoreAssert(!zfscmpTheSame(ioType, zfText("")));
    zfCoreAssert(fromCallback != zfnull);
    zfCoreAssert(toCallback != zfnull);

    ZF_GLOBAL_INITIALIZER_CLASS(ZFSerializableDataIODataHolder) *d = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFSerializableDataIODataHolder);
    _ZFP_ZFSerializableDataIOData *data = zfnew(_ZFP_ZFSerializableDataIOData);
    data->fromCallback = fromCallback;
    data->toCallback = toCallback;
    d->dataMap.set(ioType, ZFCorePointerForObject<_ZFP_ZFSerializableDataIOData *>(data));
}
void ZFSerializableDataIOUnregister(ZF_IN const zfchar *ioType)
{
    ZF_GLOBAL_INITIALIZER_CLASS(ZFSerializableDataIODataHolder) *d = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFSerializableDataIODataHolder);
    d->dataMap.remove(ioType);
}

ZFSerializableDataFromIOCallback ZFSerializableDataFromIOCallbackGet(ZF_IN const zfchar *ioType)
{
    ZF_GLOBAL_INITIALIZER_CLASS(ZFSerializableDataIODataHolder) *d = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFSerializableDataIODataHolder);
    _ZFP_ZFSerializableDataIOData *data = d->dataMap.get<_ZFP_ZFSerializableDataIOData *>(ioType);
    if(data != zfnull)
    {
        return data->fromCallback;
    }
    else
    {
        return zfnull;
    }
}
ZFSerializableDataToIOCallback ZFSerializableDataToIOCallbackGet(ZF_IN const zfchar *ioType)
{
    ZF_GLOBAL_INITIALIZER_CLASS(ZFSerializableDataIODataHolder) *d = ZF_GLOBAL_INITIALIZER_INSTANCE(ZFSerializableDataIODataHolder);
    _ZFP_ZFSerializableDataIOData *data = d->dataMap.get<_ZFP_ZFSerializableDataIOData *>(ioType);
    if(data != zfnull)
    {
        return data->toCallback;
    }
    else
    {
        return zfnull;
    }
}

ZF_NAMESPACE_GLOBAL_END

