/******************************************************************
** �ļ���:	ChatForm.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008-3-21
** ��  ��:	1.0
** ��  ��:	�������			
** Ӧ  ��:  
******************************************************************/
#pragma once

enum 
{
	CheckChannel_Map = 1,	    /// ��ͼƵ��
	CheckChannel_Around,		/// ��ΧƵ��
	CheckChannel_Army,		    /// ����Ƶ��
	CheckChannel_Family,		/// ����Ƶ��
	CheckChannel_Team,		    /// ����Ƶ��
	CheckChannel_Private,	    /// ����Ƶ��
	CheckChannel_All,	        /// ȫѡƵ��

	MaxCheckChannelCount,	    /// ���Ƶ����
};
class ChatForm : public SingletonEx<ChatForm>,public IEventExecuteSink
{
	ulong			m_currentChannel;		//��ǰ��Ƶ��
	ulong			m_currentTarget;		//��ǰ������Ŀ��
	bool			m_isSubscriber;
	/************************************************************************/
	/* event define                                                         */
	/************************************************************************/
public:
	static const std::string		EventOnChatMessageUpdate;	//����������Ϣ
	static const std::string		EventOnChannelChange;		//�ı䵱ǰ����Ƶ��
	static const std::string		EventOnTargetChange;		//���������ı�,˽��
	static const std::string		EventOnSetChannel;			//֪ͨUI��ǰƵ��,��ʵ��ʼ�����������ʾ����
	static const std::string        EventOnUpdateChatBoxSize;   //�������촰�Ĵ�С
	static const std::string        EventOnSetChatBgShow;       //��ʾ�����챳��

public:
	ChatForm();
	~ChatForm();

	//  �¼�����
	void Subscriber();

	// ȡ�����Ĵ���
	void UnSubscriber();

	// Update
	void Update();

	/** ����������Ϣ
	*/
	void sendChatMessage(const char* msg);

	/**���õ�ǰ��Ƶ��
	*/
	void setChannel(const std::string& channelName);

	/**���õ�ǰ���ε�Ƶ��
	*/
	void setChannelFilter(int nIndex,bool bSelect,bool bAllSelect = false);

	/**���õ�ǰ���촰�ڵ�ԭʼ��С
	*/
	void SetChatBoxInitSize(int right,int top);

	/**
	*/
    void UpdateChatBoxSize(int nPosX,int nPosY);

	/** �õ�����Ƿ���
	*/
	bool GetMousePressed();

	/** ��������Ƿ���
	*/
	void SetMousePressed(bool bmousePressed);

	/** IEventExecuteSink
	*/
	virtual void OnExecute(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen);
	/************************************************************************/
	/* event handle                                                         */
	/************************************************************************/

	void onChatMessageUpdate(EventArgs& args);
	void onChannelChange(EventArgs& args);		//�ı䵱ǰ����Ƶ��
	void onTargetChange(EventArgs& args);		//���������ı�,˽��
	void onSetChannel(EventArgs& args);			//֪ͨUI��ǰƵ��,��ʵ��ʼ�����������ʾ����

private:

	 bool     m_bCheck[MaxCheckChannelCount];

	 int      m_nRight;

	 int      m_nTop;

	 bool     m_bMousePressed;
};
