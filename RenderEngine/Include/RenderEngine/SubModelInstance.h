#ifndef __SubModelInstance_H__
#define __SubModelInstance_H__

#include "IRenderable.h"
#include "Material.h"

namespace xs
{
	class ModelInstance;
	class ModelNode;


	class _RenderEngineExport SubModelInstance : public IRenderable
	{
	public:
		//IRenderable
		virtual void  render(IRenderSystem* pRenderSystem,bool useMtl);

	public:
		virtual const Matrix4& getWorldTransform() const;

		void setEyeAt(const Vector3& v);

		float getDistance();

		Material* getMaterial();

		Material* getOriginalMaterial();

		void setTexture(int layer,const char* szName);

		ITexture* getTexture(int layer);

		int getRenderOrder();

		void update(const AnimationTime *pAnimationTime,const ColorValue& diffuse);

		void updateColor(const ColorValue& diffuse);

		ushort numIndices();

		//������Mesh�󶨵Ĺ�����ǰ�ľ���
		void updateBonesMatrix(xs::Skeleton * pSkeleton);

	public:
		SubModelInstance(ModelInstance *pMI,ISubModel *pSubModel, uint subModelIndex);
		~SubModelInstance();

	public:
		const char* getName();

		/** ��ģ���Ƿ�ɼ�
		@return �Ƿ�ɼ�
		*/
		virtual bool isVisible();

		/** ������ģ�͵Ŀɼ���
		*/
		virtual void  setVisible(bool bVisible);

	private:
		void  renderCPUVertexBlend(IRenderSystem* pRenderSystem,bool useMtl);
		void  renderGPUVertexBlend(IRenderSystem* pRenderSystem,bool useMtl);	

	private:
		bool m_bVisible;
		Material	m_mtl,m_mtlOrigin;
		std::string m_name;
		ModelInstance*	m_pMI;
		ISubModel*		m_pSubModel;
		ushort indexStart,indexCount,vertexStart,vertexEnd;
		GeosetAnimation* m_pGeosetAnimation;
		float		m_GeosetAlpha;
		//����֧�ֹ�����Ӳ�����
		//xs::Matrix4 m_BindedBonesMatrices[VERTEX_BLEND_MATRICES_NUM];//HighLevel shaderʹ�õĹ�������
		uint		m_uiSubModelIndex;
		float		 m_BindedBonesMatricesF[VERTEX_BLEND_MATRICES_NUM][3][4];//LowLevel shader ʹ�õĹ�������
	};
}

#endif