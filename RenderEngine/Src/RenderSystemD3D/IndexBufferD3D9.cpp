#include "StdAfx.h"
#include "IndexBufferD3D9.h"
#include "BufferManagerD3D9.h"
#include "RenderSystemD3D9.h"
#include "D3D9ResourceManager.h"
#include "D3D9Device.h"
#include "MappingsD3D9.h"


namespace xs
{

	IndexBufferD3D9 * IndexBufferD3D9Creater::create(BufferManagerD3D9 * pMgr,IndexType itype,uint numIndices,BufferUsage usage, CreateBufferFlag flag )
	{	
		IndexBufferD3D9 * pIB = new IndexBufferD3D9();
		if( !pIB->create(pMgr, itype, numIndices, usage, flag) )
		{
			pIB->release();
			return 0;
		}

		return pIB;
	}
	
	IndexBufferD3D9::IndexBufferD3D9():
	m_pBufferMgr(0),
	m_pIB(0),
	m_eIndexType(IT_16BIT),
	m_uiNumIndices(0),
	m_eUsage(BU_STATIC),
	m_uiIndexSize(0),
	m_bIsLocked(false)
	{
		ZeroMemory(&m_bufferDesc, sizeof(m_bufferDesc) );
	}

	IndexBufferD3D9::~IndexBufferD3D9()
	{
		
	}

	bool IndexBufferD3D9::create(BufferManagerD3D9 * pMgr,IndexType itype,uint numIndices,BufferUsage usage, CreateBufferFlag flag )
	{
		if( NULL == pMgr) return false;

		RenderSystemD3D9 * pRenderSystem = pMgr->getRenderSystem();
		Assert(pRenderSystem);
		D3D9Device * pDevice = pRenderSystem->getD3D9Device();
		Assert(pDevice);
		IDirect3DDevice9 * pD3D9Device = pDevice->getDevice();
		Assert(pD3D9Device);

		//��ʼ��
		m_pBufferMgr = pMgr;
		m_eIndexType = itype;
		m_uiIndexSize = MappingsD3D9::getIndexTypeSize(m_eIndexType);
		m_uiNumIndices = numIndices;
		m_eUsage = usage;

		//�ȴ����Դ�����Դ��֪ͨ
		if( !( flag & CBF_IMMEDIATE) )
			pRenderSystem->getD3D9ResourceMgr()->waitForEndFrame();
		
		//�����豸����
		pRenderSystem->getD3D9ResourceMgr()->lockDeviceAccess();

		//����buffer
		HRESULT hr = pD3D9Device->CreateIndexBuffer(  (m_uiIndexSize * m_uiNumIndices),
			MappingsD3D9::getBufferUsage(m_eUsage),
			MappingsD3D9::getIndexTypeFormat(m_eIndexType),
			MappingsD3D9::getPoolTypeByBufferUsage(m_eUsage),
			&m_pIB,
			NULL);
		
		//�����豸����
		pRenderSystem->getD3D9ResourceMgr()->unlockDeviceAccess();

		if( FAILED(hr) )
		{
			return false;
		}

		//��ȡ����
		m_pIB->GetDesc(&m_bufferDesc);

		//������Դ��ӵ���Դ������
		pRenderSystem->getD3D9ResourceMgr()->notifyResourceCreated(this);

		//��ӵ�buffer ��������
		m_pBufferMgr->addIndexBuffer(this);

		return true;
	}

	void IndexBufferD3D9::release()
	{
		//��buffer �����������
		m_pBufferMgr->removeIndexBuffer( this);

		//�������
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->lockResourceAccess();	
		COM_SAFE_RELEASE( m_pIB);
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();

		//������Դ����Դ���������
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->notifyResourceRelease(this);

		//�ͷŸö���
		delete this;
	}


	IndexType IndexBufferD3D9::getType(void ) const
	{
		return m_eIndexType;
	}

	uint IndexBufferD3D9::getNumIndices(void ) const
	{
		return m_uiNumIndices;
	}


	uint IndexBufferD3D9::getIndexSize(void ) const
	{
		return m_uiIndexSize;
	}

	BufferUsage	IndexBufferD3D9::getUsage() const
	{
		return m_eUsage;
	}

	void * IndexBufferD3D9::lock(uint offset,uint length,LockOptions options)
	{
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->lockResourceAccess();
		if( NULL == m_pIB  || offset + length > m_bufferDesc.Size    )
		{
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();
			return 0;
		}	

		if( ( options == BL_DISCARD || options == BL_NO_OVERWRITE )
			&& ( m_bufferDesc.Pool != D3DPOOL_DEFAULT) )
		{
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();
			return 0;
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
		HRESULT hr = m_pIB->Lock( offset, length, &pData, lockflags);
		if( FAILED(hr) )
		{
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();
			return 0;
		}
		m_bIsLocked = true;
		return pData;
	}

	void IndexBufferD3D9::unlock()
	{
		if( m_bIsLocked )
		{
			Assert(m_pIB);
			m_pIB->Unlock();		
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();
			m_bIsLocked = false;
		}
	}

	bool IndexBufferD3D9::isLocked()
	{
		return m_bIsLocked;
	}

	void IndexBufferD3D9::readData(uint offset,uint length,void * pDest)
	{
		if( NULL == pDest)
			return;
		if( length == 0 ) 
			return;
		if( m_eUsage & BU_WRITE_ONLY) //��Դ��ֻд�ģ���ȡʧ��
			return;

		//������Դ�ķ���
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->lockResourceAccess();
		
		if( NULL == m_pIB || offset + length > m_bufferDesc.Size )//��ȡ����ʧ��
		{
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();//����
			return;
		}
		void * pData = 0;
		HRESULT hr = m_pIB->Lock( offset, length, &pData, D3DLOCK_READONLY);
		if( FAILED(hr) )//����ʧ��
		{
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();//����
			return;
		}
		m_bIsLocked = true;
		memcpy(pDest, pData, length);		
		m_pIB->Unlock();
		m_bIsLocked = false;
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();//����
		return;
	}

	void IndexBufferD3D9::writeData(																			
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

		if( NULL == m_pIB || offset + length > m_bufferDesc.Size )//д������ʧ��
		{
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();//����
			return;
		}

		void * pData = 0;
		HRESULT hr;
		if( (m_bufferDesc.Usage & D3DUSAGE_DYNAMIC) && discardWholeBuffer)
		{
			hr = m_pIB->Lock( offset, length, &pData, D3DLOCK_DISCARD); 
		}
		else
		{
			hr = m_pIB->Lock(offset, length, &pData, 0);
		}
		if( FAILED(hr) )//lockʧ��
		{
			m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();
			return;
		}
		m_bIsLocked = true;
		memcpy( pData,pSource,length);
		m_pIB->Unlock();
		m_bIsLocked = false;
		m_pBufferMgr->getRenderSystem()->getD3D9ResourceMgr()->unlockResourceAccess();
		return;
	}

	void IndexBufferD3D9::notifyOnDeviceLost()
	{
		//�����Default Pool �����IndexBuffer�����ͷŸ�buffer
		if(m_bufferDesc.Pool == D3DPOOL_DEFAULT)
		{
			COM_SAFE_RELEASE(m_pIB);
			return;
		}

	}

	void IndexBufferD3D9::notifyOnDeviceReset()
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
			HRESULT hr = pD3D9Device->CreateIndexBuffer(  (m_uiIndexSize * m_uiNumIndices),
				MappingsD3D9::getBufferUsage(m_eUsage),
				MappingsD3D9::getIndexTypeFormat(m_eIndexType),
				MappingsD3D9::getPoolTypeByBufferUsage(m_eUsage),
				&m_pIB,
				NULL);

			if( SUCCEEDED(hr) )
			{
				m_pIB->GetDesc(&m_bufferDesc);
			}
		}
	}
	
}
