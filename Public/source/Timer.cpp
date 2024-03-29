#include "../include/Timer.h"


namespace Zephyr
{

TInt32 CTimer::Init(TInt32 nSize)
{
    TInt32 nRet = m_tPool.InitPool(nSize);
    if (nRet < SUCCESS)
    {
        return nRet;
    }
    m_tMap.Init(&m_tPool);
    m_pRuning = NULL;
    return SUCCESS;
}

void *CTimer::SetTimer(TUInt32 uGapInMs,TInt32 nRepeatTime,IfScheduler *pScheduler,TUInt64 nTimeNow)
{
    TplMultiKeyMapNode<CScheduler,TUInt64> *pNode = m_tPool.GetMem();
    if (pNode)
    {
        pNode->m_nTime = nTimeNow + uGapInMs;
        pNode->m_nGap  = uGapInMs;
        pNode->m_nRepeatTime = nRepeatTime;
        pNode->m_pScheduler = pScheduler;
        m_tMap.AddInTree(pNode);
    }
    return pNode;
}

void *CTimer::ResetTimer(void *pTimer,TUInt32 uGapInMs,TInt32 nRepeatTime,IfScheduler *pScheduler,TUInt64 nTimeNow)
{
    KillTimer(pTimer);
    return SetTimer(uGapInMs,nRepeatTime,pScheduler,nTimeNow);
// 
//     TplMultiKeyMapNode<CScheduler,TUInt64> *pNode = (TplMultiKeyMapNode<CScheduler,TUInt64> *)pIfScheduler;
//     if (pNode == m_pRuning) //正是当前节点，自己删自己！
//     {
//         pNode->m_nRepeatTime = nRepeatTime + 1;
//         pNode->m_pScheduler = pScheduler;
//         pNode->m_nGap = uGapInMs;
//         pNode->m_nTime = nTimeNow;
//     }
//     else
//     {
//         m_tMap.RemoveFromTreeItem(pNode);
//         pNode->m_nTime = nTimeNow + uGapInMs;
//         pNode->m_nGap  = uGapInMs;
//         pNode->m_nRepeatTime = nRepeatTime;
//         pNode->m_pScheduler = pScheduler;
//         m_tMap.AddInTree(pNode);
//     }
}

    //删除定时器pTimer是SetTimer返回的结果
const IfScheduler *CTimer::KillTimer(void *pTimer)
{
    TplMultiKeyMapNode<CScheduler,TUInt64> *pNode = (TplMultiKeyMapNode<CScheduler,TUInt64> *)pTimer;
    if (pNode == m_pRuning) //正是当前节点，自己删自己！
    {
        //IfScheduler *pScheduler = pNode->m_pScheduler;
        pNode->m_nRepeatTime = 0;
        return pNode->m_pScheduler;
    }
    else
    {
        m_tMap.RemoveFromTreeItem(pNode);
        IfScheduler *pScheduler = pNode->m_pScheduler;
        pNode->Clean();
        m_tPool.ReleaseMem(pNode);
        return pScheduler;
    }
}

    //Run是要定时去调用的，然后产生回调.
TUInt32 CTimer::Run(TUInt64 nTimeNow)
{
    TUInt32 nRunCnt = 0;
    //if (m_tMap.GetActivedSize())
    {
		//TplMultiKeyMapNode<CScheduler,TUInt64>::Iterator it = m_tMap.Begin();
		TplMultiKeyMapNode<CScheduler,TUInt64> *pNode = m_tMap.Begin();
        while(pNode)
        {
            if (pNode->m_nTime < nTimeNow)
            {
				//++it;
                m_pRuning = pNode; //保证m_pRuning不会被删除.

                m_tMap.RemoveFromTreeItem(pNode); //先从tree切掉自己
                if (pNode->m_nRepeatTime < 0)
                {
                    pNode->m_pScheduler->OnScheduler(nTimeNow,pNode,-1);
                    if (0 != pNode->m_nRepeatTime)
                    {
                        pNode->m_nTime += pNode->m_nGap;
                        m_tMap.AddInTree(pNode);
                    }
                    else
                    {
                        pNode->Clean();
                        m_tPool.ReleaseMem(pNode);
                    }
                }
                else if (pNode->m_nRepeatTime > 0)
                {
                    //删除
                    pNode->m_pScheduler->OnScheduler(nTimeNow,pNode,pNode->m_nRepeatTime);
                    if (0 != pNode->m_nRepeatTime)
                    {
                        --pNode->m_nRepeatTime;
                        pNode->m_nTime += pNode->m_nGap;
                        m_tMap.AddInTree(pNode);
                    }
                    else
                    {
                        pNode->Clean();
                        m_tPool.ReleaseMem(pNode);
                    }
                }
                else 
                {
                    //
                    pNode->m_pScheduler->OnScheduler(nTimeNow,pNode,0);
                    pNode->Clean();
                    m_tPool.ReleaseMem(pNode);
                }
                m_pRuning = NULL;
                pNode = m_tMap.Begin(); //m_tMap.Begin();//这样做效率不高Log(n)，但是最安全，限制最少.
                ++ nRunCnt;
                if (nRunCnt > 1024) //限制次数
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }
    return nRunCnt;
}


}