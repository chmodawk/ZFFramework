/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFCore_test.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfclass _ZFP_ZFCore_ZFAnyTestParent : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_ZFCore_ZFAnyTestParent, ZFObject)
};
zfclass _ZFP_ZFCore_ZFAnyTestChild : zfextends _ZFP_ZFCore_ZFAnyTestParent
{
    ZFOBJECT_DECLARE(_ZFP_ZFCore_ZFAnyTestChild, _ZFP_ZFCore_ZFAnyTestParent)
};

zfclass ZFCore_ZFAny_test : zfextends ZFFramework_test_TestCase
{
    ZFOBJECT_DECLARE(ZFCore_ZFAny_test, ZFFramework_test_TestCase)

protected:
    zfoverride
    virtual void testCaseOnStart(void)
    {
        zfsuper::testCaseOnStart();

        zfblockedAlloc(_ZFP_ZFCore_ZFAnyTestChild, objChild);
        _ZFP_ZFCore_ZFAnyTestParent *objCenter = objChild;
        ZFAnyT<_ZFP_ZFCore_ZFAnyTestChild *> anyChild(objChild);
        ZFAnyT<_ZFP_ZFCore_ZFAnyTestParent *> anyCenter(objChild);
        ZFAny any(objChild);

        // ============================================================
        // ZFCastZFObject
        // any
        objChild = any;
        any = objChild;
        any = anyCenter;
        anyChild = any;

        objChild = ZFCastZFObject(_ZFP_ZFCore_ZFAnyTestChild *, any);
        any = ZFCastZFObject(ZFAny, objCenter);
        any = ZFCastZFObject(ZFAny, any);
        any = ZFCastZFObject(ZFAny, anyCenter);
        anyChild = ZFCastZFObject(ZFAnyT<_ZFP_ZFCore_ZFAnyTestChild *>, any);

        // anyT
        objChild = anyCenter;
        // anyChild = objCenter; // this should compile error
        // anyChild = anyCenter; // this should compile error

        objChild = ZFCastZFObject(_ZFP_ZFCore_ZFAnyTestChild *, anyCenter);
        // anyChild = ZFCastZFObject(ZFAnyT<_ZFP_ZFCore_ZFAnyTestChild *>, objCenter); // this should compile error
        // anyChild = ZFCastZFObject(ZFAnyT<_ZFP_ZFCore_ZFAnyTestChild *>, anyCenter); // this should compile error

        // ============================================================
        // ZFCastZFObjectUnchecked
        // any
        objChild = any;
        any = objChild;
        any = anyCenter;
        anyChild = any;

        objChild = ZFCastZFObjectUnchecked(_ZFP_ZFCore_ZFAnyTestChild *, any);
        any = ZFCastZFObjectUnchecked(ZFAny, objCenter);
        any = ZFCastZFObjectUnchecked(ZFAny, any);
        any = ZFCastZFObjectUnchecked(ZFAny, anyCenter);
        anyChild = ZFCastZFObjectUnchecked(ZFAnyT<_ZFP_ZFCore_ZFAnyTestChild *>, any);

        // anyT
        objChild = anyCenter;
        // anyChild = objCenter; // this should compile error
        // anyChild = anyCenter; // this should compile error

        objChild = ZFCastZFObjectUnchecked(_ZFP_ZFCore_ZFAnyTestChild *, anyCenter);
        // anyChild = ZFCastZFObjectUnchecked(ZFAnyT<_ZFP_ZFCore_ZFAnyTestChild *>, objCenter); // this should compile error
        // anyChild = ZFCastZFObjectUnchecked(ZFAnyT<_ZFP_ZFCore_ZFAnyTestChild *>, anyCenter); // this should compile error

        ZFUNUSED(objChild);
        ZFUNUSED(objCenter);
        ZFUNUSED(anyChild);
        ZFUNUSED(anyCenter);
        ZFUNUSED(any);

        this->testCaseStop();
    }
};
ZFOBJECT_REGISTER(ZFCore_ZFAny_test)

ZF_NAMESPACE_GLOBAL_END

