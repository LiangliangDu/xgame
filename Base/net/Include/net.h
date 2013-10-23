/*******************************************************************
** �ļ���:	net.h 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	01/26/2008
** ��  ��:	1.0
** ��  ��:	����ͨѶ�ӿ�
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/


#ifndef __NET_H__
#define __NET_H__

// �����궨��
#ifndef NET_API
#	ifdef NET_EXPORTS
#		define NET_API		extern "C" __declspec(dllexport)
#	else
#		define NET_API		extern "C" __declspec(dllimport)
#	endif
#endif//NET_API

namespace xs
{
#	define MAX_NET_PACKAGE_SIZE  (1024*63)// ������ݿ��С
#	define CONN_ERROR_PACKER  -1         // ���ʧ��
#	define CONN_ERROR_DNS     -2         // ��������ʧ��

	struct IConnection;                  // TCP����
	struct IUDPSocket;                   // UDP�׽���
    struct IPacker;                      // ����ӿ�

	/**
	@name : �����¼�֪ͨ�ӿ�
	@brief: �����¼�����ʱ�ص�
	*/
	struct IConnectionEventHandler
	{
		/**
		@brief              : �յ���������
		@param pIncomingConn: �ͻ��������������
		@param ppHandler    : ��������ӵ�Handler
		@warning            : �յ����Ӻ�һ��Ҫ����Handler
		*/
		virtual void OnAccept( IConnection * pIncomingConn,IConnectionEventHandler ** ppHandler ) = 0;

		/**
		@brief      : ���ӳɹ�
		@param conn : ���Ӷ���ָ��
		*/
		virtual void OnConnected( IConnection * conn ) = 0;

		/**
		@brief      : ���ӶϿ�
		@param conn : ���Ӷ���ָ��
		@param reason:�Ͽ�ԭ��(����) 
		*/
		virtual void OnDisconnected( IConnection * conn,DWORD reason ) = 0;

		/**
		@brief        : �յ�����
		@param conn   : ���Ӷ���ָ��
		@param pData  : ���ݵ�ַ
		@pram dwDataLen:���ݳ���
		@return       :
		*/
		virtual void OnRecv( IConnection * conn,LPVOID pData,DWORD dwDataLen ) = 0;

		/**
		@name             : ��������¼�
		@brief            :
		@param conn       : ���ִ�����׽���
		@param dwErrorCode: ������
		*/
		virtual void OnError( IConnection * conn,DWORD dwErrorCode ) = 0;
	};

	/**
	@name : TCP���Ӷ���
	@brief: �ڲ���װ��һ��TCP�׽��ֶ���
	*/
	struct IConnection
	{
		/**
		@brief        : ������������
		@return       : û�д���������true,�յ����Ӻ�ص�OnAccept
		*/
		virtual bool Listen() = 0;

		/**
		@brief        : ��������Զ������
		@param  ip    : Զ������IP
		@param  port  : Զ�������˿�
		@return       : û�д���������true,���ӳɹ���ص�OnConnected
		*/
		virtual bool Connect( const char * ip,unsigned short port ) = 0;

		/**
		@brief        : ��������
		@param  pData : ����ָ��ĵ�ַ
		@param dwDataLen:���ݳ���
		@param dwFlag : �������ݵ���������,������SEND_DATA_FLAG�е�ö��ֵλ�����
		@return       : û�д���������true
		*/
		virtual bool SendData( const char * pData,DWORD dwDataLen,DWORD dwFlag=0 ) = 0;

		/**
		@brief        : �ر�����
		@return       : û�д���������true,�رճɹ���ص�OnDisconnected
		*/
		//crr �ӱ�̵ĽǶȽ�������Disconnect������������closesocket��Ȼ��release
		//���д�����ʵ�ַ�ʽҲȷʵ��ˣ�
		//Ϊ���̰߳�ȫ��disconnect��release�������ͬһ���߳�����ɣ������¶�����ӿڣ�����Ҫ���������¼���Ч�ʵ�
		//virtual bool Disconnect() = 0;

		/**
		@brief        : �����¼�����ӿ�,�������ջص��¼�
		@param pHandler:�ӿ�ָ��
		*/
		virtual void SetEventHandler( IConnectionEventHandler * pHandler ) = 0;

		/**
		@brief        : ȡ���¼�����ӿ�
		@return       : �ӿ�ָ��
		*/
		virtual IConnectionEventHandler * GetEventHandler() const = 0;


		/**
		@name              : ȡ�öԷ��������ַ
		@param dwRemoteIP  : ���ضԷ���IP [OUT]
		@param wRemotePort : ���ضԷ��Ķ˿� [OUT]
		@return            : ����Է��ĵ�ַ����ȷ���򷵻�ʧ��
		*/
		virtual bool GetRemoteAddr(DWORD &dwRemoteIP,WORD & wRemotePort) = 0;


		/**
		@name              : ȡ�öԷ��������ַ
		@param ppRemoteIP  : ���ضԷ���IP [OUT]
		@param dwRemotePort: ���ضԷ��Ķ˿� [OUT]
		@return            : ����Է��ĵ�ַ����ȷ���򷵻�ʧ��
		*/
		virtual bool GetRemoteAddr( const char ** ppRemoteIP,DWORD & dwRemotePort) = 0;

		/**
		@name         : �Ƿ��Ǳ�������
		@brief        : 
		*/
		virtual bool  IsPassive() const = 0;

		/**
		@brief        : ���ٸö���,�ͷ��ڴ�
		*/
		virtual void Release() = 0;

		virtual void ChangePacker(DWORD CryptId,uchar *key,DWORD keylen) = 0;
	};

	/**
	@name : UDP�¼�����ӿ�
	@brief: 
	*/
	struct IUDPHandler
	{
		/**
		@name             : ���ݵ����¼�
		@brief            : UDP�׽����յ�����ʱ�ص���
		@para  socket     : �յ����ݵ��׽���
		@param szRemoteIP : �Է�IP
		@param nRemotePort: �Է��˿�
		@param pData      : ���ݵ�ַ
		@pram dwDataLen   : ���ݳ���
		*/
		virtual void OnRecv( IUDPSocket * socket,LPVOID pData,DWORD dwDataLen,const char * szRemoteIP,WORD nRemotePort ) = 0;

		/**
		@name             : ��������¼�
		@brief            :
		@param socket     : ���ִ�����׽���
		@param dwErrorCode: ������
		*/
		virtual void OnError( IUDPSocket * socket,DWORD dwErrorCode ) = 0;
	};

	/**
	@name : UDP�׽���
	@brief: 
	*/
	struct IUDPSocket
	{
		/**
		@brief            : ��������
		@param szRemoteIP : �Է�IP
		@param nRemotePort: �Է��˿�
		@param  pData     : ����ָ��ĵ�ַ
		@param dwDataLen  : ���ݳ���
		@param dwFlag     : �������ݵ���������,������SEND_DATA_FLAG�е�ö��ֵλ�����
		@return           : û�д���������true
		*/
		virtual bool SendData( const char * szRemoteIP,WORD nRemotePort,const char * pData,DWORD dwDataLen,DWORD dwFlag=0 ) = 0;


		/**
		@brief        : �����¼�����ӿ�,�������ջص��¼�
		@param pHandler:�ӿ�ָ��
		*/
		virtual void SetEventHandler( IUDPHandler * pHandler ) = 0;

		/**
		@brief        : ȡ���¼�����ӿ�
		@return       : �ӿ�ָ��
		*/
		virtual IUDPHandler * GetEventHandler() const = 0;

		/**
		@brief        : ���ٸö���,�ͷ��ڴ�
		*/
		virtual void Release() = 0;
	};

	/// ��������ʱ�ı�־λ
	enum SEND_DATA_FLAG
	{
		NO_COPY      = 0X01 ,     // ��������ʱ��Ҫ���⿽���ڴ�,�����־��Ҫ��Ϊ���������
								  // ��Ϊ����������һ���첽�ص�IO,���Դ��ݸ�����ϵͳSOCKET
								  // ʵ�ֵ�����BUFF����ָ��ջ��,����ͨ��û����һ�������ڲ�
								  // ��Ҫ����newһ���ڴ�,�������ݿ�����ȥ�ٷ�.���SendData
								  // �����д��ݵ����ݵ�ַ�Ѿ��Ƿ����ڶ��ϵ�,�û�����ʱ����
								  // ָ����������ڴ淢��,�������Լ���һ���ڴ濽���Ŀ���.
		NO_ENCRYPT   = (0X01<<1), // ��������ʱͨ����ʹ��Ĭ�ϵļ����㷨���м���.Ϊ��ȡ������
								  // ����Ӧ�ò��Ѿ��ӹ����˿������øñ�־ȡ���ڲ��ļ��ܹ��̡�
		NO_PACKAGE   = (0X01<<2), // ȡ���ڲ����������.��ΪTCP���������,���Է�����ʱĬ�ϻ����
		OOB_DATA     = (0X01<<3), // ��������,��ʱ��֧��
	};

	/**
	@name         : ��ʼ��ͨѶ��
	@brief        : ��ʼ������:
	              : 1.��ʼ���첽IO���
    @param dwThreadNum:ʹ�ö��ٸ��̴߳����첽IO
	@return       : 1 ... OK
	                -1... �첽IO��ܳ�ʼ��ʧ��
	*/
	NET_API int  InitializeNetwork(DWORD dwThreadNum=1);

	/**
	@name         : �ͷ�ͨѶ��
	@brief        : ����ڳ����˳�ʱӦ�ò㻹û�е��øú���,ͨѶ����Լ��ͷ�
	@brief        : ��������������Բ�����
	*/
	NET_API int  UninitializeNetwork();

	/**
	@name            : ��ȡ�ص�������
	@brief           : ͨѶ��ĸ����¼�������ͨѶ�̴߳�����,���û�ϣ���յ���ͨѶ�¼��������û��߳�
                     : �����ϲ����Ͳ���Ҫ���⴦���߳�ͬ���Ĳ���,�������û��̵߳���ѭ����,��Ҫ����
                     : ����DispatchNetworkEvents����������ͨѶ�¼����ɷ�,��������ѭ����ȡ������Ϣһ��

	*/
	NET_API void DispatchNetworkEvents();

	/**
	@name            : ȡ�������¼���֪ͨ���
	@brief           : Ӧ�ò���Լ�������¼�Ȼ�����DispatchNetworkEvents��ȡ������Ϣ
	@return          : �����¼����
	*/
	NET_API HANDLE GetNetworkEventHandle();

	// ��������ʱ�ı�־Ϊ
#	define 	NO_PACK      0            // �����
#	define	DEFAULT_PACK (IPacker *)1 // ʹ��Ĭ�Ϸ�ʽ���

	/**
	@name            : ����һ��TCP���Ӷ���
	@param dwBindPort: �󶨶˿�,��0��Ҫ������������������ʱ���ѡ��һ�����ö˿�
	@param pHandler  : �¼�����ӿ�ָ��
	@param pPacker   : ����ӿ�,��0��ʾ���������,��1��ʾʹ��Ĭ�ϵļ��������
	@brief:
	*/
	NET_API IConnection * CreateTCPConnection(USHORT dwBindPort=0,IConnectionEventHandler * pHandler=0,IPacker * pPacker=DEFAULT_PACK);

	/**
	@name            : ����һ��UDP�׽��ֶ���
	@param dwBindPort: �󶨶˿�
	@param pHandler  : �¼�����ӿ�ָ��
	@brief:
	*/
	NET_API IUDPSocket * CreateUDPSocket(USHORT dwBindPort,IUDPHandler * pHandler=0);



///////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(_LIB) || defined(NET_STATIC_LIB)	/// ��̬��汾
#	pragma comment(lib, MAKE_LIB_NAME(xs_nm))
extern "C" IConnection * CreateTCPConnection(USHORT dwBindPort,IConnectionEventHandler * pHandler,IPacker * pPacker);
#	define	CreateTCPConnectionProc	CreateTCPConnection
#else													/// ��̬��汾
typedef IConnection * (RKT_CDECL *procCreateTCPConnection)(USHORT dwBindPort,IConnectionEventHandler * pHandler,IPacker * pPacker);
#	define	CreateTCPConnectionProc	DllApi<procCreateTCPConnection>::load(MAKE_DLL_NAME(xs_nm), "CreateTCPConnection")
#endif

};

#endif//__NET_H__