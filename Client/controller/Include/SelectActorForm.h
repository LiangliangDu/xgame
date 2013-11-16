/******************************************************************
** �ļ���:	SelectActorForm.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-3-14
** ��  ��:	1.0
** ��  ��:	��ɫ����,ѡ��			
** Ӧ  ��:  
******************************************************************/
#pragma  once

class AnimationCallback : public IAnimationCallback
{
	ModelNode*	m_pModel;
public:
	AnimationCallback(ModelNode *pModel);
	~AnimationCallback();

	ModelNode*	getModelNode();
public:
	virtual void onOneCycle(const std::string& animation,int loopTimes);
};

class SelectActorForm :
	public FormBase
{

	/************************************************************************/
	/* �¼�����                                                              */
	/************************************************************************/
public:

	static const std::string EventSelectActorEnter; //֪ͨ�򿪵�½����
	static const std::string EventSelectActorLeave; //֪ͨ�ر�ѡ�����
	static const std::string EventEnterGame; //������Ϸ	
	static const std::string EventBack; //���ص���½����
	static const std::string EventActorListChanged;//��ɫ�б����
	static const std::string EventDeleteActorFail;//ɾ����ɫʧ��
	static const std::string EventRecoverActorFail;//�ָ���ɫʧ��
	static const std::string EventSelectActorGeneralFail;//ѡ���ɫͨ�ô���
	static const std::string EventSelectActorErrorAndQuit;//�������µ�¼�Ĵ���
	static const std::string EventSelectedActorInfo;	//��ǰѡ�еĶ�������

public:
	/************************************************************************/
	/*��������																*/
	/************************************************************************/
	static const std::string PropActorViewWindow;//��ɫ��ʾ����
	static const std::string PropRotateSelectedActor;//ѡ��ѡ��Ľ�ɫ
	static const std::string PropServerInfo;//��������Ϣ

	/************************************************************************/
	/* constructor and deconstructor                                       */
	/************************************************************************/
public:
	SelectActorForm();
	virtual ~SelectActorForm();

	/************************************************************************/
	/* base class virtual function                                          */
	/************************************************************************/
	virtual const std::string& GetErrorAndQuitEventForUI(void) {return EventSelectActorErrorAndQuit; }
public:
	virtual FormType getFormType();

	/** ����Ϊ��ǰ
	*/
	virtual void EnterGame();

	/** ����Ϊ��Ч,Ϊ�л���׼��
	*/
	virtual void onLeave();

	virtual void update();

	virtual void render(IRenderSystem *pRenderSystem);

	/** ��ʼloading
	*/
	void loadStart();

	/** ����loading
	*/
	void loadEnd();

	/************************************************************************/
	/* UI�¼�����                                                           */
	/************************************************************************/

	/** ѡ���ɫ֮�������Ϸ
	*/
	void onEnter();

	/** ������ɫ
	@param name ��ɫ����
	*/
	void onToCreate();

	/** ɾ����ɫ
	*/
	void onDelete();


	void GetSelectActorInfo();

	/**�ָ���ɫ
	*/
	void RecoverActor();

	
	/** ����ɫ�����ϵ�cancel��ʱ�����ESC
	*/
	void onCancel();

	/** update all actor
	*/
	void onUpdateActor();

	/************************************************************************/
	/* message and event                                                     */
	/************************************************************************/
public:
	virtual void onMessage(ulong actionId, SGameMsgHead* head, void* data, size_t len);

	/***************************************************************************/
	/* UI����																*/
	/****************************************************************************/
	bool	SetStringProp(const std::string & propName, const std::string & propValue);
	bool	SetNumProp(const std::string & propName, int propValue);
	int		GetNumProp( const std::string & propName, int param);
	std::string GetStringProp( const std::string propName, int param);

private:
	ImageRect*	m_pBg;
	Camera*		m_pCamera;
	Viewport*	m_pViewport;
	std::list<AnimationCallback*>	m_vCallback;

	std::string m_szActorViewWindow;
	int			m_actorRotateAngle;

	// ������Ч��
	xs::ModelNode* m_pBgEffect;
	EntityView*		m_pBgEffectView;
};