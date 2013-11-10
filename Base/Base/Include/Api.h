 /**
* Created by pk 2008.01.03
*/

#ifndef RKT_API_H
#define RKT_API_H

#include "Common.h"

namespace xs {
	extern "C" RKT_API bool GetClientRect(void* hwnd,Rect* rc);
	/// ���ϵͳTick��
	RKT_API ulong getTickCount();

	/// ��ȡ�����ܼ�ʱ����ȡ��Tick��
	RKT_API ulong getTickCountEx();

	/// �߳����ߣ����룩
	RKT_API void sleep(ulong milliSeconds);

	/// ��ȡϵͳ�����ܼ���
	RKT_API int64 getPerformanceCount();

	/// �Ƿ��ǵ�����ģʽ
	RKT_API bool isDebuggerPresent();

	/// �����ж�
	RKT_API void debuggerBreak(const char* exp, const char* file, uint line, int* staticIntVarEqualZero = 0);

	/// ��ȡȫ�ֱ���������IGlobalClient��IGlobalServer��û���뵽ʲô�ð취��
	RKT_API void* getGlobal();

	/// ����ȫ�ֶ�������IGlobalClient��IGlobalServer��û���뵽ʲô�ð취��
	RKT_API void setGlobal(void* global);

#ifdef RKT_DEBUG
#	define DebuggerBreak(exp)		(void)( (exp) || (debuggerBreak(#exp, __FILE__, __LINE__, 0), 0) )
#	define DebuggerBreakOnce(exp)	{static int __s_once__ = 0; (void)( (exp) || (debuggerBreak(#exp, __FILE__, __LINE__, &__s_once__), 0) );}
#else
#	define DebuggerBreak(exp)		((void)0)
#	define DebuggerBreakOnce(exp)	((void)0)
#endif

}

#endif // RKT_API_H