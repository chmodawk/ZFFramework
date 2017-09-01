/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFPropertyType_spec.h
 * @brief type define for ZFProperty
 */

#ifndef _ZFI_ZFPropertyType_spec_h_
#define _ZFI_ZFPropertyType_spec_h_

#include "ZFPropertyType_Core.h"
#include "ZFCallback_common.h"
#include "zfautoObject.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/** @cond ZFPrivateDoc */

// ============================================================
// void
template<>
zfclassNotPOD ZFPropertyTypeIdData<void> : zfextendsNotPOD ZFPropertyTypeIdDataBase
{
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_BASE_EXPAND(ZFAny)
public:
    enum {
        PropertyRegistered = 1,
        PropertyAccessable = 0,
        PropertySerializable = 0,
    };
    static inline const zfchar *PropertyTypeId(void)
    {
        return ZFPropertyTypeId_none;
    }
    template<typename T_Access = zfint>
    zfclassNotPOD Value
    {
    public:
        static zfbool accessAvailable(ZF_IN ZFObject *obj)
        {
            return zffalse;
        }
        static typename zftTraitsType<T_Access>::TraitsType access(ZF_IN ZFObject *obj)
        {
            return typename zftTraitsType<T_Access>::TraitsType();
        }
    };
};

// ============================================================
// ZFObject
ZFM_CLASS_HAS_MEMBER_DECLARE(_ZFP_ZFPropertyTypeIdData, ClassData, const ZFClass * (*F)(void))
template<typename T_Type>
zfclassNotPOD ZFPropertyTypeIdData<T_Type,
        typename zftEnableIf<ZFM_CLASS_HAS_MEMBER(_ZFP_ZFPropertyTypeIdData, ClassData, typename zftTraitsType<T_Type>::TraitsType)>::EnableIf
    > : zfextendsNotPOD ZFPropertyTypeIdDataBase
{
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_BASE_EXPAND(T_Type)
public:
    enum {
        PropertyRegistered = 1,
        PropertyAccessable = 1,
        PropertySerializable = 1,
    };
    static inline const zfchar *PropertyTypeId(void)
    {
        return ZFPropertyTypeId_ZFObject;
    }
    zfoverride
    virtual zfbool propertyWrapperFromSerializableData(ZF_OUT zfautoObject &v,
                                                       ZF_IN const ZFSerializableData &serializableData,
                                                       ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                       ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull) const
    {
        return ZFObjectFromSerializableData(v, serializableData, outErrorHint, outErrorPos);
    }
    zfoverride
    virtual zfbool propertyWrapperToSerializableData(ZF_OUT ZFSerializableData &serializableData,
                                                     ZF_IN ZFObject *v,
                                                     ZF_OUT_OPT zfstring *outErrorHint = zfnull) const
    {
        return ZFObjectToSerializableData(serializableData, v, outErrorHint);
    }
    zfoverride
    virtual zfbool propertyWrapperFromString(ZF_OUT zfautoObject &v,
                                             ZF_IN const zfchar *src,
                                             ZF_IN_OPT zfindex srcLen = zfindexMax()) const
    {
        return ZFObjectFromString(v, src, srcLen);
    }
    zfoverride
    virtual zfbool propertyWrapperToString(ZF_IN_OUT zfstring &s,
                                           ZF_IN ZFObject *v) const
    {
        return ZFObjectToString(s, v);
    }
    static zfbool PropertyFromSerializableData(ZF_OUT zfautoObject &v,
                                               ZF_IN const ZFSerializableData &serializableData,
                                               ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                               ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull)
    {
        return ZFObjectFromSerializableData(v, serializableData, outErrorHint, outErrorPos);
    }
    static zfbool PropertyFromSerializableData(ZF_OUT T_Type &v,
                                               ZF_IN const ZFSerializableData &serializableData,
                                               ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                               ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("not supported"));
        return zffalse;
    }
    static zfbool PropertyToSerializableData(ZF_OUT ZFSerializableData &serializableData,
                                             ZF_IN T_Type const &v,
                                             ZF_OUT_OPT zfstring *outErrorHint = zfnull)
    {
        return ZFObjectToSerializableData(serializableData, ZFCastZFObjectUnchecked(ZFObject *, v), outErrorHint);
    }
    static zfbool PropertyFromString(ZF_OUT zfautoObject &v, ZF_IN const zfchar *src, ZF_IN_OPT zfindex srcLen = zfindexMax())
    {
        return ZFObjectFromString(v, src, srcLen);
    }
    static zfbool PropertyFromString(ZF_OUT T_Type &v, ZF_IN const zfchar *src, ZF_IN_OPT zfindex srcLen = zfindexMax())
    {
        return zffalse;
    }
    static zfbool PropertyToString(ZF_IN_OUT zfstring &s, ZF_IN T_Type const &v)
    {
        return ZFObjectToString(s, ZFCastZFObjectUnchecked(ZFObject *, v));
    }
    static zfbool ValueStore(ZF_OUT zfautoObject &obj, ZF_IN T_Type const &v)
    {
        obj = zfautoObjectCreateWithoutLeakTest(ZFCastZFObjectUnchecked(ZFObject *, v));
        return zftrue;
    }
    template<typename T_Access = T_Type>
    zfclassNotPOD Value
    {
    public:
        static zfbool accessAvailable(ZF_IN ZFObject *obj)
        {
            return !(obj != zfnull && ZFCastZFObject(typename zftTraitsType<T_Type>::TraitsType *, obj) == zfnull);
        }
        static typename zftTraitsType<T_Type>::TraitsType *access(ZF_IN ZFObject *obj)
        {
            return ZFCastZFObject(typename zftTraitsType<T_Type>::TraitsType *, obj);
        }
    };
};

// ============================================================
// ZFAny
template<>
zfclassNotPOD ZFPropertyTypeIdData<ZFAny> : zfextendsNotPOD ZFPropertyTypeIdDataBase
{
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_BASE_EXPAND(ZFAny)
public:
    enum {
        PropertyRegistered = 1,
        PropertyAccessable = 1,
        PropertySerializable = 1,
    };
    static inline const zfchar *PropertyTypeId(void)
    {
        return ZFPropertyTypeId_ZFObject;
    }
    zfoverride
    virtual zfbool propertyWrapperFromSerializableData(ZF_OUT zfautoObject &v,
                                                       ZF_IN const ZFSerializableData &serializableData,
                                                       ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                       ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull) const
    {
        return ZFObjectFromSerializableData(v, serializableData, outErrorHint, outErrorPos);
    }
    zfoverride
    virtual zfbool propertyWrapperToSerializableData(ZF_OUT ZFSerializableData &serializableData,
                                                     ZF_IN ZFObject *v,
                                                     ZF_OUT_OPT zfstring *outErrorHint = zfnull) const
    {
        return ZFObjectToSerializableData(serializableData, v, outErrorHint);
    }
    zfoverride
    virtual zfbool propertyWrapperFromString(ZF_OUT zfautoObject &v,
                                             ZF_IN const zfchar *src,
                                             ZF_IN_OPT zfindex srcLen = zfindexMax()) const
    {
        return ZFObjectFromString(v, src, srcLen);
    }
    zfoverride
    virtual zfbool propertyWrapperToString(ZF_IN_OUT zfstring &s,
                                           ZF_IN ZFObject *v) const
    {
        return ZFObjectToString(s, v);
    }
    static zfbool PropertyFromSerializableData(ZF_OUT zfautoObject &v,
                                               ZF_IN const ZFSerializableData &serializableData,
                                               ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                               ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull)
    {
        return ZFObjectFromSerializableData(v, serializableData, outErrorHint, outErrorPos);
    }
    static zfbool PropertyFromSerializableData(ZF_OUT ZFAny &v,
                                               ZF_IN const ZFSerializableData &serializableData,
                                               ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                               ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("not supported"));
        return zffalse;
    }
    static zfbool PropertyToSerializableData(ZF_OUT ZFSerializableData &serializableData,
                                             ZF_IN ZFAny const &v,
                                             ZF_OUT_OPT zfstring *outErrorHint = zfnull)
    {
        return ZFObjectToSerializableData(serializableData, v.toObject(), outErrorHint);
    }
    static zfbool PropertyFromString(ZF_OUT zfautoObject &v, ZF_IN const zfchar *src, ZF_IN_OPT zfindex srcLen = zfindexMax())
    {
        return ZFObjectFromString(v, src, srcLen);
    }
    static zfbool PropertyFromString(ZF_OUT ZFAny &v, ZF_IN const zfchar *src, ZF_IN_OPT zfindex srcLen = zfindexMax())
    {
        return zffalse;
    }
    static zfbool PropertyToString(ZF_IN_OUT zfstring &s, ZF_IN ZFAny const &v)
    {
        return ZFObjectToString(s, v.toObject());
    }
    static zfbool ValueStore(ZF_OUT zfautoObject &obj, ZF_IN ZFAny const &v)
    {
        obj = zfautoObjectCreateWithoutLeakTest(v.toObject());
        return zftrue;
    }
    static zfbool ValueStore(ZF_OUT zfautoObject &obj, ZF_IN ZFObject *v)
    {
        obj = zfautoObjectCreateWithoutLeakTest(v);
        return zftrue;
    }
    template<typename T_Access = ZFAny>
    zfclassNotPOD Value
    {
    public:
        static zfbool accessAvailable(ZF_IN ZFObject *obj)
        {
            return zftrue;
        }
        static ZFAny access(ZF_IN ZFObject *obj)
        {
            return ZFAny(obj);
        }
    };
};

// ============================================================
// ZFAnyT
template<typename T_Type>
zfclassNotPOD ZFPropertyTypeIdData<ZFAnyT<T_Type> > : zfextendsNotPOD ZFPropertyTypeIdDataBase
{
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_BASE_EXPAND(ZFAnyT<T_Type>)
public:
    enum {
        PropertyRegistered = 1,
        PropertyAccessable = 1,
        PropertySerializable = 1,
    };
    static inline const zfchar *PropertyTypeId(void)
    {
        return ZFPropertyTypeId_ZFObject;
    }
    zfoverride
    virtual zfbool propertyWrapperFromSerializableData(ZF_OUT zfautoObject &v,
                                                       ZF_IN const ZFSerializableData &serializableData,
                                                       ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                                       ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull) const
    {
        return ZFObjectFromSerializableData(v, serializableData, outErrorHint, outErrorPos);
    }
    zfoverride
    virtual zfbool propertyWrapperToSerializableData(ZF_OUT ZFSerializableData &serializableData,
                                                     ZF_IN ZFObject *v,
                                                     ZF_OUT_OPT zfstring *outErrorHint = zfnull) const
    {
        return ZFObjectToSerializableData(serializableData, v, outErrorHint);
    }
    zfoverride
    virtual zfbool propertyWrapperFromString(ZF_OUT zfautoObject &v,
                                             ZF_IN const zfchar *src,
                                             ZF_IN_OPT zfindex srcLen = zfindexMax()) const
    {
        return ZFObjectFromString(v, src, srcLen);
    }
    zfoverride
    virtual zfbool propertyWrapperToString(ZF_IN_OUT zfstring &s,
                                           ZF_IN ZFObject *v) const
    {
        return ZFObjectToString(s, v);
    }
    static zfbool PropertyFromSerializableData(ZF_OUT zfautoObject &v,
                                               ZF_IN const ZFSerializableData &serializableData,
                                               ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                               ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull)
    {
        return ZFObjectFromSerializableData(v, serializableData, outErrorHint, outErrorPos);
    }
    static zfbool PropertyFromSerializableData(ZF_OUT ZFAnyT<T_Type> &v,
                                               ZF_IN const ZFSerializableData &serializableData,
                                               ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                               ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("not supported"));
        return zffalse;
    }
    static zfbool PropertyToSerializableData(ZF_OUT ZFSerializableData &serializableData,
                                             ZF_IN ZFAnyT<T_Type> const &v,
                                             ZF_OUT_OPT zfstring *outErrorHint = zfnull)
    {
        return ZFObjectToSerializableData(serializableData, v.toObject(), outErrorHint);
    }
    static zfbool PropertyFromString(ZF_OUT zfautoObject &v, ZF_IN const zfchar *src, ZF_IN_OPT zfindex srcLen = zfindexMax())
    {
        return ZFObjectFromString(v, src, srcLen);
    }
    static zfbool PropertyFromString(ZF_OUT ZFAnyT<T_Type> &v, ZF_IN const zfchar *src, ZF_IN_OPT zfindex srcLen = zfindexMax())
    {
        return zffalse;
    }
    static zfbool PropertyToString(ZF_IN_OUT zfstring &s, ZF_IN ZFAnyT<T_Type> const &v)
    {
        return ZFObjectToString(s, v.toObject());
    }
    static zfbool ValueStore(ZF_OUT zfautoObject &obj, ZF_IN ZFAnyT<T_Type> const &v)
    {
        obj = zfautoObjectCreateWithoutLeakTest(v.toObject());
        return zftrue;
    }
    static zfbool ValueStore(ZF_OUT zfautoObject &obj, ZF_IN T_Type const &v)
    {
        obj = zfautoObjectCreateWithoutLeakTest(ZFCastZFObjectUnchecked(ZFObject *, v));
        return zftrue;
    }
    template<typename T_Access = ZFAnyT<T_Type> >
    zfclassNotPOD Value
    {
    public:
        static zfbool accessAvailable(ZF_IN ZFObject *obj)
        {
            return !(obj != zfnull && ZFCastZFObject(T_Type, obj) == zfnull);
        }
        static ZFAnyT<T_Type> access(ZF_IN ZFObject *obj)
        {
            return ZFAnyT<T_Type>(ZFCastZFObject(T_Type, obj));
        }
    };
};
/** @endcond */

// ============================================================
// ZFCallerInfo
/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFCallerInfo value="[file function (line)]" />
 * @endcode
 */
ZFPROPERTY_TYPE_DECLARE(ZFCallerInfo, ZFCallerInfoHolder)
ZFOUTPUT_TYPE(ZFCallerInfoHolder, {output.execute(ZFCallerInfoToString(v));})
ZFOUTPUT_TYPE(ZFCallerInfo, {output.execute(ZFCallerInfoToString(ZFCallerInfoHolder(v)));})

/** @cond ZFPrivateDoc */
template<>
zfclassNotPOD ZFPropertyTypeIdData<ZFCallerInfo> : zfextendsNotPOD ZFPropertyTypeIdDataBase
{
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_BASE_EXPAND(ZFCallerInfo)
public:
    enum {
        PropertyRegistered = 1,
        PropertyAccessable = 1,
        PropertySerializable = 0,
    };
    static inline const zfchar *PropertyTypeId(void)
    {
        return ZFPropertyTypeId_ZFCallerInfo();
    }
    zfoverride
    virtual void propertyWrapper(ZF_OUT zfautoObject &v) const
    {
        v_ZFCallerInfo *t = zfAllocWithoutLeakTest(v_ZFCallerInfo);
        v = zfautoObjectCreateWithoutLeakTest(t);
        zfReleaseWithoutLeakTest(t);
    }
    static zfbool PropertyFromSerializableData(ZF_OUT ZFCallerInfo &v,
                                               ZF_IN const ZFSerializableData &serializableData,
                                               ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                               ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("not supported"));
        return zffalse;
    }
    static zfbool PropertyToSerializableData(ZF_OUT ZFSerializableData &serializableData,
                                             ZF_IN ZFCallerInfo const &v,
                                             ZF_OUT_OPT zfstring *outErrorHint = zfnull)
    {
        return ZFCallerInfoToSerializableData(serializableData, v, outErrorHint);
    }
    static zfbool PropertyFromString(ZF_OUT ZFCallerInfo &v, ZF_IN const zfchar *src, ZF_IN_OPT zfindex srcLen = zfindexMax())
    {
        return zffalse;
    }
    static zfbool PropertyToString(ZF_IN_OUT zfstring &s, ZF_IN ZFCallerInfo const &v)
    {
        return ZFCallerInfoToString(s, v);
    }
    static zfbool ValueStore(ZF_OUT zfautoObject &obj, ZF_IN ZFCallerInfo const &v)
    {
        v_ZFCallerInfo *t = zfAllocWithoutLeakTest(v_ZFCallerInfo, v);
        obj = zfautoObjectCreateWithoutLeakTest(t);
        zfReleaseWithoutLeakTest(t);
        return zftrue;
    }
    template<typename T_Access = ZFCallerInfo, typename T_Fix = void>
    zfclassNotPOD Value
    {
        /* not support */
    };
    template<typename T_Fix>
    zfclassNotPOD Value<ZFCallerInfo, T_Fix>
    {
    public:
        static zfbool accessAvailable(ZF_IN ZFObject *obj)
        {
            return ZFPropertyTypeIdData<ZFCallerInfoHolder>::Value<ZFCallerInfoHolder const &>::accessAvailable(obj);
        }
        static ZFCallerInfo access(ZF_IN ZFObject *obj)
        {
            return ZFPropertyTypeIdData<ZFCallerInfoHolder>::Value<ZFCallerInfoHolder const &>::access(obj);
        }
    };
    template<typename T_Fix>
    zfclassNotPOD Value<ZFCallerInfo const &, T_Fix>
    {
    public:
        static zfbool accessAvailable(ZF_IN ZFObject *obj)
        {
            return ZFPropertyTypeIdData<ZFCallerInfoHolder>::Value<ZFCallerInfoHolder const &>::accessAvailable(obj);
        }
        static ZFCallerInfo access(ZF_IN ZFObject *obj)
        {
            return ZFPropertyTypeIdData<ZFCallerInfoHolder>::Value<ZFCallerInfoHolder const &>::access(obj);
        }
    };
};

// ============================================================
// pointer type
template<typename T_Type>
zfclassNotPOD ZFPropertyTypeIdData<T_Type,
        typename zftEnableIf<!ZFM_CLASS_HAS_MEMBER(_ZFP_ZFPropertyTypeIdData, ClassData, typename zftTraitsType<T_Type>::TraitsType)>::EnableIf,
        typename zftEnableIf<zftTraitsType<T_Type>::TypeIsPointer>::EnableIf
    > : zfextendsNotPOD ZFPropertyTypeIdDataBase
{
public:
    typedef typename zftTraitsType<T_Type>::TraitsType T_Type_;
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_BASE_EXPAND(T_Type_)
public:
    enum {
        PropertyRegistered = ZFPropertyTypeIdData<T_Type_>::PropertyRegistered,
        PropertyAccessable = ZFPropertyTypeIdData<T_Type_>::PropertyAccessable,
        PropertySerializable = ZFPropertyTypeIdData<T_Type_>::PropertySerializable,
    };
    static inline const zfchar *PropertyTypeId(void)
    {
        return ZFPropertyTypeIdData<T_Type_>::PropertyTypeId();
    }
    zfoverride
    virtual void propertyWrapper(ZF_OUT zfautoObject &v) const
    {
        ZFPropertyTypeIdData<T_Type_> t;
        t.propertyWrapper(v);
    }
    static zfbool PropertyFromSerializableData(ZF_OUT T_Type_ &v,
                                               ZF_IN const ZFSerializableData &serializableData,
                                               ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                               ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull)
    {
        return ZFPropertyTypeIdData<T_Type_>::PropertyFromSerializableData(v, serializableData, outErrorHint, outErrorPos);
    }
    static zfbool PropertyToSerializableData(ZF_OUT ZFSerializableData &serializableData,
                                             ZF_IN T_Type const &v,
                                             ZF_OUT_OPT zfstring *outErrorHint = zfnull)
    {
        return ZFPropertyTypeIdData<T_Type_>::PropertyToSerializableData(serializableData, (v ? *v : zftValue<T_Type_>().zfv), outErrorHint);
    }
    static zfbool PropertyToSerializableData(ZF_OUT ZFSerializableData &serializableData,
                                             ZF_IN T_Type_ const &v,
                                             ZF_OUT_OPT zfstring *outErrorHint = zfnull)
    {
        return ZFPropertyTypeIdData<T_Type_>::PropertyToSerializableData(serializableData, v, outErrorHint);
    }
    static zfbool PropertyFromString(ZF_OUT T_Type_ &v, ZF_IN const zfchar *src, ZF_IN_OPT zfindex srcLen = zfindexMax())
    {
        return ZFPropertyTypeIdData<T_Type_>::PropertyFromString(v, src, srcLen);
    }
    static zfbool PropertyToString(ZF_IN_OUT zfstring &s, ZF_IN T_Type const &v)
    {
        return ZFPropertyTypeIdData<T_Type_>::PropertyToString(s, (v ? *v : zftValue<T_Type_>().zfv));
    }
    static zfbool PropertyToString(ZF_IN_OUT zfstring &s, ZF_IN T_Type_ const &v)
    {
        return ZFPropertyTypeIdData<T_Type_>::PropertyToString(s, v);
    }
    static zfbool ValueStore(ZF_OUT zfautoObject &obj, T_Type const &v)
    {
        if(v == zfnull)
        {
            obj = zfautoObjectNull();
            return zftrue;
        }
        else
        {
            return ZFPropertyTypeIdData<T_Type_>::ValueStore(obj, *v);
        }
    }
    static zfbool ValueStore(ZF_OUT zfautoObject &obj, T_Type_ const &v)
    {
        return ZFPropertyTypeIdData<T_Type_>::ValueStore(obj, *v);
    }
    template<typename T_Access = T_Type
        , int T_IsPointer = ((zftTraitsType<T_Access>::TypeIsPointer
            && zftTypeIsSame<
                    typename zftTraitsType<T_Access>::TraitsRemoveReference,
                    T_Type_
                >::TypeIsSame != 1)
            ? 1 : 0)
        , typename T_Fix = void
        >
    zfclassNotPOD Value
    {
    public:
        static zfbool accessAvailable(ZF_IN ZFObject *obj)
        {
            return ZFPropertyTypeIdData<T_Type_>::template Value<T_Access>::accessAvailable(obj);
        }
        static T_Access access(ZF_IN ZFObject *obj)
        {
            return ZFPropertyTypeIdData<T_Type_>::template Value<T_Access>::access(obj);
        }
    };
    template<typename T_Access>
    zfclassNotPOD Value<T_Access, 1>
    {
    public:
        static zfbool accessAvailable(ZF_IN ZFObject *obj)
        {
            return ((obj == zfnull) || ZFPropertyTypeIdData<T_Type_>::template Value<T_Access>::accessAvailable(obj));
        }
        static T_Access access(ZF_IN ZFObject *obj)
        {
            return ((obj == zfnull) ? zfnull : ZFPropertyTypeIdData<T_Type_>::template Value<T_Access>::access(obj));
        }
    };
};

/** @endcond */

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFPropertyType_spec_h_

