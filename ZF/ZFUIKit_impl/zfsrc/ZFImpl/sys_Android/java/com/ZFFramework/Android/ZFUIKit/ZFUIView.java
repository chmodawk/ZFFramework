/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
package com.ZFFramework.Android.ZFUIKit;

import java.util.ArrayList;
import java.util.List;
import com.ZFFramework.Android.NativeUtil.ZFAndroidRect;
import com.ZFFramework.Android.NativeUtil.ZFAndroidSize;
import com.ZFFramework.Android.NativeUtil.ZFAndroidUI;
import com.ZFFramework.Android.ZF.ZFEnum;
import com.ZFFramework.Android.ZF.ZFMainEntry;
import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Rect;
import android.util.AttributeSet;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;

public class ZFUIView extends ViewGroup {
    public static boolean requestLayoutOverride = false;

    // ============================================================
    public long zfjniPointerOwnerZFUIView = 0;
    public View nativeImplView = null;
    public boolean viewUIEnable = true;
    public boolean viewUIEnableTree = true;
    public int viewFrame_x = 0;
    public int viewFrame_y = 0;
    public int viewFrame_width = 0;
    public int viewFrame_height = 0;

    // ============================================================
    private Rect _rectNativeCache = new Rect();
    private ZFAndroidRect _rectCache = new ZFAndroidRect();

    // ============================================================
    public static Object native_nativeViewCreate(long zfjniPointerOwnerZFUIView) {
        ZFUIView ret = new ZFUIView(ZFMainEntry.appContext());
        ret.zfjniPointerOwnerZFUIView = zfjniPointerOwnerZFUIView;
        return ret;
    }
    public static void native_nativeImplViewSet(Object nativeView,
                                                Object nativeImplView,
                                                int virtualIndex) {
        ZFUIView nativeViewTmp = (ZFUIView)nativeView;
        View nativeImplViewOld = nativeViewTmp.nativeImplView;
        View nativeImplViewNew = (View)nativeImplView;
        if(nativeViewTmp.nativeImplView != null) {
            nativeViewTmp.removeView(nativeViewTmp.nativeImplView);
        }
        nativeViewTmp.nativeImplView = nativeImplViewNew;
        if(nativeViewTmp.nativeImplView != null) {
            nativeViewTmp.addView(nativeViewTmp.nativeImplView, virtualIndex);
        }

        ZFUIViewFocus.ZFUIViewImplChanged(nativeViewTmp, nativeImplViewOld, nativeImplViewNew);
    }
    public static float native_nativeViewScaleForImpl(Object nativeView) {
        return ZFUIView.native_nativeViewScaleForPhysicalPixel(nativeView);
    }
    public static float native_nativeViewScaleForPhysicalPixel(Object nativeView) {
        return ZFAndroidUI.screenDensity(((View)nativeView).getContext());
    }
    public static void native_viewVisibleSet(Object nativeView,
                                                      boolean viewVisible) {
        ZFUIView.requestLayoutOverride = true;
        ((ZFUIView)nativeView).setVisibility(viewVisible ? View.VISIBLE : View.GONE);
        ZFUIView.requestLayoutOverride = false;
    }
    public static void native_viewAlphaSet(Object nativeView,
                                           float viewAlpha) {
        ZFUIView.requestLayoutOverride = true;
        ((ZFUIView)nativeView).setAlpha(viewAlpha);
        ZFUIView.requestLayoutOverride = false;
    }
    public static void native_viewUIEnableSet(Object nativeView,
                                              boolean viewUIEnable) {
        ZFUIView.requestLayoutOverride = true;
        ((ZFUIView)nativeView).viewUIEnable = viewUIEnable;
        ZFUIView.requestLayoutOverride = false;
    }
    public static void native_viewUIEnableTreeSet(Object nativeView,
                                                  boolean viewUIEnableTree) {
        ZFUIView.requestLayoutOverride = true;
        ZFUIView nativeViewTmp = (ZFUIView)nativeView;
        nativeViewTmp.viewUIEnableTree = viewUIEnableTree;
        nativeViewTmp.setClickable(viewUIEnableTree);
        ZFUIView.requestLayoutOverride = false;
    }
    public static void native_viewBackgroundColorSet(Object nativeView,
                                                     int viewBackgroundColor) {
        ZFUIView.requestLayoutOverride = true;
        ((ZFUIView)nativeView).setBackgroundColor(viewBackgroundColor);
        ZFUIView.requestLayoutOverride = false;
    }
    public static void native_childAdd(Object nativeView,
                                       Object nativeChild,
                                       int virtualIndex,
                                       int childLayer,
                                       int childLayerIndex) {
        ZFUIView.requestLayoutOverride = true;
        ZFUIView nativeViewTmp = (ZFUIView)nativeView;
        nativeViewTmp.addView((View)nativeChild, virtualIndex);
        ZFUIView.requestLayoutOverride = false;
    }
    public static void native_childRemove(Object nativeView,
                                          int virtualIndex,
                                          int childLayer,
                                          int childLayerIndex) {
        ZFUIView.requestLayoutOverride = true;
        ZFUIView nativeViewTmp = (ZFUIView)nativeView;
        nativeViewTmp.removeViewAt(virtualIndex);
        ZFUIView.requestLayoutOverride = false;
    }
    public static void native_viewFrameSet(Object nativeView,
                                           int viewFrame_x,
                                           int viewFrame_y,
                                           int viewFrame_width,
                                           int viewFrame_height) {
        ZFUIView.requestLayoutOverride = true;
        ZFUIView nativeViewTmp = (ZFUIView)nativeView;
        nativeViewTmp.viewFrame_x = viewFrame_x;
        nativeViewTmp.viewFrame_y = viewFrame_y;
        nativeViewTmp.viewFrame_width = viewFrame_width;
        nativeViewTmp.viewFrame_height = viewFrame_height;
        ZFUIView.requestLayoutOverride = false;
    }
    public static void native_layoutRequest(Object nativeView) {
        ZFUIView nativeViewTmp = (ZFUIView)nativeView;
        nativeViewTmp.requestLayout();
    }
    public static Object native_measureNativeView(Object nativeView,
                                                  int maxWidthOrNegative,
                                                  int maxHeightOrNegative) {
        View nativeViewTmp = (View)nativeView;
        nativeViewTmp.measure(
            (maxWidthOrNegative >= 0)
                ? MeasureSpec.makeMeasureSpec(maxWidthOrNegative, MeasureSpec.AT_MOST)
                : MeasureSpec.makeMeasureSpec(0, MeasureSpec.UNSPECIFIED),
            (maxHeightOrNegative >= 0)
                ? MeasureSpec.makeMeasureSpec(maxHeightOrNegative, MeasureSpec.AT_MOST)
                : MeasureSpec.makeMeasureSpec(0, MeasureSpec.UNSPECIFIED));
        return new ZFAndroidSize(nativeViewTmp.getMeasuredWidth(), nativeViewTmp.getMeasuredHeight());
    }

    // ============================================================
    public static native void native_notifyNeedLayout(long zfjniPointerOwnerZFUIView);
    public static native void native_notifyLayoutRootView(long zfjniPointerOwnerZFUIView,
                                                          ZFAndroidRect rect);
    public static native void native_notifyLayoutNativeImplView(long zfjniPointerOwnerZFUIView,
                                                                ZFAndroidRect rect);
    public static native void native_notifyUIEvent_mouse(long zfjniPointerOwnerZFUIView,
                                                         int mouseId,
                                                         int mouseAction,
                                                         int mousePointX,
                                                         int mousePointY);
    public static native boolean native_notifyUIEvent_key(long zfjniPointerOwnerZFUIView,
                                                          int keyId,
                                                          int keyAction,
                                                          int keyCode,
                                                          int keyCodeRaw);

    // ============================================================
    protected ZFUIView(Context context) {
        super(context);
        this.init(context);
    }
    protected ZFUIView(Context context, AttributeSet attrs) {
        super(context, attrs);
        this.init(context);
    }
    protected ZFUIView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        this.init(context);
    }
    private void init(Context context) {
        this.setClipToPadding(false);
        this.setFocusable(false);
        this.setFocusableInTouchMode(false);
    }

    private static int _keyCodeFromKeyCodeRaw(int keyCodeRaw) {
        switch(keyCodeRaw) {
            case KeyEvent.KEYCODE_UNKNOWN:
                return ZFEnum.e("ZFUIKeyCode", "kUnknown");

            case KeyEvent.KEYCODE_ESCAPE:
                return ZFEnum.e("ZFUIKeyCode", "kEsc");
            case KeyEvent.KEYCODE_TAB:
                return ZFEnum.e("ZFUIKeyCode", "kTab");
            case KeyEvent.KEYCODE_FORWARD_DEL:
                return ZFEnum.e("ZFUIKeyCode", "kBackspace");
            case KeyEvent.KEYCODE_ENTER:
                return ZFEnum.e("ZFUIKeyCode", "kEnter");
            case KeyEvent.KEYCODE_SPACE:
                return ZFEnum.e("ZFUIKeyCode", "kSpace");
            case KeyEvent.KEYCODE_CAPS_LOCK:
                return ZFEnum.e("ZFUIKeyCode", "kCapsLock");
            case KeyEvent.KEYCODE_SHIFT_LEFT:
            case KeyEvent.KEYCODE_SHIFT_RIGHT:
                return ZFEnum.e("ZFUIKeyCode", "kShift");
            case KeyEvent.KEYCODE_CTRL_LEFT:
            case KeyEvent.KEYCODE_CTRL_RIGHT:
                return ZFEnum.e("ZFUIKeyCode", "kCtrl");
            case KeyEvent.KEYCODE_ALT_LEFT:
            case KeyEvent.KEYCODE_ALT_RIGHT:
                return ZFEnum.e("ZFUIKeyCode", "kAlt");
            case KeyEvent.KEYCODE_META_LEFT:
            case KeyEvent.KEYCODE_META_RIGHT:
                return ZFEnum.e("ZFUIKeyCode", "kCommand");
            /* case KeyEvent.KEYCODE_MENU:
                return ZFEnum.e("ZFUIKeyCode", "kContextMenu"); */ // mapped to kPhoneMenu

            case KeyEvent.KEYCODE_F1:
                return ZFEnum.e("ZFUIKeyCode", "kF1");
            case KeyEvent.KEYCODE_F2:
                return ZFEnum.e("ZFUIKeyCode", "kF2");
            case KeyEvent.KEYCODE_F3:
                return ZFEnum.e("ZFUIKeyCode", "kF3");
            case KeyEvent.KEYCODE_F4:
                return ZFEnum.e("ZFUIKeyCode", "kF4");
            case KeyEvent.KEYCODE_F5:
                return ZFEnum.e("ZFUIKeyCode", "kF5");
            case KeyEvent.KEYCODE_F6:
                return ZFEnum.e("ZFUIKeyCode", "kF6");
            case KeyEvent.KEYCODE_F7:
                return ZFEnum.e("ZFUIKeyCode", "kF7");
            case KeyEvent.KEYCODE_F8:
                return ZFEnum.e("ZFUIKeyCode", "kF8");
            case KeyEvent.KEYCODE_F9:
                return ZFEnum.e("ZFUIKeyCode", "kF9");
            case KeyEvent.KEYCODE_F10:
                return ZFEnum.e("ZFUIKeyCode", "kF10");
            case KeyEvent.KEYCODE_F11:
                return ZFEnum.e("ZFUIKeyCode", "kF11");
            case KeyEvent.KEYCODE_F12:
                return ZFEnum.e("ZFUIKeyCode", "kF12");

            case KeyEvent.KEYCODE_0:
                return ZFEnum.e("ZFUIKeyCode", "k0");
            case KeyEvent.KEYCODE_1:
                return ZFEnum.e("ZFUIKeyCode", "k1");
            case KeyEvent.KEYCODE_2:
                return ZFEnum.e("ZFUIKeyCode", "k2");
            case KeyEvent.KEYCODE_3:
                return ZFEnum.e("ZFUIKeyCode", "k3");
            case KeyEvent.KEYCODE_4:
                return ZFEnum.e("ZFUIKeyCode", "k4");
            case KeyEvent.KEYCODE_5:
                return ZFEnum.e("ZFUIKeyCode", "k5");
            case KeyEvent.KEYCODE_6:
                return ZFEnum.e("ZFUIKeyCode", "k6");
            case KeyEvent.KEYCODE_7:
                return ZFEnum.e("ZFUIKeyCode", "k7");
            case KeyEvent.KEYCODE_8:
                return ZFEnum.e("ZFUIKeyCode", "k8");
            case KeyEvent.KEYCODE_9:
                return ZFEnum.e("ZFUIKeyCode", "k9");

            case KeyEvent.KEYCODE_A:
                return ZFEnum.e("ZFUIKeyCode", "kA");
            case KeyEvent.KEYCODE_B:
                return ZFEnum.e("ZFUIKeyCode", "kB");
            case KeyEvent.KEYCODE_C:
                return ZFEnum.e("ZFUIKeyCode", "kC");
            case KeyEvent.KEYCODE_D:
                return ZFEnum.e("ZFUIKeyCode", "kD");
            case KeyEvent.KEYCODE_E:
                return ZFEnum.e("ZFUIKeyCode", "kE");
            case KeyEvent.KEYCODE_F:
                return ZFEnum.e("ZFUIKeyCode", "kF");
            case KeyEvent.KEYCODE_G:
                return ZFEnum.e("ZFUIKeyCode", "kG");
            case KeyEvent.KEYCODE_H:
                return ZFEnum.e("ZFUIKeyCode", "kH");
            case KeyEvent.KEYCODE_I:
                return ZFEnum.e("ZFUIKeyCode", "kI");
            case KeyEvent.KEYCODE_J:
                return ZFEnum.e("ZFUIKeyCode", "kJ");
            case KeyEvent.KEYCODE_K:
                return ZFEnum.e("ZFUIKeyCode", "kK");
            case KeyEvent.KEYCODE_L:
                return ZFEnum.e("ZFUIKeyCode", "kL");
            case KeyEvent.KEYCODE_M:
                return ZFEnum.e("ZFUIKeyCode", "kM");
            case KeyEvent.KEYCODE_N:
                return ZFEnum.e("ZFUIKeyCode", "kN");
            case KeyEvent.KEYCODE_O:
                return ZFEnum.e("ZFUIKeyCode", "kO");
            case KeyEvent.KEYCODE_P:
                return ZFEnum.e("ZFUIKeyCode", "kP");
            case KeyEvent.KEYCODE_Q:
                return ZFEnum.e("ZFUIKeyCode", "kQ");
            case KeyEvent.KEYCODE_R:
                return ZFEnum.e("ZFUIKeyCode", "kR");
            case KeyEvent.KEYCODE_S:
                return ZFEnum.e("ZFUIKeyCode", "kS");
            case KeyEvent.KEYCODE_T:
                return ZFEnum.e("ZFUIKeyCode", "kT");
            case KeyEvent.KEYCODE_U:
                return ZFEnum.e("ZFUIKeyCode", "kU");
            case KeyEvent.KEYCODE_V:
                return ZFEnum.e("ZFUIKeyCode", "kV");
            case KeyEvent.KEYCODE_W:
                return ZFEnum.e("ZFUIKeyCode", "kW");
            case KeyEvent.KEYCODE_X:
                return ZFEnum.e("ZFUIKeyCode", "kX");
            case KeyEvent.KEYCODE_Y:
                return ZFEnum.e("ZFUIKeyCode", "kY");
            case KeyEvent.KEYCODE_Z:
                return ZFEnum.e("ZFUIKeyCode", "kZ");

            case KeyEvent.KEYCODE_GRAVE:
                return ZFEnum.e("ZFUIKeyCode", "kGrave");
            case KeyEvent.KEYCODE_MINUS:
                return ZFEnum.e("ZFUIKeyCode", "kMinus");
            case KeyEvent.KEYCODE_EQUALS:
                return ZFEnum.e("ZFUIKeyCode", "kEquals");
            case KeyEvent.KEYCODE_LEFT_BRACKET:
                return ZFEnum.e("ZFUIKeyCode", "kBracketLeft");
            case KeyEvent.KEYCODE_RIGHT_BRACKET:
                return ZFEnum.e("ZFUIKeyCode", "kBracketRight");
            case KeyEvent.KEYCODE_BACKSLASH:
                return ZFEnum.e("ZFUIKeyCode", "kBackSlash");
            case KeyEvent.KEYCODE_SEMICOLON:
                return ZFEnum.e("ZFUIKeyCode", "kSemiColon");
            case KeyEvent.KEYCODE_APOSTROPHE:
                return ZFEnum.e("ZFUIKeyCode", "kApostrophe");
            case KeyEvent.KEYCODE_COMMA:
                return ZFEnum.e("ZFUIKeyCode", "kComma");
            case KeyEvent.KEYCODE_PERIOD:
                return ZFEnum.e("ZFUIKeyCode", "kPeriod");
            case KeyEvent.KEYCODE_SLASH:
                return ZFEnum.e("ZFUIKeyCode", "kSlash");

            case KeyEvent.KEYCODE_DPAD_LEFT:
                return ZFEnum.e("ZFUIKeyCode", "kLeft");
            case KeyEvent.KEYCODE_DPAD_UP:
                return ZFEnum.e("ZFUIKeyCode", "kUp");
            case KeyEvent.KEYCODE_DPAD_RIGHT:
                return ZFEnum.e("ZFUIKeyCode", "kRight");
            case KeyEvent.KEYCODE_DPAD_DOWN:
                return ZFEnum.e("ZFUIKeyCode", "kDown");
            case KeyEvent.KEYCODE_MOVE_HOME:
                return ZFEnum.e("ZFUIKeyCode", "kHome");
            case KeyEvent.KEYCODE_MOVE_END:
                return ZFEnum.e("ZFUIKeyCode", "kEnd");
            case KeyEvent.KEYCODE_PAGE_UP:
                return ZFEnum.e("ZFUIKeyCode", "kPageUp");
            case KeyEvent.KEYCODE_PAGE_DOWN:
                return ZFEnum.e("ZFUIKeyCode", "kPageDown");
            case KeyEvent.KEYCODE_INSERT:
                return ZFEnum.e("ZFUIKeyCode", "kInsert");
            case KeyEvent.KEYCODE_DEL:
                return ZFEnum.e("ZFUIKeyCode", "kDelete");
            case KeyEvent.KEYCODE_SYSRQ:
                return ZFEnum.e("ZFUIKeyCode", "kPrintScreen");
            case KeyEvent.KEYCODE_SCROLL_LOCK:
                return ZFEnum.e("ZFUIKeyCode", "kScrollLock");
            case KeyEvent.KEYCODE_BREAK:
                return ZFEnum.e("ZFUIKeyCode", "kPauseBreak");

            case KeyEvent.KEYCODE_NUMPAD_0:
                return ZFEnum.e("ZFUIKeyCode", "kNum0");
            case KeyEvent.KEYCODE_NUMPAD_1:
                return ZFEnum.e("ZFUIKeyCode", "kNum1");
            case KeyEvent.KEYCODE_NUMPAD_2:
                return ZFEnum.e("ZFUIKeyCode", "kNum2");
            case KeyEvent.KEYCODE_NUMPAD_3:
                return ZFEnum.e("ZFUIKeyCode", "kNum3");
            case KeyEvent.KEYCODE_NUMPAD_4:
                return ZFEnum.e("ZFUIKeyCode", "kNum4");
            case KeyEvent.KEYCODE_NUMPAD_5:
                return ZFEnum.e("ZFUIKeyCode", "kNum5");
            case KeyEvent.KEYCODE_NUMPAD_6:
                return ZFEnum.e("ZFUIKeyCode", "kNum6");
            case KeyEvent.KEYCODE_NUMPAD_7:
                return ZFEnum.e("ZFUIKeyCode", "kNum7");
            case KeyEvent.KEYCODE_NUMPAD_8:
                return ZFEnum.e("ZFUIKeyCode", "kNum8");
            case KeyEvent.KEYCODE_NUMPAD_9:
                return ZFEnum.e("ZFUIKeyCode", "kNum9");
            case KeyEvent.KEYCODE_NUM_LOCK:
                return ZFEnum.e("ZFUIKeyCode", "kNumLock");
            case KeyEvent.KEYCODE_NUMPAD_ADD:
                return ZFEnum.e("ZFUIKeyCode", "kNumAdd");
            case KeyEvent.KEYCODE_NUMPAD_SUBTRACT:
                return ZFEnum.e("ZFUIKeyCode", "kNumMinus");
            case KeyEvent.KEYCODE_NUMPAD_MULTIPLY:
                return ZFEnum.e("ZFUIKeyCode", "kNumMultiply");
            case KeyEvent.KEYCODE_NUMPAD_DIVIDE:
                return ZFEnum.e("ZFUIKeyCode", "kNumDivide");
            case KeyEvent.KEYCODE_NUMPAD_ENTER:
                return ZFEnum.e("ZFUIKeyCode", "kNumEnter");
            case KeyEvent.KEYCODE_NUMPAD_DOT:
                return ZFEnum.e("ZFUIKeyCode", "kNumDot");

            case KeyEvent.KEYCODE_MEDIA_PLAY:
                return ZFEnum.e("ZFUIKeyCode", "kMediaPlay");
            case KeyEvent.KEYCODE_MEDIA_PAUSE:
                return ZFEnum.e("ZFUIKeyCode", "kMediaPause");
            case KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE:
                return ZFEnum.e("ZFUIKeyCode", "kMediaPlayPause");
            case KeyEvent.KEYCODE_MEDIA_STOP:
                return ZFEnum.e("ZFUIKeyCode", "kMediaStop");
            case KeyEvent.KEYCODE_MEDIA_RECORD:
                return ZFEnum.e("ZFUIKeyCode", "kMediaRecord");
            case KeyEvent.KEYCODE_MEDIA_PREVIOUS:
                return ZFEnum.e("ZFUIKeyCode", "kMediaPrev");
            case KeyEvent.KEYCODE_MEDIA_NEXT:
                return ZFEnum.e("ZFUIKeyCode", "kMediaNext");
            case KeyEvent.KEYCODE_MEDIA_FAST_FORWARD:
                return ZFEnum.e("ZFUIKeyCode", "kMediaFastForward");
            case KeyEvent.KEYCODE_MEDIA_REWIND:
                return ZFEnum.e("ZFUIKeyCode", "kMediaFastRewind");

            case KeyEvent.KEYCODE_VOLUME_MUTE:
                return ZFEnum.e("ZFUIKeyCode", "kVolumeMute");
            case KeyEvent.KEYCODE_VOLUME_UP:
                return ZFEnum.e("ZFUIKeyCode", "kVolumeUp");
            case KeyEvent.KEYCODE_VOLUME_DOWN:
                return ZFEnum.e("ZFUIKeyCode", "kVolumeDown");

            case KeyEvent.KEYCODE_CALL:
                return ZFEnum.e("ZFUIKeyCode", "kPhoneCall");
            case KeyEvent.KEYCODE_ENDCALL:
                return ZFEnum.e("ZFUIKeyCode", "kPhoneCallEnd");
            case KeyEvent.KEYCODE_HOME:
                return ZFEnum.e("ZFUIKeyCode", "kPhoneHome");
            case KeyEvent.KEYCODE_MENU:
                return ZFEnum.e("ZFUIKeyCode", "kPhoneMenu");
            case KeyEvent.KEYCODE_BACK:
                return ZFEnum.e("ZFUIKeyCode", "kPhoneBack");
            case KeyEvent.KEYCODE_SEARCH:
                return ZFEnum.e("ZFUIKeyCode", "kPhoneSearch");
            case KeyEvent.KEYCODE_CAMERA:
                return ZFEnum.e("ZFUIKeyCode", "kPhoneCamera");
            default:
                return ZFEnum.e("ZFUIKeyCode", "kUnknown");
        }
    }
    private static int _keyActionFromKeyActionRaw(int keyActionRaw) {
        switch(keyActionRaw) {
            case KeyEvent.ACTION_DOWN:
                return ZFEnum.e("ZFUIKeyAction", "KeyDown");
            case KeyEvent.ACTION_MULTIPLE:
                return ZFEnum.e("ZFUIKeyAction", "KeyRepeat");
            case KeyEvent.ACTION_UP:
                return ZFEnum.e("ZFUIKeyAction", "KeyUp");
            default:
                return ZFEnum.e("ZFUIKeyAction", "KeyCancel");
        }
    }
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        _pressedKeyAdd((int)event.getDownTime(), event.getKeyCode());
        if(this.zfjniPointerOwnerZFUIView != 0
            && ZFUIView.native_notifyUIEvent_key(
                this.zfjniPointerOwnerZFUIView,
                (int)event.getDownTime(),
                _keyActionFromKeyActionRaw(event.getAction()),
                _keyCodeFromKeyCodeRaw(keyCode),
                keyCode)) {
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }
    @Override
    public boolean onKeyMultiple(int keyCode, int repeatCount, KeyEvent event) {
        if(this.zfjniPointerOwnerZFUIView != 0
            && ZFUIView.native_notifyUIEvent_key(
                this.zfjniPointerOwnerZFUIView,
                (int)event.getDownTime(),
                _keyActionFromKeyActionRaw(event.getAction()),
                _keyCodeFromKeyCodeRaw(keyCode),
                keyCode)) {
            return true;
        }
        return super.onKeyMultiple(keyCode, repeatCount, event);
    }
    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
        _pressedKeyRemove((int)event.getDownTime(), event.getKeyCode());
        if(this.zfjniPointerOwnerZFUIView != 0
            && ZFUIView.native_notifyUIEvent_key(
                this.zfjniPointerOwnerZFUIView,
                (int)event.getDownTime(),
                _keyActionFromKeyActionRaw(event.getAction()),
                _keyCodeFromKeyCodeRaw(keyCode),
                keyCode)) {
            return true;
        }
        return super.onKeyUp(keyCode, event);
    }
    private final List<Integer> _pressedKeyId = new ArrayList<Integer>();
    private final List<Integer> _pressedKeyCode = new ArrayList<Integer>();
    private void _pressedKeyAdd(int keyId, int keyCode) {
        _pressedKeyId.add(keyId);
        _pressedKeyCode.add(keyCode);
    }
    private void _pressedKeyRemove(int keyId, int keyCode) {
        int index = _pressedKeyId.indexOf(keyId);
        if(index >= 0 && _pressedKeyCode.get(index) == keyCode) {
            _pressedKeyId.remove(index);
            _pressedKeyCode.remove(index);
        }
    }
    private void _pressedKeyCancel() {
        for(int i = 0; i < _pressedKeyId.size(); ++i) {
            ZFUIView.native_notifyUIEvent_key(
                this.zfjniPointerOwnerZFUIView,
                _pressedKeyId.get(i),
                ZFEnum.e("ZFUIKeyAction", "KeyCancel"),
                _keyCodeFromKeyCodeRaw(_pressedKeyCode.get(i)),
                _pressedKeyCode.get(i));
        }
    }
    @Override
    protected void onDetachedFromWindow() {
        super.onDetachedFromWindow();
        _pressedKeyCancel();
    }
    @Override
    protected void onFocusChanged(boolean gainFocus,
                                  int direction,
                                  Rect previouslyFocusedRect) {
        super.onFocusChanged(gainFocus, direction, previouslyFocusedRect);
        _pressedKeyCancel();
    }

    @Override
    public boolean dispatchTouchEvent(MotionEvent ev) {
        if(!this.viewUIEnableTree) {
            return false;
        }
        if(this.viewUIEnable) {
            return super.dispatchTouchEvent(ev);
        }

        int x = (int)ev.getX() + this.getScrollX();
        int y = (int)ev.getY() + this.getScrollY();
        for(int i = 0; i < this.getChildCount(); ++i) {
            View child = this.getChildAt(i);
            if(child != this.nativeImplView
                && (child.getVisibility() == View.VISIBLE || child.getAnimation() != null)) {
                child.getHitRect(this._rectNativeCache);
                if(this._rectNativeCache.contains(x, y)) {
                    return super.dispatchTouchEvent(ev);
                }
            }
        }
        return false;
    }
    @SuppressLint("ClickableViewAccessibility")
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        int action = ZFEnum.e("ZFUIMouseAction", "MouseDown");
        switch(event.getAction()) {
            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_POINTER_DOWN:
                action = ZFEnum.e("ZFUIMouseAction", "MouseDown");
                break;
            case MotionEvent.ACTION_MOVE:
                action = ZFEnum.e("ZFUIMouseAction", "MouseMove");
                break;
            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_POINTER_UP:
                action = ZFEnum.e("ZFUIMouseAction", "MouseUp");
                break;
            case MotionEvent.ACTION_CANCEL:
                action = ZFEnum.e("ZFUIMouseAction", "MouseCancel");
                break;
            default:
                return true;
        }
        for(int i = 0; i < event.getPointerCount(); ++i) {
            if(this.zfjniPointerOwnerZFUIView != 0) {
                ZFUIView.native_notifyUIEvent_mouse(
                    this.zfjniPointerOwnerZFUIView,
                    event.getPointerId(i),
                    action,
                    (int)event.getX(i),
                    (int)event.getY(i));
            }
        }
        return true;
    }

    @Override
    public void requestLayout() {
        if(!this.isLayoutRequested()) {
            super.requestLayout();
            if(!ZFUIView.requestLayoutOverride
                && this.zfjniPointerOwnerZFUIView != 0
                && (this.getParent() != null && !(this.getParent() instanceof ZFUIView))) {
                ZFUIView.native_notifyNeedLayout(this.zfjniPointerOwnerZFUIView);
            }
        }
        else {
            super.requestLayout();
        }
    }
    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        if(this.zfjniPointerOwnerZFUIView != 0
            && (this.getParent() != null && !(this.getParent() instanceof ZFUIView))) {
            this._rectCache.set(
                this.getLeft(),
                this.getTop(),
                MeasureSpec.getSize(widthMeasureSpec),
                MeasureSpec.getSize(heightMeasureSpec));
            ZFUIView.native_notifyLayoutRootView(this.zfjniPointerOwnerZFUIView, this._rectCache);
        }
        widthMeasureSpec = MeasureSpec.makeMeasureSpec(this.viewFrame_width, MeasureSpec.EXACTLY);
        heightMeasureSpec = MeasureSpec.makeMeasureSpec(this.viewFrame_height, MeasureSpec.EXACTLY);
        if(this.nativeImplView != null) {
            this.nativeImplView.measure(widthMeasureSpec, heightMeasureSpec);
        }

        // measure all children is necessary to ensure valid state for underlying Android View's layout logic
        for(int i = 0; i < this.getChildCount(); ++i) {
            View child = this.getChildAt(i);
            child.measure(widthMeasureSpec, heightMeasureSpec);
        }
        this.setMeasuredDimension(this.viewFrame_width, this.viewFrame_height);
    }
    @Override
    protected void onLayout(boolean changed, int l, int t, int r, int b) {
        for(int i = 0; i < this.getChildCount(); ++i) {
            View child = this.getChildAt(i);
            if(child == this.nativeImplView) {
                ZFUIView.native_notifyLayoutNativeImplView(this.zfjniPointerOwnerZFUIView, this._rectCache);
                child.layout(
                    this._rectCache.x,
                    this._rectCache.y,
                    this._rectCache.x + this._rectCache.width,
                    this._rectCache.y + this._rectCache.height);
            }
            else if (child instanceof ZFUIView) {
                ZFUIView childTmp = (ZFUIView)child;
                childTmp.layout(childTmp.viewFrame_x,
                    childTmp.viewFrame_y,
                    childTmp.viewFrame_x + childTmp.viewFrame_width,
                    childTmp.viewFrame_y + childTmp.viewFrame_height);
            }
            else {
                // usually should not go here
                child.layout(0, 0, r - l, b - t);
            }
        }
    }
}
