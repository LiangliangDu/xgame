/******************************************************************
** �ļ���:	MouseStateMgr.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-3-27
** ��  ��:	1.0
** ��  ��:	���״̬����			
** Ӧ  ��:  
******************************************************************/
#pragma once

/************************************************************************/
/* ���״̬                                                                     */
/************************************************************************/
enum _EState
{
	stateAttack = 100,//����״̬
	stateTalk,//��̸״̬
	stateOpen,//����
	stateIdle,//����ڵ�ͼ�Ƕ�λ��
	stateSkill,//ʹ�ü���
	stateCollect,//�ɼ�

	//����ΪUI״̬
	stateUINormal = 1000,//����״̬
	stateUIPick,//ץȡ��Ʒ
    //  �ӿ�����滻��ĳ��Item����Ӹ�״̬��Ŀ����Ϊ��ʵ�ֲ߻���������ӿ������ʰ����Item�����ڿ�����ϵ��ʱ��
    //  ��Item���õ��������λ�ã�ͬʱ��������λ�õ�Item��Ч���򽫱����λItemճ��������ϣ�
    //  �������е����������ǻ��ڰ���ID��Item�ڰ����е�λ�õģ�����ʱ��Ҫճ����Item��λ���Ѿ��������µ�Item��������
    //  ���ȸ��ݱ����λ�õ�Item����ȡ����ĳ�������е�ĳ��λ������Ӧ��Item����ʹ�������Ӧ��Item��λ����Ϣ��ʵ��ճ
    //  ��Ч�������Ǵ�ʱճ��������ϵ�Item���ڴӱ����߼��������Ǵӿ������ʰ��ģ�������Ҫ�����Item���з��ò�����
    //  ֻ�ܽ�����õ�������ϣ����ڴ�ʱ�Ѿ���Ӧ�ø��ݱ�ճ��Item����Ӧ�İ������ж���ʰ��λ�ã��������������״̬��
    //  ���壺������stateReplaceFromShortCut״̬ʱ�������������������ʰ�𱻵��λ�õ�Item���������Ч�������
    //  ���λ�����ڿ�����ϣ����Ὣ֮ǰճ��������ϵ�Item���õ������λ�ã������������ȡ��ճ����
    stateReplaceFromShortCut,
	stateUISplit,//���
	stateUIRepair,//����
	stateUIDrag,//�϶�״̬
	stateAutoMove,//�Զ��ƶ�
	stateInviteTeam,//��������
	stateUIIdentify,//װ������
	stateResetUIsize,  // �����С����
	stateLearnSkill,   // ����ѧϰ����ʱ�����״̬
	stateUnknow
};


#define  MaxSize  24
struct _MouseState
{
	_EState state;
	char szName[MaxSize];
};



class MouseCursorState //�����״̬
{
	std::string m_name;  //״̬ 
	std::string m_cursorImage;//���ͼ
public:
	MouseCursorState(const std::string& ){ m_cursorImage.clear();}
	const std::string& getName() const { return m_name;}
	const std::string& getCursorImage() const
	{
		return m_cursorImage;
	}

	void setCurrorImage(const std::string& cursorImage)
	{
		m_cursorImage = cursorImage;
	}
	virtual void onEnter();
	virtual void onLeave();
};

class MouseCursorStateIdentify: public MouseCursorState
{
public:
	MouseCursorStateIdentify(const std::string& name ):MouseCursorState(name) {}
	virtual void onEnter();
	virtual void onLeave();
};

class MouseCursorStateRepair: public MouseCursorState
{
public:
	MouseCursorStateRepair(const std::string& name ):MouseCursorState(name) {}
	virtual void onEnter();
	virtual void onLeave();
};

class MouseCursorStateMgr : public SingletonEx<MouseCursorStateMgr>
{
	typedef HashMap<_EState,MouseCursorState*> MouseStateMap;
	typedef HashMap<std::string,MouseStateMap::iterator> NameMapIerator;
	MouseStateMap			m_mouseStateMap;
	NameMapIerator			m_nameMapIterator;


	_EState	m_currentState;

	POINT		m_screenPt;				//���������������,��Ʒ����֮�ණ��,����

	                                    //��������λ��,���λ����Ϊ������ʾλ�òο�
public:
	void setMouseCursorPosition(const POINT& pt){ m_screenPt = pt; }

	const POINT& getMouseCursorPosition() const { return m_screenPt;}

	/************************************************************************/
	/* event define                                                         */
	/************************************************************************/
public:
	static const std::string EventOnMouseStateChanged;  //״̬�ı�
	/************************************************************************/
	/* mouse manager                                                        */
	/************************************************************************/
public:
	MouseCursorStateMgr();
	~MouseCursorStateMgr();

	/************************************************************************/
	/* instance                                                             */
	/************************************************************************/

	void _free();
	/************************************************************************/
	/* functions                                                            */
	/************************************************************************/
public:
	/** ��ʼ���¼�
	*/
	void addEvent();

	/** ����״̬���
	*/
	bool setStateCursor(const std::string& stateName,const std::string& cursorImage);

	/** �õ������״̬
	*/
	const _EState& getCurrentState() const { return m_currentState;}

	/** �л���ĳ��״̬
	*/
	bool switchToState(_EState state);

	/************************************************************************/
	/* export for accesable                                                    */
	/************************************************************************/	
	bool toAttack(){ return switchToState(stateAttack);}//����״̬
	bool toTalk(){ return switchToState(stateTalk);}//��̸״̬
	bool toOpen(){ return switchToState(stateOpen);}//����
	bool toIdle(){ return switchToState(stateIdle);}//����ڵ�ͼ�Ƕ�λ��
	bool toSkill(){ return switchToState(stateSkill);}//ʹ�ü���
	bool toCollect(){ return switchToState(stateCollect);}//�ɼ�
	//����ΪUI״̬
	bool toNormal(){ return switchToState(stateUINormal);}//����״̬
	bool toPick(){ return switchToState(stateUIPick);}//ץȡ��Ʒ
    //  �ӿ�����滻��һ��Item��
    bool toReplaceFromShortCut()
    {
        return switchToState(stateReplaceFromShortCut);
    }
	bool toRepair(){ return switchToState(stateUIRepair);}//����
	bool toDrag(){ return switchToState(stateUIDrag);}//�϶�״̬
	bool toSplit(){ return switchToState(stateUISplit);}//���״̬
	bool toIdentify(){ return switchToState(stateUIIdentify);}//������Ʒ����״̬

	bool toInvite(){return switchToState(stateInviteTeam);} //����״̬
	bool toResetUIsize(){return switchToState(stateResetUIsize);} //���ı䴰���С
	bool toLearnSkill(){return switchToState(stateLearnSkill);}  //ѧϰ���＼��


	bool isAttack(){ return m_currentState == stateAttack;}//����״̬
	bool isTalk(){ return m_currentState == stateTalk;}//��̸״̬
	bool isOpen(){ return m_currentState == stateOpen;}//����
	bool isIdle(){ return m_currentState == stateIdle;}//����ڵ�ͼ�Ƕ�λ��
	bool isSkill(){ return m_currentState == stateSkill;}//ʹ�ü���
	// �ɼ�
	bool isCollect()
	{
		return m_currentState == stateCollect;
	}

	//����ΪUI״̬
	bool isNormal(){ return m_currentState == stateUINormal;}//����״̬
	bool isPick(){ return m_currentState == stateUIPick;}//ץȡ��Ʒ
    //  �ӿ�����滻��һ��Item��
    bool isReplaceFromShortCut()
    {
        return m_currentState == stateReplaceFromShortCut;
    }
	bool isRepair(){ return m_currentState == stateUIRepair;}//����
	bool isDrag(){ return m_currentState == stateUIDrag;}//�϶�״̬
	bool isSplit(){ return m_currentState == stateUISplit;}//���״̬
	bool isIdentify() { return m_currentState == stateUIIdentify;}//װ������

	bool isInvite(){return m_currentState == stateInviteTeam;} //����״̬
	bool isResetUIsize(){return m_currentState == stateResetUIsize;} // �Ƿ�Ϊ����UI��С
	bool isLearnSkill(){return m_currentState == stateLearnSkill;}  // �Ƿ�Ϊѧϰ����״̬
};



