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
#pragma once

// �������tile���루��
#define MAX_DISTANCE_WIDTH		512

// �������tile���루�ߣ�
#define MAX_DISTANCE_HIGH		512

// ����
class CCountDistance
{
public:
	/** ����
	@param   
	@param   
	@return  
	*/
	int			Distance(const xs::Point& ptTile1, const xs::Point& ptTile2);

	/** 
	@param   
	@param   
	@return  
	*/
	CCountDistance(void);

	/** 
	@param   
	@param   
	@return  
	*/
	virtual ~CCountDistance(void);

private:
	// �Ѽ���õľ���
	ushort			m_nDistance[MAX_DISTANCE_WIDTH][MAX_DISTANCE_HIGH];
};