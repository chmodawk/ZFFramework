/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFFileDescriptor.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
zfclassPOD _ZFP_ZFFileDescriptorCallbackData
{
public:
    ZFFileDescriptorInputCallbackGetter inputCallbackGetter;
    ZFFileDescriptorOutputCallbackGetter outputCallbackGetter;
};

ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFFileDescriptorTypeHolder, ZFLevelZFFrameworkStatic)
{
}
public:
    ZFCoreMap fileDescriptorTypeMap; // _ZFP_ZFFileDescriptorCallbackData *
ZF_GLOBAL_INITIALIZER_END(ZFFileDescriptorTypeHolder)
#define _ZFP_ZFFileDescriptorTypeMap (ZF_GLOBAL_INITIALIZER_INSTANCE(ZFFileDescriptorTypeHolder)->fileDescriptorTypeMap)

static _ZFP_ZFFileDescriptorCallbackData *_ZFP_ZFFileDescriptorTypeFind(ZF_IN const zfchar *fileDescriptorType)
{
    return _ZFP_ZFFileDescriptorTypeMap.get<_ZFP_ZFFileDescriptorCallbackData *>(fileDescriptorType);
}

// ============================================================
ZFInputCallback _ZFP_ZFInputCallbackForFileDescriptor(ZF_IN const ZFCallerInfo &callerInfo,
                                                      ZF_IN const zfchar *fileDescriptor,
                                                      ZF_IN_OPT zfindex fileDescriptorLen /* = zfindexMax() */,
                                                      ZF_IN_OPT ZFFileOpenOptionFlags flags /* = ZFFileOpenOption::e_Read */,
                                                      ZF_IN_OPT const ZFFileBOMList &autoSkipBOMTable /* = ZFFileBOMListDefault() */)
{
    ZFInputCallback ret = ZFCallbackNullDetail(callerInfo);
    if(fileDescriptor == zfnull)
    {
        return ret;
    }
    const zfchar *typeStart = zfnull;
    zfindex typeLength = 0;
    const zfchar *dataStart = zfnull;
    zfindex dataLength = 0;
    {
        const zfchar *p = fileDescriptor;
        const zfchar *pEnd = ((fileDescriptorLen == zfindexMax()) ? p + zfslen(fileDescriptor) : p + fileDescriptorLen);
        for( ; p != pEnd; ++p)
        {
            if(*p == ':')
            {
                typeStart = fileDescriptor;
                typeLength = p - typeStart;
                dataStart = p + 1;
                dataLength = pEnd - dataStart;
                break;
            }
        }
        if(typeStart == zfnull)
        {
            return ret;
        }
    }
    const _ZFP_ZFFileDescriptorCallbackData *callbackData = _ZFP_ZFFileDescriptorTypeFind(zfstring(typeStart, typeLength).cString());
    if(callbackData == zfnull)
    {
        return ret;
    }
    ret = callbackData->inputCallbackGetter(
        dataStart, dataLength,
        flags,
        autoSkipBOMTable);
    ret.callbackCallerInfoSet(callerInfo);

    {
        zfstring callbackId;
        callbackId += zfText("ZFInputCallbackForFileDescriptor");
        ZFFileBOMListToString(callbackId, autoSkipBOMTable);
        callbackId += zfText(":");
        callbackId.append(fileDescriptor, fileDescriptorLen);
        ret.callbackIdSet(callbackId);
    }

    {
        zfbool success = zffalse;
        ZFSerializableData customData;
        customData.itemClassSet(ZFSerializableKeyword_node);
        do
        {
            ZFSerializableData fileDescriptorData;
            if(!zfstringToSerializableData(fileDescriptorData, fileDescriptor))
            {
                break;
            }
            fileDescriptorData.categorySet(ZFSerializableKeyword_ZFInputCallbackForFileDescriptor_fileDescriptor);
            customData.elementAdd(fileDescriptorData);

            if(flags != ZFFileOpenOption::e_Read)
            {
                ZFSerializableData flagsData;
                if(!ZFFileOpenOptionFlagsToSerializableData(flagsData, flags))
                {
                    break;
                }
                flagsData.categorySet(ZFSerializableKeyword_ZFInputCallbackForFileDescriptor_flags);
                customData.elementAdd(flagsData);
            }

            if(autoSkipBOMTable.objectCompare(ZFFileBOMListDefault()) != ZFCompareTheSame)
            {
                ZFSerializableData autoSkipBOMTableData;
                if(!zfstringToSerializableData(autoSkipBOMTableData, ZFFileBOMListToString(autoSkipBOMTable)))
                {
                    break;
                }
                autoSkipBOMTableData.categorySet(ZFSerializableKeyword_ZFInputCallbackForFileDescriptor_autoSkipBOMTable);
                customData.elementAdd(autoSkipBOMTableData);
            }

            success = zftrue;
        } while(zffalse);
        if(success)
        {
            ret.callbackSerializeCustomTypeSet(ZFCallbackSerializeCustomType_ZFInputCallbackForFileDescriptor);
            ret.callbackSerializeCustomDataSet(customData);
        }
    }

    return ret;
}
ZFMETHOD_FUNC_DEFINE_4(ZFInputCallback, ZFInputCallbackForFileDescriptor,
                       ZFMP_IN(const zfchar *, fileDescriptor),
                       ZFMP_IN_OPT(zfindex, fileDescriptorLen, zfindexMax()),
                       ZFMP_IN_OPT(ZFFileOpenOptionFlags, flags, ZFFileOpenOption::e_Read),
                       ZFMP_IN_OPT(const ZFFileBOMList &, autoSkipBOMTable, ZFFileBOMListDefault()))
{
    return ZFInputCallbackForFileDescriptor(fileDescriptor, fileDescriptorLen, flags, autoSkipBOMTable);
}
ZFCALLBACK_SERIALIZE_CUSTOM_TYPE_DEFINE(ZFCallbackSerializeCustomTypeId_ZFInputCallbackForFileDescriptor)
{
    const ZFSerializableData *fileDescriptorData = ZFSerializableUtil::requireElementByCategory(
        serializableData, ZFSerializableKeyword_ZFInputCallbackForFileDescriptor_fileDescriptor, outErrorHint, outErrorPos);
    if(fileDescriptorData == zfnull)
    {
        return zffalse;
    }
    const zfchar *fileDescriptor = zfnull;
    if(!zfstringFromSerializableData(fileDescriptor, *fileDescriptorData, outErrorHint, outErrorPos))
    {
        return zffalse;
    }

    ZFFileOpenOptionFlags flags = ZFFileOpenOption::e_Read;
    {
        const ZFSerializableData *flagsData = ZFSerializableUtil::checkElementByCategory(serializableData, ZFSerializableKeyword_ZFInputCallbackForFileDescriptor_flags);
        if(flagsData != zfnull && !ZFFileOpenOptionFlagsFromSerializableData(flags, *flagsData, outErrorHint, outErrorPos))
        {
            return zffalse;
        }
    }

    ZFFileBOMList BOMList;
    {
        const ZFSerializableData *autoSkipBOMTableData = ZFSerializableUtil::checkElementByCategory(serializableData, ZFSerializableKeyword_ZFInputCallbackForFileDescriptor_autoSkipBOMTable);
        zfstring BOMStringList;
        if(autoSkipBOMTableData != zfnull)
        {
            if(!zfstringFromSerializableData(BOMStringList, *autoSkipBOMTableData, outErrorHint, outErrorPos))
            {
                return zffalse;
            }
            BOMList.removeAll();

            if(!ZFFileBOMListFromString(BOMList, BOMStringList))
            {
                ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, *autoSkipBOMTableData, zfText("format BOM list error"));
                return zffalse;
            }
        }
        else
        {
            BOMList.addFrom(ZFFileBOMListDefault());
        }
    }

    serializableData.resolveMark();

    result = ZFInputCallbackForFileDescriptor(fileDescriptor, zfindexMax(), flags, BOMList);
    return zftrue;
}

// ============================================================
ZFOutputCallback _ZFP_ZFOutputCallbackForFileDescriptor(ZF_IN const ZFCallerInfo &callerInfo,
                                                        ZF_IN const zfchar *fileDescriptor,
                                                        ZF_IN_OPT zfindex fileDescriptorLen /* = zfindexMax() */,
                                                        ZF_IN_OPT ZFFileOpenOptionFlags flags /* = ZFFileOpenOption::e_Create */)
{
    ZFOutputCallback ret = ZFCallbackNullDetail(callerInfo);
    if(fileDescriptor == zfnull)
    {
        return ret;
    }
    const zfchar *typeStart = zfnull;
    zfindex typeLength = 0;
    const zfchar *dataStart = zfnull;
    zfindex dataLength = 0;
    {
        const zfchar *p = fileDescriptor;
        const zfchar *pEnd = ((fileDescriptorLen == zfindexMax()) ? p + zfslen(fileDescriptor) : p + fileDescriptorLen);
        for( ; p != pEnd; ++p)
        {
            if(*p == ':')
            {
                typeStart = fileDescriptor;
                typeLength = p - typeStart;
                dataStart = p + 1;
                dataLength = pEnd - dataStart;
                break;
            }
        }
        if(typeStart == zfnull)
        {
            return ret;
        }
    }
    const _ZFP_ZFFileDescriptorCallbackData *callbackData = _ZFP_ZFFileDescriptorTypeFind(zfstring(typeStart, typeLength).cString());
    if(callbackData == zfnull)
    {
        return ret;
    }
    ret = callbackData->outputCallbackGetter(
        dataStart, dataLength,
        flags);
    ret.callbackCallerInfoSet(callerInfo);

    {
        zfbool success = zffalse;
        ZFSerializableData customData;
        customData.itemClassSet(ZFSerializableKeyword_node);
        do
        {
            ZFSerializableData fileDescriptorData;
            if(!zfstringToSerializableData(fileDescriptorData, fileDescriptor))
            {
                break;
            }
            fileDescriptorData.categorySet(ZFSerializableKeyword_ZFOutputCallbackForFileDescriptor_fileDescriptor);
            customData.elementAdd(fileDescriptorData);

            if(flags != ZFFileOpenOption::e_Create)
            {
                ZFSerializableData flagsData;
                if(!ZFFileOpenOptionFlagsToSerializableData(flagsData, flags))
                {
                    break;
                }
                flagsData.categorySet(ZFSerializableKeyword_ZFOutputCallbackForFileDescriptor_flags);
                customData.elementAdd(flagsData);
            }

            success = zftrue;
        } while(zffalse);
        if(success)
        {
            ret.callbackSerializeCustomTypeSet(ZFCallbackSerializeCustomType_ZFOutputCallbackForFileDescriptor);
            ret.callbackSerializeCustomDataSet(customData);
        }
    }

    return ret;
}
ZFMETHOD_FUNC_DEFINE_3(ZFOutputCallback, ZFOutputCallbackForFileDescriptor,
                       ZFMP_IN(const zfchar *, fileDescriptor),
                       ZFMP_IN_OPT(zfindex, fileDescriptorLen, zfindexMax()),
                       ZFMP_IN_OPT(ZFFileOpenOptionFlags, flags, ZFFileOpenOption::e_Create))
{
    return ZFOutputCallbackForFileDescriptor(fileDescriptor, fileDescriptorLen, flags);
}
ZFCALLBACK_SERIALIZE_CUSTOM_TYPE_DEFINE(ZFCallbackSerializeCustomTypeId_ZFOutputCallbackForFileDescriptor)
{
    const ZFSerializableData *fileDescriptorData = ZFSerializableUtil::requireElementByCategory(
        serializableData, ZFSerializableKeyword_ZFOutputCallbackForFileDescriptor_fileDescriptor, outErrorHint, outErrorPos);
    if(fileDescriptorData == zfnull)
    {
        return zffalse;
    }
    const zfchar *fileDescriptor = zfnull;
    if(!zfstringFromSerializableData(fileDescriptor, *fileDescriptorData, outErrorHint, outErrorPos))
    {
        return zffalse;
    }

    ZFFileOpenOptionFlags flags = ZFFileOpenOption::e_Create;
    {
        const ZFSerializableData *flagsData = ZFSerializableUtil::checkElementByCategory(serializableData, ZFSerializableKeyword_ZFOutputCallbackForFileDescriptor_flags);
        if(flagsData != zfnull && !ZFFileOpenOptionFlagsFromSerializableData(flags, *flagsData, outErrorHint, outErrorPos))
        {
            return zffalse;
        }
    }
    serializableData.resolveMark();

    result = ZFOutputCallbackForFileDescriptor(fileDescriptor, zfindexMax(), flags);
    return zftrue;
}

void ZFFileDescriptorTypeRegister(ZF_IN const zfchar *descriptorType,
                                  ZF_IN ZFFileDescriptorInputCallbackGetter inputCallbackGetter,
                                  ZF_IN ZFFileDescriptorOutputCallbackGetter outputCallbackGetter)
{
    _ZFP_ZFFileDescriptorCallbackData *callbackData = zfnew(_ZFP_ZFFileDescriptorCallbackData);
    callbackData->inputCallbackGetter = inputCallbackGetter;
    callbackData->outputCallbackGetter = outputCallbackGetter;
    _ZFP_ZFFileDescriptorTypeMap.set(descriptorType, ZFCorePointerForObject<_ZFP_ZFFileDescriptorCallbackData *>(callbackData));
}
void ZFFileDescriptorTypeUnregister(ZF_IN const zfchar *descriptorType)
{
    _ZFP_ZFFileDescriptorTypeMap.remove(descriptorType);
}

void ZFFileDescriptorTypeGetAllT(ZF_OUT ZFCoreArray<const zfchar *> &ret)
{
    _ZFP_ZFFileDescriptorTypeMap.allKeyT(ret);
}

ZF_NAMESPACE_GLOBAL_END

