/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
package com.ZFFramework.Android.NativeEnum.ZFCore;

public class ZFClassDataChangeType {
    public static final int ZFClassDataChangeTypeAttach = ZFClassDataChangeType.native_ZFClassDataChangeTypeAttach();
    private native static int native_ZFClassDataChangeTypeAttach();
    public static final int ZFClassDataChangeTypeDetach = ZFClassDataChangeType.native_ZFClassDataChangeTypeDetach();
    private native static int native_ZFClassDataChangeTypeDetach();
    public static final int ZFClassDataChangeTypeUpdate = ZFClassDataChangeType.native_ZFClassDataChangeTypeUpdate();
    private native static int native_ZFClassDataChangeTypeUpdate();
}

