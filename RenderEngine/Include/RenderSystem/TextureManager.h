#ifndef __TextureManager_H__
#define __TextureManager_H__

#include "Singleton.h"
#include "RenderEngine/Manager.h"

//crr make it singleton 2010-06-07
namespace xs
{

	class TextureManager : public Manager<ITexture*> , public ITextureManager, public Singleton<TextureManager>
	{
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

		/**��ȡ��Ⱦ�̵߳�ID //added by xxh 20091029
		@return ��Ⱦ�̵߳�ID,0����ʾ��û�г�ʼ��
		@remarks �˺������ڻ�ȡ��Ⱦ�̵߳�ID����opengl���̻߳����������ж��Ƿ���ͬһ���߳�
		*/
		inline ulong getRenderThreadID() { return m_ulRenderThreadId; }

//	protected:
		TextureManager() : m_ui32Num(0){ m_ulRenderThreadId = static_cast<ulong> ( GetCurrentThreadId() ); }
	public:
		static TextureManager*	Instance()
		{
			//static TextureManager tm;
			//return &tm;
			return getInstancePtr();
		}

		~TextureManager(){}
	private:
		void doDelete(ITexture* pTexture);
		const char* getUniqueString();

		uint	m_ui32Num;

		ulong	m_ulRenderThreadId;//addedy by xxh����ǰ��Ⱦ�̵߳�id
	};

}
#endif