/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFMethod.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
void ZFMethod::_ZFP_ZFMethod_init(ZF_IN const zfchar *methodInternalId,
                                  ZF_IN zfbool methodIsUserRegister,
                                  ZF_IN ZFFuncAddrType invoker,
                                  ZF_IN ZFMethodGenericInvoker methodGenericInvoker,
                                  ZF_IN const zfchar *methodIsWhatType,
                                  ZF_IN const zfchar *methodName,
                                  ZF_IN const zfchar *returnTypeId,
                                  ZF_IN const zfchar *returnTypeName,
                                  ...)
{
    zfCoreAssert(invoker != zfnull && methodGenericInvoker != zfnull);

    this->_ZFP_ZFMethod_methodInternalId = methodInternalId;
    this->_ZFP_ZFMethod_methodIsUserRegister = methodIsUserRegister;
    this->_ZFP_ZFMethod_invoker = invoker;
    this->_ZFP_ZFMethod_invokerOrg = invoker;
    this->_ZFP_ZFMethod_methodGenericInvoker = methodGenericInvoker;
    this->_ZFP_ZFMethod_methodGenericInvokerOrg = methodGenericInvoker;
    this->_ZFP_ZFMethod_methodName = methodName;
    this->_ZFP_ZFMethod_returnTypeId = returnTypeId;
    this->_ZFP_ZFMethod_returnTypeName = returnTypeName;
    this->_ZFP_ZFMethod_paramCount = 0;

    this->_ZFP_ZFMethod_methodIsStatic = (zfstringFind(methodIsWhatType, ZFM_TOSTRING(ZFMethodIsStatic())) != zfindexMax);
    this->_ZFP_ZFMethod_methodIsVirtual = (zfstringFind(methodIsWhatType, ZFM_TOSTRING(ZFMethodIsVirtual())) != zfindexMax);

    va_list vaList;
    va_start(vaList, returnTypeName);
    do
    {
        const zfchar *paramTypeId = va_arg(vaList, const zfchar *);
        if(paramTypeId == zfnull || paramTypeId[0] == '\0')
        {
            break;
        }
        const zfchar *paramTypeName = va_arg(vaList, const zfchar *);
        const zfchar *paramDefault = va_arg(vaList, const zfchar *);
        _ZFP_ZFMethodParamDefaultValueAccessCallback paramDefaultValueAccessCallback = va_arg(vaList, _ZFP_ZFMethodParamDefaultValueAccessCallback);

        this->_ZFP_ZFMethod_paramTypeIdList[this->_ZFP_ZFMethod_paramCount] = paramTypeId;
        this->_ZFP_ZFMethod_paramTypeNameList[this->_ZFP_ZFMethod_paramCount] = paramTypeName;

        if(_ZFP_ZFMethodHasDefaultParam(paramDefault))
        {
            if(this->_ZFP_ZFMethod_paramDefaultBeginIndex == zfindexMax)
            {
                this->_ZFP_ZFMethod_paramDefaultBeginIndex = this->_ZFP_ZFMethod_paramCount;
            }
            this->_ZFP_ZFMethod_paramDefaultNameList[this->_ZFP_ZFMethod_paramCount] = _ZFP_ZFMethodDefaultParamText(paramDefault);
            this->_ZFP_ZFMethod_paramDefaultValueAccessCallbackList[this->_ZFP_ZFMethod_paramCount] = paramDefaultValueAccessCallback;
        }

        ++(this->_ZFP_ZFMethod_paramCount);
    } while(zftrue);
    va_end(vaList);
}
void ZFMethod::_ZFP_ZFMethod_initClassMemberType(ZF_IN const ZFClass *methodOwnerClass,
                                                 ZF_IN ZFMethodPrivilegeType privilegeType)
{
    this->_ZFP_ZFMethod_methodOwnerClass = methodOwnerClass;
    this->_ZFP_ZFMethod_privilegeType = privilegeType;

    methodOwnerClass->_ZFP_ZFClass_removeConst()->_ZFP_ZFClass_methodRegister(this);
    _ZFP_ZFClassDataChangeNotify(ZFClassDataChangeTypeAttach, zfnull, zfnull, this);
}
void ZFMethod::_ZFP_ZFMethod_initFuncType(ZF_IN const zfchar *methodNamespace)
{
    this->_ZFP_ZFMethod_methodNamespace = methodNamespace;

    this->_ZFP_ZFMethod_methodOwnerClass = zfnull;
    this->_ZFP_ZFMethod_privilegeType = ZFMethodPrivilegeTypePublic;

    _ZFP_ZFClassDataChangeNotify(ZFClassDataChangeTypeAttach, zfnull, zfnull, this);
}

/** @cond ZFPrivateDoc */
ZFMethod::ZFMethod(void)
: _ZFP_ZFMethodNeedInit(zftrue)
, _ZFP_ZFMethod_methodIsUserRegister(zffalse)
, _ZFP_ZFMethod_invoker(zfnull)
, _ZFP_ZFMethod_invokerOrg(zfnull)
, _ZFP_ZFMethod_methodGenericInvoker(zfnull)
, _ZFP_ZFMethod_methodGenericInvokerOrg(zfnull)
, _ZFP_ZFMethod_methodName()
, _ZFP_ZFMethod_returnTypeId()
, _ZFP_ZFMethod_returnTypeName()
, _ZFP_ZFMethod_paramCount(0)
, _ZFP_ZFMethod_paramTypeIdList()
, _ZFP_ZFMethod_paramTypeNameList()
, _ZFP_ZFMethod_paramDefaultNameList()
, _ZFP_ZFMethod_paramDefaultValueAccessCallbackList()
, _ZFP_ZFMethod_paramDefaultBeginIndex(zfindexMax)
, _ZFP_ZFMethod_methodOwnerClass(zfnull)
, _ZFP_ZFMethod_privilegeType(ZFMethodPrivilegeTypePublic)
, _ZFP_ZFMethod_methodIsStatic(zffalse)
, _ZFP_ZFMethod_methodIsVirtual(zffalse)
, _ZFP_ZFMethod_methodNamespace()
{
}
/** @endcond */
ZFMethod::~ZFMethod(void)
{
}

void ZFMethod::objectInfoT(ZF_IN_OUT zfstring &ret) const
{
    switch(this->methodPrivilegeType())
    {
        case ZFMethodPrivilegeTypePublic:
            break;
        case ZFMethodPrivilegeTypeProtected:
            ret += ZFTOKEN_ZFMethodPrivilegeTypeProtected;
            ret += zfText(": ");
            break;
        case ZFMethodPrivilegeTypePrivate:
            ret += ZFTOKEN_ZFMethodPrivilegeTypePrivate;
            ret += zfText(": ");
            break;
        default:
            zfCoreCriticalShouldNotGoHere();
            break;
    }

    if(this->methodIsStatic())
    {
        ret += zfText("static ");
    }
    else if(this->methodIsVirtual())
    {
        ret += zfText("virtual ");
    }

    ret += this->methodReturnTypeName();
    ret += zfText(" ");

    if(this->methodIsFunctionType())
    {
        if(!zfscmpTheSame(this->methodNamespace(), ZFMethodFuncNamespaceGlobal))
        {
            ret += this->methodNamespace();
        }
        ret += zfText("::");
    }
    else
    {
        ret += this->methodOwnerClass()->className();
        ret += zfText("::");
    }

    ret += this->methodName();

    if(this->methodParamCount() > 0)
    {
        ret += zfText("(");
        for(zfindex i = 0; i < this->methodParamCount(); ++i)
        {
            if(i != 0)
            {
                ret += zfText(", ");
            }
            ret += this->methodParamTypeNameAtIndex(i);

            if(this->methodParamDefaultNameAtIndex(i) != zfnull)
            {
                ret += zfText(" = ");
                ret += this->methodParamDefaultNameAtIndex(i);
            }
        }
        ret += zfText(")");
    }
    else
    {
        ret += zfText("(void)");
    }
}

void ZFMethod::methodGenericInvokerSet(ZF_IN ZFMethodGenericInvoker methodGenericInvoker) const
{
    ZFMethod *m = this->_ZFP_ZFMethod_removeConst();
    if(methodGenericInvoker != zfnull)
    {
        m->_ZFP_ZFMethod_methodGenericInvoker = methodGenericInvoker;
    }
    else
    {
        m->_ZFP_ZFMethod_methodGenericInvoker = m->_ZFP_ZFMethod_methodGenericInvokerOrg;
    }
    _ZFP_ZFClassDataChangeNotify(ZFClassDataChangeTypeUpdate, zfnull, zfnull, this);
}

void ZFMethod::methodInvokerSet(ZF_IN ZFFuncAddrType methodInvoker) const
{
    this->_ZFP_ZFMethod_removeConst()->_ZFP_ZFMethod_invoker =
        ((methodInvoker != zfnull) ? methodInvoker : this->_ZFP_ZFMethod_invokerOrg);
    _ZFP_ZFClassDataChangeNotify(ZFClassDataChangeTypeUpdate, zfnull, zfnull, this);
}

// ============================================================
zfclassLikePOD _ZFP_ZFMethodMapData
{
public:
    zfindex refCount;
    ZFMethod method;
public:
    _ZFP_ZFMethodMapData(void)
    : refCount(1)
    , method()
    {
    }
};
ZF_STATIC_INITIALIZER_INIT(ZFMethodDataHolder)
{
}
ZFCoreMap methodMap; // _ZFP_ZFMethodMapData *
ZF_STATIC_INITIALIZER_END(ZFMethodDataHolder)
#define _ZFP_ZFMethodMap (ZF_STATIC_INITIALIZER_INSTANCE(ZFMethodDataHolder)->methodMap)

void ZFMethodGetAll(ZF_OUT ZFCoreArray<const ZFMethod *> &ret,
                    ZF_IN_OPT const ZFFilterForZFMethod *methodFilter /* = zfnull */)
{
    zfCoreMutexLocker();
    const ZFCoreMap &m = _ZFP_ZFMethodMap;
    if(methodFilter != zfnull)
    {
        for(zfiterator it = m.iterator(); m.iteratorIsValid(it); )
        {
            _ZFP_ZFMethodMapData *v = m.iteratorNextValue<_ZFP_ZFMethodMapData *>(it);
            if(methodFilter->filterCheckActive(&(v->method)))
            {
                ret.add(&(v->method));
            }
        }
    }
    else
    {
        for(zfiterator it = m.iterator(); m.iteratorIsValid(it); )
        {
            _ZFP_ZFMethodMapData *v = m.iteratorNextValue<_ZFP_ZFMethodMapData *>(it);
            ret.add(&(v->method));
        }
    }
}

void _ZFP_ZFMethodInstanceSig(ZF_OUT zfstring &ret,
                              ZF_IN const zfchar *methodScope,
                              ZF_IN const zfchar *methodName,
                              ZF_IN const zfchar *methodExtSig
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
    if(methodScope == zfnull || *methodScope == '\0')
    {
        ret += ZFMethodFuncNamespaceGlobal;
    }
    else
    {
        ret += methodScope;
    }
    ret += ':';
    ret += methodName;
    ret += ':';
    ret += methodExtSig;

    ret += '-'; ret += methodParamTypeId0;
    ret += '-'; ret += methodParamTypeId1;
    ret += '-'; ret += methodParamTypeId2;
    ret += '-'; ret += methodParamTypeId3;
    ret += '-'; ret += methodParamTypeId4;
    ret += '-'; ret += methodParamTypeId5;
    ret += '-'; ret += methodParamTypeId6;
    ret += '-'; ret += methodParamTypeId7;
}

ZFMethod *_ZFP_ZFMethodInstanceFind(ZF_IN const zfchar *methodInternalId)
{
    zfCoreMutexLocker();
    _ZFP_ZFMethodMapData *v = _ZFP_ZFMethodMap.get<_ZFP_ZFMethodMapData *>(methodInternalId);
    if(v == zfnull)
    {
        return zfnull;
    }
    else
    {
        return &(v->method);
    }
}
ZFMethod *_ZFP_ZFMethodInstanceAccess(ZF_IN const zfchar *methodInternalId)
{
    zfCoreMutexLocker();
    _ZFP_ZFMethodMapData *v = _ZFP_ZFMethodMap.get<_ZFP_ZFMethodMapData *>(methodInternalId);
    if(v == zfnull)
    {
        v = zfnew(_ZFP_ZFMethodMapData);
        _ZFP_ZFMethodMap.set(methodInternalId, ZFCorePointerForObject<_ZFP_ZFMethodMapData *>(v));
    }
    else
    {
        ++(v->refCount);
    }
    return &(v->method);
}
zfbool _ZFP_ZFMethodInstanceCleanup(ZF_IN const zfchar *methodInternalId)
{
    zfCoreMutexLocker();
    _ZFP_ZFMethodMapData *v = _ZFP_ZFMethodMap.get<_ZFP_ZFMethodMapData *>(methodInternalId);
    if(v == zfnull)
    {
        return zffalse;
    }
    --(v->refCount);
    if(v->refCount == 0)
    {
        _ZFP_ZFMethodMap.remove(methodInternalId);
    }
    return zftrue;
}
zfbool _ZFP_ZFMethodInstanceCleanup(ZF_IN const ZFMethod *method)
{
    return _ZFP_ZFMethodInstanceCleanup(method->methodInternalId());
}

ZF_NAMESPACE_GLOBAL_END

#if 1 // ZFObject related method register
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFEXPORT_ENUM_DEFINE(ZFMethodPrivilegeType, ZFMethodPrivilegeTypePublic, ZFMethodPrivilegeTypeProtected, ZFMethodPrivilegeTypePrivate)

ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, const zfchar *, methodInternalId)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, zfbool, methodIsUserRegister)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, const zfchar *, methodName)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, const zfchar *, methodReturnTypeId)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, const zfchar *, methodReturnTypeName)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, zfindex, methodParamCount)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFMethod, const zfchar *, methodParamTypeIdAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFMethod, const zfchar *, methodParamTypeNameAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFMethod, const zfchar *, methodParamDefaultNameAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFMethod, zfautoObject, methodParamDefaultValueAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, zfindex, methodParamDefaultBeginIndex)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, ZFFuncAddrType, methodInvoker)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFMethod, void, methodInvokerSet, ZFMP_IN(ZFFuncAddrType, methodInvoker))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, ZFFuncAddrType, methodInvokerOrg)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, ZFMethodGenericInvoker, methodGenericInvoker)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_8(v_ZFMethod, zfautoObject, methodGenericInvoke, ZFMP_IN_OPT(ZFObject *, ownerObjOrNull, zfnull)
    , ZFMP_IN_OPT(ZFObject *, param0, ZFMethodGenericInvokerDefaultParam)
    , ZFMP_IN_OPT(ZFObject *, param1, ZFMethodGenericInvokerDefaultParam)
    , ZFMP_IN_OPT(ZFObject *, param2, ZFMethodGenericInvokerDefaultParam)
    , ZFMP_IN_OPT(ZFObject *, param3, ZFMethodGenericInvokerDefaultParam)
    , ZFMP_IN_OPT(ZFObject *, param4, ZFMethodGenericInvokerDefaultParam)
    , ZFMP_IN_OPT(ZFObject *, param5, ZFMethodGenericInvokerDefaultParam)
    , ZFMP_IN_OPT(ZFObject *, param6, ZFMethodGenericInvokerDefaultParam)
    /* ZFMETHOD_MAX_PARAM , ZFMP_IN_OPT(ZFObject *, param7, ZFMethodGenericInvokerDefaultParam) */
    /* ZFMETHOD_MAX_PARAM , ZFMP_OUT_OPT(zfstring *, errorHint, zfnull) */
    )
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, ZFMethodGenericInvoker, methodGenericInvokerOrg)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFMethod, void, methodGenericInvokerSet, ZFMP_IN(ZFMethodGenericInvoker, methodGenericInvoker))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, const ZFClass *, methodOwnerClass)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, ZFMethodPrivilegeType, methodPrivilegeType)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, zfbool, methodIsStatic)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, zfbool, methodIsVirtual)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, zfbool, methodIsFunctionType)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFMethod, const zfchar *, methodNamespace)

ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(void, ZFMethodGetAll, ZFMP_OUT(ZFCoreArray<const ZFMethod *> &, ret), ZFMP_IN_OPT(const ZFFilterForZFMethod *, methodFilter, zfnull))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(ZFCoreArrayPOD<const ZFMethod *>, ZFMethodGetAll, ZFMP_IN_OPT(const ZFFilterForZFMethod *, methodFilter, zfnull))

ZF_NAMESPACE_GLOBAL_END
#endif
