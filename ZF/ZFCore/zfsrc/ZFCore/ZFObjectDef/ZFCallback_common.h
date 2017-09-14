/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFCallback_common.h
 * @brief common callback defines
 */

#ifndef _ZFI_ZFCallback_common_h_
#define _ZFI_ZFCallback_common_h_

#include "ZFCallback.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief for advance user only
 *
 * for ZFOutputCallback and ZFInputCallback to achieve some additional operation\n
 * \n
 * usage:\n
 * set an auto released data by #ZFCallback::callbackTagSet,
 * whose key is #ZFCallbackTagKeyword_ioOwner and value is a ZFObject
 * that optionally implements those method (as #ZFMethod):
 * -  ioSeek, similar to FILE's fileSeek, proto type:\n
 *   zfindex ioSeek(ZF_IN zfindex byteSize,
 *                  ZF_IN ZFSeekPos pos);\n
 *   return newly seeked position or zfindexMax() if the callback doesn't support seek or error occurred
 * -  ioTell, similar to FILE's fileTell, proto type:\n
 *   zfindex ioTell(void);\n
 *   return current's index or zfindexMax() if the callback doesn't support seek
 * -  ioSize, calculate callback's size, proto type:\n
 *   zfindex ioSize(void);\n
 *   return size or zfindexMax() if the callback doesn't support
 *   @note for input callbacks, the size shows the current available size, may change after a ioSeek or execute call
 *   @note for ouput callbacks, the size shows the contents outputed to the output callback
 */
#define ZFCallbackTagKeyword_ioOwner zfText("ZFCallbackTagKeyword_ioOwner")
/**
 * @brief util method for ZFIOCallback::ioSeek's implementations to calculate seek index
 *
 * param:\n
 * -  (zfindex)offset callback's initial offset
 * -  (zfindex)length callback's length including offset (i.e. starting from 0)
 * -  (zfindex)curPos callback's current position including offset (i.e. start from 0)
 *
 * return an index start from 0 (offset is included), ensured range in [offset, length]
 */
extern ZF_ENV_EXPORT zfindex ZFIOCallbackCalcFSeek(ZF_IN zfindex offset,
                                                   ZF_IN zfindex length,
                                                   ZF_IN zfindex curPos,
                                                   ZF_IN zfindex seekByteSize,
                                                   ZF_IN ZFSeekPos seekPos);

// ============================================================
/**
 * @brief abstract base class, use #ZFOutputCallback or #ZFInputCallback
 */
ZFCALLBACK_DECLARE_BEGIN(ZFIOCallback, ZFCallback)
public:
    /**
     * @brief similar to FILE's fileSeek
     *
     * if seek out of range, no error would occurred and seek would try to seek the proper direction to the end\n
     * for some output callbacks, seek would cause outputed data being removed\n
     * return newly seeked position or zfindexMax() if the callback doesn't support seek
     */
    virtual zfindex ioSeek(ZF_IN zfindex byteSize,
                           ZF_IN_OPT ZFSeekPos pos = ZFSeekPosBegin) const;
    /**
     * @brief similar to FILE's fileTell, return current's index or zfindexMax() if the callback doesn't support seek
     */
    virtual zfindex ioTell(void) const;
    /**
     * @brief calculate the callback's size or return zfindexMax() if not supported
     */
    virtual zfindex ioSize(void) const;
_ZFP_ZFCALLBACK_DECLARE_END_NO_ALIAS(ZFIOCallback, ZFCallback)

// ============================================================
// ZFOutputCallback
/**
 * @brief general output callback
 *
 * proto type:
 * -  zfindex output(const void *, zfindex);
 *
 * params:
 * -  (const void *) output buffer
 * -  (zfindex) count, or zfindexMax() to calculate by src
 *  (src must be NULL-terminated)
 *
 * return:
 * -  char count written to output,
 *   or 0 if nothing to write or error occurred,
 *   or zfindexMax() if the output doesn't care the write result,
 *   so that only (result < desired) is an error state
 *
 * ADVANCED:\n
 * for implementations, see #ZFCallbackTagKeyword_ioOwner if need support seek
 */
ZFCALLBACK_DECLARE_BEGIN(ZFOutputCallback, ZFIOCallback)
public:
    /** @brief see #ZFOutputCallback */
    inline zfindex execute(ZF_IN const void *src,
                           ZF_IN_OPT zfindex count = zfindexMax()) const
    {
        return ZFCallback::executeExact<zfindex, const void *, zfindex>(src, count);
    }
    /** @brief see #ZFOutputCallback */
    inline zfindex operator()(ZF_IN const void *src,
                              ZF_IN_OPT zfindex count = zfindexMax()) const
    {
        return ZFCallback::executeExact<zfindex, const void *, zfindex>(src, count);
    }
_ZFP_ZFCALLBACK_DECLARE_END_NO_ALIAS(ZFOutputCallback, ZFIOCallback)

// ============================================================
// custom type output
#define _ZFP_ZFOUTPUT_EXPAND(T_Type) \
    template<> \
    zfclassNotPOD ZFCoreElementInfoGetter<T_Type> \
    { \
    public: \
        static void elementInfoGetter(ZF_IN_OUT zfstring &ret, ZF_IN T_Type const &v) \
        { \
            ZFCoreElementTokenGetter<T_Type>::elementTokenGetterLeft(ret, v); \
            { \
                ZFOutputCallbackForString(ret) << v; \
            } \
            ZFCoreElementTokenGetter<T_Type>::elementTokenGetterRight(ret, v); \
        } \
    };
/**
 * @brief declare your custom type to output to #ZFOutputCallback
 *
 * proto type:
 * @code
 *   const ZFOutputCallback &operator << (ZF_IN_OUT const ZFOutputCallback &output, ZF_IN YourType const &v);
 * @endcode
 * usage:
 * @code
 *   ZFOUTPUT_TYPE(YourType, {output.execute(v.toString());})
 * @endcode
 *
 * once declared, you may output your type to #ZFOutputCallback by:
 * @code
 *   output << yourObject;
 * @endcode
 */
#define ZFOUTPUT_TYPE(T_Type, outputAction) \
    /** @cond ZFPrivateDoc */ \
    inline const ZFOutputCallback &operator <<(const ZFOutputCallback &output, T_Type const &v) \
    { \
        if(output.callbackIsValid()) \
        outputAction \
        return output; \
    } \
    _ZFP_ZFOUTPUT_EXPAND(T_Type) \
    /** @endcond */
/**
 * @brief see #ZFOUTPUT_TYPE
 *
 * usage:
 * @code
 *   ZFOUTPUT_TYPE_TEMPLATE(ZFM_EXPAND(typename T0, typename T1),
 *                          ZFM_EXPAND(YourType<T0, T1>),
 *                          {output.execute(v.toString())})
 * @endcode
 */
#define ZFOUTPUT_TYPE_TEMPLATE(templateList, T_Type, outputAction) \
    /** @cond ZFPrivateDoc */ \
    template<templateList> \
    inline const ZFOutputCallback &operator <<(const ZFOutputCallback &output, T_Type const &v) \
    { \
        outputAction \
        return output; \
    } \
    template<templateList> \
    zfclassNotPOD ZFCoreElementInfoGetter<T_Type> \
    { \
    public: \
        static void elementInfoGetter(ZF_IN_OUT zfstring &ret, ZF_IN T_Type const &v) \
        { \
            ZFCoreElementTokenGetter<T_Type>::elementTokenGetterLeft(ret, v); \
            { \
                ZFOutputCallbackForString(ret) << v; \
            } \
            ZFCoreElementTokenGetter<T_Type>::elementTokenGetterRight(ret, v); \
        } \
    }; \
    /** @endcond */

/**
 * @brief see #ZFOUTPUT_TYPE
 *
 * usage:
 * @code
 *   // in header file
 *   ZFOUTPUT_TYPE_DECLARE(YourType)
 *   // in source file
 *   ZFOUTPUT_TYPE_DEFINE(YourType, {doYourStuff();})
 *
 *   // or, the inline version
 *   ZFOUTPUT_TYPE(YourType, {doYourStuff();})
 * @endcode
 */
#define ZFOUTPUT_TYPE_DECLARE(T_Type) \
    /** @cond ZFPrivateDoc */ \
    extern ZF_ENV_EXPORT const ZFOutputCallback &operator <<(const ZFOutputCallback &output, T_Type const &v); \
    _ZFP_ZFOUTPUT_EXPAND(T_Type) \
    /** @endcond */
/** @brief see #ZFOUTPUT_TYPE_DECLARE */
#define ZFOUTPUT_TYPE_DEFINE(T_Type, outputAction) \
    /** @cond ZFPrivateDoc */ \
    const ZFOutputCallback &operator <<(const ZFOutputCallback &output, T_Type const &v) \
    { \
        outputAction \
        return output; \
    } \
    /** @endcond */

// ============================================================
// common output callbacks
extern ZF_ENV_EXPORT ZFOutputCallback _ZFP_ZFOutputCallbackForString(ZF_IN const ZFCallerInfo &callerInfo,
                                                                     ZF_IN_OUT zfstring &s);
extern ZF_ENV_EXPORT ZFOutputCallback _ZFP_ZFOutputCallbackForBuffer(ZF_IN const ZFCallerInfo &callerInfo,
                                                                     ZF_IN void *buf,
                                                                     ZF_IN_OPT zfindex maxCount = zfindexMax(),
                                                                     ZF_IN_OPT zfbool autoAppendNullToken = zftrue);
/**
 * @brief create a output callback to output to a zfstring
 *
 * params:
 * -  (zfstring &) a zfstring to output
 *
 * @note you must ensure the string to output is alive while the callback is still under use
 */
#define ZFOutputCallbackForString(s) \
    _ZFP_ZFOutputCallbackForString(ZFCallerInfoMake(), s)
/**
 * @brief create a output callback to output to a buffer
 *
 * params:
 * -  (void *) buffer to write to
 * -  (zfindex) max buffer size or zfindexMax() for no limit (you must make sure buffer is enough)
 * -  (zfbool) whether auto append '\0' to tail each time write
 */
#define ZFOutputCallbackForBuffer(buf, ...) \
    _ZFP_ZFOutputCallbackForBuffer(ZFCallerInfoMake(), buf, ##__VA_ARGS__)

// ============================================================
// ZFInputCallback
/**
 * @brief general input callback
 *
 * proto type:
 * -  zfindex input(void *, zfindex);
 *
 * params:
 * -  (void *) buffer to write to,
 *   do nothing and return 0 if null
 * -  (zfindex) max read count (excluding '\0')
 *
 * return:
 * -  (zfindex) char count actually read (excluding '\0', may less than desired count such as EOF),
 *   or 0 if nothing to read (such as EOF) or error occurred
 *
 * ADVANCED:\n
 * for implementations, see #ZFCallbackTagKeyword_ioOwner if need support seek
 */
ZFCALLBACK_DECLARE_BEGIN(ZFInputCallback, ZFIOCallback)
public:
    /** @brief see #ZFInputCallback */
    inline zfindex execute(ZF_OUT void *buf,
                           ZF_IN zfindex count) const
    {
        return ZFCallback::executeExact<zfindex, void *, zfindex>(buf, count);
    }
    /** @brief see #ZFInputCallback */
    inline zfindex operator()(ZF_OUT void *buf,
                              ZF_IN zfindex count) const
    {
        return ZFCallback::executeExact<zfindex, void *, zfindex>(buf, count);
    }
_ZFP_ZFCALLBACK_DECLARE_END_NO_ALIAS(ZFInputCallback, ZFIOCallback)

// ============================================================
/**
 * @brief read single logic char to buf, return count of sizoef(zfchar) if success, or 0 if fail
 *
 * since UTF-8 has variable logic char size, use this method to read a single logic char\n
 * note: result may have more than one char for invalid encoding,
 * and buf size must at least 9 byte size
 */
extern ZF_ENV_EXPORT zfindex ZFInputCallbackReadChar(ZF_OUT zfchar *buf, ZF_IN_OUT const ZFInputCallback &input);
/**
 * @brief see #ZFInputCallbackReadChar
 */
extern ZF_ENV_EXPORT zfindex ZFInputCallbackReadChar(ZF_IN_OUT zfstring &buf, ZF_IN_OUT const ZFInputCallback &input);
/**
 * @brief util method to read all contents from input to a buffer
 *
 * returned buffer is ensured null-terminated,
 * and buffer's size shows the content's size excluding tail '\0'\n
 * return null buffer if input invalid or input error
 */
extern ZF_ENV_EXPORT ZFBuffer ZFInputCallbackReadToBuffer(ZF_IN_OUT const ZFInputCallback &input);

/**
 * @brief util method to read all contents of input to output
 *
 * return size already written to output even if error occurred
 */
extern ZF_ENV_EXPORT zfindex ZFInputCallbackReadToOutput(ZF_IN_OUT const ZFOutputCallback &output,
                                                         ZF_IN_OUT const ZFInputCallback &input);

/**
 * @brief util method to skip chars in set
 *
 * return false if all chars are skipped before end,
 * other wise, buf stores the first logic char (see #ZFInputCallbackReadChar)
 */
extern ZF_ENV_EXPORT zfbool ZFInputCallbackSkipChars(ZF_OUT zfchar *buf,
                                                     ZF_IN_OUT const ZFInputCallback &input,
                                                     ZF_IN_OPT const zfchar *charSet = zfText(" \t\r\n"));

/**
 * @brief read until any char in charSet shows up, or reached maxCount,
 *   return count read so far
 *
 * the first char matched charSet would be read and discarded,
 * and you may check it by firstCharMatchedCharSet,
 * if reached end or maxCount before matched charSet,
 * 0 would be returned to firstCharMatchedCharSet
 */
extern ZF_ENV_EXPORT zfindex ZFInputCallbackReadUntil(ZF_IN_OUT zfstring &ret,
                                                      ZF_IN_OUT const ZFInputCallback &input,
                                                      ZF_IN_OPT const zfchar *charSet = zfText(" \t\r\n"),
                                                      ZF_IN_OPT zfindex maxCount = zfindexMax(),
                                                      ZF_OUT_OPT zfchar *firstCharMatchedCharSet = zfnull);

/**
 * @brief util method to check whether the input match the tokens
 *
 * return token's index if match or zfindexMax() if no match or error,
 * header white spaces would be skipped automatically\n
 * if no match, this method would try to restore the callback state by ioSeek to original position
 */
extern ZF_ENV_EXPORT zfindex ZFInputCallbackCheckMatch(ZF_IN const zfchar **tokens,
                                                       ZF_IN zfindex tokenCount,
                                                       ZF_IN_OUT const ZFInputCallback &input);

// ============================================================
// common input callbacks
extern ZF_ENV_EXPORT ZFInputCallback _ZFP_ZFInputCallbackForInputInRange(ZF_IN const ZFCallerInfo &callerInfo,
                                                                         ZF_IN const ZFInputCallback &inputCallback,
                                                                         ZF_IN_OPT zfindex start = 0,
                                                                         ZF_IN_OPT zfindex count = zfindexMax(),
                                                                         ZF_IN_OPT zfbool autoRestorePos = zftrue);
/**
 * @brief see #ZFCALLBACK_SERIALIZE_CUSTOM_TYPE_DEFINE
 *
 * serializable data:
 * @code
 *   <node>
 *       <something category="input" ... />
 *       <zfindex category="start" ... /> // optional, 0 by default
 *       <zfindex category="count" ... /> // optional, zfindexMax() by default
 *       <zfbool category="autoRestorePos" ... /> // optional, zftrue by default
 *   </node>
 * @endcode
 */
#define ZFCallbackSerializeCustomTypeId_ZFInputCallbackForInputInRange ZFInputCallbackForInputInRange
/** @brief see #ZFCallbackSerializeCustomTypeRegister */
#define ZFCallbackSerializeCustomType_ZFInputCallbackForInputInRange ZFM_TOSTRING(ZFCallbackSerializeCustomTypeId_ZFInputCallbackForInputInRange)

/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFInputCallbackForInputInRange_input zfText("input")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFInputCallbackForInputInRange_start zfText("start")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFInputCallbackForInputInRange_count zfText("count")
/** @brief keyword for serialize */
#define ZFSerializableKeyword_ZFInputCallbackForInputInRange_autoRestorePos zfText("autoRestorePos")
/**
 * @brief create a intput callback from another input callback, specified in range
 *
 * params:
 * -  (const ZFInputCallback &) input callback to use
 * -  (zfindex) src's start index
 * -  (zfindex) src's count or zfindexMax() to use whole
 * -  (zfbool) whether to restore src input callback's position after result callback deleted
 *
 * seeking the result input callback would ensure in range [start, start + count]\n
 * src must support seek, otherwise a null callback would be returned
 */
#define ZFInputCallbackForInputInRange(anotherInputCallback, ...) \
    _ZFP_ZFInputCallbackForInputInRange(ZFCallerInfoMake(), anotherInputCallback, ##__VA_ARGS__)

extern ZF_ENV_EXPORT ZFInputCallback _ZFP_ZFInputCallbackForBuffer(ZF_IN const ZFCallerInfo &callerInfo,
                                                                   ZF_IN zfbool copy,
                                                                   ZF_IN const void *src,
                                                                   ZF_IN_OPT zfindex count = zfindexMax());
/**
 * @brief create a intput callback input from a const void *,
 *   you must ensure the buffer is alive during the callback's life time
 *
 * params:
 * -  (const void *) src to use
 * -  (zfindex) src's count or zfindexMax() to calculate automatically (treated as const zfchar *),
 *   zfindexMax() by default
 */
#define ZFInputCallbackForBuffer(buf, ...) \
    _ZFP_ZFInputCallbackForBuffer(ZFCallerInfoMake(), zffalse, buf, ##__VA_ARGS__)
/**
 * @brief see #ZFInputCallbackForBuffer,
 *   copy the contents and auto free it
 */
#define ZFInputCallbackForBufferCopy(buf, ...) \
    _ZFP_ZFInputCallbackForBuffer(ZFCallerInfoMake(), zftrue, buf, ##__VA_ARGS__)

// ============================================================
// ZFIOBridgeCallback
/**
 * @brief a util class to make a buffer to bridge input and output
 *
 * usage:
 * @code
 *   void outputFunc(ZF_IN const ZFOutputCallback &callback) {...}
 *   void inputFunc(ZF_IN const ZFInputCallback &callback) {...}
 *
 *   ZFIOBridgeCallbackXXX bridge;
 *   outputFunc(bridge); // output data to bridge's internal buffer
 *   inputFunc(bridge); // input data from bridge's internal buffer
 * @endcode
 */
zfclassLikePOD ZF_ENV_EXPORT ZFIOBridgeCallback
{
public:
    /** @cond ZFPrivateDoc */
    ZFIOBridgeCallback(void) {}
    ZFIOBridgeCallback(ZF_IN const ZFIOBridgeCallback &ref) {}
    /** @endcond */
    virtual ~ZFIOBridgeCallback(void) {}

public:
    /**
     * @brief implicit convert to input callback
     */
    virtual operator ZFInputCallback(void)
    {
        return this->inputCallback();
    }
    /**
     * @brief implicit convert to output callback
     */
    virtual operator ZFOutputCallback(void)
    {
        return this->outputCallback();
    }

public:
    /**
     * @brief get input callback
     */
    virtual ZFInputCallback inputCallback(void) zfpurevirtual;
    /**
     * @brief get input callback
     */
    virtual ZFOutputCallback outputCallback(void) zfpurevirtual;

public:
    /**
     * @brief reset input so that next input operation would read from begin
     */
    virtual void resetInput(void) zfpurevirtual;
    /**
     * @brief clear all outputed data so that next output operation would write from begin,
     *   note that input would also be reset
     */
    virtual void resetOutput(void) zfpurevirtual;
};

// ============================================================
// ZFIOBridgeCallbackUsingBuffer
zfclassFwd _ZFP_ZFIOBridgeCallbackUsingBufferPrivate;
/**
 * @brief see #ZFIOBridgeCallback
 */
zfclassLikePOD ZF_ENV_EXPORT ZFIOBridgeCallbackUsingBuffer : zfextendsLikePOD ZFIOBridgeCallback
{
public:
    /** @cond ZFPrivateDoc */
    ZFIOBridgeCallbackUsingBuffer(void);
    ZFIOBridgeCallbackUsingBuffer(ZF_IN const ZFIOBridgeCallbackUsingBuffer &ref);
    ZFIOBridgeCallbackUsingBuffer &operator =(ZF_IN const ZFIOBridgeCallbackUsingBuffer &ref);
    /** @endcond */
    virtual ~ZFIOBridgeCallbackUsingBuffer(void);

public:
    zfoverride
    virtual ZFInputCallback inputCallback(void);
    zfoverride
    virtual ZFOutputCallback outputCallback(void);

public:
    zfoverride
    virtual void resetInput(void);
    zfoverride
    virtual void resetOutput(void);

private:
    _ZFP_ZFIOBridgeCallbackUsingBufferPrivate *d;
};

// ============================================================
// basic output
ZFOUTPUT_TYPE(const zfchar *, {output.execute(v ? v : ZFTOKEN_zfnull);})
ZFOUTPUT_TYPE(zfchar *, {output << (const zfchar *)v;})

ZFOUTPUT_TYPE(const void *, {output.execute(v ? zfsFromPointer(v).cString() : ZFTOKEN_zfnull);})
ZFOUTPUT_TYPE(void *, {output << (const void *)v;})

/** @cond ZFPrivateDoc */
ZFM_CLASS_HAS_MEMBER_DECLARE(_ZFP_ZFOutputCallbackOutputZFObject, ClassData, const ZFClass * (*F)(void))
template<typename T_Type, int T_ZFObject = 0>
zfclassNotPOD _ZFP_ZFOutputCallbackOutputWrapper
{
public:
    static void outputAction(ZF_IN_OUT const ZFOutputCallback &output, T_Type const &v)
    {
        output << (*v);
    }
};
template<typename T_Type>
zfclassNotPOD _ZFP_ZFOutputCallbackOutputWrapper<T_Type, 1>
{
public:
    static void outputAction(ZF_IN_OUT const ZFOutputCallback &output, T_Type const &v)
    {
        output.execute(v->toObject()->objectInfo());
    }
};

template<typename T_Type>
const ZFOutputCallback &operator <<(const ZFOutputCallback &output, const T_Type * const &v)
{
    if(v == zfnull)
    {
        output.execute(ZFTOKEN_zfnull);
    }
    else
    {
        output << (*v);
    }
    return output;
}
template<typename T_Type>
const ZFOutputCallback &operator <<(const ZFOutputCallback &output, T_Type * const &v)
{
    if(v == zfnull)
    {
        output.execute(ZFTOKEN_zfnull);
    }
    else
    {
        _ZFP_ZFOutputCallbackOutputWrapper<T_Type *,
                ZFM_CLASS_HAS_MEMBER(_ZFP_ZFOutputCallbackOutputZFObject, ClassData, typename zftTraits<T_Type>::TrType) ? 1 : 0
            >::outputAction(output, v);
    }
    return output;
}
/** @endcond */

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFCallback_common_h_

