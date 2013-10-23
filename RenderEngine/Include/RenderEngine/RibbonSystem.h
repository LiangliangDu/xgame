#ifndef __RibbonSystem_H__
#define __RibbonSystem_H__


namespace xs
{
	class Bone;
	class ModelNode;

	class RibbonSystem : public IRenderable
	{
	public:
		/** ��Ⱦ
		@param pRenderSystem ��Ⱦϵͳ�ӿ�ָ��
		*/
		virtual void  render(IRenderSystem* pRenderSystem,bool useMtl);

	public:
		RibbonSystem();
		~RibbonSystem();

		void update(const AnimationTime *pTime,float tickDelta,IRenderSystem* pRenderSystem);
		int getRenderOrder();

		void reset();
		void setColor(const ColorValue& color);

		void Clear();//��ղ���

		int __getRibbonSegNum();

		void show( bool bShow);//��ʾƮ��ϵͳ��Ĭ����ʾ

	public:
		RibbonEmitterData*	m_pData;
		Bone*				m_pBone;
		ModelNode*			m_pNode;
		ITexture*			m_pTexture;

		float	m_currentEmission;
		uint	m_originTime;
		Color4	m_diffuse;

	private:
		struct Segment
		{
			Vector3 v1,v2;
			Vector2 t1,t2;
			Color4 c;
			Color4 fullColor;
			float lifeSpan;
			Vector3 v;//�ٶȱ仯
			Segment()
			{
				
			}
		};

		typedef std::list<Segment> SegmentList;
		SegmentList m_vSegments;


	private:
		void saveContext(IRenderSystem *pRenderSystem);
		void loadContext(IRenderSystem *pRenderSystem);
		//��Ⱦ״̬����/�ָ���Ϣ
		SceneBlendFactor	m_sbfSrc,m_sbfDst;
		bool m_alphaCheck;
		float m_alphaCheckRef;
		CullingMode	m_cullingMode;
		CompareFunction	m_alphaFunc;
		bool		m_bDepthCheck;
		bool		m_bDepthWrite;
		bool		m_lightingEnabled;
		Color4		m_color;
		bool		m_bShowFlag;//Ʈ��ϵͳ��ʾ��־
	private:
		/*
		����������ٶȲ����ȣ���ʹ��Ʈ����ƽ�������в��ֱ���ѹ�ĸо������ԣ��ڲ�����ʱ�򣬰��Ƕȣ������Ȳ�ֵ
		*/
		Vector3 m_v3PrePrePviot;//ǰ����ǰ��
		Vector3 m_v3PreviousPivot;//ǰ��
		Vector3 m_vPreviousUp;
		float m_fPreviousHeightAbove;
		float m_fPreviousHeighBelow;
	};
}

#endif