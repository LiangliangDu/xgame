#pragma once


struct IProgressManager
{
	//��ʼ����Ϸ����
	virtual bool StartInitGameProgress( uint progresslen) =0;//��ʼ��Ϸ��ʼ������
	virtual void StopInitGameProgress() = 0;//������Ϸ��ʼ������

	//���س�������
	virtual void StartLoadingScenceProgress(uint progresslen ) =0;//��ʼ���س�������
	virtual void StopLoadingScenceProgress()=0;//ֹͣ���س�������
	virtual void AdvanceLoadingScenceProgressLength( uint delta ) =0;//���ӽ���
	virtual bool IsLoadingScence()=0;//�Ƿ����ڼ��س���
	
	virtual void Release()=0;//�ͷŽ��ȹ�����
	virtual bool InitScheme(void)=0;//��ʼ�����ȹ�����������

};

IProgressManager * CreateProgressManager(void);