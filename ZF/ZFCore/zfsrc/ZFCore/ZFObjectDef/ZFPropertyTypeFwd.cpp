/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFPropertyTypeFwd.h"
#include "ZFObjectImpl.h"

#include "ZFCore/ZFSTLWrapper/zfstl_string.h"
#include "ZFCore/ZFSTLWrapper/zfstl_map.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfbool ZFPropertyTypeIdDataBase::propertyWrapperFromSerializableData(ZF_OUT zfautoObject &v,
                                                                     ZF_IN const ZFSerializableData &serializableData,
                                                                     ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */,
                                                                     ZF_OUT_OPT ZFSerializableData *outErrorPos /* = zfnull */) const
{
    this->propertyWrapper(v);
    ZFPropertyTypeWrapper *wrapper = ZFCastZFObject(ZFPropertyTypeWrapper *, v);
    if(wrapper == zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("property not serializable"));
        return zffalse;
    }
    return wrapper->wrappedValueFromSerializableData(serializableData, outErrorHint, outErrorPos);
}
zfbool ZFPropertyTypeIdDataBase::propertyWrapperToSerializableData(ZF_OUT ZFSerializableData &serializableData,
                                                                   ZF_IN ZFObject *v,
                                                                   ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */) const
{
    ZFPropertyTypeWrapper *wrapper = ZFCastZFObject(ZFPropertyTypeWrapper *, v);
    if(wrapper == zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint,
            zfText("unable to access wrapper type"));
        return zffalse;
    }
    return wrapper->wrappedValueToSerializableData(serializableData, outErrorHint);
}
zfbool ZFPropertyTypeIdDataBase::propertyWrapperFromString(ZF_OUT zfautoObject &v,
                                                           ZF_IN const zfchar *src,
                                                           ZF_IN_OPT zfindex srcLen /* = zfindexMax() */) const
{
    this->propertyWrapper(v);
    ZFPropertyTypeWrapper *wrapper = ZFCastZFObject(ZFPropertyTypeWrapper *, v);
    if(wrapper == zfnull)
    {
        return zffalse;
    }
    return wrapper->wrappedValueFromString(src, srcLen);
}
zfbool ZFPropertyTypeIdDataBase::propertyWrapperToString(ZF_IN_OUT zfstring &s,
                                                         ZF_IN ZFObject *v) const
{
    ZFPropertyTypeWrapper *wrapper = ZFCastZFObject(ZFPropertyTypeWrapper *, v);
    if(wrapper == zfnull)
    {
        return zffalse;
    }
    return wrapper->wrappedValueToString(s);
}

// ============================================================
ZF_STATIC_INITIALIZER_INIT(ZFPropertyTypeIdDataHolder)
{
}
ZF_STATIC_INITIALIZER_DESTROY(ZFPropertyTypeIdDataHolder)
{
    zfCoreAssert(m.empty());
}
zfstlmap<zfstlstringZ, ZFPropertyTypeIdDataBase *> m;
ZF_STATIC_INITIALIZER_END(ZFPropertyTypeIdDataHolder)

void _ZFP_ZFPropertyTypeIdDataRegister(ZF_IN const zfchar *propertyTypeId,
                                       ZF_IN ZFPropertyTypeIdDataBase *propertyTypeIdData)
{
    zfCoreMutexLocker();
    zfstlmap<zfstlstringZ, ZFPropertyTypeIdDataBase *> &m = ZF_STATIC_INITIALIZER_INSTANCE(ZFPropertyTypeIdDataHolder)->m;
    zfCoreAssert(m.find(propertyTypeId) == m.end());
    m[propertyTypeId] = propertyTypeIdData;
}
void _ZFP_ZFPropertyTypeIdDataUnregister(ZF_IN const zfchar *propertyTypeId)
{
    zfCoreMutexLocker();
    zfstlmap<zfstlstringZ, ZFPropertyTypeIdDataBase *> &m = ZF_STATIC_INITIALIZER_INSTANCE(ZFPropertyTypeIdDataHolder)->m;
    zfstlmap<zfstlstringZ, ZFPropertyTypeIdDataBase *>::iterator it = m.find(propertyTypeId);
    zfCoreAssert(it != m.end());
    ZFPropertyTypeIdDataBase *t = it->second;
    m.erase(it);
    zfdelete(t);
}
const ZFPropertyTypeIdDataBase *ZFPropertyTypeIdDataGet(ZF_IN const zfchar *propertyTypeId)
{
    zfCoreMutexLocker();
    zfstlmap<zfstlstringZ, ZFPropertyTypeIdDataBase *> &m = ZF_STATIC_INITIALIZER_INSTANCE(ZFPropertyTypeIdDataHolder)->m;
    zfstlmap<zfstlstringZ, ZFPropertyTypeIdDataBase *>::iterator it = m.find(propertyTypeId);
    if(it != m.end())
    {
        return it->second;
    }
    else
    {
        return zfnull;
    }
}
void ZFPropertyTypeIdDataGetAllT(ZF_OUT ZFCoreArray<const ZFPropertyTypeIdDataBase *> &ret)
{
    zfCoreMutexLocker();
    zfstlmap<zfstlstringZ, ZFPropertyTypeIdDataBase *> &m = ZF_STATIC_INITIALIZER_INSTANCE(ZFPropertyTypeIdDataHolder)->m;
    for(zfstlmap<zfstlstringZ, ZFPropertyTypeIdDataBase *>::iterator it = m.begin(); it != m.end(); ++it)
    {
        ret.add(it->second);
    }
}

ZF_NAMESPACE_GLOBAL_END

