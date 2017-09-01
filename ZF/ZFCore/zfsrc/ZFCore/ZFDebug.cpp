/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFDebug.h"
#include "ZFString.h"
#include "protocol/ZFProtocolZFOutput.h"
#include <stdio.h>

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
static zfindex _ZFP_ZFDebugWrappedZFCoreLog(ZF_IN const zfcharA *s)
{
    if(ZFPROTOCOL_TRY_ACCESS(ZFOutput) != zfnull)
    {
        return ZFPROTOCOL_ACCESS(ZFOutput)->outputCoreLog(s);
    }
    else
    {
        // try to print to std output
        fprintf(stderr, zfTextA("%s"), s);
    }
    return zfindexMax();
}
ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(ZFDebugDataHolder, ZFLevelZFFrameworkEssential)
{
    zfCoreLogOutputCallbackSet(_ZFP_ZFDebugWrappedZFCoreLog);
}
ZF_GLOBAL_INITIALIZER_DESTROY(ZFDebugDataHolder)
{
}
public:
    ZFDebugSession globalSession;
    ZFDebugSession globalNullSession;
ZF_GLOBAL_INITIALIZER_END(ZFDebugDataHolder)
#define _ZFP_ZFDebugGlobalSession (ZF_GLOBAL_INITIALIZER_INSTANCE(ZFDebugDataHolder)->globalSession)
#define _ZFP_ZFDebugGlobalNullSession (ZF_GLOBAL_INITIALIZER_INSTANCE(ZFDebugDataHolder)->globalNullSession)

// ============================================================
ZFDebugCallback _ZFP_zfDebugTNull(void)
{
    return zfDebugSessionT(_ZFP_ZFDebugGlobalNullSession);
}

// ============================================================
zfclassNotPOD _ZFP_ZFDebugSessionPrivate
{
public:
    zfindex refCount;
    zfint enableFlagCount; // enable if greater than 0
    ZFCoreArray<ZFOutputCallback> callbacks;
    ZFDebugLevelEnum debugLevel;
    zfbool autoSpace;
    zfbool autoEndl;
public:
    _ZFP_ZFDebugSessionPrivate(void)
    : refCount(1)
    , enableFlagCount(0)
    , callbacks()
    , debugLevel(ZFDebugLevel::EnumDefault())
    , autoSpace(zftrue)
    , autoEndl(zftrue)
    {
    }
};
ZFDebugSession::ZFDebugSession(void)
{
    _ZFP_ZFDebugSession_d = zfpoolNew(_ZFP_ZFDebugSessionPrivate);
}
ZFDebugSession::ZFDebugSession(ZF_IN const ZFDebugSession &ref)
{
    _ZFP_ZFDebugSession_d = ref._ZFP_ZFDebugSession_d;
    ++(_ZFP_ZFDebugSession_d->refCount);
}
ZFDebugSession &ZFDebugSession::operator =(ZF_IN const ZFDebugSession &ref)
{
    ++(ref._ZFP_ZFDebugSession_d->refCount);

    --(_ZFP_ZFDebugSession_d->refCount);
    if(_ZFP_ZFDebugSession_d->refCount == 0)
    {
        zfpoolDelete(_ZFP_ZFDebugSession_d);
    }

    _ZFP_ZFDebugSession_d = ref._ZFP_ZFDebugSession_d;
    return *this;
}
ZFDebugSession::~ZFDebugSession(void)
{
    --(_ZFP_ZFDebugSession_d->refCount);
    if(_ZFP_ZFDebugSession_d->refCount == 0)
    {
        zfpoolDelete(_ZFP_ZFDebugSession_d);
    }
    _ZFP_ZFDebugSession_d = zfnull;
}

void ZFDebugSession::debugLevelSet(ZF_IN ZFDebugLevelEnum debugLevel)
{
    _ZFP_ZFDebugSession_d->debugLevel = debugLevel;
}
ZFDebugLevelEnum ZFDebugSession::debugLevel(void) const
{
    return _ZFP_ZFDebugSession_d->debugLevel;
}
void ZFDebugSession::autoSpaceSet(ZF_IN zfbool autoSpace)
{
    _ZFP_ZFDebugSession_d->autoSpace = autoSpace;
}
zfbool ZFDebugSession::autoSpace(void) const
{
    return _ZFP_ZFDebugSession_d->autoSpace;
}
void ZFDebugSession::autoEndlSet(ZF_IN zfbool autoEndl)
{
    _ZFP_ZFDebugSession_d->autoEndl = autoEndl;
}
zfbool ZFDebugSession::autoEndl(void) const
{
    return _ZFP_ZFDebugSession_d->autoEndl;
}

// ============================================================
ZFCALLBACK_DEFINE(ZFDebugCallback, ZFOutputCallback)

// ============================================================
const _ZFP_ZFDebugCallbackConvert ZFDebugConvert = {};
const ZFDebugCallback &operator << (const ZFOutputCallback &d, _ZFP_ZFDebugCallbackConvert const &v)
{
    return *ZFCastStatic(const ZFDebugCallback *, &d);
}

const ZFOutputCallback &operator << (const ZFOutputCallback &d, ZFDebugLevelChange const &v)
{
    ZFCastStatic(const ZFDebugCallback *, &d)->debugLevelSet(v.debugLevel);
    return d;
}

const _ZFP_ZFDebugAutoSpaceOn ZFDebugAutoSpaceOn = {};
const ZFOutputCallback &operator << (const ZFOutputCallback &d, _ZFP_ZFDebugAutoSpaceOn const &v)
{
    ZFCastStatic(const ZFDebugCallback *, &d)->autoSpaceSet(zftrue);
    return d;
}

const _ZFP_ZFDebugAutoSpaceOff ZFDebugAutoSpaceOff = {};
const ZFOutputCallback &operator << (const ZFOutputCallback &d, _ZFP_ZFDebugAutoSpaceOff const &v)
{
    ZFCastStatic(const ZFDebugCallback *, &d)->autoSpaceSet(zffalse);
    return d;
}

const _ZFP_ZFDebugAutoEndlOn ZFDebugAutoEndlOn = {};
const ZFOutputCallback &operator << (const ZFOutputCallback &d, _ZFP_ZFDebugAutoEndlOn const &v)
{
    ZFCastStatic(const ZFDebugCallback *, &d)->autoEndlSet(zftrue);
    return d;
}

const _ZFP_ZFDebugAutoEndlOff ZFDebugAutoEndlOff = {};
const ZFOutputCallback &operator << (const ZFOutputCallback &d, _ZFP_ZFDebugAutoEndlOff const &v)
{
    ZFCastStatic(const ZFDebugCallback *, &d)->autoEndlSet(zffalse);
    return d;
}

// ============================================================
zfclass _ZFP_I_ZFDebugCallbackOwner : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_I_ZFDebugCallbackOwner, ZFObject)

public:
    zfoverride
    virtual ZFObject *objectOnInit(void)
    {
        zfsuper::objectOnInit();
        this->firstTimeOutput = zftrue;
        this->prefix = zfnull;
        this->suffix = zfnull;
        return this;
    }
    zfoverride
    virtual void objectOnDeallocPrepare(void)
    {
        if(ZFDebugLevelIsActive(session._ZFP_ZFDebugSession_d->debugLevel))
        {
            if(this->prefix != zfnull)
            {
                this->doOutput(this->prefix);
                zfsChange(this->prefix, (const zfchar *)zfnull);
            }
            if(session._ZFP_ZFDebugSession_d->enableFlagCount > 0 && session._ZFP_ZFDebugSession_d->autoEndl)
            {
                this->doOutput(zfText("\n"));
            }
            if(this->suffix != zfnull)
            {
                this->doOutput(this->suffix);
            }
        }
        zfsuper::objectOnDeallocPrepare();
    }
    zfoverride
    virtual void objectOnDealloc(void)
    {
        zfsChange(this->prefix, (const zfchar *)zfnull);
        zfsChange(this->suffix, (const zfchar *)zfnull);
        zfsuper::objectOnDealloc();
    }

public:
    void addPrefix(ZF_IN const zfchar *prefix)
    {
        this->prefix = zfsAppend(this->prefix, prefix);
    }
    void addSuffix(ZF_IN const zfchar *suffix)
    {
        this->suffix = zfsAppend(this->suffix, suffix);
    }

public:
    ZFMETHOD_DECLARE_2(zfindex, onOutput,
                       ZFMP_IN(const void *, src),
                       ZFMP_IN(zfindex, count))
    {
        if(session._ZFP_ZFDebugSession_d->enableFlagCount <= 0
            || !ZFDebugLevelIsActive(session._ZFP_ZFDebugSession_d->debugLevel))
        {
            return zfindexMax();
        }
        if(this->firstTimeOutput)
        {
            this->firstTimeOutput = zffalse;
            if(this->prefix != zfnull)
            {
                this->doOutput(this->prefix);
                zfsChange(this->prefix, (const zfchar *)zfnull);
            }
        }
        else if(session._ZFP_ZFDebugSession_d->autoSpace)
        {
            this->doOutput(zfText(" "));
        }

        this->doOutput(src, count);
        return count;
    }
public:
    void doOutput(ZF_IN const void *src, ZF_IN_OPT zfindex count = zfindexMax())
    {
        for(zfindex i = 0; i < session._ZFP_ZFDebugSession_d->callbacks.count(); ++i)
        {
            session._ZFP_ZFDebugSession_d->callbacks[i].execute(src, count);
        }
    }

public:
    ZFDebugSession session;
    zfbool firstTimeOutput;
    zfchar *prefix;
    zfchar *suffix;
};

// ============================================================
const ZFDebugCallback &ZFDebugCallback::debugLevelSet(ZF_IN ZFDebugLevelEnum debugLevel) const
{
    _ZFP_I_ZFDebugCallbackOwner *owner = ZFCastZFObjectUnchecked(_ZFP_I_ZFDebugCallbackOwner *, this->callbackOwnerObject());
    if(owner != zfnull)
    {
        owner->session._ZFP_ZFDebugSession_d->debugLevel = debugLevel;
    }
    return *this;
}
const ZFDebugCallback &ZFDebugCallback::autoSpaceSet(ZF_IN zfbool autoSpace) const
{
    _ZFP_I_ZFDebugCallbackOwner *owner = ZFCastZFObjectUnchecked(_ZFP_I_ZFDebugCallbackOwner *, this->callbackOwnerObject());
    if(owner != zfnull)
    {
        owner->session._ZFP_ZFDebugSession_d->autoSpace = autoSpace;
    }
    return *this;
}
const ZFDebugCallback &ZFDebugCallback::autoEndlSet(ZF_IN zfbool autoEndl) const
{
    _ZFP_I_ZFDebugCallbackOwner *owner = ZFCastZFObjectUnchecked(_ZFP_I_ZFDebugCallbackOwner *, this->callbackOwnerObject());
    if(owner != zfnull)
    {
        owner->session._ZFP_ZFDebugSession_d->autoEndl = autoEndl;
    }
    return *this;
}
const ZFDebugCallback &ZFDebugCallback::addPrefix(ZF_IN const zfchar *prefix) const
{
    _ZFP_I_ZFDebugCallbackOwner *owner = ZFCastZFObjectUnchecked(_ZFP_I_ZFDebugCallbackOwner *, this->callbackOwnerObject());
    if(owner != zfnull)
    {
        owner->addPrefix(prefix);
    }
    return *this;
}
const ZFDebugCallback &ZFDebugCallback::addSuffix(ZF_IN const zfchar *suffix) const
{
    _ZFP_I_ZFDebugCallbackOwner *owner = ZFCastZFObjectUnchecked(_ZFP_I_ZFDebugCallbackOwner *, this->callbackOwnerObject());
    if(owner != zfnull)
    {
        owner->addSuffix(suffix);
    }
    return *this;
}
const ZFDebugCallback &ZFDebugCallback::append(ZF_IN const zfchar *format,
                                               ...) const
{
    va_list vaList;
    va_start(vaList, format);
    this->appendV(format, vaList);
    va_end(vaList);
    return *this;
}
const ZFDebugCallback &ZFDebugCallback::appendV(ZF_IN const zfchar *format,
                                                ZF_IN va_list vaList) const
{
    zfstring tmp(zfslen(format));
    zfstringAppendV(tmp, format, vaList);
    this->execute(tmp.cString(), tmp.length());
    return *this;
}

// ============================================================
ZFDebugCallback _ZFP_ZFDebugCallbackCreate(ZF_IN_OUT ZFDebugSession &session)
{
    _ZFP_I_ZFDebugCallbackOwner *owner = zfAllocWithoutLeakTest(_ZFP_I_ZFDebugCallbackOwner);
    owner->session = session;
    ZFDebugCallback callback = ZFCallbackForMemberMethod(owner, ZFMethodAccess(_ZFP_I_ZFDebugCallbackOwner, onOutput));
    callback.callbackOwnerObjectRetain();
    zfReleaseWithoutLeakTest(owner);
    return callback;
}

// ============================================================
zfbool zfDebugStart(ZF_IN_OPT const ZFOutputCallback &callback /* = ZFOutputCallbackDefault() */)
{
    return zfDebugSessionStart(_ZFP_ZFDebugGlobalSession, callback);
}
ZFCoreArray<ZFOutputCallback> &zfDebugOutputCallback(void)
{
    return zfDebugSessionOutputCallback(_ZFP_ZFDebugGlobalSession);
}
void zfDebugEnableSet(ZF_IN zfbool isEnabled)
{
    zfDebugSessionEnableSet(_ZFP_ZFDebugGlobalSession, isEnabled);
}
zfbool zfDebugEnabled(void)
{
    return zfDebugSessionEnabled(_ZFP_ZFDebugGlobalSession);
}
void zfDebugStop(void)
{
    zfDebugSessionStop(_ZFP_ZFDebugGlobalSession);
}
ZFDebugCallback zfDebugT(void)
{
    return zfDebugSessionT(_ZFP_ZFDebugGlobalSession);
}
void zfDebug(ZF_IN const zfchar *format,
             ...)
{
    if(_ZFP_ZFDebugGlobalSession._ZFP_ZFDebugSession_d->enableFlagCount <= 0) {return ;}

    va_list vaList;
    va_start(vaList, format);
    (zfDebugSessionT(_ZFP_ZFDebugGlobalSession) << ZFDebugConvert).appendV(format, vaList);
    va_end(vaList);
}

// ============================================================
zfbool zfDebugSessionStart(ZF_IN_OUT ZFDebugSession &session,
                           ZF_IN_OPT const ZFOutputCallback &callback /* = ZFOutputCallbackDefault() */)
{
    zfDebugSessionStop(session);
    if(callback.callbackIsValid())
    {
        session._ZFP_ZFDebugSession_d->callbacks.add(callback);
        session._ZFP_ZFDebugSession_d->enableFlagCount = 1;
    }
    else
    {
        return zffalse;
    }
    return zftrue;
}
ZFCoreArray<ZFOutputCallback> &zfDebugSessionOutputCallback(ZF_IN const ZFDebugSession &session)
{
    return session._ZFP_ZFDebugSession_d->callbacks;
}
void zfDebugSessionEnableSet(ZF_IN_OUT ZFDebugSession &session,
                             ZF_IN zfbool isEnabled)
{
    if(isEnabled)
    {
        ++(session._ZFP_ZFDebugSession_d->enableFlagCount);
    }
    else
    {
        --(session._ZFP_ZFDebugSession_d->enableFlagCount);
    }
}
zfbool zfDebugSessionEnabled(ZF_IN_OUT ZFDebugSession &session)
{
    return (session._ZFP_ZFDebugSession_d->enableFlagCount > 0);
}
void zfDebugSessionStop(ZF_IN_OUT ZFDebugSession &session)
{
    session._ZFP_ZFDebugSession_d->callbacks.removeAll();
    session._ZFP_ZFDebugSession_d->enableFlagCount = 0;
}
ZFDebugCallback zfDebugSessionT(ZF_IN_OUT ZFDebugSession &session)
{
    return _ZFP_ZFDebugCallbackCreate(session);
}
void zfDebugSession(ZF_IN_OUT ZFDebugSession &session,
                    ZF_IN const zfchar *format,
                    ...)
{
    if(session._ZFP_ZFDebugSession_d->enableFlagCount <= 0) {return ;}

    va_list vaList;
    va_start(vaList, format);
    (zfDebugSessionT(session) << ZFDebugConvert).appendV(format, vaList);
    va_end(vaList);
}

ZF_NAMESPACE_GLOBAL_END

