#ifndef __SceneNode_H__
#define __SceneNode_H__

#include <set>
#include "RenderQueue.h"

namespace xs
{

	/** ģ���γ�һ����״�ṹ������һ��ģ��ĳ�����ϰ��˸����������൱��������ģ�͵���Node��
	�����ģ�ͺ������γɵ������ֿ�����Ϊһ��Node�ҵ�����һ��ģ�͵Ĺ�����
	*/

	class ModelInstance;
	class Bone;

	class _RenderEngineExport ModelNode
	{
	public:

		/**
		*/
		virtual void		release();
		/** ��������任���AABB
		@return ��Χ��
		*/
		virtual const AABB&		getWorldAABB(void) const;

		virtual const Sphere&	getWorldSphere(void) const;

		/** ��ȡ���ڵ��ָ��
		@return ���ڵ�ָ��
		*/
		virtual ModelNode* getParent(void) const;	

		/** ��ȡ��λ
		@return ��λ4Ԫ��
		*/
		virtual const Quaternion &getOrientation() const;	

		/** ���÷�λ
		@param q ��λ��Ԫ��
		*/
		virtual void setOrientation(const Quaternion& q);	

		/** ���÷�λ
		@param w ��λ��Ԫ��w����
		@param x ��λ��Ԫ��x����
		@param y ��λ��Ԫ��y����
		@param z ��λ��Ԫ��z����
		*/
		virtual void setOrientation( float w, float x, float y, float z);

		/** ���÷�λ����ʼ״̬
		*/
		virtual void resetOrientation(void);

		/** ���ýڵ�λ��
		@param pos �ڵ�λ��
		*/
		virtual void setPosition(const Vector3& pos);

		/** ���ýڵ�λ��
		@param x λ��x����
		@param y λ��y����
		@param z λ��z����
		*/
		virtual void setPosition(float x, float y, float z);	

		/** ��ýڵ�λ��
		@return �ڵ�λ��
		*/
		virtual const Vector3 & getPosition(void) const;	

		/** ���ýڵ����ű���
		@param scale ���ű���
		*/
		virtual void setScale(const Vector3& scale);

		/** ���ýڵ����ű���
		@param x ���ű���x����
		@param y ���ű���y����
		@param z ���ű���z����
		*/
		virtual void setScale(float x, float y, float z);

		/** ��ýڵ����ű���
		@return �ڵ����ű���
		*/
		virtual const Vector3 & getScale(void) const;

		/** ���Ŵ˽ڵ�
		@param scale ���ű���
		*/
		virtual void scale(const Vector3& scale);	

		/** ���Ŵ˽ڵ�
		@param x ���ű���x����
		@param y ���ű���y����
		@param z ���ű���z����
		*/
		virtual void scale(float x, float y, float z);	

		/** �ƶ��˽ڵ�
		@param d ����
		@see TransformSpace
		*/
		virtual void translate(const Vector3& d);	

		/** �ƶ��˽ڵ�
		@param x �����x����
		@param y �����y����
		@param z �����z����
		@see TransformSpace
		*/
		virtual void translate(float x, float y, float z);

		/** ���Զ��������ϵ���ƶ��˽ڵ�
		@param axes �Զ��������ϵ
		@param move ����
		@see TransformSpace
		*/
		virtual void translate(const Matrix3& axes, const Vector3& move);

		/** ���Զ��������ϵ���ƶ��˽ڵ�
		@param axes �Զ��������ϵ
		@param x �����x����
		@param y �����y����
		@param z �����z����
		@see TransformSpace
		*/
		virtual void translate(const Matrix3& axes, float x, float y, float z);

		/** �Ի�����Z��ת
		@param angle Ҫ��ת�Ļ���
		@see TransformSpace
		*/
		virtual void roll(const Radian& angle);

		/** �ԽǶ���Z��ת
		@param degrees Ҫ��ת�ĽǶ�
		@see TransformSpace
		*/
		virtual void roll(float degrees);

		/** �Ի�����X��ת
		@param angle Ҫ��ת�Ļ���
		@see TransformSpace
		*/
		virtual void pitch(const Radian& angle);

		/** �ԽǶ���X��ת
		@param degrees Ҫ��ת�ĽǶ�
		@see TransformSpace
		*/
		virtual void pitch(float angle);

		/** �Ի�����Y��ת
		@param angle Ҫ��ת�Ļ���
		@see TransformSpace
		*/
		virtual void yaw(const Radian& angle);

		/** �ԽǶ���Y��ת
		@param degrees Ҫ��ת�ĽǶ�
		@see TransformSpace
		*/
		virtual void yaw(float angle);	

		/** �Ի�����ĳ���Զ��������ת
		@param axis ��
		@param angle Ҫ��ת�Ļ���
		@see TransformSpace
		*/
		virtual void rotate(const Vector3& axis, const Radian& angle);

		/** �ԽǶ���ĳ���Զ��������ת
		@param axis ��
		@param angle Ҫ��ת�ĽǶ�
		@see TransformSpace
		*/
		virtual void rotate(const Vector3& axis, float angle);

		/** �ø�������Ԫ����ת
		@param q ��Ԫ��
		@see TransformSpace
		*/
		virtual void rotate(const Quaternion& q);	

		/** ��ñ�������ϵ
		@return ��������ϵ�ľ���
		*/
		virtual Matrix3 getLocalAxes(void) const;

		/** �����ӽڵ�
		@param translate �ӽڵ��ƫ����
		@param rotate �ӽڵ�ķ�λ
		@return �ӽڵ�ָ��
		*/
		virtual ModelNode* createChild(const char* boneName,const char* modelName,const Vector3& translate = Vector3::ZERO,const Quaternion& rotate = Quaternion::IDENTITY );

		/** ��һ���ڵ���Ϊ�ӽڵ�ҽ�
		@param child δ�����ӽڵ�
		*/
		virtual bool addChild(ModelNode* child,const char* boneName);	

		/** ����ӽڵ������
		@return �ӽڵ������
		*/
		virtual ushort numChildren(void) const;	

		/** ��õ�index���ӽڵ�
		@param index �ӽڵ���±�
		@return �ӽڵ��ָ��
		*/
		virtual ModelNode* getChild(ushort index) const;	

		/** ɾ��һ���ӽڵ�
		@param child �ӽڵ��ָ��
		@return ���ӽڵ��ָ��
		*/
		virtual ModelNode* removeChild(ModelNode* child);

		virtual ModelNode* getFirstChildNodeByBone(const char* boneName);
		virtual ModelNode* getNextChildNodeByBone();

		/** �ݻ�һ���ӽڵ�
		*/
		virtual void destroyChild(ModelNode* child);

		/** �ݻ������ӽڵ�
		*/
		virtual void destroyAllChildren(void);

		/** ��ôӸ��ڵ�̳еı任��������һ���Ӹ��ڵ㴫�ݵ����ڵ�ı任����
		@return �任����
		*/
		virtual const Matrix4& getFullTransform(void);

		Bone*	getBoneAttachedTo();

		/** ���´˽ڵ�
		@param tick ʱ���
		@param tickDelta ʱ���Delta
		@param pRenderSystem ��Ⱦϵͳ
		*/
		virtual void update(float tick,float tickDelta,IRenderSystem* pRenderSystem,const ColorValue& diffuse = ColorValue::White);

		/** ���´˽ڵ��ɫ������
		@param pRenderSystem ��Ⱦϵͳ
		@remarks ��ʱ�������Ҫ�ı�ģ�͵���ɫ
		*/
		virtual void updateColor(IRenderSystem* pRenderSystem,const ColorValue& diffuse = ColorValue::White);

		virtual void render(IRenderSystem* pRenderSystem,bool useMtl);

		//add by yhc
		//for Ӱ����Ⱦ
		virtual void renderByTime(IRenderSystem* pRenderSystem,bool useMtl,float tickCurrent);

		/** ���ýڵ��Ƿ�ɼ�
		*/
		void setVisible(bool bVisible);
	

		/** ֪ͨ�˽ڵ���ҪUpdate,��������绷���Ѿ������˱仯
		*/
		virtual void needUpdate();

		/**���¾���
		*/
		void updateTransform();

		ModelInstance*	getModelInstance();

		//ģ�����

		void setGlobalDiffuse(const ColorValue& color);

		const ColorValue& getSurfaceDiffuse();

		size_t getMemorySize();

		const std::string& getName() const;

		void setName(const std::string& name);

		void setStepLength(int length);

		int getStepLength();

		void setOnlyInheritTranslation(bool bInherit){m_bOnlyInheritTranslation = bInherit;}

		void setBoundingBox(const Rect& rect);
		const Rect& getBoundingBox();
		
		void SetGenerateParticle(bool bGenerate);
		int  GetParticleNum();
	public:
		typedef std::vector<ModelNode*> ChildNodeList;

	protected:
		/// Pointer to parent node
		ModelNode* m_pParent;
		/// Collection of pointers to direct children; hashmap for efficiency
		ChildNodeList m_vChildren;

		/// Stores the orientation of the node relative to it's parent.
		Quaternion m_quatOrientation;

		/// Stores the position/translation of the node relative to its parent.
		Vector3 m_vPosition;

		/// Stores the scaling factor applied to this node
		Vector3 m_vScale;

		/** Internal method for building a Matrix4 from orientation / scale / position. 
		@remarks
		Transform is performed in the order rotate, scale, translation, i.e. translation is independent
		of orientation axes, scale does not affect size of translation, rotation and scaling are always
		centered on the origin.
		*/
		void  makeTransform(
			const Vector3& position, 
			const Vector3& scale, 
			const Quaternion& orientation, 
			Matrix4& destMatrix ) const;

		/** ������Ⱦ���У�ʵ����Ҫ��������Ƿ���Լ��ӵ���Ⱦ������ȥ
		*/
		virtual void		updateRenderQueue(RenderQueue *pQueue);

		/// Cached derived transform as a 4x4 matrix
		mutable Matrix4 mTransform;
		mutable Matrix4 mDerivedTransform;

		ChildNodeList::iterator	m_itBone;
		std::string m_boneNameIt;

		std::string m_strName;
		int m_stepLength;

		RenderQueue		m_renderQueue;

		bool m_bOnlyInheritTranslation;

		Rect			m_boundingBox;

		bool m_bVisible;//�ڵ��Ƿ�ɼ���������ɼ�������ʾ��

		enum ModelType
		{
			MT_MM,
			MT_MDX,
			MT_MZ,
			MT_TX,
			MT_MX
		};
		ModelType		m_mt;

	public:
		ModelNode();
		ModelNode::~ModelNode();
	public:
		virtual bool		setModel(const char* modelName);
	private:
		AABB	m_AABB;

		Sphere	m_sphere;
		/** Tells the ModelNode to update the world bound info it stores.
		*/
		virtual void  _updateAABB(void );

		ModelInstance*		m_pModelInstance;
		Bone*				m_pBone;

		bool				m_bNeedUpdate;
	private:
		ColorValue			m_surfaceDiffuse;
	};

}

#endif