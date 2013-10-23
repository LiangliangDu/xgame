/*******************************************************************
** �ļ���:	AsynIoOperation.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/23/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  ���弸�ֳ��õ��첽IO����	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __ASYN_IO_OPERATION_H__
#define __ASYN_IO_OPERATION_H__

namespace xs{

	struct AsynIoHandler;// ����ӿ�,��AsynIoFrame.h
	struct AsynIoBuffer; // �������ṹ,��AsynIoFrame.h
	
	/// �첽��
	struct AsynIoOperation_Reader
	{
		/**
		@purpose  : ����һ��������
		@param expect_bytes : ������ȡ���ֽ��� 
		@param handler      : ������ɺ�Ĵ�����  
		@note     : �ú�����������,��ȡ�Ľ��ͨ��AsynIoResult����
		@note     : ����ڶ��Ĺ����з����������׳��쳣
		*/
		virtual bool read(DWORD expect_bytes,AsynIoHandler * handler) = 0;
	};

	/// �첽д
	struct AsynIoOperation_Writer
	{
		/**
		@purpose    : ����һ��д����
		@param data : ��Ҫд������ݵ�ַ(����ڴ���Է�����ջ��,�ڲ�ʵ��ʱ�´��һ���ڴ�)
		@param len  : ��Ҫд����ֽ���
		@param handler: ������ɺ�Ĵ�����  
		@note       : �ú�����������,��ȡ�Ľ��ͨ��AsynIoResult����
		@note       : �����д�Ĺ����з����������׳��쳣
		@warning    : UDP���豸��Ϊ��������ʱ��Ҫָ���Է��ĵ�ַ����ʵ�ֱȽ�����,Ĭ�ϵ�ַ(sockaddr_in)���ڻ���������ǰ��
		*/
		virtual bool write(const char * data,DWORD len,AsynIoHandler * handler) = 0;

		/**
		@name             : ����д��(�ۼ�IO)
		@brief            : ��Ҫ��Ϊ����������,�ر��Ǵ����ʱ����Լ���һ���ڴ濽��
		@warning          : ע��:pBuffListָ����ڴ��������AllocAsynIoBuff()�����,���治���ٿ�����
		@param pBuffList  : �������б�
		@param dwBuffCount: ����������
		@param handler    : ������ɺ�Ĵ�����  
		@note             : �ú�����������,��ȡ�Ľ��ͨ��AsynIoResult����
		@note             : �����д�Ĺ����з����������׳��쳣
		@warning          : UDP���豸��Ϊ��������ʱ��Ҫָ���Է��ĵ�ַ����ʵ�ֱȽ�����,Ĭ�ϵ�һ��Buff�����ŵ�ַ(sockaddr_in)
		*/
		virtual bool writeEx( AsynIoBuffer * pBuffList,DWORD dwBuffCount,AsynIoHandler * handler) = 0;
	};

	/// ������
	struct AsynIoOperation_Acceptor
	{
		/**
		@purpose    : �����յ�������
		@param handler: ������ɺ�Ĵ����� 
		@note       : �ú�����������,��ȡ�Ľ��ͨ��AsynIoResult����
		@note       : �����д�Ĺ����з����������׳��쳣
		*/
		virtual bool accept(AsynIoHandler * handler) = 0;
	};

	/// ������
	struct AsynIoOperation_Connector
	{
		/**
		@purpose    : ��Զ��������������
		@param addr : Զ��������ַ
		@param handler: ������ɺ�Ĵ����� 
		@note       : �ú�����������,��ȡ�Ľ��ͨ��AsynIoResult����
		@note       : �����д�Ĺ����з����������׳��쳣
		*/
		virtual bool connect( sockaddr_in * addr,AsynIoHandler * handler ) = 0;
	};
};

#endif//__ASYN_IO_OPERATION_H__