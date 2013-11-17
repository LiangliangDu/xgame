/*******************************************************************
** �ļ���:	e:\Rocket\Common\DGlobalEvent.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2008/2/13  15:10
** ��  ��:	1.0
** ��  ��:	�¼��붨��
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#pragma pack(1)

//////////////////////////����Դ���� ///////////////////////////
/// ����Դ����
enum
{
	SOURCE_TYPE_UNKNOW = 0,			// ����ID��
	SOURCE_TYPE_PERSON,				// ���ʵ��
	SOURCE_TYPE_PET,				// ����ʵ��
	SOURCE_TYPE_MONSTER,			// ����ʵ��
	SOURCE_TYPE_GOODS,				// ��Ʒʵ��
	SOURCE_TYPE_BOX,				// ����ʵ��
	SOURCE_TYPE_MAST,				// ���ʵ��
	SOURCE_TYPE_BUBLLE,				// ����ʵ�� add by zjp
	SOURCE_TYPE_FREEZE,				// ��ȴϵͳ
	SOURCE_TYPE_SKEP,				// ͨ����Ʒ��
	SOURCE_TYPE_SYSTEM,				// ϵͳ�¼�
	SOURCE_TYPE_CHAT,				// �����¼�
	SOURCE_TYPE_TEAM,				// ����¼�
	SOURCE_TYPE_INSTANCE_ZONE,      // �����¼�
	SOURCE_TYPE_FRIEND,             // �����¼�
	SOURCE_TYPE_STALL,              // ��̯�¼�
	SOURCE_TYPE_FAMILY,             // �����¼�
	SOURCE_TYPE_ARMY,               // �����¼�
	SOURCE_TYPE_MAX,
};

//////////////////////////////////////////////////////////////////
// ������� EVENT + ����Դ�� + ���庭��
//////////////////////////// �¼��� //////////////////////////////
/***************************************************************/
///////////////////////// ʵ���¼��� ////////////////////////////
/***************************************************************/
// ʵ�����BUFF
#define EVENT_CREATURE_ADDBUFF									1
// ������
struct SEventCreatureAddBuff_S
{
	DWORD			dwBuffID;		// buff id
	DWORD			dwLevel;		// �ȼ�
	LONGLONG		uidEffect;		// ��buff�����ö���
	LONGLONG		uidAdd;			// ��buff�������
	DWORD			dwBuffFlag;		// buff��־
};
// �ͻ���
struct SEventCreatureAddBuff_C
{
	DWORD			dwIndex;		// buff index
	LONGLONG        ulUid;          // buff Target uid
};

// ʵ���Ƴ�BUFF
#define EVENT_CREATURE_REMOVEBUFF								2
// �ͻ���
struct SEventCreatureRemoveBuff_C
{
	DWORD			dwIndex;		// buff index
	LONGLONG        ulUid;          // buff Target uid
};

// ��������
#define EVENT_CREATURE_DIE										3
// ������
struct SEventCreatureDie_S
{
	LONGLONG		uidMurderer;	// ����
};

// �ͻ���
struct SEventCreatureDie_C
{

};

// ��������
#define EVENT_CREATURE_ATTACK									4
// ������
struct SEventCreatureAttack_S
{
	LONGLONG		uidTarget;		// ����Ŀ��
	DWORD			dwUseSkillID;	// ʹ�ü���ID
};

// �˺�����
#define EVENT_CREATURE_HARM										5
// ������
struct SEventCreatureHarm_S
{
	LONGLONG		uidCasualty;	// �ܺ���
	DWORD			dwHPDamage;		// HP�˺�
	DWORD			dwMPDamage;		// MP�˺�		
};

struct SEventCreateHarm_C
{
	LONGLONG		uidSrc;			// ������
	LONGLONG		uidDest;		// ��������
};

// ����
#define EVENT_CREATURE_INJURED									6
// ������
struct SEventCreatureInjured_S
{
	LONGLONG		uidMurderer;	// ����
	DWORD			dwHPDamage;		// HP�˺�
	DWORD			dwMPDamage;		// MP�˺�
};

// �ͻ���
struct SEventCreatureInjured_C
{
	LONGLONG		uidMurderer;	// ����	
};


// �ı�λ�ã�����STOPHERE���л���ͼ
#define EVENT_CREATURE_CHANGELOC								7
// ������
struct SEventCreatureChangeLoc_S
{
	DWORD			dwOldZoneID;	// �ɳ���ID
    xs::Point			ptOldTile;		// ��Tile
	DWORD			dwNewZoneID;	// �³���ID
	xs::Point			ptNewTile;		// ��Tile
	bool			bSameServer;	// �ɳ������³����Ƿ�Ϊͬ������
};

// ��ʼ�ƶ����ƶ������У����Ǵ��¼�
#define EVENT_CREATURE_STARTMOVE								8
// ������
struct SEventCreatureStartMove_S
{

};

// �ͻ���
struct SEventCreatureStartMove_C
{

};

// �ƶ����
#define EVENT_CREATURE_DONEMOVE									9
// ������
struct SEventCreatureDoneMove_S
{

};

// �ͻ���
struct SEventCreatureDoneMove_C
{

};

// ʵ���������
#define EVENT_ENTITY_UPDATEPROP									10
// �ͻ���
struct SEventEntityUpdateProp_C
{
	LONGLONG uid ;  // ��Ҫ����ʵ���UID(wzh 09.12.07)
};
// �������ˣ��������˲��������޸�
struct SEventEntityUpdateProp_S
{
	LONGLONG uid;
	DWORD    dwPropID;
};

// ����ʵ��
#define EVENT_ENTITY_CREATEENTITY								11
// ������
struct SEventEntityCreateEntity_S
{
	LONGLONG		uidEntity;		// ʵ��uid
};
// �ͻ���
struct SEventEntityCreateEntity_C
{
	LONGLONG		uidEntity;		// ʵ��uid
};

// ɾ��ʵ��
#define EVENT_ENTITY_DESTROYENTITY								12
// ������
struct SEventEntityDestroryEntity_S
{
	LONGLONG		uidEntity;		// ʵ��uid
};
// �ͻ���
struct SEventEntityDestroryEntity_C
{
	LONGLONG		uidEntity;		// ʵ��uid
};

// ʹ�÷�װ������Ʒ
#define EVENT_ENTITY_USENONEQUIPABLEGOODS						13
// �ͻ���
struct SEventEntityUseNonequipableGoods_C
{
	LONGLONG	uidGoods;			// ��ƷUID
	LONGLONG    uidUser;            // ʹ����UID 
	DWORD		dwSkepID;			// ��Ʒ��ID
	DWORD		dwPlace;			// ��Ʒλ��
};

// �������
#define EVENT_PERSON_LOGIN										14
// ������
struct SEventPersonLogin_S
{
	LONGLONG		uidEntity;		// ʵ��uid
};

// �������
#define EVENT_PERSON_LOGOUT										15
// ������
struct SEventPersonLogout_S
{
	LONGLONG		uidEntity;		// ʵ��uid
};

// �л�PKģʽ
#define EVENT_PERSON_SWITCHPKMODE								16
// �ͻ���
struct SEventPersonSwitchPKMode_S
{
	int				nPKMode;		// PKģʽ
};

// ��������
#define EVENT_PERSON_UPGRADE									17
// ������
struct SEventPersonUpgrade_S
{
	// ...............
};

// ���NPC
#define EVENT_PERSON_MEETNPC									18
// ������
struct SEventPersonMeetNpc_S
{
	LONGLONG		uidMaster;		// ˭���NPC
	LONGLONG		uidNPC;			// �θ�NPC
};

// ����һ�������ٻ���
#define EVENT_PERSON_PAWNADDPET									19
// �ͻ���
struct SEventPersonPawnAddPet_C
{
	LONGLONG		uidPawn;		// �ٻ���UID
	DWORD		dwMonsterID;		// ����ID
};

// �ͷ�һ�������ٻ���
#define EVENT_PERSON_PAWNKILLPET								20
// �ͻ���
struct SEventPersonPawnKillPet_C
{
	LONGLONG		uidPawn;		// �ٻ���UID
	DWORD		dwMonsterID;		// ����ID
};

// ���������װ���������ĵ�ǰ����
#define EVENT_PERSON_EQUIPSMELTSOULCURSUBSKEP					21
struct SEventPersonEquipSmeltSoulCurSubskep_S
{
	ushort usCurSubskep;
};

// ���������װ����ʯ��Ƕ���ĵ�ǰ����
#define EVENT_PERSON_EQUIPEMBEDGEMSCURSUBSKEP					22
struct SEventPersonEquipEmbedGemsCurSubskep_S					
{
	ushort usCurSubskep;
};

// ���������װ���������ĵ�ǰ����
#define EVENT_PERSON_EQUIPREBUILDCURSUBSKEP						23
struct SEventPersonEquipRebuildCurSubskep_S
{
	ushort usCurSubskep;
};

// ���������ܹ���һ���ṹ
#define  EVENT_CREATURE_CRAZYDAMAGE								24

// ������
#define  EVENT_CREATURE_BECRAZYHIT								25

// ���ܣ���������һ���ṹ
#define EVENT_CREATURE_HEDGE									26

// ������
#define EVENT_CREATURE_BEHEDGE									27

struct SEventCreatureDamageAction_S
{
	LONGLONG uidMurderer;
	LONGLONG uidCasualty;
};

// ���������¼�
#define EVENT_CREATURE_SETLEADER								29
struct SEventCreatureSetLeader_S
{
	LONGLONG uidMaster;
	LONGLONG uidSlave;
};

// ���︴��
#define EVENT_CREATURE_RELIVE                                   30

// �����ƶ��ٶȻ��ƶ���ʽ�ı�
#define EVENT_CREATURE_CHANGESPEED                              31


// ����ͼ��һ̨������������ת�뵽��һ̨��������ת��ʱ����������� EVENT_PERSON_LOGIN
#define EVENT_PERSON_CHANGE_SERVER_LOGIN						32

// ����ͼ��һ̨������������ת�뵽��һ̨�������� ת��ʱ����������� EVENT_PERSON_LOGOUT
#define EVENT_PERSON_CHANGE_SERVER_LOGOUT						33
struct CEventPersonChangeServerLogOut_S
{
	LONGLONG		uidEntity;		// ʵ��uid
	DWORD           dwDstServerID;  // Ŀ�������ID
};

// �л���
#define EVENT_PET_SETFORMATION									34
struct CEventSetPetFormation_C
{
	int     nFormation;
};	

// ��ѡ���б����
#define EVENT_PET_FORMATIONLIST									35
struct CEventPetFormationList_C
{
	bool	nFormationEnable[6];
};

// �Զ��ƶ��¼�
#define  EVENT_PERSON_AUTOMOVE                                  36
struct CEventPersonAutoMove_C
{
	bool  bAtuoMove;
	int  nStartMoveMapID; // ��ʼ��ͼID
	int  nCurStart_x;     // ��ǰ��ʼλ��X
	int  nCurStart_y;     // ��ǰ��ʼλ��X
	int  m_nAutoMoveMapID; // Ѱ·���յĵ�ͼID
	int  nEndAutoMove_x;   // Ѱ·���յ�����
	int  nEndAutoMove_y;   // 
};

// �����Զ��ƶ�·��
#define  EVENT_PERSON_DRAWAUTOMOVE								37
struct CEventPersonDrawAutoMove_C
{
	bool bTaskTrace; //����׷�� 
	xs::Point ptDest;
};
// ���Ƶ�ͼ�϶�Աͼ��
#define  EVENT_PERSON_DRAWTEAMMEMBERPLACE						38
struct CEventTeamViewMemeberMapPlace_C
{
	int     nMapId;           // ��Ҫ��ʾ��ͼID
	int     nMemberCount;     // ���ڵĶ�Ա����
};

/************************************************************************/
/*  ����ͨ����Ϊ�¼����������Ϊһ�㶼��UI��أ��ͻ����ǰ���ID��place,��������
��������UID�ͳ���uid*/
/************************************************************************/
// �������
#define EVENT_PET_CONJURE										39

// �����ٻ�
#define EVENT_PET_CALLBACK										40

// �������														   
#define  EVENT_PET_COMBINE										41

// �������
#define  EVENT_PET_DISBAND										42

// �������
#define  EVENT_PET_RIDE											43

// ��������
#define  EVENT_PET_DISMOUNT										44

// �������
#define  EVENT_PET_CHANGENAME									45

// �ı������¼�
#define EVENT_CREATURE_CHANGELEADER								46

// ���������¼��壬��Ӵ�������
struct SEventPetAction_S
{
	LONGLONG uidPet;		
	LONGLONG uidMaster;

	SEventPetAction_S():uidPet(INVALID_UID),
						uidMaster(INVALID_UID)
	{}
};

// �ͻ����¼��壬��Ӵ�������
struct SEventPetAction_C : SEventPetAction_S
{
	ulong	 ulSkepID;
	int		 iSrcPlace;
	bool	 bIsPlaceChanged;

	SEventPetAction_C():ulSkepID(INVALID_SKEP_ID),
						iSrcPlace(-1),
						bIsPlaceChanged(false)
	{}
};

// ��ӳ����Զ��ͷż����¼�
#define  EVENT_PET_ADDAUTOSKILL									47
struct  SEventPetActionAddAutoSkill_C
{
	LONGLONG uidPet;
	int      nSkillId[4];
};

//���ﻻװ�¼�
#define	EVENT_PERSON_PERFORM									48
struct	SEventPersonPerform_C
{
	bool	perform;//true������װ����false��ж��װ��
	uchar	part;//��װ����
	ulong	resId[2];//��Դid
	char	bindPoint[2][32];//�󶨵�
	char	animation[32];//��ǰ����
	uchar	weaponsubclass;//�������࣬��������Ч
};

//װ����ʾ�¼�
#define	EVENT_PERSON_PERFORM_SHOW								49
struct SEventPersonPerformShow_C
{
	uchar	part;//����
	bool	show;//�Ƿ���ʾ
};

// TileChange
#define EVENT_CREATURE_TILECHANGE								50
#define EVENT_ADDGOODS_SUCCESS                                  51
struct SEventAddGoodsSuccess_C
{
	LONGLONG uidItem;
	bool     bSystemAdd;    //�Ƿ�Ϊϵͳ���
};

#define EVENT_PET_RIDE_DROPOUT									52
struct SEventRidePetDropOut_C
{
	int nPlace;
};

// ֪ͨ�ͻ��˾Ź��񴴽�ʵ���¼�
#define EVENT_ENTITY_ENTER_MAPGRID                              53
struct SEventEntityEnterMapGrid_S
{
	LONGLONG   uidIncomer;
	LONGLONG   uidActor;
};

//���ﻻװԤ���¼�
#define	EVENT_PERSON_PERFORM_PREVIEW							 54
struct	SEventPersonPerformPreview_C
{
	bool	perform;//true������װ����false��ж��װ��
	uchar	part;//��װ����
	ulong	resId[2];//��Դid
	char	bindPoint[2][32];//�󶨵�
	char	animation[32];//��ǰ����
	uchar	weaponsubclass;//�������࣬��������Ч
};

//װ��Ԥ����ʾ�¼�
#define	EVENT_PERSON_PERFORM_PREVIEW_SHOW						55
struct SEventPersonPerformPreviewShow_C
{
	uchar	part;//����
	bool	show;//�Ƿ���ʾ
};

//װ��Ԥ�������¼�
#define EVENT_PERSON_PERFORM_PREVIEW_RESET						 56

//by cjl
//֪ͨ�ͻ��˸����������������
#define EVENT_PERSON_PRESENT_UPDATE                             57
//�յ��˻�ȡ����Ľ��
#define EVENT_PERSON_PRESENT_RESULT                             58
struct SEventPersonPresent_C 
{
	//���¼�ΪEVENT_PERSON_PRESENT_UPDATEʱ��resultû����
	//���¼�ΪEVENT_PERSON_PRESENT_RESULTʱ
	//result == 1  �����ɹ���
	//result == 2  ���������ϣ�
	//result == 3  ����������
	//result == 4  ����ԭ���ʧ�ܣ�
	int result;
};

//����ս�����ı䣬�ܵ�װ�����ȼ�������仯��Ӱ��
#define EVENT_PERSON_FIGHT_CHANG								59

//�ͻ��˵ļ�������¼�
#define EVENT_PERSON_IDENTIFY_EQUIP					            60

//װ��������ȼ������仯
#define EVENT_EQUIP_SOUL_LEVEL_UPDATE							61
struct SEventEquipSoulLevelUpdate_C
{
	bool bOK;
};
//װ�������ɹ�
#define EVENT_EQUIP_REBUILD_SUCCEED								62
//end cjl

// ����ɾ���꽫
#define EVETN_PET_PERMANENT_DELETE								63
struct SEventPetPermanentDelete_S
{
	LONGLONG uidPet;
};

#define EVENT_PET_BORN											64
struct SEventPetBorn_S
{
	LONGLONG uidPet;
};

//by cjl
//�����¼�
#define EVENT_CREATURE_CHANGEBODY								65
struct SEventChangeBody_C
{
	//Ŀ�����
	//destForm = 0  ��ʾ֪ͨ��ǰ�����modeId��
	//destForm = 1	�������
	//destForm = 2	XP
	//destForm = 3	buff
	//destForm = 4	����
	//destForm = 5	�¼���
	int destForm;

	int	oper;//������һ����˵��0Ϊ���ᣬ1Ϊ�������buff��˵����time����˼����ӦdestForm = 0��ʾmodeId
};
//end cjl

/***************************************************************/
///////////////////// ��ȴϵͳ�¼��� ////////////////////////////
/***************************************************************/
// ��ʼ��ȴ,�ͻ�������תȦ��
#define EVENT_FREEZE_START										200
// �ͻ���
struct SEventFreezeStart_C
{
	DWORD			dwClassID;		// ��ȴ��
	DWORD			dwFreezeID;		// ��ȴID
	DWORD			dwFreezeTime;	// ��ȴʱ��
};

/***************************************************************/
/////////////////// ͨ����Ʒ���¼��� ////////////////////////////
/***************************************************************/
// ��ͨ����Ʒ�������Ʒ
#define EVENT_SKEP_ADDGOODS										210
// ������
struct SEventSkepAddGoods_S
{
	LONGLONG		uidMaster;		// �����
	LONGLONG		uidGoods;		// ��ƷUID
	DWORD			dwSkepID;		// ����ӵ���Ʒ��ID
	int				nPlace;			// ����ӵ�λ��

	DWORD			dwSrcSkepID;	// Դ��Ʒ��ID
};

// ��ͨ����Ʒ��ɾ����Ʒ
#define EVENT_SKEP_REMOVEGOODS									211
// ������
struct SEventSkepRemoveGoods_S
{
	LONGLONG		uidMaster;		// �����
	LONGLONG		uidGoods;		// ��ƷUID
	DWORD			dwSkepID;		// Դ��Ʒ��ID
	int				nPlace;			// λ��

	DWORD			dwTargetSkepID;	// ׼����������Ʒ��ID
	int				nTargetPlace;	// ׼��������λ��
	bool			bDropOut;		// �Ƿ��Ƕ���
	// ������������ֻ�з���¼�����ֵ,����Ҳֻ��link����ʱ���У�
	// �������Ϊ��Чֵ

	SEventSkepRemoveGoods_S():uidMaster(INVALID_UID),
							uidGoods(INVALID_UID),
							dwSkepID(INVALID_SKEP_ID),
							nPlace(-1),
							dwTargetSkepID(INVALID_SKEP_ID),
							nTargetPlace(-1),
							bDropOut(false)
	{

	}

};

// ͨ����Ʒ�������Ʒ
#define EVENT_SKEP_SPLITGOODS									212
// ������
struct SEventSkepSplitGoods_S
{
	LONGLONG		uidOperator;	// ������
	LONGLONG		uidGoods;		// ��ƷUID

	DWORD			dwSkepID;		// ��Ʒ��ID
	DWORD			dwPlace;		// λ��	

	DWORD			dwSplitNum;		// �������		
};

// �ͻ���
struct SEventSkepSplitGoods_C
{
	LONGLONG		uidGoods;		// ��ƷUID

	DWORD			dwSkepID;		// ��Ʒ��ID
	DWORD			dwPlace;		// λ��	

	DWORD			dwSplitNum;		// �������		
};


// ͨ����Ʒ����ĳλ�÷����˱仯
#define EVENT_SKEP_PLACECHANGE									213
// �ͻ���
struct SEventSkepPlaceChange_C
{
	DWORD			dwSkepID;		// ��Ʒ��ID
	DWORD			dwPlace;		// λ��
};

// ͨ����Ʒ�����޸�������
#define EVENT_SKEP_CHANGESIZE									214
// �ͻ���
struct SEventSkepChangeSize_C
{
	DWORD			dwSkepID;		// ��Ʒ��ID
	DWORD			dwMaxSize;		// ��С
};

// ͨ����Ʒ���ڽ�����Ʒ
#define EVENT_SKEP_EXCHANGE										215
// ��������ֻ��ͶƱ�¼�
struct SEventSkepExchange_S
{
	DWORD			dwTargetSkepID;	// Ŀ����Ʒ��ID
};

// ������Ʒ���ĵ�ǰ����
#define EVENT_SKEP_SETCURSUBSKEP								216
//�ͻ���,��Ҫ���װ������
struct SEventSkepSetCurSubskep_C								
{
	DWORD			dwSkepID;		//��Ʒ��ID
	DWORD			dwCurSubskepName;//�����õĵ�ǰ����������
};

// ��������
#define EVENT_SKEP_OPENBAG										217
//�ͻ���
struct SEventSkepOpenBag_C								
{
	DWORD			dwSkepID;	// ��Ʒ��ID
	DWORD			dwPlace;	// λ��
};

// ͨ����Ʒ����ĳλ�÷����˱仯ǰ
#define EVENT_SKEP_PRE_PLACECHANGE								218

// ͨ����Ʒ����������/ɾ����һ���۲���
#define EVENT_SKEP_DONEOBSERVER									219
struct SEventSkepUpdateObserver_S
{
	DWORD			dwSkepID;	// ��Ʒ��ID
	LONGLONG		uidObserver;	
	bool			bIsAdd;
};
struct SEventSkepObserver_C
{
	DWORD			dwSkepID;
	DWORD			dwSkepName;
};

// ͨ����Ʒ������
#define  EVENT_SKEP_CREATE										220
struct SEventSkepCreate_C
{
	DWORD			dwSkepName;
};

//by cjl
//������Ʒ��ע���EVENT_SKEP_REMOVEGOODS��ͬ
#define EVENT_SKEP_DESTROYGOODS									221
struct SEventSkepDestroyGoods_C
{
	DWORD		dwSkepID;			// ��ID
	DWORD		dwPlace;			// λ��
	LONGLONG	uidGoods;			// ��ƷUID
	bool        bDestory;           // �������٣�
	bool        bPet;               // �Ƿ��ǻ꽫��
};
//end cjl

/***************************************************************/
///////////////////////// ���¼��� ////////////////////////////
/***************************************************************/
// �������
#define EVENT_CREATURE_SIT_BREAK								280

/***************************************************************/
///////////////////////// ϵͳ�¼��� ////////////////////////////
/***************************************************************/
// �����˳���
#define EVENT_SYSTEM_BUILDZONE									300
// ������
struct SEventSystemBuildZone_S
{
	DWORD			dwMapID;		// ��ͼID
	DWORD			dwZoneID;		// ����ID
};

// �ͻ���
struct SEventSystemBuildZone_C
{
	DWORD			dwMapID;		// ��ͼID
	DWORD			dwZoneID;		// ����ID
};

// �����˳���
#define EVENT_SYSTEM_DESTORYZONE								301
// ������
struct SEventSystemDestoryZone_S
{
	DWORD			dwMapID;		// ��ͼID
	DWORD			dwZoneID;		// ����ID
};

// �ͻ���
struct SEventSystemDestoryZone_C
{

};



// ��ɫ�뿪����
#define EVENT_SYSTEM_LEAVEZONE								   302
// ������
struct SEventSystemLeaveZone_S
{
	LONGLONG        uID;            // �뿪��
	DWORD			dwMapID;		// ��ͼID
	DWORD			dwZoneID;		// ����ID
};

// �ͻ���
struct SEventSystemLeaveZone_C
{

};

// ����������
#define EVENT_SYSTEM_CLOSEZONESERVER					        304
// ������
struct SEventSystemCloseZoneServer_S
{
	
};

// �ͻ���
struct SEventSystemCloseZoneServer_C
{

};

// �رճ������������� (��û�������Ĺر�)
#define EVENT_SYSTEM_CLOSEZONESERVERORDER					    305

//�����������
#define EVENT_SYSTEM_SAVEPERSONTODB                             306
struct SEventSystemSavePersonToDB_S
{
	ulong ulUserPID;
};

//change zone
#define EVENT_SYSTEM_CHANGEZONE		                            307
struct SEventSystemChangeZone_S
{
	DWORD dwPDBID;
	DWORD dwDstZoneID;
	xs::Point ptDstTile;
};

#define EVENT_SYSTEM_LOADINGFINISH		                         308
struct SEventSystemLoadingFinish_C
{
	int nReason;
};

// ��������������
#define EVENT_SYSTEM_STARTZONESERVER							  309

// ϵͳ���øı�
#define EVENT_SYSTEM_SYSSETCHANGE    							  310
/***************************************************************/
///////////////////// ����ϵͳ�¼��� ////////////////////////////
/***************************************************************/
// ������Ϣ����(���ͻ���)	�����ģ���ʽ����html�ַ���
#define EVENT_CHAT_MSG_ARRIVED									350

struct SEventChat_Msg_Arrived_S
{	
	ulong sender;
	ulong target;
	ulong channelType;
};

#define EVENT_CHAT_SEND_MSG                                     351
struct SEventChat_Send_Msg_C
{	
	ulong channelType;
	ulong target;
};

#define EVENT_CHAT_SHIELD                                       352
struct SEventChat_Shield_C
{	
	ulong target;
	ulong ulInsertPos;
	short bShield;
};

#define EVENT_CHAT_SHIELDSTATECHANGE                             353
struct SEventChat_ShieldChange_C
{
	ulong target;
	ulong ulNewInsertPos;
};
/***************************************************************/
///////////////////// �����������¼��� //////////////////////////
/***************************************************************/
/// ���ǵļ���������ʼ(������:ʱ���������룩)
#define EVENT_SKILL_CHANNEL_START								400

/// ���ǵļ�����������(��������)
#define EVENT_SKILL_CHANNEL_END									401

/// ���Ǽ�������(������:ushort ���ܴ���ID)
#define EVENT_SKILL_UPGRADE										402

// ���ڼ������ݵĸ���(Ŀǰ���ڳ��＼��ɾ���� ͬ���޸�UI)
#define EVENT_SKILL_UPDATE                                      403
struct SEventSkillAction_C
{	
	LONGLONG	uid;		
};

/// ����ʹ��XP������(ŭ������)
#define EVENT_XPSKILL_CANUSE								    404
struct SEventXPSkillCanUse_C
{	
	LONGLONG	uidMaster;		
};

/// XP���ܳ�ʱ������ʹ����(ŭ����Ϊ0)
#define EVENT_XPSKILL_TIMEOUT								   405
struct SEventXPSkillTimeout_C
{	
	LONGLONG	uidMaster;
	char        cXPStateFlag;
};

/// �ͻ���֪ͨ������XP�ڿ�ʼʹ���ˣ��Ա��������ʼ��ʱ
#define EVENT_XPSKILL_BEGIN								       406
struct SEventXPSkillBegin_C
{	
	LONGLONG	uidMaster;
	short       sSkillId;
};

///������֪ͨ�ͻ���XP���Կ�ʼ������
#define EVENT_XPSKILL_CANBOOT							   407
struct SEventXPSkillCanBoot_C
{	
	LONGLONG	uidMaster;
};

// ���ڼ��ܾ���ĸ���(��ͬ���ȼ�)                                          
#define EVENT_SKILL_EXP_UPDATE                                 408

/***************************************************************/
////////////////////// �ɼ�ϵͳ�¼��� /////////////////////////
/***************************************************************/
// ׼���ɼ�����
#define EVENT_COLLECT_PREPARE                                  450

// ��ʼ�ɼ�����
#define EVENT_COLLECT_WAIT                                     451

// ��ʼ�ɼ�
#define EVENT_COLLECT_START                                    452
struct SEventCollect_S
{
	LONGLONG		uidMaster;               // ˭��Ĳɼ�����
	LONGLONG		uidMonster;              // �ĸ��ɼ�����
};

// ���ݱ�ը add by zjp
#define EVENT_BUBBLE_BOMB									   499
struct SEventBubbleBomb
{
	xs::Point		BombCenterTile;
};

/***************************************************************/
////////////////////// ���ǽ����¼��� ///////////////////////////
/***************************************************************/
// ������
#define EVENT_TRADE_REQUEST										500
struct SEventTradeRequest_C
{	
	LONGLONG	uidDemander;		// ˭������
};

// ���׿�ʼ
#define EVENT_TRADE_GO											501
struct SEventTradeGo_C
{	
	LONGLONG	uidTarget;			// ��˭����	
	ulong		skepId;				// �Լ��Ľ�����Ʒ��ID	
	ulong		skepIdTarget;		// �Է��Ľ�����Ʒ��ID
};

// ȡ������
#define EVENT_TRADE_CANCEL										502
struct SEventTradeCancel_C
{	
	LONGLONG	uid;				// ˭ȡ���˽���,�������Լ�
};

// �������߽���
#define EVENT_TRADE_LOCK										503
struct SEventTradeLock_C
{	
	bool		myself;				// �Լ���״̬���ǶԷ���״̬	
	bool		lock;				// �������ǽ���
};

// ����ȷ��
#define EVENT_TRADE_CONFIRM										504
struct SEventTradeConfirm_C
{	
	bool		myself;				// �Լ�ȷ�����ǶԷ�ȷ��
};

// �������
#define EVENT_TRADE_FINISH										505

// ǰ��һ�������Ƿ�����Դָ��ģ�
// ����Ǹ��ݽ���˫���������͵ģ��������Խ�ʡ����Ҫ�ĵ���
#define EVENT_TRADE_FINISH_SRC									506
struct SEventTradeFinish_C
{
};

struct SEventTradeFinish_S
{
	ulong ulPersonPID;
	ulong ulNegotiantPID;	
};

// �Է��ı��Ǯ��Ŀ
#define EVENT_TRADE_UPDATE_MONEY								507
struct SEventTradeUpdateMoney_C
{
	ulong		money;
};

// �Է��ı�Ԫ����Ŀ
#define EVENT_TRADE_UPDATE_GOLD									508
struct SEventTradeUpdateGold_C
{
	ulong		gold;
};

/***************************************************************/
////////////////////// ��������¼��� ///////////////////////////
/***************************************************************/
// ���ٶ����¼�
#define  EVENT_TEAM_DESTROY                                 538
struct SEventTeamDestroy_S
{
	DWORD	 dwTeamID;					// ����ID
	DWORD    dwCaptainDBID;             // �ӳ�ID
};
// ���������¼�
#define  EVENT_TEAM_CREATE                                  539
struct SEventTeamCreate_S 
{
	char        szName[32];                 // ��������
	DWORD		dwPDBID;					// PDBID
	DWORD		dwTeamID;					// ����ID
	DWORD		dwCaptain;					// �ӳ�
	DWORD       dwTeamMode;                 // ��������
	DWORD		dwGoodsAllotMode;			// ��Ʒ����ģʽ
	DWORD       dwPetAllotMode;             // �������ģʽ
	bool        bPrivateOpen;               // ˽��ר������
};

// �ı�ӳ�
#define  EVENT_TEAM_CHANGECAPTAIN                           540
struct SEventTeamChangeCaptain_S
{
	DWORD  dwCaptainPDBID;
	DWORD  dwTeamID;
	DWORD  dwOldCaptainPDBID;
};

// �����˶���
#define EVENT_TEAM_PERSONJOIN                               541

struct SEventTeamComm_S
{
	DWORD  dwPDBID;
	DWORD  dwCaptainDBID;
	DWORD  dwTeamID;
};
// �뿪����
#define EVENT_TEAM_PERSONQUIT                               542
struct SEventTeamQuitTeam_S
{
	DWORD  dwPDBID;
	DWORD  dwTeamID;
	bool   blogOut;
};

// ����random�¼�
#define  EVENT_TEAM_RANDOMDIDA                               543
struct SEventTeamRandomDida_C
{
	DWORD		dwPDBID;  // ����˭
	DWORD    dwTeamID;    // ����ID��
	DWORD    dwGoodsID;   // ID   
	int      nStayTime;   // �¼����� 
	int      nNumber;     // �����������
	LONGLONG UidGoods;    // ��ƷUID 
	int      nReandomGoodType; // ��Ʒ����
	long     lImageID;    //����Ӧ��Ʒ��ͼƬID
};	
// ����ӳ��¼�
#define  EVENT_TEAM_FOLLOWCAPTAIN                            544
struct SEventTeamFollowCaptain_C
{
      LONGLONG uid;
};
// ������Ϣ��ѯ�¼�
#define  EVENT_TEAM_SELFMESSAGEVIEW                           545
struct SEventTeamMessageView_C	// ������Ϣ
{
	char  szName[32];     // ��������
	DWORD dwTeamMode;               // ����ģʽ
	DWORD dwGoodsAllotMode;         // �������ģʽ
	DWORD dwPetAllotMode;           // ��ʯ����ģʽ
	DWORD dwCaptainID;              // �ӳ�ID
	DWORD dwMemberCount;            // ��Ա��Ŀ
	DWORD dwCaptainArmyID;          // ��������
	DWORD dwCaptainHomage ;         //��������λ
	bool  bPrivate;                // �Ƿ�˽��
	bool  bClick;
	SEventTeamMessageView_C(void)
	{
		memset(this, 0, sizeof(*this));
	}
};
// �����������¼�
#define EVENT_TEAM_APPLY                                       546
struct SEventTeamApply_C
{
   char szTeamApply[512];         // ����
   int  nDialoc;                  // �δ�������ӵ�λ��
   SEventTeamApply_C(void)
   {
	   memset(this, 0, sizeof(*this));
   };
};
// ��������List �¼�
#define EVENT_TEAM_SEARCH                                       547

struct SEventTeamSearch_C
{
	DWORD dwPDBID; 
	int nCount; 
	// �������
};

// ����ر����
#define EVENT_TEAM_CLOSEUI										548
struct SEventTeamCloseUI_C
{	
};

// ���Ӷ���
#define EVENT_TEAM_ADDMEMBER									549
struct SEventTeamAddMember_C
{
	DWORD		dwPDBID;
	DWORD       dwLevel;                    // �ȼ�
	char		szName[MAX_PERSONNAME_LEN];
	long		lFaceID;
	bool		bOnline;
	bool		bCaptain;
};

// �Ƴ�����
#define EVENT_TEAM_REMOVEMEMBER									550
struct SEventTeamRemoveMember_C
{
	DWORD		dwPDBID;		// pdbid
};

// ���Ķ�������
#define EVENT_TEAM_CHANGEMEMBER									551
struct SEventTeamChangeMember_C
{
	DWORD		dwPDBID;
	DWORD       dwLevel;
	char		szName[MAX_PERSONNAME_LEN];
	long		lFaceID;
	bool		bOnline;
	bool		bCaptain;
};

//������⿽����Ʒ
#define  EVENT_ADD_DUMMYCOPY                                    554
struct SEventSkepAddDummyCopy_S
{
	LONGLONG		uidMaster;		// �����
	LONGLONG		uidGoods;		// ��ƷUID
	DWORD			dwDCSkepID;		// ������ӵ���Ʒ��ID
	int				nDCPlace;		// ������ӵ�λ��

	DWORD			dwSrcSkepID;	// Դ��Ʒ��ID
};

//�Ƴ����⿽����Ʒ
#define  EVENT_REMOVE_DUMMYCOPY                                 555
struct SEventSkepRemoveDummyCopy_S
{
	LONGLONG		uidMaster;		// �����
	LONGLONG		uidGoods;		// ��ƷUID
	DWORD			dwSkepID;		// Դ��Ʒ��ID
	int				nPlace;			// λ��

	DWORD			dwDCSkepID;	// ���⿽������Ʒ��ID
	int				nDCPlace;	// ���⿽������ʾλ��
};
//��������λ�ø���
#define  EVENT_SKPE_PET_PLACECHANGE                                 556
struct SEventSkepPetPlaceChange_C
{
	DWORD			dwSkepID;		 // ������ID
	DWORD			dwPlace;		 // Դλ��
	int             nExProp;		 // �������ԣ�Ŀǰר�����󷨺ͷ��
	int				nExPropValue;	 // ��������ֵ��Ŀǰר�����󷨺ͷ��
	LONGLONG        uidGoods;        // ����UID 
	bool	        bLink;	         // �Ƿ�����
};
// ���������¼� 
#define  EVENT_PET_UPGRADE                                          557
struct SEventPetUpgrade_S
{
	// ...............
};

// ������״̬����
#define  EVENT_PET_UPDATA_FORMATION                                 558
struct SEventPetFormation_C
{
	int formation;
};

/***************************************************************/
////////////////////// ����ϵͳ�¼��� ///////////////////////////
/***************************************************************/
//  ��ҿ��Խ��ܵ�����������Ŀ��
#define PERSON_HOLD_TASK_MAX_COUNT 25

//  ÿ������������������
#define TASK_REQUIREMENT_MAX_COUNT 15

//  �ѽ���������ݶ�ȡ��ɣ�
#define EVENT_READ_HOLDTASK_DATA 601
//  �������������ݶ�ȡ��ɣ�
#define EVENT_READ_ACCOMPLISHEDTASK_DATA 602
struct SEventSystemReadTaskData_S
{
    DWORD dwHolder;
};

//  ���һ�������¼��
#define EVENT_TASK_ADDRECORD 603
struct CEventTaskAddRecord_C
{
    WORD m_wTaskID;
	WORD m_wTraceIndex;
};

//  ����һ�������¼��
#define EVENT_TASK_UPDATERECORD 604
struct CEventTaskUpdateRecord_C
{
    WORD m_wTaskID;
	uchar ucIndex;
    ushort usValue;
};

//  ���һ������
#define EVENT_TASK_ACCOMPLISH 605
struct CEventTaskAccomplish_C
{
    WORD m_wTaskID;
};

//  ��ʼ���ѽ�������Ϣ��
#define EVENT_TASK_INITIAL_HOLD_TASK 606

//	��ʼ���ɽ�������Ϣ��
#define EVENT_TASK_INITIAL_CANACCEPT_TASK 607

// �Ƴ�һ������ 
#define EVENT_TASK_REMOVE_TASK       608
struct CEventTaskRemove_C
{
	WORD m_wTaskID;
};

// �������
#define EVENT_TASK_FLYRIDE_TASK       609
struct CEventTaskFlyRide_C
{
	WORD m_wTaskID;
	WORD m_wNPCID;
	WORD m_wModelID;
	WORD m_wCurSpeed;
};

// ������ʾͼƬ
#define  EVENT_TASK_SEND_IMAGEINFO    610
struct CEventTaskImageInfo_C
{
	char  szImageName[64];       // ͼƬ���֣�
};

/////////////////��У�Ұ��꽫ˢ��/////////
// Bossˢ����ʾ�¼�
#define  EVENT_TASK_NOTICE_BOSSREFRESH    611
struct CEventTaskNoticeBossRefresh_C
{
	char  szBossName[64];       // Boss���֣�
};

/////////////////��У���Ұ�����ȡ���/////////
// ��Ұ�����ȡ���
#define  EVENT_TASK_NOTICE_BINDDATA_COMPLETE    612
struct CEventTaskNoticeBindDataComplete_S
{

};

/////////////////��У�Ұ��꽫״̬/////////
// Bossˢ����ʾ�¼�
#define  EVENT_TASK_UPDATE_AMUSEMENTBOSS    613
struct CEventTaskUpdateAmusementBoss_C
{
	char  szBossName[64];       // Boss���֣�
	bool  bDeath;
};
/***************************************************************/
////////////////////// �����¼��� ///////////////////////////
/***************************************************************/
//��ҽ��븱������ͬ��
//����ҽ��븱��֮�󣬸�������������LUA�����������ҽ���ĳ������ͼ�Ĵ���
//�����븱��֮ǰ��Ҫ����ͨ��������ȡ�Ѿ�����ø����Ĵ�������Ϊ��ʾ���߼��ж�
//����Ҫ�����߷�����������ͬ��

#define	EVENT_SYNC_RESET_INSTANCE_MAP_ENTER_TIMES_ALL		699
struct SEventSyncResetInstanceMapEnterTimesAll
{
	int nMapID;
};


#define	EVENT_SYNCHRONIZE_INSTANCE_MAP_ENTER_TIMES		700
struct SEventSynchronizeInstanceMapEnterTimes
{
	int nActorDBID;
	int nMapID;
	int nTimes;
};


//���ĵ�ǰ���������Ĺؼ�����ID//�ŶӸ����У��ӳ��ı�����Ҫ֪ͨ����������
#define	EVENT_SET_INSTANCE_ZONE_KEY_ACTOR				701
struct SEventSetInstanceZoneKeyActor
{
	int nOldKeyActorDBID;
	int nNewKeyActorDBID;
	int nMapID;
};


//���ø���,ǿ�ȸ�����ȫ������뿪ĳ��ǰ�����������ص����븱��֮ǰ�ĵ�ͼ��λ��
#define EVENT_RESET_INSTANCE_ZONE						702
struct SEventResetInstanceZone
{
	int nKeyActorDBID;
	int nMapID;
};

//�������Լ�Ϊ�ؼ���������и���
#define EVENT_RESET_ALL_INSTANCE_ZONE					703
struct SEventResetAllInstanceZone
{
	int nActorDBID;
};


enum EInstanceKickReason//���߳�������ԭ��
{
	E_INSTANCE_ZONE_BEING_RESET,					//�������������ã������е���������
	E_INSTANCE_ZONE_HAS_DESTROYED,					//����������̫�ã������Ѿ������٣�������������������Ҫ�����߳�ȥ
	E_INSTANCE_ZONE_NOT_MEMBER_OF_KEY_ACTOR,        //�����Ǹ����ؼ�����ļ�����ĳ�Ա�������ŶӸ����뿪����
	E_INSTANCE_ZONE_INVALID_REASON,					//��Ч���ɣ�ֻ�������ж��Ƿ����Ҫ���˵Ŀ���
};

#define BACKMAP_WAIT_SECONDS 30
//��ʱ��ʼ��30���Ӻ�ǿ��ĳ����뿪ĳ��ǰ�����������ص����븱��֮ǰ�ĵ�ͼ��λ�ã�(��������뿪����֮��ʱ����)

#define EVENT_START_TIMER_KICK_PERSON_TO_BACKMAP		704
struct SEventStartTimerKickPersonToBackMap
{
	int nActorDBID;
	enum EInstanceKickReason eResult;
	int nWait;     //�ȴ�ʱ�䣬30s
};

//ǿ��ĳ����뿪ĳ��ǰ�����������ص����븱��֮ǰ�ĵ�ͼ��λ�ã�(��������뿪����֮��ʱ����)
#define EVENT_KICK_PERSON_TO_BACKMAP_NOTIFY				705 //����֮ǰ����֪ͨ "�������ڵ�ǰ������10���Զ��뿪��";//������������֪ͨ XXX��������XXX�������......
#define EVENT_KICK_PERSON_TO_BACKMAP					706
struct SEventKickPersonToBackMap
{
	int nActorDBID;
};
#define EVENT_STOP_TIMER_KICK_PERSON_TO_BACKMAP          707 //ֹͣ�뿪�����Ķ�ʱ����
struct SEventStopTimerKickPersonToBackMap
{
	int nActorDBID;
};

#define  EVENT_ADD_NORMAL_ATTACK						708
struct SEventAddNormalAttack
{
	UID	 uidTarget;
};

// ���㱩��֮ǰ�����¼�����Ҫ��ȷ���Ƿ����߱���
#define  EVENT_CREATURE_BEFORECRAZYDAMAGE               709

// �Զ��ظ�
#define  EVENT_CREATURE_NEED_RECOVER                    710

// �ɼ���Ծ�¼�
#define  EVENT_CREATURE_COLLECT_JUMP                    711
struct SEventActionCollectJump_C
{
	int nEndPtX;
	int nEndPtY;
	int nTaskID;
};

// NPCͷ��������Ч��ʾ
#define  EVENT_PLAY_EFFECT_TOPMOST                    712
struct SEventActionPlayEffectTopMost_C
{
	char      szTipText[64];             // ��ʾ����
	LONGLONG  uidMonster;
	ulong     ulEffectID;
	bool      bNeedClick;
};

// NPCͷ��������Ч��ʾ
#define  EVENT_STOP_EFFECT_TOPMOST                    713
struct SEventActionStopEffectTopMost_C
{
	LONGLONG  uidMonster;
	ulong     ulEffectID;
};
/***************************************************************/
//////////////////////����ϵͳ�¼��� ///////////////////////////
/***************************************************************/
#define EVENT_FRIEND_INVITE                              801
struct  SEventFriend_AppAddFriend
{
	ulong   appUserID;                   /// ������PID
	char   name[MAX_PERSONNAME_LEN];	/// ����������
	ulong  level;						/// �����ߵȼ�
	int    nCreatureVocation;           /// ������ְҵ
	SEventFriend_AppAddFriend(void)
	{
		memset(this, 0, sizeof(*this));
	};
};    

#define EVENT_FRIEND_REMOVEFRIEND									802
struct  SEventFriend_RemoveFriend
{
	ulong friendPID;
	int  nGroupID;
	char   name[MAX_PERSONNAME_LEN];	/// ����
	SEventFriend_RemoveFriend(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define EVENT_FRIEND_ADDGROUP										803
struct  SEventFriend_AddGroup
{
	int  nGroupID;
	SEventFriend_AddGroup(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define  EVENT_FRIEND_CHANGEGROUPNAME                           804

#define  EVENT_FRIEND_MOVEFRIEND								805
struct  SEventFriend_MoveFriend
{	
	ulong friendPID;
	int  nOldGroupID;
	int  nNewGroupID;
	char   name[MAX_PERSONNAME_LEN];	/// ����
	SEventFriend_MoveFriend(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define  EVENT_FRIEND_UPDATEALLFRIEND							806
struct  SEventFriend_UpdateAll
{
	ushort usRelation;
	SEventFriend_UpdateAll(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define  EVENT_FRIEND_FRIENDLOGOFF								807
struct  SEventFriend_FriendLOGOFF
{	
	ulong userPID;
	ulong friendPID;
	int   nGroupID;
	ushort usRelation;
	SEventFriend_FriendLOGOFF(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define  EVENT_FRIEND_UPDATE									808
struct  SEventFriend_FriendUpdate
{	
	ulong userPID;
	ulong friendPID;
	SEventFriend_FriendUpdate(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define  EVENT_FRIEND_ASKADDENEMY							     809

#define  EVENT_FRIEND_REMOVEENEMY							     810

#define EVENT_FRIEND_AddRecentComm                               811
struct  SEventFriend_AddRecentComm
{	
	ulong oldFirstPID;
	ulong curFirstPID;
	SEventFriend_AddRecentComm(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define EVENT_FRIEND_UPDATEPOINT								812

#define EVENT_FRIEND_LEVELCHANGE								813
struct  SEventFriend_LevelChange
{	
	ulong ulUserPID;
	ulong ulFriendPID;
	int   nOldLevel;
	int   nCurLevel;
	SEventFriend_LevelChange(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define  EVENT_FRIEND_FRIENDLogin								814
struct  SEventFriend_FriendLogin
{	
	ulong userPID;
	ulong friendPID;
	int   nGroupID;
	ushort usRelation;
	SEventFriend_FriendLogin(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define  EVENT_FRIEND_UPDATEGROUP								815
struct  SEventFriend_UpdateGroup
{	
	ulong friendPID;
	int   nGroupID;
	ushort usRelation;
	SEventFriend_UpdateGroup(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define EVENT_FRIEND_SHIELD										 816
struct  SEventFriend_Shield
{
	ulong friendPID;
	ushort usShield; //0 ���� 1 �������
	SEventFriend_Shield(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

#define  EVENT_FRIEND_ADDFRIEND								  817
struct  SEventFriend_AddFriend
{
	ulong personID;
	ulong friendPID;
	int   nGroupID;
	ushort usRelation;
	SEventFriend_AddFriend(void)
	{
		memset(this, 0, sizeof(*this));
	};
};

#define  EVENT_FRIEND_UpdateEnemyMapPos						    818

#define  EVENT_STALL_OPENSTALLFLAG								 850
struct  SEventStall_OpenStallFlag
{	
	int   nStallID;
	SEventStall_OpenStallFlag(void)
	{
		memset(this, 0, sizeof(SEventStall_OpenStallFlag));
	};
};

#define  EVENT_STALL_UPDATESTALLINFO						     851
struct  SEventStall_UpdateStallInfo
{	
	int   nStallID;
	int	  nPropType;
	int   nValue;
	DWORD dwValue;
	uchar uEndStall;
	SEventStall_UpdateStallInfo(void)
	{
		memset(this, 0, sizeof(SEventStall_UpdateStallInfo));
	};
};

#define  EVENT_STALL_STARTSTALL									852
struct  SEventStall_StartStart
{	
	int   nStallID;
	ushort usRemote;
	SEventStall_StartStart(void)
	{
		memset(this, 0, sizeof(SEventStall_StartStart));
	};
};

#define EVENT_STALL_DRAGOUT										853
struct  SEventStall_DragOut
{	
	DWORD   dwSkepID;
	int     nPlace;
	int     nTargetPlace;
	SEventStall_DragOut(void)
	{
		dwSkepID = 0;
		nPlace = -1;
		nTargetPlace = -1;
	};
};

#define  EVENT_STALL_AddSellGoods					     854
struct  SEventStall_UpdatePrice
{
	int nStallID;
	LONGLONG uGOODSID;
	int nPlace;
	DWORD dwPrice;
	ushort usPriceType;
	ulong ulSrcPackID;
	int nSrcPlace;
	int nNum;
	SEventStall_UpdatePrice()
	{
		memset(this, 0, sizeof(SEventStall_UpdatePrice));
	}
};

#define  EVENT_STALL_AddBuyGoods	    					     855
struct  SEventStall_AddBuyGoods
{
	int nGoodsID;
	int nNum;
	int nTargetPlace;
	DWORD dwPrice;
	ushort usPriceType;
	SEventStall_AddBuyGoods()
	{
		memset(this, 0, sizeof(SEventStall_AddBuyGoods));
	}
};

#define  EVENT_STALL_RemoveBuyGoods	    					     856
struct  SEventStall_RemoveBuyGoods
{
	int nGoodsID;
	SEventStall_RemoveBuyGoods()
	{
		memset(this, 0, sizeof(SEventStall_RemoveBuyGoods));
	}
};

#define  EVENT_STALL_UndoBuyGoods	    					     857
struct  SEventStall_UndoBuyGoods
{
	ulong ulSrcSkepID;
	SEventStall_UndoBuyGoods()
	{
		memset(this, 0, sizeof(SEventStall_UndoBuyGoods));
	}
};

#define  EVENT_STALL_UpdateTotalPrice							 858
struct  SEventStall_UpdateTotalPrice				
{
	uint64 u64TotalMoney;
	uint64 u64TotalGoldIngot;
	SEventStall_UpdateTotalPrice()
	{
		memset(this, 0, sizeof(SEventStall_UpdateTotalPrice));
	}
};

#define  EVENT_STALL_ENDSTALL									  859
struct  SEventStall_EndStall
{	
	int   nStallID;
	SEventStall_EndStall(void)
	{
		memset(this, 0, sizeof(SEventStall_EndStall));
	};
};

#define  EVENT_STALL_RemoveSellGoods								860
struct  SEventStall_RemoveSellGoods
{	
	ulong ulSrcSkepID;
	int nSrcPlace;
	SEventStall_RemoveSellGoods(void)
	{
		memset(this, 0, sizeof(SEventStall_RemoveSellGoods));
	};
};

#define  EVENT_STALL_STATUSCHANGE									 861
struct  SEventStall_StatusChange
{	
	int nStallID;
	ushort usLastStatus;
	SEventStall_StatusChange(void)
	{
		memset(this, 0, sizeof(SEventStall_StatusChange));
	};
};

#define  EVENT_STALL_UPDATERECYCLEMONEY									862
struct  SEventStall_UpdateRecycleMoney
{	
	int nStallID;
	ulong dbidPerson;
	uint64 ulMoney;
	SEventStall_UpdateRecycleMoney(void)
	{
		memset(this, 0, sizeof(SEventStall_UpdateRecycleMoney));
	};
};

#define  EVENT_STALL_ADDLEAVEWORD							            863
struct  SEventStall_AddLeaveWord	
{
	int nStallID;
	ulong dbidPerson;
	char  szName[MAX_PERSONNAME_LEN];
	char  szLeaveWord[STALL_LEAVEWORD_MSG_LEN];
	SEventStall_AddLeaveWord(void)
	{
		memset(this, 0, sizeof(SEventStall_AddLeaveWord));
	};
};

#define  EVENT_STALL_CLEARLEAVEWORD							            864
struct  SEventStall_ClearLeaveWord	
{
	int nStallID;
};

#define  EVENT_STALL_LASTSTALLCHANGE							        865
struct SEventStall_LastStallChange
{
	ulong dbidPerson;
	int nLastStallID;
	int nCurStallID;
};

#define  EVENT_STALL_UPDATEINCOMEINFO							        866
struct SEventStall_UpdateIncomeInfo
{
	int nStallID;
	ulong ulRent;	
};

#define  EVENT_STALL_OPERATESTALL							           867
struct SEventStall_OperateStall
{
	int nStallID;
	int nMapID;
	int nTileX;
	int nTileY;
	ushort usType;	
};

#define  EVENT_STALL_UpdateSellGoodsNum									868
struct  SEventStall_UpdateSellGoodsNum	
{	
	int nPlace;
	int nNum;
	DWORD dwPrice;
	ushort usPriceType;
	SEventStall_UpdateSellGoodsNum(void)
	{
		memset(this, 0, sizeof(SEventStall_UpdateSellGoodsNum));
	};
};

#define  EVENT_STALL_SyncBuyGoods									    869


#define EVENT_USE_SKILL												    870
struct SEventUseSkill
{
	UID		srcUID;					// ������
	UID		destUID;				// ������
	int		nSkillID;				// ����ID
	int		nSubID;					// ���ܵȼ�
	SEventUseSkill()
	{
		memset(this, 0, sizeof(SEventUseSkill));
	}
};

#define  EVENT_SKILL_DISPLAYDAMAGEINFO							         871

#define  EVENT_SKILL_JUMPFINISH									         872
#define  EVENT_SKILL_COLLECTJUMPFINISH                                   873

#define  EVENT_SKILL_ATTACK												 874
struct SEventAttack
{
	UID		srcUID;			// ������
	UID		destUID;		// ������
	int		nSkillID;		// ����ID
	int		nSubID;			// ���ܵȼ�
};



#define  EVENT_ENTITY_BINDTOOLTP										 900

#define  EVENT_FAMILY_UPDATEFAMILY	                                     901
struct SEventUpdateFamily
{
	ulong dbidLeader;
};

#define  EVENT_FAMILY_ADDMEMBER	                                         902
struct SEventAddFamilyMember
{
	ulong dbidLeader;
	ulong dbidMember;
};

#define  EVENT_FAMILY_DISBANDFAMILY                                      903

#define  EVENT_FAMILY_JOINFAMILY                                         904
struct SEventJoinFamily
{
	ulong dbidPerson;
	ulong dbidLeader;	
};

#define  EVENT_FAMILY_QUITFAMILY                                         905
struct SEventQuitFamily
{
	ulong dbidPerson;
};

#define  EVENT_FAMILY_INVITEJOIN                                         906
struct SEventInviteJoin
{
	ulong dbidInviter;
	char szInviterName[MAX_PERSONNAME_LEN];  // �峤����
	char szFamilyName[FAMILY_NAME_LEN + 1];  // ��������
};

#define  EVENT_FAMILY_UPDATEMEMBER	                                      907

#define  EVENT_FAMILY_DEMISE	                                          908
struct SEventFamilyDemise
{
	ulong dbidLeader;	
};


#define  EVENT_FAMILY_MEMBERONLINECHANGE	                              909
struct SEventMemberOnlineChange
{
	ulong dbidLeader;	
	ulong dbidPerson;
	uchar  bOnline;
};


// ����
#define  EVENT_ACTION_SIT											910

// ����ѣ�ο������¼�
#define  EVENT_ACTION_STUN											911
struct SEventStun
{

};

#define EVENT_ACTION_ANIMATION										912
struct SEventAnimation
{
	int	 nActionID;
};

/***************************************************************/
////////////////////// �����¼��� ///////////////////////////
/***************************************************************/
// new Skill
struct SEVENTSKILLHEAD
{
	int			nSkillID;
	LONGLONG	uidSrc;
	LONGLONG	uidDest;
};

#define  EVEN_SKILL_REQUESTSKILLCONTION							    950
struct SEventSkillConditionData : public SEVENTSKILLHEAD
{
};

// ===============��������================
// �������
#define  EVENT_SKILL_MISS											951
struct SEventSkillMiss : public SEVENTSKILLHEAD
{
};

// ����
#define  EVENT_SKILL_HIT											952
struct SEventSkillHit : public SEVENTSKILLHEAD
{
};

// ����
#define  EVENT_SKILL_DOUBLE											953
struct SEventSkillDouble : public SEVENTSKILLHEAD
{
};

// =============��������===================
// ����
#define  EVENT_SKILL_DUCK											954
struct SEventSkillDuck : public SEVENTSKILLHEAD
{
};

// ������
#define  EVENT_SKILL_BEHIT											955
struct SEventSkillBeHit : public SEVENTSKILLHEAD
{
};

// ������
#define  EVENT_SKILL_BEDOUBLE										956
struct SEventSkillBeDouble : public SEVENTSKILLHEAD
{
};

// ===========��������=================
// �Լ�����
#define  EVENT_SKILL_SELFDEAD										957
struct SEventSkillSelfDead : public SEVENTSKILLHEAD
{
};

// Ŀ������
#define  EVENT_SKILL_TARGETDEAD										958
struct SEventSkillTargetDead : public SEVENTSKILLHEAD
{
};

#define  EVENT_SKILL_FINISH										959
struct SEventSkillFinish : public SEVENTSKILLHEAD
{

};

// ==========����ֵ����==============
#define EVENT_SKILL_SELFHP										960
struct SEventSkillSelfHP : public SEVENTSKILLHEAD
{

};

#define EVENT_SKILL_TARGETHP			961
struct SEventSkillTargetHP : public SEVENTSKILLHEAD
{

};

// =========��ǰ����ֵ����=============
#define  EVENT_SKILL_SELFMP				962
struct SEventSkillCurSelfMP : public SEVENTSKILLHEAD
{
	int nChangePropVal;
};

#define EVENT_SKILL_TARGETMP			963
struct SEventSkillTargetMP : public SEVENTSKILLHEAD
{

};

// =========���봥��==============
#define EVENT_SKILL_DISTANCE			964
struct SEventSkillDistance : public SEVENTSKILLHEAD
{

};

// =======��ӿ���Debuff======
#define EVENT_SKILL_ADDCONTROLBUFF		965
struct SEventSkillBuff : public SEVENTSKILLHEAD
{
	int nBuffTime;
};

// =======�˺��¼�===========
#define EVENT_SKILL_DAMAGE				966
struct SEventSkillDamage : public SEVENTSKILLHEAD
{
	int nDamage;
};

// ======�����=========
#define  EVENT_SKILL_ACTIVE			967
struct SEventSkillActive : public SEVENTSKILLHEAD
{

};

// ====�������޸ı䴥��=====
#define  EVENT_SKILL_MAX_HP_CHANGE		968
struct SEventSkillMaxHPChange : public SEVENTSKILLHEAD
{
	int nChangePropValue;
};

// ====�������Ĵ���=======
#define  EVENT_SKILL_CONSUME			969
struct SEventSkillConsume : public SEVENTSKILLHEAD
{

};

// �뿪����
#define  EVENT_SKILL_QUIT_TEAM			970		

// �������
#define  EVENT_SKILL_ENTER_TEAM			971

// ����ͼ 
#define  EVENT_SKILL_CHANGE_MAP			972
struct SEventSkillChangeMap : public SEVENTSKILLHEAD
{
	DWORD dwTeamID;
	DWORD dwPDBID;
	DWORD dwOldMapID;
	DWORD dwNewMapID;
};

// װ����Ʒ
#define  EVENT_EQUIP_EQUIPMENT			973

// ������,������������
#define  EVENT_SKILL_END_AROSE			974

#define  EVENT_SKILL_CONSUME_CHANGE     975
struct SEventChangeSkillConsume
{
	int		nMPConsumeChangePct;		// �������ĸı��
	SEventChangeSkillConsume()
	{
		memset(this, 0, sizeof(*this));
	}
};

// ������������
#define  EVETN_SKILL_HIT_END_AROSE		976

// ��Ԫ�����������˺�
#define  EVENT_SKILL_ABSORB_DAMAGE		977


// ���Ŵ���
#define  EVENT_ARMY_CREATE			    978
struct SEventArmyCreate
{
	DWORD dwLeaderID;
	char szName[ARMY_NAME_LEN + 1];
	SEventArmyCreate()
	{
		memset(this, 0, sizeof(SEventArmyCreate));
	}
};

#define  EVENT_FAMILY_JOINARMY	         979
struct SEventFamilyJoinArmy
{
	ulong dbidArmyLeader;	
};

//�򿪼�����Ӫ���
#define Event_ACTION_JOIN_CAMP_WND       980

//�򿪸ı���Ӫ���
#define Event_ACTION_CHANGE_CAMP_WND	 981

// ����¼���
#define EVENT_ALL_MAXID					1000

#pragma pack()