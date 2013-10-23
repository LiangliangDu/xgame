/*******************************************************************
** �ļ���:	AsynIoDevice.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/23/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  �첽IO�豸�ӿ�

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __ASYN_IO_DEVICE_H__
#define __ASYN_IO_DEVICE_H__

namespace xs{
	struct AsynIoResult;
	struct AsynIoHandler;

	struct AsynIoOperation_Reader;   // �첽IO��
	struct AsynIoOperation_Writer;   // �첽IOд
	struct AsynIoOperation_Acceptor; // �첽����
	struct AsynIoOperation_Connector;// �첽����

	/**
	@name : �첽IO�豸
	@brief: ֧���첽IO������ʵ����ͨ�����ļ�����Socket
	*/
	struct AsynIoDevice
	{
		/**
		@purpose  : ȡ���豸���
		@return	  :
		*/
		virtual HANDLE GetHandle() const = 0;

		/**
		@purpose  : ȡ�ö�ȡ��������豸��֧�ָò����򷵻�NULL
		@return	  :
		*/
		virtual AsynIoOperation_Reader * Reader() = 0;

		/**
		@purpose  : ȡ��д����������豸��֧�ָò����򷵻�NULL
		@return	  :
		*/
		virtual AsynIoOperation_Writer * Writer() = 0;

		/**
		@purpose  : ȡ�ý�����������豸��֧�ָò����򷵻�NULL
		@return	  :
		*/
		virtual AsynIoOperation_Acceptor * Acceptor() = 0;

		/**
		@purpose  : ȡ��������������豸��֧�ָò����򷵻�NULL
		@return	  :
		*/
		virtual AsynIoOperation_Connector * Connector() = 0;

		/**
		@purpose      : ����һ����ɶ���
		@param iotype : IO��������
		@param handler: ����¼��������
		@note         : ���豸������ɶ���Ŀ�����:
					  : 1.��ͬ�豸����ɶ���ʵ�ֿ������в�ͬ
					  : 2.�豸����ʱӦ���ͷ�����δ��ɵ�Result����,�����ڴ�й¶
		@note         : ��Ϊ�����ڶ���̵߳���,��������ڲ��Ѿ������߳�ͬ��
		@return		  : ��ɶ���ָ��
		*/
		virtual AsynIoResult * CreateAsynIoResult(int iotype=0,AsynIoHandler * handler=0) = 0;
		
		/**
		@purpose      : ɾ��һ����ɶ���
		@param	result: �������ָ��
		@note         : ��Ϊ�����ڶ���̵߳���,��������ڲ��Ѿ������߳�ͬ��
		@return		  :
		*/
		virtual void DeleteAsynIoResult(AsynIoResult * result) = 0;

		/**
		@purpose  : �����첽IO�豸
		@return	  :
		*/
		virtual void Release() = 0;
	};
};

#endif//__ASYN_IO_DEVICE_H__