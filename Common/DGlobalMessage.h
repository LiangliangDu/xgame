/*******************************************************************
** �ļ���:	e:\ourgame\ZoneManager\src\ZoneManager\DGlobalMessage.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2007/11/24  15:03
** ��  ��:	1.0
** ��  ��:	��Ϣ�붨��
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
/*��Ϣ����
|����������Ϣ��
|����ģ����Ϣ��
|��������Ϊ��Ϣ�� //*/

#pragma once

#include "DGlobalGame.h"

#pragma pack(1)

// ������Ϣ����Ϣͷ
struct SGameMsgHead
{
	// Դ�˵���
	BYTE		SrcEndPoint;

	// Ŀ��˵���
	BYTE		DestEndPoint;	

	// Ŀ��ģ����Ϣ��
	WORD		wKeyModule;

	// ��Ϊ��Ϣ��
	WORD		wKeyAction;
};
// ������Ϣ��������Ҫ����Գ��﹥��ʱ��Ŀ�꿿�����ƶ���ʹ�ü��ܵȿͻ��˺ͷ�������Ϣ�����Ĵ��� zhangjie 2009/12/14
struct SMsgActionMaster_CS
{
	LONGLONG    uidActionMaster;
};

/***************************************************************/
//////////////////////// ���������ȫ�ֶ��� /////////////////////
/***************************************************************/
enum
{ 
	// δ����
	MSG_ENDPOINT_UNKNOW = 0,

	// �������ģۼ�ƣ���
	MSG_ENDPOINT_SUPERCENTER,

	// �����������ۼ�ƣ�S��
	MSG_ENDPOINT_ZONE,

	// ���ط������ۼ�ƣ�G��
	MSG_ENDPOINT_GATEWAY,

	// ��¼�������ۼ�ƣ�L��
	MSG_ENDPOINT_LOGIN,

	// ����������ۼ�ƣ�W��
	MSG_ENDPOINT_WORLD,

	// �ͻ���    �ۼ�ƣ�C��
	MSG_ENDPOINT_CLIENT,

	// �������  �ۼ�ƣ�I��
	MSG_ENDPOINT_INPUT,	

	// ���ķ������ۼ�ƣ�E��
	MSG_ENDPOINT_CENTER,

	// ���������ۼ�ƣ�O��
	MSG_ENDPOINT_SOCIAL,

	// ���
	MSG_SERVERID_MAXID
};

/***************************************************************/
///////////////////// Ŀ��ģ����ȫ�ֶ��� //////////////////////
/***************************************************************/
enum
{
	// δ����
	MSG_MODULEID_UNKNOW = 0,

	// ��ͼ
	MSG_MODULEID_MAP,

	// ʵ������
	MSG_MODULEID_PROP,

	// ʵ����Ϊ
	MSG_MODULEID_ACTION,

	// ����ģ��
	MSG_MODULEID_TASK,

	//��������
	MSG_MODULEID_SUPERCENTER,

	// ��S������ģ��
	MSG_MODULEID_GATEWAY,

	// ��S�����ķ�����ģ��
	MSG_MODULEID_CENTERSERVER,

	// ��S������ģ��
	MSG_MODULEID_CHAT,

	// ����ģ��
	MSG_MODULEID_FRIEND,

	// ����ģ��
	MSG_MODULEID_FAMILY,

	// ���ģ��
	MSG_MODULEID_TEAM,

	// ͨ����Ʒ��
	MSG_MODULEID_SKEP,

	// ��S����¼ģ��
	MSG_MODULEID_LOGIN,

	// ����ģ��
	MSG_MODULEID_TRADE,

	// ��S���л���ͼ
	MSG_MODULEID_SWITCH,

	// ϵͳģ��
	MSG_MODULEID_SYSTEM,

	//��S��������ز���
	MSG_MODULEID_INSTANCE_ZONE,

	// ��̯ģ��
	MSG_MODULEID_STALL,

	//�����̳�
	MSG_MODULEID_ONLINE_SHOP,

	// ����ģ��
	MSG_MODULEID_ARMY,

	// ���
	MSG_MODULEID_MAXID
};

/***************************************************************/
///////////////////// ����������Ϊ�����Ϣ��/////////////////////
// �ϲ����Ϣ��ض���MSG_MODULEID_MAP
/***************************************************************/
// ֪ͨ�ͻ��˴�����ͼ
//��֤����֮�����κ�ʱ�򶼿��ܱ�������ʹ��ͬһ�ʺ���ռʽ�ĵ�¼������������MSG_LOGINSERVER_MESSAGE֪ͨ
//Ϊ�˺�MSG_LOGINSERVER_MESSAGE��ͻ��MSG_MAP_LOADMAP��100��ʼ
#define MSG_MAP_LOADMAP											101
enum
{
	LOADMAP_LOGIN  = 1,
	LOADMAP_CHANGEZONE = 2,
	LOADMAP_CHANGESERVER = 3,
};
// ��Ϣ��
struct SMsgMapLoadMap_SC
{
	DWORD		dwMapID;		// ��ͼID
	DWORD		dwZoneID;		// ����ID
	POINT		ptTile;			// �������ĵ�
	int         nLoadReason;
};

// ֪ͨ�ͻ����ͷų���
#define MSG_MAP_DESTORYMAP										102
// ��Ϣ�� 
struct SMsgMapDestoryMap_SC
{

};

#define MSG_MAP_LOADMAPSUCCESS									103
// ��Ϣ�� 
struct SMsgMapLoadMapSuccess_CS
{
	int         nLoadReason;
};
/***************************************************************/
///////////////////// ����������Ϊ�����Ϣ��/////////////////////
// �ϲ����Ϣ��ض���MSG_MODULEID_PROP
/***************************************************************/
// ֪ͨ�ͻ��˴���ʵ��
#define MSG_PROP_CREATEENTITY									1
// ��Ϣ��
struct SMsgPropCreateEntity_SC
{
	LONGLONG	uidEntity;
	char		nEntityClass;	// ʵ������
	char		nIsHero;		// �Ƿ�ͻ������ǣ�1���ǣ�2����
	DWORD		dwZoneID;
	
	// ......................   // �����ֳ�
};

///////////////////////////////////////////////////////////////////
// ֪ͨ�ͻ���ɾ��ʵ��
#define MSG_PROP_DESTROYENTITY									2
struct SMsgPropDestroyEntity_SC
{
	LONGLONG	uidEntity;
};

///////////////////////////////////////////////////////////////////
// ͬ���ͻ���ʵ������
#define MSG_PROP_UPDATEPROP										3
struct SMsgPropUpdateProp_SC
{
	LONGLONG	uidEntity;
	char		nUpdateMode;	// ����ģʽ��1��������ֵ���Ը��£�2���������Ը��£�3�������ַ����Ը���

	// ......................   // �����ֳ�
};
//////////////////////////////////////////////////////////////////////////
//by cjl,ͬ���ͻ���ʵ����������
//��Ȼʹ��SMsgPropUpdateProp_SC����nUpdateMode���岻ͬ��
//nUpdateModeҪ��UPDATE_MY_XXXö�ٶ�Ӧ
#define MSG_PROP_UPDATEMYPROP									4
//end cjl

// ���
#define MSG_PROP_MAXID											128

/***************************************************************/
///////////////////// ��������ϵͳ�����Ϣ��/////////////////////
// �ϲ����Ϣ��ض���MSG_MODULEID_SYSTEM
/***************************************************************/
// ϵͳ��Ϣ���ͻ��˻ᵯ���Ի���
#define MSG_SYSTEM_TIPS											1
// ��Ϣ��
struct SMsgSystemTips_SC
{
	DWORD	dwErrorCode;		// ������
	int		nTipsLen;			// ������Ϣ����
	// ...............			// ������Ϣ��֧��HTML	
};


// ������������
#define MSG_SYSTEM_VISITOR										2
// ��Ϣ��
struct SMsgSystemVisitor_CO
{
	DWORD		dwVisitor;		// ˭����
	DWORD		dwPDBID;		// ����˭
};

struct SMsgSystemVisitor_OS
{
	DWORD		clientid;		// ˭����
	DWORD		dwPDBID;		// ����˭
};

struct SMsgSystemVisitor_SO
{
	DWORD		clientid;		// ˭����
	DWORD		dwPDBID;		// ����˭

	LONGLONG	uid;			// uid
	DWORD		dwZoneID;		// ����ID
	DWORD		dwMapID;		// ��ͼID

	// ExportHeroContext()		// ��������
};

struct SMsgSystemVisitor_OC
{	
	DWORD		dwPDBID;		// ����˭

	LONGLONG	uid;			// uid
	DWORD		dwZoneID;		// ����ID
	DWORD		dwMapID;		// ��ͼID

	// ExportHeroContext()		// ��������
};

/***************************************************************/
///////////////////// ����������Ϊ�����Ϣ��/////////////////////
// �ϲ����Ϣ��ض���MSG_MODULEID_ACTION
/***************************************************************/
// �ӳ����������ͻ��˵���Ϣ����̳д���Ϣ��
struct SMsgActionSCHead
{
	LONGLONG	uidEntity;		// ʵ��uid	
};

///////////////////////////////////////////////////////////////////
// ʵ�����Ź���
#define	MSG_ACTION_ENTER										1
// ��Ϣ��
struct SMsgActionEnter_SS
{
	LONGLONG	uidMaster;
};

///////////////////////////////////////////////////////////////////
// ʵ���˳��Ź���
#define	MSG_ACTION_EXIT											2
// ��Ϣ��
struct SMsgActionExit_SS
{
	LONGLONG	uidMaster;
};

///////////////////////////////////////////////////////////////////
// �����ƶ���Ϣ
#define MSG_ACTION_MOVE											3

// ��Ϣ��
struct SMsgActionMove_CS
{
	DWORD		dwTimeMark;		// ʱ���

	DWORD		dwPathLen;		// ·������
	// ......................   // ·���ڵ㣬POINT * dwPathLen
};	

struct SMsgActionMove_SC
{
	bool        bAutoMove;      // �Ƿ�Ϊ�Զ�Ѱ·״̬(���������Զ��ƶ�״̬)
	DWORD		dwPathLen;		// ·������
	// ......................   // ·���ڵ㣬POINT * dwPathLen
};

struct SMsgActionMove_SS
{
	bool        bDelayCompensate;
	DWORD		dwPathLen;		// ·������
	// ......................   // ·���ڵ㣬POINT * dwPathLen
	SMsgActionMove_SS():
			bDelayCompensate(false),
			dwPathLen(0)
	{
	}
};

///////////////////////////////////////////////////////////////////
// ����˲��ͣ��ĳ��tile
#define MSG_ACTION_STOPHERE										4
// ��Ϣ��
// ���Ҫ�л�����������Ϣ�����ܴ���
struct SMsgActionStopHere_SS
{
	DWORD		dwNewZoneID;	// ����ID
	POINT		ptHere;			// ͣ����λ��	
};

struct SMsgActionStopHere_SC
{
	POINT		ptHere;			// ͣ����λ��

	char		szTTOO[128];	// �Ż���δ��Ҫȥ��
};

struct SMsgActionStopHere_CS
{
	POINT		ptHere;			// ͣ����λ��
};

///////////////////////////////////////////////////////////////////
// ʵ��������һ��BUFF
#define MSG_ACTION_ADDBUFF										5
// ��Ϣ��
struct SMsgActionAddBuff_SC
{
	DWORD		dwIndex;		      // ���
	DWORD		dwBuffID;		      // BUFF ID
	DWORD		dwLevel;		      // BUFF �ȼ�
	DWORD		dwTime;			      // ʱ�䳤
	DWORD       dwCurOverlayTimes;    // BuffЧ���Ѿ����ӵĴ���
	bool		bRandEffect;          // �Ƿ������Ч��
};

///////////////////////////////////////////////////////////////////
// ʵ���Ƴ���һ��BUFF
#define MSG_ACTION_REMOVEBUFF									6
// ��Ϣ��
struct SMsgActionRemoveBuff_SC
{
	DWORD		dwIndex;		// ���
};

///////////////////////////////////////////////////////////////////
// ʵ������
#define MSG_ACTION_DIE											7
// ��Ϣ��
struct SMsgActionDie_SC
{

};

///////////////////////////////////////////////////////////////////
// �� ��Ч����Ч
#define MSG_ACTION_PLAYEFFECT									8
// ��Ϣ��
struct SMsgActionPlayEffect_SC
{
	DWORD		dwFlashID;		// ������Ч
	DWORD		dwSoundID;		// ������Ч
};

///////////////////////////////////////////////////////////////////
// ʹ�÷�װ������Ʒ
#define MSG_ACTION_USENONEQUIPABLEGOODS							9
// ��Ϣ��
struct SMsgActionUseNonequipableGoods_SS
{	
	LONGLONG	uidNonequipableGoods;	// ��װ������Ʒuid
	LONGLONG    uidUser;                // ʹ����uid
};

////////////////////////// ������Ϣ�� ////////////////////////////
/// ʹ�ü���(CC,CZ,ZZ)
/// �����ģ�SkillContext
#define MSG_ACTION_USE_SKILL									10

/// �����������ͻ��˽�ɫ�ļ����б�����(ZC)
/// �����ģ�256�ֽڼ����б�
#define MSG_ACTION_UPDATE_SKILL_DATA							11

/// ������֪ͨ�ͻ����������(ZC)
/// �����ģ���
#define MSG_ACTION_PREPARE_SKILL_OK								12

/// ������֪ͨ�ͻ��˿���ʹ��XP������(ŭ������)
#define MSG_ACTION_CANUSE_XPSKILL								13


/// ������֪ͨ�ͻ��˼��ܱ��ж�(ZC,ZZ)
/// �����ģ�ԴUID
#define MSG_ACTION_BREAK_SKILL									14

/// ��������(ѧϰҲ������)(CZ,ZC)
/// �����ģ�4�ֽڼ���ID
#define MSG_ACTION_UPGRADE_SKILL								15

/// ������֪ͨ�ͻ��˼���ʹ��ʧ��(ZC)
/// �����ģ�����ԭ�� UseSkillResult
#define MSG_ACTION_SKILL_FAILED									16

/// ������֪ͨ�ͻ���XP���ܳ�ʱ������ʹ����(ŭ����Ϊ0)
#define MSG_ACTION_XPSKILL_TIMEOUT								17
struct SMsgActionXPSkillTimeout_SC
{	
	LONGLONG	uidMaster;
	char        cXPStateFlag;
};

/// �ͻ���֪ͨ������XP�ڿ�ʼʹ�ã��Ա��������ʼ��ʱ
#define MSG_ACTION_XPSKILL_BEGIN								18
struct SMsgActionSkillBegin_CS
{	
	LONGLONG	uidMaster;
	short       sSkillId;
};

///������֪ͨ�ͻ���XP���Կ�ʼ������
#define MSG_ACTION_XPSKILL_CANBOOT								19

////////////////////////// �˺���Ϣ�� ////////////////////////////
/// ׼���˺�
/// �����ģ�DamageCalcContext
#define MSG_ACTION_PREPARE_DAMAGE								20

/// �˺�
/// �����ģ�DamageContext
#define MSG_ACTION_DAMAGE										21

/// ׼������
/// �����ģ�CureCalcContext
#define MSG_ACTION_PREPARE_CURE									22

/// ����
/// �����ģ�CureContext
#define MSG_ACTION_CURE											23

// ��ǰ�ṩ����ʹ�õ�XP����
#define MSG_ACTION_CURRENT_XP                                   30

#define MSG_ACTION_REFRESHSKILL									31
struct SMsgActionRefreshSkill
{
	int  nFreezeID;
};

// �ɼ���Ʒ��Ч����
#define MSG_ACTION_PLAY_COLLECTEFFECT                           34
struct SMsgActionCollectEffectPlay
{	
	int      	nMonsterID;
	bool        bPlay;
};
// ׼���ɼ�����
#define MSG_ACTION_PREPARE_COLLECT                              35
struct SMsgActionPrepareCollect
{	
	LONGLONG	uidTarget;
	long        lTargetType;
};

// �ɼ�
#define MSG_ACTION_COLLECT                                      36

#define MSG_ACTION_BREAK_COLLECT                                37

/// ������֪ͨ�ͻ��˲ɼ��������(ZC)
#define MSG_ACTION_PREPARE_COLLECT_OK                           38

/// ������֪ͨ�ͻ��˲ɼ�ʧ��(ZC)
#define MSG_ACTION_COLLECT_FAILED                               39

/////////////////////////////////////////////////////////////////
// ������Ʒ��
#define MSG_ACTION_CREATESKEP									40
// ��Ϣ��
struct SMsgActionCreateSkep_SC
{	
	// �ֳ�Ϊ SBuildSkepClientContext
};

///////////////////////////////////////////////////////////////////
// ����������Ʒ
#define MSG_ACTION_BUYGOODS										41
// ��Ϣ��
struct SMsgActionBuyGoods_CS
{
	LONGLONG		uidNPC;		// NPC����
	DWORD			dwSkepID;	// ͨ����Ʒ��ID

	LONGLONG		uidGoods;	// ������Ʒ
	int				nBuyNum;	// �����

	int				nPlace;		// ����λ��
};

///////////////////////////////////////////////////////////////////
// ����������Ʒ
#define MSG_ACTION_SALEGOODS									42
// ��Ϣ��
struct SMsgActionSaleGoods_CS
{
	LONGLONG		uidNPC;		// NPC����
	DWORD			dwSkepID;	// ͨ����Ʒ��ID
	LONGLONG		uidGoods;	// ���۵���Ʒ
};

///////////////////////////////////////////////////////////////////
// ���NPC�Ի�
#define MSG_ACTION_MEETNPC										43
// ��Ϣ��
struct SMsgActionMeetNPC_CS
{
	LONGLONG		uidNPC;		// NPC��UID
};

///////////////////////////////////////////////////////////////////
// ��������
#define MSG_ACTION_PERSONFORM									44
// ��Ϣ��
struct SMsgActionPersonForm_SC
{
	// .....SPersonFormData		// һ������
};

///////////////////////////////////////////////////////////////////
// �۲����Ĺ���
#define MSG_ACTION_OBSERVERHOLD									45
// ��Ϣ��
struct SMsgActionObserverHold_SC
{
	LONGLONG		uidMonster;	// �θ���
	LONGLONG		uidHolder;	// ӵ����
	int				nTeamID;	// ����ID
};

struct SMsgActionObserverHold_CS
{
	LONGLONG		uidMonster;	// �θ���
	bool			bObserver;	// �۲�/ȡ��
};

///////////////////////////////////////////////////////////////////
// �򿪱���
#define MSG_ACTION_OPENBOX										46
// ��Ϣ��
struct SMsgActionOpenBox_CS
{
	LONGLONG		uidBox;		// ����
};

///////////////////////////////////////////////////////////////////
// �رձ���
#define MSG_ACTION_CLOSEBOX										47
// ��Ϣ��
struct SMsgActionCloseBox_CS
{
	LONGLONG		uidBox;		// ����
};

///////////////////////////////////////////////////////////////////
// �޸���ӪID
#define MSG_ACTION_CHANGECAMP									48
// ��Ϣ��
struct SMsgActionChangeCamp_SC
{
	int				nCampID;	// ��ӪID
};

///////////////////////////////////////////////////////////////////
// �л�PKģʽ
#define MSG_ACTION_SWITCHPKMODE									49
// ��Ϣ��
struct SMsgActionSwitchPKMode_CS
{
	int				nPKMode;	// PKģʽ
};

struct SMsgActionSwitchPKMode_SC
{
	int				nPKMode;	// PKģʽ
};

///////////////////////////////////////////////////////////////////
// �޸�PK������ɫ
#define MSG_ACTION_PKNAMECOLOR									50
// ��Ϣ��
struct SMsgActionPKNameColor_SC
{
	int				nPKColor;	// ������ɫ
	bool			bGrayName;	// �Ƿ����
};

///////////////////////////////////////////////////////////////////
// ��������
#define MSG_ACTION_UPGRADE										51
// ��Ϣ��
struct SMsgActionUpgrade_CS
{
	LONGLONG lUpgrdaeUid; //���������UID
	// .................
};	

///////////////////////////////////////////////////////////////////
// ��ȴ��ʼ������
#define MSG_ACTION_INITFREEZE									52
// ��Ϣ��
struct SMsgActionInitFreeze_SC
{
	struct SNodeContext
	{
		BYTE		byClassID;	// ��ȴ��ID	
		int			nFreezeID;	// ��ȴID
		int			nFreezeTime;// ��ȴʣ��ʱ�䣨���룩
	};

	// .................		// ���SNodeContext
};

///////////////////////////////////////////////////////////////////
// ��������
#define MSG_ACTION_UIDATA										53
// ��Ϣ��
struct SMsgActionUIData_SC
{	
	BYTE			byData[UIDATA_LEN];// ��������
};

struct SMsgActionUIData_CS
{
	BYTE			byData[UIDATA_LEN];// ��������
};

///////////////////////////////////////////////////////////////////
// �ͻ���׼���ƶ�
#define MSG_ACTION_PREPMOVE										54
// ��Ϣ��
struct SMsgActionPrepMove_CC
{	
	DWORD			dwPathLen;		// ·������
	POINT *			pPath;			// ·��
};

///////////////////////////////////////////////////////////////////
// ʵ�帴��
#define MSG_ACTION_RELIVE										55
// ��Ϣ��
struct SMsgActionRelive_SC
{
	LONGLONG uid;//.................
};

///////////////////////////////////////////////////////////////////
// �ͻ���վ����ǰλ��
#define MSG_ACTION_STAND										56
// ��Ϣ��
struct SMsgActionStand_CC
{
	
};

///////////////////////////////////////////////////////////////////
// ����һ�ٻ���
#define MSG_ACTION_PAWNADD										57
// ��Ϣ��
struct SMsgActionPawnAdd_SC
{	
	LONGLONG		uidPawn;		// �ٻ���
	DWORD			dwMonsterID;	// ����ID
};

///////////////////////////////////////////////////////////////////
// ɱ��һ�ٻ���
#define MSG_ACTION_PAWNKILL										58
// ��Ϣ��
struct SMsgActionPawnKill_SC
{
	LONGLONG		uidPawn;		// �ٻ���
};

///////////////////////////////////////////////////////////////////
// �ٻ��������Լ���ͷĿ
#define MSG_ACTION_PAWNLEADER									59
// ��Ϣ��
struct SMsgActionPawnLeader_SC
{
	LONGLONG		uidLeader;		// ͷĿ
	char szLeader[MAX_PERSONNAME_LEN];
};

///////////////////////////////////////////////////////////////////
// ����ֿ�����
#define MSG_ACTION_RESETWAREHOUSEPASSWORD						60
// ��Ϣ��
struct SMsgActionResetWareHousePassword_SC
{
	LONGLONG		uid;		// ����	
	char oldPassword[MAX_WAREHOUSEPASSWORD_LEN];
	char newPassword[MAX_WAREHOUSEPASSWORD_LEN];

	SMsgActionResetWareHousePassword_SC(void)
	{
		memset(this, 0, sizeof(SMsgActionResetWareHousePassword_SC));
	}
};


///////////////////////////////////////////////////////////////////
// ʹ�òֿ�
#define MSG_ACTION_OPENWAREHOUSE								61
// ��Ϣ��
struct SMsgActionOpenWareHouse_SC
{
	LONGLONG		uid;		// ����
	char password[MAX_WAREHOUSEPASSWORD_LEN];
};

///////////////////////////////////////////////////////////////////
// ��ȡ�ֿ��Ǯ
#define MSG_ACTION_SAVEORGETWAREHOUSEMONEY						62
// ��Ϣ��
struct SMsgActionSaveOrGetMoney_SC
{
	LONGLONG		uid;		// ����
	int             amount;		// ��Ǯ����
};

///////////////////////////////////////////////////////////////////
// �ֿ����֪ͨ
#define MSG_ACTION_WAREHOUSE_NOTIFICATION						63


///////////////////////////////////////////////////////////////////
// ��������
#define MSG_ACTION_PETKILL										64
// ��Ϣ��
struct SMsgActionPetKill_SC
{
	LONGLONG		uidPawn;		// �ٻ���
};

///////////////////////////////////////////////////////////////////
// �ٻس���
#define MSG_ACTION_PETCALLBACK									65

// �ٻ�����
#define MSG_ACTION_PETCONJURE									66
struct SMsgActionPetConjure_SC
{
	LONGLONG		uidPet;
	int             nSrcPlace;   // Դλ��(���޸Ķ�ӦUI��ť)
	bool			isSuccess;
};

struct SMsgActionPetConjure_CS
{
	LONGLONG		uidPet;
	int             nSrcPlace;   // Դλ��(���޸Ķ�ӦUI��ť)
};

// �������
#define MSG_ACTION_PETCOMBINATION								67
// �������
#define MSG_ACTION_PETRIDE										68
// ��Ϣ��
struct SMsgActionPetGeneral_SC
{
	LONGLONG		uidPet;		
	int             nSrcPlace;   // Դλ��(���޸Ķ�ӦUI��ť)
};

struct SMsgActionPetRide_SC
{
	LONGLONG	uidPet;
	int         nSrcPlace;   // Դλ��(���޸Ķ�ӦUI��ť)
	ulong		lPetID;		 // ����ģ��ID�������ͻ�����Ҫ
};

///////////////////////////////////////////////////////////////////
// ����װ������װ���Ƿ���ʾ
#define MSG_ACTION_EQUIPVISIBLE									69
struct SMsgActionEquipVisible_CS
{
	BYTE	equip;//ָ��������ʾ��װ��
	BYTE	visible;//����װ����ʾ
	///��Ϣ���������
};
//#define MSG_ACTION_SHOWGOODS									69
////��Ϣ��
//struct SMsgActionShowGoods_SC
//{
//	int nPlace ; //��Ʒ����Ʒ����λ��
//	bool bShow;//�Ƿ���ʾ
//	///��Ϣ�������������������
//};

///////////////////////////////////////////////////////////////////
// ��ȡĳ�����Ե���������
#define MSG_ACTION_SINGLEPETBILLBOARD							70
//��Ϣ��
struct SMsgActionReqSinglePetBillboard_SC
{
	LONGLONG uidPet;
};

///////////////////////////////////////////////////////////////////
// ��ȡĳ��������������Ե���������
#define MSG_ACTION_PETBILLBOARD									71
//��Ϣ��
struct SMsgActionReqPetBillboard_SC
{
	LONGLONG uidPet;
	ulong petPropID;
};

struct SMsgActionPetBillboardTable_SC
{
	long	pos;
	char	szPetName[MAX_PERSONNAME_LEN];
	char	szMasterName[MAX_PERSONNAME_LEN];
	short	stars;		
	long	propValue;
	bool	bHightlight;
	SMsgActionPetBillboardTable_SC()
	{
		memset(this,0,sizeof(SMsgActionPetBillboardTable_SC));
	}
};

///////////////////////////////////////////////////////////////////
// ��ȡĳ������ļ�������
#define MSG_ACTION_PETAPPRAISAL									72

struct SMsgActionPetAppraisal_SC
{
	typedef std::pair<ulong,ulong>			PetPropGrade;
	typedef std::pair<ulong,PetPropGrade>	PetGrowthGrade;

	LONGLONG uidPet;	
	long			grade_Total_InitProp;		// ��ʼ�����ܷ�
	long			grade_Total_GrowthProp;		// �ɳ����ܷ�
	long			grade_Total;				// �ܷ�

	// ת������
	PetPropGrade	grade_TransCount;

	// ��ʼ����
	PetPropGrade	grade_InitHP;
	PetPropGrade	grade_InitMin_M_A;
	PetPropGrade	grade_InitMax_M_A;
	PetPropGrade	grade_InitMin_P_A;
	PetPropGrade	grade_InitMax_P_A;
	PetPropGrade	grade_Init_P_Defence;
	PetPropGrade	grade_Init_M_Defence;

	// �ɳ���
	PetGrowthGrade	grade_Growth_Rate[PET_TYPEPROP_MAX];

	SMsgActionPetAppraisal_SC(void)
	{
		memset(this, 0, sizeof(SMsgActionPetAppraisal_SC));
	}
};
// �޸ĳ�������
#define  MSG_ACTION_CHANGPETNAME                                73
struct  SMgActionPetNameChange_SC
{
	int             nPlace;
	LONGLONG		uidPet;		// UID
	char			szPetName[MAX_PERSONNAME_LEN];
};

// �������(��SMsgActionPetGeneral_SC �ṹ)
#define  MSG_ACTION_DISBANDPET                                  74
// �������� (��SMsgActionPetRide_SC �ṹ)
#define  MSG_ACTION_DISMOUNTPET                                 75
// �����Զ��ͷż��������Ϣ
#define MSG_ACTION_ADDAUTOSKILL                                 76
// �����Զ��ͷż����Ƴ���Ϣ
#define MSG_ACTION_REMOVEAUTOSKILL                              77
struct SMgActionPetSkillCommon_SC
{ 
	LONGLONG lUid;         // �����ͷ���UID
	int  nSkillId;         // �Զ��ͷż���ID����
	bool bSuccess;         // �ɹ�
}; 
struct SMgActionPetAtuoSkill_CS
{
	LONGLONG lUid;         // �����ͷ���UID
	int  nSkillId;         // �Զ��ͷż���ID����
	int  nPlace;           // ��Ӧ��λ��
};
struct SMgActionPetAtuoSkill_SC
{
	LONGLONG lUid;         // �����ͷ���UID
	int  nSkillId;         // �Զ��ͷż���ID����
	int  nPlace;           // ��Ӧ��λ��
};
#define  MSG_ACTION_PET_FORMATION                               78
struct SMgActionPetSetFormation_CS
{
	int		nformation;		// �л�����
};
struct SMgActionPetSetFormation_SC
{
	int		nformation;		// ��
	bool	bIsActived;		// �Ƿ񼤻�
	int		nGrade[5];		// �󷨵ȼ�	add by zjp
};

// ��������Ϣ
#define  MSG_ACTION_PETRELEASE_START                            79
struct SMgActionPetRelease_SC 
{
	LONGLONG   uid;         // UID
	ulong      lPackId;     // ����ID
	int        nPlace;      // λ��
};

// �������
#define MSG_ACTION_PETEVOLUTION									80
struct SMgActionPetEvolution_SC
{
	DWORD			dwSkepID;	// ͨ����Ʒ��ID
	LONGLONG		uidPet;
	ulong			PetID;
};

// �������
#define MSG_ACTION_SETAUTOSORT									81
struct SMgActionPetAutoSort_SC
{
	bool			bAutoSort;
};
// ���＼��ѧϰ(SMgActionPetSkillCommunal_SC)
#define MSG_ACTION_PETLEARN_SKILL								82
// ���＼��ɾ��(SMgActionPetSkillCommunal_SC)
#define MSG_ACTION_PETDELECT_SKILL								83

#define MSG_ACTION_EQUIPSMELTSOUL								84
struct SMsgActionEquipSmeltSoul_CS
{
	uchar	ucType;//�������Ϣ����,��DGlobalMis
	int		nPerNum;//ÿ��ʹ�õ�����
	int		nCount;//��������
	int		nLevel;// add by zjp;��ʯ�ȼ�
	int		nSoulNum1; // װ���������ĵĻ����� add by zjp
	int		nSoulNum2;
};

#define MSG_ACTION_EQUIPEMBEDGEMS								85
struct SMsgActionEquipEmbedGems_CS
{
	uchar  ucType;//��ʯ��Ƕ����Ϣ����,��DGlobalMis
	uchar  ucDetachSlot;//����װ������
};

#define MSG_ACTION_EQUIPREBUILD									86
struct SMsgActionEquipRebuild_CS
{
	enum { RESERVE_ATTRIB_NUM_MAX = 4,};// modify by zjp
	uchar ucType; //װ����������Ϣ����,��DGlobalMis
	uchar ucReserveAttribNum;//������Ʒ����������
	uchar ucReserveBrandAttrib[RESERVE_ATTRIB_NUM_MAX];//������Ʒ������
};

#define MSG_ACTION_REPAIREQUIPMENT								87
struct SMsgActionRepairEquipment_CS
{
	ulong	ulSkepID;//װ����id
	int		iPlace;//װ����������λ��,iPlace��ʾ��������װ��
};

//by cjl
#define MSG_ACTION_IDENTIFYEQUIPMENT							88
struct SMsgActionIdentifyEquipment_CS//�ͻ��˷�������˵���Ϣ�ṹ
{
	ulong	ulSkepID;//װ�����ڵ�����id
	int		iPlace;//װ����������λ��,iPlace��ʾ��������װ���������ڼ���ʱ��ΪPACKET_ALL_EQUIP_PLACE��ʾ��������
	//������Ҫ��չ
	int    iUserID;//ʹ����ID��npcʱΪ-1������ʱΪ����id
};

struct SMsgActionIdentifyEquipment_SC//��֤���
{
	//-5 ʹ�õ��߼�������װ��
	//-2 ��������
	//-1 û�пɼ����ģ����ڼ���ȫ����
	// 0 �����ɹ�
	// 1 ��ȡ������Ʒ
	// 2 ����װ��
	// 3 �Ѿ���������
	// 4 ������û��װ��������
	// 5 ����Ǯ
	int res;
	int iUserID;//ʹ����ID
	int needMoney;
	int equipmentID;
};

#define MSG_ACTION_CHANGE_BODY									89
struct SMgActionChangeBody_SC
{
	int id;  //ģ��id
};
//end cjl

// �򿪳���ϳ����
#define MSG_ACTION_OPENPETCOMPOUND								90
struct SMsgActionNPCOpenForm_SC
{
	LONGLONG uidNPC;
};

// ����ϳ�
#define MSG_ACTION_PETCOMPOUND									91
struct SMsgActionPetCompound_CS
{
	LONGLONG uidmainpet;	// ����
	LONGLONG uidminorpet;	// ����
	DWORD	 dwtype;		// ���꣨�ϳɣ�����
	bool	 bUseGoods;		// ʹ�õ���
};

struct SMsgActionPetCompound_SC
{
	struct CompdResultItem
	{
		DWORD dwPropID;
		long  lOrgValue;
		long  lCurValue;

		CompdResultItem(DWORD _dwPropID,long _lOrgValue,long _lCurValue)
		{
			dwPropID = _dwPropID;
			lOrgValue = _lOrgValue;
			lCurValue = _lCurValue;
		}	

		CompdResultItem():dwPropID(0),lOrgValue(0),lCurValue(0)
		{}
	};

	DWORD dwError;
	LONGLONG  uidPet;;
	CompdResultItem results[14];	// ������ ��ʼ���� + �ɳ�������

	SMsgActionPetCompound_SC()
	{
		memset(this, 0, sizeof(*this));
	}
};

// �������������ĳ��
#define MSG_ACTION_PET_COMMAND									92

// ����ȡ���������
#define MSG_ACTION_PET_CANCELCOMMAND							93
struct SMsgActionPetCommand_CS
{
	DWORD		dwCmdID;
	LONGLONG	uidPet;
	LONGLONG	uidMaster;
	LONGLONG	uidTarget;
	POINT		ptTarget;
};

struct SMsgActionPetCommand_SC
{
};

// ֪ͨ�ͻ���ɾ���Լ��ĳ���ʵ��
#define MSG_ACTION_PET_DELETE									94
struct SMsgActionPetDelete
{
	LONGLONG uidPet;
};

// �ͻ��������л��ƶ���ʽ
#define MSG_ACTION_CHANGEMOVESTYLE								95
struct SMsgActionChangeMoveStyle_CS
{
	// �µ��ƶ���ʽ
	char    cMoveStyle;
};

///////////////////////////////////////////////////////////////////
// �� ��Ч����Ч
#define MSG_ACTION_PLAYGENERALEFFECT							96
// ��Ϣ��
struct SMsgActionPlayGeneralEffect_SC
{
	DWORD		dwFlashID;		// ��Ч
	DWORD		dwSoundID;		// ��Ч
	DWORD		dwZoneID;		// ����
	DWORD		dwMapID;		// ��ͼ
	POINT		ptLoc;			// �ص�
};

// add by zjp.���ݱ�ը
#define  MSG_ACTION_BUBBLE_BOMB									97
struct SMsgActionBubbleBomb_SC
{
	DWORD		dwZoneID;		// ����
	POINT		ptLoc;			// ��ը�ص�
	short       sSkillId;		        // ���ܴ���ID
	short       sSkillLevel;	        // �Ӽ���Id�����ڽ�ɫʱָ�ȼ�
};

// �����ж���
#define  MSG_ACTION_IDLE										98
struct SMsgActonIdle_SS
{
};

struct SMsgActonIdle_SC
{
};

// add by zjp.��깥��
#define  MSG_ACTION_GHOST_ATTACK								99
struct SMsgActionBubbleBomb_SS
{

};


// �Զ�Ѱ·��Ϣ
#define  MSG_ACTION_AUTOMOVE									100
struct SMsgActionAutoMove_SS
{
	int  nStartMoveMapID;
	int  nCurStart_x;   // ��ǰ��ʼλ��X
	int  nCurStart_y;   // ��ǰ��ʼλ��X
	int  nCurEnd_x;     // ��ǰ��Ҫ������X
	int  nCurEnd_y;     // ��ǰ��Ҫ������Y

	int  nEndMoveMapID; // ���͵㵽��ĵ�ͼID
	int  nEndPoint_x;   // ���͵㵽��������
	int  nEndPoint_y;   // 

	int  m_nAutoMoveMapID; // Ѱ·���յĵ�ͼID
	int  nEndAutoMove_x;   // Ѱ·���յ�����
	int  nEndAutoMove_y;   // 
};
struct SMsgActionAutoMove_SC
{
	bool m_AutoMove;      // �Ƿ�Ϊ�Զ�Ѱ·
	int  nStartMoveMapID; // ��ʼ��ͼID
	int  nCurStart_x;     // ��ǰ��ʼλ��X
	int  nCurStart_y;     // ��ǰ��ʼλ��X
	int  m_nAutoMoveMapID; // Ѱ·���յĵ�ͼID
	int  nEndAutoMove_x;   // Ѱ·���յ�����
	int  nEndAutoMove_y;   // 
};

// �����Զ�Ѱ··��
#define  MSG_ACTION_DRAWAUTOMOVEPATH                             101
struct  SMsgActionDrawAutoMovePath_SC
{
	bool       bTaskTrace; //����׷��
	POINT      ptDest;
};

// add by zjp���������ʽ
#define  MSG_ACTION_HOME_RELIVE									102
#define  MSG_ACTION_LOCAL_RELIVE								103
#define  MSG_ACTION_MAP_RELIVE									104

//���½�ɫ������Ϣ����
#define	MSG_ACTION_UPDATEBASICINFO								105
struct	SMsgActionUpdateBasicInfo_CS
{
	int	province;//ʡ��
	int city;//����		
	int constellation;//����
	int bloodtype;//Ѫ��
	char signature[ACTOR_SIGNATURE_MAX_LEN];//ǩ��
};

// ��ȡ����װ����Ϣ
#define MSG_ACTION_REQUESTEQUIPINFO								106
struct SMsgActionRequestEquipInfo_CS
{
	ulong ulUserPID;
	ulong ulPIDDest;  // Ŀ���pid
};

struct SMsgActionRequestEquipInfo_SS
{
	ulong ulUserPID;
	ulong ulPIDDest;  // Ŀ���pid
};

#define MSG_ACTION_PROPINFO										107	
struct SMsgActionPropInfo
{
	DWORD		dwViewPDBID;			    // �鿴��
	DWORD       dwReviewPDBID;              // ���鿴��
	char        szName[32];					// ���鿴�ߵ�����
	DWORD       dwLevel;                    // �ȼ�
	DWORD       dwSex;                      // �Ա�
	DWORD       dwVocation;                 // ְҵ
	DWORD       dwNation;                   //  ��������Ӫ��
	DWORD       dwNakedResId;               // ����ģ��ID
	DWORD       dwCurHP;                    // ��ǰ����ֵ
	DWORD       dwMaxHP;                    // �������ֵ
	DWORD       dwCurMP;                    // ��ǰħ��ֵ
	DWORD       dwMaxMP;                    // ���ħ��ֵ
	DWORD       dwCurSP;                    // ��ǰ����ֵ
	DWORD       dwMaxSP;                    // �������ֵ
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
	DWORD       dwFrightValue;              // ս����
	DWORD       dwFaceID;                   // ͷ��ID
	DWORD       dwProvince;                 // ʡ��
	DWORD       dwCity;                     // ����
	DWORD       dwConstellation;            // ����
	DWORD       dwBloodType;                // Ѫ��
	char        Signature[256];             // ǩ��
	LONGLONG    uID;                        // UID
	SMsgActionPropInfo(void)
	{
		memset(this, 0, sizeof(*this));
	};
};
#define MSG_ACTION_EQUIPINFO									108
struct SMsgActionEquipInfo_SC
{
	LONGLONG       uID;                        // 
	DWORD		dwViewPDBID;			    // �鿴��
	DWORD       dwReviewPDBID;              // ���鿴��
	DWORD       dwPlace;                    // ���鿴��װ����λ��	
	SMsgActionEquipInfo_SC(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define  MSG_ACTION_CLOSESHOP									109
struct SMsgActionCloseShop_SC
{
};

#define  MSG_ACTION_JUMP										110
struct SMsgActionJump
{
	xs::Point		ptTarget;				 // Ŀ��λ��
};

//�ڵ��ϳ�Ԥ����Ϣ��  by ldy
#define MSG_ACTION_COMPOSE									112
struct SProbability
{
	int	iComposeLevel;			//�ϳ��ڵ��ȼ�
	int fProbability;			//�ϳɼ���
};
struct SMsgActionComposePill_CS
{
	DWORD			dwSkepID;	//��Ʒ��ID
	int				iFee;		//�ϳɷ���
	SProbability	Probability[2];//�ϳ��ڵ�
};
//�ڵ��ϳ�ȷ��
#define MSG_ACTION_COMPOSE_CONFIRM							113
struct SMsgActionComposeConfirm_CS
{
	uchar			ucType;
};

//�꽫ʥ��Ԥ����Ϣ�� by ldy
#define MSG_ACTION_INTENSIFY								114
struct SMsgActionPetIntensify_CS
{
	DWORD		dwSkepID;		//��Ʒ��ID
	int			iFee;			//ʥ������
	int			iProbability;	//ʥ���ɹ���
	int			iStart;			//ʥ����꽫�Ǽ�
};

//�꽫ʥ��ȷ�ϣ� by ldy
#define MSG_ACTION_INTENSIFY_CONFIRM						115	
struct SMsgActionPetIntensifyConfirm_CS
{
	uchar			ucType;
};

// ͬ���ͻ��˵ĳ��������Ŀ
#define MSG_ACTION_PET_FIHGT_NUM							116	
struct SMsgActionPetFightNum_SC
{
	uchar ucFightNum;
};

// ������ ������ʾ��Χ�Լ��ܵ�tile����
#define MSG_ACTION_SKILL_TILE								117
struct SMsgActionSkillTile
{
	POINT pt;
};

// ���＼�ܾ������
#define MSG_ACTION_PET_UPDATE_SKILL_EXPRIENCE					127
struct SMsgActionPetUpdateSkillExprience
{
	UID uidPet; // �����UID
	short exprience; // ������º�ļ��ܾ���
	short sSkillId; // ����ĵ�ǰʹ�ü���ID
	short sSkillLevel; // ���ﵱǰ���ܵĵȼ�
};

// ��������Ϣ
#define  MSG_ACTION_PETRELEASE_FINISH                             128

// �޸ĳ����󷨷�λ
#define	MSG_ACTION_PET_SETPROP									129
struct SMsgActionPetSetProp_CS
{
	LONGLONG uidPet;
	DWORD dwPropID;
	DWORD dwPropValue;
};

// �������Զ��ͷż�������
#define  MSG_ACTION_PET_ADDAUTOSKILL                           130
struct SMsgActionPetAddAutoSkill_SC
{
	LONGLONG uidPet;
	int      nSkillId[PET_ATUO_SKILL_DEFAULTSIZE];
};

// �л�����״̬ȥ�ı�������ƶ��ٶȣ�
#define MSG_ACTION_CHANGE_FOLLOWSPEED                           131
struct SMsgActionChangeFollowSpeed_CS
{
	LONGLONG  uidPerson;
	bool      bFollow;
	int       nSpeed;
};


// �� ����
#define MSG_ACTION_DOCOMMAND									132
struct SMsgActionDoCommand_sc
{
	int       nCommand;
};

// 
#define MSG_ACTION_HIDE										133
struct SMsgActionHide_sc
{
	ushort usHide; // 1 hide�� 0 unhide
};

// ʰȡ��Ʒ�ɹ�֪ͨ�ͻ���ȥ����ʰȡЧ��
#define MSG_ACTION_ADDGOODS_SUCCESS							 134
struct SMsgActionAddGoodsSuccess_SC
{
	LONGLONG uidItem;
	bool     bSystemAdd;    //�Ƿ�Ϊϵͳ���
};

#define MSG_ACTION_FLY_RIDE                                  135

#define MSG_ACTION_DIS_FLY_RIDE                              136
struct SMsgActionFlyRide_SC
{
	ulong		lFlyPetID;		 // ����ģ��ID�������ͻ�����Ҫ
	ulong       lTaskID;         // ��ص�����ID��
	ulong       lNpcID;          // ��ص�NPCID��
	ulong       lCurMoveSpeed;   // ���ﵱǰ���ƶ��ٶȣ�
};

//�������
#define MSG_ACTION_DROPRIDEPET								   137
struct SMsgActionDropRidePet_cs
{
	int nPlace;
};

struct SMsgActionDropRidePet_sc
{
	int nPlace;
};

// �ɼ�NPC��Ծ
#define  MSG_ACTION_COLLECT_JUMP                             138
struct SMsgActionCollectJump_SC
{
	int nEndPtX;
	int nEndPtY;
	int nTaskID;
};

struct SMsgActionCollectJump_CS
{
	LONGLONG uidPerson;
	int nTaskID;
};
// ����NPCͷ����Ч
#define  MSG_ACTION_PLAY_EFFECT_TOPMOST                      139
struct SMsgActionPlayEffectTopMost_SC
{
	char      szTipText[64];             // ��ʾ����
	LONGLONG  uidMonster;
	ulong     ulEffectID;
	bool      bNeedClick;
};

// ����NPCͷ����Ч
#define  MSG_ACTION_STOP_EFFECT_TOPMOST                      140
struct SMsgActionStopEffectTopMost_SC
{
	LONGLONG  uidMonster;
	ulong     ulEffectID;
};

// ֹͣ ��Ч
#define MSG_ACTION_STOPEFFECT								 141
// ��Ϣ��
struct SMsgActionStopEffect_SC
{
	DWORD		dwFlashID;		// ��Ч
};

// ���������֤
#define MSG_ACTION_CHECKPETRIDE								 142
// ��Ϣ��
struct SMsgActionCheckPetRide_cs
{
	LONGLONG	uidPet;
	int         nSrcPlace;   
};

struct SMsgActionCheckPetRide_sc
{
	LONGLONG	uidPet;
	int         nPlace;
	short		check;  
};
//��¼��֪�᳡������δ���걣����ʾ
#define MSG_ACTION_ENTHRALL_PROTECT_TIPS					143
struct SMsgActionEnthrallProtectTips
{
	DWORD dwDBID;
	int iSumSeconds;
	int iIncomePercent;//�����Ա��� ��ǰ����ٷֱ�,���������Ϊ100 ������3-5СʱΪ50  5Сʱ��Ϊ0
};

//ϴ�츳
#define MSG_ACTION_RESET_GENIUS                             144

//�򿪼�����Ӫ���
#define MSG_ACTION_JOIN_CAMP_WND							145
struct SMsgActionCampOrbit
{
	int nSong;
	int nYi;
};

//�򿪸ı���Ӫ���
#define MSG_ACTION_CHANGE_CAMP_WND							146
struct SMsgActionCampChange
{
	int nEddToStrongMoney;		// ��תǿ��Ҫ��money
	int nStrongToEddMoney;		// ǿת����Ҫ��money
	int nStrongCampID;			// ǿ����ӪID
	SMsgActionCampOrbit orbit;
};


//���������¼�������ѯ��������
#define MSG_ACTION_QUERY_CLIENT_COUNT						147
struct SMsgActionQueryClientCount_ZL
{
	DWORD	dwClientID;
};

#define MAX_ACTORNAME_LEN									32
//���������¼�������޸Ľ�ɫ��
#define MSG_ACTION_ACTOR_RENAME								148
struct SMsgActionActorReName_ZL			
{
	DWORD dwClientID;
	int	  nActorID;
	char  szActorName[MAX_ACTORNAME_LEN];
	char  szNewActorName[MAX_ACTORNAME_LEN];
};

#define MSG_ACTION_BREAKPETRIDE								 149
#define MSG_ACTION_OPENPACKET								 150//by cjl

///////////////////////////////////////////////////////////////////
// �����Ϣ��
#define MSG_ACTION_MAXID									 151



//////////////////////////////////////////////////////////////////
//����
#define MSG_RESET_ALL_INSTANCE_ZONE                            1




/**				�ͻ������������˳���¼��			
@name         : �˳���¼
ע�⣬���ݵ�ǰ�������ļܹ�������Ϣ��ʵ�Ƿ�������MSG_ENDPOINT_GATEWAY�����������������Ϣ���Ա�Ͽ���ͻ��˵�����
@brief        : 
@return       : 
**/
#	define    MSG_CLIENT_LOGOUT           34


/* �ͻ�����������Ϸ���ؽ�ɫѡ�����еĽ�ɫ��Ϸ�߼����жϣ����·��ؽ�ɫ��Ϣ
*/
#	define   MSG_RE_SELECT_ACTOR         35
struct SMsgReSelectActor_SS
{
	DWORD dwClientID; //�ͻ������ش�ID
};

struct SMsgDynamicFollow_S
{
	ULONGLONG uidTarget;
	int       nFollowEyeShot;
	int		  nFollowRange;
};

struct SMsgDynamicPatrol_S
{
	BYTE      bLoop;
	BYTE      bForceChange;
	BYTE      bIgnoblock;
	int       nRange;
	int       nPatrolPointNum;
	int		  nLen;
	//...
	SMsgDynamicPatrol_S()
	{
		memset(this, 0, sizeof(SMsgDynamicPatrol_S));
	}
};

/////////////////////////////////////////////////////////////////
//super center

#define MSG_SERVERLIST_STATUS_REQUEST  10001

#define MSG_SERVERLIST_STATUS_RESPONSE  10002
struct SResponseServerListStatus
{
	DWORD dwAddr;
	WORD  wPort;
	DWORD dwOnlineNum;

	bool operator < (const SResponseServerListStatus& other)
	{
		if (dwAddr < other.dwAddr)
		{
			true;
		}
		else if (dwAddr == other.dwAddr)
		{
			return wPort < other.wPort;
		}

		return false;
	}

	bool operator ==(const SResponseServerListStatus& other)
	{
		return dwAddr == other.dwAddr && wPort == other.wPort;
	}
};

//////////////////////////////////////////////////////////////////
//�̳�
#define MSG_ONLINE_SHOP_BUY_GOODS_REQUEST		  20001
struct SOnlineShopBuyGoodsReqest
{
	int iGooodsID;
	int iCount;
};

#define MSG_ONLINE_SHOP_BUY_GOODS_RESPONSE		  20002
const int CONST_ONLINE_SHOP_MAX_GOODS_QUANTITY = 999;
enum EOnlineShopBuyGoodsResult
{
	E_ONLINE_SHOP_BUY_GOODS_RESULT_SUCCESS = 0,
	E_ONLINE_SHOP_BUY_GOODS_RESULT_INPUT_ERROR,
	E_ONLINE_SHOP_BUY_GOODS_RESULT_GOODS_NOT_FOUND,
	E_ONLINE_SHOP_BUY_GOODS_RESULT_NEED_MORE_BAOBI,
	E_ONLINE_SHOP_BUY_GOODS_RESULT_NEED_MORE_JIAOZI,
	E_ONLINE_SHOP_BUY_GOODS_RESULT_PACKET_FULL,
	E_ONLINE_SHOP_BUY_GOODS_RESULT_DATABASE_ERROR,
	E_ONLINE_SHOP_BUY_GOODS_RESULT_PROGRAM_LOGIC_ERROR,//��Ӧ�ó��ֵı���߼�����

	E_ONLINE_SHOP_BUY_GOODS_RESULT_MAX_ENUM,//ö�����ֵ
};
struct SOnlineShopBuyGoodsResponse
{
	int iGooodsID;
	int iCount;
	EOnlineShopBuyGoodsResult eResult;
};

//��ȡ��ʷ�����¼
#define MSG_ONLINE_SHOP_GET_HISTORY_REQUEST 20003

#define MSG_ONLINE_SHOP_GET_HISTORY_RESPONSE 20004
struct SOnlineShopHistoryBuyResponse
{
	int   GoodsIDArray[ONLINE_SHOP_MAX_HISTORY_PAID_RECORDS];
};

//////////////////////////////////////////////////////////////////
#pragma pack()