/*******************************************************************
** �ļ���:	CommandFactory.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	02/18/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __COMMAND_FACTORY_H__
#define __COMMAND_FACTORY_H__

#include "Common.h"
#include "Command.h"
#include "Singleton.h"
#include <map>

namespace xs
{
	class CommandFactory : public ICommandFactory,public Singleton<CommandFactory>
	{
	public:
		typedef std::map<std::string,ICommand *> COMMAND_MAP;

		/**
		@name         : ע��һ������
		@brief        :
		@param        :
		@return       :
		*/
		virtual void RegisterCommand(ICommand * cmd);

		/**
		@name         : ��������������н��ͳ��������
		@return       : ��������ڵ�������������ʽ�����򷵻�0
		*/
		virtual ICommand * CreateCommand( const char * cmd );

		COMMAND_MAP & GetCommandList() { return m_CommandList; };

		CommandFactory();

		virtual ~CommandFactory();

	private:
		COMMAND_MAP   m_CommandList;
	};

	/**
	@name : ��ѯ��������ĸ�ʽ
	@brief: �﷨: help [command]
	*/
	class Command_Help : public Command
	{
	public:
		virtual bool Execute();

		virtual Command * Clone() { return new Command_Help; }

		Command_Help();
	};
};

#endif//__COMMAND_FACTORY_H__