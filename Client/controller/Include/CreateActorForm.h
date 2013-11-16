/******************************************************************
** �ļ���:	CreateActorForm.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-3-15
** ��  ��:	1.0
** ��  ��:	������ɫ			
** Ӧ  ��:  
******************************************************************/
#pragma  once
#include "deelx.h"

class CreateActorForm :
	public FormBase	
{
	/************************************************************************/
	/* �¼�����                                                              */
	/************************************************************************/
public:

	static const std::string EventCreateActorEnter; //֪ͨ�򿪵�½����
	static const std::string EventCreateActorLeave; //֪ͨ�ر�ѡ�����
	static const std::string EventBack; //���ص���½����
	static const std::string EventCreateActorFail; //������ɫ����
	static const std::string EventCreateActorErrorAndQuit;//�����˳��Ĵ�����Ϣ

	static const std::string EventSelectGenderAnimationFinished;//��ת��ɫ�����������
	static const std::string EventSelectGenderAnimationStart;//ѡ���ɫ�������ſ�ʼ
	static const std::string  EventSelectProfessionSatrt;
	static const std::string EventSelectProfessionEnd;       //

	//�����������������Ե���������
	static const std::string PropCurRenderPage;//��ǰ��Ⱦҳ��
	static const std::string PropCurProfession;//��ǰѡ���ְҵ
	static const std::string PropProfessionVideoWindow;//ְҵ��Ƶ����

	static const std::string PropCurGender;//��ǰ���Ա�
	static const std::string PropInitFaceId;//��ʼͷ��
	static const std::string PropInitFaceIdNum;//��ʼ��ѡ��ͷ������
	static const std::string PropAvailableFaceImg;//��ʼ��ѡ������ͷ��
	static const std::string PropInitClothesId;//��ʼ����
	static const std::string PropInitClothesIdNum;//��ʼ��ѡ����������
	static const std::string PropAvailableClothesImg;//��ʼ��ѡ������

	static const std::string PropShowSelectedHeroWindow;//��ʾѡ��Ӣ�۵Ĵ���
	static const std::string PropShowSelectedPetWindow;//��ʾѡ�еĳ��ﴰ��
	static const std::string PropSelectedHeroRotation;//��תѡ��Ӣ�ۺͳ���

	static const std::string PropHeroName;//����Ӣ�۵�����

	/************************************************************************/
	/* constructor and deconstructor                                       */
	/************************************************************************/
public:
	CreateActorForm();
	virtual ~CreateActorForm();

	/************************************************************************/
	/* base class virtual function                                          */
	/************************************************************************/
	virtual const std::string& GetErrorAndQuitEventForUI(void) {return EventCreateActorErrorAndQuit;}
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


	/************************************************************************/
	/* UI�¼�����                                                           */
	/************************************************************************/
	
	/** ������ɫ
	@param name ��ɫ����
	*/
	int OnCreate(std::string & actorname);


	/** ����ɫ�����ϵ�cancel��ʱ�����ESC
	*/
	void onCancel();

	/**�����ַ�������
	*/
	bool SetStringProp(const std::string & propName, const std::string & propValue);

	/**������ֵ����
	*/
	bool SetNumProp(const std::string & propName, int propValue);

	/**������ֵ����(������������ѡ�����Ա�ѡ��)
	*/
	bool SetNumPropDetail(const std::string & propName, int propValue);
	/**��ȡ��ֵ����
	*/
	int GetNumProp(const std::string & propName);
	/**��ȡ�ַ�������
	*/
	std::string GetStringProp(const std::string & propName, const std::string  & param);

	bool  GetProfessionCanClicked();

	/************************************************************************/
	/* message and event                                                     */
	/************************************************************************/
public:
	virtual void onMessage(ulong actionId, SGameMsgHead* head, void* data, size_t len);

	void renderOnSelectProfession(IRenderSystem * pRenderSystem);//ѡ��ְҵʱ��Ⱦ
	void renderOnSelectGender(IRenderSystem * pRenderSystem,uint profession);//ѡ���Ա�ʱ��Ⱦ
	void renderSelectProfessionActionList(IRenderSystem * pRenderSystem);  //���Ƶ�ǰѡ�е�ģ�Ͷ�����
	void renderOnSelectDetails(IRenderSystem * pRenderSystem);//ѡ������������Ϣʱ��Ⱦ
	void renderBackGround(IRenderSystem * pRenderSystem);//��Ⱦ����
	// ����3���ɵĽ�ɫ
	void renderAllProfessionGender(IRenderSystem * pRenderSystem);
private:
	/** �������е�ģ�����ݣ�ֻ����һ�Σ�
	*/
	void InitLoadAllProfession();

	bool validate();//��֤������ɫ�����ݵ���Ч��

	// ���ƶ�������
	void LeftMoveBackGround(IRenderSystem * pRenderSystem);

	// ���ƶ�������
	void RightMoveBackGround(IRenderSystem * pRenderSystem);

	// ���ƶ�ģ��
	void LeftMoveProfessionModel(IRenderSystem * pRenderSystem,float fAngle);

	// ���ƶ�ģ��
	void RightMoveProfessionModel(IRenderSystem * pRenderSystem,float fAngle);

private:
	ImageRect*	m_pBg; 
	Camera*		m_pCamera;
	float       m_fCamera_x;
	float       m_fCamera_z;
	float       m_fCameraAngle;
	Viewport*	m_pViewport;
	EntityView*		m_pEntity;

	//���ڴ������������Ϣ
	uchar	m_profession;   // ��ǰְҵ
	uchar   m_pOldprofession; // ��һѡ���ְҵ��
	int     m_nRestImage;      // ��Ҫ����λ�õ�ͼƬ��
	float   m_fProfessionImagePos[3];  // 3��ͼƬ��ǰ��λ�ӣ�
	float   m_fCameraProfessionAngle[3];     // �������ת�ĽǶȣ�
	bool    m_bProfessionCanClick ;      // �ڻ���ʱ�Ƿ��ܵ����
	//�Ա�
	uchar	m_gender;
	std::string m_name;
	uint	m_faceid;
	uint	m_creatureid;

	//��ͬ����Ⱦҳ��
	uint	m_curRenderPage;
	float	m_lasttickcount;
	ImageRect * m_pPreLoadImage[4];
	//1,ѡ��ְҵ����Ⱦ״̬
	//IVideoObject * m_pAVI;// ��Ƶ ���Ź�����ʱ���Σ�WZH
	std::string m_strAVIWindow;
	bool m_bVideoRestartFlag;


	
	//2,ѡ���Ա����Ⱦ״̬
	// ����3��ְҵ�� �����Ա��ɫ��������һ�������� WZH
	struct SelectGender
	{
		xs::ModelNode * m_pSelectGender[2];
		std::list<int> m_selectGenderActionList;
		int	m_selectGenderModelRot;//�����ѡ��ĽǶ�
		EntityView * m_selectGenderPreLoaded[10];//ѡ���Ա�ʱԤ�ȼ��ص���Դ����ֹ�����һ����
		bool m_bNeedShowPersonEffect[2];//�Ƿ���ʾ�������������ϵ���Ч
		bool m_bNeedShowPlatFormEffet[2];//�Ƿ���ʾ������ƽ̨�ϵ���Ч
		SelectGender()
		{
			memset( m_pSelectGender,0, sizeof(m_pSelectGender));
			m_selectGenderModelRot = 0;
			memset(m_selectGenderPreLoaded, 0 , sizeof(m_selectGenderPreLoaded));
			for( uint i=0; i<2; ++i)
			{
				m_bNeedShowPersonEffect[i]= false;
				m_bNeedShowPlatFormEffet[i] =false;
			}
		}
	};

	// ����ְҵ��ģ�����ݣ�
	SelectGender  m_stAllProfessionGender[3];

	//3,ѡ���ɫ������Ϣ����Ⱦ״̬
	xs::ModelNode * m_pSelectBgEffect;
	EntityView * m_pSelectedHero;
	std::string m_strShowSelectedHero;
	EntityView * m_pSelectedPet;
	std::string m_strShowSelectedPet;

private:
	CRegexpT<wchar_t>	m_regexp;
	CRandGenerator m_randomgenerator;
};
