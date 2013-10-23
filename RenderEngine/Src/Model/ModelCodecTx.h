#ifndef __ModelCodecTx_H__
#define __ModelCodecTx_H__

#include "RenderEngine/Manager.h"
#include "SubModel.h"
#include "RenderEngine/MzHeader.h"
//лѧ����ӣ�����Mm����ϵͳ�Ĳ�����ͷ�ļ�
#include "RenderEngine/MmStructs.h" 
#define TX_TEX_VBO_STATIC_WRITE_ONLY //����������壬��ʹ�þ�̬vbo�����������꣬����˽�ö�̬vbo������������



/*
2009/07/24 xiexuehui for uv animation
*/

namespace xs
{
	class ModelCodecTx : public ManagedItem,public IModel
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

		//�Ƿ���Ҫ������Ӱ
		virtual bool	needDrawShadow(){ return false;}

		//��ȡPartileSystem����
	public:
		virtual  void * getParticleSystemParam(unsigned int index, string paramname, string & type, int & count );
		virtual bool setParticleSystemParam(unsigned int index, string desname, void * psrc, int srcnum, string srctype);
		virtual bool addParticleSystem();//����particlesystem	
		virtual bool removeParticleSystem(unsigned int index);//ɾ��parriclesystem
		
	private:
		void * getPSParamVector( void * pParam, string paramtype, string & type, int paramcount, int & count);
		void * getPSKeyFramesParam(void * pkf, string kftype, string & type, int & count);
		bool setPSParamVector(void * psrc, int srcnum, string srctype, void* pdes, int desnum, string destype, bool enablerange = false, float min = 0.0f, float max = 1000000.0f );
		bool setPSKeyFramesParam( void * pkf, string kftype, float * pParamVal, int iParamNum, bool enablerange = false, float min = 0.0f, float max = 1000000.0f);

		
		//���ڽ�ģ��д���ļ�
	public:
		virtual bool write(string filename,float fCopress);

		/**���ģ��ռ�õ��ڴ�
		*/
		virtual size_t getMomorySize();

		//��Ӳ����Ƥ��֧��
		virtual IVertexBuffer *	getBlendWeightBuffer();
		virtual IVertexBuffer * getBlendIndicesBuffer(uint subModelIndex);
		virtual IVertexBuffer * getOriginVertexBuffer() ;
		virtual IShaderProgram * getBlendShaderProgram();
	private:
		//���ɻ��Ȩ��buffer����ÿ����mesh���ɻ������buffer�����ܻ�����mesh
		void initForGPUVertexBlend(MODELFACE* pFaceBuffer);
		//�����Ǽ�
		void createCoreSkeleton();

	public:
		//��ȡMMParticleSystem����
		virtual  void * getMMParticleSystemParam(unsigned int index, string paramname, string & type, int & count );
		virtual bool setMMParticleSystemParam(unsigned int index, string desname, void * psrc, int srcnum, string srctype);
		virtual bool addMMParticleSystem();
		virtual bool removeMMParticleSystem(unsigned int index);
		//����MMParticleSystem����
	private:
		void * getMMPSParamVector( void * pParam, string paramtype, string & type, int paramcount, int & count);
		void * getMMPSKeyFramesParam(void * pkf, string kftype, string & type, int & count);
		bool setMMPSParamVector(void * psrc, int srcnum, string srctype, void* pdes, int desnum, string destype, bool enablerange = false, float min = 0.0f, float max = 1000000.0f );
		bool setMMPSKeyFramesParam( void * pkf, string kftype, float * pParamVal, int iParamNum, bool enablerange = false, float min = 0.0f, float max = 1000000.0f);
	private:
			void initTile(Vector2 *tc,int num,int cols,int rows,int order);//���ڽ���ʱ��ʼ����������


	public:
		//�����û�������Ⱦ˳��
		virtual bool enableCustomizeRenderOrder(bool enable) ;
		virtual bool isEnabledCustomizeRenderOrder();
		virtual bool setCustomizeRenderOrder( uint objectType, uint index, int order);
		virtual int	getCustomizeRenderOrder(uint objectType, uint index);	
	private:
		int getInitRenderOrder();
		bool	m_bIsEnableCustomizeRenderOrder;
		std::vector<int> * m_pCustomizeRenderOrderQueue;

		/*Ribbon System �༭����
		*/
	public:
		virtual void * getRibbonSystemParam( unsigned int index, string paramname, string & type, int &count);
		virtual bool setRibbonSystemParam( unsigned int index, string desname, void * psrc, int srcnum, string srctype);
		virtual bool addRibbonSystem();
		virtual bool removeRibbonSystem(unsigned int index);
	private:
		void * getRSParamVector( void * pParam, string paramtype, string & type, int paramcount, int & count);//лѧ���޸�
		void * getRSKeyFramesParam( void * pkf, string keyframetype,string & type, int & count);//лѧ���޸�
		bool setRSParamVector(void * psrc, int srcnum, string srctype, void* pdes, int desnum, string destype, bool enablerange = false, float min = 0.0f, float max = 1000000.0f );//лѧ���޸�
		bool setRSKeyFramesParam( void * pkf, string keyframetype, float * pParamVal, int iParamNum );//лѧ���޸ģ�����֡����


	public:
		virtual ~ModelCodecTx();
		ModelCodecTx(const std::string& name,IRenderSystem* pRenderSystem);

	public:
		const char*	getType() const;
		bool decode(xs::Stream *pStream);

		void loadFeiBian(xs::Stream *pStream,const std::string& animationName);

	private:
		IRenderSystem*	m_pRenderSystem;
		std::vector<SubModel> m_vRenderPasses;
		std::vector<bool>	m_vShouldSavePasses;
		//Textures
		std::vector<Animation*>		m_vAnimations;
		stdext::hash_map<std::string,Animation*>	m_AnimationMap;
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

		std::vector<MmParticleSystemData *> m_vMmParticleSystemData;//лѧ����ӣ�����MM����ϵͳ

		uint		m_ver;

		//precomputed vertexbuffer
		//IVertexBuffer*	m_pPrecomputedVBs[8192];
#define TX_PRECOMPUTED_TEX_FPS 30 //����֡�ٶ�
#define TX_PRECOMPUTED_TEX_TIME 34 //���嶯������ʱ�䣬����Ϊ34��֧��1000֡
#define TX_PRECOMPUTED_VBO_COUNT_MAX ( TX_PRECOMPUTED_TEX_FPS * TX_PRECOMPUTED_TEX_TIME * 1) //֧��1000֡�Ķ���
		IVertexBuffer*	m_pPrecomputedVBs[TX_PRECOMPUTED_VBO_COUNT_MAX];//����ÿ��30֡��������20�룬����Ҫ�ܴ�Ļ���

#if defined(TX_TEX_VBO_STATIC_WRITE_ONLY)
#define TX_PRECOMPUTED_TEX_PASS_COUNT 1 //�������ֻ�ǵ���1��������������ֻ֧��1������ͨ���������֧�ֶ��أ�������Ӧ���趨
#define TX_PRECOMPUTED_TEX_VBO_COUNT ( TX_PRECOMPUTED_TEX_FPS * TX_PRECOMPUTED_TEX_TIME ) //����Ϊÿ��30֡������仯����20�룬һ�����Ч���ᳬ�����ʱ��
		IVertexBuffer * m_pPrecomputedTexVBs[TX_PRECOMPUTED_TEX_PASS_COUNT*TX_PRECOMPUTED_TEX_VBO_COUNT];
		IVertexBuffer * m_pPrecomputedTexVBsPass[TX_PRECOMPUTED_TEX_PASS_COUNT];
#endif

		//Momory size
		size_t		m_memorySize;

	private:
		_VertexData*	m_pVertexData;

		bool			m_bAnimatedGeometry;

	private:
		void  calcAABB(_VertexData *pVtx,uint num,AABB& aabb,Sphere& sphere);

	//added by xiexuehui for uv animation 2009/07/24
	private:
		bool m_bAnimatedTexCoord;
		int m_iMaxPassNum;

#if !defined(TX_TEX_VBO_STATIC_WRITE_ONLY)
		std::map< int , IVertexBuffer *> m_mapPrecomputedTexBuffers;//Ԥ���������ӳ��
		uint m_uiPreAniTime;
#endif
		///����unwrap uvw�޸�����uv����
		std::vector< KeyFrames<Vector2> > m_vUVKFs;//���治ͬʱ��Ķ����uv���ꡣ
		
	public:
		//�ж�ģ���Ƿ����uv����
		virtual bool isAnimatedTexCoord();
		//����ָ��ʱ�������ӳ��,����ֵ������ͨ����������AnimationTime:��ǰ��ʱ��
		virtual int texBlend(const AnimationTime *pTime);
		//��ȡָ��ʱ���������,����ֵ��ָ��ͨ���������棬pass��ָ��ͨ����pTime��ָ��ʱ��
		virtual IVertexBuffer* getTexCoordBuffer(int pass);
	//added end 2009/07/24
		public: //ģ�͵���չ
			virtual void * getExtParam(std::string strParamName, std::string & strType, int & count);
			virtual bool setExtParam( std::string strParamName, void * psrc, int srcnum, string srctype);
	private:
		bool m_bShouldBoneInterKeyFrame;
		Vector4 m_boundingBox;
		bool m_bCalculatedAABB;
	public:
		//��ȡboundingbox
		virtual void getBoundingBox( Vector4 &rect);

	private:
		bool m_bMergeSubModel;//��ģ���ں�
		bool m_bLoadSkinInfoFromFile;//���ļ���ȡ����Ƥ��Ϣ


	};
}

#endif