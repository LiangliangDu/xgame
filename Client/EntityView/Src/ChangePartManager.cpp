#include "StdAfx.h"
#include "ChangePartManager.h"
#include "VisualComponentMZ.h"
#include "MWDLoader.h"
#include "ConfigActionMap.h"


ChangePartManager::ChangePartManager():m_pOwner(0),
m_bCanRequestRes(false),
m_ulCurResId(0),
m_ulNewResId(0),
m_handle(INVALID_HANDLE),
m_bLoaded(false),
m_pModelNode(0),
m_bShowRibbonSystem(false),//Ĭ��ѡ����ʾ
m_weaponBindPos(WeaponPos_Hands)
{
	//��ʼ����װ����
	for( uchar i=0; i< EEntityPart_Max; ++i)
	{
		m_CurrentPart[i].perform = false;
		m_CurrentPart[i].part = i;
		for( uchar j =0; j<EBindResNum_MainPart; ++j)
		{
			m_CurrentPart[i].resId[j] = 0;
			m_CurrentPart[i].bindType[j] = EBindType_Min;
			m_CurrentPart[i].bindPoint[j] = EBindPoint_Min;
		}
		m_CurrentPart[i].weaponclass = EWeapon_FirstClass;
	}
	//��ͨ���׵��������
	for( uchar i =0; i<EBindResNum_MainPart; ++i)
		m_CurrentPart[EEntityPart_Armor].bindType[i] = EBindType_Replace;
	//ʱװ�����������
	for( uchar i =0; i<EBindResNum_MainPart; ++i)
		m_CurrentPart[EEntityPart_Suit_Armor].bindType[i] = EBindType_Replace;
	//��ͨͷ���������
	for( uchar i =0; i<EBindResNum_MainPart; ++i)
	{
		m_CurrentPart[EEntityPart_Armet].bindType[i] = EBindType_SubNode;
		m_CurrentPart[EEntityPart_Armet].bindPoint[i] = EBindPoint_Head;
	}
	//ʱװͷ���������
	for( uchar i =0; i<EBindResNum_MainPart; ++i)
	{
		m_CurrentPart[EEntityPart_Suit_Armet].bindType[i] = EBindType_SubNode;
		m_CurrentPart[EEntityPart_Suit_Armet].bindPoint[i] = EBindPoint_Head;
	}
	//�����������
	m_CurrentPart[EEntityPart_Weapon].bindType[0] = EBindType_SubNode;
	m_CurrentPart[EEntityPart_Weapon].bindPoint[0] = EBindPoint_LeftHand;
	m_CurrentPart[EEntityPart_Weapon].bindType[1] = EBindType_SubNode;
	m_CurrentPart[EEntityPart_Weapon].bindPoint[1] = EBindPoint_RightHand;


	//��ʼ��װ����ʾ
	for( uint i=0; i<EEntityPart_Max; ++i)
	{
		m_bShowPart[i] = true;
	}
	//Ĭ�ϲ���ʾͷ����ʱװͷ����ʱװ�·�
	m_bShowPart[EEntityPart_Armet] = false;
	m_bShowPart[EEntityPart_Armor] = true;
	m_bShowPart[EEntityPart_Suit_Armet] = false;
	m_bShowPart[EEntityPart_Suit_Armor] = false;


	//����������
	m_fWeaponScale = 1.0f;
	
	//��ʼ����ɫ
	m_vWeaponColor = xs::ColorValue::White;
	m_vArmetColor = xs::ColorValue::White;
	m_vSuitArmetColor = xs::ColorValue::White;	
	m_vBodyColor = xs::ColorValue::White;
}


void ChangePartManager::create(VisualComponentMZ* pOwner, IChangePartCallBack* pCallBack)
{
	if( 0 == pOwner)
		throw std::string("ChangePartManager::create:pOwner=0");
	if( 0 == pCallBack)
		throw std::string("ChangePartManager::create:pCallBack=0");
	m_pCallBack = pCallBack;
	m_pOwner = pOwner;
}

ChangePartManager::~ChangePartManager()
{
	releaeRes();
}

void ChangePartManager::setCanRequestRes(bool canRequest)
{
	m_bCanRequestRes = canRequest;
}

void ChangePartManager::requestRes(int priority)
{
	//�ܷ�������Դ
	if( !m_bCanRequestRes) 
		return;

	//�ͷžɵ���Դ
	releaeRes();

	//�����µ���Դ
	ulong curBody = getCurrentBody();
	if(m_CurrentPart[curBody].perform && m_CurrentPart[curBody].resId[0] )//�г�ʼֵ
	{
		m_ulCurResId = m_CurrentPart[curBody].resId[0];
		//�ж��ǵ�������id������Դid
		bool isCreature = false;
		if(  ConfigCreatures::Instance()->getCreature(m_ulCurResId) )
			isCreature = true;

		m_ulNewResId = MZIDMap::getInstance().add(m_ulCurResId, isCreature?0:1);//0:����id��1:��Чid
		m_handle = gGlobalClient->getResourceManager()->requestResource(m_ulNewResId, typeResourceModel, false, priority);
		m_bLoaded = false;
		m_pModelNode = 0;
	}
	else//Ĭ��ֵ
	{
		m_ulCurResId = m_pOwner->getOwner()->getResId();
		m_ulNewResId = MZIDMap::getInstance().add(m_ulCurResId,0);//��������
		m_handle = gGlobalClient->getResourceManager()->requestResource(m_ulNewResId, typeResourceModel, false, priority);
		m_bLoaded = false;
		m_pModelNode = 0;
	}
}

void ChangePartManager::releaeRes()
{
	//ȡ���ⲿ����
	ChangePartCallBackContext context;
	context.pNode = 0;
	m_pCallBack->onChangePart(context);


	//�ͷŽڵ�ǰ���Ƚ��ӽڵ��ͷ�
	if( m_pModelNode)
	{
		m_pModelNode->destroyAllChildren();
		m_pModelNode = 0;
	}

	//�ͷ���Դ
	if( isValidHandle(m_handle) )
	{
		// hero����Դ�ӳٻ���
		bool bDelayRecycle = false;
		if (NULL != m_pOwner)
		{
			EntityViewImpl* pOwner = m_pOwner->getOwner();
			if (NULL != pOwner)
			{
				bDelayRecycle = pOwner->isMainPlayer();
			}
		}

		gGlobalClient->getResourceManager()->releaseResource(m_handle, bDelayRecycle);
		m_handle = INVALID_HANDLE;
	}

	//�Ƴ�ӳ�����Դid
	MZIDMap::getInstance().remove(m_ulNewResId);
	m_ulNewResId = 0;

	m_ulCurResId = 0;
	m_bLoaded = false;
}

ulong ChangePartManager::getCurrentBody()
{
	if( m_bShowPart[EEntityPart_Armor] )
		return EEntityPart_Armor;
	else if( m_bShowPart[EEntityPart_Suit_Armor] )
		return EEntityPart_Suit_Armor;
	else
	{
		throw std::string("ChangePartManager::getCurrentBody:no body");
	}
}



void ChangePartManager::changeArmet(SPersonMainPartChangeContext & context)
{
	ulong curBody = getCurrentBody();
	SPersonMainPartChangeContext & curContext = m_CurrentPart[EEntityPart_Armet];

	if( curBody != EEntityPart_Armor)//��ǰ��ʾ�Ĳ�����ͨװ����ģ�ͣ�ֻ�洢����
	{
		curContext = context;
		return;
	}

	if( !m_bCanRequestRes)//����������Դ��
	{
		curContext = context;
		return;
	}

	if(0 == m_pModelNode )//��ǰ��ʾ�Ľڵ㻹û�м���������ֻ�洢����
	{
		curContext = context;
		return;
	}

	//����ж�ؾɵ�ģ��
	if( !gGlobalClient->getEntityClient() )
	{
		return;
	}
	const char * pOldBP = gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(curContext.bindPoint[0] );
	ModelNode * pOld = m_pModelNode->getFirstChildNodeByBone(pOldBP);
	if( pOld )  m_pModelNode->destroyChild( pOld);

	if( context.perform)//����װ��
	{
		
		ModelNode* pNode = 0;
		ConfigCreature* pCreatureConfig = ConfigCreatures::Instance()->getCreature(context.resId[0]);
		if( pCreatureConfig )//���ȴ��������ö�ȡ
		{
			pNode = ModelNodeCreater::create(pCreatureConfig);
			if( pNode) 
				pNode->setScale(xs::Vector3::UNIT_SCALE);
		}
		else//����Ҳ����ʹ���Դ�����д���
		{
			const std::string & filename = ConfigCreatureRes::Instance()->getResFromId(context.resId[0]);
			pNode = ModelNodeCreater::create(filename.c_str() );
		}
			
		if( pNode )
		{
			const char * pBP = gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(context.bindPoint[0]);
			if( !m_pModelNode->addChild(pNode, pBP) )
			{
				pNode->release();
				pNode = 0;
			}
			else
			{
				//����ͷ����ɫ
				pNode->setGlobalDiffuse(m_vArmetColor);
			}
			
		}
	}
	else
	{
		//�Ѿ�ж����
	}

	//���滻װ����
	curContext = context;
	//����ͷ������ʾ
	showPart(EEntityPart_Armet, m_bShowPart[EEntityPart_Armet]);

	return;
}

void ChangePartManager::changeSuitArmet(SPersonMainPartChangeContext & context)
{
	ulong curBody = getCurrentBody();
	SPersonMainPartChangeContext & curContext = m_CurrentPart[EEntityPart_Suit_Armet];

	if( curBody != EEntityPart_Suit_Armor)//��ǰ��ʾ�Ĳ���ʱװװ����ģ�ͣ�ֻ�洢����
	{
		curContext = context;
		return;
	}

	if( !m_bCanRequestRes)//����������Դ��
	{
		curContext = context;
		return;
	}

	if(0 == m_pModelNode )//��ǰ��ʾ�Ľڵ㻹û�м���������ֻ�洢����
	{
		curContext = context;
		return;
	}

	//����ж�ؾɵ�ģ��
	const char * pOldBP = gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(curContext.bindPoint[0] );
	ModelNode * pOld = m_pModelNode->getFirstChildNodeByBone(pOldBP);
	if( pOld )  m_pModelNode->destroyChild( pOld);

	if( context.perform)//����װ��
	{
		ModelNode * pNode = 0;
		ConfigCreature* pCreatureConfig = ConfigCreatures::Instance()->getCreature(context.resId[0]);
		if( pCreatureConfig )
		{
			pNode = ModelNodeCreater::create(pCreatureConfig);
			if( pNode)
				pNode->setScale(xs::Vector3::UNIT_SCALE);
		}
		else
		{
			const std::string & filename = ConfigCreatureRes::Instance()->getResFromId(context.resId[0]);
			pNode = ModelNodeCreater::create(filename.c_str() );
		}
			
		if( pNode )
		{
			const char * pBP = gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(context.bindPoint[0]);
			if( !m_pModelNode->addChild(pNode, pBP) )
			{
				pNode->release();
				pNode = 0;
			}
			else
			{
				//����ʱװͷ������ɫ
				pNode->setGlobalDiffuse(m_vSuitArmetColor);
			}
			
		}
	}
	else
	{
		//�Ѿ�ж����
	}

	//���滻װ����
	curContext = context;
	//����ͷ������ʾ
	showPart(EEntityPart_Suit_Armet, m_bShowPart[EEntityPart_Suit_Armet]);

	return;
}


void ChangePartManager::changeArmor(SPersonMainPartChangeContext & context)
{
	ulong curBody = getCurrentBody();
	SPersonMainPartChangeContext & curContext = m_CurrentPart[EEntityPart_Armor];

	if( curBody != EEntityPart_Armor)//��ǰ��ʾ�Ĳ�����ͨװ����ģ�ͣ�ֻ�洢����
	{
		curContext = context;
		return;
	}

	//�ͷžɵ���Դ
	releaeRes();

	//���滷��
	curContext = context;

	//�����µ���Դ
	requestRes(0);

	return;
}

void ChangePartManager::changeSuitArmor(SPersonMainPartChangeContext& context)
{
	ulong curBody = getCurrentBody();
	SPersonMainPartChangeContext & curContext = m_CurrentPart[EEntityPart_Suit_Armor];

	if( curBody != EEntityPart_Suit_Armor)//��ǰ��ʾ�Ĳ�����ͨװ����ģ�ͣ�ֻ�洢����
	{
		curContext = context;
		return;
	}

	//�ͷžɵ���Դ
	releaeRes();

	//���滷��
	curContext = context;

	//�����µ���Դ
	requestRes(0);

	return;
}

void ChangePartManager::changeWeapon(SPersonMainPartChangeContext & context)
{
	SPersonMainPartChangeContext & curContext = m_CurrentPart[EEntityPart_Weapon];

	if( !m_bCanRequestRes)//����������Դ��
	{
		curContext = context;
		return;
	}

	if(0 == m_pModelNode )//��ǰ��ʾ�Ľڵ㻹û�м���������ֻ�洢����
	{
		curContext = context;
		return;
	}

	if(!gGlobalClient->getEntityClient())
		return;

	//����ж�ؾɵ�ģ��
	for( uint i = 0; i < EBindResNum_MainPart; ++i)
	{
		const char * pBP = gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(curContext.bindPoint[i] );
		ModelNode * pNode = m_pModelNode->getFirstChildNodeByBone(pBP);
		if( pNode ) m_pModelNode->destroyChild(pNode);	
	}

	//���滻װ����
	curContext = context;

	//���ػ���ж��װ��
	if( curContext.perform)//����װ��
	{
		ModelNode * pNodeArr[EBindResNum_MainPart];
		memset( pNodeArr,0, sizeof(pNodeArr) );
		for( uint i =0; i < EBindResNum_MainPart; ++i)
		{
			ConfigCreature* pCreatureConfig = ConfigCreatures::Instance()->getCreature(curContext.resId[i]);
			if( pCreatureConfig)//���ȴ��������ô���
			{
				pNodeArr[i] = ModelNodeCreater::create(pCreatureConfig);
				if( pNodeArr[i])
					pNodeArr[i]->setScale(xs::Vector3::UNIT_SCALE);
			}
			else//���û�У��ʹ���Դ���ô���
			{
				const std::string & filename = ConfigCreatureRes::Instance()->getResFromId(curContext.resId[i]);
				pNodeArr[i] = ModelNodeCreater::create(filename.c_str() );	
			}		
		}
		for( uint i=0; i<EBindResNum_MainPart; ++i)
		{
			if( pNodeArr[i] == 0 ) continue;
			const char * pBP = gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(curContext.bindPoint[i]);
			bool ret = m_pModelNode->addChild(pNodeArr[i], pBP);
			if( !ret ) 
			{
				safeRelease(pNodeArr[i]);
			}
			else
			{
				//����������λ��
				setWeaponPos(m_weaponBindPos);

				//���������Ĵ�С
				pNodeArr[i]->setScale(m_fWeaponScale, m_fWeaponScale, m_fWeaponScale);

				//����������ɫ
				pNodeArr[i]->setGlobalDiffuse(m_vWeaponColor);

			}
		}

		//��ʾƮ��ϵͳ
		showRibbonSystem(m_bShowRibbonSystem);
	}
	else
	{
		//�Ѿ�ж����
	}

	return;
}

void ChangePartManager::onResLoad(ModelNode* pNode)
{
	if( 0 == pNode) //������
	{
		throw std::string("ChangePartManager::onResLoad:: empty ModelNode");
		return;
	}

	m_bLoaded = true;
	m_pModelNode = pNode;

	//����������ɫ
	m_pModelNode->setGlobalDiffuse(m_vBodyColor);

	//ִ�л�װ����
	ulong curBody = getCurrentBody();
	if( curBody == EEntityPart_Armor )//��ͨװ��
	{
		changePart(m_CurrentPart[EEntityPart_Armet]);
		changePart(m_CurrentPart[EEntityPart_Weapon]);
	}
	else if( curBody == EEntityPart_Suit_Armor)
	{
		changePart(m_CurrentPart[EEntityPart_Suit_Armet]);
		changePart(m_CurrentPart[EEntityPart_Weapon]);
	}
	else
	{
		//no thing to do
	}

	//�����ⲿ
	ChangePartCallBackContext context;
	context.pNode = m_pModelNode;
	m_pCallBack->onChangePart(context);
}

void ChangePartManager::update()
{
	if( isValidHandle(m_handle) && !m_bLoaded ) //�����Ч����û�м���
	{
		IResourceNode* node = (IResourceNode*)getHandleData(m_handle);
		if( node)
		{
			IResource * res = node->getResource();
			if( res)
			{
				ModelNode * n = (ModelNode *)res->getInnerData();
				if( n )
				{
					onResLoad(n);
				}
			}
		}
	}
}

EWeaponClass ChangePartManager::getWeaponClass()
{
	if( m_CurrentPart[EEntityPart_Weapon].perform )
	{
		if( m_CurrentPart[EEntityPart_Weapon].weaponclass >= EWeapon_Max)
			throw std::string("ChangePartManager::getWeaponClass:bad weapon class");
		return static_cast<EWeaponClass>( m_CurrentPart[EEntityPart_Weapon].weaponclass);
	}
	else
	{
		return EWeapon_NoWeapon;
	}
}

void ChangePartManager::setWeaponAnimation(std::string ani)
{
	if( !gGlobalClient->getEntityClient() )
		return;
	if( m_pModelNode)
	{
		const SPersonMainPartChangeContext &  context = m_CurrentPart[EEntityPart_Weapon];
		for(uint i=0; i<2; ++i)
		{
			ModelNode* pNode= m_pModelNode->getFirstChildNodeByBone(gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(context.bindPoint[i]));
			if( pNode)
			{
				pNode->getModelInstance()->setCurrentAnimation(ani);
			}
		}
	}
}

bool ChangePartManager::getPart(uint part, SEventPersonPerform_C& c)
{
	if( part <= EEntityPart_Invalid || part >=EEntityPart_Max)
		return false;

	c.perform = m_CurrentPart[part].perform;
	c.part = m_CurrentPart[part].part;
	c.resId[0]= m_CurrentPart[part].resId[0];
	c.resId[1] = m_CurrentPart[part].resId[1];
	if( part != EEntityPart_Weapon)
	{
		sprintf_s(c.bindPoint[0], sizeof(c.bindPoint[0]),"%s",gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(m_CurrentPart[part].bindPoint[0]) );
		sprintf_s(c.bindPoint[1], sizeof(c.bindPoint[1]),"%s",gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(m_CurrentPart[part].bindPoint[1]) );
	}	
	else
	{
		int bind1 = m_CurrentPart[part].bindPoint[0];
		int bind2 = m_CurrentPart[part].bindPoint[1];
		sprintf_s(c.bindPoint[0], sizeof(c.bindPoint[0]), "%s", gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(bind1));
		sprintf_s(c.bindPoint[1], sizeof(c.bindPoint[1]), "%s", gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(bind2));
		//sprintf_s(c.bindPoint[0], sizeof(c.bindPoint[0]), "%s", gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(EBindPoint_LeftBack));
		//sprintf_s(c.bindPoint[1], sizeof(c.bindPoint[1]), "%s", gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(EBindPoint_RightBack));
		ActionMapContext actioncontext;
		actioncontext.iscreature = true;
		actioncontext.ismount = false;
		actioncontext.state = EVCS_OnPeace;
		actioncontext.weapon = getWeaponClass();
		sprintf_s(c.animation, sizeof(c.animation),"%s", ConfigActionMap::Instance()->getMappedAction(actioncontext, EntityAction_Stand) );	
		c.weaponsubclass = m_CurrentPart[part].weaponsubclass;
	}

	return true;
}

bool ChangePartManager::getPartShow(uint part, SEventPersonPerformShow_C& c)
{
	if( part <= EEntityPart_Invalid || part >=EEntityPart_Max)
		return false;

	c.part = static_cast<EntityParts>(part);
	c.show = m_bShowPart[part];
	return true;

}

int ChangePartManager::getCurrentCreatureId()
{
	ulong curBody = getCurrentBody();
	if( !m_CurrentPart[curBody].perform 
		|| 0 == m_CurrentPart[curBody].resId[0]
		|| ConfigCreatures::Instance()->getCreature( m_CurrentPart[curBody].resId[0]) )
	{
		return m_pOwner->getOwner()->getResId();
	}
	else
	{
		return m_CurrentPart[curBody].resId[0];
	}
}

void ChangePartManager::setWeaponPos(WeaponPosition pos)
{
	SPersonMainPartChangeContext &  context = m_CurrentPart[EEntityPart_Weapon];
	IEntityClient* pEntityClient = gGlobalClient->getEntityClient();
	if (NULL == pEntityClient)
	{
		return;
	}
	ISchemeCenter* pSchemeCenter = pEntityClient->GetSchemeCenter();
	if (!pSchemeCenter)
	{
		return;
	}
	m_weaponBindPos = pos;
	if( !context.perform)//û��װ������
	{
		if( m_weaponBindPos == WeaponPos_Back)
		{
			//���ھ��������������⴦��
			if( context.weaponsubclass == EQUIPMENT_SUBCLASS_SORCERER_WEAPON_1_CLASS)
			{
				for( uint i=0; i<2;++i)
				{
					if( context.bindPoint[i] == EBindPoint_LeftHand)
						context.bindPoint[i] = EBindPoint_RightBack ;
					else if( context.bindPoint[i] == EBindPoint_RightHand)
						context.bindPoint[i] = EBindPoint_LeftBack;
				}
			}
			else
			{
				for( uint i=0; i<2;++i)
				{
					if( context.bindPoint[i] == EBindPoint_LeftHand)
						context.bindPoint[i] = EBindPoint_LeftBack;
					else if( context.bindPoint[i] == EBindPoint_RightHand)
						context.bindPoint[i] = EBindPoint_RightBack;
				}
			}

		}
		else
		{
			//���ھ��������������⴦��
			if( context.weaponsubclass == EQUIPMENT_SUBCLASS_SORCERER_WEAPON_1_CLASS)
			{
				for( uint i =0; i<2; ++i)
				{
					if( context.bindPoint[i] == EBindPoint_LeftBack)
						context.bindPoint[i] = EBindPoint_RightHand ;
					else if( context.bindPoint[i] == EBindPoint_RightBack)
						context.bindPoint[i] = EBindPoint_LeftHand;
				}
			}
			else
			{
				for( uint i =0; i<2; ++i)
				{
					if( context.bindPoint[i] == EBindPoint_LeftBack)
						context.bindPoint[i] = EBindPoint_LeftHand;
					else if( context.bindPoint[i] == EBindPoint_RightBack)
						context.bindPoint[i] = EBindPoint_RightHand;
				}
			}		
		}
		return;
	}
	else
	{
		ModelNode* pNode[2];
		memset( &pNode[0], 0, sizeof(pNode));
		if(m_pModelNode)//�Ƴ�
		{		
			for( uint i=0; i<2;++i)
			{
				const char* pchar = pSchemeCenter->getBindPoint(context.bindPoint[i]);
				pNode[i] = m_pModelNode->getFirstChildNodeByBone(pchar);
				if( pNode[i])
				{
					m_pModelNode->removeChild(pNode[i]);
					pNode[i]->setPosition(xs::Vector3::ZERO);
					pNode[i]->setOrientation(xs::Quaternion::IDENTITY);
				}
			}
		}

		//��
		if( m_weaponBindPos == WeaponPos_Back)
		{
			for( uint i=0; i<2;++i)
			{
				if( context.bindPoint[i] == EBindPoint_LeftHand)
					context.bindPoint[i] = EBindPoint_RightBack;
				else if( context.bindPoint[i] == EBindPoint_RightHand)
					context.bindPoint[i] = EBindPoint_LeftBack;
			}

			////���ھ��������������⴦��
			//if( context.weaponsubclass == EQUIPMENT_SUBCLASS_SORCERER_WEAPON_1_CLASS)
			//{
			//	for( uint i=0; i<2;++i)
			//	{
			//		if( context.bindPoint[i] == EBindPoint_LeftHand)
			//			context.bindPoint[i] = EBindPoint_RightBack ;
			//		else if( context.bindPoint[i] == EBindPoint_RightHand)
			//			context.bindPoint[i] = EBindPoint_LeftBack;
			//	}
			//}
			//else
			//{
			//	for( uint i=0; i<2;++i)
			//	{
			//		if( context.bindPoint[i] == EBindPoint_LeftHand)
			//			context.bindPoint[i] = EBindPoint_LeftBack;
			//		else if( context.bindPoint[i] == EBindPoint_RightHand)
			//			context.bindPoint[i] = EBindPoint_RightBack;
			//	}
			//}		
		}
		else
		{
			for( uint i =0; i<2; ++i)
			{
				if( context.bindPoint[i] == EBindPoint_LeftBack)
					context.bindPoint[i] = EBindPoint_RightHand;
				else if( context.bindPoint[i] == EBindPoint_RightBack)
					context.bindPoint[i] = EBindPoint_LeftHand;
			}
			//���ھ��������������⴦��
			//if( context.weaponsubclass == EQUIPMENT_SUBCLASS_SORCERER_WEAPON_1_CLASS)
			//{
			//	for( uint i =0; i<2; ++i)
			//	{
			//		if( context.bindPoint[i] == EBindPoint_LeftBack)
			//			context.bindPoint[i] = EBindPoint_RightHand;
			//		else if( context.bindPoint[i] == EBindPoint_RightBack)
			//			context.bindPoint[i] =  EBindPoint_LeftHand;
			//	}
			//}
			//else
			//{
			//	for( uint i =0; i<2; ++i)
			//	{
			//		if( context.bindPoint[i] == EBindPoint_LeftBack)
			//			context.bindPoint[i] = EBindPoint_LeftHand;
			//		else if( context.bindPoint[i] == EBindPoint_RightBack)
			//			context.bindPoint[i] = EBindPoint_RightHand;
			//	}
			//}	
		}

		if(m_pModelNode)
		{
			for(uint i=0; i<2;++i)
			{
				if( !pNode[i]) continue;
				bool ret = m_pModelNode->addChild(pNode[i], gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(context.bindPoint[i]));
				if(!ret)
				{
					safeRelease(pNode[i]);
				}
				else
				{
					if( m_weaponBindPos == WeaponPos_Back)
					{
						//������������
						if(context.weaponsubclass == EQUIPMENT_SUBCLASS_WARRIOR_WEAPON_2_CLASS)
						{
							xs::Quaternion rotx;
							rotx.FromAngleAxis(180.0f, Vector3(1.0f, 0.0f, 0.0f));
							xs::Quaternion roty;
							roty.FromAngleAxis(180.0f, Vector3(0.0f,1.0f,0.0f));
							xs::Quaternion rot = roty * rotx;
							pNode[i]->setOrientation(rot);
							xs::Vector3 origin = xs::Vector3::ZERO;
							origin.y += pNode[i]->getModelInstance()->getBoundingSphere().getCenter().y;
							pNode[i]->setPosition(origin);
						}
						else if (context.weaponsubclass == EQUIPMENT_SUBCLASS_ARCHER_WEAPON_1_CLASS)
						{
							// �޸Ĺ��������ĳ������ڵĹ��������ǰ����ڳ�Z�᷽����ǰĬ���ǳ�X�᷽��
							xs::Quaternion roty;
							roty.FromAngleAxis(90.0f, Vector3(0.0f,1.0f,0.0f));
							pNode[i]->setOrientation(roty);

							xs::Vector3 origin = xs::Vector3::ZERO;
							origin.y -= pNode[i]->getModelInstance()->getBoundingSphere().getCenter().y;
							pNode[i]->setPosition(origin);
						}
						else
						{
							xs::Vector3 origin = xs::Vector3::ZERO;
							origin.y -= pNode[i]->getModelInstance()->getBoundingSphere().getCenter().y;
							pNode[i]->setPosition(origin);
						}
						
					}
					else
					{
						// �޸Ĺ��������ĳ������ڵĹ��������ǰ����ڳ�Z�᷽����ǰĬ���ǳ�X�᷽��
						if (context.weaponsubclass == EQUIPMENT_SUBCLASS_ARCHER_WEAPON_1_CLASS)
						{						
							xs::Quaternion roty;
							roty.FromAngleAxis(90.0f, Vector3(0.0f,1.0f,0.0f));
							pNode[i]->setOrientation(roty);
						}
						else
						{
							pNode[i]->setOrientation(xs::Quaternion::IDENTITY);
						}
						pNode[i]->setPosition(xs::Vector3::ZERO);
					}
				}
			}	
		}
	}
}

void ChangePartManager::showRibbonSystem(bool show)
{
	m_bShowRibbonSystem = show;
	if( !m_pModelNode)
		return;

	const char* pBP[2];
	pBP[0] = gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint( m_CurrentPart[EEntityPart_Weapon].bindPoint[0]);
	pBP[1] = gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(m_CurrentPart[EEntityPart_Weapon].bindPoint[1] );
	for( uint i=0; i<2; ++i)
	{
		ModelNode* pWeapon = m_pModelNode->getFirstChildNodeByBone(pBP[i]);
		if( pWeapon)
			pWeapon->getModelInstance()->showRibbonSystem(m_bShowRibbonSystem);
	}
}

void ChangePartManager::changePart(SPersonMainPartChangeContext & context)
{
	//��������ڵ�ʱ�첽���صģ���������ͬ�����صġ�

	//��֤�Ƿ���Ч
	if( context.part <= EEntityPart_Invalid && context.part >= EEntityPart_Max) 
		return;

	switch( context.part)
	{
	case EEntityPart_Armet:
		changeArmet( context);
		break;
	case EEntityPart_Suit_Armet:
		changeSuitArmet( context);
		break;
	case EEntityPart_Armor:
		changeArmor( context);
		break;
	case EEntityPart_Suit_Armor:
		changeSuitArmet(context);
		break;
	case EEntityPart_Weapon:
		changeWeapon(context);
		break;
	default:
		m_CurrentPart[context.part] = context;
		break;
	}

	return;
}

void ChangePartManager::showArmet(bool bShow)
{
	m_bShowPart[EEntityPart_Armet] = bShow;

	//���
	if( 0 == m_pModelNode )//�ڵ�û�м���
		return;
	ulong curBody = getCurrentBody();
	if( curBody != EEntityPart_Armor)//������ͨװ��
		return;

	const char * pBP = gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint( m_CurrentPart[EEntityPart_Armet].bindPoint[0] );
	ModelNode * pSubNode = m_pModelNode->getFirstChildNodeByBone(pBP);
	xs::SubModelInstance * pSubModel = m_pModelNode->getModelInstance()->getSubModel( getModelMeshName(MSFCP_HAIR) );

	if( bShow )
	{
		if( pSubNode )
		{
			pSubNode->setVisible(true);
			if( pSubModel)
				pSubModel->setVisible(false);
		}
		else
		{
			if( pSubModel)
				pSubModel->setVisible(true);
		}
	}
	else
	{
		if( pSubNode)
			pSubNode->setVisible(false);
		if( pSubModel)
			pSubModel->setVisible(true);
	}

	return;
}

void ChangePartManager::showSuitArmet(bool bShow)
{
	m_bShowPart[EEntityPart_Suit_Armet] = bShow;

	//���
	if( 0 == m_pModelNode )//�ڵ�û�м���
		return;
	ulong curBody = getCurrentBody();
	if( curBody != EEntityPart_Suit_Armor)//����ʱװװ��
		return;

	

	const char * pBP = gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint( m_CurrentPart[EEntityPart_Suit_Armet].bindPoint[0] );
	ModelNode * pSubNode = m_pModelNode->getFirstChildNodeByBone(pBP);
	xs::SubModelInstance * pSubModel = m_pModelNode->getModelInstance()->getSubModel( getModelMeshName(MSFCP_HAIR) );

	if( bShow )
	{
		if( pSubNode )
		{
			pSubNode->setVisible(true);
			if( pSubModel)
				pSubModel->setVisible(false);
		}
		else
		{
			if( pSubModel)
				pSubModel->setVisible(true);
		}
	}
	else
	{
		if( pSubNode)
			pSubNode->setVisible(false);
		if( pSubModel)
			pSubModel->setVisible(true);
	}

	return;
}

void ChangePartManager::showBody( bool normal)
{
	//�ͷžɵ���Դ
	releaeRes();

	//�趨��ǰ��ʾ�Ľڵ�
	if( normal )
	{
		m_bShowPart[EEntityPart_Armor] = true;
		m_bShowPart[EEntityPart_Suit_Armor] = false;
	}
	else
	{
		m_bShowPart[EEntityPart_Armor] = false;
		m_bShowPart[EEntityPart_Suit_Armor] = true;
	}

	//�����µ���Դ
	requestRes(0);	
}

void ChangePartManager::showWeapon( bool bShow)//����ʱ����Ҫ����������by cjl
{
	m_bShowPart[EEntityPart_Weapon] = bShow;

	SPersonMainPartChangeContext & curContext = m_CurrentPart[EEntityPart_Weapon];
	curContext.perform = bShow;

}//end cjl


void ChangePartManager::showPart( ulong ulPart, bool bShow)
{
	//��֤
	if (ulPart <= static_cast<ulong>(EEntityPart_Invalid) ||  ulPart >= static_cast<ulong>(EEntityPart_Max) )
		return;

	switch( ulPart)
	{
	case EEntityPart_Armet:
		showArmet(bShow);
		break;
	case EEntityPart_Armor:
		showBody(bShow);
		break;
	case EEntityPart_Suit_Armet:
		showSuitArmet(bShow);
		break;
	case EEntityPart_Suit_Armor:
		showBody(!bShow);
		break;
	case EEntityPart_Weapon://by cjl
		showWeapon(bShow);
		break;
	default:
		break;
	}

	return;
}

void ChangePartManager::setPartScale(ulong part, float scale)
{
	if( part <= EEntityPart_Invalid || part >= EEntityPart_Max )
		return;

	//ֻ��������������
	if( part != EEntityPart_Weapon )
		return ;

	m_fWeaponScale = scale;

	if( m_pModelNode && m_CurrentPart[EEntityPart_Weapon].perform )
	{
		for( uint i=0; i<EBindResNum_MainPart; ++i)
		{
			const char * pBP = gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(m_CurrentPart[EEntityPart_Weapon].bindPoint[i]);
			xs::ModelNode* pSubNode = m_pModelNode->getFirstChildNodeByBone(pBP);
			if( pSubNode )
				pSubNode->setScale(m_fWeaponScale,m_fWeaponScale,m_fWeaponScale);
		}
	}
}

void ChangePartManager::setPartColor(ulong	part, const ColorValue& color)
{
	//ֻ����ͷ������������ɫ
	if( part <= EEntityPart_Invalid || part >= EEntityPart_Max)
		return;

	switch( part )
	{
	case EEntityPart_Weapon:
		{
			m_vWeaponColor = color;
			if( m_pModelNode && m_CurrentPart[EEntityPart_Weapon].perform )
			{
				for( uint i=0; i<EBindResNum_MainPart; ++i)
				{
					const char * pBP = gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint(m_CurrentPart[EEntityPart_Weapon].bindPoint[i]);
					xs::ModelNode* pSubNode = m_pModelNode->getFirstChildNodeByBone(pBP);
					if( pSubNode )
						pSubNode->setGlobalDiffuse(m_vWeaponColor);
				}
			}
		}
		break;
	case EEntityPart_Armet:
		{
			m_vArmetColor = color;
			ulong curBody = getCurrentBody();
			if( curBody == EEntityPart_Armor
				&& m_pModelNode
				&& m_CurrentPart[EEntityPart_Armet].perform )
			{
				const char* pBP = gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint( m_CurrentPart[EEntityPart_Armet].bindPoint[0]);
				xs::ModelNode* pArmet = m_pModelNode->getFirstChildNodeByBone(pBP);
				if( pArmet)
					pArmet->setGlobalDiffuse(m_vArmetColor);
			}
		}
		break;
	case EEntityPart_Suit_Armet:
		{
			m_vSuitArmetColor = color;
			ulong curBody = getCurrentBody();
			if( curBody == EEntityPart_Suit_Armor
				&& m_pModelNode
				&& m_CurrentPart[EEntityPart_Suit_Armet].perform )
			{
				const char* pBP = gGlobalClient->getEntityClient()->GetSchemeCenter()->getBindPoint( m_CurrentPart[EEntityPart_Suit_Armet].bindPoint[0]);
				xs::ModelNode* pSuitArmet = m_pModelNode->getFirstChildNodeByBone(pBP);
				if( pSuitArmet)
					pSuitArmet->setGlobalDiffuse(m_vSuitArmetColor);
			}	
		}
		break;
	}

}

void ChangePartManager::setBodyColor(const ColorValue & color)
{
	m_vBodyColor = color;
	if( m_pModelNode )
		m_pModelNode->setGlobalDiffuse(m_vBodyColor);
}

const ColorValue & ChangePartManager::getBodyColor()
{
	return m_vBodyColor;
}
