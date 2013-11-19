/*******************************************************************
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#include "Stdafx.h"

#include "MpwFormat.h"
#include "Mpwdecoder.h"
#include "Entity2DAniPack.h"
#include "MpwFrame.h"

namespace xs
{
	/** ����
	@param   
	@param   
	@return  
	*/
	Entity2DAniPack::Entity2DAniPack()
	{
		m_listImageRes.clear();

		m_dwLastTickCount = 0;

		m_dwImageCount = 0;

		m_pRenderSystem = NULL;

		m_stringPath.clear();

		m_itlistImageRes = m_listImageRes.end();

		m_nPlayFrame = -1;

		// ��Ⱦϵͳ
		m_pRenderSystem = 0;

		m_pMpwDecoder = new MpwDecoder;

		m_memorySize = 0;
	}


	/** ����
	@param   
	@param   
	@return  
	*/
	Entity2DAniPack::~Entity2DAniPack(void)
	{

	}


	/** �ͷ�
	@param   
	@param   
	@return  
	*/
	void Entity2DAniPack::release(void)
	{
	
		safeRelease(m_pMpwDecoder);
		// �ͷ�
		TLIST_IMAGERES::iterator itI = m_listImageRes.begin();
		for( ; itI != m_listImageRes.end(); ++itI)
		{
			SIMAGERES * pImageRes = &(*itI);

			if(pImageRes->pMpwFrame != NULL)
			{
				pImageRes->pMpwFrame->finalize();
			}			

			safeDelete(pImageRes->pMpwFrame);
		}

		m_listImageRes.clear();

		delete this;
	}


	/** ��
	@param   
	@param   
	@return 1 : ʧ��
	2 ���ļ�������
	3 ��δ�ҵ��ļ�
	4 ����ȡ��Դʧ��
	5 : �Ƿ��ļ���ʽ
	6 : ��ѹʧ��
	*/
	int Entity2DAniPack::Open(IRenderSystem * pRenderSystem, char * pszPathFileName)
	{
		if(pRenderSystem == NULL || pszPathFileName == NULL)
		{
			Info("Entity2DAniPack::Open Param list is empty");
			return 1;
		}
		m_stringPackName = pszPathFileName;

		m_pRenderSystem = pRenderSystem;
		if(!m_pMpwDecoder->load(pszPathFileName))
			return 1;
		int nTotal = m_pMpwDecoder->getTotalFrame();
		m_dwImageCount = 0;
		for(int nFrame = 0 ; nFrame < nTotal ; nFrame++)
		{
			SIMAGERES imageres;			
			xs::Stream * pStream = m_pMpwDecoder->getFrameData(nFrame);
			if(pStream != NULL)
			{
				imageres.pMpwFrame = new MpwFrame();
				if( ! imageres.pMpwFrame->initialize(m_pRenderSystem,
						pStream,
						m_pMpwDecoder->getFileFormat(), true) )
				{
					safeDelete(imageres.pMpwFrame);
					return 1;
				}
			}
			m_dwImageCount++;

			int nX,nY;
			m_pMpwDecoder->getImageOffset(nFrame,nX,nY);
			imageres.m_nOffsetX = nX;
			imageres.m_nOffsetY = nY;
			m_listImageRes.push_back(imageres);
		}		
		m_pMpwDecoder->close();

		m_memorySize = 0;

		TLIST_IMAGERES::iterator begin = m_listImageRes.begin();
		TLIST_IMAGERES ::iterator end = m_listImageRes.end();
		while(begin != end)
		{
			m_memorySize += (*begin).pMpwFrame->getMemorySize();
			++begin;
		}

		// �����ָ��LISTͷ
		m_itlistImageRes = m_listImageRes.begin();
		m_nPlayFrame = 0;
		return 0;
	}


	/** ��ʾ
	@param   
	@param   
	@return  
	*/
	void Entity2DAniPack::Draw(float alpha)
	{
		if(m_dwImageCount <= 0)
			return;

		if(m_dwImageCount > 1)
		{
			// ��ʼ��
			if(m_dwLastTickCount == 0)
			{
				m_dwLastTickCount = getTickCount();
			}

			// ͼƬ��ת
			DWORD dwTickCount = getTickCount();
			if((dwTickCount - m_dwLastTickCount) >= m_pMpwDecoder->getPlayDelay())
			{
				m_itlistImageRes++;
				m_nPlayFrame++;
				if(m_itlistImageRes == m_listImageRes.end())
				{
					m_itlistImageRes = m_listImageRes.begin();
					m_nPlayFrame = 0;
				}

				m_dwLastTickCount = dwTickCount;
			}
		}

		// ��ʾ
		if((*m_itlistImageRes).pMpwFrame != NULL)
		{
			(*m_itlistImageRes).pMpwFrame->render(alpha);
		}
	}

	size_t	Entity2DAniPack::getMemorySize()
	{
		return m_memorySize;
	}

	/** ��ʾ��һ֡
	@param   
	@param   
	@return  
	*/
	void Entity2DAniPack::Draw(int nFrame)
	{
		if(nFrame < 0 || nFrame >= (int)m_dwImageCount)
		{
			return;
		}

		if(m_nPlayFrame != nFrame)
		{
			int nMargin = nFrame - m_nPlayFrame;
			advance(m_itlistImageRes, nMargin);	
			m_nPlayFrame += nMargin;
		}

		// ��ʾ
		if((*m_itlistImageRes).pMpwFrame != NULL)
		{
			(*m_itlistImageRes).pMpwFrame->render();
		}	
	}
}