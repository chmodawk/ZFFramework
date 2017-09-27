/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFLua_test.h"
#include "ZFUIKit.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfclass ZFLua_UI_test : zfextends ZFFramework_test_TestCase
{
    ZFOBJECT_DECLARE(ZFLua_UI_test, ZFFramework_test_TestCase)

protected:
    zfoverride
    virtual void testCaseOnStart(void)
    {
        zfsuper::testCaseOnStart();

        zfautoObject result;
        ZFLuaExecute(zfText(
                "local window = ZFUIWindow()\n"
                "window:windowShow()\n"
                "window:viewBackgroundColorSet(ZFUIColorRandom())\n"
                "local button = ZFUIButtonBasic()\n"
                "window:childAdd(button)\n"
                "button:layoutParam():layoutAlignSet(ZFUIAlign.e_TopInner() | ZFUIAlign.e_RightInner())\n"
                "button:viewBackgroundColorSet(ZFUIColorRandom())\n"
                "button:buttonLabelTextSet('close')\n"
                "button:observerAdd(ZFUIButton.EventButtonOnClick(), ZFCallbackForLua(function (listenerData, userData)\n"
                "        userData:holdedObj():windowHide()\n"
                "    end), window:objectHolder())\n"
                "return window\n"
            ), zfindexMax(), zftrue, &result);
        zfCoreAssert(ZFCastZFObject(ZFUIWindow *, result) != zfnull);

        ZFLISTENER_LOCAL(windowOnHide, {
            ZFLISTENER_LOCAL(testCaseStopDelay, {
                ZFLuaGC();
                ZFTestCase *testCase = userData->to<ZFObjectHolder *>()->holdedObj;
                testCase->testCaseStop();
            })
            ZFThreadTaskRequest(testCaseStopDelay, userData);
        })
        result->observerAdd(ZFUIWindow::EventWindowOnHide(), windowOnHide, this->objectHolder());
    }
};
ZFOBJECT_REGISTER(ZFLua_UI_test)

ZF_NAMESPACE_GLOBAL_END

