/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFLang.h"
#include "ZFCore/ZFSTLWrapper/zfstl_string.h"
#include "ZFCore/ZFSTLWrapper/zfstl_hashmap.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFOBSERVER_EVENT_GLOBAL_REGISTER(ZFGlobalEvent, LangOnChange)

// ============================================================
typedef zfstlhashmap<zfstlstringZ, zfstring> _ZFP_ZFLangMapType;

// ============================================================
static _ZFP_ZFLangMapType &_ZFP_ZFLangMapGlobal(void)
{
    static _ZFP_ZFLangMapType d;
    return d;
}
ZFMETHOD_FUNC_DEFINE_3(void, zfLang,
                       ZFMP_IN_OUT(zfstring &, ret),
                       ZFMP_IN(const zfchar *, key),
                       ZFMP_IN_OPT(const zfchar *, valueDefault, zfnull))
{
    zfCoreMutexLocker();
    _ZFP_ZFLangMapType &m = _ZFP_ZFLangMapGlobal();
    _ZFP_ZFLangMapType::iterator it = m.find(key);
    if(it != m.end())
    {
        ret += it->second;
    }
    else
    {
        if(valueDefault != zfnull)
        {
            ret += valueDefault;
        }
        else
        {
            ret += key;
        }
    }
}
ZFMETHOD_FUNC_DEFINE_INLINE_2(zfstring, zfLang,
                              ZFMP_IN(const zfchar *, key),
                              ZFMP_IN_OPT(const zfchar *, valueDefault, zfnull))

ZFMETHOD_FUNC_DEFINE_0(void, zfLangNotifyChanged)
{
    ZFGlobalEventCenter::instance()->observerNotify(ZFGlobalEvent::EventLangOnChange());
}

ZFMETHOD_FUNC_DEFINE_2(void, zfLangSet,
                       ZFMP_IN(const zfchar *, key),
                       ZFMP_IN(const zfchar *, value))
{
    if(key != zfnull)
    {
        zfCoreMutexLocker();
        if(value == zfnull)
        {
            _ZFP_ZFLangMapGlobal().erase(key);
        }
        else
        {
            _ZFP_ZFLangMapGlobal()[key] = value;
        }
    }
}
ZFMETHOD_FUNC_DEFINE_2(void, zfLangSetDefault,
                       ZFMP_IN(const zfchar *, key),
                       ZFMP_IN(const zfchar *, value))
{
    if(key && value)
    {
        zfCoreMutexLocker();
        _ZFP_ZFLangMapType &m = _ZFP_ZFLangMapGlobal();
        _ZFP_ZFLangMapType::iterator it = m.find(key);
        if(it == m.end())
        {
            m[key] = value;
        }
    }
}

ZFMETHOD_FUNC_DEFINE_0(void, zfLangUnload)
{
    zfCoreMutexLocker();
    _ZFP_ZFLangMapGlobal().clear();

    zfLangNotifyChanged();
}

ZFMETHOD_FUNC_DEFINE_1(void, zfLangDebug,
                       ZFMP_IN_OPT(const ZFOutputCallback &, output, ZFOutputCallbackDefault()))
{
    _ZFP_ZFLangMapType &m = _ZFP_ZFLangMapGlobal();
    for(_ZFP_ZFLangMapType::iterator it = m.begin(); it != m.end(); ++it)
    {
        output << it->first.c_str() << zfText(" = \"") << it->second << zfText("\"\n");
    }
}

ZF_NAMESPACE_GLOBAL_END

