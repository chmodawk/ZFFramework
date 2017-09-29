/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFSkinLoad.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_FUNC_DEFINE_2(zfbool, zfSkinLoad,
                       ZFMP_IN(const ZFSerializableData &, serializableData),
                       ZFMP_OUT_OPT(zfstring *, errorHint, zfnull))
{
    for(zfindex i = 0; i < serializableData.elementCount(); ++i)
    {
        const ZFSerializableData &item = serializableData.elementAtIndex(i);
        if(zfscmpTheSame(item.itemClass(), zfText("s")) && item.elementCount() > 0)
        {
            const zfchar *k = item.attributeForName(zfText("k"));
            if(k != zfnull)
            {
                zfautoObject obj = ZFObjectFromData(item.elementAtIndex(0));
                ZFStyleable *skinValue = ZFCastZFObject(ZFStyleable *, obj);
                if(skinValue != zfnull)
                {
                    zfSkinSet(k, skinValue);
                }
            }
        }
    }

    zfSkinNotifyChanged();
    return zftrue;
}

ZF_NAMESPACE_GLOBAL_END

