/*
���������������������ڱ������������
*/
#ifndef __BONEANIMATIONSET_H__
#define __BONEANIMATIONSET_H__

namespace xs
{
	class BoneAnimationSet:public ManagedItem
	{
	public:
		BoneAnimationSet(std::string strFileName);
		~BoneAnimationSet();
	public:
		/**�벻Ҫʹ��release���ͷ�ģ�ͣ�Ӧ��ʹ��BoneAnimatinSetManager::releaseModel����Ϊģ�������ü�������
		*/
		void release();

		/*��ȡ��ռ�õ��ڴ�Ĵ�С
		*/
		size_t getMemorySize();

		/*��ȡ���������ļ���
		*/
		const std::string& getFileName();

		/*���붯���ļ�
		*/
		bool decode(xs::Stream * data);

		/*�����ƻ�ȡ����
		*/
		Animation * getAnimationByName(const std::string& animation);

		/*��ȡ��������
		*/
		uint getAnimationCount();

		/*����Ż�ȡ����
		*/
		Animation * getAnimationByIndex(uint index);

		///*��ȡ������
		//*/
		//uint getBoneNum();

		///*��ȡ��������
		//*/
		//BoneData * getBoneByIndex(uint index);

		/*��ȡ�Ǽ�
		*/
		CoreSkeleton*	getCoreSkeletion();

		bool write(string filename,float fCopress);

	private:
		//�����Ǽ�
		void createCoreSkeleton();

	private:
		std::vector<BoneData*>	m_vBones;//��������
		CoreSkeleton			m_skeleton;//�Ǽ�
		std::vector<Animation*>		m_vAnimations;//������ֵ
		HASH_MAP_NAMESPACE::hash_map<std::string,Animation*>	m_AnimationMap;//����ӳ���
		uint m_version;//�汾��
		size_t m_memorySize;//��ռ�õ��ڴ���
	};
}

#endif