#ifndef __D3D9ResourceManager_H__
#define __D3D9ResourceManager_H__

#include <set>

namespace xs
{
	//D3D9��Դ����ӿ�
	class D3D9Resource
	{
	public:
		// �豸��ʧ���������ͷ�Default Pool�������Դ
		virtual void notifyOnDeviceLost() {}

		//�豸�ָ�, �������ؽ�Default Pool �������Դ
		virtual void notifyOnDeviceReset() {}
	};


	
	class D3D9ResourceManager;
	//D3D9��Դ��������������
	class D3D9ResourceManagerCreater
	{
	public:
		static D3D9ResourceManager * create();
	};

	//D3D9 ��Դ������
	class  D3D9ResourceManager
	{
	public://��Щ�����Ѿ�ͬ�����ˣ�����Ҫ������������

		//֪ͨ�豸��ʧ
		void notifyOnDeviceLost	();

		//֪ͨ�豸����
		void notifyOnDeviceReset();

		// ��Դ����ʱ�Ļص�����
		void notifyResourceCreated		(D3D9Resource* pResource);

		// ��Դ����ʱ�Ļص�����
		void notifyResourceRelease		(D3D9Resource* pResource);


	public: //�����û��Լ������ġ���Щ�����ĵ��ñ���ɶԳ���

		// ���ǵ����߳�����,�����������豸�ķ���
		inline void lockDeviceAccess() { m_DeviceMutex.Lock(); };

		// ���ǵ����߳�����,���ڽ������豸���κη���
		inline void unlockDeviceAccess() { m_DeviceMutex.Unlock(); };

		// ���ǵ����߳�����, ������������Դ�������ķ���
		inline void lockResourceMgrAccess() { m_ResourceMgrMutex.Lock(); };

		// ���ǵ����߳�����, ���ڽ�������Դ�������ķ���
		inline void unlockResourceMgrAccess() {m_ResourceMgrMutex.Unlock(); };

		//���ǵ����߳�����,����������Դ�ķ���
		inline void lockResourceAccess() { m_ResourceLocker.Wait() ; /*m_ResourceMutex.Lock();*/ };
		
		//���ǵ����̵߳����⣬���ڽ�������Դ�ķ���
		inline void unlockResourceAccess()  { m_ResourceLocker.Post();  /*m_ResourceMutex.Unlock();*/ };

		//���������̶߳���Դ�ķ���
		void lockAllResourceAccess();

		//��������lockAllResourceAccess��Ӧ
		void unlockAllResourceAccess();

		// ֪ͨ��ʼ������Ⱦ�ˣ����е���Դ������ͣ
		void beginFrame();

		// ֪ͨ��Ⱦ��ϣ���ͣ����Դ�������Լ�����
		void endFrame();

		//�ȴ���������������ڽ�������Դ�����Դ
		void waitForEndFrame() { ::WaitForSingleObject(m_hRenderEvent, INFINITE); };
		

	public:
		//�ͷ���Դ������������ʱ���뱣֤�����߳��Ѿ������ˡ�
		void release();		

	private:
		bool create();
		D3D9ResourceManager();
		~D3D9ResourceManager();
		//��Ԫ
	protected:
		friend class D3D9Resource;	
		friend class D3D9ResourceManagerCreater;

	protected:
		typedef std::set<D3D9Resource*>			ResourceContainer;
		typedef ResourceContainer::iterator		ResourceContainerIterator;	
		ResourceContainer			m_Resources;//��Դ����

		xs::Mutex					m_DeviceMutex;		//�豸���ʻ�����
		//xs::Mutex					m_ResourceMutex;	//��Դ������
		xs::Semaphore				m_ResourceLocker;	//��Դ������
		const static uint			cs_uiResSynAccessCount;//��Դ�������ʵ�����
		xs::Mutex					m_ResourceMgrMutex;	//	��Դ���������ʻ�����

		HANDLE						m_hRenderEvent;
		LONG						m_lRenderLockCount;	
	};
}

#endif
