/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFSerializableDataRefType_common.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFSERIALIZABLEDATA_REFERENCE_TYPE_DEFINE(ZFSerializableDataRefTypeId_value)
{
    ZFCoreArrayPOD<zfindexRange> pos;
    zfCoreDataPairSplitString(
        pos,
        zfindexMax,
        refData, zfindexMax,
        zfText("|"),
        zfText("["), zfText("]")
        );
    if(pos.count() < 2
        || pos[0].count <= 0
        || pos[1].count <= 0)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint,
            zfText("failed to parse object creator data from \"%s\""), refData);
        return zffalse;
    }

    zfstring creatorType;
    zfCoreDataDecode(creatorType, zfstring(refData + pos[0].start, pos[0].count));
    zfstring creatorData;
    zfCoreDataDecode(creatorData, zfstring(refData + pos[1].start, pos[1].count));

    zfautoObject owner = ZFObjectCreate(creatorType, creatorData);
    if(owner == zfautoObjectNull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint,
            zfText("failed to serialize object from \"%s\" with data \"%s\""),
            creatorType.cString(), creatorData.cString()
            );
        return zffalse;
    }

    zfindex refDataLen = zfslen(refData);
    zfindex propertyDataIndex = pos[1].start + pos[1].count + 1;
    if(propertyDataIndex == refDataLen)
    {
        return ZFObjectToSerializableData(serializableData, owner, outErrorHint);
    }

    pos.removeAll();
    const zfchar *propertyData = refData + propertyDataIndex;
    if(!zfCoreDataPairSplitString(
            pos, zfindexMax,
            propertyData, zfindexMax,
            zfText(":"),
            zfnull, zfnull,
            zftrue
        )
        || pos.isEmpty()
        )
    {
        ZFSerializableUtil::errorOccurred(outErrorHint,
            zfText("failed to parse property value name from \"%s\""), propertyData);
        return zffalse;
    }

    ZFObject *obj = owner;
    for(zfindex i = 0; i < pos.count(); ++i)
    {
        if(pos[i].count == 0)
        {
            continue;
        }

        zfstring propertyName(propertyData + pos[i].start, pos[i].count);
        const ZFProperty *property = obj->classData()->propertyForName(propertyName);
        if(property == zfnull)
        {
            ZFSerializableUtil::errorOccurred(outErrorHint,
                zfText("no property named \"%s\" in class \"%s\""),
                propertyName.cString(),
                obj->classData()->className());
            return zffalse;
        }

        if(!property->propertyIsRetainProperty())
        {
            if(i + 1 < pos.count())
            {
                ZFSerializableUtil::errorOccurred(outErrorHint,
                    zfText("property \"%s\" is not a retain property, no further property access allowed"),
                    propertyName.cString());
                return zffalse;
            }
            if(!property->propertyIsSerializable())
            {
                ZFSerializableUtil::errorOccurred(outErrorHint,
                    zfText("property \"%s\" is not serializable"),
                    propertyName.cString());
                return zffalse;
            }

            return ZFPropertySerializeTo(property, obj, serializableData, outErrorHint);
        }
        else
        {
            obj = ZFPropertyRetainGet(property, obj);
            if(obj == zfnull)
            {
                return zftrue;
            }
            if(i + 1 == pos.count())
            {
                return ZFObjectToSerializableData(serializableData, obj);
            }
        }
    }
    return zftrue;
}

ZF_NAMESPACE_GLOBAL_END

