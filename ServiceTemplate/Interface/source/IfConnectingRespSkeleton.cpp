#include "../include/IfConnectingRespSkeleton.h"
#include "Public/include/TypeUnmarshaller.h"
#include "../include/IfConnectingRespMethodId.h"
namespace Zephyr 
{
TInt32 IfConnectingRespSkeleton::HandleMsg(CMessageHeader *pMsg)
{
    typedef TInt32 (IfConnectingRespSkeleton::*_PFMSG)(CMessageHeader *); 
    struct _MSGMAP_ENTRY { TUInt32 m_uMsgID; _PFMSG m_pHandlerFunc; };
    static _MSGMAP_ENTRY sMsgMapEntries[] = 
    {
        {RESPREGISTERSERVICE_CDOID_PT_TUINT32_TINT32_ID, &IfConnectingRespSkeleton::HandleRespRegisterService_CDoid_pt_TUInt32_TInt32},
        {CONFIRMUNREGISTERSERVICE_TUINT32_ID, &IfConnectingRespSkeleton::HandleConfirmUnregisterService_TUInt32},
        {ONDISCONNECT_TUINT32_ID, &IfConnectingRespSkeleton::HandleOnDisconnect_TUInt32},
    };
    TInt32 nBegin = 0;
    TInt32 nEnd = 3;
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
TInt32 IfConnectingRespSkeleton::HandleRespRegisterService_CDoid_pt_TUInt32_TInt32(CMessageHeader *pMsg)
{
    TInt32 nLen = pMsg->GetBodyLength();
    TUChar *pBuffer =pMsg->GetBody();
    TInt32 nRet;
    CDoid _pDoid;
    nRet = Unmarshall(pBuffer,nLen,_pDoid);
    if (nRet<SUCCESS)
    {
        pBuffer += nRet;
        nLen -= nRet;
    }
    else
    {
        return nRet;
    }
    TUInt32 _uServiceId;
    nRet = Unmarshall(pBuffer,nLen,_uServiceId);
    if (nRet<SUCCESS)
    {
        pBuffer += nRet;
        nLen -= nRet;
    }
    else
    {
        return nRet;
    }
    TInt32 _nRslt;
    nRet = Unmarshall(pBuffer,nLen,_nRslt);
    if (nRet<SUCCESS)
    {
        pBuffer += nRet;
        nLen -= nRet;
    }
    else
    {
        return nRet;
    }
    m_pImplementObj->RespRegisterService(&_pDoid,_uServiceId,_nRslt);
    return SUCCESS;
}
TInt32 IfConnectingRespSkeleton::HandleConfirmUnregisterService_TUInt32(CMessageHeader *pMsg)
{
    TInt32 nLen = pMsg->GetBodyLength();
    TUChar *pBuffer =pMsg->GetBody();
    TInt32 nRet;
    TUInt32 _uServiceId;
    nRet = Unmarshall(pBuffer,nLen,_uServiceId);
    if (nRet<SUCCESS)
    {
        pBuffer += nRet;
        nLen -= nRet;
    }
    else
    {
        return nRet;
    }
    m_pImplementObj->ConfirmUnregisterService(_uServiceId);
    return SUCCESS;
}
TInt32 IfConnectingRespSkeleton::HandleOnDisconnect_TUInt32(CMessageHeader *pMsg)
{
    TInt32 nLen = pMsg->GetBodyLength();
    TUChar *pBuffer =pMsg->GetBody();
    TInt32 nRet;
    TUInt32 _uReason;
    nRet = Unmarshall(pBuffer,nLen,_uReason);
    if (nRet<SUCCESS)
    {
        pBuffer += nRet;
        nLen -= nRet;
    }
    else
    {
        return nRet;
    }
    m_pImplementObj->OnDisconnect(_uReason);
    return SUCCESS;
}
}
