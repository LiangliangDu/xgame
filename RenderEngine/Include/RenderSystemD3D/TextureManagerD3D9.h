#ifndef __TextureManagerD3D9_H__
#define __TextureManagerD3D9_H__

#include "RenderEngine/Manager.h"

namespace xs
{
	class TextureManagerD3D9;
	class RenderSystemD3D9;
	class TextureD3D9;

	class TextureManagerD3D9Creater
	{
	public: 
		static TextureManagerD3D9 * create( RenderSystemD3D9 * pRenderSystem);
	};

	class TextureManagerD3D9 : public Manager<ITexture*> , public ITextureManager
	{
		//ITextureManager �ӿ�
	public:
		/** ��ͼ�����ݴ�����ͼ,��ͼ��width*height�ĳߴ�,����image��pRect����blt����ͼ��
		@param image ͼ������
		@param pRect ͼ���������
		@param width ���
		@param height �߶�
		@param minFO Min Filter
		@param magFO Max Filter
		@param mipFO Mip Filter
		@param s ��ͼSѰַ��ʽ
		@param t ��ͼTѰַ��ʽ
		@return ��ͼָ��
		*/
		virtual ITexture*	createTextureFromImage(																
			const Image& image,																
			const Rect* pRect,																
			uint width,uint height,														
			FilterOptions minFO = FO_LINEAR,												
			FilterOptions magFO = FO_LINEAR,												
			FilterOptions mipFO = FO_NONE,													
			TextureAddressingMode s = TAM_CLAMP_TO_EDGE,											
			TextureAddressingMode t = TAM_CLAMP_TO_EDGE);										

		/** ��ͼ�����ݴ�����ͼ,��ͼ�Ĵ�С��pRect�Ŀ��,���pRect��Ϊ����ͼƬ�ĳߴ�
		@param image ͼ������
		@param pRect ͼ���������
		@param minFO Min Filter
		@param magFO Max Filter
		@param mipFO Mip Filter
		@param s ��ͼSѰַ��ʽ
		@param t ��ͼTѰַ��ʽ
		@return ��ͼָ��
		*/
		virtual ITexture*	createTextureFromImage(																
			const Image& image,																
			const Rect* pRect = 0,																
			FilterOptions minFO = FO_LINEAR,												
			FilterOptions magFO = FO_LINEAR,												
			FilterOptions mipFO = FO_NONE,													
			TextureAddressingMode s = TAM_CLAMP_TO_EDGE,											
			TextureAddressingMode t = TAM_CLAMP_TO_EDGE);										

		/** ��ͼ���ļ�������ͼ,����Щ�Կ���֧�ַ�2^n��ͼ,�������ʱ���û���Ҫʹ��2^N��ͼ
		@param name �ļ���
		@param minFO Min Filter
		@param magFO Max Filter
		@param mipFO Mip Filter
		@param s ��ͼSѰַ��ʽ
		@param t ��ͼTѰַ��ʽ
		@return ��ͼָ��
		*/
		virtual ITexture*	createTextureFromFile(																
			const std::string& name,																
			FilterOptions minFO = FO_LINEAR,												
			FilterOptions magFO = FO_LINEAR,												
			FilterOptions mipFO = FO_NONE,													
			TextureAddressingMode s = TAM_CLAMP_TO_EDGE,											
			TextureAddressingMode t = TAM_CLAMP_TO_EDGE);										

		/** ��Raw���ݴ�����ͼ
		@param pBuffer ����ָ��
		@param width pBufferͼ�����ݵĿ��
		@param height pBufferͼ�����ݵĸ߶�
		@param minFO Min Filter
		@param magFO Max Filter
		@param mipFO Mip Filter
		@param s ��ͼSѰַ��ʽ
		@param t ��ͼTѰַ��ʽ
		@return ��ͼָ��
		*/
		virtual ITexture*	createTextureFromRawData(															
			uchar* pBuffer,																	
			uint width,uint height,PixelFormat pf,										
			FilterOptions minFO = FO_LINEAR,												
			FilterOptions magFO = FO_LINEAR,												
			FilterOptions mipFO = FO_NONE,													
			TextureAddressingMode s = TAM_CLAMP_TO_EDGE,											
			TextureAddressingMode t = TAM_CLAMP_TO_EDGE);										

		/** �����յ���ͼ,δָ����ȡ��߶Ⱥ����ظ�ʽ
		@param minFO Min Filter
		@param magFO Max Filter
		@param mipFO Mip Filter
		@param s ��ͼSѰַ��ʽ
		@param t ��ͼTѰַ��ʽ
		@return ��ͼָ��
		*/
		virtual ITexture*	createEmptyTexture(																	
			FilterOptions minFO = FO_LINEAR,												
			FilterOptions magFO = FO_LINEAR,												
			FilterOptions mipFO = FO_NONE,													
			TextureAddressingMode s = TAM_CLAMP_TO_EDGE,											
			TextureAddressingMode t = TAM_CLAMP_TO_EDGE,const std::string& name= "");			

		/** �����յ���ͼ,��ָ����ȡ��߶Ⱥ����ظ�ʽ
		@param width ���
		@param height �߶�
		@param pf ���ظ�ʽ
		@param minFO Min Filter
		@param magFO Max Filter
		@param mipFO Mip Filter
		@param s ��ͼSѰַ��ʽ
		@param t ��ͼTѰַ��ʽ
		@return ��ͼָ��
		*/
		virtual ITexture*	createEmptyTexture(																	
			uint width,uint height,PixelFormat pf,										
			FilterOptions minFO = FO_LINEAR,												
			FilterOptions magFO = FO_LINEAR,												
			FilterOptions mipFO = FO_NONE,													
			TextureAddressingMode s = TAM_CLAMP_TO_EDGE,											
			TextureAddressingMode t = TAM_CLAMP_TO_EDGE);	

		/** �����յ���ͼ,��ָ����ȡ��߶Ⱥ����ظ�ʽ������Ҫ�ȴ���Ⱦ���������������Ӱ��֡�ʣ�����
		����Ⱦ�е��ò���������
		@param width ���
		@param height �߶�
		@param pf ���ظ�ʽ
		@param minFO Min Filter
		@param magFO Max Filter
		@param mipFO Mip Filter
		@param s ��ͼSѰַ��ʽ
		@param t ��ͼTѰַ��ʽ
		@return ��ͼָ��
		*/
		virtual ITexture*	createEmptyTextureNoWait(																	
			uint width,uint height,PixelFormat pf,										
			FilterOptions minFO = FO_LINEAR,												
			FilterOptions magFO = FO_LINEAR,												
			FilterOptions mipFO = FO_NONE,													
			TextureAddressingMode s = TAM_CLAMP_TO_EDGE,											
			TextureAddressingMode t = TAM_CLAMP_TO_EDGE);

		/** �����ļ���ȡ����ͼָ�룬Ҳ�������Զ������ͼ����
		@param name �ļ��������Զ������ͼ����
		@return ��ͼָ��
		*/
		virtual ITexture*	getTexture(const std::string& name);											

		/** �ͷ���ͼ
		@param pTexture ��ͼ��ָ��
		*/
		virtual void 	releaseTexture(ITexture* pTexture);															

		/** ���������ͷ���ͼ
		@param name ��ͼ������
		*/
		virtual void 	releaseTextureByName(const std::string& name);										

		/** �ͷ�������ͼ
		*/
		virtual void 	releaseAll();

	public:

		//�Զ��������������
		/** ������ȾĿ������,��ָ����ȡ��߶Ⱥ����ظ�ʽ
		@param	D3DPOOL ���������
		@param	usage	ʹ�÷�ʽ
		@param width ���
		@param height �߶�
		@param pf ���ظ�ʽ
		@param minFO Min Filter
		@param magFO Max Filter
		@param mipFO Mip Filter
		@param s ��ͼSѰַ��ʽ
		@param t ��ͼTѰַ��ʽ
		@return ��ͼָ��
		*/
		TextureD3D9* createEmptyeTexture(
			D3DPOOL	pooltype,
			DWORD usage,
			uint width,uint height,PixelFormat pf,										
			FilterOptions minFO = FO_LINEAR,												
			FilterOptions magFO = FO_LINEAR,												
			FilterOptions mipFO = FO_NONE,													
			TextureAddressingMode s = TAM_CLAMP_TO_EDGE,											
			TextureAddressingMode t = TAM_CLAMP_TO_EDGE);

		//Manager�ӿ�
	private:
		void doDelete(ITexture* pTexture);

	private:
		const char* getUniqueString();

	public:
		//�ͷ��Լ�
		void release();

		//��ȡ��Ⱦϵͳָ��
		inline RenderSystemD3D9 * getRenderSystem() { return m_pRenderSystem; }

	private:
		friend class TextureManagerD3D9Creater;
		bool create(RenderSystemD3D9 * pRenderSystem);
		TextureManagerD3D9():m_pRenderSystem(0),m_ui32Index(0){};
		~TextureManagerD3D9(){};
	private:
		RenderSystemD3D9 * m_pRenderSystem; //��Ⱦϵͳָ��
		uint				m_ui32Index;//���ڲ�������Ψһ������
	};
}
#endif