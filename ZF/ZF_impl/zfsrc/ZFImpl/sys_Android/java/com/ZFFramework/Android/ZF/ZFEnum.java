/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
package com.ZFFramework.Android.ZF;

public class ZFEnum {
    public static int raw(String rawEnumValueName) {
        return native_rawEnumValue(rawEnumValueName);
    }
    public static int e(String enumClassName, String enumValueName) {
        return native_enumValue(enumClassName, enumValueName);
    }
    public static int eDefault(String enumClassName) {
        return native_enumDefault(enumClassName);
    }
    public static String eName(String enumClassName, int enumValue) {
        return native_enumName(enumClassName, enumValue);
    }

    private native static int native_rawEnumValue(String rawEnumValueName);
    private native static int native_enumValue(String enumClassName, String enumValueName);
    private native static int native_enumDefault(String enumClassName);
    private native static String native_enumName(String enumClassName, int enumValue);
}
