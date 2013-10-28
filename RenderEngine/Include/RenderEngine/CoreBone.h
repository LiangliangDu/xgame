#ifndef __CoreBone_H__
#define __CoreBone_H__

namespace xs
{
	/*! \addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/
	//2010��12��8�գ�������֧��billboard����֧�ֲ�ֵ�����Ỻ�����õĹ�������


	/** ��������������״�ṹ�������Ĺ����γ�skeleton
	*/
	class _RenderEngineExport CoreBone
	{
	public:
		CoreBone() :m_pTranslation(0),
			m_pRotation(0),
			m_pScale(0),
			m_mtxInitMatrix(Matrix4::IDENTITY),
			m_vPivot(xs::Vector3::ZERO),
			m_name("uninitialized"),
			m_bPivotRotation(false),
			m_pParent(0),
			m_precomputeMtx(Matrix4::IDENTITY),
			m_bCanBufferData(false)
		{

		}

		~CoreBone();

	public:
		//����ģ������
		void					setName(const char *name);
		//ȡ������
		const char*				getName();

		//�������
		void 					setPivot(const Vector3& vPivot);
		//ȡ�����
		const Vector3&			getPivot();

		//�����Ƿ�����pivot��ת������
		void					setPivotRotation(bool pivotRotation);
		bool					getPivotRotation();

		//���ø�����
		void 					setParent(CoreBone* pCoreBone);
		//ȡ�ø�����
		CoreBone*				getParent();

		//�����ܷ񻺴�����
		void					setCanBufferData(bool canBuffer);

		//��ȡռ�õ��ڴ�,����ȷ
		size_t					getMemeorySize();


		//����ӿ���ʱû��
		void					setPrecomputeMatrix(const Matrix4& mtx);
		const xs::Matrix4 &	getPrecomputeMatrix();

		inline void	setInitMatrix(const Matrix4 & mtx) { m_mtxInitMatrix = mtx;}
		inline const Matrix4 & getInitMatrix() { return m_mtxInitMatrix;}

		//��ȡָ��ʱ��Ĺ�������
		void	getBoneData(
			AnimationTime* pTime, 
			int rangeIndex, 
			xs::Matrix4 & mtxTransform,
			xs::Quaternion & quatRotation
			);
		
		//����ʱ���������ľ���
		//void 					calcMatrix(IRenderSystem *pRenderSystem,AnimationTime* pTime,int rangeIndex);
		void					setInterpolationType(InterpolationType translation,InterpolationType rotation,InterpolationType scale);
		void					setKeyFramesTranslation(KeyFrames<Vector3>& keyFrames);
		void					setKeyFramesRotation(KeyFrames<Quaternion>& keyFrames);
		void					setKeyFramesScale(KeyFrames<Vector3>& keyFrames);

		std::vector<ModelKeyframeTM> *m_pMKTM;//��ʱû��
		std::vector<uint>		m_keyTime;//��¼���еĹؼ�ʱ��
		//�ؼ�֡���������ڼ��ٲ���,��һ��uint��ÿ�������Ŀ�ʼʱ�䣬�ڶ���int��m_keyTime����ĵ�һ���ؼ�ʱ���λ�ã�������int��m_keyTime����ؼ�ʱ��ĸ���
		HASH_MAP_NAMESPACE::hash_map<uint, std::pair<uint, uint> > m_keyTimeIndex;
	private:
		//void 					_calcMatrix_NoPivotRotation(IRenderSystem *pRenderSystem,AnimationTime* pTime,int rangeIndex);
		//void 					_calcMatrix_PivotRotation(IRenderSystem *pRenderSystem,AnimationTime* pTime,int rangeIndex);
		uint					getClosetKeyFrameTime(AnimationTime * pTime,int rangeIndex);
	private:
		
		//�����ĳ�ʼ�任����
		
		KeyFrames<Vector3>		*m_pTranslation;
		KeyFrames<Quaternion>	*m_pRotation;
		KeyFrames<Vector3>		*m_pScale;
		
		Matrix4					m_mtxInitMatrix;
		Vector3					m_vPivot;
		std::string				m_name;
		CoreBone*				m_pParent;
		bool					m_bPivotRotation;
		Matrix4					m_precomputeMtx;
		bool					m_bCanBufferData; //�ܷ񻺴���������

		struct					KeyFrameData
		{
			xs::Matrix4		m_mtxTransform;
			xs::Quaternion		m_quatRotation;
		};
		typedef HASH_MAP_NAMESPACE::hash_map<uint, KeyFrameData*> KeyFrameDataContainer;//�ؼ�ʱ��͹������ݵ�ӳ���
		typedef KeyFrameDataContainer::iterator KeyFrameDataContainerIterator;

		KeyFrameDataContainer	m_vNoPivotData;
		KeyFrameDataContainer	m_vPivotData;

	};
	/** @} */
}

#endif