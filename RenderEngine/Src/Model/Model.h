#ifndef __Model_H__
#define __Model_H__

#include "RenderEngine/Manager.h"
#include "SubModel.h"
#include "CollisionDetection.h"

//namespace RE
namespace xs
{
	class Model;
    class IModelCallback;
	struct IRenderSystem;

	class Model : public IModel
	{
	public:
		#define MAX_REPLACABLE_SKIN_COUNT		3
		struct CreatureSkin
		{
			std::string strFileName[MAX_REPLACABLE_SKIN_COUNT];
			uint32	ui32Base;
		};
		friend struct SubModel;
	public:
		/** ����ģ�ͼ��β���
		@param frame ֡
		@param pRenderSystem ��Ⱦϵͳ
		@param pVBVertexBlend �����ϻ�����
		*/
		virtual void	updateGeometry(uint32 frame,IRenderSystem *pRenderSystem,IVertexBuffer *pVBVertexBlend);

		/** ����ģ��Ч������
		@param pRenderSystem ��Ⱦϵͳ
		*/
		virtual void	updateFX(IRenderSystem *pRenderSystem);

		/** ����ģ��
		@param pRenderSystem ��Ⱦϵͳ�ӿ�ָ��
		@param pCallback �ص�ָ��
		*/
		virtual void	render(IRenderSystem* pRenderSystem,IModelCallback *pCallback = 0);

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
		virtual uint32	getAnimationCount() ;

		/** �Ƿ�ӵ��ĳ������
		@param animation ��������
		@see enAnimation
		@return �������animation�����򷵻ش˶������ݣ����򷵻�0
		*/
		virtual Animation* hasAnimation(const std::string& animation) ;

		/** ��ÿ��Ի���Ƥ������
		@return Ƥ������
		*/
		virtual uint32	getSkinCount() ;

		/** ���õ�ǰƤ��
		@param index Ƥ�������±�
		@return ���ӵ�д�Ƥ�����򷵻�true����֮false
		*/
		virtual bool setSkin(uint32 index) ;

		/** �����ͼָ��
		@param index ��index����ͼ
		@return ��ͼָ��
		*/
		virtual ITexture* getTexture(uint32 index) ;\
			virtual bool hasBone(CPChar szBoneName) ;\
			virtual const Matrix4& getBoneMatrix(const char* szBoneName) ;\
			virtual const Vector3& getBonePivot(const char* szBoneName) ;\

			/** �����ģ�͵�����
			@return ��ģ�͵�����
			*/
			virtual uint32 getNumSubModels() ;

		/** ����ĳ����ģ�͵Ŀɼ���
		@param index ��ģ��������±�
		@param bVisible �Ƿ�ɼ�
		*/
		virtual void	setSubModelVisible(uint32 index,bool bVisible) ;

		/** �����ײ���ģ��
		@return ģ����ײ���ģ��
		*/
		virtual void*	getCollisionModel() ;

		/** �����ײ����Χ������
		@return ��ײ����Χ��
		*/
		virtual const AABB& getCollisionAABB() ;

		/** ��Ⱦģ��
		@param pRenderSystem ��Ⱦϵͳ�ӿ�ָ��
		*/
		virtual void	render_Instancing(IRenderSystem* pRenderSystem) ;

		/** ���ü�������
		@param tick ��ǰtick
		@param tickDelta ����tick���ϴ�tickʱ���
		@param pRenderSystem ��Ⱦϵͳ�ӿ�ָ��
		@param pCamera �����ָ��
		@param animation ��������
		*/
		virtual void	setGeometry_Instancing(IRenderSystem* pRenderSystem,IVertexBuffer *pVBVertexBlend) ;

		/** �����������
		@param pRenderSystem ��Ⱦϵͳ�ӿ�ָ��
		*/
		virtual void	resetGeometry_Instancing(IRenderSystem* pRenderSystem) ;

		/** ������ģ�͵���Ⱦ����
		@param index ��ģ��������±�
		@param pRenderSystem ��Ⱦϵͳ�ӿ�ָ��
		*/
		virtual void	setGeometrySubModel_Instancing(uint32 index,IRenderSystem* pRenderSystem) ;

		/** �����ģ�͵���Ⱦ����
		@param index ��ģ��������±�
		@param pRenderSystem ��Ⱦϵͳ�ӿ�ָ��
		*/
		virtual void	resetGeometrySubModel_Instancing(uint32 index,IRenderSystem* pRenderSystem) ;

		/** ��Ⱦ��ģ��
		@param index ��ģ��������±�
		@param pRenderSystem ��Ⱦϵͳ�ӿ�ָ��
		*/
		virtual void	renderSubModel_Instancing(uint32 index,IRenderSystem* pRenderSystem) ;

		/** ��Ⱦ��Ч
		@param tick ��ǰtick
		@param tickDelta ����tick���ϴ�tickʱ���
		@param pRenderSystem ��Ⱦϵͳ�ӿ�ָ��
		@param pCamera �����ָ��
		*/
		virtual void	renderFX_Instancing(Real tick,Real tickDelta,IRenderSystem* pRenderSystem,Camera* pCamera) ;

		/**
		#return ���VertexBlend���㻺���������ڶ�ÿ��ģ�͵�ʵ����VertexBlend
		*/
		virtual IVertexBuffer*	getVertexBlendBuffer() ;
	public:
		Model(const std::string& name,IRenderSystem* pRenderSystem);
		virtual ~Model();
		void	update(Real tick,Real tickDelta,IRenderSystem *pRenderSystem);

		IRenderSystem*		m_pRenderSystem;
	private:
		AABB	m_AABB;
		Sphere	m_BoundingSphere;

		std::string	m_strFilename;
	public:
		void	onGetBoundingVolumeData(Vector3 *p,uint32 ui32Vertices,Vector3 *pNormals,uint32 ui32Normals,uint16 *pIndices,uint32 ui32Indices);
		void	onGetName(char *szName);
		void	onGetVerticePositions(Vector3 *pVertices,uint32 ui32Vertices,uint32 ui32Stride);
		void	onGetVerticeNormals(Vector3 *pVertices,uint32 ui32Vertices,uint32 ui32Stride);
		void	onGetAnimatedVertice(AnimatedVertex *pVertices,uint32 ui32Vertices,uint32 ui32Stride);
		void	onGetVerticeTexcoords(Vector2 *pVertices,Uint32 ui32Vertices,Uint32 ui32Stride);
		void	onGetTexture(Uint32 index,Bool bReplacableTexture,Int32 type,CPChar fileName);
		void	onGetIndices(Uint16 *pIndices,Uint32 ui32Indices);
		void	onGetRenderPasses(const std::vector<SubModel>& vRenderPasses);
		void	onGetGlobalSequences(Int32 *pGlobalSequences,Uint32 ui32GlobalSequences);
		ParticleSystem*	onGetParticleSystem();
		RibbonSystem*	onGetRibbonSystem();
		Skeleton*	onGetSkeleton();
		Animation*	onGetAnimation(Uint32 start,Uint32 end,Bool bLoop,Int16 id,Uint32 rangeIndex);
		void	onGetSkin(const std::vector<CreatureSkin>& vSkin);
		void	onGetIsAnimated(Bool bAnimatedBones,Bool bAnimatedGeometry,Bool bNeedPerInstanceAnimation);
		ITexture*	getTexture(Int16 index){return m_textures[index];}
		Bone*		getBone(Int16 bone);
	private:
		IVertexBuffer	*m_pVBBoundingVertices;
		IVertexBuffer	*m_pVBBoundingNormals;
		IIndexBuffer	*m_pIBBounding;
		std::string			m_strModelName;
		IVertexBuffer	*m_pVBVertex;
		IVertexBuffer	*m_pVBNormal;
		IVertexBuffer	*m_pVBVertexNormal;			//for Animated models
		AnimatedVertex	*m_pOriginVertices;			//for Animated models
		IVertexBuffer	*m_pVBTexcoord;
		//Textures - Static Textures & Replacable Textures
		ITexture*		m_textures[32];
		Bool			m_useReplacableTextures[32];
		ITexture*		m_replacableTextures[32];
		Int32			m_replacableTextureTypes[32];
		IIndexBuffer	*m_pIB;
		std::vector<SubModel> m_vRenderPasses;
		Int32*			m_pGlobalSequences;
		std::vector<ParticleSystem*>	m_vParticleSystems;
		std::vector<RibbonSystem*>		m_vRibbonSystems;
		Skeleton*		m_pSkeleton;
		std::vector<Animation*>		m_vAnimations;
		std::hash_map<std::string,Animation*>	m_AnimationMap;
		Uint32				m_ui32VerticeNum;

		std::vector<CreatureSkin>	m_vSkin;
		Real				m_fLastCalcTime;
		Bool				m_bAnimatedGeometry,m_bAnimatedBones,m_bNeedPerInstanceAnimation;

		//Collision Detection
#ifdef SUPPORT_COLLISION_DETECTION
		CollisionDetection	m_cd;
#endif
		//Bounding Vertices for Collision Detection
		Vector3*			m_pBoundingVertices;
		Uint32*				m_pBoundingIndices;
		AABB				m_CollisionAABB;
		Sphere				m_CollisionSphere;
	private:
		void	calcAABB(Vector3 *pVertices,Uint32 ui32Vertices,Uint32 ui32Stride,AABB& aabb,Sphere& sphere);
		void	_update(Real tick,Real tickDelta,IRenderSystem *pRenderSystem,Camera* pCamera,const std::string& animation);
	};

}

#endif