/*******************************************************************
** �ļ���:	e:\CoGame\Demo\src\Character\RandGenerator.h
** ��  Ȩ:	(C) 
** 
** ��  ��:	2007/9/13  16:04
** ��  ��:	1.0
** ��  ��:	�������������ʹ��ǰ�벥����CRandGenerator::Seed
** Ӧ  ��:  	
	
**************************** �޸ļ�¼ ******************************
** �޸���: 
** ��  ��: 
** ��  ��: 
********************************************************************/
#pragma once

#define GENIUS_NUMBER 0x376EAC5D

class CRandGenerator
{
	enum 
	{
		Number = 0x1000, 
	};
public:
	/** �̶�����
	@param   
	@param   
	@return  
	*/
	void Seed(DWORD dwSeed)
	{
		m_Seed = dwSeed^GENIUS_NUMBER;

		Batch();
	}

	/** �������
	@param   
	@param   
	@return  
	*/
	DWORD Seed(void)
	{
		int s;
		__asm 
		{
			_asm _emit 0x0f _asm _emit 0x31
				mov s,eax
		}

		Seed(s);

		return s^GENIUS_NUMBER;
	}

	/** 
	@param   
	@param   
	@return  
	*/
	DWORD GetSeed(void) const
	{
		return m_Seed^GENIUS_NUMBER;
	}
	
	/** ����һ��WORD
	@param   
	@param   
	@return  
	*/
	WORD GetWORD(void)
	{
		if(m_Ptr >= Number * 2)
		{
			Batch();
			m_Ptr = 0;
		}

		return *((WORD *)m_pBuffer + m_Ptr++);
	};

	/** ����һ��DWord
	@param   
	@param   
	@return  
	*/
	DWORD GetDWORD(void)
	{
		if(m_Ptr >= Number * 2 - 1)
		{
			Batch();
			m_Ptr=0;
		}	

		m_Ptr += 2;
		return *(DWORD *)((WORD *)m_pBuffer + m_Ptr - 2);
	}

	/** 
	@param   
	@param   
	@return  
	*/
	CRandGenerator(void)
	{
		int s;
		m_pBuffer = new DWORD[Number];
		m_Ptr = Number * 2;
		__asm
		{
			_asm _emit 0x0f _asm _emit 0x31
				mov s,eax
		}

		m_Seed = s;
	}

	/** 
	@param   
	@param   
	@return  
	*/
	virtual ~CRandGenerator(void)
	{
		delete[] m_pBuffer;
	}

private:
	/** ����һ��
	@param   
	@param   
	@return  
	*/
	void		Batch(void)
	{
		__asm 
		{
			cld
				mov edi,[ecx]CRandGenerator.m_pBuffer
				mov eax,[ecx]CRandGenerator.m_Seed
				mov ecx,0x1000		;//WRandom::Number
			mov esi,0xE7BD2160

				ALIGN 4
_loop_circle1:
			push ecx
				mov ecx,32
_loop_circle2:
			mov ebx,eax
				shl eax,1
				and ebx,esi;	//select the bit for xor
			mov edx,ebx
				bswap ebx
				xor bx,dx
				xor bh,bl;		// because P only judge one byte
			;// so must XOR to judge the p of whole word 
			jp _next;		//jp equals the xor 
			inc eax
_next:
			dec ecx
				jnz _loop_circle2
				pop ecx
				stosd
				dec ecx
				jnz _loop_circle1
				mov ecx,this
				mov [ecx]CRandGenerator.m_Seed,eax
		}
	}

private:
	DWORD *		m_pBuffer;
	DWORD		m_Seed;
	unsigned	m_Ptr;
};

extern CRandGenerator g_RandGenerator;
