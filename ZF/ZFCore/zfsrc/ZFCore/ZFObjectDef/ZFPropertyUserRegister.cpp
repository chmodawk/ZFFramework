/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFPropertyUserRegister.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfautoObject _ZFP_I_PropURDIVH::create(ZF_IN void *v, ZF_IN DeleteCallback deleteCallback)
{
    zfblockedAllocWithoutLeakTest(_ZFP_I_PropURDIVH, holder);
    holder->v = v;
    holder->deleteCallback = deleteCallback;
    return zfautoObjectCreateWithoutLeakTest(holder);
}

void ZFPropertyUserUnregister(ZF_IN const ZFProperty *zfproperty)
{
    if(zfproperty == zfnull)
    {
        return ;
    }
    zfCoreMutexLocker();
    zfCoreAssertWithMessageTrim(zfproperty->propertyIsUserRegister(),
            zfTextA("[ZFPropertyUserUnregister] property %s is not user registered"),
            zfsCoreZ2A(zfproperty->objectInfo().cString())
        );

    _ZFP_ZFPropertyUnregister(zfproperty);
}

ZF_NAMESPACE_GLOBAL_END

