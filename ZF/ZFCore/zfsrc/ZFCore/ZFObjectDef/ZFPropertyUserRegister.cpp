/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFPropertyUserRegister.h"
#include "ZFClass.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfautoObject _ZFP_I_ZFPropertyUserRegisteraultImplValueHolder::create(ZF_IN const ZFCorePointerBase &p)
{
    zfblockedAllocWithoutLeakTest(_ZFP_I_ZFPropertyUserRegisteraultImplValueHolder, holder);
    holder->v = p.refNew();
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

    _ZFP_ZFClassDataChangeNotify(ZFClassDataChangeTypeDetach, zfnull, zfproperty, zfnull);

    ZFMethodUserUnregister(zfproperty->setterMethod());
    ZFMethodUserUnregister(zfproperty->getterMethod());

    zfproperty->propertyOwnerClass()->_ZFP_ZFClass_removeConst()->_ZFP_ZFClass_propertyUnregister(zfproperty);
    _ZFP_ZFPropertyInstanceCleanup(_ZFP_ZFPropertyInstanceSig(
            zfproperty->propertyOwnerClass()->className(),
            zfproperty->propertyName()
        ));
}

ZF_NAMESPACE_GLOBAL_END

