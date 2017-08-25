/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFFileBOM.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFFileBOM, ZFFileBOM, {
        if(srcLen == zfindexMax)
        {
            srcLen = zfslen(src);
        }
        if((srcLen % 2) != 0 || srcLen >= ZFFileBOMMaxSize)
        {
            return zffalse;
        }

        zfmemset(v.BOM, 0, sizeof(v.BOM));

        for(zfindex i = 0; ; ++i, src += 2)
        {
            if(!zfsToIntT(v.BOM[i], src, 2, 16))
            {
                return zffalse;
            }
        }

        return zftrue;
    }, {
        for(zfindex i = 0; v.BOM[i] != 0x00; ++i)
        {
            zfstringAppend(s, zfText("%02X"), v.BOM[i]);
        }
        return zftrue;
    })

ZFCORETYPE_STRING_CONVERTER_DEFINE(ZFFileBOMList, ZFFileBOMList, {
        ZFCoreArrayPOD<zfindexRange> pos;
        if(!zfCoreDataPairSplitString(pos, zfindexMax, src, srcLen))
        {
            return zffalse;
        }

        for(zfindex i = 0; i < pos.count(); ++i)
        {
            ZFFileBOM bom;
            if(!ZFFileBOMFromString(bom, src + pos[i].start, pos[i].count))
            {
                return zffalse;
            }
            v.add(bom);
        }
        return zftrue;
    }, {
        s += zfText("(");
        for(zfindex i = 0; i < v.count(); ++i)
        {
            if(i != 0)
            {
                s += zfText(", ");
            }
            ZFFileBOMToString(s, v[i]);
        }
        s += zfText(")");
        return zftrue;
    })

// ============================================================
static const ZFFileBOM &_ZFP_ZFFileBOMUTF8Init(void)
{
    static ZFFileBOM BOM = {{0xEF, 0xBB, 0xBF}};
    return BOM;
}
ZFEXPORT_VAR_READONLY_DEFINE(ZFFileBOM, ZFFileBOMUTF8, _ZFP_ZFFileBOMUTF8Init())

// ============================================================
static const ZFFileBOMList &_ZFP_ZFFileBOMListDefaultInit(void)
{
    static ZFFileBOMList ret;
    ret.add(ZFFileBOMUTF8());
    return ret;
}
ZFEXPORT_VAR_READONLY_DEFINE(ZFFileBOMList, ZFFileBOMListDefault, _ZFP_ZFFileBOMListDefaultInit())

ZF_NAMESPACE_GLOBAL_END

