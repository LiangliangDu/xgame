#include "StdAfx.h"
#include "StreamSourceMappings.h"
#include "RenderSystemD3D9.h"
#include "D3D9Device.h"
#include "VertexBufferD3D9.h"
#include "IndexBufferD3D9.h"

namespace xs
{

	StreamSourceMappings * StreamSourceMappingsCreater::create(RenderSystemD3D9 * pRenderSystem)
	{
		if( NULL == pRenderSystem)
			return 0;
		StreamSourceMappings * pSSM = new StreamSourceMappings();
		pSSM->m_pRenderSystem = pRenderSystem;
		return pSSM;
	}

	void StreamSourceMappings::release()
	{
		VertexDeclarationContainerIterator it = m_vDecls.begin();
		for( ; it != m_vDecls.end(); ++it)
		{
			COM_SAFE_RELEASE( (*it).second );
		}

		delete this;
	}


	StreamSourceMappings::StreamSourceMappings():
	m_pRenderSystem(0),
	m_uiNumVertices(0),
	m_dwStreamsFlag(0)
	{
		for( uint i=0; i< EVDT_TypeNum; ++i)
		{
			m_streamBindRecord[i].m_bValid = false;
		}
	}

	StreamSourceMappings::~StreamSourceMappings()
	{
	}


	IDirect3DVertexDeclaration9 * StreamSourceMappings::getVertexDeclaration()
	{
		if( 0 == m_dwStreamsFlag)
			return 0;

		VertexDeclarationContainerIterator it  = m_vDecls.find( m_dwStreamsFlag);
		if( it != m_vDecls.end() )
			return it->second;

		//�����µĶ�������
		uint elementNum = 0;
		for( uint i=0; i<EVDT_TypeNum; ++i)
		{
			if( m_streamBindRecord[i].m_bValid) 
				++elementNum;
		}
		D3DVERTEXELEMENT9 * pEles = new D3DVERTEXELEMENT9[elementNum + 1];
		uint index = 0;
		for( uint i=0; i < EVDT_TypeNum; ++i)
		{
			if( m_streamBindRecord[i].m_bValid)
			{
				pEles[index] = m_streamBindRecord[i].m_element;
				++index;
			}
		}
		pEles[elementNum].Stream = 0xFF;
		pEles[elementNum].Offset = 0;
		pEles[elementNum].Type = D3DDECLTYPE_UNUSED;
		pEles[elementNum].Method = 0;
		pEles[elementNum].Usage = 0;
		pEles[elementNum].UsageIndex = 0;

		IDirect3DVertexDeclaration9 * pDcl = 0;
		HRESULT hr = m_pRenderSystem->getD3D9Device()->getDevice()->CreateVertexDeclaration( pEles, &pDcl);
		delete [] pEles;
		pEles = 0;

		if( FAILED(hr) )
		{
			return 0;
		}
		else
		{
			m_vDecls[m_dwStreamsFlag] = pDcl;
			return pDcl;
		}

	}


	uint StreamSourceMappings::getVertexType2StreamIndex(VertexDeclarationType type)
	{
		switch(type)
		{
		case EVDT_Position:
			return 0;
			break;
		case EVDT_Normal:
			return 1;
			break;
		case EVDT_DiffuseColor:
			return 2;
			break;
		case EVDT_SpecularColor:
			return 3;
			break;
		case EVDT_Tex0:
			return 4;
			break;
		case EVDT_Tex1:
			return 5;
			break;
		case EVDT_Tex2:
			return 6;
			break;
		case EVDT_Tex3:
			return 7;
			break;
		case EVDT_Tex4:
			return 8;
			break;
		case EVDT_Tex5:
			return 9;
			break;
		case EVDT_Tex6:
			return 10;
			break;
		case EVDT_Tex7:
			return 11;
			break;
		case EVDT_BlendWeight:
			return 12;
			break;
		case EVDT_BlendIndices:
			return 13;
			break;
		case EVDT_TypeNum:
		default:
			//������
			return 255;
			break;
		}		
	}

	/** ��ȡ�ж��ٸ�����
	*/
	UINT StreamSourceMappings::getNumVertices()
	{ 
		return m_uiNumVertices; 
	}

	void	StreamSourceMappings::setVertexVertexBuffer(IVertexBuffer* vertexBuffer,uint start)
	{
		D3D9Device * pDevice = m_pRenderSystem->getD3D9Device();
		IDirect3DDevice9 * pD3D9Device = pDevice->getDevice();
		uint streamIndex = getVertexType2StreamIndex(EVDT_Position);
		VertexBufferD3D9 * pD3DVB = static_cast<VertexBufferD3D9 *>(vertexBuffer);

		if( NULL == vertexBuffer || NULL == pD3DVB ||  NULL == pD3DVB->getD3DVertexBuffer9() )
		{
			//ȡ����־
			m_dwStreamsFlag &= ~EVDT_Position;
			//��Ч������
			m_streamBindRecord[ streamIndex ].m_bValid = false;
			//ȡ������������
			pD3D9Device->SetStreamSource( streamIndex, 0,0,0);	
		}
		else
		{
			IDirect3DVertexBuffer9 * pRealVB = pD3DVB->getD3DVertexBuffer9();
			//���ö��������
			m_uiNumVertices = vertexBuffer->getNumVertices();
			//���ñ�־
			m_dwStreamsFlag |= EVDT_Position;
			//��������
			m_streamBindRecord[ streamIndex ].m_bValid = true;
			m_streamBindRecord[ streamIndex ].m_element.Stream = streamIndex;
			m_streamBindRecord[ streamIndex ].m_element.Offset = 0;
			m_streamBindRecord[ streamIndex ].m_element.Type = D3DDECLTYPE_FLOAT3;
			m_streamBindRecord[ streamIndex ].m_element.Method = D3DDECLMETHOD_DEFAULT;
			m_streamBindRecord[ streamIndex ].m_element.Usage = D3DDECLUSAGE_POSITION;
			m_streamBindRecord[ streamIndex ].m_element.UsageIndex = 0;
			//��������������
			pD3D9Device->SetStreamSource( streamIndex, pRealVB,start, vertexBuffer->getVertexSize());	
			
		}
	}

	void	StreamSourceMappings::setDiffuseVertexBuffer(IVertexBuffer* vertexBuffer,uint start)
	{
		D3D9Device * pDevice = m_pRenderSystem->getD3D9Device();
		IDirect3DDevice9 * pD3D9Device = pDevice->getDevice();
		uint streamIndex = getVertexType2StreamIndex(EVDT_DiffuseColor);
		VertexBufferD3D9 * pD3DVB = static_cast<VertexBufferD3D9 *>(vertexBuffer);

		if( NULL == vertexBuffer || NULL == pD3DVB ||  NULL == pD3DVB->getD3DVertexBuffer9() )
		{
			//ȡ����־
			m_dwStreamsFlag &= ~EVDT_DiffuseColor;
			//��Ч������
			m_streamBindRecord[ streamIndex ].m_bValid = false;
			//ȡ������������
			pD3D9Device->SetStreamSource( streamIndex, 0,0,0);	
		}
		else
		{
			IDirect3DVertexBuffer9 * pRealVB = pD3DVB->getD3DVertexBuffer9();
			//���ö��������
			m_uiNumVertices = vertexBuffer->getNumVertices();
			//���ñ�־
			m_dwStreamsFlag |= EVDT_DiffuseColor;
			//��������
			m_streamBindRecord[ streamIndex ].m_bValid = true;
			m_streamBindRecord[ streamIndex ].m_element.Stream = streamIndex;
			m_streamBindRecord[ streamIndex ].m_element.Offset = 0;
			m_streamBindRecord[ streamIndex ].m_element.Type = D3DDECLTYPE_D3DCOLOR;
			m_streamBindRecord[ streamIndex ].m_element.Method = D3DDECLMETHOD_DEFAULT;
			m_streamBindRecord[ streamIndex ].m_element.Usage = D3DDECLUSAGE_COLOR;
			m_streamBindRecord[ streamIndex ].m_element.UsageIndex = 0;
			//��������������
			pD3D9Device->SetStreamSource( streamIndex, pRealVB,start, vertexBuffer->getVertexSize() );	
		}
	}

	void	 StreamSourceMappings::setBlendWeightVertexBuffer(IVertexBuffer* vertexBuffer, uint start)
	{
		D3D9Device * pDevice = m_pRenderSystem->getD3D9Device();
		IDirect3DDevice9 * pD3D9Device = pDevice->getDevice();
		uint streamIndex = getVertexType2StreamIndex(EVDT_BlendWeight);
		VertexBufferD3D9 * pD3DVB = static_cast<VertexBufferD3D9 *>(vertexBuffer);

		if( NULL == vertexBuffer || NULL == pD3DVB ||  NULL == pD3DVB->getD3DVertexBuffer9() )
		{
			//ȡ����־
			m_dwStreamsFlag &= ~EVDT_BlendWeight;
			//��Ч������
			m_streamBindRecord[ streamIndex ].m_bValid = false;
			//ȡ������������
			pD3D9Device->SetStreamSource( streamIndex, 0,0,0);	
		}
		else
		{
			IDirect3DVertexBuffer9 * pRealVB = pD3DVB->getD3DVertexBuffer9();
			//���ö��������
			m_uiNumVertices = vertexBuffer->getNumVertices();
			//���ñ�־
			m_dwStreamsFlag |= EVDT_BlendWeight;
			//��������
			m_streamBindRecord[ streamIndex ].m_bValid = true;
			m_streamBindRecord[ streamIndex ].m_element.Stream = streamIndex;
			m_streamBindRecord[ streamIndex ].m_element.Offset = 0;
			m_streamBindRecord[ streamIndex ].m_element.Type = D3DDECLTYPE_FLOAT3;
			m_streamBindRecord[ streamIndex ].m_element.Method = D3DDECLMETHOD_DEFAULT;
			m_streamBindRecord[ streamIndex ].m_element.Usage = D3DDECLUSAGE_BLENDWEIGHT;
			m_streamBindRecord[ streamIndex ].m_element.UsageIndex = 0;
			//��������������
			pD3D9Device->SetStreamSource( streamIndex, pRealVB,start, vertexBuffer->getVertexSize() );	
		}
	}

	void	 StreamSourceMappings::setBlendIndicesVertexBuffer(IVertexBuffer* vertexBuffer, uint start)
	{
		D3D9Device * pDevice = m_pRenderSystem->getD3D9Device();
		IDirect3DDevice9 * pD3D9Device = pDevice->getDevice();
		uint streamIndex = getVertexType2StreamIndex(EVDT_BlendIndices);
		VertexBufferD3D9 * pD3DVB = static_cast<VertexBufferD3D9 *>(vertexBuffer);

		if( NULL == vertexBuffer || NULL == pD3DVB ||  NULL == pD3DVB->getD3DVertexBuffer9() )
		{
			//ȡ����־
			m_dwStreamsFlag &= ~EVDT_BlendIndices;
			//��Ч������
			m_streamBindRecord[ streamIndex ].m_bValid = false;
			//ȡ������������
			pD3D9Device->SetStreamSource( streamIndex, 0,0,0);	
		}
		else
		{
			IDirect3DVertexBuffer9 * pRealVB = pD3DVB->getD3DVertexBuffer9();
			//���ö��������
			m_uiNumVertices = vertexBuffer->getNumVertices();
			//���ñ�־
			m_dwStreamsFlag |= EVDT_BlendIndices;
			//��������
			m_streamBindRecord[ streamIndex ].m_bValid = true;
			m_streamBindRecord[ streamIndex ].m_element.Stream = streamIndex;
			m_streamBindRecord[ streamIndex ].m_element.Offset = 0;
			m_streamBindRecord[ streamIndex ].m_element.Type = D3DDECLTYPE_D3DCOLOR /*D3DDECLTYPE_UBYTE4*/;//�ϵ��Կ���֧��D3DDECLTYPE_UBYTE4��������
			m_streamBindRecord[ streamIndex ].m_element.Method = D3DDECLMETHOD_DEFAULT;
			m_streamBindRecord[ streamIndex ].m_element.Usage = D3DDECLUSAGE_BLENDINDICES;
			m_streamBindRecord[ streamIndex ].m_element.UsageIndex = 0;
			//��������������
			pD3D9Device->SetStreamSource( streamIndex, pRealVB,start, vertexBuffer->getVertexSize() );	
		}
	}

	void	StreamSourceMappings::setSpecularVertexBuffer(IVertexBuffer* vertexBuffer,uint start)
	{
		D3D9Device * pDevice = m_pRenderSystem->getD3D9Device();
		IDirect3DDevice9 * pD3D9Device = pDevice->getDevice();
		uint streamIndex = getVertexType2StreamIndex(EVDT_SpecularColor);
		VertexBufferD3D9 * pD3DVB = static_cast<VertexBufferD3D9 *>(vertexBuffer);

		if( NULL == vertexBuffer || NULL == pD3DVB ||  NULL == pD3DVB->getD3DVertexBuffer9() )
		{
			//ȡ����־
			m_dwStreamsFlag &= ~EVDT_SpecularColor;
			//��Ч������
			m_streamBindRecord[ streamIndex ].m_bValid = false;
			//ȡ������������
			pD3D9Device->SetStreamSource( streamIndex, 0,0,0);	
		}
		else
		{
			IDirect3DVertexBuffer9 * pRealVB = pD3DVB->getD3DVertexBuffer9();
			//���ö��������
			m_uiNumVertices = vertexBuffer->getNumVertices();
			//���ñ�־
			m_dwStreamsFlag |= EVDT_SpecularColor;
			//��������
			m_streamBindRecord[ streamIndex ].m_bValid = true;
			m_streamBindRecord[ streamIndex ].m_element.Stream = streamIndex;
			m_streamBindRecord[ streamIndex ].m_element.Offset = 0;
			m_streamBindRecord[ streamIndex ].m_element.Type = D3DDECLTYPE_D3DCOLOR;
			m_streamBindRecord[ streamIndex ].m_element.Method = D3DDECLMETHOD_DEFAULT;
			m_streamBindRecord[ streamIndex ].m_element.Usage = D3DDECLUSAGE_COLOR;
			m_streamBindRecord[ streamIndex ].m_element.UsageIndex = 1;
			//��������������
			pD3D9Device->SetStreamSource( streamIndex, pRealVB,start, vertexBuffer->getVertexSize() );	
			
		}
	}

	void	StreamSourceMappings::setNormalVertexBuffer(IVertexBuffer* vertexBuffer,uint start)
	{
		D3D9Device * pDevice = m_pRenderSystem->getD3D9Device();
		IDirect3DDevice9 * pD3D9Device = pDevice->getDevice();
		uint streamIndex = getVertexType2StreamIndex(EVDT_Normal);
		VertexBufferD3D9 * pD3DVB = static_cast<VertexBufferD3D9 *>(vertexBuffer);

		if( NULL == vertexBuffer || NULL == pD3DVB ||  NULL == pD3DVB->getD3DVertexBuffer9() )
		{
			//ȡ����־
			m_dwStreamsFlag &= ~EVDT_Normal;
			//��Ч������
			m_streamBindRecord[ streamIndex ].m_bValid = false;
			//ȡ������������
			pD3D9Device->SetStreamSource( streamIndex, 0,0,0);	
		}
		else
		{
			IDirect3DVertexBuffer9 * pRealVB = pD3DVB->getD3DVertexBuffer9();
			//���ö��������
			m_uiNumVertices = vertexBuffer->getNumVertices();
			//���ñ�־
			m_dwStreamsFlag |= EVDT_Normal;
			//��������
			m_streamBindRecord[ streamIndex ].m_bValid = true;
			m_streamBindRecord[ streamIndex ].m_element.Stream = streamIndex;
			m_streamBindRecord[ streamIndex ].m_element.Offset = 0;
			m_streamBindRecord[ streamIndex ].m_element.Type = D3DDECLTYPE_FLOAT3;
			m_streamBindRecord[ streamIndex ].m_element.Method = D3DDECLMETHOD_DEFAULT;
			m_streamBindRecord[ streamIndex ].m_element.Usage = D3DDECLUSAGE_NORMAL;
			m_streamBindRecord[ streamIndex ].m_element.UsageIndex = 0;
			//��������������
			pD3D9Device->SetStreamSource( streamIndex, pRealVB,start, vertexBuffer->getVertexSize() );			
		}
	}

	void	StreamSourceMappings::setTexcoordVertexBuffer(ushort unit,IVertexBuffer* vertexBuffer,uint start)
	{
		if( unit >= 8)
			return;

		VertexDeclarationType vertexType;
		switch(unit)
		{
		case 0:
			vertexType = EVDT_Tex0;
			break;
		case 1:
			vertexType = EVDT_Tex1;
			break;
		case 2:
			vertexType = EVDT_Tex2;
			break;
		case 3:
			vertexType = EVDT_Tex3;
			break;
		case 4:
			vertexType = EVDT_Tex4;
			break;
		case 5:
			vertexType = EVDT_Tex5;
			break;
		case 6:
			vertexType = EVDT_Tex6;
			break;
		case 7:
			vertexType = EVDT_Tex7;
			break;
		default:
			//������
			break;
		}

		uint streamIndex = getVertexType2StreamIndex(vertexType);
		if( streamIndex >= EVDT_TypeNum)
			return;

		D3D9Device * pDevice = m_pRenderSystem->getD3D9Device();
		IDirect3DDevice9 * pD3D9Device = pDevice->getDevice();
		
		VertexBufferD3D9 * pD3DVB = static_cast<VertexBufferD3D9 *>(vertexBuffer);

		if( NULL == vertexBuffer || NULL == pD3DVB ||  NULL == pD3DVB->getD3DVertexBuffer9() )
		{
			//ȡ����־
			m_dwStreamsFlag &= ~vertexType;
			//��Ч������
			m_streamBindRecord[ streamIndex ].m_bValid = false;
			//ȡ������������
			pD3D9Device->SetStreamSource( streamIndex, 0,0,0);	
		}
		else
		{
			IDirect3DVertexBuffer9 * pRealVB = pD3DVB->getD3DVertexBuffer9();
			//���ö��������
			m_uiNumVertices = vertexBuffer->getNumVertices();
			//���ñ�־
			m_dwStreamsFlag |= vertexType;
			//��������
			m_streamBindRecord[ streamIndex ].m_bValid = true;
			m_streamBindRecord[ streamIndex ].m_element.Stream = streamIndex;
			m_streamBindRecord[ streamIndex ].m_element.Offset = 0;
			m_streamBindRecord[ streamIndex ].m_element.Type = D3DDECLTYPE_FLOAT2;
			m_streamBindRecord[ streamIndex ].m_element.Method = D3DDECLMETHOD_DEFAULT;
			m_streamBindRecord[ streamIndex ].m_element.Usage = D3DDECLUSAGE_TEXCOORD;
			m_streamBindRecord[ streamIndex ].m_element.UsageIndex = unit;
			//��������������
			pD3D9Device->SetStreamSource( streamIndex, pRealVB,start, vertexBuffer->getVertexSize());			
		}
	}

	void StreamSourceMappings::setIndexBuffer(IIndexBuffer* indexBuffer)
	{
		D3D9Device * pDevice = m_pRenderSystem->getD3D9Device();
		IDirect3DDevice9 * pD3D9Device = pDevice->getDevice();
		IndexBufferD3D9 * pD3DIB = static_cast<IndexBufferD3D9 *>(indexBuffer);

		if( NULL == indexBuffer || NULL == pD3DIB ||  NULL == pD3DIB->getD3DIndexBuffer9() )
		{
			//ȡ����������
			pD3D9Device->SetIndices( 0 );
		}
		else
		{
			//������������
			pD3D9Device->SetIndices( pD3DIB->getD3DIndexBuffer9() );		
		}
	}

}