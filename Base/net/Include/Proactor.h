/*******************************************************************
** �ļ���:	Proactor.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/23/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  �첽�¼��ֽ�ģ�� ��ǰ���� ��	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __PROACTOR_H__
#define __PROACTOR_H__

namespace xs{

	struct AsynIoDevice;
	struct AsynIoResult;

	/**
	@name : �첽�¼��ֽ�ģ�� ��ǰ���� ��
	@brief: ���� : �ֽ�����¼�
			ʵ�� : Win32�µ�����ɶ˿�APIʵ�� / unix������
	*/
	struct Proactor
	{
		/**
		@purpose         : ������ɶ˿�
		@param nThreadNum: ����ɶ˿��������󲢷������߳���
		@note            : �߳������ָ��Ϊ0��ϵͳ��������CPU��ͬ�������߳�
		@note            : �Ƽ����߳��� = CPU���� * 2 + 2
		@return		     : �����ɹ��򷵻�True
		*/
		virtual bool Create(unsigned long nConcurrentThreadsNum =0) = 0;

		/**
		@purpose          : �ر���ɶ˿�
		@return		      :
		*/
		virtual void Close() = 0;

		/**
		@purpose          : ע���豸(��֧���첽IO���豸����ɶ˿ڹ���)
		@param	   device : �豸ָ�� 
		@return		      : ע��ɹ��򷵻�true
		*/
		virtual bool RegisterDevice(AsynIoDevice * device) = 0;

		/**
		@purpose          : �ȴ�����¼�,���в�����������AsynIoHandler
		@param wait       : �ȴ��ĺ�����
		@note	          : ����Ϣѭ���г������øú���
		@note             : ��: Proactor proactor;
		@note             :     while(proactor.HandleEvents()) {}
		@return		      :
		*/
		virtual bool HandleEvents(unsigned long wait=INFINITE) = 0;

		/**
		@purpose          : ����¼�����ѭ��
		@note             : ��ͬ: while(proactor.HandleEvents()) {}
		@return		      :
		*/
		virtual void HandleEventsLoop() = 0;

		/**
		@purpose          : �˹�Ͷ��һ������¼�(����ģ���첽IO�Ĺ���)
		@param   result   : ��ɶ���ָ��
		@return		      : 
		*/
		virtual bool PostCompletion( AsynIoResult * result) = 0;
	};
};

#endif//__PROACTOR_H__