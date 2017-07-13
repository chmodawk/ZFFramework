/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFCoreGlobalInitializer.h
 * @brief global initializer step
 */
#ifndef _ZFI_ZFCoreGlobalInitializer_h_
#define _ZFI_ZFCoreGlobalInitializer_h_

#include "ZFCoreTypeDef.h"
#include "ZFCoreLevel.h"
#include "ZFCoreStaticRegister.h"
#include "ZFCoreArray.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/** @brief see #ZFFrameworkInit */
typedef void (*ZFFrameworkStateChangeCallback)(void);
extern ZF_ENV_EXPORT ZFCoreArrayPOD<ZFFrameworkStateChangeCallback> &_ZFP_ZFFrameworkInitFinishCallbacks(void);
extern ZF_ENV_EXPORT ZFCoreArrayPOD<ZFFrameworkStateChangeCallback> &_ZFP_ZFFrameworkCleanupPrepareCallbacks(void);
/** @brief called when #ZFFrameworkInit finished */
#define ZFFrameworkInitFinishCallbacks _ZFP_ZFFrameworkInitFinishCallbacks()
/** @brief called when #ZFFrameworkInit finished */
#define ZFFrameworkCleanupPrepareCallbacks _ZFP_ZFFrameworkCleanupPrepareCallbacks()

// ============================================================
/**
 * @brief must be called in main thread before any access of ZFFramework member
 *
 * usually, this would been done by implementation of ZFFramework\n
 * \n
 * ADVANCED:\n
 * if you want to dynamically load other libs written in ZFFramework
 * after ZFFramework's main lib initialized:
 * -  you must manually call #ZFFrameworkInit to initialize your newly loaded lib
 * -  when unload the additional lib,
 *   the #ZF_GLOBAL_INITIALIZER_DESTROY's order is not ensured
 * -  #ZFFrameworkInitFinishCallbacks and #ZFFrameworkCleanupPrepareCallbacks
 *   won't be called when loading the additional lib
 */
extern ZF_ENV_EXPORT void ZFFrameworkInit(void);
/**
 * @brief see #ZFFrameworkInit
 */
extern ZF_ENV_EXPORT void ZFFrameworkCleanup(void);

/**
 * @brief state for ZFFramework
 */
typedef enum {
    ZFFrameworkStateNotAvailable, /**< @brief not available */
    ZFFrameworkStateInitProcessing, /**< @brief during init step (#ZFFrameworkInit) */
    ZFFrameworkStateAvailable, /**< @brief available, init finished */
    ZFFrameworkStateCleanupProcessing, /**< @brief during cleanup step (#ZFFrameworkCleanup) */
} ZFFrameworkState;

/** @brief string tokens */
#define ZFTOKEN_ZFFrameworkStateNotAvailable zfText("StateNotAvailable")
/** @brief string tokens */
#define ZFTOKEN_ZFFrameworkStateInitProcessing zfText("StateInitProcessing")
/** @brief string tokens */
#define ZFTOKEN_ZFFrameworkStateAvailable zfText("StateAvailable")
/** @brief string tokens */
#define ZFTOKEN_ZFFrameworkStateCleanupProcessing zfText("StateCleanupProcessing")

/**
 * @brief assert fail and output log if ZFFramework not initialized
 */
extern ZF_ENV_EXPORT void ZFFrameworkAssertInit(void);
/**
 * @brief get current state of ZFFramework
 */
extern ZF_ENV_EXPORT ZFFrameworkState ZFFrameworkStateCheck(void);
/**
 * @brief get current state of ZFFramework of specified level
 */
extern ZF_ENV_EXPORT ZFFrameworkState ZFFrameworkStateCheck(ZF_IN ZFLevel level);

// ============================================================
zfclassNotPOD ZF_ENV_EXPORT _ZFP_GI_DummyBase
{
public:
    virtual ~_ZFP_GI_DummyBase(void)
    {
    }
};
typedef _ZFP_GI_DummyBase *(*_ZFP_GI_Constructor)(void);
extern ZF_ENV_EXPORT void _ZFP_GI_dataRegister(ZF_IN zfbool *ZFCoreLibDestroyFlag,
                                               ZF_IN const zfchar *name,
                                               ZF_IN ZFLevel level,
                                               ZF_IN _ZFP_GI_Constructor constructor);
extern ZF_ENV_EXPORT void _ZFP_GI_dataUnregister(ZF_IN zfbool *ZFCoreLibDestroyFlag,
                                                 ZF_IN const zfchar *name,
                                                 ZF_IN ZFLevel level);
extern ZF_ENV_EXPORT _ZFP_GI_DummyBase *&_ZFP_GI_instanceHolderAccess(ZF_IN const zfchar *name,
                                                                      ZF_IN ZFLevel level);

#define _ZFP_ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(Name, ZFLevel_) \
    /** @cond ZFPrivateDoc */ \
    zfclassNotPOD _ZFP_GI_##Name : zfextendsNotPOD _ZFP_GI_DummyBase \
    { \
    protected: \
        typedef _ZFP_GI_##Name zfself; \
    public: \
        static void _ZFP_GI_register(ZF_IN zfbool *ZFCoreLibDestroyFlag) \
        { \
            _ZFP_GI_dataRegister(ZFCoreLibDestroyFlag, ZFM_TOSTRING(Name), ZFLevel_, _ZFP_GI_##Name::_ZFP_GI_construct); \
        } \
        static void _ZFP_GI_unregister(ZF_IN zfbool *ZFCoreLibDestroyFlag) \
        { \
            _ZFP_GI_dataUnregister(ZFCoreLibDestroyFlag, ZFM_TOSTRING(Name), ZFLevel_); \
        } \
        static _ZFP_GI_DummyBase *_ZFP_GI_construct(void) \
        { \
            return zfnew(_ZFP_GI_##Name); \
        } \
        static _ZFP_GI_##Name *_ZFP_GI_instanceAccess(void) \
        { \
            static _ZFP_GI_DummyBase *&instance = \
                _ZFP_GI_instanceHolderAccess( \
                    ZFM_TOSTRING(Name), \
                    ZFLevel_); \
            if(instance == zfnull) \
            { \
                (void)_ZFP_GI_instanceHolderAccess( \
                    ZFM_TOSTRING(Name), \
                    ZFLevel_); \
            } \
            return ZFCastStatic(_ZFP_GI_##Name *, instance); \
        } \
        _ZFP_GI_##Name(void)
/**
 * @brief code block that will be executed when app start and stop
 *
 * usage:
 * @code
 *   // in a *.cpp file
 *   ZF_GLOBAL_INITIALIZER_INIT(SomeName)
 *   : data('c') // you can init member here
 *   {
 *       // code that will be executed when app start
 *   }
 *   ZF_GLOBAL_INITIALIZER_DESTROY(SomeName)
 *   {
 *       // code that will be executed when app stop
 *   }
 *   private:
 *       zfchar data; // you can add member here
 *   private:
 *       void func() {} // you can add function here
 *   ZF_GLOBAL_INITIALIZER_END(SomeName)
 * @endcode
 * \n
 * @warning if you have more than one initializer with same level,
 *   the execute order of the code block is not ensured
 * @warning init and destroy step is not one time,
 *   they'll be called each time ZFFrameworkInit/ZFFrameworkCleanup is called
 */
#define ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(Name, ZFLevel_) \
    _ZFP_ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(Name, ZFLevel_)

/**
 * @brief see #ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL
 */
#define ZF_GLOBAL_INITIALIZER_INIT(Name) \
    _ZFP_ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(Name, ZFLevelAppNormal)

#define _ZFP_ZF_GLOBAL_INITIALIZER_DESTROY(Name) \
    public: \
        virtual ~_ZFP_GI_##Name(void)
/**
 * @brief see #ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL
 */
#define ZF_GLOBAL_INITIALIZER_DESTROY(Name) \
    _ZFP_ZF_GLOBAL_INITIALIZER_DESTROY(Name)

#define _ZFP_ZF_GLOBAL_INITIALIZER_END(Name) \
    }; \
    /** @endcond */ \
    ZF_STATIC_REGISTER_INIT(GI_##Name) \
    { \
        ZFCoreLibDestroyFlag = zffalse; \
        _ZFP_GI_##Name::_ZFP_GI_register(&ZFCoreLibDestroyFlag); \
    } \
    ZF_STATIC_REGISTER_DESTROY(GI_##Name) \
    { \
        _ZFP_GI_##Name::_ZFP_GI_unregister(&ZFCoreLibDestroyFlag); \
    } \
    private: \
        zfbool ZFCoreLibDestroyFlag; \
    ZF_STATIC_REGISTER_END(GI_##Name)
/**
 * @brief see #ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL
 */
#define ZF_GLOBAL_INITIALIZER_END(Name) \
    _ZFP_ZF_GLOBAL_INITIALIZER_END(Name)

#define _ZFP_ZF_GLOBAL_INITIALIZER_INSTANCE(Name) \
    (_ZFP_GI_##Name::_ZFP_GI_instanceAccess())
/**
 * @brief access the instance of the initializer
 */
#define ZF_GLOBAL_INITIALIZER_INSTANCE(Name) \
    _ZFP_ZF_GLOBAL_INITIALIZER_INSTANCE(Name)

#define _ZFP_ZF_GLOBAL_INITIALIZER_CLASS(Name) \
    _ZFP_GI_##Name
/**
 * @brief the class holder of the global initializer
 */
#define ZF_GLOBAL_INITIALIZER_CLASS(Name) \
    _ZFP_ZF_GLOBAL_INITIALIZER_CLASS(Name)

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFCoreGlobalInitializer_h_

