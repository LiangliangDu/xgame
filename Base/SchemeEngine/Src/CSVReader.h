/*******************************************************************
** �ļ���:	e:\CoGame\SchemeEngine\src\SchemeEngine\CSVReader.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2007/6/23  18:54
** ��  ��:	1.0
** ��  ��:	CSV��ȡ��,��֧�ֱ���
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#include <string>
#include <vector>
#include <hash_map>
#include "ISchemeEngine.h"
using namespace std;
using namespace stdext;

/* csv�ļ���ʽ��
#version = 1.0.0.2
#macro camp1 = 10
#macro camp2 = 40
#macro camp3 = 60
��������, 	�Ƿ񹥻�,	Ѫ��,		����,			������,		��Ӫ
string		bool		int			int64			float		macro
������		true		1000		854202			189.2		camp1
������		false		25200		4545555			89625		camp2
��˹�׶�	0			5482122		212154587		184722.8	camp1
ѻצ������	1			45454545	235454545445	8788888.9	camp3

��ʽҪ�㣺
1����Ч�У�
	a����#�ſ�ͷ����(#��ǰ���԰�������Ŀհ׷����Ʊ��)������ע�ͣ�����ʱ����Ե�,����ʹ�����ġ�#���ַ�.
	b�����л���ֻ�пհ׷����Ʊ����ϳɵ��У�Ҳ����Ե���

2����Ч�У�
	a���ֶ������У������壬��������ͨ���������ܹ����ʵ����ݣ�����ʽǿ��Ҫ�����ֶ������У������ǵ�һ����Ч�У�
	b���ֶ������У������壬��������ͨ���������ܹ����ʵ����ݣ�����ʽǿ��Ҫ�����ֶ������У������ǵڶ�����Ч��
		bool	�������ͣ���0�����ߡ�false"(���Դ�Сд)��ʾʧ�ܣ�������ʾ�ɹ�
		int		����
		int64	64λ����
		float	������
		string	�ַ���		
	c����¼�У������壬������ÿ����¼����ͨ�����������з��ʣ��ӵ�������Ч�п�ʼ����Ч�ж��Ǽ�¼�У����ڳ���������0�С�

3���궨��
	a����#macro(ע�⣬��Ӣ��#����macro����ΪСд)��ͷ��Ϊ�궨�壬�궨���ֵĬ�϶�Ϊ�ַ�������Ҫ������
	b����������˺궨�壬Ӧ�ý���Ҫʹ�ú������ȫ���ú꣬���ҽ��ֶε�������Ϊmacro

4��������
	a��bool����֧��true,false���Ҳ֧��1,0����
	b��һ����¼ռһ�У�
	c��ÿ���ֶ�֮���÷ָ������зָ���
 */
class CCsvReader : public ICSVReader
{
	// ������������
	typedef vector< string >				TVECTOR_STRING;
	typedef hash_map< string, string >		THASH_MACROMAP;
	typedef vector< int >					TVECTOR_FIELDTYPE;
public:
	//////////////////////////// ICSVReader ///////////////////////////
	///////////////////////////////////////////////////////////////////
	/** �õ�ĳһ��(�Ѿ�ȥ����ĩβ���ܵĻس����з�)
	@param   dwRow�� ����������0��ʼ�����������������������  
	@param   
	@param   
	@return  �ɹ����ض�Ӧ�ַ�����������Խ�緵��NULL
	@note     
	@warning 
	@retval buffer 
	*/
	virtual	const char*			GetLine(DWORD dwRow);

	/** �õ�boolֵ
	@param dwRow�� ��Ч����������0��ʼ
	@param dwCol�� ����������0��ʼ
	@param bDef �� Ĭ�ϲ�����������������߶�λ��ֵδ�趨ʱ��ֱ�ӷ���Ĭ��ֵ  
	@return  ������Ӧ��boolֵ
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool			GetBool(DWORD dwRow, DWORD dwCol, bool bDef = false);

	/** �õ�intֵ
	@param dwRow�� ��Ч����������0��ʼ
	@param dwCol�� ����������0��ʼ
	@param nDef �� Ĭ�ϲ�����������������߶�λ��ֵδ�趨ʱ��ֱ�ӷ���Ĭ��ֵ
	@retval ������Ӧ��intֵ
	@note     
	@warning 
	@retval buffer 
	*/
	virtual	int				GetInt(DWORD dwRow, DWORD dwCol, int nDef = 0);

	/** �õ�LONGLONGֵ
	@param dwRow�� ��Ч����������0��ʼ
	@param dwCol�� ����������0��ʼ
	@param nDef �� Ĭ�ϲ�����������������߶�λ��ֵδ�趨ʱ��ֱ�ӷ���Ĭ��ֵ
	@retval ������Ӧ��LONGLONGֵ
	@note     
	@warning 
	@retval buffer 
	*/
	virtual	LONGLONG			GetInt64(DWORD dwRow, DWORD dwCol, LONGLONG nDef = 0);

	/** �õ�floatֵ
	@param dwRow�� ��Ч����������0��ʼ
	@param dwCol�� ����������0��ʼ
	@param fDef �� Ĭ�ϲ�����������������߶�λ��ֵδ�趨ʱ��ֱ�ӷ���Ĭ��ֵ
	@retval ������Ӧ��floatֵ 
	@note     
	@warning 
	@retval buffer 
	*/
	virtual float			GetFloat(DWORD dwRow, DWORD dwCol, float fDef = 0.0f);

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
	virtual bool			GetString(DWORD dwRow, DWORD dwCol, char* pszOutBuffer, int &nLen);

	/** ���������
	@param   
	@param   
	@param   
	@return  ����������
	@note     
	@warning 
	@retval buffer 
	*/ 
	virtual DWORD			GetRecordCount(void) const;

	/** ����ֶε���Ŀ
	@param   
	@param   
	@param   
	@return  �������ֶ���
	@note     
	@warning 
	@retval buffer 
	*/
	virtual DWORD			GetFieldCount(void) const;

	/** ͨ���ֶ�������ö�Ӧ��������
	@param   pszFieldDesc�� �ֶ������ַ���
	@param   
	@param   
	@return  ������Ӧ�������������ʧ�ܣ��򷵻�-1��
	@note     
	@warning 
	@retval buffer 
	*/
	virtual int				GetFieldIndex(const char* pszFieldDesc) const;

	/** ͨ����������ȡ��Ӧ���ֶ�����
	@param   dwCol�� ������
	@param   
	@param   
	@return  ������Ӧ���ֶ������ַ��������������Խ�磬�򷵻�NULL��
	@note     
	@warning 
	@retval buffer 
	*/
	virtual const char*			GetFieldDesc(DWORD dwCol) const;

	/** ͨ����������ö�Ӧ���ֶ�����(emUnKnow,emBool, emInt...)
	@param   dwCol��������
	@param   
	@param   
	@return  ������Ӧ�������������ʧ�ܣ��򷵻�emCSVUnKnow��
	@note     
	@warning 
	@retval buffer 
	*/
	virtual int				GetFieldType(DWORD dwCol) const;

	/** ��ȡָ���ĺ��ֵ
	@param  pszMacroName Ҫ��ȡ�ĺ������ 
	@param   
	@param   
	@return  ��Ӧ���ֵ����������ڷ���NULL
	@note     
	@warning 
	@retval buffer 
	*/
	virtual const char*			GetMacro(const char* pszMacroName) const;

	//////////////////////////// CCsvReader ///////////////////////////
	///////////////////////////////////////////////////////////////////
	/** �ҿ��ļ�
	@param   pszFileName���ļ���
	@param   
	@return  
	*/
	bool					Open(const char* pszFileName, bool bEncrypt);

	/** �ر�
	@param   
	@param   
	@return  
	*/
	void					Close(void);

	/** ���캯��
	@param   
	@param   
	@return  
	*/
	CCsvReader(char szSeparator = ',');

	/** ��������
	@param   
	@param   
	@return  
	*/
	virtual ~CCsvReader(void);

private:
	/** �򿪽ű�
	@param   
	@param   
	@return  
	*/
	bool					_Open(Stream * pStream);

	/** ȡ�ú��к����ַ�
	@param   
	@param   
	@return  
	*/
	bool					GetColString(DWORD dwRow, DWORD dwCol, char* pBuffer, DWORD dwBytes);

	/** 
	@param   
	@param   
	@return  
	*/
	void					GetColPos(const std::string &stringLine, DWORD dwCol, int &nStartPos, int &nEndPos, int nFrom = -1);

	/** �����ֶ�����
	@param   
	@param   
	@return  
	*/
	void					ParseFieldDesc(const std::string &stringLine);

	/** �����ֶ����� 
	@param   
	@param   
	@return  
	*/
	void					ParseFieldType(const std::string &stringLine);

	/** ������
	@param   
	@param   
	@return  
	*/
	bool					ParseMacro(const std::string &stringExp);

	/** ȥ���ո�ͻس���
	@param   
	@param   
	@return  
	*/
	void					FilterSpace(const char* pszStr, int nFrom, int nTo, int &nPos, int &nlen);

	//���ܱ༭ʹ�á�add wangtao
	vector<string>&         GetFiledDescVector();
	vector<int>&			GetFiledTypeVector();

private:
	char					m_szSeparator;		// �ֶμ�ķָ���
	int						m_nCurRow;			// ��ǰ��������(���ڼ��ٷ�����һ���ֶ�)	
	int						m_nCurCol;			// ��ǰ��������(���ڼ��ٷ�����һ���ֶ�)	
	int						m_nCurPos;			// ��ǰ�ֶεĽ���λ��(���ڼ��ٷ�����һ���ֶ�)
	TVECTOR_STRING			m_vectorLines;		// ���ַ���(������ע����)	
	TVECTOR_STRING			m_vectorFieldDesc;	// �ֶ�����	
	TVECTOR_FIELDTYPE		m_vectorFieldType;	// �ֶ�����	
	THASH_MACROMAP			m_hashMacroMap;		// ��ӳ���		

	// ��ǰ��ȡ���ļ���
	std::string				m_curStrName;		// ��ǰ�ļ���
};