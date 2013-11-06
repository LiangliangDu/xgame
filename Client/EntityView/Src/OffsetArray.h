//==========================================================================
/**
* @file	  : OffsetArray.h
* @author : 
* created : 2008-2-16   12:43
* purpose : һЩTILEƫ�Ƶ�����Ķ���
*/
//==========================================================================

#ifndef __OFFSETARRAY_H__
#define __OFFSETARRAY_H__

#include "Direction.h"



enum {Sector3_Size=21, FrontRect_5_6_Size=30, FrontRect_5_9_Size=46};

struct TileOffset
{
	char x,y;
};

/// �뾶Ϊ3��Բ��
//extern const TileOffset arrOffsetCircle3[Cricle3_Size];

/// �뾶Ϊ4��Բ��
//extern const TileOffset arrOffsetCircle4[Cricle4_Size];

/// �뾶Ϊ3��12��Բ��
extern const TileOffset* arrOffsetCircle[13];
extern const ulong arrSizeCircle[13];

/// 8�����Ͼ���Ϊ3������
extern const TileOffset arrOffsetSector3[eDirectionCount][Sector3_Size];

/// 8��������ǰ5*6�ľ���
extern const TileOffset arrOffsetFrontRect_5_6[eDirectionCount][FrontRect_5_6_Size];

/// 8��������ǰ5*9�ľ���
extern const TileOffset arrOffsetFrontRect_5_9[eDirectionCount][FrontRect_5_9_Size];

/// 8�����ϵ�����ƫ��
extern const TileOffset arrOffsetRadial[eDirectionCount];

/// 8�����Ͽ��Ϊ3�����߳�ʼ��ƫ��
extern const TileOffset arrOffsetRadialOrigin_3[eDirectionCount][3];

/// 8�����Ͽ��Ϊ5�����߳�ʼ��ƫ��
extern const TileOffset arrOffsetRadialOrigin_5[eDirectionCount][5];

#endif // __OFFSETARRAY_H__
