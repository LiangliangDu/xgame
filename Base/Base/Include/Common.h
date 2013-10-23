//==========================================================================
/**
* @file	  : Common.h
* @author : 
* created : 2008-1-2   16:08
* purpose : ����ͷ�ļ�
*/
//==========================================================================


#ifndef RKT_COMMON_H
#define RKT_COMMON_H

#include "Config.h" // �����û�������

#include "platform.h"
#include "type.h"
//namespace xs {


// ����������
#if defined( _MSC_VER )
#	define RKT_COMPILER_MSVC
#	define RKT_COMPILER_VER		_MSC_VER
#elif defined( __GNUC__ )
#   define RKT_COMPILER_GNUC
#   define RKT_COMPILER_VER		(((__GNUC__)*100) + (__GNUC_MINOR__*10) + __GNUC_PATCHLEVEL__)
#else
#   pragma error "Unknown compiler. Abort!"
#endif


// ƽ̨����
#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( WIN32 )
#	define RKT_WIN32
#else
#	define RKT_LINUX
#endif

	/// ģ������ú�׺
#if defined(_DEBUG)
#	define CFG_SUFFIX		"_d"
#elif defined(RELEASEDEBUG)
#	define CFG_SUFFIX		"_rd"
#else
#	define CFG_SUFFIX		""
#endif

	/// ��̬��ǰ��׺
#ifdef RKT_WIN32
#	define DLL_PREFIX	""
#	define DLL_SUFFIX	".dll"
#else
#	define DLL_PREFIX	"lib"
#	define DLL_SUFFIX	".so"
#endif


	/// ��Ͽ��ļ���
#define MAKE_DLL_NAME(module)			"./"DLL_PREFIX#module""CFG_SUFFIX""DLL_SUFFIX
#define	MAKE_LIB_NAME(module)			#module"_s"CFG_SUFFIX
#define MAKE_DLL_LIB_NAME(module)		#module""CFG_SUFFIX


// ���뵼����־
#ifdef RKT_WIN32
#	ifdef _LIB
#		define CLASS_EXPORT
#		define CLASS_IMPORT
#		define API_EXPORT		extern "C"
#		define API_IMPORT		extern "C"
#	else
#		define CLASS_EXPORT		__declspec(dllexport)
#		define CLASS_IMPORT		__declspec(dllimport)
#		define API_EXPORT		extern "C" __declspec(dllexport)
#		define API_IMPORT		extern "C" __declspec(dllimport)
#	endif
#else
#	define CLASS_EXPORT
#	define CLASS_IMPORT
#	define API_EXPORT
#	define API_IMPORT
#endif

#ifdef RKT_WIN32
#	if defined(_LIB) || defined(BASE_STATIC_LIB)
#		define RKT_EXPORT
//#		pragma comment(lib, MAKE_LIB_NAME(xs_com))
#	elif defined(BASE_EXPORTS)
#		define RKT_EXPORT	CLASS_EXPORT
//crr add for static link
#   elif defined(STATIC_LINK)
#		define RKT_EXPORT 
#	else
#		define RKT_EXPORT	CLASS_IMPORT
//#		pragma comment(lib, MAKE_DLL_LIB_NAME(xs_com))
#	endif
#elif defined(RKT_LINUX)
#	define RKT_EXPORT
#endif	// RKT_LINUX


#ifdef RKT_WIN32
#	if defined(_LIB) || defined(BASE_STATIC_LIB)
#		define RKT_API
	//#		pragma comment(lib, MAKE_LIB_NAME(xs_com))
#	elif defined(BASE_EXPORTS)
#		define RKT_API		extern "C" RKT_EXPORT
#	else
#		define RKT_API	extern "C"
	//#		pragma comment(lib, MAKE_DLL_LIB_NAME(xs_com))
#	endif
#elif defined(RKT_LINUX)
#	define RKT_API
#endif	// RKT_LINUX

#ifdef RKT_WIN32
#elif defined(RKT_LINUX)
#	ifndef __cdecl
#		define __cdecl __attribute__((__cdecl__))
#	endif
#endif
#define RKT_CDECL				__cdecl

#ifndef RKT_STDCALL
#	ifdef RKT_WIN32
#		define RKT_STDCALL		__stdcall
#	elif defined(RKT_LINUX)
#		define RKT_STDCALL		__attribute__((__stdcall__))
#	endif
#endif



#ifndef RKT_CALLBACK
#	define RKT_CALLBACK		RKT_STDCALL
#endif


// ֻ�����޷��ŵļ����ͣ�������д
typedef unsigned char			uchar;
typedef unsigned short			ushort;
typedef unsigned int			uint;
typedef unsigned long			ulong;
#ifdef RKT_WIN32
typedef __int64					int64;
typedef unsigned __int64		uint64;
#else  //RKT_LINUX
typedef long long               int64;
typedef unsigned long long      uint64;
#endif

// ��ȫɾ�����ͷ�
#ifndef safeDelete
#	define safeDelete(ptr)		if ((ptr)) {delete (ptr); (ptr) = 0;}
#endif
#ifndef safeDeleteArray
#	define safeDeleteArray(ptr)	if ((ptr)) {delete[] (ptr); (ptr) = 0;}
#endif
#ifndef safeRelease
#	define safeRelease(ptr)		if ((ptr)) {(ptr)->release(); (ptr) = 0;}
#endif

/** ������Assert,�ο�boost��,�磺
STATIC_ASSERT(sizeof(long) > 8);
*/
namespace COMPILE_ASSERT
{
	template <bool x> struct COMPILE_ASSERT_FAILURE;
	template <> struct COMPILE_ASSERT_FAILURE<true> { enum { value = 1 }; };
	template<int x> struct compile_assert_test{};
}
#define STATIC_ASSERT(exp) \
	typedef COMPILE_ASSERT::compile_assert_test< \
	sizeof(COMPILE_ASSERT::COMPILE_ASSERT_FAILURE< (bool)(exp) >) \
	> compile_assert_typedef_

//} // namespace


// hash_map�Ķ��壬Ϊ�˲����������ռ�Ĳ��죬��ֱ���� HashMap ��
#if defined(RKT_COMPILER_GNUC) && RKT_COMPILER_VER >= 310
#   define HashMap __gnu_cxx::hash_map
#else
#   if defined(RKT_COMPILER_MSVC)
#       if RKT_COMPILER_VER > 1300
#           define HashMap stdext::hash_map
#       else
#           define HashMap std::hash_map
#       endif
#   else
#       define HashMap std::hash_map
#   endif
#endif

#define PROFILE(x)

#ifdef RKT_TEST
#	define SEGMENT(x)	x
#else
#	define SEGMENT(x)
#endif

#ifdef RKT_DEBUG
#define debugBreak		_asm{int 3}
#else
#define debugBreak		(void)0
#endif

// ������������ڷ������öϵ�
#define	breakable		switch(1) case 1: default:

#endif // RKT_COMMON_H
