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

