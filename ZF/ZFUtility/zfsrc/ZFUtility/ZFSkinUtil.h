/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFSkinUtil.h
 * @brief skin util for localization
 */

#ifndef _ZFI_ZFSkinUtil_h_
#define _ZFI_ZFSkinUtil_h_

#include "ZFSkin.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief see #zfSkinApply
 */
typedef void (*ZFSkinOnChangeCallback)(ZF_IN ZFStyleable *obj,
                                       ZF_IN const zfchar *objIdentity,
                                       ZF_IN const zfchar *skinKey,
                                       ZF_IN ZFStyleable *skinValueOrNull,
                                       ZF_IN_OPT ZFObject *userData);
/**
 * @brief util method to register an object that would be automatically updated
 *   when skin changed (see #ZFGlobalEvent::EventSkinOnChange)
 *
 * note, an object with the same objIdentity can only be applied once,
 * newly applied one would override old one\n
 * skin auto update would be stopped automatically if the object would be deallocated,
 * or can be stopped manually by #zfSkinApplyCancel
 * @note skinChangeCallback would be called immediately to update for the first time
 */
extern ZF_ENV_EXPORT void zfSkinApply(ZF_IN ZFStyleable *obj,
                                      ZF_IN const zfchar *objIdentity,
                                      ZF_IN const zfchar *skinKey,
                                      ZF_IN ZFSkinOnChangeCallback skinChangeCallback,
                                      ZF_IN_OPT ZFObject *userData = zfnull);
/**
 * @brief cancel skin auto update started by #zfSkinApply
 *
 * by default, the skin auto update would be stopped if the object would be deallocated,
 * there's no need to call this method for most cases
 */
extern ZF_ENV_EXPORT void zfSkinApplyCancel(ZF_IN ZFStyleable *obj,
                                            ZF_IN const zfchar *objIdentity);

// ============================================================
/**
 * @brief util macro to declare #zfSkinApply's implementation
 *
 * usage:
 * @code
 *   // in header file
 *   / ** you may add docs here * /
 *   ZFSKINAPPLY_DECLARE(YourObjectType, YourTypeName)
 *
 *   // in cpp file
 *   ZFSKINAPPLY_DEFINE(YourObjectType, YourTypeName, {obj->applyYourSkin(objIdentity, skinKey, skinValueOrNull, userData);})
 *
 *   // impl function's proto type:
 *   //   void action(ZF_IN ZFStyleable *obj,
 *   //       ZF_IN const zfchar *objIdentity,
 *   //       ZF_IN const zfchar *skinKey,
 *   //       ZF_IN ZFStyleable *skinValueOrNull,
 *   //       ZF_IN_OPT ZFObject *userData);
 * @endcode
 * expand this method for you:
 * @code
 *   void zfSkinApplyYourTypeName(ZF_IN YourObjectType *,
 *                                ZF_IN const zfchar *skinKey);
 *   void zfSkinApplyCancelYourTypeName(ZF_IN YourObjectType *);
 * @endcode
 */
#define ZFSKINAPPLY_DECLARE(YourTypeName) \
    /** \n apply skin */ \
    ZFMETHOD_FUNC_DECLARE_2(void, zfSkinApply##YourTypeName, \
                            ZFMP_IN(ZFStyleable *, obj), \
                            ZFMP_IN(const zfchar *, skinKey)) \
    /** @brief see #zfSkinApplyCancel */ \
    ZFMETHOD_FUNC_DECLARE_1(void, zfSkinApplyCancel##YourTypeName, \
                            ZFMP_IN(ZFStyleable *, obj))
/** @brief see #ZFSKINAPPLY_DECLARE */
#define ZFSKINAPPLY_DEFINE(YourTypeName, T_action) \
    zfclassNotPOD ZF_ENV_EXPORT _ZFP_zfSkinApplyImpl_##YourTypeName \
    { \
    public: \
        static void _ZFP_action(ZF_IN ZFStyleable *obj, \
                                ZF_IN const zfchar *objIdentity, \
                                ZF_IN const zfchar *skinKey, \
                                ZF_IN ZFStyleable *skinValueOrNull, \
                                ZF_IN_OPT ZFObject *userData) \
        { \
            T_action \
        } \
    }; \
    ZFMETHOD_FUNC_DEFINE_2(void, zfSkinApply##YourTypeName, \
                           ZFMP_IN(ZFStyleable *, obj), \
                           ZFMP_IN(const zfchar *, skinKey)) \
    { \
        zfSkinApply(obj, ZFM_TOSTRING(YourTypeName), skinKey, _ZFP_zfSkinApplyImpl_##YourTypeName::_ZFP_action); \
    } \
    ZFMETHOD_FUNC_DEFINE_1(void, zfSkinApplyCancel##YourTypeName, \
                           ZFMP_IN(ZFStyleable *, obj)) \
    { \
        zfSkinApplyCancel(obj, ZFM_TOSTRING(YourTypeName)); \
    }

ZFSKINAPPLY_DECLARE(ZFStyleable)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFSkinUtil_h_

