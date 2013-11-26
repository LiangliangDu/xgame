#ifndef __RenderTargetD3D9Window_H__
#define __RenderTargetD3D9Window_H__
#include "RenderTargetD3D9.h"

namespace xs
{

	class RenderTargetManagerD3D9;
	class RenderSystemD3D9;
	class RenderTargetD3D9Window: public RenderTargetD3D9
	{
		//�ӿ�
	public:
		virtual void 		release();
		virtual const ITexture*	getTexture();
		virtual bool		getTextureData(void * pData);
		virtual void 		onAttach(RenderTargetD3D9 * pPrevious);
		virtual void 		onDetach();
		virtual void		onBeginFrame(bool clearColorBuffer,bool clearDepthBuffer,bool clearStencilBuffer);
		virtual void 		onEndFrame(int layer);
		virtual	void		clearFrameBuffer(bool clearColorBuffer,bool clearDepthBuffer ,bool clearStencilBuffer);
		virtual IDirect3DSurface9 * getDepthStencilBuffer();
		virtual bool		isDefaultRenderTarget();
		virtual void onDeviceLost();
		virtual void onDeviceReset();
		virtual RECT getFrameBufferRect();
		virtual bool switchDisplayMode(RenderEngineCreationParameters* param);
		virtual bool getDisplayMode(RenderEngineCreationParameters & createParam);


		//�������������
	private:
		friend class RenderTargetManagerD3D9;
		bool createAsDefaultRenderTarget();
		bool create(HWND hwnd);//���ݴ��ڴ�����ȾĿ��,���ڴ���ģʽ
		RenderTargetD3D9Window(RenderSystemD3D9 * pRenderSystem, bool b2d, RenderTargetManagerD3D9 * pRenderTargetMgr);
		~RenderTargetD3D9Window();	
	public:
		bool					m_bIsDefault;//�Ƿ��������ȾĿ�����豸������
		IDirect3DSwapChain9		* m_pSwapChain;//������
		D3DPRESENT_PARAMETERS	m_PresentParam;//����������
		IDirect3DSurface9	*	m_pDepthStencilBuffer;//���������ģ�滺��
		HWND					m_hWnd;//����Ĵ��ھ��	
	};

}
#endif