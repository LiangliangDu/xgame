#ifndef __HardwareCursorManagerOGL_H__
#define __HardwareCursorManagerOGL_H__

#include "IHardwareCursorManager.h"

class HardwareCursorManagerOGL: public IHardwareCursorManager, public Singleton<HardwareCursorManagerOGL>
{
	//<<interface>>
public:

	/************************************************************************/
	/* �����Ƿ���ʾ���
	@param show �Ƿ���ʾ���
	*/
	/************************************************************************/
	virtual void	showCursor( bool show);


	/************************************************************************/
	/*   ���ù���λ��  
	@param	x ��Ļ������
	@param	y ��Ļ������
	@param	updateImmediate �Ƿ������ػ���
	*/
	/************************************************************************/
	virtual	void	setCursorPosition( int x, int y, bool updateImmediate);	

	/************************************************************************/
	/* ��������ȵ�                                                         */
	/************************************************************************/
	virtual void	setCursorHotspot(uint x, uint y);

	/************************************************************************/
	/* �������ͼƬ
	@param pTexture ���ͼƬ��Ҫ�ͷ�pTexure����ȡ��ͼƬ����
	*/
	/************************************************************************/
	virtual void	setCursorImage(ITexture* pTexture);

	/************************************************************************/
	/*�����Ƿ����                                                         */
	/************************************************************************/
	virtual bool	isAvailable();
	
public:
	static HardwareCursorManagerOGL* instance()
	{
		return getInstancePtr();
	}

private:

};


#endif