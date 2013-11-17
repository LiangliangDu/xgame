//==========================================================================
/**
* @file	  : Direction.h
* @author : 
* created : 2008-1-29   17:05
* purpose : ������ؼ���
*/
//==========================================================================

#ifndef __DIRECTION_H__
#define __DIRECTION_H__

#include <math.h>

/// ���ǵ���3D����ϵ���ݣ�����Ӷ��Ϸ���ʼ����ʱ�뷽�����
enum
{
	/// ����
	eEastSouth,

	/// ����
	eEast,

	/// ����
	eEastNorth,

	/// ����
	eNorth,

	/// ����
	eWestNorth,

	/// ����
	eWest,

	/// ����
	eWestSouth,

	/// �Ϸ�
	eSouth,

	eDirectionCount
};

#if 0
//	+	|  -
//	3	|  4
// ------------> x
//	2	|  1
//	-	|  +
//		v  y
// �����һ���㵽��һ����ķ���(ʹ����Ļ����)
template<class T>
int calcDir8_ex(const T& ptFrom, const T& ptTo)
{
	int nDeltaX = ptTo.x - ptFrom.x;
	int nDeltaY = ptTo.y - ptFrom.y;
	if (nDeltaX > 0)
	{
		if (nDeltaY > 0)		return eEastSouth;
		else if (nDeltaY < 0)	return eEastNorth;
		else					return eEast;
	}
	else if (nDeltaX < 0)
	{
		if (nDeltaY > 0)		return eWestSouth;
		else if (nDeltaY < 0)	return eWestNorth;
		else					return eWest;
	}
	else
	{
		if (nDeltaY > 0)		return eSouth;
		else					return eNorth;
	}
	return eEastSouth;
}
#endif

// �����һ���㵽��һ����ķ���(ʹ��TILE����)���ʺ�8������·��
template<class T>
ulong calcDir8_tile(const T& ptFrom, const T& ptTo)
{
	long nDeltaX = ptTo.x - ptFrom.x;
	long nDeltaY = ptTo.y - ptFrom.y;

	if (nDeltaX > 0)
	{
		if (nDeltaY > 0)		return eEast;
		else if (nDeltaY < 0)	return eSouth;
		else					return eEastSouth;
	}
	else if (nDeltaX < 0)
	{
		if (nDeltaY > 0)		return eNorth;
		else if (nDeltaY < 0)	return eWest;
		else					return eWestNorth;
	}
	else
	{
		if (nDeltaY > 0)		return eEastNorth;
		else					return eWestSouth;
	}
	return eEastSouth;
}
//      ^  y
//	-	|  +
//	2	|  1
// ------------> x
//	3	|  4
//	+	|  -
// ���ݷ�Χ����ģ��ȷ��(tile����)
template<class T>
int calcDir8_tile_ex(const T& ptFrom, const T& ptTo)
{
	int nDeltaX = ptTo.x - ptFrom.x;
	int nDeltaY = ptTo.y - ptFrom.y;
	float fSlope; // б��
	if (nDeltaX == 0)
		return (nDeltaY >= 0) ? eEastNorth : eWestSouth;
	else
		fSlope = (float)nDeltaY/nDeltaX;

	if (fSlope >= 0.0f) // 1,3����
	{
		if (nDeltaX >= 0) // 1
		{
			if (fSlope >= 2.414f)	return  eEastNorth; // 90	(67.5��90.0) < tan(67.5) = 2.414 >
			if (fSlope >= 0.414f)	return  eEast; // 45	(22.5��67.5) < tan(22.5) = 0.414 >
			if (fSlope >=   0.0f)	return  eEastSouth; // 0		(00.0��22.5)
		}
		else // 3
		{
			if (fSlope >= 2.414f)	return eWestSouth;
			if (fSlope >= 0.414f)	return eWest;
			if (fSlope >=   0.0f)	return eWestNorth;
		}
	}
	else // 2,4
	{
		fSlope = -fSlope;
		if (nDeltaX >= 0) // 4
		{
			if (fSlope >= 2.414f)	return  eWestSouth;
			if (fSlope >= 0.414f)	return  eSouth;
			if (fSlope >=   0.0f)	return  eEastSouth;
		}
		else // 2
		{
			if (fSlope >= 2.414f)	return eEastNorth;
			if (fSlope >= 0.414f)	return eNorth;
			if (fSlope >=   0.0f)	return eWestNorth;		
		}
	}
	return eEastSouth;
}
// �����һ���㵽��һ����ķ�������Ӧ�ĽǶ�(ʹ��TILE����)���ʺ���·��
template<class T>
long calcAngle8_tile(const T& ptFrom, const T& ptTo)
{
	long nDeltaX = ptTo.x - ptFrom.x;
	long nDeltaY = ptTo.y - ptFrom.y;
	if (nDeltaX > 0)
	{
		if (nDeltaY > 0)		return 45;//eEast
		else if (nDeltaY < 0)	return 315;//eSouth
		else					return 0;//eEastSouth
	}
	else if (nDeltaX < 0)
	{
		if (nDeltaY > 0)		return 135;//eNorth
		else if (nDeltaY < 0)	return 225;//eWest
		else					return 180;//eWestNorth
	}
	else
	{
		if (nDeltaY > 0)		return 90;//eEastNorth
		else					return 270;//eWestSouth
	}
	return 0;//eEastSouth
}

/// ���ݽǶ�[0,360)��ȡ��ӽ���TILE����(8����)
inline ulong angle2Dir(ulong angle)
{
	float an = (float)angle;
	if (an > 337.5f) return eEastSouth;
	else if (an > 292.5f) return eSouth;
	else if (an > 247.5f) return eWestSouth;
	else if (an > 202.5f) return eWest;
	else if (an > 157.5f) return eWestNorth;
	else if (an > 112.5f) return eNorth;
	else if (an > 67.5f) return eEastNorth;
	else if (an > 22.5f) return eEast;
	return eEastSouth;
}

// ���ݵѿ�������ϵ����Ƕȣ�����ֵ��ΧΪ[0,360)
template<class T>
long calcAngle_descartes(const T& ptFrom, const T& ptTo)
{
	long angle = 0;
	long dx = ptTo.x - ptFrom.x;
	long dy = ptTo.y - ptFrom.y;
	if (dx > 0)			// 1,4����
		angle = (long)Math::ATan((float)dy/dx).valueDegrees();
	else if (dx < 0)	// 2,3����
		angle = 180 + (long)Math::ATan((float)dy/dx).valueDegrees();
	else if (dx == 0)
		angle= dy > 0 ? 90 : 270;
	else if (dy == 0)
		angle = dx > 0 ? 0 : 180;

	while (angle < 0) angle += 360;
	while (angle >= 360) angle -= 360;

	return angle;
}

#ifdef __Vector3_H__
inline long calcAngle_space(const Vector3& spaceFrom, const Vector3& spaceTo)
{
    xs::Point ptFrom( spaceFrom.z, spaceFrom.x);
    xs::Point ptTo	( spaceTo.z, spaceTo.x);
	return calcAngle_descartes(ptFrom, ptTo);
}
#endif

#if 0
//	+	|  -
//	3	|  4
// ------------> x
//	2	|  1
//	-	|  +
//		v  y
// ���ݷ�Χ����ģ��ȷ��(�ѿ����ӽǣ�����45����б��Ӱ��)
template<class T>
int calcDir8(const T& ptFrom, const T& ptTo)
{
	int nDeltaX = ptTo.x - ptFrom.x;
	int nDeltaY = ptTo.y - ptFrom.y;
	float fSlope; // б��
	if (nDeltaX == 0)
		return (nDeltaY >= 0) ? eSouth : eNorth;
	else
		fSlope = (float)nDeltaY/nDeltaX;

	if (fSlope >= 0.0f) // 1,3����
	{
		if (nDeltaX >= 0) // 1
		{
			if (fSlope >= 2.414f)	return  eSouth; // 90	(67.5��90.0) < tan(67.5) = 2.414 >
			if (fSlope >= 0.414f)	return  eEastSouth; // 45	(22.5��67.5) < tan(22.5) = 0.414 >
			if (fSlope >=   0.0f)	return  eEast; // 0		(00.0��22.5)
		}
		else // 3
		{
			if (fSlope >= 2.414f)	return eNorth;
			if (fSlope >= 0.414f)	return eWestNorth;
			if (fSlope >=   0.0f)	return eWest;
		}
	}
	else // 2,4
	{
		fSlope = -fSlope;
		if (nDeltaX >= 0) // 4
		{
			if (fSlope >= 2.414f)	return  eNorth;
			if (fSlope >= 0.414f)	return  eEastNorth;
			if (fSlope >=   0.0f)	return  eEast;
		}
		else // 2
		{
			if (fSlope >= 2.414f)	return eSouth;
			if (fSlope >= 0.414f)	return eWestSouth;
			if (fSlope >=   0.0f)	return eWest;		
		}
	}
	return eEastSouth;
}
#endif

//	+	|  -
//	3	|  4
// ------------> x
//	2	|  1
//	-	|  +
//		v  y
// ���ݷ�Χ����ģ��ȷ��(45���ӽ�)
template<class T>
int calcDir8_45(const T& ptFrom, const T& ptTo)
{
	int nDeltaX = ptTo.x - ptFrom.x;
	int nDeltaY = ptTo.y - ptFrom.y;
	float fSlope; // б��
	if (nDeltaX == 0)
		return (nDeltaY >= 0) ? eSouth : eNorth;
	else
		fSlope = (float)nDeltaY/nDeltaX;

	if (fSlope >= 0.0f) // 1,3����
	{
		if (nDeltaX >= 0) // 1
		{
			if (fSlope >= 1.618f)	return  eSouth; // 90
			if (fSlope >= 0.236f)	return  eEastSouth; // 45
			if (fSlope >=  0.0f)	return  eEast; // 0
		}
		else // 3
		{
			if (fSlope >= 1.618f)	return eNorth;
			if (fSlope >= 0.236f)	return eWestNorth;
			if (fSlope >=  0.0f)	return eWest;
		}
	}
	else // 2,4
	{
		fSlope = -fSlope;
		if (nDeltaX >= 0) // 4
		{
			if (fSlope >= 1.618f)	return  eNorth;
			if (fSlope >= 0.236f)	return  eEastNorth;
			if (fSlope >=  0.0f)	return  eEast;
		}
		else // 2
		{
			if (fSlope >= 1.618f)	return eSouth;
			if (fSlope >= 0.236f)	return eWestSouth;
			if (fSlope >=  0.0f)	return eWest;		
		}
	}
	return eEastSouth;
}

#if 0
//	+	|  -
//	3	|  4
// ------------> x
//	2	|  1
//	-	|  +
//		v  y
// ���ݷ�Χ����ģ��ȷ��(�ѿ����ӽǣ�����45����б��Ӱ��)
template<class T>
int calcDir32(const T& ptFrom, const T& ptTo)
{
	int nDeltaX = ptTo.x - ptFrom.x;
	int nDeltaY = ptTo.y - ptFrom.y;
	float fSlope;
	if (nDeltaX == 0)
		return (nDeltaY >= 0) ? 16 : 0;
	else
		fSlope = (float)nDeltaY/nDeltaX;

	if (fSlope >= 0.0f) // 1,3����
	{
		if (nDeltaX >= 0) // 1
		{
			if (fSlope >= 10.153f)	return 16; // 90	(84.375 �� 90.000) < tan(84.375) = 10.153 >
			if (fSlope >=  3.297f)	return 15; // 78.75	(73.125 �� 84.375) < tan(73.125) =  3.297 >
			if (fSlope >=  1.871f)	return 14; // 67.50	(61.875 �� 73.125) < tan(61.875) =  1.871 >
			if (fSlope >=  1.219f)	return 13; // 56.25	(50.625 �� 61.875) < tan(50.625) =  1.219 >
			if (fSlope >=  0.821f)	return 12; // 45.00	(39.375 �� 50.625) < tan(39.375) =  0.821 >
			if (fSlope >=  0.535f)	return 11; // 33.75	(28.125 �� 39.375) < tan(28.125) =  0.535 >
			if (fSlope >=  0.303f)	return 10; // 22.50	(16.875 �� 28.125) < tan(16.875) =  0.303 >
			if (fSlope >=  0.098f)	return  9; // 11.25	(05.625 �� 16.875) < tan(05.625) =  0.098 >
			if (fSlope >=  0.000f)	return  8; // 0		(00.000 �� 05.625) < tan(00.000) =  0.000 >
		}
		else // 3
		{
			if (fSlope >= 10.153f)	return 0;
			if (fSlope >=  3.297f)	return 31;
			if (fSlope >=  1.871f)	return 30;
			if (fSlope >=  1.219f)	return 29;
			if (fSlope >=  0.821f)	return 28;
			if (fSlope >=  0.535f)	return 27;
			if (fSlope >=  0.303f)	return 26;
			if (fSlope >=  0.098f)	return 25;
			if (fSlope >=  0.000f)	return 24;		
		}
	}
	else // 2,4
	{
		fSlope = -fSlope;
		if (nDeltaX >= 0) // 4
		{
			if (fSlope >= 10.153f)	return  0;
			if (fSlope >=  3.297f)	return  1;
			if (fSlope >=  1.871f)	return  2;
			if (fSlope >=  1.219f)	return  3;
			if (fSlope >=  0.821f)	return  4;
			if (fSlope >=  0.535f)	return  5;
			if (fSlope >=  0.303f)	return  6;
			if (fSlope >=  0.098f)	return  7;
			if (fSlope >=  0.000f)	return  8;
		}
		else // 2
		{
			if (fSlope >= 10.153f)	return 16;
			if (fSlope >=  3.297f)	return 17;
			if (fSlope >=  1.871f)	return 18;
			if (fSlope >=  1.219f)	return 19;
			if (fSlope >=  0.821f)	return 20;
			if (fSlope >=  0.535f)	return 21;
			if (fSlope >=  0.303f)	return 22;
			if (fSlope >=  0.098f)	return 23;
			if (fSlope >=  0.000f)	return 24;		
		}
	}
	return 0;
}


//	+	|  -
//	3	|  4
// ------------> x
//	2	|  1
//	-	|  +
//		v  y
// ���ݷ�Χ����ģ��ȷ��(����TILE���ĵ�����,��45����б��Ӱ��)
template<class T>
int calcDir32_45(const T& ptFrom, const T& ptTo)
{
	int nDeltaX = ptTo.x - ptFrom.x;
	int nDeltaY = ptTo.y - ptFrom.y;
	float fSlope;
	if (nDeltaX == 0)
		return (nDeltaY >= 0) ? 16 : 0;
	else
		fSlope = (float)nDeltaY*2/nDeltaX;

	if (fSlope >= 0.0f) // 1,3����
	{
		if (nDeltaX >= 0) // 1
		{
			if (fSlope >= 10.153f)	return 16; // 90	(84.375 �� 90.000) < tan(84.375) = 10.153 >
			if (fSlope >=  3.297f)	return 15; // 78.75	(73.125 �� 84.375) < tan(73.125) =  3.297 >
			if (fSlope >=  1.871f)	return 14; // 67.50	(61.875 �� 73.125) < tan(61.875) =  1.871 >
			if (fSlope >=  1.219f)	return 13; // 56.25	(50.625 �� 61.875) < tan(50.625) =  1.219 >
			if (fSlope >=  0.821f)	return 12; // 45.00	(39.375 �� 50.625) < tan(39.375) =  0.821 >
			if (fSlope >=  0.535f)	return 11; // 33.75	(28.125 �� 39.375) < tan(28.125) =  0.535 >
			if (fSlope >=  0.303f)	return 10; // 22.50	(16.875 �� 28.125) < tan(16.875) =  0.303 >
			if (fSlope >=  0.098f)	return  9; // 11.25	(05.625 �� 16.875) < tan(05.625) =  0.098 >
			if (fSlope >=  0.000f)	return  8; // 0		(00.000 �� 05.625) < tan(00.000) =  0.000 >
		}
		else // 3
		{
			if (fSlope >= 10.153f)	return 0;
			if (fSlope >=  3.297f)	return 31;
			if (fSlope >=  1.871f)	return 30;
			if (fSlope >=  1.219f)	return 29;
			if (fSlope >=  0.821f)	return 28;
			if (fSlope >=  0.535f)	return 27;
			if (fSlope >=  0.303f)	return 26;
			if (fSlope >=  0.098f)	return 25;
			if (fSlope >=  0.000f)	return 24;		
		}
	}
	else // 2,4
	{
		fSlope = -fSlope;
		if (nDeltaX >= 0) // 4
		{
			if (fSlope >= 10.153f)	return  0;
			if (fSlope >=  3.297f)	return  1;
			if (fSlope >=  1.871f)	return  2;
			if (fSlope >=  1.219f)	return  3;
			if (fSlope >=  0.821f)	return  4;
			if (fSlope >=  0.535f)	return  5;
			if (fSlope >=  0.303f)	return  6;
			if (fSlope >=  0.098f)	return  7;
			if (fSlope >=  0.000f)	return  8;
		}
		else // 2
		{
			if (fSlope >= 10.153f)	return 16;
			if (fSlope >=  3.297f)	return 17;
			if (fSlope >=  1.871f)	return 18;
			if (fSlope >=  1.219f)	return 19;
			if (fSlope >=  0.821f)	return 20;
			if (fSlope >=  0.535f)	return 21;
			if (fSlope >=  0.303f)	return 22;
			if (fSlope >=  0.098f)	return 23;
			if (fSlope >=  0.000f)	return 24;		
		}
	}
	return 0;
}
#endif

#endif // __DIRECTION_H__