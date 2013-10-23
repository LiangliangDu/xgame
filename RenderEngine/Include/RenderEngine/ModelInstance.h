#ifndef __ModelInstance_H__
#define __ModelInstance_H__

#include <set>
#include "SubModelInstance.h"
#include "Skeleton.h"

namespace xs
{
	/*! \addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/

	class ModelNode;
	class Material;
	class Bone;
	class ParticleSystem;
	class RibbonSystem;
	class MmParticleSystem;

	/// ����������һ���Ļص�
	struct IAnimationCallback
	{
		virtual void onOneCycle(const std::string& animation,int loopTimes) = 0;
	};

	/** ģ��ʵ����һ��ģ�Ϳ����ڳ������ж��ʵ��
	*/
	class _RenderEngineExport ModelInstance
	{
	public:
		//ModelNode
		virtual void updateRenderQueue(RenderQueue* pRenderQueue);
	public:

		void updateColor(IRenderSystem* pRenderSystem,const ColorValue& diffuse);

		/** �����������Ⱦ����ʹ���л�������Լ���״̬
		@param tick ��ǰtick
		@param tickDelta ����tick���ϴ�tick ʱ���
		@param pRenderSystem ��Ⱦϵͳ�ӿ�ָ��
		@param pCamera �����ָ��
		*/
		virtual void  update(float tick,float tickDelta,IRenderSystem* pRenderSystem,const ColorValue& diffuse);

		/**ȡ��Model����
		*/
		inline IModel* getModel()const{return m_pModel;}

		/**��ð�Χ��
		*/
		inline const AABB&	getAABB();

		/**��ð�Χ��
		*/
		inline const Sphere& getBoundingSphere();

		/**���õ�ǰ�Ķ���
		@param animation ����������
		@param loopTimes ѭ��������-1��ʾһֱѭ��
		*/
		inline bool			setCurrentAnimation(const std::string& animation,int loopTimes = -1);

		// add by zjp����ȡ��ǰ�����ĺ�ʱ
		inline int			getAnimationTicks(const std::string& animation);

		inline void			advanceTime(float tickDelta);

		inline void setAnimationTime(uint time);

		inline AnimationTime*	getAnimationTime();
		/**��õ�ǰ��������
		*/
		inline const std::string& getCurrentAnimation();

		inline Animation* _getCurrentAnimation();

		/**���ö����ٶ�
		@param speed �ٶ�
		*/
		inline void	setAnimationSpeed(float speed);
		float getAnimationSpeed() { return m_speed; }

		ModelNode* getModelNode();

		bool setModel(const char* modelName,ModelNode *pNode);

		Bone*	getBone(const char*boneName);

		uint getAnimationCount();

		Animation* getAnimation(uint index);

		uint getBoneCount();



		Bone* getBone(int index);

		const std::string& getFileName();

		uint getNumFaces();

		uint getNumVertices();

		uint getNumSubModels();

		SubModelInstance*	getSubModel(const char* subModelName);

		SubModelInstance*	getFirstSubModel();
		SubModelInstance*	getNextSubModel();

		uint getVer();

		void showAllSubModels(bool show);

		void setCallback(IAnimationCallback *pCallback){m_pCallback = pCallback;}

		IAnimationCallback* getCallback(){return m_pCallback;}

		void resetFX();

		size_t getMemorySize();

		void showRibbonSystem(bool bShow);

	public:
		IIndexBuffer*	getIndexBuffer();
		IVertexBuffer*	getVertexBuffer();
		IVertexBuffer*	getVertexBufferTexcoord();
		IVertexBuffer*	getBlendWeightBuffer();
		IVertexBuffer*  getBlendIndicesBuffer(uint subModelIndex);
		IShaderProgram* getBlendShaderProgram();
		//�붯����غ��� added by xxh 20090930
		inline ulong _getLastUpdateTime(){ return m_lastUpdateTime;};//��ȡ������ʱ�䣬�˺������Ǻܾ�ȷ��һ�㲻����ʹ��
		inline int _getCurrentLoops() {return m_loopTimes;};//��ȡ��ǰʣ���ѭ��������

		//�Ƿ���Ҫ������Ӱ
		bool			needDrawShadow();



			//add by yhc
		//���ö�Ӧʱ��Ķ�������ָ��
		void SetVBOByTime(float tickCurrent);
	public:

		ModelInstance();

		~ModelInstance();

	private:
		IModel*		m_pModel;

		//Animation
		std::string	m_currentAnimation;
		Animation*	m_pCurrentAnimation;

		//VertexBlend
		IVertexBuffer*	m_pVBVertexBlend;
		IIndexBuffer*	m_pIB;
		IVertexBuffer*	m_pVBTexcoord;
		IVertexBuffer*  m_pVBBlendWeight;
		std::vector<IVertexBuffer*> m_vBlendIndices;
		IShaderProgram* m_pBlendShaderProgram;

		//�Ƿ���Ҫ������Ӱ
		bool			m_needDrawShadow;

		//Loop
		int			m_loopTimes;
		AnimationTime		m_currentTime;
		float		m_speed;

		//SubModels
		typedef std::vector<SubModelInstance*> SubModelList;
		SubModelList	m_subModels;
		SubModelList::iterator m_iteratorSubModel;

		ModelNode*	m_pNode;

		//Skeleton
		Skeleton	m_skeleton;

		//ParticleSystem
		typedef std::vector<ParticleSystem*> ParticleSystemList;
		ParticleSystemList m_vParticleSystem;

		//RibbonSystem
		typedef std::vector<RibbonSystem*> RibbonSystemList;
		RibbonSystemList m_vRibbonSystem;

		//MmParticleSystem
		typedef std::vector<MmParticleSystem*> MmParticleSystemList;
		MmParticleSystemList m_vMmParticleSystem;

		//Animation Callback
		IAnimationCallback*		m_pCallback;

		ulong	m_lastUpdateTime;
	private:

		//void loadBone(Bone *pBone,BoneData *pData);//ȡ���˺���

		
		//лѧ����ӣ����ڴ�������ϵͳ
		//
		
		//лѧ����ӣ��������ò�ͬ�������еĶ���ʱ��
		private:
		bool setAllPSCurAnimationTime( uint aniStart, uint aniEnd);

		// ֹͣ�����µ����� [4/26/2011 zgz]
		public:
		void SetGenerateParticle(bool bGenerate);
		int  GetAllParticleNum();

		//��MMParticleSystem for modelviewer
		public:	
		int GetMMParticleSystemCount();
		void * getMMParticleSystemParam(unsigned int index, string paramname, string & type, int & count );
		bool setMMParticleSystemParam(unsigned int index, string desname, void * psrc, int srcnum, string srctype);
		bool addMMParticleSystem();
		bool removeMMParticleSystem(unsigned int index);
		
		//��ParticleSystem for modelviewer
		public:
		int GetParticleSystemCount();
		void * getParticleSystemParam(unsigned int index, string paramname, string & type, int & count );
		bool setParticleSystemParam(unsigned int index, string desname, void * psrc, int srcnum, string srctype);
		bool addParticleSystem();
		bool removeParticleSystem(unsigned int index);

		//��RibbonSystem for modelviewer
		public:
		int getRibbonSystemCount();
		void * getRibbonSystemParam( unsigned int index, string paramname, string & type, int &count);
		bool setRibbonSystemParam( unsigned int index, string desname, void * psrc, int srcnum, string srctype);
		bool addRibbonSystem();
		bool removeRibbonSystem(unsigned int index);

		//����ģ�ͻ�������
		bool setExtParam( std::string strParamName, void * psrc, int srcnum, string srctype);

		//�û��Զ���ģ�͵���Ⱦ˳��
		bool isEnableCustomizeRenderOrder();
		bool enableCustomizeRenderOrder(bool enable);
		bool setCustomizeRenderOrder( uint objectType, uint index, int order);
		void getCustomizeRenderOrder(std::vector<int> & listRenderOrder, std::vector<int> & listObjectType, std::vector<int> & listIndex, std::vector<std::string> & listname);
		
		//лѧ�Ա�д�����ڽ�ģ��д���ļ�
		public:		
		bool writeModel(string filename,float fCopress/*ѹ������*/ = 0.0f);

		//added by xiexuehui for uv animation 2009/07/24
		//�ж�ģ���Ƿ����uv����
		bool isAnimatedTexCoord();
		//��ȡָ��ʱ���������,����ֵ��ָ��ͨ���������棬pass��ָ��ͨ����pTime��ָ��ʱ��
		IVertexBuffer* getTexCoordBuffer(int pass);
		//added end 
	};
	/** @} */
}

#endif