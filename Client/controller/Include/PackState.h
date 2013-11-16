/******************************************************************
** �ļ���:	PackState.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-3-31
** ��  ��:	1.0
** ��  ��:	��Ʒ��״̬			
** Ӧ  ��:  
******************************************************************/
#pragma once

class PackState
{
	bool	m_isOpen;
	UID		m_uidNpc;	
	ulong	m_ulPackID;

	bool	m_observed; //

	bool	m_isMine;

	std::list<int> m_lUnits;

public:
	PackState(ulong ulPacked,bool isMine):m_observed(false),m_isMine(isMine){ m_ulPackID = ulPacked;m_lUnits.clear();}
	~PackState(){deselectAll();};

	/************************************************************************/
	/* �ⲿ״̬����                                                         */
	/************************************************************************/
public:
	/** �ж�ָ���İ��Ƿ�򿪣�ֻ��ʾ��
	*/
	bool isPackOpen(){ return m_isOpen; }
	

	void setObserved(){ m_observed = true;}
	bool isObserved() { return m_observed;}

	bool isMine() {return m_isMine;}

	/** ���ùر�״̬
	@param isOpen ����״̬
	*/
	void setPackState(bool isOpen){ m_isOpen = isOpen; }
	void setOwner(const UID uid){ m_uidNpc = uid;}


	const UID& getOwner() const { return m_uidNpc;}

	/** ѡ����
	*/
	void select(int iPlace);

	/** ȡ��ѡ��
	*/
	void deselect(int iPlace);

	/** ȡ��ѡ������
	*/
	void deselectAll();

	void cooling(const ulong& id);
	std::string getTooltip(const ulong& id);

	void updateTooltip();
	void updateTooltip(LONGLONG uid);//���°���������ĳһ����Ʒ��tooltip
};
