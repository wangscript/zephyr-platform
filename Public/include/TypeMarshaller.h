#ifndef __ZEPHYR_PUBLIC_TYPE_MARSHALLER_H__
#define __ZEPHYR_PUBLIC_TYPE_MARSHALLER_H__

#include "TypeDef.h"
#include "SysMacros.h"
#include "string.h"
#include <vector>
#include <list>
#include <map>
#include <set>

using namespace std;

namespace Zephyr
{
#ifndef _USE_LINK_2_MARSHALL

#define DECLARE_MARSHALLERS(TYPE) \
    inline TInt32 Marshall(TUChar *pBuffer,TInt32 uBufferLen,TYPE tType) \
    { \
        if (uBufferLen >= sizeof( TYPE )) \
        { \
            *(( TYPE *)pBuffer) = tType; \
            return sizeof( TYPE ); \
        } \
        return OUT_OF_MEM; \
    } \
    TInt32 GetLength(TYPE c) \
    { \
    return sizeof(TYPE); \
    } \
    TInt32 GetLength(TYPE *pC)\
    {\
        return sizeof(TYPE);\
    }


    inline TInt32 Marshall(TUChar *pBuffer,TInt32 uBufferLen,TChar tType) 
    { 
        if (uBufferLen >= sizeof( TChar )) 
        { 
            *(( TChar *)pBuffer) = tType; 
            return sizeof( TChar ); 
        } 
        return OUT_OF_MEM; 
    } 
    TInt32 GetLength(TChar c) 
    { 
        return sizeof(TChar); 
    }
    TInt32 GetLength(TChar *pC);

    TInt32 GetLength(const TChar *pC);

        //IMPL_MARSHALLERS(TInt8) 

    DECLARE_MARSHALLERS(TUChar) 

        //IMPL_MARSHALLERS(TUInt8) 

    DECLARE_MARSHALLERS(TInt16) 

    DECLARE_MARSHALLERS(TUInt16) 

    DECLARE_MARSHALLERS(TInt32) 

    DECLARE_MARSHALLERS(TUInt32) 

    DECLARE_MARSHALLERS(TFloat) 

    DECLARE_MARSHALLERS(TDouble) 

    DECLARE_MARSHALLERS(TInt64) 

    DECLARE_MARSHALLERS(TUInt64) 

    //DECLARE_MARSHALLERS(TBOOL)  
#else

// 
 TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,TUChar ucChar);
// 
// TInt32 GetLength(TUChar c);
// 
 TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,TChar ucChar);
// 
// TInt32 GetLength(TChar c);
// // inline TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,TInt8 nInt8);
// // inline TInt32 Unmarshall(TUChar *pBuffer,TInt32 uBuffLen,TInt8& nInt8);
// // 
// // inline TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,TUInt8 uInt8);
// // inline TInt32 Unmarshall(TUChar *pBuffer,TInt32 uBuffLen,TUInt8& uInt8);
// 
// 
 TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,TInt16 nInt16);
// 
// TInt32 GetLength(TInt16 c);
// 
 TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,TUInt16 uInt16);
// 
// TInt32 GetLength(TUInt16 c);
// 
 TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,TInt32 nInt32);
// 
// TInt32 GetLength(TInt32 c);
// 
 TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,TUInt32 uInt32);
// 
// TInt32 GetLength(TUInt32 c);
// 
 TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,TFloat fFloat);
// 
// TInt32 GetLength(TFloat c);
// 
 TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,TDouble dDouble);
// 
// TInt32 GetLength(TDouble c);
// 
 TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,TInt64 llInt64);
// 
// TInt32 GetLength(TInt64 c);
// 
 TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,TInt64 ullInt64);
// 
// TInt32 GetLength(TInt64 c);
// 
// //inline TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,TBOOL bBool); //Ϊʲô���TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,CDoid *pDoid)��ͻ�أ���
// 
// TInt32 GetLength(TBOOL c);
#endif


TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,const TChar *psz);

template<class TYPE>
TInt32 GetLength(OctSeq<TYPE> &tOctSeq)
{
    return tOctSeq.GetFullLength();
}

template<class TYPE>
TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,OctSeq<TYPE> &tOctSeq)
{
    TInt32 nLength = tOctSeq.GetFullLength();
    if (nLength > uBuffLen)
    {
        return OUT_OF_MEM;
    }
    *((TYPE*)pBuffer) = tOctSeq.m_nBodyLength;
    memcpy((pBuffer+sizeof(TYPE)),tOctSeq.m_pBuffer,tOctSeq.m_nBodyLength);
    return nLength;
}

template<class LENGTH_TYPE,class TAG_TYPE>
TInt32 GetLength(TLV<LENGTH_TYPE,TAG_TYPE> &tTLV)
{
    return tTLV.GetFullLength();
}


template<class LENGTH_TYPE,class TAG_TYPE>
TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,TLV<LENGTH_TYPE,TAG_TYPE> &tTLV)
{
    TInt32 nLength = tTLV.GetFullLength();
    if (nLength > uBuffLen)
    {
        return OUT_OF_MEM;
    }
    *((LENGTH_TYPE*)pBuffer) = tTLV.m_nBodyLength;
    pBuffer += sizeof(LENGTH_TYPE);
    *((TAG_TYPE*)pBuffer) = tTLV.m_nTag;
    pBuffer += sizeof(TAG_TYPE);
    memcpy(pBuffer,tTLV.m_pBuffer,tTLV.m_nBodyLength);
    return nLength;
}

}



template<class TYPE>
TInt32 GetLength(vector<TYPE> &tVector)
{
    TInt32 nLen = tVector.size();
    if (nLen)
    {
        TInt32 nNeed = sizeof(TInt32);
        for(TInt32 i=0;i<nLen;++i)
        {
            nNeed += GetLength(tVector[i]);
        }
        return nNeed;
    }
    else
    {
        return sizeof(TInt32);
    }
}

template<class TYPE>
TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,vector<TYPE> &tVector)
{
    TInt32 nLen = tVector.size();
    *((TInt32*)pBuffer) = nLen;
    if (nLen)
    {
        TInt32 nUsed = sizeof(TInt32);
        for(TInt32 i=0;i<nLen;++i)
        {
            TInt32 nRet = Marshall(pBuffer+nUsed,uBuffLen-nUsed,tVector[i]);
            if (nRet < SUCCESS)
            {
                return nRet;
            }
            nUsed += nRet;
        }
        return nUsed;
    }
    else
    {
        return sizeof(TInt32);
    }
}

template<class TYPE>
TInt32 GetLength(list<TYPE> &tList)
{
    TInt32 nLen = tList.size();
    if (nLen)
    {
        TInt32 nNeed = sizeof(TInt32);
        list<TYPE>::iterator it = tList.begin();
        list<TYPE>::iterator iEnd = tList.end();
        while(it != iEnd)
        {
            nNeed += GetLength(*it);
        }
        return nNeed;
    }
    else
    {
        return sizeof(TInt32);
    }
}

template<class TYPE>
TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,list<TYPE> &tList)
{
    TInt32 nLen = tList.size();
    *((TInt32*)pBuffer) = nLen;
    if (nLen)
    {
        TInt32 nUsed = sizeof(TInt32);
        list<TYPE>::iterator it = tList.begin();
        list<TYPE>::iterator iEnd = tList.end();
        while(it != iEnd)
        {
            TInt32 nRet = GetLength(*it);
            if (nRet < SUCCESS)
            {
                return nRet;
            }
            nUsed += nRet;
        }
        return nUsed;
    }
    else
    {
        return sizeof(TInt32);
    }
}

template<class TYPE>
TInt32 GetLength(set<TYPE> &tSet)
{
    TInt32 nLen = tSet.size();
    if (nLen)
    {
        TInt32 nNeed = sizeof(TInt32);
        set<TYPE>::iterator it = tSet.begin();
        set<TYPE>::iterator iEnd = tSet.end();
        while(it != iEnd)
        {
            nNeed += GetLength(*it);
        }
        return nNeed;
    }
    else
    {
        return sizeof(TInt32);
    }
}

template<class TYPE>
TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,set<TYPE> &tSet)
{
    TInt32 nLen = tSet.size();
    *((TInt32*)pBuffer) = nLen;
    if (nLen)
    {
        TInt32 nUsed = sizeof(TInt32);
        set<TYPE>::iterator it = tSet.begin();
        set<TYPE>::iterator iEnd = tSet.end();
        while(it != iEnd)
        {
            TInt32 nRet = GetLength(*it);
            if (nRet < SUCCESS)
            {
                return nRet;
            }
            nUsed += nRet;
        }
        return nUsed;
    }
    else
    {
        return sizeof(TInt32);
    }
}

template<class CKEY,class TYPE>
TInt32 GetLength(map<CKEY,TYPE> &tMap)
{
    TInt32 nLen = tMap.size();
    if (nLen)
    {
        TInt32 nNeed = sizeof(TInt32);
        map<CKEY,TYPE>::iterator it = tMap.begin();
        map<CKEY,TYPE>::iterator iEnd = tMap.end();
        while(it != iEnd)
        {
            nNeed += GetLength(it->first)
            nNeed += GetLength(it->second);
        }
        return nNeed;
    }
    else
    {
        return sizeof(TInt32);
    }
}

template<class CKEY,class TYPE>
TInt32 Marshall(TUChar *pBuffer,TInt32 uBuffLen,map<CKEY,TYPE> &tMap)
{
    TInt32 nLen = tMap.size();
    *((TInt32*)pBuffer) = nLen;
    if (nLen)
    {
        TInt32 nUsed = sizeof(TInt32);
        map<CKEY,TYPE>::iterator it = tMap.begin();
        map<CKEY,TYPE>::iterator iEnd = tMap.end();
        while(it != iEnd)
        {
            TInt32 nRet = GetLength(it->first);
            if (nRet < SUCCESS)
            {
                return nRet;
            }
            nUsed += nRet;
            nRet = GetLength(it->second);
            if (nRet < SUCCESS)
            {
                return nRet;
            }
            nUsed += nRet;
        }
        return nUsed;
    }
    else
    {
        return sizeof(TInt32);
    }
}

#endif
