/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFPropertyType_spec.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// zfautoObject
ZFPROPERTY_TYPE_DEFINE_BY_SERIALIZABLE_CONVERTER_WITH_CUSTOM_WRAPPER(zfautoObject, zfautoObject, {
        return ZFObjectFromData(v, serializableData, outErrorHint, outErrorPos);
    }, {
        return ZFObjectToData(serializableData, v, outErrorHint);
    })
ZFOUTPUT_TYPE_DEFINE(zfautoObject, {
        output.execute(
            (v == zfautoObjectNull())
            ? ZFTOKEN_zfnull
            : v.toObject()->objectInfo()
        );
    })

ZFOBJECT_REGISTER(v_zfautoObject)
void v_zfautoObject::objectInfoOnAppend(ZF_IN_OUT zfstring &ret)
{
    ZFCoreElementInfoGetter<zfautoObject>::elementInfoGetter(ret, this->zfv);
}
ZFCompareResult v_zfautoObject::objectCompare(ZF_IN ZFObject *anotherObj)
{
    ZFPropertyTypeWrapper *t = ZFCastZFObject(ZFPropertyTypeWrapper *, anotherObj);
    if(t == zfnull || !zfscmpTheSame(this->wrappedValueTypeId(), t->wrappedValueTypeId()))
    {
        return ZFCompareUncomparable;
    }
    else
    {
        return ZFComparerDefault(this->zfv, *(_ZFP_PropTypeW_zfautoObject *)t->wrappedValue());
    }
}
const zfchar *v_zfautoObject::wrappedValueTypeId(void)
{
    return ZFPropertyTypeIdData<_ZFP_PropTypeW_zfautoObject>::PropertyTypeId();
}
zfbool v_zfautoObject::wrappedValueIsInit(void)
{
    return (ZFComparerDefault(this->zfv, zftValue<_ZFP_PropTypeW_zfautoObject>().zfv) == ZFCompareTheSame);
}
ZFCompareResult v_zfautoObject::wrappedValueCompare(ZF_IN const void *v)
{
    return ZFComparerDefault(this->zfv, *(const _ZFP_PropTypeW_zfautoObject *)v);
}

// ============================================================
// ZFObject
ZF_STATIC_REGISTER_INIT(PropTIReg_ZFObject)
{
    _ZFP_ZFPropertyTypeIdDataRegister(ZFPropertyTypeId_ZFObject,
        zfnew(ZFPropertyTypeIdData<ZFObject *>));
}
ZF_STATIC_REGISTER_DESTROY(PropTIReg_ZFObject)
{
    _ZFP_ZFPropertyTypeIdDataUnregister(ZFPropertyTypeId_ZFObject);
}
ZF_STATIC_REGISTER_END(PropTIReg_ZFObject)

// ============================================================
// ZFCallerInfo
ZFPROPERTY_TYPE_DEFINE_BY_STRING_CONVERTER(ZFCallerInfo, ZFCallerInfoHolder, {
        zfindexRange pos[3] = {0};
        const zfchar *p = src;
        const zfchar *pEnd = src + ((srcLen == zfindexMax()) ? zfslen(src) : srcLen);

        zfcharSkipSpace(p, pEnd);
        if(p >= pEnd)
        {
            v.callerInfoSet();
            return zftrue;
        }
        if(*p != '[')
        {
            return zffalse;
        }
        ++p;

        if(*p != ' ')
        {
            pos[0].start = p - src;
            while(*p != ' ' && p < pEnd) {++p;}
            pos[0].count = p - src - pos[0].start;
        }
        ++p;

        if(*p != ' ')
        {
            pos[1].start = p - src;
            while(*p != ' ' && p < pEnd) {++p;}
            pos[1].count = p - src - pos[1].start;
        }
        ++p;

        if(*p != '(')
        {
            return zffalse;
        }
        ++p;
        pos[2].start = p - src;
        while(*p != ')' && p < pEnd) {++p;}
        pos[2].count = p - src - pos[2].start;

        if(p + 2 > pEnd || *p != ')' || *(p + 1) != ']')
        {
            return zffalse;
        }

        v.callerInfoSet(
                (pos[0].count > 0)
                    ? zfstring(src + pos[0].start, pos[0].count).cString()
                    : zfnull,
                (pos[1].count > 0)
                    ? zfstring(src + pos[1].start, pos[1].count).cString()
                    : zfnull,
                (zfindex)zfsToInt(zfstring(src + pos[2].start, pos[2].count).cString())
            );
        return zftrue;
    }, {
        v.callerInfoT(s);
        return zftrue;
    })

ZF_NAMESPACE_GLOBAL_END

