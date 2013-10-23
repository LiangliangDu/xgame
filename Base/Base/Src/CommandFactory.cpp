/*******************************************************************
** �ļ���:	CommandFactory.cpp 
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

#include "stdafx.h"
#include "CommandFactory.h"

#define new RKT_NEW

using namespace xs;

CommandFactory::CommandFactory()
{
	RegisterCommand(new Command_Help);
}

CommandFactory::~CommandFactory()
{
	COMMAND_MAP::iterator it = m_CommandList.begin();
	for ( ;it!=m_CommandList.end();++it )
	{
		ICommand * cmd = it->second;
		cmd->Release();
	}
}

void CommandFactory::RegisterCommand(ICommand * cmd)
{
	m_CommandList[cmd->GetCommandName()] = cmd;
}

ICommand * CommandFactory::CreateCommand(const char * cmd )
{
	std::string cmd_line = cmd;
	std::string cmd_name;

	size_t pos = cmd_line.find(' ');
	if ( pos<cmd_line.length())
		cmd_name = cmd_line.substr(0,pos);
	else
		cmd_name = cmd_line;

	COMMAND_MAP::iterator it = m_CommandList.find(cmd_name);
	if ( it==m_CommandList.end())
		return 0;

	return it->second->Clone();
}

//////////////////////////////////////////////////////////////////////////
Command_Help::Command_Help() : Command("help","��������")
{
	DeclareStrParam("","",true,"cmd","��������.");
}

bool Command_Help::Execute()
{
	std::string cmd_name;

	GetStrParam("unnamed0",cmd_name);

	if ( cmd_name.empty() )
	{
		CommandFactory::COMMAND_MAP::iterator it= CommandFactory::getInstance().GetCommandList().begin();
		for ( ;it!=CommandFactory::getInstance().GetCommandList().end();++it )
		{
			Command * pCmd = (Command*)it->second;
			m_Output += pCmd->GetCommandName();
			m_Output += "		";
			m_Output += pCmd->GetCommandDesc();
			m_Output += "\r\n";
		}
		return true;
	}else
	{
		CommandFactory::COMMAND_MAP::iterator it= CommandFactory::getInstance().GetCommandList().find(cmd_name.c_str());
		if ( it==CommandFactory::getInstance().GetCommandList().end() )
		{
			m_Output = "The command not exist!";
			return false;
		}

		Command * pCmd = (Command*)it->second;
		m_Output = pCmd->GetCommandDescDetail();
		return true;
	}
}

API_EXPORT ICommandFactory * RKT_CDECL GetCommandFactory()
{
	return &CommandFactory::getInstance();
}