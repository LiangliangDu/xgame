#ifndef __ModelData_H__
#define __ModelData_H__

namespace xs
{
	const int MODEL_NAME_NODE_SIZE             = 80;

	/// Model Animations
	struct GeosetAnimation
	{
		GeosetAnimation()
		{
			alpha.setStaticData(1.0f);
		}

		KeyFrames<float>	alpha;
	};
//////////////////////////////////////////////////////////////////////
	struct ModelKeyframeTM
	{
		float tm[4][4];
		int time;
	};
/////////////////////////////////////////////////////////////////////
	/// Bone
	struct BoneData
	{
		size_t getMemorySize()
		{
			return sizeof(*this) + translation.getMemorySize() + rotation.getMemorySize() + scale.getMemorySize();
		}

		BoneData()
		{
			name[0] = 0;

			objectId = -1;
			parentId = -1;

			translation.setStaticData(Vector3(0.0f, 0.0f, 0.0f));
			rotation.setStaticData(Quaternion(0.0f, 0.0f, 0.0f, 1.0f));
			scale.setStaticData(Vector3(1.0f, 1.0f, 1.0f));

			dontInheritTranslation = false;
			dontInheritRotation = false;
			dontInheritScaling = false;
			billboarded = false;
			billboardedLockX = false;
			billboardedLockY = false;
			billboardedLockZ = false;
			cameraAnchored = false;

			pivotPoint = Vector3(0.0f, 0.0f, 0.0f);

			pivotRotation = false;

			precomputeMtx = Matrix4::IDENTITY;

			initTrans = Vector3::ZERO;
			initQuat = Quaternion::IDENTITY;
			initScale = Vector3::UNIT_SCALE;
		}

		//��ͷ���ݸ�ֵ����,xxh 20090929,���ڹ������ݿ���
		const BoneData & operator = ( const BoneData & bonedata)
		{
			strncpy( name, bonedata.name, MODEL_NAME_NODE_SIZE);
			name[MODEL_NAME_NODE_SIZE] = '\0';
			objectId = bonedata.objectId;
			parentId = bonedata.parentId;
			translation = bonedata.translation;
			rotation = bonedata.rotation;
			scale = bonedata.scale;
			m_TMVector = bonedata.m_TMVector;
			dontInheritTranslation = bonedata.dontInheritTranslation;
			dontInheritRotation = bonedata.dontInheritRotation;
			dontInheritScaling = bonedata.dontInheritScaling;
			billboarded = bonedata.billboarded;
			billboardedLockX = bonedata.billboardedLockX;
			billboardedLockY = bonedata.billboardedLockY;
			billboardedLockZ = bonedata.billboardedLockZ;
			cameraAnchored = bonedata.cameraAnchored;
			pivotPoint = bonedata.pivotPoint;
			pivotRotation = bonedata.pivotRotation;
			initTrans = bonedata.initTrans;
			initQuat = bonedata.initQuat;
			initScale = bonedata.initScale;
			precomputeMtx = bonedata.precomputeMtx;
			return *this;
		}
	
		char name[MODEL_NAME_NODE_SIZE + 1];

		int objectId;
		int parentId;

		KeyFrames<Vector3> translation;
		KeyFrames<Quaternion> rotation;
		KeyFrames<Vector3> scale;
		std::vector<ModelKeyframeTM> m_TMVector;

		bool dontInheritTranslation;
		bool dontInheritRotation;
		bool dontInheritScaling;
		bool billboarded;
		bool billboardedLockX;
		bool billboardedLockY;
		bool billboardedLockZ;
		bool cameraAnchored;

		Vector3 pivotPoint;

		bool pivotRotation;

		//ģ�ͻ����任
		Vector3 initTrans;
		Quaternion initQuat;
		Vector3 initScale;


		Matrix4	precomputeMtx;
	};

	/// Particle Emitter2
	struct ParticleEmitter2Data
	{
		ParticleEmitter2Data()
		{
			filterMode = BM_OPAQUE;

			speed.setStaticData(0.0f);
			variation.setStaticData(0.0f);
			latitude.setStaticData(0.0f);
			gravity.setStaticData(0.0f);
			visibility.setStaticData(1.0f);
			emissionRate.setStaticData(0.0f);
			width.setStaticData(0.0f);
			length.setStaticData(0.0f);

			segmentColor1 = Color3(1.0f, 1.0f, 1.0f);
			segmentColor2 = Color3(1.0f, 1.0f, 1.0f);
			segmentColor3 = Color3(1.0f, 1.0f, 1.0f);
			alpha = Vector3(1.0f, 1.0f, 1.0f);//��(255,255,255)�ĳ�(1,1,1)
			particleScaling = Vector3(1.0f, 1.0f, 1.0f);
			headLifeSpan = Vector3(0.0f, 0.0f, 1.0f);
			headDecay = Vector3(0.0f, 0.0f, 1.0f);
			tailLifeSpan = Vector3(0.0f, 0.0f, 1.0f);
			tailDecay = Vector3(0.0f, 0.0f, 1.0f);

			rows = 1;
			columns = 1;
			textureId = -1;
			priorityPlane = 0;
			replaceableId = 0;
			time = 0.0f;
			lifeSpan = 0.0f;
			tailLength = 0.0f;

			sortPrimitivesFarZ = false;
			lineEmitter = false;
			modelSpace = false;
			alphaKey = false;
			unshaded = true;//Ĭ�Ϲرչ���
			unfogged = true;//Ĭ�Ϲر���
			xyQuad = false;
			squirt = false;
			head = false;
			tail = false;

			boneObjectId = -1;
			//added by xxh for version 5
			bEnhanceValue = false;
			bEnableSynScale = false;
			vInitSynScale = Vector3(1,1,1);
			memset(name,0,16);
			bEmmitTime2Space= false;
			iSpaceInterType = 1;
			fSpaceUint = 1.0f;
			attach2Bone = false;//Ĭ��Ϊ���󶨵�����

			nIntervalTime = 0;//Ĭ�ϲ���ת
			nAngle = 0;

			bNodeInitMatrix = true;
		}

		BlendMode filterMode;

		KeyFrames<float> speed;
		KeyFrames<float> variation;
		KeyFrames<float> latitude;
		KeyFrames<float> gravity;
		KeyFrames<float> visibility;
		KeyFrames<float> emissionRate;
		KeyFrames<float> width;
		KeyFrames<float> length;

		Color3 segmentColor1;
		Color3 segmentColor2;
		Color3 segmentColor3;
		Vector3 alpha;
		Vector3 particleScaling;
		Vector3 headLifeSpan;
		Vector3 headDecay;
		Vector3 tailLifeSpan;
		Vector3 tailDecay;

		int rows;
		int columns;
		int textureId;
		int priorityPlane;
		int replaceableId;
		float time;
		float lifeSpan;
		float tailLength;

		bool sortPrimitivesFarZ;
		bool lineEmitter;
		bool modelSpace;
		bool alphaKey;
		bool unshaded;
		bool unfogged;
		bool xyQuad;
		bool squirt;
		bool head;
		bool tail;

		std::string textureFilename;
		int boneObjectId;

		//added by xxh for version 5
		bool bEnhanceValue ;//������a���ʱ����ǿ����
		bool bEnableSynScale;//�Ƿ�����ͬ���Ŵ�
		Vector3 vInitSynScale;//ģ�͵ĳ�ʼ�Ŵ���ʣ�����ͬ���������������ʣ�������Χ�ȿռ����
		char name[16];//����ϵͳ�����֣������ʶ����ϵͳ
		bool bEmmitTime2Space;//ʱ��ת��Ϊ�ռ������������
		int iSpaceInterType;//�ռ����ʱ�Ĳ�ֵ����,1Ϊֱ���ͣ�2Ϊ������
		float fSpaceUint;//�ռ���ȵĵ�λ

		//added by xxhf for version 7
		bool  attach2Bone;//�Ƿ�󶨵�����

		//added by zgz for version 8
		//֧��������z����ת
		int    nIntervalTime; //��ת���ʱ��
		int    nAngle;        //��ת�Ƕ�

		//added by zgz for version 9
		// ���Ӱ󶨵�����ʱ����Ҫ�������ĳ�ʼ����һ�����㣬�汾12��ǰ������ϵͳ��û�п��ǣ�����һ��bug��
		// Ϊ�˱�����ǰ�����õ���Ч�����������������ʶ�Ƿ���Ҫ���ǳ�ʼ����[5/18/2011 zgz]
		bool  bNodeInitMatrix;
	};

	/// Ribbon Emitter
	struct RibbonEmitterData
	{
		RibbonEmitterData()
		{
			heightAbove.setStaticData(0.0f);
			heightBelow.setStaticData(0.0f);
			alpha.setStaticData(1.0f);
			color.setStaticData(Color3(1.0f, 1.0f, 1.0f));
			textureSlot.setStaticData(0);
			visibility.setStaticData(1.0f);

			emissionRate = 0.0f;
			lifeSpan = 0.0f;
			gravity = 0.0f;
			rows = 1;
			columns = 1;
			materialId = -1;

			filterMode = BM_OPAQUE;
			boneObjectId = -1;
			bEnhanceValue= false;
			bEnableSynScale = false;
			vInitSynScale = Vector3(1,1,1);
			memset(name,0,16);
			attach2Bone = false;

			fadeoutmode = 0;//0��ͨ��ʧģʽ,1ָ����ʧģʽ

			//added by xxh for version 9 
			//����ָ��Ʈ������
			enableAssignUpDir = false;//�Ƿ�����ָ�����Ϸ���Ĭ�ϲ�����
			vAssignedUpDir = Vector3(0.0f,1.0f,0.0f);//���ϵķ���
			
			fadespeed = 1.0f;
		}

		KeyFrames<float> heightAbove;
		KeyFrames<float> heightBelow;
		KeyFrames<float> alpha;
		KeyFrames<Color3> color;
		KeyFrames<int> textureSlot;
		KeyFrames<float> visibility;

		float emissionRate;
		float lifeSpan;
		float gravity;
		int rows;
		int columns;
		int materialId;

		BlendMode filterMode;
		std::string textureFilename;
		int	boneObjectId;

		//added by xxh for version 5
		bool bEnhanceValue ;//������a���ʱ����ǿ����
		bool bEnableSynScale;//�Ƿ�����ͬ���Ŵ�
		Vector3 vInitSynScale;//ģ�͵ĳ�ʼ�Ŵ���ʣ�����ͬ���������������ʣ�������Χ�ȿռ����
		char name[16];//Ʈ��ϵͳ�����֣������ʶ����ϵͳ

		//added by xxhf for version 7
		bool  attach2Bone;//�Ƿ�󶨵����������������ʱû�õ�

		//added by xxh for version 8
		int		fadeoutmode;//Ʈ����ʧģʽ���ڰ汾10�У��˲�����ȡ��

		//added by xxh for version 9 
		//����ָ��Ʈ������
		bool enableAssignUpDir;//�Ƿ�����ָ�����Ϸ���Ĭ�ϲ�����
		Vector3 vAssignedUpDir;//���ϵķ���

		//added by xxh for version 10
		float	fadespeed;//Ʈ����ʧ�ٶȣ��˶��ٶȳɷ���
	};

	/// MmParticleEmitterData

	struct MmTexCoordSet
	{
		Vector2 tc[4];
	};

	struct MmParticleSystemParamData
	{
		float mid;
		Color4 colors[3];
		float sizes[3];
		short d[10];
		float unk[3];
		float scales[3];
		float slowdown;
		float rotation;
		float f2[16];
	};

	struct MmParticleSystemData
	{
		MmParticleSystemData()
		{
			bEnhanceValue = false;//������a���ʱ����ǿ����
			bEnableSynScale =false;//�Ƿ�����ͬ���Ŵ�
			vInitSynScale = Vector3(1,1,1);//ģ�͵ĳ�ʼ�Ŵ���ʣ�����ͬ���������������ʣ�������Χ�ȿռ����	
			memset(name,0,16);
			bEmmitTime2Space = false;
			iSpaceInterType = 1;
			fSpaceUint = 1.0f;
			attach2Bone = 0;//Ĭ�ϲ��󶨵�����
			nIntervalTime = 0;//Ĭ�ϲ���ת zgz
			nAngle  = 0;
			bNodeInitMatrix = true;
			memset(iteratorArea, 0, sizeof(iteratorArea));
		}
		int id;
		BillboardType billboardType;
		Vector3 pos;
		short bone;
		std::string texture;
		short blend;
		short emitterType;
		short type;
		int order;
		short s2;
		short cols;
		short rows;
		KeyFrames<float> speed;
		KeyFrames<float> variation;
		KeyFrames<float> spread;
		KeyFrames<float> lat;
		KeyFrames<float> gravity;
		KeyFrames<float> lifespan;
		KeyFrames<float> rate;
		KeyFrames<float> areal;
		KeyFrames<float> areaw;
		KeyFrames<float> grav2;
		MmParticleSystemParamData p;
		std::vector<MmTexCoordSet> vTexcoords;
		//added by xxh for version 5
		bool bEnhanceValue ;//������a���ʱ����ǿ����
		bool bEnableSynScale;//�Ƿ�����ͬ���Ŵ�
		Vector3 vInitSynScale;//ģ�͵ĳ�ʼ�Ŵ���ʣ�����ͬ���������������ʣ�������Χ�ȿռ����
		char name[16];//����ϵͳ�����֣������ʶ����ϵͳ
		bool bEmmitTime2Space;//ʱ��ת��Ϊ�ռ������������
		int iSpaceInterType;//�ռ��Ͼ��ȵ����ͣ�1Ϊֱ���ͣ�2Ϊ������
		float fSpaceUint;//�ռ���ȵĵ�λ

		//added by xxh for version 7
		short attach2Bone;//�Ƿ�󶨵�����

		//added by zgz for version 8
		//֧�ֵ�������������z����ת
		int    nIntervalTime; //��ת���ʱ��
		int    nAngle;        //��ת�Ƕ�

		//added by zgz for version 9
		// ���Ӱ󶨵�����ʱ����Ҫ�������ĳ�ʼ����һ�����㣬�汾12��ǰ������ϵͳ��û�п��ǣ�����һ��bug��
		// Ϊ�˱�����ǰ�����õ���Ч�����������������ʶ�Ƿ���Ҫ���ǳ�ʼ����[5/18/2011 zgz]
		bool  bNodeInitMatrix;

		// ������Χ
		int   iteratorArea[2];
	};
}

#endif