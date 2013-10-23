#ifndef __MmParticleSystem_H__
#define __MmParticleSystem_H__

#include "_Particle.h"
//лѧ���޸ģ��ļ�����������string
#include <string>
using namespace std;

namespace xs
{
	class ParticleSystemEmitter;
	class Bone;
	class ModelNode;

	/** ����ϵͳ��
	*/
	class _RenderEngineExport MmParticleSystem : public IRenderable
	{
	public:
		MmParticleSystem();
		~MmParticleSystem();

	public:
		Bone*			m_pBone;
		MmParticleSystemData *m_pData;
		ModelNode*			m_pNode;

	public:
		void update(IRenderSystem * pRenderSystem, AnimationTime *pTime,float tickDelta,int rangeIndex);
		virtual void  render(IRenderSystem* pRenderSystem,bool useMtl);

	public:
		int getRenderOrder();
		void setColor(const ColorValue& color);
		void reset();
		static void set25d(bool b25d);
		static void setPause(bool bPause);
		void Clear();//лѧ���޸ģ��ص�����ϵͳ��ʼ״̬,����
		int __getCurParticleNum();
		void SetGenerateParticle(bool bGenerate);
	private:
		ParticleSystemEmitter*	m_pEmitter;
		typedef std::list<MmParticle> MmParticleList;
		typedef MmParticleList::iterator MmParticleListIterator;
		MmParticleList	m_particleList;
		ITexture*		m_pTexture;
		float			m_rem;
		float			m_random;
		static			bool m_b25d;
		static          bool s_bPause;

	public:
		Color4			m_color;

	private:
		bool initializeResource(IRenderSystem * pRenderSystem);
		void finalizeResource();
		void setContext(IRenderSystem * pRenderSystem);
		void saveContext(IRenderSystem *pRenderSystem);
		void loadContext(IRenderSystem *pRenderSystem);
		void renderVBO(IRenderSystem * pRenderSystem);
		void renderManual(IRenderSystem * pRenderSystem);
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
		Color4		m_saveColor;
		bool		m_bInitializeTexture;//�����Ƿ��Ѿ���ʼ����
		bool        m_bGenerate;

	private://��vbo����
		const static uint s_MaxVertices;//��󶥵���
		const static bool s_UseVBO ;//�Ƿ�ʹ��vbo����
		xs::IVertexBuffer * m_pVB;//positon vertx buffer
		xs::IVertexBuffer * m_pTexVB; //texcoord vertex buffer
		xs::IVertexBuffer * m_pDiffuseVB;//diffuse color vertex buffer
		xs::IIndexBuffer * m_pIB;//index buffer;
		uint m_uiPreviousQuads;
	};
}

#endif