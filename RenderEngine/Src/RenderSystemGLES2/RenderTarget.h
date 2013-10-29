#ifndef __RenderTarget_H__
#define __RenderTarget_H__

namespace xs
{
	class RenderSystem;
}

class RenderTargetDesc
{
public:
	unsigned int width;
	unsigned int height;
	unsigned int colorBits;
	unsigned int depthBits;
	unsigned int stencilBits;
	FilterOptions min;
	FilterOptions mag;
	FilterOptions mip;
	TextureAddressingMode s;
	TextureAddressingMode t;

	RenderTargetDesc()
		:width(0),height(0)
		,colorBits(32)
		,depthBits(16)
		,stencilBits(8)
		,min(FO_LINEAR)
		,mag(FO_LINEAR)
		,mip(FO_LINEAR)
		,s(TAM_CLAMP_TO_EDGE)
		,t(TAM_CLAMP_TO_EDGE)
	{}
};

class RenderTarget
{
public:
	virtual void 		release();
	virtual const ITexture*	getTexture();
	virtual void 		onAttach();
	virtual void 		onDetach();
	virtual void 		onEndFrame(int layer);
	virtual bool		getTextureData(void  *pData);
	virtual void		getRect(RECT *rc);
public:
	struct RenderState
	{
		Matrix4	m_mtxView,m_mtxWorld,m_mtxProjection,m_mtxModelView;
		bool	m_bDepthWriteEnabled;
		bool	m_bLightingEnabled;
		SceneBlendFactor	m_BlendFactorSource,m_BlendFactorDest;
		bool	m_bDepthCheckEnabled;
		CullingMode	m_cullingMode;
		ColorValue	m_color;
		bool	m_bAlphaCheckEnabled;
		CompareFunction	m_AlphaCompareFunction;
		float	m_AlphaCompareValue;
		FillMode	m_fillMode;
		ColorValue	m_ambientColor;
		ColorValue		m_clearColor;
		CompareFunction	m_DepthBufferFunction;

		RenderState()
		{
			m_bDepthWriteEnabled = true;
			m_bLightingEnabled = false;
			m_bDepthCheckEnabled = false;
			m_cullingMode = CULL_NONE;
			m_color = ColorValue::White;
			m_BlendFactorSource = SBF_ONE;
			m_BlendFactorDest = SBF_ZERO;
			m_mtxView = Matrix4::IDENTITY;
			m_mtxWorld = Matrix4::IDENTITY;
			m_mtxProjection = Matrix4::IDENTITY;
			m_mtxModelView = Matrix4::IDENTITY;
			m_ambientColor = ColorValue(0.2, 0.2, 0.2, 0.1);
			m_bAlphaCheckEnabled = false;
			m_AlphaCompareFunction = CMPF_ALWAYS_PASS;
			m_AlphaCompareValue = 0;
			m_fillMode = FM_SOLID;
			m_clearColor = ColorValue::Black;
			m_DepthBufferFunction = CMPF_LESS;
		}
	};

	
public:
	EGLContext			rc;		//render context
	HDC				dc;	
	bool			m_b2D;
	HWND			m_hWnd;
		
	EGLSurface		m_eglSurface;
	RenderSystem*	m_pRenderSystem;
	EGLDisplay		m_eglDisplay;

	RenderState		m_RenderState2D,m_RenderState3D;
	RenderState		m_RenderState;
	

	RenderTarget(RenderSystem* pRenderSystem);
	RenderTarget(HDC dc,HWND hWnd,RenderSystem* pRenderSystem,EGLContext shareContext = NULL);

	//�ӿڲ����������л�2D / 3Dʱ�����ã����������Ƿ���ʹ��
	int m_vpLeft,m_vpTop,m_vpWidth,m_vpHeight;

	GLuint  m_FrameBufferObj;
	GLuint  GetFrameBufferObj(){return m_FrameBufferObj;}
};

#endif