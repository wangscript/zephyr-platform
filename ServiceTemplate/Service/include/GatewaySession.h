#ifndef __ZEPHYR_GATEWAY_SESSION_H__
#define __ZEPHYR_GATEWAY_SESSION_H__

#include "Public/include/TypeDef.h"
#include "Public/include/SysMacros.h"
#include "Public/Orb/include/Session.h"
#include "../../Interface/Interface/IfConnecting.h"
#include "Public/include/IdlHeaderFile.h"
#include "Public/tpl/include/TplList.h"
#include "Route.h"
#include "Public/Interface/App/include/IfNetApp.h"
#include "Public/tpl/include/TplMultiMap.h"
namespace Zephyr
{

class CGatewayService;

class CGatewaySession : public CSession
                      , public IfConnectionCallBack    //Net的回调
                      , public IfConnecting    //远程接口
{
private:
    TplMultiKeyMap<CRoute,TUInt32> m_tRouteMap;
    CGatewayService *m_pService;
public:
    DECALRE_HANDLE_INTERFCE

    CGatewaySession();
    //只调用一次
    void Init(CGatewayService *pService);

    //这个是在连接建立起来的时候回调的.
    void OnConnected(TUInt32 uIp,TUInt16 uPortId);
public:
    virtual TInt32 OnRecv(TUChar *pMsg, TUInt32 msgLen);
    //virtual TInt32 OnRecvIn2Piece(TUChar *pMsg, TUInt32 msgLen,TUChar *pMsg2,TUInt32 msgLen2) = 0;
    //网络层会自动从factory生成parser和crypter,请应用层对这连个东西进行设置
    //应用层应该明确知道IfParser 和 IfCryptor的实现类，并在OnConnected的时候对其进行设置.
    //如果返回值en_if_connection_callback_on_connected_release_parser 设置了，那么parser会被释放
    //如果返回值en_if_connection_callback_on_connected_release_cryptor 设置了，那么pCryptor会被释放
    //IfConnection *pIfConnection在连接实际建立的时候再传给应用层。
    virtual TInt32 OnConnected(IfConnection *pIfConnection,IfParser *pParser,IfCryptor *pCryptor);
    //任何socket异常都会自动关闭网络连接
    virtual TInt32 OnDissconneted(TInt32 erroCode);

public:

    //在初始化的时候会被调.
    virtual TInt32      OnInit();
    //结束是回调.
    virtual TInt32      OnFinal();

    virtual TInt32 RegisterService(CDoid *pDoid,TUInt32 uServiceId,TUInt32 uServiceIdBegin,TUInt32 uServcieIdEnd,TUInt32 uPriority);
    virtual TInt32 UnregisterService(TUInt32 uServiceId,TUInt32 uServiceIdBegin,TUInt32 uServcieIdEnd);
    //注册广播
    virtual TInt32 RegisterTeam(TUInt32 uTeamID);
    virtual TInt32 Disconnect(TUInt32 uReason);
    virtual TInt32 SetId(TUInt32 uId);
    virtual TInt32 CheckId(TUInt32 uId);
private:
    //默认是0权限（最高），先插入的会先使用
    TInt32 AddRoute(CDoid *pDoid,TUInt32 uSrvId,TUInt32 uBegin,TUInt32 uEnd,TUInt32 uPriority=0);
    
};



}

#endif
