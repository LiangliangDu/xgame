//==========================================================================
/**
* @file	  : Resource.cpp
* @author : 
* created : 2008-1-18   13:50
*/
//==========================================================================

#include "stdafx.h"
#include "ResourceManager.h"
#include "ResourceNode.h"


namespace xs {

    template <class PoolNodeType, class KeyType>
    void ResPool<PoolNodeType,KeyType>::checkSize()
    {
        // �����������ͷſɻ����б�ͷ���Ľڵ㣬ֱ������ز����
        if (isOverflow() && mRecycledNodeList.size() > 0)
        {
            //modified by xxh 20091104�� �Դ���״̬stateError�Ķ�������ǰ�Ĳ�����������������Ա����ٴμ���
            //������һ���ô������������㲻�㣺1��û���سɹ��Ķ�������Զ�����ٴμ����ˣ�2����ʹ��mRecycledNodeListά����
            //�ڵ���������Ϸʱ����������������������޸ģ������Ѿ���mRecycledNodeList����Ĵ���stateError״̬�Ľڵ㣬
            //�ڴ������վʱ����������������ͻ����ٴμ��صĻ��ᣬͬʱҲ����Ƶ�����أ�����վά����stateError״̬�Ľڵ㲻��
            //��ΪstateError��������
            /*
             NodeList::iterator rlist_it = mRecycledNodeList.begin();
             while (rlist_it != mRecycledNodeList.end())
             {
             //Info("removeNode: delete object, id="<<(*rlist_it)->getKey()<<endl);
             if ((*rlist_it)->getState() != stateLoaded)
             {
             rlist_it++;
             continue;
             }
             mMemSize -= (*rlist_it)->getSize();
             LONGLONG key = (*rlist_it)->getKey();
             (*rlist_it)->release();
             mNodeMap.erase(key);
             mRecycledNodeList.erase(rlist_it);
             rlist_it = mRecycledNodeList.begin();
             if (!isOverflow())
             break;
             }
             */
            typename NodeList::iterator rlist_it = mRecycledNodeList.begin();
            ResourceState _ResState;
            while( rlist_it != mRecycledNodeList.end() )
            {
                _ResState = (*rlist_it)->getState();
                if( _ResState == stateLoaded || _ResState == stateError )
                {
                    mMemSize -= (*rlist_it)->getSize();
                    LONGLONG key = (*rlist_it)->getKey();
                    
                    //���������߳���ֱ��ɾ��, ����Դ�����߳�ɾ��
                    //���߳�ֻ�������ٵ��߳�ͬ�����ķ�ʱ��Ĳ�������Դ�����̼߳���ͬ��
                    //(*rlist_it)->release();
                    (*rlist_it)->setState(stateRelease);
                    if(gResourceManager)
                        gResourceManager->releaseResourceNode(*rlist_it);
                    
                    mNodeMap.erase(key);
                    mRecycledNodeList.erase(rlist_it);
                    rlist_it = mRecycledNodeList.begin();
                    if (!isOverflow())
                        break;
                }
                else//��ʱ������loading
                {
                    ++rlist_it;
                    continue;
                }
            }
        }
        
        
        DWORD dwCurTick = getTickCount();
        if (isOverflow() && mDelayRecycledNodeList.size() > 0)
        {
            // �ӳٻ��յĽڵ� TODO
            typename NodeList::iterator rlist_it = mDelayRecycledNodeList.begin();
            ResourceState _ResState;
            while( rlist_it != mDelayRecycledNodeList.end() )
            {
                _ResState = (*rlist_it)->getState();
                if( _ResState == stateLoaded || _ResState == stateError )
                {
                    mMemSize -= (*rlist_it)->getSize();
                    LONGLONG key = (*rlist_it)->getKey();
                    
                    DWORD dwRemoveTick = mDelyNodeTick[key];
                    if (dwCurTick - dwRemoveTick < 120000)
                    {
                        // �ӳٻ��յĽڵ㱣������2����
                        ++rlist_it;
                        continue;
                    }
                    
                    //���������߳���ֱ��ɾ��, ����Դ�����߳�ɾ��
                    //���߳�ֻ�������ٵ��߳�ͬ�����ķ�ʱ��Ĳ�������Դ�����̼߳���ͬ��
                    //(*rlist_it)->release();
                    (*rlist_it)->setState(stateRelease);
                    if(gResourceManager)
                        gResourceManager->releaseResourceNode(*rlist_it);
                    
                    mNodeMap.erase(key);
                    mDelayRecycledNodeList.erase(rlist_it);
                    rlist_it = mDelayRecycledNodeList.begin();
                    mDelyNodeTick.erase(key);
                    if (!isOverflow())
                        break;
                }
                else//��ʱ������loading
                {
                    ++rlist_it;
                    continue;
                }
            }
        }
    }
    
    //-------------------------------
	bool ResourceNode::load()
	{
		//ResGuard<Mutex> lock(m_mutex);

		if(m_nState != stateAdded)
			return true;
		if(m_pResourceLoader == 0)
			return false;
		m_nState = stateLoading;

		// ����ֱ�Ӹ�ֵ����Ȼ�����߳̾Ϳ���������ȡ���ָ����в������������m_pResΪҰָ��
		//m_pRes = m_pResourceLoader->loadResource(m_uResID);	
		IResource* pRes = m_pResourceLoader->loadResource(m_uResID);	
		if(pRes)
		{
			//Info("��Դ���سɹ�\n");
			m_ulSize = pRes->size();
			if(gResourceManager)
				gResourceManager->grow(m_ulSize);
//#ifdef  RKT_TEST
//			Info(
//				"addNode: key="<<getKey()
//				<<",ref="<<getRefCount()
//				<<",size="<<_ff("%.02f", ((float)getSize()/1024))
//				<<endl);
//#endif
			//Info("ResourceNode::load ok!"<<(ulong)m_uResID<<endl);

		}
		else
		{
			//Info("ResourceNode::load error!"<<(ulong)m_uResID<<endl);
			//Error("Load resource failed, type: "<<m_nType<<", name: "<<m_strName<<endl);
		}
		
		ResGuard<Mutex> lock(m_mutex);
		m_nState = ( pRes ? stateLoaded : stateError);		
		m_pRes = pRes;
		return (m_pRes ? true : false);		
	}
	void ResourceNode::release()
	{
		{
		ResGuard<Mutex> lock(m_mutex);
		safeRelease(m_pRes);
		rktCloseHandle(m_Handle);
		//char str[256];
		//sprintf(str,"ResourceNode::release:%p\n",this);
		//OutputDebugString(str);
		}
		delete this ;
	}

} // namespace