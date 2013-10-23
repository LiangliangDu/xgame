/*******************************************************************
** �ļ���:	http.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	04/02/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __HTTP_H__
#define __HTTP_H__

#include <string>
#include <map>

//////////////////////////////////////////////////////////////////////////
// �����궨��
#ifndef NET_API
#	ifdef NET_EXPORTS
#		define NET_API		extern "C" __declspec(dllexport)
#	else
#		define NET_API		extern "C" __declspec(dllimport)
#	endif
#endif//NET_API

//////////////////////////////////////////////////////////////////////////

namespace xs
{
	/// Э��汾��
	enum HTTP_VERSION
	{
		HTTP_VER_1_0    = 0,  // 1.0HTTPЭ��,һ�����ӷ���һ������
		HTTP_VER_1_1       ,  // 1.1HTTPЭ��,һ�����ӿ��Է��Ͷ������
	};

	/// HTTP��Ӧͷ
	typedef std::map<std::string,std::string>   HTTP_Response_Header;

	/**
	@name : ��������HTTP����Ӧ
	@brief:
	*/
	struct HTTP_Response_Handler
	{
		/**
		@name         : ������������Ӧ
		@brief        : 
		@param pContent:���ص�����ʵ��,�Ѿ�ȥ����ͷ��Ϣ
		@param dwLen  : ���ص����ݳ���
		@param header : HTTP��Ӧͷ,��Ӧͷ����һϵ���ַ�����ֵ��,����Content-Type:text/html
		@param url    : ֮ǰ����Request������������url,�Ա�����֪������һ�����󷵻���
		@return       :
		*/
		virtual void OnResponse( const char * pContent,DWORD dwLen,const HTTP_Response_Header & header,const char * url) = 0;

		/**
		@name         : HTTP�������
		@brief        : �����Ҳ���ҳ���
		@param dwError: �����
		@param url    : ֮ǰ����Request������������url,�Ա�����֪������һ�����󷵻���
		@note         : HTTP������:
		1xx : ��Ϣ��Ӧ�࣬��ʾ���յ������Ҽ�������
		2xx : ����ɹ���Ӧ�࣬��ʾ�������ɹ����ա����ͽ���
		3xx : �ض�����Ӧ�࣬Ϊ�����ָ���Ķ�����������ܽ�һ������
		4xx : �ͻ��˴��󣬿ͻ���������﷨��������ǲ�����ȷִ��
		5xx : ����˴��󣬷�����������ȷִ��һ����ȷ������
		@return       :
		*/
		virtual void OnError(DWORD dwError,const char * url) = 0;

		/**
		@name         : ����������ҳ����ת
		@brief        : �Զ�������ת���ҳ��
		@param new_url: ��ҳ��
		@param url    : ��ҳ�棬��֮ǰ����Request������������url,�Ա�����֪������һ�����󷵻���
		@return       :
		*/
		virtual void OnLocation(const char * new_url,const char * url) = 0;
	};

	/**
	@name         : ����HTTP����
	@brief        : ʹ��GET��ʽ
	@param   url  : Ҫ�����url,������������http://www.carfax.com/register.php?username=no1
	@param httpver: Ҫʹ�õ�httpЭ��,Ŀǰ��1.0��1.1
	@param data_rng:Ҫ��������ݶ�,���Ϊ����ָ��
	@param handler: ����http��Ӧ�Ļص��ӿ�,Ϊ�˰�ȫ�����ʹ�þ��,�þ��ָ��HTTP_Response_Handler��ָ��
	@return       :
	*/
	NET_API bool HTTP_Request( const char * url,HTTP_VERSION httpver,__int64 range_begin,__int64 range_end,handle handler);
};

#endif//__HTTP_H__