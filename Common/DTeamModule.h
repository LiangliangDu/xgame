/*******************************************************************
** �ļ���:	e:\Rocket\Common\DTeamModule.h
** ��  Ȩ:	(C) 
** ������:	pdata(Forlion Long)��Forlion@126.com��
** ��  ��:	2008/6/4  15:02
** ��  ��:	1.0
** ��  ��:	���ģ�鶨��	
** Ӧ  ��:	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#include "DGlobalGame.h"
#include <list>
#include <vector>
using namespace std;

#pragma pack(1)
/******************************************************************/
///////////////////// ��ӵĹ���ö�ٶ��� ////////////////////////
/******************************************************************/
///////////////////////////////////////////////////////////////////
enum 
{
	TEAMDATA_TEAM_TEAMDEFAULT =0,
	TEAMDATA_TEAM_TEAMTYPE = 1,
	TEAMDATA_TEAM_GOODSALLOTMODE,
	TEAMDATA_TEAM_PETSALLOTMODE,
	TEAMDATA_TEAM_TEAMPRIVATE,
};
enum 
{
	TEAMMODE_TASK = 0,     // ����
	TEAMMODE_ECTYPAL,      // ����
	TEAMMODE_BATTLEFIELD,  // ս��
	TEAMMODE_TOUPGRADE,    // ����
	TEAMMODE_NORMAL,       // ��ͨ
	TEAMMODE_MAXID,        // ���ID  
};
enum
{
	GOODSALLOTMODE_W_FREE = 0, // ��װ����ʰȡ
	GOODSALLOTMODE_G_FREE,     // ��װ����ʰȡ
	GOODSALLOTMODE_B_FREE,     // ��װ����ʰȡ
	GOODSALLOTMODE_P_FREE,     // ��װ����ʰȡ
	GOODSALLOTMODE_ALLFREE,    // ����ʰȡ
	GOODSALLOTMODE_MAXID,   // ���ID  
};
enum
{
	PETALLOTMODE_AVERAGE = 0, // ƽ������
	PETALLOTMODE_FREE,        // ����ʰȡ
	PETALLOTMODE_MAXID,       // ���ID
};

// ö�ٳ��������Ʒ����
enum 
{
	RANDOM_GOODS_DEFAULT = 0,
	RANDOM_GOODS_PET,
	RANDOM_GOODS_GOODS,
	RANDOM_GOODS_EQUIP,
	RANDOM_GOODS_MAX,
};
#define    MAX_TEAMNAME_LEN            20
/******************************************************************/
///////////////////// ��ӵ�װ���鿴�ṹ�嶨�� /////////////////////
/******************************************************************/
// Ŀǰ���˽ṹ��ʱ���������ģ�飬
///////////////////////////////////////////////////////////////////

//װ�����
#	define	MAX_EQUIP_EMBEDGEMS	4
#	define	MAX_EQUIP_BASEBRANDATTRIB	4
#	define	MAX_EQUIP_SMELTSOULATTRIB	5
#	define	MAX_EQUIP_LETTERING	71

struct SEquipmentViewInfo
{
	int  nEquipID;                      // װ��ID
	int  nEquipSmeltSoulLevel;			// ��Ʒ����ǿ���ȼ�
    int  nEquipBind;                    // ��
	int  nEquipEndureCur;               // ��ǰ�;ö�
	int  nEquipEndureMax;               // ����;�
	int  nEquipIsChecked;               // ��Ʒ�Ƿ��Ѿ�����
	int  nEquipBrandBaseLevelID[MAX_EQUIP_BASEBRANDATTRIB];        // ��ƷƷ������ id
	int  nEquipBrandBaseLevelVAL[MAX_EQUIP_BASEBRANDATTRIB];       // ��ƷƷ������ ֵ
	int  nEquipSmeltSoulMileStoneBaseID[MAX_EQUIP_SMELTSOULATTRIB]; // ��Ʒǿ���ȼ���̱�id
	int  nEquipSmeltSoulMileStoneBaseVAL[MAX_EQUIP_SMELTSOULATTRIB];// ��Ʒǿ���ȼ���̱� ֵ
	int  nEquipSlotQTY;					                            // �����
	int  nEquipGemsEmbededNum;     // ��ʯ��Ŀ
	int  nEquipGemsBaseID[MAX_EQUIP_EMBEDGEMS];         // ��Ƕ����ʯ��id
	int  nEquipGemsCombindID;                                 // ��Ϻ������ֵ
    char szLetter[MAX_EQUIP_LETTERING];                 // ����
	SEquipmentViewInfo(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
typedef vector<SEquipmentViewInfo>   TVECTOR_EQUIPMENTVIEWINFO;

/******************************************************************/
///////////////////// ��ӵĹ����ṹ�嶨�� ////////////////////////
/******************************************************************/
///////////////////////////////////////////////////////////////////
struct SMemberInfo
{
	DWORD		dwPDBID;					// pdbid
	DWORD       dwLevel;                    // �ȼ�
	DWORD       dwVocation;                 // ְҵ
	DWORD       dwFightValue;               // ս����
	char		szName[MAX_PERSONNAME_LEN];	// ����
	long		lFaceID;					// ͷ��id
	bool		bOnline;					// �������

	SMemberInfo(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
typedef list<SMemberInfo>	TLIST_MEMBERINFO;

/******************************************************************/
///////////////////////// ��ӵ���Ϣ�붨�� ////////////////////////
// �ϲ����Ϣ��ض���MSG_MODULEID_TEAM
/******************************************************************/
///////////////////////////////////////////////////////////////////
// ��������������
#define	MSG_TEAM_INVITE											1
// ��Ϣ��
struct SMsgTeamInvite_CS
{
	DWORD		dwInvitee;					// ��������
	bool        bInvite;                    // �Ƿ�Ϊ����
	
	SMsgTeamInvite_CS(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

struct SMsgTeamInvite_SO
{
	DWORD		dwInvitee;					// ��������

	char		szName[MAX_PERSONNAME_LEN];	// ������������

	SMemberInfo request;					// ������
    
	bool        bInvite;                    // �����뻹������

	SMsgTeamInvite_SO(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// ��ӵĵδ���Ϣ
#define MSG_TEAM_DIDA											2
// ��Ϣ��
#define DIDATXT_DEFAULTLEN	512
struct SMsgTeamDida_SC
{
	DWORD       dwPBIDRquest;               // ��������PBID
	int			nStayTime;					// ͣ��ʱ��
	char		szHtml[DIDATXT_DEFAULTLEN];	// dida����

	SMsgTeamDida_SC(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

struct SMsgTeamDida_OS
{
	DWORD		dwPDBID;					// ����˭
	DWORD       dwPBIDRquest;               // ��������PBID
	int			nStayTime;					// ͣ��ʱ��
	char		szHtml[DIDATXT_DEFAULTLEN];	// dida����

	SMsgTeamDida_OS(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

///////////////////////////////////////////////////////////////////
// ��������
#define MSG_TEAM_CREATETEAM										3
#define TEAMNAME_LEN	32
// ��Ϣ��
struct SMsgTeamCreateTeam_OS
{
	char        szName[TEAMNAME_LEN];       // ��������
	DWORD		dwTeamID;					// ����ID
	DWORD		dwCaptain;					// �ӳ�UID
	DWORD       dwTeamMode;                 // ��������
	DWORD		dwGoodsAllotMode;			// ��Ʒ����ģʽ
	DWORD       dwPetAllotMode;             // �������ģʽ
	bool         bPrivateOpen;              // ˽��ר������
	SMemberInfo  creater;                   // �����ߵ���Ϣ
	SMsgTeamCreateTeam_OS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
struct SMsgTeamCreateTeam_CS       // �ͻ���-������
{
	char  szName[TEAMNAME_LEN];    // ��������
	DWORD dwCaptain;               // �ӳ�UID
	DWORD dwTeamMode;              // ��������   
	DWORD dwGoodsAllotMode;        // ��Ʒ����ģʽ
	DWORD dwPetAllotMode;          // �������ģʽ
	bool  bPrivateOpen;            // ˽��ר������
	SMsgTeamCreateTeam_CS(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

struct SMsgTeamCreateTeam_SC      // ������-�ͻ���
{
	char  szName[TEAMNAME_LEN];    // ��������
	DWORD dwTeamID;
	DWORD dwCaptain;               // �ӳ�UID
	DWORD dwTeamMode;              // ��������   
	DWORD dwGoodsAllotMode;        // ��Ʒ����ģʽ
	DWORD dwPetAllotMode;          // �������ģʽ
	bool  bPrivateOpen;            // ˽��ר������
	SMsgTeamCreateTeam_SC(void)
	{
		memset(this, 0, sizeof(*this));
	};
};
struct SMsgTeamCreateTeam_SO       // ������-����
{
	char  szName[TEAMNAME_LEN];     // ��������
	DWORD dwCaptain;                // �ӳ�UID
	DWORD dwTeamMode;               // ����ģʽ
	DWORD dwGoodsAllotMode;         // ��Ʒ����ģʽ
	DWORD dwPetAllotMode;           // �������ģʽ
	bool  bPrivateOpen;             // ˽��ר������
	SMemberInfo  creater;           // �����ߵ���Ϣ
	SMsgTeamCreateTeam_SO(void)
	{
		memset(this, 0, sizeof(*this));
	};
};
///////////////////////////////////////////////////////////////////
// ���ٶ���
#define MSG_TEAM_DESTROYTEAM									4
// ��Ϣ��
struct SMsgTeamDestroyTeam_OS
{
	DWORD		dwTeamID;					// ����ID

	SMsgTeamDestroyTeam_OS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// ��Ա�仯
#define MSG_TEAM_CHANGEMEMBER									5
// ��Ϣ��
struct SMsgTeamChangeMember_OS
{
	DWORD		dwTeamID;					// ����ID
	int			nCount;						// ��Ա����
	// nCount * SMemberInfo					// ��Ա����

	SMsgTeamChangeMember_OS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SMsgTeamChangeMember_SC
{
	DWORD		dwTeamID;					// ����ID
	int			nCount;						// ��Ա����
	// nCount * SMemberInfo					// ��Ա����

	SMsgTeamChangeMember_SC(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// �ӳ��仯
#define MSG_TEAM_CHANGECAPTAIN									6
// ��Ϣ��

struct SMsgTeamChangeCaptain_OS
{
	DWORD		dwTeamID;					// ����ID
	DWORD		dwCaptain;					// �ӳ�
	DWORD       dwOldCaptain ;              // ǰ�ζӳ�

	SMsgTeamChangeCaptain_OS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SMsgTeamChangeCaptain_SC
{
	DWORD		dwTeamID;					// ����ID
	DWORD		dwCaptain;					// �ӳ�

	SMsgTeamChangeCaptain_SC(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// ����ģʽ�仯
#define MSG_TEAM_CHANGEALLOTMODE								7
// ��Ϣ��
struct SMsgTeamChangeAllotMode_OS
{
	DWORD		dwTeamID;					// ����ID
	long		lAllotMode;					// ����ģʽ

	SMsgTeamChangeAllotMode_OS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SMsgTeamChangeAllotMode_SC
{
	DWORD		dwTeamID;					// ����ID
	long		lAllotMode;					// ����ģʽ

	SMsgTeamChangeAllotMode_SC(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SMsgTeamChangeAllotMode_CS
{
	long		lAllotMode;					// ����ģʽ

	SMsgTeamChangeAllotMode_CS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SMsgTeamChangeAllotMode_SO
{
	DWORD		dwPDBID;					// �ͻ���PDBID
	long		lAllotMode;					// ����ģʽ

	SMsgTeamChangeAllotMode_SO(void)
	{
		memset(this, 0, sizeof(*this));
	}
};


///////////////////////////////////////////////////////////////////
// ת����Ϣ
#define MSG_TEAM_TRANSMIT										8
// ��Ϣ��
struct SMsgTeamTransmit_OS
{
	DWORD		dwPDBID;					// �ͻ���PDBID
	long		lMsgLen;					// ��Ϣ����
	// ..............						// ��Ϣ����

	SMsgTeamTransmit_OS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// �ͻ��˶Ը�������/���������
#define MSG_TEAM_INVITELINK										9
// ��Ϣ��
struct SMsgTeamInviteLink_SO
{	
	DWORD		dwInviteID;					// ����ID
	bool        bOnTimer;                   // �Ƿ�����Ϊ��������ʱ�ˣ�
	bool		bSelect;					// ͬ��/�ܾ�

	SMemberInfo select;						// ѡ����

	SMsgTeamInviteLink_SO(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// ת��������Ϣ
#define MSG_TEAM_TRANSCHATMESSAGE								10
// ��Ϣ
struct SMsgTeamTransChatMessage_OS
{
	DWORD		dwPDBID;					// PDBID
	int			nChannelType;				// ����Ƶ��
	int			nPos;						// λ��
	int			nChatLen;					// ���ݳ���
	// ...............						// ����	

	SMsgTeamTransChatMessage_OS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// �������
#define  MSG_TEAM_ENTERTEAM										11
// ��Ϣ��
struct SMsgTeamEnterTeam_OS
{
	char        szName[TEAMNAME_LEN];       // ��������
	DWORD		dwPDBID;					// PDBID
	DWORD		dwTeamID;					// ����ID
	DWORD		dwCaptain;					// �ӳ�
	DWORD       dwTeamMode;                 // ��������
	DWORD		dwGoodsAllotMode;			// ��Ʒ����ģʽ
	DWORD       dwPetAllotMode;             // �������ģʽ
	bool        bPrivateOpen;               // ˽��ר������
	

	SMsgTeamEnterTeam_OS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SMsgTeamEnterTeam_SC
{
	char        szName[TEAMNAME_LEN];       // ��������
	DWORD		dwTeamID;					// ����ID
	DWORD		dwCaptain;					// �ӳ�
	DWORD       dwTeamMode;                 // ��������
	DWORD		dwGoodsAllotMode;			// ��Ʒ����ģʽ
	DWORD       dwPetAllotMode;             // �������ģʽ
	bool        bPrivateOpen;               // ˽��ר������
	SMsgTeamEnterTeam_SC(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// �˳�����
#define MSG_TEAM_QUITTEAM										12
// ��Ϣ��
struct SMsgTeamQuitTeam_CS
{
	bool  bLogOut;                          // �Ƿ�Ϊ�����˶�
};

struct SMsgTeamQuitTeam_SO
{
	DWORD		dwPDBID;					// PDBID
	bool        bLogOut;                    // �Ƿ�Ϊ�����˶�
	SMsgTeamQuitTeam_SO(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SMsgTeamQuitTeam_OS
{	
	DWORD		dwPDBID;					// PDBID
	DWORD		dwTeamID;					// ����ID
	bool        bLogOut;                    // �Ƿ�Ϊ�����˶�
	SMsgTeamQuitTeam_OS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SMsgTeamQuitTeam_SC
{
	DWORD		dwPDBID;					// PDBID
	DWORD		dwTeamID;					// ����ID
	bool        bLogOut;					// �Ƿ�Ϊ�����˶�
	SMsgTeamQuitTeam_SC(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// ������Ա
#define MSG_TEAM_DISMISSMEMBER									13
// ��Ϣ��
struct SMsgTeamDismissMember_CS
{
	DWORD		dwPDBID;					// ��������

	SMsgTeamDismissMember_CS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SMsgTeamDismissMember_SO
{
	DWORD		dwCaptain;					// �ӳ�
	DWORD		dwPDBID;					// ��������

	SMsgTeamDismissMember_SO(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// �ͻ��˶�ͶƱ������
#define MSG_TEAM_VOTELINK										14
// ��Ϣ��
struct SMsgTeamVoteLink_SO
{	
	DWORD		dwPDBID;					// �ͻ���
	int			nVoteID;					// ͶƱID
	bool		bSelect;					// ͬ��/�ܾ�	

	SMsgTeamVoteLink_SO(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

///////////////////////////////////////////////////////////////////
// ����Ϊ�ӳ�
#define MSG_TEAM_APPOINTCAPTAIN									15
// ��Ϣ��
struct SMsgTeamAppointCaptain_CS
{
	DWORD		dwPDBID;					// ����˭

	SMsgTeamAppointCaptain_CS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};	

struct SMsgTeamAppointCaptain_SO
{
	DWORD		dwClient;					// �ͻ���
	DWORD		dwPDBID;					// ����˭

	SMsgTeamAppointCaptain_SO(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
///////////////////////////////////////////////////////////////////
// ��������
#define MSG_TEAM_SEARCH                                          16

struct TeamSearchInfo
{
	char  szName[TEAMNAME_LEN];     // ��������
	DWORD dwTeamMode;               // ����ģʽ
	DWORD dwCaptain;                // �ӳ�UID
	char  szCaptainName[MAX_PERSONNAME_LEN];     // �ӳ�����
	int   nCaptainLevel;             // �ӳ��ȼ�
	int   nCaptainVocation;           // �ӳ�ְҵ	
	int   nMemberNum;               // ��Ա����

	// ������Ϣ
	TeamSearchInfo(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
typedef vector<TeamSearchInfo>  TVECTOR_SEARCHINFO;

struct SMsgTeamSearch_CS
{
	DWORD		dwPDBID;					// ������

	SMsgTeamSearch_CS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

struct SMsgTeamSearch_SC
{
	DWORD		dwPDBID;					// ������
	int         nCount;                    // ������Ŀ
	 // ������Ϣ
	SMsgTeamSearch_SC(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
///////////////////////////////////////////////////////////////////
// ����������
#define MSG_TEAM_APPLY                                          17

struct SMsgTeamApply_CS
{
	DWORD		dwPDBID;					// ������
	int         dwCaptain;                  // �ӳ�
	// ������Ϣ
	SMsgTeamApply_CS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
///////////////////////////////////////////////////////////////////

// ���Ӷ�����Ϣ��ѯ
#define  MSG_TEAM_SELFTEAMMSGVIEW                               18
struct SMsgTeamSelfMsgView_CS
{
	DWORD		dwPDBID;					// ������
	DWORD       dwTeamID;                   // ����ID
	bool        bClick;                     // �����ʾ
	// ������Ϣ
	SMsgTeamSelfMsgView_CS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
struct SMsgTeamSelfMsgView_SC
{
	DWORD		dwPDBID;					// ������
	DWORD       dwCaptainID;                // 
	DWORD       dwCaptainArmy;             
	DWORD       dwCaptainHomage;
	bool        bClick;
	int         nCount;
	// ������Ϣ
	SMsgTeamSelfMsgView_SC(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
///////////////////////////////////////////////////////////////////

// ����ӳ�
#define  MSG_TEAM_FOLLOWCAPTAIN                               19
struct SMsgTeamFollowCaptain_CS
{
	DWORD		dwPDBID;					// ������
	DWORD       dwTeamID;                   // ����ID
	// ������Ϣ
	SMsgTeamFollowCaptain_CS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
struct SMsgTeamFollowCaptain_SC
{
	DWORD		dwPDBID;					// ������
	LONGLONG    lCaptainUID;                // �ӳ�UID
	DWORD       dwTeamID;                   // ����ID
	// ������Ϣ
	SMsgTeamFollowCaptain_SC(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
//////////////////////////////////////////////////////////////////
// �������ģʽ�仯
#define MSG_TEAM_CHANGEPETALLOTMODE								20
// ��Ϣ��
struct SMsgTeamChangePetAllotMode_OS
{
	DWORD		dwTeamID;					// ����ID
	long		lAllotMode;					// ����ģʽ

	SMsgTeamChangePetAllotMode_OS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
struct SMsgTeamChangePetAllotMode_SC
{
	DWORD		dwTeamID;					// ����ID
	long		lAllotMode;					// ����ģʽ

	SMsgTeamChangePetAllotMode_SC(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

//////////////////////////////////////////////////////////////////
// �޸Ķ�������
#define MSG_TEAM_CHANGETEAMNAME								21
// ��Ϣ��
struct SMsgTeamChangeTeamName_OS
{
	DWORD		dwTeamID;					// ����ID
	char        szName[TEAMNAME_LEN];       // ��������

	SMsgTeamChangeTeamName_OS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
struct SMsgTeamChangeTeamName_SC
{
	DWORD		dwTeamID;					// ����ID
	char        szName[TEAMNAME_LEN];       // ��������

	SMsgTeamChangeTeamName_SC(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

//////////////////////////////////////////////////////////////////
// �޸Ķ���˽������
#define MSG_TEAM_CHANGETEAMPRIVATE						     22
// ��Ϣ��
struct SMsgTeamChangeTeamPrivate_OS
{
	DWORD		dwTeamID;					// ����ID
	bool        bPrivate;

	SMsgTeamChangeTeamPrivate_OS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
struct SMsgTeamChangeTeamPrivate_SC
{
	DWORD		dwTeamID;					// ����ID
	bool        bPrivate;

	SMsgTeamChangeTeamPrivate_SC(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
//////////////////////////////////////////////////////////////////
// �޸Ķ�������
#define MSG_TEAM_CHANGETEAMMODE						     23
// ��Ϣ��
struct SMsgTeamChangeTeamMode_OS
{
	DWORD		dwTeamID;					// ����ID
	long        lTeamMode;                  // ��������

	SMsgTeamChangeTeamMode_OS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
struct SMsgTeamChangeTeamMode_SC
{
	DWORD		dwTeamID;					// ����ID
	long        lTeamMode;                  // ��������

	SMsgTeamChangeTeamMode_SC(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
//////////////////////////////////////////////////////////////////
// ����������Ϣ��ѯ
#define  MSG_TEAM_OTHERTEAMMSGVIEW                          24
struct SMsgTeamOtherMsgView_CS
{
	DWORD		dwPDBID;					// �鿴��
	DWORD       dwCaptain;                  // �ӳ�ID
	// ������Ϣ
	SMsgTeamOtherMsgView_CS(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
struct SMsgTeamOtherMsgView_SC
{
	DWORD		dwPDBID;			// �鿴��
	char        szName[TEAMNAME_LEN];     // ��������
	DWORD       dwTeamMode;               // ����ģʽ
	DWORD       dwGoodsAllotMode;         // ��Ʒ����ģʽ
	DWORD       dwPetAllotMode;           // �������ģʽ
	bool        bPrivate;                 // �Ƿ�˽��
	DWORD       dwCaptainID;              // �ӳ�ID
	DWORD       dwCaptainArmy;             
	DWORD       dwCaptainHomage;
	int         nCount;                    // ��Ա��Ŀ
	// ������Ϣ
	SMsgTeamOtherMsgView_SC(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
//////////////////////////////////////////////////////////////////
// ����Ч��Ա���������ӽ���
#define  MSG_TEAM_RANDOMDIDA                          25

struct SMsgTeamRandomDida_SC
{
	DWORD		dwPDBID;					// ����˭
	DWORD       dwTeamID;                   // ����ID
	DWORD       dwGoodsID;                  // ID
	int			nStayTime;					// ͣ��ʱ��
	int         nRandomNum;                 // �����
	LONGLONG    lGoodsUid;                  // ��Ӧ��Ʒ
	int         nReandomGoodType;           // ��Ʒ����
	long        lImageID;                   // ͼƬID

	SMsgTeamRandomDida_SC(void)
	{
		memset(this, 0, sizeof(*this));
	};
};
struct SMsgTeamRandomDida_CS
{
	DWORD		dwPDBID;					// ����˭
	DWORD       dwTeamID;                   // ����ID��
	LONGLONG    lGoodsUid;                  // ��Ҫʰȡ����Ʒ
	bool        bNeed;                      // �Ƿ���Ҫ
	SMsgTeamRandomDida_CS(void)
	{
		memset(this, 0, sizeof(*this));
	};
};
//////////////////////////////////////////////////////////////////
struct SMsgTeamViewTeamMemberData_SC
{
	DWORD		dwViewPDBID;			    // �鿴��
	DWORD       dwReviewPDBID;              // ���鿴��
	char        szName[TEAMNAME_LEN];       // ���鿴�ߵ�����
	DWORD       dwLevel;                    // �ȼ�
	DWORD       dwSex;                      // �Ա�
	DWORD       dwVocation;                 // ְҵ
	DWORD       dwCurHP;                    // ��ǰ����ֵ
	DWORD       dwMaxHP;                    // �������ֵ
	DWORD       dwCurMP;                    // ��ǰħ��ֵ
	DWORD       dwMaxMP;                    // ���ħ��ֵ
	DWORD       dwMinPActValue;             // ��С������
	DWORD       dwMaxPActValue;             // ��󹥻���
	DWORD       dwPDefence;                 // �������ֵ
	DWORD       dwMinMActValue;             // ��Сħ��
	DWORD       dwMaxMActValue;             // ���ħ��
	DWORD       dwMDefence;                 // ħ������ֵ
	DWORD       dwSpeed;                    // �ƶ��ٶ�
	DWORD       dwFatal;                    // ����ֵ
	DWORD		dwKickFatal;				// ����ֵ
	DWORD       dwPersent;                  // ����ֵ
	DWORD       dwHedge;                    // ����ֵ
	LONGLONG    uID;                        // UID
	SMsgTeamViewTeamMemberData_SC(void)
	{
		memset(this, 0, sizeof(*this));
	};
};
//////////////////////////////////////////////////////////////////
// �鿴��Ա�ڵ�ͼ����ʾ��Ϣ
// ��Ա��Ϣ�ṹ
struct TeamMemberMapPlace 
{
	char		szName[MAX_PERSONNAME_LEN];	// ����
	POINT       ptTitle;                    // λ��
	bool        bCaptain;                   // �Ƿ�Ϊ�ӳ�
};
typedef vector<TeamMemberMapPlace>   TVECTOR_TEAMMEMBERMAPPLACE; 
#define  MSG_TEAM_VIEWMEMBER_MAPPLACE                          26
struct SMsgTeamViewMemeberMapPlace_CS
{
	int     nMapId;           // ��Ҫ��ʾ��ͼID
};
struct SMsgTeamViewMemeberMapPlace_SC
{
	int     nMapId;           // ��Ҫ��ʾ��ͼID
	int     nMemberCount;     // ���ڵĶ�Ա����
};

// ȥȡ�������������� 
#define  MSG_TEAM_GETOTHER_TEAMDATA               27
struct SMsgTeamGetOtherTeamData_CS
{
	DWORD     dwViewerPDBID;       // �鿴��
	DWORD     dwPDBID;             // ���鿴������ID��
	WORD      wDataType;           // ��������
};
struct SMsgTeamGetOtherTeamData_SC
{
	DWORD     dwPDBID;             // ���鿴������ID��
	WORD      wDataType;           // ��������
	int		  nData;               // 
};

// ȥȡ��Ŀ��������� 
#define  MSG_TEAM_GETTARGET_TEAMDATA               28
struct SMsgTeamGetTargetTeamData_CS
{
	DWORD     dwTargetPDBID;              // Ŀ��ID
	char      szName[TEAMNAME_LEN];       // Ŀ������
	int       nFaceID;                    // Ŀ��ͷ��ID
};
struct SMsgTeamGetTargetTeamData_SC
{
	DWORD     dwTargetPDBID;              // Ŀ��ID
	char      szName[TEAMNAME_LEN];       // Ŀ������
	int       nFaceID;                    // Ŀ��ͷ��ID
	bool      bInTeam;                    // �Ƿ��ڶ���
	bool      bCaptain;                   // �Ƿ�Ϊ�ӳ�
};

// ����DIDA��æ����Ϣ��ʾ 
#define  MSG_TEAM_INVITE_DIDABUSY             29
struct SMsgTeamInviteDidaBusy_CS
{
	DWORD     dwTargetPDBID;              // Ŀ��ID
	char      sztoolTip[256];             // tip���ݣ�
};

// ���¶�����������ֵ
#define MSG_TEAM_UPDATE_PROPVALUE              30
struct  SMsgTeamUpdatePropValue_SO
{
	DWORD     dwPDBID;     // ��Ҫ���µ�����ID
	DWORD     dwLevel;     // �ȼ�
	DWORD     dwCurHP;     // ��Ѫ
	DWORD     dwMaxHP;     // �����Ѫ����
	DWORD     dwCurMP;     // MP
	DWORD     dwMaxMP;     // MAXMP
};
struct  SMsgTeamUpdatePropValue_OC
{
	DWORD     dwPDBID;     // ��Ҫ���µ�����ID
	DWORD     dwLevel;     // �ȼ�
	DWORD     dwCurHP;     // ��Ѫ
	DWORD     dwMaxHP;     // �����Ѫ����
	DWORD     dwCurMP;     // MP
	DWORD     dwMaxMP;     // MAXMP
};

// ��Ա�����Ժ�ļ���
#define  MSG_TEAM_ENTERTEAM_UPDATA				31

#define  MSG_TEAM_QUITTEAM_UPDATA				32


#pragma pack()