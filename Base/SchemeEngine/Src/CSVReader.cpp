 /*******************************************************************
** �ļ���:	e:\CoGame\SchemeEngine\src\SchemeEngine\CSVReader.cpp
** ��  Ȩ:	(C) 
** 
** ��  ��:	2007/6/23  15:17
** ��  ��:	1.0
** ��  ��:	CSV��ȡ��,��֧�ֱ���
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#include "stdafx.h"
#include <string.h>
#include "CSVReader.h"


/** ���캯��
@param   
@param   
@return  
*/
CCsvReader::CCsvReader(char szSeparator)
{
	m_szSeparator = szSeparator;
	m_nCurRow = -1;
	m_nCurCol = -1;
	m_nCurPos = -1;
}

/** ��������
@param   
@param   
@return  
*/
CCsvReader::~CCsvReader(void)
{

}

/** �õ�ĳһ��(�Ѿ�ȥ����ĩβ���ܵĻس����з�)
@param   dwRow�� ����������0��ʼ�����������������������  
@param   
@param   
@return  �ɹ����ض�Ӧ�ַ�����������Խ�緵��NULL
@note     
@warning 
@retval buffer 
*/
const char* CCsvReader::GetLine(DWORD dwRow)
{
	if(dwRow < m_vectorLines.size())
	{
		return m_vectorLines[dwRow].c_str();
	}

	return NULL;
}

/** �õ�boolֵ
@param dwRow�� ��Ч����������0��ʼ
@param dwCol�� ����������0��ʼ
@param bDef �� Ĭ�ϲ�����������������߶�λ��ֵδ�趨ʱ��ֱ�ӷ���Ĭ��ֵ  
@return  ������Ӧ��boolֵ
@note     
@warning 
@retval buffer 
*/
bool CCsvReader::GetBool(DWORD dwRow, DWORD dwCol, bool bDef)
{
	char szBuffer[512] = { 0 };
	if(!GetColString(dwRow, dwCol, szBuffer, 512))
	{
		return bDef;
	}

	if(stricmp(szBuffer, "false") == 0 || stricmp(szBuffer, "0") == 0)
	{
		return false;
	}

	return true;
}

/** �õ�intֵ
@param dwRow�� ��Ч����������0��ʼ
@param dwCol�� ����������0��ʼ
@param nDef �� Ĭ�ϲ�����������������߶�λ��ֵδ�趨ʱ��ֱ�ӷ���Ĭ��ֵ
@retval ������Ӧ��intֵ
@note     
@warning 
@retval buffer 
*/
int	CCsvReader::GetInt(DWORD dwRow, DWORD dwCol, int nDef)
{
	char szBuffer[512] = { 0 };
	if(!GetColString(dwRow, dwCol, szBuffer, 512))
	{
		return nDef;
	}

	return atoi(szBuffer);
}

/** �õ�LONGLONGֵ
@param dwRow�� ��Ч����������0��ʼ
@param dwCol�� ����������0��ʼ
@param nDef �� Ĭ�ϲ�����������������߶�λ��ֵδ�趨ʱ��ֱ�ӷ���Ĭ��ֵ
@retval ������Ӧ��LONGLONGֵ
@note     
@warning 
@retval buffer 
*/
LONGLONG CCsvReader::GetInt64(DWORD dwRow, DWORD dwCol, LONGLONG nDef)
{
	char szBuffer[512] = { 0 };
	if(!GetColString(dwRow, dwCol, szBuffer, 512))
	{
		return nDef;
	}

	LONGLONG value;
	sscanf(szBuffer,"%llu",&value);
	return value;
}

/** �õ�floatֵ
@param dwRow�� ��Ч����������0��ʼ
@param dwCol�� ����������0��ʼ
@param fDef �� Ĭ�ϲ�����������������߶�λ��ֵδ�趨ʱ��ֱ�ӷ���Ĭ��ֵ
@retval ������Ӧ��floatֵ 
@note     
@warning 
@retval buffer 
*/
float CCsvReader::GetFloat(DWORD dwRow, DWORD dwCol, float fDef)
{
	char szBuffer[512] = { 0 };
	if(!GetColString(dwRow, dwCol, szBuffer, 512))
	{
		return fDef;
	}

	return (float)atof(szBuffer);
}

/** �õ�stringֵ
@param dwRow�� ��Ч����������0��ʼ
@param dwCol�� ����������0��ʼ
@param pszOutBuffer��������������buffer,���pszBufferΪ�գ�nLen�򷵻�ʵ�ʳ���
@param nLen������������󳤶ȣ�ʵ�ʷ��صĳ���Ҳ�������������
@retval �ɹ���true, ʧ��:flase
@note     
@warning 
@retval buffer 
*/
bool CCsvReader::GetString(DWORD dwRow, DWORD dwCol, char* pszOutBuffer, int &nLen)
{
	if(dwRow >= m_vectorLines.size() || dwCol >= m_vectorFieldDesc.size())
	{
		nLen = 0;
		return false;
	}

	int nStartPos = 0, nEndPos = 0, nFrom = -1;
	if(m_nCurRow == dwRow && m_nCurCol + 1 == (int)dwCol)
	{
		nFrom = m_nCurPos;
	}
	
	GetColPos(m_vectorLines[dwRow], dwCol, nStartPos, nEndPos, nFrom);
	if(nStartPos == -1 && nEndPos == -1)
	{
		nLen = 0;
		return false;
	}

	const char* pszDebugTest = m_vectorLines[dwRow].c_str();
	
	m_nCurRow = dwRow;
	m_nCurCol = dwCol;
	m_nCurPos = nEndPos;
	std::string strout = m_vectorLines[dwRow].substr(nStartPos + 1, nEndPos - nStartPos - 1);

	pszDebugTest = strout.c_str();

	// �Ƿ�Ϊ��?
	THASH_MACROMAP::iterator it = m_hashMacroMap.find(strout);
	if(it != m_hashMacroMap.end())
	{
		if(pszOutBuffer == NULL)
		{
			nLen = ((*it).second).size() + 1;
		}
		else
		{
			if(nLen > ((*it).second).size())
			{
				nLen = ((*it).second).size();				
			}			
			
			strncpy(pszOutBuffer, ((*it).second).c_str(), nLen);
		}	
		
		return true;
	}

	if(pszOutBuffer == NULL)
	{
		nLen = strout.size() + 1;
	}
	else
	{
		if(nLen > strout.size())
		{
			nLen = strout.size() + 1;			
		}

		strncpy(pszOutBuffer, strout.c_str(), nLen);
	}	

	return true;
}

/** ���������
@param   
@param   
@param   
@return  ����������
@note     
@warning 
@retval buffer 
*/ 
DWORD CCsvReader::GetRecordCount(void) const
{
	return (DWORD)m_vectorLines.size();
}

/** ����ֶε���Ŀ
@param   
@param   
@param   
@return  �������ֶ���
@note     
@warning 
@retval buffer 
*/
DWORD CCsvReader::GetFieldCount(void) const
{
	return (DWORD)m_vectorFieldDesc.size();
}

/** ͨ���ֶ�������ö�Ӧ��������
@param   pszFieldDesc�� �ֶ������ַ���
@param   
@param   
@return  ������Ӧ�������������ʧ�ܣ��򷵻�-1��
@note     
@warning 
@retval buffer 
*/
int	CCsvReader::GetFieldIndex(const char* pszFieldDesc) const
{
	if(pszFieldDesc == NULL)
	{
		return -1;
	}

	for(int i = 0; i < (int)m_vectorFieldDesc.size(); i++)
	{
		if(stricmp(m_vectorFieldDesc[i].c_str(), pszFieldDesc) == 0)
		{
			return i;
		}
	}

	return -1;
}

/** ͨ����������ȡ��Ӧ���ֶ�����
@param   dwCol�� ������
@param   
@param   
@return  ������Ӧ���ֶ������ַ��������������Խ�磬�򷵻�NULL��
@note     
@warning 
@retval buffer 
*/
const char* CCsvReader::GetFieldDesc(DWORD dwCol) const
{
	if(dwCol >= m_vectorFieldDesc.size())
	{
		return NULL;
	}

	if(dwCol < m_vectorFieldDesc.size())
	{
		return m_vectorFieldDesc[dwCol].c_str();
	}

	return NULL;
}

/** ͨ����������ö�Ӧ���ֶ�����(emUnKnow,emBool, emInt...)
@param   dwCol��������
@param   
@param   
@return  ������Ӧ�������������ʧ�ܣ��򷵻�emCSVUnKnow��
@note     
@warning 
@retval buffer 
*/
int CCsvReader::GetFieldType(DWORD dwCol) const
{
	if(dwCol < m_vectorFieldType.size())
	{
		return m_vectorFieldType[dwCol];
	}

	return (int)emCSVUnKnow;
}

/** ��ȡָ���ĺ��ֵ
@param  pszMacroName Ҫ��ȡ�ĺ������ 
@param   
@param   
@return  ��Ӧ���ֵ����������ڷ���NULL
@note     
@warning 
@retval buffer 
*/
const char* CCsvReader::GetMacro(const char* pszMacroName) const
{
	if(pszMacroName == NULL)
	{
		return NULL;
	}

	THASH_MACROMAP::const_iterator it = m_hashMacroMap.find(pszMacroName);
	if(it != m_hashMacroMap.end())
	{
		return ((*it).second).c_str();
	}

	return NULL;
}

/** �ҿ��ļ�
@param   pszFileName���ļ���
@param   
@return  
*/
bool CCsvReader::Open(const char* pszFileName, bool bEncrypt)
{
	if(pszFileName == NULL)
	{
		return false;
	}

	m_curStrName = pszFileName;

	// ȡ���ļ�ϵͳ
	FileSystem * pFileSystem = getFileSystem();
	if(pFileSystem == NULL)
	{
		return false;
	}

	// ��ȡ�ļ�
	Stream * pStream = pFileSystem->open(pszFileName);
	if(pStream == NULL)
	{
		return false;
	}

	// �����ļ�
	char * pFileBuffer = NULL;
	MemoryStream memorystream;
	if(bEncrypt)
	{
		int nFileLength = pStream->getLength();
		pFileBuffer = new char [nFileLength + 1];
		if(!pStream->read(pFileBuffer, nFileLength))
		{
			return false;
		}
		pStream->close();
		pStream->release();

		if(!makeMap((uchar *)pFileBuffer, nFileLength, 'LAND'))
		{
			return false;
		}

		memorystream.attach((uchar *)pFileBuffer, nFileLength);
		pStream = &memorystream;
	}
	
	// ����
	if(!_Open(pStream))
	{
		if(pFileBuffer != NULL)
		{
			delete [] pFileBuffer;
			pFileBuffer = NULL;
		}
		
		// �ر��ļ�
		pStream->close();
		pStream->release();
		return false;
	}
	// �ر��ļ�
	pStream->close();
	
	pStream->release();
	if(pFileBuffer != NULL)
	{
		delete [] pFileBuffer;
		pFileBuffer = NULL;
	}
	return true;
}

/** �ر�
@param   
@param   
@return  
*/
void CCsvReader::Close(void)
{
	m_vectorLines.clear();
	m_vectorFieldDesc.clear();
	m_vectorFieldType.clear();
	m_nCurRow = m_nCurCol = m_nCurPos = -1;
}

/** �򿪽ű�
@param   
@param   
@return  
*/
bool CCsvReader::_Open(Stream *pStream)
{
	if(pStream == NULL)
	{
		return false;
	}	

	DWORD dwValidLineCount = 0;
	char  szBuffer[2048] = { 0 };
	uint dwLength = sizeof(szBuffer);
	bool  bRet = pStream->readString(szBuffer, dwLength);
	while(bRet)
	{
		// ���ע���л��߿���
		DWORD dwLen = strlen(szBuffer);
		if(dwLen > 0)
		{
			if(szBuffer[dwLen - 1] == '\r' || szBuffer[dwLen - 1] == '\n')
			{
				szBuffer[dwLen - 1] = 0;
				dwLen--;
			}
			if(dwLen > 1 && (szBuffer[dwLen - 2] == '\r' || szBuffer[dwLen - 2] == '\n'))
			{
				szBuffer[dwLen - 2] = 0;
				dwLen--;
			}
		}

		bool bMustContinue = false;
		if(dwLen > 0)
		{
			// ���Կ���
			int __nPos = 0;
			bool __bFlag = false;
			while(__nPos < dwLen)
			{
				if(szBuffer[__nPos] != m_szSeparator)
				{
					__bFlag = true;
				}
				__nPos++;
			}
			if(!__bFlag)
			{
				bMustContinue = true;
			}
			else
			{
				// �ո���Ʊ������
				int nPos = 0;
				while(szBuffer[nPos] && (szBuffer[nPos] == ' ' || szBuffer[nPos] == '\t')) 
				{
					nPos++;
				}

				if(nPos >= (int)dwLen)
				{
					bMustContinue = true;
				}
				else if(szBuffer[nPos] == '#')
				{
					// #macro
					if(nPos + 5 < (int)dwLen && memcmp(&szBuffer[nPos + 1], "macro", 5) == 0)
					{
						ParseMacro(&szBuffer[nPos + 6]);
					}

					bMustContinue = true;
				}
			}
		}
		else
		{
			bMustContinue = true;
		}

		if(!bMustContinue)
		{
			// ������������
			if(dwValidLineCount == 0) // ����ֶ�������
			{
				ParseFieldDesc(szBuffer);
				dwValidLineCount++;
			}
			else if(dwValidLineCount == 1) // ����ֶ�������
			{
				ParseFieldType(szBuffer);
				dwValidLineCount++;
			}
			else // ���ʵ�ʵ����ݼ�¼
			{
				// add by zjp
				// ��Ӣ�ĵı����ſ��ܻᵼ�����ñ��ȡʧ�ܣ���Ӷ����ñ��ʱ��һ���������
				// �жϻ��ƣ�ÿһ�������н����������ֶ���Ŀ�������е��ֶ���Ŀ��ͬ
				int nSize = m_vectorFieldType.size();
				size_t start_pos = std::string::npos;
				const std::string stringLine = szBuffer;
				size_t end_pos = stringLine.find_first_of(m_szSeparator);
				int nCount = 0;
				while(end_pos != std::string::npos) // find
				{
					nCount++;
					start_pos = end_pos;
					end_pos = stringLine.find_first_of(m_szSeparator, start_pos + 1);
					if(end_pos == std::string::npos && start_pos < stringLine.length())
					{
						end_pos = stringLine.length();
					}
				}

				if (nSize!=nCount)
				{
					ErrorLn("���ñ������Ӣ�Ķ���������,�ļ���:"<<m_curStrName.c_str()<<"���������Ч�е��к�Ϊ:"<<m_vectorLines.size()+3);
				}

				m_vectorLines.push_back(szBuffer);
			}
		}

		// ����һ��
		dwLength = sizeof(szBuffer);
		bRet = pStream->readString(szBuffer, dwLength);
	}

	return true;
}

/** ȡ�ú��к����ַ�
@param   
@param   
@return  
*/
bool CCsvReader::GetColString(DWORD dwRow, DWORD dwCol, char* pBuffer, DWORD dwBytes)
{
	if(dwRow >= m_vectorLines.size() || dwCol >= m_vectorFieldDesc.size())
	{
		return false;
	}

	if(pBuffer == NULL || dwBytes <= 0)
	{
		return false;
	}

	int nStartPos = 0, nEndPos = 0, nFrom = -1;	
	if(m_nCurRow == dwRow && m_nCurCol + 1 == (int)dwCol)
	{
		nFrom = m_nCurPos;
	}

	std::string &str = m_vectorLines[dwRow];
	GetColPos(str, dwCol, nStartPos, nEndPos, nFrom);
	if(nStartPos == -1 && nEndPos == -1) // no find
	{
		return false;
	}

	m_nCurRow = dwRow;
	m_nCurCol = dwCol;
	m_nCurPos = nEndPos;
	int nLen  = nEndPos - nStartPos - 1;
	if((int)dwBytes <= nLen)
	{
		nLen = dwBytes - 1;
	}
	else if(nLen == 0)
	{
		return false;
	}

	strncpy(pBuffer, &str[nStartPos + 1], nLen);
	pBuffer[nLen] = 0;

	// �Ƿ��Ǻ�?
	THASH_MACROMAP::iterator it = m_hashMacroMap.find(pBuffer);
	if(it != m_hashMacroMap.end())
	{
		strncpy(pBuffer, ((*it).second).c_str(), dwBytes - 1);
		pBuffer[((*it).second).length()] = 0;
	}

	return true;
}

/** 
@param   
@param   
@return  
*/
void CCsvReader::GetColPos(const std::string &stringLine, DWORD dwCol, int &nStartPos, int &nEndPos, int nFrom)
{
	if(dwCol >= m_vectorFieldDesc.size())
	{
		return;
	}

	if(nFrom >= (int)stringLine.length() || dwCol >= m_vectorFieldDesc.size())
	{
		nStartPos = nEndPos = -1;
		return;
	}

	// ��λ�еĿ�ʼλ��
	size_t start_pos = nFrom;
	if(start_pos == -1) // ��ͷ��ʼ��
	{
		for(int i = 0; i < (int)dwCol; i++)
		{
			start_pos = stringLine.find_first_of(m_szSeparator, start_pos + 1);
			if(start_pos == std::string::npos)
			{				
				nStartPos = nEndPos = -1;

				return;
			}
		}
	}

	// ��λ�еĽ���λ��
	size_t end_pos = stringLine.find_first_of(m_szSeparator, start_pos + 1);
	if(end_pos != std::string::npos)
	{
		nStartPos = start_pos;
		nEndPos = end_pos;
	}
	else
	{		
		nStartPos = start_pos;
		nEndPos = stringLine.length();
	}
}

/** �����ֶ�����
@param   
@param   
@return  
*/
void CCsvReader::ParseFieldDesc(const std::string &stringLine)
{
	size_t start_pos = std::string::npos;
	size_t end_pos = stringLine.find_first_of(m_szSeparator);
	while(end_pos != std::string::npos) // find
	{
		std::string str = stringLine.substr(start_pos + 1, end_pos - start_pos - 1);
		m_vectorFieldDesc.push_back(str);
		start_pos = end_pos;
		end_pos = stringLine.find_first_of(m_szSeparator, start_pos + 1);
		if(end_pos == std::string::npos && start_pos < stringLine.length())
		{
			end_pos = stringLine.length();
		}
	}
}

/** �����ֶ����� 
@param   
@param   
@return  
*/
void CCsvReader::ParseFieldType(const std::string &stringLine)
{
	size_t start_pos = std::string::npos;
	size_t end_pos = stringLine.find_first_of(m_szSeparator);
	while(end_pos != std::string::npos) // find
	{
		std::string str = stringLine.substr(start_pos + 1, end_pos - start_pos - 1);
		if(stricmp(str.c_str(), "bool") == 0)
		{
			m_vectorFieldType.push_back((int)emCSVBool);
		}
		else if(stricmp(str.c_str(), "int") == 0)
		{
			m_vectorFieldType.push_back((int)emCSVInt);
		}
		else if(stricmp(str.c_str(), "int64") == 0)
		{
			m_vectorFieldType.push_back((int)emCSVInt64);
		}
		else if(stricmp(str.c_str(), "float") == 0)
		{
			m_vectorFieldType.push_back((int)emCSVFloat);
		}
		else if(stricmp(str.c_str(), "string") == 0)
		{
			m_vectorFieldType.push_back((int)emCSVString);
		}
		else if(stricmp(str.c_str(), "intArray") == 0)
		{
			m_vectorFieldType.push_back((int)emCsvIntArray);
		}
		else
		{			
			m_vectorFieldType.push_back((int)emCSVUnKnow);
		}

		start_pos = end_pos;
		end_pos = stringLine.find_first_of(m_szSeparator, start_pos + 1);
		if(end_pos == std::string::npos && start_pos < stringLine.length())
		{
			end_pos = stringLine.length();
		}
	}
}

/** ������
@param   
@param   
@return  
*/
bool CCsvReader::ParseMacro(const std::string &stringExp)
{
	size_t pos = stringExp.find('=');
	size_t len = stringExp.length();
	if(pos > 0 && pos < len)
	{
		int nNamePos;
		int nNameLen = 0;
		FilterSpace(stringExp.c_str(), 0, pos, nNamePos, nNameLen);
		int nValuePos;
		int nValueLen = 0;
		FilterSpace(stringExp.c_str(), pos + 1, len, nValuePos, nValueLen);

		if(nNameLen > 0 && nValueLen > 0)
		{
			std::string name = stringExp.substr(nNamePos, nNameLen);
			std::string value = stringExp.substr(nValuePos, nValueLen);
			m_hashMacroMap[name] = value;
			return true;
		}
	}

	return false;	
}

/** ȥ���ո�ͻس���
@param   
@param   
@return  
*/
void CCsvReader::FilterSpace(const char* pszStr, int nFrom, int nTo, int &nPos, int &nlen)
{
	if(pszStr == NULL)
	{
		return;
	}

	if(nFrom == nTo)
	{
		nPos = -1;
		nlen = 0;
		return;
	}

	if(nFrom > nTo)
	{
		size_t tmp = nFrom;
		nFrom = nTo;
		nTo = tmp;
	}

	while(nFrom < nTo && pszStr[nFrom] && (pszStr[nFrom] == m_szSeparator || pszStr[nFrom] == ' ' || pszStr[nFrom] == '\t')) // �ո���Ʊ������
	{
		nFrom++;
	}

	nTo--;
	while(nTo > nFrom && pszStr[nTo] && (pszStr[nTo] == m_szSeparator || pszStr[nTo] == ' ' || pszStr[nTo] == '\t')) // �ո���Ʊ������
	{
		nTo--;
	}

	nPos = nFrom;
	nlen = nTo - nFrom + 1;
}

vector<string>& CCsvReader::GetFiledDescVector()
{
	return m_vectorFieldDesc;
}

vector<int>& CCsvReader::GetFiledTypeVector()
 {
 	return m_vectorFieldType;
 }
