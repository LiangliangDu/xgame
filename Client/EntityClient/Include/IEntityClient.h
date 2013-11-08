/*******************************************************************
 ** �ļ���:	e:\Rocket\Client\EntityClient\Include\IEntityClient.h
 ** ��  Ȩ:	(C)
 **
 ** ��  ��:	2008/1/22  14:46
 ** ��  ��:	1.0
 ** ��  ��:	ʵ��ͻ���
 ** Ӧ  ��:
 
 **************************** �޸ļ�¼ ******************************
 ** �޸���:
 ** ��  ��:
 ** ��  ��:
 ********************************************************************/
#pragma once


// ����
struct IMessageVoteSink;
struct IMessageExecuteSink;
struct IEntityClass;
struct IEntity;
struct ICreature;
struct IPerson;
struct IMonster;
struct IGoods;
struct IEquipment;
struct INonequipableGoods;
struct IBox;
struct IMast;
struct IEntityPart;
struct IEntityClient;
class  EntityView;
struct ISchemeCenter;
struct SGameMsgHead;
struct IItemVisitor;
struct IEffect;
struct ISkepGoods;
struct IPet;
struct IPetPart;
/////////////////////////////��ϢͶƱsink///////////////////////////////
struct IMessageVoteSink
{
	/**
     @param   dwMsgID ����ϢID
     @param   pszMsg ����Ϣ�ṹ
     @param   nLen ����Ϣ����
     @return  ����false����ʾ�ض�
     */
	virtual bool				OnVote(DWORD dwMsgID, SGameMsgHead * pGameMsgHead, LPCSTR pszMsg, int nLen) = 0;
};

/////////////////////////////��Ϣִ��sink///////////////////////////////
struct IMessageExecuteSink
{
	/**
     @param   dwMsgID ����ϢID
     @param   pszMsg ����Ϣ�ṹ
     @param   nLen ����Ϣ����
     @return
     */
	virtual void				OnExecute(DWORD dwMsgID, SGameMsgHead * pGameMsgHead, LPCSTR pszMsg, int nLen) = 0;
};

/////////////////////////////ʵ������///////////////////////////////
struct IEntityClass
{
	/** �Ƿ�Ϊ����
     @param
     @param
     @return
     */
	virtual bool				IsPerson(void) = 0;
    
	/** �Ƿ�Ϊ����
     @param
     @param
     @return
     */
	virtual bool				IsMonster(void) = 0;
	/** �Ƿ�Ϊ����
     @param
     @param
     @return
     */
	virtual bool               IsPet(void) = 0;
    
	/** �Ƿ�Ϊװ��
     @param
     @param
     @return
     */
	virtual bool				IsEquipment(void) = 0;
    
	/** �Ƿ�Ϊ��װ������Ʒ
     @param
     @param
     @return
     */
	virtual bool				IsNonequipableGoods(void) = 0;
    
	/** �Ƿ�Ϊ����
     @param
     @param
     @return
     */
	virtual bool				IsBox(void) = 0;
    
	/** �Ƿ�Ϊ��ˣ�̯λ��������... ...��
     @param
     @param
     @return
     */
	virtual bool				IsMast(void) = 0;
    
	/** �Ƿ�Ϊ����
     @param
     @param
     @return
     */
	virtual bool				IsCreature(void) = 0;
    
	/** �Ƿ�Ϊ��Ʒ
     @param
     @param
     @return
     */
	virtual bool				IsGoods(void) = 0;
    
	/** ȡ����Ϸ���ͣ�tEntity_Class_Person�� tEntity_Class_Monster��tEntity_Class_Equipment��tEntity_Class_NonequipableGoods��
     @param
     @param
     @return
     */
	virtual DWORD				Class(void) = 0;
};

//////////////////////////////ʵ��//////////////////////////////////
struct IEntity
{
	/** �ͷ�
     @param
     @param
     @return
     */
	virtual void				Release(void) = 0;
    
	/** ȡ��ʵ������
     @param
     @param
     @return
     */
	virtual IEntityClass *		GetEntityClass(void) = 0;
    
	/** ȡ��UID
     @param
     @param
     @return
     */
	virtual LONGLONG			GetUID(void) = 0;
    
	/** ȡ�����ڵĵ�ͼλ��
     @param
     @param
     @return
     */
	virtual xs::Point				GetMapLoc(void) = 0;
    
	/** ������ֵ����
     @param   nValue ������ֵ
     @param
     @return
     */
	virtual bool				SetNumProp(DWORD dwPropID, int nValue) = 0;
    
	/** ȡ����ֵ����
     @param
     @param
     @return
     */
	virtual int					GetNumProp(DWORD dwPropID) = 0;
    
	/** �����ַ�����
     @param   pszValue ������ֵ
     @param
     @return
     */
	virtual bool				SetStrProp(DWORD dwPropID, LPCSTR pszValue, int nLen) = 0;
    
	/** ������������
     @param
     @param
     @return
     */
	virtual bool				BatchUpdateProp(LPCSTR pszProp, int nLen) = 0;
    
	/** ��Ϣ
     @param
     @param
     @return
     */
	virtual void				OnMessage(DWORD dwMsgID, SGameMsgHead * pGameMsgHead, LPCSTR pszMsg, int nLen) = 0;
    
	/** ����ͶƱ��Ϣ
     @param
     @param
     @return
     */
	virtual bool				Subscibe(DWORD dwMsgID, IMessageVoteSink * pVoteSink, LPCSTR pszDesc) = 0;
    
	/** ȡ������ͶƱ��Ϣ
     @param
     @param
     @return
     */
	virtual bool				UnSubscibe(DWORD dwMsgID, IMessageVoteSink * pVoteSink) = 0;
    
	/** ����ִ����Ϣ
     @param
     @param
     @return
     */
	virtual bool				Subscibe(DWORD dwMsgID, IMessageExecuteSink * pExecuteSink, LPCSTR pszDesc) = 0;
    
	/** ȡ������ִ����Ϣ
     @param
     @param
     @return
     */
	virtual bool				UnSubscibe(DWORD dwMsgID, IMessageExecuteSink * pExecuteSink) = 0;
    
	/** ȡ��ʵ����ͼ����ӿ�
     @param
     @param
     @return
     */
	virtual EntityView *		GetEntityView(void) = 0;
    
	/** ȡ���¼�Դ����,SOURCE_TYPE_PERSON, SOURCE_TYPE_MONSTER ... ...
     @param
     @param
     @return
     */
	virtual BYTE				GetEventSourceType(void) = 0;
    
	/**
     @param
     @param
     @return
     */
	virtual void				Visit(IItemVisitor * pVisitor) = 0;
    
	/** �Ƿ��ܽ��ף����װ����һ����Ʒ�����Խ���
     @param
     @param
     @return
     */
	virtual bool				CanTrade(ISkepGoods * pSkepGoods,char * errorMsg = NULL) = 0;
};

////////////////////////////�������////////////////////////////////////
struct ICreature : public IEntity
{
	/** ����ʵ�岿��
     @param
     @param
     @return
     */
	virtual bool				AddEntityPart(IEntityPart * pEntityPart) = 0;
    
	/** �Ƴ�ʵ�岿��
     @param
     @param
     @return
     */
	virtual bool				RemoveEntityPart(DWORD dwPartID) = 0;
    
	/** ȡ��ʵ�岿��
     @param
     @param
     @return
     */
	virtual IEntityPart *		GetEntityPart(DWORD dwPartID) = 0;
    
	/** �Ƿ������ƶ�
     @param
     @param
     @return
     */
	virtual bool				IsMoving(void) = 0;
    
	/** ��ȡͷ��ID
     @param
     @param
     @return
     */
	virtual int                 GetFaceID(void) = 0;
    
	/** by cjl ����ֻ�漰����ۺ�����
     @param   -1��ʾ��ԭ������͸��ݱ����޸�����
     @param	 nakeResID��Ϊ0ʱ����ʾ�޸ı���������Դ
     @param   ����ʣ��ʱ�䣬Ϊ0ʱ���ʾ����
     @return
     */
	virtual bool ChangeBody(int modeID, int nakeResID = 0, int t = 0) = 0;
};

////////////////////////////�������////////////////////////////////////
//by cjl
struct SPresentSchemeInfoBase;
//end cjl
struct IPerson : public ICreature
{
	/** ȡ����������
     @param
     @param
     @return
     */
	virtual LPCSTR				GetName(void) = 0;
    
	/** ������ǰ����״̬
     @param
     @param
     @return
     */
	virtual bool				GotoState(DWORD dwState, LPCSTR pContext, int nLen) = 0;
    
	/** ȡ�õ�ǰ����״̬
     @param
     @param
     @return
     */
	virtual DWORD				GetCurState(void) = 0;
    
	/** �ͻ���ֻ�������޸����ǵ��ƶ���ʽ
     @param
     @param
     @return
     */
	virtual void               UpdateMoveStyle(char nMoveStyle) = 0;
    
	/** ��ȡ����ǩ��
     */
	virtual LPCSTR				GetSignature(void) = 0;
    
	/** ��ȡͷ��ID
     @param
     @param
     @return
     */
	virtual int                 GetFaceID(void) = 0;
    
	/** ��ȡ����״̬
     @param
     @param
     @return
     */
	virtual bool                GetFollowState(void) = 0;
    
	/** ���ø���״̬
     @param
     @param
     @return
     */
	virtual void                SetFollowState(bool bstate,int nHeroSpeed = 0,int nFollowSpeed = 0) = 0;
    
	/** ͨ����ӪIDȥ���� ��ӪͼƬ
     @param
     @param
     @return
     */
	virtual void                SetCampPicture(int nCampID) = 0;
    
	/** ���÷���״̬
     @param
     @param
     @return
     */
	virtual void				SetFLyState(bool bFly) = 0;
    
	/** ��ȡ����״̬
     @param
     @param
     @return
     */
	virtual bool				GetFLyState() = 0;
    
	/** ��ȡ����ģ�ͼ���״̬
     @param
     @param
     @return
     */
	virtual bool				GetFLyModelLoadState() = 0;
    
	/**
     @param
     @param
     @return
     */
	virtual ulong                GetRidingPet() = 0;
    
	/** ���ģ�ͼ�����ϣ�ȥ��ʼѰ·�¼�������
     @param
     @param
     @return
     */
	virtual bool				OnResLoadedToMove() = 0;
    
	/** ���÷���״̬�����ֵ��
     @param
     @param
     @return
     */
	virtual void				SetFLyToMovePoint(xs::Point pt) = 0;
    
    
	//by cjl
	/** ��ȡ�����������
     @param
     @return
     */
	virtual int						GetPresentProp(int id) = 0;
    
	/** ��ȡ��ɫĿǰ���Ի�ȡ����Ʒids
     @param
     @return
     */
	virtual SPresentSchemeInfoBase*  GetPresentGoodsID() = 0;
    
	/** ��ȡս������ʾ����
     @param
     @return
     */
	virtual int						GetFightDisplayProp(int id) = 0;
	//end cjl
    
	/** ������������״̬��
     @param
     @return
     */
	virtual void                     SetPersonDieFlage(bool bDie) = 0;
    
	/** ��ȡ��������״̬��
     @param
     @return
     */
	virtual bool                     GetPersonDieFlage() = 0;
};

////////////////////////////�������////////////////////////////////////
struct IMonster : public ICreature
{
	/**
     @param
     @param
     @return
     */
	virtual LPCSTR				GetName(void) = 0;
    
	/**
     @param
     @param
     @return
     */
	virtual void				SetName(LPCSTR pszName) = 0;
    
	/** ��ȡͷ��ID
     @param
     @param
     @return
     */
	virtual int                 GetFaceID(void) = 0;
    
	/** �����������ϵĲɼ���Ч��
     @param
     @param
     @return
     */
	virtual void                CreateCollectionEffect() = 0;
    
	/** �رչ������ϵĲɼ���Ч��
     @param
     @param
     @return
     */
	virtual void				CloseCollectionEffect() = 0;
};

////////////////////////////��Ʒ����////////////////////////////////////
struct IGoods : public IEntity
{
	/** �Ƿ���ĳ�󶨱�־
     @param
     @param
     @return
     */
	virtual bool				IsHasBindFlag(DWORD dwBindFlag) = 0;
    
	/** �ܷ����
     @param
     @param
     @return
     */
	virtual bool				CanPlace(ISkepGoods*pSkepGoods,ulong ulPackIDTarget,int& iPlaceTarget) = 0;
    
	/** �ܷ���
     @param
     @param
     @return
     */
	virtual bool				CanDropOut(ISkepGoods * pSkepGoods) = 0;
};

////////////////////////////�������////////////////////////////////////
struct IPet:public ICreature
{
	/**
     @param
     @param
     @return
     */
	virtual LPCSTR				 GetName(void) = 0;
	/**
     @param
     @param
     @return
     */
	virtual void				 SetName(LPCSTR pszName) = 0;
    
	/** �����ڻ꽫�б��ڵ��ƶ�����
     @param
     @param
     @return
     */
	virtual bool				CanPlace(ISkepGoods*pSkepGoods,ulong ulPackIDTarget,int& iPlaceTarget) = 0;
    
	/** ���������ж�
     @param
     @param
     @return
     */
	virtual bool				PetUpgrade(DWORD dwPropID, int nValue) = 0;
    
	/**
     @param
     @param
     @return
     */
	virtual LONGLONG			GetLeader(void) = 0;
    
	/** ��ȡͷ��ID
     @param
     @param
     @return
     */
	virtual int                 GetFaceID(void) = 0;
    
	/** �Ƿ���ĳ��״̬����������ˣ�
     @param
     @param
     @return
     */
	virtual bool				IsHasStateFlag(DWORD dwState) = 0;
    
	/** �ܷ���
     @param
     @param
     @return
     */
	virtual bool				CanDropOut(ISkepGoods * pSkepGoods) = 0;
    
	/** �Ƿ���ĳ�󶨱�־
     @param
     @param
     @return
     */
	virtual bool				IsHasBindFlag(DWORD dwBindFlag) = 0;
};
////////////////////////////װ������////////////////////////////////////
struct IEquipment : public IGoods
{
	/** װ��
     @param
     @param
     @return
     */
	virtual bool				OnEquip(ICreature * pCreature) = 0;
    
	/** ����
     @param
     @param
     @return
     */
	virtual bool				UnEquip(ICreature * pCreature) = 0;
    
	/** ���Ч��
     @param
     @param
     @return
     */
	virtual IEffect *			GetEffect(int nIndex) = 0;
    
	/** �ܷ�װ��
     @param
     @param
     @return
     */
	virtual bool				CanEquip(int nPlace) = 0;
    
	/**���װ������ID
     @param
     @param
     @return
     */
	virtual DWORD				GetEquipPackID(void) = 0;
    
	/**���װ������
     @param
     @param
     @return
     */
	virtual bool				GetLettering(char * pszValue, int  nLen) = 0;
    
	/**���װ��Ʒ�ʵȼ�
     @param
     @param
     @return
     */
	virtual int				GetBrandLevel() = 0;
};

////////////////////////////��װ������Ʒ����////////////////////////////////////
struct INonequipableGoods : public IGoods
{
	/** �ܷ�ʹ��
     @param
     @param
     @return
     */
	virtual bool				CanUse(void) = 0;
	/** �ܷ�ʹ��2
     @param
     @param
     @return
     */
	virtual bool                PetCanUse(LONGLONG uid) = 0;
    
};

////////////////////////////�������////////////////////////////////////
struct IBox : public IEntity
{
	/** ȡ������
     @param
     @param
     @return
     */
	virtual LPCSTR				GetName(void) = 0;
    
	/** �Ƿ���Ȩ��
     @param
     @param
     @return
     */
	virtual bool				IsMaster(long lPDBID) = 0;
};

////////////////////////////��˶���////////////////////////////////////
struct IMast : public IEntity
{
	/** ȡ������
     @param
     @param
     @return
     */
	virtual LPCSTR				GetName(void) = 0;
};

/////////////////////////////���ݶ���///////////////////////////////////
// add by zjp.
struct IBubble : public IEntity
{
	
};

////////////////////////////ʵ�岿��////////////////////////////////////
struct IEntityPart
{
	/** �ͷ�,���ͷ��ڴ�
     @param
     @param
     @return
     */
	virtual void				Release(void) = 0;
    
	/** �������������ã�Ҳ����˽ӿ�
     @param
     @param
     @return
     */
	virtual bool				Create(IEntity * pMaster, LPCSTR pszData, int nLen) = 0;
    
	/** ȡ�ǲ���ID
     @param
     @param
     @return
     */
	virtual DWORD				GetPartID(void) = 0;
    
	/** ��Ϣ
     @param
     @param
     @return
     */
	virtual	int					OnMessage(DWORD dwMsgID, LPCSTR pszMsg, int nLen) = 0;
    
	/** ȡ������
     @param
     @param
     @return
     */
	virtual IEntity *			GetMaster(void) = 0;
    
	/** �����
     @param
     @param
     @return
     */
	virtual bool				Active(LPCSTR pszContext, int nLen) = 0;
    
	/** ���Ჿ��
     @param   ���統����ת������״̬�����足���ƶ�����
     @param
     @return
     */
	virtual bool				Freeze(LPCSTR pszContext, int nLen) = 0;
};

/////////////////////////////��������//////////////////////////////////////////
struct ICommonPart : public IEntityPart
{
	/** ��ȡװ������
     @param
     @param
     @return
     */
	virtual bool  getFormData( void * pFormData) = 0;
    
	/** �����Զ�Ѱ·
     @param
     @param
     @return
     */
	virtual bool  SendAutoMoveEventByFly(ulong ulMapID,xs::Point ptEndPoint) = 0;
};

////////////////////////////��Ӫ����//////////////////////////////////////
struct ICampPart : public IEntityPart
{
	/** ȡ����ӪID
     @param
     @param
     @return
     */
	virtual int					GetCampID(void) = 0;
    
	/** �ܷ񹥻�����������ֻ�����ڹ�����﹥�������﹥��ȡPK�����ж�
     @param
     @param
     @return
     */
	virtual bool                CanAttack(ICreature * pTargetCreature) = 0;
};

/////////////////////////////////////////////////////////////////////////
struct IConjurePart : public IEntityPart
{
	/**
     @param
     @param
     @return
     */
	virtual LONGLONG			GetLeader(void) = 0;
};

////////////////////////////////////////////////////////////////////////
struct IPetPart : public IConjurePart
{
	/** ����
     @param
     @param
     @return
     */
	virtual bool				ConjurePet(LONGLONG petID,int nPlace) = 0;
    
	/** �ٻ�
     @param
     @param
     @return
     */
	virtual bool				CallBackPet(LONGLONG petID,int nPlace) = 0;
    
	/** ����
     @param
     @param
     @return
     */
	virtual void               DisbandPet(LONGLONG petID,int nPlace) = 0;
    
	/** ����
     @param
     @param
     @return
     */
	virtual bool               DismountPet(LONGLONG petID,int nPlace) = 0;
    
	/** ���
     @param
     @param
     @return
     */
	virtual bool				RidePet(LONGLONG petID,int nPlace) = 0;
    
	/** ��˼��
     @param
     @param
     @return
     */
	virtual bool				CanRidePet(LONGLONG petID,int nPlace) = 0;
    
	/** ����
     @param
     @param
     @return
     */
	virtual void				CombinePet(LONGLONG petID,int nPlace) = 0;
    
	/** ����
     @param
     @param
     @return
     */
	virtual void                ChangePetName(int nPlace,LONGLONG petID,const std::string &strName,bool hasBadWords = false) = 0;
    
	/** �󷨿���
     @param
     @param
     @return
     */
	virtual void                 SetFormation(int formation) = 0;
    
	/** ����ͷĿ
     @param
     @param
     @return
     */
	virtual void				 SetLeader(LONGLONG uid) = 0;
    
	/** ���б�
     @param
     @param
     @return
     */
	virtual void				 RefreshFormation() = 0;
    
	/** ��ȡ�����б�
     @param
     @param
     @return
     */
	virtual list<LONGLONG> *	GetPetList(void) = 0;
    
	/** ��ȡ��ǰ��
     @param
     @param
     @return
     */
	virtual int					GetCurrentFormation() = 0;
    
	/** ��ȡ�󷨵ȼ�
     @param
     @param
     @return
     */
	virtual short				GetPosSkillGrade(int id) = 0;
    
	/** �������
     @param
     @param
     @return
     */
	virtual void				SendCommand(LPCSTR pszData, int nLen) = 0;
    
	/** ȡ���������
     @param
     @param
     @return
     */
	virtual void				CancelCommand(LPCSTR pszData, int nLen) = 0;
    
	/** �ͻ�������ʼ������
     @param
     @param
     @return
     */
	virtual void				ReqStartPetRelease(LONGLONG petID,int nPlace) = 0;
    
	/** ��õ�ǰ��˳���
     @param
     @param
     @return
     */
	virtual void				GetRidePet(LONGLONG& petID, int& nPlace) = 0;
};
//////////////////////////////ʵ��ͻ���//////////////////////////////////
struct IEntityClient
{
	/** �ͷ�
     @param
     @param
     @return
     */
	virtual void				Release(void) = 0;
    
	/** ���õ�ǰ�ĳ���ID
     @param
     @param
     @return
     */
	virtual void				SetZoneID(DWORD dwZoneID)	= 0;
    
	/** ȡ�õ�ǰ�ĳ���ID
     @param
     @param
     @return
     */
	virtual DWORD				GetZoneID(void) = 0;
    
	/** ���õ�ǰ�ĵ�ͼID
     @param
     @param
     @return
     */
	virtual void				SetMapID(DWORD dwMapID) = 0;
    
	/** ȡ�õ�ǰ�ĵ�ͼID
     @param
     @param
     @return
     */
	virtual DWORD				GetMapID(void) = 0;
    
	/** ȡ�ÿͻ�������
     @param
     @param
     @return
     */
	virtual IPerson *			GetHero(void) = 0;
    
	/** ȡ�ÿͻ��˳���
     @param
     @param
     @return
     */
	virtual IPet *              GetPet(void) = 0;
	/** ͨ��UIDȡ��ʵ��
     @param
     @param   dwGOClass ����Ϊ�˷�ֹ�ⲿֱ����IEntityת����Ӧ��ʵ��ӿڣ��Է������ȶ�����в
     @                    ��tEntity_Class_Person�� tEntity_Class_Monster��tEntity_Class_Equipment��tEntity_Class_NonequipableGoods��
     @return
     */
	virtual IEntity *			Get(LONGLONG uid, DWORD dwGOClass) = 0;
    
	/** ͨ��PDBIDȡ������ʵ��
     @param
     @param
     @return
     */
	virtual IEntity *			Get(DWORD dwPDBID) = 0;
    
	/** ͨ��UIDȡ��ʵ��,������Ҫʹ���������
     @param   
     @param	
     @return  
     */
	virtual IEntity *			Get(LONGLONG uid) = 0;
    
	/** ȡ����������
     @param   
     @param   
     @return  
     */
	virtual ISchemeCenter *		GetSchemeCenter(void) = 0;
    
	/** ͨ��UID�е����к�ȡ��ʵ��
     @param   
     @param   
     @return  
     */
	virtual IEntity *			GetBySNO(DWORD dwSNO) = 0;
    
	/** ȡ�ÿͻ������ǵ�װ����SKEPID
     @param   
     @param   
     @return  
     */
	virtual DWORD				GetEquipSkepID(void) = 0;
    
	/** ȡ�ÿͻ������ǵİ�����SKEPID
     @param   
     @param   
     @return  
     */
	virtual	DWORD				GetPacketSkepID(void) = 0;
    
	/** ȡ�ÿͻ������ǵĳ����б���SKEPID
     @param   
     @param   
     @return  
     */
	virtual DWORD               GetPetlistSkepID(void) = 0;
    
	/** ȡ�ÿͻ������ǵ�̯λ��SKEPID
     @param   
     @param   
     @return  
     */
	virtual DWORD               GetStallSkepID(void) = 0;
    
    
	/** ���ÿͻ������ǵ�װ����SKEPID
     @param   
     @param   
     @return  
     */
	virtual void				SetEquipSkepID(DWORD dwSkepID) = 0;
    
	/** ���ÿͻ������ǵİ�����SKEPID
     @param   
     @param   
     @return  
     */
	virtual void				SetPacketSkepID(DWORD dwSkepID) = 0;
    
	/** ���ÿͻ������ǵĳ����б�SKEPID
     @param   
     @param   
     @return  
     */
	virtual void                SetPetlistSkepID(DWORD dwSkepID) = 0;
    
	/** ���ÿͻ������ǵ�̯λ��SKEPID
     @param   
     @param   
     @return  
     */
	virtual void                SetStallSkepID(DWORD dwSkepID) = 0;
    
    
	/** ͨ��Ĭ�����ݹ���ʵ��
     @param   
     @param   
     @return  
     */
	virtual IEntity *					BuildEntity(DWORD dwEntityClass, LONGLONG uid, LPCSTR pszContext, int nLen, int nIsHero) = 0;
    
	//Ԥ���س�������ģ��
	//add by yhc
	virtual void  LoadMapMonster(DWORD nMapID) = 0;
	virtual void  AddEffectToList(DWORD nMapID,long lResID) = 0;
    
	// add by zjp
	/** ��������װ����Ϣ
     @param   
     @param   
     @return  
     */
	virtual void RequestEquipInfo(ulong ulPersonPID) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(_LIB) || defined(ENTITYCLIENT_STATIC_LIB)		/// ��̬��汾
#	pragma comment(lib, MAKE_LIB_NAME(xs_cec))
extern "C" IEntityClient * LoadCEC(void);
#	define	CreateEntityClientProc	LoadCEC
#else														/// ��̬��汾
typedef IEntityClient * (RKT_CDECL *procCreateEntityClient)(void);
#	define	CreateEntityClientProc	DllApi<procCreateEntityClient>::load(MAKE_DLL_NAME(xs_cec), "LoadCEC")
#endif#endif