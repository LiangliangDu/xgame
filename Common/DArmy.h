/*******************************************************************
** �ļ���:	DArmy.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2011/06/16  14:00
** ��  ��:	1.0
** ��  ��:	������ض���
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#ifndef __DARMY_H__
#define __DARMY_H__
#pragma  once

#include "UserInfoDef.h"


// ������������100��
#define ARMY_CREATE_MONEY_MIN        1000000

struct SArmyInfo
{
	dbid dbidLeader;									
	char szName[ARMY_NAME_LEN + 1];
	SArmyInfo()
	{
		memset(this, 0, sizeof(SArmyInfo));
	}
};

// ���ų�Ա��Ϣ
struct SArmyMemberInfo
{
	dbid dbidMember;      // PID
	std::string strName;  // ����
	int nProfession;      // ְҵ
	int nLevel;           // �ȼ�
	dbid dbidFamilyLeader; //�����峤PID
	std::string strFamilyName;  // ��������
	bool bOnline;
	int nLastOfflineTime;
	SArmyMemberInfo()
	{
		dbidMember = 0;
		nProfession = 0;
		nLevel = 0;
		dbidFamilyLeader = 0;
		bOnline = false;
		nLastOfflineTime = 0;
	}
};

// ��������
#define ArmyMsg_Create           1 
struct SMsgArmy_Create_cs
{
	dbid dbidPerson;									
	char szArmyName[ARMY_NAME_LEN + 1];
	bool bSubmit;
	SMsgArmy_Create_cs()
	{
		memset(this, 0, sizeof(SMsgArmy_Create_cs));
	}
};

#define ArmyMsg_CreateResult    2
struct SMsgArmy_CreateResult_sc
{
	short result;
	char szArmyName[ARMY_NAME_LEN + 1];
};

#define ArmyMsg_UpdateArmyInfo 3
struct SMsgArmy_UpdateArmyInfo
{
	SArmyInfo armyInfo;
};

#define ArmyMsg_AddMember      4
struct SMsgArmy_AddMember
{
	SArmyMemberInfo memberInfo;
};

#endif //__DARMY_H__