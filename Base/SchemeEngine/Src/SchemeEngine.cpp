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
#include "stdafx.h"
#include "SchemeEngine.h"

CSchemeEngine *	g_pSchemeEngine = NULL;
/** ���캯��
@param   
@param   
@return  
*/
CSchemeEngine::CSchemeEngine(void)
{
	m_hashSchemeSink.clear();

	m_nCallNum = 0;

	m_bIsChange = false;

	m_listDynamicScheme.clear();
}

/** ��������
@param   
@param   
@return  
*/
CSchemeEngine::~CSchemeEngine(void)
{
	
}

/** �ͷ���������
@param   
@param   
@param   
@return  
@note     
@warning 
@retval buffer 
*/	
void CSchemeEngine::Release(void)
{
	m_hashSchemeSink.clear();

	delete this;
	//ȫ�ֱ�����ħ��!
	assert (this == g_pSchemeEngine);
	g_pSchemeEngine = NULL; 
}

/** ��������,���Զ�ע��sink
@param   szFileName�������ļ���
@param   pSink�����ø��»ص��ӿ�
@param   
@return  �ɹ�����true������Ϊfalse
@note     
@warning 
@retval buffer 
*/
bool CSchemeEngine::LoadScheme(const char * pszFileName, ISchemeUpdateSink * pSink, bool bDynamic)
{
	if(pszFileName == NULL || pSink == NULL || strlen(pszFileName) <= 4)
	{
		return false;
	}

	// ע��Ϊ�����Ч�ʺͱ���̫���鷳�����ﲻ�ܱ�Ƕ�׵��ã�Ҳ�����ڻص�����װ������.
	if(m_nCallNum > 0)
	{
		memcpy(NULL, NULL, -1);
	}

	char szFullFileName[MAX_PATH] = { 0 };
	strncpy(szFullFileName, pszFileName, sizeof(szFullFileName));

	// ���ļ���ȫ��ת�ɴ�д
	strlwr(szFullFileName);

	// ע��sink
	if(!RegisterSink(szFullFileName, pSink, bDynamic))
	{
		return false;
	}

	// ����ű�
	CCsvReader csvreader;
	TiXmlDocument tixmldocument;
	bool bIsCsv = false;
	if(!__Load(szFullFileName, &csvreader, &tixmldocument, bIsCsv))
	{
		UnregisterSink(szFullFileName, pSink);
		return false;
	}

	//  ������һ
	m_nCallNum++;

	// ��sink
	THASH_SCHEMESINK::iterator it = m_hashSchemeSink.find(szFullFileName);
	if(it != m_hashSchemeSink.end())
	{
		SSINK * pSSink = &((*it).second);
		if(pSSink != NULL)
		{
			TLIST_SINK::iterator itList = pSSink->listSink.begin();
			for( ; itList != pSSink->listSink.end(); ++itList)
			{
				ISchemeUpdateSink * __pSink = (*itList);
				if(bIsCsv)
				{
					if(!__pSink->OnSchemeLoad(&csvreader, pszFileName))
					{
						// ������һ
						m_nCallNum--;

						return false;
					}
				}
				else
				{
					if(!__pSink->OnSchemeLoad(&tixmldocument, pszFileName))
					{
						// ������һ
						m_nCallNum--;

						return false;
					}
				}
			}
		}
	}	

	// ������һ
	m_nCallNum--;

	// �޸���
	m_bIsChange = true;

	return true;
}

/** ��������
@param   szFileName�������ļ���
@param   
@param   
@return  �ɹ�����true������Ϊfalse
@note     
@warning 
@retval buffer 
*/
bool CSchemeEngine::UpdateScheme(const char * pszFileName)
{
	if(pszFileName == NULL)
	{
		return false;
	}

	// ���ܱ�Ƕ�׵��ã�Ҳ�����ڻص�����װ������.
	if(m_nCallNum > 0)
	{
		memcpy(NULL, NULL, -1);
	}

	char szFullFileName[MAX_PATH] = { 0 };
	strncpy(szFullFileName, pszFileName, sizeof(szFullFileName));

	// ���ļ���ȫ��ת�ɴ�д
	strlwr(szFullFileName);

	// ���Ƿ��д�sink
	THASH_SCHEMESINK::iterator it = m_hashSchemeSink.find(szFullFileName);
	if(it == m_hashSchemeSink.end())
	{
		return false;
	}

	SSINK * pSSink = &((*it).second);
	if(pSSink == NULL || !pSSink->bDynamic)
	{
		return false;
	}

	// ����ű�
	CCsvReader csvreader;
	TiXmlDocument tixmldocument;
	bool bIsCsv = false;
	if(!__Load(szFullFileName, &csvreader, &tixmldocument, bIsCsv))
	{
		return false;
	}

	//  ������һ
	m_nCallNum++;

	// ��sink
	TLIST_SINK::iterator itList = pSSink->listSink.begin();
	for( ; itList != pSSink->listSink.end(); ++itList)
	{
		ISchemeUpdateSink * __pSink = (*itList);
		if(bIsCsv)
		{
			if(!__pSink->OnSchemeUpdate(&csvreader, pszFileName))
			{
				// ������һ
				m_nCallNum--;

				return false;
			}
		}
		else
		{
			if(!__pSink->OnSchemeUpdate(&tixmldocument, pszFileName))
			{
				// ������һ
				m_nCallNum--;

				return false;
			}
		}
	}

	// ������һ
	m_nCallNum--;

	return true;
}

/** ȡ��ע�����ûص��ӿ�
@param   szFileName�������ļ���
@param   pSink�����ø��»ص��ӿ�
@param   
@return  �ɹ�����true������Ϊfalse
@note     
@warning 
@retval buffer 
*/
bool CSchemeEngine::UnregisterSink(const char * szFileName, ISchemeUpdateSink * pSink)
{
	char szFullFileName[MAX_PATH] = { 0 };
	strncpy(szFullFileName, szFileName, sizeof(szFullFileName));

	// ���ļ���ȫ��ת�ɴ�д
	strlwr(szFullFileName);
	// ���Ƿ��Ѵ���
	THASH_SCHEMESINK::iterator it = m_hashSchemeSink.find(szFullFileName);
	if(it != m_hashSchemeSink.end())
	{
		SSINK * pSchemeSink = &((*it).second);
		pSchemeSink->listSink.remove(pSink);
	}

	return true;
}

/** ����ű�
@param   
@param   
@return  
*/
bool CSchemeEngine::__Load(const char * szFileName, CCsvReader * pCSVReader, TiXmlDocument * pTiXmlDocument, bool &bIsCsv)
{
	int nLen = strlen(szFileName);
	if(nLen <= 4)
	{
		return false;
	}

	const char * pExternName = szFileName + nLen - 3;
	if(stricmp(pExternName, "CSV") == 0)	
	{	
		bIsCsv = true;
		return __LoadCSV(szFileName, false, pCSVReader);		
	}
	else if(stricmp(pExternName, "CSC") == 0)
	{
		bIsCsv = true;
		return __LoadCSV(szFileName, true, pCSVReader);		
	}
	else if(stricmp(pExternName, "XML") == 0)
	{
		bIsCsv = false;
		return __LoadXML(szFileName, false, pTiXmlDocument);		
	}
	else if(stricmp(pExternName, "XMC") == 0)
	{
		bIsCsv = false;
		return __LoadXML(szFileName, true, pTiXmlDocument);		
	}	

	return false;
}

/** ����CSV����
@param   
@param   
@return  
*/
bool CSchemeEngine::__LoadCSV(const char * szFileName, bool bEncrypt, CCsvReader * pCSVReader)
{
	if(szFileName == NULL || pCSVReader == NULL)
	{
		return false;
	}

	return pCSVReader->Open(szFileName, bEncrypt);
}

/** ����XML����
@param   
@param   
@return  
*/
bool CSchemeEngine::__LoadXML(const char * szFileName, bool bEncrypt, TiXmlDocument * pTiXmlDocument)
{
	if(szFileName == NULL || pTiXmlDocument == NULL)
	{
		return false;
	}

	// ȡ���ļ�ϵͳ
	FileSystem * pFileSystem = getFileSystem();
	if(pFileSystem == NULL)
	{
		return false;
	}

	// ��ȡ�ļ�
	CStreamHelper stream = pFileSystem->open(szFileName);
	if(stream.isNull())
	{
		return false;
	}

	int nFileLength = stream->getLength();	

	char * pFileBuffer = new char [nFileLength + 1];
	if(!stream->read(pFileBuffer, nFileLength))
	{
		return false;
	}
	stream.close();
	
	// �������ļ�XML
	if(bEncrypt)
	{
		if(!makeMap((uchar *)pFileBuffer, nFileLength, 'LAND'))
		{
			return false;
		}
	}	

	// ����TiXmlDocumentȥ����
	pTiXmlDocument->Parse(pFileBuffer);

	delete [] pFileBuffer;
	pFileBuffer = NULL;

	return true;
}

/** ע��sink
@param   
@param   
@return  
*/
bool CSchemeEngine::RegisterSink(const char * szFileName, ISchemeUpdateSink * pSink, bool bDynamic)
{
	if(szFileName == NULL || pSink == NULL)
	{
		return false;
	}
	string stringFileName = szFileName;

	// ���Ƿ��Ѵ���
	THASH_SCHEMESINK::iterator it = m_hashSchemeSink.find(stringFileName);
	if(it != m_hashSchemeSink.end())
	{
		SSINK * pSchemeSink = &((*it).second);
		pSchemeSink->listSink.push_back(pSink);
		pSchemeSink->listSink.unique();
	}
	else
	{
		SSINK sink;
		sink.bDynamic = bDynamic;
		strncpy(sink.szFileName, szFileName, sizeof(sink.szFileName));
		sink.listSink.push_back(pSink);

		// ��ӵ�LIST��ȥ
		//string stringFileName = szFileName;
		m_hashSchemeSink[stringFileName] = sink;
	}

	return true;
}

/** ȡ�����пɶ�̬���µ�����
@param   
@param   
@return  
*/
list<string> * CSchemeEngine::GetDynamicSchemeFileName(void)
{
	if(!m_bIsChange)
	{
		return &m_listDynamicScheme;
	}
	m_bIsChange = false;

	// �ɶ�̬���µ�����
	m_listDynamicScheme.clear();

	// ����
	THASH_SCHEMESINK::iterator it = m_hashSchemeSink.begin();
	for( ; it != m_hashSchemeSink.end(); ++it)
	{
		SSINK * pSchemeSink = &((*it).second);
		if(pSchemeSink != NULL && pSchemeSink->bDynamic)
		{
			string str = pSchemeSink->szFileName;
			m_listDynamicScheme.push_back(str);
		}
	}

	return &m_listDynamicScheme;
}

/** �������
@param   
@param
@return  
*/
API_EXPORT ISchemeEngine * LoadSEM(void)
{
	// ��������ˣ���ֱ�ӷ���
	if(g_pSchemeEngine != NULL)
	{
		return g_pSchemeEngine;
	}

	// ʵ������������
	g_pSchemeEngine = new CSchemeEngine();
	if(g_pSchemeEngine == NULL)
	{
		return NULL;
	}	

	return g_pSchemeEngine;
}