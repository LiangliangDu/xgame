/*******************************************************************
** �ļ���:	AsynIoFrame.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/23/2008
** ��  ��:	1.0
** ��  ��:	�첽IO���
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#ifndef __ASYN_IO_FRAME_H__
#define __ASYN_IO_FRAME_H__

// �����궨��
#ifndef NET_API
#	ifdef NET_EXPORTS
#		define NET_API		extern "C" __declspec(dllexport)
#	else
#		define NET_API		extern "C" __declspec(dllimport)
#	endif
#endif//NET_API

//////////////////////////////////////////////////////////////////////////
/********************** �첽IO������� **********************************/

/// ͨ��Ӧ�ó����ڴ���IO����ʱ���Բ������¼���ģ�ͣ�
/// 1.ͬ������ (IOģ��)
/// 2.ͬ�������� (IOģ��) + ͬ���¼���·�ֽ�(Reactor�¼�ģ��) (select/WaitForMultipleObjects)
/// 3.�첽IO (IOģ��) + �첽�¼���·�ֽ�(Proactor�¼�ģ��) (IOCP��ɶ˿�)

/// IOCPģ�͵Ļ�������:
/// 1.������ɶ˿�(Proactor)
/// 2.��IO�豸(File or Socket)
/// 3.����ɶ˿�ע��IO�豸,ʹ֮�������豸������¼�
/// 4.��IO�豸�����첽IO����,�ò������ϸ������
///     1).������ɶ���
///     2).���첽IOҪ�õ��Ļ���������Ϣ��������ɶ�����
///     3).����API,���豸�����ص�IO
/// 5.��ɶ˿ڵȴ��첽IO�������,������������������ɶ�����
/// 6.֪ͨӦ�ò�������
/// 7.������ɶ����ͷ��ڴ�

/// �������Ƿ�װһ�����ϲ���,���Proactor�ľ���ʵ�־Ϳ����γ�һ�����õ��첽IO���
/// �����ڸ���������ͨ���Լ������������ļ���д
//////////////////////////////////////////////////////////////////////////

namespace xs
{
	struct AsynIoResult;
	struct AsynIoDevice;
	struct AsynIoBuffer;
	struct Reactor;
	struct Proactor;

	/// �첽IO����
	enum AsynIoType
	{
		ASYN_IO_UNKOWN = 0,
		ASYN_IO_READ      ,
		ASYN_IO_WRITE     ,
		ASYN_IO_ACCEPT    ,
		ASYN_IO_CONNECT   ,
		ASYN_IO_READFROM  ,
		ASYN_IO_WRITETO   ,
		ASYN_IO_CLOSE     ,
	};
	
	/**
	@name : �첽IO������
	@brief: �����÷�:
	1.����һ���첽IO����ʱָ��һ���첽IO������
	2.���첽IO�������ʱ����֮ǰָ���Ĵ���������IO����
	*/
	struct AsynIoHandler
	{
		/**
		@purpose          : �첽IO���ʱ�ص��ú�����������д������룩
		@param	  result  : IO��ɶ���,����ͨ������ȡ��IO��ɵ����,�����Ƿ�ɹ�,�����˶����ֽ��Լ��ֽڵ����ݵ� 
		@return		      :
		*/
		virtual void HandleIoComplete( AsynIoResult * result ) = 0;
	};

	/**
	@name : �첽IO��ɶ���
	@brief: ����:
			1.����첽IOҪ�õ��Ļ���������Ϣ
			2.�������ʱͨ������ȡ������,�����Ƿ�ɹ�,�����˶����ֽ��Լ��ֽڵ����ݵ�
	@warning: ÿһ���첽IO��ɶ��󶼱���̳�һ���첽IO�ص��ṹ
	*/
	struct AsynIoResult : public OVERLAPPED
	{
		/**
		@purpose      : ������ɴ����� 
		@param handler: �첽IO������
		*/
		virtual void SetHandler( AsynIoHandler * handler) = 0;

		/**
		@purpose      : �������֪ͨ�¼�
		@param	event : �¼����
		@note         : �����¼�ģ��ʱ��������¼�,�������proactor����Ҫ����������
		*/
		virtual void SetEventHandle( HANDLE event ) = 0;

		/**
		@purpose      : ֪ͨ�ò������
		@note         : �ڲ�����Handler���������¼�
		*/
		virtual void Complete() = 0;

		/**
		@purpose   : ׼���첽IOҪ�õĻ�����
		@param len : ����������
		@warning   : ���֮ǰ��������PrepareBuffer׼���˻�����,���ٴε���ʱ�����ǰ�Ļ������ͷŵ������·���
		*/
		virtual void PrepareBuffer( unsigned long len ) = 0;

		/** crr add Ϊ����ʣ������׼���첽IOҪ�õĻ�����
		@purpose   : ׼���첽IOҪ�õĻ�����
		@param len : ϣ���Ļ���������
		@param pRecieved : ��һ�ν��յ������ݰ����������ѽ��յ�������
		@param dwRecievedLen : ��һ�ν��յ������ݰ����������ѽ��յ������ݳ���
		@param dwRestLen : ��һ�ν��յ������ݰ���������ʣ�µ����ݳ���
		@warning   : ���֮ǰ��������PrepareBuffer׼���˻�����,���ٴε���ʱ�����ǰ�Ļ������ͷŵ������·���
		*/
		virtual	void PrepareBuffer( unsigned long len, LPVOID pRecieved, DWORD dwRecievedLen, DWORD dwRestLen) = 0;

		//crr add����һ�ν��յ������ݰ��������������ѽ��յ������ݳ���
		virtual DWORD GetLastRecievedLen(void) const = 0;

		/**
		@brief            : ����Buff(ע��:�����ǰ�з���buff,���ﲻ������ͷŵ�)
		@param pBuffList  : �»�����ָ��
		@param dwBuffCount: ����������
		*/
		virtual void  SetBuffer(AsynIoBuffer * pBuffList,DWORD dwBuffCount) = 0;

		/**
		@purpose   : ȡ�û������б�
		@return	   : ���ػ������б�ָ��,�����ǰ��û׼���������򷵻�0
		*/
		virtual AsynIoBuffer * GetBufferList() = 0;

		/**
		@purpose   : ȡ�û���������
		@return	   : ���ػ���������,�����ǰ��û׼���������򷵻�0
		*/
		virtual DWORD GetBufferCount() const = 0;

		/**
		@purpose   : ȡ�óɹ�������ֽ���
		@return	   : ���IOû����������򷵻�0
		*/
		virtual DWORD GetTransferredBytes() const = 0;

		/**
		@purpose    :���óɹ�������ֽ���
		@param bytes:�ɹ�������ֽ���
		*/
		virtual void  SetTransferredBytes( DWORD bytes) = 0;

		/**
		@purpose    :ͨ�����ڶ��ļ�ʱ�����ļ�ƫ��ֵ
		*/
		virtual ULONG64 GetOffsetBytes() = 0;

		/**
		@purpose     :ͨ�����ڶ��ļ�ʱ�����ļ�ƫ��ֵ
		@param offset:��д�ļ�ʱ��ƫ��ֵ
		*/
		virtual void  SetOffsetBytes(ULONG64 offset) = 0;

		/**
		@purpose   : �����Ƿ�ɹ����
		@return    :
		*/
		virtual BOOL  Success() const = 0;

		/**
		@purpose   : ȡ�ô�����,��������ɹ�����򷵻�0
		@return    :
		*/
		virtual DWORD GetErrorCode() const  = 0;

		/**
		@purpose   : ���ô�����
		@err       : ������
		@return    :
		*/
		virtual void  SetErrorCode( DWORD err ) = 0;

		/**
		@purpose   : ȡ�ô���������¼����豸ָ��
		@return	   : 
		*/
		virtual AsynIoDevice * GetAsynDevice() const = 0;

		/**
		@purpose   : ���ô���������¼����豸ָ��
		@param device: �豸ָ��
		*/
		virtual void SetAsynDevice( AsynIoDevice * device) = 0;

		/**
		@purpose      : �����첽IO����
		@return		  : ���Ͷ����AsynIoOperation.h
		@note         : ���������Ҫ����Handler����ʱ������ʲô����
		*/
		virtual AsynIoType GetType() const = 0;

		/**
		@purpose      : �����첽IO����
		@param op_type: ���Ͷ����AsynIoOperation.h
		@note         : ���������Ҫ����Handler����ʱ������ʲô����
		*/
		virtual void SetType( AsynIoType op_type ) = 0;

		/**
		@name         : �ǲ���ͨ��Postģ�����ɲ���
		@brief        :
		*/
		virtual bool IsSimulation() = 0;

		virtual void SetSimulation(bool is_simulation) = 0;
	};

	/// IO������
	struct AsynIoBuffer
	{
		DWORD        len;
		char *       buf;
	};

	/// ���Buff��Ŀ
#	define	MAX_ASYN_IO_BUFF_COUNT      16

	/**
	@name             : ��ʼ���첽IO���
	@param dwThreadNum: ʹ�ö��ٸ��߳�ȥ�����첽IO
	@return		      : 1 ... OK
						-1... ��ʼ��ǰ����ʧ��
						-2... ���������̳߳�ʧ��
						-3... ��ʼ������ʧ��
	*/
	NET_API int InitializeAsynIoFrame(DWORD dwThreadNum=1);

	/**
	@name         : �ͷ��첽IO���
	@brief        : ����ڳ����˳�ʱӦ�ò㻹û�е��øú���,�첽IO��ܻ��Լ��ͷ�
	@brief        : ��������������Բ�����
	*/
	NET_API int UninitializeAsynIoFrame();

	/**
	@name         : ȡ�������첽IO��ǰ����ָ��
	@brief        : ������Щ�ط������õõ�
	*/
	NET_API Proactor * GetAsynIoProactor();

	/**
	@name         : ȡ�������첽IO�ķ�Ӧ��ָ��
	@brief        : ������Щ�ط������õõ�
	*/
	NET_API Reactor * GetAsynIoReactor();

	/**
	@name         : ����һ����Ӧ��
	@brief        : ͨ��GetAsynIoReactor��õķ�Ӧ������IO�̼߳�����,���
	              : ����Ҫ�����¼��ֲ�����IO�߳̿����Լ�����һ��Reactorȥ����
	*/
	NET_API Reactor * CreateReactor();

	/**
	@name         : ����һ���ڴ�,�����첽IO
	@brief        : Ӧ�ò���ǰ����ÿ��Լ���һ�ζ�����ڴ濽�������Ч��
	@param dwSize : ��Ҫ������ڴ��С
	@return       :
	*/
	NET_API void * AllocateAsynIoBuffer(DWORD dwSize);

	/**
	@name         : �ͷ�һ�������첽IO���ڴ�
	@brief        : Ӧ�ò���ǰ����ÿ��Լ���һ�ζ�����ڴ濽�������Ч��
	@param   buf  : ָ����Ҫ�ͷŵ��ڴ���ָ��
	@return       :
	*/
	NET_API void   DeallocateAsynIoBuffer(void * buf);
};

#endif//__ASYN_IO_FRAME_H__