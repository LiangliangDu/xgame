#ifndef __D3D9Device_H__
#define __D3D9Device_H__

/*
	����Ҫϣ��֧�ֶ����Ⱦϵͳ
*/

namespace xs
{
	class D3D9Device;
	class D3D9Driver;

	//d3d9 �豸����
	struct	D3D9DeviceCreater
	{
		/*
		������Ⱦ���洴�����������豸,��������ĵ���һ��Ҫ����������������Ⱦϵͳ���󴴽��ú����
		@param pRenderSystem ��Ⱦϵͳָ��
		@param uiAdapterOrdinal �Կ����
		@param param ��������
		@param dwBehaviorFlags �豸��Ϊ��־
		@return �豸����
		*/
		static D3D9Device * create( 
			RenderSystemD3D9 * pRenderSystem,
			uint uiAdapterOrdinal,
			const D3DDISPLAYMODE &  devMode,
			const RenderEngineCreationParameters &  param,
			DWORD dwBehaviorFlags);

		/*
		�Զ��崴���豸,��������ĵ���һ��Ҫ����������������Ⱦϵͳ���󴴽��ú����
		@param pRenderSystem ��Ⱦϵͳָ��
		@param uiAdapterOrdinal �Կ����
		@param dwBehaviorFlags �豸������־
		@param pPresentParams ����������
		@return �Ƿ񴴽��ɹ�
		*/
		static D3D9Device * create( 
			RenderSystemD3D9 * pRenderSystem,
			uint uiAdapterOrdinal,
			HWND hFocusWindow,
			DWORD dwBehaviorFlags,
			D3DPRESENT_PARAMETERS * pPresentParams);
	};

	class D3D9Device
	{
	public:
		/**�ͷ��豸
		*/
		void release();

		/** ��ȡ��ʾ����
		*/
		inline const D3DPRESENT_PARAMETERS & getPresentParams() { return m_PresentParams; };

		/**��ȡIDirect3DDevice9����
		*/
		inline IDirect3DDevice9 * getDevice() {return m_pDevice;}

		/** ��ȡ��Ⱦ����
		*/
		inline RenderSystemCapabilities * getCapabilities() { return &m_capabilities; }

		/** ��ȡD3D9��Ⱦ����
		*/	
		inline const D3DCAPS9 &  getD3D9Caps() { return m_caps; }

		/** ��ȡ�豸֧�ֵ������ʽ
		*/
		D3DFORMAT getClosetSupportedTextureFormat( PixelFormat pf);

		/**	�豸����
		*/
		bool	reset(bool fullscreen, uint width, uint height);
		bool	reset();
		bool	reset( bool bVerticalSync);
	
	private:
		/** ��ʼ����Ⱦ����
		*/
		void initCapabilities();
		/** ��ʼ��vs��Ⱦ����
		*/
		void initVertexShaderCaps();
		/** ��ʼ��ps��Ⱦ����
		*/
		void initPixelShaderCaps();

		/** ��ʼ��֧�ֵ������ʽ
		*/
		void initClosetSuppoertedTextureFormat();	

		/** �����豸
		*/
		bool _reset( bool fullscreen, uint width, uint height, bool bVerticalSync);

	private:
		friend struct D3D9DeviceCreater;
		D3D9Device();
		~D3D9Device	();	

	private:
		DWORD m_dwBehaviorFlags;				//�豸��Ϊ��ʽ
		HWND		m_hFocusWindow;				//���㴰��
		D3DPRESENT_PARAMETERS m_PresentParams;	//����������
		IDirect3DDevice9 * m_pDevice;			//d3d9�豸�ӿ�
		D3DCAPS9	m_caps;						//�豸����
		D3DDEVICE_CREATION_PARAMETERS m_createParams; //��������
		RenderSystemCapabilities m_capabilities;//�豸��Ⱦ����,��m_caps�ȼ�,������ⲿ��
		RenderSystemD3D9 *		m_pRenderSystem;//��Ⱦϵͳָ��

	private: 
		//֧�ֵĸ�ʽ
		typedef std::map<PixelFormat, D3DFORMAT> ClosetSupportedFormatContainer;
		typedef ClosetSupportedFormatContainer::iterator ClosetSupportedFormatContainerIterator;
		typedef std::map<PixelFormat, std::vector<D3DFORMAT> > PossibleSupportedFormatContainer;
		typedef PossibleSupportedFormatContainer::iterator PossibleSupportedFormatContainerIterator;
		ClosetSupportedFormatContainer m_supportedTextureFormat; //֧�ֵ���ӽ��������ʽ
	};

}

#endif