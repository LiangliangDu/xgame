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
#pragma once

#include "ILuaEngine.h"

class CLuaEngine : public ILuaEngine
{
public:
	///////////////////////////////////////////////////////////////////
	/** �ͷ�
	@param   
	@param   
	@param   
	@return  
	@note     �ͷ�������Դ���������ٴ˶���
	@warning 
	@retval buffer 
	*/
	virtual void			Release(void);

	/** ȡ��lua_State *
	@param   
	@param   
	@param   
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual lua_State *		GetLuaState(void);

	/** ִ��һ��lua�ű�
	@param   
	@param   
	@param   
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool			LoadLuaFile(LPCSTR szLuaFileName);

	/** ִ��һ���ڴ���lua
	@param   pLuaData : �����lua ����
	@param   nDataLen �����ݳ���
	@param   
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool			RunMemoryLua(LPCSTR pLuaData, int nDataLen);

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
	virtual bool			RunLuaFunction(LPCSTR szFunName, CLuaParam * pInParam = NULL, int nInNum = 0, CLuaParam * pOutParam = NULL, int nOutNum = 0);

	/** ȡ��������͵�lua����
	@param
	@param
	@param 
	@return  ��������
	@note     
	@warning 
	@retval buffer 
	*/
	virtual LPCSTR			GetLastError(void);

	/** ����Lua���棬�����¼������нű�
	@param
	@param
	@param 
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual bool			Reset(void);

	//////////////////////CLuaEngine///////////////////////////////////
	/** ����
	@param   bFromPackLoadLua : �Ƿ�Ҫ���ļ���������lua�ļ�,�������������lua������Ϳ������־Ϊflase
	@param   
	@return  
	*/
	bool					Create(bool bFromPackLoadLua);

	/** ����
	@param   
	@param   
	@return  
	*/
	CLuaEngine(void);

	/** ����
	@param   
	@param   
	@return  
	*/
	virtual ~CLuaEngine(void);

private:
	// lua��׼
	lua_State *				m_pLuaState;

	// �Ƿ�Ӱ�������lua
	bool					m_bFromPackLoadLua;
};
extern CLuaEngine *			g_pLuaEngine;