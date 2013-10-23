/*******************************************************************
** �ļ���:	AsynFileDevice.cpp 
** ��  Ȩ:	(C)  2008 - All Rights Reserved
** 
** ��  ��:	03/04/2008
** ��  ��:	1.0
** ��  ��:	
** Ӧ  ��:  	

**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/

#include "stdafx.h"
#include <assert.h>
#include "AsynFileDevice.h"
#include "AsynIoResult.h"
#include "Proactor.h"
#include "AsynIoResultImp.h"
#include "SafeReleaseHelper.h"

#ifdef WIN32

namespace xs{

	//////////////////////////////////////////////////////////////////////////
	bool AsynFileDevice::Create(const char * path)
	{	
		m_hHandle = ::CreateFile(path,
			                     GENERIC_WRITE|GENERIC_READ,
								 FILE_SHARE_WRITE|FILE_SHARE_READ,
								 0,
								 OPEN_ALWAYS,
								 FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED|FILE_FLAG_RANDOM_ACCESS,
								 0);

		if ( INVALID_HANDLE_VALUE==m_hHandle )
		{
			Error("open file failed!" << path << GetLastError());
			return false;
		}

		m_pReader = new AsynFileDevice_Reader(this);
		m_pWriter = new AsynFileDevice_Writer(this);

		GetAsynIoProactor()->RegisterDevice(this);

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	void AsynFileDevice::Close()
	{
		if ( m_hHandle!=INVALID_HANDLE_VALUE )
		{
			::CloseHandle(m_hHandle);
			m_hHandle = INVALID_HANDLE_VALUE;
		}

		assert(m_pendingList.empty());

		m_pendingList.clear();

		safeDelete(m_pReader);
		safeDelete(m_pWriter);
	}

	uint64 AsynFileDevice::GetSize()
	{
		LARGE_INTEGER size;
		if ( GetFileSizeEx(m_hHandle,&size) )
		{
			return size.QuadPart;
		}else
		{
			return 0;
		}
	}

	void AsynFileDevice::Release()
	{
		while(1)
		{
			// �����и��ݾ�,����ʹ�õ���������
			// ��guard��ʱ�����͹�֮��ͻ����m_Locker����
			// ���ǵ�ִ�е������delete thisʱm_Locker�Ѿ��͹���
			// ����guard�͹�ʱ������ڴ汻�ƻ�
			ResGuard<Mutex>  guard(m_Locker);

			if ( m_hHandle!=INVALID_HANDLE_VALUE )
			{
				RESULT_LIST::iterator it = m_pendingList.begin();
				for ( ;it!=m_pendingList.end();++it )
				{
					AsynIoResult * result = (*it);
					result->SetHandler(&SafeReleaseHelper::getInstance());
				}

				::CloseHandle(m_hHandle);
				m_hHandle = INVALID_HANDLE_VALUE;
			}

			if ( !m_pendingList.empty())
			{
				SafeReleaseHelper::getInstance().ReleaseAsynIoDevice(this);
				return;
			}

			break;
		}

		delete this;
	}

	//////////////////////////////////////////////////////////////////////////
	AsynIoResult * AsynFileDevice::CreateAsynIoResult(int iotype,AsynIoHandler * handler)
	{
		ResGuard<Mutex>  guard(m_Locker);

		AsynIoResult * result = new AsynIoResultImp((AsynIoType)iotype,handler);

		m_pendingList.insert(result);
		result->SetAsynDevice(this);

		return result;
	}

	//////////////////////////////////////////////////////////////////////////
	void AsynFileDevice::DeleteAsynIoResult(AsynIoResult * result)
	{
		ResGuard<Mutex>  guard(m_Locker);

		RESULT_LIST::iterator it = m_pendingList.find(result);
		assert(it!=m_pendingList.end());

		m_pendingList.erase(it);

		delete (AsynIoResultImp *)result;
	}

	//////////////////////////////////////////////////////////////////////////
	bool AsynFileDevice_Reader::read(DWORD expect_bytes,AsynIoHandler * handler)
	{
		AsynIoResult * result = m_pDevice->CreateAsynIoResult(ASYN_IO_READ,handler);
		result->PrepareBuffer(expect_bytes);

		result->SetOffsetBytes( ((AsynFileDevice*)m_pDevice)->GetCurPos());

		DWORD dwTransferredBytes = 0;
		BOOL ret = ::ReadFile(m_pDevice->GetHandle(),
			                    result->GetBufferList()->buf,
							    expect_bytes,
								&dwTransferredBytes,
							    result
							    );

		if ( ret==FALSE )
		{
			DWORD error_code = ::WSAGetLastError();
			if ( error_code==ERROR_IO_PENDING )
				return true;

			Error("read data failed! error code = " << error_code << "\r\n");
			result->SetErrorCode(error_code);
			GetAsynIoProactor()->PostCompletion(result);
			return false;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool AsynFileDevice_Writer::write(const char * data,DWORD len,AsynIoHandler * handler)
	{
		AsynIoResult * result =m_pDevice->CreateAsynIoResult(ASYN_IO_WRITE,handler);
		result->PrepareBuffer(len);

		memcpy(result->GetBufferList()->buf,data,len);
		result->SetOffsetBytes( ((AsynFileDevice*)m_pDevice)->GetCurPos());
		
		DWORD dwTransferredBytes = 0;
		int ret = ::WriteFile(m_pDevice->GetHandle(),
			                    result->GetBufferList()->buf,
							    result->GetBufferList()->len,
								&dwTransferredBytes,
							    result
								);

		if ( ret==FALSE )
		{
			DWORD error_code = ::WSAGetLastError();
			if ( error_code==ERROR_IO_PENDING )
				return true;

			Error("write data failed! error code = " << error_code << "\r\n");
			result->SetErrorCode(error_code);
			GetAsynIoProactor()->PostCompletion(result);
			return false;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	bool AsynFileDevice_Writer::writeEx( AsynIoBuffer * pBuffList,DWORD dwBuffCount,AsynIoHandler * handler)
	{
		assert(false);
		return false;		
	}
};

#endif//WIN32