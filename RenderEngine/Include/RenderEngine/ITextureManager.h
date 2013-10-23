#ifndef __I_TextureManager_H__
#define __I_TextureManager_H__

namespace xs
{
	/*! addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/

	/*��Ҫ����Ⱦѭ���д����������һ��Ҫ������ʹ�ú�׺ΪNoWait�����ĺ������������Ŀ��ܻ���������,
		����createEmptyTexture������Ӧ�ĺ���ΪcreateEmptyTextureNoWait��
	*/


	class Image;

	/** ��ͼ�ӿ�
	*/
	struct ITexture
	{
		/** �ͷ���ͼ
		*/
		virtual void 			release() = 0;																	
		
		/** ��ȡ��ͼ���
		@return ��ͼ���ֵ
		*/
		virtual uint			width() = 0;																	
		
		/** ��ȡ��ͼ�߶�
		@return ��ͼ�߶�ֵ
		*/
		virtual uint			height() = 0;																	
		
		/** ��ȡ��ͼ���ֵ
		@return ��ͼ���ֵ
		*/
		virtual uint			depth() = 0;																	
		
		/** ��ȡ��ͼMipmaps��Ŀ������Ϊ1
		@return Mipmaps��Ŀ
		*/
		virtual uint			getNumMipmaps() = 0;															
		
		/** ��ȡ��ͼ������cubemapΪ6�����������1
		@return ��ͼ����
		*/
		virtual uint			getNumFaces() = 0;																
		
		/** �Ƿ���Alphaͨ��
		@return true��ͨ����false��û��
		*/
		virtual bool			hasAlpha() = 0;																	
		
		/** ��ȡ��ͼ���ظ�ʽ
		@return ���ظ�ʽ
		*/
		virtual PixelFormat		getPixelFormat() = 0;															
		
		/** ��ͼ�Ƿ�ѹ��
		@return true��ѹ����ʽ��falseδѹ��
		*/
		virtual bool			isCompressed() = 0;																
		
		/** ��ȡ��ͼ���ƣ��������ļ���������ϵͳ���ɵ�Ψһ����
		@return ��ͼ����
		*/
		virtual const std::string&	getName() = 0;																	
		
		/** ���ļ��д�����ͼ
		@param name �ļ���
		@return true��ʾ�����ɹ���false��ʾʧ��
		*/
		virtual bool			loadFromFile(const std::string& name) = 0;											
		
		/** ��Raw�д�����ͼ��Raw��ÿ����Ԫ��Ӧ����pf��ʽ
		@param pBuffer �ڴ�ָ��
		@param width ���
		@param height �߶�
		@param pf ���ظ�ʽPF_R8G8B8�ȵ�
		@return true��ʾ�����ɹ���false��ʾʧ��
		*/
		virtual bool			loadFromRawData(uchar *pBuffer,uint width,uint height,PixelFormat pf) = 0;	
		
		/** ��Image�д�����ͼ
		@param image ͼ������
		@param pRect ��ͼ������,��ʱ����Ҫͼ���ȫ��
		@return true��ʾ�����ɹ���false��ʾʧ��
		*/
		virtual bool			loadFromImage(const Image& image,const Rect* pRect = 0) = 0;
		
		/** ������ͼ��������,���ظ�ʽ��Ҫ�û��Լ���֤����
		@param level Ҫ�������ݵ�ͼ��Mipmaps�ȼ�,��0��ʼ
		@param left ��߿�ʼ�±�
		@param top �ϱ߿�ʼ�±�
		@param width ���
		@param height �߶�
		@param pData ���õ���ͼ����
		@return true��ʾ�����ɹ���false��ʾʧ��
		*/
		virtual bool			setSubData(uint level,uint left,uint top,uint width,uint height,void  *pData) = 0;	
		
		/** ������ͼ��������,��ͼ���ȡ����,��image��pRect��ȡ����blt����ͼ��(0,0)
		@param level Ҫ�������ݵ�ͼ��Mipmaps�ȼ�,��0��ʼ
		@param image ͼ������
		@param pRect ͼ���������
		@return true��ʾ�����ɹ���false��ʾʧ��
		*/
		virtual bool			setSubData(uint level,const Image& image,const Rect* pRect) = 0;


		/**��ȡռ���ڴ��С
		*/
		virtual size_t			getMemorySize() = 0;

		/** �����û��Զ�����Ϣ
		*/
		virtual void			setCustomInfo(const std::string & key, const std::string & val) = 0;

		/** ��ȡ�û��Զ�����Ϣ
		@return ����false��ʾû������Զ������Ϣ
		*/
		virtual bool			getCustomInfo(const std::string & key, std::string & val)=0;
	};


	/** ��ͼ�������ӿ�
	*/
	struct ITextureManager
	{
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
			TextureAddressingMode s = TAM_WRAP,											
			TextureAddressingMode t = TAM_WRAP) = 0;										

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
			TextureAddressingMode s = TAM_WRAP,											
			TextureAddressingMode t = TAM_WRAP) = 0;										

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
			TextureAddressingMode s = TAM_WRAP,											
			TextureAddressingMode t = TAM_WRAP) = 0;										

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
			TextureAddressingMode s = TAM_WRAP,											
			TextureAddressingMode t = TAM_WRAP) = 0;										

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
			TextureAddressingMode s = TAM_WRAP,											
			TextureAddressingMode t = TAM_WRAP,const std::string& name= "") = 0;			

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
			TextureAddressingMode s = TAM_WRAP,											
			TextureAddressingMode t = TAM_WRAP) = 0;

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
			TextureAddressingMode s = TAM_WRAP,											
			TextureAddressingMode t = TAM_WRAP) = 0;

		/** �����ļ���ȡ����ͼָ�룬Ҳ�������Զ������ͼ����
		@param name �ļ��������Զ������ͼ����
		@return ��ͼָ��
		*/
		virtual ITexture*	getTexture(const std::string& name) = 0;											

		/** �ͷ���ͼ
		@param pTexture ��ͼ��ָ��
		*/
		virtual void 	releaseTexture(ITexture* pTexture) = 0;															

		/** ���������ͷ���ͼ
		@param name ��ͼ������
		*/
		virtual void 	releaseTextureByName(const std::string& name) = 0;										

		/** �ͷ�������ͼ
		*/
		virtual void 	releaseAll() = 0;
	};
	/** @} */
}
#endif