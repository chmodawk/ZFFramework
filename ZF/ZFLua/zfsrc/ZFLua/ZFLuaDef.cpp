/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFLuaDef.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
ZFCoreArray<ZFOutputCallback> &_ZFP_ZFLuaErrorCallbacks(void)
{
    static ZFCoreArray<ZFOutputCallback> d;
    return d;
}
void _ZFP_ZFLuaErrorOccurred(ZF_IN const ZFCallerInfo &callerInfo,
                             ZF_IN const zfchar *fmt,
                             ...)
{
    if(!ZFLuaErrorCallbacks.isEmpty())
    {
        zfstring s;
        if(callerInfo.callerInfoT(s))
        {
            s += zfText(" ");
        }
        va_list vaList;
        va_start(vaList, fmt);
        zfstringAppendV(s, fmt, vaList);
        va_end(vaList);
        s += zfText("\n");
        const ZFCoreArray<ZFOutputCallback> &t = ZFLuaErrorCallbacks;
        for(zfindex i = 0; i < t.count(); ++i)
        {
            t[i].execute(s.cString(), s.length());
        }
    }
}

ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFImpl_ZFLua_debug_autoOutputError, ZFLevelZFFrameworkNormal)
{
    this->debugCallback = ZFOutputCallbackDefault();
    ZFLuaErrorCallbacks.add(this->debugCallback);
}
ZF_GLOBAL_INITIALIZER_DESTROY(ZFImpl_ZFLua_debug_autoOutputError)
{
    ZFLuaErrorCallbacks.removeElement(this->debugCallback);
}
ZFOutputCallback debugCallback;
ZF_GLOBAL_INITIALIZER_END(ZFImpl_ZFLua_debug_autoOutputError)

ZF_NAMESPACE_GLOBAL_END

