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

zfclass _ZFP_ZFCore_ZFProperty_test_TestBase : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_ZFCore_ZFProperty_test_TestBase, ZFObject)

public:
    // retain
    ZFPROPERTY_RETAIN(ZFObject *, propertyRetain)
    ZFPROPERTY_RETAIN_READONLY(ZFObject *, propertyRetainReadonly, ZFPropertyNoInitValue)

    // assign
    ZFPROPERTY_ASSIGN(zfstring, propertyAssign)
    ZFPROPERTY_ASSIGN_READONLY(zfstring, propertyAssignReadonly, ZFPropertyNoInitValue)

    // custom callback
    ZFPROPERTY_CUSTOM_INIT_CHECKER_DECLARE(ZFObject *, propertyRetain)
    {
        if(outInitValue != zfnull) {*outInitValue = zfautoObjectNull();}
        return (this->propertyRetain() == zfnull);
    }
    ZFPROPERTY_CUSTOM_VALUE_COMPARER_DECLARE(ZFObject *, propertyRetain)
    {
        return ZFComparerDefault(this->propertyRetain(), anotherObj->to<zfself *>()->propertyRetain());
    }
    ZFPROPERTY_CUSTOM_ON_INIT_DECLARE(ZFObject *, propertyRetain)
    {
        zfLogT();
    }
    ZFPROPERTY_CUSTOM_ON_DEALLOC_DECLARE(ZFObject *, propertyRetain)
    {
        zfLogT();
    }
    ZFPROPERTY_CUSTOM_ON_VERIFY_DECLARE(ZFObject *, propertyRetain)
    {
        zfLogT();
    }
    ZFPROPERTY_CUSTOM_ON_ATTACH_DECLARE(ZFObject *, propertyRetain)
    {
        zfLogT();
    }
    ZFPROPERTY_CUSTOM_ON_DETACH_DECLARE(ZFObject *, propertyRetain)
    {
        zfLogT();
    }
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(ZFObject *, propertyRetain)
    {
        zfLogT();
    }

    ZFPROPERTY_CUSTOM_INIT_CHECKER_DECLARE(zfstring, propertyAssign);
    ZFPROPERTY_CUSTOM_VALUE_COMPARER_DECLARE(zfstring, propertyAssign);
    ZFPROPERTY_CUSTOM_ON_INIT_DECLARE(zfstring, propertyAssign);
    ZFPROPERTY_CUSTOM_ON_DEALLOC_DECLARE(zfstring, propertyAssign);
    ZFPROPERTY_CUSTOM_ON_VERIFY_DECLARE(zfstring, propertyAssign);
    ZFPROPERTY_CUSTOM_ON_ATTACH_DECLARE(zfstring, propertyAssign);
    ZFPROPERTY_CUSTOM_ON_DETACH_DECLARE(zfstring, propertyAssign);
    ZFPROPERTY_CUSTOM_ON_UPDATE_DECLARE(zfstring, propertyAssign);
};
ZFPROPERTY_CUSTOM_INIT_CHECKER_DEFINE(_ZFP_ZFCore_ZFProperty_test_TestBase, zfstring, propertyAssign)
{
    if(outInitValue != zfnull) {*outInitValue = zfText("");}
    return this->propertyAssign().isEmpty();
}
ZFPROPERTY_CUSTOM_VALUE_COMPARER_DEFINE(_ZFP_ZFCore_ZFProperty_test_TestBase, zfstring, propertyAssign)
{
    return ZFComparerDefault(this->propertyAssign(), anotherObj->to<zfself *>()->propertyAssign());
}
ZFPROPERTY_CUSTOM_ON_INIT_DEFINE(_ZFP_ZFCore_ZFProperty_test_TestBase, zfstring, propertyAssign)
{
    zfLogT();
}
ZFPROPERTY_CUSTOM_ON_DEALLOC_DEFINE(_ZFP_ZFCore_ZFProperty_test_TestBase, zfstring, propertyAssign)
{
    zfLogT();
}
ZFPROPERTY_CUSTOM_ON_VERIFY_DEFINE(_ZFP_ZFCore_ZFProperty_test_TestBase, zfstring, propertyAssign)
{
    zfLogT();
}
ZFPROPERTY_CUSTOM_ON_ATTACH_DEFINE(_ZFP_ZFCore_ZFProperty_test_TestBase, zfstring, propertyAssign)
{
    zfLogT();
}
ZFPROPERTY_CUSTOM_ON_DETACH_DEFINE(_ZFP_ZFCore_ZFProperty_test_TestBase, zfstring, propertyAssign)
{
    zfLogT();
}
ZFPROPERTY_CUSTOM_ON_UPDATE_DEFINE(_ZFP_ZFCore_ZFProperty_test_TestBase, zfstring, propertyAssign)
{
    zfLogT();
}

zfclass _ZFP_ZFCore_ZFProperty_test_TestChild: zfextends _ZFP_ZFCore_ZFProperty_test_TestBase
{
    ZFOBJECT_DECLARE(_ZFP_ZFCore_ZFProperty_test_TestChild, _ZFP_ZFCore_ZFProperty_test_TestBase)

public:
    ZFPROPERTY_ASSIGN(zfstring, propertyInChild)
};

// ============================================================
zfclass ZFCore_ZFProperty_test : zfextends ZFFramework_test_TestCase
{
    ZFOBJECT_DECLARE(ZFCore_ZFProperty_test, ZFFramework_test_TestCase)

protected:
    zfoverride
    virtual void testCaseOnStart(void)
    {
        zfsuper::testCaseOnStart();

        ZFLeakTestBegin();

        this->testCaseOutputSeparator();
        this->testCaseOutput(zfText("ZFProperty"));
        {
            zfblockedAlloc(_ZFP_ZFCore_ZFProperty_test_TestChild, p);

            // property list
            const ZFClass *clsTmp = p->classData();
            zfLogT() << ZFDebugAutoEndlOff << zfText("list: ");
            for(zfindex i = 0; i < clsTmp->propertyCount(); ++i)
            {
                if(i > 0)
                {
                    zfLogTrimT() << ZFDebugAutoEndlOff << zfText(", ");
                }
                zfLogTrimT() << ZFDebugAutoSpaceOff << ZFDebugAutoEndlOff
                << clsTmp->propertyAtIndex(i)->propertyName();
            }
            zfLogTrimT();

            // reflect
            p->propertyAssignSet(zfText("oldValue"));
            zfLogT() << zfText("before:") << p->propertyAssign();
            p->classData()->methodForName(zfText("propertyAssignSet"))->execute<void, zfstring const &>(p, zfText("newValue"));
            zfLogT() << zfText("after:") << p->propertyAssign();
            zfLogT() << zfText("access by reflect:") << p->classData()->methodForName(zfText("propertyAssign"))->execute<zfstring const &>(p);

            // retain
            zfLogTrimT();
            zfLogTrimT() << zfText("retain");

            p->propertyRetainSet(zflineAlloc(ZFObject));
            zfLogT() << p->propertyRetain();

#if 0 // this should not compile
            p->propertyRetainReadonlySet(zflineAlloc(ZFObject));
#endif
            zfLogT() << p->propertyRetainReadonly();

            // assign
            zfLogTrimT();
            zfLogTrimT() << zfText("assign");

            p->propertyAssignSet(zfstring());
            zfLogT() << p->propertyAssign();

#if 0 // this should not compile
            p->propertyAssignReadonlySet(zfstring());
#endif
            zfLogT() << p->propertyAssignReadonly();

            // copy
            this->testCaseOutputSeparator();
            this->testCaseOutput(zfText("copy propertis"));
            zfblockedAlloc(_ZFP_ZFCore_ZFProperty_test_TestBase, pBase);
            zfblockedAlloc(_ZFP_ZFCore_ZFProperty_test_TestChild, pChild);
            pBase->propertyAssignSet(zfText("string set in another"));
            ZFPropertyCopyAll(pChild, pBase);
            this->testCaseOutputSeparator();
            zfLogTrimT() << zfText("after copy:") << pChild->propertyAssign();

            this->testCaseOutputSeparator();
            this->testCaseOutput(zfText("copy by ZFPropertyCopyAll"));
            pChild->propertyAssignSet(zfText(""));
            ZFPropertyCopyAll(pChild, pBase);
            zfLogTrimT() << zfText("after copy:") << pChild->propertyAssign();
        }

        ZFLeakTestPrintStatus();
        ZFLeakTestEnd();

        this->testCaseStop();
    }
};
ZFOBJECT_REGISTER(ZFCore_ZFProperty_test)

ZF_NAMESPACE_GLOBAL_END

