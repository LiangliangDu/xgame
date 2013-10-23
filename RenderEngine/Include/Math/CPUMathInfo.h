#ifndef __CPUMathInfo_H__
#define __CPUMathInfo_H__
#include "ReMathPrerequisite.h"

namespace xs
{
	/* ��ȡCPU������ѧ����Ĺ��ܣ�����MMX��SSE��3DNow��
	*/
	enum	CPUMathCapability
	{
		CPUMC_MMX = 0x00000001,//֧��mmx
		CPUMC_SSE = 0x00000002,//֧��sse
		CPUMC_SSE2 = 0x00000004,//֧��sse2
		CPUMC_3DNOW = 0x00000008,//֧��3dNow
	};
	class _ReMathExport CPUMathInfo
	{
		static bool s_initialize;//�Ƿ��ʼ��cpu��ѧ���㹦��
		static uint s_capability;//cpu����
	public:
		static uint getCapability();//��ȡ����
	private:
		static void initializeCPUCapability();//��ʼ��cpu��ѧ������Ϣ
		static uint isOsSupport(CPUMathCapability cap);//����ϵͳ�Ƿ�֧��CPU�����ֹ���
	};
}
#endif