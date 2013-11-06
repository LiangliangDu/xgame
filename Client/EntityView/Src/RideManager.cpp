#include "StdAfx.h"
#include "RideManager.h"
#include "VisualComponentMZ.h"
#include "MWDLoader.h"



RideManager::RideManager():m_pOwner(0),
m_bIsRide(false),
m_ulResId(0),
m_pRideNode(0),
m_ulNewResId(0),
m_handle(INVALID_HANDLE),
m_bLoaded(false),
m_bCanRequestRes(false)
{

}

void RideManager::create(VisualComponentMZ* pOwner, IRideCallBack* pCallBack)
{
	if( 0 == pOwner)
		throw std::string("RideManager::create:pOwner=0");
	if( 0 == pCallBack)
		throw std::string("RideManager::create:pCallBack=0");
	m_pRideCallBack = pCallBack;
	m_pOwner = pOwner;
}

RideManager::~RideManager()
{
	releaseRes();
}

void RideManager::releaseRes()
{
	//ȡ�����
	RideCallBackContext context;
	context.pRideNode = 0;
	m_pRideCallBack->onRide(context);

	if( isValidHandle( m_handle) ) //��Դ��Ч���ͷ���Դ
	{
		// hero�������Դ�ӳٻ���
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
	m_pRideNode = 0;

	//�Ƴ�ӳ�����Դid
	MZIDMap::getInstance().remove(m_ulNewResId);
	m_ulNewResId = 0;
	m_bLoaded = false;
}


void RideManager::requestRes(int priority)
{
	if( !m_bIsRide )//û����ˣ�����������Դ
		return;
	if( !m_bCanRequestRes)//����������Դ
		return;

	//�ͷžɵ���Դ
	releaseRes();

	//����������Դ
	m_pRideNode = 0;
	m_ulNewResId = MZIDMap::getInstance().add(m_ulResId, 0);
	m_handle = gGlobalClient->getResourceManager()->requestResource(m_ulNewResId, typeResourceModel, false, priority);
	m_bLoaded = false;
}

void RideManager::setCanRequestRes(bool canRequest)
{
	m_bCanRequestRes = canRequest;
}

bool RideManager::isRide()
{
	return m_bIsRide;
}


void RideManager::update()
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
					m_bLoaded = true;
					m_pRideNode = n;
					//���
					RideCallBackContext context;
					context.pRideNode = n;
					ConfigCreature * cc = ConfigCreatures::Instance()->getCreature(m_ulResId);
					if( cc) context.strBindPoint = cc->cRide.boneName;
					else context.strBindPoint.clear();
					context.ulRideResId = m_ulResId;
					m_pRideCallBack->onRide(context);
				}
			}
		}
	}
}

bool RideManager::ride(bool bRide, ulong resId)
{
	bool realNeedRide = false; //�������Ƿ��������
	if( bRide &&  0 != resId )
	{
		realNeedRide = true;
	}


	if( m_bIsRide && realNeedRide && resId == m_ulResId ) //������ˣ�����Դid��ͬ
	{
		return true;//ʲô��������
	}
	else if ( m_bIsRide && realNeedRide && resId != m_ulResId ) //��ʱ�Ǹ������
	{
		//�ͷžɵ���Դ
		releaseRes();	
		//��������id
		m_ulResId = resId;
		//����������Դ
		requestRes(0);
		return true;
	}
	else if( m_bIsRide && !realNeedRide) //��ʱ������
	{
		//�ͷ���Դ
		releaseRes();

		//�������״̬
		m_bIsRide = false;

		return true;
	}
	else if( !m_bIsRide && realNeedRide) //��ʱ������
	{		
		m_bIsRide =true;
		m_ulResId = resId;
		//������Դ
		requestRes(0);
		return true;
	}
	else if( !m_bIsRide && !realNeedRide)//��������
	{
		return true;//ʲô��������
	}
	else
	{
		//�����ܵ�������
		throw std::string("RideManager::ride::invalid flow");
		return true;
	}

}