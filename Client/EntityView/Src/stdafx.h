// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

// ������뽫λ������ָ��ƽ̨֮ǰ��ƽ̨��ΪĿ�꣬���޸����ж��塣
// �йز�ͬƽ̨��Ӧֵ��������Ϣ����ο� MSDN��
#ifndef WINVER				// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define WINVER 0x0501		// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif

#ifndef _WIN32_WINNT		// ����ʹ���ض��� Windows XP ����߰汾�Ĺ��ܡ�
#define _WIN32_WINNT 0x0501	// ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif						

#ifndef _WIN32_WINDOWS		// ����ʹ���ض��� Windows 98 ����߰汾�Ĺ��ܡ�
#define _WIN32_WINDOWS 0x0410 // ����ֵ����Ϊ�ʵ���ֵ����ָ���� Windows Me ����߰汾��ΪĿ�ꡣ
#endif

#ifndef _WIN32_IE			// ����ʹ���ض��� IE 6.0 ����߰汾�Ĺ��ܡ�
#define _WIN32_IE 0x0600	// ����ֵ����Ϊ��Ӧ��ֵ���������� IE �������汾��
#endif

#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�:
#include <windows.h>



// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "Base.h"
#pragma comment(lib, MAKE_DLL_LIB_NAME(xs_com))
#pragma comment(lib, MAKE_DLL_LIB_NAME(xs_gui))
#define new RKT_NEW

#include "Re.h"
#include "IResourceManager.h"
using namespace xs;

#if !defined (SAFE_RELEASE)
#define SAFE_RELEASE(p)				{ if((p) != NULL) { (p)->Release(); (p)=NULL; } }
#endif

#if !defined (SAFE_DELETE)
#define SAFE_DELETE(p)				{ if((p) != NULL) { delete (p);     (p)=NULL; } }
#endif

#if !defined (SAFE_DELETEARRAY)
#define SAFE_DELETEARRAY(p)			{ if((p) != NULL) { delete [](p);    (p)=NULL; } }
#endif


#include "IGlobalClient.h"
#include "ISceneManager2.h"
#include "ISchemeEngine.h"
#include "IEntityClient.h"

#include "Direction.h"
#include "MapTable.h"

#include "DGlobalGame.h"
#include "DEntityProp.h"
#include "DGlobalMisc.h"
#include "net.h"
#include "DGlobalMessage.h"
#include "HelperFunc.h"
#include "DGlobalEvent.h"


enum UpdateOption
{
	updatePosition	=	0x1,	/// λ��
	updateAngle		=	0x2,	/// �Ƕ�
	updateAnimation	=	0x4,	/// ����
	updateAniSpeed	=	0x8,	/// �����ٶ�
	updateColor		=	0x10,	/// ��ɫ
	updateScale		=	0x20,	/// ����
	updateFadeIn	=	0x40,	/// ����
	updateFadeOut	=	0x80,	/// ����
	updatePart		=	0x100,	/// ����
	updateRidePet	=	0x200,	/// �������
	updatePetdie    =   0x400,  /// ��������(wan)
	updateJump      =   0x800,  /// ��Ծ
	//updateDelete	=	0x200,	/// ɾ���Լ�
//	updateMoveSpeed	=	0x400,	/// �ƶ��ٶ�
};

#define FADE_ALPHA	0.001f

