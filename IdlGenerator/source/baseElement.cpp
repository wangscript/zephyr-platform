#include "../include/baseElement.h"

namespace Zephyr
{

IMPLEMENT_STATIC_CLASS_POOL(CBaseElement)



TplMap<TplPtPack<CBaseElement,string >,string> *CBaseElement::sm_pBaseElements = NULL;
TplMap<TplPtPack<CBaseElement,string >,string> *CBaseElement::sm_pBaseKeyWords = NULL;

TInt32   CBaseElement::AddType(CBaseElement *pBaseElement)
{
    TplPtPack<CBaseElement,string > *pItem = sm_pBaseElements->PrepareItem();
    if (pItem)
    {
        (*pItem).m_pPt = pBaseElement;
        int nRet = sm_pBaseElements->AddInTree(pItem);
        if (nRet < SUCCESS)
        {
            sm_pBaseElements->ReleaseItem(pItem);
            return nRet;
        }
        return SUCCESS;
    }
    return OUT_OF_MEM;
}

TInt32   CBaseElement::AddBaseType(const char *psz)
{
    CBaseElement *pBase = CREATE_FROM_STATIC_POOL(CBaseElement);
    if (!pBase)
    {
        return OUT_OF_MEM;
    }
    pBase->SetName(psz);
    return AddType(pBase);
}

CBaseElement *CBaseElement::IsOneType(const char *psz)
{
    string key = psz;
    TplPtPack<CBaseElement,string > *pElePack = sm_pBaseElements->GetItemByKey(&key);
    if (pElePack)
    {
        return pElePack->m_pPt;
    }
    return NULL;
}

TInt32   CBaseElement::AddKeyWords(const char *pName,EnKeyWords key)
{
    TplPtPack<CBaseElement,string > *pItem = sm_pBaseKeyWords->PrepareItem();
    if (pItem)
    {
        CBaseElement *pElem = CREATE_FROM_STATIC_POOL(CBaseElement);
        pElem->m_szName = pName;
        pElem->m_nElmentType = key;
        (*pItem).m_pPt = pElem;
        int nRet = sm_pBaseKeyWords->AddInTree(pItem);
        if (nRet < SUCCESS)
        {
            RELEASE_INTO_STATIC_POOL(CBaseElement,pElem);
            return nRet;
        }
        return SUCCESS;
    }
    return OUT_OF_MEM;
}

CBaseElement *CBaseElement::IsKeyWords(const char *psz)
{
    string str = psz;
    TplPtPack<CBaseElement,string > *pElePack = sm_pBaseKeyWords->GetItemByKey(&str);
    if (pElePack)
    {
        return pElePack->m_pPt;
    }
    return NULL;
}




TInt32 CBaseElement::IgnorType(char **ppElements,EnType *pTypes,int nProcess2,int nTotalEles,EnType eType)
{
    TInt32 nRet = 0;
    TInt32 total = nTotalEles - nProcess2;
    while (nRet < total)
    {
        EnType e = pTypes[nProcess2+nRet];
        if (e != eType)
        {
            return nRet;
        }
        ++nRet;
    }
    return nRet;
}

TInt32 CBaseElement:: Process(char **ppElements,EnType *pTypes,int nProcess2,int nTotalEles)
{
    return 0;
}

const char *CBaseElement::GetHierachyName()
{
    return m_szName.c_str();
}

void CBaseElement::MakeOneWords(char **ppWords,int nFrom,int nWordsNr)
{
    if (nWordsNr>0)
    {
        --nWordsNr;
        for (int i=1;i<nWordsNr;++i)
        {
            int nLen = strlen(ppWords[nFrom+i]);
            memmove(ppWords[nFrom+i]-i,ppWords[nFrom+i],nLen);
        }
        int nLen = strlen(ppWords[nFrom+nWordsNr])+1;
        memmove(ppWords[nFrom+nWordsNr]-nWordsNr,ppWords[nFrom+nWordsNr],nLen);
    }
}


TInt32 CBaseElement::IgnorTypes(char **ppElements,EnType *pTypes,int nProcess2,int nTotalEles,int nrOfType,EnType eIgnoreTypes[])
{
    TInt32 nRet = 0;
    TInt32 total = nTotalEles - nProcess2;
    while (nRet < total)
    {
        EnType e = pTypes[nProcess2+nRet];
        bool bNotIgnore = true;
        for (int i=0;i<nrOfType;++i)
        {
            if (e==eIgnoreTypes[i])
            {
                bNotIgnore = false;
                break;
            }
        }
        if (bNotIgnore)
        {
            return nRet;;
        }
        ++nRet;
    }
    return nRet;
}

void CBaseElement::AddChildElement(CBaseElement *pElement)
{
    TplPtPack<CBaseElement,string> t;
    t.m_pPt = pElement;
    m_tChilds.push_back(t);
}

bool CBaseElement::IsBracesBegin(char *pStr,EnType nType)
{
    if (operator_type == nType)
    {
        if (pStr[0] == '{')
        {
            return true;
        }
    }
    return false;
}

bool CBaseElement::IsBracesEnd(char *pStr,EnType nType)
{
    if (operator_type == nType)
    {
        if (pStr[0] == '}')
        {
            return true;
        }
    }
    return false;
}


void CBaseElement::OnError(TInt32 nErr)
{
    printf("OnError %d",nErr);
}

}