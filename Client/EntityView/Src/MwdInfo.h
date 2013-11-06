//==========================================================================
/**
* @file	  : MwdInfo.h
* @author : 
* created : 2008-6-11   12:39
* purpose : MWD��Ϣ�ۺ��ļ�
*/
//==========================================================================

#ifndef __MWDINFO_H__
#define __MWDINFO_H__

#pragma pack(push)
#pragma pack(1)

/* file format:
------------------
|  MwdInfoHeader |
------------------
|  MwdInfo1      |
|  MwdInfo2      |
|  ......        |
------------------
|  map table     |
------------------
*/

/// ��Ϣ�ļ�ͷ
struct MwdInfoHeader // 32 bytes
{
	ulong	mask;			/// �ļ�ͷ��ʶ�ַ�(INFO)
	ulong	version;		/// �汾��
	ulong	tableOff;		/// ӳ���ƫ�ƣ�����ļ���ʼ����
	ulong	itemCount;		/// ��Ŀ��
};

/// ����С��Tileƫ�Ƶ����ݽṹ
struct TileOff // 2 bytes
{
	char x;
	char y;
};

/// Mwd��Ϣ
struct MwdInfo // 24 bytes
{
	ulong	w;				/// ͼƬ�����(����)
	ulong	h;				/// ͼƬ���߶�(����)
	POINT	anchorOffset;	/// ê�������ͼƬ���Ͻ������ε�ƫ����(����)
	TileOff	sortOffset1;	/// ��һ����㣨���ê��ƫ�ƣ�
	TileOff	sortOffset2;	/// �ڶ�����㣨���ê��ƫ�ƣ�
	TileOff	tileOffset;		/// ռλ������������Ͻ����ê���ƫ��
	uchar	tileWidth;		/// ռλ���������Ŀ�ȣ�x����
	uchar	tileHeight;		/// ռλ���������Ŀ�ȣ�y����

	//uchar	tileInfo[];		/// ռλ����Ϣ
};

/// ӳ�����Ŀ
struct TableItem // 8 bytes
{
	ulong	offset;			/// ���ļ��е�ƫ�ƣ�������ļ�ͷ�������ļ���ʼ����
	size_t	size;			/// ���ݿ��С���ֽ�����
};

#pragma pack(pop)


#endif // __MWDINFO_H__