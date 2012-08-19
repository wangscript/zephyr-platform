#ifndef __IFCONNECTINGRESP_METHOD_ID_H__
#define __IFCONNECTINGRESP_METHOD_ID_H__
#include "../../include/ServiceIdDef.h"

#define IFCONNECTINGRESP_INTERFACE_ID ((0x00000003) * 200) 
#define IfConnectingRespServiceId (GATEWAY_SERVICE_ID*1000)
#define IfConnectingRespServiceIdBegin RESPREGISTERSERVICE_CDOID_PT_TUINT32_TINT32_ID
#define RESPREGISTERSERVICE_CDOID_PT_TUINT32_TINT32_ID ((GATEWAY_SERVICE_ID*1000)+IFCONNECTINGRESP_INTERFACE_ID+(0))
#define CONFIRMUNREGISTERSERVICE_TUINT32_ID ((GATEWAY_SERVICE_ID*1000)+IFCONNECTINGRESP_INTERFACE_ID+(1))
#define ONDISCONNECT_TUINT32_ID ((GATEWAY_SERVICE_ID*1000)+IFCONNECTINGRESP_INTERFACE_ID+(2))
#define IfConnectingRespServiceIdEnd ((GATEWAY_SERVICE_ID*1000)+IFCONNECTINGRESP_INTERFACE_ID+(0x00000003))
#endif

