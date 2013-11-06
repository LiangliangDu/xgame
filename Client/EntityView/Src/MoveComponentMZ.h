//==========================================================================
/**
* @file	  : MoveComponentMZ.h
* @author : 
* created : 2008-1-25   17:40
* purpose : �ƶ����(MZ)
*/
//==========================================================================

#ifndef __MOVECOMPONENTMZ_H__
#define __MOVECOMPONENTMZ_H__

#include "EntityViewImpl.h"
#include "MoveComponent.h"
#include "ISceneManager2.h"
#include "PathNodes.h"
#include "ConfigCreatures.h"
#include "ConfigCreatureRes.h"
/**
�Ľ��������û���꣬������·����Ϊ����������ֹͣʱ������·����ֹͣλ�û��棬��ͨ��tile���ĵ�ʱ������
*/


class MoveComponentMZ : public MoveComponent
{
private:
	PathNodes<POINT>    mPathList;			/// ·������
	float               mBaseTimePerTile;   //����ʱ��
	float				mTimePerTile;		//���ڸĳ��ٶ����ƶ�һ��tile����Ҫ��ʱ��/// �ƶ��ٶ� ���㷽����speed = 32*1.414/����tile���ʱ��
	bool                mNeedWait;			/// �Ƿ���Ϊǰ�����˶���Ҫ�ȴ�?


	ulong			    mTicks,mOldTicks;   /// tick��(����ı������)
	Vector3             mStartPos;				/// ��ʼ����λ��(����ı������)
	Vector3             mNextPos;				/// ��һ��λ��

	bool                mIsMoving;				/// �Ƿ������ƶ�

	// �Ƿ񲥷��ƶ���Ч
	int                 m_nPlayDelay;
public:
	MoveComponentMZ();
	virtual ~MoveComponentMZ();

	virtual void create();
	virtual void close();

	virtual bool update(ulong curTicks, ulong deltaTicks);
	virtual bool handleCommand(ulong cmd, ulong param1, ulong param2);
	virtual void handleMessage(ulong msgId, ulong param1, ulong param2);


	bool move(const POINT* nodes, size_t count);

	// �ƶ�һС��
	void moveStep(ulong period);

	void resetMoveInfo();
	void stopMove();
	bool isMoving(){return mIsMoving;}

	bool GetNextMovingTile(POINT *pt);
	//���������ƶ��ٶ�,��ȡ��ǰ����λ��
	POINT GetPixelSpeed(long angle,ulong period);
};


#endif // __MOVECOMPONENTMZ_H__