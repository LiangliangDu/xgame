#ifndef __BONEANIMATIONSETMANAGER_H__
#define __BONEANIMATIONSETMANAGER_H__

#include "RenderEngine/Manager.h"
#include "BoneAnimationSet.h"
namespace xs
{
	class BoneAnimationSetManager: public Manager< BoneAnimationSet * >, public Singleton<BoneAnimationSetManager>
	{
	public:
		BoneAnimationSetManager();
		virtual ~BoneAnimationSetManager();

	public:
		/** ���ع�������
		@param fileName ���������ļ���
		@return ��������ָ��
		*/
		BoneAnimationSet * loadBoneAnimationSet( const char * fileName);

		/** �ӹ��������ļ����ƻ�ȡ��������
		@param fileName ���������ļ���
		@return ��������ָ��
		*/
		BoneAnimationSet * getByName(const char* fileName);

		/** �����������ٹ�������
		@param fileName ���������ļ���
		*/
		void releaseBoneAnimationSet( const char * fileName);

		/** ����ָ�����ٹ�������
		@param fileName ��������ָ��
		*/
		void releaseBoneAnimationSet(  BoneAnimationSet * pAni);


	public:
		/** ʵ�ʵ�ɾ������
		@param id Ҫɾ���Ķ���
		@remarks ��Ҫʵ�ִ˺�������������ɾ��
		*/
		virtual void  doDelete(BoneAnimationSet* id);

	private:
		struct BananaSkin
		{
			BoneAnimationSet * pAni;
			ManagedItem * pManagedItem;
		};
		typedef std::list<BananaSkin> RecycleBin;
		RecycleBin m_recycleBin;
		size_t	m_recycleBinSize;
	};
}
#endif