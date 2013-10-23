#ifndef __ModelManager_H__
#define __ModelManager_H__

#include "RenderEngine/Manager.h"

namespace xs
{
	class ModelManager : public IModelManager,public Manager<IModel*>
	{
	public:
		ModelManager(IRenderSystem* pRenderSystem);
	public:
		/** ����ģ�͹�����
		*/
		virtual void 		release() ;									

		virtual char*		getFirstModelExt();

		virtual char*		getNextModelExt();

		/** ����ģ��
		@param fileName ģ���ļ���
		@return ģ�ͽӿ�ָ��
		*/
		virtual IModel*		loadModel(const char* fileName) ;					

		/** ���ļ�����ȡģ�ͽӿ�ָ��
		@param fileName ģ���ļ���
		@return ģ�ͽӿ�ָ��
		*/
		virtual IModel*		getByName(const char* fileName) ;					

		/** ����ģ��
		@param pModel ģ�ͽӿ�ָ��
		*/
		virtual void 		releaseModel(IModel* pModel) ;				

		/** ������������ģ��
		@param fileName ģ���ļ���
		*/
		virtual void 		releaseModel(const char* fileName) ;				

		/** ��������ģ��
		*/
		virtual void 		releaseAll() ;

	public:

		/** ʵ�ʵ�ɾ������
		@param id Ҫɾ���Ķ���
		@remarks ��Ҫʵ�ִ˺�������������ɾ��
		*/
		virtual void  doDelete(IModel* id);

	private:
		IRenderSystem*		m_pRenderSystem;

		uint				m_it;

		struct BananaSkin
		{
			IModel *pModel;
			ManagedItem *pManagedItem;
		};

		typedef std::list<BananaSkin>	RecycleBin;
		RecycleBin			m_recycleBin;
		size_t				m_recycleBinSize;
	};

}

#endif