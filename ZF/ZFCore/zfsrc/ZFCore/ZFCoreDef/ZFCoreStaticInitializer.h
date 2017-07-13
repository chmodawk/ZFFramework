/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFCoreStaticInitializer.h
 * @brief static initializer step
 */
#ifndef _ZFI_ZFCoreStaticInitializer_h_
#define _ZFI_ZFCoreStaticInitializer_h_

#include "ZFCoreTypeDef.h"
#include "ZFCoreStaticRegister.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
zfclassNotPOD ZF_ENV_EXPORT _ZFP_SI_DummyBase
{
public:
    virtual ~_ZFP_SI_DummyBase(void)
    {
    }
};
typedef _ZFP_SI_DummyBase *(*_ZFP_SI_Constructor)(void);
extern ZF_ENV_EXPORT _ZFP_SI_DummyBase *&_ZFP_SI_instanceHolderAccess(ZF_IN const zfchar *name,
                                                                      ZF_IN _ZFP_SI_Constructor constructor);
extern ZF_ENV_EXPORT void _ZFP_SI_instanceCleanup(ZF_IN const zfchar *name);
zfclassLikePOD ZF_ENV_EXPORT _ZFP_SI_InstanceCleanupHolder
{
public:
    _ZFP_SI_InstanceCleanupHolder(ZF_IN const zfchar *name)
    : _name(name)
    {
    }
    ~_ZFP_SI_InstanceCleanupHolder(void)
    {
        _ZFP_SI_instanceCleanup(_name);
    }
private:
    const zfchar *_name;
};

// ============================================================
/**
 * @brief static initializer
 *
 * called before any other active code,
 * must be used in a cpp file\n
 * typical usage:
 * @code
 *   // in a cpp file only
 *   ZF_STATIC_INITIALIZER_INIT(YourInitName)
 *   : privateMember() // you may add member init here
 *   {
 *       // add your own init phase here
 *       // note: never access ZFFramework member here
 *   }
 *   ZF_STATIC_INITIALIZER_DESTROY(YourInitName)
 *   {
 *       // add your own cleanup phase here
 *       // note: never access ZFFramework member here
 *   }
 *   private:
 *       zfbool privateMember; // you may add member declaration here
 *       void func(void) {} // you may add private function here
 *   ZF_STATIC_INITIALIZER_END(YourInitName)
 * @endcode
 * \n
 * @note if more than one initializer exists,
 *   the order of the initialization is not ensured
 * @note use #ZF_GLOBAL_INITIALIZER_INIT is recommended at most of case
 * @warning you should not access any of ZFFramework members
 *   in the static initializer,
 *   you may check it by #ZFFrameworkStateCheck
 */
#define ZF_STATIC_INITIALIZER_INIT(Name) \
    zfclassNotPOD _ZFP_SI_##Name : zfextendsNotPOD _ZFP_SI_DummyBase \
    { \
    public: \
        static _ZFP_SI_DummyBase *_ZFP_SI_constructor_##Name(void) \
        { \
            return zfnew(_ZFP_SI_##Name); \
        } \
        static _ZFP_SI_##Name *_ZFP_SI_instanceAccess(void) \
        { \
            static _ZFP_SI_DummyBase *&instance = _ZFP_SI_instanceHolderAccess( \
                zfText(#Name), \
                _ZFP_SI_##Name::_ZFP_SI_constructor_##Name); \
            static _ZFP_SI_InstanceCleanupHolder _cleanupHolder(zfText(#Name)); \
            return ZFCastStatic(_ZFP_SI_##Name *, instance); \
        } \
    public: \
        _ZFP_SI_##Name(void)
/**
 * @brief see #ZF_STATIC_INITIALIZER_INIT
 */
#define ZF_STATIC_INITIALIZER_DESTROY(Name) \
        virtual ~_ZFP_SI_##Name(void)
/**
 * @brief see #ZF_STATIC_INITIALIZER_INIT
 */
#define ZF_STATIC_INITIALIZER_END(Name) \
    }; \
    ZF_STATIC_REGISTER_INIT(SI_##Name) \
    { \
        _ZFP_SI_##Name::_ZFP_SI_instanceAccess(); \
    } \
    ZF_STATIC_REGISTER_END(SI_##Name)
/**
 * @brief access the instance of the initializer
 */
#define ZF_STATIC_INITIALIZER_INSTANCE(Name) \
    (_ZFP_SI_##Name::_ZFP_SI_instanceAccess())

#define _ZFP_ZF_STATIC_INITIALIZER_CLASS(Name) \
    _ZFP_SI_##Name
/**
 * @brief the class holder of the static initializer
 */
#define ZF_STATIC_INITIALIZER_CLASS(Name) \
    _ZFP_ZF_STATIC_INITIALIZER_CLASS(Name)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFCoreStaticInitializer_h_

