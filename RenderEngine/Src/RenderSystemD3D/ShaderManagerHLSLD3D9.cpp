#include "StdAfx.h"
#include "ShaderManagerHLSLD3D9.h"
#include "RenderSystemD3D9.h"
#include "D3D9Device.h"
#include "ShaderFragmentHLSLD3D9.h"
#include "ShaderProgramHLSLD3D9.h"


namespace xs
{

	ShaderManagerHLSLD3D9 * ShaderManagerHLSLD3D9Creater::create(RenderSystemD3D9 * pRenderSystem)
	{
		if( NULL == pRenderSystem)
			return 0;

		ShaderManagerHLSLD3D9 * pMgr= new ShaderManagerHLSLD3D9();
		if( NULL == pMgr)
			return 0;

		if( !pMgr->create(pRenderSystem) )
		{
			pMgr->release();
			return 0;
		}
		else
		{
			return pMgr;
		}
	}

	ShaderManagerHLSLD3D9::ShaderManagerHLSLD3D9():
		m_pRenderSystem(0),
		m_ui32Num(0)
	{
		// nothing to do
	}

	ShaderManagerHLSLD3D9::~ShaderManagerHLSLD3D9()
	{
		//nothing to do
	}

	bool ShaderManagerHLSLD3D9::create(RenderSystemD3D9 * pRenderSystem)
	{
		if( NULL == pRenderSystem)
			return false;

		m_pRenderSystem = pRenderSystem;
		return true;
	}

	void ShaderManagerHLSLD3D9::release()
	{
		releaseAllShader();
		delete this;
	}

	/** ���ļ��д�����ɫ��
	@param ShaderType ��ɫ������
	@param fn �ļ���
	@return ��ɫ���ӿ�ָ��
	*/
	IShader* ShaderManagerHLSLD3D9::createShaderFromFile(ShaderType st,const std::string& fn)
	{
		m_mutex.Lock();
		IShader *pShader = 0;
		if(names.find(fn) != names.end()) 
		{
			pShader = names[fn];
			items[pShader]->addRef();
		}
		else
		{
			xs::CStreamHelper pStream = xs::getFileSystem()->open(fn.c_str());
			if(pStream)
			{
				uint len = pStream->getLength();
				uchar *pData = new uchar[len];
				pStream->read(pData,len);
				pShader = _createShaderFromMemory( m_pRenderSystem, fn, st, pData, len);
				if(pShader)
				{
					do_add(fn,pShader,static_cast<ShaderFragmentHLSLD3D9*>(pShader));
				}
				delete[] pData;
			}
		}

		m_mutex.Unlock();
		return pShader;
	}

	/** ���ڴ������д�����ɫ��
	@param ShaderType ��ɫ������
	@param pBuffer ���ݵ�ַ
	@param len ���ݳ���
	@return ��ɫ���ӿ�ָ��
	@see ShaderType
	*/
	IShader* ShaderManagerHLSLD3D9::createShaderFromMemory(ShaderType st,const uchar *pBuffer,uint len)
	{
		if( NULL == pBuffer || len <= 0)
			return 0;
		m_mutex.Lock();
		std::string name( getUniqueString() );
		IShader * pShader = _createShaderFromMemory(m_pRenderSystem, name, st, pBuffer, len );
		if( pShader)
		{
			do_add( name, pShader, static_cast<ShaderFragmentHLSLD3D9 *>(pShader) );
		}
		m_mutex.Unlock();
		return pShader;
	}

	/** ����һ����ɫ��
	@param IShader* ��ɫ��ָ��
	*/
	void ShaderManagerHLSLD3D9::releaseShader(IShader* pShader)
	{
		m_mutex.Lock();
		del( pShader );
		m_mutex.Unlock();
	}

	/** �������е���ɫ��
	*/
	void ShaderManagerHLSLD3D9::releaseAllShader()
	{
		m_mutex.Lock();
		std::map<IShader*,ManagedItem*>::iterator e = items.end();
		for(std::map<IShader*,ManagedItem*>::iterator b = items.begin();b != e;++b)
		{
			doDelete((*b).first);
		}
		items.clear();
		names.clear();
		m_mutex.Unlock();
	}


	void ShaderManagerHLSLD3D9::doDelete(IShader* pShader)
	{
		ShaderFragmentHLSLD3D9 * pD3DShader = static_cast<ShaderFragmentHLSLD3D9 *>(pShader);
		if( NULL != pD3DShader )
		{
			pD3DShader->release();
		}
	}

	const char* ShaderManagerHLSLD3D9::getUniqueString()
	{
		m_mutex.Lock();
		static char szName[256];	
		sprintf_s(szName,"ReShaderManagerUnique%d",m_ui32Num++);
		m_mutex.Unlock();
		return szName;
	}

	IShader * ShaderManagerHLSLD3D9::_createShaderFromMemory(
		RenderSystemD3D9 * pRenderSystem,
		const std::string & name,
		ShaderType st,
		const uchar *pBuffer,
		uint len )
	{
		if( NULL == pRenderSystem)
			return 0;

		if( NULL == pBuffer || len <= 0)
			return 0;

		ShaderFragmentHLSLD3D9 * pShader = new ShaderFragmentHLSLD3D9( name);
		if( NULL == pShader )
			return 0;

		if( !pShader->create( pRenderSystem, st, pBuffer, len) )
		{
			pShader->release();
			return 0;
		}
		else
		{
			return pShader;
		}
	}

}