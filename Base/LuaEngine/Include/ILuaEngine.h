/*******************************************************************
** �ļ���:	e:\CoGame\LuaEngine\build\ILuaEngine.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2007/8/24  19:22
** ��  ��:	1.0
** ��  ��:	Lua����
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

/// ����һ��
struct lua_State;

namespace xs {

/*! \addtogroup LuaEngine
*  lua����
*  @{
*/

enum
{
	PARAM_DATATYPE_NONE = -1,			/// LUA_TNONE
	PARAM_DATATYPE_NIL = 0,				/// LUA_TNIL
	PARAM_DATATYPE_BOOLEAN = 1,			/// LUA_TBOOLEAN
	PARAM_DATATYPE_LIGHTUSERDATA = 2,	/// LUA_TLIGHTUSERDATA
	PARAM_DATATYPE_NUMBER = 3,			/// LUA_TNUMBER
	PARAM_DATATYPE_STRING =	4,			/// LUA_TSTRING
	PARAM_DATATYPE_TABLE = 5,			/// LUA_TTABLE
	PARAM_DATATYPE_FUNCTION = 6,		/// LUA_TFUNCTION
	PARAM_DATATYPE_USERDATA	= 7,		/// LUA_TUSERDATA
	PARAM_DATATYPE_THREAD = 8,			/// LUA_TTHREAD
};


/// Lua����
class CLuaParam
{
public:
	/** 
	@param   
	@param   
	@return  
	*/
	void operator = (int nValue)
	{
		m_nDataType = PARAM_DATATYPE_NUMBER;
		memcpy(m_szValue, &nValue, sizeof(int));
	}

	/** 
	@param   
	@param   
	@return  
	*/
	void operator = (LPCSTR pszValue)
	{
		m_nDataType = PARAM_DATATYPE_STRING;
		strncpy(m_szValue, pszValue, sizeof(m_szValue) - 1);
	}

	/** 
	@param   
	@param   
	@return  
	*/
	void operator = (void * pValue)
	{
		m_nDataType = PARAM_DATATYPE_LIGHTUSERDATA;		
		memcpy(m_szValue, &pValue, sizeof(void *));
	}

	/** 
	@param   
	@param   
	@return  
	*/
	operator LPCSTR(void)
	{
		return m_szValue;
	}

	/** 
	@param   
	@param   
	@return  
	*/
	operator int(void)
	{
		return *((int *)m_szValue);
	}

	/** 
	@param   
	@param   
	@return  
	*/
	operator void *(void)
	{
		return (void *)(* (int *)m_szValue);
	}

	/** ȡ����������
	@param   
	@param   
	@return  
	*/
	int		GetDataType(void)
	{
		return m_nDataType;
	}

	/** ����
	@param   
	@param   
	@return  
	*/
	~CLuaParam(void)
	{
		m_nDataType = PARAM_DATATYPE_NUMBER;
		memset(m_szValue, 0, sizeof(m_szValue));
	}

private:
	/// ��������
	int				m_nDataType;

	/// ��̬���ɲ��ã�����Ƶ�������ײ�Ʒ�ڴ���Ƭ
	char			m_szValue[1024];	
};

/// lua������
struct ILuaEngine
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
	virtual void			Release(void) = 0;

	/** ȡ��lua_State *
	@param   
	@param   
	@param   
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual lua_State *		GetLuaState(void) = 0;	

	/** ִ��һ��lua�ű�
	@param   szLuaFileName �� lua�ļ���
	@param   
	@param   
	@return  �ɹ�������true,ʧ�ܣ�false
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool			LoadLuaFile(LPCSTR szLuaFileName) = 0;

	/** ִ��һ���ڴ���lua
	@param   pLuaData : �����lua ����
	@param   nDataLen �����ݳ���
	@param   
	@return  �ɹ�������true,ʧ�ܣ�false
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool			RunMemoryLua(LPCSTR pLuaData, int nDataLen) = 0;

	/** ִ��һ��lua����
	@param   szFuncName : lua������
	@param   pInParam : �����������ָ��
	@param   nInNum : �����������
	@param   pOutParam : �����������ָ��
	@param   nOutNum : �����������
	@return  �ɹ�������true,ʧ�ܣ�false
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool			RunLuaFunction(LPCSTR szFunName, CLuaParam * pInParam = 0, int nInNum = 0, CLuaParam * pOutParam = 0, int nOutNum = 0) = 0;

	/** ȡ��������͵�lua����
	@param
	@param
	@param 
	@return  ��������
	@note     
	@warning 
	@retval buffer 
	*/
	virtual const char*			GetLastError(void) = 0;

	/** ����Lua���棬�����¼������нű�
	@param
	@param
	@param 
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool			Reset(void) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(_LIB) || defined(LUAENGINE_STATIC_LIB)		/// ��̬��汾
	#	pragma comment(lib, MAKE_LIB_NAME(xs_lem))
	extern "C" ILuaEngine * CreateLuaEngine(bool bFromPackLoadLua);
	#	define	CreateLuaEngineProc	LoadLEM
#else													/// ��̬��汾
	typedef ILuaEngine * (RKT_CDECL *procCreateLuaEngine)(bool bFromPackLoadLua);
	#	define	CreateLuaEngineProc	DllApi<procCreateLuaEngine>::load(MAKE_DLL_NAME(xs_lem), "LoadLEM")
#endif

} //*namespace xs
