/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFLang.h
 * @brief language util for localization
 */

#ifndef _ZFI_ZFLang_h_
#define _ZFI_ZFLang_h_

#include "ZFUtilityDef.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZF_NAMESPACE_BEGIN(ZFGlobalEvent)
/**
 * @brief see #ZFObject::observerNotify
 *
 * called when language changed
 */
ZFOBSERVER_EVENT_GLOBAL(LangOnChange)
ZF_NAMESPACE_END(ZFGlobalEvent)

// ============================================================
/**
 * @brief access localized string with key,
 *   or return the key itself if no such localized string or not loaded
 *
 * to use localized string, you must:
 * -  prepare your own language file and load it manually,
 *   then store language datas by #zfLangSet
 * -  use this method to access localized language
 *
 * it all depends on app to manage language files,
 * and decide which file to use
 */
ZFMETHOD_FUNC_DECLARE_3(void, zfLang,
                        ZFMP_IN_OUT(zfstring &, ret),
                        ZFMP_IN(const zfchar *, key),
                        ZFMP_IN_OPT(const zfchar *, valueDefault, zfnull))
/** @brief see #zfLang */
ZFMETHOD_FUNC_DECLARE_INLINE_2(zfstring, zfLang,
                               ZFMP_IN(const zfchar *, key),
                               ZFMP_IN_OPT(const zfchar *, valueDefault, zfnull))
{
    zfstring ret;
    zfLang(ret, key, valueDefault);
    return ret;
}

/**
 * @brief notify lang changed
 */
ZFMETHOD_FUNC_DECLARE_0(void, zfLangNotifyChanged)

/**
 * @brief manually change one language data, or remove if value is null
 *
 * no event would be fired when set by this method, no thread-safe is supplied\n
 * for implementation that supply load logic, you should:
 * -# load by your own logic, and save by #zfLangSet
 * -# notify data changed by #zfLangNotifyChanged
 */
ZFMETHOD_FUNC_DECLARE_2(void, zfLangSet,
                        ZFMP_IN(const zfchar *, key),
                        ZFMP_IN(const zfchar *, value))
/**
 * @brief similar to #zfLangSet, but applies only if not exist
 */
ZFMETHOD_FUNC_DECLARE_2(void, zfLangSetDefault,
                        ZFMP_IN(const zfchar *, key),
                        ZFMP_IN(const zfchar *, value))

/**
 * @brief unload all data (not recommended)
 */
ZFMETHOD_FUNC_DECLARE_0(void, zfLangUnload)

/**
 * @brief for debug use only
 */
ZFMETHOD_FUNC_DECLARE_1(void, zfLangDebug,
                        ZFMP_IN_OPT(const ZFOutputCallback &, output, ZFOutputCallbackDefault()))

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFLang_h_

#include "ZFLangUtil.h"

