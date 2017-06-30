/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
package com.ZFFramework.Android.NativeEnum.ZFCore;

public class ZFSerializablePropertyType {
    public static final int ZFSerializablePropertyTypeNotSerializable = ZFSerializablePropertyType.native_ZFSerializablePropertyTypeNotSerializable();
    private native static int native_ZFSerializablePropertyTypeNotSerializable();
    public static final int ZFSerializablePropertyTypeSerializableProperty = ZFSerializablePropertyType.native_ZFSerializablePropertyTypeSerializableProperty();
    private native static int native_ZFSerializablePropertyTypeSerializableProperty();
    public static final int ZFSerializablePropertyTypeEmbededProperty = ZFSerializablePropertyType.native_ZFSerializablePropertyTypeEmbededProperty();
    private native static int native_ZFSerializablePropertyTypeEmbededProperty();
}

