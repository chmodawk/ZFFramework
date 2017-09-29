/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFLangUtil.h
 * @brief language util for localization
 */

#ifndef _ZFI_ZFLangUtil_h_
#define _ZFI_ZFLangUtil_h_

#include "ZFLang.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief see #zfLangApply
 */
typedef void (*ZFLangOnChangeCallback)(ZF_IN ZFObject *obj,
                                       ZF_IN const zfchar *objIdentity,
                                       ZF_IN const zfchar *langKey,
                                       ZF_IN const zfchar *langValue,
                                       ZF_IN_OPT ZFObject *userData);
/**
 * @brief util method to register an object that would be automatically updated
 *   when language changed (see #ZFGlobalEvent::EventLangOnChange)
 *
 * note, an object with the same objIdentity can only be applied once,
 * newly applied one would override old one\n
 * language auto update would be stopped automatically if the object would be deallocated,
 * or can be stopped manually by #zfLangApplyCancel
 * @note langChangeCallback would be called immediately to update for the first time
 */
extern ZF_ENV_EXPORT void zfLangApply(ZF_IN ZFObject *obj,
                                      ZF_IN const zfchar *objIdentity,
                                      ZF_IN const zfchar *langKey,
                                      ZF_IN ZFLangOnChangeCallback langChangeCallback,
                                      ZF_IN_OPT ZFObject *userData = zfnull);
/**
 * @brief cancel language auto update started by #zfLangApply
 *
 * by default, the language auto update would be stopped if the object would be deallocated,
 * there's no need to call this method for most cases
 */
extern ZF_ENV_EXPORT void zfLangApplyCancel(ZF_IN ZFObject *obj,
                                            ZF_IN const zfchar *objIdentity);

// ============================================================
/**
 * @brief util macro to declare #zfLangApply's implementation
 *
 * usage:
 * @code
 *   // in header file
 *   / ** you may add docs here * /
 *   ZFLANGAPPLY_DECLARE(YourObjectType, YourTypeName)
 *
 *   // in cpp file
 *   ZFLANGAPPLY_DEFINE(YourObjectType, YourTypeName, {obj->applyYourLang(objIdentity, langKey, langValue, userData);})
 *
 *   // impl function's proto type:
 *   //   void action(ZF_IN YourObjectType *obj,
 *   //       ZF_IN const zfchar *objIdentity,
 *   //       ZF_IN const zfchar *langKey,
 *   //       ZF_IN const zfchar *langValue,
 *   //       ZF_IN_OPT ZFObject *userData);
 * @endcode
 * expand this method for you:
 * @code
 *   void zfLangApplyYourTypeName(ZF_IN YourObjectType *,
 *                                ZF_IN const zfchar *langKey);
 *   void zfLangApplyCancelYourTypeName(ZF_IN YourObjectType *);
 * @endcode
 */
#define ZFLANGAPPLY_DECLARE(T_ZFObject, YourTypeName) \
    /** \n apply language for T_ZFObject */ \
    ZFMETHOD_FUNC_DECLARE_2(void, zfLangApply##YourTypeName, \
                            ZFMP_IN(T_ZFObject *, obj), \
                            ZFMP_IN(const zfchar *, langKey)) \
    /** @brief see #zfLangApplyCancel */ \
    ZFMETHOD_FUNC_DECLARE_1(void, zfLangApplyCancel##YourTypeName, \
                            ZFMP_IN(T_ZFObject *, obj))
/** @brief see #ZFLANGAPPLY_DECLARE */
#define ZFLANGAPPLY_DEFINE(T_ZFObject, YourTypeName, T_action) \
    zfclassNotPOD ZF_ENV_EXPORT _ZFP_zfLangApplyImpl_##YourTypeName \
    { \
    public: \
        static void _ZFP_action(ZF_IN ZFObject *_obj, \
                                ZF_IN const zfchar *objIdentity, \
                                ZF_IN const zfchar *langKey, \
                                ZF_IN const zfchar *langValue, \
                                ZF_IN_OPT ZFObject *userData) \
        { \
            T_ZFObject *obj = _obj->to<T_ZFObject *>(); \
            T_action \
        } \
    }; \
    ZFMETHOD_FUNC_DEFINE_2(void, zfLangApply##YourTypeName, \
                           ZFMP_IN(T_ZFObject *, obj), \
                           ZFMP_IN(const zfchar *, langKey)) \
    { \
        zfLangApply(ZFObjectToObject(obj), ZFM_TOSTRING(YourTypeName), langKey, _ZFP_zfLangApplyImpl_##YourTypeName::_ZFP_action); \
    } \
    ZFMETHOD_FUNC_DEFINE_1(void, zfLangApplyCancel##YourTypeName, \
                           ZFMP_IN(T_ZFObject *, obj)) \
    { \
        zfLangApplyCancel(ZFObjectToObject(obj), ZFM_TOSTRING(YourTypeName)); \
    }

// ============================================================
/**
 * @brief auto apply localized string to propery when #ZFGlobalEvent::EventLangOnChange
 */
ZFMETHOD_FUNC_DECLARE_3(void, zfLangApplyProperty_zfstring,
                        ZFMP_IN(ZFObject *, obj),
                        ZFMP_IN(const ZFProperty *, property),
                        ZFMP_IN(const zfchar *, langKey))
/** @brief see #zfLangApplyProperty_zfstring, #zfLangApplyCancel */
ZFMETHOD_FUNC_DECLARE_2(void, zfLangApplyCancelProperty_zfstring,
                        ZFMP_IN(ZFObject *, obj),
                        ZFMP_IN(const ZFProperty *, property))

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFLangUtil_h_

