/******************************************************************
** �ļ���:	LoginForm.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-3-14
** ��  ��:	1.0
** ��  ��:	��Ʒ��������			
** Ӧ  ��:  
******************************************************************/
#pragma  once


class LoginForm :
	public FormBase
{
	

	/************************************************************************/
	/* �¼�����                                                              */
	/************************************************************************/
public:
    
	static const std::string EventLoginEnter; //֪ͨ�򿪵�½����
	static const std::string EventLoginLeave; //֪ͨ�򿪵�½����
	static const std::string EventLoginOk; //��½�ɹ�
	static const std::string EventLoginFail; //��½ʧ��

	static const std::string EventOnLoginEnable; //��ť��Ч
	static const std::string EventOnLoginDisable; //��ť��Ч
	static const std::string EventOnReloadUserName;

	//����
	static const std::string PropShowGameMakersWndName;//��ʾ��Ϸ�����˴���,���������ʱֻ����������Ƿ�Ӧ����ʾ��Ϸ������
	static const std::string PropGameMakersList;//��Ϸ�������б�

	static const std::string EventLoginQueueUpdate; //��¼�Ŷ�

	std::string m_userName;
	std::string m_password;

	/************************************************************************/
	/* constructor and deconstructor                                       */
	/************************************************************************/
public:
	LoginForm();
	virtual ~LoginForm();

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

	void   sendLogin();

	void   sendRequestLogin();
	
	/************************************************************************/
	/* UI�¼�����                                                           */
	/************************************************************************/

	/** ��½������
	*/
	void onLogin(const std::string &username,const std::string& password);

	/** ����½�����ϵ�cancel��ʱ��
	*/
	void onCancel();

	//��������
	bool	SetStringProp(const std::string & propName, const std::string & propValue);
	
	/************************************************************************/
	/* message and event                                                     */
	/************************************************************************/
public:
	virtual void onMessage(ulong actionId, SGameMsgHead* head, void* data, size_t len);
	virtual void OnDisconnected( IConnection * conn,DWORD reason );
	virtual void OnError( IConnection * conn,DWORD dwErrorCode );
	virtual void OnConnected( IConnection * conn );
	int CharToHex( unsigned char  D[],unsigned char  S[], long size_d);

private:
	ImageRect*	m_pBg;
	bool m_bConnectedServer;

	uchar tmpkey[33];  //�����¼�ĻỰ��Կ
	char *m_Key;

	std::string m_szShowGameMakersWndName;
	std::vector< std::string> m_GamemakersList;
	float m_fGameMakersListShift;
	float m_fGameMakersListLineWidth;
};