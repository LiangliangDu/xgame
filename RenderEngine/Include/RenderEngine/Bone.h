#ifndef __Bone_H__
#define __Bone_H__

namespace xs
{
	class CoreBone;

	class _RenderEngineExport Bone
	{
	public:
		Bone(CoreBone * pCoreBone):m_pCoreBone(pCoreBone),
			m_bPivotRotation(false),
			m_pParent(0),
			m_vPivot(xs::Vector3::ZERO),
			m_vTransformedPivot(xs::Vector3::ZERO),
			m_mtxTransform(Matrix4::IDENTITY),
			m_quatRotation(Quaternion::IDENTITY),
			m_mtxInitMatrix(Matrix4::IDENTITY),
			m_precomputeMtx(Matrix4::IDENTITY),
			m_bNeedUpdate(true)
		{
		}
	public:
		//����ģ������
		void					setName(const char *name);
		//�����Ƿ�����pivot��ת������
		void					setPivotRotation(bool pivotRotation);
		//�������
		void 					setPivot(const Vector3& vPivot);
		//���ø�����
		void 					setParent(Bone * pBone);
		//����Ԥ�������
		void					setPrecomputeMatrix(const Matrix4& mtx);
		//ȡ������
		const char*				getName();
		//ȡ�ø�����
		Bone*					getParent();
		//ȡ�����
		const Vector3&			getPivot();
		//���µ�ǰ�ľ���
		void					calcMatrix(AnimationTime * pTime, int rangeIndex);
		//�Ƿ���Ҫ���¹���
		bool					getNeedUpdate();
		//�����Ƿ���Ҫ���¹���
		void					setNeedUpdate(bool needUpdate);
		//ȡ�ñ任������
		inline const Vector3&			getTransformedPivot()
		{
			return m_vTransformedPivot;
		}
		//ȡ�����յı任����
		inline const Matrix4&	getFullTransform()
		{
			return m_mtxTransform;
		}
		//ȡ����Ԫ���汾��������ת����
		inline const Quaternion& getFullRotation()
		{
			return m_quatRotation;
		}
		//���ó�ʼ����
		inline void	setInitMatrix(const Matrix4 & mtx) 
		{ 
			m_mtxInitMatrix = mtx;
		}
		//��ȡ��ʼ����
		inline const Matrix4 & getInitMatrix() 
		{
			return m_mtxInitMatrix;
		}
	private:	
		Matrix4					m_mtxInitMatrix;		//�����ĳ�ʼ�任����
		Vector3					m_vPivot;				//��ʼ���
		Vector3					m_vTransformedPivot;	//��ǰ���
		Matrix4					m_mtxTransform;			//��ǰ�任����
		Quaternion				m_quatRotation;			//��ǰ��ת����
		std::string				m_name;					//����Ӱ�ӵ�����
		Bone*					m_pParent;				//������Ӱ��
		bool					m_bPivotRotation;		//��������ı�־
		Matrix4					m_precomputeMtx;		//Ԥ�������
		CoreBone*				m_pCoreBone;			//�����������Ĺ���
		bool					m_bNeedUpdate;			//���������Ƿ���Ҫ����
	};

}
#endif