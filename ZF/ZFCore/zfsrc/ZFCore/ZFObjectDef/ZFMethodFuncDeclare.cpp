/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFMethodFuncDeclare.h"
#include "ZFClass.h"

#include "ZFCore/ZFSTLWrapper/zfstl_string.h"
#include "ZFCore/ZFSTLWrapper/zfstl_vector.h"
#include "ZFCore/ZFSTLWrapper/zfstl_map.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZF_STATIC_INITIALIZER_INIT(ZFMethodFuncDataHolder)
{
}
zfstlmap<zfstlstringZ, zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> > > methodMap;
ZF_STATIC_INITIALIZER_END(ZFMethodFuncDataHolder)
#define _ZFP_ZFMethodFuncMethodMap ZF_STATIC_INITIALIZER_INSTANCE(ZFMethodFuncDataHolder)->methodMap

void _ZFP_ZFMethodFuncRegister(ZF_IN const ZFMethod *method)
{
    _ZFP_ZFMethodFuncMethodMap
        [method->methodNamespace()]
        [method->methodName()]
        .push_back(method);
}
void _ZFP_ZFMethodFuncUnregister(ZF_IN const ZFMethod *method)
{
    zfstlmap<zfstlstringZ, zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> > > &m = _ZFP_ZFMethodFuncMethodMap;
    zfstlmap<zfstlstringZ, zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> > >::iterator itNS = m.find(method->methodNamespace());
    if(itNS == m.end())
    {
        return ;
    }
    zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> >::iterator itName = itNS->second.find(method->methodName());
    if(itName == itNS->second.end())
    {
        return ;
    }
    zfstlvector<const ZFMethod *> &l = itName->second;
    for(zfstlsize i = 0; i < l.size(); ++i)
    {
        if(l[i] == method)
        {
            l.erase(l.begin() + i);
            if(l.empty())
            {
                itNS->second.erase(itName);
                if(itNS->second.empty())
                {
                    m.erase(itNS);
                }
            }
        }
    }
}

const ZFMethod *ZFMethodFuncGet(ZF_IN const zfchar *methodNamespace,
                                ZF_IN const zfchar *methodName)
{
    zfCoreMutexLocker();
    if(zfscmpTheSame(methodNamespace, zfText("")))
    {
        methodNamespace = ZFMethodFuncNamespaceGlobal;
    }
    zfstlmap<zfstlstringZ, zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> > > &m = _ZFP_ZFMethodFuncMethodMap;
    zfstlmap<zfstlstringZ, zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> > >::iterator itNS = m.find(methodNamespace);
    if(itNS == m.end())
    {
        return zfnull;
    }
    zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> >::iterator itName = itNS->second.find(methodName);
    if(itName == itNS->second.end())
    {
        return zfnull;
    }
    else
    {
        return itName->second[0];
    }
}
const ZFMethod *ZFMethodFuncGet(ZF_IN const zfchar *methodNamespace,
                                ZF_IN const zfchar *methodName
                                , ZF_IN_OPT const zfchar *methodParamTypeId0
                                , ZF_IN_OPT const zfchar *methodParamTypeId1 /* = zfnull */
                                , ZF_IN_OPT const zfchar *methodParamTypeId2 /* = zfnull */
                                , ZF_IN_OPT const zfchar *methodParamTypeId3 /* = zfnull */
                                , ZF_IN_OPT const zfchar *methodParamTypeId4 /* = zfnull */
                                , ZF_IN_OPT const zfchar *methodParamTypeId5 /* = zfnull */
                                , ZF_IN_OPT const zfchar *methodParamTypeId6 /* = zfnull */
                                , ZF_IN_OPT const zfchar *methodParamTypeId7 /* = zfnull */
                                )
{
    zfCoreMutexLocker();
    if(zfscmpTheSame(methodNamespace, zfText("")))
    {
        methodNamespace = ZFMethodFuncNamespaceGlobal;
    }
    zfstlmap<zfstlstringZ, zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> > > &m = _ZFP_ZFMethodFuncMethodMap;
    zfstlmap<zfstlstringZ, zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> > >::iterator itNS = m.find(methodNamespace);
    if(itNS == m.end())
    {
        return zfnull;
    }
    zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> >::iterator itName = itNS->second.find(methodName);
    if(itName == itNS->second.end())
    {
        return zfnull;
    }

    zfstlvector<const ZFMethod *> &l = itName->second;
    for(zfstlsize i = 0; i < l.size(); ++i)
    {
        const ZFMethod *m = l[i];

        #define _ZFP_ZFMethodFuncDeclare_paramLoop(N) \
            if(zfscmpTheSame(methodParamTypeId##N, (const zfchar *)zfnull)) {return m;} \
            if(m->methodParamCount() <= N || !zfscmpTheSame(m->methodParamTypeIdAtIndex(N), methodParamTypeId##N)) {continue;}
        _ZFP_ZFMethodFuncDeclare_paramLoop(0)
        _ZFP_ZFMethodFuncDeclare_paramLoop(1)
        _ZFP_ZFMethodFuncDeclare_paramLoop(2)
        _ZFP_ZFMethodFuncDeclare_paramLoop(3)
        _ZFP_ZFMethodFuncDeclare_paramLoop(4)
        _ZFP_ZFMethodFuncDeclare_paramLoop(5)
        _ZFP_ZFMethodFuncDeclare_paramLoop(6)
        _ZFP_ZFMethodFuncDeclare_paramLoop(7)
        #undef _ZFP_ZFMethodFuncDeclare_paramLoop
        return m;
    }
    return zfnull;
}

void ZFMethodFuncGetAllT(ZF_IN_OUT ZFCoreArray<const ZFMethod *> &ret,
                         ZF_IN_OPT const ZFFilterForZFMethod *filter /* = zfnull */)
{
    zfCoreMutexLocker();

    zfstlmap<zfstlstringZ, zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> > > &m = _ZFP_ZFMethodFuncMethodMap;
    for(zfstlmap<zfstlstringZ, zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> > >::iterator itNS = m.begin();
        itNS != m.end();
        ++itNS)
    {
        for(zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> >::iterator itName = itNS->second.begin();
            itName != itNS->second.end();
            ++itName)
        {
            if(filter == zfnull)
            {
                for(zfstlsize i = 0; i < itName->second.size(); ++i)
                {
                    ret.add(itName->second[i]);
                }
            }
            else
            {
                for(zfstlsize i = 0; i < itName->second.size(); ++i)
                {
                    if(filter->filterCheckActive(itName->second[i]))
                    {
                        ret.add(itName->second[i]);
                    }
                }
            }
        }
    }
}

void ZFMethodFuncGetAllT(ZF_IN_OUT ZFCoreArray<const ZFMethod *> &ret,
                         ZF_IN const zfchar *methodNamespace,
                         ZF_IN const zfchar *methodName,
                         ZF_IN_OPT const ZFFilterForZFMethod *filter /* = zfnull */)
{
    zfCoreMutexLocker();

    zfstlmap<zfstlstringZ, zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> > > &m = _ZFP_ZFMethodFuncMethodMap;
    zfstlmap<zfstlstringZ, zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> > >::iterator itNS = m.find(methodNamespace);
    if(itNS == m.end())
    {
        return ;
    }
    zfstlmap<zfstlstringZ, zfstlvector<const ZFMethod *> >::iterator itName = itNS->second.find(methodName);
    if(itName == itNS->second.end())
    {
        return ;
    }
    if(filter == zfnull)
    {
        for(zfstlsize i = 0; i < itName->second.size(); ++i)
        {
            ret.add(itName->second[i]);
        }
    }
    else
    {
        for(zfstlsize i = 0; i < itName->second.size(); ++i)
        {
            if(filter->filterCheckActive(itName->second[i]))
            {
                ret.add(itName->second[i]);
            }
        }
    }
}

ZF_NAMESPACE_GLOBAL_END

