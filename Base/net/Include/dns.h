/*******************************************************************
** �ļ���:	dns.h 
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

#ifndef __ASYN_DNS_H__
#define __ASYN_DNS_H__

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
	/**
	@name : DNS��ѯ�� (����������ѯ����Ķ���)
	@brief: ��������ѯ�ɹ������ýӿ�֪ͨ������Ӧ��IP��ַ
	*/
	struct DNS_Queryer
	{
		/**
		@name         : ��ѯ�����ɹ�
		@brief        : 
		@param domain : Ҫ��ѯ������
		@param ipset  : ��Ӧ��ip�б�,����������Ӧ�Ķ��ip
		@return       :
		*/
		virtual void Handle_DNS_Response( const char * szDomain,const char ** ppIPList,unsigned int nIPNum) = 0;

		/**
		@name         : ��ѯ����ʧ��
		@brief        : 
		@param domain : Ҫ��ѯ������
		@param dwError: ������,��������������
		@return       :
		*/
		virtual void Handle_DNS_Error( const char * szDomain,DWORD dwErrorCode ) = 0;
	};


	/**
	@name         : ��ѯһ������
	@brief        :
	@param domain : ����ѯ������
	@param queryer: ��ѯ��,���ڲ�ѯ�ɹ����֪ͨ
	@note         : �ڲ�ѯ�����и�ָ����뱣����Ч,�����ָ�뱻�ͷ�,��Ҫ��������Cancel_DNS_Queryȡ����ѯ
	@return       :
	*/
	NET_API bool DNS_Query( const char * domain,DNS_Queryer * queryer );

	/**
	@name         : ȡ��һ��������ѯ����
	@brief        :
	@param domain : ����ѯ������
	@param queryer: ��ѯ��,���ڲ�ѯ�ɹ����֪ͨ
	@return       :
	*/
	NET_API bool Cancel_DNS_Query( const char * domain,DNS_Queryer * queryer );
};

#endif//__ASYN_DNS_H__