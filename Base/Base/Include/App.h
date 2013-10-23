/**
* Created by pk 2008.01.07
*/

#ifndef RKT_APP_H
#define RKT_APP_H

#include "Common.h"

namespace xs {

class CApplication
{
public:
	virtual int run() = 0;
};

/** ӵ����Ϣѭ����Win32Ӧ�ó��� */
class RKT_EXPORT CAppWin32 : public CApplication
{
	// ���죨������
public:
	CAppWin32()							{ }
	virtual ~CAppWin32()				{ }

	// ����
public:
	virtual bool onCreate()				{ return true; }
	virtual int run();
	/// ��������Ϸʱ�����Խ�����ֵ��Ϊ1��������û��windows��Ϣʱ����ѭ������onIdle
	virtual int onIdle(int idleCount)	{ return 0; }
	virtual void onClose()				{ }
};


/// �ж�ĳ�������Ƿ���
RKT_API bool isKeyPressed(uint virtualKeyCode);


/** ��Ϣ�ַ��� */
class RKT_EXPORT CMessageDispatcher
{
	// ���죨������
public:
	CMessageDispatcher()			{ }
	virtual ~CMessageDispatcher()	{ }

	// ����
public:
	/** �����ַ�������Ȥ����Ϣ(�ص�����)��WM_DESTROY ��Ϣ��ϵͳ���ã����û�����
	@param hWnd ��ϢԴ�Ĵ��ھ��
	@param message ��Ϣ��
	@param wParam ����1
	@param lParam ����2
	@return �����������Ϣ��������windows����Ĭ�ϴ����뷵��true�����򷵻�false
	*/
	virtual bool onMessage(void* hWnd, uint message, uint wParam, uint lParam)	{ return false; }
};

/** �����ڵ�Ӧ�ó��򣨽����ʺ���ϷӦ�ã�ֻ�е������ڣ� */
class RKT_EXPORT CAppWindow : public CAppWin32
{
private:
	CMessageDispatcher* m_msgDispatcher;	/// ��Ϣ�ַ���
	void*	m_hWnd;							/// ���ھ��

	// ���죨������
public:
	CAppWindow() : m_msgDispatcher(0), m_hWnd(0) { }
	CAppWindow(CMessageDispatcher* msgDispatcher) : m_hWnd(0), m_msgDispatcher(msgDispatcher) { }
	virtual ~CAppWindow()	{ }

	// ����
public:
	bool createWindow(ulong w, ulong h, ulong xPos = 0, ulong yPos = 0, bool centerWnd = true);
	void setWindowTitle(const char* title);
	void showWindow(bool show);

	// ����
public:
	void setMessageDispatcher(CMessageDispatcher* msgDispatcher)	{ m_msgDispatcher = msgDispatcher; }
	CMessageDispatcher* getMessageDispatcher() const				{ return m_msgDispatcher; }
	void* getHWND() const											{ return m_hWnd; }
	virtual void onSize(int dx, int dy)								{ };
	virtual bool onCreate()											{ return m_hWnd != NULL; }
};

/*
class RKT_EXPORT CApplicationScript : public CApplication
{
};*/


} // namespace xs


#endif // RKT_APP_H