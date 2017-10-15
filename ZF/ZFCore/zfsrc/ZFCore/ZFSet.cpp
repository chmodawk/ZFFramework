/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFSet.h"
#include "ZFMap.h"

ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// ZFSet
ZFOBJECT_REGISTER(ZFSet)

void ZFSet::objectOnInit(ZF_IN ZFContainer *another)
{
    this->objectOnInit();
    zfself::addFrom(another);
}
void ZFSet::objectOnInit(void)
{
    zfsuper::objectOnInit();
    d = zfAllocWithoutLeakTest(ZFMapEditable);
}
void ZFSet::objectOnDealloc(void)
{
    zfReleaseWithoutLeakTest(d);
    d = zfnull;
    zfsuper::objectOnDealloc();
}

ZFMETHOD_DEFINE_0(ZFSet, zfindex, count)
{
    return d->count();
}
ZFMETHOD_DEFINE_0(ZFSet, zfbool, isEmpty)
{
    return d->isEmpty();
}
ZFMETHOD_DEFINE_1(ZFSet, zfbool, isContain,
                  ZFMP_IN(ZFObject *, obj))
{
    return d->isContain(obj);
}

void ZFSet::add(ZF_IN ZFObject *obj)
{
    zfCoreAssertWithMessage(obj != zfnull, zfTextA("insert null object"));
    if(!d->isContain(obj))
    {
        d->set(obj, zfnullObject());
        this->contentOnAdd(obj);
        this->contentOnChange();
    }
}
void ZFSet::addFrom(ZF_IN ZFContainer *another)
{
    if(another == this || another == zfnull)
    {
        return ;
    }

    for(zfiterator it = another->iterator(); another->iteratorIsValid(it);)
    {
        ZFObject *obj = another->iteratorNext(it);
        if(!d->isContain(obj))
        {
            d->set(obj, zfnullObject());
            this->contentOnAdd(obj);
        }
    }

    this->contentOnChange();
}

void ZFSet::removeElement(ZF_IN ZFObject *obj)
{
    ZFKeyValuePairHolder tmp = d->removeAndGetPair(obj);
    if(tmp.key.toObject() != zfnull)
    {
        this->contentOnRemove(tmp.key.toObject());
        this->contentOnChange();
    }
}
void ZFSet::removeAll(void)
{
    if(!d->isEmpty())
    {
        for(zfiterator it = d->iterator(); d->iteratorIsValid(it); )
        {
            this->contentOnRemove(d->iteratorNextKey(it));
        }
        d->removeAll();

        this->contentOnChange();
    }
}

// ============================================================
ZFMETHOD_DEFINE_0(ZFSet, zfiterator, iterator)
{
    return d->iterator();
}

ZFMETHOD_DEFINE_1(ZFSet, zfiterator, iteratorFind,
                  ZFMP_IN(ZFObject *, value))
{
    return d->iteratorForKey(value);
}

ZFMETHOD_DEFINE_1(ZFSet, zfbool, iteratorIsValid,
                  ZFMP_IN(const zfiterator &, it))
{
    return d->iteratorIsValid(it);
}
ZFMETHOD_DEFINE_2(ZFSet, zfbool, iteratorIsEqual,
                  ZFMP_IN(const zfiterator &, it0),
                  ZFMP_IN(const zfiterator &, it1))
{
    return d->iteratorIsEqual(it0, it1);
}

ZFMETHOD_DEFINE_1(ZFSet, ZFObject *, iteratorGet,
                  ZFMP_IN(const zfiterator &, it))
{
    return d->iteratorGetKey(it);
}

ZFMETHOD_DEFINE_1(ZFSet, ZFObject *, iteratorNext,
                  ZFMP_IN_OUT(zfiterator &, it))
{
    return d->iteratorNextKey(it);
}
ZFMETHOD_DEFINE_1(ZFSet, ZFObject *, iteratorPrev,
                  ZFMP_IN_OUT(zfiterator &, it))
{
    return d->iteratorPrevKey(it);
}

void ZFSet::iteratorSet(ZF_IN_OUT zfiterator &it,
                        ZF_IN ZFObject *value)
{
    this->add(value);
}
void ZFSet::iteratorRemove(ZF_IN_OUT zfiterator &it)
{
    ZFKeyValuePair tmp = d->iteratorGetPair(it);
    if(tmp.key != zfnull)
    {
        this->contentOnRemove(tmp.key);
        d->iteratorRemove(it);
        this->contentOnChange();
    }
}
void ZFSet::iteratorAdd(ZF_IN ZFObject *value,
                        ZF_IN_OPT const zfiterator &it /* = zfiteratorInvalid */)
{
    this->add(value);
}

ZF_NAMESPACE_GLOBAL_END

