/*******************************************************************
** ��  ��:	��Դ����*.mpk)
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#include "MpwFormat.h"
#include "IMpwDecoder.h"
#include <string>
using namespace std;

namespace xs
{
	class MpwFrame;

	class _RenderEngineExport Entity2DAniPack
	{
	public:
		struct SIMAGERES
		{
			// ͼƬ��Դ
			MpwFrame *		pMpwFrame;
			int				m_nOffsetX;
			int				m_nOffsetY;

			SIMAGERES(void)
			{
				memset(this, 0, sizeof(SIMAGERES));
			}
		};
		typedef list< SIMAGERES >	TLIST_IMAGERES;		
	public:
		///////////////////////////CEntity2DAni////////////////////////////
		/** �ͷ�
		@param   
		@param   
		@return  
		*/
		virtual void				release(void);

		/** ��
		@param   
		@param   
		@return  
		*/
		virtual int					Open(IRenderSystem * pRenderSystem, char * pszPathFileName);


		/** ��ʾ
		@param   
		@param   
		@return  
		*/
		virtual void				Draw(float alpha = 1.0f);	

		/** ��ʾ��һ֡
		@param   
		@param   
		@return  
		*/
		virtual void				Draw(int nFrame);

		virtual size_t				getMemorySize();

		/** ����
		@param   
		@param   
		@return  
		*/
		Entity2DAniPack();


		/** ����
		@param   
		@param   
		@return  
		*/
		virtual ~Entity2DAniPack(void);

	public:
		// ����Ŀ¼��ͼƬ
		TLIST_IMAGERES				m_listImageRes;

		// ��ǰָ���ͼƬ��Դ�����
		TLIST_IMAGERES::iterator	m_itlistImageRes;
	
		// ��ǰ���ĺ�֡
		int							m_nPlayFrame;	

		// ·����
		string						m_stringPath;

		// �ϴβ��ŵ�ʱ��
		DWORD						m_dwLastTickCount;

		// ��Ⱦϵͳ
		IRenderSystem *				m_pRenderSystem;

		// ͼƬ����
		DWORD						m_dwImageCount;
		// ·����
		string						m_stringPackName;

		IMpwDecoder					*m_pMpwDecoder;

		size_t						m_memorySize;

	};
}