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

_ZFP_MtdFURHolder::_ZFP_MtdFURHolder(ZF_IN const zfchar *methodNamespace_,
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
: _methodNamespace(methodNamespace_)
, _methodName(methodName_)
, _methodExtSig(methodExtSig_)
, _methodInternalId()
, _method(zfnull)
{
    zfCoreAssertWithMessageTrim(!_methodName.isEmpty(), zfTextA("[ZFMethodFuncUserRegister] null methodName"));
    _ZFP_ZFMethodInstanceSig(_methodInternalId, _methodNamespace, _methodName, _methodExtSig
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
        zfTextA("[ZFMethodFuncUserRegister] registering a method that already registered, methodNamespace: %s, methodName: %s, methodExtSig: %s"),
        zfsCoreZ2A(_methodNamespace.cString()),
        zfsCoreZ2A(_methodName.cString()),
        zfsCoreZ2A(_methodExtSig.cString()));
    _method = _ZFP_ZFMethodInstanceAccess(_methodInternalId);
}

void ZFMethodFuncUserUnregister(ZF_IN const ZFMethod *method)
{
    if(method == zfnull)
    {
        return ;
    }
    zfCoreMutexLocker();
    zfCoreAssertWithMessageTrim(method->methodIsUserRegister(),
            zfTextA("[ZFMethodFuncUserUnregister] method %s is not user registered"),
            zfsCoreZ2A(method->objectInfo().cString())
        );
    zfCoreAssertWithMessageTrim(method->methodIsFunctionType(),
            zfTextA("[ZFMethodFuncUserUnregister] method %s is not function type"),
            zfsCoreZ2A(method->objectInfo().cString())
        );

    _ZFP_ZFMethodFuncUnregister(method);
    _ZFP_ZFClassDataChangeNotify(ZFClassDataChangeTypeDetach, zfnull, zfnull, method);
    _ZFP_ZFMethodInstanceCleanup(method);
}

ZF_NAMESPACE_GLOBAL_END

