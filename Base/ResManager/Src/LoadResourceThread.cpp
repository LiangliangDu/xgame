//==========================================================================
/**
* @file	  : LoadRecourceThread.h
* @author : 
* created : 2008-1-21  22:32
* purpose : 
*/
//==========================================================================

#include "stdafx.h"
#include "LoadResourceThread.h"
#include "ResourceNode.h"
#include <queue>
namespace xs
{
	
	void LoadTask::run()
	{

		IRenderSystem* pRenderSystem = m_pResourceThreadLoader->getRenderSystem();
		uint key = pRenderSystem->MTaddRenderTarget();
		m_semaphoreInit.Post();
		//����ѭ������
		while(true)
		{
			if(m_pResourceThreadLoader->isExit())
				break;
			
			ResourceNode* node = m_pResourceThreadLoader->getNode(m_bGroundPrivate);
			//û�м��ص���Դ
			if(node == 0)
			{
				//û����Դ����
				m_semaphore.Wait(300);
			}
			else
			{
				m_stateTask = stateTaskBusy;
				//char str[256];
				//sprintf(str,"node->load;%p\n",node);
				//OutputDebugString(str);
				switch(node->getState())
				{
				case stateAdded:
					{
						node->load();
					}
					break;
				case stateRelease:
					{
						safeRelease(node);
					}
					break;
				default:
					break;
				}
				m_stateTask = stateTaskIdle;
			}
		}
		pRenderSystem->MTremoveRenderTarget(key);
		m_stateTask = stateTaskEnd;
	}
	void LoadTask::release()
	{
		//������״̬���˳�,��run����û�н���ѭ���������,�޷�����������.
		while(true)
		{
			if(m_stateTask == stateTaskEnd)
				break;
			m_semaphore.Wait(100);
		}
		delete this;
	}

/*
	bool mygreater::operator()(const ResourceNode*& _Left, const ResourceNode*& _Right) const
	{	
		return _Left->getPriority() > _Right->getPriority();
	}*/

	/**�����߳�
	@param threads �߳�����
	@return �ɹ�����true,ʧ�ܷ���false
	@note  Ŀǰֻ֧��һ���߳�,�����opengl���߳�֧�ּ����й�,�Ժ���Ҫ����
	*/
	bool ResourceThreadLoader::create(int threads)
	{
		//����̳߳�
		int i ;
		LoadTask* pLoadTask;
		close();
		m_exitFlag = false;
		m_threadMaxCount = threads ;//threads,force to 1 now 
		m_pRenderSystem = getRenderEngine()->getRenderSystem();
		m_masterRenderTarget = m_pRenderSystem->getCurrentRenderTarget() ;		
		m_pRenderSystem->setCurrentRenderTarget(0);

		for ( i = 0 ; i<m_threadMaxCount; i++)
		{
			bool bGroundPrivate = false;
			if (m_threadMaxCount > 1 && 0 == i)
			{
				// ����ж����Դ�����̣߳����һ���������߳���Ϊ�ر����ר���߳�
				bGroundPrivate = true;
			}
			pLoadTask = new LoadTask(this, bGroundPrivate);
			m_taskList.push_back(pLoadTask);
			//m_threadPool.add(pLoadTask,THREAD_PRIORITY_LOWEST);
			//�Ӹ�һ������̵߳����ȼ��� by yhc
			//crr 0210-07-09 ������Ե�ԣ�ֻ�����������ڵ�һ��cpu��������cpuʱ��������߳���ʱ��Ƭ
			HANDLE hThread = m_threadPool.add(pLoadTask,Thread::Low);
			//SetThreadAffinityMask(hThread, 0x00000001);
			pLoadTask->wait();
		}
		m_pRenderSystem->setCurrentRenderTarget(m_masterRenderTarget);
		
		return true;
	}

	/** �ύ�����߳���Դ�ڵ���Ϣ
	@node �߳���Դ�ڵ���Ϣ
	*/
	void ResourceThreadLoader::loadRes(ResourceNode*node)
	{
		if (NULL == node)
		{
			return;
		}
		int nTaskNum = m_taskList.size();
		if (nTaskNum > 1 && node->getType() == typeResourceGroundTile)
		{
			m_mutexQueueGround.Lock();
			m_queueNodesGround.push(node);
			m_mutexQueueGround.Unlock();
		}
		else
		{
			m_mutexQueue.Lock();
			m_queueNodes.push(node);
			m_mutexQueue.Unlock();
		}
		
		std::list<LoadTask*>::iterator it = m_taskList.begin();
		while(it != m_taskList.end())
		{
			if (nTaskNum > 1 && node->getType() == typeResourceGroundTile && !(*it)->IsGroundPrivate())
			{
				it++;
				continue;
			}

			if((*it)->post())
				break;
			it++;
		}
	}

	/** Ϊ�˸��ô��룬��ɾ���Ľڵ�Ҳ����Դ�����߳�ȥ�ͷ�
	@node �߳���Դ�ڵ���Ϣ
	*/
	void ResourceThreadLoader::releaseRes(ResourceNode* node)
	{
		loadRes(node);
	}

	ResourceNode* ResourceThreadLoader::getNode(bool bGroundNode/* = false*/)
	{
		ResourceNode* pNode = 0;
		if (bGroundNode)
		{
			m_mutexQueueGround.Lock();
			if(!m_queueNodesGround.empty())
			{
				pNode = m_queueNodesGround.top();
				m_queueNodesGround.pop();
			}
			m_mutexQueueGround.Unlock();
		}
		else
		{
			m_mutexQueue.Lock();
			if(!m_queueNodes.empty())
			{
				pNode = m_queueNodes.top();
				m_queueNodes.pop();
			}
			m_mutexQueue.Unlock();
		}		
		return pNode;
	}
	
	/** �ر��߳�
	*/
	void ResourceThreadLoader::close()
	{
		m_exitFlag = true ;		
		m_taskList.clear();
		m_threadPool.wait();
		m_threadPool.clear();
	}
}