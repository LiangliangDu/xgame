#ifndef __MmParticle_H__
#define __MmParticle_H__

namespace xs
{

	/** ������
	*/
	struct _RenderEngineExport MmParticle
	{
		Vector3 m_vPos;		//λ��
		Vector3 m_vSpeed;	//�ٶ�
		Vector3 m_vDown;	//����
		Vector3	m_vOrigin;	//��ʼλ��

		float	m_fSize;	//��С
		float	m_fLife;	//��ǰ����
		float	m_fMaxLife;	//��������
		int	m_i32Tile;	//��������ϵͳ�����е�λ��
		ColorValue m_color;	//��ɫ

		float  m_ftickDelta; //������������tick
		float  m_fSelfRotAngle; //������Z����ת�Ƕ� zgz
		MmParticle() : m_ftickDelta(0.0f), m_fSelfRotAngle(0.0f)
		{

		}
	};

}

#endif