#include "../include/IfAuthServiceSkeleton.h"
#include "Public/include/TypeUnmarshaller.h"
#include "../include/IfAuthServiceMethodId.h"
namespace Zephyr 
{
TInt32 IfAuthServiceSkeleton::HandleMsg(CMessageHeader *pMsg)
{
    typedef TInt32 (IfAuthServiceSkeleton::*_PFMSG)(CMessageHeader *); 
    struct _MSGMAP_ENTRY { TUInt32 m_uMsgID; _PFMSG m_pHandlerFunc; };
    static _MSGMAP_ENTRY sMsgMapEntries[] = 
    {
        {IFAUTHSERVICE_INTERFACE_ID, &IfAuthServiceSkeleton::HandleAuthenticate_TUInt32_TChar_pt_TChar_pt},
        {IFAUTHSERVICE_INTERFACE_ID, &IfAuthServiceSkeleton::HandleOnDisconneted_CDoid},
    };
    TInt32 nBegin = 0;
    TInt32 nEnd = 2;
    TUInt32 nMethodId = pMsg->GetMethodId();
    _PFMSG pPfMsg = NULL;
    while(nBegin < nEnd)
    {
        if (nBegin == (nEnd -1))
        {
            if (sMsgMapEntries[nBegin].m_uMsgID == nMethodId)
            {
                pPfMsg=sMsgMapEntries[nBegin].m_pHandlerFunc;
            }
            else if (sMsgMapEntries[nEnd].m_uMsgID == nMethodId)
            {
                pPfMsg=sMsgMapEntries[nEnd].m_pHandlerFunc;
            }
            break;
        }
        TInt32 nMiddle = (nBegin + nEnd) >> 1;
        TUInt32 nMiddleVal = sMsgMapEntries[nMiddle].m_uMsgID;
        if (nMiddleVal == nMethodId)
        {
            pPfMsg = sMsgMapEntries[nMiddle].m_pHandlerFunc;
            break;
        }
        else
        {
            if (nMiddleVal>nMethodId)
            {
                nEnd = nMiddle;
            }
            else
            {
                nBegin   = nMiddle;
            }
        }
    }
    if (NULL == pPfMsg)
    {
        return CAN_NOT_HANDLE_THIS_MSG;
    }
    return (this->*pPfMsg)(pMsg);
}; 
TInt32 IfAuthServiceSkeleton::HandleAuthenticate_TUInt32_TChar_pt_TChar_pt(CMessageHeader *pMsg)
{
    TInt32 nLen = pMsg->GetBodyLength();
    TUChar *pBuffer =pMsg->GetBody();
    TInt32 nRet;
    TUInt32 _uIp;
    nRet = Unmarshall(pBuffer,nLen,_uIp);
    if (nRet<SUCCESS)
    {
        pBuffer += nRet;
        nLen -= nRet;
    }
    else
    {
        return nRet;
    }
    TChar *_pszName;
    nRet = Unmarshall(pBuffer,nLen,_pszName);
    if (nRet<SUCCESS)
    {
        pBuffer += nRet;
        nLen -= nRet;
    }
    else
    {
        return nRet;
    }
    TChar *_pszPwd;
    nRet = Unmarshall(pBuffer,nLen,_pszPwd);
    if (nRet<SUCCESS)
    {
        pBuffer += nRet;
        nLen -= nRet;
    }
    else
    {
        return nRet;
    }
    m_pImplementObj->Authenticate(_uIp,_pszName,_pszPwd);
    return SUCCESS;
}
TInt32 IfAuthServiceSkeleton::HandleOnDisconneted_CDoid(CMessageHeader *pMsg)
{
    TInt32 nLen = pMsg->GetBodyLength();
    TUChar *pBuffer =pMsg->GetBody();
    TInt32 nRet;
    CDoid _tMyDoid;
    nRet = Unmarshall(pBuffer,nLen,_tMyDoid);
    if (nRet<SUCCESS)
    {
        pBuffer += nRet;
        nLen -= nRet;
    }
    else
    {
        return nRet;
    }
    m_pImplementObj->OnDisconneted(_tMyDoid);
    return SUCCESS;
}
}
