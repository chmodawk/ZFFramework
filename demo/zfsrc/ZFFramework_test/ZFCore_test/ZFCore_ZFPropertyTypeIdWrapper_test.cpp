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
zfclass ZFCore_ZFPropertyTypeIdWrapper_test : zfextends ZFFramework_test_TestCase
{
    ZFOBJECT_DECLARE(ZFCore_ZFPropertyTypeIdWrapper_test, ZFFramework_test_TestCase)

protected:
    zfoverride
    virtual void testCaseOnStart(void)
    {
        zfsuper::testCaseOnStart();

        ZFObject *v = zfnull;

        zfblockedAlloc(v_zfstring, test_zfstring, zfText("string type"));
        v = test_zfstring;

        // for aliased type, when accessed, a new instance would be created and stored as tag in holder object
        typedef const zfchar * _ZFP_AliasedChar;
        zfLogTrimT() << zfText("============================================================");
        zfLogTrimT() << zfText("const zfchar *");
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedChar>::Value<_ZFP_AliasedChar>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedChar>::Value<const _ZFP_AliasedChar &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedChar>::Value<_ZFP_AliasedChar &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedChar>::Value<_ZFP_AliasedChar *>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedChar>::Value<const _ZFP_AliasedChar *>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedChar>::Value<_ZFP_AliasedChar * &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedChar>::Value<_ZFP_AliasedChar * const &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedChar>::Value<const _ZFP_AliasedChar * &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedChar>::Value<const _ZFP_AliasedChar * const &>::access(v, zfnull);

        // for wrapped type, all should be able to access
        zfLogTrimT() << zfText("============================================================");
        zfLogTrimT() << zfText("zfstring");
        zfLogTrimT() << ZFPropertyTypeIdData<zfstring>::Value<zfstring>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfstring>::Value<const zfstring &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfstring>::Value<zfstring &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfstring>::Value<zfstring *>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfstring>::Value<const zfstring *>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfstring>::Value<zfstring * &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfstring>::Value<zfstring * const &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfstring>::Value<const zfstring * &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfstring>::Value<const zfstring * const &>::access(v, zfnull);

        // zfautoObject processed as normal raw type
        zfblockedAlloc(ZFString, test_String, zfText("zfautoObject"));
        zfblockedAlloc(v_zfautoObject, test_zfautoObject, zfautoObjectCreate(test_String));
        v = test_zfautoObject;
        zfLogTrimT() << zfText("============================================================");
        zfLogTrimT() << zfText("zfautoObject");
        zfLogTrimT() << ZFPropertyTypeIdData<zfautoObject>::Value<zfautoObject>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfautoObject>::Value<const zfautoObject &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfautoObject>::Value<zfautoObject &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfautoObject>::Value<zfautoObject *>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfautoObject>::Value<const zfautoObject *>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfautoObject>::Value<zfautoObject * &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfautoObject>::Value<zfautoObject * const &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfautoObject>::Value<const zfautoObject * &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<zfautoObject>::Value<const zfautoObject * const &>::access(v, zfnull);

        // ZFAny processed as aligned type
        zfblockedAlloc(ZFString, test_ZFAny, zfText("ZFAny"));
        v = test_ZFAny;
        zfLogTrimT() << zfText("============================================================");
        zfLogTrimT() << zfText("ZFAny");
        zfLogTrimT() << ZFPropertyTypeIdData<ZFAny>::Value<ZFAny>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<ZFAny>::Value<const ZFAny &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<ZFAny>::Value<ZFAny &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<ZFAny>::Value<ZFAny *>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<ZFAny>::Value<const ZFAny *>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<ZFAny>::Value<ZFAny * &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<ZFAny>::Value<ZFAny * const &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<ZFAny>::Value<const ZFAny * &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<ZFAny>::Value<const ZFAny * const &>::access(v, zfnull);

        // ZFAnyT processed as aligned type
        zfblockedAlloc(ZFStringEditable, test_ZFAnyT, zfText("ZFAnyT<ZFString *>"));
        v = test_ZFAnyT;
        typedef ZFAnyT<ZFString *> _ZFP_AliasedAnyT;
        zfLogTrimT() << zfText("============================================================");
        zfLogTrimT() << zfText("ZFAnyT<ZFString *>");
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedAnyT>::Value<_ZFP_AliasedAnyT>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedAnyT>::Value<const _ZFP_AliasedAnyT &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedAnyT>::Value<_ZFP_AliasedAnyT &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedAnyT>::Value<_ZFP_AliasedAnyT *>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedAnyT>::Value<const _ZFP_AliasedAnyT *>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedAnyT>::Value<_ZFP_AliasedAnyT * &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedAnyT>::Value<_ZFP_AliasedAnyT * const &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedAnyT>::Value<const _ZFP_AliasedAnyT * &>::access(v, zfnull);
        zfLogTrimT() << ZFPropertyTypeIdData<_ZFP_AliasedAnyT>::Value<const _ZFP_AliasedAnyT * const &>::access(v, zfnull);

        this->testCaseStop();
    }
};
ZFOBJECT_REGISTER(ZFCore_ZFPropertyTypeIdWrapper_test)

ZF_NAMESPACE_GLOBAL_END

