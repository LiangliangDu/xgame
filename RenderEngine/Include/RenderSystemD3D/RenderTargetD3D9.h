#ifndef __RenderTargetD3D9_H__
#define __RenderTargetD3D9_H__
namespace xs
{
	class RenderSystemD3D9;
	class RenderTargetManagerD3D9;

	class RenderTargetD3D9
	{
		//�ӿ�
	public:
		virtual void 		release()=0;
		virtual const ITexture*	getTexture()=0;
		virtual bool		getTextureData(void * pData)=0;
		virtual void 		onAttach(RenderTargetD3D9 * pPrevious);
		virtual void 		onDetach();

		virtual void		onBeginFrame(bool clearColorBuffer,bool clearDepthBuffer,bool clearStencilBuffer)=0;
		virtual void 		onEndFrame(int layer)=0;

		virtual void		clearFrameBuffer(bool clearColorBuffer,bool clearDepthBuffer ,bool clearStencilBuffer) =0;

		virtual bool		isDefaultRenderTarget() {return false; };//�ж���ȾĿ���ǲ����豸��һ������
		
		virtual IDirect3DSurface9 * getDepthStencilBuffer()=0;

		virtual void onDeviceLost() = 0;
		virtual void onDeviceReset() = 0;
		virtual RECT getFrameBufferRect() = 0;

		virtual bool switchDisplayMode(RenderEngineCreationParameters* param)=0;//�ı���ʾģʽ

		virtual bool getDisplayMode(RenderEngineCreationParameters & createParam)=0;//��ȡ��ǰ����ʾģʽ

	public:	
		//���֡���溯��
		void				setClearColor(const ColorValue& color);
		const ColorValue&	getClearColor();
		void				setClearDepth(float depth);
		float				getClearDepth();
		void				setClearStencil(int stencil);
		int					getClearStencil();

		//2d 3d�л�
		void				switchTo2D();
		void 				switchTo2D(int left,int top,int width,int height);
		void				switchTo3D();
		bool				is2dMode();

		//�����ѡ
		void				setCullingMode(const CullingMode& cm);
		const CullingMode&	getCullingMode();

		//���ղ���
		void				setLightingEnabled(bool enabled);
		bool				isLightingEnabled();

		//����任
		void				setWorldMatrix(const Matrix4 & mtx);
		const Matrix4&		getWorldMatrix();
		const Matrix4&		getModelViewMatrix();
		void				setViewMatrix(const Matrix4& mtx);
		const Matrix4&		getViewMatrix();
		void				setProjectionMatrix(const Matrix4& mtx);
		const Matrix4&		getProjectionMatrix();

		void				getWorldMatrix(D3DXMATRIX & mtx);
		void				getViewMatrix(D3DXMATRIX & mtx);
		void				getProjectionMatrix(D3DXMATRIX & mtx);

		//��ȼ��
		bool					isDepthBufferCheckEnabled();
		void					setDepthBufferCheckEnabled(bool enabled);
		void					setDepthBufferFunction(const CompareFunction& cf);
		void					setDepthBufferWriteEnabled(bool enabled);
		bool					isDepthBufferWriteEnabled();
		const CompareFunction&	getDepthBufferFunction();

		//��ɫ����mask
		void					setColorBufferWriteEnabled(bool red, bool green, bool blue, bool alpha);

		//�ӿ�
		void					setViewport(int left,int top,int width,int height);
		void					getViewport(int &left,int &top,int &width,int &height);

		//ͶӰ����ͶӰ
		Vector3					unproject( const Vector3 & v);
		Vector3					project(const Vector3 & v);

	public:
		struct RenderState
		{
			//����ȾĿ���������2D��3Dģʽ��ص�״̬

			//����״̬
			Matrix4	m_mtxView;
			Matrix4 m_mtxWorld;
			Matrix4 m_mtxModelView;
			Matrix4	m_mtxProjection;
			//�����ѡ
			CullingMode	m_cullingMode;
			//���ղ���
			bool	m_bLightingEnabled;
			//��ȼ��
			bool	m_bDepthWriteEnabled;
			bool	m_bDepthCheckEnabled;
			CompareFunction	m_DepthBufferFunction;

		public:
			RenderState();//���캯��
		};

	private:
		void setRenderState( const RenderState & rs);

	public:
		void resetRenderState();//������Ⱦ״̬

	protected:
		inline DWORD		F2DW(float f) { return *((DWORD*)&f);}
		void				convertProjectionMatrix(const Matrix4& matrix,
							Matrix4& dest, bool forGpuProgram);
		
	protected:
		//�������������
		RenderTargetD3D9(RenderSystemD3D9 * pRenderSystem, bool b2d, RenderTargetManagerD3D9 * pRenderTargetMgr);
		virtual ~RenderTargetD3D9();	
	public:
		//��2D��3Dģʽ��ص���Ⱦ״̬
		RenderState		m_RenderState2D,m_RenderState3D;
		RenderState		m_RenderState;
		bool			m_b2D;

		//����ȾĿ����ص�״̬��������2D��3Dģʽ�޹ص�״̬
	public:
		//֡�������״̬
		ColorValue	m_clearColor;
		float	m_clearDepth;
		int	m_clearStencil;

		//�ӿڲ���
		D3DVIEWPORT9 m_viewport;

		//��ɫ����Mask
		bool m_redChannel;
		bool m_greenChannel;
		bool m_blueChannel;
		bool m_alphaChannel;

	public:
		RenderSystemD3D9 * m_pRenderSystem;//��Ⱦϵͳ
		RenderTargetManagerD3D9 * m_pRenderTargetMgr;//��ȾĿ�������
	};
}
#endif