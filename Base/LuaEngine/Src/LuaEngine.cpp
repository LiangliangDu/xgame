/*******************************************************************
** �ļ���:	e:\CoGame\LuaEngine\src\LuaEngine\LuaEngine.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2007/8/22  14:26
** ��  ��:	1.0
** ��  ��:	lua����
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#include "stdafx.h"
#include "LuaEngine.h"

CLuaEngine * g_pLuaEngine = NULL;
/** ���д���׷��(��Ϣ��
@param   
@param   
@return  
*/
static int luaA_Trace(lua_State *L)
{
	int n = lua_gettop(L);  /* �������� */
	int i;
	lua_getglobal(L, "tostring");
	for (i=1; i<=n; i++) {
		const char *s;
		lua_pushvalue(L, -1);  /* function to be called */
		lua_pushvalue(L, i);   /* value to print */
		lua_call(L, 1, 1);
		s = lua_tostring(L, -1);  /* get result */
		if (s == NULL)
			return luaL_error(L, "`tostring' must return a string to `print'");
		if (i>1) Info("\t");
		Info(s);
		lua_pop(L, 1);  /* pop result */
	}
	Info(endl);
	return 0;
}

/** ���д���׷��(����
@param   
@param   
@return  
*/
static int luaA_Error (lua_State *L)
{
	int n = lua_gettop(L);  /* number of arguments */
	int i;
	lua_getglobal(L, "tostring");
	for (i=1; i<=n; i++) {
		const char *s;
		lua_pushvalue(L, -1);  /* function to be called */
		lua_pushvalue(L, i);   /* value to print */
		lua_call(L, 1, 1);
		s = lua_tostring(L, -1);  /* get result */
		if (s == NULL)
			return luaL_error(L, "`tostring' must return a string to `print'");
		if (i>1) Error("\t");
		Error(s);
		lua_pop(L, 1);  /* pop result */
	}
	Error(endl);
	return 0;
}

/** ���д���׷��(���棩
@param   
@param   
@return  
*/
static int luaA_Warning(lua_State *L)
{
	int n = lua_gettop(L);  /* number of arguments */
	int i;
	lua_getglobal(L, "tostring");
	for (i=1; i<=n; i++) {
		const char *s;
		lua_pushvalue(L, -1);  /* function to be called */
		lua_pushvalue(L, i);   /* value to print */
		lua_call(L, 1, 1);
		s = lua_tostring(L, -1);  /* get result */
		if (s == NULL)
			return luaL_error(L, "`tostring' must return a string to `print'");
		if (i>1) Warning("\t");
		Warning(s);
		lua_pop(L, 1);  /* pop result */
	}
	Warning(endl);
	return 0;
}

/** ����lua
@param   
@param   
@return  
*/
static int luaA_LoadLua(lua_State * L)
{
	size_t l;
	const char * sFileName = luaL_checklstring(L, 1, &l);
	if(sFileName != NULL && g_pLuaEngine != NULL)
	{
		return g_pLuaEngine->LoadLuaFile(sFileName);
	}

	return false;
}

/* function: getWorkDir */
static int luaA_getWorkDir(lua_State* L)
{
	tolua_pushstring(L, getWorkDir());
	return 1;
}


/** ����
@param   
@param   
@return  
*/
CLuaEngine::CLuaEngine(void)
{
	m_pLuaState = NULL;

	m_bFromPackLoadLua = true;
}

/** ����
@param   
@param   
@return  
*/
CLuaEngine::~CLuaEngine(void)
{

}

/** �ͷ�
@param   
@param   
@param   
@return  
@note     �ͷ�������Դ���������ٴ˶���
@warning 
@retval buffer 
*/
void CLuaEngine::Release(void)
{
	if(m_pLuaState != NULL)
	{
		lua_close(m_pLuaState);
	}

	//ȫ�ֱ�����ħ��!
	assert (this == g_pLuaEngine);
	g_pLuaEngine = NULL;

	delete this;
}

/** ����
@param   
@param   
@return  
*/
bool CLuaEngine::Create(bool bFromPackLoadLua)
{
	// �Ƿ�Ӱ�������lua
	m_bFromPackLoadLua = bFromPackLoadLua;

	// ��ʼ��LUA��
	m_pLuaState = lua_open();
	if(m_pLuaState == NULL)
	{
		return false;
	}

	// ��ʼ�����еı�׼��
	luaopen_base(m_pLuaState);
	luaopen_io(m_pLuaState);
	luaopen_string(m_pLuaState);
	luaopen_table(m_pLuaState);	
	luaopen_math(m_pLuaState);
	luaopen_loadlib(m_pLuaState);
	//luaL_openlibs(m_pLuaState);
	//luaopen_debug(m_pLuaState);

	// ����II�����й������⣬��ջ̫С��������Ƶ���ĵ���
	lua_checkstack(m_pLuaState, 256);

	// ��ʼ��һЩ������api
	lua_register(m_pLuaState, "dofile", luaA_LoadLua);	
	lua_register(m_pLuaState, "print", luaA_Trace);
	lua_register(m_pLuaState, "trace", luaA_Trace);
	lua_register(m_pLuaState, "error", luaA_Error);
	lua_register(m_pLuaState, "warning", luaA_Warning);
	lua_register(m_pLuaState, "getWorkDir", luaA_getWorkDir);

	return true;
}

/** ȡ��lua_State *
@param   
@param   
@param   
@return  
@note     
@warning 
@retval buffer 
*/
lua_State *	CLuaEngine::GetLuaState(void)
{
	return m_pLuaState;
}

/** ִ��һ��lua�ű�
@param   
@param   
@param   
@return  
@note     
@warning 
@retval buffer 
*/
bool CLuaEngine::LoadLuaFile(LPCSTR szLuaFileName)
{
	if(szLuaFileName == NULL)
	{
		return false;
	}

	if(m_bFromPackLoadLua)
	{
		FileSystem * pFileSystem = getFileSystem();
		if(pFileSystem == NULL)
		{
			return false;
		}

		Stream * pStream = pFileSystem->open(szLuaFileName);
		if(pStream == NULL)
		{
			return false;
		}
		
		uint nLength = pStream->getLength();
		if(nLength > 0)
		{
			// ���ļ������ڴ�
			char * pData = new char[nLength + 1]; pData[nLength] = 0;
			pStream->read(pData, nLength);
			pStream->close();
			pStream->release();

			// �ܹ��ڴ�����ļ�			
			int top = lua_gettop(m_pLuaState);
			int nResult = luaL_loadbuffer(m_pLuaState, pData, nLength, pData);
			if(nResult == 0)
			{
				nResult = lua_pcall(m_pLuaState, 0, 0, 0);
				if(nResult == 0)
				{
					lua_settop(m_pLuaState, top);

					delete []pData;

					return true;
				}
			}

			delete []pData;

			LPCSTR pszErrInfor = lua_tostring(m_pLuaState, -1);
			Error("[LuaEngine] ����" << szLuaFileName << "�ļ�ʧ�ܣ�ʧ��ԭ��" << pszErrInfor << endl);

			lua_settop(m_pLuaState, top);

			return false;			
		}

		return true;
	}
	else
	{
		int top = lua_gettop(m_pLuaState);
		try
		{		
			int nResult = luaL_loadfile(m_pLuaState, szLuaFileName);
			if(nResult == 0)
			{
				nResult = lua_pcall(m_pLuaState, 0, 0, 0);
				if(nResult == 0)
				{
					lua_settop(m_pLuaState, top);

					return true;
				}
			}
		}
		catch (...)
		{

		}

		LPCSTR pszErrInfor = lua_tostring(m_pLuaState, -1);
		Error("[LuaEngine] ����" << szLuaFileName << "�ļ�ʧ�ܣ�ʧ��ԭ��" << pszErrInfor << endl);

		lua_settop(m_pLuaState, top);

		return false;
	}

	return false;
}

/** ִ��һ���ڴ���lua
@param   pLuaData : �����lua ����
@param   nDataLen �����ݳ���
@param   
@return  
@note     
@warning 
@retval buffer 
*/
bool CLuaEngine::RunMemoryLua(LPCSTR pLuaData, int nDataLen)
{
	if(pLuaData == NULL || nDataLen <= 0)
	{
		return false;
	}

	// �ܹ��ڴ�����ļ�			
	int top = lua_gettop(m_pLuaState);
	int nResult = luaL_loadbuffer(m_pLuaState, pLuaData, nDataLen, pLuaData);
	if(nResult == 0)
	{
		nResult = lua_pcall(m_pLuaState, 0, 0, 0);
		if(nResult == 0)
		{
			lua_settop(m_pLuaState, top);

			return true;
		}
	}

	LPCSTR pszErrInfor = lua_tostring(m_pLuaState, -1);
	Error("[LuaEngine] ִ���ڴ�luaʧ�ܣ�ʧ��ԭ��" << pszErrInfor << endl);

	lua_settop(m_pLuaState, top);			

	return false;
}

/** ִ��һ��lua����
@param   szFuncName : lua������
@param   pInParam : �����������ָ��
@param   nInNum : �����������
@param   pOutParam : �����������ָ��
@param   nOutNum : �����������
@return  
@note     
@warning 
@retval buffer 
*/
bool CLuaEngine::RunLuaFunction(LPCSTR szFunName, CLuaParam * pInParam, int nInNum, CLuaParam * pOutParam, int nOutNum)
{
	int top = lua_gettop(m_pLuaState);

	try
	{
		lua_getglobal(m_pLuaState, szFunName);

		if(!lua_isfunction(m_pLuaState, -1))
		{
			Error("[LuaEngine] ����" << szFunName << "����ʧ�ܣ��Ҳ����˺�����" << endl);

			lua_settop(m_pLuaState, top);

			return false;
		}

		for(int i = 0; i < nInNum; i++)
		{
			switch(pInParam[i].GetDataType())
			{
			case PARAM_DATATYPE_NUMBER:
				{
					lua_pushnumber(m_pLuaState, (int)pInParam[i]);
				}			
				break;			
			case PARAM_DATATYPE_STRING:
				{
					lua_pushstring(m_pLuaState, (LPCSTR)pInParam[i]);
				}			
				break;
			case PARAM_DATATYPE_LIGHTUSERDATA:
				{
					lua_pushlightuserdata(m_pLuaState, (void *)pInParam[i]);
				}
				break;
			default:
				{
					Error("[LuaEngine] ����" << szFunName << "����ʧ�ܣ�����������ʹ���" << endl);

					lua_settop(m_pLuaState, top);

					return false;
				}
			}
		}

		// ����ִ��
		int nResult = lua_pcall(m_pLuaState, nInNum, nOutNum, 0);
		if(nResult == 0)
		{
			for(int n = 0; n < nOutNum; n++)
			{
				int nType = lua_type(m_pLuaState, -1);
				switch(nType)
				{
				case PARAM_DATATYPE_NUMBER:
					{
						pOutParam[n] = (int)lua_tonumber(m_pLuaState, -1);

						lua_pop(m_pLuaState, 1);
					}
					break;
				case PARAM_DATATYPE_STRING:
					{
						pOutParam[n] = (LPCSTR)lua_tostring(m_pLuaState, -1);

						lua_pop(m_pLuaState, 1);
					}
					break;
				case PARAM_DATATYPE_LIGHTUSERDATA:
					{
						pOutParam[n] = (LPCSTR)lua_topointer(m_pLuaState, -1);

						lua_pop(m_pLuaState, 1);
					}
					break;
				default:
					{
						Error("[LuaEngine] ����" << szFunName << "����ʧ�ܣ�����������ʹ���" << endl);

						lua_settop(m_pLuaState, top);

						return false;
					}
				}
			}

			lua_settop(m_pLuaState, top);

			return true;
		}
	}
	catch (...)
	{

	}

	LPCSTR pszErrInfor = lua_tostring(m_pLuaState, -1);
	Error("[LuaEngine] ����" << szFunName << "����ʧ�ܣ�ʧ��ԭ��" << pszErrInfor << endl);

	lua_settop(m_pLuaState, top);

	return false;
}

/** ȡ��������͵�lua����
@param
@param
@param 
@return  ��������
@note     
@warning 
@retval buffer 
*/
LPCSTR CLuaEngine::GetLastError(void)
{
	return lua_tostring(m_pLuaState, -1);
}

/** ����Lua���棬�����¼������нű�
@param
@param
@param 
@return  
@note     
@warning 
@retval buffer 
*/
bool CLuaEngine::Reset(void)
{
	assert (m_pLuaState);
	if(m_pLuaState == NULL)
	{
		return false;
	}
	lua_close(m_pLuaState);
	return this->Create(m_bFromPackLoadLua);
}

/** �������
@param   
@param   
@return  
*/
API_EXPORT ILuaEngine * LoadLEM(bool bFromPackLoadLua)
{
	// ��������ˣ���ֱ�ӷ���
	if(g_pLuaEngine != NULL)
	{
		return g_pLuaEngine;
	}

	// ʵ����
	g_pLuaEngine = new CLuaEngine();
	if(!g_pLuaEngine)
	{
		return NULL;
	}

	// ��ʼ�����ݿ����������
	if(!g_pLuaEngine->Create(bFromPackLoadLua))
	{
		SAFE_DELETE(g_pLuaEngine);
		return NULL;
	}	

	return g_pLuaEngine;
}