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
#include "stdafx.h"
#include "EventEngine.h"

CEventEngine *	g_pEventEngine = NULL;
/** 
@param   
@param   
@return  
*/
CEventEngine::CEventEngine(void)
{

}

/** 
@param   
@param   
@return  
*/
CEventEngine::~CEventEngine(void)
{

}

/** �ͷ�
@param   
@param   
@param   
@return  
@note     
@warning 
@retval buffer 
*/
void CEventEngine::Release(void)
{
	delete this;
	//ȫ�ֱ�����ħ��!
	assert(this == g_pEventEngine);
	g_pEventEngine = NULL;
}

/** ����
@param   
@param   
@return  
*/
bool CEventEngine::Create(void)
{
	return true;
}

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
bool CEventEngine::FireVote(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen)
{
	return m_VoteCenter.Fire(wEventID, bSrcType, dwSrcID, pszContext, nLen);
}

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
void CEventEngine::FireExecute(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen)
{
	static Timer per4Timer;
	per4Timer.reset();

	m_ExecuteCenter.Fire(wEventID, bSrcType, dwSrcID, pszContext, nLen);

	if( per4Timer.getTime() > 30 ) //lilinll77
		ErrorLn("�¼�����ִ��ʱ�����,EventID ="<<wEventID<<",SrcType ="<<bSrcType);
}

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
bool CEventEngine::Subscibe(IEventVoteSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszDesc)
{
	return m_VoteCenter.Subscibe(pSink, wEventID, bSrcType, dwSrcID, pszDesc);
}

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
bool CEventEngine::Subscibe(IEventExecuteSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszDesc)
{
	return m_ExecuteCenter.Subscibe(pSink, wEventID, bSrcType, dwSrcID, pszDesc);
}

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
bool CEventEngine::UnSubscibe(IEventVoteSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID)
{
	return m_VoteCenter.UnSubscibe(pSink, wEventID, bSrcType, dwSrcID);
}

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
bool CEventEngine::UnSubscibe(IEventExecuteSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID)
{
	return m_ExecuteCenter.UnSubscibe(pSink, wEventID, bSrcType, dwSrcID);
}

/** �������
@param   
@param   
@return  
*/
API_EXPORT IEventEngine * LoadEEM(void)
{
	// ��������ˣ���ֱ�ӷ���
	if(g_pEventEngine != NULL)
	{
		return g_pEventEngine;
	}

	// ʵ����
	g_pEventEngine = new CEventEngine();
	if(!g_pEventEngine)
	{
		return NULL;
	}

	// ����
	if(!g_pEventEngine->Create())
	{
		SAFE_DELETE(g_pEventEngine);

		return NULL;
	}

	return g_pEventEngine;
}
