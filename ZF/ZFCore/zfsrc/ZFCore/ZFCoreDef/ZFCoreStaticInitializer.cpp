/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFCoreStaticInitializer.h"
#include "ZFCoreArray.h"
#include "ZFCoreMutex.h"
#include "ZFCorePointer.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfclassLikePOD _ZFP_SI_ItemData
{
public:
    zfindex refCount;
    zfstring name;
    _ZFP_SI_Base *instance;
public:
    _ZFP_SI_ItemData(void)
    : refCount(1)
    , name()
    , instance(zfnull)
    {
    }
    ~_ZFP_SI_ItemData(void)
    {
        if(this->instance != zfnull)
        {
            zfdelete(this->instance);
        }
    }
};
#define _ZFP_SI_DataArrayType ZFCoreArray<ZFCorePointerForObject<_ZFP_SI_ItemData *> >

zfclassNotPOD _ZFP_SI_Data
{
public:
    _ZFP_SI_DataArrayType data;

public:
    _ZFP_SI_Base *&access(ZF_IN const zfchar *name,
                          ZF_IN _ZFP_SI_Constructor constructor)
    {
        for(zfindex i = 0; i < this->data.count(); ++i)
        {
            _ZFP_SI_ItemData &itemData = *(this->data[i].pointerValueGet());
            if(zfscmpTheSame(itemData.name.cString(), name))
            {
                ++(itemData.refCount);
                return itemData.instance;
            }
        }
        _ZFP_SI_ItemData *itemData = zfnew(_ZFP_SI_ItemData);
        itemData->name = name;
        itemData->instance = constructor();
        this->data.add(ZFCorePointerForObject<_ZFP_SI_ItemData *>(itemData));
        return itemData->instance;
    }
    void cleanup(ZF_IN const zfchar *name)
    {
        for(zfindex i = 0; i < this->data.count(); ++i)
        {
            _ZFP_SI_ItemData &itemData = *(this->data[i].pointerValueGet());
            if(zfscmpTheSame(itemData.name.cString(), name))
            {
                --(itemData.refCount);
                if(itemData.refCount == 0)
                {
                    this->data.remove(i);
                }
                break;
            }
        }
    }
};
static _ZFP_SI_Data &_ZFP_SI_dataRef_(void)
{
    static _ZFP_SI_Data d;
    return d;
}
#define _ZFP_SI_dataRef _ZFP_SI_dataRef_()

_ZFP_SI_Base *&_ZFP_SI_instanceAccess(ZF_IN const zfchar *name,
                                      ZF_IN _ZFP_SI_Constructor constructor)
{
    return _ZFP_SI_dataRef.access(name, constructor);
}
void _ZFP_SI_instanceCleanup(ZF_IN _ZFP_SI_Base *instance)
{
    _ZFP_SI_dataRef.cleanup(instance->_ZFP_SI_name());
}

ZF_NAMESPACE_GLOBAL_END

