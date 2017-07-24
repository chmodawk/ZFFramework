/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFMethodDeclare.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

/* ZFMETHOD_MAX_PARAM */
const ZFMethod *ZFMethodGet(ZF_IN const zfchar *className,
                            ZF_IN const zfchar *methodName)
{
    const ZFClass *cls = ZFClass::classForName(className);
    if(cls != zfnull)
    {
        return cls->methodForName(methodName);
    }
    return zfnull;
}
const ZFMethod *ZFMethodGet(ZF_IN const zfchar *className,
                            ZF_IN const zfchar *methodName
                            , ZF_IN_OPT const zfchar *methodParamTypeId0
                            , ZF_IN_OPT const zfchar *methodParamTypeId1 /* = zfnull */
                            , ZF_IN_OPT const zfchar *methodParamTypeId2 /* = zfnull */
                            , ZF_IN_OPT const zfchar *methodParamTypeId3 /* = zfnull */
                            , ZF_IN_OPT const zfchar *methodParamTypeId4 /* = zfnull */
                            , ZF_IN_OPT const zfchar *methodParamTypeId5 /* = zfnull */
                            , ZF_IN_OPT const zfchar *methodParamTypeId6 /* = zfnull */
                            , ZF_IN_OPT const zfchar *methodParamTypeId7 /* = zfnull */
                            )
{
    const ZFClass *cls = ZFClass::classForName(className);
    if(cls != zfnull)
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
    return zfnull;
}

const ZFMethod *ZFMethodGet(ZF_IN const ZFClass *cls,
                            ZF_IN const zfchar *methodName)
{
    if(cls != zfnull)
    {
        return cls->methodForName(methodName);
    }
    return zfnull;
}
const ZFMethod *ZFMethodGet(ZF_IN const ZFClass *cls,
                            ZF_IN const zfchar *methodName
                            , ZF_IN_OPT const zfchar *methodParamTypeId0
                            , ZF_IN_OPT const zfchar *methodParamTypeId1 /* = zfnull */
                            , ZF_IN_OPT const zfchar *methodParamTypeId2 /* = zfnull */
                            , ZF_IN_OPT const zfchar *methodParamTypeId3 /* = zfnull */
                            , ZF_IN_OPT const zfchar *methodParamTypeId4 /* = zfnull */
                            , ZF_IN_OPT const zfchar *methodParamTypeId5 /* = zfnull */
                            , ZF_IN_OPT const zfchar *methodParamTypeId6 /* = zfnull */
                            , ZF_IN_OPT const zfchar *methodParamTypeId7 /* = zfnull */
                            )
{
    if(cls != zfnull)
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
    return zfnull;
}

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(const ZFMethod *, ZFMethodGet, ZFMP_IN(const zfchar *, className), ZFMP_IN(const zfchar *, methodName))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_8(const ZFMethod *, ZFMethodGet, ZFMP_IN(const zfchar *, className), ZFMP_IN(const zfchar *, methodName)
    , ZFMP_IN(const zfchar *, param0)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId1, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId2, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId3, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId4, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId5, zfnull)
    /* ZFMETHOD_MAX_PARAM , ZFMP_IN_OPT(const zfchar *, methodParamTypeId6, zfnull) */
    /* ZFMETHOD_MAX_PARAM , ZFMP_IN_OPT(const zfchar *, methodParamTypeId7, zfnull) */
    )
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(const ZFMethod *, ZFMethodGet, ZFMP_IN(const ZFClass *, cls), ZFMP_IN(const zfchar *, methodName))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_8(const ZFMethod *, ZFMethodGet, ZFMP_IN(const ZFClass *, cls), ZFMP_IN(const zfchar *, methodName)
    , ZFMP_IN(const zfchar *, param0)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId1, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId2, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId3, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId4, zfnull)
    , ZFMP_IN_OPT(const zfchar *, methodParamTypeId5, zfnull)
    /* ZFMETHOD_MAX_PARAM , ZFMP_IN_OPT(const zfchar *, methodParamTypeId6, zfnull) */
    /* ZFMETHOD_MAX_PARAM , ZFMP_IN_OPT(const zfchar *, methodParamTypeId7, zfnull) */
    )

ZF_NAMESPACE_GLOBAL_END
#endif

