#ifndef __IFCONNECTINGRESP_STUB_H__
#define __IFCONNECTINGRESP_STUB_H__
#include "Public/include/TypeDef.h"
#include "Public/include/Doid.h"
#include "Public/Interface/Platform/include/IfSkeleton.h"
#include "../Interface/IfConnectingResp.h"
namespace Zephyr 
{
class IfConnectingRespStub : public IfConnectingResp
{
public:
    IfSkeleton *m_pOnwerObj;
    CDoid  m_tTarget;
    void Init(IfSkeleton *pSkeleton,const CDoid *pDoid)
    {
        m_pOnwerObj = pSkeleton;
        m_tTarget = *pDoid;
    }
    virtual TInt32 RespRegisterService(CDoid* pDoid,TUInt32 uServiceId,TInt32 nRslt);
    virtual TInt32 ConfirmUnregisterService(TUInt32 uServiceId);
    virtual TInt32 OnDisconnect(TUInt32 uReason);
    virtual TInt32 SendRSAPublicKey(TUInt16 uBits,TUInt16 isFermat4,OctSeq<TUInt16> e,OctSeq<TUInt16> n,TUInt32 uDyncNr);
};
}
#endif
