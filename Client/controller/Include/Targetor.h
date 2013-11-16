/******************************************************************
** �ļ���:	Targetor.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-4-3
** ��  ��:	1.0
** ��  ��:	Ŀ��״̬����			
** Ӧ  ��:  
******************************************************************/
#pragma once

#include "TimerHandler.h"

class TargetorMgr:
	public SingletonEx<TargetorMgr>,
	public IMessageExecuteSink,
	public IEventExecuteSink,
	public TimerHandler
{
	UID		m_targetUID;    //Ŀ��UID

	bool    m_bPermanentSelect; // �Ƿ�Ϊ����ѡ��

	UID		m_boxUID;		//Ŀ�걦��

//	EffectContext m_ec;     //�ŵ׹�Ч
	/************************************************************************/
	/* Event define                                                         */
	/************************************************************************/
public:
	static const std::string		EventOnTargetEnter;  //ѡ��Ŀ��
	static const std::string		EventOnTargetLeave;	 //ʧȥĿ��
	static const std::string		EventOnTargetSwitch; //�ı�Ŀ��
	/************************************************************************/
	/* constructor and deconstructor                                        */
	/************************************************************************/
public:
	TargetorMgr();
	~TargetorMgr();

	void create();
	void close();



	/************************************************************************/
	/* event functions                                                           */
	/************************************************************************/
public:
	/** �õ�Ŀ���¼�
	*/
	void onTargetorEnter(EventArgs& args);

	/** ʧȥĿ���¼�
	*/
	void onTargetorLeave(EventArgs& args);

	/** �ı�Ŀ���¼�
	*/
	void onTargetorSwitch(EventArgs& args);

	virtual void OnTimer( unsigned long dwTimerID );

public:
	/** ����Ŀ��
	*/
	void setTarget(const UID& uid, bool bPermanentSelect = false, bool bNotShowTargetFrame = false, bool bNotShowEffect = false);
	void setTarget(IEntity* pEntity, bool bPermanentSelect = false, bool bNotShowTargetFrame = false, bool bNotShowEffect = false);
	const UID getTarget() const;

	//void SetPermanentSelect(bool bPermanentSelect);

	const bool TargetorMgr::IsPermanentSelect(void) const;

    //  ��¼��굱ǰλ�ã�
    void SetGoundTile(const POINT& pointTile);
    //  ��ȡ��굱ǰλ�ã�
    const POINT& GetGroundTile() const;

	void lost();	

	void updateProperty(IEntity* pEntity);

	/** ��Ҵ��ڷ�����״̬ʱ,��ѡ��ĳ����ʱ,��ɫӦת�����������
	�����Ĵ������ǿ��ѡ��Ŀ�����Ӧ 
	�������������,ѡ���Ժ���������,�ͻᷢ�ֽ�ɫ��ת��ȥ����
	*/
	void startTurnHead();

	void stopTurnHead();

	/** �����ͣʱҪ���Ʊ��������
	*/
	void SelectBox(LONGLONG uidBox);

	void UnSelectedBox();

	/************************************************************************/
	/* ������                                                                     */
	/************************************************************************/
	// �˴����
	void requestExchange(LONGLONG uid);

	/************************************************************************/
	/* interface functions                                                  */
	/************************************************************************/
public:
	virtual void	OnExecute(DWORD dwMsgID, SGameMsgHead * pGameMsgHead, LPCSTR pszMsg, int nLen);

	virtual void	OnExecute(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen);

private:
	void capture(bool bNotShowTargetFrame, bool bNotShowEffect);
protected:
    //  ��굱ǰλ�ã�������ڵ����ƶ�ʱ��¼��굱ǰ����λ�õ�Tile��
    POINT m_pointGroundTile;
};
