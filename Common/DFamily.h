/*******************************************************************
** �ļ���:	DFamily.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2011/02/17  14:00
** ��  ��:	1.0
** ��  ��:	̯λ��Ϣ����
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#ifndef __DFAMILY_H__
#define __DFAMILY_H__
#pragma  once

#include "UserInfoDef.h"

// �����������30��
#define FAMILY_CREATE_LEV_MIN          30 

// ������������1w��
#define FAMILY_CREATE_MONEY_MIN        100000000 

//�������볬ʱ30s
#define FAMILY_INVITE_TIMEOUT	       30000 

struct SFamilyCreateContent
{
	dbid dbidCreate;									
	char szFamilyName[FAMILY_NAME_LEN + 1];
};

struct SFamilyInfo
{
	dbid dbidLeader;									
	int   nLevel;     //����ȼ�
	DWORD dwCamp;      //������Ӫ
	char szFamilyName[FAMILY_NAME_LEN + 1];
	SFamilyInfo()
	{
		memset(this, 0, sizeof(SFamilyInfo));
	}
};

// �����Ա��Ϣ
struct SFamilyMemberInfo
{
	dbid dbidMember;      // PID
	std::string strName;  // ����
	int nProfession;      // ְҵ
	int nLevel;           // �ȼ�
	int nBattlePower;     // ս����
	bool bOnline;
	int nLastOfflineTime;
	SFamilyMemberInfo()
	{
		dbidMember = 0;
		nProfession = 0;
		nLevel = 0;
		nBattlePower = -1;
		bOnline = false;
		nLastOfflineTime = 0;
	}
};

// ��������
#define FamilyMsg_CreateFamily           1 
struct SMsgFamily_CreateFamily_cs
{
	dbid dbidCreate;									
	char szFamilyName[FAMILY_NAME_LEN + 1];
};

// ���¼�����Ϣ
#define FamilyMsg_UpdateFamily           2 
struct SMsgFamily_UpdateFamily_sc
{
	SFamilyInfo familyInfo;
};

#define FamilyMsg_AddMember				3 
struct SMsgFamily_AddMember_sc
{
	dbid dbidLeader;      // PID
	dbid dbidMember;      // PID
	char szName[MAX_PERSONNAME_LEN];  // ����
	int nProfession;      // ְҵ
	int nLevel;           // �ȼ�
	int nBattlePower;     // ս����
	int nLastOfflineTime;
	uchar bOnline;
};

#define FamilyMsg_Result				4
enum EFamilyResult
{
	EFamilyResult_Create  = 1,
};
struct SMsgFamily_Result_ss
{
	int nType;
	int nResult; // 1�ɹ�, 0ʧ��
	DWORD dwParam;
};

#define FamilyMsg_Disband				5
struct SMsgFamily_Disband_ss
{
	dbid dbidLeader;      // PID
};

#define FamilyMsg_RecruitMember			6
struct SMsgFamily_RecruitMember_cs
{
	dbid dbidLeader;      // PID
	char szName[MAX_PERSONNAME_LEN];  // ����
};

#define FamilyMsg_InviteJoin			7
struct SMsgFamily_InviteJoin_sc
{
	dbid dbidInviter;      // PID
	char szInviterName[MAX_PERSONNAME_LEN];  // �峤����
	char szFamilyName[FAMILY_NAME_LEN + 1];  // ��������
};

#define FamilyMsg_ReplyInvite			8
struct SMsgFamily_ReplyInvite_cs
{
	dbid dbidPeroson;      // PID
	dbid dbidInviter;
	int  nResult;          // 1ͬ�⣬0�ܾ�
	int  nBattlePower;
};

#define FamilyMsg_UpdateMember			9

#define FamilyMsg_QuitFamily			10
struct SMsgFamily_QuitFamily_cs
{
	dbid dbidLeader;
	dbid dbidPerson; 
	int  nFireOut;  // ����
};

#define FamilyMsg_Demise				11
struct SMsgFamily_Demise_cs
{
	dbid dbidLeader;
	dbid dbidPerson; 
};

#define FamilyMsg_SetOnline				12
struct SMsgFamily_SetOnline_cs
{
	dbid dbidLeader;
	dbid dbidPerson; 
	int  nLastOffLineTime;
	uchar bOnline;
};

#define FamilyMsg_UpdateBattlePower		13
struct SMsgFamily_UpdateBattlePower_ss
{
	dbid dbidLeader;
	dbid dbidPerson; 
	int  nBattlePower;
};

#define FamilyMsg_QueryBattlePower		14
struct SMsgFamily_QueryBattlePower_ss
{
	dbid dbidLeader;
	dbid dbidPerson; 
};

#define FamilyMsg_TimeStamp				15
struct SMsgFamily_TimeStamp_sc
{
	ulong uTS; //32λ�޷��������Ա���136���ʱ����(����2106��)
};

#define FamilyMsg_JoinArmy				16
struct SMsgFamily_JoinArmy_ss
{
	dbid dbidFamilyLeader;
	dbid dbidArmyLeader;
};
#endif //__DFAMILY_H__