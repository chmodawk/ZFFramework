/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFCoreUtilCallerInfo.h
 * @brief caller info utils
 */
#ifndef _ZFI_ZFCoreUtilCallerInfo_h_
#define _ZFI_ZFCoreUtilCallerInfo_h_

#include "ZFCoreUtilCharTypeWrapper.h"
#include "ZFCoreStringUtil.h"

ZF_NAMESPACE_GLOBAL_BEGIN

template<typename T_Char>
ZF_ENV_EXPORT void _ZFP_ZF_CALLER_FILE_TO_NAME(ZF_IN_OUT typename zfwrapCharToString<T_Char>::StringType &ret,
                                               ZF_IN const T_Char *filePath)
{
    if(filePath == zfnull)
    {
        return ;
    }
    const T_Char *p = filePath + zfslenT(filePath);
    while(p > filePath)
    {
        --p;
        if(*p == '/' || *p == '\\')
        {
            ++p;
            break;
        }
    }
    ret += p;
}
template<typename T_Char>
ZF_ENV_EXPORT typename zfwrapCharToString<T_Char>::StringType _ZFP_ZF_CALLER_FILE_TO_NAME(ZF_IN const T_Char *filePath)
{
    typename zfwrapCharToString<T_Char>::StringType ret;
    _ZFP_ZF_CALLER_FILE_TO_NAME(ret, filePath);
    return ret;
}
/**
 * @brief convert file path to file name
 *
 * used by ZF_CALLER_FILE_NAME, you may use this function directly if you want\n
 * the return value would be deleted after line end,
 * you should not save the value for future use,
 * store it in a std::string if necessary
 */
#define ZF_CALLER_FILE_TO_NAME(path) (_ZFP_ZF_CALLER_FILE_TO_NAME(path).cString())
/**
 * @brief see #ZF_CALLER_FILE_TO_NAME
 */
#define ZF_CALLER_FILE_TO_NAME_REF(ret, path) _ZFP_ZF_CALLER_FILE_TO_NAME(ret, path)
/**
 * @brief similar to __FILE__ in C++ world, except that don't include full path
 *
 * note that this macro contains string convertion, take care of performance if necessary\n
 * the return value would be deleted after line end,
 * you should not save the value for future use,
 * store it in a zfstring if necessary
 */
#define ZF_CALLER_FILE_NAME ZF_CALLER_FILE_TO_NAME(__FILE__)

/**
 * @brief same as __FILE__ in C++ world
 *
 * ensured in zfcharA format, you should convert to zfchar type if necessary
 */
#define ZF_CALLER_FILE __FILE__
/**
 * @brief same as __FUNCTION__ in C++ world
 *
 * ensured in zfcharA format, you should convert to zfchar type if necessary
 */
#define ZF_CALLER_FUNCTION __FUNCTION__
/**
 * @brief same as __LINE__ in C++ world
 */
#define ZF_CALLER_LINE __LINE__

// ============================================================
// ZFCallerInfo
/**
 * @brief util class to hold caller info
 *
 * note: caller file and function name are stored as raw pointer for performance,
 * use #ZFCallerInfoHolder if necessary
 */
zfclassLikePOD ZF_ENV_EXPORT ZFCallerInfo
{
public:
    virtual ~ZFCallerInfo(void) {}
    /**
     * @brief main constructor
     */
    ZFCallerInfo(ZF_IN_OPT const zfcharA *callerFile = zfnull,
                 ZF_IN_OPT const zfcharA *callerFunc = zfnull,
                 ZF_IN_OPT zfindex callerLine = 0)
    : _callerFile(zfsCoreA2Z(callerFile))
    , _callerFunc(zfsCoreA2Z(callerFunc))
    , _callerLine(callerLine)
    {
    }
    /** @cond ZFPrivateDoc */
    ZFCallerInfo(ZF_IN const ZFCallerInfo &ref)
    : _callerFile(ref._callerFile)
    , _callerFunc(ref._callerFunc)
    , _callerLine(ref._callerLine)
    {
    }
    virtual ZFCallerInfo &operator =(ZF_IN const ZFCallerInfo &ref)
    {
        _callerFile = ref._callerFile;
        _callerFunc = ref._callerFunc;
        _callerLine = ref._callerLine;
        return *this;
    }
    zfbool operator == (ZF_IN const ZFCallerInfo &ref) const
    {
        return (zfscmpTheSame((const zfchar *)_callerFile, (const zfchar *)ref._callerFile)
                && zfscmpTheSame((const zfchar *)_callerFunc, (const zfchar *)ref._callerFunc)
                && _callerLine == ref._callerLine);
    }
    inline zfbool operator != (ZF_IN const ZFCallerInfo &ref) const {return !this->operator == (ref);}
    /** @endcond */
public:
    /**
     * @brief set the caller info
     */
    virtual void callerInfoSet(ZF_IN_OPT const zfcharA *callerFile = zfnull,
                               ZF_IN_OPT const zfcharA *callerFunc = zfnull,
                               ZF_IN_OPT zfindex callerLine = 0)
    {
        _callerFile = zfsCoreA2Z(callerFile);
        _callerFunc = zfsCoreA2Z(callerFunc);
        _callerLine = callerLine;
    }
    /** @brief return caller info looks like "[File function (line)]" */
    inline zfbool callerInfoT(ZF_IN_OUT zfstring &ret) const
    {
        if(this->callerFile() != zfnull)
        {
            _callerInfo(ret);
            return zftrue;
        }
        else
        {
            return zffalse;
        }
    }
    /** @brief return caller info looks like "[File function (line)]" */
    inline zfstring callerInfo(void) const
    {
        zfstring ret;
        this->callerInfoT(ret);
        return ret;
    }
    /** @brief return caller info looks like "[File function (line)]" */
    inline zfstringA callerInfoA(void) const
    {
        zfstringA ret;
        this->callerInfoAT(ret);
        return ret;
    }
public:
    /** @brief return object info */
    inline void objectInfoT(ZF_IN_OUT zfstring &ret) const
    {
        this->callerInfoT(ret);
    }
    /** @brief return object info */
    inline zfstring objectInfo(void) const
    {
        zfstring ret;
        this->objectInfoT(ret);
        return ret;
    }
private:
    void _callerInfo(ZF_IN_OUT zfstring &ret) const
    {
        ret += zfText("[");
        ZF_CALLER_FILE_TO_NAME_REF(ret, this->callerFile());
        ret += zfText(" ");
        ret += this->callerFunc();
        ret += zfText(" (");
        zfsFromIntT(ret, this->callerLine());
        ret += zfText(")]");
    }

#if ZFCHAR_TYPE_SAME_AS_CHAR_A
    protected:
        /** @cond ZFPrivateDoc */
        const zfchar *_callerFile;
        const zfchar *_callerFunc;
        zfindex _callerLine;
        /** @endcond */
    public:
        /** @brief see #ZF_CALLER_FILE */
        inline const zfchar *callerFile(void) const {return _callerFile;}
        /** @brief see #ZF_CALLER_FUNCTION */
        inline const zfchar *callerFunc(void) const {return _callerFunc;}
        /** @brief see #ZF_CALLER_LINE */
        inline zfindex callerLine(void) const {return _callerLine;}

        /** @brief return caller info looks like "[File function (line)]" */
        inline zfbool callerInfoAT(ZF_IN_OUT zfstringA &ret) const
        {
            if(this->callerFile() != zfnull)
            {
                _callerInfo(ret);
                return zftrue;
            }
            else
            {
                return zffalse;
            }
        }
#else
    protected:
        /** @cond ZFPrivateDoc */
        zfstring _callerFile;
        zfstring _callerFunc;
        zfindex _callerLine;
        /** @endcond */
    public:
        /** @brief see #ZF_CALLER_FILE */
        inline const zfchar *callerFile(void) const {return _callerFile.isEmpty() ? zfnull : _callerFile.cString();}
        /** @brief see #ZF_CALLER_FUNCTION */
        inline const zfchar *callerFunc(void) const {return _callerFunc.isEmpty() ? zfnull : _callerFunc.cString();}
        /** @brief see #ZF_CALLER_LINE */
        inline zfindex callerLine(void) const {return _callerLine;}

        /** @brief return caller info looks like "[File function (line)]" */
        inline zfbool callerInfoAT(ZF_IN_OUT zfstringA &ret) const
        {
            if(this->callerFile() != zfnull)
            {
                zfstring t;
                _callerInfo(t);
                ret += zfsCoreZ2A(t);
                return zftrue;
            }
            else
            {
                return zffalse;
            }
        }
#endif
};

/**
 * @brief util macro to make #ZFCallerInfo
 */
#define ZFCallerInfoMake() \
    ZFCallerInfo(ZF_CALLER_FILE, ZF_CALLER_FUNCTION, ZF_CALLER_LINE)

extern ZF_ENV_EXPORT const ZFCallerInfo &_ZFP_ZFCallerInfoEmpty(void);
/**
 * @brief empty caller info
 */
#define ZFCallerInfoEmpty() _ZFP_ZFCallerInfoEmpty()

// ============================================================
// ZFCallerInfoHolder
/**
 * @brief util class to hold caller info
 */
zfclassLikePOD ZF_ENV_EXPORT ZFCallerInfoHolder : zfextendsLikePOD ZFCallerInfo
{
    /** @cond ZFPrivateDoc */
#if ZFCHAR_TYPE_SAME_AS_CHAR_A
    private:
        zfstring _callerFileHolder;
        zfstring _callerFuncHolder;
    public:
        ZFCallerInfoHolder(ZF_IN_OPT const zfcharA *callerFile = zfnull,
                           ZF_IN_OPT const zfcharA *callerFunc = zfnull,
                           ZF_IN_OPT zfindex callerLine = 0)
        : ZFCallerInfo()
        , _callerFileHolder()
        , _callerFuncHolder(zfsCoreA2Z(callerFunc))
        {
            ZF_CALLER_FILE_TO_NAME_REF(_callerFileHolder, zfsCoreA2Z(callerFile));
            ZFCallerInfo::callerInfoSet(_callerFileHolder, _callerFuncHolder, callerLine);
        }
        ZFCallerInfoHolder(ZF_IN const ZFCallerInfo &ref)
        : ZFCallerInfo()
        , _callerFileHolder()
        , _callerFuncHolder(ref.callerFunc())
        {
            ZF_CALLER_FILE_TO_NAME_REF(_callerFileHolder, zfsCoreA2Z(ref.callerFile()));
            ZFCallerInfo::callerInfoSet(_callerFileHolder, _callerFuncHolder, ref.callerLine());
        }
        virtual ZFCallerInfoHolder &operator =(ZF_IN const ZFCallerInfo &ref)
        {
            _callerFileHolder.removeAll();
            ZF_CALLER_FILE_TO_NAME_REF(_callerFileHolder, zfsCoreA2Z(ref.callerFile()));
            _callerFuncHolder = ref.callerFunc();
            ZFCallerInfo::callerInfoSet(_callerFileHolder, _callerFuncHolder, ref.callerLine());
            return *this;
        }
    public:
        virtual void callerInfoSet(ZF_IN_OPT const zfcharA *callerFile = zfnull,
                                   ZF_IN_OPT const zfcharA *callerFunc = zfnull,
                                   ZF_IN_OPT zfindex callerLine = 0)
        {
            _callerFileHolder = callerFile;
            _callerFuncHolder = callerFunc;
            ZFCallerInfo::callerInfoSet(_callerFileHolder, _callerFuncHolder, callerLine);
        }
#else
    public:
        ZFCallerInfoHolder(ZF_IN_OPT const zfcharA *callerFile = zfnull,
                           ZF_IN_OPT const zfcharA *callerFunc = zfnull,
                           ZF_IN_OPT zfindex callerLine = 0)
        : ZFCallerInfo(callerFile, callerFunc, callerLine)
        {
        }
        ZFCallerInfoHolder(ZF_IN const ZFCallerInfo &ref)
        : ZFCallerInfo(ref)
        {
        }
        virtual ZFCallerInfoHolder &operator =(ZF_IN const ZFCallerInfo &ref)
        {
            ZFCallerInfo::operator = (ref);
            return *this;
        }
#endif
    /** @endcond */
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFCoreUtilCallerInfo_h_

