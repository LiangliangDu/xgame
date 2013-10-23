#ifndef __ParticleSystem_H__
#define __ParticleSystem_H__

#include "Particle.h"
#include <string>
using namespace std;

namespace xs
{
	class Bone;
	class ModelNode;

	class _RenderEngineExport ParticleSystem : public IRenderable
	{
	public:
		/** ��Ⱦ
		@param pRenderSystem ��Ⱦϵͳ�ӿ�ָ��
		*/
		virtual void  render(IRenderSystem* pRenderSystem,bool useMtl);

	public:
		ParticleSystem();
		~ParticleSystem();

		void update(const AnimationTime *pTime,float tickDelta,IRenderSystem* pRenderSystem);
		int getRenderOrder();
		static void set25dMode(bool b25d);
		static void setPause(bool bPause);
		void reset();
		void setColor(const ColorValue& color);
		int __getCurParticleNum();
		void SetGenerateParticle(bool bGenerate);

	public:
		ParticleEmitter2Data*	m_pData;
		Bone*					m_pBone;
		typedef std::list<Particle> ParticleContainer;
		typedef ParticleContainer::iterator ParticleContainerIterator;
		ParticleContainer	m_vParticles;
		ITexture*			m_pTexture;
		float	m_currentEmission;
		ModelNode*			m_pNode;
		static bool	m_b25d;
		static bool	s_bPause;
		ColorValue			m_color;
		void Clear();//�������ϵͳ������
	private:
		bool initializeResource(IRenderSystem * pRenderSystem);//��ʼ������ϵͳ��Դ
		void finalizeResource();//�ͷ�����ϵͳ��Դ
		void renderVBO(IRenderSystem * pRenderSystem);//ʹ��vbo��Ⱦ
		void renderManual(IRenderSystem * pRenderSystem);//ʹ���ֹ���Ⱦ
		void saveContext(IRenderSystem *pRenderSystem);//������Ⱦ״̬
		void loadContext(IRenderSystem *pRenderSystem);//������Ⱦ״̬
		void setContext(IRenderSystem * pRenderSystem);//������Ⱦ״̬

	private:
		//��Ⱦ״̬����/�ָ���Ϣ
		SceneBlendFactor	m_sbfSrc,m_sbfDst;
		bool m_alphaCheck;
		float m_alphaCheckRef;
		CullingMode	m_cullingMode;
		CompareFunction	m_alphaFunc;
		bool		m_bDepthCheck;
		bool		m_bDepthWrite;
		bool		m_lightingEnabled;
		bool		m_bFogEnabled;

	private://��vbo����
		const static uint s_MaxVertices;//������������
		const static bool s_UseVBO;//�Ƿ�ʹ��vbo����
		xs::IVertexBuffer * m_pVB;//position vertx buffer
		xs::IVertexBuffer * m_pTexVB;//texcoord vertex buffer
		xs::IVertexBuffer * m_pDiffuseVB;//diffuse vertex buffer
		xs::IIndexBuffer * m_pIB;//index buffer
		uint m_uiPreviousQuads;

	private:
		bool		m_bInitializeTexture;//�Ƿ��Ѿ���ʦ��������
		bool        m_bGenerate;
	private: //�Ѳ������ӵĺ�����������
		void generateParticleByTime(const AnimationTime * pTime,float tickDelta,IRenderSystem* pRenderSystem);
		void generateParticleBySpace(const AnimationTime * pTime, float tickDelta,IRenderSystem* pRenderSystem);
	};
}

#endif