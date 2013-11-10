#include "StdAfx.h"
#include "PixelFormat.h"
#include "ImageCodecSfp.h" 

namespace xs
{
    
    ImageCodec*	ImageCodecSfp::Instance()
    {
        static ImageCodecSfp codec;
        return &codec;
    }

	const char*	ImageCodecSfp::getType() const
	{
		static std::string strType = "sfp";
		return strType.c_str();
	}

#pragma pack (push)
#pragma pack (1)

	typedef struct __RLEHEADER // 20 bytes
	{
		ushort wFlags;		// RLEѹ�����ݱ�ʶ(GF) (Graphic Flag? Gao Feng?)
		uint dwTotalSize;	// ���ṹ�����ɫ������ݵ�������С
		uint dwWidth;		// RLEͼƬ�Ŀ�
		uint dwHeight;		// RLEͼƬ�ĸ�
		uchar nUseColor;		// ��ͼƬʹ�õĵ�ɫ�����ɫ��(�涨���255����ɫ,idx=255�ĵ㿴��͸����)
		uchar bHaveAlphaChannel;// �Ƿ���alphaͨ������
		uint dwDataOffset;	// ͼƬ���ݵ�ƫ����
		__RLEHEADER(){memset(this, 0, sizeof(__RLEHEADER));wFlags = 'FG';}
		bool hasPalette(){return (nUseColor != 0) && (dwDataOffset != sizeof(__RLEHEADER));}
		bool isHiColor() {return (nUseColor == 16) && (dwDataOffset == sizeof(__RLEHEADER));}
		bool isValid()
		{
			return (wFlags == 'FG' && dwTotalSize > 0 && dwWidth > 0 && dwHeight > 0 && dwDataOffset >= sizeof(__RLEHEADER));
		}
	}RLEHEADER;

	//16λ��ṹ
	struct WPixel {
		union {
			ushort color;								// 16bit �߲�
			struct {
				ushort blue:5;						// 5bit ��ɫ
				ushort green:6;						// 6bit ��ɫ
				ushort red:5;							// 5bit ��ɫ
			};
		};
		WPixel() {}
		WPixel(uint c) {color=(ushort)((c>>8&0xf800)|(c>>5&0x7e0)|(c>>3&0x1f));}	//��DWORDת��
		WPixel(int r,int g,int b) : red(r>>3),green(g>>2),blue(b>>3) {}
		operator uint() const {return (color<<5&0x7fc00)|(color<<8&0xf80000)|((color<<3|(color&7))&0x3ff);}
		// rrrgggggg0000000000 | rrrrr0000000000000000000 | ggbbbbbbbb => rrrrrrrr gggggggg bbbbbbbb

	};

#pragma pack (pop)

	ImageCodecSfp::ImageCodecSfp()
	{
		WPixel *pPixel = (WPixel*)m_defaultPal;
		memset(pPixel,0x77,sizeof(m_defaultPal));
		pPixel[255] = WPixel(255,0,255);
	}

	bool ImageCodecSfp::getDimension(xs::Stream* input,uint& width,uint& height,uint& depth)
	{
		if(!input || input->getLength() < sizeof(RLEHEADER))return false;

		RLEHEADER h;
		input->read(&h,sizeof(h));
		if(!h.isValid())
		{
			Error("Invalid SFP file\n");
			return false;
		}

		width = h.dwWidth;
		height = h.dwHeight;
		depth = 1;
			
		return true;
	}

#define alpha32mask	0x20		// 1/32=0.03125
#define alpha16mask	0x861		// 1/16=0.0625
#define alpha8mask	0x18e3		// 1/8=0.125
#define alpha4mask	0x39e7		// 1/4=0.25
#define alpha2mask	0x7bef		// 1/2=0.5

	// result=��*src + dest - ��*dest; ��=0/32
	__declspec(naked) void _alpha_0(void)
	{
		_asm
		{
			add edi, 2;
			ret;
		}
	}

	// result=��*src + dest - ��*dest; ��=1/32
	__declspec(naked) void _alpha_1(void)
	{
		_asm
		{
			shr ax, 5;				// ax=s/32
			mov bx, [edi];			// bx=d
			and ax, alpha32mask;
			add ax, bx;				// ax=s/32 + d
			shr bx, 5;				// bx=d/32
			and bx, alpha32mask;
			sub ax, bx;				// ax=s/32 + 31d/32
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}

	// result=��*src + dest - ��*dest; ��=2/32
	__declspec(naked) void _alpha_2(void)
	{
		_asm
		{
			shr ax, 4;				// ax=s/16
			mov bx, [edi];			// bx=d
			and ax, alpha16mask;
			add ax, bx;				// ax=s/16 + d
			shr bx, 4;				// bx=d/16
			and bx, alpha16mask;
			sub ax, bx;				// ax=2s/32 + 30d/32
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}

	// result=��*src + dest - ��*dest; ��=3/32
	__declspec(naked) void _alpha_3(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 4;				// ax=s/16
			shr bx, 4;				// bx=d/16
			and ax, alpha16mask;
			and bx, alpha16mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/16
			mov dx, bx;				// dx=d/16
			shr ax, 1;				// ax=s/32
			shr bx, 1;				// bx=d/32
			and ax, alpha2mask;
			and bx, alpha2mask;
			add ax, cx;				// ax=s/32 + s/16 = 3s/32
			add bx, dx;				// bx=d/32 + d/16 = 3d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=29d/32
			add ax, cx;				// ax=3s/32 + 29d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}

	// result=��*src + dest - ��*dest; ��=4/32
	__declspec(naked) void _alpha_4(void)
	{
		_asm
		{
			push cx;
			mov bx, [edi];			// bx=d
			shr ax, 3;				// ax=s/8
			mov cx, bx;				// cx=d
			and ax, alpha8mask;
			shr cx, 3;				// cx=d/8
			and cx, alpha8mask;
			sub bx, cx;				// bx=d - d/8 = 7d/8
			pop cx;
			add ax, bx;				// ax=4s/32 + 28d/32
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=5/32
	__declspec(naked) void _alpha_5(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 3;				// ax=s/8
			shr bx, 3;				// bx=d/8
			and ax, alpha8mask;
			and bx, alpha8mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/8
			mov dx, bx;				// dx=d/8
			shr ax, 2;				// ax=s/32
			shr bx, 2;				// bx=d/32
			and ax, alpha4mask;
			and bx, alpha4mask;
			add ax, cx;				// ax=s/32 + s/8 = 5s/32
			add bx, dx;				// bx=d/32 + d/8 = 5d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=27d/32
			add ax, cx;				// ax=5s/32 + 27d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=6/32
	__declspec(naked) void _alpha_6(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 3;				// ax=s/8
			shr bx, 3;				// bx=d/8
			and ax, alpha8mask;
			and bx, alpha8mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/8
			mov dx, bx;				// dx=d/8
			shr ax, 1;				// ax=s/16
			shr bx, 1;				// bx=d/16
			and ax, alpha2mask;
			and bx, alpha2mask;
			add ax, cx;				// ax=s/16 + s/8 = 6s/32
			add bx, dx;				// bx=d/16 + d/8 = 6d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=26d/32
			add ax, cx;				// ax=6s/32 + 26d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=7/32
	__declspec(naked) void _alpha_7(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 2;				// ax=s/4
			shr bx, 2;				// bx=d/4
			and ax, alpha4mask;
			and bx, alpha4mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/4
			mov dx, bx;				// dx=d/4
			shr cx, 3;				// cx=s/32
			shr dx, 3;				// dx=d/32
			and cx, alpha8mask;
			and dx, alpha8mask;
			sub ax, cx;				// ax=s/4 - s/32 = 7s/32
			sub bx, dx;				// bx=d/4 + d/32 = 7d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=25d/32
			add ax, cx;				// ax=7s/32 + 25d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=8/32
	__declspec(naked) void _alpha_8(void)
	{
		_asm
		{
			push cx;
			mov bx, [edi];			// bx=d
			shr ax, 2;				// ax=s/4
			mov cx, bx;				// cx=d
			and ax, alpha4mask;
			shr cx, 2;				// cx=d/4
			and cx, alpha4mask;
			sub bx, cx;
			pop cx;
			add ax, bx;				// ax=8s/32 + 24d/32
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}

	// result=��*src + dest - ��*dest; ��=9/32
	__declspec(naked) void _alpha_9(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 2;				// ax=s/4
			shr bx, 2;				// bx=d/4
			and ax, alpha4mask;
			and bx, alpha4mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/4
			mov dx, bx;				// dx=d/4
			shr ax, 3;				// ax=s/32
			shr bx, 3;				// bx=d/32
			and ax, alpha8mask;
			and bx, alpha8mask;
			add ax, cx;				// ax=s/32 + s/4 = 9s/32
			add bx, dx;				// bx=d/32 + d/4 = 9d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=23d/32
			add ax, cx;				// ax=9s/32 + 23d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}

	// result=��*src + dest - ��*dest; ��=10/32
	__declspec(naked) void _alpha_10(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 2;				// ax=s/4
			shr bx, 2;				// bx=d/4
			and ax, alpha4mask;
			and bx, alpha4mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/4
			mov dx, bx;				// dx=d/4
			shr ax, 2;				// ax=s/16
			shr bx, 2;				// bx=d/16
			and ax, alpha4mask;
			and bx, alpha4mask;
			add ax, cx;				// ax=s/16 + s/4 = 10s/32
			add bx, dx;				// bx=d/16 + d/4 = 10d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=22d/32
			add ax, cx;				// ax=10s/32 + 22d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}

	// result=��*src + dest - ��*dest; ��=11/32
	__declspec(naked) void _alpha_11(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 2;				// ax=s/4
			shr bx, 2;				// bx=d/4
			and ax, alpha4mask;
			and bx, alpha4mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/4
			mov dx, bx;				// dx=d/4
			shr ax, 2;				// ax=s/16
			shr bx, 2;				// bx=d/16
			and ax, alpha4mask;
			and bx, alpha4mask;
			add cx, ax;				// ax=s/4 + s/16 = 10s/32
			add dx, bx;				// bx=d/4 + d/16 = 10d/32
			shr ax, 1;				// ax=s/32
			shr bx, 1;				// bx=d/32
			and ax, alpha2mask;
			and bx, alpha2mask;
			add ax, cx;				// ax=s/4 + s/16 + s/32 = 11s/32
			add bx, dx;				// bx=d/4 + d/16 + d/32 = 11d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=21d/32
			add ax, cx;				// ax=11s/32 + 21d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}

	// result=��*src + dest - ��*dest; ��=12/32
	__declspec(naked) void _alpha_12(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 2;				// ax=s/4
			shr bx, 2;				// bx=d/4
			and ax, alpha4mask;
			and bx, alpha4mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/4
			mov dx, bx;				// dx=d/4
			shr ax, 1;				// ax=s/8
			shr bx, 1;				// bx=d/8
			and ax, alpha2mask;
			and bx, alpha2mask;
			add ax, cx;				// ax=s/8 + s/4 = 12s/32
			add bx, dx;				// bx=d/8 + d/4 = 12d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=20d/32
			add ax, cx;				// ax=12s/32 + 20d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=13/32
	__declspec(naked) void _alpha_13(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 2;				// ax=s/4
			shr bx, 2;				// bx=d/4
			and ax, alpha4mask;
			and bx, alpha4mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/4
			mov dx, bx;				// dx=d/4
			shr ax, 1;				// ax=s/8
			shr bx, 1;				// bx=d/8
			and ax, alpha2mask;
			and bx, alpha2mask;
			add cx, ax;				// ax=s/4 + s/8 = 12s/32
			add dx, bx;				// bx=d/4 + d/8 = 12d/32
			shr ax, 2;				// ax=s/32
			shr bx, 2;				// bx=d/32
			and ax, alpha4mask;
			and bx, alpha4mask;
			add ax, cx;				// ax=s/4 + s/8 + s/32 = 13s/32
			add bx, dx;				// bx=d/4 + d/8 + d/32 = 13d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=19d/32
			add ax, cx;				// ax=13s/32 + 19d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=14/32
	__declspec(naked) void _alpha_14(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 1;				// ax=s/2
			shr bx, 1;				// bx=d/2
			and ax, alpha2mask;
			and bx, alpha2mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/2
			mov dx, bx;				// dx=d/2
			shr cx, 3;				// cx=s/16
			shr dx, 3;				// dx=d/16
			and cx, alpha8mask;
			and dx, alpha8mask;
			sub ax, cx;				// ax=s/2 - s/16 = 14s/32
			sub bx, dx;				// bx=d/2 + d/16 = 14d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=18d/32
			add ax, cx;				// ax=14s/32 + 18d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=15/32
	__declspec(naked) void _alpha_15(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 1;				// ax=s/2
			shr bx, 1;				// bx=d/2
			and ax, alpha2mask;
			and bx, alpha2mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/2
			mov dx, bx;				// dx=d/2
			shr cx, 4;				// cx=s/32
			shr dx, 4;				// dx=d/32
			and cx, alpha16mask;
			and dx, alpha16mask;
			sub ax, cx;				// ax=s/2 - s/32 = 15s/32
			sub bx, dx;				// bx=d/2 + d/32 = 15d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=17d/32
			add ax, cx;				// ax=15s/32 + 17d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=16/32
	__declspec(naked) void _alpha_16(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 1;				// ax=s/2
			shr bx, 1;				// bx=d/2
			and ax, alpha2mask;
			and bx, alpha2mask;
			add ax, bx;				// ax=16s/32 + 16d/32
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=17/32
	__declspec(naked) void _alpha_17(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 1;				// ax=s/2
			shr bx, 1;				// bx=d/2
			and ax, alpha2mask;
			and bx, alpha2mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/2
			mov dx, bx;				// dx=d/2
			shr ax, 4;				// ax=s/32
			shr bx, 4;				// bx=d/32
			and ax, alpha16mask;
			and bx, alpha16mask;
			add ax, cx;				// ax=s/32 + s/2 = 17s/32
			add bx, dx;				// bx=d/32 + d/2 = 17d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=15d/32
			add ax, cx;				// ax=17s/32 + 15d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}



	// result=��*src + dest - ��*dest; ��=18/32
	__declspec(naked) void _alpha_18(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 1;				// ax=s/2
			shr bx, 1;				// bx=d/2
			and ax, alpha2mask;
			and bx, alpha2mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/2
			mov dx, bx;				// dx=d/2
			shr ax, 3;				// ax=s/16
			shr bx, 3;				// bx=d/16
			and ax, alpha8mask;
			and bx, alpha8mask;
			add ax, cx;				// ax=s/16 + s/2 = 18s/32
			add bx, dx;				// bx=d/16 + d/2 = 18d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=14d/32
			add ax, cx;				// ax=18s/32 + 14d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=19/32
	__declspec(naked) void _alpha_19(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 1;				// ax=s/2
			shr bx, 1;				// bx=d/2
			and ax, alpha2mask;
			and bx, alpha2mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/2
			mov dx, bx;				// dx=d/2
			shr ax, 3;				// ax=s/16
			shr bx, 3;				// bx=d/16
			and ax, alpha8mask;
			and bx, alpha8mask;
			add cx, ax;				// ax=s/2 + s/16 = 18s/32
			add dx, bx;				// bx=d/2 + d/16 = 18d/32
			shr ax, 1;				// ax=s/32
			shr bx, 1;				// bx=d/32
			and ax, alpha2mask;
			and bx, alpha2mask;
			add ax, cx;				// ax=s/2 + s/16 + s/32 = 19s/32
			add bx, dx;				// bx=d/2 + d/16 + d/32 = 19d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=13d/32
			add ax, cx;				// ax=19s/32 + 13d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=20/32
	__declspec(naked) void _alpha_20(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 1;				// ax=s/2
			shr bx, 1;				// bx=d/2
			and ax, alpha2mask;
			and bx, alpha2mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/2
			mov dx, bx;				// dx=d/2
			shr ax, 2;				// ax=s/8
			shr bx, 2;				// bx=d/8
			and ax, alpha4mask;
			and bx, alpha4mask;
			add ax, cx;				// ax=s/8 + s/2 = 20s/32
			add bx, dx;				// bx=d/8 + d/2 = 20d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=12d/32
			add ax, cx;				// ax=20s/32 + 12d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}



	// result=��*src + dest - ��*dest; ��=21/32
	__declspec(naked) void _alpha_21(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 1;				// ax=s/2
			shr bx, 1;				// bx=d/2
			and ax, alpha2mask;
			and bx, alpha2mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/2
			mov dx, bx;				// dx=d/2
			shr ax, 2;				// ax=s/8
			shr bx, 2;				// bx=d/8
			and ax, alpha4mask;
			and bx, alpha4mask;
			add cx, ax;				// ax=s/2 + s/8 = 20s/32
			add dx, bx;				// bx=d/2 + d/8 = 20d/32
			shr ax, 2;				// ax=s/32
			shr bx, 2;				// bx=d/32
			and ax, alpha4mask;
			and bx, alpha4mask;
			add ax, cx;				// ax=s/2 + s/8 + s/32 = 21s/32
			add bx, dx;				// bx=d/2 + d/8 + d/32 = 21d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=11d/32
			add ax, cx;				// ax=21s/32 + 11d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}



	// result=��*src + dest - ��*dest; ��=22/32
	__declspec(naked) void _alpha_22(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 1;				// ax=s/2
			shr bx, 1;				// bx=d/2
			and ax, alpha2mask;
			and bx, alpha2mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/2
			mov dx, bx;				// dx=d/2
			shr ax, 2;				// ax=s/8
			shr bx, 2;				// bx=d/8
			and ax, alpha4mask;
			and bx, alpha4mask;
			add cx, ax;				// ax=s/2 + s/8 = 20s/32
			add dx, bx;				// bx=d/2 + d/8 = 20d/32
			shr ax, 1;				// ax=s/16
			shr bx, 1;				// bx=d/16
			and ax, alpha2mask;
			and bx, alpha2mask;
			add ax, cx;				// ax=s/2 + s/8 + s/16 = 22s/32
			add bx, dx;				// bx=d/2 + d/8 + d/16 = 22d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=10d/32
			add ax, cx;				// ax=22s/32 + 10d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}



	// result=��*src + dest - ��*dest; ��=23/32
	__declspec(naked) void _alpha_23(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 1;				// ax=s/2
			shr bx, 1;				// bx=d/2
			and ax, alpha2mask;
			and bx, alpha2mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/2
			mov dx, bx;				// dx=d/2
			shr cx, 1;				// cx=s/4
			shr dx, 1;				// dx=d/4
			and cx, alpha2mask;
			and dx, alpha2mask;
			add ax, cx;				// ax=s/2 + s/4 = 24s/32
			add bx, dx;				// bx=d/2 + d/4 = 24d/32
			shr cx, 3;				// cx=s/32
			shr dx, 3;				// dx=d/32
			and cx, alpha8mask;
			and dx, alpha8mask;
			sub ax, cx;				// ax=s/2 + s/4 - s/32 = 23s/32
			sub bx, dx;				// bx=d/2 + d/4 - d/32 = 23d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=9d/32
			add ax, cx;				// ax=23s/32 + 9d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=24/32
	__declspec(naked) void _alpha_24(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 1;				// ax=s/2
			shr bx, 1;				// bx=d/2
			and ax, alpha2mask;
			and bx, alpha2mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/2
			mov dx, bx;				// dx=d/2
			shr ax, 1;				// ax=s/4
			shr bx, 1;				// bx=d/4
			and ax, alpha2mask;
			and bx, alpha2mask;
			add ax, cx;				// ax=s/4 + s/2 = 24s/32
			add bx, dx;				// bx=d/4 + d/2 = 24d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=8d/32
			add ax, cx;				// ax=24s/32 + 8d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=25/32
	__declspec(naked) void _alpha_25(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 1;				// ax=s/2
			shr bx, 1;				// bx=d/2
			and ax, alpha2mask;
			and bx, alpha2mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/2
			mov dx, bx;				// dx=d/2
			shr ax, 1;				// ax=s/4
			shr bx, 1;				// bx=d/4
			and ax, alpha2mask;
			and bx, alpha2mask;
			add cx, ax;				// ax=s/2 + s/4 = 24s/32
			add dx, bx;				// bx=d/2 + d/4 = 24d/32
			shr ax, 3;				// ax=s/32
			shr bx, 3;				// bx=d/32
			and ax, alpha8mask;
			and bx, alpha8mask;
			add ax, cx;				// ax=s/2 + s/4 + s/32 = 25s/32
			add bx, dx;				// bx=d/2 + d/4 + d/32 = 25d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=7d/32
			add ax, cx;				// ax=25s/32 + 7d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=26/32
	__declspec(naked) void _alpha_26(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			shr ax, 1;				// ax=s/2
			shr bx, 1;				// bx=d/2
			and ax, alpha2mask;
			and bx, alpha2mask;
			push cx;
			push dx;
			mov cx, ax;				// cx=s/2
			mov dx, bx;				// dx=d/2
			shr ax, 1;				// ax=s/4
			shr bx, 1;				// bx=d/4
			and ax, alpha2mask;
			and bx, alpha2mask;
			add cx, ax;				// ax=s/2 + s/4 = 24s/32
			add dx, bx;				// bx=d/2 + d/4 = 24d/32
			shr ax, 2;				// ax=s/16
			shr bx, 2;				// bx=d/16
			and ax, alpha4mask;
			and bx, alpha4mask;
			add ax, cx;				// ax=s/2 + s/4 + s/16 = 26s/32
			add bx, dx;				// bx=d/2 + d/4 + d/16 = 26d/32
			pop dx;
			mov cx, [edi];			// cx=d
			sub cx, bx;				// cx=6d/32
			add ax, cx;				// ax=26s/32 + 6d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=27/32
	__declspec(naked) void _alpha_27(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			push cx;
			shr bx, 3;				// bx=d/8
			push dx;
			and bx, alpha8mask;
			mov cx, ax;				// cx=s
			mov dx, bx;				// dx=d/8
			shr cx, 3;				// cx=s/8
			shr dx, 2;				// dx=d/32
			and cx, alpha8mask;
			and dx, alpha4mask;
			sub ax, cx;				// ax=s - s/8 = 28s/32
			add bx, dx;				// bx=d/8 + d/32 = 5d/32
			shr cx, 2;				// cx=s/32
			pop dx;
			and cx, alpha4mask;
			sub ax, cx;				// ax=s - s/8 - s/32 = 27s/32
			add ax, bx;				// ax=27s/32 + 5d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=28/32
	__declspec(naked) void _alpha_28(void)
	{
		_asm
		{
			mov bx, ax;				// ax=s
			shr bx, 3;				// bx=s/8
			and bx, alpha8mask;
			sub ax, bx;				// ax=s - s/8 = 7s/8
			mov bx, [edi];			// bx=d
			shr bx, 3;				// bx=d/8
			and bx, alpha8mask;
			add ax, bx;				// ax=28s/32 + 4d/32
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=29/32
	__declspec(naked) void _alpha_29(void)
	{
		_asm
		{
			mov bx, [edi];			// bx=d
			push cx;
			shr bx, 4;				// bx=d/16
			push dx;
			and bx, alpha16mask;
			mov cx, ax;				// cx=s
			mov dx, bx;				// dx=d/16
			shr cx, 4;				// cx=s/16
			shr dx, 1;				// dx=d/32
			and cx, alpha16mask;
			and dx, alpha2mask;
			sub ax, cx;				// ax=s - s/16 = 30s/32
			add bx, dx;				// bx=d/16 + d/32 = 3d/32
			shr cx, 1;				// cx=s/32
			pop dx;
			and cx, alpha2mask;
			sub ax, cx;				// ax=s - s/16 - s/32 = 29s/32
			add ax, bx;				// ax=29s/32 + 3d/32
			pop cx;
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=30/32
	__declspec(naked) void _alpha_30(void)
	{
		_asm
		{
			mov bx, ax;				// ax=s
			shr bx, 4;				// bx=s/16
			and bx, alpha16mask;
			sub ax, bx;				// ax=s - s/16 = 15s/16
			mov bx, [edi];			// bx=d
			shr bx, 4;				// bx=d/16
			and bx, alpha16mask;
			add ax, bx;				// ax=30s/32 + 2d/32
			mov [edi], ax;
			add edi, 2;
			ret;
		}
	}


	// result=��*src + dest - ��*dest; ��=31/32
	__declspec(naked) void _alpha_31(void)
	{
		//	_asm
		//	{
		//		mov bx, ax;				// ax=s
		//		shr bx, 5;				// bx=s/32
		//		and bx, alpha32mask;
		//		sub ax, bx;				// ax=s - s/32 = 31s/32
		//		mov bx, [edi];			// bx=d
		//		shr bx, 5;				// bx=d/16
		//		and bx, alpha32mask;
		//		add ax, bx;				// ax=31s/32 + 1d/32
		//		mov [edi], ax;
		//		add edi, 2;
		//		ret;
		//	}
		// ���ǽ���=31/32��������ȫ��͸��
		_asm
		{
			mov [edi], ax;
			add edi, 2;
			RET;
		}
	}

	// result=��*src + dest - ��*dest; ��=32/32
	__declspec(naked) void _alpha_32(void)
	{
		_asm
		{
			mov [edi], ax;
			add edi, 2;
			RET;
		}
	}

	typedef void (*TRANS_DRAW_FUNC)(void);
	TRANS_DRAW_FUNC alpha_level[] = 
	{_alpha_0,_alpha_1,_alpha_2,_alpha_3,_alpha_4,_alpha_5,_alpha_6,_alpha_7,
	_alpha_8,_alpha_9,_alpha_10,_alpha_11,_alpha_12,_alpha_13,_alpha_14,_alpha_15,
	_alpha_16,_alpha_17,_alpha_18,_alpha_19,_alpha_20,_alpha_21,_alpha_22,_alpha_23,
	_alpha_24,_alpha_25,_alpha_26,_alpha_27,_alpha_28,_alpha_29,_alpha_30,_alpha_31};

	/*
	dx: Ŀ��x
	dy: Ŀ��y
	w: ͼƬ���
	h: ͼƬ�߶�
	pitch: Ŀ��ͼƬ��pitchֵ
	ptr: Ŀ��ͼƬ�ĵ�ַ
	color: ��ɫ������(������ͼƬ�Դ��ģ�Ҳ��������紫���)
	bits: ԴSFP��ͼ�����ݵ�ַ
	*/
	void __stdcall blit_rle_alpha(int dx,int dy,int w,int h,int pitch,uchar* ptr,WPixel* color,uchar* bits)
	{
		WPixel* startptr = (WPixel*)(ptr + dy * pitch + (dx << 1));
		__asm
		{
			xor eax, eax;		// i=0
			xor ebx, ebx;		// j=0
			mov esi, bits;		// Դ����
			mov edi, startptr;	// Ŀ������
			add esi, 2;
			cld;
			align 4;
loops1:
			cmp ebx, w;			// j >= w ?
			jnl next_line;		// ������һ��

			xor ecx, ecx;
			mov cl, [esi];		// ecx <-- [esi]
			cmp ecx, 0x40;
			jl mask_handle;		// �ǣ���jump��mask_handle
			cmp ecx, 0x80;
			jl shadow_handle;
			cmp ecx, 0xc0;
			jl alpha_8_handle;

			// normal handle
			and cl, 0x3f;
			inc esi;			// nPos += 1
			inc cl;				// rep_count = cl + 1
			add ebx, ecx;		// j += rep_count
			push eax;
			push ebx;
loops2:
			lodsw;				// ax = [esi]
			movzx edx, al;		// ��ȡ�ظ���ɫ����ɫ����index
			movzx ebx, ah;		// alpha
			shl edx, 1;			// ��Ϊ��ɫ����һ����ɫ��2���ֽڣ�����Ҫ��index*2
			add edx, color;		// �õ���ɫ���ж�Ӧ������λ��
			mov ax,[edx];		// ��ȡָ������ɫ
			mov edx, offset alpha_level[0];
			shl ebx, 2;
			dec cl;				// rep_count--
			add edx, ebx;
			call [edx];
			cmp cl, 0;			// rep_count > 0 ?
			jg loops2;
			pop ebx;
			pop eax;
			jmp loops1;

next_line:
			mov ecx, w;			// ��ȡw
			shl ecx, 1;			// w*2
			mov edx, pitch;		// ��ȡpitch
			sub edx, ecx;		// delta = pitch-2*w
			add edi, edx;		// edi += delta
			inc eax;			// i++
			cmp eax, h;			// �����н�����i>=h��
			jnl done;			// all done
			xor ebx, ebx;		// j=0
			add esi, 2;			// �����б�־
			jmp loops1;


mask_handle: // ͸������
			inc cl;				// rep_count = cl + 1
			inc esi;			// Դָ���ƶ�1���ֽ�
			add ebx, ecx;		// j+=rep_count
			shl ecx, 1;			// rep_count*=2
			add edi, ecx;		// Ŀ��ָ������͸��������
			jmp loops1;

shadow_handle: // Ӱ�Ӵ���
			sub cl, 0x3f;
			add ebx, ecx;
			push eax;
			push ebx;
			inc esi;
			lodsb;				// al = [esi]
			movzx ebx, al;
			mov edx, offset alpha_level[0];
			shl ebx, 2;
			add edx, ebx;

			// modify by pk,2003.7.8�����ܽ���ɫĬ��Ϊ0����Ϊ���ܵ�ɫ�����б�������
			mov ebx, color;
			mov ax, [ebx];	// �õ���ɫ
loops4:	push eax;
			dec cl;				// rep_count--
			call [edx];
			pop eax;
			cmp cl, 0;			// rep_count > 0 ?
			jg loops4;

			/* ԭʼ���룺
			loops4:	xor eax, eax;		
			dec cl;				// rep_count--
			call [edx];
			cmp cl, 0;			// rep_count > 0 ?
			jg loops4;*/

			pop ebx;
			pop eax;
			jmp loops1;

alpha_8_handle:
			sub cl, 0x7f;
			push eax;
			add ebx, ecx;
			push ebx;
			inc esi;
			mov ebx, color;
loops3:	xor edx, edx;		// edx=0
			mov dl, [esi];		// dl<--index
			shl edx, 1;			// edx=index*2��Ϊ��ɫ����һ����ɫ��2���ֽڣ�����Ҫ��
			add edx, ebx;		// edx=&color[index]�õ���ɫ���ж�Ӧ��������ɫ��ַ
			mov ax,[edx];		// ax=color[index]��ȡָ������ɫ
			mov [edi], ax;
			inc esi;
			add edi, 2;
			dec cl;
			cmp cl, 0;
			jg loops3;
			pop ebx;
			pop eax;
			jmp loops1;

done:
			nop
		}
	}

	/** @see blit_rle_alpha
	*/
	void __stdcall blit_rle_alpha_c(int w,int h,uchar* dst,WPixel* color,uchar* src)
	{
		uchar* pDst = dst;
		uchar* pSrc = src;
		for(int i = 0;i < h;i++)
		{
			uchar *pLine = pDst + i * 4 * w;
			uchar *pNow = pLine;
			pLine += 4 * w;
			pSrc += 2;
			while(pNow < pLine)
			{
				uchar num = *pSrc;
				if(num < 0x40)
				{
					num++;
					pSrc++;
					//for(int j = 0;j < num;j++)
					//{
					//	*pNow++ = 0;
					//	*pNow++ = 0;
					//	*pNow++ = 0;
					//	*pNow++ = 0;
					//}
					memset(pNow,0,4 * num);
					pNow += 4 * num;
				}
				else if(num < 0x80)
				{
					num -= 0x3f;
					pSrc++;
					uchar data = *pSrc++;
					WPixel c = color[0];
					for(char j = 0;j < num;j++)
					{
						*pNow++ = c.blue << 3;
						*pNow++ = c.green << 2;
						*pNow++ = c.red << 3;
						*pNow++ = data << 3;	//data * 256 / 32
					}
				}
				else if(num < 0xc0)
				{
					num -= 0x7f;
					pSrc++;
					for(char j = 0;j < num;j++)
					{
						uint data = *pSrc++;
						WPixel c = color[data];

						*pNow++ = c.blue << 3;
						*pNow++ = c.green << 2;
						*pNow++ = c.red << 3;
						*pNow++ = 0xFF;
					}
				}
				else
				{
					num &= 0x3f;
					pSrc++;
					num++;
					for(char j = 0;j < num;j++)
					{
						uchar cIndex = *pSrc++;
						uchar a = *pSrc++;
						WPixel c = color[cIndex];
						*pNow++ = c.blue << 3;
						*pNow++ = c.green << 2;
						*pNow++ = c.red << 3;
						*pNow++ = a << 3;
					}
				}
			}
		}
	}

	void blit_rle_copy(int dx,int dy,int w,int h,int pitch,uchar* ptr,WPixel* color,uchar* bits)
	{
		WPixel* startptr = (WPixel*)(ptr + dy * pitch + (dx << 1));

		_asm
		{
			xor eax, eax;		// i=0
			xor ebx, ebx;		// j=0
			mov esi, bits;		// Դ����
			mov edi, startptr;	// Ŀ������
			add esi, 2;
			align 4;

lineloops:
			cmp ebx, w;			// һ�н�����(j<w)?
			jnl next_line;

			xor ecx,ecx;		// ecx=0
			mov cl, [esi];		// ��Դ�ж�ȡһ���ֽڵ�cl
			cmp ecx, 0x80;		// �Ƿ���͸����־��
			jl mask_handle;		// �ǣ���jump��mask_handle
			cmp ecx, 0xc0;		// �Ƿ����ظ�����ɫ��
			jl repeat_handle;	// �ǣ���jump��repeat_handle

			//normal_handle:
			sub cl, 0xbf;
			add esi, 1;			// nPos += 1
loops2:	xor edx, edx;
			mov dl, [esi];		// ��ȡ��������ɫ���е���ɫ����index
			shl edx, 1;			// ��Ϊ��ɫ����һ����ɫ��2���ֽڣ�����Ҫ��index*2
			add edx, color;		// �õ���ɫ���ж�Ӧ������λ��
			mov dx,[edx];		// ��ȡָ������ɫ
			mov [edi],dx;		// д����ɫ
			add edi, 2;			// Ŀ��ָ���2
			inc ebx;			// j++
			inc esi;			// nPos++
			//dec ecx;			// rep_count--
			//cmp ecx, 0;			// rep_count > 0 ?
			//jg loops2;
			loop loops2;
			jmp lineloops;

next_line:
			mov ecx, w;			// ��ȡw
			shl ecx, 1;			// w*2
			mov edx, pitch;		// ��ȡpitch
			sub edx, ecx;		// delta = pitch-2*w
			add edi, edx;		// edi += delta
			add eax, 1;			// i++
			cmp eax, h;			// �����н�����
			jnl done;			// all done
			xor ebx, ebx;		// j=0
			add esi, 2;
			jmp lineloops;


mask_handle: // ����͸��
			inc cl;
			add ebx, ecx;		// j+=ecx
			test ecx, 0x0001;	// �Ƿ�����?
			jnz pre_handle_one_pixel_for_mask;

memset16_for_mask:
			push eax;			// ������ǰ��ֵ
			mov eax, 0xf81ff81f;// ��ȡҪ����ֵ,һ�δ���2������
			shr ecx, 1			// �����Ŀ����2
				rep stosd			// �ظ�����ڴ洮
				pop eax;			// �ָ���ǰֵ

memset16_done_for_mask:
			inc esi;			// Դָ���ƶ�1���ֽ�
			jmp lineloops;

pre_handle_one_pixel_for_mask:
			mov word ptr [edi],0xf81f;	// д����ɫ
			add edi, 2;					// Ŀ���ַ+2
			cmp ecx, 1;					// �������Ҫ�����һ��
			jz  memset16_done_for_mask; // �򲻽����ڴ���䣬��Ϊǰ���Ѿ������
			jmp memset16_for_mask;		// 16bit�ڴ����

repeat_handle:
			xor edx, edx;		// edx=0
			sub cl, 0x7f;		// cl = cl - 127
			mov dl, [esi+1];	// ��ȡ�ظ���ɫ����ɫ����dl
			shl edx, 1;			// ��Ϊ��ɫ����һ����ɫ��2���ֽڣ�����Ҫ������*2
			add edx, color;		// �õ���ɫ���ж�Ӧ������λ��
			add ebx, ecx;		// j+=ecx
			test ecx, 0x0001;	// �Ƿ�����?
			jnz pre_handle_one_pixel;

memset16:
			push eax;			// ������ǰ��ֵ
			mov ax, [edx]		// ��ȡҪ����ֵ
			shl eax, 16			// ���ֵ����16bit
				add ax, [edx]		// һ�δ���2������
				shr ecx, 1			// �����Ŀ����2
					rep stosd			// �ظ�����ڴ洮
					pop eax;			// �ָ���ǰֵ

memset16_done:
				add esi, 2;			// Դָ���ƶ�2���ֽ�
				jmp lineloops;

pre_handle_one_pixel:
				push eax;
				mov ax,[edx];		// ��ȡָ������ɫ
				mov [edi],ax;		// д����ɫ
				pop eax;
				add edi, 2;			// Ŀ���ַ+2
				cmp ecx, 1;			// �������Ҫ�����һ��
				jz  memset16_done;  // �򲻽����ڴ���䣬��Ϊǰ���Ѿ������
				jmp memset16;		// 16bit�ڴ����

done:
				nop
		}
	}

	bool ImageCodecSfp::decode(xs::Stream* input,ImageData& data,const void *p1,const void *p2) const
	{
		if(input->getLength() < sizeof(RLEHEADER))
		{
			Error("Invalid SPF file!\n");
			return false;
		}

		RLEHEADER h;
		input->read(&h,sizeof(h));

		data.height = h.dwHeight;
		data.width = h.dwWidth;
		data.depth = 1;
		data.size = 0;
		data.num_mipmaps = 1;
		data.flags = 0;
		data.format = PF_UNKNOWN;
		data.pData = 0;

		uint paletteSize = h.nUseColor << 1;
		uint dataSize = h.dwTotalSize - h.dwDataOffset;

		if(paletteSize > 0)
		{
			input->read((void*)m_defaultPal,paletteSize);
		}
		else if(p1 && p2)
		{
			memcpy((void*)m_defaultPal,p1,(size_t)p2);
		}

		if(!dataSize)
		{
			Error("No SFP image data\n");
			return false;
		}
		uchar *pData = new uchar[dataSize];
		input->read(pData,dataSize);

		if(h.bHaveAlphaChannel)
#if 1
		{
			uint size = data.width * data.height * 4;
			uchar *pDest = new uchar[size];
			blit_rle_alpha_c(data.width,data.height,pDest,(WPixel*)m_defaultPal,pData);

			data.size = size;
			data.format = PF_A8R8G8B8;
			data.pData = pDest;
		}
#else
		{
			uint size = data.width * data.height * 2;
			ushort *pAlpha = new ushort[data.width * data.height];
			uchar *pDest = (uchar*)pAlpha;

			WPixel cAlpha = WPixel(255,0,255);
			for(uint i = 0;i < data.height;i++)
				for(uint j = 0;j < data.width;j++)
				{
					*pAlpha++ = cAlpha.color;
				}
				blit_rle_alpha(0,0,data.width,data.height,data.width * 2,pDest,(WPixel*)m_defaultPal,pData);

				pAlpha = (ushort*)pDest;
				for(uint i = 0;i < data.height;i++)
					for(uint j = 0;j < data.width;j++)
					{
						WPixel c;
						c.color = *pAlpha;
						if(c.color == cAlpha.color)
						{
							*pAlpha = MAKE1555WORD(0,c.red << 3,c.green << 2,c.blue << 3);
						}
						else
						{
							*pAlpha = MAKE1555WORD(1,c.red << 3,c.green << 2,c.blue << 3);
						}
						pAlpha++;
					}

					data.size = size;
					data.format = PF_A1R5G5B5;
					data.pData = pDest;
		}
#endif
		else
		{
			uint size = data.width * data.height * 2;
			uchar *pDest = (uchar*)new ushort[data.width * data.height];
			memset(pDest,0xFF,size);
			blit_rle_copy(0,0,data.width,data.height,data.width * 2,pDest,(WPixel*)m_defaultPal,pData);

			data.size = size;
			data.format = PF_R5G6B5;
			data.pData = pDest;
		}

		delete[] pData;

		return true;
	}

	bool ImageCodecSfp::code(void) const
	{
		Error("Code to SFP Not Implemented Yet!");
		return false;
	}

	bool ImageCodecSfp::codeToFile(xs::FileStream&,const ImageData& data) const
	{
		Error("Code to SFP Not Implemented Yet!");
		return false;
	}

}