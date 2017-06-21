/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFCopyable.h"
#include "ZFSerializable.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFOBJECT_REGISTER(ZFCopyable)

zfautoObject ZFCopyable::copy(void)
{
    zfautoObject ret = this->classData()->newInstance(ZFCallerInfoMake());
    if(ret != zfautoObjectNull)
    {
        ZFCastZFObjectUnchecked(zfself *, ret.toObject())->copyableOnCopyFrom(this->toObject());
        if(ret.toObject()->classData()->classIsTypeOf(ZFSerializable::ClassData()))
        {
            ZFCastZFObjectUnchecked(ZFSerializable *, ret.toObject())->serializableCopyInfoFrom(ZFCastZFObjectUnchecked(ZFSerializable *, this));
        }
    }
    return ret;
}

void ZFCopyable::copyFrom(ZF_IN ZFObject *anotherObj)
{
    if(anotherObj != zfnull && anotherObj != this->toObject() && anotherObj->classData() == this->classData())
    {
        this->copyableOnCopyFrom(anotherObj);
        if(this->classData()->classIsTypeOf(ZFSerializable::ClassData()))
        {
            ZFCastZFObjectUnchecked(ZFSerializable *, this)->serializableCopyInfoFrom(ZFCastZFObjectUnchecked(ZFSerializable *, anotherObj));
        }
    }
}

ZF_NAMESPACE_GLOBAL_END

#if 1 // ZFObject related method register
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

ZFMETHOD_USER_REGISTER_0({return invokerObject->to<ZFCopyable *>()->copy();}, ZFCopyable, zfautoObject, copy)
ZFMETHOD_USER_REGISTER_1({return invokerObject->to<ZFCopyable *>()->copyFrom(anotherObj);}, ZFCopyable, void, copy, ZFMP_IN(ZFObject *, anotherObj))

ZF_NAMESPACE_GLOBAL_END
#endif

