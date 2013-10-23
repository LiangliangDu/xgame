/*******************************************************************
** �ļ���:	ICommand.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	02/21/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __INTERFACE_COMMAND_H__
#define __INTERFACE_COMMAND_H__

#include <string>

namespace xs
{
	/**
	@name : ����ӿ�
	@brief:
	*/
	struct ICommand
	{
		/**
		@name         : ȡ����������
		*/
		virtual const std::string & GetCommandName() = 0;

		/**
		@name         : ��������������н����������
		@param cmd_str: �������ִ�
		@return       : �����ʽ�����򷵻�false
		*/
		virtual bool Parse( const std::string & cmd_str ) = 0;

		/**
		@name         : ִ������
		@return       : ����ִ�гɹ��򷵻�true,����ʹ��GetError���ش�����ʾ
		*/
		virtual bool Execute() = 0;

		/**
		@name         : ȡ�ô�����ʾ
		@brief        : 
		*/
		virtual const std::string & GetError() const = 0;

		/**
		@name         : �ӵ�ǰ��ģ���¡һ����ͬ���������
		@brief        :
		*/
		virtual ICommand * Clone() = 0;

		/**
		@name         : �����������
		@brief        :
		*/
		virtual void Release() = 0;
	};

	/**
	@name : �����
	@brief:
	*/
	struct ICommandFactory
	{
		/**
		@name              : ע��һ������
		@brief             :
		@param pCmdTemplate: �������ģ�����,�Ժ�ͨ�����ģ�洴��������,�����˳�ʱ������Release�������
		@return            :
		*/
		virtual void RegisterCommand(ICommand * pCmdTemplate) = 0;

		/**
		@name         : ���������������,����һ��ִ�и������������
		@brief        : ���û����������򷵻�0
		@param cmd_line: ���������
		@return       : �������
		*/
		virtual ICommand * CreateCommand( const char * cmd_line ) = 0;
	};

};

/**
@name         : ��������ʵ��
@brief        :
*/
//COMMAND_API ICommandFactory * GetCommandFactory();

/// ��̬��汾
#if defined(_LIB) || defined(BASE_STATIC_LIB)
#	pragma comment(lib, MAKE_LIB_NAME(xs_com))
extern "C" xs::ICommandFactory * GetCommandFactory();
#	define	GetCommandFactoryProc	GetCommandFactory
#else 
/// ��̬��汾
typedef xs::ICommandFactory* (RKT_CDECL *procGetCommandFactory)();
#	define	GetCommandFactoryProc	DllApi<procGetCommandFactory>::load(MAKE_DLL_NAME(xs_com), "GetCommandFactory")
#endif


#endif//__INTERFACE_COMMAND_H__