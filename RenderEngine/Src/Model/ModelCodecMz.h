#ifndef __ModelCodecMz_H__
#define __ModelCodecMz_H__

#include "RenderEngine/Manager.h"
#include "SubModel.h"
#include "RenderEngine/MzHeader.h"

namespace xs
{
	class ModelCodecMz : public ManagedItem,public IModel
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

		/**���ģ��ռ�õ��ڴ�
		*/
		virtual size_t getMomorySize();
		
		//���ڽ�ģ��д���ļ�
		virtual bool write(string filename,float fCopress);

		//��Ӳ����Ƥ��֧��

		virtual IVertexBuffer *	getBlendWeightBuffer();

		virtual IVertexBuffer * getBlendIndicesBuffer(uint subModelIndex);

		virtual IVertexBuffer * getOriginVertexBuffer() ;

		virtual IShaderProgram * getBlendShaderProgram();

	public:
		virtual ~ModelCodecMz();
		ModelCodecMz(const std::string& name,IRenderSystem* pRenderSystem);

	public:
		const char*	getType() const;
		bool decode(xs::Stream *pStream);

		void loadFeiBian(xs::Stream *pStream,const std::string& animationName);

	private:
		//���ɻ��Ȩ��buffer����ÿ����mesh���ɻ������buffer�����ܻ�����mesh
		void initForGPUVertexBlend(MODELFACE* pFaceBuffer);
		//�����Ǽ�
		void createCoreSkeleton();

	private:
		IRenderSystem*	m_pRenderSystem;
		std::vector<SubModel> m_vRenderPasses;
		//Textures
		std::vector<Animation*>		m_vAnimations;
		HASH_MAP_NAMESPACE::hash_map<std::string,Animation*>	m_AnimationMap;
		//VertexBuffer
		IVertexBuffer	*m_pVBTexcoord;
		uint				m_ui32VerticeNum;
		//IndexBuffer
		IIndexBuffer	*m_pIB;
		IVertexBuffer	*m_pVBPosNormal;

		IVertexBuffer*	m_pBlendWeightBuffer;
		std::vector<IVertexBuffer*> m_vBlendIndices;
		IShaderProgram* m_pBlendProgram;
		//BoundingVolume
		AABB	m_AABB;
		Sphere	m_BoundingSphere;

		//Skeleton
		std::vector<BoneData*>	m_vBones;
		CoreSkeleton			m_skeleton;

		//Materials
		std::vector<Material> m_vMaterials;

		//Ribbon
		std::vector<RibbonEmitterData*> m_vRibbonEmitters;

		//Particle
		std::vector<ParticleEmitter2Data*> m_vParticleEmitters;

		uint		m_ver;

		//�Ƿ������aabb
		bool m_bCalculatedAABB;

		bool m_bLoadSkinInfoFromFile;//���ļ���ȡ����Ƥ��Ϣ

		//precomputed vertexbuffer
#define MZ_PRECOMPUTED_VBO_COUNT_MAX ( 30 * 3 * 60 ) //֡�� * ƽ������ʱ�� * ��������
		IVertexBuffer*	m_pPrecomputedVBs[ MZ_PRECOMPUTED_VBO_COUNT_MAX /*8192*/];

		//Momory size
		size_t		m_memorySize;

	private:
		_VertexData*	m_pVertexData;

		bool			m_bAnimatedGeometry;

	private:
		void  calcAABB(_VertexData *pVtx,uint num,AABB& aabb,Sphere& sphere);
	};
}

#endif