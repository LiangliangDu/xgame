/******************************************************************
** �ļ���:	UIStateManager.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-3-14
** ��  ��:	1.0
** ��  ��:	����ģ̬������			
** Ӧ  ��:  
******************************************************************/
#include "IFormManager.h"
#pragma  once

class FormManager;

extern FormManager * gFormManager;

enum FormType
{
	selectServerForm, //ѡ�������
	loginForm,	//��½
	selectActorForm,//��ɫѡ��
	progressForm,   //����
	createActorForm,//������ɫ
	gameForm	//��Ϸ
};
//form����
class FormBase:
	public InputMessageHandler,
	public IMessageHandler, 
	public IConnectionEventHandler
{
public:
	FormBase():m_isConnectedError(false){}
	virtual ~FormBase(){}
	/** �õ����������
	*/
	virtual FormType getFormType() = 0;

	/** ����Ϊ��ǰ
	*/
	virtual void onEnter() = 0;

	/** ����ʱ��
	*/
	virtual void update() = 0;

	virtual void render(IRenderSystem *pRenderSystem) = 0;

	/** ����Ϊ��Ч,Ϊ�л���׼��
	*/
	virtual void onLeave() = 0;


	/** �ж��Ƿ����Ӵ���
	*/
	bool isConnectedError() { return m_isConnectedError == true;}

	/** ���ص�ͼ
	*/
	virtual bool loadMap(ulong actionId, SGameMsgHead* head, void* data, size_t len);


/************************************************************************/
/* interface                                                            */
/************************************************************************/

	virtual void onMouseMessage(MouseMessage& msg){};
	virtual void onKeyMessage(KeyMessage& msg){};
	virtual void OnAccept( IConnection * pIncomingConn,IConnectionEventHandler ** ppHandler ){}

	virtual void OnConnected( IConnection * conn );
	virtual void OnDisconnected( IConnection * conn,DWORD reason );
	virtual void OnRecv( IConnection * conn,LPVOID pData,DWORD dwDataLen );
	virtual void OnError( IConnection * conn,DWORD dwErrorCode );
	virtual void onMessage(ulong actionId, SGameMsgHead* head, void* data, size_t len);
	virtual const std::string& GetErrorAndQuitEventForUI(void) {return EventActorErrorAndQuit;}
protected:
		bool m_isConnectedError;
		static const std::string EventActorErrorAndQuit;
};

class FormManager: public IFormManager,
				   public EventSet
{
	
	
	typedef std::list<FormBase*> LFormBase;
	
	LFormBase		m_lFormBase;  //form �����б�

	FormType		m_currentFormType;

	FormBase*		m_currentForm;	
	Actor*			m_pActor;

	/************************************************************************/
	/* constructor and deconstructor                                        */
	/************************************************************************/
public:
	FormManager();
	~FormManager();

	/** ����
	*/
	bool create();

	/** add Event
	*/
	void addFormEvent(const std::string & eventName);

	/** �л���ָ����form.
	*/
	void switchToForm(FormType formType);

	/** ȡ�������form,ע����,��Ϊ���ܷ��ؿ�ֵ
	*/
	FormBase *getCurrentForm() { return m_currentForm ;}

	void fillActorInfo(SMsgLoginServer_ActorInfo*ssa);

	SMsgLoginServer_ActorInfo* getActorInfo(); 

	bool setCurrentActor( const unsigned long & index);
	const unsigned long getCurrentActor();

	//void setCurrentActor(const unsigned long& actorIndex){ if ( m_pActor) m_pActor->setCurrentActorIdx(actorIndex);}
	//const unsigned long getCurrentActor() const { return m_pActor->getCurrentActorIdx();}

	Actor* getActor() const { return m_pActor; }
	/************************************************************************/
	/* �ӿ�ʵ��                                                              */
	/************************************************************************/
public:
	/**ѡ�������
	/*
	*/
	virtual void toSelectServer();

	/** ��½
	*/
	virtual void toLogin();

	/** ��ɫѡ��
	*/
	virtual void toSelectActor();

	virtual void toCreateActor();

	/** ��Ϸ
	*/
	virtual void toGame() ;

	//������
	virtual void toProgress() ;

	virtual void update() ;

	virtual void render(IRenderSystem *pRenderSystem);

	/** �ͷ�
	*/
	virtual void release();//

	/** ��Ϸ״̬
	*/
	virtual bool isGameState();

	/** ��½״̬
	*/
	virtual bool isLoginState();

	/** ��ɫѡ��״̬
	*/
	virtual bool isSelectState();

	/** ������ɫ״̬
	*/
	virtual bool isCreateActorState();

	//virtual bool shortcut(int shortcutkey);

	virtual void useSkill(const ulong& id,const ulong& subId){} 

	/** �������ֵĽӿ�
	*/
	virtual void PlaySound(DWORD dwSID, int nLoop, float fVolume,int nSountType);

	/** ֹͣ���е�����
	*/
	virtual bool StopAllSound(bool bMute);

	virtual bool StopSoundBySID(DWORD dwSID);

	/** ���дʻ㣻��¶�����촰��ʹ��
	*/
	virtual const std::vector<std::string> & GetBadWordsList();

	/** ���ƶ�ʱ��Ҫȥ�ж��Ƿ�رոý�������
	*/
	virtual void CloseTaskFormWinodow(int x,int y,bool bCloseForce);

	/** ���ô�����С��
	*/
	virtual void SetIconMainWindow(bool bIcon);

	virtual int  addDida(int nLoc, LPCSTR pszNote,int slapse);
	virtual void removeDida(int nIndex);


	//������ҷ�����˳���Ϸ�ͻ��˲���
	virtual void HandleQuitExeOperate(void);

	virtual EFormManangerError GetErrorState(void) const;

	/** UpdteSyetemSet ����ϵͳ����
	*/
	virtual void UpdateSyetemSet(void);
public:
	void getServerInfo(std::string & strArea, std::string & strServer);


};