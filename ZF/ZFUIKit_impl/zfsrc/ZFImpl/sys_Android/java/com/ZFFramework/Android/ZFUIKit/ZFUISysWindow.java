/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
package com.ZFFramework.Android.ZFUIKit;

import com.ZFFramework.Android.NativeUtil.ZFAndroidLog;
import com.ZFFramework.Android.NativeUtil.ZFAndroidRect;
import com.ZFFramework.Android.ZF.ZFEnum;
import com.ZFFramework.Android.ZF.ZFMainEntry;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.graphics.Color;
import android.os.Bundle;
import android.view.Surface;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.FrameLayout;

/**
 * @brief window as a Activity in Android
 *
 * must be started by ZFMainEntry or another ZFUISysWindow\n
 * before use, you must declare this in your AndroidManifest.xml:
 * @code
 *   <activity
 *       android:name="com.ZFFramework.Android.ZFUIKit.ZFUISysWindow"
 *       android:configChanges="orientation|keyboardHidden|screenSize"
 *       android:label="ZFFramework"
 *       android:windowSoftInputMode="adjustResize" >
 *   </activity>
 * @endcode
 */
public final class ZFUISysWindow extends Activity {
    private static final String _key_isMainWindow = "isMainWindow";
    private static final String _key_zfjniPointerOwnerZFUISysWindow = "zfjniPointerOwnerZFUISysWindow";
    private boolean _isMainWindow = false;
    private long _zfjniPointerOwnerZFUISysWindow = 0;
    private MainLayout _containerView = null;
    private int _windowOrientation = ZFEnum.e("ZFUIOrientation", "Top");
    private int _windowOrientationFlags = ZFEnum.e("ZFUIOrientation", "Top");

    // ============================================================
    public static void native_nativeMainWindowCreate(long zfjniPointerOwnerZFUISysWindow) {
        Intent intent = new Intent(ZFMainEntry.mainEntryActivity(), ZFUISysWindow.class);
        intent.putExtra(_key_isMainWindow, true);
        intent.putExtra(_key_zfjniPointerOwnerZFUISysWindow, zfjniPointerOwnerZFUISysWindow);
        ZFMainEntry.mainEntryActivity().startActivity(intent);
    }
    public static Object native_nativeWindowRootViewOnAdd(Object nativeWindow,
                                                          Object nativeWindowRootView) {
        ZFUISysWindow nativeWindowTmp = (ZFUISysWindow)nativeWindow;
        nativeWindowTmp._containerView.addView((View)nativeWindowRootView);
        return nativeWindowTmp._containerView;
    }
    public static void native_nativeWindowRootViewOnRemove(Object nativeWindow,
                                                           Object nativeWindowRootView) {
        ((ZFUISysWindow)nativeWindow)._containerView.removeView((View)nativeWindowRootView);
    }
    public static void native_modalWindowShow(Object nativeWindow,
                                              long zfjniPointerOwnerZFUISysWindow) {
        Intent intent = new Intent((ZFUISysWindow)nativeWindow, ZFUISysWindow.class);
        intent.putExtra(_key_zfjniPointerOwnerZFUISysWindow, zfjniPointerOwnerZFUISysWindow);
        ((ZFUISysWindow)nativeWindow).startActivity(intent);
    }
    public static void native_modalWindowFinish(Object nativeWindow) {
        ((ZFUISysWindow)nativeWindow).finish();
    }
    public static void native_windowLayoutParamOnChange(Object nativeWindow) {
        ZFUISysWindow nativeWindowTmp = (ZFUISysWindow)nativeWindow;
        nativeWindowTmp._containerView.requestLayout();
    }
    public static int native_windowOrientation(Object nativeWindow) {
        if(nativeWindow == null) {
            int nativeOrientation = ZFMainEntry.mainEntryActivity().getResources().getConfiguration().orientation;
            if(nativeOrientation == Configuration.ORIENTATION_LANDSCAPE) {
                return ZFEnum.e("ZFUIOrientation", "Left");
            }
            else {
                return ZFEnum.e("ZFUIOrientation", "Top");
            }
        }
        return ((ZFUISysWindow)nativeWindow)._windowOrientation;
    }
    public static void native_windowOrientationFlagsSet(Object nativeWindow,
                                                        int windowOrientationFlags) {
        ZFUISysWindow nativeWindowTmp = (ZFUISysWindow)nativeWindow;
        nativeWindowTmp._windowOrientationFlags = windowOrientationFlags;

        boolean left = ((windowOrientationFlags & ZFEnum.e("ZFUIOrientation", "Left")) != 0);
        boolean top = ((windowOrientationFlags & ZFEnum.e("ZFUIOrientation", "Top")) != 0);
        boolean right = ((windowOrientationFlags & ZFEnum.e("ZFUIOrientation", "Right")) != 0);
        boolean bottom = ((windowOrientationFlags & ZFEnum.e("ZFUIOrientation", "Bottom")) != 0);

        int count = 0;
        if(left) {++count;}
        if(top) {++count;}
        if(right) {++count;}
        if(bottom) {++count;}
        if(count > 1) {
            nativeWindowTmp.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR);
        }
        else if(top) {
            nativeWindowTmp.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
        }
        else if(left) {
            nativeWindowTmp.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_REVERSE_LANDSCAPE);
        }
        else if(right) {
            nativeWindowTmp.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        }
        else if(bottom) {
            nativeWindowTmp.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_REVERSE_PORTRAIT);
        }
    }

    // ============================================================
    private static native void native_notifyMeasureWindow(long zfjniPointerOwnerZFUISysWindow,
                                                          int refWidth,
                                                          int refHeight,
                                                          Object resultRect);
    private static native void native_notifyOnCreate(long zfjniPointerOwnerZFUISysWindow,
                                                     Object nativeWindow);
    private static native void native_notifyOnDestroy(long zfjniPointerOwnerZFUISysWindow);
    private static native void native_notifyOnResume(long zfjniPointerOwnerZFUISysWindow);
    private static native void native_notifyOnPause(long zfjniPointerOwnerZFUISysWindow);
    private static native void native_notifyOnRotate(long zfjniPointerOwnerZFUISysWindow);

    // ============================================================
    private static class MainLayout extends FrameLayout {
        public ZFUISysWindow _owner = null;
        public int _left = 0;
        public int _top = 0;
        public int _right = 0;
        public int _bottom = 0;

        public MainLayout(ZFUISysWindow owner) {
            super(owner);
            _owner = owner;
            this.setBackgroundColor(Color.WHITE);
        }

        private static ZFAndroidRect _rectCache = new ZFAndroidRect();
        @Override
        protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
            ZFUIOnScreenKeyboardState.keyboardFrameUpdate(((Activity)getContext()).getWindow(), _rectCache);
            int keyboardHeight = _rectCache.height;

            int width = MeasureSpec.getSize(widthMeasureSpec);
            int height = MeasureSpec.getSize(heightMeasureSpec);
            this.setMeasuredDimension(width, height);
            height += keyboardHeight;

            if(_owner != null && _owner._zfjniPointerOwnerZFUISysWindow != 0) {
                ZFUISysWindow.native_notifyMeasureWindow(_owner._zfjniPointerOwnerZFUISysWindow, width, height, _rectCache);
                _left = _rectCache.x;
                _top = _rectCache.y;
                _right = _rectCache.x + _rectCache.width;
                _bottom = _rectCache.y + _rectCache.height;
            }

            int childWidthSpec = MeasureSpec.makeMeasureSpec(_right - _left, MeasureSpec.EXACTLY);
            int childHeightSpec = MeasureSpec.makeMeasureSpec(_bottom - _top, MeasureSpec.EXACTLY);
            for(int i = 0; i < this.getChildCount(); ++i) {
                this.getChildAt(i).measure(childWidthSpec, childHeightSpec);
            }
        }
        @Override
        protected void onLayout(boolean changed, int left, int top, int right, int bottom) {
            for(int i = 0; i < this.getChildCount(); ++i) {
                this.getChildAt(i).layout(this._left, this._top, this._right, this._bottom);
            }
        }
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Bundle params = this.getIntent().getExtras();
        if(params == null) {
            ZFAndroidLog.shouldNotGoHere();
        }
        _isMainWindow = params.getBoolean(_key_isMainWindow, false);
        _zfjniPointerOwnerZFUISysWindow = params.getLong(_key_zfjniPointerOwnerZFUISysWindow);
        if(_zfjniPointerOwnerZFUISysWindow == 0) {
            ZFAndroidLog.shouldNotGoHere();
        }

        _containerView = new MainLayout(this);
        this.requestWindowFeature(Window.FEATURE_NO_TITLE);

        ZFUISysWindow.native_notifyOnCreate(_zfjniPointerOwnerZFUISysWindow, this);

        this.setContentView(_containerView);

        ZFMainEntry.activityAfterCreate(this, _containerView);
    }
    @Override
    protected void onDestroy() {
        ZFMainEntry.activityBeforeDestroy(this, _containerView);

        boolean needDestroyMainEntry = this._isMainWindow;

        ZFUISysWindow.native_notifyOnDestroy(_zfjniPointerOwnerZFUISysWindow);

        _containerView._owner = null;
        _containerView = null;

        if(needDestroyMainEntry && ZFMainEntry.mainEntryActivity() != null) {
            ZFMainEntry.mainEntryActivity().finish();
        }

        super.onDestroy();
    }
    @Override
    protected void onResume() {
        super.onResume();
        ZFUISysWindow.native_notifyOnResume(_zfjniPointerOwnerZFUISysWindow);
    }
    @Override
    protected void onPause() {
        ZFUISysWindow.native_notifyOnPause(_zfjniPointerOwnerZFUISysWindow);
        super.onPause();
    }
    @SuppressWarnings("deprecation")
    @Override
    public void onConfigurationChanged(Configuration newConfig) {
        super.onConfigurationChanged(newConfig);

        int windowOrientationOld = _windowOrientation;
        switch(((WindowManager)getSystemService(Context.WINDOW_SERVICE)).getDefaultDisplay().getOrientation()) {
            case Surface.ROTATION_0:
                _windowOrientation = ZFEnum.e("ZFUIOrientation", "Top");
                break;
            case Surface.ROTATION_90:
                _windowOrientation = ZFEnum.e("ZFUIOrientation", "Right");
                break;
            case Surface.ROTATION_180:
                _windowOrientation = ZFEnum.e("ZFUIOrientation", "Bottom");
                break;
            case Surface.ROTATION_270:
                _windowOrientation = ZFEnum.e("ZFUIOrientation", "Left");
                break;
            default:
                _windowOrientation = ZFEnum.e("ZFUIOrientation", "Top");
                break;
        }

        if(windowOrientationOld != _windowOrientation) {
            ZFUISysWindow.native_notifyOnRotate(_zfjniPointerOwnerZFUISysWindow);
        }
    }
}
