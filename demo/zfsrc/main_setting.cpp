/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFCore.h"
#include "ZFUIKit.h"

ZF_NAMESPACE_GLOBAL_BEGIN

#if ZF_ENV_DEBUG // global debug level
    ZF_GLOBAL_INITIALIZER_INIT_WITH_LEVEL(main_setting_debugLevel, ZFLevelAppEssential)
    {
        ZFDebugLevelSet(ZFDebugLevel::e_Verbose);
    }
    ZF_GLOBAL_INITIALIZER_END(main_setting_debugLevel)
#endif

#if ZF_ENV_DEBUG // auto print view tree when app paused
    ZF_GLOBAL_INITIALIZER_INIT(main_setting_autoPrintViewTree)
    {
        if(!ZFProtocolIsAvailable(zfText("ZFUIView")))
        {
            return ;
        }
        ZFLISTENER_LOCAL(windowOnPause, {
            ZFUISysWindow *sysWindow = listenerData.sender->to<ZFUISysWindow *>();
            ZFUIViewTreePrint(sysWindow->rootView());
        })
        this->windowOnPauseListener = windowOnPause;
        ZFObjectGlobalEventObserver.observerAdd(
            ZFUISysWindow::EventSysWindowOnPause(), this->windowOnPauseListener);
    }
    ZF_GLOBAL_INITIALIZER_DESTROY(main_setting_autoPrintViewTree)
    {
        ZFObjectGlobalEventObserver.observerRemove(
            ZFUISysWindow::EventSysWindowOnPause(), this->windowOnPauseListener);
    }
    private:
        ZFListener windowOnPauseListener;
    ZF_GLOBAL_INITIALIZER_END(main_setting_autoPrintViewTree)
#endif

ZF_NAMESPACE_GLOBAL_END

