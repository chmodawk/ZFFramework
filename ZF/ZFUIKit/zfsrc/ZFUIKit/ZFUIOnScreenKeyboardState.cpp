/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIOnScreenKeyboardState.h"
#include "protocol/ZFProtocolZFUIOnScreenKeyboardState.h"
#include "ZFUIWindow.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFOBJECT_REGISTER(ZFUIOnScreenKeyboardState)

ZFOBSERVER_EVENT_REGISTER(ZFUIOnScreenKeyboardState, KeyboardStateOnChange)

ZFMETHOD_DEFINE_1(ZFUIOnScreenKeyboardState, ZFUIOnScreenKeyboardState *, instanceForSysWindow,
                  ZFMP_IN_OPT(ZFUISysWindow *, windowSysWindow, zfnull))
{
    if(windowSysWindow == zfnull)
    {
        windowSysWindow = ZFUISysWindow::mainWindow();
    }
    ZFUIOnScreenKeyboardState *ret = windowSysWindow->tagGet<ZFUIOnScreenKeyboardState *>(zfText("_ZFP_ZFUIOnScreenKeyboardState"));
    if(ret == zfnull)
    {
        zfblockedAllocWithoutLeakTest(ZFUIOnScreenKeyboardState, tmp);
        windowSysWindow->tagSetMarkCached(zfText("_ZFP_ZFUIOnScreenKeyboardState"), tmp);
        tmp->_ZFP_ZFUIOnScreenKeyboardState_windowSysWindow = windowSysWindow;
        ret = tmp;
    }
    return ret;
}
ZFMETHOD_DEFINE_1(ZFUIOnScreenKeyboardState, ZFUIOnScreenKeyboardState *, instanceForView,
                  ZFMP_IN_OPT(ZFUIView *, view, zfnull))
{
    return ZFUIOnScreenKeyboardState::instanceForSysWindow(ZFUIWindow::sysWindowForView(view));
}

ZFMETHOD_DEFINE_0(ZFUIOnScreenKeyboardState, ZFUISysWindow *, windowSysWindow)
{
    return _ZFP_ZFUIOnScreenKeyboardState_windowSysWindow;
}

ZFMETHOD_DEFINE_0(ZFUIOnScreenKeyboardState, zfbool, keyboardShowing)
{
    return this->_ZFP_ZFUIOnScreenKeyboardState_keyboardShowing;
}
ZFMETHOD_DEFINE_0(ZFUIOnScreenKeyboardState, const ZFUIRect &, keyboardFrame)
{
    return this->_ZFP_ZFUIOnScreenKeyboardState_keyboardFrame;
}
ZFMETHOD_DEFINE_0(ZFUIOnScreenKeyboardState, const ZFUIRect &, keyboardFramePrev)
{
    return this->_ZFP_ZFUIOnScreenKeyboardState_keyboardFramePrev;
}

ZFMETHOD_DEFINE_1(ZFUIOnScreenKeyboardState, void, keyboardFixClientFrameT,
                  ZFMP_OUT(ZFUIRect &, clientFrame))
{
    zffloat scale = this->windowSysWindow()->rootView()->scaleFixed();
    ZFPROTOCOL_ACCESS(ZFUIOnScreenKeyboardState)->keyboardFixClientFrame(
        this,
        ZFUIRectApplyScale(this->keyboardFrame(), scale),
        clientFrame);
    ZFUIRectApplyScaleReversely(clientFrame, clientFrame, scale);
}

void ZFUIOnScreenKeyboardState::objectInfoOnAppend(ZF_IN_OUT zfstring &ret)
{
    zfsFromPointerT(ret, this->windowSysWindow());
    if(this->keyboardShowing())
    {
        ret += zfText(" keyboardFrame: ");
        ZFUIRectToString(ret, this->keyboardFrame());
    }
    else
    {
        ret += zfText(" keyboardNotShow");
    }
}

ZF_NAMESPACE_GLOBAL_END

