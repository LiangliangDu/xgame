/*******************************************************************
** �ļ���:	e:\ourgame\ZoneManager\include\DGlobalGame.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2007/11/15  16:10
** ��  ��:	1.0
** ��  ��:	��Ϸ��ȫ�ֱض���
** Ӧ  ��:  ���������ͻ���
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#pragma pack(1)

//////////////////////// ȫ�ֺ� //////////////////////////////////
// ��Чuid
#define INVALID_UID							0

// ��Ч��ͼid
#define INVALID_MAPID						0

// ��Ч����id
#define INVALID_ZONEID						0

// ��Ч�Ľ�ɫDBID
#define INVALID_PDBID						0

// ��Ч���û�DBID
#define INVALID_UDBID						0

// ��Ч��UID SerialNo
#define INVALID_UIDSERIALNO					0

// ��Ч�ľ��룬�϶������˲�����Χ
#define INVALID_DISTANCE					0x7FFFFFFF

// ��Ч��BUFF ID
#define INVALID_BUFF_ID						0

// ��Ч��Ч��ID
#define INVALID_EFFECT_ID					0

// ��Ч��������Ʒ��ID
#define INVALID_SKEP_ID						0

// ��Ч��ӪID
#define INVALID_CAMP_ID						0

// ��Ч��Ӫ�Ķ�ID
#define INVALID_CAMP_TEAMID					0

// ��Ч����ID
#define INVALID_FAMILY_ID					0

// ��Ч�ID
#define INVALID_AMUSEMENT_ID				0

// ����ͼ��
#define MAP_MAXCOUNT						256

// ������ֳ���
#define MAX_PERSONNAME_LEN					(16 + 1)

// װ��������ȼ�����װΪ0����ʣ�»��оŵ��ɾ�����
#define EQUIPMENT_SMELT_MAXLEVEL			10

// �����ƶ��ٶ����ȼ���0 ~ 9����������ˣ�
#define CREATURE_MOVESPEED_MAXLEVEL			10

//������Բ���pk����С�ȼ�
#define  PK_LEVEL_LIMIT						30

// �������ȼ�
#define PERSON_MAX_LEVEL					120

// ʵ����Ч��������
#define ENTITYCOMMUNICATE_VALIDDISTANCE		7

// װ������฽�����Ը���
#define EQUIPMENT_EFFECT_MAXCOUNT			16

// ����������a�ϴ�С
#define PERSON_PACKET_DEFAULTSIZE			99

//����������a�ϴ�С(����������λ��
#define PERSON_PACKET_NONBAG_DEFAULTSIZE    96

//���ҵ����ߴ�
#define  PERSON_PACKET_BAG_MAXCAPACITY		24

//���������δ��������Ĭ�ϴ�С
#define PERSON_PACKET_NONBAGBLOCK_DEFAULTSIZE  32

//����ֿ���δ��������Ĭ�ϴ�С
#define PERSON_LIB_NONBAGBLOCK_DEFAULTSIZE  24

// �̵���Ʒ���a�ϴ�С
#define SHOPMALL_SKEP_DEFAULTSIZE			60

// ����ع���Ʒ���a�ϴ�С
#define PERSON_SHOP_SKEP_DEFAULTSIZE		24

// ����ֿ�����Ĭ�ϴ�С
#define PERSON_WAREHOUSE_DEFAULTSIZE		99

// �����������Ĭ�ϴ�С
#define PERSON_PETLIST_DEFAULTSIZE			24

// �����б��Ĭ�ϴ�С
#define PET_LORD_PACK_DEFAULTSIZE			12

// ��������Ĭ�ϴ�С zgz
#define PET_RIDE_PACK_DEFAULTSIZE			12

// �����Զ��ͷż��ܲ۵Ĵ�С
#define PET_ATUO_SKILL_DEFAULTSIZE          4

// װ���������Ĵ�С
#define PERSON_EQUIPSMELTSOUL_SKEPSIZE		5 // modify by zjp��ֻ��5����

// װ����ʯ��Ƕ���Ĵ�С
#define PERSON_EQUIPEMBEDGEMS_SKEPSIZE		15

// modify by zjp�����ڵĲ߻��ĵ�����������ֻ��Ҫ3��slot
// װ���������Ĵ�С
#define PERSON_EQUIPREBUILD_SKEPSIZE		3
//by ldy �ڵ��ϳ���Ҫ16��slot
#define PERSON_COMPOSE_SKEPSIZE				16
//by ldy, �꽫ʥ����Ҫ17��slot
#define SOUL_INTENSIFY_SKEPSIZE				17
//by ldy �����������ںϳɵ���ߵȼ�
#define MAX_PILL_COMPOSE_LEVEL				13
//by ldy,�꽫ǿ�������ʥ������					
#define MAX_PETINTENSIFY_SANCTIFY			16
//by ldy,�꽫����ʥ���Ǽ�
#define MAX_PET_START						40

// ����Ȩ�ޱ���ʱ��
#define BOX_POPEDOMPROTECT_TIME				(1 * 1000 * 30)

// ������������
#define BOX_LIFECYCLE_TIME					(1 * 1000 * 60)

// ���Ӵ�ͣ��ʱ�䣬����ǿ�ƹر�
#define BOX_OPENSETTLE_TIME					(20 * 1000)

// װ���;ö��ٵ�һ��
#define EQUIPMENT_ENDURE_POINT2RANK			256

// �������ݳ���
#define UIDATA_LEN							140


//�ֿ�������󳤶�
#define MAX_WAREHOUSEPASSWORD_LEN			16

//�ֿ��뱳����Ǯ����
#define MAX_PERSON_MONEY					(20 * 10000 * 10000)			

// �����Ա������
#define TEAM_MEMBER_MAXCOUNT				5

// ��Ч�Ķ���ID
#define INVALID_TEAM_ID						0

// BuffЧ���Ѿ����ӵ�������
#define MAX_BUFF_OVERLAY_TIMES				100

// �Ŵ���ʱ�(��ֱ�)
#define TENTHOUSAND_MULTIPLE		        10000.00

// �Ŵ���ʱ�(�ٷֱ�)
#define HUNDRED_MULTIPLE		            100.00

//װ����Ƕ�ı�ʯ���������
#define EQUIP_EMBED_GEMS_MAX_NUM			4 //��DBDEF_MAX_EQUIP_EMBEDGEMSҪ���������

//��Ʒ����������Ե��������
#define	EQUIP_SMELT_SOUL_ATTRIB_MAX_NUM		5//��DBDEF_MAX_EQUIP_SMELTSOULATTRIBҪ���������

//װ�������ӵ�еĻ���Ʒ������
#define EQUIP_BASE_ATTRIB_MAX_NUM			4//��DBDEF_MAX_EQUIP_BASEBRANDATTRIBҪ���������

//װ�����ֵ���������
#define EQUIP_LETTERING_MAX_NUM				71//��DBDEF_MAX_EQUIP_LETTERINGҪ���������

//װ��������ͼ۸�
#define EQUIP_REPAIR_MIN_PRICE				1

//װ�������ļ۸�
#define EQUIP_IDENTIFY_PRICE				0.1f

// ͨ��װ�����Ĵ�С
#define COM_EQUIPSKEP_SIZE                  11

// �������ǩ���ĳ���
#define ACTOR_SIGNATURE_MAX_LEN				71

// ����ս����������
#define  PET_TYPEPROP_MAX					7

// �ɼ�������
#define  COLLECT_MAX_DISTANCE               2

#define STALL_LEAVEWORD_MSG_LEN					61 // ����������󳤶�

// �������ʹ��
#define  PETRIDE_UNLIMITEDLY				-1

// ����������󳤶�
const int FAMILY_NAME_LEN = 16;

// ����������󳤶�
const int ARMY_NAME_LEN = 16;

// �����̳���ʷ�����¼��
#define ONLINE_SHOP_MAX_HISTORY_PAID_RECORDS 10

// ϴ�츳��Ҫ����Ʒ(ϴ�赤) add wangtao
const int C_RESET_GENIUS_GOOD = 4004;

// ������Ӫ��Ҫ�����ɫ10��
const int C_JOIN_CAMP_NEED_PERSON_LV = 10;

// petdata���츳���ʣ�������󳤶�,���±�Ϊ�츳ID��ż�±�Ϊ�츳���ֵĸ���
const int C_PET_GENIUS_SIZE = 20;
////////////////////////// UID ////////////////////////////////////
typedef LONGLONG UID;
struct ___UID
{
	DWORD dwSerialNo;						// ���кţ������棬��ͨ����IDҲ���Ա�ʶ����
	DWORD dwHandle;							// �����������ظ���
};

// �ֽ�����к�
#define ANALYZEUID_SERIALNO(uid)			(((___UID *)&uid)->dwSerialNo)

// �ֽ�����
#define ANALYZEUID_HANDLE(uid)				(((___UID *)&uid)->dwHandle)

/////////////////////// ʵ�� //////////////////////////////////
// ʵ������
enum
{
	/*
					  00000000 00000001		// ���� ��1��
					  00000000 00000010		// ���� ��2��
					  00000000 00000011		// װ�� ��3��
					  00000000 00000100		// ��װ������Ʒ ��4��
					  00000000 00000101		// ���� ��5��
					  00000000 00000110		// ��� ��6��

					1 00000000 00000000		// �Ƿ�Ϊ����
				   10 00000000 00000000		// �Ƿ�Ϊ��Ʒ
	11111111 11111111 11111111 11111111		// .....	
	//*/

	tEntity_Class_Person = 0x0001,			// ����
	tEntity_Class_Monster = 0x0002,			// ����	
	tEntity_Class_Pet = 0x0003,				// ����
	tEntity_Class_Equipment = 0x0004,		// װ��
	tEntity_Class_NonequipableGoods = 0x00005,		// ��װ������Ʒ
	tEntity_Class_Box = 0x00006,			// ����
	tEntity_Class_Mast = 0x00007,			// ��� ��̯λ��������... ...��
	tEntity_Class_Bubble = 0x00008,			// ���� add by zjp

	// -- �������ⲿ�����õ��ģ�����ͨ���ӿ�ʵ�� ----
	tEntity_IsClass_Creature = 0x10000,		// �Ƿ�Ϊ����
	tEntity_IsClass_Goods = 0x20000,		// �Ƿ�Ϊ��Ʒ
};

////////////////////////�㲥��������///////////////////////////////
// �㲥�������ͣ�����IGameZone::BroadcastMessage
enum
{
	/*
					  00000000 00000001		// �㲥������
					  00000000 00000010		// �㲥������
					  00000000 00000100		// �㲥������
					  00000000 00001000		// �㲥������
	11111111 11111111 11111111 11111111		// .....	
	//*/
	tBroadcast_Entity_Person = 0x0001,		// �㲥������
	tBroadcast_Entity_Monster = 0x0002,		// �㲥������
	tBroadcast_Entity_Pet	= 0x0004,		// �㲥������
	tBroadcast_Entity_Other = 0x0008,		// �㲥������
};

////////////////////////��������ͬ����ʽ////////////////////////////
// ��������ͬ����ʽ
enum
{
	/*
					00000000 00000001		// ͬ����������
					00000000 00000010		// ͬ��˽�����ԣ�ֻ�����ѿͻ��ˣ�
					00000000 00000011		// ͬ���㲥����
	11111111 11111111 11111111 11111111		// .....	
	//*/ // ͬ�������ѿͻ��ˣ�ֻ֧���������û�����ѿͻ���
	tCreature_SyncProp_Single = 0x0001,		// ͬ���������ԣ�����ǹ㲥���ԣ����㲥�������˽�����ԣ���ͬ�������ѿͻ��ˣ�
	tCreature_SyncProp_Private = 0x0002,	// ͬ��˽�����ԣ�ֻ������֧�֣�
	tCreature_SyncProp_Broadcast = 0x0003,	// ͬ���㲥���ԣ�ֻ������֧�֣�
};

////////////////////////////��Ʒװ���󶨷�ʽ////////////////////////
// add by zjp
enum
{
	eBind_NOT_BIND,					// ����
	eBind_GET_BIND,					// ��ȡ��
	eBind_EQUIP_BIND,				// װ����
};

/////////////////////////// ��Ʒ�󶨱�־λ /////////////////////////
enum
{
	/*
					  00000000 00000001		// �Ƿ���ȡ�󶨣�
					  00000000 00000010		// �����Ƿ����䣿
					  00000000 00000100		// �Ƿ���������
					  00000000 00001000		// �Ƿ��������٣�
					  00000000 00010000		// �Ƿ�������۸�NPC��
					  00000000 00100000		// �Ƿ�����Ÿ��˲ֿ⣿
					  00000000 01000000		// �Ƿ����������ֿ⣿
	11111111 11111111 11111111 11111111		// .....	
	//*/
	tGoods_BindFlag_Hold = 0x001,			// �Ƿ��Ѿ���
	tGoods_BindFlag_Trade = 0x002,			// �ɷ���
	tGoods_BindFlag_Stall =  0x004,			// �ɷ��̯����
	tGoods_BindFlag_Throw = 0x008,			// �Ƿ�������
	tGoods_BindFlag_Auction = 0x010,		// �ɷ�����
	tGoods_BindFlag_Mail = 0x020,			// �ɷ��ʼ�
	tGoods_BindFlag_DieDrop = 0x040,		// �ɷ�����
	tGoods_BindFlag_SaleToNPC = 0x080,		// �Ƿ�������۸�NPC��
	tGoods_BindFlag_Smelt = 0x100,			// �ɷ�������
	tGoods_BindFlag_Split = 0x200,			// �ɷ���
	tGoods_BindFlag_WareHouse = 0x400,		// �Ƿ�����Ųֿ⣿
	tGoods_BindFlag_Destroy = 0x800,		// �Ƿ������������٣�by cjl
};

//by cjl
enum
{
	tChangeBody_BindFlag_Pet	 = 0x001, //�Ƿ��Я������
	tChangeBody_BindFlag_Buffer  = 0x002, //�Ƿ�Я��buffer
	tChangeBody_BindFlag_Common  = 0x004, //�Ƿ���ͨ����
	tChangeBody_BindFlag_XP		 = 0x008, //�Ƿ��ܷ�XP
};
//end cjl

// add by zjp����״̬��Ӧ���Լ�(ֻ������״̬�����Ҳ߻�Ҫ��ÿ��״̬��Ӧ��������ͬ)
enum 
{
	eBind_Attribute =   tGoods_BindFlag_Hold+
						tGoods_BindFlag_SaleToNPC+
						tGoods_BindFlag_Smelt+
						tGoods_BindFlag_Split+
						tGoods_BindFlag_Throw+		//by cjl
						tGoods_BindFlag_WareHouse,

	eNoBind_Attribute =   tGoods_BindFlag_Trade+
						  tGoods_BindFlag_Stall+
						  tGoods_BindFlag_Throw+
						  tGoods_BindFlag_Auction+
						  tGoods_BindFlag_Mail+
						  tGoods_BindFlag_DieDrop+
						  tGoods_BindFlag_SaleToNPC+
						  tGoods_BindFlag_Smelt+
						  tGoods_BindFlag_Split+
						  tGoods_BindFlag_WareHouse,
};

//////////////////////// ��ң֣ɣ�Ȩ�� //////////////////////////
enum
{
	tVIP_Popedom_Kickout = 0x001,			// ����
	tVIP_Popedom_Estop = 0x002,				// ����
	tVIP_Popedom_Forbid_Login = 0x004,		// ��ֹ��¼
	tVIP_Popedom_Through = 0x008,			// ���㴫��
	tVIP_Popedom_Call_In = 0x010,			// ����
	tVIP_Popedom_Transmission = 0x020,		// ����ָ����ɫ���
	tVIP_Popedom_Hide = 0x040,				// ����
	tVIP_Popedom_First_Login = 0x080,		// ���ȵ�¼
	tVIP_Popedom_Free_Through = 0x100,		// ��Ѵ���
	tVIP_Popedom_Free_WorldChat = 0x200,	// ���緢�Բ���ҪǮ
	tVIP_Popedom_Special_Channel = 0x400,	// ����Ƶ������
	tVIP_Popedom_Consult_TaskData = 0x800,	// ��ѯ��������
	tVIP_Popedom_Change_TaskData = 0x1000,	// �޸Ľ�������ֵ
	tVIP_Popedom_Consult_SvrState = 0x2000,	// ��ѯ��ǰ������״��
};

///////////////////////////// ��·ѡ�� //////////////////////////
enum
{
	FINDPATH_OPTION_EMPTY      =0x00,		// ������·
	FINDPATH_OPTION_OPTIMIZE   =0x01,		// �Ż�·��
	FINDPATH_OPTION_NEAREST    =0x02,		// ������������յ����ƶ�������ĵ�	
};

////////////////////////////// ������ //////////////////////////
enum
{
	tLingHun_State_Ming = 0x00,				// ����̬
	tLingHun_State_Di,						// �ػ�̬
	tLingHun_State_Tian,					// ���̬
	tLingHun_State_Max,						// ���
};

enum
{
	EN_BUFF_MAX_OVERLAY    =  100,          // BUFF���������Ӵ���
	EN_BUFF_MAX_COEXIST    =  100,          // BUFF������󲢴����
};

enum
{
	tPet_State_Fighting = 0x001,		// �����Ƿ������			
	tPet_State_Riding = 0x002,			// �����Ƿ���ˣ�
	tPet_State_Combining = 0x004,		// �����Ƿ���壿
	tPet_State_InterimCallBack = 0x008, // �����Ƿ���ʱ�ٻأ�
};

#pragma pack()