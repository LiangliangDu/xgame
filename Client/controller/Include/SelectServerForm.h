/******************************************************************
** �ļ���:	SelectServerForm.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2010-5-17
** ��  ��:	1.0
** ��  ��:	������ѡ��ҳ��
** Ӧ  ��:  
******************************************************************/
#pragma  once


class SelectServerForm :
	public FormBase
{
	

	/************************************************************************/
	/* �¼�����                                                              */
	/************************************************************************/
public:
    
	static const std::string EventSelectServerEnter; //֪ͨ�򿪷�����ѡ�����
	static const std::string EventSelectServerLeave; //֪ͨ�뿪����ѡ�����
	static const std::string EventSelectServerOk;    //�ɹ�
	static const std::string EventSelectServerCancel; //ʧ��

	static const std::string EventOnSelectServerEnable; //��ť��Ч
	static const std::string EventOnSelectServerDisable; //��ť��Ч
	static const std::string EventUpdateServerListStatus;//���·�����״̬�б�

	/************************************************************************/
	/* constructor and deconstructor                                       */
	/************************************************************************/
public:
	SelectServerForm();
	virtual ~SelectServerForm();

	/************************************************************************/
	/* base class virtual function                                          */
	/************************************************************************/
public:
	virtual FormType getFormType();

	/** ����Ϊ��ǰ
	*/
	virtual void onEnter();

	/** ����Ϊ��Ч,Ϊ�л���׼��
	*/
	virtual void onLeave();

	virtual void update();

	virtual void render(IRenderSystem *pRenderSystem);

	//���ӵ�super center
	bool ConnectSuperCenter(const std::string & strIP, WORD wPort);

	void DisConnectSuperCenter(void);
	
	/************************************************************************/
	/* UI�¼�����                                                           */
	/************************************************************************/

	/** ѡ���½������
	*/
	void onSelectServer(const std::string &strArea,const std::string& strServer);

	/** ��ѡ���¼�������Ľ����ϵ�cancel��ʱ��
	*/
	void onCancel();
	
	/************************************************************************/
	/* message and event                                                     */
	/************************************************************************/
public:
	virtual void onMessage(ulong actionId, SGameMsgHead* head, void* data, size_t len);
	virtual void OnDisconnected( IConnection * conn,DWORD reason );
	virtual void OnError( IConnection * conn,DWORD dwErrorCode );
	virtual void OnConnected( IConnection * conn );
public:
	void getServerInfo(std::string & strArea, std::string & strServer);

private:
	ImageRect*	m_pBg;
	std::string m_strArea;
	std::string m_strServer;

	IConnection*		m_SuperCenterConnection;	/// ���ӳ������ĵ��������ӣ�Ŀǰ���ڻ�ȡ�������б�״̬

};