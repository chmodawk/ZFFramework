/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFCoreType_methodRegister.h"
#include "ZFPropertyType_CoreType.h"
#include "ZFObjectImpl.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZF_NAMESPACE_GLOBAL_END

#if _ZFP_ZFOBJECT_METHOD_REG
#include "../ZFObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

// ============================================================
// ZFBuffer
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFBuffer, zfbool, bufferMalloc, ZFMP_IN(zfindex, bufferSize))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFBuffer, zfbool, bufferRealloc, ZFMP_IN(zfindex, bufferSize))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFBuffer, void, bufferFree)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFBuffer, void *, bufferGiveUp)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFBuffer, void, bufferSizeSet, ZFMP_IN(zfindex, bufferSize))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_3(v_ZFBuffer, void, bufferSet, ZFMP_IN(void *, buffer), ZFMP_IN(zfindex, bufferSize), ZFMP_IN(zfbool, bufferAutoFree))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFBuffer, zfbool, bufferCopy, ZFMP_IN(const void *, buffer), ZFMP_IN(zfindex, bufferSize))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFBuffer, zfbool, bufferCopy, ZFMP_IN(const zfchar *, s), ZFMP_IN_OPT(zfindex, length, zfindexMax()))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFBuffer, zfbool, bufferCopy, ZFMP_IN(const zfstring &, s))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFBuffer, void *, buffer)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFBuffer, const zfchar *, bufferAsString)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFBuffer, zfindex, bufferAsStringLength)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFBuffer, zfindex, bufferSize)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFBuffer, zfbool, bufferAutoFree)

// ============================================================
// zfCoreArgSplit
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(void, zfCoreArgSplit, ZFMP_OUT(ZFCoreArray<zfstring> &, result), ZFMP_IN(const zfchar *, cmdLine))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(ZFCoreArray<zfstring>, zfCoreArgSplit, ZFMP_IN(const zfchar *, cmdLine))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(void, zfCoreArgMerge, ZFMP_OUT(zfstring &, result), ZFMP_IN(const ZFCoreArray<zfstring> &, argList))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(zfstring, zfCoreArgMerge, ZFMP_IN(const ZFCoreArray<zfstring> &, argList))

// ============================================================
// zfCoreDataEncode
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_0(const zfchar *, zfCoreDataEncodeCharMapDefault)
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_5(void, zfCoreDataEncode, ZFMP_OUT(zfstring &, result), ZFMP_IN(const zfchar *, src), ZFMP_IN_OPT(zfindex, srcLen, zfindexMax()), ZFMP_IN_OPT(const zfchar *, charMap, zfCoreDataEncodeCharMapDefault()), ZFMP_IN_OPT(zfchar, escapeToken, '%'))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_4(void, zfCoreDataDecode, ZFMP_OUT(zfstring &, result), ZFMP_IN(const zfchar *, src), ZFMP_IN_OPT(zfindex, srcLen, zfindexMax()), ZFMP_IN_OPT(zfchar, escapeToken, '%'))

// ============================================================
// ZFIdentityGenerator
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFIdentityGenerator, zfidentity, current)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFIdentityGenerator, zfidentity, next)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFIdentityGenerator, zfidentity, nextMarkUsed)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFIdentityGenerator, zfbool, used, ZFMP_IN(zfidentity, identity))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFIdentityGenerator, void, markUsed, ZFMP_IN(zfidentity, identity))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFIdentityGenerator, void, markUnused, ZFMP_IN(zfidentity, identity))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFIdentityGenerator, void, removeAll)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFIdentityGenerator, void, allUsed, ZFMP_IN_OUT(ZFCoreArray<zfidentity> &, ret))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFIdentityGenerator, ZFCoreArrayPOD<zfidentity>, allUsed)
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfidentity, zfidentityCalcString, ZFMP_IN(const zfchar *, src), ZFMP_IN_OPT(zfindex, srcLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfidentity, zfidentityCalcBuf, ZFMP_IN(const void *, src), ZFMP_IN(zfindex, srcLen))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(zfidentity, zfidentityCalcPointer, ZFMP_IN(const void *, p))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(zfidentity, zfidentityCalcPointer, ZFMP_IN(ZFFuncAddrType, p))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_1(zfidentity, zfidentityCalcPointer, ZFMP_IN(ZFMemberFuncAddrType, p))

// ============================================================
// ZFLevel
ZFEXPORT_ENUM_DEFINE(ZFLevel
    , ZFLevelZFFrameworkStatic
    , ZFLevelZFFrameworkEssential
    , ZFLevelZFFrameworkHigh
    , ZFLevelZFFrameworkNormal
    , ZFLevelZFFrameworkLow
    , ZFLevelAppEssential
    , ZFLevelAppHigh
    , ZFLevelAppNormal
    , ZFLevelAppLow
    , ZFLevelZFFrameworkPostLow
    , ZFLevelZFFrameworkPostNormal
    , ZFLevelZFFrameworkPostHigh
    , ZFLevelZFFrameworkPostEssential
    , ZFLevelZFFrameworkPostStatic
    )

// ============================================================
// ZFCoreStatistic
ZF_NAMESPACE_BEGIN(ZFCoreStatistic)
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_WITH_NS_1(ZFCoreStatistic, void, invokeCountLog, ZFMP_IN(const zfchar *, key))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_WITH_NS_1(ZFCoreStatistic, void, invokeCountRemove, ZFMP_IN(const zfchar *, key))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_WITH_NS_0(ZFCoreStatistic, void, invokeCountRemoveAll)
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_WITH_NS_1(ZFCoreStatistic, zfindex, invokeCountGet, ZFMP_IN(const zfchar *, key))
ZF_NAMESPACE_END(ZFCoreStatistic)

// ============================================================
// zfstring
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_zfstring, void, append, ZFMP_IN(const zfstring &, s))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_3(v_zfstring, void, append, ZFMP_IN(const zfstring &, s), ZFMP_IN(zfindex, pos), ZFMP_IN_OPT(zfindex, len, zfindexMax()))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_zfstring, void, append, ZFMP_IN(const zfchar *, s))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_zfstring, void, append, ZFMP_IN(const zfchar *, s), ZFMP_IN(zfindex, len))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_zfstring, void, assign, ZFMP_IN(const zfstring &, s))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_3(v_zfstring, void, assign, ZFMP_IN(const zfstring &, s), ZFMP_IN(zfindex, pos), ZFMP_IN_OPT(zfindex, len, zfindexMax()))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_zfstring, void, assign, ZFMP_IN(const zfchar *, s))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_zfstring, void, assign, ZFMP_IN(const zfchar *, s), ZFMP_IN(zfindex, len))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_zfstring, void, insert, ZFMP_IN(zfindex, insertAt), ZFMP_IN(const zfstring &, s))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_4(v_zfstring, void, insert, ZFMP_IN(zfindex, insertAt), ZFMP_IN(const zfstring &, s), ZFMP_IN(zfindex, pos), ZFMP_IN_OPT(zfindex, len, zfindexMax()))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_zfstring, void, insert, ZFMP_IN(zfindex, insertAt), ZFMP_IN(const zfchar *, s))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_3(v_zfstring, void, insert, ZFMP_IN(zfindex, insertAt), ZFMP_IN(const zfchar *, s), ZFMP_IN(zfindex, len))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_3(v_zfstring, void, replace, ZFMP_IN(zfindex, replacePos), ZFMP_IN(zfindex, replaceLen), ZFMP_IN(const zfstring &, s))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_5(v_zfstring, void, replace, ZFMP_IN(zfindex, replacePos), ZFMP_IN(zfindex, replaceLen), ZFMP_IN(const zfstring &, s), ZFMP_IN(zfindex, pos), ZFMP_IN_OPT(zfindex, len, zfindexMax()))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_3(v_zfstring, void, replace, ZFMP_IN(zfindex, replacePos), ZFMP_IN(zfindex, replaceLen), ZFMP_IN(const zfchar *, s))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_4(v_zfstring, void, replace, ZFMP_IN(zfindex, replacePos), ZFMP_IN(zfindex, replaceLen), ZFMP_IN(const zfchar *, s), ZFMP_IN(zfindex, len))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_zfstring, zfindex, length)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_zfstring, zfbool, isEmpty)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_zfstring, void, capacitySet, ZFMP_IN(zfindex, capacity))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_zfstring, zfindex, capacity)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_zfstring, void, remove, ZFMP_IN_OPT(zfindex, pos, 0), ZFMP_IN_OPT(zfindex, len, zfindexMax()))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_zfstring, void, removeAll)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_zfstring, zfint, compare, ZFMP_IN(const zfstring &, s))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_zfstring, zfint, compare, ZFMP_IN(const zfchar *, s), ZFMP_IN_OPT(zfindex, len, zfindexMax()))

// ============================================================
// zfstringFind
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_4(zfindex, zfstringFind, ZFMP_IN(const zfchar *, src), ZFMP_IN(zfindex, srcLen), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFind, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfstring &, find))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_3(zfindex, zfstringFind, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFind, ZFMP_IN(const zfstring &, src), ZFMP_IN(zfchar, find))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_4(zfindex, zfstringFindReversely, ZFMP_IN(const zfchar *, src), ZFMP_IN(zfindex, srcLen), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFindReversely, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfstring &, find))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_3(zfindex, zfstringFindReversely, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFindReversely, ZFMP_IN(const zfstring &, src), ZFMP_IN(zfchar, find))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_4(zfindex, zfstringFindCaseInsensitive, ZFMP_IN(const zfchar *, src), ZFMP_IN(zfindex, srcLen), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFindCaseInsensitive, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfstring &, find))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_3(zfindex, zfstringFindCaseInsensitive, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFindCaseInsensitive, ZFMP_IN(const zfstring &, src), ZFMP_IN(zfchar, find))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_4(zfindex, zfstringFindCaseInsensitiveReversely, ZFMP_IN(const zfchar *, src), ZFMP_IN(zfindex, srcLen), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFindCaseInsensitiveReversely, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfstring &, find))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_3(zfindex, zfstringFindCaseInsensitiveReversely, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFindCaseInsensitiveReversely, ZFMP_IN(const zfstring &, src), ZFMP_IN(zfchar, find))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_4(zfindex, zfstringFindFirstOf, ZFMP_IN(const zfchar *, src), ZFMP_IN(zfindex, srcLen), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFindFirstOf, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfstring &, find))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_3(zfindex, zfstringFindFirstOf, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFindFirstOf, ZFMP_IN(const zfstring &, src), ZFMP_IN(zfchar, find))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_4(zfindex, zfstringFindFirstNotOf, ZFMP_IN(const zfchar *, src), ZFMP_IN(zfindex, srcLen), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFindFirstNotOf, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfstring &, find))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_3(zfindex, zfstringFindFirstNotOf, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFindFirstNotOf, ZFMP_IN(const zfstring &, src), ZFMP_IN(zfchar, find))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_4(zfindex, zfstringFindLastOf, ZFMP_IN(const zfchar *, src), ZFMP_IN(zfindex, srcLen), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFindLastOf, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfstring &, find))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_3(zfindex, zfstringFindLastOf, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFindLastOf, ZFMP_IN(const zfstring &, src), ZFMP_IN(zfchar, find))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_4(zfindex, zfstringFindLastNotOf, ZFMP_IN(const zfchar *, src), ZFMP_IN(zfindex, srcLen), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFindLastNotOf, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfstring &, find))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_3(zfindex, zfstringFindLastNotOf, ZFMP_IN(const zfstring &, src), ZFMP_IN(const zfchar *, find), ZFMP_IN_OPT(zfindex, findLen, zfindexMax()))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindex, zfstringFindLastNotOf, ZFMP_IN(const zfstring &, src), ZFMP_IN(zfchar, find))

// ============================================================
// core type
ZFEXPORT_VAR_READONLY_DEFINE(zfindex, zfindexMax, zfindexMax())
ZFEXPORT_VAR_READONLY_DEFINE(zfindex, zfindexZero, zfindexZero())
ZFEXPORT_VAR_READONLY_DEFINE(zfint, zfintZero, zfintZero())
ZFEXPORT_VAR_READONLY_DEFINE(zfuint, zfuintZero, zfuintZero())
ZFEXPORT_VAR_READONLY_DEFINE(zffloat, zffloatZero, zffloatZero())
ZFEXPORT_VAR_READONLY_DEFINE(zfdouble, zfdoubleZero, zfdoubleZero())
ZFEXPORT_VAR_READONLY_DEFINE(zflongdouble, zflongdoubleZero, zflongdoubleZero())
ZFEXPORT_VAR_READONLY_DEFINE(zfbyte, zfbyteZero, zfbyteZero())
ZFEXPORT_VAR_READONLY_DEFINE(zftimet, zftimetZero, zftimetZero())
ZFEXPORT_VAR_READONLY_DEFINE(zfflags, zfflagsZero, zfflagsZero())
ZFEXPORT_VAR_READONLY_DEFINE(zfidentity, zfidentityZero, zfidentityZero())
ZFEXPORT_VAR_READONLY_DEFINE(zfidentity, zfidentityInvalid, zfidentityInvalid())
ZFEXPORT_ENUM_DEFINE(ZFCompareResult, ZFCompareUncomparable, ZFCompareSmaller, ZFCompareTheSame, ZFCompareGreater)
ZFEXPORT_ENUM_DEFINE(ZFSeekPos, ZFSeekPosBegin, ZFSeekPosCur, ZFSeekPosCurReversely, ZFSeekPosEnd)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_zfindexRange, zfindex, start)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_zfindexRange, zfindex, count)

ZFEXPORT_VAR_READONLY_VALUEREF_DEFINE(zfindexRange, zfindexRangeZero, zfindexRangeZero())
ZFEXPORT_VAR_READONLY_VALUEREF_DEFINE(zfindexRange, zfindexRangeMax, zfindexRangeMax())
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfindexRange, zfindexRangeMake, ZFMP_IN(zfindex, start), ZFMP_IN(zfindex, count))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(ZFCompareResult, zfindexRangeIsEqual, ZFMP_IN(const zfindexRange &, e0), ZFMP_IN(const zfindexRange &, e1))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfbool, zfindexRangeContain, ZFMP_IN(const zfindexRange &, range), ZFMP_IN(zfindex, index))

// ============================================================
// zfVersion
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_3(void, zfVersionGet, ZFMP_OUT(zfstring &, ret), ZFMP_IN(const zfchar *, version), ZFMP_IN(zfindex, subVersionIndex))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfstring, zfVersionGet, ZFMP_IN(const zfchar *, version), ZFMP_IN(zfindex, subVersionIndex))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_3(void, zfVersionGetInt, ZFMP_OUT(zfuint &, ret), ZFMP_IN(const zfchar *, version), ZFMP_IN(zfindex, subVersionIndex))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(zfuint, zfVersionGetInt, ZFMP_IN(const zfchar *, version), ZFMP_IN(zfindex, subVersionIndex))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_4(void, zfVersionSet, ZFMP_IN_OUT(zfstring &, version), ZFMP_IN(zfindex, subVersionIndex), ZFMP_IN(const zfchar *, subVersion), ZFMP_IN_OPT(const zfchar *, emptySubVersion, zfText("0")))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_4(void, zfVersionSetInt, ZFMP_IN_OUT(zfstring &, version), ZFMP_IN(zfindex, subVersionIndex), ZFMP_IN(zfuint, subVersion), ZFMP_IN_OPT(const zfchar *, emptySubVersion, zfText("0")))
ZFMETHOD_FUNC_USER_REGISTER_FOR_FUNC_2(ZFCompareResult, zfVersionCompare, ZFMP_IN(const zfchar *, version0), ZFMP_IN(const zfchar *, version1))
ZFEXPORT_VAR_READONLY_DEFINE(zfindex, ZFVERSION_MAIN, ZFVERSION_MAIN())
ZFEXPORT_VAR_READONLY_DEFINE(zfindex, ZFVERSION_SUB, ZFVERSION_SUB())
ZFEXPORT_VAR_READONLY_DEFINE(zfindex, ZFVERSION_MINOR, ZFVERSION_MINOR())
ZFEXPORT_VAR_READONLY_DEFINE(zfindex, ZFVERSION_BUILD, ZFVERSION_BUILD())

// ============================================================
// ZFTokenForContainer
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForContainer, const zfchar *, tokenLeft)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForContainer, const zfchar *, tokenRight)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForContainer, const zfchar *, tokenSeparator)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForContainer, const zfchar *, tokenValueLeft)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForContainer, const zfchar *, tokenValueRight)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForContainer, const zfchar *, tokenEtc)
ZFEXPORT_VAR_READONLY_VALUEREF_DEFINE(ZFTokenForContainer, ZFTokenForContainerTrim, ZFTokenForContainerTrim())
ZFEXPORT_VAR_READONLY_VALUEREF_DEFINE(ZFTokenForContainer, ZFTokenForContainerDetail, ZFTokenForContainerDetail())
ZFEXPORT_VAR_READONLY_VALUEREF_DEFINE(ZFTokenForContainer, ZFTokenForContainerPlainList, ZFTokenForContainerPlainList())
ZFEXPORT_VAR_VALUEREF_DEFINE(ZFTokenForContainer, ZFTokenForContainerDefault, ZFTokenForContainerDefault())

ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForKeyValueContainer, const zfchar *, tokenLeft)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForKeyValueContainer, const zfchar *, tokenRight)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForKeyValueContainer, const zfchar *, tokenSeparator)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForKeyValueContainer, const zfchar *, tokenPairLeft)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForKeyValueContainer, const zfchar *, tokenPairRight)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForKeyValueContainer, const zfchar *, tokenPairSeparator)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForKeyValueContainer, const zfchar *, tokenKeyLeft)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForKeyValueContainer, const zfchar *, tokenKeyRight)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForKeyValueContainer, const zfchar *, tokenValueLeft)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForKeyValueContainer, const zfchar *, tokenValueRight)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_VAR(v_ZFTokenForKeyValueContainer, const zfchar *, tokenEtc)
ZFEXPORT_VAR_READONLY_VALUEREF_DEFINE(ZFTokenForKeyValueContainer, ZFTokenForKeyValueContainerTrim, ZFTokenForKeyValueContainerTrim())
ZFEXPORT_VAR_READONLY_VALUEREF_DEFINE(ZFTokenForKeyValueContainer, ZFTokenForKeyValueContainerDetail, ZFTokenForKeyValueContainerDetail())
ZFEXPORT_VAR_VALUEREF_DEFINE(ZFTokenForKeyValueContainer, ZFTokenForKeyValueContainerDefault, ZFTokenForKeyValueContainerDefault())

// ============================================================
// ZFFilterForNumber
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForNumber, void, copyFrom, ZFMP_IN(ZFFilterForNumber const &, ref))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFFilterForNumber, void, filterAdd, ZFMP_IN(zfint const &, e), ZFMP_IN_OPT(ZFFilterType, filterType, ZFFilterTypeExclude))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFFilterForNumber, void, filterRemove, ZFMP_IN(zfint const &, e), ZFMP_IN_OPT(ZFFilterType, filterType, ZFFilterTypeExclude))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForNumber, void, filterRemoveAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFilterForNumber, void, filterRemoveAll)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFilterForNumber, zfindex, filterCount)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForNumber, zfint, filterGet, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForNumber, ZFFilterType, filterGetFilterType, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForNumber, zfbool, filterCheckActive, ZFMP_IN(zfint const &, e))

// ============================================================
// ZFFilterForIndex
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForIndex, void, copyFrom, ZFMP_IN(ZFFilterForIndex const &, ref))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFFilterForIndex, void, filterAdd, ZFMP_IN(zfindex const &, e), ZFMP_IN_OPT(ZFFilterType, filterType, ZFFilterTypeExclude))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFFilterForIndex, void, filterRemove, ZFMP_IN(zfindex const &, e), ZFMP_IN_OPT(ZFFilterType, filterType, ZFFilterTypeExclude))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForIndex, void, filterRemoveAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFilterForIndex, void, filterRemoveAll)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFilterForIndex, zfindex, filterCount)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForIndex, zfindex, filterGet, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForIndex, ZFFilterType, filterGetFilterType, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForIndex, zfbool, filterCheckActive, ZFMP_IN(zfindex const &, e))

// ============================================================
// ZFFilterForIdentity
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForIdentity, void, copyFrom, ZFMP_IN(ZFFilterForIdentity const &, ref))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFFilterForIdentity, void, filterAdd, ZFMP_IN(zfidentity const &, e), ZFMP_IN_OPT(ZFFilterType, filterType, ZFFilterTypeExclude))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFFilterForIdentity, void, filterRemove, ZFMP_IN(zfidentity const &, e), ZFMP_IN_OPT(ZFFilterType, filterType, ZFFilterTypeExclude))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForIdentity, void, filterRemoveAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFilterForIdentity, void, filterRemoveAll)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFilterForIdentity, zfindex, filterCount)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForIdentity, zfidentity, filterGet, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForIdentity, ZFFilterType, filterGetFilterType, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForIdentity, zfbool, filterCheckActive, ZFMP_IN(zfidentity const &, e))

// ============================================================
// ZFFilterForString
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForString, void, copyFrom, ZFMP_IN(ZFFilterForString const &, ref))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFFilterForString, void, filterAdd, ZFMP_IN(const zfchar *, e), ZFMP_IN_OPT(ZFFilterType, filterType, ZFFilterTypeExclude))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_2(v_ZFFilterForString, void, filterRemove, ZFMP_IN(const zfchar *, e), ZFMP_IN_OPT(ZFFilterType, filterType, ZFFilterTypeExclude))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForString, void, filterRemoveAtIndex, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFilterForString, void, filterRemoveAll)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_0(v_ZFFilterForString, zfindex, filterCount)
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForString, const zfchar *, filterGet, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForString, ZFFilterType, filterGetFilterType, ZFMP_IN(zfindex, index))
ZFMETHOD_USER_REGISTER_FOR_WRAPPER_FUNC_1(v_ZFFilterForString, zfbool, filterCheckActive, ZFMP_IN(const zfchar *, e))

ZF_NAMESPACE_GLOBAL_END
#endif

