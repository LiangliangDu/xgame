//==========================================================================
/**
* @file	  : MoveComponentMZ.cpp
* @author : 
* created : 2008-1-29   11:04
*/
//==========================================================================

#include "stdafx.h"
#include "MoveComponentMZ.h"
#include "IAudioEngine.h"
#include "IFormManager.h"

//#define TIME_UNIT	16
#	define     MAX_MOVE_STEP     16

MoveComponentMZ::MoveComponentMZ():
mIsMoving(false),m_nPlayDelay(0)
{
}

MoveComponentMZ::~MoveComponentMZ()
{
	stopMove();
}
void MoveComponentMZ::create()
{
	mBaseTimePerTile = 300.0f;
	mTimePerTile = 300.0f;
	mOldTicks = 0;
	mTicks = 0;
}

void MoveComponentMZ::close()
{

}

bool MoveComponentMZ::handleCommand(ulong cmd, ulong param1, ulong param2)
{
	switch (cmd)
	{
	case EntityCommand_Move:
		{
			if (getOwner()->isMainPlayer())
			{
				breakable;
			}

			const xs::Point* pathList = (const xs::Point*)param1;
			size_t count = (size_t)param2;

			if (!pathList) return false;

			if (move(pathList, count))
			{
				mIsMoving = true;
				getOwner()->onMessage(msgMoveStart);
			}
		}
		break;
	case EntityCommand_Stand:
		if (getOwner()->isMainPlayer())
		{
			breakable;
		}
		if (param1 != 0) // �������µ�tile���꣬�������쳣վ����˲��
		{
			const xs::Point& newTile = *(const xs::Point*)param1;
			const xs::Point& ptTile = getOwner()->getTile();
			if (ptTile.x != newTile.x || ptTile.y != newTile.y)
			{
#if 0
				if (getOwner()->isMainPlayer())
				{
					Error("EntityCommand_Stand:"
						<<ptTile.x<<","<<ptTile.y<<"--->"
						<<newTile.x<<","<<newTile.y<<endl);
				}
				else
				{
					if (getOwner()->isMainPlayer())
					{
						Warning("MainPlayer EntityCommand_Stand:"
							<<ptTile.x<<","<<ptTile.y<<"--->"
							<<newTile.x<<","<<newTile.y<<endl);
					}
					else
					{
						Warning("NoMainPlayer EntityCommand_Stand:"
							<<ptTile.x<<","<<ptTile.y<<"--->"
							<<newTile.x<<","<<newTile.y<<endl);
					}
				}
#endif
				gGlobalClient->getSceneManager()->moveEntity(ptTile, newTile, getOwner());
			}
		}

		if (mIsMoving)
		{
			if (getOwner()->getEntityViewObserver())
				getOwner()->getEntityViewObserver()->onMoveBreak(getOwner());
		}

		stopMove();
		break;
	case EntityCommand_IsMoving:
		{
			*(bool*)param1 = mIsMoving;
			if (mIsMoving)
			{
				m_nPlayDelay = m_nPlayDelay + 1;
				if (m_nPlayDelay == 25)
				{
					// ģ����·������
					IFormManager* pFormMange = gGlobalClient->getFormManager();
					const ConfigCreature* mConfig = ConfigCreatures::Instance()->getCreature(getOwner()->getResId());
					if (pFormMange && mConfig->aa.soundMove != 0) pFormMange->PlaySound(mConfig->aa.soundMove,0,1,SOUNDRES_TYPE_SOUND);
					m_nPlayDelay = 0;
				}
			}          
		}
		break;
	case EntityCommand_NextMovingTile:
		{
			return GetNextMovingTile((xs::Point*)param1);
		}

		break;
	}

	return MoveComponent::handleCommand(cmd, param1, param2);
}

void MoveComponentMZ::handleMessage(ulong msgId, ulong param1, ulong param2)
{
	switch (msgId)
	{
	case msgMoveSpeedChanged:
		{
			//���ٶȱ���һ��
			if(mTicks>0)
			{
				mTicks = mTicks * param1/mBaseTimePerTile;
			}

			mBaseTimePerTile = param1;
			
			
			if(gGlobalClient->getSceneManager()&&gGlobalClient->getSceneManager()->getRunType() != RUN_TYPE_EDITOR)
			{
				IEntity* pEntity = (IEntity*)getOwner()->getUserData();
				if(pEntity != NULL && pEntity->GetEntityClass()->IsCreature())
				{
					if (((ICreature*)pEntity)->GetNumProp(CREATURE_PROP_CUR_MOVE_STYLE) == EMoveStyle_Run)
					{
						//��Ϊ�������Ķ�ʱ����׼ȷ,�������Ķ�ʱ�����ÿ��һ��������20ms,������Խ���������ҪԽ��,���ڿͻ���Ҫ�ȷ��������ٶ���һ��
						mBaseTimePerTile += 20;
					}
					else
					{
						mBaseTimePerTile += 10;
					}
				}
			}
		
			mTimePerTile = mBaseTimePerTile;
		}
	}

	MoveComponent::handleMessage(msgId, param1, param2);
}

// ��ɫ����ָ����·���ƶ�
// nodes: ·���б�ָ��(xs::Point*);
// count: ·���б�ڵ���Ŀ
bool MoveComponentMZ::move(const xs::Point* nodes, size_t count)
{
	//IEntity* pEntity = (IEntity*)getOwner()->getUserData();
	//if(pEntity&&!pEntity->GetEntityClass()->IsPerson())
	//	Info("move="<<getTickCount());

	// ������
	if (!nodes || count < 2) // ·��ֻ��һ���ڵ�(�Ǿ��ǵ�ǰTILE��)
		return false;

//	mPileTicks = 0;

	// �Ƿ��Ǵ�ԭ�ؿ�ʼ��·����������Ƿ�����ǿ������
	{
		const xs::Point& ptNewTile = nodes[0];
		const xs::Point& ptCurTile = getOwner()->getTile();
		
		if (ptCurTile.x != ptNewTile.x || ptCurTile.y != ptNewTile.y) // ǿ������
		{
			if(!mPathList.empty()&&( mPathList.next().x == ptNewTile.x && mPathList.next().y == ptNewTile.y) )
			{
				//���ƶ��е���һ��tile,���ǺϷ���
				int i=0;
			}
			else
			{
				if (getOwner()->isMainPlayer())
				{
					Warning("Entity has moved forcibly by Server:"
						<<ptCurTile.x<<","<<ptCurTile.y<<"--->"
						<<ptNewTile.x<<","<<ptNewTile.y<<endl);
				}

				if (gGlobalClient->getSceneManager()->moveEntity(ptCurTile, ptNewTile, getOwner()))
				{
					mPathList.clear(); // ����ϴε�·���б�
					Vector3 curPos;
					gGlobalClient->getSceneManager()->tile2Space(ptNewTile, curPos);

					getOwner()->setSpace(curPos);
				}
				else
				{
					Error("moveEntity failed"<<endl);
				}
			}
			
		}
	}

	if (!mPathList.empty()) // ��һ�εĻ�û����
	{
		const xs::Point& ptCurTile = getOwner()->getTile();
		const xs::Point& back = mPathList.back();
		if (nodes[count-1].x == back.x && nodes[count-1].y == back.y
			&& nodes[0].x == ptCurTile.x && nodes[0].y == ptCurTile.y) // Ŀ����ͬ������
		{
			return true;
		}
		else // �����п���Ҫ��������(�����˳����ǰ�ķ�������Ҫ����)
		{
			//���Ҫ��Ѱ·��ʱ���ǰ���һ��Ŀ������Ѱ��·
			if(nodes[0].x == mPathList.next().x && nodes[0].y == mPathList.next().y )
			{
				mPathList.trimRight(mPathList.current() + 1); // �õ���ǰ·���ĵ�ǰTILE�Ժ������TILE
				mPathList.add(nodes, count);	// �����µ�·��
				return true;
			}
			/*
			else
			{
				//mPathList.trimRight(mPathList.current());
				mPathList.clear();
				mPathList.add(nodes, count);	// �����µ�·��
				resetMoveInfo();
				return true;
			}*/
		}
	}
	//else
	{
		// ����·���б�
		mPathList.clear();
		mPathList.add(nodes, count);
	}

	//��ʱ���ǵ��¶���ԭ��
	//gGlobalClient->getTimerAxis()->SetTimer(0, 1, this);

	resetMoveInfo();
	//mIsMoving = true;

	return true;
}



void MoveComponentMZ::resetMoveInfo()
{
	//Info("resetMoveInfo");
	if(mPathList.empty())
		mTicks = 0;
	//else
	//	Info("mTicks = "<<mTicks<<endl);

	mOldTicks = gGlobalClient->getTimeStamp();
	gGlobalClient->getSceneManager()->tile2Space(mPathList.cur(), mStartPos);
	gGlobalClient->getSceneManager()->tile2Space(mPathList.next(), mNextPos);

	//�ߵ�ʱ��б��*1.414
	mTimePerTile = mBaseTimePerTile*1.414f;

	//IEntity* pEntity = (IEntity*)getOwner()->getUserData();
	//if(pEntity&&pEntity->GetEntityClass()->IsPerson())
	//{
		if(mPathList.cur().x == mPathList.next().x || mPathList.cur().y == mPathList.next().y)
			mTimePerTile = mBaseTimePerTile;
	//}


	//�������ԭ��̤��������Ҫ�ı䷽��
	if(mPathList.cur().x != mPathList.next().x || mPathList.cur().y != mPathList.next().y)
	{
		long angle = calcAngle8_tile(mPathList.cur(), mPathList.next());
		getOwner()->setAngle(angle);
	}	
}



bool MoveComponentMZ::update(ulong curTicks, ulong deltaTicks)
{
	if(mOldTicks>0)
		deltaTicks = gGlobalClient->getTimeStamp() - mOldTicks;

	// �˴�����С���л�����ʱ�������deltaTicks >1000������������Զ�Ѱ·�����У�
	// ������ǿ�����ˣ����Խ�deltaTicks���Ƴ�һ������ķ�Χ����WZH��

	if(deltaTicks>300)
		deltaTicks = 300;
	mOldTicks = curTicks;
	
	//  ���ʵ����ͼ�Ѿ������Ϊ����ɾ�������ٽ����κδ���
    if (getOwner()->isNeedDelete())
    {
        return false;
    }

	if (!mIsMoving) 
		return true;
	if(getOwner()->isMainPlayer())
	{
		//Info("delta:"<<deltaTicks<<endl);
		breakable;
	}
	moveStep(deltaTicks);
	return true;
}

bool MoveComponentMZ::GetNextMovingTile(xs::Point * pt)
{
	if(!mPathList.empty()&& pt )
		*pt = mPathList.next();
	return mIsMoving;
}
xs::Point MoveComponentMZ::GetPixelSpeed(long angle,ulong period)
{
	xs::Point ptRet;
	ptRet.x = 0;
	ptRet.y = 0;
	if(angle==0)
	{
		ptRet.x = 320*period/mTimePerTile;
		ptRet.y = 160*period/mTimePerTile;
	}

	if(angle==45)
	{
		ptRet.x = 640*period/mTimePerTile;
		ptRet.y = 0; 
	}
	if(angle==90)
	{
		ptRet.x = 320*period/mTimePerTile;
		ptRet.y = -(160*period/mTimePerTile);
	}
	if(angle==135)
	{
		ptRet.x = 0;
		ptRet.y = -(320*period/mTimePerTile);
	}
	if(angle==180)
	{
		ptRet.x = -(320*period/mTimePerTile);
		ptRet.y = -(160*period/mTimePerTile);
	}
	
	if(angle==225)
	{
		ptRet.x = -(640*period/mTimePerTile);
		ptRet.y = 0;
	}
	if(angle==270)
	{
		ptRet.x = -(320*period/mTimePerTile);
		ptRet.y = 160*period/mTimePerTile;
	}
	if(angle==315)
	{
		ptRet.x = 0;
		ptRet.y = 320*period/mTimePerTile;
	}

	return ptRet;
}

#define min(a,b)            (((a) < (b)) ? (a) : (b))

// ��������һ��
void MoveComponentMZ::moveStep(ulong period)
{
	//TODO �Ƿ�����赲
	bool bIgnoBlock = false;
	IEntity* pEntity = (IEntity*)getOwner()->getUserData();
	if (NULL != pEntity)
	{
		if (pEntity->GetNumProp(CREATURE_PROP_IGNO_BLCOK) > 0)
		{
			bIgnoBlock = true;
		}
	}

	if (mNeedWait)
	{
		Tile* pTile = gGlobalClient->getSceneManager()->getTile(mPathList.next());
		
		if (!bIgnoBlock && pTile->isBlock())
			return;
		else
			mNeedWait = false;
	}
	//if(period>50)
		//Info("period:"<<period<<endl);
	mTicks += period;

	if (mTicks >= mTimePerTile) // ������һ��TILE���ĵ�
	{
		// ·������һ��
		++mPathList;

		if (mPathList.isLast()) // �����յ�
		{	
			getOwner()->setSpace(mNextPos);
			stopMove();
			//Info("Խ�����ĵ� - ����"<<endl);
		}
		else
		{
			IPerson * pHero = gGlobalClient->getEntityClient()->GetHero();
			IEntity* pEntity = (IEntity*)getOwner()->getUserData();
			if(pHero && pEntity && pHero->GetUID() == pEntity->GetUID())
			{
				// �����ж��Ƿ�رս�������(���ƶ������н����ж�)
				xs::Point ptMapLoc = pHero->GetMapLoc();
				IFormManager* pFromManager = gGlobalClient->getFormManager();
				if (pFromManager)
				{
					pFromManager->CloseTaskFormWinodow(ptMapLoc.x ,ptMapLoc.y,false);
				}

				if (mPathList.current()% (MAX_MOVE_STEP-1) == 0 && mPathList.current() != 0 )
				{ 
					SGameMsgHead gamemsghead;
					gamemsghead.SrcEndPoint = MSG_ENDPOINT_CLIENT;
					gamemsghead.DestEndPoint = MSG_ENDPOINT_ZONE;
					gamemsghead.wKeyModule = MSG_MODULEID_ACTION;
					gamemsghead.wKeyAction = MSG_ACTION_MOVE;

					SMsgActionMaster_CS msgmovemaster;
					msgmovemaster.uidActionMaster = pEntity->GetUID();

					SMsgActionMove_CS msgactionmove;
					ulong ulsize = mPathList.size()- mPathList.current();

					msgactionmove.dwPathLen = min(ulsize,MAX_MOVE_STEP);

					obuf512 obuf;
					obuf.push_back(&gamemsghead, sizeof(gamemsghead));
					obuf.push_back(&msgmovemaster, sizeof(msgmovemaster));
					obuf.push_back(&msgactionmove, sizeof(msgactionmove));
					obuf.push_back(&mPathList.cur(),msgactionmove.dwPathLen * sizeof(xs::Point));
					IConnection * pConn = gGlobalClient->getNetConnection();
					if( pConn) 
					{
						pConn->SendData(obuf.data(), obuf.size());
					}
				}
			}
			//end

			ulong delta = mTicks - (ulong)mTimePerTile;
			mTicks = 0;
			resetMoveInfo();
			
			if (delta > 0)
			{
				//Info("Խ����·��Ŀ���"<<endl);
				moveStep(delta);
			}
				//Info("Խ�����ĵ� - ����ı�"<<endl);
			if (getOwner()->getEntityViewObserver())
				getOwner()->getEntityViewObserver()->onTileChanged(getOwner(), getOwner()->getTile());
		}
		return;
	}
	if (mTicks >= mTimePerTile/2) // Խ��TILE���紦
	{
		Tile* pTile = gGlobalClient->getSceneManager()->getTile(mPathList.next());
		if (!bIgnoBlock && pTile->isBlock())
		{
			//Info("Need Wait!"<<endl);
			mNeedWait = true;
			return;
		}

		//Info("Խ���߽�("<<mPathList.cur().x<<","<<mPathList.cur().y<<")->("
		//	<<mPathList.next().x<<","<<mPathList.next().y<<")"<<endl);
		// �ƶ�ʵ���ڵ�ͼ�ϵ�TILEλ��
		if(getOwner()->isMainPlayer())
		{
			breakable;
		}
		getOwner()->mCalcWorld = false;
		gGlobalClient->getSceneManager()->moveEntity(mPathList.cur(), mPathList.next(), getOwner());

		getOwner()->mCalcWorld = true;
	}

	//�������ԭ��̤��������Ҫ�ı�����
	if(mPathList.cur().x != mPathList.next().x || mPathList.cur().y != mPathList.next().y)
	{
		//��ʹ�ÿռ�������,����2D��Ļ��������
		long angle = calcAngle8_tile(mPathList.cur(), mPathList.next()); //����
		xs::Point ptStart;
		gGlobalClient->getSceneManager()->space2World(mStartPos,ptStart);
		//Info("ptStart:"<<ptStart.x<<","<<ptStart.y<<endl);

		xs::Point ptAdd = GetPixelSpeed(angle,mTicks);

		//��������
		int nAdd = 0;
		if(ptAdd.x>0)
		{
			if(ptAdd.x%10>=5)
				nAdd = 1;
		}
		else
		{
			if(ptAdd.x%10<=-5)
				nAdd = -1;
		}

		ptStart.x +=ptAdd.x/10+nAdd;// + ptAdd.x%10>=5?1:0;
		nAdd = 0;
		if(ptAdd.y>0)
		{
			if(ptAdd.y%10>=5)
				nAdd = 1;
		}
		else
		{
			if(ptAdd.y%10<=-5)
				nAdd = -1;
		}

		ptStart.y +=ptAdd.y/10+nAdd;// + ptAdd.y%10>=5?1:0;
		//Info("ptAdd:"<<ptAdd.x<<","<<ptAdd.y<<endl);
		Vector3 curPos;
		gGlobalClient->getSceneManager()->world2Space(ptStart,curPos);
		getOwner()->setSpace(curPos);
	}	
}


void MoveComponentMZ::stopMove()
{
	if (gGlobalClient->getSceneManager()->getRunType() == RUN_TYPE_EDITOR)
	{
		return;
	}
	
	IEntity* pEntity = (IEntity*)getOwner()->getUserData();
	//if(pEntity&&!pEntity->GetEntityClass()->IsPerson())
	//	Info("stop="<<getTickCount());

	mNeedWait = false;
	mPathList.clear();
	//gGlobalClient->getTimerAxis()->KillTimer(0, this);
	mIsMoving = false;
	getOwner()->onMessage(msgMoveFinished);
	if (getOwner()->getEntityViewObserver())
		getOwner()->getEntityViewObserver()->onMoveFinished(getOwner());
	mTicks = 0;
}

