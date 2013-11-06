/*******************************************************************
** �ļ���:	e:\Rocket\Common\DGlobalMisc.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2008/2/26  21:02
** ��  ��:	1.0
** ��  ��:	ȫ�ֱȽ��ӵĶ���
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#include "DEntityProp.h"

#pragma pack(1)

/////////////////////////// Ч���鶨��  ////////////////////////////
enum
{
	EEffectGroupID_NULL            = 0,

	/******************zhangjie new******************/
	// ����HP����
	EN_EFFECTGROUPID_BASE_MAX_HP,// �������������������ֵ
	EN_EFFECTGROUPID_BASE_MAX_HP_RATIO,// ���������������������ֵ����ֱȣ�
	EN_EFFECTGROUPID_SUM_MAX_HP_RATIO,// �������ﵱǰ�����������ֵ����ֱȣ�

	// MP����
	EN_EFFECTGROUPID_BASE_MAX_MP,// �������������������ֵ
	EN_EFFECTGROUPID_BASE_MAX_MP_RATIO,// ���������������������ֵ����ֱȣ�
	EN_EFFECTGROUPID_SUM_MAX_MP_RATIO,// �������ﵱǰ�����������ֵ����ֱȣ�

	// ��С������
	EN_EFFECTGROUPID_WEAPON_MIN_P_A_RATIO,// ������������������С��ֵ����ֱȣ�
	EN_EFFECTGROUPID_BASE_MIN_P_A,// �����������������Сֵ
	EN_EFFECTGROUPID_BASE_MIN_P_A_RATIO,// �����������������С��ֵ����ֱȣ�
	EN_EFFECTGROUPID_SUM_MIN_P_A_RATIO,// ���ӵ�ǰ����������С��ֵ����ֱȣ�

	// ���������
	EN_EFFECTGROUPID_WEAPON_MAX_P_A_RATIO,// ��������������������ֵ����ֱȣ�
	EN_EFFECTGROUPID_BASE_MAX_P_A,// ������������������ֵ
	EN_EFFECTGROUPID_BASE_MAX_P_A_RATIO,// �������������������ֵ����ֱȣ�
	EN_EFFECTGROUPID_SUM_MAX_P_A_RATIO,// ���ӵ�ǰ������������ֵ����ֱȣ�

	// ������(����)
	EN_EFFECTGROUPID_WEAPON_P_A_RATIO,// ������������������ֵ����ֱȣ��������Сͬʱ����
	EN_EFFECTGROUPID_BASE_P_A,// ���������������ֵ�������Сͬʱ����
	EN_EFFECTGROUPID_BASE_P_A_RATIO,// �����������������ֵ����ֱȣ��������Сͬʱ����
	EN_EFFECTGROUPID_SUM_P_A_RATIO,// ���ӵ�ǰ������������ֵ����ֱȣ��������Сͬʱ����

	// ��С��������
	EN_EFFECTGROUPID_WEAPON_MIN_M_A_RATIO,// ���������ķ���������С��ֵ����ֱȣ�
	EN_EFFECTGROUPID_BASE_MIN_M_A,// ��������ķ���������Сֵ
	EN_EFFECTGROUPID_BASE_MIN_M_A_RATIO,// ��������ķ���������С��ֵ����ֱȣ�
	EN_EFFECTGROUPID_SUM_MIN_M_A_RATIO,// ���ӵ�ǰ�ķ���������С��ֵ����ֱȣ�

	// ���������
	EN_EFFECTGROUPID_WEAPON_MAX_M_A_RATIO,// ���������ķ�����������ֵ����ֱȣ�
	EN_EFFECTGROUPID_BASE_MAX_M_A,// ��������ķ����������ֵ
	EN_EFFECTGROUPID_BASE_MAX_M_A_RATIO,// ��������ķ�����������ֵ����ֱȣ�
	EN_EFFECTGROUPID_SUM_MAX_M_A_RATIO,// ���ӵ�ǰ�ķ�����������ֵ����ֱȣ�

	// ��������(����)
	EN_EFFECTGROUPID_WEAPON_M_A_RATIO,// ���������ķ���������ֵ����ֱȣ��������Сͬʱ����
	EN_EFFECTGROUPID_BASE_M_A,// ��������ķ�������ֵ�������Сͬʱ����
	EN_EFFECTGROUPID_BASE_M_A_RATIO,// ��������ķ���������ֵ����ֱȣ��������Сͬʱ����
	EN_EFFECTGROUPID_SUM_M_A_RATIO,// ���ӵ�ǰ�ķ���������ֵ����ֱȣ������Сͬʱ���ӣ�

	// �������ֵ 
	EN_EFFECTGROUPID_BASE_P_D,// ����������������ֵ
	EN_EFFECTGROUPID_BASE_P_D_RATIO,// ������������������ֵ����ֱȣ�
	EN_EFFECTGROUPID_SUM_P_D_RATIO,// ���ӵ�ǰ�����������ֵ����ֱȣ�

	// ��������ֵ
	EN_EFFECTGROUPID_BASE_M_D,// ��������ķ�������ֵ
	EN_EFFECTGROUPID_BASE_M_D_RATIO,// ��������ķ���������ֵ����ֱȣ�
	EN_EFFECTGROUPID_SUM_M_D_RATIO,// ���ӵ�ǰ�ķ���������ֵ����ֱȣ�

	// ����
	EN_EFFECTGROUPID_PRESENT,// ��������ֵ
	EN_EFFECTGROUPID_PRESENT_RATIO,// ����������

	// ����
	EN_EFFECTGROUPID_HEDGE,// ��������ֵ
	EN_EFFECTGROUPID_HEDGE_RATIO,// ����������

	// ����
	EN_EFFECTGROUPID_FATAL,// ���ӻ���ֵ
	EN_EFFECTGROUPID_FATAL_RATIO,// ���ӻ�����

	// ����
	EN_EFFECTGROUPID_KICK_FATAL,// ��������ֵ

	// �ƶ��ٶ�
	EN_EFFECTGROUPID_MOVE_SPEED,// �ƶ��ٶ�
	EN_EFFECTGROUPID_MOVE_SPEED_RATIO,// �ƶ��ٶȱ�ֵ����ֱȣ�

	// �����ٶ� 
	EN_EFFECTGROUPID_ATTACK_SPEED,// �����ٶ�ֵ
	EN_EFFECTGROUPID_ATTACK_SPEED_RATIO,// �����ٶȱ�ֵ����ֱȣ�

	// �����ظ� 
	EN_EFFECTGROUPID_HP_RECOVER,// ���������ظ��ٶ�ֵ
	EN_EFFECTGROUPID_HP_RECOVER_RATIO,// ���������ظ��ٶȱ�ֵ����ֱȣ�

	// �����ظ�
	EN_EFFECTGROUPID_MP_RECOVER,// ���������ظ��ٶ�ֵ
	EN_EFFECTGROUPID_MP_RECOVER_RATIO,// ���������ظ��ٶȱ�ֵ����ֱȣ�

	// ���̹���
	EN_EFFECTGROUPID_PENETRATE,// ���̣�����)�˺�ֵ

	// �ֿ�����
	EN_EFFECTGROUPID_KICK_PENETRATE,// �ֿ����̣��ֿ�����)�˺�ֵ
	EN_EFFECTGROUPID_KICK_PENETRATE_RATIO,// �ֿ����̣��ֿ�����)�˺���ֵ����ֱȣ�

	// �����˺�
	EN_EFFECTGROUPID_FATAL_DAMAGE_RATIO,// ���ӻ����˺���ֵ����ֱ�)

	// �����˺�����
	EN_EFFECTGROUPID_KICK_FATAL_DAMAGE_RATIO,// �ֿ������˺���ֵ����ֱ�)

	// �����������
	EN_EFFECTGROUPID_IGNORE_P_D,// �����������ֵ
	EN_EFFECTGROUPID_IGNORE_P_D_RATIO,// �������������ֵ����ֱȣ�

	// ���Է�������
	EN_EFFECTGROUPID_IGNORE_M_D,// ���Է�������ֵ
	EN_EFFECTGROUPID_IGNORE_M_D_RATIO,// ���Է���������ֵ����ֱȣ�

	// �����˺�����
	EN_EFFECTGROUPID_REDUCE_P_DAMAGE,// �����˺�����ֵ
	EN_EFFECTGROUPID_REDUCE_P_DAMAGE_RATIO,// �����˺������ֵ����ֱȣ�

	// �����˺�����
	EN_EFFECTGROUPID_REDUCE_M_DAMAGE,// �����˺�����ֵ
	EN_EFFECTGROUPID_REDUCE_M_DAMAGE_RATIO,// �����˺������ֵ����ֱȣ�

	// old
	EEffectGroupID_Unable_Move,						// �޷��ƶ�
	EEffectGroupID_Unable_Attack,					// �޷�����
	EEffectGroupID_Unable_UseGoods,					// �޷�ʹ����Ʒ
	EEffectGroupID_Unable_UseSkill,					// ��ħ

	EEffectGroupID_Immunity_Damage,					// �����κ��˺�
	EEffectGroupID_Immunity_BreakPreSkill,			// ��ֹʩ�����	

	EEffectGroupID_FuriousMove,						// ����
	EEffectGroupID_BreakSkill,						// ��ϵ�ǰʩ��

	EEffectGroupID_Immunity_Buff,					// ����ĳ�����͵�BUFF
	EEffectGroupID_Clean_HurtBuff,					// ����к�BUFF	
	EEffectGroupID_ImposeOn_Buff,					// ����ĳ�����͵�BUFF	

	/*---------------------------�����˺���ֵ--------------------------------*/
	EN_EFFECTGROUPID_INCREASE_P_DAMAGE_RATIO,       //�����˺����ӱ�ֵ����ֱȣ�
	EN_EFFECTGROUPID_INCREASE_M_DAMAGE_RATIO,       // �����˺����ӱ�ֵ����ֱȣ�

	/*---------------------------�������еļ���MP���ı�ֵ--------------------------------*/
	EN_EFFECTGROUPID_INCREASE_SKILL_CONSUMEMP_RATIO,       // �������еļ���MP���ı�ֵ

	/*---------------------------����������Ͼۼ������������Ŀ--------------------------------*/
	EEffectGroupID_Magic_Balloon_Num,               // ������Ͼۼ������������Ŀ

	/*---------------------------����--------------------------------*/
	EEffectGroupID_PM_Shield_Absorb_Remain,         // ���������˺�ֵ���ӣ��ɻ��������൱��������ֵ����X%���˺�����õ�

	/*---------------------------�����Զ�����X--------------------------------*/
	EEffectGroupID_Durative_AddHP,					// �����Զ�����n������
	EEffectGroupID_Durative_AddMP,					// �����Զ�����n�㷨��
	EEffectGroupID_Durative_AddHP_Per,				// �����Զ����ӣ�����
	EEffectGroupID_Durative_AddMP_Per,				// �����Զ����ӣ�����
	EEffectGroupID_Durative_AddExp,					// �����Զ�����n�㾭��
	EEffectGroupID_Durative_AddMPAndHP_Per,         // �����Զ����ӣ�������ͬʱ����HP����ڱ�������MPֵ��

	/*---------------------------��ͨ�����������⹥����--------------------------------*/
	EEffectGroupID_Plus_Normal_Attack_Per,          // ��ͨ�����������⹥�����ٷֱ�
	EEffectGroupID_Normal_Attack_ConsumeMP_Per,     // ÿ����ͨ�����������ķ���ֵ�İٷֱ�

	/*---------------------------����--------------------------------*/
	EN_EFFECTGROUPID_DEST_DAMAGE2SRC_PER,           // ��X%�ļ��ʽ��˺���100%����������ߣ�����Լ������ܵ������˺���
	EN_EFFECTGROUPID_REBOUND_DAMAGE_RATIO,          // ���ܺ�BUFF��������פ�������ܣ������ķ����˺��ٷֱ�

	EEffectGroupID_RandomAttack,					// add by zjp.��������˺�

	/*---------------------------�����Զ��˺���--------------------------------*/
	EN_EFFECTGROUPID_PATTACK_PDAMAGE,               // ȡ���������������Զ������˺�
	EN_EFFECTGROUPID_MATTACK_MDAMAGE,               // ȡ�����������������Զ������˺�
	EN_EFFECTGROUPID_PATTACK_MDAMAGE,               // ȡ���������������Զ������˺�
	EN_EFFECTGROUPID_MATTACK_PDAMAGE,               // ȡ�����������������Զ������˺�
	EN_EFFECTGROUPID_HPATTACK_PDAMAGE,              // ȡ�൱��ʩ���ߵ�ǰ����ֵ���ޣ������Զ������˺�

	/*--------------------�ù������򱻻���ĳ������ȥ�ı䱻������ĳ������-----------------------*/
	EN_EFFECTGROUPID_ADD_MaxPA_SD,                  // Ŀ��ʵ���������������һ����ֵ������ֵ���ڹ�����������������������X%
	EN_EFFECTGROUPID_ADD_MinPA_SD,                  // Ŀ��ʵ����С����������һ����ֵ������ֵ���ڹ�����������������������X%
	EN_EFFECTGROUPID_ADD_MaxMA_SD,                  // Ŀ��ʵ���������������һ����ֵ������ֵ���ڹ�����������������������X%
	EN_EFFECTGROUPID_ADD_MinMA_SD,                  // Ŀ��ʵ����С������������һ����ֵ������ֵ���ڹ�����������������������X%
	EN_EFFECTGROUPID_ADD_PD_MD_SD,                  // Ŀ��ʵ�������������һ����ֵ������ֵ���ڹ����������������������X%��
	EN_EFFECTGROUPID_ADD_MD_MD_SD,                  // Ŀ��ʵ�ʷ�����������һ����ֵ������ֵ���ڹ����������������������X%��

	/*-------------------------����ĳ��ID��BUFF-------------------------------------------*/
	EEffectGroupID_Immunity_BuffID,					// ����ĳ��ID��BUFF
	EEffectGroupID_Immunity_BeCrazyDamage,          // ���߱�����

	// ��ʱ��AOE
	EEffectGoupID_AoeDamage,						// ��ʱ��AOE

	EEffectGoupID_KICKFATALRATIO,					// �ı�������

	EEffectGoupID_ChangeMoveSpeedByTime,			// �ݼ��ĸı��ƶ��ٶ�

	EEffectGroupID_Bubble,							// XP����

	EEffectGroupID_MaxID,							// ���
};

/////////////////////////// ��ȴ�鶨��  ////////////////////////////
enum
{
	EFreeze_ClassID_Skill = 1,						// ������ȴ��
	EFreeze_ClassID_Goods,							// ��Ʒ��ȴ��
	EFreeze_ClassID_Chat,							// ������ȴ��
	EFreeze_ClassID_Task,							// ������ȴ��

	EFreeze_ClassID_Max,							// ���
};

/////////////////////////// ��Ʒ������  ////////////////////////////
enum
{
	ESkepType_Unknow = 0,							// δ֪��Ʒ��
	ESkepType_Real,									// ʵ����Ʒ��
	ESkeyType_Link,									// ������Ʒ��
	ESkeyType_Pet,									// ������
};

/////////////////////////// ��Ʒ��Ȩ��  ////////////////////////////
enum
{
	/*
					  00000000 00000001				// ����Ȩ��
					  00000000 00000010				// ���Ȩ��
					  00000000 00000100				// �Ƴ�Ȩ��
					  00000000 00001000				// ʹ��Ȩ��
					  00000000 00010000				// ���Ȩ��
					  00000000 00100000				// �ϲ�Ȩ��
					  00000000 01000000				// �۲�Ȩ��
	11111111 11111111 11111111 11111111				// .....	
	//*/
	ESkepPopedom_Link = 0x0001,						// ����Ȩ��
	ESkepPopedom_Add = 0x0002,						// ���Ȩ��
	ESkepPopedom_Remove = 0x0004,					// �Ƴ�Ȩ��
	ESkepPopedom_Use = 0x0008,						// ʹ��Ȩ��
	ESkepPopedom_Split = 0x0010,					// ���Ȩ��
	ESkepPopedom_Unite = 0x0020,					// �ϲ�Ȩ��
	ESkepPopedom_Observe = 0x0040,					// �۲�Ȩ��
};

/////////////////////////// ��Ʒ������  ////////////////////////////
enum
{
	ESkepName_UnKnow = 0,							// δ֪��
	ESkepName_Packet,								// ������	
	ESkepName_WareHouse,							// �ֿ���
	ESkepName_Equip,								// װ����
	ESkepName_Trade,								// ������	
	ESkepName_Stall,								// ̯λ��
	ESkepName_Shop,									// �̵���
	ESkepName_Auction,								// ������
	ESkepName_Hock,									// ������
	ESkepName_Box,									// ������
	ESkepName_Pets,									// ������
	ESkepName_PetLib,                               // ����ֿ���
	ESkepName_EquipSmeltSoul,						// װ�����������ᴿ��Ʒ��
	ESkepName_EquipEmbedGems,						// װ����ʯ��Ƕ��
	ESkepName_EquipRebuild,							// װ��������
	ESkepName_Compose,								//�ڵ��ϳ�	by ldy
	ESkepName_Intensify,							//�꽫ʥ�� by ldy
	ESKepName_Max,									// �����Ͻ�
};

//////////////////////// �����������  ///////////////////////////
enum
{
	EMonster_HoldStrategy_Simple = 1,				// �򵥲���
	EMonster_HoldStrategy_LastAttack,				// ���һ�ι���Ȩ
	EMonster_HoldStrategy_DurativeAttack,			// ��������Ȩ
	EMonster_HoldStrategy_Born,						// ��������
	EMonster_HoldStrategy_System,					// ϵͳ����
};

////////////////////////// �У�ģʽ ///////////////////////////////
enum
{
	EPKMode_Name_Safe = 0,								// ��ȫģʽ
	//EPKMode_Name_Blind,								// ȫ��ģʽ
	//EPKMode_Name_Team,								// ����ģʽ
	//EPKMode_Name_Clan,								// ����ģʽ
	//EPKMode_Name_Nation,								// ����ģʽ
	//EPKMode_Name_Justice,								// �ƶ�ģʽ
	//EPKMode_Name_Camp,								// ��Ӫģʽ
	EPKMode_Name_Good,									//����ģʽ
	EPKMode_Name_Bad,									//����ģʽ 

	EPKMode_Name_Max,									// .......
};

////////////////////////// �У����� ///////////////////////////////
enum
{
	EPK_AreaName_General = 0,						// ��ͨ��
	EPK_AreaName_Arena,								// �д���
	EPK_AreaName_Safe,								// ��ȫ��	
	EPK_AreaName_Risky,								// Σ����

	EPK_AreaName_Stall = 20,						// ��̯��
};

enum
{
	EPK_Setting_NotDecide = 0,							//��֮��Ĺ���(��pkģʽ)����
	EPK_Setting_CanAttack,								//����pk
	EPK_Setting_BanAttack,								//��ֹpk
};

////////////////////////// ���������ɫ ///////////////////////////
enum
{
	EPK_NameColor_Blue = 0,							// ����
	EPK_NameColor_White,							// ����	
	EPK_NameColor_Yellow,							// ����
	EPK_NameColor_Red,								// ����

	EPK_NameColor_Max,								// ...
};

////////////////////////// �����ͷ�ԭ�� //////////////////////////
enum
{
	EDiePunish_Type_Absolve = 0,					// ��������װ
	EDiePunish_Type_AreaGeneral,					// ��ͨ������
	EDiePunish_Type_AreaRisky,						// Σ��������

	EDiePunish_Type_Max,							// ....
};

// add by zjp��
////////////////////////// ������ʽ //////////////////////////
enum
{
	EDead_Mode_NORMAL = 0,							// ������������npc��ɱ
	EDead_Mode_PK,									// PK����

	EDEAD_MODE_MAX,									// ....
};


////////////////////////// ��ӷ���ģʽ //////////////////////////
enum
{
	ETeamPrize_AllotMode_Turn = 0,					// ����ʰȡ
	ETeamPrize_AllotMode_Free,						// ����ʰȡ
	ETeamPrize_AllotMode_Captain,					// �ӳ�ʰȡ
	ETeamPrize_AllotMode_Rand,                      // ���ʰȡ

	ETeamPrize_Allot_Max,							// .....
};

/////////////////////////// ����������� ////////////////////////
enum
{
	tVisible_Reserve = 0x0001,	//��������Чֵ
	tVisible_Weapon = 0x0002,	//����������ʾ
	tVisible_Armet = 0x0004,
	tVisible_Armor = 0x0008,	
	tVisible_Cuff = 0x0010,
	tVisible_Shoes = 0x0020,		
	tVisible_Necklace = 0x0040,	
	tVisible_Ring = 0x0080,
	tVisible_DecorationL = 0x0100,
	tVisible_DecorationR = 0x0200,
	tVisible_SuitArmet = 0x0400,
	tVisible_SuitArmor = 0x0800,
};
struct SPersonFormData
{
	DWORD	GoodsID[PERSON_EQUIPPLACE_MAX];			// ��ƷID	
	BYTE	ExtendedReason[PERSON_EQUIPPLACE_MAX];	// ��չ����ԭ��	
	WORD	VisibleFlag;//����װ������ʾ,���flagֻ�Ƕ�ͷ��������ʱװͷ��)���¼ף�����ʱװ�¼�)��Ч

	SPersonFormData(void)
	{
		memset(this, 0, sizeof(SPersonFormData));
	}
};

/////////////////////////// ϵͳ������ ////////////////////////////
enum
{
	ESystem_Error_LoginError = 0,					// ��¼����
	ESystem_Error_DuplicateLogin,				// �ظ���½ 
	ESystem_Error_ZoneSelectError,					// ѡ���������
	ESystem_Error_ZoneInvalidData,					// �Ƿ�����
	ESystem_Error_ZoneChangeZone,					// �л�����
	ESystem_Error_CloseZoneServer,                  // �������ر�
};

//////////////////////////װ��������������///////////////////////////
enum
{
	EEquipSmeltName_SoulStoneUpgrade = 0,//��ʯ�ϳ�
	EEquipSmeltName_SmeltSoul, //װ������
	EEquipSmeltName_Max,
};

//////////////////////////װ��������λ������///////////////////////////
enum
{
	EEquipSmeltSoulSkepPlace_SoulStoneUpgradePlaceStart = 0, //��ʯ�ϳɵ���ʼλ��
	EEquipSmeltSoulSkepPlace_SoulStoneUpgradePlaceEnd = 8,   //��ʯ�ϳɵĽ���λ��
	EEquipSmeltSoulSkepPlace_UpgradeMainMtlStart = 0,		//��ʯ������ʼλ��
	EEquipSmeltSoulSkepPlace_UpgradeMainMtlEnd = 5,          //��ʯ��������λ��
	EEquipSmeltSoulSkepPlace_UpgradeMainMtl0 = 0,				 
	EEquipSmeltSoulSkepPlace_UpgradeMainMtl1 = 1,				 
	EEquipSmeltSoulSkepPlace_UpgradeMainMtl2 = 2,
	EEquipSmeltSoulSkepPlace_UpgradeMainMtl3 = 3,
	EEquipSmeltSoulSkepPlace_UpgradeMainMtl4 = 4,
	EEquipSmeltSoulSkepPlace_UpgradeSupMtl0 = 5,
	EEquipSmeltSoulSkepPlace_UpgradeSupMtl1 = 6,
	EEquipSmeltSoulSkepPlace_UpgradeSupMtl2 = 7,

	EEquipSmeltSoulSkepPlace_EquipSmeltSoulPlaceStart = 1,   //װ���������ʼλ��
	EEquipSmeltSoulSkepPlace_EquipSmeltSoulPlaceEnd = 5,	// װ������Ľ���λ��
	EEquipSmeltSoulSkepPlace_SmeltEquipment = 8,
	EEquipSmeltSoulSkepPlace_SmeltMainMtl0 = 9,
	EEquipSmeltSoulSkepPlace_SmeltMainMtl1 = 10,
	EEquipSmeltSoulSkepPlace_SmeltMainMtl2 = 11,
	EEquipSmeltSoulSkepPlace_SmeltMainMtl3 = 12,
	EEquipSmeltSoulSkepPlace_SmeltSupMtl0 = 13,
	EEquipSmeltSoulSkepPlace_SmeltSupMtl1 = 14,
	EEquipSmeltSoulSkepPlace_SmeltSupMtl2 = 15,
};

////////////////////////װ����ʯ��Ƕ��������//////////////////////////////////
enum
{
	EEquipEmbedGemsName_GemDrillSlot = 0,    //װ�����
	EEquipEmbedGemsName_GemUpgrade,   //��ʯ�ϳ�
	EEquipEmbedGemsName_EmbedGems,   //װ����Ƕ��ʯ
	EEquipEmbedGemsName_DetachGems,  //װ��ȥ����Ƕ�ı�ʯ
	EEquipEmbedGemsName_Max,
};

//////////////////////////װ����ʯ��Ƕ��λ������///////////////////////////
enum
{
	EEquipEmbedGemsSkepPlace_EquipDrillSlotPlaceStart = 0, //װ�����������ʼλ��
	EEquipEmbedGemsSkepPlace_EquipDrillSlotPlaceEnd   = 2, //װ�������������λ��
	EEquipEmbedGemsSkepPlace_EquipDrillSlot = 0, //��׵�λ��
	EEquipEmbedGemsSkepPlace_DrillSlotMtl = 1, //��ײ���λ��

	EEquipEmbedGemsSkepPlace_GemsUpgradePlaceStart = 2, //��ʯ�ں�������ʼλ��
	EEquipEmbedGemsSkepPlace_GemsUpgradePlaceEnd   = 11, //��ʯ�ں���������λ��
	EEquipEmbedGemsSkepPlace_GemsFusionAgent = 2, //��ʯ�ںϼ�
	EEquipEmbedGemsSkepPlace_FusionGem0	=3,       //���ںϵ���ʯ
	EEquipEmbedGemsSkepPlace_FusionGem1	=4,
	EEquipEmbedGemsSkepPlace_FusionGem2	=5,
	EEquipEmbedGemsSkepPlace_FusionGem3	=6,
	EEquipEmbedGemsSkepPlace_FusionGem4	=7,
	EEquipEmbedGemsSkepPlace_FusionSupMtl0	=8,    //��ʯ�ںϸ�������
	EEquipEmbedGemsSkepPlace_FusionSupMtl1  =9,
	EEquipEmbedGemsSkepPlace_FusionSupMtl2  =10,

	EEquipEmbedGemsSkepPlace_EmbedGemsPlaceStart = 11 , //װ����Ƕ��ʯ������ʼλ��
	EEquipEmbedGemsSkepPlace_EmbedGemsPlaceEnd  =13,     //װ����Ƕ��ʯ��������λ��
	EEquipEmbedGemsSkepPlace_EquipEmbedGems = 11,  //��Ƕ��ʯ��װ��
	EEquipEmbedGemsSkepPlace_GemsEmbed      = 12,  //Ƕ�����ʯ

	EEquipEmbedGemsSkepPlace_DetachGemsPlaceStart = 13 , //װ��ȥ����ʯ������ʼλ��
	EEquipEmbedGemsSkepPlace_DetachGemsPlaceEnd  =15,     //װ��ȥ����ʯ��������λ��
	EEquipEmbedGemsSkepPlace_EquipDetachGems =13,  //�����װ��
	EEquipEmbedGemsSkepPlace_DetachGemsMtl   =14,  //����Ĳ���
};

///////////////////////װ��������������/////////////////////////////////////////
enum
{
	EEquipRebuildName_Rebuild = 0,   //װ������
	EEquipRebuildName_Max,
};

//////////////////////////װ����������λ������///////////////////////////
enum
{
	EEquipRebuildSkepPlace_RebuildPlaceStart = 0, //װ������������ʼλ��
	EEquipRebuildSkepPlace_RebuildPlaceEnd   = 3, //װ��������������λ�� modify by zjp ���ڵ����Ӵ�СΪ3

	EEquipRebuildSkepPlace_RebuildEquip		= 0, //������װ��

	EEquipRebuildSkepPlace_RebuildMainMtl0  = 1, //��Ҫ����������
	EEquipRebuildSkepPlace_RebuildMainMtl1  = 2,
	EEquipRebuildSkepPlace_RebuildMainMtl2  = 3,

	EEquipRebuildSkepPlace_RebuildSupMtl0 = 4,   //��������������
	EEquipRebuildSkepPlace_RebuildSupMtl1 = 5, 

	EEquipRebuildSkepPlace_AttribReserveMtl0 = 6,//����Ʒ�ʵĲ���
	EEquipRebuildSkepPlace_AttribReserveMtl1 = 7,
	EEquipRebuildSkepPlace_AttribReserveMtl2 = 8,
};

///////////////////////////////�ϳ���/////////////////////////////////
enum ComposeSkep
{
	ComposeName_Confirm = 0,					//�ϳ�ȷ��
	ComposeName_Max,
};

enum 
{
	ComposeSkepPlace_Start = 0,
	ComposeSkepPlace_End = 16,
};

///////////////////////////////�꽫ʥ����/////////////////////////////////
enum
{
	PetIntensifySkepPlace_PillStart = 0,			//�ڵ�������ʼ
	PetIntensifySkepPlace_PillEnd = 15,			//�ڵ���������
	PetIntensifySkepPlace_Pet = 16,				//�꽫����

};

enum 
{
	PetIntensifyConfirm = 0,				//�꽫ʥ��ȷ��
	PetIntensifyOp_Max,
};

///////////////////////////////�������/////////////////////////////////
enum ESKILLPOINT_CONSUME
{
	SKILLPOINT_CONSUME_BRANCH_FIRST = 1,	        // ��һ�����ܷ�֧�����ĵļ��ܵ�
	SKILLPOINT_CONSUME_BRANCH_SECOND,	            // �ڶ������ܷ�֧�����ĵļ��ܵ�
};

///////////////////////////////�ƶ����/////////////////////////////////
// ��ʾ�ƶ�һ��tile�����ѵ�ʱ�䣨���룩��ֵԽС��ʾ�ƶ��ٶ�Խ�죬�޸���ǰ���ٶȵȼ�������Ϊ�߻�Ҫ���ٶ��������ڼ���ʹ��ʱ��������ٶȰٷֱ�
enum EMOVETILECOSTTIME
{
	EMOVETILECOSTTIME_MIN            = 1,           // �����ƶ���ʾ�ƶ�һ��tile�����ѵ�ʱ����Сֵ
	EMOVETILECOSTTIME_PERSON_INIT    = 200,	        // �����ʼ�����ٶ�
	EMOVETILECOSTTIME_MONSTER_INIT   = 260,	        // �����ʼ�����ٶ�
	EMOVETILECOSTTIME_PET_INIT       = 260,	        // �����ʼ�����ٶ�
	EMOVETILECOSTTIME_PERSON_WALK    = 530,	        // ������·ʱ���ٶ�
	EMOVETILECOSTTIME_MONSTER_WALK   = 530,	        // ������·ʱ���ٶ�
	EMOVETILECOSTTIME_PET_WALK       = 530,	        // ������·ʱ���ٶ�
	EMOVETILECOSTTIME_CREATURE_MAX   = 50000,       // �����ƶ�ʱ�����ٶ�
};

// ��ʾ�ƶ�һ��tile�����ѵ�ʱ�䣨���룩��ֵԽС��ʾ�ƶ��ٶ�Խ��
enum EMOVETIMEPERTILE
{
	EMOVETIMEPERTILE_MIN       = 1,                 // �ƶ�һ��tile�����ѵ�ʱ����Сֵ
	EMOVETIMEPERTILE_NORMAL    = 200,	            // ����Ĭ�ϵĿ��ʱ��(�ô�ʱ������׼���ƶ��ٶ�ת��)
	EMOVETIMEPERTILE_MAX       = 99999,             // �����ƶ�ʱ�������ʱ�䣨��Ӧ�����ٶȣ�
};

// �ƶ��ٶ�
enum EMOVESPEED
{
	EMOVESPEED_MIN              = 1,                // �������ƶ��ٶȣ�����������
	EMOVESPEED_NORAML           = 300,              // ����Ĭ�ϵ��ƶ��ٶ�(�ô��ٶ�����׼����ʱ��ת��)
	EMOVESPEED_MAX              = 99999,            // �����ƶ��ٶ�
};

// �ƶ�ģʽ
enum EMoveStyle
{
	EMoveStyle_Walk,                                // ��                                                   
	EMoveStyle_Run,                                 // ��
	EMoveStyle_Sitdown,                             // ���¶���
	EMoveStyle_Sit,                                 // ��

	EMoveStyle_Max,                                 // ���
};

// ���ι������ʱ����(����)
enum EATTACKINTERVAL
{
	EATTACKINTERVAL_MIN          = 1,                // ���ι���������ʱ����
	EATTACKINTERVAL_NORMAL       = 1000,             // ��׼�����ٶȣ�1.0�빥��һ��
	EATTACKINTERVAL_MAX          = 99999,            // ���ι�������ʱ����
};
// �����ٶ�ֵ
enum EATTACKSPEED
{
	EATTACKSPEED_MIN              = 1,                 // �����ٶ���Сֵ
	EATTACKSPEED_NORMAL           = 210,	           // ��׼�Ĺ����ٶ�ֵ
	EATTACKSPEED_MAX              = 99999,             // �����ٶ����ֵ
};

// ��ͨ������ID
enum EAttackFreezeID
{
	EAttackFreezeID_Normal       = 1999,               // ������ͨ������ȴID
};

// ������Ч
enum  
{
	Sound_BackGround_1 = 1,
	Sound_BackGround_2,
	Sound_BackGround_3,
	Sound_BackGround_4,
	Sound_BackGround_5,
	Sound_BackGround_6,
	Sound_BackGround_7,
	Sound_SystemSound_Icon1 = 3001,
	Sound_SystemSound_Icon2,
	Sound_SystemSound_Icon3,
	Sound_SystemSound_Icon4,
	Sound_SystemSound_Icon5,
	Sound_SystemSound_EnterGame,
	Sound_SystemSound_LeaveGame,
	Sound_SystemSound_OpenSkep,
	Sound_SystemSound_CloseSkep,
	Sound_SystemSound_BuyGoods,
	Sound_SystemSound_SellGoods,
	Sound_SystemSound_Invite,
	Sound_SystemSound_Succe,
	Sound_SystemSound_Delect,
	Sound_SystemSound_Failed,
	Sound_SystemSound_QequestTask,
	Sound_SystemSound_FinishTask,
	Sound_SystemSound_FailedTask,
	Sound_SystemSound_Upgrade,
	Sound_SystemSound_SkillUpgrade,
	Sound_SystemSound_FalseOperate,
	Sound_SystemSound_SkillBreak,
	Sound_SystemSound_SystemTip,
	Sound_SystemSound_PrivateMsg,
	Sound_SystemSound_TradeLock,
	Sound_SystemSound_DrapIcon,
};
// ��ЧID��ָ�����ŵ���ЧIDö�٣�
enum
{
	Effect_FinishTask_EffectID = 1005,
	Effect_ArrivedPlace_EffectID = 1006,
	Effect_AutoMove_EffectID = 1007,
};
#pragma pack()