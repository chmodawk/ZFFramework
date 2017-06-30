/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFMethodSerializable.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFMethod, const ZFMethod *, {
        ZFCoreArrayPOD<zfindexRange> pos;
        if(!ZFMethodSigSplit(pos, src, srcLen))
        {
            return zffalse;
        }
        v = ZFMethodFromSig(src, pos);
        return (v != zfnull);
    }, {
        if(v->methodIsFunctionType())
        {
            if(!zfscmpTheSame(v->methodNamespace(), ZFMethodFuncNamespaceGlobal))
            {
                s += v->methodNamespace();
            }
        }
        else
        {
            s += v->methodOwnerClass()->className();
        }

        s += zfText("::");
        s += v->methodName();

        for(zfindex i = 0; i < v->methodParamCount(); ++i)
        {
            s += zfText(":");
            s += v->methodParamTypeIdAtIndex(i);
        }

        return zftrue;
    })

/* ZFMETHOD_MAX_PARAM */
const ZFMethod *ZFMethodFromSig(ZF_IN const zfchar *classOrNamespace,
                                ZF_IN const zfchar *methodName
                                , ZF_IN_OPT const zfchar *methodParamTypeId0 /* = zfnull */
                                , ZF_IN_OPT const zfchar *methodParamTypeId1 /* = zfnull */
                                , ZF_IN_OPT const zfchar *methodParamTypeId2 /* = zfnull */
                                , ZF_IN_OPT const zfchar *methodParamTypeId3 /* = zfnull */
                                , ZF_IN_OPT const zfchar *methodParamTypeId4 /* = zfnull */
                                , ZF_IN_OPT const zfchar *methodParamTypeId5 /* = zfnull */
                                , ZF_IN_OPT const zfchar *methodParamTypeId6 /* = zfnull */
                                , ZF_IN_OPT const zfchar *methodParamTypeId7 /* = zfnull */
                                )
{
    const ZFClass *cls = zfnull;
    if(classOrNamespace != zfnull && *classOrNamespace != '\0')
    {
        cls = ZFClass::classForName(classOrNamespace);
    }

    if(cls == zfnull)
    {
        return ZFMethodFuncGet(classOrNamespace, methodName
                , methodParamTypeId0
                , methodParamTypeId1
                , methodParamTypeId2
                , methodParamTypeId3
                , methodParamTypeId4
                , methodParamTypeId5
                , methodParamTypeId6
                , methodParamTypeId7
            );
    }
    else
    {
        return cls->methodForName(methodName
                , methodParamTypeId0
                , methodParamTypeId1
                , methodParamTypeId2
                , methodParamTypeId3
                , methodParamTypeId4
                , methodParamTypeId5
                , methodParamTypeId6
                , methodParamTypeId7
            );
    }
}
const ZFMethod *ZFMethodFromSig(ZF_IN const zfchar *methodSig,
                                ZF_IN const ZFCoreArray<zfindexRange> &methodSigPos)
{
    if(methodSig == zfnull || methodSigPos.count() != ZFMETHOD_MAX_PARAM + 2)
    {
        return zfnull;
    }

    zfstring classOrNamespace(methodSig, methodSigPos[0].start, methodSigPos[0].count);
    zfstring methodName(methodSig, methodSigPos[1].start, methodSigPos[1].count);

    const ZFClass *cls = zfnull;
    if(methodSigPos[0].count > 0)
    {
        cls = ZFClass::classForName(classOrNamespace);
    }

    if(methodSigPos[2].count == 0)
    {
        if(cls == zfnull)
        {
            return ZFMethodFuncGet(classOrNamespace, methodName);
        }
        else
        {
            return cls->methodForName(methodName);
        }
    }
    else
    {
        if(cls == zfnull)
        {
            return ZFMethodFuncGet(classOrNamespace, methodName
                    , zfstring(methodSig, methodSigPos[2].start, methodSigPos[2].count)
                    , zfstring(methodSig, methodSigPos[3].start, methodSigPos[3].count)
                    , zfstring(methodSig, methodSigPos[4].start, methodSigPos[4].count)
                    , zfstring(methodSig, methodSigPos[5].start, methodSigPos[5].count)
                    , zfstring(methodSig, methodSigPos[6].start, methodSigPos[6].count)
                    , zfstring(methodSig, methodSigPos[7].start, methodSigPos[7].count)
                    , zfstring(methodSig, methodSigPos[8].start, methodSigPos[8].count)
                    , zfstring(methodSig, methodSigPos[9].start, methodSigPos[9].count)
                );
        }
        else
        {
            return cls->methodForName(methodName
                    , zfstring(methodSig, methodSigPos[2].start, methodSigPos[2].count)
                    , zfstring(methodSig, methodSigPos[3].start, methodSigPos[3].count)
                    , zfstring(methodSig, methodSigPos[4].start, methodSigPos[4].count)
                    , zfstring(methodSig, methodSigPos[5].start, methodSigPos[5].count)
                    , zfstring(methodSig, methodSigPos[6].start, methodSigPos[6].count)
                    , zfstring(methodSig, methodSigPos[7].start, methodSigPos[7].count)
                    , zfstring(methodSig, methodSigPos[8].start, methodSigPos[8].count)
                    , zfstring(methodSig, methodSigPos[9].start, methodSigPos[9].count)
                );
        }
    }
}

zfbool ZFMethodSigSplit(ZF_OUT ZFCoreArray<zfindexRange> &ret,
                        ZF_IN const zfchar *src,
                        ZF_IN_OPT zfindex srcLen /* = zfindexMax */)
{
    ZFCoreArrayPOD<zfindexRange> pos;
    if(!zfCoreDataPairSplitString(
        pos,
        zfHint("desiredCountOrIndexMax")zfindexMax,
        src, srcLen,
        zfHint("separatorTokens")zfText(":"),
        zfHint("leftToken")zfnull, zfHint("rightToken")zfnull,
        zfHint("allowEmptyItem")zftrue)
        || pos.count() < 3
        || pos[1].count != 0
        || pos[2].count == 0)
    {
        return zffalse;
    }

    // [Scope]::methodName[:methodParamTypeId0]
    ret.add(pos[0]);
    ret.add(pos[2]);
    for(zfindex i = 3; i < pos.count(); ++i)
    {
        ret.add(pos[i]);
    }
    while(ret.count() < (ZFMETHOD_MAX_PARAM + 2))
    {
        ret.add(zfindexRangeZero());
    }

    return zftrue;
}

ZF_NAMESPACE_GLOBAL_END

#if 1 // ZFObject related method register
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_8(const ZFMethod *, ZFMethodFromSig, ZFMP_IN(const zfchar *, classOrNamespace), ZFMP_IN(const zfchar *, methodName)
    , ZFMP_IN(const zfchar *, param0)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId1, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId2, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId3, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId4, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId5, zfnull)
    /* ZFMETHOD_MAX_PARAM , ZFMP_IN_OPT(const zfchar *, methodParamTypeId6, zfnull) */
    /* ZFMETHOD_MAX_PARAM , ZFMP_IN_OPT(const zfchar *, methodParamTypeId7, zfnull) */
    )
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(const ZFMethod *, ZFMethodFromSig, ZFMP_IN(const zfchar *, methodSig), ZFMP_IN(const ZFCoreArray<zfindexRange> &, methodSigPos))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_3(zfbool, ZFMethodSigSplit, ZFMP_OUT(ZFCoreArray<zfindexRange> &, ret), ZFMP_IN(const zfchar *, src), ZFMP_IN_OPT(zfindex, srcLen, zfindexMax))

ZF_NAMESPACE_GLOBAL_END
#endif

