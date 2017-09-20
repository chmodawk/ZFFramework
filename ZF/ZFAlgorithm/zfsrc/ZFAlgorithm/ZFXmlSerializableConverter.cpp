/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFXmlSerializableConverter.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFSERIALIZABLEDATA_REFERENCE_TYPE_DEFINE(ZFSerializableDataRefTypeId_xml)
{
    ZFXmlItem xmlElement = ZFXmlParseFirstElement(ZFInputCallbackForFileDescriptor(refData));
    if(xmlElement.xmlType() == ZFXmlType::e_XmlNull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint,
            zfText("failed to load xml element from \"%s\""), refData);
        return zffalse;
    }
    return ZFXmlParseToData(serializableData, xmlElement);
}

ZFOBJECT_CREATOR_DEFINE(ZFObjectCreatorTypeId_xml, data)
{
    ZFXmlItem xmlElement = ZFXmlParseFirstElement(ZFInputCallbackForFileDescriptor(data));
    if(xmlElement.xmlIsNull())
    {
        return zfautoObjectNull();
    }
    ZFSerializableData serializableData;
    if(ZFXmlParseToData(serializableData, xmlElement))
    {
        return ZFObjectFromData(serializableData);
    }
    return zfautoObjectNull();
}

static zfbool _ZFP_ZFXmlParseToData(ZF_OUT ZFSerializableData &serializableData,
                                    ZF_IN const ZFXmlItem &xmlElement,
                                    ZF_OUT_OPT zfstring *outErrorHint = zfnull,
                                    ZF_OUT_OPT ZFXmlItem *outErrorPos = zfnull)
{
    if(xmlElement.xmlIsNull())
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, zfText("null xml element"));
        if(outErrorPos != zfnull)
        {
            *outErrorPos = xmlElement;
        }
        return zffalse;
    }
    if(xmlElement.xmlType() != ZFXmlType::e_XmlElement)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, zfText("param not type of xml element"));
        if(outErrorPos != zfnull)
        {
            *outErrorPos = xmlElement;
        }
        return zffalse;
    }

    if(xmlElement.xmlName() == zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, zfText("missing xml node name"));
        if(outErrorPos != zfnull)
        {
            *outErrorPos = xmlElement;
        }
        return zffalse;
    }
    serializableData.itemClassSet(xmlElement.xmlName());

    ZFXmlItem attribute = xmlElement.xmlAttributeFirst();
    while(!attribute.xmlIsNull())
    {
        if(attribute.xmlName() == zfnull)
        {
            ZFSerializableUtil::errorOccurred(outErrorHint, zfText("missing xml attribute name"));
            if(outErrorPos != zfnull)
            {
                *outErrorPos = attribute;
            }
            return zffalse;
        }
        if(zfscmpTheSame(attribute.xmlName(), ZFSerializableKeyword_refType))
        {
            serializableData.referenceRefTypeSet(attribute.xmlValue());
        }
        else if(zfscmpTheSame(attribute.xmlName(), ZFSerializableKeyword_refData))
        {
            serializableData.referenceRefDataSet(attribute.xmlValue());
        }
        else
        {
            serializableData.attributeSet(attribute.xmlName(), attribute.xmlValue());
        }

        attribute = attribute.xmlAttributeNext();
    }

    ZFXmlItem element = xmlElement.xmlChildElementFirst();
    while(!element.xmlIsNull())
    {
        ZFSerializableData childData;
        if(!_ZFP_ZFXmlParseToData(childData, element, outErrorHint, outErrorPos))
        {
            return zffalse;
        }
        serializableData.elementAdd(childData);
        element = element.xmlSiblingElementNext();
    }

    return zftrue;
}
ZFMETHOD_FUNC_DEFINE_4(zfbool, ZFXmlParseToData,
                       ZFMP_OUT(ZFSerializableData &, serializableData),
                       ZFMP_IN(const ZFXmlItem &, xmlElement),
                       ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull),
                       ZFMP_OUT_OPT(ZFXmlItem *, outErrorPos, zfnull))
{
    return _ZFP_ZFXmlParseToData(serializableData, xmlElement, outErrorHint, outErrorPos)
        && serializableData.referenceInfoLoad();
}
ZFMETHOD_FUNC_DEFINE_3(ZFSerializableData, ZFXmlParseToData,
                       ZFMP_IN(const ZFXmlItem &, xmlElement),
                       ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull),
                       ZFMP_OUT_OPT(ZFXmlItem *, outErrorPos, zfnull))
{
    ZFSerializableData ret;
    if(ZFXmlParseToData(ret, xmlElement, outErrorHint, outErrorPos))
    {
        return ret;
    }
    else
    {
        return ZFSerializableData();
    }
}
ZFMETHOD_FUNC_DEFINE_4(zfbool, ZFXmlPrintFromData,
                       ZFMP_OUT(ZFXmlItem &, xmlElement),
                       ZFMP_IN(const ZFSerializableData &, serializableData),
                       ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull),
                       ZFMP_OUT_OPT(ZFSerializableData *, outErrorPos, zfnull))
{
    xmlElement = ZFXmlPrintFromData(serializableData, outErrorHint, outErrorPos);
    return (xmlElement.xmlType() != ZFXmlType::e_XmlNull);
}
ZFMETHOD_FUNC_DEFINE_3(ZFXmlItem, ZFXmlPrintFromData,
                       ZFMP_IN(const ZFSerializableData &, serializableData),
                       ZFMP_OUT_OPT(zfstring *, outErrorHint, zfnull),
                       ZFMP_OUT_OPT(ZFSerializableData *, outErrorPos, zfnull))
{
    if(serializableData.itemClass() == zfnull)
    {
        ZFSerializableUtil::errorOccurred(outErrorHint, outErrorPos, serializableData, zfText("missing serializable class"));
        return ZFXmlItem();
    }

    ZFXmlItem ret(ZFXmlType::e_XmlElement);
    ret.xmlNameSet(serializableData.itemClass());

    if(serializableData.referenceRefType() != zfnull)
    {
        ret.xmlAttributeAdd(ZFSerializableKeyword_refType, serializableData.referenceRefType());
    }
    if(serializableData.referenceRefData() != zfnull)
    {
        ret.xmlAttributeAdd(ZFSerializableKeyword_refData, serializableData.referenceRefData());
    }

    for(zfiterator it = serializableData.attributeIterator();
        serializableData.attributeIteratorIsValid(it);
        serializableData.attributeIteratorNext(it))
    {
        ret.xmlAttributeAdd(serializableData.attributeIteratorGetKey(it),
            serializableData.attributeIteratorGet(it));
    }

    for(zfindex i = 0; i < serializableData.elementCount(); ++i)
    {
        ZFXmlItem child = ZFXmlPrintFromData(serializableData.elementAtIndex(i), outErrorHint, outErrorPos);
        if(child.xmlType() == ZFXmlType::e_XmlNull)
        {
            return ZFXmlItem();
        }
        ret.xmlChildAdd(child);
    }

    return ret;
}

ZFMETHOD_FUNC_DEFINE_3(void, ZFXmlPrint,
                       ZFMP_IN(const ZFSerializableData &, serializableData),
                       ZFMP_IN_OPT(const ZFOutputCallback &, outputCallback, ZFOutputCallbackDefault()),
                       ZFMP_IN_OPT(const ZFXmlOutputFlags &, flags, ZFXmlOutputFlagsDefault()))
{
    ZFXmlItem xmlElement = ZFXmlPrintFromData(serializableData);
    if(xmlElement.xmlType() != ZFXmlType::e_XmlNull)
    {
        xmlElement.xmlAttributeSortRecursively();
        ZFXmlItemToOutput(outputCallback, xmlElement, flags);
        outputCallback.execute(zfText("\n"));
    }
}
ZFMETHOD_FUNC_DEFINE_3(void, ZFXmlPrint,
                       ZFMP_IN(ZFObject *, obj),
                       ZFMP_IN_OPT(const ZFOutputCallback &, outputCallback, ZFOutputCallbackDefault()),
                       ZFMP_IN_OPT(const ZFXmlOutputFlags &, flags, ZFXmlOutputFlagsDefault()))
{
    ZFXmlPrint(ZFObjectToData(obj), outputCallback, flags);
}

// ============================================================
ZFMETHOD_FUNC_DEFINE_2(zfbool, ZFXmlParse,
                       ZFMP_OUT(ZFSerializableData &, ret),
                       ZFMP_IN(const ZFInputCallback &, input))
{
    if(!input.callbackIsValid())
    {
        return zffalse;
    }
    ZFXmlItem xmlElement = ZFXmlParseFirstElement(input);
    if(xmlElement.xmlType() == ZFXmlType::e_XmlNull)
    {
        return zffalse;
    }
    if(!ZFXmlParseToData(ret, xmlElement))
    {
        return zffalse;
    }

    ret.pathInfoSet(input.pathType(), input.pathInfo());
    return zftrue;
}
ZFMETHOD_FUNC_DEFINE_1(ZFSerializableData, ZFXmlParse,
                       ZFMP_IN(const ZFInputCallback &, input))
{
    ZFSerializableData ret;
    if(ZFXmlParse(ret, input))
    {
        return ret;
    }
    else
    {
        return ZFSerializableData();
    }
}

ZF_NAMESPACE_GLOBAL_END

