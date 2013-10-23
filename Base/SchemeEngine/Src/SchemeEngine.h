/*******************************************************************
** �ļ���:	e:\CoGame\SchemeEngine\src\SchemeEngine\SchemeEngine.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2007/6/24  1:56
** ��  ��:	1.0
** ��  ��:	��������
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#include "ISchemeEngine.h"
#include "../include/tinyxml.h"
#include "CSVReader.h"
#include <string>
#include <list>
#include <vector>
#include <hash_map>
using namespace std;
using namespace stdext;

class CSchemeEngine : public ISchemeEngine
{
	typedef list< ISchemeUpdateSink * >		TLIST_SINK;
	struct SSINK
	{
		char		szFileName[MAX_PATH];
		bool		bDynamic;
		TLIST_SINK	listSink;		
	};
	
	typedef hash_map< string, SSINK >		THASH_SCHEMESINK;
public:
	//////////////////////////// ISchemeEngine ////////////////////////
	///////////////////////////////////////////////////////////////////
	/** �ͷ���������
	@param   
	@param   
	@param   
	@return  
	@note     
	@warning 
	@retval buffer 
	*/	
	virtual void			Release(void);

	/** ��������,���Զ�ע��sink
	@param   szFileName�������ļ���
	@param   pSink�����ø��»ص��ӿ�
	@param   bDynamic:�Ƿ�֧�ֶ�̬����
	@return  �ɹ�����true������Ϊfalse
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool			LoadScheme(const char * pszFileName, ISchemeUpdateSink * pSink, bool bDynamic = true);

	/** ��������
	@param   szFileName�������ļ���
	@param   
	@param   
	@return  �ɹ�����true������Ϊfalse
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool			UpdateScheme(const char * pszFileName);

	/** ȡ��ע�����ûص��ӿ�
	@param   szFileName�������ļ���
	@param   pSink�����ø��»ص��ӿ�
	@param   
	@return  �ɹ�����true������Ϊfalse
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool			UnregisterSink(const char * pszFileName, ISchemeUpdateSink * pSink);

	/** ȡ�����пɶ�̬���µ�����
	@param   
	@param   
	@return  
	*/
	virtual list<string> *	GetDynamicSchemeFileName(void);

	//////////////////////////// CSchemeEngine ////////////////////////
	///////////////////////////////////////////////////////////////////
	/** ���캯��
	@param   
	@param   
	@return  
	*/
	CSchemeEngine(void);

	/** ��������
	@param   
	@param   
	@return  
	*/
	virtual ~CSchemeEngine(void);

private:
	/** ע��sink
	@param   
	@param   
	@return  
	*/
	bool					RegisterSink(const char * szFileName, ISchemeUpdateSink * pSink, bool bDynamic);

	/** ��������
	@param   
	@param   
	@return  
	*/
	bool					__Load(const char * szFileName, CCsvReader * pCSVReader, TiXmlDocument * pTiXmlDocument, bool &bIsCsv);

	/** ����CSV����
	@param   
	@param   
	@return  
	*/
	bool					__LoadCSV(const char * szFileName, bool bEncrypt, CCsvReader * pCSVReader);

	/** ����XML����
	@param   
	@param   
	@return  
	*/
	bool					__LoadXML(const char * szFileName, bool bEncrypt, TiXmlDocument * pTiXmlDocument);

private:
	// �ص��ӿ�
	THASH_SCHEMESINK		m_hashSchemeSink;

	// ���ô���
	int						m_nCallNum;

	// �Ƿ��޸���
	bool					m_bIsChange;

	// �ɶ�̬���µ�����
	list<string>			m_listDynamicScheme;
};