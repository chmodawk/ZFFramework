/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#ifndef _ZFI_ZFImpl_sys_Qt_ZF_h_
#define _ZFI_ZFImpl_sys_Qt_ZF_h_

#include "ZFImpl.h"


#if ZF_ENV_sys_Qt
#include <QObject>
#include <QDebug>
#include <QVariant>
#include "ZFCore/ZFObject.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
extern ZF_ENV_EXPORT void ZFImpl_sys_Qt_QObjectTagSet(ZF_IN_OUT QObject *obj, ZF_IN const zfchar *name, ZF_IN QVariant const &tag);
extern ZF_ENV_EXPORT QVariant ZFImpl_sys_Qt_QObjectTagGet(ZF_IN_OUT QObject *obj, ZF_IN const zfchar *name);

extern ZF_ENV_EXPORT void ZFImpl_sys_Qt_QObjectTagSetZFObject(ZF_IN_OUT QObject *obj, ZF_IN const zfchar *name, ZF_IN ZFObject *tag);
extern ZF_ENV_EXPORT ZFObject *ZFImpl_sys_Qt_QObjectTagGetZFObject(ZF_IN_OUT QObject *obj, ZF_IN const zfchar *name);
template<typename T_ZFObject>
T_ZFObject ZFImpl_sys_Qt_QObjectTagGetZFObject(ZF_IN_OUT QObject *obj, ZF_IN const zfchar *name)
{
    return ZFCastZFObjectUnchecked(T_ZFObject, ZFImpl_sys_Qt_QObjectTagGetZFObject(obj, name));
}

// ============================================================
/**
 * @brief convert QString to zfstring, appended to result, do nothing if error
 */
extern ZF_ENV_EXPORT void ZFImpl_sys_Qt_zfstringFromQString(ZF_IN_OUT zfstring &result, ZF_IN QString const &nativeString);
/**
 * @brief convert QString to zfstring, appended to result, do nothing if error
 */
inline zfstring ZFImpl_sys_Qt_zfstringFromQString(ZF_IN QString const &nativeString)
{
    zfstring ret;
    ZFImpl_sys_Qt_zfstringFromQString(ret, nativeString);
    return ret;
}
/**
 * @brief convert zfstring to QString, return a autoreleased object
 */
extern ZF_ENV_EXPORT QString ZFImpl_sys_Qt_zfstringToQString(ZF_IN const zfchar *s);

ZF_NAMESPACE_GLOBAL_END
#endif // #if ZF_ENV_sys_Qt
#endif // #ifndef _ZFI_ZFImpl_sys_Qt_ZF_h_

