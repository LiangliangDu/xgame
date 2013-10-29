/*******************************************************************
** ��  ��:	����ʽ
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
//#ifdef WIN32
	#include "Stdafx.h"
//#else
//	#include "../StdAfx.h"
//#endif

#include "MpwFormat.h"


// ÿ��Ŀ¼��ɢ�ļ�����
#define DIR_MAX_FILE_COUNT				256

// �������ʱ
#define ANI_MAX_DELAY					600000

///////////////////////////////////////////////////////////////////
// ������
enum
{
	PACKTYPE_UNKNOW = 0,								// δ֪��
	PACKTYPE_ANI,										// ������
	PACKTYPE_MAX,										// �����
};


/** ���캯��
@param   
@param   
@return  
*/
PackFileHeader::PackFileHeader(void)
{
	memset(&m_PackFileHeader, 0, sizeof(SPackFileHeader));
	m_PackFileHeader.m_dwCode = 'WMTL';
	m_PackFileHeader.m_dwVersion = (1<<16 | 1<<0);
	m_PackFileHeader.m_dwPackType = PACKTYPE_ANI;
}

/** ���캯��
@param   
@param   
@return  
*/
bool PackFileHeader::Open(xs::Stream * pStream)
{
	memset(&m_PackFileHeader, 0, sizeof(SPackFileHeader));

	if(pStream == NULL)
	{
		return false;
	}

	// �ƶ�ĩ
	pStream->seek(0, SEEK_END);

	// ȡ�ó���
	long lLen = pStream->getPosition();

	long length = pStream->getLength();

	long pl = sizeof(SPackFileHeader);

	// �������Ƿ��С�ڰ��ļ�
	if(lLen < sizeof(SPackFileHeader))
	{
		return false;
	}

	// �ƶ��ļ���
	pStream->seek(0, SEEK_SET);

	// ��ȡ����
	if(!pStream->read(&m_PackFileHeader, sizeof(SPackFileHeader)))
	{
		return false;
	}

	// ������֤
	if(m_PackFileHeader.m_dwVersion != (1<<16 | 1<<0) || m_PackFileHeader.m_dwCode != 'WMTL' || 
		m_PackFileHeader.m_dwPackType < PACKTYPE_UNKNOW || m_PackFileHeader.m_dwPackType >= PACKTYPE_MAX ||
		m_PackFileHeader.m_dwTotalFrame <= 0 || m_PackFileHeader.m_dwTotalFrame > DIR_MAX_FILE_COUNT || 
		m_PackFileHeader.m_dwPlayDelay <= 0 || m_PackFileHeader.m_dwPlayDelay > ANI_MAX_DELAY)
	{
		return false;
	}

	return true;
}

/** ����ѹ����־
@param   
@param   
@return  
*/
void PackFileHeader::SetCompressFlag(DWORD dwFlag)
{
	m_PackFileHeader.m_dwCompress = dwFlag;
}


/** ȡ��ѹ����־
@param   
@param   
@return  
*/
DWORD PackFileHeader::GetCompressFlag(void)
{
	return m_PackFileHeader.m_dwCompress;
}

/** ���ü��ܱ�־
@param   
@param   
@return  
*/
void PackFileHeader::SetEncryptFlag(DWORD dwFlag)
{
	m_PackFileHeader.m_dwEncrypt = dwFlag;
}

/** ȡ�ü��ܱ�־
@param   
@param   
@return  
*/
DWORD PackFileHeader::GetEncryptFlag(void)
{
	return m_PackFileHeader.m_dwEncrypt;
}

/** ���ñ�ʶ��
@param   
@param   
@return  
*/
void PackFileHeader::SetPackCaption(LPCSTR pszCaption)
{
	//if(strlen(m_PackFileHeader.m_szCaption) == 0)
	//{
	//	lstrcpyn(m_PackFileHeader.m_szCaption, pszCaption, sizeof(m_PackFileHeader.m_szCaption));
	//}
}

/** ȡ�ñ�ʶ��
@param   
@param   
@return  
*/
LPCSTR PackFileHeader::GetPackCaption(void)
{
	//return m_PackFileHeader.m_szCaption;
	return "";
}

/** ���ð�����
@param   
@param   
@return  
*/
void PackFileHeader::SetPackType(DWORD dwPackType)
{
	m_PackFileHeader.m_dwPackType = dwPackType;
}

/** ��ð�����
@param   
@param   
@return  
*/
DWORD PackFileHeader::GetPackType(void)
{
	return m_PackFileHeader.m_dwPackType;
}

/** ���ú���Zip����
@param   
@param   
@return  
*/
void PackFileHeader::SetZipLen(DWORD dwZipLen)
{
	m_PackFileHeader.m_dwZipLen = dwZipLen;
}

/** ��ú���Zip����
@param   
@param   
@return  
*/
DWORD PackFileHeader::GetZipLen(void)
{
	return m_PackFileHeader.m_dwZipLen;
}

/** ȡ�ýṹ��С
@param   
@param   
@return  
*/
int PackFileHeader::GetStructSize(void)
{
	return sizeof(m_PackFileHeader);
}

/** ȡ�ñ����ֽ�
@param   
@param   
@return  
*/
char * PackFileHeader::GetReserve(void)
{
	//return m_PackFileHeader.m_szReserve;
	return 0;
}

/** ���ñ����ֽ�
@param   
@param   
@return  
*/
void PackFileHeader::SetReserve(char * pszReserve, int nLen)
{
	//memcpy(m_PackFileHeader.m_szReserve, pszReserve, nLen);
}

/** �ļ���ʽ
@param   
@param   
@return  
*/
void PackFileHeader::SetFileFormat(LPCSTR szFileFormat)
{
	//lstrcpyn(m_PackFileHeader.m_szFileFormat, szFileFormat, sizeof(m_PackFileHeader.m_szFileFormat));
    strncpy(m_PackFileHeader.m_szFileFormat, szFileFormat, sizeof(m_PackFileHeader.m_szFileFormat));
}

/** �ļ���ʽ
@param   
@param   
@return  
*/
LPCSTR PackFileHeader::GetFileFormat(void)
{
	return m_PackFileHeader.m_szFileFormat;
}

/** �ܶ���֡��
@param   
@param   
@return  
*/
void PackFileHeader::SetTotalFrame(DWORD dwTotalFrame)
{
	m_PackFileHeader.m_dwTotalFrame = dwTotalFrame;	
}

/** �ܶ���֡��
@param   
@param   
@return  
*/
DWORD PackFileHeader::GetTotalFrame(void)
{
	return m_PackFileHeader.m_dwTotalFrame;
}

/** ����������ʱ
@param   
@param   
@return  
*/
void PackFileHeader::SetPlayDelay(DWORD dwPlayDelay)
{
	m_PackFileHeader.m_dwPlayDelay = dwPlayDelay;
}

/** ����������ʱ
@param   
@param   
@return  
*/
DWORD PackFileHeader::GetPlayDelay(void)
{
	return m_PackFileHeader.m_dwPlayDelay;
}

/** ���캯��
@param   
@param   
@return  
*/

FrameInfoHeader::FrameInfoHeader(void)
{
	memset(&m_FrameInfoHeader, 0, sizeof(SFrameInfoHeader));
}

/** ���캯��
@param   
@param   
@return  
*/
bool FrameInfoHeader::Open(xs::Stream * pStream)
{
	memset(&m_FrameInfoHeader, 0, sizeof(SFrameInfoHeader));	

	if(pStream == NULL)
	{
		return false;
	}

	// ȡ�õ�ǰλ��
	long lOldPos = pStream->getPosition();

	// �ƶ��ļ�ĩ
	pStream->seek(0, SEEK_END);

	// ȡ���ļ�����
	long lNewLen = pStream->getPosition();

	int len = pStream->getLength();

	// ���ļ������Ƿ��С�ڰ��ļ�
	if((lNewLen - lOldPos) <= sizeof(SFrameInfoHeader))
	{
		return false;
	}

	// �ƶ��ļ���ԭ��λֵ
	pStream->seek(lOldPos, SEEK_SET);

	// ��ȡ����ͷ
	if(!pStream->read(&m_FrameInfoHeader, sizeof(SFrameInfoHeader)))
	{
		return false;
	}

	if(m_FrameInfoHeader.m_nImageSize > 0)
	{
		// ȡ�õ�ǰλ��
		lOldPos = pStream->getPosition();

		// �ƶ��ļ�ĩ
		pStream->seek(0, SEEK_END);

		// ȡ���ļ�����
		lNewLen = pStream->getPosition();

		// �ƶ��ļ���ԭ��λֵ
		pStream->seek(lOldPos, SEEK_SET);

		// ���ļ������Ƿ��С�ڰ��ļ�
		if((lNewLen - lOldPos) <= sizeof(m_FrameInfoHeader.m_nImageSize))
		{
			return false;
		} 

		// ��ȡͼƬ����
		char * pImageData = new char [m_FrameInfoHeader.m_nImageSize];		
		if(!pStream->read(pImageData, m_FrameInfoHeader.m_nImageSize))
		{
			return false;
		}

		m_streamImageData.attach((uchar *)pImageData, m_FrameInfoHeader.m_nImageSize);

		pImageData = NULL;
	}

	return true;
}

/** �ͷ�
@param   
@param   
@return  
*/
void FrameInfoHeader::Release(void)
{
	if(m_streamImageData.getBuffer() != NULL)
	{
		uchar * pBuff = m_streamImageData.detach();
		safeDeleteArray(pBuff);
	}

	delete this;
}

/** �ر�
@param   
@param   
@return  
*/
void FrameInfoHeader::Close(void)
{
	if(m_streamImageData.getBuffer() != NULL)
	{
		uchar * pBuff = m_streamImageData.detach();
		safeDeleteArray(pBuff);
	}
}

/** ����ͼƬ��С
@param   
@param   
@return  
*/
void FrameInfoHeader::SetImageSize(int nWidth, int nHeight)
{
	m_FrameInfoHeader.m_nWidth = nWidth;
	m_FrameInfoHeader.m_nHeight = nHeight;
}

/** ȡ��ͼƬ��С
@param   
@param   
@return  
*/
void FrameInfoHeader::GetImageSize(int &nWidth, int &nHeight)
{
	nWidth = m_FrameInfoHeader.m_nWidth;
	nHeight = m_FrameInfoHeader.m_nHeight;
}

void FrameInfoHeader::GetImageOffset(int &nX,int &nY)
{
	nX = m_FrameInfoHeader.m_nOffsetX;
	nY = m_FrameInfoHeader.m_nOffsetY;
}

/** ȡ��ͼƬ����
@param   
@param   
@return  
*/
xs::Stream * FrameInfoHeader::GetImageData(int &nImageSize)
{
	nImageSize = m_FrameInfoHeader.m_nImageSize;

	return &m_streamImageData;
}