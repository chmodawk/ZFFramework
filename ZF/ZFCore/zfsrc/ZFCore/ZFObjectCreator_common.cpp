/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFObjectCreator_common.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFOBJECT_CREATOR_DEFINE(ZFObjectCreatorType_method, data)
{
    if(data == zfnull)
    {
        return zfautoObjectNull;
    }

    ZFCoreArrayPOD<zfindexRange> pos;
    if(!zfCoreDataPairSplitString(
            pos, zfHint("desiredCountOrIndexMax")3,
            data, zfHint("srcLen")zfindexMax,
            zfHint("separatorTokens")zfText(":"),
            zfHint("leftToken")zfnull, zfHint("rightToken")zfnull,
            zfHint("allowEmptyItem")zftrue)
       || pos[0].count == 0 || pos[1].count != 0 || pos[2].count == 0)
    {
        return zfautoObjectNull;
    }

    const ZFClass *cls = ZFClass::classForName(zfstring(data + pos[0].start, pos[0].count));
    if(cls == zfnull) {return zfautoObjectNull;}

    const ZFMethod *method = cls->methodForName(zfstring(data + pos[2].start, pos[2].count));
    if(method == zfnull || !method->methodIsStatic()) {return zfautoObjectNull;}

    return method->executeStatic<zfautoObject>();
}

ZF_NAMESPACE_GLOBAL_END

