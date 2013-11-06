//==========================================================================
/**
* @file	  : MapTable.cpp
* @author : 
* created : 2008-3-19   19:17
*/
//==========================================================================

#include "stdafx.h"
#include "MapTable.h"
#include "StateDef.h"
#include "ISchemeCenter.h"

/*
����ģ�ͷ�Ϊ3����mesh����ͷ������ͷ����Ӧ����mesh, ����Ӧ����mesh�������壨�����⣩��Ӧ����mesh��ͷ������ͷ����Ӧ����mesh����Ϊ����toukui������Ӧ����mesh������������lian���������Ӧ����mesh������������shenti��
4) ������һ����mesh���ɣ�����Ϊ����toukui��
*/

static char * sModelMeshNames[MSFCP_MAX+1] =
{
	"shenti",
	"lian",
	"toufa",
	"",
};

const char * getModelMeshName(uint index)
{
	if( index >= MSFCP_MAX) return sModelMeshNames[MSFCP_MAX];
	else return sModelMeshNames[index];
}

//�ƶ���schemecenter
/*
const char * getBindPoint(ulong bp)
{
	static const char * map[EBindPoint_Max] = 
	{
		"",
		"guadian_zuoshou",
		"guadian_youshou",
		"guadian_zuobei",
		"guadian_youbei",
		"guadian_toubu",
		"guangxiao1",
		"guangxiao2",
		"guangxiao3",
		"guangxiao4",
		"guangxiao5",
		"lizi1",
		"lizi2",
		"lizi3",
		"lizi4",
	};
	if( bp >= EBindPoint_Max ) return map[EBindPoint_Min];
	return map[bp];
}
*/