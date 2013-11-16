/******************************************************************
** �ļ���:	actor.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-3-18
** ��  ��:	1.0
** ��  ��:	��װ��ɫ��Ϣ,�����ȡ			
** Ӧ  ��:  
******************************************************************/
#pragma  once

class Actor
{
	static DWORD s_equipShowFlag[PERSON_EQUIPPLACE_MAX];//��ɫ��ʾ����
	std::string m_szActorNameBuff;//�����ɫ��
	unsigned short m_currentSelectActor;//��ǰѡ���ɫ
	SMsgLoginServer_ActorInfo m_actorInfo;//��ɫ�б�
	EntityView * m_entity; //����ʾ�Ľ�ɫ
public:

	Actor(SMsgLoginServer_ActorInfo* actorInfo);
	~Actor();

	//�������ص�ֵ���ܹ����棬��Ϊ���
	const std::string &  getActorName(ulong idx);
	const unsigned char & getLevel(ulong idx) const;
	const unsigned char & getSex(ulong idx) const ;
	const unsigned char & getNation(ulong idx) const ;
	const unsigned char & getProfession(ulong idx)  const;
	const unsigned long & getFaceID(ulong idx) const ;
	const unsigned short & getActorNum() const;
	const unsigned char & getActorState(ulong idx) const;
	const unsigned short& getCurrentSelected() const;
	bool					isActorExpired(ulong idx) const;//��ɫ�Ƿ����,7������
	int					  getDeleteTime(ulong idx) const;//��ȡ��ɫɾ��ʱ��
	

	EntityView*	getEntityView() const;
	
	void fillActorInfo(SMsgLoginServer_ActorInfo*ssa);
	SMsgLoginServer_ActorInfo* getActorInfo(){ return &m_actorInfo ;} 
	void udpateActorInfo(SMsgLoginServer_ActorInfo* actorInfo);
	bool setCurrentActorIdx(unsigned long idx); 
	const unsigned long getCurrentActorIdx() const { return m_currentSelectActor;}
	
	void releaseRes();
private:
	void OnEquipShow(DWORD equipId, EntityView * pEntityView, int sex, int  nSmeltSoulLevel);//by cjl,����˵�ǰǿ���ȼ�
};