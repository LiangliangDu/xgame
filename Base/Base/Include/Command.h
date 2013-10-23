/*******************************************************************
** �ļ���:	Command.h 
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

#ifndef __GATEWAY_COMMAND_H__
#define __GATEWAY_COMMAND_H__

#include <string>
#include <map>

#include "Common.h"
#include "ICommand.h"

namespace xs
{

	/**
	@name : �����������
	@brief: Ŀǰֻ֧�����ͺ��ַ�������
	*/
	class RKT_EXPORT Parameter
	{
	public:
		enum TYPE
		{
			enType_Nil  = 0,
			enType_Int     ,
			enType_String  ,
		};
		
		std::string       m_strValue; // �ִ�����ֵ
		int               m_nValue;   // ���Ͳ���ֵ

		TYPE              m_Type;     // ��������
		std::string       m_Desc;     // ��������
		std::string       m_Detail;   // ��ϸ����
		bool              m_IsOption; // �Ƿ��ѡ
		bool              m_Selected; // �Ƿ�ѡ�����������

		Parameter() : m_Type(enType_Nil),m_IsOption(true),m_Selected(false){}

		Parameter(const int & val) : m_Type(enType_Int),m_nValue(val),m_IsOption(true),m_Selected(false){}

		Parameter(const std::string & val) : m_Type(enType_String),m_strValue(val),m_IsOption(true),m_Selected(false){}
	};

	/**
	@name : �������
	@brief: ʵ��������������/����/ִ��
	*/
	class RKT_EXPORT Command : public ICommand
	{
	public:
		/**
		@name         : ȡ����������
		*/
		virtual const std::string & GetCommandName();

		/**
		@name         : ȡ�ø�����ĸ�ʽ�ִ�
		@brief        : ����: NETSTAT [-a] [-b] [-e] [-p protocol] [interval]
		@note         : ������ʽԼ��:
		@note         : 1.[]��Ϊ��ѡ����,()����Ϊ�������
		@note         : 2.������û��ֵ   ex. [-a]
		@note         : 3.��������ֵ     ex. [-p protocol]
		@note         : 4.û������ֵ     ex. [interval]
		*/
		virtual const std::string & GetCommandFormat();

		/**
		@name         : ȡ�ø�����ܵļ�����
		@brief        : 
		*/
		virtual const std::string & GetCommandDesc();

		/**
		@name         : ȡ�ø�����������ִ�
		@brief        : �����������ڵ���ϸ����
		@note         : ϸ�������ĸ�ʽ:
		@note         : �������� + ����
		@note         : ������ʽ + ����
		@note         : ������   + �������� + ����
		*/
		virtual const std::string & GetCommandDescDetail();

		/**
		@name         : ��������������н����������
		@param cmd_str: �������ִ�
		@return       : �����ʽ�����򷵻�false
		*/
		virtual bool Parse( const std::string & cmd_str );

		/**
		@name         : ִ������
		@return       : ����ִ�гɹ��򷵻�true,����ʹ��GetError���ش�����ʾ
		*/
		virtual bool Execute();

		/**
		@name         : ȡ�ô�����ʾ
		@brief        : ���û����������ִ��ǿ�
		*/
		virtual const std::string & GetError() const;

		virtual void Release() { delete this; }

		virtual Command * Clone() = 0;

		Command(const std::string & name,const std::string & desc) : m_Name(name),m_Desc(desc),m_nUnnamedParamNum(0){}

	protected:
		/**
		@name         : ����������һ���ִ�����
		@brief        : 
		@param   key  : ������ֵ,��[-a] [-b]�е�a��b,���key������Ϊ[interval]��ʽ
		@param defval : Ĭ����ֵ
		@param bOption: �Ƿ��ǿ�ѡ����
		@param desc   : �ò�������������[interval]�е�interval
		@param detail : �ò�������ϸ˵��
		@return       :
		*/
		bool DeclareStrParam(const std::string & key,const std::string & defval,bool bOption,const std::string & desc,const std::string & detail);

		/**
		@name         : ����������һ�����β���
		@brief        : 
		@param   key  : ������ֵ,��[-a] [-b]�е�a��b,���key������Ϊ[interval]��ʽ
		@param defval : Ĭ����ֵ
		@param bOption: �Ƿ��ǿ�ѡ����
		@param desc   : �ò�������������[interval]�е�interval
		@param detail : �ò�������ϸ˵��
		@return       :
		*/
		bool DeclareIntParam(const std::string & key,int defval,bool bOption,const std::string & desc,const std::string & detail);

		bool GetIntParam(const std::string & key,int & value);

		bool GetStrParam(const std::string & key,std::string & value);

		bool IsOptionOpen(const std::string & key);

		bool GetNextSegment(const char * cmd,int & begin_segment,int & segment_len);

		Command(){}

	protected:
		typedef std::map<std::string,Parameter>   PARAM_TABLE;
		PARAM_TABLE     m_Params;    // �����б�
		std::string     m_Name;      // ��������
		std::string     m_Output;    // ������ʾ
		std::string     m_Format;    // �����ʽ
		std::string     m_Desc;      // �������ܼ�����
		std::string     m_Detail;    // ����������Ϣ���ڵ���ϸ����
		int             m_nUnnamedParamNum; // ������������
	};
};

#endif//__GATEWAY_COMMAND_H__