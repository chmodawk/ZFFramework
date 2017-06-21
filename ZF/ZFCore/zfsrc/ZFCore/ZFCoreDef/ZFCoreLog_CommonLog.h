/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFCoreLog_CommonLog.h
 * @brief common log messages for ZFFramework
 *
 * used internally, you should use zfLog or zfDebug instead
 */

#ifndef _ZFI_ZFCoreLog_CommonLog_h_
#define _ZFI_ZFCoreLog_CommonLog_h_

#include "ZFCoreLog.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief print a critical error message which is easy to notice
 */
#define zfCoreLogCriticalMessage(fmt, ...) \
    do { \
        zfCoreLogTrimNoEndl(zfTextA("============================================================\n")); \
        zfCoreLogTrimNoEndl(zfTextA("| ")); \
        zfCoreLog(fmt, ##__VA_ARGS__); \
        zfCoreLogTrimNoEndl(zfTextA("============================================================\n")); \
    } while(zffalse)

/**
 * @brief see #zfCoreLogCriticalMessage
 */
#define zfCoreLogCriticalMessageTrim(fmt, ...) \
    do { \
        zfCoreLogTrimNoEndl(zfTextA("============================================================\n")); \
        zfCoreLogTrimNoEndl(zfTextA("| ")); \
        zfCoreLogTrim(fmt, ##__VA_ARGS__); \
        zfCoreLogTrimNoEndl(zfTextA("============================================================\n")); \
    } while(zffalse)

/**
 * @brief see #zfCoreLogCriticalMessage
 */
#define zfCoreLogCriticalMessageDetail(callerInfo, fmt, ...) \
    do { \
        zfCoreLogTrimNoEndl(zfTextA("============================================================\n")); \
        zfCoreLogTrimNoEndl(zfTextA("| ")); \
        zfCoreLogDetail(callerInfo, fmt, ##__VA_ARGS__); \
        zfCoreLogTrimNoEndl(zfTextA("============================================================\n")); \
    } while(zffalse)

// ============================================================
/**
 * @brief assert exp is zftrue
 *
 * do nothing if exp is zftrue, otherwise,
 * print a critical error message,
 * then terminate app by #zfCoreCriticalError
 * @note unlike zfassert, this function is always active, even if ZF_ENV_DEBUG is zftrue
 * @see zfassert
 */
#define zfCoreAssert(exp) \
    zfCoreAssertWithMessage(exp, zfTextA("assert failed for \"%s\""), ZFM_TOSTRING_A(exp))

/**
 * @brief see #zfCoreAssert
 */
#define zfCoreAssertTrim(exp) \
    zfCoreAssertWithMessageTrim(exp, zfTextA("assert failed for \"%s\""), ZFM_TOSTRING_A(exp))

/**
 * @brief see #zfCoreAssert
 */
#define zfCoreAssertDetail(exp, callerInfo) \
    zfCoreAssertWithMessageDetail(exp, callerInfo, zfTextA("assert failed for \"%s\""), ZFM_TOSTRING_A(exp))

// ============================================================
/**
 * @brief print a critical error message and abort
 */
#define zfCoreCriticalMessage(fmt, ...) \
    do { \
        zfCoreCriticalErrorPrepare(); \
        zfCoreLogCriticalMessage(fmt, ##__VA_ARGS__); \
        zfCoreCriticalError(); \
    } while(zffalse)

/**
 * @brief see #zfCoreCriticalMessage
 */
#define zfCoreCriticalMessageTrim(fmt, ...) \
    do { \
        zfCoreCriticalErrorPrepare(); \
        zfCoreLogCriticalMessageTrim(fmt, ##__VA_ARGS__); \
        zfCoreCriticalError(); \
    } while(zffalse)

/**
 * @brief see #zfCoreCriticalMessage
 */
#define zfCoreCriticalMessageDetail(callerInfo, fmt, ...) \
    do { \
        zfCoreCriticalErrorPrepare(); \
        zfCoreLogCriticalMessageDetail(callerInfo, fmt, ##__VA_ARGS__); \
        zfCoreCriticalError(); \
    } while(zffalse)

// ============================================================
/**
 * @brief #zfCoreAssert with custom message
 */
#define zfCoreAssertWithMessage(exp, fmt, ...) \
    do \
    { \
        if(!(exp)) \
        { \
            zfCoreCriticalMessage(fmt, ##__VA_ARGS__); \
        } \
    } while(zffalse)

/**
 * @brief see #zfCoreAssertWithMessage
 */
#define zfCoreAssertWithMessageTrim(exp, fmt, ...) \
    do \
    { \
        if(!(exp)) \
        { \
            zfCoreCriticalMessageTrim(fmt, ##__VA_ARGS__); \
        } \
    } while(zffalse)

/**
 * @brief see #zfCoreAssertWithMessage
 */
#define zfCoreAssertWithMessageDetail(exp, callerInfo, fmt, ...) \
    do \
    { \
        if(!(exp)) \
        { \
            zfCoreCriticalMessageDetail(callerInfo, fmt, ##__VA_ARGS__); \
        } \
    } while(zffalse)

// ============================================================
/**
 * @brief log that likes "[file function (line)] index i out of range [0, n)"
 */
#define zfCoreCriticalIndexOutOfRange(index, range) \
    do { \
        zfCoreCriticalErrorPrepare(); \
        zfCoreLogCriticalMessage(zfTextA("index %s out of range [0, %s)"), \
            zfsFromInt<zfstringA>(index).cString(), \
            zfsFromInt<zfstringA>(range).cString()); \
        zfCoreCriticalError(); \
    } while(zffalse)
/**
 * @brief see #zfCoreCriticalIndexOutOfRange
 */
#define zfCoreCriticalIndexOutOfRangeDetail(index, range, callerInfo) \
    do { \
        zfCoreCriticalErrorPrepare(); \
        zfCoreLogCriticalMessageDetail(callerInfo, \
            zfTextA("index %s out of range [0, %s)"), \
            zfsFromInt<zfstringA>(index).cString(), \
            zfsFromInt<zfstringA>(range).cString()); \
        zfCoreCriticalError(); \
    } while(zffalse)

// ============================================================
/**
 * @brief log that likes "[file function (line)] should not go here"
 */
#define zfCoreCriticalShouldNotGoHere() \
    do { \
        zfCoreCriticalErrorPrepare(); \
        zfCoreLogCriticalMessage(zfTextA("should not go here")); \
        zfCoreCriticalError(); \
    } while(zffalse)
/**
 * @brief see #zfCoreCriticalShouldNotGoHere
 */
#define zfCoreCriticalShouldNotGoHereDetail(callerInfo) \
    do { \
        zfCoreCriticalErrorPrepare(); \
        zfCoreLogCriticalMessageDetail(callerInfo, zfTextA("should not go here")); \
        zfCoreCriticalError(); \
    } while(zffalse)

// ============================================================
/**
 * @brief log that likes "[file function (line)] not supported"
 */
#define zfCoreCriticalNotSupported() \
    do { \
        zfCoreCriticalErrorPrepare(); \
        zfCoreLogCriticalMessage(zfTextA("not supported")); \
        zfCoreCriticalError(); \
    } while(zffalse)
/**
 * @brief see #zfCoreCriticalNotSupported
 */
#define zfCoreCriticalNotSupportedDetail(callerInfo) \
    do { \
        zfCoreCriticalErrorPrepare(); \
        zfCoreLogCriticalMessageDetail(callerInfo, zfTextA("not supported")); \
        zfCoreCriticalError(); \
    } while(zffalse)

ZF_NAMESPACE_GLOBAL_END

#if 0 // test only
    #if (defined(ANDROID) || defined(__ANDROID__))
        #include <jni.h>
        #include <android/log.h>
        #define zfzfzfLog(fmt, ...) \
            ((void)__android_log_print(ANDROID_LOG_ERROR, "test", fmt, ##__VA_ARGS__))
    #elif (defined(QT_VERSION) || defined(QT_CORE_LIB))
        #include <QDebug>
        #define zfzfzfLog(fmt, ...) \
            qDebug(fmt, ##__VA_ARGS__)
    #else
        #include <stdio.h>
        #define zfzfzfLog(fmt, ...) \
            do { \
                printf(fmt, ##__VA_ARGS__); \
                printf("\n"); \
            } while(false)
    #endif
#endif

#endif // #ifndef _ZFI_ZFCoreLog_CommonLog_h_

