/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFCallback_common.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN


zfindex ZFIOCallbackCalcFSeek(ZF_IN zfindex offset,
                              ZF_IN zfindex length,
                              ZF_IN zfindex curPos,
                              ZF_IN zfindex seekByteSize,
                              ZF_IN ZFSeekPos seekPos)
{
    switch(seekPos)
    {
        case ZFSeekPosBegin:
            return ((offset + seekByteSize > length) ? length : (offset + seekByteSize));
        case ZFSeekPosCur:
            return ((curPos + seekByteSize > length) ? length : curPos + seekByteSize);
        case ZFSeekPosCurReversely:
            return ((offset + seekByteSize > curPos) ? offset : (curPos - seekByteSize));
        case ZFSeekPosEnd:
            return ((offset + seekByteSize > length) ? offset : (length - seekByteSize));
        default:
            zfCoreCriticalShouldNotGoHere();
            return zfindexMax();
    }
}

// ============================================================
zfindex ZFIOCallback::ioSeek(ZF_IN zfindex byteSize,
                             ZF_IN_OPT ZFSeekPos pos /* = ZFSeekPosBegin */) const
{
    ZFObject *owner = this->callbackTagGet(ZFCallbackTagKeyword_ioOwner);
    if(owner == zfnull)
    {
        return zfindexMax();
    }
    const ZFMethod *method = owner->classData()->methodForName(zfText("ioSeek"));
    if(method == zfnull)
    {
        return zfindexMax();
    }
    return method->execute<zfindex, zfindex, ZFSeekPos>(owner, byteSize, pos);
}
zfindex ZFIOCallback::ioTell(void) const
{
    ZFObject *owner = this->callbackTagGet(ZFCallbackTagKeyword_ioOwner);
    if(owner == zfnull)
    {
        return zfindexMax();
    }
    const ZFMethod *method = owner->classData()->methodForName(zfText("ioTell"));
    if(method == zfnull)
    {
        return zfindexMax();
    }
    return method->execute<zfindex>(owner);
}
zfindex ZFIOCallback::ioSize(void) const
{
    ZFObject *owner = this->callbackTagGet(ZFCallbackTagKeyword_ioOwner);
    if(owner == zfnull)
    {
        return zfindexMax();
    }
    const ZFMethod *method = owner->classData()->methodForName(zfText("ioSize"));
    if(method == zfnull)
    {
        return zfindexMax();
    }
    return method->execute<zfindex>(owner);
}

// ============================================================
// ZFOutputCallbackForString
zfclass _ZFP_ZFOutputCallbackForStringOwner : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_ZFOutputCallbackForStringOwner, ZFObject)

public:
    zfstring *pString;
    zfindex savedLength;
    ZFMETHOD_DECLARE_2(zfindex, onOutput,
                       ZFMP_IN(const void *, s),
                       ZFMP_IN(zfindex, count))
    {
        pString->append((const zfchar *)s, count);
        return count;
    }
    ZFMETHOD_DECLARE_2(zfindex, ioSeek,
                       ZFMP_IN(zfindex, byteSize),
                       ZFMP_IN(ZFSeekPos, pos))
    {
        zfindex tmp = ZFIOCallbackCalcFSeek(this->savedLength, this->pString->length(), this->pString->length(), byteSize, pos);
        this->pString->remove(tmp);
        return tmp - this->savedLength;
    }
    ZFMETHOD_DECLARE_0(zfindex, ioTell)
    {
        return ((this->pString->length() >= this->savedLength) ? (this->pString->length() - this->savedLength) : zfindexMax());
    }
    ZFMETHOD_DECLARE_0(zfindex, ioSize)
    {
        return this->ioTell();
    }
};
ZFOutputCallback _ZFP_ZFOutputCallbackForString(ZF_IN const ZFCallerInfo &callerInfo,
                                                ZF_IN zfstring &s)
{
    _ZFP_ZFOutputCallbackForStringOwner *owner = zfAlloc(_ZFP_ZFOutputCallbackForStringOwner);
    owner->pString = &s;
    owner->savedLength = owner->pString->length();
    ZFOutputCallback ret = ZFCallbackForMemberMethodDetail(
        owner, ZFMethodAccess(_ZFP_ZFOutputCallbackForStringOwner, onOutput),
        callerInfo);
    ret.callbackTagSet(ZFCallbackTagKeyword_ioOwner, owner);
    zfRelease(owner);
    return ret;
}

// ============================================================
// ZFOutputCallbackForBuffer
zfclass _ZFP_ZFOutputCallbackForBufferOwner : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_ZFOutputCallbackForBufferOwner, ZFObject)

public:
    zfbool autoAppendNullToken;
    zfbyte *pStart;
    zfbyte *pEnd; // autoAppendNullToken ? (buf + maxCount - 1) : (buf + maxCount)
    zfbyte *p;

public:
    ZFMETHOD_DECLARE_2(zfindex, onOutput,
                       ZFMP_IN(const void *, s),
                       ZFMP_IN(zfindex, count))
    {
        const zfbyte *pSrc = (const zfbyte *)s;
        if(count == zfindexMax())
        {
            while(*pSrc && p < pEnd)
            {
                *p = *pSrc;
                ++p;
                ++pSrc;
            }
            if(autoAppendNullToken)
            {
                *p = '\0';
            }
            return p - (const zfbyte *)s;
        }
        else
        {
            const zfbyte *pSrcEnd = (const zfbyte *)s + count;
            while(*pSrc && pSrc < pSrcEnd && p < pEnd)
            {
                *p = *pSrc;
                ++p;
                ++pSrc;
            }
            if(autoAppendNullToken)
            {
                *p = '\0';
            }
            return p - (const zfbyte *)s;
        }
    }
    ZFMETHOD_DECLARE_2(zfindex, ioSeek,
                       ZFMP_IN(zfindex, byteSize),
                       ZFMP_IN(ZFSeekPos, pos))
    {
        switch(pos)
        {
            case ZFSeekPosBegin:
            {
                if(pEnd > pStart && pStart + byteSize > pEnd)
                {
                    p = pEnd;
                }
                else
                {
                    p = pStart + byteSize;
                }
            }
                break;
            case ZFSeekPosCur:
            {
                if(pEnd > pStart && p + byteSize > pEnd)
                {
                    p = pEnd;
                }
                else
                {
                    p += byteSize;
                }
            }
                break;
            case ZFSeekPosCurReversely:
            {
                if(p - byteSize < pStart)
                {
                    p = pStart;
                }
                else
                {
                    p -= byteSize;
                }
            }
                break;
            case ZFSeekPosEnd:
            {
                if(pEnd <= pStart)
                {
                    return zffalse;
                }
                if(pEnd - byteSize < pStart)
                {
                    p = pStart;
                }
                else
                {
                    p = pEnd - byteSize;
                }
            }
                break;
            default:
                zfCoreCriticalShouldNotGoHere();
                return zfindexMax();
        }
        return p - pStart;
    }
    ZFMETHOD_DECLARE_0(zfindex, ioTell)
    {
        return p - pStart;
    }
    ZFMETHOD_DECLARE_0(zfindex, ioSize)
    {
        return ((pEnd > pStart) ? (pEnd - pStart) : zfindexMax());
    }
};
ZFOutputCallback _ZFP_ZFOutputCallbackForBuffer(ZF_IN const ZFCallerInfo &callerInfo,
                                                ZF_IN void *buf,
                                                ZF_IN_OPT zfindex maxCount /* = zfindexMax() */,
                                                ZF_IN_OPT zfbool autoAppendNullToken /* = zftrue */)
{
    if(buf == zfnull || maxCount == 0 || (maxCount == 1 && autoAppendNullToken))
    {
        return ZFCallbackNullDetail(callerInfo);
    }
    _ZFP_ZFOutputCallbackForBufferOwner *owner = zfAlloc(_ZFP_ZFOutputCallbackForBufferOwner);
    owner->autoAppendNullToken = autoAppendNullToken;
    owner->pStart = (zfbyte *)buf;
    if(maxCount == zfindexMax())
    {
        owner->pEnd = zfnull;
        --(owner->pEnd);
    }
    else
    {
        owner->pEnd = owner->pStart + maxCount;
        if(autoAppendNullToken)
        {
            --(owner->pEnd);
        }
    }
    owner->p = owner->pStart;
    ZFOutputCallback ret = ZFCallbackForMemberMethodDetail(
        owner, ZFMethodAccess(_ZFP_ZFOutputCallbackForBufferOwner, onOutput),
        callerInfo);
    ret.callbackTagSet(ZFCallbackTagKeyword_ioOwner, owner);
    zfRelease(owner);
    return ret;
}

// ============================================================
// ZFInputCallback
zfindex ZFInputCallbackReadChar(ZF_OUT zfchar *p, ZF_IN_OUT const ZFInputCallback &input)
{
    #if 0
        ZFSTRINGENCODING_ASSERT(ZFStringEncoding::e_UTF8)
    #endif

    if(input.execute(p, 1) != 1)
    {
        p[0] = '\0';
        return 0;
    }
    if((zfbyte)p[0] < 0x7F)
    {
        p[1] = '\0';
        return 1;
    }

    if(input.execute(p + 1, 1) != 1)
    {
        p[1] = '\0';
        return 1;
    }
    if((zfbyte)p[0] <= 0xDF && (zfbyte)p[1] <= 0xBF)
    {
        p[2] = '\0';
        return 2;
    }

    if(input.execute(p + 2, 1) != 1)
    {
        p[2] = '\0';
        return 2;
    }
    if((zfbyte)p[0] <= 0xEF && (zfbyte)p[1] <= 0xBF && (zfbyte)p[2] <= 0xBF)
    {
        p[3] = '\0';
        return 3;
    }

    if(input.execute(p + 3, 1) != 1)
    {
        p[3] = '\0';
        return 3;
    }
    if((zfbyte)p[0] <= 0xF7 && (zfbyte)p[1] <= 0xBF && (zfbyte)p[2] <= 0xBF && (zfbyte)p[3] <= 0xBF)
    {
        p[4] = '\0';
        return 4;
    }

    if(input.execute(p + 4, 1) != 1)
    {
        p[4] = '\0';
        return 4;
    }
    if((zfbyte)p[0] <= 0xFB && (zfbyte)p[1] <= 0xBF && (zfbyte)p[2] <= 0xBF && (zfbyte)p[3] <= 0xBF && (zfbyte)p[4] <= 0xBF)
    {
        p[5] = '\0';
        return 5;
    }

    if(input.execute(p + 5, 1) != 1)
    {
        p[5] = '\0';
        return 5;
    }
    if((zfbyte)p[0] <= 0xFD && (zfbyte)p[1] <= 0xBF && (zfbyte)p[2] <= 0xBF && (zfbyte)p[3] <= 0xBF && (zfbyte)p[4] <= 0xBF && (zfbyte)p[5] <= 0xBF)
    {
        p[6] = '\0';
        return 6;
    }

    if(input.execute(p + 6, 1) != 1)
    {
        p[6] = '\0';
        return 6;
    }
    if((zfbyte)p[0] <= 0xFE && (zfbyte)p[1] <= 0xBF && (zfbyte)p[2] <= 0xBF && (zfbyte)p[3] <= 0xBF && (zfbyte)p[4] <= 0xBF && (zfbyte)p[5] <= 0xBF && (zfbyte)p[6] <= 0xBF)
    {
        p[7] = '\0';
        return 7;
    }

    if(input.execute(p + 7, 1) != 1)
    {
        p[7] = '\0';
        return 7;
    }

    p[8] = '\0';
    return 8;
}
zfindex ZFInputCallbackReadChar(ZF_IN_OUT zfstring &buf, ZF_IN_OUT const ZFInputCallback &input)
{
    zfchar tmp[9] = {0};
    zfindex ret = ZFInputCallbackReadChar(tmp, input);
    buf += tmp;
    return ret;
}

ZFBuffer ZFInputCallbackReadToBuffer(ZF_IN_OUT const ZFInputCallback &input)
{
    if(!input.callbackIsValid())
    {
        return ZFBuffer();
    }

    ZFBuffer ret;
    zfindex totalSize = input.ioSize();
    if(totalSize != zfindexMax())
    {
        ret.bufferMalloc(totalSize + sizeof(zfcharW));
        if(input.execute(ret.buffer(), totalSize) != totalSize)
        {
            ret.bufferFree();
        }
        else
        {
            ret.bufferSizeSet(totalSize);
        }
    }
    else
    {
        #define _ZFP_ZFInputCallbackReadToBuffer_blockSize 256
        zfindex readCount = 0;
        zfindex size = 0;
        do
        {
            ret.bufferRealloc(ret.bufferSize() + _ZFP_ZFInputCallbackReadToBuffer_blockSize);
            readCount = input.execute(ret.bufferT<zfbyte *>() + size, _ZFP_ZFInputCallbackReadToBuffer_blockSize - sizeof(zfcharW));
            size += readCount;
            if(readCount < _ZFP_ZFInputCallbackReadToBuffer_blockSize - sizeof(zfcharW))
            {
                ret.bufferRealloc(size + sizeof(zfcharW));
                ret.bufferSizeSet(size);
                break;
            }
        } while(zftrue);
        #undef _ZFP_ZFInputCallbackReadToBuffer_blockSize
    }
    return ret;
}
zfindex ZFInputCallbackReadToOutput(ZF_IN_OUT const ZFOutputCallback &output,
                                    ZF_IN_OUT const ZFInputCallback &input)
{
    zfindex size = 0;
    if(input.callbackIsValid() && output.callbackIsValid())
    {
        #define _ZFP_ZFInputCallbackReadToOutput_blockSize 256
        zfchar buf[_ZFP_ZFInputCallbackReadToOutput_blockSize] = {0};
        zfindex readCount = 0;
        zfindex writeCount = 0;
        do
        {
            readCount = input.execute(buf, _ZFP_ZFInputCallbackReadToOutput_blockSize);
            writeCount = output.execute(buf, readCount);
            size += writeCount;
            if(readCount < _ZFP_ZFInputCallbackReadToOutput_blockSize || writeCount < readCount)
            {
                break;
            }
        } while(zftrue);
        #undef _ZFP_ZFInputCallbackReadToOutput_blockSize
    }
    return size;
}

zfbool ZFInputCallbackSkipChars(ZF_OUT zfchar *buf,
                                ZF_IN_OUT const ZFInputCallback &input,
                                ZF_IN_OPT const zfchar *charSet /* = zfText(" \t\r\n") */)
{
    zfindex charSetCount = zfslen(charSet);
    zfbool matched = zffalse;
    do
    {
        switch(ZFInputCallbackReadChar(buf, input))
        {
            case 0:
                return zffalse;
            case 1:
                break;
            default:
                return zftrue;
        }
        matched = zffalse;
        for(zfindex i = 0; i < charSetCount; ++i)
        {
            if(charSet[i] == buf[0])
            {
                matched = zftrue;
                break;
            }
        }
        if(!matched)
        {
            return zftrue;
        }
    } while(zftrue);
    return zffalse;
}
zfindex ZFInputCallbackReadUntil(ZF_IN_OUT zfstring &ret,
                                 ZF_IN_OUT const ZFInputCallback &input,
                                 ZF_IN_OPT const zfchar *charSet /* = zfText(" \t\r\n") */,
                                 ZF_IN_OPT zfindex maxCount /* = zfindexMax() */,
                                 ZF_OUT_OPT zfchar *firstCharMatchedCharSet /* = zfnull */)
{
    zfindex readCount = 0;
    if(firstCharMatchedCharSet != zfnull)
    {
        *firstCharMatchedCharSet = '\0';
    }
    if(input.callbackIsValid())
    {
        zfchar buf[9] = {0};
        zfindex charSetCount = zfslen(charSet);
        zfbool matched = zffalse;
        while(readCount < maxCount)
        {
            zfindex t = ZFInputCallbackReadChar(buf, input);
            if(t == 0)
            {
                break;
            }
            else if(t == 1)
            {
                matched = zffalse;
                for(zfindex i = 0; i < charSetCount; ++i)
                {
                    if(charSet[i] == buf[0])
                    {
                        matched = zftrue;
                        break;
                    }
                }
                if(matched)
                {
                    if(firstCharMatchedCharSet != zfnull)
                    {
                        *firstCharMatchedCharSet = buf[0];
                    }
                    break;
                }
            }

            ret += buf;
            readCount += t;
        }
    }
    return readCount;
}
zfindex ZFInputCallbackCheckMatch(ZF_IN const zfchar **tokens,
                                  ZF_IN zfindex tokenCount,
                                  ZF_IN_OUT const ZFInputCallback &input)
{
    zfindex ret = zfindexMax();
    if(input.callbackIsValid())
    {
        zfindex saved = input.ioTell();
        zfindex maxLen = 0;
        for(zfindex i = 0; i < tokenCount; ++i)
        {
            maxLen = zfmMax(maxLen, zfslen(tokens[i]));
        }
        zfchar *buf = (zfchar *)zfmalloc(sizeof(zfchar) * maxLen);
        zfblockedFree(buf);

        zfbool matched = zffalse;
        zfindex firstCharLen = ZFInputCallbackSkipChars(buf, input);
        zfindex matchedLen = 0;
        if(firstCharLen < maxLen)
        {
            input.execute(buf + firstCharLen, maxLen - firstCharLen);
            for(zfindex i = 0; i < tokenCount; ++i)
            {
                matchedLen = zfslen(tokens[i]);
                if(zfsncmp(tokens[i], buf, matchedLen) == 0)
                {
                    matched = zftrue;
                    ret = i;
                    break;
                }
            }
        }

        if(matched)
        {
            input.ioSeek(maxLen - matchedLen, ZFSeekPosCurReversely);
        }
        else
        {
            input.ioSeek(saved, ZFSeekPosBegin);
        }
    }
    return ret;
}

// ============================================================
// ZFInputCallbackForInputInRange
zfclass _ZFP_ZFInputCallbackForInputInRangeOwner : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_ZFInputCallbackForInputInRangeOwner, ZFObject)
public:
    ZFInputCallback src;
    zfindex srcStart;
    zfindex srcCount;
    zfbool autoRestorePos;
    zfindex savedPos;
    zfindex curPos; // ensured init with start

protected:
    zfoverride
    virtual void objectOnDeallocPrepare(void)
    {
        if(autoRestorePos)
        {
            src.ioSeek(savedPos);
        }
        zfsuper::objectOnDeallocPrepare();
    }

public:
    ZFMETHOD_DECLARE_2(zfindex, onInput,
                       ZFMP_IN(void *, buf),
                       ZFMP_IN(zfindex, count))
    {
        if(buf == zfnull)
        {
            return 0;
        }
        if(curPos - srcStart + count > srcCount)
        {
            count = srcCount - curPos + srcStart;
        }
        count = src.execute(buf, count);
        curPos += count;
        return count;
    }
    ZFMETHOD_DECLARE_2(zfindex, ioSeek,
                       ZFMP_IN(zfindex, byteSize),
                       ZFMP_IN(ZFSeekPos, pos))
    {
        curPos = ZFIOCallbackCalcFSeek(srcStart, srcCount, curPos, byteSize, pos);
        return curPos;
    }
    ZFMETHOD_DECLARE_0(zfindex, ioTell)
    {
        return curPos - srcStart;
    }
    ZFMETHOD_DECLARE_0(zfindex, ioSize)
    {
        return srcStart + srcCount - curPos;
    }
};
ZFInputCallback _ZFP_ZFInputCallbackForInputInRange(ZF_IN const ZFCallerInfo &callerInfo,
                                                    ZF_IN const ZFInputCallback &inputCallback,
                                                    ZF_IN_OPT zfindex start /* = 0 */,
                                                    ZF_IN_OPT zfindex count /* = zfindexMax() */,
                                                    ZF_IN_OPT zfbool autoRestorePos /* = zftrue */)
{
    zfbool valid = zffalse;
    zfindex savedPos = zfindexMax();
    zfindex countFixed = count;
    do
    {
        if(!inputCallback.callbackIsValid()) {break;}

        savedPos = inputCallback.ioTell();
        if(savedPos == zfindexMax()) {break;}

        if(inputCallback.ioSeek(start, ZFSeekPosBegin) != start) {break;}

        zfindex srcCount = inputCallback.ioSize();
        if(srcCount == zfindexMax()) {break;}
        if(start + countFixed > srcCount)
        {
            countFixed = srcCount - start;
        }

        valid = zftrue;
    } while(zffalse);
    if(!valid)
    {
        if(savedPos != zfindexMax())
        {
            inputCallback.ioSeek(savedPos, ZFSeekPosBegin);
        }
        return ZFCallbackNullDetail(callerInfo);
    }

    _ZFP_ZFInputCallbackForInputInRangeOwner *owner = zfAlloc(_ZFP_ZFInputCallbackForInputInRangeOwner);
    owner->src = inputCallback;
    owner->srcStart = start;
    owner->srcCount = countFixed;
    owner->autoRestorePos = autoRestorePos;
    owner->savedPos = savedPos;
    owner->curPos = start;
    ZFInputCallback ret = ZFCallbackForMemberMethodDetail(
        owner, ZFMethodAccess(_ZFP_ZFInputCallbackForInputInRangeOwner, onInput),
        callerInfo);
    ret.callbackTagSet(ZFCallbackTagKeyword_ioOwner, owner);
    zfRelease(owner);

    if(inputCallback.callbackId() != zfnull)
    {
        ret.callbackIdSet(zfstringWithFormat(zfText("ZFInputCallbackForInputInRange[%zi, %zi]:%@"), start, count, inputCallback.callbackId()));
    }

    if(inputCallback.callbackSerializeCustomType() != zfnull)
    {
        ZFSerializableData inputData;
        if(ZFCallbackToData(inputData, inputCallback))
        {
            ZFSerializableData customData;
            customData.itemClassSet(ZFSerializableKeyword_node);

            zfbool success = zffalse;
            do {
                inputData.categorySet(ZFSerializableKeyword_ZFInputCallbackForInputInRange_input);
                customData.elementAdd(inputData);

                if(start != 0)
                {
                    ZFSerializableData startData;
                    if(!zfindexToData(startData, start))
                    {
                        break;
                    }
                    startData.categorySet(ZFSerializableKeyword_ZFInputCallbackForInputInRange_start);
                    customData.elementAdd(startData);
                }

                if(count != zfindexMax())
                {
                    ZFSerializableData countData;
                    if(!zfindexToData(countData, count))
                    {
                        break;
                    }
                    countData.categorySet(ZFSerializableKeyword_ZFInputCallbackForInputInRange_count);
                    customData.elementAdd(countData);
                }

                if(!autoRestorePos)
                {
                    ZFSerializableData autoRestorePosData;
                    if(!zfboolToData(autoRestorePosData, autoRestorePos))
                    {
                        break;
                    }
                    autoRestorePosData.categorySet(ZFSerializableKeyword_ZFInputCallbackForInputInRange_autoRestorePos);
                    customData.elementAdd(autoRestorePosData);
                }

                success = zftrue;
            } while(zffalse);

            if(success)
            {
                ret.callbackSerializeCustomTypeSet(ZFCallbackSerializeCustomType_ZFInputCallbackForInputInRange);
                ret.callbackSerializeCustomDataSet(customData);
            }
        }
    }

    return ret;
}
ZFCALLBACK_SERIALIZE_CUSTOM_TYPE_DEFINE(ZFCallbackSerializeCustomTypeId_ZFInputCallbackForInputInRange)
{
    const ZFSerializableData *inputData = ZFSerializableUtil::requireElementByCategory(
        serializableData, ZFSerializableKeyword_ZFInputCallbackForInputInRange_input, outErrorHint, outErrorPos);
    if(inputData == zfnull)
    {
        return zffalse;
    }
    ZFCallback input;
    if(!ZFCallbackFromData(input, *inputData, outErrorHint, outErrorPos))
    {
        return zffalse;
    }

    zfindex start = 0;
    {
        const ZFSerializableData *startData = ZFSerializableUtil::checkElementByCategory(serializableData, ZFSerializableKeyword_ZFInputCallbackForInputInRange_start);
        if(startData != zfnull && !zfindexFromData(start, *startData, outErrorHint, outErrorPos))
        {
            return zffalse;
        }
    }
    zfindex count = zfindexMax();
    {
        const ZFSerializableData *countData = ZFSerializableUtil::checkElementByCategory(serializableData, ZFSerializableKeyword_ZFInputCallbackForInputInRange_count);
        if(countData != zfnull && !zfindexFromData(count, *countData, outErrorHint, outErrorPos))
        {
            return zffalse;
        }
    }
    zfbool autoRestorePos = zftrue;
    {
        const ZFSerializableData *autoRestorePosData = ZFSerializableUtil::checkElementByCategory(serializableData, ZFSerializableKeyword_ZFInputCallbackForInputInRange_autoRestorePos);
        if(autoRestorePosData != zfnull && !zfboolFromData(autoRestorePos, *autoRestorePosData, outErrorHint, outErrorPos))
        {
            return zffalse;
        }
    }
    serializableData.resolveMark();

    result = ZFInputCallbackForInputInRange(input, start, count, autoRestorePos);
    return zftrue;
}

// ============================================================
// ZFInputCallbackForBuffer
zfclass _ZFP_ZFInputCallbackForBufferOwner : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_ZFInputCallbackForBufferOwner, ZFObject)

public:
    zfbool isCopy;
    const zfbyte *pStart;
    const zfbyte *pEnd; // ensured valid
    const zfbyte *p;
public:
    ZFMETHOD_DECLARE_2(zfindex, onInput,
                       ZFMP_IN(void *, buf),
                       ZFMP_IN(zfindex, count))
    {
        if(buf == zfnull)
        {
            return 0;
        }
        if(p + count > pEnd)
        {
            count = pEnd - p;
        }
        zfmemcpy(buf, p, count);
        p += count;
        return count;
    }
    ZFMETHOD_DECLARE_2(zfindex, ioSeek,
                       ZFMP_IN(zfindex, byteSize),
                       ZFMP_IN(ZFSeekPos, pos))
    {
        const zfbyte *nullAddr = zfnull;
        p = nullAddr + ZFIOCallbackCalcFSeek(pStart - nullAddr, pEnd - nullAddr, p - nullAddr, byteSize, pos);
        return p - pStart;
    }
    ZFMETHOD_DECLARE_0(zfindex, ioTell)
    {
        return p - pStart;
    }
    ZFMETHOD_DECLARE_0(zfindex, ioSize)
    {
        return pEnd - p;
    }
};
ZFInputCallback _ZFP_ZFInputCallbackForBuffer(ZF_IN const ZFCallerInfo &callerInfo,
                                              ZF_IN zfbool copy,
                                              ZF_IN const void *src,
                                              ZF_IN_OPT zfindex count /* = zfindexMax() */)
{
    if(src == zfnull)
    {
        return ZFCallbackNullDetail(callerInfo);
    }
    zfindex len = count;
    void *srcTmp = zfnull;
    if(len == zfindexMax())
    {
        len = zfslen((const zfchar *)src);
    }
    if(copy)
    {
        srcTmp = zfmalloc(sizeof(zfchar) * len);
        zfmemcpy(srcTmp, src, sizeof(zfchar) * len);
        src = srcTmp;
    }
    if(src == zfnull)
    {
        return ZFCallbackNullDetail(callerInfo);
    }

    _ZFP_ZFInputCallbackForBufferOwner *owner = zfAlloc(_ZFP_ZFInputCallbackForBufferOwner);
    owner->isCopy = copy;
    owner->pStart = (const zfbyte *)src;
    owner->pEnd = owner->pStart + len;
    owner->p = owner->pStart;
    ZFInputCallback ret = ZFCallbackForMemberMethodDetail(
        owner, ZFMethodAccess(_ZFP_ZFInputCallbackForBufferOwner, onInput),
        callerInfo);
    ret.callbackTagSet(ZFCallbackTagKeyword_ioOwner, owner);
    if(copy)
    {
        ret.callbackTagSet(
            zfText("ZFInputCallbackForBufferCopiedBuffer"),
            zflineAlloc(ZFTypeHolder, srcTmp, ZFTypeHolderTypePOD));

    }
    zfRelease(owner);
    return ret;
}

// ============================================================
// ZFIOBridgeCallback

// ============================================================
// ZFIOBridgeCallbackUsingBuffer
zfclass _ZFP_ZFIOBridgeCallbackUsingBufferPrivate : zfextends ZFObject
{
    ZFOBJECT_DECLARE_WITH_CUSTOM_CTOR(_ZFP_ZFIOBridgeCallbackUsingBufferPrivate, ZFObject)

public:
    ZFCoreArrayPOD<zfbyte> ioBuf;
    zfindex inputIndex;

public:
    _ZFP_ZFIOBridgeCallbackUsingBufferPrivate(void)
    : ioBuf()
    , inputIndex(0)
    {
    }

public:
    ZFMETHOD_DECLARE_2(zfindex, onInput,
                       ZFMP_IN(void *, buf),
                       ZFMP_IN(zfindex, count))
    {
        if(buf == zfnull)
        {
            return this->ioBuf.count();
        }
        else
        {
            count = zfmMin(count, this->ioBuf.count() - this->inputIndex);
            zfmemcpy(buf, this->ioBuf.arrayBuf() + this->inputIndex, count);
            this->inputIndex = zfmMin(this->inputIndex + count, this->ioBuf.count());
            return count;
        }
    }
    ZFMETHOD_DECLARE_2(zfindex, onOutput,
                       ZFMP_IN(const void *, buf),
                       ZFMP_IN(zfindex, count))
    {
        if(count == 0)
        {
            return count;
        }
        if(count == zfindexMax())
        {
            count = zfslen((const zfchar *)buf) * sizeof(zfchar);
        }
        this->ioBuf.addFrom(ZFCastStatic(const zfbyte *, buf), count);
        return count;
    }
};

/** @cond ZFPrivateDoc */
ZFIOBridgeCallbackUsingBuffer::ZFIOBridgeCallbackUsingBuffer(void)
: ZFIOBridgeCallback()
{
    d = zfAllocWithoutLeakTest(_ZFP_ZFIOBridgeCallbackUsingBufferPrivate);
}
ZFIOBridgeCallbackUsingBuffer::ZFIOBridgeCallbackUsingBuffer(ZF_IN const ZFIOBridgeCallbackUsingBuffer &ref)
: ZFIOBridgeCallback(ref)
{
    d = zfnull;
    this->operator=(ref);
}
ZFIOBridgeCallbackUsingBuffer &ZFIOBridgeCallbackUsingBuffer::operator =(ZF_IN const ZFIOBridgeCallbackUsingBuffer &ref)
{
    zfRetainWithoutLeakTest(ref.d);
    zfReleaseWithoutLeakTest(d);
    d = ref.d;
    return *this;
}
/** @endcond */
ZFIOBridgeCallbackUsingBuffer::~ZFIOBridgeCallbackUsingBuffer(void)
{
    zfReleaseWithoutLeakTest(d);
    d = zfnull;
}

ZFInputCallback ZFIOBridgeCallbackUsingBuffer::inputCallback(void)
{
    return ZFCallbackForMemberMethod(d, ZFMethodAccess(_ZFP_ZFIOBridgeCallbackUsingBufferPrivate, onInput));
}
ZFOutputCallback ZFIOBridgeCallbackUsingBuffer::outputCallback(void)
{
    return ZFCallbackForMemberMethod(d, ZFMethodAccess(_ZFP_ZFIOBridgeCallbackUsingBufferPrivate, onOutput));
}

void ZFIOBridgeCallbackUsingBuffer::resetInput(void)
{
    d->inputIndex = 0;
}
void ZFIOBridgeCallbackUsingBuffer::resetOutput(void)
{
    d->inputIndex = 0;
    d->ioBuf.removeAll();
}

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
ZFMETHOD_USER_REGISTER_2({return ZFIOCallback(invokerObject->to<v_ZFCallback *>()->zfv).ioSeek(byteSize, pos);}, v_ZFCallback, zfindex, ioSeek, ZFMP_IN(zfindex, byteSize), ZFMP_IN_OPT(ZFSeekPos, pos, ZFSeekPosBegin))
ZFMETHOD_USER_REGISTER_0({return ZFIOCallback(invokerObject->to<v_ZFCallback *>()->zfv).ioTell();}, v_ZFCallback, zfindex, ioTell)
ZFMETHOD_USER_REGISTER_0({return ZFIOCallback(invokerObject->to<v_ZFCallback *>()->zfv).ioSize();}, v_ZFCallback, zfindex, ioSize)

// ============================================================
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(ZFOutputCallback, ZFOutputCallbackForString, ZFMP_IN_OUT(zfstring &, s))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(ZFBuffer, ZFInputCallbackReadToBuffer, ZFMP_IN_OUT(const ZFInputCallback &, input))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, ZFInputCallbackReadToOutput, ZFMP_IN_OUT(const ZFOutputCallback &, output), ZFMP_IN_OUT(const ZFInputCallback &, input))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_4(ZFInputCallback, ZFInputCallbackForInputInRange, ZFMP_IN(const ZFInputCallback &, inputCallback), ZFMP_IN_OPT(zfindex, start, 0), ZFMP_IN_OPT(zfindex, count, zfindexMax()), ZFMP_IN_OPT(zfbool, autoRestorePos, zftrue))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(ZFInputCallback, ZFInputCallbackForBuffer, ZFMP_IN(const zfchar *, buf), ZFMP_IN_OPT(zfindex, count, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(ZFInputCallback, ZFInputCallbackForBufferCopy, ZFMP_IN(const zfchar *, buf), ZFMP_IN_OPT(zfindex, count, zfindexMax()))

ZF_NAMESPACE_GLOBAL_END
#endif

