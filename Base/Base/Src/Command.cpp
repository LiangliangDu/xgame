/*******************************************************************
** �ļ���:	Command.cpp 
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
#include "Command.h"

#define new RKT_NEW

using namespace xs;

bool Command::DeclareStrParam(const std::string & key,const std::string & defval,bool bOption,const std::string & desc,const std::string & detail)
{
	Parameter param(defval);
	param.m_IsOption = bOption;
	param.m_Desc = desc;
	param.m_Detail = detail;

	std::string name = key;

	if ( key.empty() )
	{
		char unnamed[64];
		sprintf(unnamed,"unnamed%d",m_nUnnamedParamNum++);
		name = unnamed;
	}

	PARAM_TABLE::value_type val(name,param);
	m_Params.insert(val);
	return true;
}

bool Command::DeclareIntParam(const std::string & key,int defval,bool bOption,const std::string & desc,const std::string & detail)
{
	Parameter param(defval);
	param.m_IsOption = bOption;
	param.m_Desc = desc;
	param.m_Detail = detail;
	
	std::string name = key;

	if ( key.empty() )
	{
		char unnamed[64];
		sprintf(unnamed,"unnamed%d",m_nUnnamedParamNum++);
		name = unnamed;
	}

	PARAM_TABLE::value_type val(name,param);
	m_Params.insert(val);
	return true;	
}

bool Command::GetIntParam(const std::string & key,int & value)
{
	PARAM_TABLE::iterator it = m_Params.find(key);
	if ( it==m_Params.end())
		return false;
	Parameter & param = it->second;
	if ( param.m_Type!=Parameter::enType_Int)
		return false;
	value = param.m_nValue;
	return true;
}

bool Command::GetStrParam(const std::string & key,std::string & value)
{
	PARAM_TABLE::iterator it = m_Params.find(key);
	if ( it==m_Params.end())
		return false;
	Parameter & param = it->second;
	if ( param.m_Type!=Parameter::enType_String)
		return false;
	value = param.m_strValue;
	return true;
}

bool Command::IsOptionOpen(const std::string & key)
{
	PARAM_TABLE::iterator it = m_Params.find(key);
	if ( it==m_Params.end())
		return false;
	Parameter & param = it->second;
	if ( param.m_Type!=Parameter::enType_Nil)
		return false;
	return param.m_Selected;
}

const std::string & Command::GetCommandName()
{
	return m_Name;
}


/**
@name         : ȡ�ø�����ĸ�ʽ�ִ�
@brief        : ����: NETSTAT [-a] [-b] [-e] [-p protocol] [interval]
@note         : ������ʽԼ��:
@note         : 1.[]��Ϊ��ѡ����,()����Ϊ�������
@note         : 2.������û��ֵ   ex. [-a]
@note         : 3.��������ֵ     ex. [-p protocol]
@note         : 4.û������ֵ     ex. [interval]
*/
const std::string & Command::GetCommandFormat()
{
	if ( !m_Format.empty() )
		return m_Format;

	m_Format = m_Name;
	m_Format +=" ";

	PARAM_TABLE::iterator it = m_Params.begin();
	for ( ;it!=m_Params.end();++it )
	{
		Parameter & param = it->second;
		const std::string & name= it->first;

		m_Format += param.m_IsOption ? "[" : "(";
		if ( name.find("unnamed")!=0 )
		{
			m_Format += "-";
			m_Format += name;
			m_Format += " ";
		}

		if ( param.m_Type!=Parameter::enType_Nil)
		{
			m_Format += param.m_Desc;
		}

		m_Format += param.m_IsOption ? "] " : ") ";
	}

	return m_Format;
}

const std::string & Command::GetCommandDesc()
{
	return m_Desc;
}

/**
@name         : ȡ�ø�����������ִ�
@brief        : �����������ڵ���ϸ����
@note         : ϸ�������ĸ�ʽ:
@note         : �������� + ����
@note         : ������ʽ + ����
@note         : ������   + �������� + ����
*/
const std::string & Command::GetCommandDescDetail()
{
	if ( !m_Detail.empty() )
		return m_Detail;

	m_Detail = m_Desc;
    m_Detail +="\r\n";
	m_Detail +="\r\n";
	m_Detail +=GetCommandFormat();
	m_Detail +="\r\n";
	m_Detail +="\r\n";

	PARAM_TABLE::iterator it = m_Params.begin();
	for ( ;it!=m_Params.end();++it )
	{
		Parameter & param = it->second;
		const std::string & name= it->first;

		m_Detail += "-";
		m_Detail += name.find("unnamed")==0 ? param.m_Desc : name;
		m_Detail += param.m_IsOption ? "(��ѡ)" : "(����)";
		m_Detail += "		";
		m_Detail += param.m_Detail;
		m_Detail += "\r\n";
	}

	return m_Detail;
}

bool Command::GetNextSegment(const char * cmd,int & begin_segment,int & segment_len)
{
	begin_segment = -1;
	segment_len = 0;

	for(int i=0;cmd[i]!=0 && cmd[i]!='\r' && cmd[i]!='\n';++i)
	{
		if ( cmd[i]!=' ' && cmd[i]!='	')
		{
			if(segment_len==0)
			{
				begin_segment = i;
				segment_len = 1;
			}else
			{
				++segment_len;
			}
		}else
		{
			if ( segment_len>0 )
			{
				break;
			}
		}
	}

	return segment_len>0;
}

bool Command::Parse( const std::string & cmd_str )
{
	int begin_segment = 0;
	int segment_len = 0;

	const char * cmd = cmd_str.c_str(); 
	Parameter * pPendingParam = 0;
	int unnamed_index = 0;

	while( GetNextSegment(cmd,begin_segment,segment_len) )
	{
		// ��һ��������,����
		if ( cmd==cmd_str.c_str() )
		{
			if ( memcmp(cmd+begin_segment,m_Name.c_str(),m_Name.length())!=0 )
				return false;

			cmd += begin_segment+segment_len;
			continue;
		}

		// �ֽ������
		if ( pPendingParam==0 )
		{
			if ( cmd[begin_segment]=='-')
			{
				if ( segment_len<=1 )
				{
					m_Output = "Invalid parameter in ^";
					m_Output += cmd+begin_segment;
					return false;
				}

				std::string param_name(cmd+begin_segment+1,segment_len-1);
				PARAM_TABLE::iterator it = m_Params.find(param_name);
				if ( it==m_Params.end())
				{
					m_Output = "Invalid parameter in ^";
					m_Output += cmd+begin_segment;
					return false;
				}

				Parameter & param = it->second;
				param.m_Selected  = true;
				if ( param.m_Type!=Parameter::enType_Nil)
				{
					pPendingParam = &param;
					cmd += begin_segment+segment_len;
					continue;
				}
			}else
			{
				char param_name[64];
				sprintf(param_name,"unnamed%d",unnamed_index++);
				PARAM_TABLE::iterator it = m_Params.find(param_name);
				if ( it==m_Params.end())
				{
					m_Output = "Invalid parameter in ^";
					m_Output += cmd+begin_segment;
					return false;
				}

				Parameter & param = it->second;
				param.m_Selected = true;
				if ( param.m_Type==Parameter::enType_Nil)
				{
					m_Output = "Invalid parameter in ^";
					m_Output += cmd+begin_segment;
					return false;
				}
				pPendingParam = &param;
			}
		}

		// �ֽ����ֵ
		if ( pPendingParam)
		{
			if ( cmd[begin_segment]=='-')
			{
				m_Output = "Invalid parameter in ^";
				m_Output += cmd+begin_segment;
				return false;
			}

			if ( pPendingParam->m_Type==Parameter::enType_Int)
			{
				sscanf(cmd+begin_segment,"%d",&pPendingParam->m_nValue);
				pPendingParam = 0;
			}else if( pPendingParam->m_Type==Parameter::enType_String)
			{
				pPendingParam->m_strValue.assign(cmd+begin_segment,segment_len);
				pPendingParam = 0;
			}else
			{
				m_Output = "Invalid parameter in ^";
				m_Output += cmd+begin_segment;
				return false;
			}
		}

		cmd += begin_segment+segment_len;
	}

	// ���ȱ�ٱ���Ĳ���
	PARAM_TABLE::iterator it = m_Params.begin();
	for ( ;it!=m_Params.end();++it )
	{
		if ( it->second.m_IsOption==false && it->second.m_Selected==false )
		{
			m_Output = "Parameter not enough!";
			return false;
		}
	}

	return true;
}

bool Command::Execute()
{
	m_Output = "Executed an unimplemented command!";
	return false;
}

const std::string & Command::GetError() const
{
	return m_Output;
}