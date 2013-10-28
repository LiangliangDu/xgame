#ifndef __ModelCodecMm_H__
#define __ModelCodecMm_H__

#include "RenderEngine/Manager.h"
#include "SubModel.h"
#include "RenderEngine/MmStructs.h"

namespace xs
{
	class ModelCodecMm : public ManagedItem,public IModel
	{
	public:
		virtual void release();

		/** ����ļ���
		@return �ļ���
		*/
		virtual const std::string& getFileName() ;

		/** ��ð�Χ������
		@return ģ�Ͱ�Χ��
		*/
		virtual const AABB&	getAABB() ;

		/** ��ð�Χ������
		@return ģ�Ͱ�Χ��
		*/
		virtual const Sphere& getBoudingSphere() ;

		/** ���ģ�Ͷ�����Ŀ
		@return ģ�Ͷ�����
		*/
		virtual uint	getAnimationCount() ;

		/** ���ĳ������
		@param index �±�
		@return ����ָ��
		*/
		virtual Animation* getAnimation(uint index);

		/** �Ƿ�ӵ��ĳ������
		@param animation ��������
		@see enAnimation
		@return �������animation�����򷵻ش˶������ݣ����򷵻�0
		*/
		virtual Animation* hasAnimation(const std::string& animation) ;

		//��ȡģ�͵ĹǼ�
		virtual CoreSkeleton * getCoreSkeletion();

		/** �����ģ�͵�����
		@return ��ģ�͵�����
		*/
		virtual uint getNumSubModels() ;

		/** �����ģ��ָ��
		@param name ��ģ������
		@return ��ģ��ָ��
		*/
		virtual ISubModel*	getSubModel(const char* name);

		/** �����±��������ģ��ָ��
		@param name ��ģ���±�
		@return ��ģ��ָ��
		*/
		virtual ISubModel*	getSubModel(int index);

		virtual IIndexBuffer*	getIndexBuffer();

		virtual IVertexBuffer*	getTexcoordBuffer();

		/**�������
		*/
		virtual uint getNumFaces();

		/**��ö�����
		*/
		virtual uint getNumVertices();

		/**��ð汾��
		*/
		virtual uint getVer();

		virtual IVertexBuffer* vertexBlend(Skeleton *pSkeleton,const AnimationTime *pTime);

		virtual uint numParticleSystem();

		virtual ParticleEmitter2Data*	getParticleSystemData(uint index);

		virtual uint numRibbonSystem();

		virtual RibbonEmitterData*	getRibbonSystemData(uint index);

		virtual uint numMmParticleSystem();

		virtual MmParticleSystemData* getMmParticleSystem(uint index);

		//��Ӳ����Ƥ��֧��
		virtual IVertexBuffer *	getBlendWeightBuffer();
		virtual IVertexBuffer * getBlendIndicesBuffer(uint subModelIndex);
		virtual IVertexBuffer * getOriginVertexBuffer() ;
		virtual IShaderProgram * getBlendShaderProgram();
	private:
		//���ɻ��Ȩ��buffer����ÿ����mesh���ɻ������buffer�����ܻ�����mesh
		void initForGPUVertexBlend(MmFace* pFaceBuffer);
		//�����Ǽ�
		void createCoreSkeleton();

	public:

		//////��ȡMMPartileSystem����
		////virtual  void * getMMParticleSystemParam(unsigned int index, string paramname, string & type, int & count );
		////void * aidGetMMPSParamVector( void * pParam, string paramtype, string & type, int paramcount, int & count);
		////void * aidGetMMPSParamsKeyFrames( MmParticleSystemData & mmpsdata, string paraname,string & type, int & count);
		//////����MMParticleSystem����
		////virtual bool setMMParticleSystemParam(unsigned int index, string desname, void * psrc, int srcnum, string srctype);
		////bool aidSetMMPSParamVector(void * psrc, int srcnum, string srctype, void* pdes, int desnum, string destype, bool enablerange = false, float min = 0.0f, float max = 0.0f );
		////bool setMMPSKeyFramesParam(KeyFrames<float> * pkf, float * pParamVal, int iParamNum, string szParamType);
		//////����mmparticlesystem
		////virtual bool addMMParticleSystem();
		//////ɾ��mmparriclesystem
		////virtual bool removeMMParticleSystem(unsigned int index);
		////
		//////��ģ��д�뵽�ļ�
		////bool write(string filename);

		/**���ģ��ռ�õ��ڴ�
		*/
		virtual size_t getMomorySize();

	public:
		virtual ~ModelCodecMm();
		ModelCodecMm(const std::string& name,IRenderSystem* pRenderSystem);

	public:
		const char*	getType() const;
		bool decode(xs::Stream *pStream);

	private:
		IRenderSystem*	m_pRenderSystem;

		uint	m_ver;

		//Global Sequences
		std::vector<uint>	m_vGlobalSequences;

		//isAnimated
		bool	m_bAnimatedGeometry;
		bool	m_bAnimatedBones;
		bool	m_bNeedPerInstanceAnimation;

		//Textures
		std::vector<MmTexture>	m_vTextures;

		//Materials
		std::vector<Material>	m_vMaterials;
		std::vector<int> m_vRecordMaterialstextureIndex;//��¼m_vMaterials��layer��������Ϣ

		//VertexBuffer
		IVertexBuffer	*m_pVBTexcoord;

		//IndexBuffer
		IIndexBuffer	*m_pIB;

		//Vertices
		AnimatedVertex*	m_pOriginVertices;
		uint			m_numVertices;

		//����Ӳ��������
		IVertexBuffer	*m_pVBPosNormal;;
		IVertexBuffer*	m_pBlendWeightBuffer;
		std::vector<IVertexBuffer*> m_vBlendIndices;
		IShaderProgram* m_pBlendProgram;

		//Bounding Volume
		AABB	m_aabb;
		Sphere	m_sphere;

		//Faces
		uint	m_numFaces;

		//Skeleton
		std::vector<BoneData*>	m_vBones;
		CoreSkeleton			m_skeleton;

		//Animations
		std::vector<Animation*>	m_vAnimations;
        HASH_MAP_NAMESPACE::hash_map<std::string,Animation*> m_AniamtionMap;

		std::vector<SubModel> m_vRenderPasses;
		std::vector<int> m_vRecordMaterialIndex;//лѧ���޸ģ���¼SubModel��MaterialIndex
		//precomputed vertexbuffer
#define MM_PRECOMPUTED_VBO_COUNT_MAX (30 * 3 * 60 ) // ֡��* ����ƽ��ʱ�� * ��������
		IVertexBuffer*	m_pPrecomputedVBs[MM_PRECOMPUTED_VBO_COUNT_MAX  /*30720*/];

		//Momory size
		size_t		m_memorySize;

		//
		std::vector<MmParticleSystemData>	m_vMmParticleSystems;

	private:
		void	calcAABB(Vector3* pVertices,uint ui32Stride,uint numVertices);
	};
}

#endif