/******************************************************************
** �ļ���:	SkillForm.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-4-7
** ��  ��:	1.0
** ��  ��:	���ܴ���			
** Ӧ  ��:  
******************************************************************/
#pragma once

enum EXPProgress
{
	EXPProgress_Full      = 1,        // XP���ܲ�����Ϊ��״̬
	EXPProgress_Empty     = 2,        // XP���ܲ�����Ϊ��״̬
	EXPProgress_BeginDec  = 3,        // XP���ܲ۽��ȿ�ʼ�ݼ�
	EXPProgress_PersonDie = 4,        // ��������XP���ܲ�״̬
};

//	�������
enum eSkillFormType
{
	eBranchOne = 1,
	eBranchTwo,
	eBranchThree,
	eGenius,
	eMaxPage,
};

//������Ϣ
struct _SkillInfo_
{	
	int			nSlotIndex;	//�����츳�Ĳ�������
    uint        unBranch;	//���ܷ�֧��	
	int			index;		//��ְҵ�����б��е�����
	ulong		maxLevel;	//��󼶱�
	std::string name;		//����
	std::string normalImage;
	std::string hoverImage;
	std::string disableImage;
	std::string normalImageExt;	//�ڶ���̬
	std::string hoverImageExt;
	std::string disableImageExt;
};

class SKillForm : public SingletonEx<SKillForm>, public IEventExecuteSink
{
	//��ʾ
	static const std::string	EventOnSkillFormEnter;

	//�ر�
	static const std::string    EventOnSkillFormLeave; 

	//����
	static const std::string	EventOnUpdateSkill;

	//�����츳����
	static const std::string    EventOnUpdateGeniusPoints;

	//��ʼ��ϵ���ƺ�ҳ��
	static const std::string    EventOnSkillFormBranchInit;

 	// ��ʾXPͼ��
 	static const std::string	EventOnShowXPSkill; 	

 	// ʼ��XP��
 	static const std::string	EventOnInitXPSlot; 

	// �ȼ�δ��10��ʱ���츳��ҳ��tip��ʾ
	static const std::string    EventOnGeniusTip;

	// ������ȴ
	static const std::string	EventOnCoolingSkill;

	//����item��ʶID
	ulong						m_slotID;							

public:
	SKillForm();
	~SKillForm(){}

	//  �¼����ĺ�ȡ�����Ĵ���
	void Subscriber();

	void UnSubscriber();

	void ReadSkillAndGeniusInfo();

	void OpenSkillForm();

	void CloseSkillForm();

	void Update();

	void UpdateGeniusPoints();

	void UpgradeSkill(bool isSkill, int nSlotIndex, int upCount);

	std::string GetTooltip(const int& pos, bool bShortCut = false);

	virtual void OnExecute(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen);

    //  ��SKillForm�������ʵ���У�Ҫ������¼���ܵ���������ͨ���������Լ���
    //  ���д����Ա����߼��ϵ���������Ϊ��λ�������Ͼ�ֻ��SkillForm�в���������ģ�
 	bool GetGeniusInfoBySlotPos(const int& pos, _SkillInfo_& info) const;
	//	����UIλ���Ҽ���
	bool GetSkillInfoBySlotPos(const int& pos, _SkillInfo_& info) const;
	//  ���ݼ����������Ҽ������츳
	bool GetSkillInfoByIndex(int nSkillIndex, _SkillInfo_& SkillInfo) const;

     //  �л����ܷ�֧��
     void SwitchSkillBranch(int unNewSkillBranchIndex, bool bUpdate);

	 //ĳϵ��ҳ�������
	 void CountSkillBranchPageNum(SkillBranchInitArgs& args);
	 int CountMaxPage(const int nums);

	 //����ϵ����Ϸ�ҳ
	 void SetCurBranchCurPage(int curPage, bool bUpdate);

	 //���������ܣ��϶������������ϵ������
	 bool LeftClicked(int pos);

 	 bool leftClickedXPSkill(int pos);

	//�Ƿ�Ϊskillformģ��
 	bool isSkillSlot(ulong id) { return m_slotID == id;}

 	bool isSkillSlotXP(ulong id) { return m_slotXPID == id;}

	//�����ǳ��ﻹ������(Ĭ��Ϊ0����ʹ�ü���ʱ����Ӧ�����UID)
	void UseSkill(const int& idx, LONGLONG Useruid = 0);

	void UseTileSkill(POINT pt, bool bXP);

 	int getSkillXPImage(SkillId* pSkillList, std::string& tooltip, int nIndex);

	//ϴ�츳
	void ResetGeniusPoints();

	//ȡѧϰ����Lv����Ҫ��money
	int GetLearnSkillNeedMoney(int nSlotIndex);

	// ȡ�츳��tip����
	std::string GetGeniusTip(int nSlotIndex, int geniusLv, int tempGeniusPoint);

	// �Ƿ����츳���
	bool IsEanbleGeniusWnd();

	// �ȼ�С��10��ʱ���츳��ҳ��tip����
	std::string GetGeniusPageTooltipText();

	// ������ȴ
	void SKillForm::coolingSkill(const ulong& id);

	bool	IsSkillTargetValid(SkillContext *pContext);

protected:
	void SetArgs(SkillUpdateArgs& args, const _SkillInfo_& info);

 	// ����EVENT_XPSKILL_CANUSE�¼�
 	void ProcEventXPSkillCanUse(void);
 
 	// ����EVENT_XPSKILL_TIMEOUT�¼�
 	void ProcEventXPSkillTimeout(LPCSTR pszContext, int nLen);
 
 	// ����EVENT_XPSKILL_CANBOOT�¼�
 	void ProcEventXPSkillCanBoot(void);

	// ����������ѧ�����ǰ��,ѧ���еȼ�Ҫ��͵���ǰ��, δѧ���Ҳһ������
	void SortSkill(int branch);

	// �ж��Ƿ�ﵽ��һ����ѧϰ�ȼ�
	bool NextLevelIsEnable(SkillId skillId);

protected:
	std::vector<_SkillInfo_>  m_SkillsBranchOne;	//��1ϵ
	std::vector<_SkillInfo_>  m_SkillsBranchTwo;	//��2ϵ
	std::vector<_SkillInfo_>  m_Genius;				//ְҵ�����츳
	std::vector<_SkillInfo_>  m_XP;                 //XP����
	std::vector<string>       m_SkillBranchName;	//���ܷ�֧���ƣ�

	int						  m_CurType;			//��ǰѡ�񣨵�һϵ���ܶ�ϵ���������ܣ��츳��                   
	int                       m_CurBranchCurPage;   //��ǰϵ�ĵ�ǰҳ
	std::vector<int>          m_BranchMaxPage;		//ÿϵ��������ҳ��
	ulong					  m_ulTaskID;			//����ɼ���Ծ�ͷ�ʱ���󶨵�����ID

 	ulong					  m_curXPSlotID;		//XP���ܲ�UI��Чģ��ID 	
 	ulong					  m_ulXPProgressBar;	//XP�����������󲥷ŵ���Ч 
 	ulong					  m_slotXPID;           //XP���ܱ�ʶID
};