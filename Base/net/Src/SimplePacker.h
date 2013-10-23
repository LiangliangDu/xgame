/*******************************************************************
** �ļ���:	SimplePacker.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/29/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __SIMPLE_PACKER_H__
#define __SIMPLE_PACKER_H__

#include "IPacker.h"
#include <list>

namespace xs{

#	define  HEAD_TYPE        WORD

	/**
	@name : �򵥴������
	@brief: �����ʽ: ���ݳ���(2Bytes) + ʵ������
	*/
	class SimplePacker : public IPacker
	{
	public:
		virtual void Pack( const char * pRawData,DWORD dwDataLen,std::vector<AsynIoBuffer> & OutBuff )
		{
			char * pHeadBuff = (char *)AllocateAsynIoBuffer(sizeof(HEAD_TYPE));
			*(HEAD_TYPE *)pHeadBuff = (HEAD_TYPE)dwDataLen;

			AsynIoBuffer buff;

			buff.buf = pHeadBuff;
			buff.len = sizeof(HEAD_TYPE);

			OutBuff.push_back(buff);

			buff.buf = (char *)pRawData;
			buff.len = dwDataLen;

			OutBuff.push_back(buff);
		}

		bool UnPack( const char * pData,DWORD dwLen,std::vector<AsynIoBuffer> & OutBuff  )
		{
			RecycleBuffer();

			while(dwLen>0)
			{
				if ( m_dwPendingLen>MAX_NET_PACKAGE_SIZE )
					return false;

				DWORD dwNeedLen = m_dwPendingLen-m_dwRecvedPos;
				if ( dwLen >= dwNeedLen )
				{
					if ( m_dwRecvedPos!=0 )
					{
						memcpy(m_pPendingBuff+m_dwRecvedPos,pData,dwNeedLen);
						UnPackOk(m_pPendingBuff,OutBuff);
					}else
					{
						UnPackOk(pData,OutBuff);
 					}
					dwLen -= dwNeedLen;
					pData += dwNeedLen;
				}else
				{
					if ( m_pPendingBuff==0 )  // �����������û׼��������׼��������
					{
						m_pPendingBuff = (char *)AllocateAsynIoBuffer(m_dwPendingLen);
					}
					memcpy(m_pPendingBuff+m_dwRecvedPos,pData,dwLen);
					m_dwRecvedPos += dwLen;
					dwLen = 0;
				}
			}

			return true;
		}

		// ������ȡ�ɹ�
		void UnPackOk( const char * pData,std::vector<AsynIoBuffer> & OutBuff  )
		{
			// ��ǰ������ȡ��ͷ
			if ( m_pPendingBuff==(char*)&m_dwPackageLen )
			{
				m_dwPendingLen = *(HEAD_TYPE*)pData;  // ��ʼ��ȡ����
				m_pPendingBuff = 0;
				m_dwRecvedPos  = 0;
			}
			// ��ǰ������ȡ����
			else 
			{
				AsynIoBuffer buff;                // ���ظ�Ӧ�ò�
				buff.buf = (char *)pData;
				buff.len = m_dwPendingLen;

				OutBuff.push_back(buff);

				if ( m_pPendingBuff )             // ��ʼ��ȡ��ͷ
				{
					m_BuffRecycle.push_back(m_pPendingBuff);
				}

				m_pPendingBuff= (char *)&m_dwPackageLen;
				m_dwRecvedPos = 0;
				m_dwPendingLen= sizeof(HEAD_TYPE);
			}
		}

		virtual IPacker * Clone() { return new SimplePacker;}

		virtual void Release() { delete this; }

		SimplePacker() : m_pPendingBuff(0),m_dwPendingLen(0),m_dwRecvedPos(0),m_dwPackageLen(0)
		{
			m_pPendingBuff= (char *)&m_dwPackageLen; // ��һ������Ҫ�հ�ͷ
			m_dwPendingLen= sizeof(HEAD_TYPE);
		}

		virtual ~SimplePacker() 
		{
			RecycleBuffer();

			m_dwPendingLen = 0;
			m_dwRecvedPos  = 0;
			m_dwPackageLen = 0;
		}

		inline void RecycleBuffer()
		{
			if ( !m_BuffRecycle.empty() )
			{
				std::list<char*>::iterator it = m_BuffRecycle.begin();
				for ( ;it!=m_BuffRecycle.end();++it )
				{
					DeallocateAsynIoBuffer(*it);
				}

				m_BuffRecycle.clear();
			}
		}

	protected:
		char       *       m_pPendingBuff;   // ��û�����������,�����ǰ�����Ҳ����������
		DWORD              m_dwPendingLen;   // �����ܹ���Ҫ��ȡ���ֽ���
		DWORD              m_dwRecvedPos;    // �����Ѿ���ȡ���ֽ���
		HEAD_TYPE          m_dwPackageLen;   // ������
		std::list<char*>   m_BuffRecycle;    // ������ʱ������
	};
};

#endif//__SIMPLE_PACKER_H__