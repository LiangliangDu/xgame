/******************************************************************************
ģ������
	tea.h
������
	tea�㷨
���ߣ�
	
******************************************************************************/

#ifndef _TEA_H_
#define _TEA_H_

#include "CryptType.h"

namespace xs{ namespace CryptPool{

ulong Encrypt_tea(uchar newbuf[], uchar buffer[], ulong length,uchar * key_,ulong keylen);
ulong Decrypt_tea(uchar newbuf[], uchar buffer[], ulong length,uchar * key_,ulong keylen);
ulong Set_tea_key(uchar keybuf[],ulong keylen);

}} //

#endif