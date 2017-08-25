/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFFile.h"
#include "protocol/ZFProtocolZFFile.h"
#include "protocol/ZFProtocolZFFilePath.h"
#include "protocol/ZFProtocolZFFileReadWrite.h"
#include "protocol/ZFProtocolZFFileResProcess.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// _ZFP_ZFFileFindDataPrivate
zfclassNotPOD _ZFP_ZFFileFindDataPrivate
{
public:
    typedef enum
    {
        NotStarted,
        NormalFileFind,
        ResFileFind,
        ResAdditionalFileFind,
    } FindStatus;
public:
    zfindex refCount;
    zfstring resFindFirstPathSaved;
    ZFFileFindDataContainer d;
    _ZFP_ZFFileFindDataPrivate::FindStatus findStatus;
    zfstring resAdditionalPathWithSeparator;
    ZFFileFindDataContainer dForResAdditionPath;

public:
    void resAdditionalPathCopy(void)
    {
        d.parentPath = dForResAdditionPath.parentPath;
        if(zfstringFind(d.parentPath, resAdditionalPathWithSeparator) == 0)
        {
            d.parentPath.remove(0, resAdditionalPathWithSeparator.length());
        }

        d.path = dForResAdditionPath.path;
        if(zfstringFind(d.path, resAdditionalPathWithSeparator) == 0)
        {
            d.path.remove(0, resAdditionalPathWithSeparator.length());
        }

        d.name = dForResAdditionPath.name;
        d.fileIsFolder = dForResAdditionPath.fileIsFolder;
        d.nativeFd = dForResAdditionPath.nativeFd;
    }

public:
    _ZFP_ZFFileFindDataPrivate(void)
    : refCount(1)
    , resFindFirstPathSaved()
    , d()
    , findStatus(NotStarted)
    , resAdditionalPathWithSeparator()
    , dForResAdditionPath()
    {
    }
};

// ============================================================
// ZFFileFindData
/** @cond ZFPrivateDoc */
ZFFileFindData::ZFFileFindData(void)
: d(zfnew(_ZFP_ZFFileFindDataPrivate))
{
}
ZFFileFindData::ZFFileFindData(ZF_IN ZFFileFindData const &ref)
: d(ref.d)
{
    ++(d->refCount);
}
ZFFileFindData &ZFFileFindData::operator=(ZF_IN ZFFileFindData const &ref)
{
    ++(ref.d->refCount);
    --(d->refCount);
    if(d->refCount == 0)
    {
        zfdelete(d);
    }
    d = ref.d;
    return *this;
}
zfbool ZFFileFindData::operator==(ZF_IN ZFFileFindData const &ref) const
{
    return (zftrue
            && d->resFindFirstPathSaved == ref.d->resFindFirstPathSaved
            && d->d == ref.d->d
            && d->findStatus == ref.d->findStatus
            && d->resAdditionalPathWithSeparator == ref.d->resAdditionalPathWithSeparator
            && d->dForResAdditionPath == ref.d->dForResAdditionPath
        );
}
ZFFileFindData::~ZFFileFindData(void)
{
    --(d->refCount);
    if(d->refCount == 0)
    {
        zfdelete(d);
    }
}
/** @endcond */
const zfchar *ZFFileFindData::fileParentPath(void) const
{
    return d->d.parentPath.cString();
}
const zfchar *ZFFileFindData::filePath(void) const
{
    return d->d.path.cString();
}
const zfchar *ZFFileFindData::fileName(void) const
{
    return d->d.name.cString();
}
zfbool ZFFileFindData::fileIsFolder(void) const
{
    return d->d.fileIsFolder;
}
void ZFFileFindData::objectInfoT(ZF_IN_OUT zfstring &ret) const
{
    ret += ZFTOKEN_ZFObjectInfoLeft;
    if(this->fileIsFolder())
    {
        ret += zfText("(dir)");
    }
    ret += this->fileName();
    ret += ZFTOKEN_ZFObjectInfoRight;
}

// ============================================================
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFFileFindData, ZFFileFindData)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFileFindData, const zfchar *, fileParentPath)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFileFindData, const zfchar *, filePath)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFileFindData, const zfchar *, fileName)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFileFindData, zfbool, fileIsFolder)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFileFindData, void, objectInfoT, ZFMP_IN_OUT(zfstring &, ret))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFileFindData, zfstring, objectInfo)

// ============================================================
ZFEXPORT_VAR_READONLY_DEFINE(ZFFileToken, ZFFileTokenInvalid, zfnull)

// ============================================================
zfclassLikePOD _ZFP_ZFFileTokenForRes
{
public:
    ZFFileToken fd; // fd returned by ZFFile::fileOpen or ZFFile::resOpen
    zfstring resAdditionalPathWithSeparator; // not null if it's located in additional res path

public:
    _ZFP_ZFFileTokenForRes(void)
    : fd(ZFFileTokenInvalid())
    , resAdditionalPathWithSeparator()
    {
    }
};

// ============================================================
ZFENUM_DEFINE(ZFFileOpenOption)
ZFENUM_FLAGS_DEFINE(ZFFileOpenOption, ZFFileOpenOptionFlags)

// ============================================================
// implementation
#define _ZFP_ZFFileImpl ZFPROTOCOL_ACCESS(ZFFile)
#define _ZFP_ZFFilePathImpl ZFPROTOCOL_ACCESS(ZFFilePath)
#define _ZFP_ZFFileReadWriteImpl ZFPROTOCOL_ACCESS(ZFFileReadWrite)
#define _ZFP_ZFFileResProcessImpl ZFPROTOCOL_ACCESS(ZFFileResProcess)

// ============================================================
// ZFFile
const zfchar ZFFile::fileSeparator = '/';
const zfchar *ZFFile::fileSeparatorString = zfText("/");

ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR_READONLY(ZFFile, zfchar, fileSeparator)
ZFMETHOD_USER_REGISTER_FOR_ZFOBJECT_VAR_READONLY(ZFFile, const zfchar *, fileSeparatorString)

ZFOBJECT_REGISTER(ZFFile)

ZFOBSERVER_EVENT_REGISTER(ZFFile, SettingPathOnChange)
ZFOBSERVER_EVENT_REGISTER(ZFFile, StoragePathOnChange)
ZFOBSERVER_EVENT_REGISTER(ZFFile, StorageSharedPathOnChange)
ZFOBSERVER_EVENT_REGISTER(ZFFile, CachePathOnChange)
ZFOBSERVER_EVENT_REGISTER(ZFFile, CachePathBeforeClear)
ZFOBSERVER_EVENT_REGISTER(ZFFile, CachePathAfterClear)

ZFMETHOD_DEFINE_2(ZFFile, zfbool, filePathFormat,
                  ZFMP_OUT(zfstring &, ret),
                  ZFMP_IN(const zfchar *, src))
{
    if(src == zfnull)
    {
        return zffalse;
    }
    return _ZFP_ZFFileImpl->filePathFormat(ret, src);
}

ZFMETHOD_DEFINE_2(ZFFile, void, fileNameOf,
                  ZFMP_OUT(zfstring &, ret),
                  ZFMP_IN(const zfchar *, src))
{
    zfindex pos = zfstringFindReversely(src, zfindexMax, &ZFFile::fileSeparator, 1);
    if(pos != zfindexMax)
    {
        ret += (src + pos + 1);
    }
    else
    {
        ret += src;
    }
}
ZFMETHOD_DEFINE_2(ZFFile, void, fileNameOfWithoutExt,
                  ZFMP_OUT(zfstring &, ret),
                  ZFMP_IN(const zfchar *, src))
{
    zfindex len = zfslen(src);
    zfindex pos = zfstringFindReversely(src, len, &ZFFile::fileSeparator, 1);
    if(pos != zfindexMax)
    {
        ++pos;
    }
    else
    {
        pos = 0;
    }
    zfindex dotPos = zfstringFindReversely(src + pos, len - pos, zfText("."), 1);
    if(dotPos != zfindexMax)
    {
        ret.append(src + pos, dotPos - pos);
    }
    else
    {
        ret += (src + pos);
    }
}
ZFMETHOD_DEFINE_2(ZFFile, void, fileExtOf,
                  ZFMP_OUT(zfstring &, ret),
                  ZFMP_IN(const zfchar *, src))
{
    zfindex pos = zfstringFindReversely(src, zfindexMax, zfText("."), 1);
    if(pos != zfindexMax)
    {
        ret += (src + pos + 1);
    }
}
ZFMETHOD_DEFINE_2(ZFFile, void, fileParentPathOf,
                  ZFMP_OUT(zfstring &, ret),
                  ZFMP_IN(const zfchar *, src))
{
    zfindex pos = zfstringFindReversely(src, zfindexMax, &ZFFile::fileSeparator, 1);
    if(pos != zfindexMax)
    {
        ret.append(src, pos);
    }
}
ZFMETHOD_DEFINE_2(ZFFile, void, filePathComponentsOf,
                  ZFMP_OUT(ZFCoreArray<zfstring> &, ret),
                  ZFMP_IN(const zfchar *, src))
{
    zfindex len = zfslen(src);
    zfindex posL = 0;
    zfindex posR = len;
    do
    {
        posL = zfstringFindReversely(src, posR, &ZFFile::fileSeparator, 1);
        if(posL == zfindexMax)
        {
            if(posR > 0)
            {
                ret.add(zfstring(src, posR));
            }
            break;
        }
        else
        {
            if(posL != posR - 1)
            {
                ret.add(zfstring(src, posL + 1, posR - posL - 1));
            }
            posR = posL;
        }
    } while(zftrue);
}

ZFMETHOD_DEFINE_1(ZFFile, zfbool, fileIsExist,
                  ZFMP_IN(const zfchar *, path))
{
    if(path == zfnull)
    {
        return zffalse;
    }
    return _ZFP_ZFFileImpl->fileIsExist(path);
}

ZFMETHOD_DEFINE_1(ZFFile, zfbool, fileIsFolder,
                  ZFMP_IN(const zfchar *, path))
{
    if(path == zfnull)
    {
        return zffalse;
    }
    return _ZFP_ZFFileImpl->fileIsFolder(path);
}

ZFMETHOD_DEFINE_3(ZFFile, zfbool, filePathCreate,
                  ZFMP_IN(const zfchar *, path),
                  ZFMP_IN_OPT(zfbool, autoMakeParent, zftrue),
                  ZFMP_IN_OPT(zfstring *, errPos, zfnull))
{
    if(path == zfnull)
    {
        return zffalse;
    }
    return _ZFP_ZFFileImpl->filePathCreate(path, autoMakeParent, errPos);
}

ZFMETHOD_DEFINE_5(ZFFile, zfbool, fileCopy,
                  ZFMP_IN(const zfchar *, srcPath),
                  ZFMP_IN(const zfchar *, dstPath),
                  ZFMP_IN_OPT(zfbool, isRecursive, zftrue),
                  ZFMP_IN_OPT(zfbool, isForce, zffalse),
                  ZFMP_IN_OPT(zfstring *, errPos, zfnull))
{
    if(srcPath == zfnull || dstPath == zfnull)
    {
        return zffalse;
    }
    return _ZFP_ZFFileImpl->fileCopy(srcPath, dstPath, isRecursive, isForce, errPos);
}

ZFMETHOD_DEFINE_5(ZFFile, zfbool, fileMove,
                  ZFMP_IN(const zfchar *, srcPath),
                  ZFMP_IN(const zfchar *, dstPath),
                  ZFMP_IN_OPT(zfbool, isRecursive, zftrue),
                  ZFMP_IN_OPT(zfbool, isForce, zffalse),
                  ZFMP_IN_OPT(zfstring *, errPos, zfnull))
{
    if(srcPath == zfnull || dstPath == zfnull)
    {
        return zffalse;
    }
    return _ZFP_ZFFileImpl->fileMove(srcPath, dstPath, isRecursive, isForce, errPos);
}
ZFMETHOD_DEFINE_4(ZFFile, zfbool, fileRemove,
                  ZFMP_IN(const zfchar *, path),
                  ZFMP_IN_OPT(zfbool, isRecursive, zftrue),
                  ZFMP_IN_OPT(zfbool, isForce, zffalse),
                  ZFMP_IN_OPT(zfstring *, errPos, zfnull))
{
    if(path == zfnull)
    {
        return zffalse;
    }
    return _ZFP_ZFFileImpl->fileRemove(path, isRecursive, isForce, errPos);
}

ZFMETHOD_DEFINE_2(ZFFile, zfbool, fileFindFirst,
                  ZFMP_IN(const zfchar *, path),
                  ZFMP_IN_OUT(ZFFileFindData &, fd))
{
    if(path == zfnull)
    {
        return zffalse;
    }
    switch(fd.d->findStatus)
    {
        case _ZFP_ZFFileFindDataPrivate::NotStarted:
            break;
        case _ZFP_ZFFileFindDataPrivate::NormalFileFind:
            zfCoreCriticalMessage(zfTextA("have you forgot fileFindClose for last find operation?"));
            return zffalse;
        case _ZFP_ZFFileFindDataPrivate::ResFileFind:
        case _ZFP_ZFFileFindDataPrivate::ResAdditionalFileFind:
            zfCoreCriticalMessage(zfTextA("have you forgot resFindClose for last find operation?"));
            return zffalse;
        default:
            zfCoreCriticalShouldNotGoHere();
            return zffalse;
    }
    if(_ZFP_ZFFileImpl->fileFindFirst(path, fd.d->d))
    {
        fd.d->findStatus = _ZFP_ZFFileFindDataPrivate::NormalFileFind;
        return zftrue;
    }
    return zffalse;
}
ZFMETHOD_DEFINE_1(ZFFile, zfbool, fileFindNext,
                  ZFMP_IN_OUT(ZFFileFindData &, fd))
{
    switch(fd.d->findStatus)
    {
        case _ZFP_ZFFileFindDataPrivate::NotStarted:
            zfCoreCriticalMessage(zfTextA("have you forgot fileFindFirst?"));
            return zffalse;
        case _ZFP_ZFFileFindDataPrivate::NormalFileFind:
            break;
        case _ZFP_ZFFileFindDataPrivate::ResFileFind:
        case _ZFP_ZFFileFindDataPrivate::ResAdditionalFileFind:
            zfCoreCriticalMessage(zfTextA("fileFindNext while started by resFindFirst"));
            return zffalse;
        default:
            zfCoreCriticalShouldNotGoHere();
            return zffalse;
    }
    return _ZFP_ZFFileImpl->fileFindNext(fd.d->d);
}
ZFMETHOD_DEFINE_1(ZFFile, void, fileFindClose,
                  ZFMP_IN_OUT(ZFFileFindData &, fd))
{
    switch(fd.d->findStatus)
    {
        case _ZFP_ZFFileFindDataPrivate::NotStarted:
            zfCoreCriticalMessage(zfTextA("fileFindClose while not started by fileFindFirst or fileFindFirst failed"));
            return ;
        case _ZFP_ZFFileFindDataPrivate::NormalFileFind:
            break;
        case _ZFP_ZFFileFindDataPrivate::ResFileFind:
        case _ZFP_ZFFileFindDataPrivate::ResAdditionalFileFind:
            zfCoreCriticalMessage(zfTextA("fileFindClose while started by resFindFirst"));
            return ;
        default:
            zfCoreCriticalShouldNotGoHere();
            return ;
    }
    _ZFP_ZFFileImpl->fileFindClose(fd.d->d);
    fd.d->findStatus = _ZFP_ZFFileFindDataPrivate::NotStarted;
}

// ============================================================
ZFMETHOD_DEFINE_0(ZFFile, const zfchar *, modulePath)
{
    return _ZFP_ZFFilePathImpl->modulePath();
}
ZFMETHOD_DEFINE_0(ZFFile, const zfchar *, moduleFilePath)
{
    return _ZFP_ZFFilePathImpl->moduleFilePath();
}

ZFMETHOD_DEFINE_0(ZFFile, const zfchar *, settingPath)
{
    return _ZFP_ZFFilePathImpl->settingPath();
}
ZFMETHOD_DEFINE_1(ZFFile, void, settingPathSet,
                  ZFMP_IN_OPT(const zfchar *, path, zfnull))
{
    zfstring old = _ZFP_ZFFilePathImpl->settingPath();
    _ZFP_ZFFilePathImpl->settingPathSet(path);
    if(!old.isEmpty())
    {
        ZFPointerHolder *t = ZFPointerHolder::cacheAccess();
        t->holdedData = old.cString();
        ZFGlobalEventCenter::instance()->observerNotify(ZFFile::EventSettingPathOnChange(), t);
        ZFPointerHolder::cacheRelease(t);
    }
}

ZFMETHOD_DEFINE_0(ZFFile, const zfchar *, storagePath)
{
    return _ZFP_ZFFilePathImpl->storagePath();
}
ZFMETHOD_DEFINE_1(ZFFile, void, storagePathSet,
                  ZFMP_IN_OPT(const zfchar *, path, zfnull))
{
    zfstring old = _ZFP_ZFFilePathImpl->storagePath();
    _ZFP_ZFFilePathImpl->storagePathSet(path);
    if(!old.isEmpty())
    {
        ZFPointerHolder *t = ZFPointerHolder::cacheAccess();
        t->holdedData = old.cString();
        ZFGlobalEventCenter::instance()->observerNotify(ZFFile::EventStoragePathOnChange(), t);
        ZFPointerHolder::cacheRelease(t);
    }
}

ZFMETHOD_DEFINE_0(ZFFile, const zfchar *, storageSharedPath)
{
    return _ZFP_ZFFilePathImpl->storageSharedPath();
}
ZFMETHOD_DEFINE_1(ZFFile, void, storageSharedPathSet,
                  ZFMP_IN_OPT(const zfchar *, path, zfnull))
{
    zfstring old = _ZFP_ZFFilePathImpl->storageSharedPath();
    _ZFP_ZFFilePathImpl->storageSharedPathSet(path);
    if(!old.isEmpty())
    {
        ZFPointerHolder *t = ZFPointerHolder::cacheAccess();
        t->holdedData = old.cString();
        ZFGlobalEventCenter::instance()->observerNotify(ZFFile::EventStorageSharedPathOnChange(), t);
        ZFPointerHolder::cacheRelease(t);
    }
}

ZFMETHOD_DEFINE_0(ZFFile, const zfchar *, cachePath)
{
    return _ZFP_ZFFilePathImpl->cachePath();
}
ZFMETHOD_DEFINE_1(ZFFile, void, cachePathSet,
                  ZFMP_IN_OPT(const zfchar *, path, zfnull))
{
    zfstring old = _ZFP_ZFFilePathImpl->cachePath();
    _ZFP_ZFFilePathImpl->cachePathSet(path);
    if(!old.isEmpty())
    {
        ZFPointerHolder *t = ZFPointerHolder::cacheAccess();
        t->holdedData = old.cString();
        ZFGlobalEventCenter::instance()->observerNotify(ZFFile::EventCachePathOnChange(), t);
        ZFPointerHolder::cacheRelease(t);
    }
}

ZFMETHOD_DEFINE_0(ZFFile, void, cachePathClear)
{
    ZFGlobalEventCenter::instance()->observerNotify(ZFFile::EventCachePathBeforeClear());
    _ZFP_ZFFilePathImpl->cachePathClear();
    ZFGlobalEventCenter::instance()->observerNotify(ZFFile::EventCachePathAfterClear());
}

ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFFileCachePathAutoClear, ZFLevelZFFrameworkLow)
{
    ZFFile::cachePathClear();
}
ZF_GLOBAL_INITIALIZER_END(ZFFileCachePathAutoClear)

// ============================================================
ZFMETHOD_DEFINE_3(ZFFile, ZFFileToken, fileOpen,
                  ZFMP_IN(const zfchar *, filePath),
                  ZFMP_IN_OPT(ZFFileOpenOptionFlags, flag, ZFFileOpenOption::e_Read),
                  ZFMP_IN_OPT(zfbool, autoCreateParent, zftrue))
{
    if(autoCreateParent && (zffalse
        || ZFBitTest(flag, ZFFileOpenOption::e_Create)
        || ZFBitTest(flag, ZFFileOpenOption::e_Write)
        || ZFBitTest(flag, ZFFileOpenOption::e_Append)
        ))
    {
        ZFFile::filePathCreate(ZFFile::fileParentPathOf(filePath).cString());
    }
    return _ZFP_ZFFileReadWriteImpl->fileOpen(filePath, flag);
}
ZFMETHOD_DEFINE_1(ZFFile, zfbool, fileClose,
                  ZFMP_IN(ZFFileToken, token))
{
    return _ZFP_ZFFileReadWriteImpl->fileClose(token);
}
ZFMETHOD_DEFINE_1(ZFFile, zfindex, fileTell,
                  ZFMP_IN(ZFFileToken, token))
{
    return _ZFP_ZFFileReadWriteImpl->fileTell(token);
}
ZFMETHOD_DEFINE_3(ZFFile, zfbool, fileSeek,
                  ZFMP_IN(ZFFileToken, token),
                  ZFMP_IN(zfindex, byteSize),
                  ZFMP_IN_OPT(ZFSeekPos, position, ZFSeekPosBegin))
{
    return _ZFP_ZFFileReadWriteImpl->fileSeek(token, byteSize, position);
}
ZFMETHOD_DEFINE_3(ZFFile, zfindex, fileRead,
                  ZFMP_IN(ZFFileToken, token),
                  ZFMP_IN(void *, buf),
                  ZFMP_IN(zfindex, maxByteSize))
{
    return _ZFP_ZFFileReadWriteImpl->fileRead(token, buf, maxByteSize);
}
ZFMETHOD_DEFINE_3(ZFFile, zfindex, fileWrite,
                  ZFMP_IN(ZFFileToken, token),
                  ZFMP_IN(const void *, src),
                  ZFMP_IN_OPT(zfindex, maxByteSize, zfindexMax))
{
    if(src == zfnull)
    {
        return 0;
    }
    return _ZFP_ZFFileReadWriteImpl->fileWrite(token, src,
        (maxByteSize == zfindexMax) ? (sizeof(zfchar) * zfslen((const zfchar *)src)) : maxByteSize);
}
ZFMETHOD_DEFINE_1(ZFFile, void, fileFlush,
                  ZFMP_IN(ZFFileToken, token))
{
    return _ZFP_ZFFileReadWriteImpl->fileFlush(token);
}
ZFMETHOD_DEFINE_1(ZFFile, zfbool, fileEof,
                  ZFMP_IN(ZFFileToken, token))
{
    return _ZFP_ZFFileReadWriteImpl->fileEof(token);
}
ZFMETHOD_DEFINE_1(ZFFile, zfbool, fileError,
                  ZFMP_IN(ZFFileToken, token))
{
    return _ZFP_ZFFileReadWriteImpl->fileError(token);
}
ZFMETHOD_DEFINE_1(ZFFile, zfindex, fileSize,
                  ZFMP_IN(ZFFileToken, token))
{
    if(token == ZFFileTokenInvalid())
    {
        return zfindexMax;
    }
    zfindex saved = ZFFile::fileTell(token);
    if(saved == zfindexMax)
    {
        return zfindexMax;
    }
    ZFFile::fileSeek(token, 0, ZFSeekPosEnd);
    zfindex size = ZFFile::fileTell(token);
    ZFFile::fileSeek(token, saved, ZFSeekPosBegin);
    return size;
}

// ============================================================
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFFileResAdditionalPathDataHolder, ZFLevelZFFrameworkStatic)
{
}
public:
    ZFCoreArray<zfstring> resAdditionalPathList;
ZF_GLOBAL_INITIALIZER_END(ZFFileResAdditionalPathDataHolder)
#define _ZFP_ZFFileResAdditionalPathList (ZF_GLOBAL_INITIALIZER_INSTANCE(ZFFileResAdditionalPathDataHolder)->resAdditionalPathList)

ZFMETHOD_DEFINE_1(ZFFile, void, resAdditionalPathAdd,
                  ZFMP_IN(const zfchar *, path))
{
    if(path == zfnull || *path == '\0')
    {
        return ;
    }
    _ZFP_ZFFileResAdditionalPathList.add(path);
}
ZFMETHOD_DEFINE_1(ZFFile, void, resAdditionalPathRemove,
                  ZFMP_IN(const zfchar *, path))
{
    if(path == zfnull || *path == '\0')
    {
        return ;
    }
    _ZFP_ZFFileResAdditionalPathList.removeElement(path);
}
ZFMETHOD_DEFINE_0(ZFFile, ZFCoreArray<zfstring>, resAdditionalPathList)
{
    return _ZFP_ZFFileResAdditionalPathList;
}
ZFMETHOD_DEFINE_1(ZFFile, const zfchar *, resAdditionalPathCheck,
                  ZFMP_IN(const zfchar *, resPath))
{
    for(zfindex i = 0; i < _ZFP_ZFFileResAdditionalPathList.count(); ++i)
    {
        zfstring t;
        t += _ZFP_ZFFileResAdditionalPathList[i];
        t += ZFFile::fileSeparator;
        t += resPath;
        if(ZFFile::fileIsExist(t))
        {
            return _ZFP_ZFFileResAdditionalPathList[i].cString();
        }
    }
    return zfnull;
}

ZFMETHOD_DEFINE_5(ZFFile, zfbool, resCopy,
                  ZFMP_IN(const zfchar *, resPath),
                  ZFMP_IN(const zfchar *, dstPath),
                  ZFMP_IN_OPT(zfbool, isRecursive, zftrue),
                  ZFMP_IN_OPT(zfbool, isForce, zffalse),
                  ZFMP_IN_OPT(zfstring *, errPos, zfnull))
{
    const zfchar *resAdditionalPath = ZFFile::resAdditionalPathCheck(resPath);
    if(resAdditionalPath == zfnull)
    {
        return _ZFP_ZFFileResProcessImpl->resCopy(resPath, dstPath, isRecursive, isForce, errPos);
    }
    else
    {
        zfstring resPathTmp;
        resPathTmp += resAdditionalPath;
        resPathTmp += ZFFile::fileSeparator;
        resPathTmp += resPath;
        zfstring errPosTmp;
        zfbool ret = _ZFP_ZFFileImpl->fileCopy(resPathTmp, dstPath, isRecursive, isForce, &errPosTmp);
        if(errPos != zfnull)
        {
            if(!ret)
            {
                zfstring header;
                header += resAdditionalPath;
                header += ZFFile::fileSeparator;
                if(zfstringFind(errPosTmp, header) == 0)
                {
                    errPosTmp.remove(0, header.length());
                }
            }
            *errPos += errPosTmp;
        }
        return ret;
    }
}
ZFMETHOD_DEFINE_1(ZFFile, ZFFileToken, resOpen,
                  ZFMP_IN(const zfchar *, resPath))
{
    if(resPath == zfnull)
    {
        return ZFFileTokenInvalid();
    }

    _ZFP_ZFFileTokenForRes *ret = zfnew(_ZFP_ZFFileTokenForRes);
    const zfchar *resAdditionalPath = ZFFile::resAdditionalPathCheck(resPath);
    if(resAdditionalPath == zfnull)
    {
        ret->fd = _ZFP_ZFFileResProcessImpl->resOpen(resPath);
    }
    else
    {
        ret->resAdditionalPathWithSeparator = resAdditionalPath;
        ret->resAdditionalPathWithSeparator += ZFFile::fileSeparator;
        zfstring resPathTmp;
        resPathTmp += ret->resAdditionalPathWithSeparator;
        resPathTmp += resPath;
        ret->fd = _ZFP_ZFFileReadWriteImpl->fileOpen(resPathTmp);
    }
    if(ret->fd == ZFFileTokenInvalid())
    {
        zfdelete(ret);
        ret = zfnull;
    }
    return (ZFFileToken)ret;
}
ZFMETHOD_DEFINE_1(ZFFile, zfbool, resClose,
                  ZFMP_IN(ZFFileToken, token))
{
    if(token == ZFFileTokenInvalid())
    {
        return zffalse;
    }

    _ZFP_ZFFileTokenForRes *resToken = (_ZFP_ZFFileTokenForRes *)token;
    zfblockedDelete(resToken);
    if(resToken->resAdditionalPathWithSeparator.isEmpty())
    {
        return _ZFP_ZFFileResProcessImpl->resClose(resToken->fd);
    }
    else
    {
        return _ZFP_ZFFileReadWriteImpl->fileClose(resToken->fd);
    }
}
ZFMETHOD_DEFINE_1(ZFFile, zfindex, resTell,
                  ZFMP_IN(ZFFileToken, token))
{
    if(token == ZFFileTokenInvalid())
    {
        return zffalse;
    }

    _ZFP_ZFFileTokenForRes *resToken = (_ZFP_ZFFileTokenForRes *)token;
    if(resToken->resAdditionalPathWithSeparator.isEmpty())
    {
        return _ZFP_ZFFileResProcessImpl->resTell(resToken->fd);
    }
    else
    {
        return _ZFP_ZFFileReadWriteImpl->fileTell(resToken->fd);
    }
}
ZFMETHOD_DEFINE_3(ZFFile, zfbool, resSeek,
                  ZFMP_IN(ZFFileToken, token),
                  ZFMP_IN(zfindex, byteSize),
                  ZFMP_IN_OPT(ZFSeekPos, position, ZFSeekPosBegin))
{
    if(token == ZFFileTokenInvalid())
    {
        return zffalse;
    }

    _ZFP_ZFFileTokenForRes *resToken = (_ZFP_ZFFileTokenForRes *)token;
    if(resToken->resAdditionalPathWithSeparator.isEmpty())
    {
        return _ZFP_ZFFileResProcessImpl->resSeek(resToken->fd, byteSize, position);
    }
    else
    {
        return _ZFP_ZFFileReadWriteImpl->fileSeek(resToken->fd, byteSize, position);
    }
}
ZFMETHOD_DEFINE_3(ZFFile, zfindex, resRead,
                  ZFMP_IN(ZFFileToken, token),
                  ZFMP_IN(void *, buf),
                  ZFMP_IN(zfindex, maxByteSize))
{
    if(token == ZFFileTokenInvalid())
    {
        return zffalse;
    }

    _ZFP_ZFFileTokenForRes *resToken = (_ZFP_ZFFileTokenForRes *)token;
    if(resToken->resAdditionalPathWithSeparator.isEmpty())
    {
        return _ZFP_ZFFileResProcessImpl->resRead(resToken->fd, buf, maxByteSize);
    }
    else
    {
        return _ZFP_ZFFileReadWriteImpl->fileRead(resToken->fd, buf, maxByteSize);
    }
}
ZFMETHOD_DEFINE_1(ZFFile, zfbool, resEof,
                  ZFMP_IN(ZFFileToken, token))
{
    if(token == ZFFileTokenInvalid())
    {
        return zffalse;
    }

    _ZFP_ZFFileTokenForRes *resToken = (_ZFP_ZFFileTokenForRes *)token;
    if(resToken->resAdditionalPathWithSeparator.isEmpty())
    {
        return _ZFP_ZFFileResProcessImpl->resEof(resToken->fd);
    }
    else
    {
        return _ZFP_ZFFileReadWriteImpl->fileEof(resToken->fd);
    }
}
ZFMETHOD_DEFINE_1(ZFFile, zfbool, resError,
                  ZFMP_IN(ZFFileToken, token))
{
    if(token == ZFFileTokenInvalid())
    {
        return zffalse;
    }

    _ZFP_ZFFileTokenForRes *resToken = (_ZFP_ZFFileTokenForRes *)token;
    if(resToken->resAdditionalPathWithSeparator.isEmpty())
    {
        return _ZFP_ZFFileResProcessImpl->resError(resToken->fd);
    }
    else
    {
        return _ZFP_ZFFileReadWriteImpl->fileError(resToken->fd);
    }
}

ZFMETHOD_DEFINE_2(ZFFile, zfbool, resFindFirst,
                  ZFMP_IN(const zfchar *, resPath),
                  ZFMP_IN_OUT(ZFFileFindData &, fd))
{
    if(resPath == zfnull)
    {
        return zffalse;
    }
    switch(fd.d->findStatus)
    {
        case _ZFP_ZFFileFindDataPrivate::NotStarted:
            break;
        case _ZFP_ZFFileFindDataPrivate::NormalFileFind:
            zfCoreCriticalMessage(zfTextA("have you forgot fileFindClose for last find operation?"));
            return zffalse;
        case _ZFP_ZFFileFindDataPrivate::ResFileFind:
        case _ZFP_ZFFileFindDataPrivate::ResAdditionalFileFind:
            zfCoreCriticalMessage(zfTextA("have you forgot resFindClose for last find operation?"));
            return zffalse;
        default:
            zfCoreCriticalShouldNotGoHere();
            return zffalse;
    }

    fd.d->resFindFirstPathSaved = resPath;
    const zfchar *resAdditionalPath = ZFFile::resAdditionalPathCheck(resPath);
    if(resAdditionalPath == zfnull)
    {
        fd.d->resAdditionalPathWithSeparator.removeAll();
        if(_ZFP_ZFFileResProcessImpl->resFindFirst(resPath, fd.d->d))
        {
            fd.d->findStatus = _ZFP_ZFFileFindDataPrivate::ResFileFind;
            return zftrue;
        }
        return zffalse;
    }
    else
    {
        fd.d->resAdditionalPathWithSeparator = resAdditionalPath;
        fd.d->resAdditionalPathWithSeparator += ZFFile::fileSeparator;
        zfstring resPathTmp;
        resPathTmp += fd.d->resAdditionalPathWithSeparator;
        resPathTmp += resPath;
        if(_ZFP_ZFFileImpl->fileFindFirst(resPathTmp, fd.d->dForResAdditionPath))
        {
            fd.d->findStatus = _ZFP_ZFFileFindDataPrivate::ResFileFind;
            fd.d->resAdditionalPathCopy();
            return zftrue;
        }
        else
        {
            fd.d->resAdditionalPathWithSeparator.removeAll();
            if(_ZFP_ZFFileResProcessImpl->resFindFirst(resPath, fd.d->d))
            {
                fd.d->findStatus = _ZFP_ZFFileFindDataPrivate::ResFileFind;
                return zftrue;
            }
            return zffalse;
        }
    }
}
ZFMETHOD_DEFINE_1(ZFFile, zfbool, resFindNext,
                  ZFMP_IN_OUT(ZFFileFindData &, fd))
{
    switch(fd.d->findStatus)
    {
        case _ZFP_ZFFileFindDataPrivate::NotStarted:
            zfCoreCriticalMessage(zfTextA("have you forgot resFindFirst?"));
            return zffalse;
        case _ZFP_ZFFileFindDataPrivate::NormalFileFind:
            zfCoreCriticalMessage(zfTextA("resFindNext while started by fileFindFirst"));
            return zffalse;
        case _ZFP_ZFFileFindDataPrivate::ResFileFind:
        case _ZFP_ZFFileFindDataPrivate::ResAdditionalFileFind:
            break;
        default:
            zfCoreCriticalShouldNotGoHere();
            return zffalse;
    }

    if(fd.d->resAdditionalPathWithSeparator.isEmpty())
    {
        return _ZFP_ZFFileResProcessImpl->resFindNext(fd.d->d);
    }
    else
    {
        if(_ZFP_ZFFileImpl->fileFindNext(fd.d->dForResAdditionPath))
        {
            fd.d->resAdditionalPathCopy();
            return zftrue;
        }
        else
        {
            fd.d->resAdditionalPathWithSeparator.removeAll();
            if(_ZFP_ZFFileResProcessImpl->resFindFirst(fd.d->resFindFirstPathSaved, fd.d->d))
            {
                return zftrue;
            }
            return zffalse;
        }
    }
}
ZFMETHOD_DEFINE_1(ZFFile, void, resFindClose,
                  ZFMP_IN_OUT(ZFFileFindData &, fd))
{
    switch(fd.d->findStatus)
    {
        case _ZFP_ZFFileFindDataPrivate::NotStarted:
            zfCoreCriticalMessage(zfTextA("resFindClose while not started by resFindFirst or resFindFirst failed"));
            return ;
        case _ZFP_ZFFileFindDataPrivate::NormalFileFind:
            zfCoreCriticalMessage(zfTextA("resFindClose while started by fileFindFirst"));
            return ;
        case _ZFP_ZFFileFindDataPrivate::ResFileFind:
        case _ZFP_ZFFileFindDataPrivate::ResAdditionalFileFind:
            break;
        default:
            zfCoreCriticalShouldNotGoHere();
            return ;
    }

    if(fd.d->resAdditionalPathWithSeparator.isEmpty())
    {
        _ZFP_ZFFileResProcessImpl->resFindClose(fd.d->d);
    }
    else
    {
        _ZFP_ZFFileImpl->fileFindClose(fd.d->dForResAdditionPath);
    }
    fd.d->resAdditionalPathWithSeparator.removeAll();
    fd.d->findStatus = _ZFP_ZFFileFindDataPrivate::NotStarted;
}
ZFMETHOD_DEFINE_1(ZFFile, zfindex, resSize,
                  ZFMP_IN(ZFFileToken, token))
{
    if(token == ZFFileTokenInvalid())
    {
        return zfindexMax;
    }
    zfindex saved = ZFFile::resTell(token);
    ZFFile::resSeek(token, 0, ZFSeekPosEnd);
    zfindex size = ZFFile::resTell(token);
    ZFFile::resSeek(token, saved, ZFSeekPosBegin);
    return size;
}

ZF_NAMESPACE_GLOBAL_END

