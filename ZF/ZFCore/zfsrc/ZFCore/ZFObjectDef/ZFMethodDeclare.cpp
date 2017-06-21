/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFMethodDeclare.h"
#include "ZFClass.h"

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

