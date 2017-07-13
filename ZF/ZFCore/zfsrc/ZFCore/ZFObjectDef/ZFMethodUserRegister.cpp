/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFMethodUserRegister.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

_ZFP_MtdURHolder::_ZFP_MtdURHolder(ZF_IN const ZFClass *ownerClass_,
                                   ZF_IN const zfchar *methodName_,
                                   ZF_IN const zfchar *methodExtSig_
                                   , ZF_IN_OPT const zfchar *methodParamTypeId0 /* = zfnull */
                                   , ZF_IN_OPT const zfchar *methodParamTypeId1 /* = zfnull */
                                   , ZF_IN_OPT const zfchar *methodParamTypeId2 /* = zfnull */
                                   , ZF_IN_OPT const zfchar *methodParamTypeId3 /* = zfnull */
                                   , ZF_IN_OPT const zfchar *methodParamTypeId4 /* = zfnull */
                                   , ZF_IN_OPT const zfchar *methodParamTypeId5 /* = zfnull */
                                   , ZF_IN_OPT const zfchar *methodParamTypeId6 /* = zfnull */
                                   , ZF_IN_OPT const zfchar *methodParamTypeId7 /* = zfnull */
                                   )
: _methodOwnerClass(ownerClass_)
, _methodName(methodName_)
, _methodExtSig(methodExtSig_)
, _methodInternalId()
, _method(zfnull)
{
    zfCoreAssertWithMessageTrim(_methodOwnerClass != zfnull, zfTextA("[ZFMethodUserRegister] null class"));
    zfCoreAssertWithMessageTrim(!_methodName.isEmpty(), zfTextA("[ZFMethodUserRegister] null methodName"));
    _ZFP_ZFMethodInstanceSig(_methodInternalId, _methodOwnerClass->className(), _methodName, _methodExtSig
        , methodParamTypeId0
        , methodParamTypeId1
        , methodParamTypeId2
        , methodParamTypeId3
        , methodParamTypeId4
        , methodParamTypeId5
        , methodParamTypeId6
        , methodParamTypeId7
        );

    _method = _ZFP_ZFMethodInstanceFind(_methodInternalId);
    zfCoreAssertWithMessageTrim(_method == zfnull,
        zfTextA("[ZFMethodUserRegister] registering a method that already registered, class: %s, methodName: %s, methodExtSig: %s"),
        zfsCoreZ2A(_methodOwnerClass->className()),
        zfsCoreZ2A(_methodName.cString()),
        zfsCoreZ2A(_methodExtSig.cString()));
    _method = _ZFP_ZFMethodInstanceAccess(_methodInternalId);
}

void ZFMethodUserUnregister(ZF_IN const ZFMethod *method)
{
    zfCoreMutexLocker();
    zfCoreAssertWithMessageTrim(method->methodIsUserRegister(),
            zfTextA("[ZFMethodUserUnregister] method %s is not user registered"),
            zfsCoreZ2A(method->objectInfo().cString())
        );
    zfCoreAssertWithMessageTrim(!method->methodIsFunctionType(),
            zfTextA("[ZFMethodUserUnregister] method %s is not class member type"),
            zfsCoreZ2A(method->objectInfo().cString())
        );

    _ZFP_ZFClassDataChangeNotify(ZFClassDataChangeTypeDetach, zfnull, zfnull, method);
    method->methodOwnerClass()->_ZFP_ZFClass_removeConst()->_ZFP_ZFClass_methodUnregister(method);
    _ZFP_ZFMethodInstanceCleanup(method);
}

ZF_NAMESPACE_GLOBAL_END

