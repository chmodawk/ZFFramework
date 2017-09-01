/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFClassSerializable.h
 * @brief serialization for ZFClass
 */

#ifndef _ZFI_ZFClassSerializable_h_
#define _ZFI_ZFClassSerializable_h_

#include "ZFClass.h"
#include "ZFSerializable.h"
#include "ZFPropertyType.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 */
ZFPROPERTY_TYPE_ACCESS_ONLY_DECLARE(ZFClassInstanceObserverAddParam, ZFClassInstanceObserverAddParam)

/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFClass value="ClassName" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFClass, const ZFClass *)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFClassSerializable_h_

