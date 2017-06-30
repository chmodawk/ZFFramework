/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file zfnullObject.h
 * @brief zfnullObject
 */

#ifndef _ZFI_zfnullObject_h_
#define _ZFI_zfnullObject_h_

#include "ZFObjectCore.h"

ZF_NAMESPACE_GLOBAL_BEGIN

extern ZF_ENV_EXPORT ZFObject *_ZFP_zfnullObject(void);
/**
 * @brief a global null object
 *
 * useful when adding null to a container,
 * since containers doesn't allow null
 */
#define zfnullObject() _ZFP_zfnullObject()

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_zfnullObject_h_

