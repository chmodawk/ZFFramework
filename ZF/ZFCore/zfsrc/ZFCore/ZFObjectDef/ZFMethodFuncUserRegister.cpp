/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFMethodFuncUserRegister.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

void ZFMethodFuncUserUnregister(ZF_IN const ZFMethod *method)
{
    if(method == zfnull)
    {
        return ;
    }
    zfCoreAssertWithMessageTrim(method->methodIsUserRegister(),
            zfTextA("[ZFMethodFuncUserUnregister] method %s is not user registered"),
            zfsCoreZ2A(method->objectInfo().cString())
        );
    zfCoreAssertWithMessageTrim(method->methodIsFunctionType(),
            zfTextA("[ZFMethodFuncUserUnregister] method %s is not function type"),
            zfsCoreZ2A(method->objectInfo().cString())
        );

    _ZFP_ZFMethodUnregister(method);
}

ZF_NAMESPACE_GLOBAL_END

