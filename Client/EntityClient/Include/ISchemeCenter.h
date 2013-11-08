/*******************************************************************
** �ļ���:	e:\Rocket\Server\ZoneServer\Include\ISchemeCenter.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2008/1/16  11:34
** ��  ��:	1.0
** ��  ��:	��������,�������˲�����нű���������������ȡ����
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once
#include <map>

#pragma pack(1)

//by cjl
//ChangeBody.csv
#define CHANGE_BODY_SKILL_NUM 5
struct SChangeBodySchemeInfo
{
	char szName[MAX_PERSONNAME_LEN];//����
	int  time;//�������ʱ��
	int  resID;//������ԴID
	int  icon;//ͷ�꣬�ͻ������ã������û�õ�
	int  bufferID;//buff���ID,�ͻ������ã������û�õ�
	int  skill[CHANGE_BODY_SKILL_NUM];//����
	int  newPropID;//�����Ե�����
	int  flag;//��ʶ��
	int getSkillNum()
	{
		int num = 0;
		for (int i=0;i<CHANGE_BODY_SKILL_NUM;i++)
		{
			if (skill[i]>0)
			{
				num++;
			}
		}
		return num;
	}

	bool haveState(int state)
	{
		return (flag & state) == state;
	}

	SChangeBodySchemeInfo()
	{
		memset(this, 0, sizeof(SChangeBodySchemeInfo));
	}
};

//Present.csv 
#define PRESENT_GOODS_MAX_NUMBER 10
struct  SPresentSchemeInfoBase
{
	SPresentSchemeInfoBase():num(0){};
	long goods[PRESENT_GOODS_MAX_NUMBER];
	long goodnum[PRESENT_GOODS_MAX_NUMBER];
	char num;//��ʵ�ĸ���
	DWORD flag[PRESENT_GOODS_MAX_NUMBER];//��־λ
};

struct SPresentSchemeInfo : public SPresentSchemeInfoBase
{
	SPresentSchemeInfo():SPresentSchemeInfoBase(),second(0){};
	int second;
};
//end cjl

// monster.csv
enum EMonster
{
	EMonster_ID,                             // ����ID
	EMonster_Name,							 // �༭����
	EMonster_Profession,					 // ְҵ��
	EMonster_Function,						 // ��������
	EMonster_GameName,						 // ��Ϸ������
	EMonster_ResID,							 // ��ԴID
	EMonster_FaceID,                         // ͷ��ID
	EMonster_Type,							 // ����
	EMonster_Camp,							 // ��Ӫ 	
	EMonster_Level,							 // �ȼ�
	EMonster_Fight,							 // ս����
	EMonster_HP,							 // ����ֵ
	EMonster_HPRecoverRatio,				 // �����ظ��ٷֱ�
	EMonster_HPRecoverInterval,				 // �����ظ����(����)
	EMonster_MP,							 // ħ��ֵ
	EMonster_MoveSpeed,						 // �ƶ��ٶ�
	EMonster_WalkSpeed,						 // ��·�ٶ�
	EMonster_EyeShot,						 // ��Ұ	
	EMonster_ChaseEyeShot,					 // ׷����Ұ
	EMonster_RetrieveDist,					 // �ع�/׷������
	EMonster_RadiateDist,					 // �ٻ���Ұ
	EMonster_IsRadiated,					 // �Ƿ��ٻ�
	EMonster_PrizeStrategy,					 // ����ӵ�в���	
							 
	EMonster_MinPAttack,					 // ��С������
	EMonster_MaxPAttack,					 // ���������
	EMonster_MinMAttack,					 // ��С��������
	EMonster_MaxMAttack,					 // ���������
							 
	EMonster_PDefend,						 // �������	
	EMonster_MDefend,						 // ��������
	EMonster_PresentPer,					 // ���и���
	EMonster_HedgePer,						 // ���ܸ���
	EMonster_FatalPer,						 // ���ĸ���
							 
	EMonster_Present,						 // ����ֵ
	EMonster_Hedge,							 // ����ֵ
	EMonster_PFatal,						 // ����ֵ
	EMonster_KickFatal,						 // ����ֵ
	EMonster_AttackSpeed,					 // �����ٶ�ֵ
							 
	EMonster_UsableSkill1_ID,				 // ��ʹ�õļ���1 [����id]
	EMonster_UsableSkill1_Per,				 // ��ʹ�õļ���1 [ʹ�ø���]
	EMonster_UsableSkill1_Time,				 // ��ʹ�õļ���1 [ʹ��ʱ��]

	EMonster_UsableSkill2_ID,				 // ��ʹ�õļ���2 [����id]
	EMonster_UsableSkill2_Per,				 // ��ʹ�õļ���2 [ʹ�ø���]
	EMonster_UsableSkill2_Time,				 // ��ʹ�õļ���2 [ʹ��ʱ��]

	EMonster_UsableSkill3_ID,				 // ��ʹ�õļ���3 [����id]
	EMonster_UsableSkill3_Per,				 // ��ʹ�õļ���3 [ʹ�ø���]
	EMonster_UsableSkill3_Time,				 // ��ʹ�õļ���3 [ʹ��ʱ��]

	EMonster_UsableSkill4_ID,				 // ��ʹ�õļ���4 [����id]
	EMonster_UsableSkill4_Per,				 // ��ʹ�õļ���4 [ʹ�ø���]
	EMonster_UsableSkill4_Time,				 // ��ʹ�õļ���4 [ʹ��ʱ��]
							 
	EMonster_AIID,							 // �����õ�AI
	EMonster_FullControl,					 // �Ƿ���Ҫȱʡ��AI���ع飬�˳�ս����,����npc��ȫ���ڳ���Ŀ���֮��
	EMonster_IdleRandom,					 // �й�ĸ���
};
struct SMonsterSchemeInfo
{
	long			lMonsterID;						// ����ID
	char			szName[16];						// �༭����
	char			szProfession[32];				// ְҵ��
	char			szFunction[16];					// ������
	char			szGameName[16];					// ��Ϸ������
	long			lResID;							// ��ԴID
	long            lFaceID;                        // ͷ��ID
	long			lType;							// ����
	long			lCamp;							// ��Ӫ 	
	long			lLevel;							// �ȼ�
	long			lFight;							// ս����
	long			lHP;							// ����ֵ
	long            lHPRecoverRatio;                // �����ظ��ٷֱ�
	long            lHPRecoverInterval;             // �����ظ����(����)
	long			lMP;							// ħ��ֵ
	long			lMoveSpeed;						// �ƶ��ٶ�
	long            lWalkSpeed;                     // ��·�ٶ�
	long			lEyeShot;						// ��Ұ	
	long			lChaseEyeShot;					// ׷����Ұ
	long			lRetrieveDist;					// �ع�/׷������
	long            lRadiateDist;                   // �ٻ���Ұ
	long            lIsRadiated;                    // �Ƿ��ٻ�
	long			lPrizeStrategy;					// ����ӵ�в���	

	long			lMinPAttack;					// ��С������
	long			lMaxPAttack;					// ���������
	long			lMinMAttack;					// ��С��������
	long			lMaxMAttack;					// ���������

	long			lPDefend;						// �������	
	long			lMDefend;						// ��������
	long			lPresentPer;					// ���и���
	long			lHedgePer;						// ���ܸ���
	long			lFatalPer;						// ���ĸ���

	long			lPresent;					    // ����ֵ
	long			lHedge;						    // ����ֵ
	long			lPFatal;                        // ����ֵ
	long            lKickFatal;                     // ����ֵ
	long            lAttackSpeed;                   // �����ٶ�ֵ

	long			lUsableSkill1[3];				// ��ʹ�õļ���1 [����id, ʹ�ø���, ʹ��ʱ��]
	long			lUsableSkill2[3];				// ��ʹ�õļ���2 [����id, ʹ�ø���, ʹ��ʱ��]
	long			lUsableSkill3[3];				// ��ʹ�õļ���3 [����id, ʹ�ø���, ʹ��ʱ��]
	long			lUsableSkill4[3];				// ��ʹ�õļ���4 [����id, ʹ�ø���, ʹ��ʱ��]

	long			lAIID;							// �����õ�AI
	long			lFullControl;					// �Ƿ���Ҫȱʡ��AI���ع飬�˳�ս����,����npc��ȫ���ڳ���Ŀ���֮��
	long			lIdleRandom;					// �й�ĸ���
};

// PersonBaseProp.csv
struct SPersonBasePropSchemeInfo
{
	long			lBaseMinPA;						//��С������ֵ
	long			lBaseMaxPA;						//���������ֵ
	long			lBasePD;						//�������ֵ
	long			lBaseMinMA;						//��С��������ֵ
	long			lBaseMaxMA;						//���������ֵ
	long			lBaseMD;						//��������ֵ
	long			lBaseHP;						//����ֵ
	long			lBaseHPRecover;					//�����ָ�ֵ
	long			lBaseMP;						//����ֵ
	long			lBaseMPRecover;					//�����ָ�ֵ
	long            lBaseSP;						//����ֵ
	long            lBaseSPRecover;					//�����ָ�ֵ
	long			lBaseHedge;						//����ֵ
	long			lBaseHedgeRatio;				//������
	long			lBasePresent;					//����ֵ
	long			lBasePresentRatio;				//������
	long			lBaseFatalDamage;				//����ֵ
	long			lBaseFatalDamageRatio;			//������
	long			lBaseKickFatalDamage;			//����ֵ
	long			lBaseAttackSpeed;				//�����ٶ�
	long			lBaseMoveSpeed;					//�ƶ��ٶ�
};

// PetData.csv
struct SPetSchemeInfo
{
	long            lPetID;                         // ����ID
	long            lResID;                         // ��ԴID
	char            szName[16];                     // ����
	long			lGrade;							// ����
	long            lImageID[3];                    // ��ͼID
	long            lEggImageID[3];                 // δ���ͼ��ID
	long            lBigImageID[3];					// ����ͼID
	long			lLevel;							// �����ȼ�
	bool            bState;                         // Ĭ�Ͻ��״̬
	long            lTransUpper;                    // ת�����޴��� 
	long            lLevelDiff;						// �����ȼ���ֵ
	long			lFightChummy;					// ������Ҫ����С���ܶ�
	long            lLevelUpper;                    // �ȼ�����ֵ
	long            lReleaseTime;                   // ���ʱ��
	bool            bRide;                          // �Ƿ����
	long            lRealization[2];                // ����ȼ�����
	long            lMoveSpeed;                     // �ƶ��ٶ�
	long			lRideSpeed;						// ����ٶ�
	long            lWatchSize;                     // ��Ұ��Χ

	long            lGeniusNumUpper;                // �츳������
	long            lSkillNum;                      // ������
	long            lFeedType;                      // ιʳ����
	long            lFeedTime;                      // ιʳʱ����
	long            lType;                          // �����ͱ�ʶ
	bool            bCombine;                       // �ܷ����
	long			lEvolutionPetID;				// ������ĳ���
	char			szDesc[512];					// ����

	long			lBoxResID;						// ���������ԴID	
	long			lBoxRayResID;					// ������˸��ԴID
	long			lFightEffectID;					// ������Ч
	long			lFightEffectDelay;				// ������Ч��ʱ
	long			lRollbackEffectID;				// �ٻ���Ч
	long			lCombineEffectID;				// ������Ч

	long			lUsableSkill[3];				// ��ʹ�õļ���[����id, ʹ�ø���, ʹ��ʱ��]
	long			lAIID;							// AI
	long			lIdleRandom;					// �й����	
	long			lPropID;						// ����ս�����Ա���е�ID
	long			lCompdType;						// �ϳ�����
	long			lBindFlag;						// �󶨱�־λ	
	long			lUseTerm;						// ʹ������
	long			lPower;							// ��������
	int             iGeniusRandom[C_PET_GENIUS_SIZE];// ���츳���ֵĸ���
};

// PetPropData.csv
// ����ս�������������
///  �ɳ��ʱ�����λС������Ϊ�ǰ��������棬���Լ���ʱҪ����10000
struct SPetPropSchemeInfo
{
	long            lPetPropID;                     // ��������ID
	char            szTypeDes[16];                  // ����
	long            lMainProp[PET_TYPEPROP_MAX];	// ������
	long			lMinorProp[PET_TYPEPROP_MAX];	// ������

	long            lChummyUpper;                   // ��������ֵ
	long            lChummyDrop;                    // ���ܶ���������ֵ
	long            lChummyInc;						// ���ܶȻָ���

	long            lLuckyValueUpper;               // ����ֵ����

	long            lInitHpLower;                   // ��ʼ��������
	long			lInitHpRandUpper;				// ��ʼ�������ֵ����
	long            lInitHpUpper;                   // ��ʼ��������

	long            lInitPAtcLower;                 // ��ʼ�﹥����
	long			lInitPAtcRandUpper;				// ��ʼ�﹥�����ֵ����
	long            lInitPAtcUpper;                 // ��ʼ�﹥����

	long            lInitMAtcLower;                 // ��ʼħ������
	long			lInitMAtcRandUpper;				// ��ʼħ�������ֵ����
	long            lInitMAtcUpper;                 // ��ʼħ������

	long            lInitPDefLower;                 // ��ʼ�������
	long			lInitPDefRandUpper;				// ��ʼ��������ֵ����
	long            lInitPDefUpper;                 // ��ʼ�������

	long            lInitMDefLower;                 // ��ʼħ������
	long			lInitMDefRandUpper;				// ��ʼħ�������ֵ����
	long            lInitMDefUpper;                 // ��ʼħ������

	long            lHPGrowthLower;                 // �����ɳ�������
	long			lHPGrowthRandUpper;				// �����ɳ������ֵ����
	long            lHPGrowthUpper;                 // �����ɳ�������

	long            lPAtcGrowthLower;				// �﹥�ɳ�������
	long			lPAtcGrowthRandUpper;			// �﹥�ɳ������ֵ����
	long            lPAtcGrowthUpper;				// �﹥�ɳ�������

	long            lMAtcGrowthLower;				// ħ���ɳ�������
	long			lMAtcGrowthRandUpper;			// ħ���ɳ������ֵ����
	long            lMAtcGrowthUpper;				// ħ���ɳ�������

	long            lPDefGrowthLower;               // �����ɳ�������
	long			lPDefGrowthRandUpper;			// �����ɳ������ֵ����
	long            lPDefGrowthUpper;               // �����ɳ�������

	long            lMDefGrowthLower;               // ħ���ɳ�������
	long			lMDefGrowthRandUpper;			// ħ���ɳ������ֵ����
	long            lMDefGrowthUpper;               // ħ���ɳ�������

	long			lInitHPUpperGrade;				// ��ʼ����ֵ����ֵ����
	long			lInitMinPAUpperGrade;			// ��ʼ��С�﹥����ֵ����
	long			lInitMaxPAUpperGrade;			// ��ʼ����﹥����ֵ����
	long			lInitMinMAUpperGrade;			// ��ʼ��С������������ֵ����
	long			lInitMaxMAUpperGrade;			// ��ʼ�������������ֵ����
	long			lInitPDefUpperGrade;			// ��ʼ�����������ֵ����
	long			lInitMDefUpperGrade;			// ��ʼ������������ֵ����
	long			lHPGrowthUpperGrade;			// ����ֵ�ɳ��ʼ���ֵ����
	long			lMinPAGrowthUpperGrade;			// ��С�������ɳ��ʼ���ֵ����
	long			lMaxPAGrowthUpperGrade;			// ����������ɳ��ʼ���ֵ����
	long			lMinMAGrowthUpperGrade;			// ��С���������ɳ��ʼ���ֵ����
	long			lMaxMAGrowthUpperGrade;			// ����������ɳ��ʼ���ֵ����
	long			lPDefGrowthUpperGrade;			// ��������ɳ��ʼ���ֵ����
	long			lMDefGrowthUpperGrade;			// ���������ɳ��ʼ���ֵ����
};

// ������վλ
struct SPetFormation
{
	long	lFormationID;							// ��ID
	char	szName[8];								// ������
	long	lRadius[3];								// ��λ�뾶
	long	lAngle[3];								// ��λ�Ƕ�
	long    lPosFactor[8];							// ��λ�ӳ�ϵ��
	long    lExFactor;								// ����ϵ��	
	long	lKeyPos;								// ����
	long	lActorPropID;							// ��ɫ��������
	long    lPetPropID;								// �����Ӧ����
	float	fPetPosSkillFactor[8];					// add by zjp �����󷨼��ܵ�����ϵ��
	float	fPetPosSkillGrade[5];					// add by zjp �����󷨼��ܵ��ݶ�ֵ
};

// ������ȼ��ҹ�����������
struct SPetLevelPropInfo					
{
	long		lNextExp;						// ���¼�����
	long		lFatalPer;						// ������
	long		lFatal;                         // ����ֵ
	long		lPresent;					    // ����ֵ
	long		lPresentPer;					// ������
	long		lHedge;						    // ����ֵ
	long		lHedgePer;						// ������
	long		lKickFatal;                     // ����ֵ
	long		lKickFatalPer;					// ������
	long		lAttackSpeed;					// �����ٶ�ֵ

	SPetLevelPropInfo(void)
	{
		memset(this, 0, sizeof(*this));
	}
};

// PetFilter.csv
struct SPetFilterInfo
{
	int             nID;                            // ɸѡ��Ӧ������ID
	int             nType;                          // ɸѡ����(������һ��ɸѡ)
	int             nTypeLevel;                     // ��Ӧ���͵�ɸѡ�ȼ�
	char            szName[16];                     // ��Ӧɸѡ������
	int             nPlayerLevel;                   // ��ҵȼ�
	int             nPlayerNazarite;                // �������ȼ�
	int             nPlayerHomage;                  // ��ҹ�ְ
	int             nPetLevel;                      // �꽫�ȼ�
	int             nPetInsetLevel;                 // �꽫�ڵ��ȼ�
	int             nPetStar;                       // �꽫Ʒ��
	bool            bPetRide;                       // �꽫���
	int             nPetType;                       // �꽫����
	char            szPosAttribute[16];             // ������
	int             nNeedPetNum;                    // �󷨴�����Ҫ������
	int             nPosPlace;                      // �󷨴�����λ
	int             nHostPetLevel;                  // ���꽫�ȼ�
	int             HostPetPointLower;              // ���꽫��������
	int             nHostPetPointUpper;             // ���꽫��������
	int             nSecondPetLevel;                // �λ꽫�ȼ�
	int             nSecondPetPoint;                // �λ꽫����
};
// ����ϳ��������ֹ���
struct SPetCompdGradeRule
{
	long	lRefineID;						// ���꣨�ϳɣ�����ID
	char    szName[16];						// ����������
	long	lMainGrade;						// ��������
	long	lMinorGrade;					// ��������
	long	lMinorChummy;					// ��������ܶ�
	short	nIsSameElement;					// �Ƿ���Ҫͬ���ԣ���ľˮ������
	short   nNeedPropComp;					// �Ƿ�Ƚ�����
	short	nNeedIDCard;					// �Ƿ���Ҫ�����
	short	nNeedSameType;					// ͬ����
	short	nNeedLuckyComp;					// �Ƿ���Ҫ�Ƚ�����ֵ
	short   nIsTypeRelated;					// �Ƿ�����������й�
};

// ����ϳ����õȼ�����
struct SPetCompdLevelRule
{
	short	nMainLevel;						// ���輶��
	short	nMinorLevel;					// ���輶��
};

// ��Ʒ���û���
struct SGoodsSchemeInfo
{
	long			lGoodsID;						// ��ƷID,����
	char			szName[32];						// ����

	long			lGoodsClass;					// ��Ʒ�ࣨ1��װ����2����Ʒ��
	long			lGoodsSubClass;					// ��Ʒ���ࣨװ����ҩƷ������ͬ��

	long			lAllowVocation;					// ʹ��ְҵ
	long			lAllowLevel;					// ʹ�õȼ�

	long            lPreCondition;                  // ǰ������

	long			lPileQty;						// ��������

	long			lBuyCost;						// ��������۸�
	long			lSaleCost;						// ������������

	long			lBaseLevel;						// ������Ʒ����
	long			lPickupBcastFlag;				// ʰȡ��㲥��־
	long			lHoldMaxQty;					// ӵ��������
	long			lShortcutFlag;					// �ܷ�ſ����
	long			lBindFlag;						// �󶨱�־λ	
	long			lUseTerm;						// ʹ������

	long			lIconID[3];						// ��Ʒ��ͼƬ����������������Ч��
	long			lIconEffectID;					// ��Ʒ����Ч

	long			lBoxResID;						// ���������ԴID	
	long			lBoxRayResID;					// ������˸��ԴID

	char			szDesc[256];					// ����

	long			lUseCount;						// ʹ�ô���
	long			lGoldGotPrice;					// Ԫ���۸�
	long			lLogoutAction;					// �ǳ���Ϊ��0��ʾ�ǳ�����ʧ�����䣬1�ǵǳ���ʧ��2�ǵǳ����䡣
	long			lChangeMapAction;				// 0��ʾ�뿪��ǰ��ͼ����ʧ��1��ʾ�뿪��ǰ��ͼ��ʧ��
	long			lCanSaleToNPC;					// �ܷ���NPC����
	long			lIsDieDrop;						// �����Ƿ����
	long			lQualityLevel;					// Ʒ�����Եȼ�

	
};

//Equippment.csv
#define ESI_EQUIPLOCNUM							3//װ���Ŀ�װ��λ��
#define ESI_EQUIPAPPIDLEFT						0//װ����һ����Դid
#define ESI_EQUIPAPPIDRIGHT						1//װ���ڶ�����Դid
#define ESI_EQUIPAPPMAX							2//װ����Դ����
#define ESI_SMELTSOULSTABLENUM					3//����ǿ���ȶ�̬����
#define ESI_SMELTSOULMAXLEVEL					9//����ǿ��������
#define ESI_SMELTSOULLEVELATTRIBNUM				4//���꼶���Ӧ����������
#define ESI_BRANDATTRIBMAXLEVEL					6//���Ʒ�����Եȼ�
#define ESI_MAXSLOT								4//װ��������
#define ESI_EQUIP_BASIC_COMBAT_PROPNUM			4//װ���������Ե��������
#define ESI_EQUIP_BRAND_COMBAT_PROPNUM			4//װ��Ʒ�����Ե��������
struct SEquipmentSchemeInfo: public SGoodsSchemeInfo
{
	long			lAllowCamp;						//ʹ����Ӫ
	long			lAllowGender;					//ʹ���Ա�

	long			lSuitEquipID;					// ��װID

	// note by zjp;��Ӧ��Equipment_BasicAttribute.csv����ÿһ���ĸ���������
	//װ���Ļ�������
	long			lBasicCombatPropID[ESI_EQUIP_BASIC_COMBAT_PROPNUM];	//��������id
	long			lBasicCombatPropVal[ESI_EQUIP_BASIC_COMBAT_PROPNUM];//��������ֵ
	
	long			lCanRepair;						//�Ƿ������
	long			lMaxEndurance;					//����;ö�

	long			lEquipLoc[ESI_EQUIPLOCNUM];				//��װ��λ��
	float			fBaseMaleZoom;							//�зŴ���
	uint			uiBaseMaleColor;						//����ɫ
	long			lBaseMaleModelResID[ESI_EQUIPAPPMAX];	//����Դid
	long			lBaseMaleTextureResID[ESI_EQUIPAPPMAX]; //����ͼid

	float			fBaseFemaleZoom;						//Ů�Ŵ���
	uint			uiBaseFemaleColor;						//Ů������ɫ
	long			lBaseFelmaleModelResID[ESI_EQUIPAPPMAX];//Ů��Դid
	long			lBaseFelmaleTextureResID[ESI_EQUIPAPPMAX];//Ů����ͼid

	long			lNeedIdentify;							//�Ƿ���Ҫ����,by cjl
	long			lBrandAttribNum;						//Ʒ����������
	long			lBrandLevel;							//Ʒ�����Եȼ�,��ʷԭ�� lQualityLevel Ҳ��Ʒ�����Եȼ�
	long			lBrandAttribID;							//Ʒ������ID����������Ʒ������

	long			lMaxSlot;								//������

	long			lMaxSmeltSoulLevel;						//���ǿ���ȼ�
	long			lSmeltSoulStablePropID[ESI_SMELTSOULSTABLENUM]; //����ǿ���ȶ�̬����id
	long			lSmeltSoulStablePropValue[ESI_SMELTSOULSTABLENUM];//����ǿ���ȶ�̬����ֵ
	long			lSmeltSoulLevelPropID[ESI_SMELTSOULMAXLEVEL][ESI_SMELTSOULLEVELATTRIBNUM];//����ǿ����������Ӧ������id
	long			lSmeltSoulLevelPropValue[ESI_SMELTSOULMAXLEVEL][ESI_SMELTSOULLEVELATTRIBNUM];//����ǿ����������Ӧ������ֵ

	long			lThrowAndDestroy;				//by cjl ����������

	SEquipmentSchemeInfo(void)
	{
		memset(this, 0, sizeof(SEquipmentSchemeInfo));
	}

	~SEquipmentSchemeInfo(void)
	{
		memset(this, 0, sizeof(SEquipmentSchemeInfo));
	}
};

//
//װ��ǿ�����ȶ�̬����
struct SEquipmentSmeltStalbeConfig
{
	long	lSmeltLevel;
	long	lStableLevel;	
};

//װ�����������������ֵ�ӳ���
struct STableEquipCombatPropID2PropName
{
	typedef std::map<int, std::string> MapInt2String;
	typedef std::map<std::string, int> MapString2Int;
	typedef std::map<int, int> MapInt2Int;//by cjl

	MapInt2String basic_id2name;//��������
	MapString2Int basic_name2id;//��������
	MapInt2Int	  basic_id2value;//by cjl,������ʾ����

	MapInt2String brand_id2name;//Ʒ������
	MapString2Int brand_name2id;//Ʒ������
	MapInt2Int    brand_id2value;//by cjl,������ʾ����

	MapInt2String smeltlevel_id2name;//��������(�뼶�����)
	MapString2Int smeltlevel_name2id;//��������(�뼶�����)
	MapInt2Int    smeltlevel_id2value;//by cjl,������ʾ����

	MapInt2String smeltstable_id2name;//��������(�ȶ�̬)
	MapString2Int smeltstable_name2id;//��������(�ȶ�̬)
	MapInt2Int    smeltstable_id2value;//by cjl,������ʾ����
};

//by cjl
//װ����Ч���ñ�
#define EEL_EFFECTLEVEL								10//װ����Ч�ĵȼ�,��һ����Ĭ�ϵ�
struct SEquipmentAttachedEffects
{
	long	lID[EEL_EFFECTLEVEL];					  //��Чid
};
//Equipment_BrandAttrib.csv
//װ��Ʒ���������ñ�
#define EBA_BRANDATTRIB_AVALIBLENUM							4//Ʒ������,�ͷ���˲�ͬ��ֻ��Ҫ��ϵǰ4��
struct SEquipmentBrandAttribute
{
	long	lID;										//Ʒ������id
	long	lAvaliableNum;								//��Ч��Ʒ����������(��һ����30������)
	long	lAttribName[EBA_BRANDATTRIB_AVALIBLENUM];			//��������
	long	lAttribValBound[EBA_BRANDATTRIB_AVALIBLENUM];	//����ֵ���½�
	//long	lAttribValUpperBound[EBA_BRANDATTRIB_AVALIBLENUM];	//����ֵ�Ͻ�
	SEquipmentBrandAttribute(void) { memset(this,0,sizeof(SEquipmentBrandAttribute)); } 
	~SEquipmentBrandAttribute(void) { memset(this,0,sizeof(SEquipmentBrandAttribute)); }
};
//end cjl

//GemsCombinationEffect.csv
//��ʯ���Ч�����ñ�
#define GCE_EFFECTRANK								3//���������3��
#define GCE_RANKBITNUM								3//��3λ��ʾ��ʯ�ȼ�����ʯ��7���ȼ�
#define GCE_EFFECTNAMELEN							16//���Ч��������
struct SGemsCombinationEffect
{
	long	lEffectID;								//���Ч��id���ɲ�ͬ�ı�ʯ��˳������
	long	lEffectLevel;							//��ϵļ�����
	char	cEffectName[GCE_EFFECTNAMELEN];			//��ϵ�����
	
	long			lPMinAttack;				// ����������С����
	long			lPMaxAttack;				// ����������󹥻�
	long			lPDefend;					// �����������,û�������Сֵ֮��

	long			lMMinAttack;				// ���ӷ�����С����
	long			lMMaxAttack;				// ���ӷ�����󹥻�
	long			lMDefend;					// ���ӷ�����������û�����ֵ����Сֵ֮��

	long			lPresent;					//�������и���
	long			lHedge;						//�������ܸ���

	long			lFatalDamage;				//���ӱ���ֵ
	long			lResist;					//���Ӹ�

	long			lHPLimmit;					//������������
	long			lMPLimmit;					//���ӷ�������

	long			lMoveSpeed;					//�����ƶ��ٶȰٷֱ�
	long			lAttackSpeed;				//���ӹ����ٶȰٷֱ�

	long			lDirectPlusPDamage;			//����������������������˺�
	long			lDirectPlusMDamage;			//�������ӷ��������ķ����˺�
	long			lDirectMinusPDamage;		//ֱ�Ӽ������������˺�
	long			lDirectMinusMDamage;		//ֱ�Ӽ������շ����˺�		
	SGemsCombinationEffect(void) { memset(this,0, sizeof(SGemsCombinationEffect) );}
	~SGemsCombinationEffect(void) {}
};

// NonequipableGoods.csv
struct SNonequipableGoodsSchemeInfo : public SGoodsSchemeInfo
{
	long			lOnID;							// ����ID
	long			lSkillRequirement;				// ����Ҫ��
	long			lCanSaveToWare;					// �ܷ����ֿ�
	long			lCanDrouOut;					// �ܷ���
	long            lFlashID;                       // ʹ����Ʒ��Ĺ�Ч

	// add by zjp;�����ӵ�����
	long			lCanUse;						// �Ƿ����ʹ��
	long			lLoadTime;						// ʹ��ʱ�Ķ���ʱ��
	long			lFunctionLevel;					// ����ID�ȼ�
	long			lCDType;						// ʹ��ʱ�ǵ�CD���ǹ���CD
	long			lCDTime;						// ʹ��ʱCDʱ��

	// zgz
	long            lPetID;							// �����ĳ���ID��ʹ�ô���Ʒ�����һֻ����
};

// MapInfo.xml
struct SMapSchemeInfo
{
	long			lMapID;							// ��ͼID
	char			szName[32];						// ��ͼ����
	long			lOpenZoneServerID;				// ���ų�����ID
	long			lStartLoadFlag;					// �����Ƿ����룬 1�����롣2��������
	long			lDynamicFlag;					// �Ƿ�̬���룬 1����̬��2������̬
	long			lVestNation;					// �������ң�0����ʾ������1��2��3.... ������ID
	char			szMapFile[MAX_PATH];			// ��ͼ�ļ�����
	char			szWayFile[MAX_PATH];			// ���ڶ�ȡ����ͼ���Զ�Ѱ·�ļ�
	char			szWorldPicFile[MAX_PATH];		// �����ͼ
	char			szMonsterBuildFile[MAX_PATH];	// �������������ļ�
	char			szChunnelBuildFile[MAX_PATH];	// ���������������ļ�
	char			szBoxBuildFile[MAX_PATH];		// ��ҩ����ȵȵ����������ļ�
	long			lBackMusicID;					// ��������id
	long			lGroupMapID;					// ���ͼid

    long            lCellFlag;                      //�õ�ͼ�Ƿ���Է���
	long            lCellCapacity;                  //����ʱ��ÿ���������������ɵ�����
	long            lInstanceFlag;					//������־Instance �����ָñ�־ʱ���� ���߱�־cell    
	long			lInstanceKickNotify;			//���������Ƿ���������ʾ
};

// Entity.xml
struct SPropCountRateSchemeInfo
{
	int				nConstit_ex_HP;					// һ�����ʶһ���������ֵ
	int				nConstit_ex_PD;					// һ�����ʶһ������������
	int				nForce_ex_PA;					// һ�������һ�����������
	double			fCelerity_ex_PS;				// һ�����ݶһ�������������
	double			fCelerity_ex_Present;			// һ�����ݶһ���������
	int				nIntellect_ex_MA;				// һ�������һ����ٷ�������
	int				nEnergy_ex_MD;					// һ�㾫��һ����ٷ�������
	int				nEnergy_ex_MP;					// һ�㾫��һ����ٷ���ֵ
	double			fEnergy_ex_MF;					// һ�㾫��һ����ٷ�������
	double			fEnergy_ex_Present;				// һ�㾫��һ���������
	double			fDefault_base_Present;			// Ĭ�ϻ���������
	double			fDefault_base_Hedge;			// Ĭ�ϻ���������
	double			fDefault_FatalPer;		        // Ĭ����������
	double			fDefault_base_Penetrate;		// Ĭ�ϻ�����͸
	double			fDefault_base_Resist;			// Ĭ�ϻ�����
};
//Aduio.XML
struct SAudioConfig 
{
	long            lMusicID;                      //����ID
	char            szMusicFileName[MAX_PATH];     //�����ļ�
};
// ConfingAreaAudio.XML
struct SAreaAudioConfig
{
	int            nMapID;          // ��ͼID
	int            nMusicID; 
	int            nMusicType;      // ��������
	int            nLoop;           // ѭ������    
    xs::Rect	       rectArea;		// ��������
};

//Creature.xml

struct ConfigRide//�������
{
	std::string boneName;//���ʱ�󶨹���
	std::string rideAction;//��˶���
};

struct SCreatureConfig: public ConfigModelNode
{
	std::string resId;
	std::string basicCreatureName;
	ConfigRide  cRide;
};

/////////////////////��װ////////////////////////////////////
//////////����Ҫ������lua/////////////////////////////////////

/// ʵ�岿��
enum EntityParts
{
	EEntityPart_Invalid = 0,	//��Чֵ
	EEntityPart_Weapon,			//����
	EEntityPart_Armet,			//ͷ��
	EEntityPart_Armor,			//����
	EEntityPart_Cuff,			//����
	EEntityPart_Shoes,			//Ь��
	EEntityPart_Necklace,		//����
	EEntityPart_Ring,			//��ָ
	EEntityPart_DecorationL,	//���׹
	EEntityPart_DecorationR,	//�ҹ�׹
	EEntityPart_Suit_Armet, //ʱװͷ��
	EEntityPart_Suit_Armor,//ʱװ����
	EEntityPart_Max,		//���ֵ��������������չ
};

//��װʱ����Դ�����֣�һ������Ҫ��Դ������һ���Ǹ�����Դ�������ӵ���Ч
enum // ��װʱ��Դ������
{
	EBindResNum_MainPart = 2,//��Ҫ��Դ������
	EBindResNum_Attachment = 6,//������Դ������
};

enum //��Դ��ʹ�����ͣ�Ŀǰֻʹ����ģ�Ͱ�
{
	EBindType_Min,
	EBindType_Replace=0, //�滻����ģ��
	EBindType_SubNode, //��ģ��
	EBindType_Texture, //�滻����Ŀǰû�ã�
	EBindType_Max,
};

enum //�ڰ�ģ�͵�����£��󶨵�
{
	//��������Ҫ�����İ󶨵�
	EBindPoint_Min = 0, //
	EBindPoint_LeftHand ,//����
	EBindPoint_RightHand ,//����
	EBindPoint_LeftBack,//��
	EBindPoint_RightBack,//�ұ�
	EBindPoint_Head,//ͷ��
	//�����Ǹ�����Ч�İ󶨵�
	EBindPoint_Attach_WeakRay,//�ⲿ����
	EBindPoint_Attach_StrongRay, //�ⲿǿ��
	EBindPoint_Attach_FlowRay_1, //������1
	EBindPoint_Attach_FlowRay_2, //������2
	EBindPoint_Attach_RadiationRay, //���͹�
	EBindPoint_Attach_FewFloatParticles, //����Ư������
	EBindPoint_Attach_SomeFloatParticles, //һЩƯ������
	EBindPoint_Attach_RadiationParticles, //��ɢ����
	EBindPoint_Attach_RibbonParticles, //������βЧ��������
	EBindPoint_Max,
};
enum //װ������Ч������
{
	EAttachType_Min =0,
	EAttachType_SmeltSoul, //װ�������İ�����
	EAttachType_EmbedGems, //װ��Ƕ�뱦ʯ
	EAttachType_Max,
};

enum EWeaponClass //��������
{
	EWeapon_NoWeapon,//û������
	EWeapon_FirstClass,//���������������
	EWeapon_SecondClass,//���������󣬷���
	EWeapon_Max,
};

struct SPersonMainPartChangeContext //������Ҫװ����װ����
{
	ulong resId[EBindResNum_MainPart];//��Դid
	bool perform;//true������װ����false��ж��װ��
	uchar part;//��װ����
	uchar bindType[EBindResNum_MainPart];//�󶨷�ʽ
	uchar bindPoint[EBindResNum_MainPart];//�󶨵�
	uchar weaponclass;//��������Ч
	uchar weaponsubclass;//�������࣬��������Ч
};

struct SPersonAttachPartChangeContext//������Ҫװ������Ч����װ����
{
	ulong resId[EBindResNum_Attachment];//��Դid
	float	scale[EBindResNum_Attachment];//������Ч������
	uint color[EBindResNum_Attachment];//�󶨵���ɫ
	bool perform;//true�����ӣ�false��ȡ������
	uchar part;//�󶨲���
	uchar attachType;//���ӵ�����
	uchar bindType[EBindResNum_Attachment];//�󶨷�ʽ
	uchar bindPoint[EBindResNum_Attachment];//�󶨵�
};

struct SPersonPartDeformationContext
{
	bool deform;//�Ƿ����
	ulong part;//�󶨲�����Ŀǰֻ֧������
	ulong resId[EBindResNum_MainPart];//����ʹ�õ���Դid
	//����Ҫ�󶨵�Ͱ����ͣ���Ϊ���Ǹ��ӵ�
};

// add by zjp��������Ʒ
#define SOUL_LEVEL_MAX						5//by cjl
struct SEspecilGood
{
	int		nGoodID;
	int		nProtect;
	bool	bSoul;
	int		nSoulLevel;		  // ��ʯ�ȼ�
	bool	bAssistantSmelt;
	float	nAddProbability; // ���Ӹ���ɹ���
	int		nReduceLevel;	// ����ʧ�ܽ��͵ȼ���
	int		nPillLevel;		//�ڵ��ȼ�//by cjl ,����²���
	bool	bPill;			//�Ƿ��ڵ�//by cjl ,����²���
};

// add by zjp��װ���ȼ�-����Ʒ��
struct SEquipLevelToQuality
{
	int nUpperLevel; // �ȼ�����
	int nQuality;	 // ����Ʒ��
};

// add by zjp���������
struct SSmeltInfo
{
	int nSmeltLevel;	// ���꼶��
	std::string sName1;      // ��������1
	int    nNum1;		// ��������1
	std::string sName2;		// ��������2
	int    nNum2;		// ��������2
};

struct SSmeltSoulProbability
{
	int nSoulCount;
	int nProbability;
};

struct SGoodsType
{
	int         nGoodsID;           // goods ID
	char		szDesc[16];			// ����
	SGoodsType()
	{
		memset(this, 0, sizeof(SGoodsType));
	}
};

struct SItemProp
{
	int  nItemID;
	char szName[32];
	SItemProp()
	{
		memset(this, 0, sizeof(SItemProp));
	}
};

struct SStallInfo
{
	int         nStallID;           // ̯λID
	int			nMapID;				// ��ͼID
	char		szStallName[32];	// ̯λ����

	//int			nStallFlagMonsterID;// ̯λ�����ID

	int         nPrimaryResID;		// ����̯λNPCID
	int         nIntermediateResID; // �м�̯λNPCID
	int         nAdvanceResID;      // �߼�̯λNPCID

// 	int         nFlagTileX;			// ̯λ������X
// 	int         nFlagTileY;			// ̯λ������Y
// 	int         nFlagAngle;			// ̯λ�췽��

	int         nTileX;				// ����X
	int         nTileY;				// ����Y
	int         nAngle;				// ����
};

struct SOnlineShopGoods
{
	int		iGoodsID;		//��ƷID���
	int		iItemID;		//��ƷID����ӦEquipment��Nonequipablegoods���е���ƷID��
	char    szGoodsName[24];	//�������9������
	int		eGoodsType;		 //��Ʒ����
	int		eGoodsSubType;	 //��Ʒ����
	//�����ñ�ͬ���ǣ�����תΪ��¼�����۸� �� ԭʼ�۸�
	int		iPriceBaobi;	//���Ҽ۸�
	int		iOriginalPriceBaobi; //ԭʼ���Ҽ۸�
	int		iPriceJiaozi;   //���Ӽ۸�
	int		iOriginalPriceJiaozi;//ԭʼ���Ӽ۸�
	const char* GetGoodsName(void) const
	{
		return szGoodsName;
	}
};

//--���ñ���"�ۺ�۸�"�ֶ������0�����ʾ����ƷΪ������Ʒ��
//--������Ʒ�ļ۸���ʾΪ�ۺ�۸񣬶���ԭ�ۡ���ҹ���ʱ�����Ҳ���ۺ�۸�
//--Ϊ�˽���ͳһ����α��һ�������Ĵ��� Ϊ99999
#define ONLINE_SHOP_PROMOTION_FAKE_TYPE 9999

///////////////////////////////////////////////////////////////

struct SMapWeather
{
	ulong ulWeatherMagicID;
	int	  nDurationTime;  // -1��ʾ����60~300ֱ�����
	int  nFade;
	int  nFall;
	SMapWeather()
	{
		ulWeatherMagicID = 0;
		nDurationTime = 0;
		nFade = 0;
		nFall = 0;
	}
};


///////////////////////////////////////////////////////////////////
// ��������
struct ISchemeCenter
{
	//by cjl
	/** ȡ�ñ����������Ϣ
	@param  
	@return  
	*/
	virtual  SChangeBodySchemeInfo*			GetChangeBodySchemeInfo(int id) = 0;

	/** ȡ�����������������Ϣ
	@param  ְҵ 
	@param  ����ȼ�,��1��ʼ
	@return  
	*/	
	virtual SPresentSchemeInfo *			GetPresentSchemeInfo(int vocation, int PresentLevel) = 0;
	//end cjl

	/** ȡ�ù����������Ϣ
	@param   
	@param   
	@return  
	*/	
	virtual SMonsterSchemeInfo *			GetMonsterSchemeInfo(long lMonsterID) = 0;

	/** ȡ�ó����������Ϣ
	@param   
	@param   
	@return  
	*/	
	virtual SPetSchemeInfo*                GetPetSchemeInfo(long lPetID) = 0;

	/** ȡ�ó������������Ϣ
	@param   
	@param   
	@return  
	*/
	virtual SPetFormation *                 GetPetFormation(long lFormation) = 0;


	/** ȡ����Ʒ��������Ϣ
	@param   
	@param   
	@return  
	*/
	virtual SGoodsSchemeInfo *				GetGoodsSchemeInfo(long lGoodsID) = 0;

	/** ȡ��װ����������Ϣ
	@param   lGoodsID ����ƷID
	@return  
	*/
	virtual SEquipmentSchemeInfo *			GetEquipmentSchemeInfo(long lGoodsID) = 0;

	/** ȡ��װ���ĸ���Ʒ������������Ϣ by cjl
	@param   lGoodsID ����ƷID
	@return  
	*/
	virtual SEquipmentBrandAttribute *			GetEquipmentBrandAttributesSchemeInfo(long lGoodsID) = 0;

	/**�õ�װ���ĸ�����Ч
	@param
	@param
	@return
	*/
	virtual SEquipmentAttachedEffects * GetEquipmentAttachedEffects(long lAttachEffectID) = 0;

	/** ȡ�÷�װ������Ʒ��������Ϣ
	@param   
	@param   
	@return  
	*/
	virtual SNonequipableGoodsSchemeInfo *			GetNonequipableGoodsSchemeInfo(long lGoodsID) = 0;

	/** ȡ��װ����ʯ��Ƕ�����Ч��
	@param   lGoodsID ����ƷID
	@return  
	*/
	virtual SGemsCombinationEffect * 		GetEquipmentEmbedGemsCombinationEffect(long lEffectID) = 0;

	/** ȡ�õ�ͼ������Ϣ
	@param   
	@param   
	@return  
	*/
	virtual SMapSchemeInfo *				GetMapSchemeInfo(long lMapID) = 0;

	/**ȡ��������������Ϣ
	@param   lMusicID������ID
	@param   
	@return  
	*/
	virtual SAudioConfig*                  GetAudioSchemeInfo(long lMusicID) = 0;

	///**ȡ�ó���������ID
	//@param  
	//@param   
	//@return  
	//*/
	virtual bool                 GetAreaAudioMusicID(int lMapID,xs::Point pt,int &nMusicID,int &nMusicType,int &nLoopType) = 0;

	/** ȡ�ó�ʼ���
	@param   nSelfCampID �����ѵ���ӪID
	@param   nOtherCampID���Է�����ӪID
	@return  
	*/
	virtual int								GetInitEnmity(int nSelfCampID, int nOtherCampID) = 0;

	/** ȡ�������������
	@param   lLevel : �ȼ�
	@param   lVocation : ְҵ
	@return  
	*/
	virtual SPersonBasePropSchemeInfo *		GetPersonBasePropSchemeInfo(long lLevel, long lVocation) = 0;

	/** ͨ����ӪIDȥ��ȡ��Ӫ����
	@param   nCampID ����ӪID
	@return  
	*/
	virtual std::string             GetCampNameByCampID(int nCampID) = 0;

	/** ȡ�á����¼����顱
	@param   
	@param   
	@return  
	*/
	virtual int								GetNextLevelExp(int nCurLevel) = 0;

	/** ȡ�������ƶ��ٶ�
	@param   nSpeedLevel ���ٶȵȼ�
	@param   
	@return  
	*/
	virtual int								GetCreatureMoveSpeed(int nSpeedLevel) = 0;

	/** ȡ����������ٶ�
	@param   nSpeedLevel ���ٶȵȼ�
	@param   
	@return  
	*/
	virtual int								GetCreatureRideSpeed(int nSpeedLevel) = 0;


	/** ȡ�ó���ɸѡ������
	@param   nType ������
	@param   nTypeLevel���ȼ�
	@return  
	*/
	virtual SPetFilterInfo*                 GetPetFilterSchemeInfo(int nTypeID)= 0;

	/** �õ��������¼��ľ���
	@param   
	@param   
	@return  
	*/
	virtual SPetLevelPropInfo *				GetPetLevelPropInfo(int nCurLevel) = 0;

	/** �õ���Ҫװ����װ����
	@param   
	@param   
	@return  
	*/
	virtual bool							GetPersonMainPartChangeContext(int nEquipID, int nGender, int nSmeltSoulLevel,SPersonMainPartChangeContext & context  )= 0;//by cjl,����˵�ǰǿ���ȼ�


	/** �õ�������Ҫװ������Ч����װ����
	@param   
	@param   
	@return  
	*/
	virtual bool							  GetPersonAttachPartChangeContext(int nEquipID, int nAttachType, int nSmeltSoulLevel, int nEmbedGems, SPersonAttachPartChangeContext & context)= 0;
	

	/** �õ����ﻻװ�����󶨵�
	@param   
	@param   
	@return  
	*/
	virtual const char * getBindPoint(ulong bp) = 0;

	/** ȡ�ó���ϳɵ��������ƹ���
	@param   
	@param   
	@return  
	*/
	virtual SPetCompdGradeRule *           GetPetCompdGradeSchemeInfo(long lRefineID,long lGrade) = 0;

	/** ȡ�ó���ϳɵļ������ƹ���
	@param   
	@param   
	@return  
	*/
	virtual SPetCompdLevelRule *           GetPetCompdLevelSchemeInfo(long lLevel) = 0;

	/** ���װ��ս������id�����ֵ�ӳ���
	@param   
	@param   
	@return  
	*/
	virtual const STableEquipCombatPropID2PropName * GetEquipTableCombatPropId2PropName() = 0;
	/** ȡ�ó���ս������
	@param   
	@param   
	@return  
	*/
	virtual SPetPropSchemeInfo *			GetPetPropSchemeInfo(long lPetID) = 0;

	/** ���װ�������ȶ�̬����
	@param   
	@param   
	@return  
	*/
	virtual const SEquipmentSmeltStalbeConfig * GetEquipSmeltStableConfig(int smeltlevel ) = 0;

	/** ���������Ʒ�������� add by zjp
	@param   
	@param   
	@return  
	*/
	virtual SEspecilGood* GetEspecialGood(int nGoodID) = 0;

	/** ���������ǵȼ� add by zjp
	@param   
	@param   
	@return  
	*/
	virtual int	 GetNeededQuality(int nLevel) = 0;

	/** ȡ��������Ϣ���� add by zjp
	@param   
	@param   
	@return  
	*/
	virtual SSmeltInfo*  GetSmeltInfo(int nSmeltLevel) = 0;

	/** ȡ�÷�װ����������Ϣ���� add by zjp
	@param   
	@param   
	@return  
	*/
	virtual SSmeltInfo*  GetSmeltNotWeaponInfo(int nSmeltLevel) = 0;

	/** ȡ�þ���װ����� add by zjp
	@param   
	@param   
	@return  
	*/
	virtual int		    GetSmeltEquipFee(int nLevel) = 0;

	/** ȡ��������� add by zjp
	@param   
	@param   
	@return  
	*/
	virtual int         GetRebuildEquipFee(int nLevel) = 0;

	/** ȡ�û�����������
	@param   
	@param   
	@return  
	*/
	virtual int			GetSoulUpgradeFee(int nQuality) = 0;

	/** ͨ������ȡ�û�����ƷID
	@param   
	@param   
	@return  
	*/
	virtual int		   GetSoulIDByName(std::string name) = 0;

	/** ��ȡ�ᴿ�ɹ���
	@param   
	@param   
	@return  
	*/
	virtual int		   GetSmeltSoulProbability(int nCount) = 0;

	
	/** 
	@param   
	@param   
	@return  
	*/
	virtual std::list<SItemProp>   GetItemPropList(int nType) = 0;
	
	/** 
	@param   
	@param   
	@return  
	*/
	virtual std::list<SGoodsType>*   GetGoodsTypeList(int nType, int nItemID) = 0;

	/** 
	@param   
	@param   
	@return  
	*/
	virtual SStallInfo*				GetSchemeStall(int nStallID) = 0;

	/** 
	@param   
	@param   
	@return  
	*/
	virtual const std::string & getResFromId(int id) = 0;

	/** 
	@param   
	@param   
	@return  
	*/
	virtual int		getSoundIDFromId(int id) = 0;

	/** 
	@param   
	@param   
	@return  
	*/
	virtual SCreatureConfig* getCreature(int id) = 0;

	/** 
	@param   
	@param   
	@return  
	*/
	virtual int						GetOnlineShopGoodsCount(int iType, int iSubType) const = 0;

	virtual const SOnlineShopGoods *GetOnlineShopGoodsByID(int iGoodsID) = 0;

	virtual void GetOnlineShopGoodsStart(void) = 0;
	virtual const SOnlineShopGoods * GetOnlineShopNextGoods(int iType, int iSubType) = 0;
	
	virtual bool                    GetRandeMapWeather(DWORD dwMapID, SMapWeather& mapWeather) = 0; 
};

#pragma pack()