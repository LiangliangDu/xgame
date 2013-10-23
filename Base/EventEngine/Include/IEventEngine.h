/*******************************************************************
** �ļ���:	e:\CoGame\EventEngine\include\IEventEngine.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2007/9/9  20:58
** ��  ��:	1.0
** ��  ��:	�¼�����
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

namespace xs {
/*! \addtogroup EventEngine
*  �¼�����
*  @{
*/

/// ͶƱ�¼�sink
struct IEventVoteSink 
{
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
	virtual bool		OnVote(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen) = 0;	
};

/// ִ���¼�sink
struct IEventExecuteSink 
{
	/** 
	@param   wEventID ���¼�ID
	@param   bSrcType ������Դ����
	@param   dwSrcID : ����Դ��ʶ��ʵ��ΪUID��"���к�"���ݣ���ʵ���Ϊ0��
	@param   pszContext : ������
	@param   nLen : �����ĳ���
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual void		OnExecute(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen) = 0;
};

/// �¼�����
struct IEventEngine
{
	/** �ͷ�
	@param   
	@param   
	@param   
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual void		Release(void) = 0;
	
	/** ����ͶƱ�¼�   
	@param   wEventID ���¼�ID
	@param   bSrcType ������Դ����
	@param   dwSrcID : ����Դ��ʶ��ʵ��ΪUID��"���к�"���ݣ���ʵ���Ϊ0��
	@param   pszContext : ������
	@param   nLen : �����ĳ���	  
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool		FireVote(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen) = 0;

	/** ����ִ���¼�
	@param   wEventID ���¼�ID
	@param   bSrcType ������Դ����
	@param   dwSrcID : ����Դ��ʶ��ʵ��ΪUID��"���к�"���ݣ���ʵ���Ϊ0��
	@param   pszContext : ������
	@param   nLen : �����ĳ���	  
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual void		FireExecute(WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszContext, int nLen) = 0;

	/** ����ͶƱ�¼�
	@param   pSink : �ص�sink
	@param   wEventID : �¼�ID
	@param   bSrcType ������Դ����
	@param	 dwSrcID : ����Դ��ʶ��ʵ��ΪUID��"���к�"���ݣ���ʵ���Ϊ0�������Ϊ0�����ʾ��������
	@param	 pDesc : �������������������Գ���
	@return  �ɹ�����true,ʧ�ܷ���false
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool		Subscibe(IEventVoteSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszDesc) = 0;

	/** ����ִ���¼�
	@param   pSink : �ص�sink
	@param   wEventID : �¼�ID
	@param   bSrcType ������Դ����
	@param	 dwSrcID : ����Դ��ʶ��ʵ��ΪUID��"���к�"���ݣ���ʵ���Ϊ0�������Ϊ0�����ʾ��������
	@param	 pDesc : �������������������Գ���
	@return  �ɹ�����true,ʧ�ܷ���false
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool		Subscibe(IEventExecuteSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID, LPCSTR pszDesc) = 0;

	/** ȡ������ͶƱ�¼�
	@param   pSink : �ص�sink
	@param   wEventID : �¼�ID
	@param   bSrcType ������Դ����
	@param	 dwSrcID : ����Դ��ʶ��ʵ��ΪUID��"���к�"���ݣ���ʵ���Ϊ0�������Ϊ0�����ʾ��������
	@param	 pDesc : �������������������Գ���
	@return  �ɹ�����true,ʧ�ܷ���false
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool		UnSubscibe(IEventVoteSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID) = 0;

	/** ȡ������ִ���¼�
	@param   pSink : �ص�sink
	@param   wEventID : �¼�ID
	@param   bSrcType ������Դ����
	@param	 dwSrcID : ����Դ��ʶ��ʵ��ΪUID��"���к�"���ݣ���ʵ���Ϊ0�������Ϊ0�����ʾ��������
	@param	 pDesc : �������������������Գ���
	@return  �ɹ�����true,ʧ�ܷ���false
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool		UnSubscibe(IEventExecuteSink * pSink, WORD wEventID, BYTE bSrcType, DWORD dwSrcID) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(_LIB) || defined(EVENTENGINE_STATIC_LIB)	/// ��̬��汾
	#	pragma comment(lib, MAKE_LIB_NAME(xs_eem))
	extern "C" IEventEngine * CreateEventEngine(void);
	#	define	CreateEventEngineProc	LoadEEM
#else													/// ��̬��汾
	typedef  IEventEngine * (RKT_CDECL *procCreateEventEngine)(void);
	#	define	CreateEventEngineProc	DllApi<procCreateEventEngine>::load(MAKE_DLL_NAME(xs_eem), "LoadEEM")
#endif

}//namespace xs*/
