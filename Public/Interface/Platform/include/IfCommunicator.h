#ifndef __ZEPHYR_PUBLIC_PLATFORM_IF_COMMUNICATOR_H__
#define __ZEPHYR_PUBLIC_PLATFORM_IF_COMMUNICATOR_H__

#include "Message.h"
#include "TypeDef.h"

namespace Zephyr
{

class IfCommunicator
{
public:

    //add a new idx , that indicate the pipe to use!
    virtual CMessageHeader *GetMsg(unsigned short needRetMsgBuff = 1) = 0;

    virtual void ReturnMsgBuff(CMessageHeader *pMsg) = 0;

    virtual CMessageHeader *PrepareMsg(TInt32 bodyLength,TUInt32 methodId,CDoid srcId,CDoid* destDoid,TInt32 destDoidNum) = 0;

    //virtual int SendMsg(SCTDMessageHeader *,bool bNeedCopy = false) = 0;
    //do not need the para bNeedCopy any more, I will check it!
    virtual int SendMsg(CMessageHeader *pMsg) = 0;

    //application should not call this !!! called by work thread only! or else some events would lost!
    virtual CConnectionEvent *GetConnectionEvent() = 0;

    //maybe I could expose less header files
};

class IfCommunicatorMgr
{
    virtual IfCommunicator* GetCommunicator(TInt32 srvId) = 0;
};

}


#endif
