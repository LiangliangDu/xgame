//////////////////////////////////////////////////////////////////////////
//  ���ļ����������ݽ�����������
//      CTaskInfo�� ����������Ϣ�Ľṹ��
//      EEntityTaskSign�� ����ʵ��������ǣ�
//      ITaskClient�� ��������ܵĽӿڣ�
//      ITaskPart�� ���񲿼��Ľӿڣ�
//      CreateTaskClientProc�� ���ڴ���ITaskClient�ӿڵĺꣻ
//      CloseTaskClient�� �����ͷ�TaskPart.dll�ĺꣻ

#pragma once

#include "IEntityClient.h"
#include "../Common/GlobalDefine.h"
#include "../Common/DGlobalEvent.h"
#include <map>

class ITaskPart;
class IAmusementPart;

//////////////////////////////////////////////////////////////////////////
//  �ѽ���������ݵĶ��壻

#pragma pack(1)
typedef struct CHoldTaskData
{
public:
    CHoldTaskData()
    {
        memset(this, 0, sizeof(CHoldTaskData));
    }

    //  ��������Ч���ɵ����߱�֤��
    unsigned short& operator[](unsigned char ucIndex)
    {
		static  unsigned short ucTemp = 0;
        if (ucIndex >= TASK_REQUIREMENT_MAX_COUNT)
        {
            ASSERT(false);
			return ucTemp;
        }
        return TaskData[ucIndex];
    }

//private:
    //  �������ݱ�ÿ��Ԫ�ض�Ӧһ�������������ɶȣ�����Ӧ�ľ��������������LUA�ű�����ȷ����
    //  index�������������������LUA�ű���֤���������������Ӧ����ȷ�ԣ�
    //  value�������������ɶȣ�
    unsigned short TaskData[TASK_REQUIREMENT_MAX_COUNT];

	// �����������
	uchar   ucTaskTraceIndex;
} TARRAY_HOLDTASK_DATA;

#pragma pack()
//  �ѽ�����ļ�¼�ṹ��
//  key������ID��
//  value���������ݣ�
typedef std::map< unsigned short, TARRAY_HOLDTASK_DATA > TMAP_HOLDTASK_INFO;

//////////////////////////////////////////////////////////////////////////
//  CTaskInfo�������������������Ϣ�Ľṹ��
struct CTaskInfo
{
    //  �������ƣ�
    std::string m_strTaskName;
    //  ����������
    std::string m_strTaskDescription;
    //  ��������
    std::string m_strTaskRequirement;
    //  ������������
    std::string m_strTaskArea;
	//	�ɷ�����ʵ��
	std::string m_strTaskDispatched;
    //  ����ȼ���
    int m_nTaskLevel;
    //  ���Խ����������͵ȼ���
    int m_nMinLevel;
    //  ���Խ����������ߵȼ���
    int m_nMaxLevel;
	//	ǰ������
	std::string m_strPreTasks;
	// ��ѡǰ������
	std::string m_strChosePreTasks;
	// ��Ӫ�����ʶ
	std::string m_strNationTasks;
	//	�����Ѷȣ�
	int	m_nTaskDifficulty;
	//  ��������
	int m_nTouchOffType;
	//  �����Ƿ�ѭ����
	int m_nTaskRepetition;
	//	��������
	int	m_nVocation;
	// �����Ƿ�ɹ���
	int m_nShare;
	// �����Ƿ��ɾ��
	int m_nDelete;
	// ����ʣ��ʱ��
	int m_nLeavingTime;
	//  ������ʾͼƬ������
	std::string m_strToolTipImageName;
    //  ��������
    CTaskPrize m_TaskPrize;
};

//  ������Ϣ��
//  Key������ID��
//  Value��������Ϣ��
typedef map< WORD, CTaskInfo > TMAP_TASKINFO_SCHEME;

//////////////////////////////////////////////////////////////////////////
//  EEntityTaskSign������������ʵ��������ǣ�
enum EEntityTaskSign
{
    ETS_LOWWER_BOUND = -1,

    //  �������ǣ�
    ETS_NoTaskSign,
    //  �пɽ�������
    ETS_HasAcceptableTask,
	//  �пɽ��ܵ�ѭ������
	ETS_HasAcceptableRepetitionTask,
    //  �����������
    ETS_HasAccomplishedTask,
	//  ������ɵ�ѭ������
	ETS_HasAccomplishedRepetitionTask,
    //  ��δ�������
    ETS_HasUnfinishedTask,

    ETS_UPPER_BOUND,
};

//////////////////////////////////////////////////////////////////////////
//  CAmusemetInfo������������Ϣ�Ľṹ��
struct CAmusementInfo
{
	//  ���ƣ�
	std::string m_strAmusementName;

	//  ���ͣ�
	int m_nAmusementType;

	//  ������
	int m_nAmusementPlayerCount;

	//  ��ʾ����
	std::string m_strAmusementMapArea;

	// ���ʱ��Σ�
	int   m_nAmusementTimeSpace;

	// ����ʱ�䣻
	std::string m_strStartTime;

	// �������ڣ�
	std::string m_strStartDay;

	//  ͼƬID��
	int m_nImageIconID;

	// ��ȼ���
	int m_nNeedLevel;

	//  ���Խ��ܵ���͵ȼ���
	int m_nMinLevel;

	//  ���Խ��ܵ���ߵȼ���
	int m_nMaxLevel;

	//  ����ɴ�����
	int m_nReportNumber;

	//	�Ѷȣ�
	int	m_nAmusementDifficulty;

	//  ����ʱ��������
	std::string m_strStartTimeDescription;

	//	�ɷ�NPC��
	std::string m_strAmusementDispatched;

	//  �������
	std::string m_strAmusementPrize;

	//  ������
	std::string m_strDescription;
};

//  ���Ϣ��
//  Key���ID��
//  Value�����Ϣ��
typedef map<WORD, CAmusementInfo> TMAP_AMUSEMENTINFO_SCHEME;
//////////////////////////////////////////////////////////////////////////
//  CAmusementPetInfo������������Ϣ�Ľṹ��
struct CAmusementPetInfo
{
	//  ���ƣ�
	std::string m_strAmusementPetName;

	//  ���ͣ�
	int m_nAmusementType;

	// �꽫ˢ�µ�ͼID��
	int m_nAmusementPetMapID;

	//  ��ʾ����
	std::string m_strAmusementPetMapArea;

	// �꽫�ȼ���
	int m_nPetLevel;

	// �Ƿ���ʾ��
	int m_nNotice;

	// ��ʾ���ݣ�
	std::string m_strNoticeContext;

	// ˢ��ʱ�䣻
	int m_nReFreshTime;

	// ����ʱ�䣻
	std::string m_strStartTime;

	// �������ڣ�
	std::string m_strStartDay;

	//  ͼƬ�����֣�
	int  m_nImageIconID;

	//  ���Խ��ܵ���͵ȼ���
	int m_nMinLevel;

	//  ���Խ��ܵ���ߵȼ���
	int m_nMaxLevel;

	//  ��ЧID��
	int m_nSoundID;

	//	�Ѷȣ�
	int	m_nDifficulty;

	//  ����ʱ��������
	std::string m_strStartTimeDescription;

	//	�ص㣻
	std::string m_strDispatchedMap;

	//  �������
	std::string m_strAmusementPetPrize;

	//  ������
	std::string m_strDescription;
};

//  ��꽫��Ϣ��
//  Key����꽫ID��
//  Value����꽫��Ϣ��
typedef map<WORD, CAmusementPetInfo> TMAP_AMUSEMENTPETINFO_SCHEME;
//////////////////////////////////////////////////////////////////////////
//  ITaskClient�ӿڵ�������
class ITaskClient
{
public:
    //  �ͷ�����ĺ�����
    virtual void Release() = 0;

    //  �������񲿼���
    virtual ITaskPart* CreateTaskPart() = 0;

	//  �����������
	virtual IAmusementPart* CreateAmusementPart() = 0;

    //  ��ȡָ���������Ϣ��
    virtual CTaskInfo* GetTaskInfo(WORD wTaskID) = 0;

	//	��ȡ����������Ϣ
	virtual TMAP_TASKINFO_SCHEME& GetTaskList() = 0;

	//  ��ȡָ�������Ϣ��
	virtual CAmusementInfo* GetAmusementInfo(WORD wAmusementID) = 0;

	// ��ȡָ�����������Ϣ
	virtual TMAP_AMUSEMENTINFO_SCHEME& GetAmusementList() = 0;

	//  ��ȡָ��Ұ��꽫����Ϣ��
	virtual CAmusementPetInfo* GetAmusementPetInfo(WORD wAmusementID) = 0;

	// ��ȡҰ��꽫��������Ϣ
	virtual TMAP_AMUSEMENTPETINFO_SCHEME& GetAmusementPetList() = 0;

    //  ��ȡָ��ʵ��Ŀ��ɷ�����
    virtual vector< WORD >* GetEntityDispatchedTask(int nEntityID) = 0;

    //  ��ȡָ��ʵ��Ŀɽ�����
    virtual vector< WORD >* GetEntityAccomplishedTask(int nEntityID) = 0;

    //  ��ȡָ������ָ��������ָ��NPC�ĶԻ���Ϣ��
    virtual std::string GetDialogInfo(WORD wTaskID, uint unDialogIndex) = 0;

    //  ��ȡָ��ʵ��������ǣ�
    virtual EEntityTaskSign GetEntityTaskSign(LONGLONG uidEntity) = 0;
};

//////////////////////////////////////////////////////////////////////////
//  EEntityAmusementType������������ʵ��Ļ���ͣ�
enum EEntityAmusementType
{
	EAT_LOWWER_BOUND = 0,

	//  ���ڻ��
	EAT_TYPE_ONTIME,
	//  ÿ�ջ��
	EAT_TYPE_ONDAY,
	//  ѭ�����
	EAT_TYPE_LOOP,
	//  �������
	EAT_TYPE_COPY,
	//  Ұ��꽫
	EAT_TYPE_BOSS,

	EAT_UPPER_BOUND,
};

//////////////////////////////////////////////////////////////////////////
//  ITaskPart�ӿڵ�������
class ITaskPart : public IEntityPart
{
public:
    //  ��ȡ�����¼��
    virtual const TMAP_HOLDTASK_INFO& GetTastRecord() const = 0;

	//	��ȡ�ɽ������¼��
	virtual const set<WORD>& GetCanAcceptTaskRecord() const = 0;

    //  ��ʼ�������б�
    virtual void InitHoldTaskList(LPCSTR lpszTaskList, int nTaskListLength) = 0;

    //  ��ʼ������������б�
    virtual void InitAccomplishedTaskList(LPCSTR lpszTaskList, int nTaskListLength) = 0;

    //  ���һ�������¼��
    virtual void AddTask(WORD wTaskID,WORD wTraceIndex = 0) = 0;

    //  ɾ��ָ���������¼��
    virtual void RemoveTask(WORD wTaskID) = 0;

	virtual void OnRemoveTask(WORD wTaskID) = 0;

    //  ����ָ���������¼��
    virtual void UpdateTask(WORD wTaskID, uchar ucIndex, ushort usValue) = 0;

    //  ���ָ��������
    virtual void AccomplishTask(WORD wTaskID) = 0;

	// ɾ���Ѿ���ɵ�����
	virtual void DeleteTaskCompelete(WORD wTaskID) = 0;

    //  �ܷ����ָ��������
    virtual bool CanAccept(WORD wTaskID) = 0;

    //  ָ�������Ƿ��Ѿ�������
    virtual bool IsAccomplishedTask(WORD wTaskID) = 0;

	// ������ʾͼƬ
	virtual bool SendTaskImageToolTipByName(LPCSTR pContext) = 0; 
};

//////////////////////////////////////////////////////////////////////////
//  IAmusementPart�ӿڵ�������
class IAmusementPart : public IEntityPart
{
public:
	////  ��ȡ��¼��
	//virtual const TMAP_HOLDTASK_INFO& GetTastRecord() const = 0;

	////	��ȡ�ɽ������¼��
	//virtual const set<WORD>& GetCanAcceptTaskRecord() const = 0;

	////  ��ʼ����б�
	virtual void InitAmusementList(LPCSTR lpszAmusementList, int nAmusementListLength) = 0;

	////  ���һ�����¼��
	virtual void AddAmusement(WORD wAmusementID,WORD wIndex = 0) = 0;

	////  ɾ��ָ���Ļ��¼��
	virtual void RemoveAmusement(WORD wAmusementID) = 0;

	////  ����ָ���Ļ��¼��
	virtual void UpdateAmusement(WORD wAmusementID,ushort usValue) = 0;

	////  ���ָ���Ļ��
	virtual void AccomplishAmusement(WORD wAmusementID) = 0;

	//// ɾ���Ѿ���ɵĻ
	virtual void DeleteAmusementCompelete(WORD wAmusementID) = 0;

	////  �ܷ����ָ���Ļ��
	virtual bool CanAccept(WORD wAmusementID) = 0;

	////  ָ����Ƿ��Ѿ�������
	virtual bool IsAccomplishedAmusement(WORD wAmusementID) = 0;

};

//////////////////////////////////////////////////////////////////////////
//  ���������Ķ��壻
//  ��̬��汾��
#if defined(_LIB) || defined(TASKCLIENT_STATIC_LIB)
#	pragma comment(lib, MAKE_LIB_NAME(xs_ctk))
extern "C" ITaskClient* LoadCTK(void);
#	define	CreateTaskClientProc	LoadCTK
#	define  CloseTaskClient()
//  ��̬��汾��
#else
typedef ITaskClient* (RKT_CDECL *procCreateTaskClient)(void);
//  ���ڴ���ITaskClient�ӿڣ�
#define CreateTaskClientProc DllApi<procCreateTaskClient>::load(MAKE_DLL_NAME(xs_ctk), "LoadCTK")
//  �����ͷ�TaskPart.dll��
#define CloseTaskClient() DllApi<procCreateTaskClient>::freelib()
#endif
