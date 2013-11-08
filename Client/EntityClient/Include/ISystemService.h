/*******************************************************************
** �ļ���:	e:\Rocket\Client\EntityClient\Include\ISystemService.h
** ��  Ȩ:	(C) 
** ������:	
** ��  ��:	2008/6/17  20:36
** ��  ��:	1.0
** ��  ��:	ϵͳ������	
** Ӧ  ��:	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

/*! \addtogroup SystemService
*  ϵͳ������
*  @{
*/

// ���Զ�̷�����
struct IPersonVisitor
{
	/** 
	@param   
	@param   
	@return  
	*/
	virtual void			OnVisit(DWORD dwZoneID, DWORD dwMapID, IPerson * pVirtual) = NULL;
};

// ϵͳ������
struct ISystemService
{
	/** �ͷ�
	@param   
	@param   
	@param   
	@return  
	@note     �ͷ�������Դ���������ٴ˶���
	@warning 
	@retval buffer 
	*/
	virtual void			Release(void) = NULL;

	/** ����Զ����ҷ�����
	@param   
	@param   
	@return  
	*/
	virtual	bool			VisitPerson(DWORD dwPDBID, IPersonVisitor * pVisitor) = NULL;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(_LIB) || defined(ENTITYCLIENT_STATIC_LIB)		/// ��̬��汾
	#	pragma comment(lib, MAKE_LIB_NAME(EntityClient))
	extern "C" ISystemService * CreateSystemService(void);
	#	define	CreateSystemServiceProc	CreateSystemService
#else														/// ��̬��汾
	typedef ISystemService * (RKT_CDECL *procCreateSystemService)(void);
	#	define	CreateSystemServiceProc	DllApi<procCreateSystemService>::load(MAKE_DLL_NAME(EntityClient), "CreateSystemService")
#endif

