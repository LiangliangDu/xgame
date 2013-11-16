
/*******************************************************************
** �ļ���:	BadWords.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2008/2/27  16:57
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#include "ISchemeEngine.h"
#include <string>

//#define BADWORDS_SCHEME_FILENAME			"Data\\Scp\\BadWords.csc"
#define BADWORDS_SCHEME_FILENAME			"Data\\Scp\\BadWords.csv"


class CBadWords : public SingletonEx<CBadWords>, public ISchemeUpdateSink
{	
	std::vector<std::string> m_badwords; //���д����б�
public:
	///////////////////////////////ISchemeUpdateSink///////////////////	
	/** CSV��������ʱ֪ͨ
	@param   pCSVReader����ȡCSV�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/ 
	virtual bool			OnSchemeLoad(ICSVReader * pCSVReader,const char* szFileName);

	/** XML��������ʱ֪ͨ
	@param   pTiXmlDocument����ȡXML�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/
	virtual bool			OnSchemeLoad(TiXmlDocument * pTiXmlDocument,const char* szFileName);

	/** ���ö�̬����ʱ֪ͨ
	@param   pCSVReader����ȡCSV�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/
	virtual bool			OnSchemeUpdate(ICSVReader * pCSVReader, const char* szFileName);

	/** ���ö�̬����ʱ֪ͨ
	@param   pTiXmlDocument����ȡXML�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/
	virtual bool			OnSchemeUpdate(TiXmlDocument * pTiXmlDocument, const char* szFileName);

	///////////////////////////////CSchemeBuff//////////////////////////
	/** ����ű�
	@param   
	@param   
	@return  
	*/
	bool					LoadScheme(void);

	/** �ر�
	@param   
	@param   
	@return  
	*/
	void					Close(void);

	/** 
	@param   
	@param   
	@return  
	*/
	const std::vector<std::string> &	GetBadWordsList();

	/** 
	@param   
	@param   
	@return  
	*/
	CBadWords(void);

	/** 
	@param   
	@param   
	@return  
	*/
	virtual ~CBadWords(void);
};
