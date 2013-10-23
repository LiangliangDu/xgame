#ifndef __ISTREAMSYSTEM_H__
#define __ISTREAMSYSTEM_H__

/** ʹ��ʾ����

@code


uint streamLength = 0;

//////////////////////////////////////////////////////////////////////////
// ����Ŀ¼̬����ϵͳ
// ����ϵͳ
Handle dataHandle = openStreamSystem("e:/newlife/program/bin/data");
if (!isValidHandle(dataHandle))
	return;

// ����ϵͳ�е�һ����
CStream* stream = openStream(dataHandle, "npc/npc1.dat");
if (stream)
	streamLength = stream->getLength();

// �رո����������Ͳ��ᵼ���ڴ�й©��
closeStream(stream);

// �ر���ϵͳ
closeStreamSystem(dataHandle);

//////////////////////////////////////////////////////////////////////////
// ������̬����ϵͳ(���������ƣ�������һ�е�·�����Բ�ͬ)
dataHandle = openStreamSystem("e:/newlife/program/bin/data.pkg");
if (!isValidHandle(dataHandle))
	return;

CStream* stream = openStream(dataHandle, "npc/npc1.dat");
if (stream)
	streamLength = stream->getLength();
closeStream(stream);

closeStreamSystem(dataHandle);


@endcode

 */

#include "Stream.h"
#include "Handle.h"

namespace xs{

/** ��һ����ϵͳ
 @param streamSysPath ��·�����������ļ�ʱ�ᵱ������������������Ŀ¼ʱ�ᵱ��Ŀ¼��������
 @return �ɹ�������ϵͳ�ľ�������򷵻���Ч���
 */
Handle openStreamSystem(const char* streamSysPath);

/** �ر�һ����ϵͳ
 @param streamSysHandle Ҫ�رյ���ϵͳ���
 @return �ɹ�����true�����򷵻�false
 */
bool closeStreamSystem(Handle streamSysHandle);

/** �����ϵͳ���Ƿ����ָ����������
@param streamSysHandle ��ϵͳ���
@param streamName		ָ������������
@return ���ڷ���true�����򷵻�false
*/
bool findStream(Handle streamSysHandle, const char* streamName);

/** ����ϵͳ�д�һ��ָ����������
 @param streamSysHandle ��ϵͳ���
 @param streamName		ָ������������
 @return �ɹ�����ָ���������󣬷��򷵻�NULL
 @see closeStream
 */
CStream* openStream(Handle streamSysHandle, const char* streamName);

/** ����ϵͳ��ö��������
@param streamSysHandle ��ϵͳ���
@param pCallback	Callback����ö�ٵ���������
*/
void listStream(Handle streamSysHandle, IListStreamCallback* pCallback,void *p);

/** �رմ򿪵�������
 @param stream Ҫ�رյ�������
 */
void closeStream(CStream* stream);

}


#endif // __ISTREAMSYSTEM_H__
