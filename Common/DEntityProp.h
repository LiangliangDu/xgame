/*******************************************************************
** �ļ���:	e:\Rocket\Server\EntityServer\Src\DEntityProp.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2008/1/12  15:58
** ��  ��:	1.0
** ��  ��:	ʵ�����Զ���
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ *******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
/*
ʵ�����Դ����ǱȽ��鷳�ġ�
һ��δ����Ҫ��������Ի���ɾ�����ԡ����ֽ����������ʹ�����Լ�����̬��ϡ�
	ʹ�����Լ�Ч�ʲ��ߣ�������Ҫ��ͣ��new�ڴ棬��̫���ã��������ǵ���Ϸ��
	�����ڳ��ھ͹̶����ԣ�δ��Ҫ��ӻ���ɾ���Ļ����ֲ��ࡣ���Է������Լ���
����ÿ��ʵ�������Ҫ�ֹ㲥���ԣ�ͬһ���Ź�������ն˶��ɼ�����˽�����ԣ�ֻ
	�������ն˿ɼ������������ԣ�ֻ���ڷ������ˣ��������նˣ������ݿ����ԣ�
	�����ݿ⣩�����ʹ�����Լ���ÿ�θ��£���Ҫȥ��ѯһƬ��Ч�ʲ��ߡ�������
	�ķ��������Ҫȡ��ĳ��ʵ������й㲥���ԣ�ֱ��copyǰ��һ�����ݼ��ɣ��ܿ졣
��������������͹����Ϊ�кܶ�ģ�飬����״̬�ͼ��ܣ�������ֿ�������Щ
	ģ�鶼ֻ�������Ȼ�����й������ԣ���Ҳ�в�ͬ�����ԡ������һ������ID��
	�������������̫���˷��ڴ档�������������ID���Ʊ�����ģ��Ҫ�ֿ�����
	���ڲ�ȡ�������ⲿͳһ���ڲ��ֿ������ڲ������
	ͨ��s_nCreatureID2MonsterIDTableת����
//*/
#pragma once

//////////////////////////////����ID����///////////////////////////
enum
{
	// ����ID�������ENTITYPART + Ӧ�õ�ʵ��� + ���ܺ��壩
	ENTITYPART_ENTITY_INVALID = 0,		// ��Ч����ID
	ENTITYPART_ENTITY_BUFF,				// buff����
	ENTITYPART_PERSON_BROADCAST,		// �㲥����
	
	ENTITYPART_MONSTER_AI,				// ���ɲ���	
	ENTITYPART_MONSTER_HOLD,			// ��������

	ENTITYPART_CREATURE_MOVE,			// �ƶ�����	
	ENTITYPART_CREATURE_SKILL,			// ���ܲ���
	ENTITYPART_CREATURE_COMMON,			// ��������	
	ENTITYPART_CREATURE_RIDE,			// ��˲���
	ENTITYPART_CREATURE_CONJURE,		// �ٻ�����
	ENTITYPART_CREATURE_CAMP,			// ��Ӫ����
	ENTITYPART_CREATURE_DIE,			// ��������

	ENTITYPART_PERSON_CHAT,				// ���첿��
	ENTITYPART_PERSON_FREEZE,			// ��ȴ����
	ENTITYPART_PERSON_TEAM,				// ��Ӳ���
	ENTITYPART_PERSON_STALL,			// ��̯����
	ENTITYPART_PERSON_FRIEND,			// ���Ѳ���
	ENTITYPART_PERSON_PACKET,			// ��������
	ENTITYPART_PERSON_EQUIP,			// װ������
	ENTITYPART_PERSON_WARE,				// �ֿⲿ��
	ENTITYPART_PERSON_DIE,				// ��������
	ENTITYPART_PERSON_PKMODE,			// �У˲���	
	ENTITYPART_PERSON_CLAN,				// ���岿��
	ENTITYPART_PERSON_NATION,			// ���Ҳ���
	ENTITYPART_PERSON_HUN,				// ��겿��
	ENTITYPART_PERSON_PET,				// ���ﲿ��
	ENTITYPART_PERSON_PETWAREHOUSE,		// ����ֿⲿ��
	ENTITYPART_PERSON_SHOP,				// �̵겿��
    ENTITYPART_PERSON_TASK,				//  ���񲿼���
	ENTITYPART_PERSON_AMUSEMENT,        // �������
	ENTITYPART_PERSON_EQUIPSMELTSOUL,  // װ�����겿��
	ENTITYPART_PERSON_EQUIPEMBEDGEMS,  // װ����ʯ��Ƕ����
	ENTITYPART_PERSON_EQUIPREBUILD,	   // װ����������	
	ENTITYPART_PERSON_COMPOSE,		   //�ϳɲ���  by ldy
	ENTITYPART_PET_INTENSIFY,		   //�꽫ʥ��	by ldy
	ENTITYPART_PERSON_STATISTICS,      // ɱ��ͳ�Ʋ���
	ENTITYPART_PERSON_COLLECTION,      // �ɼ�����

	ENTITYPART_ENTITY_MAXID,			// ��󲿼�ID
};



//////////////////////�������״̬ID����///////////////////////////


enum
{
	CREATURE_CONTROLSTATE_UNKNOW = 0,	// δ֪��
	CREATURE_CONTROLSTATE_STAND,		// վ��
	CREATURE_CONTROLSTATE_SIT,			// ����
	CREATURE_CONTROLSTATE_RIDE,			// ����
	CREATURE_CONTROLSTATE_DIE,			// ����
	CREATURE_CONTROLSTATE_JUMP,         // ��Ծ
	CREATURE_CONTROLSTATE_FLY,          // ����
	CREATURE_CONTROLSTATE_SWITCH,		// �л�������
	CREATURE_CONTROLSTATE_STALL,		// ��̯
	CREATURE_CONTROLSTATE_TRADE,		// ����
	CREATURE_CONTROLSTATE_CHANGEBODY,   // ����
};
//by cjl �������ᡢ����ԭ��
enum
{
	FULL_FREEZE_PART_REASON_CHANGEBODY,		//���������ȫ����
	PART_FREEZE_PART_REASON_CHANGEBODY,		//��������Ĳ��ֶ��ᣬ�缼�ܲ���
};
//end cjl

///////////////////////�����Ա�////////////////////////////////////
enum
{
	PERSON_SEX_MALE = 0,				// ����
	PERSON_SEX_FEMALE,					// Ů��
};

///////////////////////������ӪID////////////////////////////////////
enum
{
	PERSON_CAMP_KNIGHT = 1,				// ����
	PERSON_CAMP_FENCIBLE = 2,			// �ξ�
	PERSON_CAMP_ONUS     = 3,           // ���
	PERSON_CAMP_MAXID,
};

///////////////////////����ְҵ////////////////////////////////////
enum
{
	PERSON_VOCATION_MIN = -1,
	PERSON_VOCATION_WARRIOR,			// սʿ
	PERSON_VOCATION_ARCHER,				// ����
	PERSON_VOCATION_SORCERER,			// ��ʦ
	PERSON_VOCATION_MAX,				// ���
};
//////////////////////////////��������/////////////////////////////
enum
{	
	CREATURE_PROP_PDBID =1,                                 // ��ɫ���ݿ�ID 

	CREATURE_PROP_SEX,                                      // �Ա�
	CREATURE_PROP_VOCATION,                                 // ְҵ
	CREATURE_PROP_LEVEL,                                    // �ȼ�
	CREATURE_PROP_NATION,                                   // ����
	CREATURE_PROP_FAMILY,									// ����
	CREATURE_PROP_ARMY,										// ����
	CREATURE_PROP_PROVINCE,                                 // ��ɫ��ʡ��
	CREATURE_PROP_CITY,                                     // ��ɫ���ڵĳ���
	CREATURE_PROP_CONSTELLATION,                            // ��ɫ������
	CREATURE_PROP_BLOODTYPE,                                // ��ɫ��Ѫ��
	CREATURE_PROP_CUR_HP,                                   // ��ǰ����ֵ  //����ʵ��(����)��������
	CREATURE_PROP_CUR_MAX_HP,                               // ����ֵ����
	CREATURE_PROP_CUR_MP,                                   // ��ǰ����ֵ
	CREATURE_PROP_CUR_MAX_MP,                               // ����ֵ����  //����ʵ��(����)��������
	CREATURE_PROP_CUR_SP,									// ��ǰ����ֵ
	CREATURE_PROP_CUR_MAX_SP,								// ����ֵ����	
	CREATURE_PROP_CUR_MOVE_SPEED,                           // ��ǰ�ƶ��ٶ�
	CREATURE_PROP_CUR_WALK_SPEED,                           // ��·�ٶ�
	CREATURE_PROP_CUR_MOVE_STYLE,                           // ��ǰ�ƶ���ʽ

	CREATURE_PROP_CUR_MIN_P_A,                              // ��ǰ��С������
	CREATURE_PROP_CUR_MAX_P_A,                              // ��ǰ���������
	CREATURE_PROP_CUR_MIN_M_A,                              // ��ǰ��С��������
	CREATURE_PROP_CUR_MAX_M_A,                              // ��ǰ���������
	CREATURE_PROP_CUR_P_D,                                  // ����ʵ��(����)�������ֵ
	CREATURE_PROP_CUR_M_D,                                  // ����ʵ��(����)��������

	CREATURE_PROP_CUR_FATAL,                                // ����ʵ��(����)����ֵ��������ʾ
	CREATURE_PROP_CUR_KICK_FATAL,                           // ����ʵ��(����)����ֵ��������ʾ
	CREATURE_PROP_CUR_PRESENT,                              // ����ʵ��(����)����ֵ��������ʾ
	CREATURE_PROP_CUR_HEDGE,                                // ����ʵ��(����)����ֵ,������ʾ
	CREATURE_PROP_CUR_FIGHT,                                // ����ʵ��(����)ս����
	CREATURE_PROP_FACEID,                                   // ͷ��ID
	CREATURE_PROP_IGNO_BLCOK,                               // �Ƿ�����赲
	
	CREATURE_PERSON_BROADCAST,                              // ��������Ϊ�㲥����
	/////////////////////////////////////////////////

	CREATURE_PROP_PURSE_MONEY,                              // ���Ͻ�Ǯ
	CREATURE_PROP_PURSE_MONEY_INCOME_CHECK,                 // crr�ŵ����ϵĽ�Ǯ�����������顣�������ID������Ϊ�˲��ƻ�SetNumProp�Ļص�֧�֣����������ϵͳ�����Ǯ����
															//�ô��ǿ���ͳһ�ڻص��ĵط�ͳһ����,�����պ�����������
															//������m_nNumProp[CREATURE_PROP_PURSE_MONEY_ENTHRALl_PROTECT]���Ӧ��ֵ��ʱ������
	CREATURE_PROP_PURSE_GOLDINGOT,                          // ����Ԫ�� ��˾���ݿ��еı���
	CREATURE_PROP_PURSE_JIAOZI,                             // ���Ͻ���
	CREATURE_PROP_USABLEBAG,								// ��������
	CREATURE_PROP_WARE_MONEY,                               // �ֿ��Ǯ
	CREATURE_PROP_WARE_LOCK,                                // �ֿ��Ƿ���
	CREATURE_PROP_WARE_lOCKTIME,                            // ����ʱ��
	CREATURE_PROP_EXP,                                      // ����
	CREATURE_PROP_SKILLPOINT,                               // ���ܵ�
	CREATURE_PROP_SKILLPOINT_CONSUME_BRANCH_FIRST,          // ��һ�����ܷ�֧�����ĵļ��ܵ�
	CREATURE_PROP_SKILLPOINT_CONSUME_BRANCH_SECOND,         // �ڶ������ܷ�֧�����ĵļ��ܵ�
	CREATURE_PROP_SKILL_CONSUMEMP_INC_PER,                  // ���еļ����������Ӱٷֱ�
	CREATURE_PROP_BASE_MAX_HP,                              // ��������ֵ����	
	CREATURE_PROP_BASE_MAX_MP,                              // ��������ֵ����
	CREATURE_PROP_BASE_MAX_SP,                              // ��������ֵ����
	CREATURE_PROP_CUR_ATTACK_SPEED,                         // ����ʵ��(����)�����ٶ�ֵ
	CREATURE_PROP_NORMAL_ATTACK_CONSUMEMP_PER,              // ÿ����ͨ�����������ķ���ֵ�İٷֱ�
	//CREATURE_PROP_NORMAL_ATTACK_RATE_PER,                 // ��ͨ�����ٶ����Ӱٷֱ�
	CREATURE_PROP_MAGIC_BALLOON_NUM,                        // ������Ͼۼ������������Ŀ

	CREATURE_PROP_ENTHRALL_PROTECT_INCOME_PERCENT,			//�����Ա��� ��ǰ����ٷֱ�,���������Ϊ100 ������3-5СʱΪ50  5Сʱ��Ϊ0

	CREATURE_PERSON_PRIVATE,                                // ��������Ϊ˽������
	/////////////////////////////////////////////////

	CREATURE_PROP_PETS_STAR_FIGHT,                          // ���г��������Ǽ���ߵ�ս����
	CREATURE_PROP_PLUS_PM_SHIELD_ABSORB_REMAIN,             // ����ʣ�������˺�ֵ

	CREATURE_PROP_SKILL_DAMAGE_FIRST,                       // ��Ŀ������ֵ����ĳһ����Ŀ��������صİٷֱ�ֵʱ���ܺ͹�����ɵ��˺���߰ٷֱȣ���ԡ���Ϊ���͡�ֱ�����㡱��פ�ͱ�������
	CREATURE_PROP_SKILL_DAMAGE_MACRAZYDAMAGEGETMP,          // �κη������������󣬶��᷵���÷��������ķ���ֵ��X%��ʩ����

	CREATURE_PROP_GET_MP_BY_HEDGE_PER,                      // ÿ�����ܶ����Իָ�����ֵ���޵İٷ�֮���ٵ�����ֵ
	CREATURE_PROP_PLUS_NORMAL_ATTACK_PER,                   // ��ͨ�����������⹥�����ٷֱ�
	CREATURE_PROP_CHANGE_BUFF_TIME_PER,                     // �ܵ����м��ٶȣ�������ѣЧ���ĳ���ʱ�����Ӱٷֱ� 
	CREATURE_PROP_IGNORE_MD_PER,                            // ʹ����κη���X%�������ӶԷ��ķ�������
	CREATURE_PROP_DEST_DAMAGE2SRC_PER,                      // ��X%�ļ��ʽ��˺���100%����������ߣ�����Լ������ܵ������˺���
	CREATURE_PROP_ADDMP_BY_CRAZYDAMAGE_PER,                 // �κμ�����ɱ����󲹳��൱���ܷ���ֵX%�ķ���ֵ�����ָ������Գ�������������ķ�����80%

	//װ������������
	//װ��������
	//�������е�
	CREATURE_PROP_EQUIP_WEAPON_BASE_MIN_P_A,				//����������С������ֵ			(=����������С������ֵ + ǿ���ı�����������С������ֵ)
	CREATURE_PROP_EQUIP_WEAPON_BASE_MAX_P_A,				//�����������������ֵ			(=�����������������ֵ + ǿ���ı������������������ֵ )
	CREATURE_PROP_EQUIP_WEAPON_BASE_MIN_M_A,				//����������С��������ֵ			(=����������С��������ֵ + ǿ���ı�����������С��������ֵ)
	CREATURE_PROP_EQUIP_WEAPON_BASE_MAX_M_A,				//�����������������ֵ			(=�����������������ֵ + ǿ���ı������������������ֵ)

	//����װ��������
	CREATURE_PROP_EQUIP_BASE_MIN_P_A,                       //װ��������С������ֵ			(=װ��������С������ֵ + ǿ���ı�װ��������С������ֵ)
	CREATURE_PROP_EQUIP_BASE_MAX_P_A,                       //װ���������������ֵ			(=װ���������������ֵ + ǿ���ı�װ���������������ֵ )
	CREATURE_PROP_EQUIP_BASE_P_D,                           //װ�������������ֵ				(=װ�������������ֵ + ǿ���ı�װ�������������ֵ)
	CREATURE_PROP_EQUIP_BASE_MIN_M_A,                       //װ��������С��������ֵ			(=װ��������С��������ֵ + ǿ���ı�װ��������С��������ֵ)
	CREATURE_PROP_EQUIP_BASE_MAX_M_A,                       //װ���������������ֵ			(=װ���������������ֵ + ǿ���ı�װ���������������ֵ)
	CREATURE_PROP_EQUIP_BASE_M_D,                           //װ��������������ֵ				(=װ��������������ֵ + ǿ���ı�װ��������������ֵ)

	CREATURE_PROP_EQUIP_BASE_MAX_HP,                        //װ�������������ֵ				(=װ�������������ֵ + ǿ���ı�װ�������������ֵ)
	CREATURE_PROP_EQUIP_BASE_MAX_MP,                        //װ�������������ֵ				(=װ�������������ֵ + ǿ���ı�װ�������������ֵ)
	CREATURE_PROP_EQUIP_BASE_MAX_SP,                        //װ�������������ֵ				(=װ�������������ֵ + ǿ���ı�װ�������������ֵ)
	CREATURE_PROP_EQUIP_BASE_HEDGE,                         //װ����������ֵ					(=װ����������ֵ + ǿ���ı�װ����������ֵ)
	CREATURE_PROP_EQUIP_BASE_PRESENT,                       //װ����������ֵ					(=װ����������ֵ + ǿ���ı�װ����������ֵ)
	CREATURE_PROP_EQUIP_BASE_FATAL,                         //װ����������ֵ					(=װ����������ֵ + ǿ���ı�װ����������ֵ)
	CREATURE_PROP_EQUIP_BASE_KICK_FATAL,                    //װ����������ֵ					(=װ����������ֵ + ǿ���ı�װ����������ֵ)

	//װ�����ӵ�
	CREATURE_PROP_EQUIP_PLUS_MIN_P_A,                       //װ�����Ӹı���С������ֵ
	CREATURE_PROP_EQUIP_PLUS_MIN_P_A_RATIO,                 //װ�����Ӹı�������С�������ٷֱ�	����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_MIN_P_A_RATIO_2,               //װ�����Ӹı䵱ǰ��С�������ٷֱ�	����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_MAX_P_A,                       //װ�����Ӹı����������ֵ
	CREATURE_PROP_EQUIP_PLUS_MAX_P_A_RATIO,                 //װ�����Ӹı���������������ٷֱ�	����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_MAX_P_A_RATIO_2,               //װ�����Ӹı䵱ǰ����������ٷֱ�	����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_P_D,                           //װ�����Ӹı��������ֵ
	CREATURE_PROP_EQUIP_PLUS_P_D_RATIO,                     //װ�����Ӹı�������������ٷֱ�		����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_P_D_RATIO_2,                   //װ�����Ӹı䵱ǰ��������ٷֱ�		����ֱȣ�

	CREATURE_PROP_EQUIP_PLUS_MIN_M_A,                       //װ�����Ӹı���С��������ֵ
	CREATURE_PROP_EQUIP_PLUS_MIN_M_A_RATIO,                 //װ�����Ӹı�������С���������ٷֱ�	����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_MIN_M_A_RATIO_2,               //װ�����Ӹı䵱ǰ��С���������ٷֱ�	����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_MAX_M_A,                       //װ�����Ӹı����������ֵ
	CREATURE_PROP_EQUIP_PLUS_MAX_M_A_RATIO,                 //װ�����Ӹı���������������ٷֱ�	����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_MAX_M_A_RATIO_2,               //װ�����Ӹı䵱ǰ����������ٷֱ�	����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_M_D,                           //װ�����Ӹı䷨������ֵ
	CREATURE_PROP_EQUIP_PLUS_M_D_RATIO,                     //װ�����Ӹı����﷨�������ٷֱ�		����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_M_D_RATIO_2,                   //װ�����Ӹı䵱ǰ���������ٷֱ�		����ֱȣ�

	CREATURE_PROP_EQUIP_PLUS_MAX_HP,                        //װ�����Ӹı��������ֵ
	CREATURE_PROP_EQUIP_PLUS_MAX_HP_RATIO,                  //װ�����Ӹı�������������ٷֱ�		����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_MAX_HP_RATIO_2,                //װ�����Ӹı䵱ǰ��������ٷֱ�		����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_MAX_MP,                        //װ�����Ӹı��������ֵ
	CREATURE_PROP_EQUIP_PLUS_MAX_MP_RATIO,                  //װ�����Ӹı�������������ٷֱ�		����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_MAX_MP_RATIO_2,                //װ�����Ӹı䵱ǰ��������ٷֱ�		����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_MAX_SP,                        //װ�����Ӹı��������ֵ
	CREATURE_PROP_EQUIP_PLUS_MAX_SP_RATIO,                  //װ�����Ӹı�������������ٷֱ�		����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_MAX_SP_RATIO_2,                //װ�����Ӹı䵱ǰ��������ٷֱ�		����ֱȣ�

	CREATURE_PROP_EQUIP_PLUS_HP_RECOVER,                    //װ�����������ظ�ֵ
	CREATURE_PROP_EQUIP_PLUS_HP_RECOVER_RATIO,              //װ�����Ӹı������ظ��ٷֱ�			����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_MP_RECOVER,                    //װ�����������ظ�ֵ
	CREATURE_PROP_EQUIP_PLUS_MP_RECOVER_RATIO,              //װ�����Ӹı������ظ��ٷֱ�			����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_SP_RECOVER,                    //װ�����������ظ�ֵ
	CREATURE_PROP_EQUIP_PLUS_SP_RECOVER_RATIO,              //װ�����Ӹı������ظ��ٷֱ�			����ֱȣ�

	CREATURE_PROP_EQUIP_PLUS_HEDGE,                         //װ����������ֵ
	CREATURE_PROP_EQUIP_PLUS_HEDGE_RATIO,                   //װ�����Ӹı�������
	CREATURE_PROP_EQUIP_PLUS_PRESENT,                       //װ����������ֵ
	CREATURE_PROP_EQUIP_PLUS_PRESENT_RATIO,                 //װ�����Ӹı�������

	CREATURE_PROP_EQUIP_PLUS_FATAL,                         //װ�����ӻ���ֵ
	CREATURE_PROP_EQUIP_PLUS_FATAL_RATIO,                   //װ�����Ӹı������
	CREATURE_PROP_EQUIP_PLUS_KICK_FATAL,                    //װ����������ֵ

	CREATURE_PROP_EQUIP_PLUS_FATAL_DAMAGE_RATIO,            //װ�����ӻ����˺���߰ٷֱ�			����ֱ�)
	CREATURE_PROP_EQUIP_PLUS_KICK_FATAL_DAMAGE_RATIO,       //װ�����ӻ����˺�����ٷֱ�			����ֱ�)

	CREATURE_PROP_EQUIP_PLUS_ATTACK_SPEED,                  //װ�����ӹ����ٶ�ֵ
	CREATURE_PROP_EQUIP_PLUS_ATTACK_SPEED_RATIO,            //װ�����Ӹı乥���ٶȰٷֱ�			����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_MOVE_SPEED,                    //װ�������ƶ��ٶ�ֵ
	CREATURE_PROP_EQUIP_PLUS_MOVE_SPEED_RATIO,              //װ�����Ӹı��ƶ��ٶȰٷֱ�			����ֱȣ�

	CREATURE_PROP_EQUIP_PLUS_IGNORE_P_D,                    //װ�����Ӻ����������ֵ
	CREATURE_PROP_EQUIP_PLUS_IGNORE_P_D_RATIO,              //װ�����Ӻ�����������ٷֱ�			����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_IGNORE_M_D,                    //װ�����Ӻ��Է�������ֵ
	CREATURE_PROP_EQUIP_PLUS_IGNORE_M_D_RATIO,              //װ�����Ӻ��Է��������ٷֱ�			����ֱȣ�

	CREATURE_PROP_EQUIP_PLUS_REDUCE_P_DAMAGE,               //װ�����������˺�����ֵ
	CREATURE_PROP_EQUIP_PLUS_REDUCE_P_DAMAGE_RATIO,         //װ�����������˺�����ٷֱ�			����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_REDUCE_M_DAMAGE,               //װ�����ӷ����˺�����ֵ
	CREATURE_PROP_EQUIP_PLUS_REDUCE_M_DAMAGE_RATIO,         //װ�����ӷ����˺�����ٷֱ�			����ֱȣ�

	CREATURE_PROP_EQUIP_PLUS_INCREASE_P_DAMAGE,             //װ�����������˺�����ֵ
	CREATURE_PROP_EQUIP_PLUS_INCREASE_P_DAMAGE_RATIO,       //װ�����������˺����Ӱٷֱ�			����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_INCREASE_M_DAMAGE,             //װ�����ӷ����˺�����ֵ
	CREATURE_PROP_EQUIP_PLUS_INCREASE_M_DAMAGE_RATIO,       //װ�����ӷ����˺����Ӱٷֱ�			����ֱȣ�
	CREATURE_PROP_EQUIP_PLUS_REBOUND_DAMAGE_RATIO,          //װ�����ӷ����˺��ٷֱ�				����ֱȣ�

	CREATURE_PROP_EQUIP_PLUS_PENETRATE,                     //װ�����Ӵ��̹���ֵ
	CREATURE_PROP_EQUIP_PLUS_KICK_PENETRATE,                //װ�����Ӵ��̵ֿ�ֵ
	CREATURE_PROP_EQUIP_PLUS_KICK_PENETRATE_RATIO,          //װ�����Ӵ��̵ֿ��ٷֱ�				����ֱȣ�

	CREATURE_PROP_EQUIP_PLUS_FIGHT,							//װ�������������ս����

	CREATURE_PROP_CUR_HP_RECOVER,                           //����ʵ��(����)�����ظ��ٶ�
	CREATURE_PROP_CUR_MP_RECOVER,                           //����ʵ��(����)�����ظ��ٶ�
	CREATURE_PROP_CUR_SP_RECOVER,                           //����ʵ��(����)�����ظ��ٶ�

	CREATURE_PROP_CUR_HEDGE_RATIO,                          //����ʵ��(����)������
	CREATURE_PROP_CUR_PRESENT_RATIO,                        //����ʵ��(����)������

	CREATURE_PROP_CUR_FATAL_RATIO,                          //����ʵ��(����)������
	CREATURE_PROP_CUR_KICK_FATAL_RATIO,                     //����ʵ��(����)������

	CREATURE_PROP_CUR_FATAL_DAMAGE_RATIO,                   //����ʵ��(����)���ӻ����˺���ֵ����ֱ�)
	CREATURE_PROP_CUR_KICK_FATAL_DAMAGE_RATIO,              //����ʵ��(����)�ֿ������˺���ֵ����ֱ�)
	
	//CREATURE_PROP_CUR_ATTACK_SPEED,				        //����ʵ��(����)�����ٶ�ֵ

	CREATURE_PROP_CUR_IGNORE_P_D,                           //����ʵ��(����)�����������ֵ
	CREATURE_PROP_CUR_IGNORE_P_D_RATIO,                     //����ʵ��(����)�������������ֵ����ֱȣ�
	CREATURE_PROP_CUR_IGNORE_M_D,                           //����ʵ��(����)���Է�������ֵ
	CREATURE_PROP_CUR_IGNORE_M_D_RATIO,                     //����ʵ��(����)���Է���������ֵ����ֱȣ�

	CREATURE_PROP_CUR_REDUCE_P_DAMAGE,                      //����ʵ��(����)�����˺�����ֵ
	CREATURE_PROP_CUR_REDUCE_P_DAMAGE_RATIO,                //����ʵ��(����)�����˺������ֵ����ֱȣ�
	CREATURE_PROP_CUR_REDUCE_M_DAMAGE,                      //����ʵ��(����)�����˺�����ֵ
	CREATURE_PROP_CUR_REDUCE_M_DAMAGE_RATIO,                //����ʵ��(����)�����˺������ֵ����ֱȣ�

	CREATURE_PROP_CUR_INCREASE_P_DAMAGE,                    //����ʵ��(����)�����˺�����ֵ
	CREATURE_PROP_CUR_INCREASE_P_DAMAGE_RATIO,              //����ʵ��(����)�����˺����ӱ�ֵ����ֱȣ�
	CREATURE_PROP_CUR_INCREASE_M_DAMAGE,                    //����ʵ��(����)�����˺�����ֵ
	CREATURE_PROP_CUR_INCREASE_M_DAMAGE_RATIO,              //����ʵ��(����)�����˺����ӱ�ֵ����ֱȣ�
	CREATURE_PROP_CUR_REBOUND_DAMAGE_RATIO,                 // ����ʵ��(����)�����˺��ٷֱ�

	CREATURE_PROP_CUR_PENETRATE,                            //����ʵ��(����)���̣�����)�˺�ֵ
	CREATURE_PROP_CUR_KICK_PENETRATE,                       //����ʵ��(����)�ֿ����̣��ֿ�����)�˺�ֵ
	CREATURE_PROP_CUR_KICK_PENETRATE_RATIO,                 //����ʵ��(����)�ֿ����̣��ֿ�����)�˺���ֵ����ֱȣ�

	//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������Լӳ�

	//�����������õ�buff
	CREATURE_PROP_SKILL_WEAPON_MIN_P_A_RATIO,               //���ܺ�BUFF���ǳ�פ�������ܳ��⣩������������������������С��ֵ����ֱȣ�
	CREATURE_PROP_SKILL_WEAPON_MAX_P_A_RATIO,               //���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������������������ֵ����ֱȣ�
	CREATURE_PROP_SKILL_WEAPON_MIN_M_A_RATIO,               //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������������ķ���������С��ֵ����ֱȣ�
	CREATURE_PROP_SKILL_WEAPON_MAX_M_A_RATIO,               //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������������ķ�����������ֵ����ֱȣ�

	//����/���� �ķ�����/���� ��������ص�
	CREATURE_PROP_SKILL_BASE_MIN_P_A,                       //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����������������������Сֵ
	CREATURE_PROP_SKILL_BASE_MIN_P_A_RATIO,                 //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����������������������С��ֵ����ֱȣ�
	CREATURE_PROP_SKILL_BASE_MAX_P_A,                       //���ܺ�BUFF���ǳ�פ�������ܳ��⣩������������������������ֵ
	CREATURE_PROP_SKILL_BASE_MAX_P_A_RATIO,                 //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������������������������ֵ����ֱȣ�

	CREATURE_PROP_SKILL_BASE_MIN_M_A,                       //���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ���������Сֵ
	CREATURE_PROP_SKILL_BASE_MIN_M_A_RATIO,                 //���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ���������С��ֵ����ֱȣ�
	CREATURE_PROP_SKILL_BASE_MAX_M_A,                       //���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ����������ֵ
	CREATURE_PROP_SKILL_BASE_MAX_M_A_RATIO,	                //���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ�����������ֵ����ֱȣ�

	CREATURE_PROP_SKILL_BASE_P_D,                           //���ܺ�BUFF���ǳ�פ�������ܳ��⣩����������������������ֵ
	CREATURE_PROP_SKILL_BASE_P_D_RATIO,                     //���ܺ�BUFF���ǳ�פ�������ܳ��⣩������������������������ֵ����ֱȣ�

	CREATURE_PROP_SKILL_BASE_M_D,                           //���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ�������ֵ
	CREATURE_PROP_SKILL_BASE_M_D_RATIO,                     //���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ���������ֵ����ֱȣ�

	//����/���� �ķ�����/���� ����ǰ��ص�
	CREATURE_PROP_SKILL_SUM_MIN_P_A_RATIO,                  //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ����������С��ֵ����ֱȣ�
	CREATURE_PROP_SKILL_SUM_MAX_P_A_RATIO,                  //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ������������ֵ����ֱȣ�
	CREATURE_PROP_SKILL_SUM_MIN_M_A_RATIO,                  //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ�ķ���������С��ֵ����ֱȣ�
	CREATURE_PROP_SKILL_SUM_MAX_M_A_RATIO,                  //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ�ķ�����������ֵ����ֱȣ�
	CREATURE_PROP_SKILL_SUM_P_D_RATIO,                      //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ�����������ֵ����ֱȣ�
	CREATURE_PROP_SKILL_SUM_M_D_RATIO,                      //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ�ķ���������ֵ����ֱȣ�

	//��HP/MP��ص�
	CREATURE_PROP_SKILL_BASE_MAX_HP,                        //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������������������������ֵ
	CREATURE_PROP_SKILL_BASE_MAX_HP_RATIO,                  //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������������������������ֵ����ֱȣ�
	CREATURE_PROP_SKILL_BASE_MAX_MP,                        //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������������������������ֵ
	CREATURE_PROP_SKILL_BASE_MAX_MP_RATIO,                  //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������������������������ֵ����ֱȣ�
	CREATURE_PROP_SKILL_BASE_MAX_SP,                        //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������������������������ֵ
	CREATURE_PROP_SKILL_BASE_MAX_SP_RATIO,                  //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������������������������ֵ����ֱȣ�
	CREATURE_PROP_SKILL_SUM_MAX_HP_RATIO,                   //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������������ﵱǰ�����������ֵ����ֱȣ�
	CREATURE_PROP_SKILL_SUM_MAX_MP_RATIO,                   //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������������ﵱǰ�����������ֵ����ֱȣ�
	CREATURE_PROP_SKILL_SUM_MAX_SP_RATIO,                   //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������������ﵱǰ�����������ֵ����ֱȣ�

	CREATURE_PROP_SKILL_HP_RECOVER,                         //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������������ظ��ٶ�ֵ
	CREATURE_PROP_SKILL_HP_RECOVER_RATIO,                   //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������������ظ��ٶȱ�ֵ����ֱȣ�
	CREATURE_PROP_SKILL_MP_RECOVER,                         //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������������ظ��ٶ�ֵ
	CREATURE_PROP_SKILL_MP_RECOVER_RATIO,                   //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������������ظ��ٶȱ�ֵ����ֱȣ�
	CREATURE_PROP_SKILL_SP_RECOVER,                         //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������������ظ��ٶ�ֵ
	CREATURE_PROP_SKILL_SP_RECOVER_RATIO,                   //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������������ظ��ٶȱ�ֵ����ֱȣ�

	CREATURE_PROP_SKILL_HEDGE,                              //���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ֵ
	CREATURE_PROP_SKILL_HEDGE_RATIO,                        //���ܺ�BUFF���ǳ�פ�������ܳ��⣩����������������
	CREATURE_PROP_SKILL_PRESENT,                            //���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ֵ
	CREATURE_PROP_SKILL_PRESENT_RATIO,                      //���ܺ�BUFF���ǳ�פ�������ܳ��⣩����������������

	CREATURE_PROP_SKILL_FATAL,                              //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӻ���ֵ
	CREATURE_PROP_SKILL_FATAL_RATIO,                        //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӻ�����
	CREATURE_PROP_SKILL_KICK_FATAL,                         //���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ֵ

	CREATURE_PROP_SKILL_FATAL_DAMAGE_RATIO,                 //���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӻ����˺���ֵ����ֱ�)
	CREATURE_PROP_SKILL_KICK_FATAL_DAMAGE_RATIO,            //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĵֿ������˺���ֵ����ֱ�)

	CREATURE_PROP_SKILL_ATTACK_SPEED,                       //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����Ĺ����ٶ�ֵ
	CREATURE_PROP_SKILL_ATTACK_SPEED_RATIO,                 //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����Ĺ����ٶȱ�ֵ����ֱȣ�
	CREATURE_PROP_SKILL_MOVE_SPEED,                         //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������ƶ��ٶ�
	CREATURE_PROP_SKILL_MOVE_SPEED_RATIO,                   //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������ƶ��ٶȱ�ֵ����ֱȣ�

	CREATURE_PROP_SKILL_IGNORE_P_D,                         //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĺ����������ֵ
	CREATURE_PROP_SKILL_IGNORE_P_D_RATIO,                   //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĺ������������ֵ����ֱȣ�
	CREATURE_PROP_SKILL_IGNORE_M_D,                         //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĺ��Է�������ֵ
	CREATURE_PROP_SKILL_IGNORE_M_D_RATIO,                   //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĺ��Է���������ֵ����ֱȣ�

	CREATURE_PROP_SKILL_REDUCE_P_DAMAGE,                    //���ܺ�BUFF��������פ�������ܣ������������˺�����ֵ
	CREATURE_PROP_SKILL_REDUCE_P_DAMAGE_RATIO,              //���ܺ�BUFF��������פ�������ܣ������������˺������ֵ����ֱȣ�
	CREATURE_PROP_SKILL_REDUCE_M_DAMAGE,                    //���ܺ�BUFF��������פ�������ܣ������ķ����˺�����ֵ
	CREATURE_PROP_SKILL_REDUCE_M_DAMAGE_RATIO,              //���ܺ�BUFF��������פ�������ܣ������ķ����˺������ֵ����ֱȣ�

	CREATURE_PROP_SKILL_INCREASE_P_DAMAGE,                  //���ܺ�BUFF��������פ�������ܣ������������˺�����ֵ
	CREATURE_PROP_SKILL_INCREASE_P_DAMAGE_RATIO,            //���ܺ�BUFF��������פ�������ܣ������������˺����ӱ�ֵ����ֱȣ�
	CREATURE_PROP_SKILL_INCREASE_M_DAMAGE,                  //���ܺ�BUFF��������פ�������ܣ������ķ����˺�����ֵ
	CREATURE_PROP_SKILL_INCREASE_M_DAMAGE_RATIO,            //���ܺ�BUFF��������פ�������ܣ������ķ����˺����ӱ�ֵ����ֱȣ�
	CREATURE_PROP_SKILL_REBOUND_DAMAGE_RATIO,               // ���ܺ�BUFF��������פ�������ܣ������ķ����˺��ٷֱ�

	CREATURE_PROP_SKILL_PENETRATE,                          //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����Ĵ��̣�����)�˺�ֵ
	CREATURE_PROP_SKILL_KICK_PENETRATE,                     //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĵֿ����̣��ֿ�����)�˺�ֵ
	CREATURE_PROP_SKILL_KICK_PENETRATE_RATIO,               //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĵֿ����̣��ֿ�����)�˺���ֵ����ֱȣ�

	CREATURE_PROP_SKILLREBOUND,                             //���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������˺�������ֵ����ֱȣ�

	//����/���� �ķ���/���� ����ı�ֵ
	CREATURE_PROP_PLUS_MIN_P_A,                             // ����ı���С������ֵ
	CREATURE_PROP_PLUS_MAX_P_A,                             // ����ı����������ֵ
	CREATURE_PROP_PLUS_MIN_M_A,                             // ����ı���С��������ֵ
	CREATURE_PROP_PLUS_MAX_M_A,                             // ����ı����������ֵ
	CREATURE_PROP_PLUS_P_D,                                 // ����ı��������ֵ
	CREATURE_PROP_PLUS_M_D,                                 // ����ı䷨������ֵ

	//��פ���ܼ��ܴ��������Լӳ�
	CREATURE_PROP_PERMANENT_SKILL_BASE_MIN_P_A,				//��פ���ܴ����������������������Сֵ
	CREATURE_PROP_PERMANENT_SKILL_BASE_MIN_P_A_RATIO,       //��פ���ܴ����������������������С��ֵ����ֱȣ�
	CREATURE_PROP_PERMANENT_SKILL_BASE_MAX_P_A,				//��פ���ܴ�����������������������ֵ
	CREATURE_PROP_PERMANENT_SKILL_BASE_MAX_P_A_RATIO,		//��פ���ܴ������������������������ֵ����ֱȣ�

	CREATURE_PROP_PERMANENT_SKILL_BASE_MIN_M_A,				//��פ���ܴ�������������ķ���������Сֵ
	CREATURE_PROP_PERMANENT_SKILL_BASE_MIN_M_A_RATIO,		//��פ���ܴ�������������ķ���������С��ֵ����ֱȣ�
	CREATURE_PROP_PERMANENT_SKILL_BASE_MAX_M_A,				//��פ���ܴ�������������ķ����������ֵ
	CREATURE_PROP_PERMANENT_SKILL_BASE_MAX_M_A_RATIO,		//��פ���ܴ�������������ķ�����������ֵ����ֱȣ�

	CREATURE_PROP_PERMANENT_SKILL_BASE_P_D,					//��פ���ܴ���������������������ֵ
	CREATURE_PROP_PERMANENT_SKILL_BASE_P_D_RATIO,			//��פ���ܴ�����������������������ֵ����ֱȣ�

	CREATURE_PROP_PERMANENT_SKILL_BASE_M_D,					//��פ���ܴ�������������ķ�������ֵ
	CREATURE_PROP_PERMANENT_SKILL_BASE_M_D_RATIO,			//��פ���ܴ�������������ķ���������ֵ����ֱȣ�

	CREATURE_PROP_PERMANENT_SKILL_BASE_MAX_HP,				//��פ���ܴ����������������ֵ
	CREATURE_PROP_PERMANENT_SKILL_BASE_MAX_HP_RATIO,		//��פ���ܴ������������������ֵ����ֱȣ�
	CREATURE_PROP_PERMANENT_SKILL_BASE_MAX_MP,				//��פ���ܴ����������������ֵ
	CREATURE_PROP_PERMANENT_SKILL_BASE_MAX_MP_RATIO,		//��פ���ܴ������������������ֵ����ֱȣ�
	CREATURE_PROP_PERMANENT_SKILL_BASE_MAX_SP,				//��פ���ܴ����������������ֵ
	CREATURE_PROP_PERMANENT_SKILL_BASE_MAX_SP_RATIO,		//��פ���ܴ������������������ֵ����ֱȣ�

	CREATURE_PROP_PERMANENT_SKILL_BASE_HP_RECOVER,			//��פ���ܴ��������������ظ��ٶ�ֵ
	CREATURE_PROP_PERMANENT_SKILL_BASE_HP_RECOVER_RATIO,	//��פ���ܴ��������������ظ��ٶȱ�ֵ����ֱȣ�
	CREATURE_PROP_PERMANENT_SKILL_BASE_MP_RECOVER,			//��פ���ܴ��������������ظ��ٶ�ֵ
	CREATURE_PROP_PERMANENT_SKILL_BASE_MP_RECOVER_RATIO,	//��פ���ܴ��������������ظ��ٶȱ�ֵ����ֱȣ�
	CREATURE_PROP_PERMANENT_SKILL_BASE_SP_RECOVER,			//��פ���ܴ��������������ظ��ٶ�ֵ
	CREATURE_PROP_PERMANENT_SKILL_BASE_SP_RECOVER_RATIO,	//��פ���ܴ��������������ظ��ٶȱ�ֵ����ֱȣ�

	CREATURE_PROP_PERMANENT_SKILL_BASE_HEDGE,				//��פ���ܴ�������������ֵ
	CREATURE_PROP_PERMANENT_SKILL_BASE_HEDGE_RATIO,			//��פ���ܴ���������������
	CREATURE_PROP_PERMANENT_SKILL_BASE_PRESENT,				//��פ���ܴ�������������ֵ
	CREATURE_PROP_PERMANENT_SKILL_BASE_PRESENT_RATIO,		//��פ���ܴ���������������

	CREATURE_PROP_PERMANENT_SKILL_BASE_FATAL,				//��פ���ܴ��������ӻ���ֵ
	CREATURE_PROP_PERMANENT_SKILL_BASE_FATAL_RATIO,			//��פ���ܴ��������ӻ�����
	CREATURE_PROP_PERMANENT_SKILL_BASE_KICK_FATAL,			//��פ���ܴ�������������ֵ

	CREATURE_PROP_PERMANENT_SKILL_ATTACK_SPEED,				//��פ���ܴ����Ĺ����ٶ�ֵ
	CREATURE_PROP_PERMANENT_SKILL_ATTACK_SPEED_RATIO,		//��פ���ܴ����Ĺ����ٶȱ�ֵ����ֱȣ�
	CREATURE_PROP_PERMANENT_SKILL_MOVE_SPEED,				//��פ���ܴ������ƶ��ٶ�
	CREATURE_PROP_PERMANENT_SKILL_MOVE_SPEED_RATIO,			//��פ���ܴ������ƶ��ٶȱ�ֵ����ֱȣ�

	CREATURE_PROP_SUCK,										//��Ѫ��ֱ� add by zjp
	CREATURE_PROP_SKILL_KICK_FATAL_RATIO,					//���ܸı������������ 
	CREATURE_PROP_SKILL_FAN_TANG_RATIO,						//���ܷ����˺���ֱ�

	CREATURE_PROP_VIPPOPEDOM,                               // VIPȨ��

	CREATURE_MONSTER_ID,                                    // �������ID ********* ���������ר�ã�

	CREATURE_PROP_ZQ_ACCOUNT_ID,							//����ͨ��֤���ڹ�˾���ݿ��е��ʺ�ID
	//by cjl
	CREATURE_PROP_EQUIP_ADATP_NUM,							//װ���ʺϵĸ���
	CREATURE_PROP_EQUIP_ADATP_FIGHT,						//װ���ʺϵ�ս�����ӳ�
	CREATURE_PROP_EQUIP_BRAND_NUM,							//װ��Ʒ�ʼӳɵĸ���
	CREATURE_PROP_EQUIP_BRAND_FIGHT,						//װ��Ʒ�ʼӳɵ�ս�����ӳ�
	CREATURE_PROP_EQUIP_SLOTQTY_NUM,						//װ�������ĸ���
	CREATURE_PROP_EQUIP_SLOTQTY_FIGHT,						//װ��������ս�����ӳ�
	CREATURE_PROP_EQUIP_STRENGTH_NUM,						//װ��ǿ���ĸ���
	CREATURE_PROP_EQUIP_STRENGTH_FIGHT,						//װ��ǿ����ս�����ӳ�
	//end cjl

	/* 1������д�С�ȣ���СֵID�����������ֵIDǰһλ��
	2��ֻ�е�ǰֵ������Ҫ��С�ȡ�
	3����ǰֵ��һ�㶼�ǽ�ֹ�޸ĵģ���Ϊ���ǻ���ֵ�͸���ֵ��������ģ�Ҫ�ľ͸ĸ���ֵ�ͺ��ˡ�
	4������ֵ����������Ϊ�����ģ���ΪBUFFΪ��ֵ�м��м��ġ�//*/

	CREATURE_PROP_MAXID,                                    // �������ID	
};

//by cjl
///////////////////////�������Ա��Ӧ��ƫ����///////////////////////
enum
{
	CREATURE_PROP_OFFSET_PDBID = CREATURE_PROP_PDBID+1,										// ��ɫ���ݿ�ID ����ʼ
	CREATURE_PROP_OFFSET_BROADCAST = CREATURE_PERSON_BROADCAST-1,							// ��������Ϊ�㲥���� ������
	
	CREATURE_PROP_OFFSET_MAX_HP = CREATURE_PROP_BASE_MAX_HP,								// ��������ֵ���� �� ��ʼ
	CREATURE_PROP_OFFSET_CUR_ATTACK_SPEED = CREATURE_PROP_CUR_ATTACK_SPEED,					// ����ʵ��(����)�����ٶ�ֵ�� ����
	
	CREATURE_PROP_OFFSET_PERSON_PRIVATE = CREATURE_PERSON_PRIVATE+1,						// ��������Ϊ˽�����ԣ���ʼ
	CREATURE_PROP_OFFSET_ADDMP_BY_CRAZYDAMAGE_PE = CREATURE_PROP_ADDMP_BY_CRAZYDAMAGE_PER,  // �κμ�����ɱ����󲹳��൱���ܷ���ֵX%�ķ���ֵ�����ָ������Գ�������������ķ�����80%,����
	
	CREATURE_PROP_OFFSET_EQUIP_PLUS_FIGHT = CREATURE_PROP_EQUIP_PLUS_FIGHT,					//װ�������������ս��������ʼ
	CREATURE_PROP_OFFSET_CUR_KICK_PENETRATE_RATIO = CREATURE_PROP_CUR_KICK_PENETRATE_RATIO, //����ʵ��(����)�ֿ����̣��ֿ�����)�˺���ֵ����ֱȣ��� ����

	CREATURE_PROP_OFFSET_PLUS_MIN_P_A = CREATURE_PROP_PLUS_MIN_P_A,                         // ����ı���С������ֵ����ʼ
	CREATURE_PROP_OFFSET_PLUS_M_D = CREATURE_PROP_PLUS_M_D,									// ����ı䷨������ֵ�� ����
};	

/////////////////////////////������������///////////////////////////
enum//������������ʹ��
{
	UPDATE_MY_PRESENT_PROP = 0,								// ��������������,���볡��ʱ����
	UPDATE_MY_PRESENT_RESULT,								// ����������
	UPDATE_MY_FIGHT_DISPLAY,								// ս������ʾ����
	UPDATE_MY_CHANGE_BODY_DATA,								// ������ò����
	UPDATE_MY_MAXID,										// �������ID
};
#define PERSON_PRESENT_LEVEL_KEY      "����ȼ�"		   //���ð�
#define PERSON_PRESENT_TOTAL_TIME_KEY "����ѻ���ʱ��"	   //���ð�
#define PERSON_PRESENT_TIME_KEY       "�����ǰʱ��"       //��ʱ��

enum //do something ʹ��
{
	PERSON_GET_MY_PRESENT = 0,								//��ȡ���
	PERSON_GET_MY_PRESENT_RESULT,                           //��ȡ������
	PERSON_GET_CHANGEBODY_COMMON_DATA,						//���ݲ��޸���ͨ��������
	PERSON_SET_CHANGEBODY_COMMON_DATA,						//������ͨ��������
	PERSON_GET_CHANGEBODY_DATA,								//���ݲ��޸ĸ߼���������
	PERSON_SET_CHANGEBODY_DATA,								//���ø߼���������
	PERSON_SET_CHANGEBODY_DATA_FOR_COPY,					//���ñ�������
	PERSON_DO_SOMETHING_MAX,
};
//end cjl


//////////////////////////////����װ��λ��//////////////////////////
enum
{
	PERSON_EQUIPPLACE_RESERVE = 0,		// ����/��Чֵ
	PERSON_EQUIPPLACE_WEAPON,			// ����  
	PERSON_EQUIPPLACE_ARMET,			// ͷ��
	PERSON_EQUIPPLACE_ARMOR,			// ����
	PERSON_EQUIPPLACE_CUFF,				// ���� 
	PERSON_EQUIPPLACE_SHOES,			// Ь��
	PERSON_EQUIPPLACE_NECKLACE,			// ����
	PERSON_EQUIPPLACE_RING,				// ��ָ
	PERSON_EQUIPPLACE_DECORATION_L,		// ���׹
	PERSON_EQUIPPLACE_DECORATION_R,		// �ҹ�׹
	PERSON_EQUIPPLACE_SUIT_ARMET,		// ʱװͷ��
	PERSON_EQUIPPLACE_SUIT_ARMOR,		// ʱװ����
	PERSON_EQUIPPLACE_MAX,				// ���	
};

//////////////////////////////װ����ԭ��//////////////////////////////////////
enum
{
	DEDUCT_ENDURE_REASON_MIN = 0,
	DEDUCT_ENDURE_REASON_ATTACK,		//����
	DEDUCT_ENDURE_REASON_INJURED,		//����
	DEDUCT_ENDURE_REASON_PVE_DIE,		//pve����
	DEDUCT_ENDURE_REASON_MAX,			
};

#if 0
////////////////////////////////��������/////////////////////////////
//enum
//{
//	MONSTER_TYPE_GENERAL = 1,			// ��ͨ��		��ֻ�����ˣ�
//	MONSTER_TYPE_POLISH,				// ��Ӣ��		��ֻ�����ˣ�
//	MONSTER_TYPE_RARE,					// ϡ�й�		��ֻ�����ˣ�
//	MONSTER_TYPE_BOSS,					// BOSS��		��ֻ�����ˣ�
//
//	MONSTER_TYPE_VALOR,					// ���͹�		���˺͹ֶ��ṥ����
//
//	MONSTER_TYPE_LIFE,					// ����			��Сè��С���ȣ�
//
//	MONSTER_TYPE_NPCSAFE,				// ���ɹ���NPC	���˺͹ֶ����ṥ����
//	MONSTER_TYPE_NPCATTACK,				// �ɹ���NPC	��ֻ�����֣�
//
//	MONSTER_TYPE_GUARD,					// ����			�����������ͷ���Ӫ���˺͹֣�
//
//	MONSTER_TYPE_PAWNLUO,				// צ�����ٻ��� ����ͬʱӵ�ж����
//	MONSTER_TYPE_PAWNPET,				// �������ٻ���	��ֻ����ӵ��һ�����й̶�Ŀ�껷��
//
//	MONSTER_TYPE_GUYONG,				// ��Ӷ��		�������͹�û����ֻ����AI�ٳ���
//
//	MONSTER_TYPE_STALL,				    // ̯λNPC		�����ڰ�̯��
//};
#endif

//////////////////////////////��������/////////////////////////////
enum
{
/*  ���͹�
	1��	���Թ����ˡ�������
	2��	���Ա��ˡ�������﹥����
	3��	����ƶ�����Ŀ���ϸ�����Ӫ����жϣ��������������ʾ������ͼ�꣬����Ѻ���ʾ����ͷ��ͼ��
*/
	MONSTER_TYPE_VALOR = 1,

/*  BOSS��
	1��	���Թ����ˡ�������
	2��	���Ա��ˡ�������﹥����
	3��	����ƶ�����Ŀ���ϸ�����Ӫ����жϣ��������������ʾ������ͼ�꣬����Ѻ���ʾ����ͷ��ͼ��

*/
	MONSTER_TYPE_BOSS,

/*  �ɹ���NPC
	1��	���Թ����ˡ�������
	2��	���Ա��ˡ�������﹥����
	3������ƶ�����Ŀ���ϸ�����Ӫ����жϣ���������ʾ������ͼ�꣬����������Ѻ���ʾ���Ի���ͼ��
*/
	MONSTER_TYPE_NPCATTACK,

/*  ����
	1�����Թ����ˡ�������
	2�����Ա��ˡ�������﹥����
	3���ض�����������ҡ�
	4���˺ͳ��ﲻ����������������ֻ�������������󷴻���
	5������ƶ�����Ŀ������ʾ����ͷ��ͼ�꣬�ܵ�������������ʾ������ͼ��
*/
	MONSTER_TYPE_GUARD,

/*  ���飨Сè��С���ȣ�
	1��	�����Թ����ˡ�������
	2��	�����Ա��ˡ�������﹥����
	3��	����ƶ�����Ŀ�����޷�ѡ�С�
*/
	MONSTER_TYPE_LIFE,

/*  ���ɹ���NPC
	1�������Թ����ˡ�������
	2�������Ա��ˡ�������﹥����
	3������ƶ�����Ŀ������ʾ���Ի���ͼ��
*/
	MONSTER_TYPE_NPCSAFE,

/* �ɼ�NPC
	1�������Թ����ˡ�������
	2�������Ա��ˡ�������﹥����
	3������ƶ�����Ŀ������ʾ���ɼ���ͼ��
*/
	MONSTER_TYPE_NPCCOLLECTION,

// ̯λNPC		�����ڰ�̯��
	MONSTER_TYPE_STALL,

/* ��Ӣ�֣�ͬboss
	1�������Թ����ˡ�������
	2�������Ա��ˡ�������﹥����
	3������ƶ�����Ŀ������ʾ���ɼ���ͼ��
*/
	MONSTER_TYPE_ELITE,	
};

////////////////////////////////////////////////////////////////////
// �벻Ҫֱ������������IDȥ�����������ԣ���CREATURE_PROP_CUR_HP����
// ��ID������ʵ���ڲ����Զ�ת��������ID����ʵ���ⲿ�����漰��������
// ���ڴ˴�����Ҫ�ǿͻ���ҲҪʹ�ã��������ⲿ�˽����֧����Щ���ԡ�
///////////////////////////////////////////////////////////////////
/*****************************************************************/
/******** �벻Ҫֱ������������IDȥ������������ *******************/
enum
{
	MONSTER_PROP_MONSTERID = 1,                    // ����ID
	MONSTER_PROP_CUR_HP,                           // ��ǰ����ֵ
	MONSTER_PROP_MAX_HP,                           // ����ֵ����
	MONSTER_PROP_CUR_MP,                           // ��ǰ����ֵ
	MONSTER_PROP_MAX_MP,                           // ����ֵ����
	MONSTER_PROP_CUR_MOVE_SPEED,                   // ��ǰ�ƶ��ٶ�
	MONSTER_PROP_CUR_WALK_SPEED,                   // ��ǰ��·�ٶ�
	MONSTER_PROP_CUR_MOVE_STYLE,                   // ��ǰ�ƶ���ʽ
	MONSTER_PROP_IGNO_BLCOK,                       // �Ƿ�����赲

	MONSTER_PROP_BROADCAST,                        // ����Ϊ�㲥����
	/////////////////////////////////////////////////

	MONSTER_PROP_CUR_MIN_P_A,                      // ��ǰ��С������
	MONSTER_PROP_CUR_MAX_P_A,                      // ��ǰ���������
	MONSTER_PROP_CUR_MIN_M_A,                      // ��ǰ��С��������
	MONSTER_PROP_CUR_MAX_M_A,                      // ��ǰ���������

	MONSTER_PROP_CUR_P_D,                          // ��ǰ������� 
	MONSTER_PROP_CUR_M_D,                          // ��ǰ��������

	//����ʵ��(����)����ֵ
	MONSTER_PROP_LEVEL,                            // ����ȼ�
	MONSTER_PROP_CUR_FIGHT,                        // ����ʵ��(����ս����)
	MONSTER_PROP_CUR_HEDGE,                        // ����ʵ��(����)����ֵ,������ʾ
	MONSTER_PROP_CUR_HEDGE_RATIO,                  // ����ʵ��(����)������
	MONSTER_PROP_CUR_PRESENT,                      // ����ʵ��(����)����ֵ��������ʾ
	MONSTER_PROP_CUR_PRESENT_RATIO,                // ����ʵ��(����)������

	MONSTER_PROP_CUR_FATAL,                        // ����ʵ��(����)����ֵ��������ʾ
	MONSTER_PROP_CUR_FATAL_RATIO,                  // ����ʵ��(����)������
	MONSTER_PROP_CUR_KICK_FATAL,                   // ����ʵ��(����)����ֵ��������ʾ
	MONSTER_PROP_CUR_KICK_FATAL_RATIO,             // ����ʵ��(����)������

	MONSTER_PROP_CUR_FATAL_DAMAGE_RATIO,           // ����ʵ��(����)���ӻ����˺���ֵ����ֱ�)
	MONSTER_PROP_CUR_KICK_FATAL_DAMAGE_RATIO,      // ����ʵ��(����)�ֿ������˺���ֵ����ֱ�)

	MONSTER_PROP_CUR_ATTACK_SPEED,                 // ����ʵ��(����)�����ٶ�ֵ

	MONSTER_PROP_CUR_IGNORE_P_D,                   // ����ʵ��(����)�����������ֵ
	MONSTER_PROP_CUR_IGNORE_P_D_RATIO,             // ����ʵ��(����)�������������ֵ����ֱȣ�
	MONSTER_PROP_CUR_IGNORE_M_D,                   // ����ʵ��(����)���Է�������ֵ
	MONSTER_PROP_CUR_IGNORE_M_D_RATIO,             // ����ʵ��(����)���Է���������ֵ����ֱȣ�

	MONSTER_PROP_CUR_REDUCE_P_DAMAGE,              // ����ʵ��(����)�����˺�����ֵ
	MONSTER_PROP_CUR_REDUCE_P_DAMAGE_RATIO,        // ����ʵ��(����)�����˺������ֵ����ֱȣ�
	MONSTER_PROP_CUR_REDUCE_M_DAMAGE,              // ����ʵ��(����)�����˺�����ֵ
	MONSTER_PROP_CUR_REDUCE_M_DAMAGE_RATIO,        // ����ʵ��(����)�����˺������ֵ����ֱȣ�

	MONSTER_PROP_CUR_INCREASE_P_DAMAGE,            // ����ʵ��(����)�����˺�����ֵ
	MONSTER_PROP_CUR_INCREASE_P_DAMAGE_RATIO,      // ����ʵ��(����)�����˺����ӱ�ֵ����ֱȣ�
	MONSTER_PROP_CUR_INCREASE_M_DAMAGE,            // ����ʵ��(����)�����˺�����ֵ
	MONSTER_PROP_CUR_INCREASE_M_DAMAGE_RATIO,      // ����ʵ��(����)�����˺����ӱ�ֵ����ֱȣ�

	// �����˺��ٷֱ�
	MONSTER_PROP_CUR_REBOUND_DAMAGE_RATIO,         // ����ʵ��(����)�����˺��ٷֱ�

	MONSTER_PROP_CUR_PENETRATE,                    // ����ʵ��(����)���̣�����)�˺�ֵ
	MONSTER_PROP_CUR_KICK_PENETRATE,               // ����ʵ��(����)�ֿ����̣��ֿ�����)�˺�ֵ
	MONSTER_PROP_CUR_KICK_PENETRATE_RATIO,         // ����ʵ��(����)�ֿ����̣��ֿ�����)�˺���ֵ����ֱȣ�
	MONSTER_PROP_CUR_HP_RECOVER,                   // ����ʵ��(����)�����ظ��ٶ�

	//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������Լӳ�
	//����/���� �ķ�����/���� ��������ص�
	MONSTER_PROP_SKILL_BASE_MIN_P_A,               // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����������������������Сֵ
	MONSTER_PROP_SKILL_BASE_MIN_P_A_RATIO,         // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����������������������С��ֵ����ֱȣ�
	MONSTER_PROP_SKILL_BASE_MAX_P_A,               // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩������������������������ֵ
	MONSTER_PROP_SKILL_BASE_MAX_P_A_RATIO,         // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������������������������ֵ����ֱȣ�

	MONSTER_PROP_SKILL_BASE_MIN_M_A,               // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ���������Сֵ
	MONSTER_PROP_SKILL_BASE_MIN_M_A_RATIO,         // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ���������С��ֵ����ֱȣ�
	MONSTER_PROP_SKILL_BASE_MAX_M_A,               // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ����������ֵ
	MONSTER_PROP_SKILL_BASE_MAX_M_A_RATIO,         // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ�����������ֵ����ֱȣ�

	MONSTER_PROP_SKILL_BASE_P_D,                   // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩����������������������ֵ
	MONSTER_PROP_SKILL_BASE_P_D_RATIO,             // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩������������������������ֵ����ֱȣ�

	MONSTER_PROP_SKILL_BASE_M_D,                   // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ�������ֵ
	MONSTER_PROP_SKILL_BASE_M_D_RATIO,             // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ���������ֵ����ֱȣ�

	//����/���� �ķ�����/���� ����ǰ��ص�
	MONSTER_PROP_SKILL_SUM_MIN_P_A_RATIO,          // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ����������С��ֵ����ֱȣ�
	MONSTER_PROP_SKILL_SUM_MAX_P_A_RATIO,          // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ������������ֵ����ֱȣ�
	MONSTER_PROP_SKILL_SUM_MIN_M_A_RATIO,          // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ�ķ���������С��ֵ����ֱȣ�
	MONSTER_PROP_SKILL_SUM_MAX_M_A_RATIO,          // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ�ķ�����������ֵ����ֱȣ�
	MONSTER_PROP_SKILL_SUM_P_D_RATIO,              // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ�����������ֵ����ֱȣ�
	MONSTER_PROP_SKILL_SUM_M_D_RATIO,              // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ�ķ���������ֵ����ֱȣ�

	//��HP/MP��ص�
	MONSTER_PROP_SKILL_BASE_MAX_HP,                // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӹ��������������ֵ
	MONSTER_PROP_SKILL_BASE_MAX_HP_RATIO,          // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӹ����������������ֵ����ֱȣ�
	MONSTER_PROP_SKILL_BASE_MAX_MP,                // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӹ��������������ֵ
	MONSTER_PROP_SKILL_BASE_MAX_MP_RATIO,          // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӹ����������������ֵ����ֱȣ�
	MONSTER_PROP_SKILL_SUM_MAX_HP_RATIO,           // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӹ��ﵱǰ�����������ֵ����ֱȣ�
	MONSTER_PROP_SKILL_SUM_MAX_MP_RATIO,           // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӹ��ﵱǰ�����������ֵ����ֱȣ�

	MONSTER_PROP_SKILL_HEDGE,                      // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ֵ
	MONSTER_PROP_SKILL_HEDGE_RATIO,                // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩����������������
	MONSTER_PROP_SKILL_PRESENT,                    // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ֵ
	MONSTER_PROP_SKILL_PRESENT_RATIO,              // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩����������������

	MONSTER_PROP_SKILL_FATAL,                      // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӻ���ֵ
	MONSTER_PROP_SKILL_FATAL_RATIO,                // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӻ�����
	MONSTER_PROP_SKILL_KICK_FATAL,                 // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ֵ

	MONSTER_PROP_SKILL_FATAL_DAMAGE_RATIO,         // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӻ����˺���ֵ����ֱ�)
	MONSTER_PROP_SKILL_KICK_FATAL_DAMAGE_RATIO,    // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĵֿ������˺���ֵ����ֱ�)

	MONSTER_PROP_SKILL_ATTACK_SPEED,               // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����Ĺ����ٶ�ֵ
	MONSTER_PROP_SKILL_ATTACK_SPEED_RATIO,         // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����Ĺ����ٶȱ�ֵ����ֱȣ�
	MONSTER_PROP_SKILL_MOVE_SPEED,                 // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������ƶ��ٶ�
	MONSTER_PROP_SKILL_MOVE_SPEED_RATIO,           // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������ƶ��ٶȱ�ֵ����ֱȣ�

	MONSTER_PROP_SKILL_IGNORE_P_D,                 // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĺ����������ֵ
	MONSTER_PROP_SKILL_IGNORE_P_D_RATIO,           // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĺ������������ֵ����ֱȣ�
	MONSTER_PROP_SKILL_IGNORE_M_D,                 // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĺ��Է�������ֵ
	MONSTER_PROP_SKILL_IGNORE_M_D_RATIO,           // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĺ��Է���������ֵ����ֱȣ�

	MONSTER_PROP_SKILL_REDUCE_P_DAMAGE,            // ���ܺ�BUFF��������פ�������ܣ������������˺�����ֵ
	MONSTER_PROP_SKILL_REDUCE_P_DAMAGE_RATIO,      // ���ܺ�BUFF��������פ�������ܣ������������˺������ֵ����ֱȣ�
	MONSTER_PROP_SKILL_REDUCE_M_DAMAGE,            // ���ܺ�BUFF��������פ�������ܣ������ķ����˺�����ֵ
	MONSTER_PROP_SKILL_REDUCE_M_DAMAGE_RATIO,      // ���ܺ�BUFF��������פ�������ܣ������ķ����˺������ֵ����ֱȣ�

	MONSTER_PROP_SKILL_INCREASE_P_DAMAGE,          // ���ܺ�BUFF��������פ�������ܣ������������˺�����ֵ
	MONSTER_PROP_SKILL_INCREASE_P_DAMAGE_RATIO,    // ���ܺ�BUFF��������פ�������ܣ������������˺����ӱ�ֵ����ֱȣ�
	MONSTER_PROP_SKILL_INCREASE_M_DAMAGE,          // ���ܺ�BUFF��������פ�������ܣ������ķ����˺�����ֵ
	MONSTER_PROP_SKILL_INCREASE_M_DAMAGE_RATIO,    // ���ܺ�BUFF��������פ�������ܣ������ķ����˺����ӱ�ֵ����ֱȣ�

	// �����˺��ٷֱ�
	MONSTER_PROP_SKILL_REBOUND_DAMAGE_RATIO,       // ���ܺ�BUFF��������פ�������ܣ������ķ����˺��ٷֱ�


	MONSTER_PROP_SKILL_PENETRATE,				   // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����Ĵ��̣�����)�˺�ֵ
	MONSTER_PROP_SKILL_KICK_PENETRATE,			   // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĵֿ����̣��ֿ�����)�˺�ֵ
	MONSTER_PROP_SKILL_KICK_PENETRATE_RATIO,	   // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĵֿ����̣��ֿ�����)�˺���ֵ����ֱȣ�

	MONSTER_PROP_SKILLREBOUND,                     // ���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������˺�������ֵ����ֱȣ�

	//����/���� �ķ���/���� ����ı�ֵ
	MONSTER_PROP_PLUS_MIN_P_A,                     // ����ı���С������ֵ
	MONSTER_PROP_PLUS_MAX_P_A,                     // ����ı����������ֵ
	MONSTER_PROP_PLUS_MIN_M_A,                     // ����ı���С��������ֵ
	MONSTER_PROP_PLUS_MAX_M_A,                     // ����ı����������ֵ
	MONSTER_PROP_PLUS_P_D,                         // ����ı��������ֵ
	MONSTER_PROP_PLUS_M_D,                         // ����ı䷨������ֵ

	/* 1������д�С�ȣ���СֵID�����������ֵIDǰһλ��
	   2��ֻ�е�ǰֵ������Ҫ��С�ȡ�
	   3����ǰֵ��һ�㶼�ǽ�ֹ�޸ĵģ���Ϊ���ǻ���ֵ�͸���ֵ��������ģ�Ҫ�ľ͸ĸ���ֵ�ͺ��ˡ�
	   4������ֵ����������Ϊ�����ģ���ΪBUFFΪ��ֵ�м��м��ġ�//*/

	MONSTER_PROP_MAXID,                            // �������ID
};

//
// ��������
// 
enum
{
	PET_PROP_PDBID = 1,				// �������ݿ�ID
	PET_PROP_PETID ,				// ��������ID	
	PET_PROP_SID,					// �����	
	PET_PROP_ELEMENT,				// ��������	
	PET_PROP_GENIUS,				// �츳
	PET_PROP_LEVEL,					// �ȼ�
	PET_PROP_STARS,					// �Ǽ���Ʒ��
	PET_PROP_TITLE,					// ͷ�Σ����	
	PET_PROP_CUR_HP,				// ��ǰ����ֵ
	PET_PROP_MAX_HP,				// ����ֵ����
	PET_PROP_CUR_MP,				// ��ǰ����ֵ
	PET_PROP_MAX_MP,				// ����ֵ����
	PET_PROP_CUR_MOVE_SPEED,		// ��ǰ�ƶ��ٶ�
	PET_PROP_CUR_WALK_SPEED,		// ��ǰ��·�ٶ�
	PET_PROP_CUR_MOVE_STYLE,        // ��ǰ�ƶ���ʽ
	PET_PROP_DEATH,					// �Ƿ�����

	PET_PROP_BROADCAST,				// ����Ϊ�㲥����
	/////////////////////////////////////////////////
	PET_PROP_BASE_MAX_HP,			// ��������������ֵ

	PET_PROP_RELEASE_STATE,			// ����δ���
	PET_PROP_CHUMMY,				// ���ܶ�
	PET_PROP_CUR_BIRTH_TIMES,		// ת������
	PET_PROP_POTENTIAL,				// Ǳ��ֵ
	PET_PROP_RELEASE_START_TIME,	// ���ʱ��
	PET_PROP_POSITION,				// �󷨣���λ
	PET_PROP_REALIZATION_TIMES,	    // �������	
	PET_PROP_EXP,					// ����

	PET_PROP_CUR_MIN_P_A,			// ��ǰ��С������
	PET_PROP_CUR_MAX_P_A,			// ��ǰ���������

	PET_PROP_CUR_MIN_M_A,			// ��ǰ��С��������
	PET_PROP_CUR_MAX_M_A,			// ��ǰ���������

	PET_PROP_CUR_P_D,				// ��ǰ�������
	PET_PROP_CUR_M_D,				// ��ǰ��������

	PET_PROP_CUR_FATAL_PER,			// ��ǰ��������	
	PET_PROP_CUR_HIT_PER,			// ��ǰ���и���	
	PET_PROP_CUR_HEDGE_PER,			// ��ǰ���ܸ���

	PET_PROP_HP_GROWTH_PER,			// �����ɳ���

	PET_PROP_MIN_P_A_GROWTH_PER,	// ��С�������ɳ���
	PET_PROP_MAX_P_A_GROWTH_PER,	// ����������ɳ���
	PET_PROP_MIN_M_A_GROWTH_PER,	// ��Сħ�������ɳ���
	PET_PROP_MAX_M_A_GROWTH_PER,	// ���ħ�������ɳ���
	PET_PROP_P_DEF_GROWTH_PER,		// ��������ɳ���
	PET_PROP_M_DEF_GROWTH_PER,		// ���������ɳ���

	PET_PROP_LUCK,					// ����ֵ
	PET_PROP_FEED_STARTTIME,		// ��ʼιʳ
	PET_PROP_SUB_EXP,				// �ڵ�����
	PET_PROP_BIND,					// �󶨱�־
	PET_PROP_ACTION_STATE,			// ��������˵���Ϊ��־

	PET_PROP_INIT_HP,				// ��ʼ����ֵ������ʱ��Ҫʹ��
	PET_PROP_INIT_MIN_P_A,			// ��ʼ��С������������ʱ��ʹ��
	PET_PROP_INIT_MAX_P_A,			// ��ʼ���������������ʱ��ʹ��
	PET_PROP_INIT_MIN_M_A,			// ��ʼ��С��������������ʱ��ʹ��
	PET_PROP_INIT_MAX_M_A,			// ��ʼ���������������ʱ��ʹ��
	PET_PROP_INIT_P_D,				// ��ʼ�������������ʱ��ʹ��
	PET_PROP_INIT_M_D,				// ��ʼ��������������ʱ��ʹ��

	PET_PROP_AWORDTIME,				// ���ʱ��(��λ��) ��������ʱ��
	PET_PROP_SANCTIFY,				// ʥ������ ldy
	PET_PROP_PRIVATE,				// ����Ϊ����˽������
	////////////////////////////////////////////////////////////////
	//����ʵ��(����)����ֵ
	PET_PROP_CUR_HP_RECOVERY,					//����ʵ�ʣ����գ��ظ��ٶ�
	PET_PROP_CUR_FIGHT,                         //����ʵ��(����ս����)
	PET_PROP_CUR_HEDGE,							//����ʵ��(����)����ֵ,������ʾ
	PET_PROP_CUR_HEDGE_RATIO,					//����ʵ��(����)������
	PET_PROP_CUR_PRESENT,						//����ʵ��(����)����ֵ��������ʾ
	PET_PROP_CUR_PRESENT_RATIO,					//����ʵ��(����)������

	PET_PROP_CUR_FATAL,							//����ʵ��(����)����ֵ��������ʾ
	PET_PROP_CUR_FATAL_RATIO,					//����ʵ��(����)������
	PET_PROP_CUR_KICK_FATAL,					//����ʵ��(����)����ֵ��������ʾ
	PET_PROP_CUR_KICK_FATAL_RATIO,				//����ʵ��(����)������

	PET_PROP_CUR_FATAL_DAMAGE_RATIO,			//����ʵ��(����)���ӻ����˺���ֵ����ֱ�)
	PET_PROP_CUR_KICK_FATAL_DAMAGE_RATIO,		//����ʵ��(����)�ֿ������˺���ֵ����ֱ�)

	PET_PROP_CUR_ATTACK_SPEED,					//����ʵ��(����)�����ٶ�ֵ

	PET_PROP_CUR_IGNORE_P_D,					//����ʵ��(����)�����������ֵ
	PET_PROP_CUR_IGNORE_P_D_RATIO,				//����ʵ��(����)�������������ֵ����ֱȣ�
	PET_PROP_CUR_IGNORE_M_D,					//����ʵ��(����)���Է�������ֵ
	PET_PROP_CUR_IGNORE_M_D_RATIO,				//����ʵ��(����)���Է���������ֵ����ֱȣ�

	PET_PROP_CUR_REDUCE_P_DAMAGE,				//����ʵ��(����)�����˺�����ֵ
	PET_PROP_CUR_REDUCE_P_DAMAGE_RATIO,			//����ʵ��(����)�����˺������ֵ����ֱȣ�
	PET_PROP_CUR_REDUCE_M_DAMAGE,				//����ʵ��(����)�����˺�����ֵ
	PET_PROP_CUR_REDUCE_M_DAMAGE_RATIO,			//����ʵ��(����)�����˺������ֵ����ֱȣ�

	PET_PROP_CUR_INCREASE_P_DAMAGE,				//����ʵ��(����)�����˺�����ֵ
	PET_PROP_CUR_INCREASE_P_DAMAGE_RATIO,		//����ʵ��(����)�����˺����ӱ�ֵ����ֱȣ�
	PET_PROP_CUR_INCREASE_M_DAMAGE,				//����ʵ��(����)�����˺�����ֵ
	PET_PROP_CUR_INCREASE_M_DAMAGE_RATIO,		//����ʵ��(����)�����˺����ӱ�ֵ����ֱȣ�

	// �����˺��ٷֱ�
	PET_PROP_CUR_REBOUND_DAMAGE_RATIO,			//����ʵ��(����)�����˺��ٷֱ�

	PET_PROP_CUR_PENETRATE,						//����ʵ��(����)���̣�����)�˺�ֵ
	PET_PROP_CUR_KICK_PENETRATE,				//����ʵ��(����)�ֿ����̣��ֿ�����)�˺�ֵ
	PET_PROP_CUR_KICK_PENETRATE_RATIO,			//����ʵ��(����)�ֿ����̣��ֿ�����)�˺���ֵ����ֱȣ�

	//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������Լӳ�
	//����/���� �ķ�����/���� ��������ص�
	PET_PROP_SKILL_BASE_MIN_P_A,				//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����������������������Сֵ
	PET_PROP_SKILL_BASE_MIN_P_A_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����������������������С��ֵ����ֱȣ�
	PET_PROP_SKILL_BASE_MAX_P_A,				//���ܺ�BUFF���ǳ�פ�������ܳ��⣩������������������������ֵ
	PET_PROP_SKILL_BASE_MAX_P_A_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������������������������ֵ����ֱȣ�

	PET_PROP_SKILL_BASE_MIN_M_A,				//���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ���������Сֵ
	PET_PROP_SKILL_BASE_MIN_M_A_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ���������С��ֵ����ֱȣ�
	PET_PROP_SKILL_BASE_MAX_M_A,				//���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ����������ֵ
	PET_PROP_SKILL_BASE_MAX_M_A_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ�����������ֵ����ֱȣ�

	PET_PROP_SKILL_BASE_P_D,					//���ܺ�BUFF���ǳ�פ�������ܳ��⣩����������������������ֵ
	PET_PROP_SKILL_BASE_P_D_RATIO,				//���ܺ�BUFF���ǳ�פ�������ܳ��⣩������������������������ֵ����ֱȣ�

	PET_PROP_SKILL_BASE_M_D,					//���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ�������ֵ
	PET_PROP_SKILL_BASE_M_D_RATIO,				//���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ķ���������ֵ����ֱȣ�

	//����/���� �ķ�����/���� ����ǰ��ص�
	PET_PROP_SKILL_SUM_MIN_P_A_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ����������С��ֵ����ֱȣ�
	PET_PROP_SKILL_SUM_MAX_P_A_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ������������ֵ����ֱȣ�
	PET_PROP_SKILL_SUM_MIN_M_A_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ�ķ���������С��ֵ����ֱȣ�
	PET_PROP_SKILL_SUM_MAX_M_A_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ�ķ�����������ֵ����ֱȣ�
	PET_PROP_SKILL_SUM_P_D_RATIO,				//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ�����������ֵ����ֱȣ�
	PET_PROP_SKILL_SUM_M_D_RATIO,				//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӵ�ǰ�ķ���������ֵ����ֱȣ�

	//��HP/MP��ص�
	PET_PROP_SKILL_BASE_MAX_HP,					//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӳ��������������ֵ
	PET_PROP_SKILL_BASE_MAX_HP_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӳ����������������ֵ����ֱȣ�
	PET_PROP_SKILL_SUM_MAX_HP_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӳ��ﵱǰ�����������ֵ����ֱȣ�

	PET_PROP_SKILL_HP_RECOVERY,					//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������������ظ��ٶ�ֵ
	PET_PROP_SKILL_HP_RECOVERY_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������������ظ��ٶȱ�ֵ����ֱȣ�

	//��ս����ص�
	PET_PROP_SKILL_HEDGE,						//���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ֵ
	PET_PROP_SKILL_HEDGE_RATIO,					//���ܺ�BUFF���ǳ�פ�������ܳ��⣩����������������
	PET_PROP_SKILL_PRESENT,						//���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ֵ
	PET_PROP_SKILL_PRESENT_RATIO,				//���ܺ�BUFF���ǳ�פ�������ܳ��⣩����������������

	PET_PROP_SKILL_FATAL,						//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӻ���ֵ
	PET_PROP_SKILL_FATAL_RATIO,					//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӻ�����
	PET_PROP_SKILL_KICK_FATAL,					//���ܺ�BUFF���ǳ�פ�������ܳ��⣩��������������ֵ

	PET_PROP_SKILL_FATAL_DAMAGE_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩���������ӻ����˺���ֵ����ֱ�)
	PET_PROP_SKILL_KICK_FATAL_DAMAGE_RATIO,		//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĵֿ������˺���ֵ����ֱ�)

	PET_PROP_SKILL_ATTACK_SPEED,				//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����Ĺ����ٶ�ֵ
	PET_PROP_SKILL_ATTACK_SPEED_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����Ĺ����ٶȱ�ֵ����ֱȣ�
	PET_PROP_SKILL_MOVE_SPEED,					//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������ƶ��ٶ�
	PET_PROP_SKILL_MOVE_SPEED_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������ƶ��ٶȱ�ֵ����ֱȣ�

	PET_PROP_SKILL_IGNORE_P_D,					//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĺ����������ֵ
	PET_PROP_SKILL_IGNORE_P_D_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĺ������������ֵ����ֱȣ�
	PET_PROP_SKILL_IGNORE_M_D,					//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĺ��Է�������ֵ
	PET_PROP_SKILL_IGNORE_M_D_RATIO,			//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĺ��Է���������ֵ����ֱȣ�

	PET_PROP_SKILL_REDUCE_P_DAMAGE,				//���ܺ�BUFF��������פ�������ܣ������������˺�����ֵ
	PET_PROP_SKILL_REDUCE_P_DAMAGE_RATIO,		//���ܺ�BUFF��������פ�������ܣ������������˺������ֵ����ֱȣ�
	PET_PROP_SKILL_REDUCE_M_DAMAGE,				//���ܺ�BUFF��������פ�������ܣ������ķ����˺�����ֵ
	PET_PROP_SKILL_REDUCE_M_DAMAGE_RATIO,		//���ܺ�BUFF��������פ�������ܣ������ķ����˺������ֵ����ֱȣ�

	PET_PROP_SKILL_INCREASE_P_DAMAGE,			//���ܺ�BUFF��������פ�������ܣ������������˺�����ֵ
	PET_PROP_SKILL_INCREASE_P_DAMAGE_RATIO,		//���ܺ�BUFF��������פ�������ܣ������������˺����ӱ�ֵ����ֱȣ�
	PET_PROP_SKILL_INCREASE_M_DAMAGE,			//���ܺ�BUFF��������פ�������ܣ������ķ����˺�����ֵ
	PET_PROP_SKILL_INCREASE_M_DAMAGE_RATIO,		//���ܺ�BUFF��������פ�������ܣ������ķ����˺����ӱ�ֵ����ֱȣ�

	// �����˺��ٷֱ�
	PET_PROP_SKILL_REBOUND_DAMAGE_RATIO,		//���ܺ�BUFF��������פ�������ܣ������ķ����˺��ٷֱ�
	PET_PROP_SKILL_PENETRATE,					//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����Ĵ��̣�����)�˺�ֵ
	PET_PROP_SKILL_KICK_PENETRATE,				//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĵֿ����̣��ֿ�����)�˺�ֵ
	PET_PROP_SKILL_KICK_PENETRATE_RATIO,		//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�����ĵֿ����̣��ֿ�����)�˺���ֵ����ֱȣ�

	PET_PROP_SKILLREBOUND,						//���ܺ�BUFF���ǳ�פ�������ܳ��⣩�������˺�������ֵ����ֱȣ�

	//����/���� �ķ���/���� ����ı�ֵ
	PET_PROP_PLUS_MIN_P_A,                      // ����ı���С������ֵ
	PET_PROP_PLUS_MAX_P_A,                      // ����ı����������ֵ
	PET_PROP_PLUS_MIN_M_A,                      // ����ı���С��������ֵ
	PET_PROP_PLUS_MAX_M_A,                      // ����ı����������ֵ
	PET_PROP_PLUS_P_D,                          // ����ı��������ֵ
	PET_PROP_PLUS_M_D,                          // ����ı䷨������ֵ

	/* 1������д�С�ȣ���СֵID�����������ֵIDǰһλ��
	2��ֻ�е�ǰֵ������Ҫ��С�ȡ�
	3����ǰֵ��һ�㶼�ǽ�ֹ�޸ĵģ���Ϊ���ǻ���ֵ�͸���ֵ��������ģ�Ҫ�ľ͸ĸ���ֵ�ͺ��ˡ�
	4������ֵ����������Ϊ�����ģ���ΪBUFFΪ��ֵ�м��м��ġ�*/

	PET_PROP_MAXID,					// �������ID
}; 
//#define PET_POEWR_FLOAT 10000.0f      //bu cjl �����powerҪ�������ֵ��Ȼ���ɸ���

// ���ö����Ϊ��ȡ�����������зǹ��������������ò���������ӳ��, �������ƶ�Ӧ�ɳ�����������ԡ�
// �ⲿ���ó����ר������ʱ���Ա����ⲿ����ʱ�������ı����ǳ���ĺ������ԡ��Դﵽ������������ö�ٵ���Ŀ��
// ���ǻ����ⲿ����������ͬ���Ƶ�ö�ٹ�ָͬ��ͬһ�����ݣ��ڵĵ�����ʱҪ����������ʵ��ĵ��ã������ҵ���ȷ������
// �˴���������� �ݶ�(WZH 09.12.09) 
enum CREATURE_TO_PET
{
	CREATURE_PET_PROP_SID = CREATURE_PROP_SEX,													// ��������� <=> �����Ա�										
    CREATURE_PET_PROP_GENIUS = CREATURE_PROP_NATION,											// �츳 <=> �������
	CREATURE_PET_PROP_ELEMENT = CREATURE_PROP_PROVINCE,											// �������� <=> ����ʡ��
	CREATURE_PET_PROP_SANCTIFY = CREATURE_PROP_CONSTELLATION,									// ʥ������ <=> �������� ldy
	CREATURE_PET_PROP_STARS = CREATURE_PROP_FACEID,												// �Ǽ���Ʒ�� <=> ����ͷ��
	CREATURE_PET_PROP_HOMAGE = CREATURE_PROP_PURSE_MONEY,										// ͷ�Σ���� <=> ���Ͻ�Ǯ
	CREATURE_PET_PROP_DEATH = CREATURE_PROP_PURSE_GOLDINGOT,									// ����״̬ <=> ����Ԫ�� 
	
	CREATURE_PET_PROP_RELEASE_STATE = CREATURE_PROP_USABLEBAG,									// ����δ��� <=> ��������
	CREATURE_PET_PROP_CHUMMY = CREATURE_PROP_WARE_MONEY,										// ���ܶ� <=> �ֿ��Ƿ���
	CREATURE_PET_PROP_CUR_BIRTH_TIMES = CREATURE_PROP_WARE_LOCK,								// ��ǰת������ <=> �ֿ�����	
	CREATURE_PET_PROP_POTENTIAL = CREATURE_PROP_SKILLPOINT,										// Ǳ��ֵ<=>���ܵ�
	CREATURE_PET_PROP_RELEASE_START_TIME = CREATURE_PROP_SKILLPOINT_CONSUME_BRANCH_FIRST,		// ��⿪ʼʱ��<=>��һ�����ܷ�֧�����ĵļ��ܵ�
	CREATURE_PET_PROP_POSITION = CREATURE_PROP_SKILLPOINT_CONSUME_BRANCH_SECOND,				// �� ��λ <=> �ڶ������ܷ�֧�����ĵļ��ܵ�
	CREATURE_PET_PROP_REALIZATION_TIMES = CREATURE_PROP_EQUIP_BASE_P_D,							// �������<=> ��װ��С��������
	CREATURE_PET_PROP_HP_GROWTH_PER = CREATURE_PROP_EQUIP_BASE_MIN_M_A,							// �����ɳ���<=>��������
	CREATURE_PET_PROP_MIN_P_A_GROWTH_PER = CREATURE_PROP_EQUIP_BASE_MAX_M_A,						// ��С�������ɳ���<=>��������
	CREATURE_PET_PROP_MAX_P_A_GROWTH_PER = CREATURE_PROP_EQUIP_BASE_M_D,							// ����������ɳ���<=>��������
	CREATURE_PET_PROP_MIN_M_A_GROWTH_PER = CREATURE_PROP_EQUIP_BASE_MAX_HP,						// ��Сħ�������ɳ���<=>��������
	CREATURE_PET_PROP_MAX_M_A_GROWTH_PER = CREATURE_PROP_EQUIP_BASE_MAX_MP,						// ���ħ�������ɳ���<=>��������				
	CREATURE_PET_PROP_P_DEF_GROWTH_PER = CREATURE_PROP_EQUIP_BASE_HEDGE,						// ��������ɳ���<=>������С������
	CREATURE_PET_PROP_M_DEF_GROWTH_PER = CREATURE_PROP_EQUIP_BASE_PRESENT,						// ���������ɳ���<=>�������������
	CREATURE_PET_PROP_LUCK = CREATURE_PROP_EQUIP_BASE_FATAL,									// ����ֵ<=>������С��������
	CREATURE_PET_PROP_FEED_STARTTIME = CREATURE_PROP_EQUIP_BASE_KICK_FATAL,						// ��ʼιʳ<=>�������������
	CREATURE_PET_PROP_INIT_HP  = CREATURE_PROP_EQUIP_PLUS_MIN_P_A,								// ��ʼ����ֵ<=>������С�������
	CREATURE_PET_PROP_INIT_MIN_P_A = CREATURE_PROP_EQUIP_PLUS_MIN_P_A_RATIO,					// ��ʼ��С������<=>��������������
    CREATURE_PET_PROP_INIT_MAX_P_A = CREATURE_PROP_EQUIP_PLUS_MIN_P_A_RATIO_2,					// ��ʼ���������<=>������С��������
    CREATURE_PET_PROP_INIT_MIN_M_A = CREATURE_PROP_EQUIP_PLUS_MAX_P_A,							// ��ʼ��С��������<=>�������������
	CREATURE_PET_PROP_INIT_MAX_M_A = CREATURE_PROP_EQUIP_PLUS_MAX_P_A_RATIO,					// ��ʼ���������<=>��������
    CREATURE_PET_PROP_INIT_P_D = CREATURE_PROP_EQUIP_PLUS_MAX_P_A_RATIO_2,						// ��ʼ�������<=>��������
	CREATURE_PET_PROP_INIT_M_D = CREATURE_PROP_EQUIP_PLUS_P_D,									// ��ʼ��������<=>��������
    CREATURE_PET_PROP_INIT_HIT_PET = CREATURE_PROP_EQUIP_PLUS_P_D_RATIO,						// ��ʼ���и���<=>��������
    CREATURE_PET_PROP_INIT_HEDGE_PET = CREATURE_PROP_EQUIP_PLUS_P_D_RATIO_2,					// ��ʼ���ܸ���<=>���Ӿ���
	CREATURE_PET_PROP_INIT_FATAL_PER = CREATURE_PROP_EQUIP_PLUS_MIN_M_A,						// ��ʼ��������<=>�����������ԣ����ʣ����������ݣ�����������
	CREATURE_PET_PROP_SUB_EXP = CREATURE_PROP_EQUIP_PLUS_MIN_M_A_RATIO ,						// �ڵ����� <=> ��װ��С������ 
	CREATURE_PET_PROP_ACTIONSTATE = CREATURE_PROP_EQUIP_PLUS_MIN_M_A_RATIO_2 ,							// �󶨱�־ <-> ��װ���������
	CREATURE_PET_PROP_AWORDTIME = CREATURE_PROP_EQUIP_PLUS_MAX_M_A,								// ���ʱ��<=>װ�����Ӹı����������ֵ

	CREATURE_PET_PROP_MAXID = CREATURE_PROP_MAXID,												// �������ID
};

/////////////////////////////�������꣨�ϳɣ�////////////////////
enum
{
	PET_MAINPROP_COMPOUND = 1,		//����������
	PET_MINORPROP_COMPOUND  ,		//����������
	PET_INITPROP_COMPOUND  ,		//��ʼ��������
	PET_LUCKYPROP_COMPOUND  ,		//����ֵ����
	PET_IDCARDPROP_COMPOUND  ,		//���������
};


//////////////////////////// ��Ʒ�� ////////////////////////////////
//  ��Ʒ�������ࣻ
enum EGOODS_CLASS
{
	GOODS_CLASS_MIN   = 0,

	GOODS_CLASS_EQUIPMENT,                          // װ��
	GOODS_CLASS_NONEQUIPABLEGOODS,                  // ��װ������Ʒ

	GOODS_CLASS_MAX,
};

//  װ�����ࣻ
enum EEQUIPMENT_SUBCLASS
{
	EQUIPMENT_SUBCLASS_MIN = 0,
	EQUIPMENT_SUBCLASS_WARRIOR_WEAPON_2_CLASS,	//�̱�EQUIPMENT_SUBCLASS_SORCERER_SINGLE_WEAPON
	EQUIPMENT_SUBCLASS_WARRIOR_WEAPON_1_CLASS,	//���� EQUIPMENT_SUBCLASS_WARRIOR_SINGLE_WEAPON
	EQUIPMENT_SUBCLASS_ARCHER_WEAPON_1_CLASS,	//��ϵ EQUIPMENT_SUBCLASS_ARCHER_DOUBLE_WEAPON
	EQUIPMENT_SUBCLASS_ARCHER_WEAPON_2_CLASS,	//��ϵ EQUIPMENT_SUBCLASS_ARCHER_SINGLE_WEAPON
	EQUIPMENT_SUBCLASS_SORCERER_WEAPON_1_CLASS,	//��� EQUIPMENT_SUBCLASS_SORCERER_DOUBLE_WEAPON
	EQUIPMENT_SUBCLASS_SORCERER_WEAPON_2_CLASS,	//���� EQUIPMENT_SUBCLASS_SORCERER_SINGLE_WEAPON
	EQUIPMENT_SUBCLASS_ARMET,					//ͷ��	
	EQUIPMENT_SUBCLASS_ARMOR,					//�¼�
	EQUIPMENT_SUBCLASS_SHOES,					//Ь��
	EQUIPMENT_SUBCLASS_CUFF,					//����
	EQUIPMENT_SUBCLASS_RING,					//��ָ
	EQUIPMENT_SUBCLASS_DECORATION,				//��׹
	EQUIPMENT_SUBCLASS_NECKLACE,				//����
	EQUIPMENT_SUBCLASS_SUITARMET,				//ͷ��ʱװ
	EQUIPMENT_SUBCLASS_SUITARMOR,				//����ʱװ
	EQUIPMENT_SUBCLASS_GEMS,					//��ʯ
	EQUIPMENT_SUBCLASS_BAG,						//����
	EQUIPMENT_SUBCLASS_OTHER,					//����
	EQUIPMENT_SUBCLASS_MAX,						//���
};

//  ��Ʒ����(NonequipableGoods.csv��)��
enum ENONEQUIPABLEGOODS_SUBCLASS
{
	NONEQUIPABLEGOODS_SUBCLASS_MIN    = 0,

	NONEQUIPABLEGOODS_SUBCLASS_LEECHDOM,             // ҩƷ
	NONEQUIPABLEGOODS_SUBCLASS_SKILLBOOK,            // ������
	NONEQUIPABLEGOODS_SUBCLASS_PETSKILLBOOK,         // ���＼����(wzh)
	NONEQUIPABLEGOODS_SUBCLASS_TASKGOOD,			 // ������Ʒ
	NONEQUIPABLEGOODS_SUBCLASS_ORE,				     // ��ʯ
	NONEQUIPABLEGOODS_SUBCLASS_HERBAGE,              // ��ҩ
	NONEQUIPABLEGOODS_SUBCLASS_WOOD,				 // ľ��
	NONEQUIPABLEGOODS_SUBCLASS_MATERIAL,             // ����
	NONEQUIPABLEGOODS_SUBCLASS_MICS,                 // ����
	NONEQUIPABLEGOODS_SUBCLASS_STONE,				 // ��ʯ
	NONEQUIPABLEGOODS_SUBCLASS_SOLE,				 // ����
	NONEQUIPABLEGOODS_SUBCLASS_PROP,				 // ����
	NONEQUIPABLEGOODS_SUBCLASS_SECRET,               // �䷽
	NONEQUIPABLEGOODS_SUBCLASS_SPAR,                 // ����
	NONEQUIPABLEGOODS_SUBCLASS_RIDE,				 // ��� zgz
	NONEQUIPABLEGOODS_SUBCLASS_OTHER,                // ����

	NONEQUIPABLEGOODS_SUBCLASS_MAX
};

//////////////////////////// ����/���� /////////////////////////////
//�����ı�����ʱû�п���
enum
{
	EQUIPMENT_FUNCTIONTYPE_WEAPON = 1,	// ����
	EQUIPMENT_FUNCTIONTYPE_ARMOUR,		// ����
};

//////////////////////////////װ��Ʒ�����Լ���//////////////////////////////
enum
{
	GOODS_BRAND_LEVEL_NONE_LEVEL	= 0,		//��Ʒ������
	GOODS_BRAND_LEVEL_GRAY_LEVEL,				//��ɫƷ������
	GOODS_BRAND_LEVEL_WHITE_LEVEL,				//��ɫƷ������
	GOODS_BRAND_LEVEL_GREEN_LEVEL,				//��ɫƷ������
	GOODS_BRAND_LEVEL_BLUE_LEVEL,				//��ɫƷ������
	GOODS_BRAND_LEVEL_VIOLET_LEVEL,				//��ɫ����Ʒ��
	GOODS_BRAND_LEVEL_GOLDEN_LEVEL,				//��ɫƷ������
	GOODS_BRAND_LEVEL_MAX_LEVEL,				//���Ʒ������
};
//////////////////////////////װ�����꼶��/////////////////////////////////////
enum
{
	EQUIPMENT_SMELT_SOUL_LEVEL_0 = 0,				//���꼶��0
	EQUIPMENT_SMELT_SOUL_LEVEL_1,
	EQUIPMENT_SMELT_SOUL_LEVEL_2,
	EQUIPMENT_SMELT_SOUL_LEVEL_3,
	EQUIPMENT_SMELT_SOUL_LEVEL_4,
	EQUIPMENT_SMELT_SOUL_LEVEL_5,
	EQUIPMENT_SMELT_SOUL_LEVEL_6,
	EQUIPMENT_SMELT_SOUL_LEVEL_7,
	EQUIPMENT_SMELT_SOUL_LEVEL_8,
	EQUIPMENT_SMELT_SOUL_LEVEL_9,
	EQUIPMENT_SMELT_SOUL_LEVEL_MAX,

};

//////////////////////////////װ��ս��������//////////////////////////
#define EQUIP_COMBAT_PROP_ID2PROP( id )		(  (id) <= EQUIP_COMBAT_PROP_ID_MIN  \
											? ( EQUIP_COMBAT_PROP_ID_MIN ) : \
											(  (id) >= EQUIP_COMBAT_PROP_ID_MAX ? \
											( EQUIP_COMBAT_PROP_ID_MIN ): \
											( (id) - EQUIP_COMBAT_PROP_ID_MIN + EQUIP_PROP_CUR_BASE) ) )

enum
{
	//װ������������
	EQUIP_COMBAT_PROP_ID_MIN = 0,						//�½�
	//װ��������
	EQUIP_COMBAT_PROP_ID_BASE_MIN_P_A,					//װ��(����)������С������ֵ
	EQUIP_COMBAT_PROP_ID_BASE_MAX_P_A,					//װ��(����)�������������ֵ
	EQUIP_COMBAT_PROP_ID_BASE_P_D,						//װ�������������ֵ		
	EQUIP_COMBAT_PROP_ID_BASE_MIN_M_A,					//װ��(����)������С��������ֵ	
	EQUIP_COMBAT_PROP_ID_BASE_MAX_M_A,					//װ��(����)�������������ֵ
	EQUIP_COMBAT_PROP_ID_BASE_M_D,						//װ��������������ֵ		
	EQUIP_COMBAT_PROP_ID_BASE_MAX_HP,					//װ�������������ֵ
	EQUIP_COMBAT_PROP_ID_BASE_MAX_MP,					//װ�������������ֵ		
	EQUIP_COMBAT_PROP_ID_BASE_HEDGE,					//װ����������ֵ
	EQUIP_COMBAT_PROP_ID_BASE_PRESENT,					//װ����������ֵ		
	EQUIP_COMBAT_PROP_ID_BASE_FATAL,					//װ����������ֵ		
	EQUIP_COMBAT_PROP_ID_BASE_KICK_FATAL,				//װ����������ֵ
	//װ�����ӵ�
	EQUIP_COMBAT_PROP_ID_PLUS_MIN_P_A,					//װ�����Ӹı���С������ֵ		
	EQUIP_COMBAT_PROP_ID_PLUS_MIN_P_A_RATIO,			//װ�����Ӹı�������С�������ٷֱ�	����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_MIN_P_A_RATIO_2,			//װ�����Ӹı䵱ǰ��С�������ٷֱ�	����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_MAX_P_A,					//װ�����Ӹı����������ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_MAX_P_A_RATIO,			//װ�����Ӹı���������������ٷֱ�	����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_MAX_P_A_RATIO_2,			//װ�����Ӹı䵱ǰ����������ٷֱ�	����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_P_D,						//װ�����Ӹı��������ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_P_D_RATIO,				//װ�����Ӹı�������������ٷֱ�		����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_P_D_RATIO_2,				//װ�����Ӹı䵱ǰ��������ٷֱ�		����ֱȣ�

	EQUIP_COMBAT_PROP_ID_PLUS_MIN_M_A,					//װ�����Ӹı���С��������ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_MIN_M_A_RATIO,			//װ�����Ӹı�������С���������ٷֱ�	����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_MIN_M_A_RATIO_2,			//װ�����Ӹı䵱ǰ��С���������ٷֱ�	����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_MAX_M_A,					//װ�����Ӹı����������ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_MAX_M_A_RATIO,			//װ�����Ӹı���������������ٷֱ�	����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_MAX_M_A_RATIO_2,			//װ�����Ӹı䵱ǰ����������ٷֱ�	����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_M_D,						//װ�����Ӹı䷨������ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_M_D_RATIO,				//װ�����Ӹı����﷨�������ٷֱ�		����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_M_D_RATIO_2,				//װ�����Ӹı䵱ǰ���������ٷֱ�		����ֱȣ�

	EQUIP_COMBAT_PROP_ID_PLUS_MAX_HP,					//װ�����Ӹı��������ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_MAX_HP_RATIO,				//װ�����Ӹı�������������ٷֱ�		����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_MAX_HP_RATIO_2,			//װ�����Ӹı䵱ǰ��������ٷֱ�		����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_MAX_MP,					//װ�����Ӹı��������ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_MAX_MP_RATIO,				//װ�����Ӹı�������������ٷֱ�		����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_MAX_MP_RATIO_2,			//װ�����Ӹı䵱ǰ��������ٷֱ�		����ֱȣ�

	EQUIP_COMBAT_PROP_ID_PLUS_HP_RECOVER,				//װ�����������ظ�ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_HP_RECOVER_RATIO,			//װ�����Ӹı������ظ��ٷֱ�			����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_MP_RECOVER,				//װ�����������ظ�ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_MP_RECOVER_RATIO,			//װ�����Ӹı������ظ��ٷֱ�			����ֱȣ�

	EQUIP_COMBAT_PROP_ID_PLUS_HEDGE,					//װ����������ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_HEDGE_RATIO,				//װ�����Ӹı�������
	EQUIP_COMBAT_PROP_ID_PLUS_PRESENT,					//װ����������ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_PRESENT_RATIO,			//װ�����Ӹı�������

	EQUIP_COMBAT_PROP_ID_PLUS_FATAL,					//װ�����ӻ���ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_FATAL_RATIO,				//װ�����Ӹı������
	EQUIP_COMBAT_PROP_ID_PLUS_KICK_FATAL,				//װ����������ֵ

	EQUIP_COMBAT_PROP_ID_PLUS_FATAL_DAMAGE_RATIO,		//װ�����ӻ����˺���߰ٷֱ�			����ֱ�)
	EQUIP_COMBAT_PROP_ID_PLUS_KICK_FATAL_DAMAGE_RATIO,	//װ�����ӻ����˺�����ٷֱ�			����ֱ�)
	
	EQUIP_COMBAT_PROP_ID_PLUS_ATTACK_SPEED,				//װ�����ӹ����ٶ�ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_ATTACK_SPEED_RATIO,		//װ�����Ӹı乥���ٶȰٷֱ�			����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_MOVE_SPEED,				//װ�������ƶ��ٶ�ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_MOVE_SPEED_RATIO,			//װ�����Ӹı��ƶ��ٶȰٷֱ�			����ֱȣ�

	EQUIP_COMBAT_PROP_ID_PLUS_IGNORE_P_D,				//װ�����Ӻ����������ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_IGNORE_P_D_RATIO,			//װ�����Ӻ�����������ٷֱ�			����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_IGNORE_M_D,				//װ�����Ӻ��Է�������ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_IGNORE_M_D_RATIO,			//װ�����Ӻ��Է��������ٷֱ�			����ֱȣ�

	EQUIP_COMBAT_PROP_ID_PLUS_REDUCE_P_DAMAGE,			//װ�����������˺�����ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_REDUCE_P_DAMAGE_RATIO,	//װ�����������˺�����ٷֱ�			����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_REDUCE_M_DAMAGE,			//װ�����ӷ����˺�����ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_REDUCE_M_DAMAGE_RATIO,	//װ�����ӷ����˺�����ٷֱ�			����ֱȣ�

	EQUIP_COMBAT_PROP_ID_PLUS_INCREASE_P_DAMAGE,		//װ�����������˺�����ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_INCREASE_P_DAMAGE_RATIO,	//װ�����������˺����Ӱٷֱ�			����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_INCREASE_M_DAMAGE,		//װ�����ӷ����˺�����ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_INCREASE_M_DAMAGE_RATIO,	//װ�����ӷ����˺����Ӱٷֱ�			����ֱȣ�
	EQUIP_COMBAT_PROP_ID_PLUS_REBOUND_DAMAGE_RATIO,		//װ�����ӷ����˺��ٷֱ�				����ֱȣ�

	EQUIP_COMBAT_PROP_ID_PLUS_PENETRATE,				//װ�����Ӵ��̹���ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_KICK_PENETRATE,			//װ�����Ӵ��̵ֿ�ֵ
	EQUIP_COMBAT_PROP_ID_PLUS_KICK_PENETRATE_RATIO,		//װ�����Ӵ��̵ֿ��ٷֱ�				����ֱȣ�

	EQUIP_COMBAT_PROP_ID_BASE_FIGHT,					//װ�����е�ս����

	EQUIP_COMBAT_PROP_ID_MAX,							 //�Ͻ�
};


////////////////////////////////��ʯ����/////////////////////////////
enum
{	
	Gem_Type_Min = -1,				//�½�
	Gem_Type_Zhong,					//��
	Gem_Type_Xiao,					//Т
	Gem_Type_Ren,					//��,
	Gem_Type_Yi,					//��
	Gem_Type_Li,					//��
	Gem_Type_Zhi,					//��
	Gem_Type_Xin,					//��
	Gem_Type_Yong,					//��
	Gem_Type_Max,					//�Ͻ�
};
///////////////////////////////��ʯ�ȼ�////////////////////////////////////
enum
{
	Gem_Level_Min = 0,				//�½�
	Gem_Level_1,					//1��
	Gem_Level_2,					//2��
	Gem_Level_3,					//3��
	Gem_Level_Max,					//�Ͻ�
};

//////////////////////////////��װ����Ʒ����/////////////////////////////
enum
{
	GOODS_PROP_GOODSID = 1,				// ��ƷID
	GOODS_PROP_QTY,						// ����	
	GOODS_PROP_BIND,					// �󶨱�־
	GOODS_PROP_ENDURECUR,				// ��ǰ�;�
	GOODS_PROP_ENDUREMAX,				// ����;�
	GOODS_PROP_SLOTQTY,					// �����
	GOODS_PROP_BROADCAST,				// ����Ϊ�㲥����	
	GOODS_PROP_MAXID,					// �������ID
	GOODS_PROP_EFFECTID,				// ��������
};

//////////////////////////////װ����Ʒ����/////////////////////////////
//������װ����Ʒ������
enum
{
	EQUIP_PROP_GOODSID = GOODS_PROP_GOODSID,				// ��ƷID
	EQUIP_PROP_QTY = GOODS_PROP_QTY,						// ����	
	EQUIP_PROP_BIND = GOODS_PROP_BIND,						// �󶨱�־
	EQUIP_PROP_ENDURECUR = GOODS_PROP_ENDURECUR,			// ��ǰ�;�
	EQUIP_PROP_ENDUREMAX = GOODS_PROP_ENDUREMAX,			// ����;�
	EQUIP_PROP_SLOTQTY = GOODS_PROP_SLOTQTY,				// �����
	EQUIP_PROP_BROADCAST_PLACEHOLDER = GOODS_PROP_BROADCAST,// ����Ϊ�㲥����	
	EQUIP_PROP_MAXID_PLACEHOLDER = GOODS_PROP_MAXID,		// �������ID
	EQUIP_PROP_EFFECTID_PLACEHOLDER = GOODS_PROP_EFFECTID,	// ��������

	//װ������������
	EQUIP_PROP_CUR_BASE = EQUIP_PROP_EFFECTID_PLACEHOLDER +1,//װ�����ӵ����ԵĻ���
	//װ��������
	EQUIP_PROP_CUR_BASE_MIN_P_A,					//װ��(����)������С������ֵ			(=װ��(����)������С������ֵ + ǿ���ı�װ��(����)������С������ֵ)
	EQUIP_PROP_CUR_BASE_MAX_P_A,					//װ��(����)�������������ֵ			(=װ��(����)�������������ֵ + ǿ���ı�װ��(����)�������������ֵ )
	EQUIP_PROP_CUR_BASE_P_D,						//װ�������������ֵ					(=װ�������������ֵ + ǿ���ı�װ�������������ֵ)
	EQUIP_PROP_CUR_BASE_MIN_M_A,					//װ��(����)������С��������ֵ			(=װ��(����)������С��������ֵ + ǿ���ı�װ��(����)������С��������ֵ)
	EQUIP_PROP_CUR_BASE_MAX_M_A,					//װ��(����)�������������ֵ			(=װ��(����)�������������ֵ + ǿ���ı�װ��(����)�������������ֵ)
	EQUIP_PROP_CUR_BASE_M_D,						//װ��������������ֵ					(=װ��������������ֵ + ǿ���ı�װ��������������ֵ)
	EQUIP_PROP_CUR_BASE_MAX_HP,						//װ�������������ֵ					(=װ�������������ֵ + ǿ���ı�װ�������������ֵ)
	EQUIP_PROP_CUR_BASE_MAX_MP,						//װ�������������ֵ					(=װ�������������ֵ + ǿ���ı�װ�������������ֵ)
	EQUIP_PROP_CUR_BASE_HEDGE,						//װ����������ֵ						(=װ����������ֵ + ǿ���ı�װ����������ֵ)
	EQUIP_PROP_CUR_BASE_PRESENT,					//װ����������ֵ						(=װ����������ֵ + ǿ���ı�װ����������ֵ)
	EQUIP_PROP_CUR_BASE_FATAL,						//װ����������ֵ						(=װ����������ֵ + ǿ���ı�װ����������ֵ)
	EQUIP_PROP_CUR_BASE_KICK_FATAL,					//װ����������ֵ						(=װ����������ֵ + ǿ���ı�װ����������ֵ)
	//װ�����ӵ�
	EQUIP_PROP_CUR_PLUS_MIN_P_A,					//װ�����Ӹı���С������ֵ		
	EQUIP_PROP_CUR_PLUS_MIN_P_A_RATIO,				//װ�����Ӹı�������С�������ٷֱ�	����ֱȣ�
	EQUIP_PROP_CUR_PLUS_MIN_P_A_RATIO_2,			//װ�����Ӹı䵱ǰ��С�������ٷֱ�	����ֱȣ�
	EQUIP_PROP_CUR_PLUS_MAX_P_A,					//װ�����Ӹı����������ֵ
	EQUIP_PROP_CUR_PLUS_MAX_P_A_RATIO,				//װ�����Ӹı���������������ٷֱ�	����ֱȣ�
	EQUIP_PROP_CUR_PLUS_MAX_P_A_RATIO_2,			//װ�����Ӹı䵱ǰ����������ٷֱ�	����ֱȣ�
	EQUIP_PROP_CUR_PLUS_P_D,						//װ�����Ӹı��������ֵ
	EQUIP_PROP_CUR_PLUS_P_D_RATIO,					//װ�����Ӹı�������������ٷֱ�		����ֱȣ�
	EQUIP_PROP_CUR_PLUS_P_D_RATIO_2,				//װ�����Ӹı䵱ǰ��������ٷֱ�		����ֱȣ�

	EQUIP_PROP_CUR_PLUS_MIN_M_A,					//װ�����Ӹı���С��������ֵ
	EQUIP_PROP_CUR_PLUS_MIN_M_A_RATIO,				//װ�����Ӹı�������С���������ٷֱ�	����ֱȣ�
	EQUIP_PROP_CUR_PLUS_MIN_M_A_RATIO_2,			//װ�����Ӹı䵱ǰ��С���������ٷֱ�	����ֱȣ�
	EQUIP_PROP_CUR_PLUS_MAX_M_A,					//װ�����Ӹı����������ֵ
	EQUIP_PROP_CUR_PLUS_MAX_M_A_RATIO,				//װ�����Ӹı���������������ٷֱ�	����ֱȣ�
	EQUIP_PROP_CUR_PLUS_MAX_M_A_RATIO_2,			//װ�����Ӹı䵱ǰ����������ٷֱ�	����ֱȣ�
	EQUIP_PROP_CUR_PLUS_M_D,						//װ�����Ӹı䷨������ֵ
	EQUIP_PROP_CUR_PLUS_M_D_RATIO,					//װ�����Ӹı����﷨�������ٷֱ�		����ֱȣ�
	EQUIP_PROP_CUR_PLUS_M_D_RATIO_2,				//װ�����Ӹı䵱ǰ���������ٷֱ�		����ֱȣ�

	EQUIP_PROP_CUR_PLUS_MAX_HP,						//װ�����Ӹı��������ֵ
	EQUIP_PROP_CUR_PLUS_MAX_HP_RATIO,				//װ�����Ӹı�������������ٷֱ�		����ֱȣ�
	EQUIP_PROP_CUR_PLUS_MAX_HP_RATIO_2,				//װ�����Ӹı䵱ǰ��������ٷֱ�		����ֱȣ�
	EQUIP_PROP_CUR_PLUS_MAX_MP,						//װ�����Ӹı��������ֵ
	EQUIP_PROP_CUR_PLUS_MAX_MP_RATIO,				//װ�����Ӹı�������������ٷֱ�		����ֱȣ�
	EQUIP_PROP_CUR_PLUS_MAX_MP_RATIO_2,				//װ�����Ӹı䵱ǰ��������ٷֱ�		����ֱȣ�

	EQUIP_PROP_CUR_PLUS_HP_RECOVER,					//װ�����������ظ�ֵ
	EQUIP_PROP_CUR_PLUS_HP_RECOVER_RATIO,			//װ�����Ӹı������ظ��ٷֱ�			����ֱȣ�
	EQUIP_PROP_CUR_PLUS_MP_RECOVER,					//װ�����������ظ�ֵ
	EQUIP_PROP_CUR_PLUS_MP_RECOVER_RATIO,			//װ�����Ӹı������ظ��ٷֱ�			����ֱȣ�

	EQUIP_PROP_CUR_PLUS_HEDGE,						//װ����������ֵ
	EQUIP_PROP_CUR_PLUS_HEDGE_RATIO,				//װ�����Ӹı�������
	EQUIP_PROP_CUR_PLUS_PRESENT,					//װ����������ֵ
	EQUIP_PROP_CUR_PLUS_PRESENT_RATIO,				//װ�����Ӹı�������

	EQUIP_PROP_CUR_PLUS_FATAL,						//װ�����ӻ���ֵ
	EQUIP_PROP_CUR_PLUS_FATAL_RATIO,				//װ�����Ӹı������
	EQUIP_PROP_CUR_PLUS_KICK_FATAL,					//װ����������ֵ

	EQUIP_PROP_CUR_PLUS_FATAL_DAMAGE_RATIO,			//װ�����ӻ����˺���߰ٷֱ�			����ֱ�)
	EQUIP_PROP_CUR_PLUS_KICK_FATAL_DAMAGE_RATIO,	//װ�����ӻ����˺�����ٷֱ�			����ֱ�)
	
	EQUIP_PROP_CUR_PLUS_ATTACK_SPEED,				//װ�����ӹ����ٶ�ֵ
	EQUIP_PROP_CUR_PLUS_ATTACK_SPEED_RATIO,			//װ�����Ӹı乥���ٶȰٷֱ�			����ֱȣ�
	EQUIP_PROP_CUR_PLUS_MOVE_SPEED,					//װ�������ƶ��ٶ�ֵ
	EQUIP_PROP_CUR_PLUS_MOVE_SPEED_RATIO,			//װ�����Ӹı��ƶ��ٶȰٷֱ�			����ֱȣ�

	EQUIP_PROP_CUR_PLUS_IGNORE_P_D,					//װ�����Ӻ����������ֵ
	EQUIP_PROP_CUR_PLUS_IGNORE_P_D_RATIO,			//װ�����Ӻ�����������ٷֱ�			����ֱȣ�
	EQUIP_PROP_CUR_PLUS_IGNORE_M_D,					//װ�����Ӻ��Է�������ֵ
	EQUIP_PROP_CUR_PLUS_IGNORE_M_D_RATIO,			//װ�����Ӻ��Է��������ٷֱ�			����ֱȣ�

	EQUIP_PROP_CUR_PLUS_REDUCE_P_DAMAGE,			//װ�����������˺�����ֵ
	EQUIP_PROP_CUR_PLUS_REDUCE_P_DAMAGE_RATIO,		//װ�����������˺�����ٷֱ�			����ֱȣ�
	EQUIP_PROP_CUR_PLUS_REDUCE_M_DAMAGE,			//װ�����ӷ����˺�����ֵ
	EQUIP_PROP_CUR_PLUS_REDUCE_M_DAMAGE_RATIO,		//װ�����ӷ����˺�����ٷֱ�			����ֱȣ�

	EQUIP_PROP_CUR_PLUS_INCREASE_P_DAMAGE,			//װ�����������˺�����ֵ
	EQUIP_PROP_CUR_PLUS_INCREASE_P_DAMAGE_RATIO,	//װ�����������˺����Ӱٷֱ�			����ֱȣ�
	EQUIP_PROP_CUR_PLUS_INCREASE_M_DAMAGE,			//װ�����ӷ����˺�����ֵ
	EQUIP_PROP_CUR_PLUS_INCREASE_M_DAMAGE_RATIO,	//װ�����ӷ����˺����Ӱٷֱ�			����ֱȣ�
	EQUIP_PROP_CUR_PLUS_REBOUND_DAMAGE_RATIO,		//װ�����ӷ����˺��ٷֱ�				����ֱȣ�

	EQUIP_PROP_CUR_PLUS_PENETRATE,					//װ�����Ӵ��̹���ֵ
	EQUIP_PROP_CUR_PLUS_KICK_PENETRATE,				//װ�����Ӵ��̵ֿ�ֵ
	EQUIP_PROP_CUR_PLUS_KICK_PENETRATE_RATIO,		//װ�����Ӵ��̵ֿ��ٷֱ�				����ֱȣ�

	EQUIP_PROP_CUR_BASE_FIGHT,						//װ�����е�ս����

	EQUIP_PROP_CUR_MAX,			 //װ�����ӵ����Ե��Ͻ�

	EQUIP_PROP_BRAND_BASE_LEVEL_ID,		//��ƷƷ������1 id
	EQUIP_PROP_BRAND_LEVEL_2_ID,		//��ƷƷ������2 id
	EQUIP_PROP_BRAND_LEVEL_3_ID,		//��ƷƷ������3 id
	EQUIP_PROP_BRAND_LEVEL_4_ID,		//��ƷƷ������4 id
	EQUIP_PROP_BRAND_MAX_LEVEL_ID,		//��ƷƷ������id���ֵ

	EQUIP_PROP_BRAND_BASE_LEVEL_VAL,	//��ƷƷ������1 ֵ	
	EQUIP_PROP_BRAND_LEVEL_2_VAL,		//��ƷƷ������2 ֵ	
	EQUIP_PROP_BRAND_LEVEL_3_VAL,		//��ƷƷ������3 ֵ	
	EQUIP_PROP_BRAND_LEVEL_4_VAL,		//��ƷƷ������4 ֵ
	EQUIP_PROP_BRAND_MAX_LEVEL_VAL,		//��ƷƷ������ֵ��

	EQUIP_PROP_SMELT_SOUL_LEVEL,		//��Ʒ����ǿ���ȼ�

	EQUIP_PROP_GEMS_EMBEDED_NUM,				//��Ƕ��ʯ������

	EQUIP_PROP_GEMS_BASE_ID,			//��Ƕ�ĵ�1����ʯ��id
	EQUIP_PROP_GEMS_2_ID,				//��Ƕ�ĵ�2����ʯ��id
	EQUIP_PROP_GEMS_3_ID,				//��Ƕ�ĵ�3����ʯ��id
	EQUIP_PROP_GEMS_4_ID,				//��Ƕ�ĵ�4����ʯ��id
	EQUIP_PROP_GEMS_MAX_ID,				//��Ƕ�ı�ʯid�Ͻ�
	EQUIP_PROP_GEMS_COMBIND_ID,			//��ʯ��Ϻ�ĸ�������id

	EQUIP_PROP_EXPIRE_DATE,				//��Ʒ��������
	EQUIP_PROP_USING_TIMES,				//��Ʒʹ�ô���
	EQUIP_PROP_IS_CHECKED,				//��Ʒ�Ƿ��Ѿ�����


	EQUIP_PROP_BROADCAST,				// ����Ϊ�㲥����	

	EQUIP_PROP_MAXID,					// �������ID

	EQUIP_PROP_EFFECTID,				// ��������
	EQUIP_PROP_LETTERING,				// ��������
};

#define PACKET_ALL_EQUIP_PLACE        -2//by cjl,��ʾ��������װ����λ�ã�����С��-1

//////////////////////////////��������/////////////////////////////
enum
{
	BOX_STATE_CLOSE = 0,				// �ر�
	//BOX_STATE_OPEN,						// ��
};

enum
{
	BOX_TYPE_PACK = 0,					// �������������������������İ�����
	BOX_TYPE_HERBALMEDICINE,			// ��ҩ	
	BOX_TYPE_MINERALRESOURCES,			// ���
	BOX_TYPE_PRECIOUSDEPOSITS,			// ����
};

enum
{
	BOX_BORNREASON_UNKNOW = 0,			// δ֪ԭ��
	BOX_BORNREASON_MONSTERDIE,			// ��������
	BOX_BORNREASON_PERSONDIE,			// ��������
	BOX_BORNREASON_PERSONTHROW,			// �����Ӷ���
	BOX_BORNREASON_SYSTEM,				// ϵͳ���ɵ�
};

enum
{
	BOX_PROP_RESID = 1,					// ���������ԴID
	BOX_PROP_RAYRESID,					// ������˸��ԴID
	BOX_PROP_STATE,						// ״̬���򿪣��ر�
	BOX_PROP_TYPE,						// ��������

	BOX_PROP_OPENNEEDTIME,				// ������ʱ�䣨��Ҫ��ò��ܴ򿪣�

	BOX_PROP_GOODSID,					// ��������Ʒ������ID���ͻ��˸��������ʾ��ͬ����ɫ

	BOX_PROP_BROADCAST,					// ����Ϊ�㲥����

	BOX_PROP_BORNREASON,				// ����ԭ�򣺹����װ��������װ��������������ҩ��	

	BOX_PROP_MAXID,						// �������ID

	BOX_PROP_CLEARPOPEDOM,				// ���Ȩ��
};

//////////////////////////////�������/////////////////////////////
enum
{
	MAST_TYPE_CHUNNEL = 1,				// ������
	MAST_TYPE_STALL,					// ̯λ
};

enum
{
	MAST_PROP_RESID = 1,				// ��������Դ
	MAST_PROP_TYPE,						// ���ͣ������ţ�̯λ

	MAST_PROP_BROADCAST,				// ����Ϊ�㲥����

	MAST_PROP_MAXID,					// �������ID
};

//////////////////////////////��������/////////////////////////
// add by zjp.
enum
{
	BUBBLE_PROP_RESID = 1,				// ���������Դ
	BUBBLE_PROP_TYPE,					// ����

	BUBBLE_PROP_BROADCAST,				// ����Ϊ�㲥����

	BUBBLE_PROP_MAXID,					// �������ID
};

/************************************************************************/
/*AI �¼�ö��
*/
/************************************************************************/
enum
{
	AI_EVENT_BORN         =   0 ,// ����	0	Ŀ�����Լ�
	AI_EVENT_BEHIT              ,// ����	1	Ŀ���ǵ�ǰ�����Լ��Ķ���
	AI_EVENT_ATTACK             ,// ����	2	Ŀ���ǵ�ǰ��������
	AI_EVENT_COMMAND            ,// �����¼�	3	Ŀ���Ƿ�����Ķ���
	AI_EVENT_THINK              ,// ��ʱ�¼�	4	Ŀ�����Լ�
	AI_EVENT_DIE                ,// �����¼�	5	Ŀ����ɱ���Լ��Ķ���
	AI_EVENT_MASTER             ,// ���������¼�	6	���������¼������˷����������������յ����¼�����Ŀ��Ϊ���˵�ǰѡ�е�Ŀ�꣨������Ϊϵͳ������Ŀ��Ϊ���������ڹ����Ķ���
	AI_EVENT_MASTER_TIMER       ,// ��������¼�	7	��������¼���һ��ÿ��500ms�̶��Գ��ﴥ�����¼����¼�Ŀ������Ϊ����
	AI_EVENT_FRIEND_TIMER       ,// �Ѻ�Ŀ������¼�	8	ÿ��500ms����һ�ε�����¼���ÿ�λ��һ���������б����Ѻö�����ΪAIĿ�꣬ÿ����һ�θ���һ���Ѻö��󣬱���һ�κ��ٴ�ͷ������
	AI_EVENT_PREATTACK          ,// Ŀ�������¼�	9	Ŀ�������������Ķ���
	AI_EVENT_RETRIEVE           ,// �ع�	10	Ŀ�����Լ�
	AI_EVENT_EXIT_BATTLE        ,// �˳�ս�� 11 Ŀ���Լ�
	AI_EVENT_RETRIEVE_OK        ,// �ع���� 12	Ŀ�����Լ�
	AI_EVENT_ESCAPE             ,// �����¼� 13 Ŀ���Լ�
	AI_EVENT_ESCAPE_OK          ,// ���ܽ��� 14 Ŀ�����Լ�
	AI_EVENT_TALK				,// ����
	AI_EVENT_CRAZY_ATTACK		,// ����
	AI_EVENT_CRAZY_BEHIT		,// ������
	AI_EVENT_HEDGE				,// ����
	AI_EVENT_BEHEDGE			,// ������	
	AI_EVENT_DYNAMIC			,// ��̬�����˾���
	AI_EVENT_MASTER_CMD_TIMER	,// ����ǿ������
	AI_EVENT_SELF_SUB			,// ���ϵ��Ƕ��ı�����¼�

	///////���±��붩�ĵ��������ϣ�δ�ٻ�������û��AI�����ģ��������ٻ�������ʱ����ܶ����¼��������ٻ�����֮��������������������ˡ�
	AI_EVENT_MASTERSUB_CRAZY_ATTACK		,// ���˱����¼�
	AI_EVENT_MASTERSUB_CRAZY_BEHIT		,// ���˱�����	
	AI_EVENT_MASTERSUB_BEHIT			,// ���˱����¼�
	AI_EVENT_MASTERSUB_HEDGE			,// ���������¼�
	AI_EVENT_MASTERSUB_BEHEDGE			,// ���˱�����

	///////����Ϊ���˿����������Ҫ�ɶԣ���ʼ��Ӧ����
	AI_EVENT_MASTERCMD_ATTACK			,// ���������
	AI_EVENT_MASTERCMD_STOPATTACK		,// ��������ֹͣ����
	AI_EVENT_MASTERCMD_PICKUP			,// ��������ʰȡ
	AI_EVENT_MASTERCMD_STOPPICK			,// ��������ֹͣʰȡ
	AI_EVENT_MASTER_OK					,// �����������
};

/// ʵ�嶯��(���ղ߻��ĵ�����)
enum EntityAction
{
	EntityAction_Min = -1,			// ������Сֵ��
	EntityAction_Stand,				//վ������
	EntityAction_Stand_1,			//վ������(����ڶ���)
	EntityAction_Walk,				//���߶���
	EntityAction_Run,				//�ܲ�
	EntityAction_SitingDown,			//���¹���
	EntityAction_Siting,				//��
	EntityAction_JumpStart,			//��Ծ��ʼ
	EntityAction_JumpMidway,			//��Ծ��
	EntityAction_JumpEnd,			//��Ծ����
	EntityAction_CombatWound,		//ս������
	EntityAction_Death,				//����
	EntityAction_Stun,				//��ѣ
	EntityAction_Attack,				//��һ����ͨ����
	EntityAction_Attack_1,			//�ڶ�����ͨ����
	EntityAction_Collect,			//�ɼ�
	EntityAction_Reserve_2,			//Ԥ�����Ǽ��ܵĶ���
	EntityAction_Reserve_3,			//Ԥ�����Ǽ��ܵĶ���
	EntityAction_Reserve_4,			//Ԥ�����Ǽ��ܵĶ���
	EntityAction_Reserve_5,			//Ԥ�����Ǽ��ܵĶ���
	EntityAction_Reserve_6,			//Ԥ�����Ǽ��ܵĶ���
	EntityAction_Reserve_7,			//Ԥ�����Ǽ��ܵĶ���
	EntityAction_Skill_1,	
	EntityAction_Skill_2,	
	EntityAction_Skill_3,	
	EntityAction_Skill_4,	
	EntityAction_Skill_5,	
	EntityAction_Skill_6,	
	EntityAction_Skill_7,	
	EntityAction_Skill_8,	
	EntityAction_Skill_9,	
	EntityAction_Skill_10,	
	EntityAction_Skill_11,	
	EntityAction_Skill_12,	
	EntityAction_Skill_13,	
	EntityAction_Skill_14,	
	EntityAction_Skill_15,	
	EntityAction_Skill_16,	
	EntityAction_Skill_17,	
	EntityAction_Skill_18,	
	EntityAction_Skill_19,	
	EntityAction_Skill_20,	
	EntityAction_Skill_21,	
	EntityAction_Skill_22,	
	EntityAction_Skill_23,	
	EntityAction_Skill_24,	
	EntityAction_Skill_25,	
	EntityAction_Skill_26,	
	EntityAction_Skill_27,	
	EntityAction_Skill_28,	
	EntityAction_Skill_29,	
	EntityAction_Skill_30,	
	EntityAction_Skill_31,	
	EntityAction_Skill_32,	
	EntityAction_Skill_33,	
	EntityAction_Skill_34,	
	EntityAction_Skill_35,	
	EntityAction_Skill_36,	
	EntityAction_Skill_37,	
	EntityAction_Skill_38,	
	EntityAction_Skill_39,	
	EntityAction_Skill_40,	
	EntityAction_Skill_41,	
	EntityAction_Skill_42,	
	EntityAction_Skill_43,	
	EntityAction_Skill_44,	
	EntityAction_Skill_45,	
	EntityAction_Skill_46,	
	EntityAction_Skill_47,	
	EntityAction_Skill_48,	
	EntityAction_Skill_49,	
	EntityAction_Skill_50,	
	EntityAction_Skill_51,	
	EntityAction_Skill_52,	
	EntityAction_Skill_53,	
	EntityAction_Skill_54,	
	EntityAction_Skill_55,	
	EntityAction_Skill_56,	
	EntityAction_Skill_57,	
	EntityAction_Skill_58,	
	EntityAction_Skill_59,	
	EntityAction_Skill_60,	
	EntityAction_Skill_61,	
	EntityAction_Skill_62,	
	EntityAction_Skill_63,	
	EntityAction_Skill_64,	
	EntityAction_Skill_65,	
	EntityAction_Skill_66,	
	EntityAction_Skill_67,	
	EntityAction_Skill_68,	
	EntityAction_Skill_69,	
	EntityAction_Skill_70,	
	EntityAction_Skill_71,	
	EntityAction_Skill_72,	
	EntityAction_Skill_73,	
	EntityAction_Skill_74,	
	EntityAction_Skill_75,	
	EntityAction_Skill_76,	
	EntityAction_Skill_77,	
	EntityAction_Skill_78,	
	EntityAction_Skill_79,	
	EntityAction_Skill_80,	
	EntityAction_Skill_81,	
	EntityAction_Skill_82,	
	EntityAction_Skill_83,	
	EntityAction_Skill_84,	
	EntityAction_Skill_85,	
	EntityAction_Skill_86,	
	EntityAction_Skill_87,	
	EntityAction_Skill_88,	
	EntityAction_Skill_89,	
	EntityAction_Skill_90,	
	EntityAction_Skill_91,	
	EntityAction_Skill_92,	
	EntityAction_Skill_93,	
	EntityAction_Skill_94,	
	EntityAction_Skill_95,	
	EntityAction_Skill_96,	
	EntityAction_Skill_97,	
	EntityAction_Skill_98,	
	EntityAction_Skill_99,	
	EntityAction_Skill_100,	
	EntityAction_Max,			//�������ֵ
};

//by cjl
//�������
enum 
{
	ICreatureDouble_ChangeBody_Rule = 0,//�������
	ICreatureDouble_Rule_Max,
};
//end cjl