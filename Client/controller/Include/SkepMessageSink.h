/******************************************************************
** �ļ���:	SkepMessageSink.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-3-19
** ��  ��:	1.0
** ��  ��:	��Ʒ��������			
** Ӧ  ��:  
******************************************************************/
#pragma once

class SkepMessageSink: public SingletonEx<SkepMessageSink>,public IMessageExecuteSink
{
	// ��ǰ��ģ��ID
	ulong			m_curAniID;

	// ��ǰ�鿴���Ա�
	ulong           m_ulSex;

	// ��ǰ�鿴��ģ�͵���ģID
	ulong           m_ulNakedResId;

	/************************************************************************/
	/* event define                                                         */
	/************************************************************************/
public:
	static const std::string  EventCreateSkep;  //֪ͨ������Ʒ��
	static const std::string  EquipInfo;		//�鿴����װ����ʾ��
	static const std::string  PropInfo;			// �鿴��������

	/************************************************************************/
	/* constructor and deconstructor                                       */
	/************************************************************************/
public:
	SkepMessageSink();
	~SkepMessageSink();
	/************************************************************************/
	/* interface function                                                   */
	/************************************************************************/
	/** 
	@param   dwMsgID ����ϢID
	@param   pszMsg ����Ϣ�ṹ
	@param   nLen ����Ϣ����
	@return  
	*/
	virtual void OnExecute(DWORD dwMsgID, SGameMsgHead * pGameMsgHead, LPCSTR pszMsg, int nLen);
	// ��ת
	void         RotatePersonView(float fAngle);

	//
	void		OnClose();
};