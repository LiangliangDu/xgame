#ifndef __RenderTargetD3D9Texture_H__
#define __RenderTargetD3D9Texture_H__
#include "RenderTargetD3D9.h"

namespace xs
{

	class RenderTargetManagerD3D9;
	class RenderSystemD3D9;
	class TextureD3D9;
	class RenderTargetD3D9Texture: public RenderTargetD3D9
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
		virtual void onDeviceLost();
		virtual void onDeviceReset();
		virtual RECT getFrameBufferRect();
		virtual bool switchDisplayMode(RenderEngineCreationParameters* param);
		virtual bool getDisplayMode(RenderEngineCreationParameters & createParam);

		//�������������
	private:
		friend class RenderTargetManagerD3D9;
		RenderTargetD3D9Texture(RenderSystemD3D9 * pRenderSystem, bool b2d,RenderTargetManagerD3D9 * pRenderTargetMgr);
		~RenderTargetD3D9Texture();
		bool create(int width, int height,bool alpha,
			FilterOptions min , 
			FilterOptions mag, 
			FilterOptions mip,
			TextureAddressingMode s,											
			TextureAddressingMode t);
	public:
		TextureD3D9				* m_pTexture; //����
		IDirect3DSurface9	*	m_pDepthStencilBuffer;//���������ģ�滺��
	};

}

#endif