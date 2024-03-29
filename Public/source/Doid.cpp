#include "Doid.h"
#include "SysMacros.h"
#include <stdio.h>

namespace Zephyr
{





ostream & operator<<(ostream &os,CDoid &tDoid)
{
    os<<"["<<tDoid.m_nodeId<<","<<tDoid.m_virtualIp<<","<<tDoid.m_srvId<<","<<tDoid.m_objId<<"]";
    return os;
}



void CDoid::ToStr(TChar *pBuff)
{
    sprintf(pBuff,"[%u,%u,%u,%u]",(unsigned int)m_nodeId,(unsigned int)m_virtualIp,(unsigned int)m_srvId,(unsigned int)m_objId);
}

TInt32 GetLength(CDoid &rDoid)
{
    return sizeof(CDoid);
}
TInt32 GetLength(CDoid *pDoid)
{
    return sizeof(CDoid);
}


TInt32 Unmarshall(TUChar *pBuffer,TUInt32 nLen,CDoid *&pDoid)
{
    if (nLen < sizeof(CDoid))
    {
        return OUT_OF_MEM;
    }
    pDoid = (CDoid *)pBuffer;
    return sizeof(CDoid);
}

TInt32 Marshall(TUChar *pBuffer,TUInt32 nLen,CDoid *pDoid)
{
    if (nLen < sizeof(CDoid))
    {
        return OUT_OF_MEM;
    }
    *((CDoid*)pBuffer) = *pDoid;
    return sizeof(CDoid);
}

TInt32 Unmarshall(TUChar *pBuffer,TUInt32 nLen,CDoid& rDoid)
{
    if (nLen < sizeof(CDoid))
    {
        return OUT_OF_MEM;
    }
    rDoid = *((CDoid *)pBuffer);
    return sizeof(CDoid);
}

TInt32 Marshall(TUChar *pBuffer,TUInt32 nLen,CDoid& rDoid)
{
    if (nLen < sizeof(CDoid))
    {
        return OUT_OF_MEM;
    }
    *((CDoid*)pBuffer) = rDoid;
    return sizeof(CDoid);
}

}

