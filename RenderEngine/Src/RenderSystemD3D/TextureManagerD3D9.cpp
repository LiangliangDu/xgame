#include "StdAfx.h"
#include "TextureManagerD3D9.h"
#include "RenderSystemD3D9.h"
#include "D3D9Device.h"
#include "TextureD3D9.h"

namespace xs
{


	TextureManagerD3D9 * TextureManagerD3D9Creater::create( RenderSystemD3D9 * pRenderSystem)
	{
		if( NULL == pRenderSystem)
			return 0;

		TextureManagerD3D9 * pMgr = new TextureManagerD3D9();
		if( NULL == pMgr)
			return 0;

		if( !pMgr->create(pRenderSystem) )
		{
			pMgr->release();
			return 0;
		}

		return pMgr;
	}

	bool TextureManagerD3D9::create(RenderSystemD3D9 * pRenderSystem)
	{
		if( NULL == pRenderSystem) 
			return false;

		m_pRenderSystem = pRenderSystem;

		return true;
	}



	void TextureManagerD3D9::release()
	{
		releaseAll();

		delete this;
	}



	const char* TextureManagerD3D9::getUniqueString()
	{
		m_mutex.Lock();
		static char szName[256];
		sprintf_s(szName,"ReTextureManagerUnique%d",m_ui32Index++);
		m_mutex.Unlock();
		return szName;
	}
	
	/** ��ͼ�����ݴ�����ͼ,��ͼ��width*height�ĳߴ�,����image��pRect����blt����ͼ��
	@param image ͼ������
	@param pRect ͼ���������
	@param width ���
	@param height �߶�
	@param minFO Min Filter
	@param magFO Max Filter
	@param mipFO Mip Filter
	@param s ��ͼSѰַ��ʽ
	@param t ��ͼTѰַ��ʽ
	@return ��ͼָ��
	*/
	ITexture* TextureManagerD3D9::createTextureFromImage(																
		const Image& image,																
		const Rect* pRect,																
		uint width,uint height,														
		FilterOptions minFO,												
		FilterOptions magFO,												
		FilterOptions mipFO,													
		TextureAddressingMode s,											
		TextureAddressingMode t)
	{
		ITexture *pTexture = createEmptyTexture(width,height,image.getFormat(),minFO,magFO,mipFO,s,t);
		if(pTexture)
		{
			//TODO:mipmaps
			if(!pTexture->setSubData(0,image,pRect))
			{
				releaseTexture(pTexture);
				pTexture = 0;
			}
		}

		return pTexture;
	}

	/** ��ͼ�����ݴ�����ͼ,��ͼ�Ĵ�С��pRect�Ŀ��,���pRect��Ϊ����ͼƬ�ĳߴ�
	@param image ͼ������
	@param pRect ͼ���������
	@param minFO Min Filter
	@param magFO Max Filter
	@param mipFO Mip Filter
	@param s ��ͼSѰַ��ʽ
	@param t ��ͼTѰַ��ʽ
	@return ��ͼָ��
	*/
	ITexture* TextureManagerD3D9::createTextureFromImage(																
		const Image& image,																
		const Rect* pRect,																
		FilterOptions minFO ,												
		FilterOptions magFO ,												
		FilterOptions mipFO ,													
		TextureAddressingMode s ,											
		TextureAddressingMode t)
	{
		ITexture *pTexture = createEmptyTexture(minFO,magFO,mipFO,s,t);
		if(pTexture)
		{
			if(!pTexture->loadFromImage(image,pRect))
			{
				releaseTexture(pTexture);
				pTexture = 0;
			}
		}

		return pTexture;
	}

	/** ��ͼ���ļ�������ͼ,����Щ�Կ���֧�ַ�2^n��ͼ,�������ʱ���û���Ҫʹ��2^N��ͼ
	@param name �ļ���
	@param minFO Min Filter
	@param magFO Max Filter
	@param mipFO Mip Filter
	@param s ��ͼSѰַ��ʽ
	@param t ��ͼTѰַ��ʽ
	@return ��ͼָ��
	*/
	ITexture* TextureManagerD3D9::createTextureFromFile(																
		const std::string& name,																
		FilterOptions minFO,												
		FilterOptions magFO,												
		FilterOptions mipFO,													
		TextureAddressingMode s ,											
		TextureAddressingMode t)
	{
		m_mutex.Lock();
		if(names.find(name) != names.end()) 
		{
			ITexture *pTexture = names[name];
			items[pTexture]->addRef();
			m_mutex.Unlock();
			return pTexture;
		}
		m_mutex.Unlock();

		ITexture* pTexture = createEmptyTexture(minFO,magFO,mipFO,s,t,name);
		if(pTexture)
		{
			if(pTexture->loadFromFile(name))
			{
				return pTexture;
			}
			releaseTexture(pTexture);
			pTexture = 0;
		}

		return pTexture;
	}

	/** ��Raw���ݴ�����ͼ
	@param pBuffer ����ָ��
	@param width pBufferͼ�����ݵĿ��
	@param height pBufferͼ�����ݵĸ߶�
	@param minFO Min Filter
	@param magFO Max Filter
	@param mipFO Mip Filter
	@param s ��ͼSѰַ��ʽ
	@param t ��ͼTѰַ��ʽ
	@return ��ͼָ��
	*/
	ITexture* TextureManagerD3D9::createTextureFromRawData(															
		uchar* pBuffer,																	
		uint width,uint height,PixelFormat pf,										
		FilterOptions minFO,												
		FilterOptions magFO,												
		FilterOptions mipFO,													
		TextureAddressingMode s,											
		TextureAddressingMode t)
	{
		ITexture* pTexture = createEmptyTexture(minFO,magFO,mipFO,s,t);
		if(pTexture)
		{
			if(pTexture->loadFromRawData(pBuffer,width,height,pf))
			{
				return pTexture;
			}
			releaseTexture(pTexture);
			pTexture = 0;
		}

		return pTexture;
	}

	/** �����յ���ͼ,δָ����ȡ��߶Ⱥ����ظ�ʽ
	@param minFO Min Filter
	@param magFO Max Filter
	@param mipFO Mip Filter
	@param s ��ͼSѰַ��ʽ
	@param t ��ͼTѰַ��ʽ
	@return ��ͼָ��
	*/
	ITexture* TextureManagerD3D9::createEmptyTexture(																	
		FilterOptions minFO ,												
		FilterOptions magFO,												
		FilterOptions mipFO ,													
		TextureAddressingMode s,											
		TextureAddressingMode t,
		const std::string& initialName)
	{
		m_mutex.Lock();

		std::string name;
		if(initialName != "")
		{
			name = initialName;
			if( names.find( name) != names.end() )
			{
				m_mutex.Unlock();
				return 0;
			}
		}
		else
			name = getUniqueString();

		TextureD3D9 * pTexture = new TextureD3D9(name, this, minFO, magFO, mipFO, s, t);
		if(!pTexture)
		{
			Error("Unable to allocate memory,TextureManager::createEmptyTexture failed!");
			m_mutex.Unlock();
			return 0;
		}

		do_add(name,pTexture,pTexture);

		m_mutex.Unlock();
		return pTexture;
	}

	/** �����յ���ͼ,��ָ����ȡ��߶Ⱥ����ظ�ʽ
	@param width ���
	@param height �߶�
	@param pf ���ظ�ʽ
	@param minFO Min Filter
	@param magFO Max Filter
	@param mipFO Mip Filter
	@param s ��ͼSѰַ��ʽ
	@param t ��ͼTѰַ��ʽ
	@return ��ͼָ��
	*/
	ITexture*	TextureManagerD3D9::createEmptyTexture(																	
		uint width,
		uint height,
		PixelFormat pf,										
		FilterOptions minFO,												
		FilterOptions magFO ,												
		FilterOptions mipFO ,													
		TextureAddressingMode s,											
		TextureAddressingMode t)
	{
		ITexture * pTexture = createEmptyTexture(minFO,magFO,mipFO,s,t);
		if(pTexture)
		{
			bool ret = pTexture->loadFromRawData(NULL, width, height, pf);
			if( !ret) 
			{
				pTexture->release();
				return 0;
			}
			else
			{
				return pTexture;
			}
		}
		return 0;
	}

	/** �����յ���ͼ,��ָ����ȡ��߶Ⱥ����ظ�ʽ������Ҫ�ȴ���Ⱦ���������������Ӱ��֡�ʣ�����
	����Ⱦ�е��ò���������
	@param width ���
	@param height �߶�
	@param pf ���ظ�ʽ
	@param minFO Min Filter
	@param magFO Max Filter
	@param mipFO Mip Filter
	@param s ��ͼSѰַ��ʽ
	@param t ��ͼTѰַ��ʽ
	@return ��ͼָ��
	*/
	ITexture*	TextureManagerD3D9::createEmptyTextureNoWait(																	
		uint width,uint height,PixelFormat pf,										
		FilterOptions minFO,												
		FilterOptions magFO,												
		FilterOptions mipFO,													
		TextureAddressingMode s,											
		TextureAddressingMode t)
	{
		TextureD3D9 * pTexture = static_cast<TextureD3D9 *>( createEmptyTexture(minFO,magFO,mipFO,s,t) );
		if(pTexture)
		{
			bool ret = pTexture->_create(D3DPOOL_MANAGED, 0,width, height, pf, TextureD3D9::CTO_NOWAIT);
			if(!ret)
			{
				pTexture->release();
				return 0;
			}
			else
			{
				return pTexture;
			}
		}
		return 0;	
	}

	/** �����ļ���ȡ����ͼָ�룬Ҳ�������Զ������ͼ����
	@param name �ļ��������Զ������ͼ����
	@return ��ͼָ��
	*/
	ITexture*	TextureManagerD3D9::getTexture(const std::string& name)
	{
		m_mutex.Lock();
		ITexture *pTexture = get(name);
		m_mutex.Unlock();

		return pTexture;
	}

	/** �ͷ���ͼ
	@param pTexture ��ͼ��ָ��
	*/
	void 	TextureManagerD3D9::releaseTexture(ITexture* pTexture)
	{
		m_mutex.Lock();
		del(pTexture);
		m_mutex.Unlock();
	}

	/** ���������ͷ���ͼ
	@param name ��ͼ������
	*/
	void TextureManagerD3D9::releaseTextureByName(const std::string& name)
	{
		m_mutex.Lock();
		delByName(name);
		m_mutex.Unlock();
	}

	/** �ͷ�������ͼ
	*/
	void TextureManagerD3D9::releaseAll()
	{
		m_mutex.Lock();
		std::map<ITexture*,ManagedItem*>::iterator e = items.end();
		for(std::map<ITexture*,ManagedItem*>::iterator b = items.begin();b != e;++b)
		{
			doDelete((*b).first);
		}
		items.clear();
		names.clear();
		m_mutex.Unlock();
	}

	void TextureManagerD3D9::doDelete(ITexture* pTexture)
	{
		if(pTexture)
		{
			delete static_cast<TextureD3D9*>(pTexture);
		}
	}

	TextureD3D9* TextureManagerD3D9::createEmptyeTexture(
		D3DPOOL	pooltype,
		DWORD usage,
		uint width,uint height,PixelFormat pf,										
		FilterOptions minFO,												
		FilterOptions magFO,												
		FilterOptions mipFO ,													
		TextureAddressingMode s,											
		TextureAddressingMode t)
	{
		TextureD3D9 * pTexture = static_cast<TextureD3D9 *>( createEmptyTexture(minFO,magFO,mipFO,s,t) );
		if(pTexture)
		{
			bool ret = pTexture->_create(pooltype, usage,width, height, pf);
			if(!ret)
			{
				pTexture->release();
				return 0;
			}
			else
			{
				return pTexture;
			}
		}
		return 0;
		
	}
}
