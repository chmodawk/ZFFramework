/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFToken.h"

ZF_NAMESPACE_GLOBAL_BEGIN

const ZFTokenForContainer _ZFP_ZFTokenForContainerTrim;

const ZFTokenForContainer _ZFP_ZFTokenForContainerDetail(
          zfText("[\n    ") // tokenLeft
        , zfText("\n]")     // tokenRight
        , zfText(",\n    ") // tokenSeparator
        , zfText("")        // tokenValueLeft
        , zfText("")        // tokenValueRight
        , zfText("...")     // tokenEtc
    );

const ZFTokenForContainer _ZFP_ZFTokenForContainerPlainList(
          zfText("")        // tokenLeft
        , zfText("")        // tokenRight
        , zfText("\n")      // tokenSeparator
        , zfText("")        // tokenValueLeft
        , zfText("")        // tokenValueRight
        , zfText("...")     // tokenEtc
    );

ZFTokenForContainer _ZFP_ZFTokenForContainerDefault = ZFTokenForContainerTrim();

// ============================================================
const ZFTokenForKeyValueContainer _ZFP_ZFTokenForKeyValueContainerTrim;
const ZFTokenForKeyValueContainer _ZFP_ZFTokenForKeyValueContainerDetail(
          zfText("{\n    ") // tokenLeft
        , zfText("\n}")     // tokenRight
        , zfText(",\n    ") // tokenSeparator
        , zfText("")        // tokenPairLeft
        , zfText("")        // tokenPairRight
        , zfText(" = ")     // tokenPairSeparator
        , zfText("")        // tokenKeyLeft
        , zfText("")        // tokenKeyRight
        , zfText("")        // tokenValueLeft
        , zfText("")        // tokenValueRight
        , zfText("...")     // tokenEtc
    );
ZFTokenForKeyValueContainer _ZFP_ZFTokenForKeyValueContainerDefault = ZFTokenForKeyValueContainerTrim();

ZF_NAMESPACE_GLOBAL_END

