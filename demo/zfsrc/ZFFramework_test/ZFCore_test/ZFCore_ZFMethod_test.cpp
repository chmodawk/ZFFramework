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

// ============================================================
zfclass _ZFP_ZFCore_ZFMethod_test_TestBase : zfextends ZFObject
{
    ZFOBJECT_DECLARE(_ZFP_ZFCore_ZFMethod_test_TestBase, ZFObject)
public:
    zfstring s;

public:
    ZFMETHOD_DECLARE_0(void, methodNormal)
    {
        zfLogT();
    }
    ZFMETHOD_DECLARE_0(void, methodDefinedInCppFile);
    ZFMETHOD_DECLARE_0(void, methodStaticallyRegistered)
    {
        zfLogT();
    }
    ZFMETHOD_DECLARE_0(void, methodOverrided)
    {
        zfLogT();
    }
    ZFMETHOD_DECLARE_0(void, methodOverridedStaticallyRegisteredInBase)
    {
        zfLogT();
    }
    ZFMETHOD_DECLARE_0(void, methodOverridedStaticallyRegisteredInBaseAndChild)
    {
        zfLogT();
    }
    ZFMETHOD_DECLARE_DETAIL_0(
                              protected, ZFMethodIsVirtual,
                              void, methodProtected)
    {
        zfLogT();
    }
    ZFMETHOD_DECLARE_DETAIL_0(
                              private, ZFMethodIsVirtual,
                              void, methodPrivate)
    {
        zfLogT();
    }
    ZFMETHOD_DECLARE_STATIC_0(void, methodStatic)
    {
        zfLogT();
    }
    ZFMETHOD_DECLARE_1(void, methodOverloaded
                       , ZFMP_IN(zfint, param0))
    {
        zfLogT() << param0;
    }
    ZFMETHOD_DECLARE_1(void, methodOverloaded
                       , ZFMP_IN(zffloat, param0))
    {
        zfLogT() << param0;
    }
    ZFMETHOD_DECLARE_1(
                       void, methodForDefaultParam
                       , ZFMP_IN_OPT(const zfstring &, param0, zfText("DefaultParam")))
    {
        zfLogT() << param0;
    }
    ZFMETHOD_DECLARE_0(zfstring &, methodReturnReference)
    {
        zfLogT();
        return this->s;
    }
    ZFMETHOD_DECLARE_1(void, methodParamIsReference
                       , ZFMP_IN(zfstring &, param0)
                       )
    {
        zfLogT();
        param0 = zfText("newString");
    }
    ZFMETHOD_DECLARE_2(void, methodFor2Param
                       , ZFMP_IN(const zfchar *, param0)
                       , ZFMP_IN(const zfchar *, param1)
                       )
    {
        zfLogT() << param0 << param1;
    }
    ZFMETHOD_DECLARE_3(void, methodFor3Param
                       , ZFMP_IN(const zfchar *, param0)
                       , ZFMP_IN(const zfchar *, param1)
                       , ZFMP_IN(const zfchar *, param2)
                       )
    {
        zfLogT() << param0 << param1 << param2;
    }
    ZFMETHOD_DECLARE_4(void, methodFor4Param
                       , ZFMP_IN(const zfchar *, param0)
                       , ZFMP_IN(const zfchar *, param1)
                       , ZFMP_IN(const zfchar *, param2)
                       , ZFMP_IN(const zfchar *, param3)
                       )
    {
        zfLogT() << param0 << param1 << param2 << param3;
    }
    ZFMETHOD_DECLARE_5(void, methodFor5Param
                       , ZFMP_IN(const zfchar *, param0)
                       , ZFMP_IN(const zfchar *, param1)
                       , ZFMP_IN(const zfchar *, param2)
                       , ZFMP_IN(const zfchar *, param3)
                       , ZFMP_IN(const zfchar *, param4)
                       )
    {
        zfLogT() << param0 << param1 << param2 << param3 << param4;
    }
    ZFMETHOD_DECLARE_6(void, methodFor6Param
                       , ZFMP_IN(const zfchar *, param0)
                       , ZFMP_IN(const zfchar *, param1)
                       , ZFMP_IN(const zfchar *, param2)
                       , ZFMP_IN(const zfchar *, param3)
                       , ZFMP_IN(const zfchar *, param4)
                       , ZFMP_IN(const zfchar *, param5)
                       )
    {
        zfLogT() << param0 << param1 << param2 << param3 << param4 << param5;
    }
    ZFMETHOD_DECLARE_7(void, methodFor7Param
                       , ZFMP_IN(const zfchar *, param0)
                       , ZFMP_IN(const zfchar *, param1)
                       , ZFMP_IN(const zfchar *, param2)
                       , ZFMP_IN(const zfchar *, param3)
                       , ZFMP_IN(const zfchar *, param4)
                       , ZFMP_IN(const zfchar *, param5)
                       , ZFMP_IN(const zfchar *, param6)
                       )
    {
        zfLogT() << param0 << param1 << param2 << param3 << param4 << param5 << param6;
    }
    ZFMETHOD_DECLARE_8(void, methodFor8Param
                       , ZFMP_IN(const zfchar *, param0)
                       , ZFMP_IN(const zfchar *, param1)
                       , ZFMP_IN(const zfchar *, param2)
                       , ZFMP_IN(const zfchar *, param3)
                       , ZFMP_IN(const zfchar *, param4)
                       , ZFMP_IN(const zfchar *, param5)
                       , ZFMP_IN(const zfchar *, param6)
                       , ZFMP_IN(const zfchar *, param7)
                       )
    {
        zfLogT() << param0 << param1 << param2 << param3 << param4 << param5 << param6 << param7;
    }
};
#if 0 // if opened, all method should be registered statically
    ZFOBJECT_REGISTER(_ZFP_ZFCore_ZFMethod_test_TestBase)
#endif
ZFMETHOD_REGISTER(_ZFP_ZFCore_ZFMethod_test_TestBase, methodStaticallyRegistered)
ZFMETHOD_REGISTER(_ZFP_ZFCore_ZFMethod_test_TestBase, methodOverridedStaticallyRegisteredInBase)
ZFMETHOD_REGISTER(_ZFP_ZFCore_ZFMethod_test_TestBase, methodOverridedStaticallyRegisteredInBaseAndChild)
ZFMETHOD_DEFINE_0(_ZFP_ZFCore_ZFMethod_test_TestBase, void, methodDefinedInCppFile)
{
    zfLogT();
}

// ============================================================
zfclass _ZFP_ZFCore_ZFMethod_test_TestChild : zfextends _ZFP_ZFCore_ZFMethod_test_TestBase
{
    ZFOBJECT_DECLARE(_ZFP_ZFCore_ZFMethod_test_TestChild, _ZFP_ZFCore_ZFMethod_test_TestBase)

public:
    ZFMETHOD_DECLARE_0(void, methodOverrided)
    {
        zfsuper::methodOverrided();
        zfLogT();
    }
    ZFMETHOD_DECLARE_0(void, methodOverridedStaticallyRegisteredInBase)
    {
        zfsuper::methodOverridedStaticallyRegisteredInBase();
        zfLogT();
    }
    ZFMETHOD_DECLARE_0(void, methodOverridedStaticallyRegisteredInBaseAndChild)
    {
        zfsuper::methodOverridedStaticallyRegisteredInBaseAndChild();
        zfLogT();
    }

    ZFMETHOD_DECLARE_0(void, methodInChild)
    {
        zfLogT();
    }
};
#if 0 // if opened, all method should be registered statically
    ZFOBJECT_REGISTER(_ZFP_ZFCore_ZFMethod_test_TestChild)
#endif
ZFMETHOD_REGISTER(_ZFP_ZFCore_ZFMethod_test_TestChild, methodOverridedStaticallyRegisteredInBaseAndChild)

// ============================================================
zfclass ZFCore_ZFMethod_test : zfextends ZFFramework_test_TestCase
{
    ZFOBJECT_DECLARE(ZFCore_ZFMethod_test, ZFFramework_test_TestCase)

protected:
    zfoverride
    virtual void testCaseOnStart(void)
    {
        zfsuper::testCaseOnStart();

        const ZFClass *clsBase = _ZFP_ZFCore_ZFMethod_test_TestBase::ClassData();
        const ZFClass *clsChild = _ZFP_ZFCore_ZFMethod_test_TestChild::ClassData();

        // ============================================================
        this->testCaseOutputSeparator();
        this->testCaseOutput(zfText("ZFMethod registration"));

        this->testCaseOutputSeparator();
        this->testCaseOutput(zfText("method registered before any of instances created:"));

        this->testCaseOutputSeparator();
        this->testCaseOutput(zfText("Base:"));
        this->printMethodInfo(_ZFP_ZFCore_ZFMethod_test_TestBase::ClassData());
        this->testCaseOutput(zfText("Child:"));
        this->printMethodInfo(_ZFP_ZFCore_ZFMethod_test_TestChild::ClassData());

        this->testCaseOutputSeparator();

        this->prepareInstance();
        this->testCaseOutput(zfText("method registered after any of instances created:"));
        this->testCaseOutputSeparator();
        this->testCaseOutput(zfText("Base:"));
        this->printMethodInfo(_ZFP_ZFCore_ZFMethod_test_TestBase::ClassData());
        this->testCaseOutput(zfText("Child:"));
        this->printMethodInfo(_ZFP_ZFCore_ZFMethod_test_TestChild::ClassData());

        // ============================================================
        this->testCaseOutputSeparator();
        this->testCaseOutput(zfText("ZFMethod directly access"));
        this->testCaseOutput(zfText("methodNormal: %s"),
                ZFMethodAccess(_ZFP_ZFCore_ZFMethod_test_TestBase, methodNormal)->objectInfo().cString());
        this->testCaseOutput(zfText("methodStatic: %s"),
                ZFMethodAccess(_ZFP_ZFCore_ZFMethod_test_TestBase, methodStatic)->objectInfo().cString());
        this->testCaseOutput(zfText("methodOverloaded(zfint): %s"),
                ZFMethodAccessDetail_1(_ZFP_ZFCore_ZFMethod_test_TestBase, methodOverloaded, zfint)->objectInfo().cString());
        this->testCaseOutput(zfText("methodOverloaded(zffloat): %s"),
                ZFMethodAccessDetail_1(_ZFP_ZFCore_ZFMethod_test_TestBase, methodOverloaded, zffloat)->objectInfo().cString());

        this->testCaseOutput(zfText("unlike reflected by ZFClass, ZFMethodAccess would comiple error if method not defined"));
#if 0 // this should not able to be compiled
        ZFMethodAccess(_ZFP_ZFCore_ZFMethod_test_TestBase, methodNotDefined);
#endif

        // ============================================================
        this->testCaseOutputSeparator();
        this->testCaseOutput(zfText("ZFMethod reflection"));
        this->testCaseOutput(zfText("call method normally:"));
        this->pBase->methodNormal();
        this->pChild->methodNormal();
        this->pBasePointToChild->methodNormal();

        this->testCaseOutputSeparator();
        this->testCaseOutput(zfText("call by reflect:"));
        clsBase->methodForNameIgnoreParent(zfText("methodNormal"))->execute<void>(this->pBase);
        clsBase->methodForNameIgnoreParent(zfText("methodNormal"))->execute<void>(this->pChild);
        clsBase->methodForNameIgnoreParent(zfText("methodNormal"))->execute<void>(this->pBasePointToChild);

        this->testCaseOutput(zfText("should be null since it's in base only: %p"),
                clsChild->methodForNameIgnoreParent(zfText("methodNormal")));
        this->testCaseOutput(zfText("should not be null since we search hierarchically: %p"),
                clsChild->methodForName(zfText("methodNormal")));
        this->testCaseOutput(zfText("should not be null since it's in child only: %p"),
                clsChild->methodForNameIgnoreParent(zfText("methodInChild")));

        clsChild->methodForName(zfText("methodNormal"))->execute<void>(this->pBase);
        clsChild->methodForName(zfText("methodNormal"))->execute<void>(this->pChild);
        clsChild->methodForName(zfText("methodNormal"))->execute<void>(this->pBasePointToChild);

        // ============================================================
        this->testCaseOutputSeparator();
        this->testCaseOutput(zfText("ZFMethod overloaded method"));

        clsBase->methodForNameIgnoreParent(zfText("methodOverloaded"), zfText("zfint"))->execute<void, zfint>(this->pBase, 123);
        clsBase->methodForNameIgnoreParent(zfText("methodOverloaded"), zfText("zffloat"))->execute<void, zffloat>(this->pBase, 123.456f);

        // ============================================================
        this->testCaseOutputSeparator();
        this->testCaseOutput(zfText("ZFMethod with default param"));

        this->pBase->methodForDefaultParam();
        clsBase->methodForNameIgnoreParent(zfText("methodForDefaultParam"))->execute<void, const zfstring &>(this->pBase,
            zfText("default value not available when reflect"));

        // ============================================================
        this->testCaseOutputSeparator();
        this->testCaseOutput(zfText("ZFMethod special method type"));

        this->testCaseOutput(zfText("reflect static method"));
        clsBase->methodForNameIgnoreParent(zfText("methodStatic"))->executeStatic<void>();
        this->testCaseOutput(zfText("executeStatic(param...) is equal to execute(zfnull, param...)"));
        clsBase->methodForNameIgnoreParent(zfText("methodStatic"))->execute<void>((ZFObject *)zfnull);

        this->testCaseOutputSeparator();

        this->testCaseOutput(zfText("return reference:"));
        this->pBase->s = zfText("oldString");
        this->testCaseOutput(zfText("before: %s"), this->pBase->s.cString());
        clsBase->methodForNameIgnoreParent(zfText("methodReturnReference"))->execute<zfstring &>(this->pBase) = zfText("newString");
        this->testCaseOutput(zfText("after: %s"), this->pBase->s.cString());

        this->testCaseOutputSeparator();

        zfstring _paramReference;
        zfstring &paramReference = _paramReference;
        this->testCaseOutput(zfText("param is reference:"));
        paramReference = zfText("oldString");
        this->testCaseOutput(zfText("before: %s"), paramReference.cString());
        clsBase->methodForNameIgnoreParent(zfText("methodParamIsReference"))->execute<void, zfstring &>(this->pBase, paramReference);
        this->testCaseOutput(zfText("after: %s"), paramReference.cString());

        this->testCaseOutputSeparator();
        this->testCaseOutput(zfText("note that you must specify both ReturnType and ParamType, "));
        this->testCaseOutput(zfText("if not, no compiler would occurred, but app may crash at runtime"));
#if 0
        // invoke method without explicitly specifying the param types
        // this code may or may not crash
        paramReference = zfText("oldString");
        this->testCaseOutput(zfText("these code may have wrong result or crash:"));
        this->testCaseOutput(zfText("before: %s"), paramReference.cString()));
        clsBase->methodForNameIgnoreParent(zfText("methodParamIsReference"))->execute<void>(this->pBase, paramReference);
        this->testCaseOutput(zfText("after: %s"), paramReference.cString()));
#endif

        this->testCaseStop();
    }

private:
    _ZFP_ZFCore_ZFMethod_test_TestBase *pBase;
    _ZFP_ZFCore_ZFMethod_test_TestChild *pChild;
    _ZFP_ZFCore_ZFMethod_test_TestBase *pBasePointToChild;
public:
    zfoverride
    virtual ZFObject *objectOnInit(void)
    {
        zfsuper::objectOnInit();

        this->pBase = zfnull;
        this->pChild = zfnull;
        this->pBasePointToChild = zfnull;
        return this;
    }
    zfoverride
    virtual void objectOnDealloc(void)
    {
        this->destroyInstance();
        zfsuper::objectOnDealloc();
    }
private:
    void prepareInstance(void)
    {
        this->destroyInstance();

        this->pBase = zfAlloc(_ZFP_ZFCore_ZFMethod_test_TestBase);
        this->pChild = zfAlloc(_ZFP_ZFCore_ZFMethod_test_TestChild);
        this->pBasePointToChild = this->pChild;
    }
    void destroyInstance(void)
    {
        zfRelease(this->pBase);
        zfRelease(this->pChild);

        this->pBase = zfnull;
        this->pChild = zfnull;
        this->pBasePointToChild = zfnull;
    }
    void printMethodInfo(const ZFClass *cls, const zfchar *indent = zfText("  "))
    {
        for(zfindex i = 0; i < cls->methodCount(); ++i)
        {
            this->testCaseOutput(zfText("%s%s"), indent, cls->methodAtIndex(i)->objectInfo().cString());
        }
    }
};
ZFOBJECT_REGISTER(ZFCore_ZFMethod_test)

ZF_NAMESPACE_GLOBAL_END

