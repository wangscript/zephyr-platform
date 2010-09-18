/*-------------------------------------------------------------
 Copyright (C)| 
 File: Connector.h
 Author: Zephyr Shannon
 Date: 2010-3-2 10:31:50
 Version: 
 Description:  主动连接的管理器
 Others: 
 Function List: 
 Histroy: 
 -------------------------------------------------------------*/

 
#ifndef __ZEPHYR_CONNECTOR_H__
#define __ZEPHYR_CONNECTOR_H__

#include "TypeDef.h"
#include "SysMacros.h"
#include "Connection.h"
#include "ConnectionPool.h"
#include "IfNetApp.h"
#include "IfCryptorFactory.h"
#include "IfParserFactory.h"
#include <winsock2.h>

namespace Zephyr
{

class CSocketList
{
public:
    CConnection *m_pConnection;
    CSocketList *m_pNext;
public:
    CSocketList()
    {
        m_pConnection = NULL;
        m_pNext  = NULL;
    }
};

class CConnectionMgr;

class CConnector
{
private:
    TInt16          m_pendingConnections;
    TInt16          m_maxPendingConnection;
    CConnection     *m_pList;
    TInt32          m_connected;
    TInt32          m_failed;
    //IfNetApp        *m_pIfNetApp;
    HANDLE          m_hCompletionPort;
    
    CConnectionPool *m_pConnectionPool;
    
    IfCryptorFactory *m_pCryptorFactory;
    
    IfParserFactory  *m_pParserFactory;
    //CConnectionMgr  *m_pConnectionMgr;
public:
    CConnector();
    ~CConnector();
    TInt32 Init(TInt32 maxPendingConnections,HANDLE completionPort,CConnectionPool *m_pConnectionPool,IfParserFactory *pParserFactory,IfCryptorFactory *pCryptorFactory);
    //TInt32 Connect(TChar *pRemoteIp,TChar *pMyIp,TUInt16 remotePort,TUInt16 myPort,void *pAppCallBack);
    TInt32 Connect(CConPair *pPair,IfConnectionCallBack *pAppCallBack);
    
    TInt32 Run(const TUInt32 runCnt);
    
    //TInt32 Connect(CConnection *pConnection);
    //TInt32 StopConnecting(CConnection *pConnection);

    TBool  IsListFull()
    {
        if (m_maxPendingConnection <= m_pendingConnections)
        {
            return TRUE;
        }
        return FALSE;
    }
private:
    void AddToPendingList(CConnection *pConnection);
    
    void OnConnectionEstablish(CConnection *pConnection);
};

}


#endif
 