/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFContainer.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFOBJECT_REGISTER(ZFContainer)

ZFOBSERVER_EVENT_REGISTER(ZFContainer, ContentOnChange)
ZFOBSERVER_EVENT_REGISTER(ZFContainer, ContentOnAdd)
ZFOBSERVER_EVENT_REGISTER(ZFContainer, ContentOnRemove)

zfbool ZFContainer::serializableOnCheck(void)
{
    if(!zfsuperI(ZFSerializable)::serializableOnCheck()) {return zffalse;}
    for(zfiterator it = this->iterator(); this->iteratorIsValid(it); )
    {
        if(!ZFObjectIsSerializable(this->iteratorNext(it)))
        {
            return zffalse;
        }
    }
    return zftrue;
}
zfbool ZFContainer::serializableOnSerializeFromData(ZF_IN const ZFSerializableData &serializableData,
                                                    ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */,
                                                    ZF_OUT_OPT ZFSerializableData *outErrorPos /* = zfnull */)
{
    if(!zfsuperI(ZFSerializable)::serializableOnSerializeFromData(serializableData, outErrorHint, outErrorPos)) {return zffalse;}

    this->removeAll();

    for(zfindex i = 0; i < serializableData.elementCount(); ++i)
    {
        const ZFSerializableData &categoryData = serializableData.elementAtIndex(i);
        if(categoryData.resolved()) {continue;}
        const zfchar *category = ZFSerializableUtil::checkCategory(categoryData);
        if(category == zfnull) {continue;}

        if(zfscmpTheSame(category, ZFSerializableKeyword_ZFContainer_element))
        {
            zfautoObject element;
            if(!ZFObjectFromData(element, categoryData, outErrorHint, outErrorPos))
            {
                return zffalse;
            }
            if(element == zfautoObjectNull())
            {
                ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, categoryData,
                    zfText("null element"));
                return zffalse;
            }
            this->iteratorAdd(element.toObject());

            categoryData.resolveMark();
        }
    }
    return zftrue;
}
zfbool ZFContainer::serializableOnSerializeToData(ZF_IN_OUT ZFSerializableData &serializableData,
                                                  ZF_IN ZFSerializable *referencedOwnerOrNull,
                                                  ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */)
{
    if(!zfsuperI(ZFSerializable)::serializableOnSerializeToData(serializableData, referencedOwnerOrNull, outErrorHint)) {return zffalse;}
    zfself *ref = ZFCastZFObject(zfself *, referencedOwnerOrNull);

    if(ref == zfnull)
    {
        for(zfiterator it = this->iterator(); this->iteratorIsValid(it); )
        {
            ZFSerializableData elementData;
            if(!ZFObjectToData(elementData, this->iteratorNext(it), outErrorHint))
            {
                return zffalse;
            }
            elementData.categorySet(ZFSerializableKeyword_ZFContainer_element);
            serializableData.elementAdd(elementData);
        }
    }
    else
    {
        return this->serializableOnSerializeToDataWithRef(serializableData, ref, outErrorHint);
    }

    return zftrue;
}
zfbool ZFContainer::serializableOnSerializeToDataWithRef(ZF_IN_OUT ZFSerializableData &serializableData,
                                                         ZF_IN ZFSerializable *referencedOwnerOrNull,
                                                         ZF_OUT_OPT zfstring *outErrorHint /* = zfnull */)
{
    ZFContainer *ref = ZFCastZFObject(ZFContainer *, referencedOwnerOrNull);
    if(ref == zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint,
            zfText("%s not type of %s"),
            referencedOwnerOrNull->toObject()->objectInfoOfInstance().cString(), ZFContainer::ClassData()->className());
        return zffalse;
    }

    if(ref->count() == 0)
    {
        for(zfiterator it = this->iterator(); this->iteratorIsValid(it); )
        {
            ZFObject *element = this->iteratorNext(it);
            ZFSerializableData elementData;
            if(!ZFObjectToData(elementData, element, outErrorHint))
            {
                return zffalse;
            }
            elementData.categorySet(ZFSerializableKeyword_ZFContainer_element);
            serializableData.elementAdd(elementData);
        }
        return zftrue;
    }

    ZFContainer *tmp = this->classData()->newInstanceWithoutLeakTest();
    zfblockedReleaseWithoutLeakTest(tmp);
    tmp->addFrom(ref);
    for(zfiterator it = this->iterator(); this->iteratorIsValid(it); )
    {
        ZFObject *element = this->iteratorNext(it);
        zfiterator itTmp = tmp->iteratorFind(element);
        if(ref->iteratorIsValid(itTmp))
        {
            tmp->iteratorRemove(itTmp);
            continue;
        }

        ZFSerializableData elementData;
        if(!ZFObjectToData(elementData, element, outErrorHint))
        {
            return zffalse;
        }
        elementData.categorySet(ZFSerializableKeyword_ZFContainer_element);
        serializableData.elementAdd(elementData);
    }

    if(tmp->count() > 0)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint,
            zfText("missing elements from referenced container: %s"), tmp->objectInfoOfContent().cString());
        return zffalse;
    }

    return zftrue;
}

void ZFContainer::objectOnDeallocPrepare(void)
{
    this->removeAll();
    zfsuper::objectOnDeallocPrepare();
}

ZFMETHOD_DEFINE_3(ZFContainer, void, objectInfoOfContentT,
                  ZFMP_IN_OUT(zfstring &, ret),
                  ZFMP_IN_OPT(zfindex, maxCount, zfindexMax()),
                  ZFMP_IN_OPT(const ZFTokenForContainer &, token, ZFTokenForContainerDefault()))
{
    zfindex count = 0;
    ret += token.tokenLeft;
    zfiterator it = this->iterator();
    for(; this->iteratorIsValid(it) && count < maxCount; ++count)
    {
        if(count > 0)
        {
            ret += token.tokenSeparator;
        }
        ret += token.tokenValueLeft;
        this->iteratorNext(it)->objectInfoT(ret);
        ret += token.tokenValueRight;
    }
    if(count < this->count())
    {
        if(count > 0)
        {
            ret += token.tokenSeparator;
        }
        ret += token.tokenEtc;
    }
    ret += token.tokenRight;
}

zfidentity ZFContainer::objectHash(void)
{
    ZFObject *first = zfnull;
    {
        zfiterator it = this->iterator();
        if(this->iteratorIsValid(it))
        {
            first = this->iteratorGet(it);
        }
    }
    if(first != zfnull)
    {
        return zfidentityHash(this->count(), first->objectHash());
    }
    else
    {
        return zfidentityZero();
    }
}
ZFCompareResult ZFContainer::objectCompare(ZF_IN ZFObject *anotherObj)
{
    if(this == anotherObj) {return ZFCompareTheSame;}
    zfself *another = ZFCastZFObject(zfself *, anotherObj);
    if(another == zfnull) {return ZFCompareUncomparable;}

    if(this->count() != another->count()
        || this->objectHash() != another->objectHash())
    {
        return ZFCompareUncomparable;
    }
    for(zfiterator it = this->iterator(), itRef = another->iterator(); this->iteratorIsValid(it);)
    {
        if(ZFObjectCompare(this->iteratorNext(it), another->iteratorNext(itRef)) != ZFCompareTheSame)
        {
            return ZFCompareUncomparable;
        }
    }
    return ZFCompareTheSame;
}

void ZFContainer::objectCachedOnChange(void)
{
    zfsuper::objectCachedOnChange();
    zfbool objectCached = this->objectCached();
    for(zfiterator it = this->iterator(); this->iteratorIsValid(it); )
    {
        this->iteratorNext(it)->objectCachedSet(objectCached);
    }
}

ZF_NAMESPACE_GLOBAL_END

