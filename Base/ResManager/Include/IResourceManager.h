/*******************************************************************
** �ļ���:	IResourceManager.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2008/1/9  10:07
** ��  ��:	1.0
** ��  ��:	ʵ����Դ������
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#ifndef __IRESOURCEMANAGER_H_
#define __IRESOURCEMANAGER_H_

#include "LoadLib.h"

namespace xs
{
	/** ��Դ����
	*/
	enum ResourceType
	{
		typeResourceModel = 0,	/// ģ����Դ
		typeResourcePic,        /// ͼƬ����Դ
		typeResourceGroundTile, //��ͼ��Դ
		typeResourceMinimap,	//С��ͼ
		typeResourceLogic,		//���Ƿ��ں�̨�߳�ִ�е�һ���߼�
		ResourceTypeMaxCount,
	};

	/** ����ģʽ
	*/
	enum ResLoadModel
	{
		modeSynch,//ͬ��
		modeAsynch,//�첽
	};

	/** ��Դ���ص�״̬	   
	*/
	enum ResourceState
	{
		stateUninit,	/// δ��ʼ��
		stateAdded,	/// �Ѿ���ӵ����ض���
		stateLoading,	/// ���ڼ�����
		stateLoaded,	/// �������
		stateRelease,   /// ���ͷ�
		stateError,	/// ���ع����г���
	};


	/** �������ݽӿڣ�mwp��mz����Ҫʵ�ָýӿ�
	*/
	struct IResource
	{
		virtual size_t size() const = 0;
		virtual void release() = 0;
		virtual void* getInnerData() = 0;
	};


	/** ��Դ�������ӿ�
	*/
	struct IResourceLoader
	{
		/** ������Դ
		@param name ��Դ������
		@return void* ������Դ�ڴ�
		@note ���ʧ�ܷ���ֵΪNULL
		*/
		virtual IResource* loadResource(const ulong uResID/*const std::string& name*/) = 0 ;

		/** �ͷ���Դ���ض���
		*/
		virtual void  release() = 0 ;
	};


	/** ��Դ�ڵ�ӿ�
	*/
	struct IResourceNode
	{
		virtual IResource* getResource() const = 0;
	};


	/** ��Դ�������ӿ�
	*/
	struct IResourceManager
	{
		/** ע����Դ������
		@param type ���������ͣ��ο� ResourceType ö�ٶ���
		@param resLoader ע���������ָ��
		*/
		virtual void registerResourceLoader(ResourceType type, IResourceLoader* resLoader) = 0 ;


		/** ж����Դ������
		@param type ��Դ����������
		*/
		virtual void unregisterResourceLoader(ResourceType type) = 0 ;



		/** ���������Դ
		@param resName ��Դ������,������Դ����·������
		@param type ��Դ���ͣ��ο� ResourceType ö�ٶ���
		@param bImmediately �������ػ������첽����
		*/
		virtual handle requestResource(const ulong uResID/*const std::string& resName*/, ResourceType type, bool bImmediately = false, int priority = 0) = 0 ;


		/** �ͷ�ָ������Դ
		@param resHandle ָ������Դ���
		@param bDelayRecycle �Ƿ��ӳٻ���
		 (�ӳ�2���ӲŻ��գ�����Ƶ��ʹ�õ���Դ���ͷţ����ǹ��ɵ�ʹ�ô����Ի�����ڴ渺��������ֻ���ںܱ�Ҫ�ĵط���ʹ��)
		*/
		virtual bool releaseResource(handle resHandle, bool bDelayRecycle = false) = 0 ;


		/** ������Դ����ģʽ,
		@param mode modeSynch ͬ�� modeAsynch �첽
		*/
		virtual void setLoadMode(ResLoadModel mode) = 0; 


		/** ��ȡ��Դ����ģʽ,
		@return modeSynch ͬ�� modeAsynch �첽
		*/
		virtual const ResLoadModel  getLoadMode() const = 0; 

		/** ֹͣ�����߳�
		*/
		virtual void stop() = 0;

		/** ����ָ����Դ
		*/
		//virtual IResource* findResource(ulong resId) = 0 ;

		/** ж����Դ������
		*/
		virtual void release() = 0 ;
	};



	#if defined(_LIB) || defined(RESOURCEMANAGER_STATIC_LIB)/// ��̬��汾
	#	pragma comment(lib, MAKE_LIB_NAME(xs_rmm))
    extern "C" API_EXPORT IResourceManager* LoadRMM(uint threads);
	#	define	CreateResourceManagerProc	LoadRMM
    
	#else /// ��̬��汾
		typedef IResourceManager* (RKT_STDCALL *procCreateResourceManager)(uint threads);
	#	define	CreateResourceManagerProc	DllApi<procCreateResourceManager>::load(MAKE_DLL_NAME(xs_rmm), "LoadRMM")
	#endif

}

#endif