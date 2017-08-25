/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFKeyValuePair.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFEXPORT_VAR_READONLY_DEFINE(ZFKeyValuePair, ZFKeyValuePairZero, ZFKeyValuePairMake(zfnull, zfnull))

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_SERIALIZABLE_CONVERTER(ZFKeyValuePairHolder, ZFKeyValuePairHolder, {
        const ZFSerializableData *data = zfnull;
        data = ZFSerializableUtil::checkElementByCategory(serializableData, ZFSerializableKeyword_ZFKeyValuePair_key);
        if(data != zfnull)
        {
            if(!ZFObjectFromSerializableData(v.key, *data, outErrorHint, outErrorPos))
            {
                return zffalse;
            }
        }
        else
        {
            v.key = zfnull;
        }
        data = ZFSerializableUtil::checkElementByCategory(serializableData, ZFSerializableKeyword_ZFKeyValuePair_value);
        if(data != zfnull)
        {
            if(!ZFObjectFromSerializableData(v.value, *data, outErrorHint, outErrorPos))
            {
                return zffalse;
            }
        }
        else
        {
            v.value = zfnull;
        }
        return zftrue;
    }, {
        if(v.key != zfnull)
        {
            ZFSerializableData data;
            if(!ZFObjectToSerializableData(data, v.key, outErrorHint))
            {
                return zffalse;
            }
            data.categorySet(ZFSerializableKeyword_ZFKeyValuePair_key);
            serializableData.elementAdd(data);
        }
        if(v.value != zfnull)
        {
            ZFSerializableData data;
            if(!ZFObjectToSerializableData(data, v.value, outErrorHint))
            {
                return zffalse;
            }
            data.categorySet(ZFSerializableKeyword_ZFKeyValuePair_value);
            serializableData.elementAdd(data);
        }
        return zftrue;
    })

ZFPROPERTY_TYPE_ALIAS_DEFINE(ZFKeyValuePairHolder, ZFKeyValuePairHolder, ZFKeyValuePair, ZFKeyValuePair)

ZF_NAMESPACE_GLOBAL_END

