/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFUIListAdapterArray.h
 * @brief basic list adapter which hold all list cells directly (with no recycle logic)
 */

#ifndef _ZFI_ZFUIListAdapterArray_h_
#define _ZFI_ZFUIListAdapterArray_h_

#include "ZFUIListAdapter.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
/**
 * @brief basic list adapter which hold all list cells directly (with no recycle logic)
 */
zfclass ZF_ENV_EXPORT ZFUIListAdapterArray : zfextends ZFObject, zfimplements ZFUIListAdapter
{
    ZFOBJECT_DECLARE(ZFUIListAdapterArray, ZFObject)
    ZFIMPLEMENTS_DECLARE(ZFUIListAdapter)

public:
    zfoverride
    virtual ZFObject *objectOnInit(void)
    {
        zfsuper::objectOnInit();
        d = zfAllocWithoutLeakTest(ZFArrayEditable);
        return this;
    }
    zfoverride
    virtual void objectOnDealloc(void)
    {
        zfReleaseWithoutLeakTest(d);
        zfsuper::objectOnDealloc();
    }
    zfoverride
    virtual void objectOnDeallocPrepare(void)
    {
        this->cellRemoveAll();
        zfsuper::objectOnDeallocPrepare();
    }

public:
    /**
     * @brief directly access internal cell array,
     *   you may modify it directly, with caution
     */
    ZFMETHOD_DECLARE_0(ZFArrayEditable *, cellArray)
    {
        return d;
    }
    /**
     * @brief add cell
     */
    ZFMETHOD_DECLARE_1(void, cellAdd,
                       ZFMP_IN(ZFUIListCell *, cell))
    {
        d->add(cell);
    }
    /**
     * @brief add cell at index
     */
    ZFMETHOD_DECLARE_2(void, cellAdd,
                       ZFMP_IN(zfindex, index),
                       ZFMP_IN(ZFUIListCell *, cell))
    {
        d->add(index, cell);
    }
    /**
     * @brief remove cell
     */
    ZFMETHOD_DECLARE_2(void, cellRemove,
                       ZFMP_IN(zfindex, index),
                       ZFMP_IN_OPT(zfindex, count, 1))
    {
        d->remove(index, count);
    }
    /**
     * @brief remove cell
     */
    ZFMETHOD_DECLARE_1(void, cellRemoveElement,
                       ZFMP_IN(ZFUIListCell *, cell))
    {
        d->removeElement(cell);
    }
    /**
     * @brief remove all cell
     */
    ZFMETHOD_DECLARE_0(void, cellRemoveAll)
    {
        d->removeAll();
    }

public:
    /**
     * @brief whether to override default list cell size hint, false by default
     *
     * if true, #cellSizeHintOverrideValue would be used instead of #ZFUIListAdapter::cellSizeHint
     */
    ZFPROPERTY_ASSIGN(zfbool, cellSizeHintOverride)
    /**
     * @brief valid only if #cellSizeHintOverride, -1 by default, see #ZFUIListAdapter::cellSizeAtIndex
     */
    ZFPROPERTY_ASSIGN_WITH_INIT(zfint, cellSizeHintOverrideValue, ZFPropertyInitValue(-1))

public:
    ZFMETHOD_DECLARE_0(zfindex, cellCount)
    {
        return d->count();
    }
    ZFMETHOD_DECLARE_1(zfautoObject, cellAtIndex,
                       ZFMP_IN(zfindex, index))
    {
        return zfautoObjectCreate(d->get(index));
    }
    ZFMETHOD_DECLARE_2(zfint, cellSizeAtIndex,
                       ZFMP_IN(zfindex, index),
                       ZFMP_IN(ZFUIListCell *, cell))
    {
        if(this->cellSizeHintOverride())
        {
            return this->cellSizeHintOverrideValue();
        }
        else
        {
            return zfsuperI(ZFUIListAdapter)::cellSizeAtIndex(index, cell);
        }
    }

protected:
    zfoverride
    virtual zfautoObject cellCacheOnAccess(ZF_IN zfindex index)
    {
        return zfautoObjectCreate(d->get(index));
    }

private:
    ZFArrayEditable *d;
};

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFUIListAdapterArray_h_

