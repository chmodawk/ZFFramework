/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFImpl_sys_Android_ZF.h"

#if ZF_ENV_sys_Android

ZF_NAMESPACE_GLOBAL_BEGIN

#define ZFImpl_sys_Android_JNI_ID_ZFEnum ZFImpl_sys_Android_JNI_ID(ZF_ZFEnum)
#define ZFImpl_sys_Android_JNI_NAME_ZFEnum ZFImpl_sys_Android_JNI_NAME(ZF.ZFEnum)

ZF_NAMESPACE_GLOBAL_END

ZFSTRINGENCODING_ASSERT(ZFStringEncoding::e_UTF8)

JNI_METHOD_DECLARE(jint, ZFImpl_sys_Android_JNI_ID_ZFEnum, native_1rawEnumValue,
                   JNIEnv *jniEnv, jclass jniCls,
                   jstring rawEnumValueName)
{
    const zfchar *rawEnumValueNameT = JNIUtilGetStringUTFChars(jniEnv, rawEnumValueName, zfnull);
    zfuint ret = ZFEnumInvalid();
    do
    {
        const ZFMethod *method = ZFMethodFuncGet(ZFMethodFuncNamespaceGlobal, rawEnumValueNameT);
        if(method == zfnull) {break;}
        ret = method->executeStatic<zfuint>();
    } while(zffalse);
    JNIUtilReleaseStringUTFChars(jniEnv, rawEnumValueName, rawEnumValueNameT);
    return (jint)ret;
}
JNI_METHOD_DECLARE(jint, ZFImpl_sys_Android_JNI_ID_ZFEnum, native_1enumDefault,
                   JNIEnv *jniEnv, jclass jniCls,
                   jstring enumClassName)
{
    const zfchar *enumClassNameT = JNIUtilGetStringUTFChars(jniEnv, enumClassName, zfnull);
    zfuint ret = ZFEnumInvalid();
    do
    {
        const ZFClass *cls = ZFClass::classForName(enumClassNameT);
        if(cls == zfnull || !cls->classIsTypeOf(ZFEnum::ClassData())) {break;}
        const ZFMethod *method = cls->methodForName(zfText("EnumDefault"));
        if(method == zfnull) {break;}
        ret = method->executeStatic<zfuint>();
    } while(zffalse);
    JNIUtilReleaseStringUTFChars(jniEnv, enumClassName, enumClassNameT);
    return (jint)ret;
}
JNI_METHOD_DECLARE(jint, ZFImpl_sys_Android_JNI_ID_ZFEnum, native_1enumValue,
                   JNIEnv *jniEnv, jclass jniCls,
                   jstring enumClassName,
                   jstring enumValueName)
{
    const zfchar *enumClassNameT = JNIUtilGetStringUTFChars(jniEnv, enumClassName, zfnull);
    const zfchar *enumValueNameT = JNIUtilGetStringUTFChars(jniEnv, enumValueName, zfnull);
    zfuint ret = ZFEnumInvalid();
    do
    {
        const ZFClass *cls = ZFClass::classForName(enumClassNameT);
        if(cls == zfnull || !cls->classIsTypeOf(ZFEnum::ClassData())) {break;}
        const ZFMethod *method = cls->methodForName(zfText("EnumValueForName"));
        if(method == zfnull) {break;}
        ret = method->executeStatic<zfuint, const zfchar *>(enumValueNameT);
    } while(zffalse);
    JNIUtilReleaseStringUTFChars(jniEnv, enumClassName, enumClassNameT);
    JNIUtilReleaseStringUTFChars(jniEnv, enumValueName, enumValueNameT);
    return (jint)ret;
}
JNI_METHOD_DECLARE(jstring, ZFImpl_sys_Android_JNI_ID_ZFEnum, native_1enumName,
                   JNIEnv *jniEnv, jclass jniCls,
                   jstring enumClassName,
                   jint enumValue)
{
    const zfchar *enumClassNameT = JNIUtilGetStringUTFChars(jniEnv, enumClassName, zfnull);
    const zfchar *ret = ZFEnumNameInvalid();
    do
    {
        const ZFClass *cls = ZFClass::classForName(enumClassNameT);
        if(cls == zfnull || !cls->classIsTypeOf(ZFEnum::ClassData())) {break;}
        const ZFMethod *method = cls->methodForName(zfText("EnumNameForValue"));
        if(method == zfnull) {break;}
        ret = method->executeStatic<const zfchar *, zfuint>((zfuint)enumValue);
    } while(zffalse);
    JNIUtilReleaseStringUTFChars(jniEnv, enumClassName, enumClassNameT);
    return JNIUtilNewStringUTF(jniEnv, ret);
}

#endif // #if ZF_ENV_sys_Android

