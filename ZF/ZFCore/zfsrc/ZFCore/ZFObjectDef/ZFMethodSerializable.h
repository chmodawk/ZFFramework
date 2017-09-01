/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFMethodSerializable.h
 * @brief serialization for ZFMethod
 */

#ifndef _ZFI_ZFMethodSerializable_h_
#define _ZFI_ZFMethodSerializable_h_

#include "ZFMethod.h"
#include "ZFSerializable.h"
#include "ZFPropertyType.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFMethod value="methodSig" />
 * @endcode
 *
 * valid method signature:
 * -  "OwnerClass::methodName" :
 *   for class member type method
 * -  "OwnerClass::methodName:methodParamTypeId0" :
 *   for class member type method
 * -  "::methodName" :
 *   for function type method with default name space
 * -  "::methodName:methodParamTypeId0" :
 *   for function type method with default name space
 * -  "MethodNamespace::methodName" :
 *   for function type method with custom name space
 * -  "MethodNamespace::methodName:methodParamTypeId0" :
 *   for function type method with custom name space
 */
ZFPROPERTY_TYPE_DECLARE(ZFMethod, const ZFMethod *)

/* ZFMETHOD_MAX_PARAM */
/**
 * @brief parse method from method sig
 */
extern ZF_ENV_EXPORT const ZFMethod *ZFMethodFromSig(ZF_IN const zfchar *classOrNamespace,
                                                     ZF_IN const zfchar *methodName
                                                     , ZF_IN_OPT const zfchar *methodParamTypeId0 = zfnull
                                                     , ZF_IN_OPT const zfchar *methodParamTypeId1 = zfnull
                                                     , ZF_IN_OPT const zfchar *methodParamTypeId2 = zfnull
                                                     , ZF_IN_OPT const zfchar *methodParamTypeId3 = zfnull
                                                     , ZF_IN_OPT const zfchar *methodParamTypeId4 = zfnull
                                                     , ZF_IN_OPT const zfchar *methodParamTypeId5 = zfnull
                                                     , ZF_IN_OPT const zfchar *methodParamTypeId6 = zfnull
                                                     , ZF_IN_OPT const zfchar *methodParamTypeId7 = zfnull
                                                     );
/**
 * @brief parse method from method sig
 *
 * methodSigPos must be successfully decoded by #ZFMethodSigSplit
 */
extern ZF_ENV_EXPORT const ZFMethod *ZFMethodFromSig(ZF_IN const zfchar *methodSig,
                                                     ZF_IN const ZFCoreArray<zfindexRange> &methodSigPos);

/**
 * @brief split method sig
 *
 * result ensured to contain (ZFMETHOD_MAX_PARAM + 2) element if success:
 * -  pos[0] : range of OwnerClass or MethodNamespace, 0 length for global namespace
 * -  pos[1] : range of methodName, ensured not empty
 * -  pos[2] : range of methodParamTypeId0, 0 length if none
 * -  pos[3] : range of methodParamTypeId1, 0 length if none
 * -  pos[4] : range of methodParamTypeId2, 0 length if none
 * -  pos[5] : range of methodParamTypeId3, 0 length if none
 * -  pos[6] : range of methodParamTypeId4, 0 length if none
 * -  pos[7] : range of methodParamTypeId5, 0 length if none
 * -  pos[8] : range of methodParamTypeId6, 0 length if none
 * -  pos[9] : range of methodParamTypeId7, 0 length if none
 */
extern ZF_ENV_EXPORT zfbool ZFMethodSigSplit(ZF_OUT ZFCoreArray<zfindexRange> &ret,
                                             ZF_IN const zfchar *src,
                                             ZF_IN_OPT zfindex srcLen = zfindexMax());

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFMethodSerializable_h_

