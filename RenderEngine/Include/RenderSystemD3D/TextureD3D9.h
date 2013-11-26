#ifndef __TextureD3D9_H__
#define __TextureD3D9_H__


#include "RenderEngine/Manager.h"
#include "D3D9ResourceManager.h"
/*
	ITexture�ӿڵ����ʹ����ֻ֧����ͨ��������֧��Cube Texture�� Volume Texture, 
	�������ڵ�ʵ����ʱֻ֧����ͨ������
*/


namespace xs
{
	class TextureManagerD3D9;

	class TextureD3D9 : public ManagedItem , public ITexture, public D3D9Resource
	{
		// ITexture�ӿ�
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

		/** ���ļ��д�����ͼ����������ͼ��
		@param name �ļ���
		@return true��ʾ�����ɹ���false��ʾʧ��
		*/
		virtual bool			loadFromFile(const std::string& name);											

		/** ��Raw�д�����ͼ��Raw��ÿ����Ԫ��Ӧ����pf��ʽ����������ͼ��
		@param pBuffer �ڴ�ָ��
		@param width ���
		@param height �߶�
		@param pf ���ظ�ʽPF_R8G8B8�ȵ�
		@return true��ʾ�����ɹ���false��ʾʧ��
		*/
		virtual bool			loadFromRawData(uchar *pBuffer,uint width,uint height,PixelFormat pf);	

		/** ��Image�д�����ͼ����������ͼ��
		@param image ͼ������
		@param pRect ��ͼ������,��ʱ����Ҫͼ���ȫ��
		@return true��ʾ�����ɹ���false��ʾʧ��
		*/
		virtual bool			loadFromImage(const Image& image,const Rect* pRect = 0);

		/** ������ͼ��������,���ظ�ʽ��Ҫ�û��Լ���֤����,��������ͼ��
		@param level Ҫ�������ݵ�ͼ��Mipmaps�ȼ�,��0��ʼ
		@param left ��߿�ʼ�±�
		@param top �ϱ߿�ʼ�±�
		@param width ���
		@param height �߶�
		@param pData ���õ���ͼ����
		@return true��ʾ�����ɹ���false��ʾʧ��
		*/
		virtual bool			setSubData(uint level,uint left,uint top,uint width,uint height,void  *pData);	

		/** ������ͼ��������,��ͼ���ȡ����,��image��pRect��ȡ����blt����ͼ��(0,0)����������ͼ��
		@param level Ҫ�������ݵ�ͼ��Mipmaps�ȼ�,��0��ʼ
		@param image ͼ������
		@param pRect ͼ���������, RECT��right ��bottom ��D3D9�Ĳ�һ����
		@return true��ʾ�����ɹ���false��ʾʧ��
		*/
		virtual bool			setSubData(uint level,const Image& image,const Rect* pRect);


		/**��ȡռ���ڴ��С
		*/
		virtual size_t			getMemorySize();

		/** �����û��Զ�����Ϣ
		*/
		virtual void			setCustomInfo(const std::string & key, const std::string & val);

		/** ��ȡ�û��Զ�����Ϣ
		@return ����false��ʾû������Զ������Ϣ
		*/
		virtual bool			getCustomInfo(const std::string & key, std::string & val);


		//D3D9Resource�ӿ�
	public:
		// �豸��ʧ���������ͷ�Default Pool�������Դ
		virtual void notifyOnDeviceLost();

		//�豸�ָ�, �������ؽ�Default Pool �������Դ
		virtual void notifyOnDeviceReset();

	public:
		enum	CreateTextureOptions
		{
			CTO_DEFAULT = 0x0,//Ĭ��
			CTO_NOWAIT = 0x1,//����Ҫ�ȴ���Ⱦ���
		};
		/** ��������,�Զ������غ�ʹ�÷�ʽ
		*/
		bool _create(D3DPOOL pool, DWORD usage, uint width, uint height,  PixelFormat pf, CreateTextureOptions option= CTO_DEFAULT);

		/**
		*/
		bool lock(UINT level, D3DLOCKED_RECT & lockedrect, DWORD flag);

		/**
		*/
		void unlock();

		/**
		*/
		bool isLocked();

		/**
		*/

	public:
		void		setWidth(uint w);
		void		setHeight(uint h);
		void		setDepth(uint d);
		void		setNumMipmaps(uint numMipmaps);
		void		setFlags(int flags);
		void		setPixelFormat(PixelFormat pf);
		bool		_loadFromImage(const Image& image);

		void		applyFilterState(DWORD sampler);//�˺�������Ⱦϵͳ���ã����ù�����״̬
		inline		IDirect3DTexture9 * getD3DTexture(){ return m_pTex;};//��ȡD3D9����

		inline FilterOptions getMinFilter() const { return m_minFilter;}
		inline FilterOptions getMagFilter() const { return m_magFilter;}
		inline FilterOptions getMipFilter() const { return m_mipmapFilter;}
		inline TextureAddressingMode getAddressS() const { return m_addressS;}
		inline TextureAddressingMode getAddressT() const { return m_addressT;}

	private:
		RECT		getD3DRect(const  xs::Box & box );
		UINT		getRowPitch(PixelFormat pf, uint rowWidth);

	public:
		TextureD3D9(const std::string& name
			,TextureManagerD3D9* pTextureManager
			,FilterOptions min
			,FilterOptions mag
			,FilterOptions mip
			,TextureAddressingMode s
			,TextureAddressingMode t);
		virtual ~TextureD3D9();
	private:
		uint		m_ui32Width;
		uint		m_ui32Height;
		uint		m_ui32Depth;
		uint		m_ui32NumMipmaps;
		int		m_i32Flags;
		PixelFormat	m_pf;		
		size_t		m_memorySize;

		FilterOptions m_minFilter;
		FilterOptions m_magFilter;
		FilterOptions m_mipmapFilter;
		TextureAddressingMode m_addressS;
		TextureAddressingMode m_addressT;

		TextureManagerD3D9 *m_pTextureManager;
		D3DPOOL		m_poolType;
		DWORD		m_usage;	
		IDirect3DTexture9 * m_pTex;

		bool		m_bLocked;
		uint		m_uiLockedLevel;

		typedef stdext::hash_map<std::string, std::string> CustomInfoMap;
		CustomInfoMap m_customInfo;
	};
}
#endif