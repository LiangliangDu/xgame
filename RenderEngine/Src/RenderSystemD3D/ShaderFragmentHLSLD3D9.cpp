#include "StdAfx.h"
#include "ShaderFragmentHLSLD3D9.h"
#include "RenderSystemD3D9.h"
#include "D3D9Device.h"
#include "MappingsD3D9.h"

namespace xs
{
	ShaderFragmentHLSLD3D9::ShaderFragmentHLSLD3D9( const std::string & name)
		:ManagedItem(name)
		,m_pRenderSystem(0)
		,m_pShader(0)
		,m_pConstantTable(0)
	{
		
	}

	ShaderFragmentHLSLD3D9::~ShaderFragmentHLSLD3D9()
	{
	
	}

	bool ShaderFragmentHLSLD3D9::create(RenderSystemD3D9 * pRenderSystem, ShaderType st,const uchar *pBuffer,uint len)
	{
		//��֤
		if( NULL == pRenderSystem )
			return false;
		if( NULL == pBuffer)
			return false;
		if( len <= 0 )
			return false;

		m_type = st;
		m_pRenderSystem = pRenderSystem;
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();
		if( NULL == pD3DDevice) return false;
		xs::D3D9ResourceManager * pD3DResMgr = m_pRenderSystem->getD3D9ResourceMgr();
		if( NULL == pD3DResMgr) return false;

		//shader profile
		//shader mode 3 ��Ҫvertex shader �� pixel shaderһ��ʹ�ã�������Ҫ�ֿ�ʹ�ã����Բ���shader mode 3
		const char * pVertexShaderProfile[3] =
		{
			"vs_2_a",
			"vs_2_0",
			"vs_1_1",
		};
		const char * pPixelShaderProfile[3] = 
		{
			"ps_2_b",
			"ps_2_a",
			"ps_2_0",
		};	

		//vertex shader
		if( m_type == ST_VERTEX_PROGRAM)
		{
			//����shader	
			bool bCompileSucceed = false;
			HRESULT hr;
			ID3DXBuffer * pShaderBuf = 0;
			//ID3DXBuffer* pErrorString = 0;
			for( uint i =0; i < 3; ++i)
			{	
				hr  = D3DXCompileShader( 
					(LPCSTR)pBuffer,
					(UINT)len,
					NULL,
					NULL,
					"main",
					pVertexShaderProfile[i],
					0,
					&pShaderBuf,
					/*&pErrorString*/ NULL,
					&m_pConstantTable);
				//if( FAILED(hr) )
				//{
				//	const char * pError = (char *)pErrorString->GetBufferPointer();
				//	int __i = 0;
				//}
				bCompileSucceed = SUCCEEDED( hr);
				if( bCompileSucceed ) break;
			}
			if( !bCompileSucceed)
				return false;

			//����shader object
			pD3DResMgr->waitForEndFrame();//�ȴ�������Դ��֪ͨ
			pD3DResMgr->lockDeviceAccess();//�����豸
			hr = pD3DDevice->CreateVertexShader( 
				(const DWORD *)(pShaderBuf->GetBufferPointer()),
				(IDirect3DVertexShader9 **)(&m_pShader) );	
			pD3DResMgr->unlockDeviceAccess();
			pShaderBuf->Release();
			if( FAILED( hr) ) 
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
			//����shader	
			bool bCompileSucceed = false;
			HRESULT hr;
			ID3DXBuffer * pShaderBuf = 0;
			for( uint i =0; i < 3; ++i)
			{	
				hr  = D3DXCompileShader( 
					(LPCSTR)pBuffer,
					(UINT)len,
					NULL,
					NULL,
					"main",
					pPixelShaderProfile[i],
					0,
					&pShaderBuf,
					NULL,
					&m_pConstantTable);
				bCompileSucceed = SUCCEEDED( hr);
				if( bCompileSucceed ) break;
			}
			if( !bCompileSucceed)
				return false;

			//����shader object
			pD3DResMgr->waitForEndFrame();//�ȴ�������Դ��֪ͨ
			pD3DResMgr->lockDeviceAccess();//�����豸
			hr = pD3DDevice->CreatePixelShader( 
				(const DWORD *)(pShaderBuf->GetBufferPointer()),
				(IDirect3DPixelShader9 **)(&m_pShader) );	
			pD3DResMgr->unlockDeviceAccess();
			pShaderBuf->Release();
			if( FAILED( hr) ) 
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

	void ShaderFragmentHLSLD3D9::release()		
	{
		xs::D3D9ResourceManager * pD3DResMgr = m_pRenderSystem->getD3D9ResourceMgr();
		Assert( NULL != pD3DResMgr);
		if( m_pShader)
		{
			switch( m_type)
			{
			case ST_VERTEX_PROGRAM:
				{
					pD3DResMgr->lockResourceAccess();
					((IDirect3DVertexShader9 *)m_pShader )->Release();
					m_pShader = 0;
					COM_SAFE_RELEASE( m_pConstantTable);
					pD3DResMgr->unlockResourceAccess();
					pD3DResMgr->notifyResourceRelease(this);
				}
				break;
			case ST_FRAGMENT_PROGRAM:
				{
					pD3DResMgr->lockResourceAccess();
					((IDirect3DPixelShader9 *)m_pShader)->Release();
					m_pShader = 0;
					COM_SAFE_RELEASE( m_pConstantTable);
					pD3DResMgr->unlockResourceAccess();
					pD3DResMgr->notifyResourceRelease(this);
				}
				break;
			default: //�����ᵽ������
				break;
			}
		}	

		delete this;
	}

	/** �����ɫ�����Ͷ�����ɫ������������ɫ��
	@return ��ɫ������
	@see ShaderType
	*/
	ShaderType ShaderFragmentHLSLD3D9::getType()
	{
		return m_type;
	}

	/** ������ɫ��
	@return �Ƿ�ɹ�
	*/
	bool ShaderFragmentHLSLD3D9::compile()
	{
		return true;
	}

	/** �󶨵�����ɫ��
	@return �Ƿ�󶨳ɹ�
	*/
	bool ShaderFragmentHLSLD3D9::bind()
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

		m_pConstantTable->SetDefaults( pD3DDevice);

		return SUCCEEDED(hr);
	}

	/** ȡ���󶨴���ɫ������bind����ʹ��
	*/
	void ShaderFragmentHLSLD3D9::unbind()
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



	/** ����ͳһ�����ͱ���
	@param	strPara ������
	@param	value   ����ֵ
	@return	�Ƿ����óɹ�
	*/
	bool ShaderFragmentHLSLD3D9::setUniformBool(const std::string & strPara,  int value)
	{
		if( NULL == m_pConstantTable) return false;
		D3DXHANDLE h = m_pConstantTable->GetConstantByName(NULL, strPara.c_str() );
		if( NULL == h) return false;
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();

		HRESULT hr = m_pConstantTable->SetBool(pD3DDevice, h, (BOOL)value);
		return SUCCEEDED(hr);
	}

	/** ����ͳһ���ͱ���
	@param	strPara ������
	@param	value	����ֵ
	@return	�Ƿ����óɹ�
	*/
	bool ShaderFragmentHLSLD3D9::setUniformInt(const std::string & strPara, int value)
	{
		if( NULL == m_pConstantTable) return false;
		D3DXHANDLE h = m_pConstantTable->GetConstantByName(NULL, strPara.c_str() );
		if( NULL == h) return false;
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();

		HRESULT hr = m_pConstantTable->SetInt(pD3DDevice, h, (INT)value);
		return SUCCEEDED(hr);
	}

	/** ����ͳ�����ͱ���
	@param	strPara ������
	@param	value	����ֵ
	@return	�Ƿ����óɹ�
	*/
	bool ShaderFragmentHLSLD3D9::setUniformFloat(const std::string & strPara, float value)
	{
		if( NULL == m_pConstantTable) return false;
		D3DXHANDLE h = m_pConstantTable->GetConstantByName(NULL, strPara.c_str() );
		if( NULL == h) return false;
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();

		HRESULT hr = m_pConstantTable->SetFloat(pD3DDevice, h, (FLOAT)value);
		return SUCCEEDED(hr);	
	}

	/** ����ͳһ��������
	@param	strPara ������
	@param	value	����ֵ
	@return	�Ƿ����óɹ�
	*/
	bool ShaderFragmentHLSLD3D9::setUniformVector4(const std::string & strPara, const Vector4 & value)
	{
		if( NULL == m_pConstantTable) return false;
		D3DXHANDLE h = m_pConstantTable->GetConstantByName(NULL, strPara.c_str() );
		if( NULL == h) return false;
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();

		HRESULT hr = m_pConstantTable->SetVector(pD3DDevice, h, (CONST D3DXVECTOR4 *)value.val);
		return SUCCEEDED(hr);
	}

	/** ����һ��ľ���
	@param	strPara ������
	@param	value	����ֵ����������ݣ����������
	@return			�Ƿ����óɹ�
	*/
	bool ShaderFragmentHLSLD3D9::setUniformMatrix(const std::string & strPara, const Matrix4 &  value)
	{
		if( NULL == m_pConstantTable) return false;
		D3DXHANDLE h = m_pConstantTable->GetConstantByName(NULL, strPara.c_str() );
		if( NULL == h) return false;
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();

		D3DXMATRIX  d3dmtx;
		MappingsD3D9::getMatrix( value, d3dmtx);
		D3DXMatrixTranspose( &d3dmtx, &d3dmtx);//������ı��������Ч�ʸ�
		HRESULT hr = m_pConstantTable->SetMatrixTranspose(pD3DDevice, h, &d3dmtx);
		return SUCCEEDED(hr);
	}


	/** ����ͳһ����������
	@param	strPara ������
	@param	count	�����С
	@param	pValue  �����ַ
	@return	�Ƿ����óɹ�
	*/
	bool ShaderFragmentHLSLD3D9::setUniformBoolArray(const std::string & strPara, uint count,  int * pValue)
	{
		if( NULL == m_pConstantTable) return false;
		D3DXHANDLE h = m_pConstantTable->GetConstantByName(NULL, strPara.c_str() );
		if( NULL == h) return false;
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();

		HRESULT hr = m_pConstantTable->SetBoolArray(pD3DDevice, h, (CONST BOOL *)pValue, (UINT)count );
		return SUCCEEDED(hr);
		
	}

	/** ����ͳһ��������
	@param	strPara ������
	@param	count	�����С
	@param	pValue  �����ַ
	@return	�Ƿ����óɹ�
	*/
	bool ShaderFragmentHLSLD3D9::setUniformIntArray(const std::string & strPara, uint count,  int * pValue)
	{
		if( NULL == m_pConstantTable) return false;
		D3DXHANDLE h = m_pConstantTable->GetConstantByName(NULL, strPara.c_str() );
		if( NULL == h) return false;
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();

		HRESULT hr = m_pConstantTable->SetIntArray(pD3DDevice, h, (CONST INT *)pValue, (UINT)count );
		return SUCCEEDED(hr);	
	}

	/** ����ͳһ����������
	@param	strPara ������
	@param	count	�����С
	@param	pValue  �����ַ
	@return	�Ƿ����óɹ�
	*/
	bool ShaderFragmentHLSLD3D9::setUniformFloatArray(const std::string & strPara, uint count,  float * pValue)
	{
		if( NULL == m_pConstantTable) return false;
		D3DXHANDLE h = m_pConstantTable->GetConstantByName(NULL, strPara.c_str() );
		if( NULL == h) return false;
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();

		HRESULT hr = m_pConstantTable->SetFloatArray(pD3DDevice, h, (CONST FLOAT *)pValue, (UINT)count );
		return SUCCEEDED(hr);
	}

	/** ����ͳһ����������
	@param	strPara ������
	@param	count	�����С
	@param	pValue  �����ַ
	@return	�Ƿ����óɹ�
	*/
	bool ShaderFragmentHLSLD3D9::setUniformVector4Array(const std::string & strPara, uint count,  xs::Vector4 * pValue)
	{
		if( NULL == m_pConstantTable) return false;
		D3DXHANDLE h = m_pConstantTable->GetConstantByName(NULL, strPara.c_str() );
		if( NULL == h) return false;
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();

		HRESULT hr = m_pConstantTable->SetVectorArray(pD3DDevice, h, (CONST D3DXVECTOR4 *)pValue, (UINT)count );
		return SUCCEEDED(hr);
	}

	/** ����ͳһ����������
	@param	strPara ������
	@param	count	�����С
	@param	pValue  �����ַ
	@return	�Ƿ����óɹ�
	*/
	bool ShaderFragmentHLSLD3D9::setUniformMatrixArray(const std::string & strPara, uint count,  xs::Matrix4 * pValue)
	{
		if( 0 == m_pConstantTable) return false;
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();
		D3DXHANDLE h = m_pConstantTable->GetConstantByName(NULL, strPara.c_str() );
		if( 0 == h) return false;
		HRESULT hr = m_pConstantTable->SetMatrixTransposeArray(pD3DDevice,h, (CONST D3DXMATRIX *)pValue, count);
		return SUCCEEDED(hr);
	}

	/** �����磬�������ͶӰ����󶨵�shader�ĳ���
	*/
	void ShaderFragmentHLSLD3D9::bindTransformMatrix( uint flag )
	{
		//ֻ��vertex shader ��Ч
		//WORLD_MATRIX
		//VIEW_MATRIX
		//WORLD_VIEW_MATRIX
		//PROJECTION_MATRIX
		//VIEW_PROJECTION_MATRIX
		//WORLD_VIEW_PROJECTION_MATRIX
		//"WORLD_NORMAL_MATRIX":transform normal from object  to world space
		//"VIEW_NORMAL_MATRIX":transform normal from  world space to view space
		//"WORLD_VIEW_NORMAL_MATRIX":transform normal from object space to view space

		if(ST_VERTEX_PROGRAM != m_type) return;
		if( NULL == m_pConstantTable ) return;

		D3DXMATRIX mtx;
		D3DXHANDLE handle;
		IDirect3DDevice9 * pD3DDevice = m_pRenderSystem->getD3D9Device()->getDevice();

		////test begin
		//D3DXMATRIX test;
		//m_pRenderSystem->getTransformMatrix(TMT_VIEW_NORMAL,test);
		//D3DXVECTOR3 v3;
		//v3.x = 1; v3.y = 1; v3.z = 1;
		//D3DXVec3TransformNormal( &v3, &v3, &test);
		//D3DXVec3Normalize(&v3,&v3);
		//int __i = 0;
		////test end
		
		if( flag & TMT_WORLD )
		{
			//world matrix
			handle = m_pConstantTable->GetConstantByName(NULL, "WORLD_MATRIX");
			if( NULL != handle )
			{
				m_pRenderSystem->getTransformMatrix(TMT_WORLD, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				m_pConstantTable->SetMatrixTranspose( pD3DDevice, handle, &mtx);
			}
		}

		if( flag & TMT_VIEW)
		{
			//view matrix 
			handle = m_pConstantTable->GetConstantByName(NULL, "VIEW_MATRIX");
			if( NULL != handle )
			{
				m_pRenderSystem->getTransformMatrix(TMT_VIEW, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				m_pConstantTable->SetMatrixTranspose( pD3DDevice, handle, &mtx);
			}
		}

		if( flag & TMT_WORLD_VIEW)
		{
			//world view matrix
			handle = m_pConstantTable->GetConstantByName(NULL, "WORLD_VIEW_MATRIX");
			if( NULL != handle )
			{
				m_pRenderSystem->getTransformMatrix(TMT_WORLD_VIEW, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				m_pConstantTable->SetMatrixTranspose( pD3DDevice, handle, &mtx);
			}
		}

		if( flag & TMT_PROJECTION)
		{
			//projection matrix
			handle = m_pConstantTable->GetConstantByName(NULL, "PROJECTION_MATRIX");
			if( NULL != handle )
			{
				m_pRenderSystem->getTransformMatrix(TMT_PROJECTION, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				m_pConstantTable->SetMatrixTranspose( pD3DDevice, handle, &mtx);
			}
		}

		if( flag & TMT_VIEW_PROJECTION)
		{
			//view projection matrix
			handle = m_pConstantTable->GetConstantByName(NULL, "VIEW_PROJECTION_MATRIX");
			if( NULL != handle )
			{
				m_pRenderSystem->getTransformMatrix(TMT_VIEW_PROJECTION, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				m_pConstantTable->SetMatrixTranspose( pD3DDevice, handle, &mtx);
			}
		}

		if( flag & TMT_WORLD_VIEW_PROJECTION)
		{
			//world view projection matrix
			handle = m_pConstantTable->GetConstantByName(NULL, "WORLD_VIEW_PROJECTION_MATRIX");
			if( NULL != handle )
			{
				m_pRenderSystem->getTransformMatrix(TMT_WORLD_VIEW_PROJECTION, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				m_pConstantTable->SetMatrixTranspose( pD3DDevice, handle, &mtx);
			}
		}

		if( flag & TMT_WORLD_NORMAL)
		{
			//transform normal from object space to world space
			handle = m_pConstantTable->GetConstantByName(NULL, "WORLD_NORMAL_MATRIX");
			if( NULL != handle )
			{
				m_pRenderSystem->getTransformMatrix(TMT_WORLD_NORMAL, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				m_pConstantTable->SetMatrixTranspose( pD3DDevice, handle, &mtx);
			}	
		}

		if( flag & TMT_VIEW_NORMAL)
		{
			//transform normal from world space to view space
			handle = m_pConstantTable->GetConstantByName(NULL, "VIEW_NORMAL_MATRIX");
			if( NULL != handle )
			{
				m_pRenderSystem->getTransformMatrix(TMT_VIEW_NORMAL, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				m_pConstantTable->SetMatrixTranspose( pD3DDevice, handle, &mtx);
			}	
		}

		if( flag & TMT_WORLD_VIEW_NORMAL)
		{
			//transform normal from world space to view space
			handle = m_pConstantTable->GetConstantByName(NULL, "WORLD_VIEW_NORMAL_MATRIX");
			if( NULL != handle )
			{
				m_pRenderSystem->getTransformMatrix(TMT_WORLD_VIEW_NORMAL, mtx);
				D3DXMatrixTranspose(&mtx, &mtx);
				m_pConstantTable->SetMatrixTranspose( pD3DDevice, handle, &mtx);
			}	
		}

	}
}
