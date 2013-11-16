//==========================================================================
/**
* @file	  : EntityDef.h
* @author : 
* created : 2008-1-21   9:58
* purpose : ʵ����ض���
*/
//==========================================================================

#ifndef __ENTITYDEF_H__
#define __ENTITYDEF_H__

#include "DGlobalGame.h"	// for UID typedef


/// ʵ������
enum EntityType
{
	typeUnknow = 0,		/// δ֪ʵ��
	typeStatic,			/// ��̬ʵ��
	typeCage,			/// ���ӣ����ڱ༭���Ź֣�
	typeWaypoint,		/// ·�㣨���ڱ༭����
	typeSpile,			/// 

	typePerson,			///����
	typePet,			///����
	typeMonster,		///����
	typeEffect,			/// ��Ч
	typeBox,			/// ����
	typeBubble,			/// ���� add by zjp

	typeMaxCount,
};


/// ʵ�������ȼ�
enum SortLevel
{
	lvlNoSort			= 0,		/// ����������
	lvlSpecificBlock	= 2,		/// �����
	lvlLowest			= 10,		/// ��͵ȼ�
	lvlMidle			= 100,		/// �м�ȼ�
	lvlHight			= 1000,		/// �ߵȼ�
	lvlHighest			= 10000		/// ��ߵȼ�
};


/// ʵ���־
enum EntityFlags
{
	// FlagVisible������view����ʾ�б��У�������ʾ��view�ɼ���FlagInScreenһ��ͱ�ʾ��View�ɼ�
	flagVisible		= 0x1,			/// �ɼ�������ʾ�б��У�
	flagSelectable	= 0x2,			/// ��ѡ��
	flagSelected	= 0x4,			/// ��ѡ��
	flagSelectedForMapEdit	= 0x8,	/// ��ѡ�У����ڵ�ͼ�༭����
	flagHighlight	= 0x10,			/// �Ƿ����
	flag2D			= 0x20,			/// 2D����
	flag3D			= 0x40,			/// 3D����
	flagDrawName	= 0x100,		/// ����ʵ������
	flagDrawResId	= 0x200,		/// ����ʵ����ԴId
	flagDrawHP		= 0x400,		/// ����ʵ��HP
	flagDrawMP		= 0x800,		/// ����ʵ��MP
	flagInScreen	= 0x1000,		/// ��ʶ�����Ƿ�����Ļ��Χ֮��
	flagInMap		= 0x2000,		/// ��ʶ�����Ƿ��ڵ�ͼ��
	flagFade		= 0x4000,		/// �Ƿ�֧�ֵ��뵭������         
	flagNoLogic		= 0x8000,		/// �Ƿ��Ƿ��߼�����
	flagDie         = 0x10000,      /// �Ƿ�����������(wan)
	flagDrawTitle	= 0x20000,		/// �ƺ�
	flagDrawTextGroup	= 0x40000,		/// ������
	flagDrawTeam		= 0x80000,		/// С������
	flagDrawFinishTaskEffect = 0x100000,        /// ��Ч��ʶ
	flagDrawAutoMoveEffect = 0x200000,         /// �Զ�Ѱ·��Ч��ʶ
	flagDrawFinishAutoMoveEffect = 0x400000,   /// �Զ�Ѱ·������ʶ
	flagDrawTaskIcon  = 0x800000,            /// ����ͼ��
	flagDrawBoxMouseMove = 0x1000000,		/// �����ͣ���Ʊ�����
	flagMapItem          = 0x2000000,		/// ��ͼ���
	flagUnRender		 = 0x4000000,		/// flagVisible�޷�����ʵ���Ƿ���Ⱦ�������������flag
	flagUnRenderShadow	 = 0x8000000,		/// �Ƿ������Ӱ
	flagGlobalSceneMagic = 0x10000000,		/// �Ƿ�ȫ��������Ч
	flagFallMagic		 = 0x20000000,		/// �Ƿ��������Ч�����磺�ꡢѩ

	///zgz �����ͷţ������ӳٴ���ԭ��ԭ�ȵ�ͼ�ϵ�ʵ�����л���ͼʱû����ȷ�ͷŵ����������Ӵ˱�־ʹ�������ͷű����ڴ�й¶
	/// �����ô˱�־! �������������Ҫ�����ͷţ���ȷ��ʵ��ָ���Ѵӳ�������������ɾ�����ͻ��˱�����
	flagReleaseImmediate = 0x40000000,		

	flagDrawStall        = 0x80000000,      /// ̯λ��ʶ	
};

#if 0  //лѧ��ע�ͣ�20090923

/// ʵ�岿��
enum EntityParts
{
	EntityPart_Body,		/// ���ɣ����壬���壬����(������һ��ֻ�����ɣ����������ӣ�������Ʒ)

	// �����ʺϽ�ɫ�͹���
	EntityPart_Armet,		/// ͷ����ñ�ӣ���
	EntityPart_Jacket,		/// ���£��пˣ����£�����
	EntityPart_Pants,		/// ���ӣ��̿�
	EntityPart_Shoes,		/// Ь�ӣ���
	EntityPart_Manteau,		/// ���磬���������
	EntityPart_RWeapon,		/// �����������絶����(��ɫ���������ϸ�����)

	// �����ʺϹ���
	EntityPart_Sash,		/// ���磬���
	EntityPart_Girdle,		/// ����
	EntityPart_Cuff,		/// ���󣬻��֣�����
	EntityPart_Tail,		/// β��
	EntityPart_LRWeapon,	/// ˫����������˫�ִ���˫��ì������˫�ֵ�
	EntityPart_LWeapon,		/// �������������

	// ����
	EntityPart_Reserve1,	/// ����1��������������������������ʱ���������ﲻ���������ⲿ����ʹ�ô������ͬ
	EntityPart_Reserve2,	/// ����2
	EntityPart_Reserve3,	/// ����3

	// ����Ҫ�����ܻ��ҽӵ㣬�ŵ׹�Ч�㣬ͷ����Ч�㣬�м价�ƹ�Ч��

	EntityPart_Max,
};
#endif


/// ʵ������
enum EntityCommand
{
	// �����
	EntityCommand_SetPart,			///���ò�������װ (ulong part, ulong resId)�����resIdΪ0��ʾ����ȡ�²���
	EntityCommand_GetPart,			///��ȡ����,��ȡ��װ����(ulong part,SEventPersonPerform_C* pContext)
	EntityCommand_SetPartScale,		///���ò��������ű�����ֻ��ģ����Ч (ulong part, float scale)
	EntityCommand_SetPartColor,		///���ò�������ɫ (ulong part, const ColorValue* color)
	EntityCommand_ShowPart,			////�����Ƿ���ʾװ��(ulong part, ulong show)
	EntityCommand_GetPartShow,		///��ȡ�Ƿ���ʾװ��(ulong part, uchar * pShow)

	EntityCommand_PartDeformation,//װ����������
	EntityCommand_PartAttachEffect,//װ��������Ч

	EntityCommand_AttachMagic,		/// ��ʵ��(��Ҫָ����)������һ����Ч (const MagicView* magic, 0)
    //  ����һ����ʵ����صĹ�Ч��ע�⣺�����Ч��û��������ʵ���ϣ�
    EntityCommand_AddMagic,
	EntityCommand_DetachMagic,		/// ȡ��ʵ��(��Ҫָ����)����ָ���Ĺ�Ч (ulong id, int loops)
    //  �Ƴ�һ����ʵ����صĹ�Ч��ע�⣺�����Ч��û��������ʵ���ϣ�
    EntityCommand_RemoveMagic,
	EntityCommand_ClearMagic,		/// ���ʵ�����ϵ����й�Ч(һ�㷢����ʵ������ʱ) (0, 0)
	EntityCommand_AddModifier,		/// ����޸��� (const Modifier* modifier, 0)
	EntityCommand_RemoveModifiers,	/// �Ƴ��޸��� (ulong key, 0)

	// ������
	EntityCommand_ForceStop,		/// add by zjpǿ��ֹͣվ����ֹͣ��������
	EntityCommand_Stand,			/// վ�� (const xs::Point* tile=0, 0)
	EntityCommand_Fallow,			/// ���� (ulong fallowId, 0)
	EntityCommand_Move,				/// �ƶ��������������߻��Ǳ��� (const xs::Point* pathList, size_t count)
	EntityCommand_RapidMoveStart,	/// �����ƶ�(˲�ơ����)��ʼ (ShadowManager* mgr, 0)
	EntityCommand_RapidMoveEnd,		/// �����ƶ�(˲�ơ����)����
	EntityCommand_AttackReady,		/// ����׼�� (const AttackContext* context, 0)
	EntityCommand_Attack,			/// ������ (const AttackContext* context, 0)
	//EntityCommand_SpellReady,		/// ����׼���������� (ulong actionId, 0)
	//EntityCommand_Spell,			/// ʩ�� (ulong actionId, 0)
	EntityCommand_Wound,			/// �ܻ� (0, 0)
	EntityCommand_Death,			/// ���� (0, 0)
	EntityCommand_Stun,				/// ѣ�� (0, 0)
	EntityCommand_Sitdown,			/// ���� (0, 0)
	EntityCommand_Siting,			/// �� (0, 0)
	EntityCommand_GetSitState,      /// ��ȡ����״̬
	EntityCommand_Collect,			/// �ɼ� (0, 0)
	EntityCommand_ShowRibbon,       /// �Ƿ���ʾ����Ʈ��
	EntityCommand_SetMount,			/// ������£��� (ulong mount, ulong actionIndex) mountΪ1������Ϊ0������,actionIndexΪʹ�õڼ��׶�������0Ϊ����
	EntityCommand_GetMount,			/// ��ȡ�Ƿ���������̬ (ulong* mount, 0) mountΪ1�������ϣ�Ϊ0��û������
	EntityCommand_SetDefaultSpeed,  /// ����Ĭ���ٶȣ��ܲ�����·��     
	EntityCommand_SetMoveStyle,		/// �����ƶ����� (ulong style, 0) styleΪ0�����ߣ�Ϊ1������
	EntityCommand_GetMoveStyle,		/// ��ȡ�ƶ����� (ulong* style, 0) styleΪ0�����ߣ�Ϊ1������
	EntityCommand_Relive,			/// ʵ�帴�� (0, 0)
	EntityCommand_IsMoving,			/// ʵ���Ƿ������ƶ� (bool* isMoving, 0)
	EntityCommand_ChangeModel,		/// ��ģ��


	// ��ģ�Ϳ���
	EntityCommand_SetScale,			/// ������ģ�͵����ű���(Ĭ��Ϊ1) (const float* scale, 0) �ڶ�������Ϊ0��ʾ����Ե�ǰ���űȽ������ţ�Ϊ1��ʾ��Ե�ǰ���űȽ�������
	EntityCommand_GetScale,			/// ��ȡ��ģ�͵����ű��� (float* scale, 0)
	EntityCommand_SetMoveSpeed,		/// ������ģ�͵��ƶ��ٶ� (ulong tileMoveTime, 0)��������ƶ��ٶ����ƶ����ζ�Ӧ������Tile���ĵ���ƶ�ʱ�䣨���룩
	EntityCommand_GetMoveSpeed,		/// ��ȡ��ģ�͵��ƶ��ٶ� (ulong* tileMoveTime, 0)
	//EntityCommand_SetAniSpeed,		/// ������ģ�Ͷ������ٶ�(Ĭ��Ϊ1) (const float* speed, 0)
	//EntityCommand_GetAniSpeed,		/// ��ȡ��ģ�Ͷ������ٶ� (float* speed, 0)
	EntityCommand_SetColor,			/// ������ģ�͵���ɫ (const ColorValue* color, 0)
	EntityCommand_GetColor,			/// ��ȡ��ģ�͵���ɫ (ColorValue* color, 0)

	// Topmost��
	EntityCommand_SetName,			/// �������� (const char* name, size_t len)
	EntityCommand_GetName,			/// ��ȡ���� (std::string* name, 0)
	EntityCommand_SetNameColor,		/// �������Ƶ���ɫ (const ColorValue* color, 0)
	EntityCommand_GetNameColor,		/// ��ȡ���Ƶ���ɫ (ColorValue* color, 0)
	EntityCommand_SetHPInfo,		/// ����HP��Ϣ (ulong cur, ulong max)
	EntityCommand_SetMPInfo,		/// ����MP��Ϣ (ulong cur, ulong max)
	EntityCommand_SetSpInfo,		/// ����SP������Ϣ(ulong cur, ulong max)
	EntityCommand_ChangeLayout,		/// �ı�topmost��Ϣ�е���ʾ�Ͳ���ʾ�ı�ʶ(ulong hideFlags, ulong showFlags)���ο�TopmostFlagsö��
	EntityCommand_SetTitle,			/// ���óƺ�
	EntityCommand_AddGroupText,		/// ���������ʾ��
	EntityCommand_ClearGroupText,	/// ���������ʾ��

    //  ���������ǣ�
    EntityCommand_SetTaskSign,

	// ��Ч��
	EntityCommand_MoveRadial,		/// �����ƶ������ڹ�Ч (const xs::Point* ptBegin, const xs::Point* ptEnd)
	EntityCommand_MoveTrack,		/// �ƶ������٣����ڹ�Ч������� (IEntity* source, IEntity* target)
	EntityCommand_Jump,				/// ��Ծ
	EntityCommand_NextMovingTile,
	EntityCommand_GetAnimationTime, //  ��ȡʵ��Ķ���ʱ��
	EntityCommand_GetJumpTime,		//  ��ȡʵ���λ��ʱ��
	EntityCommand_UseBigTexture,
	EntityCommand_GetBoneSpace,		// add by zjp;��ȡ������space���� 
	EntityCommand_Max,
};

// ��
enum EN_SIT
{
	EN_SIT_NONE = 0,                // û������
	EN_SIT_ACTION,                  // ������
	EN_SIT_DONE,                    // ������
};

/// ħ�����������
enum MagicType
{
	MagicType_General,		/// ͨ��ħ��
	MagicType_MoveRadial,	/// �����ƶ�ħ��
	MagicType_MoveTrack,	/// ����ħ��
};

/// ��Ч����������
enum EffectType
{
	EffectType_General,		/// ͨ�ö���Ч��
	EffectType_Fly,			/// �����ද��Ч����׷����Ч��
	EffectType_LifeTime,	/// �������ද��Ч���������ʱû�õ���
	EffectType_MultiTimes,	/// ����ද��Ч���������ʱû�õ���
	EffectType_Area,		/// �����ද��Ч�������編ʦȫ�����ף�
	EffectType_MultiDir,	/// �෽���ද��Ч���������ʱû�õ���
	EffectType_RapidMove,	/// ˲���ද��Ч���������棩
	EffectType_DestRapidMove,	/// Ŀ��˲���ද��Ч����������������
	EffectType_SrcDestRapidMove, /// Դ��Ŀ��˲���ද��Ч�������絹תǬ����
	EffectType_Jump,		//��Ծ�ද��Ч�� add by yhc
};



#pragma pack(push)
#pragma pack(1)
/// ��������������
struct AttackContext
{
	ulong actionId;			/// ����Id
	ulong loops;			/// ����ѭ������
    //  �����ٶȣ�
    float fAnimateSpeed;
	bool  isSpellAttack;	/// �Ƿ��Ƿ�������
};

/// ��������Ч����������
struct SkillEffectContext
{
	ulong			id;				/// Ч��Id
	handle			src;			/// ����Ч��������
	handle			target;			/// ����Ч�������ߣ�����Ϊ NULL
    xs::Point			ptCenter;		/// ����Ч�����ĵ�(ʩ��λ��)������˲����Ч������ָ˲��Ŀ��˲�ƺ󵽴��λ�ã�
	xs::Point			ptTarget;		/// Ŀ���
	int				loops;			/// ��Чѭ������
    //  ��¼��Ч�ĳ���ʱ�䣻
    int nDuration;
	bool			isSpellSkill;	/// �Ƿ��Ƿ�������
	int				selectType;		/// ����ѡ������(0-��ѡ�� 1-ѡ��ʵ�� 2-ѡ��Tile)
};

/// ����ȫ������Ч��������
struct SceneMagicContext
{
	ulong magicID;
	int   nFade;
	int   nFall;
};

// ��ѯ����ʱ���������
struct RequestAnimationContext
{
	ulong		    id;
	handle			src;
};

#pragma pack(pop)

//ģ����ģ������
enum ModelSubMeshForChangePart
{
	MSFCP_BODY = 0,
	MSFCP_FACE = 1,
	MSFCP_HAIR = 2,
	MSFCP_MAX = 3,
};

//����ӳ����Ҫ��������

//���ӻ������״̬�����ڶ�������
enum EVisualComponentState 
{
	EVCS_OnPeace=0,//��ս��״̬
	EVCS_OnFight,//ս��״̬
	EVCS_Max,//
};

//����ӳ��������
struct ActionMapContext
{
	EVisualComponentState state;//״̬
	uchar weapon;//��������,��ӦEWeaponClass
	bool iscreature;//�Ƿ�����
	bool ismount;//�Ƿ����
};

// ͷ������
struct TextLine
{
	DWORD	   txFont;				// ����		
	ColorValue txColor;				// ������ɫ
	autostring txStr;				// ��������
	std::string     txPicture;		// ͼƬ
	DWORD	   txEffectID;			// ��ЧID

	TextLine():txFont(0),txEffectID(0){}
};

// ����Ʈ��
enum EShowRibbon
{
	EShowRibbon_Stop,   // ֹͣ��������Ʈ��
	EShowRibbon_Start,   // ��ʼ��������Ʈ��
};
#endif // __ENTITYDEF_H__