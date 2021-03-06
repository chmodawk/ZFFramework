/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
/**
 * @file ZFPropertyType_ZFCoreArray.h
 * @brief type define for ZFProperty
 */

#ifndef _ZFI_ZFPropertyType_ZFCoreArray_h_
#define _ZFI_ZFPropertyType_ZFCoreArray_h_

#include "ZFPropertyType_spec.h"
ZF_NAMESPACE_GLOBAL_BEGIN

/** @cond ZFPrivateDoc */

// ============================================================
// ZFCoreArray
/**
 * @brief see #ZFPROPERTY_TYPE_DECLARE
 *
 * serializable data:
 * @code
 *   <ZFCoreArray>
 *       <SomeType />
 *       ... // each element
 *   </ZFCoreArray>
 * @endcode
 *
 * string data:
 * @code
 *   [e0_encoded_string_data, e1_encoded_string_data, ...]
 * @endcode
 */
#define ZFPropertyTypeId_ZFCoreArray() zfText("ZFCoreArray")

/** @brief type wrapper for #ZFPropertyTypeIdData::Value */
zfclass ZF_ENV_EXPORT v_ZFCoreArray : zfextends ZFPropertyTypeWrapper
{
    ZFOBJECT_DECLARE_WITH_CUSTOM_CTOR(v_ZFCoreArray, ZFPropertyTypeWrapper)
public:
    /** @brief the value, see #ZFPropertyTypeIdData::Value */
    ZFCoreArrayBase *zfv;
protected:
    v_ZFCoreArray(void) : zfv(zfnull) {}
protected:
    /** @brief init with value */
    virtual void objectOnInit(ZF_IN const void *v)
    {
        this->objectOnInit();
        this->wrappedValueSet(v);
    }
    /** @brief init with value */
    virtual void objectOnInit(ZF_IN const ZFCoreArrayBase *v)
    {
        this->objectOnInit();
        this->wrappedValueSet(v);
    }
    /** @brief init with value */
    virtual void objectOnInit(ZF_IN ZFCoreArrayBase const &v)
    {
        this->objectOnInit();
        this->wrappedValueSet(v);
    }

    zfoverride
    virtual void objectOnInit(void) {zfsuper::objectOnInit();}
    zfoverride
    virtual void objectOnDealloc(void)
    {
        if(this->zfv != zfnull)
        {
            this->zfv->refDelete();
            this->zfv = zfnull;
        }
        zfsuper::objectOnDealloc();
    }
    zfoverride
    virtual inline void objectInfoOnAppendTokenLeft(ZF_IN_OUT zfstring &ret) {}
    zfoverride
    virtual inline void objectInfoOnAppendTokenRight(ZF_IN_OUT zfstring &ret) {}
    zfoverride
    virtual void objectInfoOnAppend(ZF_IN_OUT zfstring &ret) {}

public:
    zfoverride
    virtual ZFCompareResult objectCompare(ZF_IN ZFObject *anotherObj)
    {
        zfself *t = ZFCastZFObject(zfself *, anotherObj);
        if(t == zfnull)
        {
            return ZFCompareUncomparable;
        }
        else if(this->zfv == zfnull && t->zfv == zfnull)
        {
            return ZFCompareTheSame;
        }
        else if(this->zfv != zfnull && t->zfv != zfnull && this->zfv->refImpl() == t->zfv->refImpl())
        {
            return ZFCompareTheSame;
        }
        else
        {
            return ZFCompareUncomparable;
        }
    }
public:
    zfoverride
    virtual const zfchar *wrappedValueTypeId(void)
    {
        return ZFPropertyTypeId_ZFCoreArray();
    }
    zfoverride
    virtual void *wrappedValue(void) {return this->zfv;}
    zfoverride
    virtual void wrappedValueSet(ZF_IN const void *v)
    {
        ZFCoreArrayBase *t = zfnull;
        if(v != zfnull)
        {
            t = ((const ZFCoreArrayBase *)v)->refNew();
        }
        if(this->zfv != zfnull)
        {
            this->zfv->refDelete();
        }
        this->zfv = t;
    }
    virtual void wrappedValueSet(ZF_IN const ZFCoreArrayBase *v)
    {
        this->wrappedValueSet((const void *)v);
    }
    virtual void wrappedValueSet(ZF_IN const ZFCoreArrayBase &v)
    {
        this->wrappedValueSet((const void *)&v);
    }
public:
    zfoverride
    virtual void wrappedValueReset(void)
    {
        if(this->zfv != zfnull)
        {
            this->zfv->refDelete();
        }
        this->zfv = zfnull;
    }
    zfoverride
    virtual zfbool wrappedValueIsInit(void)
    {
        return (this->zfv == zfnull);
    }
    zfoverride
    virtual ZFCompareResult wrappedValueCompare(ZF_IN const void *v)
    {
        if(this->zfv == zfnull && v == zfnull)
        {
            return ZFCompareTheSame;
        }
        else if(this->zfv != zfnull && v != zfnull && this->zfv->refImpl() == ((const ZFCoreArrayBase *)v)->refImpl())
        {
            return ZFCompareTheSame;
        }
        else
        {
            return ZFCompareUncomparable;
        }
    }
public:
    zfoverride
    virtual zfbool wrappedValueFromData(ZF_IN const ZFSerializableData &serializableData,
                                        ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                        ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData,
            zfText("not available for plain array type"));
        return zffalse;
    }
    zfoverride
    virtual zfbool wrappedValueToData(ZF_OUT ZFSerializableData &serializableData,
                                      ZF_OUT_OPT zfstring *outErrorHint = zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint,
            zfText("not available for plain array type"));
        return zffalse;
    }
    zfoverride
    virtual zfbool wrappedValueFromString(ZF_IN const zfchar *src,
                                          ZF_IN_OPT zfindex srcLen = zfindexMax())
    {
        return zffalse;
    }
    zfoverride
    virtual zfbool wrappedValueToString(ZF_IN_OUT zfstring &s)
    {
        return zffalse;
    }
};

template<typename T_Type>
zfclassNotPOD ZFPropertyTypeIdData<ZFCoreArray<T_Type> > : zfextendsNotPOD ZFPropertyTypeIdDataBase
{
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_BASE_EXPAND(ZFCoreArray<T_Type>)
public:
    enum {
        PropertyRegistered = ZFPropertyTypeIdData<T_Type>::PropertyRegistered,
        PropertySerializable = ZFPropertyTypeIdData<T_Type>::PropertySerializable,
    };
    static inline const zfchar *PropertyTypeId(void)
    {
        return (PropertySerializable ? ZFPropertyTypeId_ZFCoreArray() : ZFPropertyTypeId_none);
    }
    static zfbool ValueStore(ZF_OUT zfautoObject &obj, ZF_IN ZFCoreArray<T_Type> const &v)
    {
        v_ZFCoreArray *holder = zfAllocWithoutLeakTest(v_ZFCoreArray);
        holder->wrappedValueSet(v);
        obj = zfautoObjectCreateWithoutLeakTest(holder);
        zfReleaseWithoutLeakTest(holder);
        return zftrue;
    }
    template<typename T_Access = ZFCoreArray<T_Type>
        , int T_IsPointer = ((zftTraits<T_Access>::TrIsPtr
            && zftTypeIsSame<
                    typename zftTraits<T_Access>::TrNoRef,
                    ZFCoreArray<T_Type>
                >::TypeIsSame != 1)
            ? 1 : 0)
        , typename T_Fix = void
        >
    zfclassNotPOD Value
    {
    public:
        static zfbool accessAvailable(ZF_IN ZFObject *obj, ZF_OUT ZFPropertyTypeValueAccessCallback *accessCallback)
        {
            return (ZFCastZFObject(v_ZFCoreArray *, obj) != zfnull);
        }
        static T_Access access(ZF_IN ZFObject *obj, ZF_IN ZFPropertyTypeValueAccessCallback accessCallback)
        {
            v_ZFCoreArray *holder = ZFCastZFObject(v_ZFCoreArray *, obj);
            if(holder->zfv == zfnull)
            {
                holder->wrappedValueSet(typename zftTraits<T_Access>::TrType());
            }
            return *(typename zftTraits<T_Access>::TrType *)holder->zfv;
        }
    };
    template<typename T_Access>
    zfclassNotPOD Value<T_Access, 1>
    {
    public:
        static zfbool accessAvailable(ZF_IN ZFObject *obj, ZF_OUT ZFPropertyTypeValueAccessCallback *accessCallback)
        {
            return (ZFCastZFObject(v_ZFCoreArray *, obj) != zfnull);
        }
        static typename zftTraits<T_Access>::TrNoRef access(ZF_IN ZFObject *obj, ZF_IN ZFPropertyTypeValueAccessCallback accessCallback)
        {
            v_ZFCoreArray *holder = ZFCastZFObject(v_ZFCoreArray *, obj);
            if(holder->zfv == zfnull)
            {
                holder->wrappedValueSet(typename zftTraits<T_Access>::TrType());
            }
            return (typename zftTraits<T_Access>::TrType *)holder->zfv;
        }
    };
};

template<typename T_Type>
zfclassNotPOD ZFPropertyTypeIdData<ZFCoreArrayPOD<T_Type> > : zfextendsNotPOD ZFPropertyTypeIdDataBase
{
    _ZFP_ZFPROPERTY_TYPE_ID_DATA_BASE_EXPAND(ZFCoreArrayPOD<T_Type>)
public:
    enum {
        PropertyRegistered = ZFPropertyTypeIdData<T_Type>::PropertyRegistered,
        PropertySerializable = ZFPropertyTypeIdData<T_Type>::PropertySerializable,
    };
    static inline const zfchar *PropertyTypeId(void)
    {
        return (PropertySerializable ? ZFPropertyTypeId_ZFCoreArray() : ZFPropertyTypeId_none);
    }
    static zfbool ValueStore(ZF_OUT zfautoObject &obj, ZF_IN ZFCoreArray<T_Type> const &v)
    {
        return ZFPropertyTypeIdData<ZFCoreArray<T_Type> >::ValueStore(obj, v);
    }
    template<typename T_Access = ZFCoreArray<T_Type>
        , int T_IsPointer = ((zftTraits<T_Access>::TrIsPtr
            && zftTypeIsSame<
                    typename zftTraits<T_Access>::TrNoRef,
                    ZFCoreArray<T_Type>
                >::TypeIsSame != 1)
            ? 1 : 0)
        , typename T_Fix = void
        >
    zfclassNotPOD Value
    {
    public:
        static zfbool accessAvailable(ZF_IN ZFObject *obj, ZF_OUT ZFPropertyTypeValueAccessCallback *accessCallback)
        {
            return (ZFCastZFObject(v_ZFCoreArray *, obj) != zfnull);
        }
        static T_Access access(ZF_IN ZFObject *obj, ZF_IN ZFPropertyTypeValueAccessCallback accessCallback)
        {
            v_ZFCoreArray *holder = ZFCastZFObject(v_ZFCoreArray *, obj);
            if(holder->zfv == zfnull)
            {
                holder->wrappedValueSet(typename zftTraits<T_Access>::TrType());
            }
            return *(typename zftTraits<T_Access>::TrType *)holder->zfv;
        }
    };
    template<typename T_Access>
    zfclassNotPOD Value<T_Access, 1>
    {
    public:
        static zfbool accessAvailable(ZF_IN ZFObject *obj, ZF_OUT ZFPropertyTypeValueAccessCallback *accessCallback)
        {
            return (ZFCastZFObject(v_ZFCoreArray *, obj) != zfnull);
        }
        static typename zftTraits<T_Access>::TrNoRef access(ZF_IN ZFObject *obj, ZF_IN ZFPropertyTypeValueAccessCallback accessCallback)
        {
            v_ZFCoreArray *holder = ZFCastZFObject(v_ZFCoreArray *, obj);
            if(holder->zfv == zfnull)
            {
                holder->wrappedValueSet(typename zftTraits<T_Access>::TrType());
            }
            return (typename zftTraits<T_Access>::TrType *)holder->zfv;
        }
    };
};

/** @endcond */

// ============================================================
/** @brief convert array from string */
template<typename T_Type>
zfbool ZFCoreArrayFromString(ZF_OUT ZFCoreArray<T_Type> &v,
                             ZF_IN zfbool (*elementFromString)(
                                 ZF_OUT T_Type &,
                                 ZF_IN const zfchar *,
                                 ZF_IN_OPT zfindex),
                             ZF_IN const zfchar *src,
                             ZF_IN_OPT zfindex srcLen = zfindexMax())
{
    ZFCoreArrayPOD<zfindexRange> pos;
    if(!zfCoreDataPairSplitString(pos, zfindexMax(), src, srcLen, zfText(","), zfText("["), zfText("]"), zftrue))
    {
        return zffalse;
    }
    for(zfindex i = 0; i < pos.count(); ++i)
    {
        zfstring elementString;
        zfCoreDataDecode(elementString, zfstring(src + pos[i].start, pos[i].count));
        zftValue<T_Type> t;
        if(!elementFromString(t.zfv, elementString.cString(), elementString.length()))
        {
            return zffalse;
        }
        v.add(t.zfv);
    }
    return zftrue;
}
/** @brief convert array to string */
template<typename T_Type>
zfbool ZFCoreArrayToString(ZF_OUT zfstring &s,
                           ZF_IN zfbool (*elementToString)(
                               ZF_OUT zfstring &,
                               ZF_IN T_Type const &),
                           ZF_IN ZFCoreArray<T_Type> const &v)
{
    s += zfText("[");
    for(zfindex i = 0; i < v.count(); ++i)
    {
        if(i != 0)
        {
            s += zfText(", ");
        }

        zfstring elementString;
        if(!elementToString(elementString, v[i]))
        {
            return zffalse;
        }
        zfCoreDataEncode(s, elementString.cString(), elementString.length());
    }
    s += zfText("]");
    return zftrue;
}
/** @brief convert array to string */
template<typename T_Type>
zfstring ZFCoreArrayToString(ZF_IN ZFCoreArray<T_Type> const &v,
                             ZF_IN zfbool (*elementToString)(
                                 ZF_OUT zfstring &ret,
                                 ZF_IN T_Type const &))
{
    zfstring ret;
    if(ZFCoreArrayToString(ret, v, elementToString))
    {
        return ret;
    }
    else
    {
        return zfstring();
    }
}

// ============================================================
/** @brief convert array from serializable data */
template<typename T_Type>
zfbool ZFCoreArrayFromData(ZF_OUT ZFCoreArray<T_Type> &v,
                           ZF_IN zfbool (*elementFromData)(
                               ZF_OUT T_Type &,
                               ZF_IN const ZFSerializableData &,
                               ZF_OUT_OPT zfstring *outErrorHint,
                               ZF_OUT_OPT ZFSerializableData *),
                           ZF_IN const ZFSerializableData &serializableData,
                           ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                           ZF_OUT_OPT ZFSerializableData *outErrorPos = zfnull)
{
    v.removeAll();

    if(!ZFSerializableUtil::requireSerializableClass(ZFPropertyTypeId_ZFCoreArray(), serializableData, outErrorHint, outErrorPos))
    {
        return zffalse;
    }

    for(zfindex i = 0; i < serializableData.elementCount(); ++i)
    {
        const ZFSerializableData &element = serializableData.elementAtIndex(i);
        if(element.resolved())
        {
            continue;
        }

        zftValue<T_Type> t;
        if(!elementFromData(t.zfv, element, outErrorHint, outErrorPos))
        {
            return zffalse;
        }
        v.add(t.zfv);
    }

    return zftrue;
}
/** @brief convert array to serializable data */
template<typename T_Type>
zfbool ZFCoreArrayToData(ZF_OUT ZFSerializableData &serializableData,
                         ZF_IN zfbool (*elementToData)(
                             ZF_OUT ZFSerializableData &,
                             ZF_IN T_Type const &,
                             ZF_OUT_OPT zfstring *outErrorHint),
                         ZF_IN ZFCoreArray<T_Type> const &v,
                         ZF_OUT_OPT zfstring *outErrorHint = zfnull)
{
    serializableData.itemClassSet(ZFPropertyTypeId_ZFCoreArray());
    for(zfindex i = 0; i < v.count(); ++i)
    {
        ZFSerializableData element;
        if(!elementToData(element, v[i], outErrorHint))
        {
            return zffalse;
        }
        serializableData.elementAdd(element);
    }
    return zftrue;
}
/** @brief convert array to serializable data */
template<typename T_Type>
ZFSerializableData ZFCoreArrayToData(ZF_IN ZFCoreArray<T_Type> const &v,
                                     ZF_IN zfbool (*elementToData)(
                                         ZF_OUT ZFSerializableData &,
                                         ZF_IN T_Type const &,
                                         ZF_OUT_OPT zfstring *outErrorHint),
                                     ZF_OUT_OPT zfstring *outErrorHint = zfnull)
{
    ZFSerializableData ret;
    if(ZFCoreArrayToData(ret, elementToData, v, outErrorHint))
    {
        return ret;
    }
    else
    {
        return ZFSerializableData();
    }
}

ZF_NAMESPACE_GLOBAL_END
#endif // #ifndef _ZFI_ZFPropertyType_ZFCoreArray_h_

