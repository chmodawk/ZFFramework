/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFSerializableDataRefType_common.h
 * @brief common type for #ZFSERIALIZABLEDATA_REFERENCE_TYPE_DEFINE
 */

#ifndef _ZFI_ZFSerializableDataRefType_common_h_
#define _ZFI_ZFSerializableDataRefType_common_h_

#include "ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief see #ZFSERIALIZABLEDATA_REFERENCE_TYPE_DEFINE
 *
 * format:
 * @code
 *   <Node refType="value" refData="data, see below" />
 * @endcode
 *
 * refData's rule:
 * -  "[MyObjectCreatorType|MyObjectCreatorData]"\n
 *   use #ZFObjectCreate to create a ZFObject,
 *   then serialize the object to data and copy it to the result node
 * -  "[MyObjectCreatorType|MyObjectCreatorData]::myPropertyName1::myPropertyName2"
 *   use #ZFObjectCreate to create a ZFObject,
 *   then access the object's property value,
 *   serialize the value to data and copy it to the result node
 *
 * \n
 * typical useage:
 * @code
 *   <Node refType="value" refData="[method|MyStyle::DefaultStyleReflect]::myProperty"
 * @endcode
 * this would access MyStyle's default style (by #ZFObjectCreatorTypeId_method),
 * then copy the "myProperty" value to the result node
 */
#define ZFSerializableDataRefTypeId_value value
/** @brief see #ZFSerializableDataRefTypeId_value */
#define ZFSerializableDataRefType_value ZFM_TOSTRING(ZFSerializableDataRefTypeId_value)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFSerializableDataRefType_common_h_

