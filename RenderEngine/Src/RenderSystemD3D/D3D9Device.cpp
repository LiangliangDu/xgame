#include "StdAfx.h"
#include "RenderSystemD3D9.h"
#include "D3D9Device.h"
#include "D3D9Driver.h"

//�Ƿ�֧��PerfHud���ߣ�1��֧�֣�0����֧��
#define D3D9DEVICE_SUPPORT_PERFHUD			0


namespace xs
{

	D3D9Device* D3D9DeviceCreater::create( 
			RenderSystemD3D9 * pRenderSystem,
			uint uiAdapterOrdinal,
			const D3DDISPLAYMODE &  devMode,
			const RenderEngineCreationParameters &  param,
			DWORD dwBehaviorFlags)
	{
		//��ʼ����������
		D3DPRESENT_PARAMETERS presentParams;
		ZeroMemory(&presentParams, sizeof(presentParams));
		presentParams.Windowed = param.fullscreen ? FALSE : TRUE;
		if( presentParams.Windowed )
		{
			//�󻺴��ʽ
			//presentParams.BackBufferCount = 1;//�󻺴�����Ƿ�ֱͬ������
			presentParams.BackBufferWidth = 0;
			presentParams.BackBufferHeight = 0;
			presentParams.BackBufferFormat = devMode.Format;
			//��Ⱦ����
			presentParams.hDeviceWindow = (HWND)param.hwnd;
			//��ν�������
			presentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
			//���ģ�滺��
			presentParams.EnableAutoDepthStencil = param.stencilBuffer  ? TRUE : FALSE;
			if( presentParams.EnableAutoDepthStencil )
				presentParams.AutoDepthStencilFormat = D3DFMT_D24S8;
			else
				presentParams.AutoDepthStencilFormat = D3DFMT_D32;
			//��ֱͬ��
			if( param.vertcialSync)
			{
				presentParams.BackBufferCount = 2;
				presentParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			}
			else
			{
				presentParams.BackBufferCount = 1;
				presentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
			}
		}
		else
		{
			//�󻺴��ʽ
			//presentParams.BackBufferCount =1;//�󻺴�����Ƿ�ֱͬ������
			presentParams.BackBufferFormat = devMode.Format;
			presentParams.BackBufferHeight = devMode.Height;
			presentParams.BackBufferWidth = devMode.Width;
			presentParams.hDeviceWindow =  (HWND)param.hwnd;
			//���潻����ʽ
			presentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
			//���ģ�滺��
			presentParams.EnableAutoDepthStencil = param.stencilBuffer ? TRUE : FALSE;
			if( presentParams.EnableAutoDepthStencil )
				presentParams.AutoDepthStencilFormat = D3DFMT_D24S8;
			else
				presentParams.AutoDepthStencilFormat = D3DFMT_D32;	
			//��ֱͬ��
			if( param.vertcialSync)
			{
				presentParams.BackBufferCount = 2;
				presentParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			}
			else
			{
				presentParams.BackBufferCount = 1;
				presentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
			}

			presentParams.FullScreen_RefreshRateInHz = devMode.RefreshRate;//ȫ��ˢ����
		}

		if (NULL != pRenderSystem)
		{
			IDirect3D9* pD3D9 = pRenderSystem->getDirect3D9();
			if (NULL != pD3D9)
			{
				DWORD dwQualityLevel = 0, dwQualityLevelDepth = 0;
				bool bSupport      = SUCCEEDED(pD3D9->CheckDeviceMultiSampleType(uiAdapterOrdinal, D3DDEVTYPE_HAL, presentParams.BackBufferFormat, presentParams.Windowed, D3DMULTISAMPLE_2_SAMPLES, &dwQualityLevel));
				bool bSupportDepth = SUCCEEDED(pD3D9->CheckDeviceMultiSampleType(uiAdapterOrdinal, D3DDEVTYPE_HAL, presentParams.AutoDepthStencilFormat, presentParams.Windowed, D3DMULTISAMPLE_2_SAMPLES, &dwQualityLevelDepth));
				if (bSupport && bSupportDepth)
				{
					presentParams.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;//D3DMULTISAMPLE_NONE; //D3DMULTISAMPLE_2_SAMPLES;
					presentParams.MultiSampleQuality = std::min(dwQualityLevel, dwQualityLevelDepth) - 1;
				}

			}
		}
        //presentParams.Flags =  D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

		dwBehaviorFlags |= D3DCREATE_MULTITHREADED | D3DCREATE_PUREDEVICE/* | D3DCREATE_ADAPTERGROUP_DEVICE*/;
		D3D9Device * pDevice = D3D9DeviceCreater::create(
			pRenderSystem,
			uiAdapterOrdinal,
			(HWND)param.hwnd,
			dwBehaviorFlags,
			&presentParams);
		if( NULL == pDevice)
		{
			if( param.stencilBuffer) presentParams.AutoDepthStencilFormat = D3DFMT_D15S1;
			else presentParams.AutoDepthStencilFormat = D3DFMT_D16;
			pDevice = D3D9DeviceCreater::create(
			pRenderSystem,
			uiAdapterOrdinal,
			(HWND)param.hwnd,
			dwBehaviorFlags,
			&presentParams);
		}

		return pDevice;
	}

	D3D9Device * D3D9DeviceCreater::create( 
			RenderSystemD3D9 * pRenderSystem,
			uint uiAdapterOrdinal,
			HWND hFocusWindow,
			DWORD dwBehaviorFlags,
			D3DPRESENT_PARAMETERS * pPresentParams)
	{
		if( NULL == hFocusWindow )
		{
			Trace("Trace:D3D9DeviceCreater::create	hFocusWindow == 0\n");
			return 0;
		}

		if( NULL == pPresentParams)
		{
			Trace("Trace:D3D9DeviceCreater::create	pPresentParams == 0\n");
			return 0;
		}

		if( NULL == pRenderSystem)
		{
			Trace("Trace:D3D9DeviceCreater::create	pRenderSystem == 0\n");
			return 0;
		}	

		IDirect3D9 * pD3D9 = pRenderSystem->getDirect3D9();
		if( NULL == pD3D9)
		{
			Trace("Trace:D3D9DeviceCreater::create	pD3D9 == 0\n");
			return 0;
		}

		D3D9Device * pDevice = new D3D9Device();
		if( NULL == pDevice)
		{
			Trace("Trace:D3D9DeviceCreater::create	pDevice == 0\n");
			return 0;
		}

#if D3D9DEVICE_SUPPORT_PERFHUD

		pDevice->m_pRenderSystem = pRenderSystem;
		HRESULT hr;
		pDevice->m_dwBehaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		pDevice->m_PresentParams = *pPresentParams;
		pDevice->m_hFocusWindow = hFocusWindow;
		UINT adapter = 0;
		uint adaptercount = pRenderSystem->getDirect3D9()->GetAdapterCount();
		for( uint i=0; i<adaptercount; ++i)
		{
			D3DADAPTER_IDENTIFIER9 id;
			pRenderSystem->getDirect3D9()->GetAdapterIdentifier(i,0, &id);
			if( std::string(id.Description).find("PerfHUD") != std::string::npos )
			{
				adapter = i;
			}
		}

		hr = pD3D9->CreateDevice( 
			adapter,
			D3DDEVTYPE_REF,
			pDevice->m_hFocusWindow,
			pDevice->m_dwBehaviorFlags,
			&pDevice->m_PresentParams,
			&pDevice->m_pDevice );

#else

		pDevice->m_pRenderSystem = pRenderSystem;
		HRESULT hr;
		pDevice->m_dwBehaviorFlags =  dwBehaviorFlags | D3DCREATE_HARDWARE_VERTEXPROCESSING;
		pDevice->m_PresentParams = *pPresentParams;
		pDevice->m_hFocusWindow = hFocusWindow;

		//����HAL�豸��֧��Ӳ��T&L
		hr = pD3D9->CreateDevice( 
			uiAdapterOrdinal,
			D3DDEVTYPE_HAL,
			pDevice->m_hFocusWindow,
			pDevice->m_dwBehaviorFlags,
			&pDevice->m_PresentParams,
			&pDevice->m_pDevice );

		//���ܺ󻺴�Ϊ����1����
		if( FAILED(hr) )
		{
			// Try a second time, may fail the first time due to back buffer count,
			// which will be corrected down to 1 by the runtime
			pDevice->m_PresentParams.BackBufferCount = 1;
			hr = pD3D9->CreateDevice( 
				uiAdapterOrdinal,
				D3DDEVTYPE_HAL,
				pDevice->m_hFocusWindow,
				pDevice->m_dwBehaviorFlags,
				&pDevice->m_PresentParams,
				&pDevice->m_pDevice );
		}

		//����HAL�豸��֧�ֻ��T&L
		if( FAILED(hr) )
		{
			pDevice->m_dwBehaviorFlags &= ~(D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_PUREDEVICE);
			pDevice->m_dwBehaviorFlags |= D3DCREATE_MIXED_VERTEXPROCESSING;
			hr= pD3D9->CreateDevice(
					uiAdapterOrdinal,
					D3DDEVTYPE_HAL,
					pDevice->m_hFocusWindow,
					pDevice->m_dwBehaviorFlags,
					&pDevice->m_PresentParams,
					&pDevice->m_pDevice);
		
		}

		//����HAL�豸��֧�����T&L
		if( FAILED(hr) )
		{
			pDevice->m_dwBehaviorFlags &= ~D3DCREATE_MIXED_VERTEXPROCESSING;
			pDevice->m_dwBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
			hr= pD3D9->CreateDevice( 
					uiAdapterOrdinal,
					D3DDEVTYPE_HAL,
					pDevice->m_hFocusWindow,
					pDevice->m_dwBehaviorFlags,
					&pDevice->m_PresentParams,
					&pDevice->m_pDevice);	
		}

		//����REF�豸
		if( FAILED(hr) )
		{
			hr= pD3D9->CreateDevice( 
					uiAdapterOrdinal,
					D3DDEVTYPE_REF,
					pDevice->m_hFocusWindow,
					pDevice->m_dwBehaviorFlags,
					&pDevice->m_PresentParams,
					&pDevice->m_pDevice);	
		}
#endif

		if( FAILED(hr) )
		{
			delete pDevice;
			Trace("Trace:D3D9DeviceCreater::create	CreateDevice == 0\n");
			return 0;
		}

		//��ȡ�豸��Ⱦ����
		hr = pDevice->m_pDevice->GetDeviceCaps( &pDevice->m_caps);
		if( FAILED(hr) )
		{
			pDevice->m_pDevice->Release();
			delete pDevice;
			Trace("Trace:D3D9DeviceCreater::create	GetDeviceCaps == 0\n");
			return 0;
		}

		//��ȡ��������
		hr = pDevice->m_pDevice->GetCreationParameters( &pDevice->m_createParams);
		if( FAILED(hr))
		{
			pDevice->m_pDevice->Release();
			delete pDevice;
			Trace("Trace:D3D9DeviceCreater::create	GetCreationParameters == 0\n");
			return 0;
		}		

		//��ʼ���豸����Ⱦ����
		if( pDevice)
		{
			pDevice->initCapabilities();
		}

		//���֧�ֵ������ʽ
		if( pDevice )
		{
			pDevice->initClosetSuppoertedTextureFormat();
		}

		return pDevice;
	}


	/**	�豸����
	*/

	bool D3D9Device::reset()
	{
		bool fullscreen = m_PresentParams.Windowed ? false : true;
		uint width = m_PresentParams.BackBufferWidth;
		uint height = m_PresentParams.BackBufferHeight;
		bool bSync = (m_PresentParams.PresentationInterval == D3DPRESENT_INTERVAL_ONE);
		return _reset( fullscreen, width, height, bSync);
	}

	bool D3D9Device::reset( bool bVerticalSync)
	{
		bool fullscreen = m_PresentParams.Windowed ? false : true;
		uint width = m_PresentParams.BackBufferWidth;
		uint height = m_PresentParams.BackBufferHeight;
		return _reset( fullscreen, width, height, bVerticalSync);
	}

	/** �����豸
	*/
	bool D3D9Device::_reset( bool fullscreen, uint width, uint height, bool bVerticalSync)
	{
		D3DPRESENT_PARAMETERS params = m_PresentParams;
		const D3DDISPLAYMODE &	devMode = m_pRenderSystem->getD3D9Driver()->getCurrentDisplayMode();

		if( bVerticalSync ) 
		{
			params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			params.BackBufferCount = 2;
		}
		else 
		{
			params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
			params.BackBufferCount = 1;
		}

	/*	if( fullscreen )
		{
			D3DDISPLAYMODE mode;
			bool ret = m_pRenderSystem->getD3D9Driver()->getDisplayMode( devMode.Width, devMode.Height, devMode.Format, mode);
			if( ret ) params.FullScreen_RefreshRateInHz = mode.RefreshRate;
			else	params.FullScreen_RefreshRateInHz = devMode.RefreshRate;
			params.Windowed = FALSE;
			params.BackBufferFormat = devMode.Format;
			params.BackBufferHeight = devMode.Height;
			params.BackBufferWidth = devMode.Width;
		}
		else*/
		{
			params.Windowed = TRUE;
			params.BackBufferFormat = devMode.Format;
			params.BackBufferWidth = width;
			params.BackBufferHeight  = height;
			params.FullScreen_RefreshRateInHz = 0;
		}

		HRESULT hr = m_pDevice->Reset( &params);
		if( FAILED(hr) && params.BackBufferCount == 2 )
		{
			params.BackBufferCount = 1;
			hr = m_pDevice->Reset( &params);
		}

		if( FAILED(hr) ) return false;
		
		//�������
		m_PresentParams = params;

		//���³�ʼ���豸֧�ֵĸ�ʽ��
		initClosetSuppoertedTextureFormat();

		return true;		
	}

	bool D3D9Device::reset(bool fullscreen, uint width, uint height)
	{
		bool bSync = (m_PresentParams.PresentationInterval == D3DPRESENT_INTERVAL_ONE);
		return _reset( fullscreen, width, height, bSync);
	}


	D3D9Device::D3D9Device():
	m_dwBehaviorFlags(0),
	m_pDevice(0),
	m_hFocusWindow(0)
	{
		memset(&m_createParams, 0, sizeof( m_createParams));
		memset(&m_caps,0,sizeof(m_caps));
		memset(&m_PresentParams, 0, sizeof(m_PresentParams) );
	}

	D3D9Device::~D3D9Device()
	{
		
	}

	void D3D9Device::release()
	{
		COM_SAFE_RELEASE( m_pDevice);
		delete this;
	}


	/** ��ʼ����Ⱦ����
	*/
	void D3D9Device::initCapabilities()
	{

		Trace("=========D3D9 Information==========\n");

		//����Ƿ�Ӳ��֧���Զ�mipmap����
		if ((m_caps.Caps2 & D3DCAPS2_CANAUTOGENMIPMAP))
		{
			m_capabilities.setCapability(RSC_AUTOMIPMAP);
			Trace("OK! AutoMipmap\n");
		}
		else
		{
			Trace("FAIL! AutoMipmap\n");
		}

		//���������,Ĭ��֧��
		{
			m_capabilities.setCapability(RSC_BLENDING);
			Trace("OK! Blending\n");
		}


		//��������֧��
		{
			m_capabilities.setNumTextureUnits( static_cast<ushort>(m_caps.MaxSimultaneousTextures) );
			Trace("TextureUnits: "<<m_caps.MaxSimultaneousTextures<<endl);
		}

		//����ĸ�������
		if( m_caps.MaxAnisotropy > 1)
		{
			m_capabilities.setCapability(RSC_ANISOTROPY);
			Trace("OK! Anisotropy Filter\n");
		}
		else
		{
			Trace("FAIL! Anisotropy Filter\n");
		}

		//DOT3����
		if( m_caps.TextureOpCaps & D3DTEXOPCAPS_DOTPRODUCT3)
		{
			m_capabilities.setCapability(RSC_DOT3);
			Trace("OK! Dot3\n");
		}
		else
		{
			Trace("FAIL! Dot3\n");
		}

		//����������
		if( m_caps.TextureOpCaps & D3DPTEXTURECAPS_CUBEMAP)
		{	
			m_capabilities.setCapability(RSC_CUBEMAPPING);
			Trace("OK! CubeMapping\n");	
		}
		else
		{
			Trace("FAIL! CubeMapping\n");
		}

		//Ӳ����ģ�建��֧��
		IDirect3DSurface9 * pSurf;
		m_pDevice->GetDepthStencilSurface( &pSurf);
		if( NULL != pSurf)
		{
			D3DSURFACE_DESC surfdesc;
			pSurf->GetDesc( &surfdesc);
			pSurf->Release();
			bool supportstencil = false;
			ushort stencildepth = 0;
			switch(surfdesc.Format)
			{
			case D3DFMT_D15S1:
				supportstencil = true;
				stencildepth = 1;
				break;
			case D3DFMT_D24S8:
			case D3DFMT_D24FS8:
				supportstencil = true;
				stencildepth = 8;
				break;
			case D3DFMT_D24X4S4:
				supportstencil = true;
				stencildepth = 4;
				break;
			}
			if( supportstencil )
			{
				m_capabilities.setCapability(RSC_HWSTENCIL);
				m_capabilities.setStencilBufferBitDepth(stencildepth);
				Trace("OK! Hardware Stencil Buffer depth = "<<stencildepth<<endl);
			}
			else 
			{
				Trace("FAIL! Hardware Stencil Buffer\n");
			}		
		}
		else
		{
			Trace("FAIL! Hardware Stencil Buffer\n");
		}

		//VBO֧��,��������
		{
			m_capabilities.setCapability(RSC_VBO);
			Trace("OK! Vertex Buffer Object\n");
		}

		//vertex shader֧��
		initVertexShaderCaps();

		//pixel shader֧��
		initPixelShaderCaps();

		//ѹ������
		{
			// We always support compression, D3DX will decompress if device does not support
			//RSC_TEXTURE_COMPRESSION_VTC, ��֧��
			m_capabilities.setCapability(RSC_TEXTURE_COMPRESSION);
			m_capabilities.setCapability(RSC_TEXTURE_COMPRESSION_DXT);
			Trace("OK! Texture Compression\n");
		}

		//���в���
		if ((m_caps.RasterCaps & D3DPRASTERCAPS_SCISSORTEST) )
		{
			m_capabilities.setCapability(RSC_SCISSOR_TEST);
			Trace("OK! Scissor Test\n");
		}
		else
		{
			Trace("FAIL! Scissor Test\n");
		}

		//֧�ֶ���ļ�����
		if (m_caps.MaxUserClipPlanes > 0)	
		{
			m_capabilities.setCapability(RSC_USER_CLIP_PLANES);	
			Trace("OK! User Clip Planes="<<m_caps.MaxUserClipPlanes<<endl );
		}
		else
		{
			Trace("FAIL! User Clip Planes\n");
		}

		//˫��ģ�建��
		if ((m_caps.StencilCaps & D3DSTENCILCAPS_TWOSIDED))
		{
			m_capabilities.setCapability(RSC_TWO_SIDED_STENCIL);
			Trace("OK! Two Side Stencil\n");
		}
		else
		{
			Trace("FAIL! Two Side Stencil\n");
		}

		// ģ�建��֧��ѭ��
		if ((m_caps.StencilCaps & D3DSTENCILCAPS_INCR) &&
			(m_caps.StencilCaps & D3DSTENCILCAPS_DECR) )
		{
			m_capabilities.setCapability(RSC_STENCIL_WRAP);
			Trace("OK! Stencil Wrap\n");
		}
		else
		{
			Trace("FAIL! Stencil Wrap\n");
		}

		//Ӳ��֧���ڵ����
		HRESULT hrOcclusion = m_pDevice->CreateQuery(D3DQUERYTYPE_OCCLUSION, NULL);
		if( FAILED(hrOcclusion) )
		{
			Trace("FAIL! Hardware Occlusion Query\n");
		}
		else
		{
			m_capabilities.setCapability(RSC_HWOCCLUSION);
			Trace("OK! Hardware Occlusion Query\n");
		}

		// vbo ���������ݸ�ʽ��UBYTE4 type?
		if (m_caps.DeclTypes & D3DDTCAPS_UBYTE4)		
		{
			m_capabilities.setCapability(RSC_VERTEX_FORMAT_UBYTE4);
			Trace("OK! Vertex Declaration Support UBYTE4\n");
		}
		else
		{
			Trace("FAIL! Vertex Declaration Support UBYTE4\n");
		}

		// Inifinite far plane always supported
		{
			m_capabilities.setCapability(RSC_INFINITE_FAR_PLANE);
			Trace("OK! Infinite Far Plane\n");
		}

		// ��2���ݵ������֧��
		if ( (m_caps.TextureCaps & D3DPTEXTURECAPS_POW2) == 0
			&& (m_caps.TextureCaps &D3DPTEXTURECAPS_NONPOW2CONDITIONAL) == 0  )
		{	
			m_capabilities.setCapability(RSC_NON_POWER_OF_2_TEXTURES);
			Trace("OK! Non Power of 2 Textures\n");
		}	
		else
		{
			Trace("FAIL! Non Power of 2 Textures\n");
		}

		//��������ʽ������
		D3DFORMAT floatFormats[6] = {D3DFMT_R16F, D3DFMT_G16R16F, 
			D3DFMT_A16B16G16R16F, D3DFMT_R32F, D3DFMT_G32R32F, 
			D3DFMT_A32B32G32R32F};
		D3DDISPLAYMODE devmod;
		IDirect3D9 * pD3D9 = m_pRenderSystem->getDirect3D9();
		pD3D9->GetAdapterDisplayMode(m_createParams.AdapterOrdinal,&devmod);
		for (int i = 0; i < 6; ++i)
		{
			if (SUCCEEDED(pD3D9->CheckDeviceFormat(m_createParams.AdapterOrdinal, 
				m_createParams.DeviceType,devmod.Format, 
				0, D3DRTYPE_TEXTURE, floatFormats[i])))
			{
				m_capabilities.setCapability(RSC_TEXTURE_FLOAT);
				Trace("OK! float Texture\n");
				break;
			}
		}
		if( !m_capabilities.hasCapability(RSC_TEXTURE_FLOAT) )
		{
			Trace("FAIL! float Texture\n");
		}

		//3D ����
		if (m_caps.TextureCaps & D3DPTEXTURECAPS_VOLUMEMAP)	
		{
			m_capabilities.setCapability(RSC_TEXTURE_3D);	
			Trace("OK! 3D Texture\n");
		}
		else
		{
			Trace("FAIL! 3D Texture\n");
		}

		//֧��HLSL,�����޶�Ϊͬʱ֧��Vertex Shader ��Pixel Shader
		//�����ں���initPixelShaderCaps����
		{
			if( m_capabilities.hasCapability(RSC_HIGHLEVEL_SHADER) )
			{	Trace("OK! HLSL\n"); }
			else
			{	Trace("FAIL! HLSL\n");}
		}

		//��������size
		m_capabilities.setMaxTextureSize( m_caps.MaxTextureHeight > m_caps.MaxTextureWidth ? m_caps.MaxTextureHeight:m_caps.MaxTextureWidth);
	}


	void D3D9Device::initVertexShaderCaps()
	{
		ushort major = static_cast<ushort>((m_caps.VertexShaderVersion & 0x0000FF00) >> 8);
		ushort minor = static_cast<ushort>(m_caps.VertexShaderVersion & 0x000000FF);
		bool vs2x = false;
		bool vs2a = false;

		// Special case detection for vs_2_x/a support
		if (major >= 2)
		{
			if ((m_caps.VS20Caps.Caps & D3DVS20CAPS_PREDICATION) &&
				(m_caps.VS20Caps.DynamicFlowControlDepth > 0) &&
				(m_caps.VS20Caps.NumTemps >= 12))
			{
				vs2x = true;
			}

			if ((m_caps.VS20Caps.Caps & D3DVS20CAPS_PREDICATION) &&
				(m_caps.VS20Caps.DynamicFlowControlDepth > 0) &&
				(m_caps.VS20Caps.NumTemps >= 13))
			{
				vs2a = true;
			}
		}

		// Populate max param count
		switch (major)
		{
		case 1:
			// No boolean params allowed
			m_capabilities.setVertexProgramConstantBoolCount(0);
			// No integer params allowed
			m_capabilities.setVertexProgramConstantIntCount(0);
			// float params, always 4D
			m_capabilities.setVertexProgramConstantFloatCount(static_cast<ushort>(m_caps.MaxVertexShaderConst));
			//��������Ե�����
			m_capabilities.setMaxVertexAttribs(16);
			//��������ڶ�����ɫ����Uniform����������,?? bool + int + float
			m_capabilities.setMaxVertexUniformComponents(m_caps.MaxVertexShaderConst);
			//���������Varying�����ĸ���������������?? oPos# + oD# + oFog# + oPts# + oT#
			m_capabilities.setMaxVaryingFloats( 1 + 2 + 1 + 1 + 8);
			//�������Ӷ��㴦�����з��ʵ�������ͼ��Ӳ����Ԫ������
			m_capabilities.setMaxVertexTextureImageUnits(0);

			break;
		case 2:
			// 16 boolean params allowed
			m_capabilities.setVertexProgramConstantBoolCount(16);
			// 16 integer params allowed, 4D
			m_capabilities.setVertexProgramConstantIntCount(16);
			// float params, always 4D
			m_capabilities.setVertexProgramConstantFloatCount(static_cast<ushort>(m_caps.MaxVertexShaderConst));
			//��������Ե�����
			m_capabilities.setMaxVertexAttribs(16);
			//��������ڶ�����ɫ����Uniform����������,?? bool + int + float
			m_capabilities.setMaxVertexUniformComponents(16 + 16 + m_caps.MaxVertexShaderConst);
			//���������Varying�����ĸ���������������?? oPos# + oD# + oFog# + oPts# + oT#
			m_capabilities.setMaxVaryingFloats( 1 + 2 + 1 + 1 + 8);
			//�������Ӷ��㴦�����з��ʵ�������ͼ��Ӳ����Ԫ������
			m_capabilities.setMaxVertexTextureImageUnits(16);
			break;
		case 3:
			// 16 boolean params allowed
			m_capabilities.setVertexProgramConstantBoolCount(16);
			// 16 integer params allowed, 4D
			m_capabilities.setVertexProgramConstantIntCount(16);
			// float params, always 4D
			m_capabilities.setVertexProgramConstantFloatCount(static_cast<ushort>(m_caps.MaxVertexShaderConst));
			//��������Ե�����
			m_capabilities.setMaxVertexAttribs(16);
			//��������ڶ�����ɫ����Uniform����������,?? bool + int + float
			m_capabilities.setMaxVertexUniformComponents(16 + 16 + m_caps.MaxVertexShaderConst);
			//���������Varying�����ĸ���������������?? oPos# + oD# + oFog# + oPts# + oT#
			m_capabilities.setMaxVaryingFloats( 12 );
			//�������Ӷ��㴦�����з��ʵ�������ͼ��Ӳ����Ԫ������
			m_capabilities.setMaxVertexTextureImageUnits(4);
			break;
		default:
			break;
		}

		// populate syntax codes in program manager (no breaks in this one so it falls through)
		switch(major)
		{
		case 3:
			m_capabilities.setMaxVertexProgramVersion("vs_3_0");
			break;
		case 2:
			if( vs2a)
				m_capabilities.setMaxVertexProgramVersion("vs_2_a");
			else if( vs2x)
				m_capabilities.setMaxVertexProgramVersion("vs_2_x");
			else 
				m_capabilities.setMaxVertexProgramVersion("vs_2_0");
			break;
		case 1:
			m_capabilities.setMaxVertexProgramVersion("vs_1_1");
			break;
		default:
			break;
		}

		if( major > 0)
			m_capabilities.setCapability(RSC_VERTEX_PROGRAM);	
	}
	void D3D9Device::initPixelShaderCaps()
	{
		ushort major = static_cast<ushort>((m_caps.PixelShaderVersion & 0x0000FF00) >> 8);
		ushort minor = static_cast<ushort>(m_caps.PixelShaderVersion & 0x000000FF);

		// Special case detection for ps_2_x/a/b support
		bool ps2a = false;
		bool ps2b = false;
		if (major >= 2)
		{
			if ((m_caps.PS20Caps.Caps & D3DPS20CAPS_NOTEXINSTRUCTIONLIMIT) &&
				(m_caps.PS20Caps.NumTemps >= 32))
			{
				ps2b = true;
			}

			if ((m_caps.PS20Caps.Caps & D3DPS20CAPS_NOTEXINSTRUCTIONLIMIT) &&
				(m_caps.PS20Caps.Caps & D3DPS20CAPS_NODEPENDENTREADLIMIT) &&
				(m_caps.PS20Caps.Caps & D3DPS20CAPS_ARBITRARYSWIZZLE) &&
				(m_caps.PS20Caps.Caps & D3DPS20CAPS_GRADIENTINSTRUCTIONS) &&
				(m_caps.PS20Caps.Caps & D3DPS20CAPS_PREDICATION) &&
				(m_caps.PS20Caps.NumTemps >= 22))
			{
				ps2a = true;
			}
		}

		switch (major)
		{
		case 1:
			// no boolean params allowed
			m_capabilities.setFragmentProgramConstantBoolCount(0);
			// no integer params allowed
			m_capabilities.setFragmentProgramConstantIntCount(0);
			// float params, always 4D
			// NB in ps_1_x these are actually stored as fixed point values,
			// but they are entered as floats
			m_capabilities.setFragmentProgramConstantFloatCount(8);
			//�������Ӷ����ƬԪ�������з��ʵ�������ͼ��Ӳ����Ԫ������
			m_capabilities.setMaxCombinedTextureImageUnits(0);
			//������õ����꼯������
			m_capabilities.setMaxTextureCoords(4);
			//������ƬԪ��ɫ��Uniform�����Ĳ���(Ҳ���Ǹ�����)������
			m_capabilities.setMaxFragmentUniformComponents(8);
			break;
		case 2:
			// 16 boolean params allowed
			m_capabilities.setFragmentProgramConstantBoolCount(16);
			// 16 integer params allowed, 4D
			m_capabilities.setFragmentProgramConstantIntCount(16);
			// float params, always 4D
			m_capabilities.setFragmentProgramConstantFloatCount(32);
			//�������Ӷ����ƬԪ�������з��ʵ�������ͼ��Ӳ����Ԫ������
			m_capabilities.setMaxCombinedTextureImageUnits(16);
			//������õ����꼯������
			m_capabilities.setMaxTextureCoords(8);
			//������ƬԪ��ɫ��Uniform�����Ĳ���(Ҳ���Ǹ�����)������ ?? int + bool + float
			m_capabilities.setMaxFragmentUniformComponents(16 + 16 +32);
			break;
		case 3:
			// 16 boolean params allowed
			m_capabilities.setFragmentProgramConstantBoolCount(16);
			// 16 integer params allowed, 4D
			m_capabilities.setFragmentProgramConstantIntCount(16);
			// float params, always 4D
			m_capabilities.setFragmentProgramConstantFloatCount(224);
			//�������Ӷ����ƬԪ�������з��ʵ�������ͼ��Ӳ����Ԫ������
			m_capabilities.setMaxCombinedTextureImageUnits(16);
			//������õ����꼯������
			m_capabilities.setMaxTextureCoords(10);
			//������ƬԪ��ɫ��Uniform�����Ĳ���(Ҳ���Ǹ�����)������ ?? int + bool + float
			m_capabilities.setMaxFragmentUniformComponents(16 + 16 +224);
			break;
		}

		// populate syntax codes in program manager (no breaks in this one so it falls through)
		switch(major)
		{
		case 3:
			if (minor > 0)
				m_capabilities.setMaxFragmentProgramVersion("ps_3_x");
			else
				m_capabilities.setMaxFragmentProgramVersion("ps_3_0");
			break;
		case 2:
			if (ps2b)
				m_capabilities.setMaxFragmentProgramVersion("ps_2_b");
			else if( ps2a)
				m_capabilities.setMaxFragmentProgramVersion("ps_2_a");
			else
				m_capabilities.setMaxFragmentProgramVersion("ps_2_0");
			break;
		case 1:
			if( minor >= 4)
				m_capabilities.setMaxFragmentProgramVersion("ps_1_4");
			else if( minor >= 3)
				m_capabilities.setMaxFragmentProgramVersion("ps_1_3");
			else if( minor >= 2)
				m_capabilities.setMaxFragmentProgramVersion("ps_1_2");
			else
				m_capabilities.setMaxFragmentProgramVersion("ps_1_1");
			break;
		}

		if( major > 0 )
			m_capabilities.setCapability(RSC_FRAGMENT_PROGRAM);

		//HLSL֧��ps���λps_2_0
		if( major >= 2)
			m_capabilities.setCapability(RSC_HIGHLEVEL_SHADER);

	}

	D3DFORMAT D3D9Device::getClosetSupportedTextureFormat( PixelFormat pf)
	{
		ClosetSupportedFormatContainerIterator it = m_supportedTextureFormat.find(pf);
		if( it == m_supportedTextureFormat.end())
			return D3DFMT_UNKNOWN;
		else
			return it->second;
	}

	void D3D9Device::initClosetSuppoertedTextureFormat()
	{
		m_supportedTextureFormat.clear();

		PossibleSupportedFormatContainer possible;
		possible[PF_A8].push_back(D3DFMT_A8);
		possible[PF_L8].push_back(D3DFMT_L8);
		possible[PF_L16].push_back(D3DFMT_L16);
		possible[PF_R3G3B2].push_back(D3DFMT_R3G3B2);
		possible[PF_A1R5G5B5].push_back(D3DFMT_A1R5G5B5);
		possible[PF_R5G6B5].push_back(D3DFMT_R5G6B5);// !=
		possible[PF_B5G6R5].push_back(D3DFMT_R5G6B5);// !=
		possible[PF_A4R4G4B4].push_back(D3DFMT_A4R4G4B4);

		possible[PF_R8G8B8].push_back(D3DFMT_R8G8B8);// !=
		possible[PF_R8G8B8].push_back(D3DFMT_X8R8G8B8);
		possible[PF_R8G8B8].push_back(D3DFMT_X8B8G8R8);

		possible[PF_B8G8R8].push_back(D3DFMT_R8G8B8);// !=
		possible[PF_B8G8R8].push_back(D3DFMT_X8R8G8B8);
		possible[PF_B8G8R8].push_back(D3DFMT_X8B8G8R8);

		possible[PF_X8R8G8B8].push_back(D3DFMT_X8R8G8B8);// !=
		possible[PF_X8R8G8B8].push_back(D3DFMT_X8B8G8R8);
		possible[PF_X8R8G8B8].push_back(D3DFMT_R8G8B8);

		possible[PF_A8R8G8B8].push_back(D3DFMT_A8R8G8B8);// !=
		possible[PF_A8R8G8B8].push_back(D3DFMT_A8B8G8R8);

		possible[PF_X8B8G8R8].push_back(D3DFMT_X8B8G8R8); // !=
		possible[PF_X8B8G8R8].push_back(D3DFMT_X8R8G8B8);
		possible[PF_X8B8G8R8].push_back(D3DFMT_R8G8B8);

		possible[PF_A8B8G8R8].push_back(D3DFMT_A8B8G8R8);// !=
		possible[PF_A8B8G8R8].push_back(D3DFMT_A8R8G8B8);

		possible[PF_B8G8R8A8].push_back(D3DFMT_A8R8G8B8);//!=
		possible[PF_B8G8R8A8].push_back(D3DFMT_A8B8G8R8);

		possible[PF_R8G8B8A8].push_back(D3DFMT_A8B8G8R8);// !=
		possible[PF_R8G8B8A8].push_back(D3DFMT_A8R8G8B8);	

		possible[PF_A2R10G10B10].push_back(D3DFMT_A2R10G10B10);	
		possible[PF_A2B10G10R10].push_back(D3DFMT_A2B10G10R10);
		possible[PF_FLOAT16_R].push_back(D3DFMT_R16F);
		possible[PF_FLOAT16_RGB].push_back(D3DFMT_A16B16G16R16F);
		possible[PF_FLOAT16_RGBA].push_back(D3DFMT_A16B16G16R16F);
		possible[PF_FLOAT32_R].push_back(D3DFMT_R32F);
		possible[PF_FLOAT32_RGB].push_back(D3DFMT_A32B32G32R32F);
		possible[PF_FLOAT32_RGBA].push_back(D3DFMT_A32B32G32R32F);
		possible[PF_SHORT_RGBA].push_back(D3DFMT_A16B16G16R16);
		possible[PF_RGB_DXT1].push_back(D3DFMT_DXT1);
		possible[PF_DXT1].push_back(D3DFMT_DXT1);
		possible[PF_DXT2].push_back(D3DFMT_DXT2);
		possible[PF_DXT3].push_back(D3DFMT_DXT3);
		possible[PF_DXT4].push_back(D3DFMT_DXT4);
		possible[PF_DXT5].push_back(D3DFMT_DXT5);
		possible[PF_DEPTH].push_back(D3DFMT_D32);
		possible[PF_DEPTH].push_back(D3DFMT_D24FS8);

		IDirect3D9 * pd3d9 = m_pRenderSystem->getDirect3D9();
		D3D9Driver * pDriver = m_pRenderSystem->getD3D9Driver();
		D3DDISPLAYMODE devMod = pDriver->getCurrentDisplayMode();
		UINT	adapterOrdinal = pDriver->getAdapterOrdinal();

		PossibleSupportedFormatContainerIterator possibleit = possible.begin();
		for( ; possibleit != possible.end(); ++possibleit)
		{
			for( uint i=0; i< possibleit->second.size(); ++i)
			{
				if( S_OK == pd3d9->CheckDeviceFormat(
					adapterOrdinal, 
					m_createParams.DeviceType,
					devMod.Format,
					0,
					D3DRTYPE_TEXTURE,
					possibleit->second[i]) )
				{
					m_supportedTextureFormat[possibleit->first] = possibleit->second[i];
					break;
				}
			}
		}
	}
}
