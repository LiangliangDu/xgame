#include "stdafx.h"


#include "DataPacker.h"





namespace xs{

	#	define MAX_NET_PACKAGE_SIZE  (1024*63)// ������ݿ��С


	




	void DataPacker::Pack( const char * pRawData,DWORD dwDataLen,std::vector<AsynIoBuffer> & OutBuff )
	{
		char * pHeadBuff = (char *)AllocateAsynIoBuffer(sizeof(HEAD_TYPE));
		*(HEAD_TYPE *)pHeadBuff = (HEAD_TYPE)dwDataLen;

		AsynIoBuffer buff;

		buff.buf = pHeadBuff;
		buff.len = sizeof(HEAD_TYPE);

		OutBuff.push_back(buff);

		CryptPool::Encrypt(m_dwCryptId, (CryptPool::uchar*)pRawData, dwDataLen,key,keysize);

		buff.buf = (char *)pRawData;
		buff.len = dwDataLen;

		OutBuff.push_back(buff);
	}

	bool DataPacker::UnPack( const char * pData,DWORD dwLen,std::vector<AsynIoBuffer> & OutBuff  )
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
	void DataPacker::UnPackOk( const char * pData,std::vector<AsynIoBuffer> & OutBuff  )
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

			CryptPool::Decrypt(m_dwCryptId, (CryptPool::uchar*)pData, m_dwPendingLen,key,keysize);
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


	ulong DataPacker::SetSessionKey(ulong id,uchar * key,ulong keylen)
	{
		//assert(id<g_nPoolSize);
		switch (id)
		{
		case 0:
			Set_rc4_key(key,keylen);
			break;
		case 1:
			Set_tea_key(key,keylen);
			break;
		case 2:
			Set_blowfish_key(key,keylen);
			break;
		default:
			break;
		}
		return 1;
	}

	ulong DataPacker::Set_rc4_key(uchar keybuf[],ulong keylen)
	{
		assert(16==keylen);
		memcpy_s(key,sizeof(key),keybuf,keylen);
		return 1;
	}

	ulong DataPacker::Set_tea_key(uchar keybuf[],ulong keylen)
	{
		assert(64==keylen);
		memcpy_s(key,sizeof(key),keybuf,keylen);
		return 1;
	}

	ulong DataPacker::Set_blowfish_key(uchar keybuf[],ulong keylen)
	{
		assert(64==keylen);
		memcpy_s(key,sizeof(key),keybuf,keylen);
		return 1;
	}


};

