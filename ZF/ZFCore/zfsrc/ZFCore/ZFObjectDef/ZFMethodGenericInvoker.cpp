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

zfclass _ZFP_I_ZFMethodGenericInvokeraultParamType : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_I_ZFMethodGenericInvokeraultParamType, ZFObject)
};
ZFObject *_ZFP_ZFMethodGenericInvokeraultParamRef = zfnull;
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFMethodGenericInvokeraultParamInit, ZFLevelZFFrameworkEssential)
{
    _ZFP_ZFMethodGenericInvokeraultParamRef = zfAllocWithoutLeakTest(_ZFP_I_ZFMethodGenericInvokeraultParamType);
    _ZFP_ZFMethodGenericInvokeraultParamHolderRef = zfautoObjectCreateWithoutLeakTest(_ZFP_ZFMethodGenericInvokeraultParamRef);
}
ZF_GLOBAL_INITIALIZER_DESTROY(ZFMethodGenericInvokeraultParamInit)
{
    zfReleaseWithoutLeakTest(_ZFP_ZFMethodGenericInvokeraultParamRef);
    _ZFP_ZFMethodGenericInvokeraultParamRef = zfnull;

    _ZFP_ZFMethodGenericInvokeraultParamHolderRef = zfautoObjectNull;
}
ZF_GLOBAL_INITIALIZER_END(ZFMethodGenericInvokeraultParamInit)

zfautoObject _ZFP_ZFMethodGenericInvokeraultParamHolderRef;

ZF_NAMESPACE_GLOBAL_END

