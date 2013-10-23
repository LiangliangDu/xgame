#ifndef __I_StackWalk_H__
#define __I_StackWalk_H__

#include <string>

enum
{
	///�Ƿ����Log
	dumpLog,

	///������Ϣ
	dumpBasicInfo,

	///ģ���б�
	dumpModuleList,

	//�����б�
	dumpWindowList,

	///�����б�
	dumpProcessList,

	///�Ĵ���
	dumpRegister,

	///����ջ
	dumpCallStack,

	///���dmp�ļ�
	dumpMiniDump,

	dumpCount
};

struct IStackWalk;

struct IStackWalkCallback
{
	///��ʼdump��Ϣ������������-
	virtual void onDumpStart(IStackWalk*) = 0;

	///������IStackWalk��dumpLn Dump�������LogFile����Ϣ
	virtual void onDump(IStackWalk*,PEXCEPTION_POINTERS) = 0;

	///Dump��������ô˺������˺�������ֵ�ᱻ�����쳣����ķ���ֵ
	virtual long onDumpFinish(IStackWalk*,PEXCEPTION_POINTERS) = 0;
};

struct IStackWalk
{
	///��һ��IStackWalkCallback�Ļص�
	virtual bool attachStackWalkCallback(IStackWalkCallback *) = 0;

	///ɾ���ص�
	virtual bool detachStackWalkCallback(IStackWalkCallback *) = 0;

	///����Log�ļ���
	virtual void setLogFileName(const char* szLogFileName) = 0;

	///����Dmp�ļ���
	virtual void setDumpFileName(const char* szDumpFileName) = 0;

	///�������ö�ٵĿ���
	virtual void setDumpOn(int iEnum,bool bOn) = 0;

	///����Dump����
	virtual void setDumpType(long lDumpType) = 0;

	///�õ��쳣��
	virtual unsigned long getExceptionCode(PEXCEPTION_POINTERS pExceptionInfo) = 0;

	///�õ��쳣����
	virtual const char* getExceptionDesc(PEXCEPTION_POINTERS pExceptionInfo) = 0;

	///�õ�������ģ���ļ�ƫ��
	virtual unsigned long getCrashFileOffset(PEXCEPTION_POINTERS pExceptionInfo) = 0;

	///�õ�������ģ���ļ���
	virtual const char*	getCrashModuleName(PEXCEPTION_POINTERS pExceptionInfo) = 0;

	///���һЩDump��Ϣ��Log�ļ�
	virtual void dumpLn(const char* szMsg) = 0;

	///ȡ�ñ���ģ��Ĳ�Ʒ�汾��
	virtual void getCrashModuleProductVer(PEXCEPTION_POINTERS pExceptionInfo,unsigned short pwVer[4]) = 0;

	///ȡ�õ�ǰ����ջ
	virtual std::string getCallStack(CONTEXT& Context,HANDLE hThread) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(_LIB) || defined(CRASHDUMP_STATIC_LIB)	/// ��̬��汾
#	pragma comment(lib, MAKE_LIB_NAME(xs_swm))
extern "C" IStackWalk * LoadSWM();
#	define	createStackWalkProc	LoadSWM
#else													/// ��̬��汾
typedef IStackWalk * (RKT_CDECL *proccreateStackWalk)(void);
#	define	createStackWalkProc	DllApi<proccreateStackWalk>::load(MAKE_DLL_NAME(xs_swm), "LoadSWM")
#endif


#endif