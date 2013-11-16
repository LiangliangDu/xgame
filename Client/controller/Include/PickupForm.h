/******************************************************************
** �ļ���:	PickupForm.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-4-8
** ��  ��:	1.0
** ��  ��:	����			
** Ӧ  ��:  
******************************************************************/
#pragma once

class PickupForm : public TimerHandler,public IEventExecuteSink,public SingletonEx<PickupForm>
{
	enum
	{
		ITEM_TYPE_GOODS = 1,
		ITEM_TYPE_PETS  = 2,
	};
	/************************************************************************/
	/* �¼�����                                                             */
	/************************************************************************/
	static const	std::string EventOnAddGoodsSuccess;     // ȥ����Ч��
	static const    std::string EventOpenItemHelpToolTipForm; // �Ƿ���Ҫ����ʾ���
	/************************************************************************/
	/* data member                                                          */
	/************************************************************************/
	int		m_iCount;     //����
	UID		m_uid;			//�����UID
	bool	m_isOpen;		//��ȡ���ǹر�
	ulong	m_timeId;
	bool	m_running;
public:
	PickupForm();

	~PickupForm();

	void Init();

	void UnInit();

	void setUID(const UID& uid);

	void setOpenState(bool setting);

	bool isOpen(){ return m_isOpen ;}
	void setCount(int count) { m_iCount = count ;}

	virtual void OnExecute(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen);

	/************************************************************************/
	/* event handler                                                        */
	/************************************************************************/
	void open(const UID& uid);
	void close();

	bool pick(ulong ulPackID,int iPos,int iTartPos = -1 );

	void reset();

	void startTimer();
	void endTimer();

	virtual void OnTimer( unsigned long dwTimerID );
	
	bool CanPick();

	void  Update();
private:

	// ��Ӧ��Ʒʰȡ�ɹ��¼�
	void                    OnEventAddGoodsSuccess(LPCSTR pszContext, int nLen);

	//������ʾ����ı�
	string                  GetAddItemToolTip(IEntity* pEntity);

	//�����Ʒʱ��Ҫ�ڰ�������������ʾ��
	int                    AddEquipIconInBagEffectTooltip(IEquipment *pEntity);

};