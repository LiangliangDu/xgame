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
#pragma once

#include "stdio.h"

#pragma pack(1)

// ÿ��Ŀ¼��ɢ�ļ�����
#define DIR_MAX_FILE_COUNT				256

// �������ʱ
#define ANI_MAX_DELAY					600000

// ����ʶ����ַ�
#define PACKCAPTION_MAX_LEN				32

// �Ƿ�����
#ifndef INVALID_COORDINATE
	#define INVALID_COORDINATE			-9999999
#endif

///////////////////////////////////////////////////////////////////
// ������
enum
{
	PACKTYPE_UNKNOW = 0,								// δ֪��
	PACKTYPE_ANI,										// ������
	PACKTYPE_MAX,										// �����
};


///////////////////////////////////////////////////////////////////
// ��������Ϣͷ
class CAniInfoHeader
{
public:
	struct SAniHeader
	{
		DWORD				m_dwVersion;				// �汾(ǰ16�ֽ�Ϊ���汾����16�ֽ�Ϊ���汾)
		DWORD				m_dwCode;					// ��ʶ��		
		DWORD				m_dwCompress;				// ѹ����־
		DWORD				m_dwEncrypt;				// ���ܱ�־
		char				m_szReserve[128];			// �����ֽ�

		int					m_nDrawAniPixel[2];			// ��ͼƬ���Ͻ���������(X,Y)(����Ϸ�в������ã�ֻ���ڹ����У�
		int					m_nAnchorOffset[2];			// ê�㵽ͼƬ���Ͻǵ�����ƫ��(X,Y)
		int					m_nSortPoint1[2];			// �����1�����ê���TILEƫ��(X,Y)
		int					m_nSortPoint2[2];			// �����2�����ê���TILEƫ��(X,Y)
		int					m_nTileOffset[2];			// TILE�����Ͻ������ê���TILEƫ��(X,Y)
		int					m_nTileW;					// X�����ռλ����
		int					m_nTileH;					// Y�����ռλ����
		int					m_iImageMaxWidth;			//ͼƬ�����
		int					m_iImageMaxHeight;			//ͼƬ���߶�

		DWORD *				m_pTileFlag;				// TILE��Ϣ(�˴�С�������ļ�����)	

		SAniHeader(void)
		{
			memset(this, 0, sizeof(SAniHeader));

			// ��ʶ��
			m_dwCode = 'WMTL';

			// �汾(ǰ16�ֽ�Ϊ���汾����16�ֽ�Ϊ���汾)
			m_dwVersion = (1 << 16 | 1 << 0);

			// ��ͼƬ���Ͻ���������(X,Y)
			m_nDrawAniPixel[0] = INVALID_COORDINATE;
			m_nDrawAniPixel[1] = INVALID_COORDINATE;

			// ê�㵽ͼƬ���Ͻǵ�����ƫ��(X,Y)
			m_nAnchorOffset[0] = INVALID_COORDINATE;
			m_nAnchorOffset[1] = INVALID_COORDINATE;

			// �����1�����ê���TILEƫ��(X,Y)
			m_nSortPoint1[0] = INVALID_COORDINATE;
			m_nSortPoint1[1] = INVALID_COORDINATE;

			// �����2�����ê���TILEƫ��(X,Y)
			m_nSortPoint2[0] = INVALID_COORDINATE;
			m_nSortPoint2[1] = INVALID_COORDINATE;

			// TILE�����Ͻ������ê���TILEƫ��(X,Y)
			m_nTileOffset[0] = INVALID_COORDINATE;
			m_nTileOffset[1] = INVALID_COORDINATE;
		}
	};

public:
	/** ��
	@param   pszMwdFileName ��Ϊ*.mwd�ļ���
	@param   
	@return  
	*/
	bool					Open(LPCSTR pszMwdFileName);

	/** �ͷ�
	@param   
	@param   
	@return  
	*/
	void					Release(void);

	/** �ر�
	@param   
	@param   
	@return  
	*/
	void					Close(void);

	/** ê�㵽ͼƬ���Ͻǵ�ƫ��(X,Y)
	@param   
	@param   
	@return  
	*/
	void					SetAnchorOffset(int nX, int nY);

	/** ê�㵽ͼƬ���Ͻǵ�ƫ��(X,Y)
	@param   
	@param   
	@return  
	*/
	void					GetAnchorOffset(int &nX, int &nY);

	/** �����1ƫ��(X,Y)
	@param   
	@param   
	@return  
	*/
	void					SetSortPoint1(int nX, int nY);

	/** �����1ƫ��(X,Y)
	@param   
	@param   
	@return  
	*/
	void					GetSortPoint1(int &nX, int &nY);

	/** �����2ƫ��(X,Y)
	@param   
	@param   
	@return  
	*/
	void					SetSortPoint2(int nX, int nY);

	/** �����2ƫ��(X,Y)
	@param   
	@param   
	@return  
	*/
	void					GetSortPoint2(int &nX, int &nY);

	/**  TILE�����Ͻ������ê���TILEƫ��
	@param   
	@param   
	@return  
	*/
	void					SetTileOffset(int nX, int nY);

	/**  TILE�����Ͻ������ê���TILEƫ��
	@param   
	@param   
	@return  
	*/
	void					GetTileOffset(int &nX, int &nY);	

	/** Tileռλ����
	@param   
	@param   
	@return  
	*/
	void					SetTileSize(int nW, int nH);

	/** Tileռλ����
	@param   
	@param   
	@return  
	*/
	void					GetTileSize(int &nW, int &nH);

	/** ����Tile��Ϣ
	@param   
	@param   
	@return  
	*/
	void					SetTileInfor(DWORD * pTileInfor);

	/** ȡ��tile��Ϣ
	@param   
	@param   
	@return  
	*/
	DWORD *					GetTileInfor(void);

	/** ��ͼƬ���Ͻ���������
	@param   
	@param   
	@return  
	*/
	void					SetDrawAniPixel(int nX, int nY);

	/** ��ͼƬ���Ͻ���������
	@param   
	@param   
	@return  
	*/
	void					GetDrawAniPixel(int &nX, int &nY);	

	int						GetImageMaxWidth() { return m_AniHeader.m_iImageMaxWidth;}
	int						GetImageMaxHeight() { return m_AniHeader.m_iImageMaxHeight;}

	/** ���캯��
	@param   
	@param   
	@return  
	*/
	CAniInfoHeader(void);

private:
	// ����ͷ
	SAniHeader				m_AniHeader;
};


#pragma pack()