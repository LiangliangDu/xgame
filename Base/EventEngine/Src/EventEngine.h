/*******************************************************************
** �ļ���:	e:\CoGame\EventEngine\src\EventEngine\EventEngine.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2007/9/9  21:33
** ��  ��:	1.0
** ��  ��:	�¼�����
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#include <hash_map>
#include <list>
using namespace std;

#include "IEventEngine.h"
#include "EventEngineT.h"

struct OnVoteObject
{
	bool operator() (IEventVoteSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen)
	{
		if(pSink == NULL)
		{
			return false;
		}

		return pSink->OnVote(wEventID, bSrcType, dwSrcID, pszContext, nLen);		
	}
};

struct OnExecuteObject
{
	bool operator() (IEventExecuteSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen)
	{
		if(pSink == NULL)
		{
			return false;
		}

		pSink->OnExecute(wEventID, bSrcType, dwSrcID, pszContext, nLen);

		return true;
	}
};

class CEventEngine : public IEventEngine
{
	typedef TEventEngine< IEventVoteSink, OnVoteObject >		TCENTER_VOTE;

	typedef TEventEngine< IEventExecuteSink, OnExecuteObject >	TCENTER_EXECUTE;
public:
	////////////////////////IEventEngine///////////////////////////////
	/** �ͷ�
	@param   
	@param   
	@param   
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual void		Release(void);

	/** 
	@param   
	@param   
	@return  
	*/
	/** ����ͶƱ�¼�   
	@param   wEventID ���¼�ID
	@param   bSrcType ������Դ����
	@param   dwSrcID : ����Դ��ʶ��UID��"���к�"���ݣ�
	@param   pszContext : ������
	@param   nLen : �����ĳ���	  
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool		FireVote(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen);

	/** ����ִ���¼�
	@param   wEventID ���¼�ID
	@param   bSrcType ������Դ����
	@param   dwSrcID : ����Դ��ʶ��UID��"���к�"���ݣ�
	@param   pszContext : ������
	@param   nLen : �����ĳ���	  
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual void		FireExecute(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen);

	/** ����ͶƱ�¼�
	@param   pSink : �ص�sink
	@param   wEventID : �¼�ID
	@param   bSrcType ������Դ����
	@param	 dwSrcID : ����Դ��ʶ��UID��"���к�"���ݣ������Ϊ0�����ʾ��������
	@param	 pDesc : �������������������Գ���
	@return  �ɹ�����true,ʧ�ܷ���false
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool		Subscibe(IEventVoteSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszDesc);

	/** ����ִ���¼�
	@param   pSink : �ص�sink
	@param   wEventID : �¼�ID
	@param   bSrcType ������Դ����
	@param	 dwSrcID : ����Դ��ʶ��UID��"���к�"���ݣ������Ϊ0�����ʾ��������
	@param	 pDesc : �������������������Գ���
	@return  �ɹ�����true,ʧ�ܷ���false
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool		Subscibe(IEventExecuteSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszDesc);

	/** ȡ������ͶƱ�¼�
	@param   pSink : �ص�sink
	@param   wEventID : �¼�ID
	@param   bSrcType ������Դ����
	@param	 dwSrcID : ����Դ��ʶ��UID��"���к�"���ݣ������Ϊ0�����ʾ��������
	@param	 pDesc : �������������������Գ���
	@return  �ɹ�����true,ʧ�ܷ���false
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool		UnSubscibe(IEventVoteSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID);

	/** ȡ������ִ���¼�
	@param   pSink : �ص�sink
	@param   wEventID : �¼�ID
	@param   bSrcType ������Դ����
	@param	 dwSrcID : ����Դ��ʶ��UID��"���к�"���ݣ������Ϊ0�����ʾ��������
	@param	 pDesc : �������������������Գ���
	@return  �ɹ�����true,ʧ�ܷ���false
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool		UnSubscibe(IEventExecuteSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID);

	////////////////////////CEventEngine///////////////////////////////
	/** ����
	@param   
	@param   
	@return  
	*/
	bool				Create(void);

	/** 
	@param   
	@param   
	@return  
	*/
	CEventEngine(void);

	/** 
	@param   
	@param   
	@return  
	*/
	virtual ~CEventEngine(void);	
private:	
	// ͶƱ����
	TCENTER_VOTE			m_VoteCenter;
	
	// ִ������
	TCENTER_EXECUTE			m_ExecuteCenter;
};
extern CEventEngine *		g_pEventEngine;

