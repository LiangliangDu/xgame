/*******************************************************************
** �ļ���:	
** ��  Ȩ:	
** ������:	
** ��  ��:
** ��  ��:	
** ��  ��:	
** Ӧ  ��:	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

/*! \addtogroup TeamClient
*  ��ӿͻ���
*  @{
*/
// ��ӿͻ���
struct ITeamClient
{
	/** ��������
	@param   
	@param   
	@return  
	*/
	virtual bool           CreateTeam(const std::string& strName,DWORD dwTeamMode,DWORD dwGoodsAllotMode,DWORD dwPetAllotMode,bool bOpen) = 0;
     
	/** ��������
	@param   
	@param   
	@return  
	*/
	virtual bool           FindTeam() = 0;

	/** �������
	@param   
	@param   
	@return  
	*/
	virtual bool           ApplyTeam(DWORD dwCaptain) = 0;

	/** �鿴��������Ϣ
	@param   
	@param   
	@return  
	*/
	virtual bool          ViewSelfTeamMessage(bool bClick) =0;

	/** �鿴����������Ϣ
	@param   
	@param   
	@return  
	*/
	virtual bool          ViewOtherTeamMessage(DWORD dwCaptain) = 0;

	/** �鿴��Ա����װ������ϸ��Ϣ
	@param   ����Ҫ��ѯ����Ա��PDBID
	@param   
	@return  
	*/
	virtual bool         ViewTeamMemberMessage(DWORD dwPDBID)= 0;

	/** ����ӳ�
	@param   
	@param   
	@return  
	*/
	virtual void         FollowCaptain(void) = 0;

	/** �ͷ�
	@param   
	@param   
	@param   
	@return  
	@note     �ͷ�������Դ���������ٴ˶���
	@warning 
	@retval buffer 
	*/
	virtual void			Release(void) = 0;

	/** �������
	@param   
	@param   
	@param   
	@return  
	@note    
	@warning 
	@retval buffer 
	*/
	virtual void			Clean(void) = 0;

	/** ����ID
	@param   
	@param   
	@return  
	*/
	virtual DWORD			GetTeamID(void) = 0;

	/** ����/����
	@param
	@param
	@return
	*/
	virtual bool			Invite(DWORD dwPDBID,bool bInvite) = 0;

	/** �˳�����
	@param �Ƿ�Ϊ�����˶� Ĭ��Ϊfalse
	@param 
	@return
	*/
	virtual void            QuitTeam(bool blogOut = false) = 0;

	/** ������Ա
	@param
	@param
	@return
	*/
	virtual void			DismissMember(DWORD dwPDBID) = 0;

	/** �����ӳ�
	@param   
	@param   
	@return  
	*/
	virtual void			ChangeTeamCaptain(DWORD dwPDBID) = 0;

	/** ���䷽ʽ�޸�
	@param   
	@param   
	@return  
	*/
	virtual void			ChangeAllotMode(long lAllotMode) = 0;

	/** ��ǰ���䷽ʽ
	@param   
	@param   
	@return  
	*/
	virtual long			GetCurAllotMode(void) = 0;

	/** �Ƿ�Ϊ����
	@param   
	@param   
	@return  
	*/
	virtual bool			IsTeammate(DWORD dwPDBID) = 0;

	/** �õ��ӳ�UID
	@param   
	@param   
	@return  
	*/
	virtual LONGLONG        GetTeamCaptainUID(void) = 0;

	/** �õ���������
	@param   
	@param   
	@return  
	*/
	virtual int            GetTeamMemberNumber(void) = 0;

	/** �õ��Ƿ�Ϊ�ӳ�
	@param   
	@param   
	@return  
	*/
	virtual bool            IsTeamCaptain(void) = 0;

	/** �õ���������
	@param   
	@param   
	@return  
	*/
	virtual std::string     GetTeamName()= 0;

	/** �ö�������
	@param   
	@param   
	@return  
	*/
	virtual int             GetTeamMode()= 0;

	/** �õ��꽫����ģʽ
	@param   
	@param   
	@return  
	*/
	virtual int             GetPetAllotMode()= 0;

	/** �õ���Ʒ����
	@param   
	@param   
	@return  
	*/
	virtual int				GetGoodsAllotMode()= 0;

	/** �õ�˽������
	@param   
	@param   
	@return  
	*/
	virtual bool            GetTeamPrivate()= 0;

	/** �õ�Ŀ��Ķ�����Ϣ
	@param   
	@param   
	@return  
	*/
	virtual void			GetTargetTeamMessage(int nDBid,const std::string& strName,int faceid) = 0;     
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(_LIB) || defined(TEAMCLIENT_STATIC_LIB)		/// ��̬��汾
	#	pragma comment(lib, MAKE_LIB_NAME(xs_ctm))
	extern "C" ITeamClient * LoadCTM(void);
	#	define	CreateTeamClientProc	LoadCTM
#else													/// ��̬��汾
	typedef ITeamClient * (RKT_CDECL *procCreateTeamClient)(void);
	#	define	CreateTeamClientProc	DllApi<procCreateTeamClient>::load(MAKE_DLL_NAME(xs_ctm), "LoadCTM")
#endif

