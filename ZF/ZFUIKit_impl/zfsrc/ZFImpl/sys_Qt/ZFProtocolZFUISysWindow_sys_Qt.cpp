/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFImpl_sys_Qt_ZFUIKit.h"
#include "ZFUIKit/protocol/ZFProtocolZFUISysWindow.h"
#include "ZFImpl/sys_Qt/ZFMainEntry_sys_Qt.h"

#if ZF_ENV_sys_Qt

#include <QWidget>
#include <QLayout>
#include <QEvent>
#include <QApplication>
#include <QDesktopWidget>

static void _ZFP_ZFUISysWindowImpl_sys_Qt_updateWindowLayout(ZF_IN ZFUISysWindow *sysWindow, ZF_IN QWidget *nativeWindow)
{
    QRect screenRect = QApplication::desktop()->screenGeometry();
    ZFUIRect frame = ZFPROTOCOL_ACCESS(ZFUISysWindow)->notifyMeasureWindow(
            sysWindow,
            ZFUIRectMake(0, 0, screenRect.width(), screenRect.height()),
            ZFUIMarginZero()
        );
    nativeWindow->setGeometry(ZFImpl_sys_Qt_ZFUIKit_ZFUIRectToQRect(frame));
    if(nativeWindow->layout() != zfnull)
    {
        QRect t(0, 0, frame.size.width, frame.size.height);
        for(int i = 0; i < nativeWindow->layout()->count(); ++i)
        {
            nativeWindow->layout()->itemAt(i)->widget()->setGeometry(t);
        }
    }
}
class _ZFP_ZFUISysWindowImpl_sys_Qt_EventWrapper : public QObject
{
    Q_OBJECT

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event)
    {
        ZFUISysWindow *owner = ZFImpl_sys_Qt_QObjectTagGetZFObject<ZFObjectHolder *>(obj, zfText("_ZFP_ZFUISysWindowImpl_sys_Qt_ownerZFUISysWindow"))->holdedObj;
        if(owner == zfnull)
        {
            return QObject::eventFilter(obj, event);
        }
        switch(event->type())
        {
            case QEvent::WindowActivate:
                ZFPROTOCOL_ACCESS(ZFUISysWindow)->notifyOnResume(owner);
                break;
            case QEvent::WindowDeactivate:
                ZFPROTOCOL_ACCESS(ZFUISysWindow)->notifyOnPause(owner);
                #if ZF_ENV_DEBUG && 0
                    zfLogTrimT() << ZFImpl_sys_Qt_ZFUIKit_QWidgetGetViewTree(ZFImpl_sys_Qt_rootWindow());
                #endif
                break;
            default:
                break;
        }
        return QObject::eventFilter(obj, event);
    }
};

ZF_NAMESPACE_GLOBAL_BEGIN

ZFPROTOCOL_IMPLEMENTATION_BEGIN(ZFUISysWindowImpl_sys_Qt, ZFUISysWindow, ZFProtocolLevel::e_SystemHigh)
    ZFPROTOCOL_IMPLEMENTATION_PLATFORM_HINT(zfText("Qt:QWidget"))
    ZFPROTOCOL_IMPLEMENTATION_PLATFORM_DEPENDENCY_BEGIN()
    ZFPROTOCOL_IMPLEMENTATION_PLATFORM_DEPENDENCY_ITEM(ZFUIView, zfText("Qt:QWidget"))
    ZFPROTOCOL_IMPLEMENTATION_PLATFORM_DEPENDENCY_END()

public:
    zfoverride
    virtual void protocolOnInit(void)
    {
        zfsuper::protocolOnInit();
        this->_mainWindow = zfnull;
    }
    zfoverride
    virtual void protocolOnDeallocPrepare(void)
    {
        this->mainWindowOnCleanup();
        zfsuper::protocolOnDeallocPrepare();
    }
public:
    virtual ZFUISysWindow *mainWindow(void)
    {
        if(this->_mainWindow == zfnull)
        {
            this->_mainWindow = zfRetain(ZFUISysWindow::ClassData()->newInstance(ZFCallerInfoMake()).to<ZFUISysWindow *>());
            ZFImpl_sys_Qt_Window *nativeWindow = ZFImpl_sys_Qt_rootWindow();
            ZFImpl_sys_Qt_QObjectTagSetZFObject(nativeWindow, zfText("_ZFP_ZFUISysWindowImpl_sys_Qt_ownerZFUISysWindow"), this->_mainWindow->objectHolder());
            nativeWindow->installEventFilter(&_eventWrapper);

            this->notifyOnCreate(this->_mainWindow, nativeWindow);

            _ZFP_ZFUISysWindowImpl_sys_Qt_updateWindowLayout(this->_mainWindow, nativeWindow);
            nativeWindow->show();
        }
        return this->_mainWindow;
    }
    virtual void mainWindowOnCleanup(void)
    {
        if(this->_mainWindow != zfnull)
        {
            if(this->_mainWindow->nativeWindowIsResumed())
            {
                this->notifyOnPause(this->_mainWindow);
            }
            zfblockedRelease(this->_mainWindow);
            QWidget *nativeWindow = ZFImpl_sys_Qt_rootWindow();
            nativeWindow->removeEventFilter(&_eventWrapper);
            ZFImpl_sys_Qt_QObjectTagSetZFObject(nativeWindow, zfText("_ZFP_ZFUISysWindowImpl_sys_Qt_ownerZFUISysWindow"), zfnull);

            this->notifyOnDestroy(this->_mainWindow);
        }
    }
    virtual void mainWindowOnDestroy(void)
    {
        this->_mainWindow = zfnull;
    }

    // ============================================================
public:
    virtual void nativeWindowOnCleanup(ZF_IN ZFUISysWindow *sysWindow)
    {
    }

    virtual void nativeWindowRootViewOnAdd(ZF_IN ZFUISysWindow *sysWindow,
                                           ZF_OUT void *&nativeParentView)
    {
        ZFImpl_sys_Qt_Window *nativeWindow = ZFCastStatic(ZFImpl_sys_Qt_Window *, sysWindow->nativeWindow());

        QWidget *nativeRootView = ZFCastStatic(QWidget *, sysWindow->rootView()->nativeView());
        nativeWindow->layout()->addWidget(nativeRootView);
        nativeParentView = (void *)nativeWindow;
    }
    virtual void nativeWindowRootViewOnRemove(ZF_IN ZFUISysWindow *sysWindow)
    {
        ZFImpl_sys_Qt_Window *nativeWindow = ZFCastStatic(ZFImpl_sys_Qt_Window *, sysWindow->nativeWindow());
        QWidget *nativeRootView = ZFCastStatic(QWidget *, sysWindow->rootView()->nativeView());
        nativeWindow->layout()->removeWidget(nativeRootView);
    }

    virtual ZFUISysWindow *modalWindowShow(ZF_IN ZFUISysWindow *sysWindowOwner)
    {
        ZFUISysWindow *modalWindow = zfRetain(ZFUISysWindow::ClassData()->newInstance(ZFCallerInfoMake()).to<ZFUISysWindow *>());
        ZFImpl_sys_Qt_Window *nativeModalWindow = new ZFImpl_sys_Qt_Window();
        ZFImpl_sys_Qt_QObjectTagSetZFObject(nativeModalWindow, zfText("_ZFP_ZFUISysWindowImpl_sys_Qt_ownerZFUISysWindow"), modalWindow->objectHolder());
        nativeModalWindow->installEventFilter(&_eventWrapper);
        this->notifyOnCreate(modalWindow, nativeModalWindow);

        _ZFP_ZFUISysWindowImpl_sys_Qt_updateWindowLayout(modalWindow, nativeModalWindow);
        nativeModalWindow->show();

        return modalWindow;
    }
    virtual void modalWindowFinish(ZF_IN ZFUISysWindow *sysWindowOwner,
                                   ZF_IN ZFUISysWindow *sysWindowToFinish)
    {
        this->notifyOnDestroy(sysWindowToFinish);
        QWidget *nativeModalWindow = ZFCastStatic(QWidget *, sysWindowOwner->nativeWindow());
        nativeModalWindow->hide();
        nativeModalWindow->removeEventFilter(&_eventWrapper);
        ZFImpl_sys_Qt_QObjectTagSetZFObject(nativeModalWindow, zfText("_ZFP_ZFUISysWindowImpl_sys_Qt_ownerZFUISysWindow"), zfnull);
        delete nativeModalWindow;
    }

    virtual void windowLayoutParamOnInit(ZF_IN ZFUISysWindow *sysWindow)
    {
        // centered by default
        sysWindow->windowLayoutParam()->layoutAlignSet(ZFUIAlign::e_Center);
        sysWindow->windowLayoutParam()->sizeHintSet(ZFUISizeMake(480, 640));
    }
    virtual void windowLayoutParamOnChange(ZF_IN ZFUISysWindow *sysWindow)
    {
        _ZFP_ZFUISysWindowImpl_sys_Qt_updateWindowLayout(sysWindow, (ZFImpl_sys_Qt_Window *)sysWindow->nativeWindow());
    }

    virtual ZFUIOrientationEnum windowOrientation(ZF_IN ZFUISysWindow *sysWindow)
    {
        // Qt don't support rotate
        return ZFUIOrientation::e_Top;
    }
    virtual void windowOrientationFlagsSet(ZF_IN ZFUISysWindow *sysWindow,
                                           ZF_IN const ZFUIOrientationFlags &flags)
    {
        // Qt don't support rotate
    }

private:
    ZFUISysWindow *_mainWindow;
    _ZFP_ZFUISysWindowImpl_sys_Qt_EventWrapper _eventWrapper;
ZFPROTOCOL_IMPLEMENTATION_END(ZFUISysWindowImpl_sys_Qt)
ZFPROTOCOL_IMPLEMENTATION_REGISTER(ZFUISysWindowImpl_sys_Qt)

ZF_NAMESPACE_GLOBAL_END

#include "ZFProtocolZFUISysWindow_sys_Qt.moc"

#endif // #if ZF_ENV_sys_Qt

