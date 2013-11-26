#include "StdAfx.h"
#include "ShaderFragmentD3D9.h"
#include "RenderSystemD3D9.h"
#include "D3D9Device.h"


namespace xs
{

	ShaderFragmentD3D9::ShaderFragmentD3D9( const std::string & name)
		:ManagedItem(name)
		,m_pRenderSystem(0)
		,m_pShader(0)
	{
		
	}

	ShaderFragmentD3D9::~ShaderFragmentD3D9()
	{
	
	}

	bool ShaderFragmentD3D9::create(RenderSystemD3D9 * pRenderSystem, ShaderType st,const uchar *pBuffer,uint len)
	{
		if( NULL == pRenderSystem )
			return false;
		if( NULL == pBuffer)
			return false;
		if( len <= 0 )
			return false;

		m_type = st;
		m_pRenderSystem = pRenderSystem;
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();
		if( NULL == pD3DDevice)
			return false;
		xs::D3D9ResourceManager * pD3DResMgr = m_pRenderSystem->getD3D9ResourceMgr();
		if( NULL == pD3DResMgr)
			return false;

		//vertex shader
		if( m_type == ST_VERTEX_PROGRAM)
		{
			//compile shader
			ID3DXBuffer * pShaderBuf = 0;
			HRESULT hr = D3DXAssembleShader(
				(LPCSTR)pBuffer,
				(UINT)len,
				NULL,
				NULL,
				0,
				&pShaderBuf,
				NULL);	
			if( FAILED(hr) )
				return false;

			//create shader object
			pD3DResMgr->waitForEndFrame();//�ȴ�������Դ��֪ͨ
			pD3DResMgr->lockDeviceAccess();//�����豸
			hr = pD3DDevice->CreateVertexShader( 
				(const DWORD *)(pShaderBuf->GetBufferPointer()),
				(IDirect3DVertexShader9 **)(&m_pShader) );
			pD3DResMgr->unlockDeviceAccess();
			pShaderBuf->Release();

			if( FAILED(hr) )
			{
				return false;
			}
			else
			{
				pD3DResMgr->notifyResourceCreated(this);
				return true;			
			}		
		}
		else // pixel shader
		{
			//compile shader
			ID3DXBuffer * pShaderBuf = 0;
			HRESULT hr = D3DXAssembleShader(
				(LPCSTR)pBuffer,
				(UINT)len,
				NULL,
				NULL,
				0,
				&pShaderBuf,
				NULL);	
			if( FAILED(hr) )
				return false;

			//create shader object
			pD3DResMgr->waitForEndFrame();//�ȴ�������Դ��֪ͨ
			pD3DResMgr->lockDeviceAccess();//�����豸
			hr = pD3DDevice->CreatePixelShader( 
				(const DWORD *)(pShaderBuf->GetBufferPointer()),
				(IDirect3DPixelShader9 **)(&m_pShader) );
			pD3DResMgr->unlockDeviceAccess();
			pShaderBuf->Release();

			if( FAILED(hr) )
			{
				return false;
			}
			else
			{
				pD3DResMgr->notifyResourceCreated(this);
				return true;			
			}		
		}
	}

	void ShaderFragmentD3D9::release()		
	{
		if( m_pShader)
		{
			xs::D3D9ResourceManager * pD3DResMgr = m_pRenderSystem->getD3D9ResourceMgr();
			Assert( NULL != pD3DResMgr);
			switch( m_type)
			{
			case ST_VERTEX_PROGRAM:
				{
					pD3DResMgr->lockResourceAccess();
					((IDirect3DVertexShader9 *)m_pShader )->Release();
					m_pShader = 0;
					pD3DResMgr->unlockResourceAccess();
					pD3DResMgr->notifyResourceRelease(this);
				}
				break;
			case ST_FRAGMENT_PROGRAM:
				{
					pD3DResMgr->lockResourceAccess();
					((IDirect3DPixelShader9 *)m_pShader)->Release();
					m_pShader = 0;
					pD3DResMgr->unlockResourceAccess();
					pD3DResMgr->notifyResourceRelease(this);
				}
				break;
			default: // �����ᵽ����
				break;
			}
		}
		delete this;
	}

	/** �����ɫ�����Ͷ�����ɫ������������ɫ��
	@return ��ɫ������
	@see ShaderType
	*/
	ShaderType ShaderFragmentD3D9::getType()
	{
		return m_type;
	}

	/** ������ɫ��
	@return �Ƿ�ɹ�
	*/
	bool ShaderFragmentD3D9::compile()
	{
		return true;
	}

	/** �󶨵�����ɫ��
	@return �Ƿ�󶨳ɹ�
	*/
	bool ShaderFragmentD3D9::bind()
	{
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();
		if( NULL == pD3DDevice)
			return false;
		
		HRESULT hr;
		switch( m_type)
		{
		case ST_VERTEX_PROGRAM:
			hr = pD3DDevice->SetVertexShader( (IDirect3DVertexShader9 *)m_pShader);
			break;
		case ST_FRAGMENT_PROGRAM:
			hr = pD3DDevice->SetPixelShader( (IDirect3DPixelShader9 *)m_pShader);
			break;
		default:
			return false;
			break;		
		}

		return SUCCEEDED(hr);
	}

	/** ȡ���󶨴���ɫ������bind����ʹ��
	*/
	void ShaderFragmentD3D9::unbind()
	{
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();
		if( NULL == pD3DDevice)
			return;
		
		HRESULT hr;
		switch( m_type)
		{
		case ST_VERTEX_PROGRAM:
			hr = pD3DDevice->SetVertexShader( NULL);
			break;
		case ST_FRAGMENT_PROGRAM:
			hr = pD3DDevice->SetPixelShader( NULL);
			break;
		default:
			return;
			break;		
		}
		return;
	}

	/** ����ͳһ������ά����
	@param startRegister	��ʼ�ĸ��㳣���Ĵ������
	@param pData			��������ָ��
	@param countVector4		��ά���������ĸ���
	*/
	bool ShaderFragmentD3D9::setUniformFloatVector4(uint startRegister, float * pData, uint countVector4)
	{
		if( 0 == pData || 0 == countVector4 )
			return false;

		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();
		HRESULT hr;
		if( ST_VERTEX_PROGRAM == m_type )
			hr = pD3DDevice->SetVertexShaderConstantF( (UINT)startRegister, pData, countVector4);
		else
			hr = pD3DDevice->SetPixelShaderConstantF( (UINT)startRegister, pData, countVector4);

		return SUCCEEDED(hr);
	}

	/** ����ͳһ������ά����
	@param startRegister	��ʼ�����ͳ����Ĵ������
	@param pData			��������ָ��
	@param countVector4		��ά���������ĸ���
	*/
	bool ShaderFragmentD3D9::setUniformIntVector4(uint startRegister, int * pData, uint countVector4)
	{
		if( 0 == pData || 0 == countVector4 )
			return false;

		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();
		HRESULT hr;
		if( ST_VERTEX_PROGRAM == m_type )
			hr = pD3DDevice->SetVertexShaderConstantI( (UINT)startRegister, pData, countVector4);
		else
			hr = pD3DDevice->SetPixelShaderConstantI( (UINT)startRegister, pData, countVector4);

		return SUCCEEDED(hr);
	}

	/** ����ͳһ��������
	@param startRegister	��ʼ�Ĳ��������Ĵ������
	@param pData			��������ָ�룬0��ʾfalse����0��ʾtrue
	@param countBool		�������ݵĸ���
	*/
	bool ShaderFragmentD3D9::setUniformBool(uint startRegister, int * pData, uint countBool)
	{
		if( 0 == pData || 0 == countBool )
			return false;

		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();
		HRESULT hr;
		if( ST_VERTEX_PROGRAM == m_type )
			hr = pD3DDevice->SetVertexShaderConstantB( (UINT)startRegister, (const BOOL *)pData, countBool);
		else
			hr = pD3DDevice->SetPixelShaderConstantB( (UINT)startRegister, (const BOOL*)pData, countBool);
		return SUCCEEDED(hr);	
	}

	/** �����磬�������ͶӰ�Ⱦ���󶨵�shader�ĳ���,�ʺϵ�shader��ֻ��ͬʱ��һ������
	*/
	void ShaderFragmentD3D9::bindTransformMatrix(uint index, uint type, uint bindRow)
	{
		if( ST_VERTEX_PROGRAM != m_type) return;
		if( bindRow <= 0 || bindRow > 4) return;

		D3DXMATRIX mtx;
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();
		
		switch( type)
		{
		case TMT_WORLD:
			{
				m_pRenderSystem->getTransformMatrix( TMT_WORLD, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				pD3DDevice->SetVertexShaderConstantF(index, &mtx.m[0][0], bindRow);
				return;
			}
			break;
		case TMT_VIEW:
			{
				m_pRenderSystem->getTransformMatrix( TMT_VIEW, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				pD3DDevice->SetVertexShaderConstantF(index, &mtx.m[0][0], bindRow);
				return;		
			}
			break;
		case TMT_WORLD_VIEW:
			{
				m_pRenderSystem->getTransformMatrix( TMT_WORLD_VIEW, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				pD3DDevice->SetVertexShaderConstantF(index, &mtx.m[0][0], bindRow);
				return;			
			}
			break;
		case TMT_PROJECTION:
			{
				m_pRenderSystem->getTransformMatrix( TMT_PROJECTION, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				pD3DDevice->SetVertexShaderConstantF(index, &mtx.m[0][0], bindRow);
				return;
			}
			break;
		case TMT_VIEW_PROJECTION:
			{
				m_pRenderSystem->getTransformMatrix( TMT_VIEW_PROJECTION, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				pD3DDevice->SetVertexShaderConstantF(index, &mtx.m[0][0], bindRow);
				return;	
			}
			break;
		case TMT_WORLD_VIEW_PROJECTION:
			{
				m_pRenderSystem->getTransformMatrix( TMT_WORLD_VIEW_PROJECTION, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				pD3DDevice->SetVertexShaderConstantF(index, &mtx.m[0][0], bindRow);
				return;
			}
			break;
		case TMT_WORLD_NORMAL:
			{
				m_pRenderSystem->getTransformMatrix( TMT_WORLD_NORMAL, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				pD3DDevice->SetVertexShaderConstantF(index, &mtx.m[0][0], bindRow);
				return;	
			}
			break;
		case TMT_VIEW_NORMAL:
			{
				m_pRenderSystem->getTransformMatrix( TMT_VIEW_NORMAL, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				pD3DDevice->SetVertexShaderConstantF(index, &mtx.m[0][0], bindRow);
				return;	
			}
			break;
		case TMT_WORLD_VIEW_NORMAL:
			{
				m_pRenderSystem->getTransformMatrix( TMT_WORLD_VIEW_NORMAL, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				pD3DDevice->SetVertexShaderConstantF(index, &mtx.m[0][0], bindRow);
				return;		
			}
			break;
		default:
			break;
		}
		return;
	}
}
