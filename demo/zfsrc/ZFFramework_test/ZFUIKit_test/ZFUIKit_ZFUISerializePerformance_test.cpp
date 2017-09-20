/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFUIKit_test.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfclass _ZFP_ZFUISerializePerformance_test_TestObject : zfextends ZFObject, zfimplements ZFSerializable
{
    ZFOBJECT_DECLARE(_ZFP_ZFUISerializePerformance_test_TestObject, ZFObject)
    ZFIMPLEMENTS_DECLARE(ZFSerializable)

    ZFPROPERTY_RETAIN(_ZFP_ZFUISerializePerformance_test_TestObject *, vObj)

    ZFPROPERTY_ASSIGN(zfstring, v0)
    ZFPROPERTY_ASSIGN(zfstring, v1)
    ZFPROPERTY_ASSIGN(zfstring, v2)
    ZFPROPERTY_ASSIGN(zfstring, v3)
    ZFPROPERTY_ASSIGN(zfstring, v4)
    ZFPROPERTY_ASSIGN(zfstring, v5)
    ZFPROPERTY_ASSIGN(zfstring, v6)
    ZFPROPERTY_ASSIGN(zfstring, v7)
    ZFPROPERTY_ASSIGN(zfstring, v8)
    ZFPROPERTY_ASSIGN(zfstring, v9)
    ZFPROPERTY_ASSIGN(zfstring, v10)
    ZFPROPERTY_ASSIGN(zfstring, v11)
    ZFPROPERTY_ASSIGN(zfstring, v12)
    ZFPROPERTY_ASSIGN(zfstring, v13)
    ZFPROPERTY_ASSIGN(zfstring, v14)
    ZFPROPERTY_ASSIGN(zfstring, v15)

public:
    void modifyProperty(void)
    {
        for(zfindex i = 0; i < 16; ++i)
        {
            zfstring v = zfstringWithFormat(zfText("v%zi"), i);
            zfself::ClassData()->propertyForName(v)
                ->setterMethod()->execute<void, zfstring const &>(this, v);
        }
        this->vObjSet(zflineAlloc(_ZFP_ZFUISerializePerformance_test_TestObject));
        this->vObj()->v0Set(zfText("dummy"));
    }
};

zfclass ZFUIKit_ZFUISerializePerformance_test : zfextends ZFFramework_test_TestCase
{
    ZFOBJECT_DECLARE(ZFUIKit_ZFUISerializePerformance_test, ZFFramework_test_TestCase)

protected:
    zfoverride
    virtual void testCaseOnStart(void)
    {
        zfsuper::testCaseOnStart();
        ZFFramework_test_protocolCheck(ZFUIView)
        ZFFramework_test_protocolCheck(ZFUITextView)
        ZFFramework_test_protocolCheck(ZFUIImage)
        ZFFramework_test_protocolCheck(ZFUIImageView)
        ZFUIWindow *window = zfnull;
        ZFUIView *container = zfnull;
        ZFUIKit_test_prepareTestWindow(window, container, this);

        zfblockedAlloc(ZFUIView, outputViewContainer);
        container->childAdd(outputViewContainer);
        outputViewContainer->layoutParam()->sizeParamSet(ZFUISizeParamFillWidthFillHeight());
        outputViewContainer->layoutParam()->layoutMarginSet(ZFUIMarginMake(0, 50, 0, 0));
        outputViewContainer->viewBackgroundColorSet(ZFUIColorBlack());

        zfblockedAlloc(ZFUITextView, outputView);
        outputViewContainer->childAdd(outputView);
        outputView->layoutParam()->sizeParamSet(ZFUISizeParamFillWidthWrapHeight());
        outputView->textSingleLineSet(zffalse);
        outputView->textColorSet(ZFUIColorWhite());
        outputView->textSet(zfText("press start"));

        zfblockedAlloc(ZFUIKit_test_Button, startButton);
        container->childAdd(startButton);
        startButton->layoutParam()->layoutAlignSet(ZFUIAlign::e_TopInner);
        startButton->buttonLabelTextStringSet(zfText("start"));

        ZFLISTENER_LOCAL_BEGIN(onStart) {
            ZFUIKit_ZFUISerializePerformance_test *owner = userData->tagGet<ZFObjectHolder *>(zfText("owner"))->holdedObj;
            zfautoObject testObject = owner->prepareTestObject();
            ZFUITextView *outputView = userData->tagGet<ZFUITextView *>(zfText("outputView"));
            outputView->textSet(zfText("running..."));
            ZFSerializableData data = ZFObjectToData(testObject);

            zfindex toDataTimes = 1000;
            ZFCoreStatistic::invokeTimeAccurateLogBegin(zfText("ZFUISerializePerformance_test_toData"));
            for(zfindex i = 0; i < toDataTimes; ++i)
            {
                ZFObjectToData(testObject);
            }
            ZFCoreStatistic::invokeTimeAccurateLogEnd(zfText("ZFUISerializePerformance_test_toData"));

            zfindex fromDataTimes = toDataTimes;
            ZFCoreStatistic::invokeTimeAccurateLogBegin(zfText("ZFUISerializePerformance_test_fromData"));
            for(zfindex i = 0; i < fromDataTimes; ++i)
            {
                ZFObjectFromData(data);
            }
            ZFCoreStatistic::invokeTimeAccurateLogEnd(zfText("ZFUISerializePerformance_test_fromData"));

            zfstring result;
            ZFTimeValue toDataUsedTime = ZFCoreStatistic::invokeTimeAccurateGetTotalTime(zfText("ZFUISerializePerformance_test_toData"));
            zfstringAppend(result, zfText("serialize %zi object to data cost %s seconds"),
                toDataTimes,
                ZFTimeValueToStringFriendly(toDataUsedTime).cString());
            result += zfText("\n");
            ZFTimeValue fromDataUsedTime = ZFCoreStatistic::invokeTimeAccurateGetTotalTime(zfText("ZFUISerializePerformance_test_fromData"));
            zfstringAppend(result, zfText("serialize %zi object from data cost %s seconds"),
                fromDataTimes,
                ZFTimeValueToStringFriendly(fromDataUsedTime).cString());
            result += zfText("\ndata:\n");
            ZFXmlPrint(data, ZFOutputCallbackForString(result));
            outputView->textSet(result);

            ZFCoreStatistic::invokeTimeAccurateRemove(zfText("ZFUISerializePerformance_test_toData"));
            ZFCoreStatistic::invokeTimeAccurateRemove(zfText("ZFUISerializePerformance_test_fromData"));
        } ZFLISTENER_LOCAL_END(onStart)
        zfblockedAlloc(ZFObject, userData);
        userData->tagSet(zfText("owner"), this->objectHolder());
        userData->tagSet(zfText("outputView"), outputView);
        startButton->observerAdd(ZFUIButton::EventButtonOnClick(), onStart, userData);

        this->prepareSettingButton(window);
    }

private:
    void prepareSettingButton(ZF_IN ZFUIWindow *window)
    {
        zfblockedAlloc(ZFArrayEditable, settings);

        { // auto scroll x
            zfblockedAlloc(ZFUIKit_test_SettingData, setting);
            settings->add(setting);
            setting->userDataSet(this->objectHolder());
            ZFLISTENER_LOCAL(buttonTextGetter, {
                ZFStringEditable *text = listenerData.param0->to<ZFStringEditable *>();
                text->stringValueSet(zfText("change test object"));
            })
            setting->buttonTextGetterSet(buttonTextGetter);
            ZFLISTENER_LOCAL(buttonClickListener, {
                ZFUIKit_ZFUISerializePerformance_test *t = userData->to<ZFObjectHolder *>()->holdedObj;
                t->testObjectType = ((t->testObjectType + 1) % t->testObjectTypeCount);
            })
            setting->buttonClickListenerSet(buttonClickListener);
        }

        ZFUIKit_test_prepareSettingButtonWithTestWindow(window, settings);
    }

public:
    zfoverride
    virtual ZFObject *objectOnInit(void)
    {
        zfsuper::objectOnInit();
        this->testObjectType = 0;
        this->testObjectTypeCount = 3;
        return this;
    }
    zfindex testObjectType;
    zfindex testObjectTypeCount;
    zfautoObject prepareTestObject(void)
    {
        switch(this->testObjectType)
        {
            case 0:
            {
                zfblockedAlloc(ZFUIKit_test_Button, v);
                v->buttonBackgroundStyle()->viewBackgroundColorSet(ZFUIColorRandom());
                return zfautoObjectCreate(v);
            }
            case 1:
            {
                zfblockedAlloc(ZFUIImageView, v);
                v->imageSet(ZFUIImageLoadFromColor(ZFUIColorRed()).toAny());
                return zfautoObjectCreate(v);
            }
            case 2:
            default:
            {
                zfblockedAlloc(_ZFP_ZFUISerializePerformance_test_TestObject, v);
                v->modifyProperty();
                return zfautoObjectCreate(v);
            }
        }
    }
};
ZFOBJECT_REGISTER(ZFUIKit_ZFUISerializePerformance_test)

ZF_NAMESPACE_GLOBAL_END

