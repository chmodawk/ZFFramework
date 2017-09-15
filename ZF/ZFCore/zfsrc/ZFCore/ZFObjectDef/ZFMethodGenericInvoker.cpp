/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFMethodGenericInvoker.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfclass _ZFP_I_ZFMethodGenericInvokerDefaultParamType : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_I_ZFMethodGenericInvokerDefaultParamType, ZFObject)
};
ZFObject *_ZFP_ZFMethodGenericInvokerDefaultParamRef = zfnull;
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFMethodGenericInvokerDefaultParamInit, ZFLevelZFFrameworkEssential)
{
    _ZFP_ZFMethodGenericInvokerDefaultParamRef = zfAllocWithoutLeakTest(_ZFP_I_ZFMethodGenericInvokerDefaultParamType);
    _ZFP_ZFMethodGenericInvokerDefaultParamHolderRef = zfautoObjectCreateWithoutLeakTest(_ZFP_ZFMethodGenericInvokerDefaultParamRef);
}
ZF_GLOBAL_INITIALIZER_DESTROY(ZFMethodGenericInvokerDefaultParamInit)
{
    zfReleaseWithoutLeakTest(_ZFP_ZFMethodGenericInvokerDefaultParamRef);
    _ZFP_ZFMethodGenericInvokerDefaultParamRef = zfnull;

    _ZFP_ZFMethodGenericInvokerDefaultParamHolderRef = zfautoObjectNull();
}
ZF_GLOBAL_INITIALIZER_END(ZFMethodGenericInvokerDefaultParamInit)

zfautoObject _ZFP_ZFMethodGenericInvokerDefaultParamHolderRef;

void _ZFP_MtdGIParamError(ZF_OUT_OPT zfstring *errorHint,
                          ZF_IN zfindex paramIndex,
                          ZF_IN const zfchar *paramTypeId,
                          ZF_IN ZFObject *param)
{
    zfstringAppend(errorHint,
            zfText("[ZFMethodGenericInvoker] unable to access param%zi as type %s: %s"),
            paramIndex,
            paramTypeId,
            ZFObjectInfo(param).cString()
        );
}
void _ZFP_MtdGIRetError(ZF_OUT_OPT zfstring *errorHint,
                        ZF_IN const zfchar *returnTypeId,
                        ZF_IN const zfchar *returnValueInfo)
{
    zfstringAppend(errorHint,
        zfText("[ZFMethodGenericInvoker] unable to convert return value as type %s: %s"),
        returnTypeId,
        returnValueInfo);
}

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_FUNC_USER_REGISTER_0({return ZFMethodGenericInvokerDefaultParam();}, ZFObject *, ZFMethodGenericInvokerDefaultParam)

ZF_NAMESPACE_GLOBAL_END
#endif

