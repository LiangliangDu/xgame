#ifndef __I_ModelManager_H__
#define __I_ModelManager_H__
#include <string> //лѧ���޸�
using namespace std; //лѧ���޸�

namespace xs
{
	/*! \addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/

	class Camera;
	struct IRenderSystem;
	class Animation;
	struct ITexture;
	struct IVertexBuffer;
	class Skeleton;
	class CoreSkeleton;
	struct AnimationTime;
	class Material;
	struct GeosetAnimation;
	struct IShaderProgram;

#define VERTEX_BLEND_MATRICES_NUM		83 //������13,���ڲ��ܳ���83����ͬʱ��Ӧ��shader�ļ�����Ļ�Ͼ�����ҲҪ��ͬ
#define VERTEX_BLEND_MAPPINGS_NUM		256 //ģ�Ͱ����Ĺ����������޼�1�����һ��������Ϊ��Ԫ��һ����256����Ҫ��

	/** ��ģ�ͽӿ�
	*/
	struct ISubModel
	{
		/** �����ģ�͵�����
		@return ��ģ�͵�����
		*/
		virtual const char* getName() = 0;

		virtual ushort getIndexStart() = 0;

		virtual ushort getIndexCount() = 0;

		virtual ushort getVertexStart() = 0;

		virtual ushort getVertexEnd() = 0;

		virtual const Material&	getMaterial() = 0;

		virtual GeosetAnimation*	getGeosetAnimation() = 0;

		virtual bool	isAnimated() = 0;

		//��Ӳ����Ƥ��֧��

		/*��ȡ�󶨵��Ĺ�������������������Ĵ�С����ΪVERTEX_BLEND_MATRICES_NUM
		@validIndicesNum	��Ч�Ĺ�������������
		@return				 �󶨵��Ĺ���������
		*/
		virtual uchar *		getBindedBonesIndices(uint & validIndicesNum)=0;
	};

	/** ģ�ͽӿ�
	*/
	struct IModel
	{
		/**�벻Ҫʹ��release���ͷ�ģ�ͣ�Ӧ��ʹ��IModelManager::releaseModel����Ϊģ�������ü�������
		*/
		virtual void release() = 0;
		/** ����ļ���
		@return �ļ���
		*/
		virtual const std::string& getFileName() = 0;

		/** ��ð�Χ������
		@return ģ�Ͱ�Χ��
		*/
		virtual const AABB&	getAABB() = 0;

		/** ��ð�Χ������
		@return ģ�Ͱ�Χ��
		*/
		virtual const Sphere& getBoudingSphere() = 0;

		/** ���ģ�Ͷ�����Ŀ
		@return ģ�Ͷ�����
		*/
		virtual uint	getAnimationCount() = 0;

		/** ���ĳ������
		@param index �±�
		@return ����ָ��
		*/
		virtual Animation* getAnimation(uint index) = 0;

		/** �Ƿ�ӵ��ĳ������
		@param animation ��������
		@see enAnimation
		@return �������animation�����򷵻ش˶������ݣ����򷵻�0
		*/
		virtual Animation* hasAnimation(const std::string& animation) = 0;

		//��ȡģ�͵ĹǼ�
		virtual CoreSkeleton * getCoreSkeletion()=0;
	
		/** �����ģ�͵�����
		@return ��ģ�͵�����
		*/
		virtual uint getNumSubModels() = 0;

		/** �����ģ��ָ��
		@param name ��ģ������
		@return ��ģ��ָ��
		*/
		virtual ISubModel*	getSubModel(const char* name) = 0;

		/** �����±��������ģ��ָ��
		@param name ��ģ���±�
		@return ��ģ��ָ��
		*/
		virtual ISubModel*	getSubModel(int index) = 0;

		virtual IIndexBuffer*	getIndexBuffer() = 0;

		virtual IVertexBuffer*	getTexcoordBuffer() = 0;

		/**�������
		*/
		virtual uint getNumFaces() = 0;

		/**��ö�����
		*/
		virtual uint getNumVertices() = 0;

		/**��ð汾��
		*/
		virtual uint getVer() = 0;

		virtual IVertexBuffer* vertexBlend(Skeleton *pSkeleton,const AnimationTime *pTime) = 0;

		virtual uint numParticleSystem() = 0;

		virtual ParticleEmitter2Data*	getParticleSystemData(uint index) = 0;

		virtual uint numRibbonSystem() = 0;

		virtual RibbonEmitterData*	getRibbonSystemData(uint index) = 0;

		virtual uint numMmParticleSystem() = 0;

		virtual MmParticleSystemData* getMmParticleSystem(uint index) = 0;

		
		//����ָ��ʱ�������ӳ��,����ֵ������ͨ����������AnimationTime:��ǰ��ʱ��
		virtual int texBlend(const AnimationTime *pTime){ return 0;}
		//��ȡָ��ʱ���������,����ֵ��ָ��ͨ���������棬pass��ָ��ͨ����pTime��ָ��ʱ��
		virtual IVertexBuffer* getTexCoordBuffer(int pass){ return 0;}
		//�ж�ģ���Ƿ����uv����
		virtual bool isAnimatedTexCoord(){ return false;}

		//MMParticleSystem
		virtual  void * getMMParticleSystemParam(unsigned int index, string paramname, string & type, int & count ){return 0;}
		virtual bool setMMParticleSystemParam(unsigned int index, string desname, void * psrc, int srcnum, string srctype){ return false;}
		virtual bool addMMParticleSystem(){return false;}
		virtual bool removeMMParticleSystem(unsigned int index){return false;}

		//ParticleSystem
		virtual  void * getParticleSystemParam(unsigned int index, string paramname, string & type, int & count){return 0;}
		virtual bool setParticleSystemParam(unsigned int index, string desname, void * psrc, int srcnum, string srctype){ return false;}
		virtual bool addParticleSystem(){return false;}
		virtual bool removeParticleSystem(unsigned int index){return false;}

		//Ribbon System
		virtual void * getRibbonSystemParam( unsigned int index, string paramname, string & type, int &count){return 0;}
		virtual bool setRibbonSystemParam( unsigned int index, string desname, void * psrc, int srcnum, string srctype){ return false;}
		virtual bool addRibbonSystem(){ return false;}
		virtual bool removeRibbonSystem(unsigned int index){ return false;}

		
		//��ģ��д���ļ�
		virtual bool write(string filename,float fCopress) { return false;}

		/**���ģ��ռ�õ��ڴ�
		*/
		virtual size_t getMomorySize() = 0;

		//��չ,����ģ�͵Ĳ����趨
		//��ȡboundingbox
		virtual void getBoundingBox( Vector4 &rect){ rect.x = -1.0f;rect.y =-1.0f;rect.z = 1.0f;rect.w = 1.0f;}
		//��ȡģ�ͻ�����չ����
		virtual void * getExtParam(std::string strParamName, std::string & strType, int & count)
		{
			//���������²�����
			//nodeScale��node�ĳ�ʼ����
			strType ="";
			count = 0;
			return 0;
		}
		//����ģ�ͻ�������
		virtual bool setExtParam( std::string strParamName, void * psrc, int srcnum, string srctype)
		{
			return false;
		}

		//�����û�������Ⱦ˳��
		virtual bool enableCustomizeRenderOrder(bool enable) { return false; };
		virtual bool isEnabledCustomizeRenderOrder() { return false;};
		enum{ ECustomizeRenderOrderObject_SubModel = 0, ECustomizeRenderOrderObject_ParticleSystem, ECustomizeRenderOrderObject_RibbonSystem,
		ECustomizeRenderOrderObject_MMParticleSystem, ECustomizeRenderOrderObject_Max,};
		virtual bool setCustomizeRenderOrder( uint objectType, uint index, int order){return false;};
		virtual int	getCustomizeRenderOrder(uint objectType, uint index){return 0;}		

		//�Ƿ���Ҫ������Ӱ
		virtual bool	needDrawShadow(){ return true;}

		//��Ӳ����Ƥ��֧��

		//��ȡ�����ϵĹ���Ȩ��buffer
		virtual IVertexBuffer *	getBlendWeightBuffer() { return 0;};
		//��ȡ�����ϵ�����Buffer
		virtual IVertexBuffer * getBlendIndicesBuffer(uint subModelIndex) { return 0;}
		//��ȡ��ʼ�Ķ���buffer
		virtual IVertexBuffer * getOriginVertexBuffer() { return 0;}
		//��ȡ�����ϵ�shader,Ҳ�������ж��Ƿ���Ӳ������
		virtual IShaderProgram * getBlendShaderProgram() { return 0;};
	}; 

	/** ģ�͹������ӿ�
	*/
	struct IModelManager
	{
		/** ����ģ�͹�����
		*/
		virtual void 		release() = 0;				

		virtual char*		getFirstModelExt() = 0;

		virtual char*		getNextModelExt() = 0;
		/** ����ģ��
		@param fileName ģ���ļ���
		@return ģ�ͽӿ�ָ��
		*/
		virtual IModel*		loadModel(const char* fileName) = 0;

		/** ���ļ�����ȡģ�ͽӿ�ָ��
		@param fileName ģ���ļ���
		@return ģ�ͽӿ�ָ��
		*/
		virtual IModel*		getByName(const char* fileName) = 0;					

		/** ����ģ��
		@param pModel ģ�ͽӿ�ָ��
		*/
		virtual void 		releaseModel(IModel* pModel) = 0;				

		/** ������������ģ��
		@param fileName ģ���ļ���
		*/
		virtual void 		releaseModel(const char* fileName) = 0;				

		/** ��������ģ��
		*/
		virtual void 		releaseAll() = 0;
	};
	//add by yhc 2010.1.29
	//ȥ���ظ��Ͷ����keyframe 
	//λ��
	void CompressPos(KeyFrames<Vector3> &inKeyFramesPos,KeyFrames<Vector3> &outKeyFramesPos,float fRange);
	void CompressQua(KeyFrames<Quaternion>  &inKeyFramesQua,KeyFrames<Quaternion>  &outKeyFramesQua,float fRange);
			

	extern "C" __declspec(dllexport) IModelManager* LoadModelManager(IRenderSystem* pRenderSystem);
	/** @} */
}

#endif