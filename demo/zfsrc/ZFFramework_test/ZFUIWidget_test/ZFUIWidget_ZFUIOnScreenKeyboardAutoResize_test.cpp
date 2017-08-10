/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIWidget_test.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfclass ZFUIWidget_ZFUIOnScreenKeyboardAutoResize_test : zfextends ZFFramework_test_TestCase
{
    ZFOBJECT_DECLARE(ZFUIWidget_ZFUIOnScreenKeyboardAutoResize_test, ZFFramework_test_TestCase)

protected:
    zfoverride
    virtual void testCaseOnStart(void)
    {
        zfsuper::testCaseOnStart();
        ZFFramework_test_protocolCheck(ZFUIView)
        ZFUIWindow *window = zfnull;
        ZFUIView *container = zfnull;
        ZFUIKit_test_prepareTestWindow(window, container, this);

        ZFUIOnScreenKeyboardAutoResizeStart(window);

        container->viewBackgroundColorSet(ZFUIColorGreen);
        for(zfindex i = 0; i < 3; ++i)
        {
            zfblockedAlloc(ZFUITextEdit, view);
            container->childAdd(view);
            view->layoutParam()->sizeParamSet(ZFUISizeParamFillWidthWrapHeight);
            view->viewBackgroundColorSet(ZFUIColorRandom());
            view->layoutParam()->layoutMarginSet(ZFUIMarginMake(10));
        }
        container->childAtIndex(0)->layoutParam()->layoutAlignSet(ZFUIAlign::e_TopInner);
        container->childAtIndex(1)->layoutParam()->layoutAlignSet(ZFUIAlign::e_Center);
        container->childAtIndex(2)->layoutParam()->layoutAlignSet(ZFUIAlign::e_BottomInner);
    }
};
ZFOBJECT_REGISTER(ZFUIWidget_ZFUIOnScreenKeyboardAutoResize_test)

ZF_NAMESPACE_GLOBAL_END

