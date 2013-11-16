/******************************************************************
** �ļ���:	ProgressForm.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-3-19
** ��  ��:	1.0
** ��  ��:				
** Ӧ  ��:  
******************************************************************/
#pragma once


class ProgressForm :
	public FormBase
{
public:
	//static const std::string EventProgressStart;	//���ؽ��ȿ�ʼ�¼�
	//static const std::string EventProgressEnd;		//���Ƚ���

private:
	/************************************************************************/
	/* constructor and deconstructor                                        */
	/************************************************************************/
public:
	ProgressForm();
	~ProgressForm(); 
	/************************************************************************/
	/* general functions                                                    */
	/************************************************************************/
public:

	/************************************************************************/
	/* interface functions                                                  */
	/************************************************************************/
public:
	virtual void onMessage(ulong actionId, SGameMsgHead* head, void* data, size_t len);

	virtual FormType getFormType(){ return progressForm;}

	/** ����Ϊ��ǰ
	*/
	virtual void onEnter();

	/** ����ʱ��
	*/
	virtual void update();

	virtual void render(IRenderSystem *pRenderSystem);


	/** ����Ϊ��Ч,Ϊ�л���׼��
	*/
	virtual void onLeave();
};