#include "StdAfx.h"
#include "VertexBufferD3D9.h"
#include "BufferManagerD3D9.h"
#include "D3D9Device.h"
#include "RenderSystemD3D9.h"
#include "MappingsD3D9.h"
#include "D3D9ResourceManager.h"

namespace xs
{


	VertexBufferD3D9 * VertexBufferD3D9Creater::create(BufferManagerD3D9 * pBufferMgr, uint vertexSize, uint numVertices, BufferUsage usage, CreateBufferFlag flag)
	{
		VertexBufferD3D9 * pVB = new VertexBufferD3D9();
		if( NULL == pVB)
			return 0;
		
		if( !pVB->create(pBufferMgr, vertexSize, numVertices,usage, flag) )
		{
			pVB->release();
			return 0;
		}

		return pVB;
	}

	VertexBufferD3D9::VertexBufferD3D9():
	m_pVB(0),
	m_uiVertexSize(0),
	m_uiNumVertices(0),
	m_uiSizeInBytes(0),
	m_eUsage(BU_STATIC),
	m_pBufferMgr(0),
	m_bIsLocked(false)
	{
		ZeroMemory(&m_bufferDesc, sizeof(m_bufferDesc));
	}

	VertexBufferD3D9::~VertexBufferD3D9()
	{
		
	}

	bool VertexBufferD3D9::create(BufferManagerD3D9 * pBufferMgr, uint vertexSize, uint numVertices, BufferUsage usage, CreateBufferFlag flag )
	{
		if( NULL == pBufferMgr)
			return false;
		if( vertexSize == 0 || numVertices == 0 )
			return false;

		RenderSystemD3D9 * pRenderSystem = pBufferMgr->getRenderSystem();
		Assert( pRenderSystem );
		D3D9Device * pDevice =  pRenderSystem->getD3D9Device();
		Assert( pDevice);
		IDirect3DDevice9 * pD3D9Device = pDevice->getDevice();
		Assert( pD3D9Device);

		//��ʼ��
		m_uiVertexSize = vertexSize;
		m_uiNumVertices = numVertices;
		m_uiSizeInBytes = m_uiVertexSize * m_uiNumVertices;
		m_eUsage = usage;
		m_pBufferMgr = pBufferMgr;

		//�ȴ����Դ�����Դ��֪ͨ
		if( !(flag & CBF_IMMEDIATE) ) pRenderSystem->getD3D9ResourceMgr()->waitForEndFrame();
					
		//�����������豸�ķ���
		pRenderSystem->getD3D9ResourceMgr()->lockDeviceAccess();

		HRESULT hr = pD3D9Device->CreateVertexBuffer(
			m_uiVertexSize * m_uiNumVertices,
			MappingsD3D9::getBufferUsage(m_eUsage),
			0,//��ָ��FVF��ʽ
			MappingsD3D9::getPoolTypeByBufferUsage(m_eUsage),
			&m_pVB,
			NULL);

		//�����豸�ķ���
		pRenderSystem->getD3D9ResourceMgr()->unlockDeviceAccess();

		if( FAILED(hr) )
		{
			return false;
		}
		
		m_pVB->GetDesc(&m_bufferDesc);

		//������Դ��ӵ���Դ������
		pRenderSystem->getD3D9ResourceMgr()->notifyResourceCreated(this);

		//��ӵ�buffer��������
		m_pBufferMgr->addVertexBuffer(this);

		return true;
	}

	/** �ͷŶ��㻺��������
	*/
	void 	VertexBufferD3D9::release()
	{
		//��buffer �����������
		m_pBufferMgr->removeVertexBuffer(this);

		//�������
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->lockResourceAccess();	
		COM_SAFE_RELEASE( m_pVB);
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();

		//��Դ�������ͷŸ���Դ
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->notifyResourceRelease( this);
		
		//�ͷŸö���
		delete this;
	}

	uint	VertexBufferD3D9::getVertexSize() const
	{
		return m_uiVertexSize;
	}

	uint	VertexBufferD3D9::getNumVertices() const
	{
		return m_uiNumVertices;
	}

	BufferUsage	VertexBufferD3D9::getUsage() const
	{
		return m_eUsage;
	}

	void *	VertexBufferD3D9::lock(uint offset,uint length,LockOptions options) 
	{
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->lockResourceAccess();
		if( NULL == m_pVB  || offset + length > m_bufferDesc.Size )
		{
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();
			return 0;
		}	

		//BL_DISCARD �� BL_NO_OVERWRITE ֻ�� D3DPOOL_DEFAULT����Ч
		if( ( options == BL_DISCARD || options == BL_NO_OVERWRITE )
			&& ( m_bufferDesc.Pool != D3DPOOL_DEFAULT) )
		{
			options = BL_NORMAL;
		}

		DWORD lockflags =0;
		switch( options)
		{
		case BL_NORMAL:
			break;
		case BL_DISCARD:
			lockflags = D3DLOCK_DISCARD;
			break;
		case BL_NO_OVERWRITE:
			lockflags = D3DLOCK_NOOVERWRITE;
			break;
		case BL_READ_ONLY:
			lockflags = D3DLOCK_READONLY;
			break;
		default:
			// �ⲻ����
			break;
		}

		void * pData = 0;
		HRESULT hr = m_pVB->Lock( offset, length, &pData, lockflags);
		if( FAILED(hr) )
		{
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();
			return 0;
		}
		m_bIsLocked = true;
		return pData;
	}

	void 	VertexBufferD3D9::unlock()
	{
		if( m_bIsLocked )
		{
			Assert(m_pVB);
			m_pVB->Unlock();
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();
			m_bIsLocked = false;
		}
	}

	bool	VertexBufferD3D9::isLocked()
	{
		return m_bIsLocked;
	}

	void 	VertexBufferD3D9::readData(uint offset,uint length,void * pDest)
	{
		if( NULL == pDest)
			return;
		if( length == 0 ) 
			return;
		if( m_eUsage & BU_WRITE_ONLY) //��Դ��ֻд�ģ���ȡʧ��
			return;

		//������Դ�ķ���
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->lockResourceAccess();
		
		if( NULL == m_pVB || offset + length > m_bufferDesc.Size )//��ȡ����ʧ��
		{
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();//����
			return;
		}
		void * pData = 0;
		HRESULT hr = m_pVB->Lock( offset, length, &pData, D3DLOCK_READONLY);
		if( FAILED(hr) )//����ʧ��
		{
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();//����
			return;
		}
		m_bIsLocked = true;
		memcpy(pDest, pData, length);		
		m_pVB->Unlock();
		m_bIsLocked = false;
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();//����
		return;
	}


	void 	VertexBufferD3D9::writeData(																			
		uint offset,																	
		uint length,																	
		const void * pSource,															
		bool discardWholeBuffer )
	{
		if( NULL == pSource )
			return;
		if( length == 0 )
			return;

		//������Դ����
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->lockResourceAccess();

		if( NULL == m_pVB || offset + length > m_bufferDesc.Size )//д������ʧ��
		{
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();//����
			return;
		}

		void * pData = 0;
		HRESULT hr;
		//discardWholeBuffer ֻ�е���;ΪD3DUSAGE_DYNAMICʱ������
		if( (m_bufferDesc.Usage & D3DUSAGE_DYNAMIC) && discardWholeBuffer)
		{
			hr = m_pVB->Lock( offset, length, &pData, D3DLOCK_DISCARD); 
		}
		else
		{
			hr = m_pVB->Lock(offset, length, &pData, 0);
		}
		if( FAILED(hr) )//lockʧ��
		{
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();
			return;
		}
		m_bIsLocked = true;
		memcpy( pData,pSource,length);
		m_pVB->Unlock();
		m_bIsLocked = false;
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();
		return;
	}

	IVertexBuffer*	VertexBufferD3D9::clone()
	{
		//����VertexBuffer
		IVertexBuffer * pVB = m_pBufferMgr->createVertexBuffer(
			m_uiVertexSize, m_uiNumVertices, m_eUsage);
		if( NULL == pVB)
			return 0;
		
		//����
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->lockResourceAccess();
		if( NULL == m_pVB)
		{
			pVB->release();
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();
			return 0;
		}
			
		//����Ŀ�껺��
		void * pDest = pVB->lock(0,0, BL_DISCARD);
		if( NULL == pDest )
		{
			pVB->release();
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();
			return 0;
		}

		//����Դ����
		void * pSrc = 0;
		if( m_eUsage & BU_WRITE_ONLY )
		{
			pSrc = this->lock(0,0, BL_NORMAL);
		}
		else
		{
			pSrc = this->lock(0,0, BL_READ_ONLY);
		}
		if( NULL == pSrc)
		{
			if( pDest) pVB->unlock();
			pVB->release();
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();
			return 0;
		}

		//���ݿ���
		memcpy( pDest, pSrc, m_uiSizeInBytes);


		//����
		this->unlock();
		pVB->unlock();
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();
		return pVB;
	}

	void VertexBufferD3D9::notifyOnDeviceLost()
	{
		//�����Default Pool �����IndexBuffer�����ͷŸ�buffer
		if(m_bufferDesc.Pool == D3DPOOL_DEFAULT)
		{
			COM_SAFE_RELEASE(m_pVB);
			return;
		}
	}

	void VertexBufferD3D9::notifyOnDeviceReset()
	{
		//�����Default Pool �����IndexBuffer�����ؽ���buffer
		if( m_bufferDesc.Pool == D3DPOOL_DEFAULT)
		{
			RenderSystemD3D9 * pRenderSystem = m_pBufferMgr->getRenderSystem();
			Assert(pRenderSystem);
			D3D9Device * pDevice = pRenderSystem->getD3D9Device();
			Assert( pDevice);
			IDirect3DDevice9 * pD3D9Device = pDevice->getDevice();
			Assert( pD3D9Device);	

			//����buffer
			HRESULT hr = pD3D9Device->CreateVertexBuffer( 
				m_uiSizeInBytes,
				MappingsD3D9::getBufferUsage(m_eUsage),
				0,
				MappingsD3D9::getPoolTypeByBufferUsage(m_eUsage),
				&m_pVB,
				NULL);

			if( SUCCEEDED(hr) )
			{
				m_pVB->GetDesc(&m_bufferDesc);
			}
		}
	}

}