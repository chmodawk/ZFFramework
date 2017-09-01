/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFFileCallback.h"

#include "ZFString.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
static zfindex _ZFP_ZFFileSkipBOMAndUpdateFileToken(ZF_IN ZFFileToken fileToken,
                                                    ZF_IN const ZFFileBOMList &autoSkipBOMTable,
                                                    ZF_IN zfbool resType)
{
    if(!resType)
    {
        zfindex ret = 0;
        if(!autoSkipBOMTable.isEmpty())
        {
            for(zfindex i = 0; i < autoSkipBOMTable.count(); ++i)
            {
                zfbyte tmp[ZFFileBOMMaxSize] = {0};
                ZFFile::fileRead(fileToken, tmp, ZFFileBOMMaxSize);
                ZFFile::fileSeek(fileToken, 0);
                const zfbyte *BOM = autoSkipBOMTable[i].BOM;
                zfindex len = zfslenA((const zfcharA *)BOM);
                if(zfmemcmp(tmp, BOM, len) == 0)
                {
                    ret = len;
                    ZFFile::fileSeek(fileToken, ret);
                    break;
                }
            }
        }
        return ret;
    }
    else
    {
        zfindex ret = 0;
        if(!autoSkipBOMTable.isEmpty())
        {
            for(zfindex i = 0; i < autoSkipBOMTable.count(); ++i)
            {
                zfbyte tmp[ZFFileBOMMaxSize] = {0};
                ZFFile::resRead(fileToken, tmp, ZFFileBOMMaxSize);
                ZFFile::resSeek(fileToken, 0);
                const zfbyte *BOM = autoSkipBOMTable[i].BOM;
                zfindex len = zfslenA((const zfcharA *)BOM);
                if(zfmemcmp(tmp, BOM, len) == 0)
                {
                    ret = len;
                    ZFFile::resSeek(fileToken, ret);
                    break;
                }
            }
        }
        return ret;
    }
}
static zfindex _ZFP_ZFFileCallbackSeek(ZF_IN_OUT ZFFileToken fileToken,
                                       ZF_IN zfindex BOMSize,
                                       ZF_IN zfindex byteSize,
                                       ZF_IN ZFSeekPos pos,
                                       ZF_IN zfbool resType)
{
    if(!resType)
    {
        if(fileToken == ZFFileTokenInvalid())
        {
            return zfindexMax();
        }
        zfindex fileSize = ZFFile::fileSize(fileToken);
        if(fileSize == zfindexMax())
        {
            return zfindexMax();
        }
        zfindex tmp = ZFIOCallbackCalcFSeek(BOMSize, fileSize, ZFFile::fileTell(fileToken), byteSize, pos);
        ZFFile::fileSeek(fileToken, tmp);
        return tmp - BOMSize;
    }
    else
    {
        if(fileToken == ZFFileTokenInvalid())
        {
            return zfindexMax();
        }
        zfindex fileSize = ZFFile::resSize(fileToken);
        if(fileSize == zfindexMax())
        {
            return zfindexMax();
        }
        zfindex tmp = ZFIOCallbackCalcFSeek(BOMSize, fileSize, ZFFile::resTell(fileToken), byteSize, pos);
        ZFFile::resSeek(fileToken, tmp);
        return tmp - BOMSize;
    }
}
static zfindex _ZFP_ZFFileCallbackTell(ZF_IN ZFFileToken fileToken,
                                       ZF_IN zfindex BOMSize,
                                       ZF_IN zfbool resType)
{
    if(!resType)
    {
        if(fileToken == ZFFileTokenInvalid())
        {
            return zfindexMax();
        }
        return ZFFile::fileTell(fileToken) - BOMSize;
    }
    else
    {
        if(fileToken == ZFFileTokenInvalid())
        {
            return zfindexMax();
        }
        return ZFFile::resTell(fileToken) - BOMSize;
    }
}

// ============================================================
zfclass _ZFP_ZFOutputCallbackForFileOwner : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_ZFOutputCallbackForFileOwner, ZFObject)

public:
    zfoverride
    virtual ZFObject *objectOnInit(void)
    {
        zfsuper::objectOnInit();
        this->autoFlushSize = 0;
        this->token = ZFFileTokenInvalid();
        this->notFlushedCount = 0;
        return this;
    }
    zfoverride
    virtual void objectOnDealloc(void)
    {
        if(this->token != ZFFileTokenInvalid())
        {
            ZFFile::fileClose(this->token);
            this->token = ZFFileTokenInvalid();
        }
        zfsuper::objectOnDealloc();
    }

public:
    virtual zfbool openFile(ZF_IN const zfchar *filePath,
                            ZF_IN ZFFileOpenOptionFlags flags)
    {
        if(this->token != ZFFileTokenInvalid())
        {
            ZFFile::fileClose(this->token);
        }
        this->token = ZFFile::fileOpen(filePath, flags);
        return (this->token != ZFFileTokenInvalid());
    }

    ZFMETHOD_DECLARE_2(zfindex, onOutput,
                       ZFMP_IN(const void *, s),
                       ZFMP_IN(zfindex, count))
    {
        ZFSTRINGENCODING_ASSERT(ZFStringEncoding::e_UTF8)
        zfindex ret = ZFFile::fileWrite(this->token, s, count);
        this->notFlushedCount += ret;
        if(this->notFlushedCount >= this->autoFlushSize)
        {
            this->notFlushedCount = 0;
            ZFFile::fileFlush(this->token);
        }
        return ret;
    }
    ZFMETHOD_DECLARE_2(zfindex, ioSeek,
                       ZFMP_IN(zfindex, byteSize),
                       ZFMP_IN(ZFSeekPos, pos))
    {
        return _ZFP_ZFFileCallbackSeek(this->token, 0, byteSize, pos, zffalse);
    }
    ZFMETHOD_DECLARE_0(zfindex, ioTell)
    {
        return _ZFP_ZFFileCallbackTell(this->token, 0, zffalse);
    }
    ZFMETHOD_DECLARE_0(zfindex, ioSize)
    {
        return ZFFile::fileSize(this->token) - ZFFile::fileTell(this->token);
    }

public:
    zfindex autoFlushSize;

private:
    ZFFileToken token;
    zfindex notFlushedCount;
};
zfclass _ZFP_ZFInputCallbackForFileOwner : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_ZFInputCallbackForFileOwner, ZFObject)

public:
    zfoverride
    virtual ZFObject *objectOnInit(void)
    {
        zfsuper::objectOnInit();
        this->token = ZFFileTokenInvalid();
        this->BOMSize = 0;
        return this;
    }
    zfoverride
    virtual void objectOnDealloc(void)
    {
        if(this->token != ZFFileTokenInvalid())
        {
            ZFFile::fileClose(this->token);
            this->token = ZFFileTokenInvalid();
        }
        zfsuper::objectOnDealloc();
    }

public:
    virtual zfbool openFile(ZF_IN const zfchar *filePath,
                            ZF_IN ZFFileOpenOptionFlags flags,
                            ZF_IN const ZFFileBOMList &autoSkipBOMTable)
    {
        if(this->token != ZFFileTokenInvalid())
        {
            ZFFile::fileClose(this->token);
        }
        this->token = ZFFile::fileOpen(filePath, flags);
        if(this->token != ZFFileTokenInvalid() && !autoSkipBOMTable.isEmpty())
        {
            this->BOMSize = _ZFP_ZFFileSkipBOMAndUpdateFileToken(this->token, autoSkipBOMTable, zffalse);
        }
        return (this->token != ZFFileTokenInvalid());
    }

    ZFMETHOD_DECLARE_2(zfindex, onInput,
                       ZFMP_IN(void *, buf),
                       ZFMP_IN(zfindex, count))
    {
        if(buf == zfnull)
        {
            return 0;
        }

        return ZFFile::fileRead(this->token, buf, count);
    }
    ZFMETHOD_DECLARE_2(zfindex, ioSeek,
                       ZFMP_IN(zfindex, byteSize),
                       ZFMP_IN(ZFSeekPos, pos))
    {
        return _ZFP_ZFFileCallbackSeek(this->token, this->BOMSize, byteSize, pos, zffalse);
    }
    ZFMETHOD_DECLARE_0(zfindex, ioTell)
    {
        return _ZFP_ZFFileCallbackTell(this->token, this->BOMSize, zffalse);
    }
    ZFMETHOD_DECLARE_0(zfindex, ioSize)
    {
        return ZFFile::fileSize(this->token) - ZFFile::fileTell(this->token);
    }

private:
    ZFFileToken token;
    zfindex BOMSize;
};
zfclass _ZFP_ZFInputCallbackForResFileOwner : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_ZFInputCallbackForResFileOwner, ZFObject)

public:
    zfoverride
    virtual ZFObject *objectOnInit(void)
    {
        zfsuper::objectOnInit();
        this->token = ZFFileTokenInvalid();
        return this;
    }
    zfoverride
    virtual void objectOnDealloc(void)
    {
        if(this->token != ZFFileTokenInvalid())
        {
            ZFFile::resClose(this->token);
            this->token = ZFFileTokenInvalid();
        }
        zfsuper::objectOnDealloc();
    }

public:
    virtual zfbool openFile(ZF_IN const zfchar *resFilePath,
                            ZF_IN const ZFFileBOMList &autoSkipBOMTable)
    {
        if(this->token != ZFFileTokenInvalid())
        {
            ZFFile::resClose(this->token);
        }
        this->token = ZFFile::resOpen(resFilePath);
        if(this->token != ZFFileTokenInvalid() && !autoSkipBOMTable.isEmpty())
        {
            this->BOMSize = _ZFP_ZFFileSkipBOMAndUpdateFileToken(this->token, autoSkipBOMTable, zftrue);
        }
        return (this->token != ZFFileTokenInvalid());
    }

    ZFMETHOD_DECLARE_2(zfindex, onInput,
                       ZFMP_IN(void *, buf),
                       ZFMP_IN(zfindex, count))
    {
        if(buf == zfnull)
        {
            return 0;
        }

        return ZFFile::resRead(this->token, buf, count);
    }
    ZFMETHOD_DECLARE_2(zfindex, ioSeek,
                       ZFMP_IN(zfindex, byteSize),
                       ZFMP_IN(ZFSeekPos, pos))
    {
        return _ZFP_ZFFileCallbackSeek(this->token, this->BOMSize, byteSize, pos, zftrue);
    }
    ZFMETHOD_DECLARE_0(zfindex, ioTell)
    {
        return _ZFP_ZFFileCallbackTell(this->token, this->BOMSize, zftrue);
    }
    ZFMETHOD_DECLARE_0(zfindex, ioSize)
    {
        return ZFFile::resSize(this->token) - ZFFile::resTell(this->token);
    }

private:
    ZFFileToken token;
    zfindex BOMSize;
};

// ============================================================
static ZFOutputCallback _ZFP_ZFOutputCallbackForFile_create(ZF_IN const ZFCallerInfo &callerInfo,
                                                            ZF_IN const zfchar *filePath,
                                                            ZF_IN ZFFileOpenOptionFlags flags,
                                                            ZF_IN zfindex autoFlushSize)
{
    _ZFP_ZFOutputCallbackForFileOwner *outputOwner = zfAlloc(_ZFP_ZFOutputCallbackForFileOwner);
    if(!outputOwner->openFile(filePath, flags))
    {
        zfRelease(outputOwner);
        return ZFCallbackNullDetail(callerInfo);
    }
    outputOwner->autoFlushSize = autoFlushSize;
    ZFOutputCallback ret = ZFCallbackForMemberMethodDetail(
        outputOwner, ZFMethodAccess(_ZFP_ZFOutputCallbackForFileOwner, onOutput),
        callerInfo);
    ret.callbackTagSet(ZFCallbackTagKeyword_ioOwner, outputOwner);
    zfRelease(outputOwner);

    ret.callbackTagSetMarkCached(ZFCallbackTagKeyword_filePath, zflineAllocWithoutLeakTest(ZFString, filePath));
    return ret;
}
static void _ZFP_ZFOutputCallbackForFile_storeImplData(ZF_IN_OUT ZFOutputCallback &ret,
                                                       ZF_IN const zfchar *filePathKeyName,
                                                       ZF_IN const zfchar *filePath,
                                                       ZF_IN ZFFileOpenOptionFlags flags,
                                                       ZF_IN zfindex autoFlushSize)
{
    zfbool success = zffalse;
    ZFSerializableData customData;
    customData.itemClassSet(ZFSerializableKeyword_node);
    do
    {
        ZFSerializableData filePathData;
        if(!zfstringToSerializableData(filePathData, filePath))
        {
            break;
        }
        filePathData.categorySet(filePathKeyName);
        customData.elementAdd(filePathData);

        if(flags != ZFFileOpenOption::e_Create)
        {
            ZFSerializableData flagsData;
            if(!ZFFileOpenOptionFlagsToSerializableData(flagsData, flags))
            {
                break;
            }
            flagsData.categorySet(ZFSerializableKeyword_ZFFileCallback_flags);
            customData.elementAdd(flagsData);
        }

        if(autoFlushSize != zfindexMax())
        {
            ZFSerializableData autoFlushSizeData;
            if(!zfindexToSerializableData(autoFlushSizeData, autoFlushSize))
            {
                break;
            }
            autoFlushSizeData.categorySet(ZFSerializableKeyword_ZFFileCallback_autoFlushSize);
            customData.elementAdd(autoFlushSizeData);
        }

        success = zftrue;
    } while(zffalse);
    if(success)
    {
        ret.callbackSerializeCustomTypeSet(ZFCallbackSerializeCustomType_ZFOutputCallbackForFile);
        ret.callbackSerializeCustomDataSet(customData);
    }
}
static zfbool _ZFP_ZFOutputCallbackForFile_parseImplData(ZF_IN const ZFSerializableData &serializableData,
                                                         ZF_IN const zfchar *filePathKeyName,
                                                         ZF_OUT const zfchar *&filePath,
                                                         ZF_OUT ZFFileOpenOptionFlags &flags,
                                                         ZF_OUT zfindex &autoFlushSize,
                                                         ZF_OUT zfstring *outErrorHint,
                                                         ZF_OUT ZFSerializableData *outErrorPos)
{
    const ZFSerializableData *filePathData = ZFSerializableUtil::requireElementByCategory(serializableData, filePathKeyName, outErrorHint, outErrorPos);
    if(filePathData == zfnull)
    {
        return zffalse;
    }
    filePath = zfnull;
    if(!zfstringFromSerializableData(filePath, *filePathData, outErrorHint, outErrorPos))
    {
        return zffalse;
    }

    flags = ZFFileOpenOption::e_Create;
    {
        const ZFSerializableData *flagsData = ZFSerializableUtil::checkElementByCategory(serializableData, ZFSerializableKeyword_ZFFileCallback_flags);
        if(flagsData != zfnull && !ZFFileOpenOptionFlagsFromSerializableData(flags, *flagsData, outErrorHint, outErrorPos))
        {
            return zffalse;
        }
    }
    autoFlushSize = zfindexMax();
    {
        const ZFSerializableData *autoFlushSizeData = ZFSerializableUtil::checkElementByCategory(serializableData, ZFSerializableKeyword_ZFFileCallback_autoFlushSize);
        if(autoFlushSizeData != zfnull && !zfindexFromSerializableData(autoFlushSize, *autoFlushSizeData, outErrorHint, outErrorPos))
        {
            return zffalse;
        }
    }
    serializableData.resolveMark();
    return zftrue;
}

// ============================================================
static ZFInputCallback _ZFP_ZFInputCallbackForFile_create(ZF_IN const ZFCallerInfo &callerInfo,
                                                          ZF_IN const zfchar *filePath,
                                                          ZF_IN ZFFileOpenOptionFlags flags,
                                                          ZF_IN const ZFFileBOMList &autoSkipBOMTable)
{
    _ZFP_ZFInputCallbackForFileOwner *inputOwner = zfAlloc(_ZFP_ZFInputCallbackForFileOwner);
    if(!inputOwner->openFile(filePath, flags, autoSkipBOMTable))
    {
        zfRelease(inputOwner);
        return ZFCallbackNullDetail(callerInfo);
    }
    ZFInputCallback ret = ZFCallbackForMemberMethodDetail(
        inputOwner, ZFMethodAccess(_ZFP_ZFInputCallbackForFileOwner, onInput),
        callerInfo);
    ret.callbackTagSet(ZFCallbackTagKeyword_ioOwner, inputOwner);
    zfRelease(inputOwner);

    ret.callbackTagSetMarkCached(ZFCallbackTagKeyword_filePath, zflineAllocWithoutLeakTest(ZFString, filePath));
    return ret;
}
static void _ZFP_ZFInputCallbackForFile_storeImplData(ZF_IN_OUT ZFInputCallback &ret,
                                                      ZF_IN const zfchar *filePathKeyName,
                                                      ZF_IN const zfchar *filePath,
                                                      ZF_IN const zfchar *callbackIdType,
                                                      ZF_IN const zfchar *callbackIdFilePath,
                                                      ZF_IN ZFFileOpenOptionFlags flags,
                                                      ZF_IN const ZFFileBOMList &autoSkipBOMTable)
{
    {
        zfstring callbackId;
        callbackId += callbackIdType;
        ZFFileBOMListToString(callbackId, autoSkipBOMTable);
        callbackId += zfText(":");
        callbackId += callbackIdFilePath;
        ret.callbackIdSet(callbackId);
    }

    {
        zfbool success = zffalse;
        ZFSerializableData customData;
        customData.itemClassSet(ZFSerializableKeyword_node);
        do
        {
            ZFSerializableData filePathData;
            if(!zfstringToSerializableData(filePathData, filePath))
            {
                break;
            }
            filePathData.categorySet(filePathKeyName);
            customData.elementAdd(filePathData);

            if(flags != ZFFileOpenOption::e_Read)
            {
                ZFSerializableData flagsData;
                if(!ZFFileOpenOptionFlagsToSerializableData(flagsData, flags))
                {
                    break;
                }
                flagsData.categorySet(ZFSerializableKeyword_ZFFileCallback_flags);
                customData.elementAdd(flagsData);
            }

            if(autoSkipBOMTable.objectCompare(ZFFileBOMListDefault()) != ZFCompareTheSame)
            {
                ZFSerializableData autoSkipBOMTableData;
                if(!zfstringToSerializableData(autoSkipBOMTableData, ZFFileBOMListToString(autoSkipBOMTable)))
                {
                    break;
                }
                autoSkipBOMTableData.categorySet(ZFSerializableKeyword_ZFFileCallback_autoSkipBOMTable);
                customData.elementAdd(autoSkipBOMTableData);
            }

            success = zftrue;
        } while(zffalse);
        if(success)
        {
            ret.callbackSerializeCustomTypeSet(ZFCallbackSerializeCustomType_ZFInputCallbackForFile);
            ret.callbackSerializeCustomDataSet(customData);
        }
    }
}
static zfbool _ZFP_ZFInputCallbackForFile_parseImplData(ZF_IN const ZFSerializableData &serializableData,
                                                        ZF_IN const zfchar *filePathKeyName,
                                                        ZF_OUT const zfchar *&filePath,
                                                        ZF_OUT ZFFileOpenOptionFlags &flags,
                                                        ZF_OUT ZFFileBOMList &autoSkipBOMTable,
                                                        ZF_OUT zfstring *outErrorHint,
                                                        ZF_OUT ZFSerializableData *outErrorPos)
{
    const ZFSerializableData *filePathData = ZFSerializableUtil::requireElementByCategory(serializableData, filePathKeyName, outErrorHint, outErrorPos);
    if(filePathData == zfnull)
    {
        return zffalse;
    }
    filePath = zfnull;
    if(!zfstringFromSerializableData(filePath, *filePathData, outErrorHint, outErrorPos))
    {
        return zffalse;
    }

    flags = ZFFileOpenOption::e_Read;
    {
        const ZFSerializableData *flagsData = ZFSerializableUtil::checkElementByCategory(serializableData, ZFSerializableKeyword_ZFFileCallback_flags);
        if(flagsData != zfnull && !ZFFileOpenOptionFlagsFromSerializableData(flags, *flagsData, outErrorHint, outErrorPos))
        {
            return zffalse;
        }
    }

    {
        const ZFSerializableData *autoSkipBOMTableData = ZFSerializableUtil::checkElementByCategory(serializableData, ZFSerializableKeyword_ZFFileCallback_autoSkipBOMTable);
        zfstring BOMStringList;
        if(autoSkipBOMTableData != zfnull)
        {
            if(!zfstringFromSerializableData(BOMStringList, *autoSkipBOMTableData, outErrorHint, outErrorPos))
            {
                return zffalse;
            }
            autoSkipBOMTable.removeAll();

            if(!ZFFileBOMListFromString(autoSkipBOMTable, BOMStringList))
            {
                ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, *autoSkipBOMTableData, zfText("format BOM list error"));
                return zffalse;
            }
        }
        else
        {
            autoSkipBOMTable.addFrom(ZFFileBOMListDefault());
        }
    }
    serializableData.resolveMark();
    return zftrue;
}

// ============================================================
static ZFInputCallback _ZFP_ZFInputCallbackForResFile_create(ZF_IN const ZFCallerInfo &callerInfo,
                                                             ZF_IN const zfchar *resFilePath,
                                                             ZF_IN const ZFFileBOMList &autoSkipBOMTable)
{
    _ZFP_ZFInputCallbackForResFileOwner *inputOwner = zfAlloc(_ZFP_ZFInputCallbackForResFileOwner);
    if(!inputOwner->openFile(resFilePath, autoSkipBOMTable))
    {
        zfRelease(inputOwner);
        return ZFCallbackNullDetail(callerInfo);
    }
    ZFInputCallback ret = ZFCallbackForMemberMethodDetail(
        inputOwner, ZFMethodAccess(_ZFP_ZFInputCallbackForResFileOwner, onInput),
        callerInfo);
    ret.callbackTagSet(ZFCallbackTagKeyword_ioOwner, inputOwner);
    zfRelease(inputOwner);

    ret.callbackTagSetMarkCached(ZFCallbackTagKeyword_resPath, zflineAllocWithoutLeakTest(ZFString, resFilePath));
    return ret;
}

// ============================================================
// ZFOutputCallbackForFile
ZFOutputCallback _ZFP_ZFOutputCallbackForFile(ZF_IN const ZFCallerInfo &callerInfo,
                                              ZF_IN const zfchar *filePath,
                                              ZF_IN_OPT ZFFileOpenOptionFlags flags /* = ZFFileOpenOptionCreate */,
                                              ZF_IN_OPT zfindex autoFlushSize /* = zfindexMax() */)
{
    ZFOutputCallback ret = _ZFP_ZFOutputCallbackForFile_create(callerInfo,
        filePath, flags, autoFlushSize);
    if(!ret.callbackIsValid())
    {
        return ret;
    }
    _ZFP_ZFOutputCallbackForFile_storeImplData(ret, ZFSerializableKeyword_ZFFileCallback_filePath, filePath, flags, autoFlushSize);
    return ret;
}
ZFMETHOD_FUNC_DEFINE_3(ZFOutputCallback, ZFOutputCallbackForFile,
                       ZFMP_IN(const zfchar *, filePath),
                       ZFMP_IN_OPT(ZFFileOpenOptionFlags, flags, ZFFileOpenOption::e_Create),
                       ZFMP_IN_OPT(zfindex, autoFlushSize, zfindexMax()))
{
    return ZFOutputCallbackForFile(filePath, flags, autoFlushSize);
}
ZFCALLBACK_SERIALIZE_CUSTOM_TYPE_DEFINE(ZFCallbackSerializeCustomTypeId_ZFOutputCallbackForFile)
{
    const zfchar *filePath = zfnull;
    ZFFileOpenOptionFlags flags = ZFFileOpenOption::e_Create;
    zfindex autoFlushSize = zfindexMax();
    if(!_ZFP_ZFOutputCallbackForFile_parseImplData(
            serializableData,
            ZFSerializableKeyword_ZFFileCallback_filePath, filePath,
            flags,
            autoFlushSize,
            outErrorHint, outErrorPos
        ))
    {
        return zffalse;
    }

    result = ZFOutputCallbackForFile(filePath, flags, autoFlushSize);
    if(!result.callbackIsValid())
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("failed to open file: %s"), filePath);
        return zffalse;
    }
    return zftrue;
}
// ============================================================
// ZFInputCallbackForFile
ZFInputCallback _ZFP_ZFInputCallbackForFile(ZF_IN const ZFCallerInfo &callerInfo,
                                            ZF_IN const zfchar *filePath,
                                            ZF_IN_OPT ZFFileOpenOptionFlags flags /* = ZFFileOpenOption::e_Read */,
                                            ZF_IN_OPT const ZFFileBOMList &autoSkipBOMTable /* = ZFFileBOMListDefault() */)
{
    ZFInputCallback ret = _ZFP_ZFInputCallbackForFile_create(callerInfo,
        filePath, flags, autoSkipBOMTable);
    if(!ret.callbackIsValid())
    {
        return ret;
    }
    _ZFP_ZFInputCallbackForFile_storeImplData(
        ret,
        ZFSerializableKeyword_ZFFileCallback_filePath, filePath,
        zfText("ZFInputCallbackForFile"), filePath,
        flags,
        autoSkipBOMTable);
    return ret;
}
ZFMETHOD_FUNC_DEFINE_3(ZFInputCallback, ZFInputCallbackForFile,
                       ZFMP_IN(const zfchar *, filePath),
                       ZFMP_IN_OPT(ZFFileOpenOptionFlags, flags, ZFFileOpenOption::e_Read),
                       ZFMP_IN_OPT(const ZFFileBOMList &, autoSkipBOMTable, ZFFileBOMListDefault()))
{
    return ZFInputCallbackForFile(filePath, flags, autoSkipBOMTable);
}
ZFCALLBACK_SERIALIZE_CUSTOM_TYPE_DEFINE(ZFCallbackSerializeCustomTypeId_ZFInputCallbackForFile)
{
    const zfchar *filePath = zfnull;
    ZFFileOpenOptionFlags flags = ZFFileOpenOption::e_Create;
    ZFFileBOMList autoSkipBOMTable;
    if(!_ZFP_ZFInputCallbackForFile_parseImplData(
            serializableData,
            ZFSerializableKeyword_ZFFileCallback_filePath, filePath,
            flags,
            autoSkipBOMTable,
            outErrorHint, outErrorPos
        ))
    {
        return zffalse;
    }

    result = ZFInputCallbackForFile(filePath, flags, autoSkipBOMTable);
    if(!result.callbackIsValid())
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("failed to open file: %s"), filePath);
        return zffalse;
    }
    return zftrue;
}

// ============================================================
// ZFInputCallbackForResFile
ZFInputCallback _ZFP_ZFInputCallbackForResFile(ZF_IN const ZFCallerInfo &callerInfo,
                                               ZF_IN const zfchar *resFilePath,
                                               ZF_IN_OPT const ZFFileBOMList &autoSkipBOMTable /* = ZFFileBOMListDefault() */)
{
    ZFInputCallback ret = _ZFP_ZFInputCallbackForResFile_create(callerInfo,
        resFilePath, autoSkipBOMTable);
    if(!ret.callbackIsValid())
    {
        return ret;
    }
    _ZFP_ZFInputCallbackForFile_storeImplData(
        ret,
        ZFSerializableKeyword_ZFFileCallback_filePath, resFilePath,
        zfText("ZFInputCallbackForResFile"), resFilePath,
        ZFFileOpenOption::e_Read,
        autoSkipBOMTable);
    return ret;
}
ZFMETHOD_FUNC_DEFINE_2(ZFInputCallback, ZFInputCallbackForResFile,
                       ZFMP_IN(const zfchar *, resFilePath),
                       ZFMP_IN_OPT(const ZFFileBOMList &, autoSkipBOMTable, ZFFileBOMListDefault()))
{
    return ZFInputCallbackForResFile(resFilePath, autoSkipBOMTable);
}
ZFCALLBACK_SERIALIZE_CUSTOM_TYPE_DEFINE(ZFCallbackSerializeCustomTypeId_ZFInputCallbackForResFile)
{
    const zfchar *filePath = zfnull;
    ZFFileOpenOptionFlags flags = ZFFileOpenOption::e_Create;
    ZFUNUSED(flags);
    ZFFileBOMList autoSkipBOMTable;
    if(!_ZFP_ZFInputCallbackForFile_parseImplData(
            serializableData,
            ZFSerializableKeyword_ZFFileCallback_filePath, filePath,
            flags,
            autoSkipBOMTable,
            outErrorHint, outErrorPos
        ))
    {
        return zffalse;
    }

    result = ZFInputCallbackForResFile(filePath, autoSkipBOMTable);
    if(!result.callbackIsValid())
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("failed to open res file: %s"), filePath);
        return zffalse;
    }
    return zftrue;
}

// ============================================================
static zfbool _ZFP_ZFFileCallbackForLocalFileCheckPath(ZF_OUT zfstring &result,
                                                       ZF_OUT zfbool &isResFile,
                                                       ZF_IN const ZFSerializableData &dataToCheckParentPath,
                                                       ZF_IN const zfchar *filePath)
{
    if(filePath == zfnull)
    {
        return zffalse;
    }
    const zfchar *parentPath = zfnull;
    {
        ZFSerializableData check = dataToCheckParentPath;
        zfbool hasParent = zftrue;
        do
        {
            ZFString *t = check.serializableDataTagGet<ZFString *>(ZFSerializableDataTagKeyword_filePath);
            if(t != zfnull)
            {
                parentPath = t->stringValue();
                isResFile = zffalse;
                break;
            }
            t = check.serializableDataTagGet<ZFString *>(ZFSerializableDataTagKeyword_resPath);
            if(t != zfnull)
            {
                parentPath = t->stringValue();
                isResFile = zftrue;
                break;
            }
            hasParent = check.serializableDataParent(check);
        } while(hasParent);
    }
    if(parentPath == zfnull)
    {
        return zffalse;
    }
    ZFFile::fileParentPathOf(result, parentPath);
    result += ZFFile::fileSeparator;
    result += filePath;
    return zftrue;
}

// ============================================================
// ZFOutputCallbackForLocalFile
ZFOutputCallback _ZFP_ZFOutputCallbackForLocalFile(ZF_IN const ZFCallerInfo &callerInfo,
                                                   ZF_IN const ZFSerializableData &dataToCheckParentPath,
                                                   ZF_IN const zfchar *localPath,
                                                   ZF_IN_OPT ZFFileOpenOptionFlags flags /* = ZFFileOpenOptionCreate */,
                                                   ZF_IN_OPT zfindex autoFlushSize /* = zfindexMax() */)
{
    zfstring fileAbsPath;
    zfbool isResFile = zffalse;
    if(!_ZFP_ZFFileCallbackForLocalFileCheckPath(fileAbsPath, isResFile, dataToCheckParentPath, localPath)
        || isResFile)
    {
        return ZFCallbackNullDetail(callerInfo);
    }

    ZFOutputCallback ret = _ZFP_ZFOutputCallbackForFile_create(callerInfo,
        fileAbsPath, flags, autoFlushSize);
    if(!ret.callbackIsValid())
    {
        return ret;
    }
    _ZFP_ZFOutputCallbackForFile_storeImplData(ret, ZFSerializableKeyword_ZFFileCallback_localPath, localPath, flags, autoFlushSize);
    return ret;
}
ZFMETHOD_FUNC_DEFINE_4(ZFOutputCallback, ZFOutputCallbackForLocalFile,
                       ZFMP_IN(const ZFSerializableData &, dataToCheckParentPath),
                       ZFMP_IN(const zfchar *, localPath),
                       ZFMP_IN_OPT(ZFFileOpenOptionFlags, flags, ZFFileOpenOption::e_Create),
                       ZFMP_IN_OPT(zfindex, autoFlushSize, zfindexMax()))
{
    return ZFOutputCallbackForLocalFile(dataToCheckParentPath, localPath, flags, autoFlushSize);
}
ZFCALLBACK_SERIALIZE_CUSTOM_TYPE_DEFINE(ZFCallbackSerializeCustomTypeId_ZFOutputCallbackForLocalFile)
{
    const zfchar *filePath = zfnull;
    ZFFileOpenOptionFlags flags = ZFFileOpenOption::e_Create;
    zfindex autoFlushSize = zfindexMax();
    if(!_ZFP_ZFOutputCallbackForFile_parseImplData(
            serializableData,
            ZFSerializableKeyword_ZFFileCallback_localPath, filePath,
            flags,
            autoFlushSize,
            outErrorHint, outErrorPos
        ))
    {
        return zffalse;
    }

    result = ZFOutputCallbackForLocalFile(serializableData, filePath, flags, autoFlushSize);
    if(!result.callbackIsValid())
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("failed to open local file: %s"), filePath);
        return zffalse;
    }
    return zftrue;
}
// ============================================================
// ZFInputCallbackForLocalFile
ZFInputCallback _ZFP_ZFInputCallbackForLocalFile(ZF_IN const ZFCallerInfo &callerInfo,
                                                 ZF_IN const ZFSerializableData &dataToCheckParentPath,
                                                 ZF_IN const zfchar *localPath,
                                                 ZF_IN_OPT ZFFileOpenOptionFlags flags /* = ZFFileOpenOption::e_Read */,
                                                 ZF_IN_OPT const ZFFileBOMList &autoSkipBOMTable /* = ZFFileBOMListDefault() */)
{
    zfstring fileAbsPath;
    zfbool isResFile = zffalse;
    if(!_ZFP_ZFFileCallbackForLocalFileCheckPath(fileAbsPath, isResFile, dataToCheckParentPath, localPath))
    {
        return ZFCallbackNullDetail(callerInfo);
    }

    ZFInputCallback ret;
    if(isResFile)
    {
        ret = _ZFP_ZFInputCallbackForResFile_create(callerInfo,
            fileAbsPath, autoSkipBOMTable);
    }
    else
    {
        ret = _ZFP_ZFInputCallbackForFile_create(callerInfo,
            fileAbsPath, flags, autoSkipBOMTable);
    }
    if(!ret.callbackIsValid())
    {
        return ret;
    }
    _ZFP_ZFInputCallbackForFile_storeImplData(
        ret,
        ZFSerializableKeyword_ZFFileCallback_localPath, localPath,
        zfText("ZFInputCallbackForLocalFile"), fileAbsPath,
        ZFFileOpenOption::e_Read,
        autoSkipBOMTable);
    return ret;
}
ZFMETHOD_FUNC_DEFINE_4(ZFInputCallback, ZFInputCallbackForLocalFile,
                       ZFMP_IN(const ZFSerializableData &, dataToCheckParentPath),
                       ZFMP_IN(const zfchar *, filePath),
                       ZFMP_IN_OPT(ZFFileOpenOptionFlags, flags, ZFFileOpenOption::e_Read),
                       ZFMP_IN_OPT(const ZFFileBOMList &, autoSkipBOMTable, ZFFileBOMListDefault()))
{
    return ZFInputCallbackForLocalFile(dataToCheckParentPath, filePath, flags, autoSkipBOMTable);
}
ZFCALLBACK_SERIALIZE_CUSTOM_TYPE_DEFINE(ZFCallbackSerializeCustomTypeId_ZFInputCallbackForLocalFile)
{
    const zfchar *filePath = zfnull;
    ZFFileOpenOptionFlags flags = ZFFileOpenOption::e_Create;
    ZFFileBOMList autoSkipBOMTable;
    if(!_ZFP_ZFInputCallbackForFile_parseImplData(
            serializableData,
            ZFSerializableKeyword_ZFFileCallback_localPath, filePath,
            flags,
            autoSkipBOMTable,
            outErrorHint, outErrorPos
        ))
    {
        return zffalse;
    }

    result = ZFInputCallbackForLocalFile(serializableData, filePath, flags, autoSkipBOMTable);
    if(!result.callbackIsValid())
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("failed to open local file: %s"), filePath);
        return zffalse;
    }
    return zftrue;
}

ZF_NAMESPACE_GLOBAL_END

