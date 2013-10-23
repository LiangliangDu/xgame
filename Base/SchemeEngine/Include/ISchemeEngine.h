/*******************************************************************
** �ļ���:	e:\CoGame\SchemeEngine\include\ISchemeEngine.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2007/6/23  14:57
** ��  ��:	1.0
** ��  ��:  ��������,CSVֻ֧�ֶ�ȡ��XML֧�ֶ�д
** Ӧ  ��:  ����������Ϊ�����Ч�ʺͱ���̫���鷳�����ﲻ�ܱ�Ƕ�׵��ã�Ҳ�����ڻص�����װ������.	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#include <list>
using namespace std;

// ����
class TiXmlDocument;

namespace xs {

/**************************** CSV��ȡ�� *****************************
********************************************************************/
// �ֶ�����
enum
{
	emCSVUnKnow = -1,		// δ֪
	emCSVBool,				// bool
	emCSVInt,				// int
	emCSVInt64,				// int64
	emCSVFloat,				// float
	emCSVString,			// string
	emCSVMacro,				// ��
	emCsvIntArray           //intArray          
};

// CSV��ȡ��
struct ICSVReader
{
	/** �õ�ĳһ��(�Ѿ�ȥ����ĩβ���ܵĻس����з�)
	@param   dwRow�� ����������0��ʼ�����������������������  
	@param   
	@param   
	@return  �ɹ����ض�Ӧ�ַ�����������Խ�緵��0
	@note     
	@warning 
	@retval buffer 
	*/
	virtual	const char*		GetLine(DWORD dwRow) = 0;

	/** �õ�boolֵ
	@param dwRow�� ��Ч����������0��ʼ
	@param dwCol�� ����������0��ʼ
	@param bDef �� Ĭ�ϲ�����������������߶�λ��ֵδ�趨ʱ��ֱ�ӷ���Ĭ��ֵ  
	@return  ������Ӧ��boolֵ
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool			GetBool(DWORD dwRow, DWORD dwCol, bool bDef = false) = 0;

	/** �õ�intֵ
	@param dwRow�� ��Ч����������0��ʼ
	@param dwCol�� ����������0��ʼ
	@param nDef �� Ĭ�ϲ�����������������߶�λ��ֵδ�趨ʱ��ֱ�ӷ���Ĭ��ֵ
	@retval ������Ӧ��intֵ
	@note     
	@warning 
	@retval buffer 
	*/
	virtual	int				GetInt(DWORD dwRow, DWORD dwCol, int nDef = 0) = 0;

	/** �õ�LONGLONGֵ
	@param dwRow�� ��Ч����������0��ʼ
	@param dwCol�� ����������0��ʼ
	@param nDef �� Ĭ�ϲ�����������������߶�λ��ֵδ�趨ʱ��ֱ�ӷ���Ĭ��ֵ
	@retval ������Ӧ��LONGLONGֵ
	@note     
	@warning 
	@retval buffer 
	*/
	virtual	LONGLONG		GetInt64(DWORD dwRow, DWORD dwCol, LONGLONG nDef = 0) = 0;

	/** �õ�floatֵ
	@param dwRow�� ��Ч����������0��ʼ
	@param dwCol�� ����������0��ʼ
	@param fDef �� Ĭ�ϲ�����������������߶�λ��ֵδ�趨ʱ��ֱ�ӷ���Ĭ��ֵ
	@retval ������Ӧ��floatֵ 
	@note     
	@warning 
	@retval buffer 
	*/
	virtual float			GetFloat(DWORD dwRow, DWORD dwCol, float fDef = 0.0f) = 0;

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
	virtual bool			GetString(DWORD dwRow, DWORD dwCol, char* pszOutBuffer, int &nLen) = 0;

	/** ���������
	@param   
	@param   
	@param   
	@return  ����������
	@note     
	@warning 
	@retval buffer 
	*/ 
	virtual DWORD			GetRecordCount(void) const = 0;

	/** ����ֶε���Ŀ
	@param   
	@param   
	@param   
	@return  �������ֶ���
	@note     
	@warning 
	@retval buffer 
	*/
	virtual DWORD			GetFieldCount(void) const = 0;

	/** ͨ���ֶ�������ö�Ӧ��������
	@param   pszFieldDesc�� �ֶ������ַ���
	@param   
	@param   
	@return  ������Ӧ�������������ʧ�ܣ��򷵻�-1��
	@note     
	@warning 
	@retval buffer 
	*/
	virtual int				GetFieldIndex(const char* pszFieldDesc) const = 0;

	/** ͨ����������ȡ��Ӧ���ֶ�����
	@param   dwCol�� ������
	@param   
	@param   
	@return  ������Ӧ���ֶ������ַ��������������Խ�磬�򷵻�0��
	@note     
	@warning 
	@retval buffer 
	*/
	virtual const char *	GetFieldDesc(DWORD dwCol) const = 0;

	/** ͨ����������ö�Ӧ���ֶ�����(emCSVUnKnow,emCSVBool, emCSVInt,emCSVInt64...)
	@param   dwCol��������
	@param   
	@param   
	@return  ������Ӧ�������������ʧ�ܣ��򷵻�emCSVUnKnow��
	@note     
	@warning 
	@retval buffer 
	*/
	virtual int				GetFieldType(DWORD dwCol) const = 0;

	/** ��ȡָ���ĺ��ֵ
	@param  pszMacroName Ҫ��ȡ�ĺ������ 
	@param   
	@param   
	@return  ��Ӧ���ֵ����������ڷ���0
	@note     
	@warning 
	@retval buffer 
	*/
	virtual const char *	GetMacro(const char* pszMacroName) const = 0;

	//���ܱ༭ʹ�á�add wangtao
	virtual vector<string>&         GetFiledDescVector() = 0;
	virtual vector<int>&			GetFiledTypeVector() = 0;
};


/************************** ��������ӿ� ****************************
********************************************************************/
// ���ø��»ص��ӿ�
struct ISchemeUpdateSink
{
	/** CSV��������ʱ֪ͨ
	@param   pCSVReader����ȡCSV�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/ 
	virtual bool			OnSchemeLoad(ICSVReader * pCSVReader,const char* szFileName) = 0;

	/** XML��������ʱ֪ͨ
	@param   pTiXmlDocument����ȡXML�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/
	virtual bool			OnSchemeLoad(TiXmlDocument * pTiXmlDocument,const char* szFileName) = 0;

	
	/** ���ö�̬����ʱ֪ͨ
	@param   pCSVReader����ȡCSV�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/
	virtual bool			OnSchemeUpdate(ICSVReader * pCSVReader, const char* szFileName) = 0;

	/** ���ö�̬����ʱ֪ͨ
	@param   pTiXmlDocument����ȡXML�ķ��ؽӿ�
	@param   szFileName�������ļ���
	@param   
	@return  
	@note     
	@warning ��Ҫ�ڴ˷����ͷ�pCSVReader����pTiXmlDocument,��Ϊһ���ļ���Ӧ���sink
	@retval buffer 
	*/
	virtual bool			OnSchemeUpdate(TiXmlDocument * pTiXmlDocument, const char* szFileName) = 0;
};

struct ISchemeEngine
{
	/** �ͷ���������
	@param   
	@param   
	@param   
	@return  
	@note     
	@warning 
	@retval buffer 
	*/	
	virtual void			Release(void) = 0;

	/** ��������,���Զ�ע��sink
	@param   szFileName�������ļ���������Ϊ����·��
	@param   pSink�����ø��»ص��ӿ�
	@param   bDynamic:�Ƿ�֧�ֶ�̬����
	@return  �ɹ�����true������Ϊfalse
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool			LoadScheme(const char* szFileName, ISchemeUpdateSink * pSink, bool bDynamic = true) = 0;

	/** ��������
	@param   szFileName�������ļ���������Ϊ����·��
	@param   
	@param   
	@return  �ɹ�����true������Ϊfalse
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool			UpdateScheme(const char* szFileName) = 0;

	/** ȡ��ע�����ûص��ӿ�
	@param   szFileName�������ļ���������Ϊ����·��
	@param   pSink�����ø��»ص��ӿ�
	@param   
	@return  �ɹ�����true������Ϊfalse
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool			UnregisterSink(const char* szFileName, ISchemeUpdateSink * pSink) = 0;

	/** ȡ�����пɶ�̬���µ�����
	@param   
	@param   
	@return  
	*/
	virtual list<string> *	GetDynamicSchemeFileName(void) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(_LIB) || defined(SCHEMEENGINE_STATIC_LIB)	/// ��̬��汾
	#	pragma comment(lib, MAKE_LIB_NAME(xs_sem))
extern "C" xs::ISchemeEngine * LoadSEM(void);
	#	define	CreateSchemeEngineProc	LoadSEM
#else													/// ��̬��汾
typedef xs::ISchemeEngine * (RKT_CDECL *procCreateSchemeEngine)(void);
	#	define	CreateSchemeEngineProc	DllApi<procCreateSchemeEngine>::load(MAKE_DLL_NAME(xs_sem), "LoadSEM")
#endif

} //*namespace xs/
