#ifndef __Skeleton_H__
#define __Skeleton_H__
#include "Bone.h"

namespace xs
{
	class CoreSkeleton;
	class Bone;

	class _RenderEngineExport Skeleton
	{
	public:
		///���캯��
		Skeleton();

		///��������
		~Skeleton();

		///��������
		bool	create(CoreSkeleton* pCoreSkeleton);

		/// ��ù���������
		uint	getBoneCount() const;

		/// ��õ�index������
		Bone*	getBone(ushort index) const;

		/// �������ƻ�ù���
		Bone*	getBone(const char *name) const;

		/// ���㴫�ݾ���
		void 	calcMatrix(AnimationTime* pTime,int rangeIndex = -1);

	private:
		CoreSkeleton*		m_pCoreSkeleton;//�����������ĹǼ�
		std::vector<Bone*>	m_vBones;
	};
}
#endif