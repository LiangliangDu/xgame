#include "StdAfx.h"
#include "RenderTargetManagerD3D9.h"
#include "RenderTargetD3D9.h"
#include "RenderTargetD3D9Texture.h"
#include "RenderTargetD3D9Window.h"
#include "D3D9Device.h"
#include "RenderSystemD3D9.h"

namespace xs
{

	RenderTargetManagerD3D9 * RenderTargetManagerD3D9Creater::create(RenderSystemD3D9 * pRenderSystem)
	{
		//���
		if( NULL == pRenderSystem )
			return 0;

		//������ȾĿ�������
		RenderTargetManagerD3D9 * pMgr = new RenderTargetManagerD3D9();
		if( NULL == pMgr)
			return 0;

		if( !pMgr->create( pRenderSystem) )
		{
			pMgr->release();
			return 0;
		}
		else
		{
			return pMgr;
		}
	}

	RenderTargetManagerD3D9::RenderTargetManagerD3D9():
	m_pRenderSystem(0),
	m_currentRenderTargetID(0),
	m_pCurrentRenderTarget(0),
	m_uiRTTID(1)
	{
		m_vRenderTargets.clear();		
	}


	RenderTargetManagerD3D9::~RenderTargetManagerD3D9()
	{
		m_vRenderTargets.clear();
	}

	bool RenderTargetManagerD3D9::create(RenderSystemD3D9 * pRenderSystem)
	{
		if( NULL == pRenderSystem)
			return false;
		m_pRenderSystem = pRenderSystem;

		//���Ĭ����ȾĿ��
		RenderTargetD3D9Window * pRTW = new RenderTargetD3D9Window(m_pRenderSystem, false,this);
		if( NULL == pRTW)
		{
			delete pRTW;
			return false;
		}
		if( !pRTW->createAsDefaultRenderTarget() )
		{
			pRTW->release();
			return false;
		}
		m_vRenderTargets[(uint)pRTW->m_hWnd] = pRTW;
		m_currentRenderTargetID = (uint)pRTW->m_hWnd;
		m_pCurrentRenderTarget = pRTW;


		return true;
	}

	/**�ͷ���ȾĿ�������
	*/
	void RenderTargetManagerD3D9::release()
	{	
		//ȡ����ǰ��ȾĿ��
		setCurrentRenderTarget(0);

		//��Ҫ�������ͷ����е���ȾĿ��
		RenderTargetContainerIterator it = m_vRenderTargets.begin();
		for( ; it != m_vRenderTargets.end(); ++it)
		{
			(*it).second->release();
		}		

		delete this;
	}

	/** �豸��ʧ�������豸����ǰ���ô˺����ͷ���Դ
	*/
	void RenderTargetManagerD3D9::onDeviceLost()
	{
		RenderTargetContainerIterator it = m_vRenderTargets.begin();
		for(  ; it!= m_vRenderTargets.end(); ++it)
		{
			it->second->onDeviceLost();
		}
	}


	/** �豸���ú���ô˺����ͷ���Դ
	*/
	void RenderTargetManagerD3D9::onDeviceReset()
	{
		RenderTargetContainerIterator it = m_vRenderTargets.begin();
		for(  ; it!= m_vRenderTargets.end(); ++it)
		{
			it->second->onDeviceReset();
		}

		//����������ȾĿ��
		if( m_pCurrentRenderTarget )
		{
			m_pCurrentRenderTarget->onAttach(m_pCurrentRenderTarget);
			m_pCurrentRenderTarget->resetRenderState();
		}
	}

	/**�����Ⱦ�����ڵ���ȾĿ��
	@param hwnd ��Ⱦ���ھ��
	*/
	bool RenderTargetManagerD3D9::addRenderTarget(uint hwnd)
	{
		if( m_vRenderTargets.find(hwnd) != m_vRenderTargets.end() )
			return false;//�Ѿ�����һ����������ȾĿ����

		//��Ҫ����������µĽ�����
		RenderTargetD3D9Window * pRT = new RenderTargetD3D9Window(m_pRenderSystem, false, this);
		if(NULL == pRT)
			return false;

		if( !pRT->create( (HWND)hwnd) )
		{
			pRT->release();
			return false;
		}

		m_vRenderTargets[hwnd] = pRT;
		return true;
	}

	/**���õ�ǰ����ȾĿ��
	@param hwnd ���ھ������RTT���
	@return �Ƿ�ɹ�
	*/
	bool RenderTargetManagerD3D9::setCurrentRenderTarget(uint hwnd)
	{
		if( hwnd == m_currentRenderTargetID) return true;

		if( 0 == hwnd)
		{
			if( m_pCurrentRenderTarget)
				m_pCurrentRenderTarget->onDetach();
			m_pCurrentRenderTarget = 0;
			m_currentRenderTargetID  = 0;
			return true;
		}

		RenderTargetContainerIterator it = m_vRenderTargets.find( hwnd);
		if( it == m_vRenderTargets.end() ) return false;

		RenderTargetD3D9 * pOldRenderTarget = m_pCurrentRenderTarget;
		if( m_pCurrentRenderTarget)
			m_pCurrentRenderTarget->onDetach();

		m_currentRenderTargetID = hwnd;
		m_pCurrentRenderTarget = it->second;
		it->second->onAttach(pOldRenderTarget);
		return true;
	}

	/**��õ�ǰ����ȾĿ��id
	@return ��ǰ����ȾĿ��Ĵ��ھ����������RTT�ľ��
	*/
	uint RenderTargetManagerD3D9::getCurrentRenderTargetID() 
	{
		return m_currentRenderTargetID;
	}

	/**�����Ⱦ���������ȾĿ��
	@param width ���
	@param height �߶�
	@param alpha ��ȾĿ���Ƿ���alphaͨ��
	@param min ��С�˲���
	@param mag ����˲���
	@param mip mipmap�˲���ʽ
	@param s ����sѰַ��ʽ
	@param t ����tѰַ��ʽ
	@return ���ɵ�RTT�ľ��
	*/
	uint RenderTargetManagerD3D9::addRTT(
		int width,
		int height, 
		bool alpha,
		FilterOptions min , 
		FilterOptions mag , 
		FilterOptions mip ,
		TextureAddressingMode s,											
		TextureAddressingMode t)
	{
		RenderTargetD3D9Texture * pRTT = new RenderTargetD3D9Texture(m_pRenderSystem, false, this);
		if( NULL == pRTT)
			return 0;
		if( !pRTT->create(width, height, alpha, min, mag, mip, s, t) )
		{
			pRTT->release();
			return 0;
		}

		//���Ҳ���ͻ��rtt id
		while( m_vRenderTargets.find( m_uiRTTID) != m_vRenderTargets.end() )
		{
			++m_uiRTTID;
		}

		m_vRenderTargets[m_uiRTTID] = pRTT;
		return m_uiRTTID++;	
	}

	/**���Overlay RenderTarget��ֻ�����һ��
	*/
	bool RenderTargetManagerD3D9::addOverlayRenderTarget()
	{
		//��ʱ��֧��
		return false;
	}

	/**ɾ��Overlay RenderTarget
	*/
	void RenderTargetManagerD3D9::removeOverlayRenderTarget()
	{
		//��ʱ��֧��
		return;
	}

	bool RenderTargetManagerD3D9::setOverlayRenderTarget()
	{
		//��ʱ��֧��
		return false;
	}

	/**ɾ����ȾĿ��
	@param hwnd ���ھ��
	@return �Ƿ�ɹ�
	*/
	bool RenderTargetManagerD3D9::removeRenderTarget(uint hwnd)
	{
		RenderTargetContainerIterator it = m_vRenderTargets.find( hwnd);
		if( it == m_vRenderTargets.end() )
			return false;

		//�����Ĭ����ȾĿ�꣬���豸��һ�����ԣ��ǲ��ܱ�ɾ����
		if( it->second->isDefaultRenderTarget() )
			return false;

		//���ɾ������ȾĿ���ǵ�ǰ��ȾĿ��
		if( hwnd == m_currentRenderTargetID)
		{
			m_pCurrentRenderTarget->onDetach();
			m_pCurrentRenderTarget = 0;
			m_currentRenderTargetID = 0;
		}
		
		it->second->release();
		m_vRenderTargets.erase(it);
		return true;
	}

	/**���߳����RenderTarget,���߳������ȾĿ��ֻ�������첽����
	@param hwnd ���ھ��
	@return �Ƿ�ɹ�
	*/
	uint RenderTargetManagerD3D9::MTaddRenderTarget()
	{
		//�����Ѿ������ˣ��첽������Դ�Ĺ���������ʲôҲ����
		return 1;
	}

	/**���߳�ɾ����ȾĿ��,���߳������ȾĿ��ֻ�������첽����
	@param hwnd ���ھ��
	@return �Ƿ�ɹ�
	*/
	bool RenderTargetManagerD3D9::MTremoveRenderTarget(uint key)
	{
		//�����Ѿ������ˣ��첽������Դ�Ĺ���������ʲôҲ����
		//nothing to do
		return true;
	}

			/** ��ȡ��ȾĿ��
		@return ��ȾĿ��
		*/
	RenderTargetD3D9 * RenderTargetManagerD3D9::getRenderTarget(uint id)
	{
		RenderTargetContainerIterator it = m_vRenderTargets.find(id);
		if( it == m_vRenderTargets.end() )
			return 0;
		else
			return it->second;
	}
}
