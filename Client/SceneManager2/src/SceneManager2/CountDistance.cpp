/*******************************************************************
** �ļ���:	e:\Rocket\Server\ZoneManager\Src\CountDistance.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2008/1/29  10:34
** ��  ��:	1.0
** ��  ��:	��������tile�ľ���
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#include "StdAfx.h"
#include <math.h>
#include "DGlobalGame.h"
#include "CountDistance.h"

/** 
@param   
@param   
@return  
*/
CCountDistance::CCountDistance(void)
{
	// ���� |x1-x2|��ƽ����|y1-y2|��ƽ�����ٽ�����Ϳ������͵���AB�ľ���
	for(int nW = 0; nW < MAX_DISTANCE_WIDTH; nW++)
	{
		for(int nH = 0; nH < MAX_DISTANCE_HIGH; nH++)
		{
			m_nDistance[nW][nH]= (ushort)(sqrt(pow((double)nW, 2) + pow((double)nH, 2)) + 0.5);	
		}
	}
}

/** 
@param   
@param   
@return  
*/
CCountDistance::~CCountDistance(void)
{

}

/** ����
@param   
@param   
@return  
*/
int	CCountDistance::Distance(const POINT& ptTile1, const POINT& ptTile2)
{
	int nW = abs(ptTile1.x - ptTile2.x);
	int nH = abs(ptTile1.y - ptTile2.y);	

	if((nW >= MAX_DISTANCE_WIDTH) || ( nH >= MAX_DISTANCE_HIGH))
	{
		return INVALID_DISTANCE;
	}

	return m_nDistance[nW][nH];
}

CCountDistance	g_countDistance;