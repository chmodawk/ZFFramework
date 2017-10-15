/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFLua_test.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfclass _ZFP_ZFLua_ZFCallbackForLua_test_Object : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_ZFLua_ZFCallbackForLua_test_Object, ZFObject)

    ZFOBSERVER_EVENT(Test)

public:
    ZFMETHOD_DECLARE_0(void, notifyTest)
    {
        this->observerNotify(zfself::EventTest(), ZFValue::intValueCreate(1111), ZFValue::intValueCreate(2222));
    }

protected:
    zfoverride
    virtual void objectOnInit(void)
    {
        zfLogT() << (void *)this;
        zfsuper::objectOnInit();
    }
    zfoverride
    virtual void objectOnDealloc(void)
    {
        zfLogT() << (void *)this;
        zfsuper::objectOnDealloc();
    }
    zfoverride
    virtual void objectOnRetain(void)
    {
        zfsuper::objectOnRetain();
        zfLogT() << (void *)this << this->objectRetainCount();
    }
    zfoverride
    virtual void objectOnRelease(void)
    {
        zfsuper::objectOnRelease();
        zfLogT() << (void *)this << this->objectRetainCount();
    }
};
ZFOBJECT_REGISTER(_ZFP_ZFLua_ZFCallbackForLua_test_Object)
ZFOBSERVER_EVENT_REGISTER(_ZFP_ZFLua_ZFCallbackForLua_test_Object, Test)

zfclass ZFLua_ZFCallbackForLua_test : zfextends ZFFramework_test_TestCase
{
    ZFOBJECT_DECLARE(ZFLua_ZFCallbackForLua_test, ZFFramework_test_TestCase)

protected:
    zfoverride
    virtual void testCaseOnStart(void)
    {
        zfsuper::testCaseOnStart();

        {
            ZFCoreStatisticInvokeTimeAccurateLoggerOneTime(zfText("run lua code"));
            ZFLuaExecute(zfText(
                    "local obj = zfAlloc('_ZFP_ZFLua_ZFCallbackForLua_test_Object')\n"
                    "local callback = ZFCallbackForLua("
                    "        function(listenerData, userData)"
                    "            print(listenerData)\n"
                    "            print(userData)\n"
                    "        end\n"
                    "    )\n"
                    "obj:observerAdd(_ZFP_ZFLua_ZFCallbackForLua_test_Object.EventTest(), callback)\n"
                    "obj:notifyTest()\n"
                ));
        }

        {
            ZFCoreStatisticInvokeTimeAccurateLoggerOneTime(zfText("lua gc"));
            ZFLuaGC();
        }

        this->testCaseStop();
    }
};
ZFOBJECT_REGISTER(ZFLua_ZFCallbackForLua_test)

ZF_NAMESPACE_GLOBAL_END

