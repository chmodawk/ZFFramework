/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFUIOnScreenKeyboardState.h
 * @brief on screen keyboard state helper
 */

#ifndef _ZFI_ZFUIOnScreenKeyboardState_h_
#define _ZFI_ZFUIOnScreenKeyboardState_h_

#include "ZFUISysWindow.h"

ZF_NAMESPACE_GLOBAL_BEGIN

/**
 * @brief on screen keyboard state helper
 */
zffinal zfclass ZF_ENV_EXPORT ZFUIOnScreenKeyboardState : zfextends ZFObject
{
    ZFOBJECT_DECLARE_WITH_CUSTOM_CTOR(ZFUIOnScreenKeyboardState, ZFObject)

public:
    /**
     * @brief access keyboard state for sys window
     */
    ZFMETHOD_DECLARE_STATIC_1(ZFUIOnScreenKeyboardState *, instanceForSysWindow,
                              ZFMP_IN_OPT(ZFUISysWindow *, windowSysWindow, zfnull));
    /**
     * @brief access keyboard state for view
     */
    ZFMETHOD_DECLARE_STATIC_1(ZFUIOnScreenKeyboardState *, instanceForView,
                              ZFMP_IN_OPT(ZFUIView *, view, zfnull));

public:
    /**
     * @brief owner sys window, null and invalid if not accessed by #instanceForSysWindow
     *   (which is typically not allowed)
     */
    ZFMETHOD_DECLARE_0(ZFUISysWindow *, windowSysWindow);

public:
    /**
     * @brief see #ZFObject::observerNotify
     *
     * called when keyboard visibility changed or keyboard frame changed
     */
    ZFOBSERVER_EVENT(KeyboardStateOnChange)

public:
    /**
     * @brief true if the keyboard currently showing
     */
    ZFMETHOD_DECLARE_0(zfbool, keyboardShowing);
    /**
     * @brief current key board frame, #ZFUIRectZero if not show
     */
    ZFMETHOD_DECLARE_0(const ZFUIRect &, keyboardFrame);
    /**
     * @brief previous key board frame, #ZFUIRectZero if not show
     */
    ZFMETHOD_DECLARE_0(const ZFUIRect &, keyboardFramePrev);

    /**
     * @brief fix client frame accorrding to current keyboard frame
     *
     * output is the available client frame that won't be covered by the keyboard
     */
    ZFMETHOD_DECLARE_1(void, keyboardFixClientFrameT,
                       ZFMP_OUT(ZFUIRect &, clientFrame));
    /**
     * @brief see #keyboardFixClientFrame
     */
    ZFMETHOD_DECLARE_0(ZFUIRect, keyboardFixClientFrame)
    {
        ZFUIRect ret = ZFUIRectZero();
        this->keyboardFixClientFrameT(ret);
        return ret;
    }

protected:
    zfoverride
    virtual void objectInfoOnAppend(ZF_IN_OUT zfstring &ret);

public:
    ZFUISysWindow *_ZFP_ZFUIOnScreenKeyboardState_windowSysWindow;
    zfbool _ZFP_ZFUIOnScreenKeyboardState_keyboardShowing;
    ZFUIRect _ZFP_ZFUIOnScreenKeyboardState_keyboardFrame;
    ZFUIRect _ZFP_ZFUIOnScreenKeyboardState_keyboardFramePrev;
protected:
    /** @cond ZFPrivateDoc */
    ZFUIOnScreenKeyboardState(void)
    : _ZFP_ZFUIOnScreenKeyboardState_windowSysWindow(zfnull)
    , _ZFP_ZFUIOnScreenKeyboardState_keyboardShowing(zffalse)
    , _ZFP_ZFUIOnScreenKeyboardState_keyboardFrame(ZFUIRectZero())
    , _ZFP_ZFUIOnScreenKeyboardState_keyboardFramePrev(ZFUIRectZero())
    {
    }
    /** @endcond */
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIOnScreenKeyboardState_h_

