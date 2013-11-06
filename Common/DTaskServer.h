/*******************************************************************
** �ļ���:	e:\CoGame\TaskServer\src\TaskServer\DTaskServer.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2007/8/24  16:16
** ��  ��:	1.0
** ��  ��:	�������������
** Ӧ  ��:  
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#include "DGlobalGame.h"
#include "DGlobalMessage.h"

#pragma pack(1)

/***************************************************************/
///////////////////// ����������Ϊ�����Ϣ��/////////////////////
// �ϲ����Ϣ��ض���MSG_MODULEID_TASK
/***************************************************************/
enum 
{
	TASK_MEET_NPC = 0,  // NPC
	TASK_USE_ITEM = 1,  // ʹ����Ʒ����
	TASK_EXPLORD  = 2,  // ̽������
	TASK_SHARE = 3,     // ���������
};
// ��ʾ������Ϣ
#define MSG_TASK_SHOWINFO										1
struct SMsgTaskShowInfo_SC
{
	//int			nBodyLen;			// ��Ϣ���ݳ���
	// .......................		// ��Ϣ����
	//  ����ID��
	WORD m_wTaskID;
    //  ���NPC��
    int m_nNPCID;
	//  �Ի���Ϣ������
	uint m_unDialogIndex;
    //  �Ի�ģʽ��
    uchar m_ucMode;
	// �Ի���򿪷�ʽ
	uchar m_ucOpenType;
};

// �ͻ�����Ӧ
#define MSG_TASK_RESPOND										2
struct SMsgTaskRespond_CS
{
	char		szLuaFunName[128];	// lua������
	int			nParamLen;			// ���������ֽ���
	int			nContextLen;		// �����������ֽ���
	// ...................			// ��������: ID'#'ֵ'#' + ID'#'ֵ'#'
	// ..................			// ����������: ID'#'ֵ'#' + ID'#'ֵ'#'
};

// �رտͻ���������Ϣ����
#define MSG_TASK_CLOSEINFOWND									3
struct SMsgTaskCloseInfoWnd_SC
{

};

// �ͻ��˵�¼�������������־
#define MSG_TASK_LOGIN											4
struct SMsgTaskLoginInfo_CS
{
	
};

// ����һ��������־
#define MSG_TASK_ADDRECORD										5
struct SMsgTaskAddRecord_SC
{
	DWORD		dwTaskID;			// ����ID
	DWORD       dwTraceIndex;       // ��������ֵ
	// ..................			// ��־����
};

// �Ƴ�һ��������־
#define MSG_TASK_REMOVERECORD									6
struct SMsgTaskRemoveRecord
{
	DWORD		dwTaskID;			// ����ID
};
struct SMsgTaskRemoveRecord_SC
{
	DWORD		dwTaskID;			// ����ID
};

// �Ƴ�����������־
#define MSG_TASK_REMOVEALLRECORD								7
struct SMsgTaskRemoveAllRecord_SC
{
};

// ִ��һ�νű�
#define MSG_TASK_RUNSCRIPT										8

//  ��ʾ�Ի���Ϣ��
#define MSG_DIALOG_SHOWINFO										9
struct SMsgDialogShowInfo_SC
{
	int			nBodyLen;			// ��Ϣ���ݳ���
	// .......................		// ��Ϣ����
};

//  �ͻ��˽������������
#define MSG_TASK_ACCEPT_REQUEST 10
struct SMsgTaskAcceptRequest_CS
{
	WORD m_wTaskID;
};

//  ����һ��������־��
#define MSG_TASK_UPDATERECORD 11
struct SMsgTaskUpdateRecord_SC
{
    //  ����ID��
    DWORD dwTaskID;
    //  ����������
    uchar ucIndex;
    //  �������ݣ�
    ushort usValue;
};

//  �ͻ��˽������������
#define MSG_TASK_REPORT_REQUEST 12
struct SMsgTaskReportRequest_CS
{
    WORD m_wTaskID;
    int m_nTaskParam;
};

//  ����˷����ͻ��˵�����������Ӧ��
#define MSG_TASK_ACCOMPLISH 13
struct SMsgTaskAccomplish_SC
{
    WORD m_wTaskID;
};

//  ����˷����ͻ��˵��ѽ��������Ϣ��
#define  MSG_TASK_INITIAL_HOLD_TASK 14
struct SMsgTaskInitialHoldTask_SC
{
    int m_nTaskDataLength; 
};

//  ����˷����ͻ��˵�������������Ϣ��
#define MSG_TASK_INITIAL_ACCOMPLISHED_TASK 15
struct SMsgTaskInitialAccomplishedTask_SC
{
    int m_nTaskDataLength; 
};

// ͨ�ô��ڵ���Ϣ
#define  MSG_TASK_NOTIFY_CREATE_COMMWND 16

// ����ͨ�ô��ڵĽ��
#define  MSG_TASK_CHOSEN_RESULT  17

// ̽�����񴥷�����Ϣ��
#define  MSG_TASK_NOTIFY_EXPLORD_CREATE 18

// ����̽������ѡ��Ľ��
#define MSG_TASK_EXPLORD_CHOSEN_RESULT  19

// ���͹���������Ϣ
#define MSG_TASK_SHARE    20

// ���ͽ��ܹ���������Ϣ  
#define MSG_TASK_SHARE_ACCEPT 21

// ���ʹ���ͨ�õģ���Ʒ��̽���������������������Ϣ����
#define MSG_TASK_CREATE_COM_DSC_WND 22

// �Զ�Ѱ·��ɺ��Զ������Ի�����Ϣ
#define  MSG_TASK_CREATE_TASKDIALOGBOX 23
struct  SMsgTaskCreateTaskDialogBox_SC
{
	char		szNPCName[128];	// ����
	DWORD       dwTaskID;
};

// ����������������±�
#define MSG_TASK_UPDATE_TASKTRACEINDEX 24
struct  SMsgTaskUpdateTaskTraceIndex_SC
{
	int      nTaskID;
	int      nIndex;
	bool     bAutoTrace;
};

//ͨ������Ի���
#define  MSG_DIALOG_COMMINPUT                               25
struct SMsgSystemCommInput_SC
{
	char  szContent[128];        // �Ի���������ʾ��Ϣ
	char  szCallBackFunc[64];    // �ص�
	ushort usInput;              // �Ƿ���Ҫ�������
	int   nTime;

	SMsgSystemCommInput_SC(void)
	{
		memset(this, 0, sizeof(SMsgSystemCommInput_SC));
	}
};

struct SMsgSystemCommInput_CS
{
	char  szContent[64];         // ��ҵ�����, �ص�ʱ��Ϊ����
	char  szCallBackFunc[64];    // �ص�
	ushort usInput;              // �Ƿ����������
	ushort usResult;
	SMsgSystemCommInput_CS(void)
	{
		memset(this, 0, sizeof(SMsgSystemCommInput_CS));
	}
};
// ɾ���������������
#define  MSG_TASK_COMPELETE_DELETE          26
struct SMsgTaskCompeleteDelete_SC
{
	 WORD  wTaskID;
};

// �������񵯶Ի���
#define  MSG_TASK_FLYRIDE_CREATEDIALOGBOX     27
struct SMsgTaskFlyRideCreateDialogBox_CS
{
	WORD  wTaskID;
	WORD  wNpcID;
	WORD  wSpeed;
};

//by cjl
// ���������ȡ��Ʒ
#define MSG_TASK_GET_PRESENT                   28
struct SMsgTaskPresent_CS
{
	int nPresentLevel;//������֤��
};
//end cjl

// ��ͻ��˷�����Ҫ��ʾ������ͼƬ
#define MSG_TASK_SEND_IMAGEINFO                 29
struct SMsgTaskImageInfo_SC
{
	char  szImageName[64];       // ͼƬ���֣�
	SMsgTaskImageInfo_SC()
	{
		memset(this, 0 ,sizeof(SMsgTaskImageInfo_SC));
	}
};

// Ŀǰ�������ø���Ϣ�Ľṹ����ɾ������Ϣ�� ���壻WZH
// �л��������������ѽ��������ݷ�����Ϣ
//  ����˷����ͻ��˵��ѽ��������Ϣ��
#define  MSG_TASK_HOLD_TASK_TOSERVER             30
struct SMsgTaskInitialHoldTask_SS
{
	DWORD dwHolder;
	int   nTaskCount;
};  

// �л��������������ѽ��������ݷ�����Ϣ
//  ����˷����ͻ��˵�������������Ϣ��
#define  MSG_TASK_FINISHED_TASK_TOSERVER         31
struct SMsgTaskInitialFinishedTask_SS
{
	DWORD  dwHoldPDID;
	DWORD  dwTaskCounts;
};  

// ��ʱ������ʱ�䣻֪ͨ������
#define  MSG_TASK_OTIMER_RESPOND				 32
struct SMsgTaskInitialOnTimerRespondTask_CS
{
	DWORD  dwTaskID;
};

// �رն�����ʱ����ʱ��
#define MSG_TASK_CLOSE_CLIENT_COUNTDOWN			  33
struct SMsgTaskCloseClientCountDown_SC
{
	DWORD  dwTaskID;
};

// ��ʼ����һ���ݣ�
#define MSG_TASK_INIT_AMUSEMENT			          34
struct SMsgTaskInitAmusement_SC
{
	DWORD  dwPDBID;
};

// ������һ���ݣ�
#define MSG_TASK_UPDATE_AMUSEMENT			       35
struct SMsgTaskUpdateAmusement_SC
{
	DWORD  dwPDBID;                    // ���ID��
	char   szAmusementName[256];       // ���֣�
	int    nKeyValue;                  // ֵ��
};
#pragma pack()
