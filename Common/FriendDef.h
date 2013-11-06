//==========================================================================
/**
* @file	  : FriendDef.h
* @author : pk <pk163@163.com>
* created : 2008-6-16   10:48
* purpose : ����ϵͳ��ض���
*/
//==========================================================================

#ifndef __FRIENDDEF_H__
#define __FRIENDDEF_H__

#include "UserInfoDef.h"
#include <string>
using namespace std;

const static DWORD FRIEND_INVITE_INTERVAL_MIN = 30000; //�������������Сʱ���� 30000ms

const static DWORD FRIEND_ACCEPT_INVITE_INTERVAL_MAX = 60; //���ѽ������볬ʱʱ�� 60s

const static DWORD FRIENDPOINT_TRADE_NUM_PERDAY = 4;//���׼��Ѻöȣ�ÿ�����4��

const static int FRIEND_DEFAULT_GROUPID = 1; //Ĭ�Ϻ��ѷ���ID
const static string FRIEND_DEFAULT_GROUPNAME = "����"; //Ĭ�Ϻ��ѷ�����

const static int FRIEND_GROUP_NUM_MAX = 5;//1��Ĭ�Ϸ��� + 4���Զ������

#define MAX_FRIENDGROUP_NAME 12

enum 
{
	MAX_FRIEDN_NUM = 100,                /// �������� 
	MAX_ENEMY_NUM  = 150,				/// �������� 
	MAX_RECENT_NUM = 100,               /// �����ϵ�������
	MAX_SHIELD_NUM = 150,               /// ������������
};

/// ���ѹ�ϵ
enum FriendRelation
{
	FriendRelation_Buddy      =  1,  				/// ����
	FriendRelation_Stranger,			/// İ����
	FriendRelation_Blacklist,			/// ������
	FriendRelation_Enemy,				/// ����
	FriendRelation_Shield,              /// ���εĺ��ѻ����
};

enum RemoveFriendReason
{
	Friend_Logoff      =   1 //��������
};

enum AddEnemyReason
{
	Murder   = 1,  //��ɱ
	Manu     = 2,  //�ֶ����
};

enum  FriendOperate
{
	FriendOperate_StartInvite = 1,
	FriendOperate_Chat		  = 2,
	FriendOperate_Trade		  = 3,
	FriendOperate_Interchange = 4,
};

enum FriendPointTimeInterval
{
	FriendPoint_Interval_Chat    = 7200,   // ������� 2Сʱһ�� ��λ��s
	FriendPoint_Interval_Trade   = 86400,  // ���� ÿ��4��    ��λ��s
	FriendPoint_Interval_Team    = 1440000,// ��� ÿ24���� ����һ�� ��λ��ms
};

enum FriendPointADD
{
	FriendPoint_Chat    = 1, // ������� ����1��
	FriendPoint_Trade   = 1, // ���� ����1��
	FriendPoint_TEAM	= 1, // ��� ����һ��

	FriendPoint_BADPK   = 100, // ����PK������100�� �ݶ�	
	FriendPoint_MAX     = 1500,
};
#pragma pack(push)
#pragma pack(1)

/// �û���Ϣ
struct FriendGroupInfo
{
	DWORD     GroupID;         /// ����ID
	char	  GroupName[MAX_PERSONNAME_LEN + 1];	/// GroupNmae
	int       nMemberNum;
	int       nOnlineNum;
	FriendGroupInfo()
	{
		memset(this, 0, sizeof(FriendGroupInfo));
	}

	void OnAddFriend(bool bOnline)
	{
		++nMemberNum;
		if (bOnline)
		{
			++nOnlineNum;
		}
		if (nOnlineNum > nMemberNum)
		{
			nOnlineNum = nMemberNum;
		}
	}

	void OnRemoveFriend(bool bOnline)
	{	
		if (nMemberNum > 0)
		{
			--nMemberNum;
		}
		if (bOnline && nOnlineNum > 0)
		{
			--nOnlineNum;
		}	

		if (nOnlineNum < 0)
		{
			nOnlineNum = 0;
		}
	}
};

/// �����б��еĺ��Ѽ�¼
struct FriendRecord
{
	ulong   FriendID;                           /// ����ID
	ushort	Relation;							/// ���ѹ�ϵ
	int     FriendGroup;                        /// �������
	ulong   FriendPoint;                        /// �Ѻö�
	ushort  TeamAddPoint;                       /// ������ӵ��Ѻö�
	ushort  TalkAddPoint;                       /// �������ӵ��Ѻö�
	ushort  TradeAddPoint;                      /// �������ӵ��Ѻö�
	ushort  InterchangeAddPoint;                /// �д����ӵ��Ѻö�
	ushort  GiveGoodsAddPoint;                  /// ���������Ѻöȵ���
	ushort  UseGoodsAddPoint;                   /// ʹ����Ʒ���ӵ��Ѻö�

	// ��������������ͳһ������ģ�����ˣ������û���� [4/15/2011 zgz]
	bool    bShield;                            /// �Ƿ����� 

	bool    bRecently;                          /// �Ƿ�Ϊ���
	ushort  MurderNumber;                       /// ��ıɱ����
	ulong	FaceID;					            /// ͷ��
	int		Level;								/// �ȼ�
	uchar	Profession;							/// ְҵ
	bool	Online;					            /// �Ƿ�����
	int     nMapID;                             /// ��ͼID
	char	Name[32];							/// �û���
	uchar	Nation;							    /// ����
	FriendRecord()
	{
		memset(this, 0 ,sizeof(FriendRecord));
	}
};

#pragma pack(pop)

////////////////////////// ������Ϣ����//////////////////////
// �ͻ��˷�����������
/// �����û���Ϣ(CS,SC)
#define   FriendMsg_UpdateFriendInfo                 1

struct  SMsgFriend_UpdateFirendGroup_SC  
{
	DWORD   dwActor;  
	int      nCount;
	SMsgFriend_UpdateFirendGroup_SC(void)
	{
		memset(this, 0, sizeof(*this));
	};
};    

/// ����ϵͳ����
#define   FriendMsg_UpdateSysConfig                  2

/// ���º��ѹ�ϵ(��ӻ��޸�)
#define   FriendMsg_UpdateFriendRelation             3
   
/// ɾ������ (dbid actorId, dbid friendId)
#define   FriendMsg_RemoveFriend                     4

struct  SMsgFriend_RemoveFriend_SC  
{
	dbid userPID;
	dbid firendPID;
	SMsgFriend_RemoveFriend_SC(void)
	{
		memset(this, 0, sizeof(*this));
	};
};  
/// ���������Ϣ
#define   FriendMsg_RequestFriendInfo                5

/// ����������Ϣ
#define   FriendMsg_SendMsg                          6

// �������������ͻ���
/// ���º����б�
#define   FriendMsg_UpdateFriendList                 7

struct    SMsgFriend_UpdateFirendlist_OS
{
	DWORD   dwActor;                      // ��Ҫ����˭�ĺ����б�
    int     nCount;                       // ���Ѹ���
	SMsgFriend_UpdateFirendlist_OS(void)
	{
		memset(this, 0, sizeof(*this));
	};
};
struct   SMsgFriend_UpdateFirendlist_SC
{
	DWORD   dwActor;                      // ��Ҫ����˭�ĺ����б�
	int     nCount;                       // ���Ѹ���
	SMsgFriend_UpdateFirendlist_SC(void)
	{
		memset(this, 0, sizeof(*this));
	};
};
/// ����������Ϣ
#define   FriendMsg_ResponseFriendInfo               8

/// ת��������Ϣ
#define   FriendMsg_MsgArrived                       9

/// ����֪ͨ
#define   FriendMsg_FriendLogin                        10

struct  SMsgFriend_FriendLogin_SC  
{		
	dbid userPID;
	dbid friendPID;
	SMsgFriend_FriendLogin_SC()
	{
		memset(this, 0, sizeof(*this));
	}
};

/// ����֪ͨ
#define   FriendMsg_FriendLogoff                       11
struct  SMsgFriend_FriendLogoff_SC  
{		
		dbid userPID;
		dbid friendPID;
		SMsgFriend_FriendLogoff_SC()
		{
			memset(this, 0, sizeof(*this));
		}
};

/// ������Ӻ���
#define   FriendMsg_ApplyAddFriend			         12

struct  SMsgFriend_AppAddFriend_SC  
{
	dbid   appUserID;                   /// ������PID
	char   name[MAX_PERSONNAME_LEN + 1];	/// ����������
	ulong  level;						/// �����ߵȼ�
	int    nCreatureVocation;           /// ������ְҵ
	SMsgFriend_AppAddFriend_SC(void)
	{
		memset(this, 0, sizeof(*this));
	};
};    

/// ���ܺ�������
#define   FriendMsg_AcceptApply			             13
struct  SMsgFriend_AcceptApply_cs  
{
	dbid   acceptID;                   /// ����������PID
	dbid   inviteID;                   /// ������PID 
	char   name[MAX_PERSONNAME_LEN + 1];	/// ����������
	SMsgFriend_AcceptApply_cs(void)
	{
		memset(this, 0, sizeof(*this));
	};
};    


#define  FriendMsg_AddFriend                        14
struct  SMsgFriend_AddFriend_sc  
{
	dbid userPID;
	FriendRecord friendRecode;        // ���Ѽ�¼
	SMsgFriend_AddFriend_sc(void)
	{
		memset(this, 0, sizeof(*this));
	};
};    

// ���Ѳ���
#define  FriendMsg_SearchFriend                      15

//�ͻ���������������������
struct  SMsgFriend_SearchFriend_cs  
{
	dbid   searcherID;                   /// ��ѯ��PID
	dbid   personID;
	char szfriendName[MAX_PERSONNAME_LEN + 1];        
	SMsgFriend_SearchFriend_cs(void)
	{
		memset(this, 0, sizeof(*this));
	};
};  

// ��������ת�������������д���
struct  SMsgFriend_SearchFriend_ss  
{
	dbid   searcherID;                   /// ��ѯ��PID
	char szfriendName[MAX_PERSONNAME_LEN + 1];        
	SMsgFriend_SearchFriend_ss(void)
	{
		memset(this, 0, sizeof(*this));
	};
};  

struct SMsgFriend_SearchRecord
{
	dbid personPID;                     //PID
	char szName[MAX_PERSONNAME_LEN + 1];    // ����    
	int  nLevel;						// �ȼ�
	int  nSex;							// �Ա�
	int  nVocation;						// ְҵ
	int  nFaceID;                         // ͷ��

};

// ��ѯ���
struct  SMsgFriend_SearchFriend_sc 
{	
	int nCount;                         // �������
	//...�䳤�ļ�¼
	SMsgFriend_SearchFriend_sc(void)
	{
		memset(this, 0, sizeof(*this));
	};
}; 

#define  FriendMsg_SearchFriendByMapID              16
struct  SMsgFriend_SearchFriendByMapID_ss  
{
	dbid   searcherID;                   /// ��ѯ��PID
	DWORD   dwMapID;                   
	SMsgFriend_SearchFriendByMapID_ss(void)
	{
		memset(this, 0, sizeof(*this));
	};
}; 

// �������ѷ���
#define  FriendMsg_AddGroup                           17
struct  SMsgFriend_AddGroup_cs  
{
	dbid   userPID;								/// ������PID
	int   nGroupID;
	char   szGroupName[MAX_PERSONNAME_LEN + 1];     // ����                
	SMsgFriend_AddGroup_cs(void)
	{
		memset(this, 0, sizeof(*this));
	};
}; 

struct  SMsgFriend_AddGroup_sc  
{
	int   nGroupID;								/// 
	char    szGroupName[MAX_PERSONNAME_LEN + 1];     // ����                
	SMsgFriend_AddGroup_sc(void)
	{
		memset(this, 0, sizeof(*this));
	};
}; 

#define FriendMsg_ChangeGroupName                    18
struct SMsgFriend_ChangeGroupName_cs
{
	dbid   userPID;								    ///���PID 
	int  nGroupID;                                // ����ID 
	char   szGroupName[MAX_PERSONNAME_LEN + 1];     // ����                
	SMsgFriend_ChangeGroupName_cs(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define FriendMsg_MoveFriend						 19
struct SMsgFriend_MoveFriend_cs
{
	dbid   userPID;								    ///���PID 
	dbid   friendPID;								// ����PID	
	int  nGroupID;                                // ����ID 
	SMsgFriend_MoveFriend_cs(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

struct SMsgFriend_MoveFriend_sc
{
	dbid   userPID;
	dbid   friendPID;								// ����PID	
	int  nGroupID;                                // ����ID 
	SMsgFriend_MoveFriend_sc(void)
	{
		memset(this, 0, sizeof(*this));
	};
};
#define FriendMsg_RemoveGroup						 20
struct SMsgFriend__RemoveGroup_cs
{
	dbid userPID;
	int nGroupID;
	SMsgFriend__RemoveGroup_cs()
	{
		memset(this, 0 ,sizeof(SMsgFriend__RemoveGroup_cs));
	}
};

struct SMsgFriend__RemoveGroup_sc
{
	int nGroupID;
	SMsgFriend__RemoveGroup_sc()
	{
		memset(this, 0 ,sizeof(SMsgFriend__RemoveGroup_sc));
	}
};

#define FriendMsg_ViewDetail                          21
struct SMsgFriend__ViewDetail_cs
{
	dbid userPID;
	dbid playerPID;
	SMsgFriend__ViewDetail_cs()
	{
		memset(this, 0 ,sizeof(SMsgFriend__ViewDetail_cs));
	}
};

struct SMsgFriend__ViewDetail_sc
{
	dbid playerPID;
	char szPlayerName[MAX_PERSONNAME_LEN];
	int  nLevel;
	int  nVoctaion;
	int  nMapID;
	SMsgFriend__ViewDetail_sc()
	{
		memset(this, 0 ,sizeof(SMsgFriend__ViewDetail_sc));
	}
};

#define FriendMsg_Update                             22
struct SMsgFriend__Update_sc
{
	dbid userPID;
	FriendRecord friendRecode;        // ���Ѽ�¼
	SMsgFriend__Update_sc(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define  FriendMsg_AddEnemy                         23
struct SMsgFriend__AddEnemy_sc
{
	FriendRecord friendRecode;        
	SMsgFriend__AddEnemy_sc(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define  FriendMsg_PlayerDie                         24
struct SMsgFriend__PlayerDie_ss
{
	dbid playerPID;   
	dbid MurdererPID;	// ����
	SMsgFriend__PlayerDie_ss(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define FriendMsg_AskAddEnemy						25
struct SMsgFriend__AskAddEnemy_sc
{
	dbid MurdererPID;	// ����
	SMsgFriend__AskAddEnemy_sc(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

struct SMsgFriend__AgreeAddEnemy_cs
{
	dbid userPID;
	dbid tagetPID;
	SMsgFriend__AgreeAddEnemy_cs(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define FriendMsg_RemoveEnemy						26
struct SMsgFriend__RemoveEnemy_cs
{
	dbid userPID;	// 
	dbid enemyPID;
	SMsgFriend__RemoveEnemy_cs(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

struct SMsgFriend__RemoveEnemy_sc
{
	dbid enemyPID;
	SMsgFriend__RemoveEnemy_sc(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define FriendMsg_Shield						27
struct SMsgFriend__Shield_cs
{
	dbid userPID;	// 
	dbid playerPID;
	bool bShield;
	ushort relation;
	SMsgFriend__Shield_cs(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define FriendMsg_TradeFinish						28
struct SMsgFriend__TradeFinish_ss
{
	dbid userPID;	// 
	dbid playerPID;
	SMsgFriend__TradeFinish_ss(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define  FriendMsg_EnterTeam                        29
struct SMsgFriend__TeamComm_ss
{
	dbid userPID;	// 
	DWORD  dwTeamID;
	SMsgFriend__TeamComm_ss(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define  FriendMsg_QuitTeam                        30

#define  FriendMsg_UpdateFriendPoint               31
struct SMsgFriend__UpdateFriendPoint_s
{
	dbid userPID;	// 
	dbid friendPID;
	ulong ulPoint;
	bool bBoth;
	SMsgFriend__UpdateFriendPoint_s(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

/// �ܾ���������
#define   FriendMsg_RefuseApply			             32
struct  SMsgFriend_RefuseApply_cs  
{
	dbid   refuseID;                   /// �ܾ�������PID
	dbid   inviteID;                   /// ������PID 
	SMsgFriend_RefuseApply_cs(void)
	{
		memset(this, 0, sizeof(*this));
	};
};    


/// ��ѯ��ǰ��ͼ������Ϣ
#define   FriendMsg_UpdateMapEnemy			         33
struct  SMsgFriend_UpdateMapEnemy_cs  
{
	dbid   userPID;                  
	ulong  ulMapID;
	SMsgFriend_UpdateMapEnemy_cs(void)
	{
		memset(this, 0, sizeof(*this));
	};
};  

struct  SMsgFriend_UpdateMapEnemy_ss
{
		dbid   userPID;   
		ulong  ulMapID;
		int    nLen;
		//...
};

struct SEnemyMapPlace 
{
	char		szName[MAX_PERSONNAME_LEN];	// ����
	POINT       ptTitle;                    // λ��
};
#endif // __FRIENDDEF_H__