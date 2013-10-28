#ifndef __ModelCodecWarcraft3_H__
#define __ModelCodecWarcraft3_H__

#include "RenderEngine/Manager.h"
#include "SubModel.h"
#include "ModelData.h"

namespace xs
{
	//+-----------------------------------------------------------------------------
	//| Warcraft3 Model constants
	//+-----------------------------------------------------------------------------
	const uint MODEL_DEFAULT_VERSION          = 800;
	const int MODEL_NAME_SIZE                  = 336;
	const int MODEL_NAME_CAMERA_SIZE           = 80;
	const int MODEL_NAME_TEXTURE_SIZE          = 256;
	const int MODEL_NAME_SEQUENCE_SIZE         = 80;
	const int MODEL_NAME_ATTACHMENT_SIZE       = 256;
	const int MODEL_NAME_PARTICLE_EMITTER_SIZE = 256;
	//+-----------------------------------------------------------------------------
	//| Node flags
	//+-----------------------------------------------------------------------------
	const DWORD NODE_FLAG_HELPER                   = 0;
	const DWORD NODE_FLAG_DONT_INHERIT_TRANSLATION = 1;
	const DWORD NODE_FLAG_DONT_INHERIT_ROTATION    = 2;
	const DWORD NODE_FLAG_DONT_INHERIT_SCALING     = 4;
	const DWORD NODE_FLAG_BILLBOARDED              = 8;
	const DWORD NODE_FLAG_BILLBOARDED_LOCK_X       = 16;
	const DWORD NODE_FLAG_BILLBOARDED_LOCK_Y       = 32;
	const DWORD NODE_FLAG_BILLBOARDED_LOCK_Z       = 64;
	const DWORD NODE_FLAG_CAMERA_ANCHORED          = 128;
	const DWORD NODE_FLAG_BONE                     = 256;
	const DWORD NODE_FLAG_LIGHT                    = 512;
	const DWORD NODE_FLAG_EVENT_OBJECT             = 1024;
	const DWORD NODE_FLAG_ATTACHMENT               = 2048;
	const DWORD NODE_FLAG_PARTICLE_EMITTER         = 4096;
	const DWORD NODE_FLAG_COLLISION_SHAPE          = 8192;
	const DWORD NODE_FLAG_RIBBON_EMITTER           = 16384;
	const DWORD NODE_FLAG_UNSHADED                 = 32768;
	const DWORD NODE_FLAG_EMITTER_USES_MDL         = 32768;
	const DWORD NODE_FLAG_SORT_PRIMITIVES_FAR_Z    = 65536;
	const DWORD NODE_FLAG_EMITTER_USES_TGA         = 65536;
	const DWORD NODE_FLAG_LINE_EMITTER             = 131072;
	const DWORD NODE_FLAG_UNFOGGED                 = 262144;
	const DWORD NODE_FLAG_MODEL_SPACE              = 524288;
	const DWORD NODE_FLAG_XY_QUAD                  = 1048576;

	const float GRAPHICS_DEFAULT_FIELD_OF_VIEW   = Math::PI / 4.0f;
	const float GRAPHICS_DEFAULT_NEAR_DISTANCE   = 1.0f;
	const float GRAPHICS_DEFAULT_FAR_DISTANCE    = 10000.0f;

	//+-----------------------------------------------------------------------------
	//| Collision shape type enumeration
	//+-----------------------------------------------------------------------------
	enum COLLISION_SHAPE_TYPE
	{
		COLLISION_SHAPE_TYPE_NONE,
		COLLISION_SHAPE_TYPE_BOX,
		COLLISION_SHAPE_TYPE_SPHERE,
	};


	class ModelCodecWarcraft3 : public ManagedItem,public IModel
	{
	public:
		virtual void release();

		/** ����ļ���
		@return �ļ���
		*/
		virtual const std::string& getFileName();

		/** ��ð�Χ������
		@return ģ�Ͱ�Χ��
		*/
		virtual const AABB&	getAABB();

		/** ��ð�Χ������
		@return ģ�Ͱ�Χ��
		*/
		virtual const Sphere& getBoudingSphere();

		/** ���ģ�Ͷ�����Ŀ
		@return ģ�Ͷ�����
		*/
		virtual uint	getAnimationCount();

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
		virtual Animation* hasAnimation(const std::string& animation);

		//��ȡģ�͵ĹǼ�
		virtual CoreSkeleton * getCoreSkeletion();

		/** �����ģ�͵�����
		@return ��ģ�͵�����
		*/
		virtual uint getNumSubModels();

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

		virtual MmParticleSystemData* getMmParticleSystem(uint index);

		virtual uint numMmParticleSystem();

		//////��ȡPartileSystem����
		////virtual  void * getParticleSystemParam(unsigned int index, string paramname, string & type, int & count );
		////void * aidGetPSParamVector( void * pParam, string paramtype, string & type, int paramcount, int & count);
		////void * aidGetPSParamsKeyFrames( ParticleEmitter2Data & mmpsdata, string paraname,string & type, int & count);
		//////����ParticleSystem����
		////virtual bool setParticleSystemParam(unsigned int index, string desname, void * psrc, int srcnum, string srctype);
		////bool aidSetPSParamVector(void * psrc, int srcnum, string srctype, void* pdes, int desnum, string destype, bool enablerange = false, float min = 0.0f, float max = 0.0f );
		////bool setPSKeyFramesParam(KeyFrames<float> * pkf, float * pParamVal, int iParamNum, string szParamType);
		//////����particlesystem
		////virtual bool addParticleSystem();
		//////ɾ��parriclesystem
		////virtual bool removeParticleSystem(unsigned int index);

		//////���ڽ�ģ��д���ļ�
		////virtual bool write(string filename);

		/**���ģ��ռ�õ��ڴ�
		*/
		virtual size_t getMomorySize();

	public:
		virtual ~ModelCodecWarcraft3();
		ModelCodecWarcraft3(const std::string& name,IRenderSystem* pRenderSystem);

	public:
		const char*	getType() const;
		bool decode(xs::Stream *pStream);

	private:
		//�����Ǽ�
		void createCoreSkeleton();
	public:
		IRenderSystem*	m_pRenderSystem;

		//ģ�Ͱ�Χ�а�Χ����Ϣ
		struct Extent
		{
			Extent()
			{
				radius = 0.0f;
				min = Vector3(0.0f, 0.0f, 0.0f);
				max = Vector3(0.0f, 0.0f, 0.0f);
			}

			float radius;
			Vector3 min;
			Vector3 max;
		};

		/// ģ�ͻ�����Ϣ
		struct ModelData
		{
			ModelData()
			{
				ver = MODEL_DEFAULT_VERSION;
				name[0] = 0;
				blendTime = 150;
			}

			uint ver;
			char name[MODEL_NAME_SIZE + 1];
			Extent extent;
			int blendTime;
		};
		ModelData model;

		/// ��ͼ������Ϣ
		struct TextureData
		{
			TextureData()
			{
				replaceableId = 0;

				wrapWidth = false;
				wrapHeight = false;

				fileName[0] = 0;

				internalTextureId = -1;
			}

			int replaceableId;

			bool wrapWidth;
			bool wrapHeight;

			char fileName[MODEL_NAME_TEXTURE_SIZE + 1];

			int internalTextureId;
		};
		std::vector<TextureData>	m_vTextures;

		/// ���ʲ�
		struct MaterialLayerData
		{
			MaterialLayerData()
			{
				blendMode = BM_OPAQUE;

				textureId = -1;
				textureAnimationId = -1;

				unshaded = false;
				unfogged = false;
				twoSided = false;
				sphereEnvironmentMap = false;
				noDepthTest = false;
				noDepthSet = false;
			}

			BlendMode blendMode;

			KeyFrames<int> animatedTextureId;
			KeyFrames<float> alpha;

			int textureId;
			int textureAnimationId;

			bool unshaded;
			bool unfogged;
			bool twoSided;
			bool sphereEnvironmentMap;
			bool noDepthTest;
			bool noDepthSet;
		};

		//��������
		struct MaterialData
		{
			MaterialData()
			{
				priorityPlane = 0;

				constantColor = false;
				sortPrimitivesFarZ = false;
				fullResolution = false;

				internalMaterialId = -1;
			}

			int priorityPlane;

			bool constantColor;
			bool sortPrimitivesFarZ;
			bool fullResolution;

			std::vector<MaterialLayerData*> layerContainer;

			int internalMaterialId;
		};
		std::vector<MaterialData> m_vMaterials;

		/// ��ͼ����
		struct TextureAnimationData
		{
			TextureAnimationData()
			{
				translation.setStaticData(Vector3(0,0,0));
				rotation.setStaticData(Quaternion(0,0,0,1));
				scale.setStaticData(Vector3(1,1,1));
				internalTextureAnimationId = -1;
			}

			KeyFrames<Vector3> translation;
			KeyFrames<Quaternion> rotation;
			KeyFrames<Vector3> scale;

			int internalTextureAnimationId;
		};
		std::vector<TextureAnimationData*> m_vTextureAnimations;

		/// Geoset Vertex Data
		class GeosetVertexData
		{
		public:
			GeosetVertexData()
			{
				position = Vector3(0,0,0);
				normal = Vector3(0,0,0);
				texturePosition = Vector2(0,0);
				vertexGroup = -1;
			}

			Vector3 position;
			Vector3 normal;
			Vector2 texturePosition;

			int vertexGroup;
		};

		/// Geoset Face Data
		class GeosetFaceData
		{
		public:
			GeosetFaceData()
			{
				index1 = -1;
				index2 = -1;
				index3 = -1;
			}

			short index1;
			short index2;
			short index3;
		};

		/// Geoset Group Node Data
		struct GeosetGroupNodeData
		{
			GeosetGroupNodeData()
			{
				nodeId = -1;
			}

			int nodeId;
		};

		/// Geoset Group Data
		class GeosetGroupData
		{
		public:
			GeosetGroupData()
			{
				matrixListSize = 0;
				mtx = Matrix4::IDENTITY;
			}

			void clear()
			{
				matrixListSize = 0;
				mtx = Matrix4::IDENTITY;
				matrixList.clear();
			}

			int matrixListSize;
			std::vector<GeosetGroupNodeData> matrixList;

			Matrix4 mtx;
		};

		/// Geoset Data
		struct GeosetData
		{
			GeosetData()
			{
				materialId = -1;
				selectionGroup = 0;

				unselectable = false;

				internalGeosetId = -1;
			}

			int materialId;
			int selectionGroup;

			bool unselectable;

			std::vector<GeosetVertexData> vertexContainer;
			std::vector<GeosetFaceData> faceContainer;
			std::vector<GeosetGroupData> groupContainer;
			std::vector<Extent> extentContainer;

			Extent extent;

			int internalGeosetId;
		};
		std::vector<GeosetData*> m_vGeosets;

		/// Geoset Animation Data
		struct GeosetAnimationData
		{
			GeosetAnimationData()
			{
				geosetId = -1;

				color.setStaticData(Color3(1.0f,1.0f,1.0f));
				alpha.setStaticData(1.0f);

				useColor = false;
				dropShadow = false;

				internalGeosetAnimationId = -1;
			}

			int geosetId;

			KeyFrames<Color3> color;
			KeyFrames<float> alpha;

			bool useColor;
			bool dropShadow;

			int internalGeosetAnimationId;
		};
		std::vector<GeosetAnimationData*> m_vGeosetAnimations;

		/// Bone
		struct BoneExtraData : public BoneData
		{
			BoneExtraData()
			{
				geosetId = -1;
				geosetAnimationId = -1;
			}

			int geosetId;
			int geosetAnimationId;
		};

		std::vector<BoneExtraData*> m_vBoneExtras;
		CoreSkeleton				m_skeleton;//�Ǽ�

		/// Lights
		struct LightData : public BoneData
		{
			LightData()
			{
				type = 0;

				attenuationStart.setStaticData(0);
				attenuationEnd.setStaticData(0);
				color.setStaticData(Color3(1.0f, 1.0f, 1.0f));
				intensity.setStaticData(0.0f);
				ambientColor.setStaticData(Color3(1.0f, 1.0f, 1.0f));
				ambientIntensity.setStaticData(0.0f);
				visibility.setStaticData(1.0f);
			}

			uint type;

			KeyFrames<float> attenuationStart;
			KeyFrames<float> attenuationEnd;
			KeyFrames<Color3> color;
			KeyFrames<float> intensity;
			KeyFrames<Color3> ambientColor;
			KeyFrames<float> ambientIntensity;
			KeyFrames<float> visibility;
		};

		std::vector<LightData*>	m_vLights;

		/// Helper
		struct HelperData : public BoneData
		{
			HelperData()
			{
			}
		};

		std::vector<HelperData*> m_vHelpers;

		/// Attachment
		struct AttachmentData : public BoneData
		{
			AttachmentData()
			{
				path[0] = 0;
				visibility.setStaticData(1.0f);

				attachmentId = -1;
			}

			char path[MODEL_NAME_ATTACHMENT_SIZE + 1];
			KeyFrames<float> visibility;

			int attachmentId;
		};

		std::vector<AttachmentData*> m_vAttachments;

		/// Pivot Points
		std::vector<Vector3> m_vPivotPoints;

		/// Particle Emitter
		struct ParticleEmitterData : public BoneData
		{
			ParticleEmitterData()
			{
				emissionRate.setStaticData(0.0f);
				gravity.setStaticData(0.0f);
				longitude.setStaticData(0.0f);
				latitude.setStaticData(0.0f);
				visibility.setStaticData(1.0f);

				particleFileName[0] = 0;
				particleLifeSpan.setStaticData(0.0f);
				particleInitialVelocity.setStaticData(0.0f);

				emitterUsesMdl = false;
				emitterUsesTga = false;
			}

			KeyFrames<float> emissionRate;
			KeyFrames<float> gravity;
			KeyFrames<float> longitude;
			KeyFrames<float> latitude;
			KeyFrames<float> visibility;

			char particleFileName[MODEL_NAME_PARTICLE_EMITTER_SIZE + 1];
			KeyFrames<float> particleLifeSpan;
			KeyFrames<float> particleInitialVelocity;

			bool emitterUsesMdl;
			bool emitterUsesTga;
		};

		std::vector<ParticleEmitterData*> m_vParticleEmitters;

		class Warcraft3ParticleEmitter2 : public BoneData,public ParticleEmitter2Data
		{
		};

		std::vector<Warcraft3ParticleEmitter2*> m_vParticleEmitter2s;

		/// Ribbon Emitter
		struct Warcraft3RibbonEmitter : public BoneData,public RibbonEmitterData
		{
		};

		std::vector<Warcraft3RibbonEmitter*> m_vRibbonEmitters;

		/// Event Object
		struct EventObjectData : public BoneData
		{
			EventObjectData()
			{
				globalSequenceId = -1;
			}

			int globalSequenceId;

			std::list<int> eventTrack;
		};

		std::vector<EventObjectData*> m_vEventObjects;

		/// Camera
		struct CameraData
		{
			CameraData()
			{
				name[0] = 0;

				source = Vector3(0.0f, 0.0f, 0.0f);
				target = Vector3(0.0f, 0.0f, 0.0f);

				sourceTranslation.setStaticData(Vector3(0.0f, 0.0f, 0.0f));
				targetTranslation.setStaticData(Vector3(0.0f, 0.0f, 0.0f));
				rotation.setStaticData(0.0f);

				fieldOfView = GRAPHICS_DEFAULT_FIELD_OF_VIEW;
				nearDistance = GRAPHICS_DEFAULT_NEAR_DISTANCE;
				farDistance = GRAPHICS_DEFAULT_FAR_DISTANCE;
			}

			char name[MODEL_NAME_CAMERA_SIZE + 1];

			Vector3 source;
			Vector3 target;

			KeyFrames<Vector3> sourceTranslation;
			KeyFrames<Vector3> targetTranslation;
			KeyFrames<float> rotation;

			float fieldOfView;
			float nearDistance;
			float farDistance;
		};
		std::vector<CameraData*> m_vCameras;

		/// CollisionShapeData
		struct CollisionShapeData : public BoneData
		{
			CollisionShapeData()
			{
				type = COLLISION_SHAPE_TYPE_BOX;
				boundsRadius = 0.0f;

				vertexList.push_back(Vector3(0.0f, 0.0f, 0.0f));
				vertexList.push_back(Vector3(0.0f, 0.0f, 0.0f));
			}

			COLLISION_SHAPE_TYPE type;
			float boundsRadius;
			std::list<Vector3> vertexList;
		};

		std::vector<CollisionShapeData*> m_vCollisionShapes;

		std::vector<Animation*>		m_vAnimations;
		std::vector<uint>			m_vGlobalSequences;
		std::vector<SubModel> m_vRenderPasses;

	private:
		template<class T> void	readKeyFrames(Stream *pStream,KeyFrames<T>& keyFrames,bool bScale);
		void readGeosetData(Stream* pStream,GeosetData* pData);
		void readBaseData(Stream* pStream,BoneData* pData,uint *pNodeType = 0);

	private:
		AABB		m_aabb;
		Sphere		m_sphere;

		typedef HASH_MAP_NAMESPACE::hash_map<std::string,Animation*> AnimationMap;
		AnimationMap m_AnimationMap;

		std::vector<SubModel> m_vSubModels;

		//VertexBuffer
		IVertexBuffer	*m_pVBTexcoord;
		//IndexBuffer
		IIndexBuffer	*m_pIB;

		uint m_numVertices;
		uint m_numFaces;

		std::vector<BoneData*>	m_vBones;

		//precomputed vertexbuffer
#define W3_PRECOMPUTED_VBO_COUNT_MAX ( 30 * 3 * 60 ) //֡��*ƽ������ʱ��*��������
		IVertexBuffer*	m_pPrecomputedVBs[ W3_PRECOMPUTED_VBO_COUNT_MAX /*8192*/];

		//Momory size
		size_t		m_memorySize;
	};
}

#endif