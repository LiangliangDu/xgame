//==========================================================================
/**
* @file	  : LoadRecourceThread.h
* @author : 
* created : 2008-1-21  22:32
* purpose : 
*/
//==========================================================================


#ifndef _LOADRESOURCETHREAD_H
#define _LOADRESOURCETHREAD_H
#include <queue>

namespace xs
{

	class ResourceNode;
	class ResourceThreadLoader;


	/** ����״̬
	*/
	enum stateTask
	{
		stateTaskEnd,   //�������
		stateTaskBusy,  //����æµ״̬
		stateTaskIdle   //�������״̬
	};

	/** �̼߳���������
	*/
	class LoadTask: public IRunnable
	{
		ResourceThreadLoader*		m_pResourceThreadLoader; //pointer of ResourceThreadLoader
		
		stateTask						m_stateTask;			//����״̬

		Semaphore						m_semaphore;			//�ź���

		Semaphore						m_semaphoreInit;        //�ȴ���ʼ�����

		bool                            m_bGroundPrivate;       //ר�ż��صر��

	public: //���캯������������
		LoadTask(ResourceThreadLoader*pResourceThreadLoader, bool bGroundPrivate = false):
			m_pResourceThreadLoader(pResourceThreadLoader),
			m_bGroundPrivate(bGroundPrivate),
			m_stateTask(stateTaskIdle),
			m_semaphore(false),
			m_semaphoreInit(false)
			
			{		
			}

		virtual ~LoadTask(){}

		//�ӿں���ʵ��
	public:
		virtual void run();
		virtual void release();

	public: //���ú���
		//inline stateTask getStateTask() const { return m_stateTask; }
		inline bool post(){
			if(m_stateTask != stateTaskIdle)
				return false ;
			m_semaphore.Post() ;
			return true; 
		}

		void wait()
		{
			while(true)
			{
				if(m_semaphoreInit.Wait(100))
					break;
			}
		}

		bool IsGroundPrivate()
		{
			return m_bGroundPrivate;
		}
	};


	template<class _Ty>
	struct mygreater
		: public binary_function<_Ty, _Ty, bool>
	{	
		inline bool operator()(const _Ty& _Left, const _Ty& _Right) const
		{
			return _Left->getPriority() > _Right->getPriority();
		}
	};

	class ResourceThreadLoader
	{
		
		int									m_threadMaxCount;   //����߳�������  
		ThreadPool							m_threadPool;       //�̳߳�
		bool								m_exitFlag;         //�˳���־

		typedef std::priority_queue<ResourceNode*, std::vector<ResourceNode*>, mygreater<ResourceNode*> > QUEUE_NODES;
		
		QUEUE_NODES	m_queueNodes;
		QUEUE_NODES m_queueNodesGround;

		//std::queue<ResourceNode*>			m_queueNodes;		//�����ض���

		Mutex								m_mutexQueue;		//�������
		Mutex								m_mutexQueueGround;	//�ر���ػ������

		std::list<LoadTask*>				m_taskList;			//�����б�

		IRenderSystem*						m_pRenderSystem;

		uint								m_masterRenderTarget ;//���߳���Ⱦϵͳ����ȾĿ��
		

	public: //���캯������������
		ResourceThreadLoader():m_threadMaxCount(0),m_exitFlag(false),m_pRenderSystem(0){}
		virtual ~ResourceThreadLoader(){}

	public: //�ⲿ���ú��� 
		/**�����߳�
		@param threads �߳�����
		@return �ɹ�����true,ʧ�ܷ���false
		@note  Ŀǰֻ֧��һ���߳�,�����opengl���߳�֧�ּ����й�,�Ժ���Ҫ����
			   2010.12.13 zgz ����������D3D�������Ǵ�����2���̣߳�1��ר���ڵر����
		*/
		bool create(int threads) ;

		/** �ύ�����߳���Դ�ڵ���Ϣ
		@node �߳���Դ�ڵ���Ϣ
		*/
		void loadRes(ResourceNode*node);

		/** Ϊ�˸��ô��룬��ɾ���Ľڵ�Ҳ����Դ�����߳�ȥ�ͷ� zgz
		@node �߳���Դ�ڵ���Ϣ
		*/
		void releaseRes(ResourceNode* node);

		/** �ر��߳�
		*/
		void close();

		/** �̲߳�ѯ�Ƿ��˳�
		*/
		inline bool isExit(){ return m_exitFlag; }

		//ȡ��һ�����ؽڵ�
		ResourceNode* getNode(bool bGroundNode = false);

		IRenderSystem* getRenderSystem(){ return m_pRenderSystem ;}

		uint getMasterRenderTarget(){ return m_masterRenderTarget ;}

	};

	

}


#endif