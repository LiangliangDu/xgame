/*******************************************************************
** �ļ���:	e:\CoGame\2DEntityEditor\2DEntityEditor\PacketFormat.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2007/7/24  15:54
** ��  ��:	1.0
** ��  ��:	����ʽ
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#include "stdafx.h"
#include "PacketFormat.h"


/** ���캯��
@param   
@param   
@return  
*/
CAniInfoHeader::CAniInfoHeader(void)
{

}

/** ��
@param   pszMwdFileName ��Ϊ*.mwd�ļ���
@param   
@return  
*/
bool CAniInfoHeader::Open(LPCSTR pszMwdFileName)
{
	memset(&m_AniHeader, 0, sizeof(SAniHeader));
	if(pszMwdFileName == NULL)
	{
		return false;
	}

	xs::Stream * pStreamFile = xs::getFileSystem()->open(pszMwdFileName);
	if(pStreamFile == NULL)
	{		
		return false;
	}

	// �����ļ�����
	int nFileLen = pStreamFile->getLength();

	// ���ļ������Ƿ��С�ڰ��ļ�
	if(nFileLen < sizeof(SAniHeader) - 4/*TILE��Ϣָ�볤��*/)
	{
		pStreamFile->close();
		return false;
	}

	// ��ȡ����ͷ
	int nDataSize = sizeof(SAniHeader) - 4/*TILE��Ϣָ�볤��*/;
	if(!pStreamFile->read(&m_AniHeader, nDataSize))
	{
		pStreamFile->close();
		return false;
	}

	// ������֤���汾�ţ���ʶ�룩
	if(m_AniHeader.m_dwVersion != (1 << 16 | 1 << 0) || m_AniHeader.m_dwCode != 'WMTL')
	{
		pStreamFile->close();
		return false;
	}

	// ������֤
	if(m_AniHeader.m_nTileW < 0 || m_AniHeader.m_nTileH < 0)
	{	
		pStreamFile->close();
		return false;
	}

	// ��TILE��Ϣ
	DWORD dwTitleSize = m_AniHeader.m_nTileW * m_AniHeader.m_nTileH;
	if(dwTitleSize > 0)
	{
		// ȡ�õ�ǰλ��
		int nCurPos = pStreamFile->getPosition();

		// ���ļ������Ƿ��С��TITLE��Ϣ
		if((nFileLen - nCurPos) < (int)(dwTitleSize * sizeof(DWORD)))
		{
			pStreamFile->close();
			return false;
		}
	}

	m_AniHeader.m_pTileFlag = new DWORD[dwTitleSize];
	pStreamFile->read((uchar*)m_AniHeader.m_pTileFlag,dwTitleSize * sizeof(DWORD));

	// �ر�
	pStreamFile->close();

	return true;
}

/** �ͷ�
@param   
@param   
@return  
*/
void CAniInfoHeader::Release(void)
{
	if(m_AniHeader.m_pTileFlag != NULL)
	{
		SAFE_DELETEARRAY(m_AniHeader.m_pTileFlag);
	}

	delete this;
}

/** �ر�
@param   
@param   
@return  
*/
void CAniInfoHeader::Close(void)
{
	if(m_AniHeader.m_pTileFlag != NULL)
	{
		SAFE_DELETEARRAY(m_AniHeader.m_pTileFlag);
	}
}

/** ê�㵽ͼƬ���Ͻǵ�ƫ��(X,Y)
@param   
@param   
@return  
*/
void CAniInfoHeader::SetAnchorOffset(int nX, int nY)
{
	m_AniHeader.m_nAnchorOffset[0] = nX;
	m_AniHeader.m_nAnchorOffset[1] = nY;
}

/** ê�㵽ͼƬ���Ͻǵ�ƫ��(X,Y)
@param   
@param   
@return  
*/
void CAniInfoHeader::GetAnchorOffset(int &nX, int &nY)
{
	nX = m_AniHeader.m_nAnchorOffset[0];
	nY = m_AniHeader.m_nAnchorOffset[1];
}

/** �����1ƫ��(X,Y)
@param   
@param   
@return  
*/
void CAniInfoHeader::SetSortPoint1(int nX, int nY)
{
	m_AniHeader.m_nSortPoint1[0] = nX;
	m_AniHeader.m_nSortPoint1[1] = nY;
}

/** �����1ƫ��(X,Y)
@param   
@param   
@return  
*/
void CAniInfoHeader::GetSortPoint1(int &nX, int &nY)
{
	nX = m_AniHeader.m_nSortPoint1[0];
	nY = m_AniHeader.m_nSortPoint1[1];
}

/** �����2ƫ��(X,Y)
@param   
@param   
@return  
*/
void CAniInfoHeader::SetSortPoint2(int nX, int nY)
{
	m_AniHeader.m_nSortPoint2[0] = nX;
	m_AniHeader.m_nSortPoint2[1] = nY;
}

/** �����2ƫ��(X,Y)
@param   
@param   
@return  
*/
void CAniInfoHeader::GetSortPoint2(int &nX, int &nY)
{
	nX = m_AniHeader.m_nSortPoint2[0];
	nY = m_AniHeader.m_nSortPoint2[1];
}

/**  TILE�����Ͻ������ê���TILEƫ��
@param   
@param   
@return  
*/
void CAniInfoHeader::SetTileOffset(int nX, int nY)
{
	m_AniHeader.m_nTileOffset[0] = nX;
	m_AniHeader.m_nTileOffset[1] = nY;
}

/**  TILE�����Ͻ������ê���TILEƫ��
@param   
@param   
@return  
*/
void CAniInfoHeader::GetTileOffset(int &nX, int &nY)
{
	nX = m_AniHeader.m_nTileOffset[0];
	nY = m_AniHeader.m_nTileOffset[1];
}

/** Tileռλ����
@param   
@param   
@return  
*/
void CAniInfoHeader::SetTileSize(int nW, int nH)
{
	m_AniHeader.m_nTileW = nW;
	m_AniHeader.m_nTileH = nH;
}

/** Tileռλ����
@param   
@param   
@return  
*/
void CAniInfoHeader::GetTileSize(int &nW, int &nH)
{
	nW = m_AniHeader.m_nTileW;
	nH = m_AniHeader.m_nTileH;
}

/** ����Tile��Ϣ
@param   
@param   
@return  
*/
void CAniInfoHeader::SetTileInfor(DWORD * pTileInfor)
{
	if(m_AniHeader.m_pTileFlag != NULL)
	{
		SAFE_DELETEARRAY(m_AniHeader.m_pTileFlag);
	}

	if(pTileInfor != NULL)
	{
		m_AniHeader.m_pTileFlag = new DWORD [m_AniHeader.m_nTileW * m_AniHeader.m_nTileH];	
		memcpy(m_AniHeader.m_pTileFlag, pTileInfor, sizeof(DWORD) * m_AniHeader.m_nTileW * m_AniHeader.m_nTileH);
	}
}

/** ȡ��tile��Ϣ
@param   
@param   
@return  
*/
DWORD *	CAniInfoHeader::GetTileInfor(void)
{
	return m_AniHeader.m_pTileFlag;
}

/** ��ͼƬ���Ͻ���������
@param   
@param   
@return  
*/
void CAniInfoHeader::SetDrawAniPixel(int nX, int nY)
{
	m_AniHeader.m_nDrawAniPixel[0] = nX;
	m_AniHeader.m_nDrawAniPixel[1] = nY;
}

/** ��ͼƬ���Ͻ���������
@param   
@param   
@return  
*/
void CAniInfoHeader::GetDrawAniPixel(int &nX, int &nY)
{
	nX = m_AniHeader.m_nDrawAniPixel[0];
	nY = m_AniHeader.m_nDrawAniPixel[1];
}