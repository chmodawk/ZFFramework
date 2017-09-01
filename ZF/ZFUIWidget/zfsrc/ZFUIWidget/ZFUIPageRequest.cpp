/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIPageRequest.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
ZFPROPERTY_TYPE_ACCESS_ONLY_DEFINE(ZFUIPageRequestPageCreateParam, ZFUIPageRequestPageCreateParam)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFUIPageRequestPageCreateParam, const ZFClass * const &, pageClass)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFUIPageRequestPageCreateParam, void, pageClassSet, ZFMP_IN(const ZFClass * const &, pageClass))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFUIPageRequestPageCreateParam, ZFObject * const &, pageCreateParam)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFUIPageRequestPageCreateParam, void, pageCreateParamSet, ZFMP_IN(ZFObject * const &, pageCreateParam))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFUIPageRequestPageCreateParam, zfbool const &, pageAutoResume)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFUIPageRequestPageCreateParam, void, pageAutoResumeSet, ZFMP_IN(zfbool const &, pageAutoResume))

// ============================================================
// request
ZFOBJECT_REGISTER(ZFUIPageRequest)
ZFOBJECT_REGISTER(ZFUIPageRequestPageCreate)
ZFOBJECT_REGISTER(ZFUIPageRequestPageResume)
ZFOBJECT_REGISTER(ZFUIPageRequestPageGroupResume)
ZFOBJECT_REGISTER(ZFUIPageRequestPageDestroy)
ZFOBJECT_REGISTER(ZFUIPageRequestCustom)

ZF_NAMESPACE_GLOBAL_END

