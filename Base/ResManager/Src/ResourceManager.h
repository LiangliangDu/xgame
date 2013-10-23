//==========================================================================
/**
* @file	  : ResourceManager.h
* @author : 
* created : 2008-1-18   13:59
* purpose : 
*/
//==========================================================================

#ifndef __RESOURCEMANAGER_H__
#define __RESOURCEMANAGER_H__

#include "IResourceManager.h"
#include "ResourceNode.h"
#include "LoadResourceThread.h"

#include <hash_map>

namespace xs
{
	class ResourceThreadLoader ;

	/** ��Դ������
	*/
	class ResourceManager : public IResourceManager
	{
		IResourceLoader*				m_ResourceLoaders[ResourceTypeMaxCount]; /// �������б�
		bool							m_bImmediately;		/// �Ƿ�����������Դ����ʹ�ú�̨�̼߳��أ�
		ResPool<ResourceNode*, LONGLONG>	m_LoadedResPool;	/// ��Դ�Ļ����

		ResourceThreadLoader            m_threadLoader ;

		ResLoadModel					m_resLoadModel;     //��Դ����ģʽ


	public:
		ResourceManager();
		virtual ~ResourceManager();

		void grow(ulong size);
		
		void releaseResourceNode(ResourceNode* node);

		/** �����߳���
		@param threads �������߳�������
		@note  ��ΪOpengl���߳�֧�ַ�����Щ������û��Ū���,����2�߳���֮������\n
		Ŀǰֻ�ܹ�����һ���߳�,�Ժ���ʵ��
		*/
		bool     create(int threads) ;

		// IResourceManager
	public:
		virtual void registerResourceLoader(ResourceType type, IResourceLoader* resLoader);
		virtual void unregisterResourceLoader(ResourceType type);
		virtual handle requestResource(const ulong uResID/*const std::string& resName*/, ResourceType type, bool bImmediately = false, int priority = 0);
		virtual bool releaseResource(handle resHandle, bool bDelayRecycle = false);
		/** ������Դ����ģʽ,
		@param mode modeSynch ͬ�� modeAsynch �첽
		*/
		virtual void setLoadMode(ResLoadModel mode); 
		virtual const ResLoadModel  getLoadMode() const; 
		/** ֹͣ�����߳�
		*/
		virtual void stop();

		virtual void release();
	};

} // namespace

extern xs::ResourceManager *gResourceManager;

#endif // __RESOURCEMANAGER_H__
