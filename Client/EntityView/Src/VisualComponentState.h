#ifndef __VISUALCOMPONENTSTATE_H__
#define __VISUALCOMPONENTSTATE_H__
#include <map>

class VisualComponentMZ;

class CVisualComponentState //���״̬�ӿ�
{
	friend class  CVisualComponentStateMgr;
private:
	void OnEnter();
	void OnLeave();
	void SetState(EVisualComponentState state);
private:
	EVisualComponentState m_eState;//״̬
};

class CVisualComponentStateMgr: public TimerHandler
{
private:
	CVisualComponentState m_StateSet[EVCS_Max];
	VisualComponentMZ * m_pMaster;
	EVisualComponentState m_CurState;
	const static DWORD s_fight2PeaceInterval;

public:
	////////////////////TimerHandler////////////////////
	void OnTimer(unsigned long dwTimerID);
public:
	CVisualComponentStateMgr();
	bool Create(VisualComponentMZ * pComp);
	~CVisualComponentStateMgr();
	void OnCommand(EntityCommand cmd);//��ͬ�������ı䵱ǰ״̬
	inline EVisualComponentState GetCurrentState() { return m_CurState; };//��ȡ��ǰ״̬
	void initCommandToStateMap();
private:
	static bool		s_bInitMapCommandToState;//�Ƿ��ʼ����
	typedef std::map<uint, EVisualComponentState> CommandToStateMap;
	static CommandToStateMap* s_pMapCommandToState;//ʵ�����״̬��ӳ��
	int				m_nCurCommand;
};

#endif
