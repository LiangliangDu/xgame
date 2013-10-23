#ifndef __Texture_H__
#define __Texture_H__

/*
1) modified by xxh 20091029 
ԭ�򣺶�Ӧnvidi��Geforce 9400 �Կ������������ڵ͵İ汾ʱ����glCompressedTexImage2D()�첽����dds�������뱣֤���ݲ���Ϊ�ա���������
�Խϸߵİ汾������������˵����������������ҪglCompressedTexImage2D()ָ�������ݣ�����glCompressedTexSubImage2D�ϴ����ݡ���seh���ܴ���
���ܱ����������ޡ����ڲ���������ϴ�ͬ���ķ�����renderengine����settexture()����ʱ���������ϴ�����
���������ͬ���ϴ�����ע�⣺����ļ��ؿ��ܻ��첽������������ͷ�һ����ͬ���ģ���������ʹ��һ���̼߳��������޸ĺ󣬺�����loadFromFile��
loadFromRawData��loadFromImage �Է�ѹ����������岻�䣬����ѹ��������������Ѿ������ݼ��ص��ڴ棬��û���ϴ����Դ塣��Ⱦ��������������ʱ�����ȵ���
������uploadTextureToGraphicMemory()
*/

#include "RenderEngine/Manager.h"
#include "TextureManager.h"

namespace xs
{
	class Texture : public ManagedItem , public ITexture
	{
	public:
		/** �ͷ���ͼ
		*/
		virtual void 			release();																	

		/** ��ȡ��ͼ���
		@return ��ͼ���ֵ
		*/
		virtual uint			width();																	

		/** ��ȡ��ͼ�߶�
		@return ��ͼ�߶�ֵ
		*/
		virtual uint			height();																	

		/** ��ȡ��ͼ���ֵ
		@return ��ͼ���ֵ
		*/
		virtual uint			depth();																	

		/** ��ȡ��ͼMipmaps��Ŀ������Ϊ1
		@return Mipmaps��Ŀ
		*/
		virtual uint			getNumMipmaps();															

		/** ��ȡ��ͼ������cubemapΪ6�����������1
		@return ��ͼ����
		*/
		virtual uint			getNumFaces();																

		/** �Ƿ���Alphaͨ��
		@return true��ͨ����false��û��
		*/
		virtual bool			hasAlpha();																	

		/** ��ȡ��ͼ���ظ�ʽ
		@return ���ظ�ʽ
		*/
		virtual PixelFormat		getPixelFormat();															

		/** ��ͼ�Ƿ�ѹ��
		@return true��ѹ����ʽ��falseδѹ��
		*/
		virtual bool			isCompressed();																

		/** ��ȡ��ͼ���ƣ��������ļ���������ϵͳ���ɵ�Ψһ����
		@return ��ͼ����
		*/
		virtual const std::string&	getName();																	

		/** ���ļ��д�����ͼ
		@param name �ļ���
		@return true��ʾ�����ɹ���false��ʾʧ��
		*/
		virtual bool			loadFromFile(const std::string& name);											

		/** ��Raw�д�����ͼ��Raw��ÿ����Ԫ��Ӧ����pf��ʽ
		@param pBuffer �ڴ�ָ��
		@param width ���
		@param height �߶�
		@param pf ���ظ�ʽPF_R8G8B8�ȵ�
		@return true��ʾ�����ɹ���false��ʾʧ��
		*/
		virtual bool			loadFromRawData(uchar *pBuffer,uint width,uint height,PixelFormat pf);	

		/** ��Image�д�����ͼ
		@param image ͼ������
		@param pRect ��ͼ������,��ʱ����Ҫͼ���ȫ��
		@return true��ʾ�����ɹ���false��ʾʧ��
		*/
		virtual bool			loadFromImage(const Image& image,const Rect* pRect = 0);

		/** ������ͼ��������,���ظ�ʽ��Ҫ�û��Լ���֤����
		@param level Ҫ�������ݵ�ͼ��Mipmaps�ȼ�,��0��ʼ
		@param left ��߿�ʼ�±�
		@param top �ϱ߿�ʼ�±�
		@param width ���
		@param height �߶�
		@param pData ���õ���ͼ����
		@return true��ʾ�����ɹ���false��ʾʧ��
		*/
		virtual bool			setSubData(uint level,uint left,uint top,uint width,uint height,void  *pData);	

		/** ������ͼ��������,��ͼ���ȡ����,��image��pRect��ȡ����blt����ͼ��(0,0)
		@param level Ҫ�������ݵ�ͼ��Mipmaps�ȼ�,��0��ʼ
		@param image ͼ������
		@param pRect ͼ���������
		@return true��ʾ�����ɹ���false��ʾʧ��
		*/
		virtual bool			setSubData(uint level,const Image& image,const Rect* pRect);

		virtual size_t			getMemorySize();

		/** �����û��Զ�����Ϣ
		*/
		virtual void			setCustomInfo(const std::string & key, const std::string & val);

		/** ��ȡ�û��Զ�����Ϣ
		@return ����false��ʾû������Զ������Ϣ
		*/
		virtual bool			getCustomInfo(const std::string & key, std::string & val);

	public:
		Texture(const std::string& name,ITextureManager* pTextureManager) 
			:ManagedItem(name),m_pTextureManager(pTextureManager)
			,m_ui32Width(1)
			,m_ui32Height(1)
			,m_ui32Depth(1)
			,m_gluiTextureID(0)
			,m_ui32NumMipmaps(1)
			,m_i32Flags(0)
			,m_pf(PF_UNKNOWN)
			,m_memorySize(0)
			,m_pImageBuffer(0)
			,m_lUploadFlag(0){}
		virtual ~Texture(){ if( m_pImageBuffer){delete m_pImageBuffer; m_pImageBuffer = 0;}}
	private:
		uint		m_ui32Width;
		uint		m_ui32Height;
		uint		m_ui32Depth;
		GLuint		m_gluiTextureID;
		uint		m_ui32NumMipmaps;
		int		m_i32Flags;
		PixelFormat	m_pf;
		ITextureManager *m_pTextureManager;
		size_t		m_memorySize;

		typedef stdext::hash_map<std::string, std::string> CustomInfoMap;
		CustomInfoMap m_customInfo;

	public:
		GLuint		getGLTextureID();
	public:
		void		setWidth(uint w);
		void		setHeight(uint h);
		void		setDepth(uint d);
		void		setGLTextureID(GLuint id);
		void		setNumMipmaps(uint numMipmaps);
		void		setFlags(int flags);
		void		setPixelFormat(PixelFormat pf);
	private:
		//modified by xxh �����ǵ����Դ洢���imageʱ,����
		// _loadFromImage(image, &Image);
		//�����Դ洢ʱ�������
		// _loadFromImage(image);
		bool		_loadFromImage(const Image& image, Image * pImage = 0);
		//added by xxh 20091029 ,����ͬ���ϴ�����
	public:
		//�ϴ�����,���������Ч��
		inline bool uploadTextureToGraphicMemory()
		{
			if( m_lUploadFlag == 1 ) return true;	
			else return realUpLoadTextureToGraphicMemory();
		};
		volatile Image * m_pImageBuffer;//ͼƬ���棬��û���ϴ��������Ѿ���������ʱ���������
		volatile LONG m_lUploadFlag;//�����Ѿ��ϴ��ı�־��1��ʾ�ϴ��ˣ�0��ʾ��û���ϴ���
	private:
		bool realUpLoadTextureToGraphicMemory();
	};

}
#endif