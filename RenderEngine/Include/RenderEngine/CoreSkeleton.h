#ifndef __CoreSkeleton_H__
#define __CoreSkeleton_H__

#include "CoreBone.h"

namespace xs
{
	/*! \addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/

	//2010��12��8�գ�������֧��billboard����֧�ֲ�ֵ�����Ỻ�����õĹ�������

	/** �Ǽܣ���������Լ������Ĳ�ι�ϵ
	*/
	class _RenderEngineExport CoreSkeleton
	{
	public:
		///
		CoreSkeleton();

		///
		~CoreSkeleton();

		/// ����һ������
		CoreBone*	createCoreBone();

		/// ��ù���������
		uint	getCoreBoneCount() const;

		/// ��õ�index������
		CoreBone*	getCoreBone(ushort index) const;

		/// �������ƻ�ù���
		CoreBone*	getCoreBone(const char *name) const;

		/// ��ȡ�ǼܵĴ�С,���������Ҫ��������
		size_t		getMemeorySize();
		
	private:
		std::vector<CoreBone*>		m_vCoreBones;	
	};
	/** @} */
}

#endif