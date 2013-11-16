/******************************************************************
** �ļ���:	ProgressBar.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-4-8
** ��  ��:	1.0
** ��  ��:	������			
** Ӧ  ��:  
******************************************************************/
#pragma once

/** ���Ƚ����������
*/
struct IProgressSink
{
	virtual void done() = 0;
};

class ProgressBar : public SingletonEx<ProgressBar>, public IEventVoteSink
{
	/************************************************************************/
	/* event define                                                         */
	/************************************************************************/
	static const std::string		EventOnProgressEnter;   //show
	static const std::string		EventOnProgressLeave;	//hide
	static const std::string		EventOnProgresUpdate;   //update progress

	ulong			m_startTime;		//
	ulong			m_preTime ;         //previous update time
	ulong			m_delay;			//���µ�Ƶ��
	ulong			m_total;			//������ʱ��
	ulong			m_init;				//��ʼ��,
	bool			m_working;			//����������
    //  �Ƿ�ת��ʾ��
    bool m_bInverse;

	bool			m_autoDelete;       //�Զ�ɾ��

	IProgressSink*  m_pSink;
public:
	ProgressBar();
	~ProgressBar(){}

	//��ʼ��һЩ�¼��ȵ�
	void create();

	//  �¼�����
	void Subscriber();
	// ȡ�����Ĵ���
	void UnSubscriber();

	//����ʱ��
	void update() ;
	
	/************************************************************************/
	/* event handler                                                        */
	/************************************************************************/

	void onProgressEnter(EventArgs& args);   //show
	void onProgressLeave(EventArgs& args);	//hide
	void onProgresUpdate(EventArgs& args);   //update progress

	/************************************************************************/
	/* operater functions                                                   */
	/************************************************************************/
	/** ���ý���
	@ProgressBarInitArgs ��ʱ��
	@pSink ������ɺ����
	@slapse ��ʼ��,��Ϊ���ܲ��Ǵ���㿪ʼ,Ĭ��Ϊ0,start/time
	*/
	void setProgress(const CProgressBarInitArgs& ProgressBarInitArgs, IProgressSink* pSink = 0, ulong slapse = 0, bool autoDelete = false);

	/** ��������
	*/
	void start();

	/** �رս���
	*/
	void stop();
	
	//////////////////////////IEventVoteSink/////////////////////////////////////////
	/** 
	@param   wEventID ���¼�ID
	@param   bSrcType ������Դ����
	@param   dwSrcID : ����Դ��ʶ��ʵ��ΪUID��"���к�"���ݣ���ʵ���Ϊ0��
	@param   pszContext : ������
	@param   nLen : �����ĳ���
	@return  �������false : ���ж�ִ�У������������ִ��
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool	OnVote(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen);

};