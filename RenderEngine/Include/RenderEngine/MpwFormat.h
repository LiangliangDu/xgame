/*******************************************************************
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

// ����ʶ����ַ�
#define __PACKCAPTION_MAX_LEN				32
///////////////////////////////////////////////////////////////////
// ���ļ�ͷ
class PackFileHeader	
{
	struct SPackFileHeader
	{
		DWORD				m_dwVersion;				// �汾(ǰ16�ֽ�Ϊ���汾����16�ֽ�Ϊ���汾)
		//char				m_szCaption[__PACKCAPTION_MAX_LEN];// ��ʶ��
		DWORD				m_dwCode;					// ��ʶ��
		DWORD				m_dwPackType;				// ������
		DWORD				m_dwCompress;				// ѹ����־��ѹ��ֻ��ѹ�����ļ�ͷ������ݣ�
		DWORD				m_dwEncrypt;				// ���ܱ�־������ֻ����ܰ��ļ�ͷ������ݣ�
		
		char				m_szFileFormat[8];			// �ļ���ʽ
		DWORD				m_dwTotalFrame;				// �ܹ�����֡��
		DWORD				m_dwPlayDelay;				// ����������ʱ

		DWORD				m_dwZipLen;					// ����Zip����
		//char				m_szReserve[128];			// �����ֽ� m_ptViewPortOffset(����Ϸ�в������ã�ֻ���ڹ����У�

		SPackFileHeader(void)
		{
			memset(this, 0, sizeof(SPackFileHeader));

			// �����ʼ��
			m_dwPlayDelay = 30;
		}
	};
public:
	/** �� 
	@param   
	@param   
	@return  
	*/
	bool					Open(xs::Stream * pStream);

	/** ����ѹ����־
	@param   
	@param   
	@return  
	*/
	void					SetCompressFlag(DWORD dwFlag);

	/** ȡ��ѹ����־
	@param   
	@param   
	@return  
	*/
	DWORD					GetCompressFlag(void);

	/** ���ü��ܱ�־
	@param   
	@param   
	@return  
	*/
	void					SetEncryptFlag(DWORD dwFlag);

	/** ȡ�ü��ܱ�־
	@param   
	@param   
	@return  
	*/
	DWORD					GetEncryptFlag(void);

	/** ���ñ�ʶ��
	@param   
	@param   
	@return  
	*/
	void					SetPackCaption(LPCSTR pszCaption);

	/** ȡ�ñ�ʶ��
	@param   
	@param   
	@return  
	*/
	LPCSTR					GetPackCaption(void);

	/** ���ð�����
	@param   
	@param   
	@return  
	*/
	void					SetPackType(DWORD dwPackType);

	/** ��ð�����
	@param   
	@param   
	@return  
	*/
	DWORD					GetPackType(void);	

	/** ���ú���Zip����
	@param   
	@param   
	@return  
	*/
	void					SetZipLen(DWORD dwZipLen);

	/** ��ú���Zip����
	@param   
	@param   
	@return  
	*/
	DWORD					GetZipLen(void);	

	/** ȡ�ýṹ��С
	@param   
	@param   
	@return  
	*/
	int						GetStructSize(void);

	/** ȡ�ñ����ֽ�
	@param   
	@param   
	@return  
	*/
	char *					GetReserve(void);

	/** ���ñ����ֽ�
	@param   
	@param   
	@return  
	*/
	void					SetReserve(char * pszReserve, int nLen);

	/** �ļ���ʽ
	@param   
	@param   
	@return  
	*/
	void					SetFileFormat(LPCSTR szFileFormat);

	/** �ļ���ʽ
	@param   
	@param   
	@return  
	*/
	LPCSTR					GetFileFormat(void);

	/** �ܶ���֡��
	@param   
	@param   
	@return  
	*/
	void					SetTotalFrame(DWORD dwTotalFrame);

	/** �ܶ���֡��
	@param   
	@param   
	@return  
	*/
	DWORD					GetTotalFrame(void);

	/** ����������ʱ
	@param   
	@param   
	@return  
	*/
	void					SetPlayDelay(DWORD dwPlayDelay);

	/** ����������ʱ
	@param   
	@param   
	@return  
	*/
	DWORD					GetPlayDelay(void);

	/** ���캯��
	@param   
	@param   
	@return  
	*/
	PackFileHeader(void);	

private:
	// ���ļ�ͷ
	SPackFileHeader			m_PackFileHeader;
};

///////////////////////////////////////////////////////////////////
// ������ÿһ֡����
class FrameInfoHeader
{
private:
	struct SFrameInfoHeader
	{
		int					m_nImageSize;				// ͼƬ���ݴ�С
		short				m_nWidth;					// ͼƬ��
		short				m_nHeight;					// ͼƬ��
		short				m_nOffsetX;
		short				m_nOffsetY;

		SFrameInfoHeader(void)
		{
			memset(this, 0, sizeof(SFrameInfoHeader));
		}
	};	

public:
	/** ��
	@param   
	@param   
	@return  
	*/
	bool					Open(xs::Stream * pStream);

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

	/** ����ͼƬ��С
	@param   
	@param   
	@return  
	*/
	void					SetImageSize(int nWidth, int nHeight);

	/** ȡ��ͼƬ��С
	@param   
	@param   
	@return  
	*/
	void					GetImageSize(int &nWidth, int &nHeight);

	void					GetImageOffset(int &nX,int &nY);

	/** ȡ��ͼƬ����
	@param   
	@param   
	@return  
	*/
	xs::Stream *			GetImageData(int &nImageSize);

	/** ���캯��
	@param   
	@param   
	@return  
	*/
	FrameInfoHeader(void);

private:
	// ����ͷ
	SFrameInfoHeader		m_FrameInfoHeader;

	// ͼƬ����
	xs::MemoryStream		m_streamImageData;

public:
	FrameInfoHeader(const FrameInfoHeader& f)
	{
		*this = f;
	}
};

#pragma pack()