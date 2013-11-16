/******************************************************************
** �ļ���:	IFormManager.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-3-14
** ��  ��:	1.0
** ��  ��:	����ģ̬�������ӿ�			
** Ӧ  ��:  
******************************************************************/
#pragma  once

enum EFormManangerError
{
	E_FORM_MANAGER_NO_ERROR = 0,
	E_FORM_MANAGER_NETWORK_DISCONNECT
};

struct IFormManager
{
	//ѡ�������
	virtual void toSelectServer() = 0;

	///** ��½
	//*/
	virtual void toLogin() = 0;

	///** ��ɫѡ��
	//*/
	virtual void toSelectActor() = 0;

	///** ������ɫ����
	//*/
	virtual void toCreateActor() = 0;

	///** ��Ϸ
	//*/
	virtual void toGame() = 0;

	//������
	virtual void toProgress() = 0;

	/** update
	*/
	virtual void update() = 0;

	/** render
	*/
	virtual void render(IRenderSystem *pRenderSystem) = 0;


	/** �ͷ�
	*/
	virtual void release() = 0;//

	/** ��Ϸ״̬
	*/
	virtual bool isGameState() = 0;

	/** ��½״̬
	*/
	virtual bool isLoginState() = 0;

	/** ��ɫѡ��״̬
	*/
	virtual bool isSelectState() = 0;

	/** ������ɫ״̬
	*/
	virtual bool isCreateActorState() = 0;

	virtual int  addDida(int nLoc, LPCSTR pszNote,int slapse)  = 0;
	virtual void removeDida(int nIndex) = 0;

	/** ��ݹ���
	*/
	//virtual bool shortcut(int shortcutkey) = 0;

	/** ����Ʒ��ģ���ṩһ��ʹ�ü��ܵĽӿ�
	*/
	virtual void useSkill(const ulong& id,const ulong& subId) = 0;

	/** �������ֵĽӿ�
	*/
	virtual void PlaySound(DWORD dwSID, int nLoop, float fVolume,int nSountType) = 0;

	/** ֹͣ���е�����
	*/
	virtual bool StopAllSound(bool bMute) = 0;

	/** ֹͣ����
	*/
	virtual bool StopSoundBySID(DWORD dwSID) = 0;

	/** ���дʻ㣻��¶�����촰��ʹ��
	*/
	virtual const std::vector<std::string> & GetBadWordsList() = 0;

	/** ���ƶ�ʱ��Ҫȥ�ж��Ƿ�رոý�������
	*/
    virtual void CloseTaskFormWinodow(int x,int y,bool bCloseForce) = 0;

	//������ҷ�����˳���Ϸ�ͻ��˲���
	virtual void HandleQuitExeOperate(void) = 0;

	/** ���ô�����С��
	*/
	virtual void SetIconMainWindow(bool bIcon) = 0;

	/** ��ȡ����״̬�����������Ӵ���
	*/
	virtual EFormManangerError GetErrorState(void) const = 0;

	/** UpdateSyetemSet ����ϵͳ����
	*/
	virtual void UpdateSyetemSet(void) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(_LIB) || defined(CONTROLLERGAME_STATIC_LIB)		/// ��̬��汾
#	pragma comment(lib, MAKE_LIB_NAME(xs_cfm))
extern "C" IFormManager * LoadCFM(void);
#	define	CreateFormManagerProc	LoadCFM
#else														/// ��̬��汾
typedef IFormManager * (RKT_CDECL *procCreateFormManager)(void);
#	define	CreateFormManagerProc	DllApi<procCreateFormManager>::load(MAKE_DLL_NAME(xs_cfm), "LoadCFM")
#endif
