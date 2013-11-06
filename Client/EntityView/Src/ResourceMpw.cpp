#include "stdafx.h"
#include "ResourceMpw.h"

size_t ResourceMpw::size() const
{
	return m_pMpw ? m_pMpw->getMemorySize() : 0;
}

void ResourceMpw::release()
{
	safeRelease(m_pMpw);
	delete this;
}

bool ResourceMpw::load(const std::string& name)
{
	Entity2DAniPack *pMpw = new Entity2DAniPack();
	int nResult = pMpw->Open(getRenderEngine()->getRenderSystem(),(char*)name.c_str());

	if(nResult)
	{
		//����deleteʱ���е���Դû���ͷ�
		/*
		delete pMpw;
		pMpw = 0;
		return false;
		*/
		safeRelease( pMpw);
		return false;
		
	}

	m_pMpw = pMpw;
	return true;
}

void* ResourceMpw::getInnerData()
{
	return (void*)m_pMpw;
}