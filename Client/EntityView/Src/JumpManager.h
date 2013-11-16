//==========================================================================
/**
* @file	  : JumpManager.h
* @author : 
* created : 2009-12-12   15:27
* purpose : ��Ծ����
*/
//==========================================================================

#ifndef __JUMPMANAGER_H__
#define __JUMPMANAGER_H__

class EntityViewImpl;
enum JUMPSTATE
{
	JUMPSTATE_READY,
	JUMPSTATE_STATR,
	JUMPSTATE_MIDWAY,
	JUMPSTATE_END,
	JUMPSTATE_FINISH
};

struct IJumpObserver
{
	virtual void onFinished() = 0;
};

// ������Ծ��״̬������
class JumpManager
{
	ulong				mStartTick;
	Vector3				mStartPos, mEndPos, mDistance;
	float				m_a,m_x1,m_x2;//�����߷���ϵ��
	float				m_jumpHeight; //��Ծ�ĵ�ǰ�߶�
	ulong				m_AllTick;//��Ծ��ʱ�䳤
	float				m_MoveSpeed;//�ƶ��ٶ�
	xs::Point			    mTargetTile;
	IJumpObserver*	    mObserver;

	ulong				mAniTick;//��ǰ����ʱ��

	JUMPSTATE mState;
public:
	JumpManager();
	void setObserver(IJumpObserver* ob)	{ mObserver = ob; }
	bool create(const xs::Point& ptBegin, const xs::Point& ptEnd);
	bool update(ulong tick, ulong deltaTick,EntityViewImpl* pView);
	bool IsEnd(ulong tick);
	JUMPSTATE GetJumpState();
	void SetMoveSpeed(float moveSpeed);
	void JumpEnd(EntityViewImpl* pView);
	int  GetAllTicks(){return m_AllTick;}
	float GetjumpHeight(){return m_jumpHeight;}
	//ulong GetAniTime(){return mAniTick;}
};

#endif // __SHADOWMANAGER_H__