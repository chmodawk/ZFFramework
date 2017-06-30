/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
package com.ZFFramework.Android.NativeEnum.ZFCore;

public class ZFObjectInstanceState {
    public static final int ZFObjectInstanceStateOnInit = ZFObjectInstanceState.native_ZFObjectInstanceStateOnInit();
    private native static int native_ZFObjectInstanceStateOnInit();
    public static final int ZFObjectInstanceStateOnInitFinish = ZFObjectInstanceState.native_ZFObjectInstanceStateOnInitFinish();
    private native static int native_ZFObjectInstanceStateOnInitFinish();
    public static final int ZFObjectInstanceStateIdle = ZFObjectInstanceState.native_ZFObjectInstanceStateIdle();
    private native static int native_ZFObjectInstanceStateIdle();
    public static final int ZFObjectInstanceStateOnDeallocPrepare = ZFObjectInstanceState.native_ZFObjectInstanceStateOnDeallocPrepare();
    private native static int native_ZFObjectInstanceStateOnDeallocPrepare();
    public static final int ZFObjectInstanceStateOnDealloc = ZFObjectInstanceState.native_ZFObjectInstanceStateOnDealloc();
    private native static int native_ZFObjectInstanceStateOnDealloc();
}

