/**
* Created by pk 2008.01.03
*/

#ifndef RKT_LOADLIB_H
#define RKT_LOADLIB_H

#include "Common.h"

#ifdef RKT_WIN32
#	include <windows.h>
#	include <stdio.h>
#elif defined (RKT_LINUX)
#	include <dlfcn.h>
#endif

namespace xs {

	/** ����һ����̬���ӿ�
	@param filename ��̬���ӿ��·����
	@retval �ɹ�����ָ����̬���ӿ�ľ�������򷵻�NULL
	@see freelib
	*/
	RKT_API void* loadlib(const char* filename);

	/** �ͷ�һ����̬���ӿ�
	@param moduleHandle Ҫ�ͷŵĶ�̬���ӿ�ľ��
	@return �ɹ�����true�����򷵻�false
	@see loadlib
	*/
	RKT_API bool freelib(void* moduleHandle);


	/// api�������͵Ķ��壬ͬһ�ֵ��÷�ʽ�º���ԭ�Ϳ������¶��壬��Ӱ�췵�صĽ��
	typedef int (RKT_CDECL *Proc)(void);


	/** ��ȡ��̬���ӿ��ж�ӦAPI�ĺ�����ַ
	@param moduleHandle Ҫ�ͷŵĶ�̬���ӿ�ľ��
	@param procName �������ƣ��뱣֤��Сдû�д���
	@retval ���ض�Ӧ�����ĵ�ַ
	*/
	RKT_API Proc getProcAddress(void* moduleHandle, const char* procName);


	/// DLL���󴴽�������
	template<class _Proc>
	class DllApi
	{
	protected:
		static void* handle;	/// dll���
		static int ref;			/// ���ü���

	public:
		static void freelib()
		{
#ifdef RKT_WIN32
			if (handle && --ref == 0)
			{
				::FreeLibrary((HMODULE)handle);
				handle = 0;
			}
#else
			if (handle && --ref == 0)
			{
				dlclose(handle);
				handle = 0;
			}
#endif
		}

		static _Proc load(const char* filename, const char* proc)
		{
#ifdef RKT_WIN32
			if (!handle)
			{
				handle = ::LoadLibraryA(filename);
				if (NULL == handle)
				{
					Error("LoadLibraryA" << filename << " failed, LastError=" << GetLastError() << endl);
				}
				
				ref = 1;
			}
			else ref++;

			return (_Proc)GetProcAddress((HMODULE)handle, proc);
#else
			if (!handle)
			{
				handle = dlopen(filename, RTLD_NOW);
				ref = 1;
			}
			else ref++;

			return (_Proc)dlsym(handle, proc);
#endif
		}
	};

	template<class _Proc> void* DllApi<_Proc>::handle = 0;
	template<class _Proc> int DllApi<_Proc>::ref = 0;

/* ����
	// IFoo.h
	#pragma once

	#include "LoadLib.h"

	namespace xs {

		struct IFoo
		{
			virtual int foo(int a) = 0;
			virtual void release() = 0;
		};


		#if defined(_LIB) || defined(FOO_STATIC_LIB)/// ��̬��汾
		#	pragma comment(lib, MAKE_LIB_NAME(Foo))
		extern "C" IFoo* CreateFoo(int dummy);
		#	define	CreateFooProc	CreateFoo
		#else /// ��̬��汾
		typedef IFoo* (RKT_CDECL *procCreateFoo)(int dummy);
		#	define	CreateFooProc	DllApi<procCreateFoo>::load(MAKE_DLL_NAME(Foo), "CreateFoo")
		#endif

	}

	// Foo.cpp
	#include "stdafx.h"
	#include "Foo.h"

	namespace xs {

		API_EXPORT IFoo* CreateFoo(int dummy)
		{
			return static_cast<IFoo*>(new Foo());
		}

	}

	// main.cpp
	#include "stdafx.h"

	#define FOO_STATIC_LIB
	#include "IFoo.h"

	int _tmain(int argc, _TCHAR* argv[])
	{
		using namespace xs;
		IFoo* i = CreateFooProc(25);
		int ret = i->foo(10);
		i->release();

		return 0;
	}
*/
}

#endif // RKT_LOADLIB_H