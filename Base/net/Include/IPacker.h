/*******************************************************************
** �ļ���:	IPacker.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/30/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __I_PACKER_H__
#define __I_PACKER_H__

#include "AsynIoFrame.h"
#include <vector>

namespace xs{

	/**
	@name            : ����㷨
	@brief           : ���û����͵����ݴ�ɰ�,�յ����ٰ����⿪.����㷨�������û��ǿ��Զ��Ƶ�
	@return       :
	*/
	struct IPacker
	{
		/**
		@name            : �������
		@brief           : ���û����͵����ݴ�ɰ�
		@param pRawData  : �û�����
		@param dwDataLen : ���ݳ���
		@param PackedData: ��ð��������
		@return          :
		*/
		virtual void Pack( const char * pRawData,DWORD dwDataLen,std::vector<AsynIoBuffer> & PackedData ) = 0;

		/**
		@name            : �������
		@brief           : ���յ��������ݽ�ɰ�
		@param pStreamData: �յ���������
		@param dwLen     : ���ݳ���
		@param UnpackedData: �������İ�����
		@return          : ������ʧ�ܷ���false
		*/
		virtual bool UnPack( const char * pStreamData,DWORD dwLen,std::vector<AsynIoBuffer> & UnpackedData ) = 0;

		/**
		@name         : ��¡һ�������
		@brief        : ����һ�����Լ�ͬ���͵Ķ���
		@return       :
		*/
		virtual IPacker * Clone() = 0;

		virtual void Release() = 0;
	};
};

#endif//__I_PACKER_H__