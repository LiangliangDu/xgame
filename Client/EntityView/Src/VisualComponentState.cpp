#include "StdAfx.h"
#include "VisualComponentState.h"
#include "VisualComponentMZ.h"

////////////////////CVisualComponentState////////////////////////////////

bool CVisualComponentStateMgr::s_bInitMapCommandToState = false;//�Ƿ��ʼ����
CVisualComponentStateMgr::CommandToStateMap * CVisualComponentStateMgr::s_pMapCommandToState = 0;//ʵ�����״̬��ӳ��

void CVisualComponentState::OnEnter()
{

}

void CVisualComponentState::OnLeave()
{

}

void CVisualComponentState::SetState( EVisualComponentState state )
{
	m_eState = state;
}


//////////////////////////////////CVisualComponentStateMgr//////////////////////////

const DWORD CVisualComponentStateMgr::s_fight2PeaceInterval = 8 * 1000; // modify by zjp���߻�Ҫ��8���е�ս��״̬����ʱ��

CVisualComponentStateMgr::CVisualComponentStateMgr()
{
	m_StateSet[EVCS_OnPeace].SetState(EVCS_OnPeace);
	m_StateSet[EVCS_OnFight].SetState(EVCS_OnFight);
	m_CurState = EVCS_OnPeace;
	m_nCurCommand = EntityCommand_Max;
}

bool CVisualComponentStateMgr::Create(VisualComponentMZ * pComp)
{
	if( !pComp) return false;
	m_pMaster = pComp;
	return true;
}

CVisualComponentStateMgr::~CVisualComponentStateMgr()
{
	gGlobalClient->getTimerAxis()->KillTimer(0,this);
	m_nCurCommand = EntityCommand_Max;
}

void CVisualComponentStateMgr::OnTimer(unsigned long dwTimerID)
{
	if (m_nCurCommand==EntityCommand_AttackReady)
	{
		gGlobalClient->getTimerAxis()->KillTimer(0,this);
		gGlobalClient->getTimerAxis()->SetTimer(0, s_fight2PeaceInterval,this,1);		
		return;
	}
	if( m_CurState ==EVCS_OnFight) 
	{
		m_StateSet[EVCS_OnFight].OnLeave();
		m_CurState = EVCS_OnPeace;
		m_StateSet[EVCS_OnPeace].OnLeave();
		if( !m_pMaster) return;
		int actionid = m_pMaster->getCurrentAction();

		if (actionid == EntityAction_Death)
			return;
		
		//���Զ���ͬ��
		if( actionid == EntityAction_Walk  || actionid == EntityAction_Run ) 
			m_pMaster->handleCommand(EntityCommand_Move,1,0);
		else
			m_pMaster->handleCommand(EntityCommand_Stand,1,0);
	}
}

void CVisualComponentStateMgr::initCommandToStateMap()
{
	CommandToStateMap* pMap = new CommandToStateMap();

	(*pMap)[EntityCommand_RapidMoveStart] = EVCS_OnFight;	/// �����ƶ�(˲�ơ����)��ʼ (ShadowManager* mgr, 0)
	(*pMap)[EntityCommand_RapidMoveEnd] = EVCS_OnFight;		/// �����ƶ�(˲�ơ����)����
	(*pMap)[EntityCommand_AttackReady] = EVCS_OnFight;		/// ����׼�� (const AttackContext* context, 0)
	(*pMap)[EntityCommand_Attack] = EVCS_OnFight;			/// ������ (const AttackContext* context, 0)
	(*pMap)[EntityCommand_Wound] = EVCS_OnFight;			/// �ܻ� (0, 0)
	(*pMap)[EntityCommand_Death] = EVCS_OnFight;			/// ���� (0, 0)
	(*pMap)[EntityCommand_Stun] = EVCS_OnFight;				/// ѣ�� (0, 0)	

	(*pMap)[EntityCommand_Sitdown] = EVCS_OnPeace;			// ���� (0, 0)
	(*pMap)[EntityCommand_Siting] = EVCS_OnPeace;			/// �� (0, 0)
	(*pMap)[EntityCommand_Collect] = EVCS_OnPeace;			/// �ɼ� (0, 0)
	(*pMap)[EntityCommand_Relive] = EVCS_OnPeace;		/// ʵ�帴�� (0, 0)


	s_pMapCommandToState = pMap;
	s_bInitMapCommandToState = true;
}

//EVisualComponentState CVisualComponentStateMgr::MapCommandToState(EntityCommand cmd)
//{
//	static EVisualComponentState s_CommandToState[EntityCommand_Max] = 
//	{
//		//// �����
//		EVCS_Max,			//EntityCommand_SetPart,			/// ���ò�������װ (ulong part, ulong resId)�����resIdΪ0��ʾ����ȡ�²���
//		EVCS_Max,			//EntityCommand_SetPartScale,		/// ���ò��������ű�����ֻ��ģ����Ч (ulong part, float scale)
//		EVCS_Max,			//EntityCommand_SetPartColor,		/// ���ò�������ɫ (ulong part, const ColorValue* color)
//
//		//
//		EVCS_Max,			//EntityCommand_ShowPart,	////added by xxh 20090923, ���ڿ����Ƿ���ʾװ��
//
//		EVCS_Max,			//EntityCommand_PartDeformation,//װ����������
//		EVCS_Max,			//EntityCommand_PartAttachEffect,//װ��������Ч
//
//		EVCS_Max,			//EntityCommand_AttachMagic,		/// ��ʵ��(��Ҫָ����)������һ����Ч (const MagicView* magic, 0)
//		////  ����һ����ʵ����صĹ�Ч��ע�⣺�����Ч��û��������ʵ���ϣ�
//		EVCS_Max,			//EntityCommand_AddMagic,
//		EVCS_Max,			//EntityCommand_DetachMagic,		/// ȡ��ʵ��(��Ҫָ����)����ָ���Ĺ�Ч (ulong id, int loops)
//		////  �Ƴ�һ����ʵ����صĹ�Ч��ע�⣺�����Ч��û��������ʵ���ϣ�
//		EVCS_Max,			//EntityCommand_RemoveMagic,
//		EVCS_Max,			//EntityCommand_ClearMagic,		/// ���ʵ�����ϵ����й�Ч(һ�㷢����ʵ������ʱ) (0, 0)
//		EVCS_Max,			//EntityCommand_AddModifier,		/// ����޸��� (const Modifier* modifier, 0)
//		EVCS_Max,			//EntityCommand_RemoveModifiers,	/// �Ƴ��޸��� (ulong key, 0)
//
//		//// ������
//		EVCS_Max,			// EntityCommand_ForceStop		/// add by zjpǿ��ֹͣվ����ֹͣ��������
//		EVCS_Max,			//EntityCommand_Stand,			/// վ�� (const POINT* tile=0, 0)
//		EVCS_Max,			//EntityCommand_Fallow,			/// ���� (ulong fallowId, 0)
//		EVCS_Max,			//EntityCommand_Move,				/// �ƶ��������������߻��Ǳ��� (const POINT* pathList, size_t count)
//		EVCS_OnFight,			//EntityCommand_RapidMoveStart,	/// �����ƶ�(˲�ơ����)��ʼ (ShadowManager* mgr, 0)
//		EVCS_OnFight,			//EntityCommand_RapidMoveEnd,		/// �����ƶ�(˲�ơ����)����
//		EVCS_OnFight,			//EntityCommand_AttackReady,		/// ����׼�� (const AttackContext* context, 0)
//		EVCS_OnFight,			//EntityCommand_Attack,			/// ������ (const AttackContext* context, 0)
//
//		EVCS_OnFight,			//EntityCommand_Wound,			/// �ܻ� (0, 0)
//		EVCS_OnFight,			//EntityCommand_Death,			/// ���� (0, 0)
//		EVCS_OnFight,			//EntityCommand_Stun,				/// ѣ�� (0, 0)
//
//		EVCS_OnPeace,			//EntityCommand_Sitdown,			/// ���� (0, 0)
//		EVCS_OnPeace,           //EntityCommand_Siting              /// �� (0, 0)
//
//		EVCS_Max,           //EntityCommand_GetSitState         /// ��ȡ����״̬
//		EVCS_OnPeace,           //EntityCommand_Collect             /// �ɼ� (0, 0)
//		EVCS_OnPeace,           //EntityCommand_ShowRibbon          /// �Ƿ���ʾ����Ʈ��
//		EVCS_Max,			//EntityCommand_SetMount,			/// ������£��� (ulong mount, ulong actionIndex) mountΪ1������Ϊ0������,actionIndexΪʹ�õڼ��׶�������0Ϊ����
//		EVCS_Max,			//EntityCommand_GetMount,			/// ��ȡ�Ƿ���������̬ (ulong* mount, 0) mountΪ1�������ϣ�Ϊ0��û������
//		EVCS_Max,			//EntityCommand_SetDefaultSpeed,  /// ����Ĭ���ٶȣ��ܲ�����·��
//		EVCS_Max,			//EntityCommand_SetMoveStyle,		/// �����ƶ����� (ulong style, 0) styleΪ0�����ߣ�Ϊ1������
//		EVCS_Max,			//EntityCommand_GetMoveStyle,		/// ��ȡ�ƶ����� (ulong* style, 0) styleΪ0�����ߣ�Ϊ1������
//		EVCS_OnPeace,		//EntityCommand_Relive,			/// ʵ�帴�� (0, 0)
//		EVCS_Max,			//EntityCommand_IsMoving,			/// ʵ���Ƿ������ƶ� (bool* isMoving, 0)
//		EVCS_Max,			//EntityCommand_ChangeModel,		/// ��ģ��
//
//		//// ��ģ�Ϳ���
//		EVCS_Max,			//EntityCommand_SetScale,			/// ������ģ�͵����ű���(Ĭ��Ϊ1) (const float* scale, 0) �ڶ�������Ϊ0��ʾ����Ե�ǰ���űȽ������ţ�Ϊ1��ʾ��Ե�ǰ���űȽ�������
//		EVCS_Max,			//EntityCommand_GetScale,			/// ��ȡ��ģ�͵����ű��� (float* scale, 0)
//		EVCS_Max,			//EntityCommand_SetMoveSpeed,		/// ������ģ�͵��ƶ��ٶ� (ulong tileMoveTime, 0)��������ƶ��ٶ����ƶ����ζ�Ӧ������Tile���ĵ���ƶ�ʱ�䣨���룩
//		EVCS_Max,			//EntityCommand_GetMoveSpeed,		/// ��ȡ��ģ�͵��ƶ��ٶ� (ulong* tileMoveTime, 0)
//		//EVCS_Max,			////EntityCommand_SetAniSpeed,		/// ������ģ�Ͷ������ٶ�(Ĭ��Ϊ1) (const float* speed, 0)
//		//EVCS_Max,			////EntityCommand_GetAniSpeed,		/// ��ȡ��ģ�Ͷ������ٶ� (float* speed, 0)
//		EVCS_Max,			//EntityCommand_SetColor,			/// ������ģ�͵���ɫ (const ColorValue* color, 0)
//		EVCS_Max,			//EntityCommand_GetColor,			/// ��ȡ��ģ�͵���ɫ (ColorValue* color, 0)
//
//		//// Topmost��
//		EVCS_Max,			//EntityCommand_SetName,			/// �������� (const char* name, size_t len)
//		EVCS_Max,			//EntityCommand_GetName,			/// ��ȡ���� (std::string* name, 0)
//		EVCS_Max,			//EntityCommand_SetNameColor,		/// �������Ƶ���ɫ (const ColorValue* color, 0)
//		EVCS_Max,			//EntityCommand_GetNameColor,		/// ��ȡ���Ƶ���ɫ (ColorValue* color, 0)
//		EVCS_Max,			//EntityCommand_SetHPInfo,		/// ����HP��Ϣ (ulong cur, ulong max)
//		EVCS_Max,			//EntityCommand_SetMPInfo,		/// ����MP��Ϣ (ulong cur, ulong max)
//		EVCS_Max,			//EntityCommand_ChangeLayout,		/// �ı�topmost��Ϣ�е���ʾ�Ͳ���ʾ�ı�ʶ(ulong hideFlags, ulong showFlags)���ο�TopmostFlagsö��
//		// add by zjp��
//		EVCS_Max,			//EntityCommand_SetTitle,			/// ���óƺ�
//		EVCS_Max,			//EntityCommand_AddGroupText,		/// ���������ʾ��
//		EVCS_Max,			//EntityCommand_ClearGroupText,	/// ���������ʾ��
//
//		////  ���������ǣ�
//		EVCS_Max,			//EntityCommand_SetTaskSign,
//
//		//// ��Ч��
//		EVCS_Max,			//EntityCommand_MoveRadial,		/// �����ƶ������ڹ�Ч (const POINT* ptBegin, const POINT* ptEnd)
//		EVCS_Max,			//EntityCommand_MoveTrack,		/// �ƶ������٣����ڹ�Ч������� (IEntity* source, IEntity* target)
//		EVCS_Max,			//EntityCommand_Jump,				/// ��Ծ
//		EVCS_Max,			//EntityCommand_NextMovingTile,
//	};
//
//	return s_CommandToState[cmd];
//}

void CVisualComponentStateMgr::OnCommand(EntityCommand cmd)
{
	if( !s_bInitMapCommandToState)
	{
		initCommandToStateMap();
	}
	CommandToStateMap::iterator it = (*s_pMapCommandToState).find(cmd);
	if( it == (*s_pMapCommandToState).end() )
	{
		if (m_nCurCommand==EntityCommand_AttackReady && cmd==EntityCommand_Stand)
		{
			m_nCurCommand = EntityCommand_Stand;
		}
		return;	 
	}
	EVisualComponentState newstate = it->second;

	m_nCurCommand = cmd;
	switch( newstate)
	{
	case EVCS_OnFight:
		{
			switch(m_CurState)
			{
			case EVCS_OnFight:
				{
					gGlobalClient->getTimerAxis()->KillTimer(0,this);
					gGlobalClient->getTimerAxis()->SetTimer(0, s_fight2PeaceInterval,this,1);		
				}
				break;
			case EVCS_OnPeace:
				{
					gGlobalClient->getTimerAxis()->SetTimer(0, s_fight2PeaceInterval,this,1);
					m_CurState = EVCS_OnFight;				
				}
				break;
			default:
				break;			
			}
		}
		break;
	case EVCS_OnPeace:
		{
			switch(m_CurState)
			{
			case EVCS_OnPeace:
				{
					//donothing
				}
				break;
			case EVCS_OnFight:
				{
					gGlobalClient->getTimerAxis()->KillTimer(0,this);
					m_CurState = EVCS_OnPeace;			
				}
				break;
			default:
				break;
				
			}
		
		}
		break;
	default:
		break;
	}

	return;
}


