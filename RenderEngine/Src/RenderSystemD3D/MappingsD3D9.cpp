#include "StdAfx.h"
#include "MappingsD3D9.h"

namespace xs
{


	//��ȡbuffer��Ӧ��D3D9ʹ�÷�ʽ
	DWORD	MappingsD3D9::getBufferUsage( BufferUsage usage)
	{
		//���ÿ���BU_DISCARDABLE
		DWORD ret = 0;
		// BU_DYNAMIC
		if( (usage & BU_DYNAMIC))
		{
			ret |= D3DUSAGE_DYNAMIC;
		}

		if( usage & BU_WRITE_ONLY)
		{
			ret |= D3DUSAGE_WRITEONLY;
		}
		return ret;

	}

	D3DPOOL	MappingsD3D9::getPoolTypeByBufferUsage( BufferUsage usage)
	{
		//ֻ�����ַ�ʽ������Դ��Default Pool �� Managed Pool
		//�����Դ�ǿɶ����ģ���ʹ��Default Pool 
		//����ʹ��Managed Pool
		if( usage & BU_DYNAMIC)
			return D3DPOOL_DEFAULT;
		else
			return D3DPOOL_MANAGED;
	}

	//�����������ͻ�ȡ��Ӧ�ĸ�ʽ
	D3DFORMAT MappingsD3D9::getIndexTypeFormat(IndexType type)
	{
		if( type == IT_16BIT)
			return D3DFMT_INDEX16;
		else 
			return D3DFMT_INDEX32;
	}
	//�����������ͻ�ȡ��Ӧ��������С
	UINT MappingsD3D9::getIndexTypeSize(IndexType type)
	{
		if( type == IT_16BIT)
			return sizeof(WORD);
		else 
			return sizeof(DWORD);	
	}

	//��ȡD3D9��Ӧ��ͼԪ����
	D3DPRIMITIVETYPE MappingsD3D9::getPrimptiveType( PrimitiveType type)
	{
		switch (type) 
		{
		case PT_LINES:
			return D3DPT_LINELIST;
			break;

		case PT_LINE_STRIP:
			return D3DPT_LINESTRIP;
			break;

		case PT_LINE_LOOP: //û�з�յ��ߣ����ߴ���ʾ
			return D3DPT_LINESTRIP;
			break;

		case PT_TRIANGLES:
			return D3DPT_TRIANGLELIST;
			break;

		case PT_TRIANGLE_STRIP:
			return D3DPT_TRIANGLESTRIP;
			break;

		case PT_TRIANGLE_FAN:
			return D3DPT_TRIANGLEFAN;
			break;

		case PT_POINTS:
			return D3DPT_POINTLIST;
			break;

		case PT_QUADS:
			return D3DPT_TRIANGLELIST;
			break;
		}
		//��Ҫ������
		return D3DPT_LINESTRIP;
	}

	//��ȡD3D9ͼԪ���ͺͶ���������Ӧ��ͼԪ����
	UINT MappingsD3D9::getPrimitiveCount(PrimitiveType type, uint indexCount)
	{
		switch (type) 
		{
		case PT_LINES:
			return indexCount/2;
			break;

		case PT_LINE_STRIP:
			if( indexCount < 2 )
				return 0;
			else
				return indexCount -1;
			break;

		case PT_TRIANGLES:
			return indexCount/3;
			break;

		case PT_TRIANGLE_STRIP:
			if( indexCount < 3)
				return 0;
			else 
				return indexCount - 2;
			break;

		case PT_TRIANGLE_FAN:
			if( indexCount < 3)
				return 0;
			else 
				return indexCount - 2;
			break;

		case PT_POINTS:
			return indexCount;
			break;

		//ԭ����֧��
		case PT_LINE_LOOP:
		case PT_QUADS:
		case PT_QUAD_STRIP:
		default:
			return 0;
		}
	}

	//��ȡ��Ӧ��D3D9����
	D3DXMATRIX MappingsD3D9::getMatrix( const xs::Matrix4 & mat)
	{
		//D3D9���д洢��
		return D3DXMATRIX(
            mat[0][0], mat[1][0], mat[2][0], mat[3][0],
            mat[0][1], mat[1][1], mat[2][1], mat[3][1],
            mat[0][2], mat[1][2], mat[2][2], mat[3][2],
            mat[0][3], mat[1][3], mat[2][3], mat[3][3]);	
	}
	//��ȡD3D9�����Ӧ�ı��������
	xs::Matrix4 MappingsD3D9::getMatrix(const D3DXMATRIX & mat)
	{
		//D3D9���д洢��
		return Matrix4(
            mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
            mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
            mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
            mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]);
	}

	//��ȡD3D9���ղ���
	void MappingsD3D9::getLight(/*const */xs::Light & lit, D3DLIGHT9 & d3d9lit)
	{
		//����
		switch(lit.getType())
		{
		case LT_POINT:
			d3d9lit.Type = D3DLIGHT_POINT;
			break;
		case LT_DIRECTIONAL:
			d3d9lit.Type = D3DLIGHT_DIRECTIONAL;
			break;
		case LT_SPOTLIGHT:
			d3d9lit.Type = D3DLIGHT_SPOT;
			break;
		}

		//λ��
		Vector3 pos = lit.getPosition();
		d3d9lit.Position.x = pos.x;
		d3d9lit.Position.y = pos.y;
		d3d9lit.Position.z = pos.z;
		
		//����
		Vector3 dir = lit.getDirection();
		d3d9lit.Direction.x = dir.x;
		d3d9lit.Direction.y = dir.y;
		d3d9lit.Direction.z = dir.z;

		//������
		xs::ColorValue ambient = lit.getAmbientColor();
		d3d9lit.Ambient.a = ambient.a;
		d3d9lit.Ambient.r = ambient.r;
		d3d9lit.Ambient.g = ambient.g;
		d3d9lit.Ambient.b = ambient.b;

		//ɢ���
		xs::ColorValue diffuse = lit.getDiffuseColor();
		d3d9lit.Diffuse.a = diffuse.a;
		d3d9lit.Diffuse.r = diffuse.r;
		d3d9lit.Diffuse.g = diffuse.g;
		d3d9lit.Diffuse.b = diffuse.b;

		//�����
		xs::ColorValue specular = lit.getSpecularColor();
		d3d9lit.Specular.a = specular.a;
		d3d9lit.Specular.r = specular.r;
		d3d9lit.Specular.g = specular.g;
		d3d9lit.Specular.b = specular.b;

		//˥��
		d3d9lit.Attenuation0 = lit.getAttenuationConstant();
		d3d9lit.Attenuation1 = lit.getAttenuationLinear();
		d3d9lit.Attenuation2 = lit.getAttenuationQuadric();
		d3d9lit.Range = lit.getAttenuationRange();

		//�۹��Ч��
		d3d9lit.Theta = lit.getSpotlightInnerAngle().valueRadians();
		d3d9lit.Phi = lit.getSpotlightOuterAngle().valueRadians(); 
		d3d9lit.Falloff = lit.getSpotlightFalloff();

		return;
	}
	//��ȡ������ղ���
	void MappingsD3D9::getLight(const D3DLIGHT9 & d3d9lit, xs::Light  & lit)
	{
		//����
		switch(d3d9lit.Type)
		{
		case D3DLIGHT_POINT :
			lit.setType(LT_POINT);
			break;
		case D3DLIGHT_DIRECTIONAL :
			lit.setType(LT_DIRECTIONAL);
			break;
		case D3DLIGHT_SPOT :
			lit.setType(LT_SPOTLIGHT);
			break;
		}

		//λ��
		lit.setPosition( d3d9lit.Position.x, d3d9lit.Position.y, d3d9lit.Position.z);
		
		//����
		lit.setDirection( d3d9lit.Direction.x, d3d9lit.Direction.y, d3d9lit.Direction.z);

		//������
		lit.setAmbientColor( xs::ColorValue(d3d9lit.Ambient.r, d3d9lit.Ambient.g, d3d9lit.Ambient.b, d3d9lit.Ambient.a) );

		//ɢ���
		lit.setDiffuseColor( xs::ColorValue(d3d9lit.Diffuse.r, d3d9lit.Diffuse.g, d3d9lit.Diffuse.b, d3d9lit.Diffuse.a) );

		//�����
		lit.setSpecularColor( xs::ColorValue(d3d9lit.Specular.r, d3d9lit.Specular.g, d3d9lit.Specular.b, d3d9lit.Specular.a) );

		//˥��
		lit.setAttenuation(d3d9lit.Range, d3d9lit.Attenuation0, d3d9lit.Attenuation1,  d3d9lit.Attenuation2 );

		//�۹��Ч��
#ifndef RE_FORCE_ANGLE_TYPES
		if (lit.getType() == LT_SPOTLIGHT)
		{
			lit.setSpotlightRange( d3d9lit.Theta, d3d9lit.Phi, d3d9lit.Falloff);
		}		
#endif
		return;		
	}

	//��D3D9ȡ���ģʽ
	D3DFILLMODE MappingsD3D9::getFillMode( FillMode fm)
	{
		switch( fm)
		{
		case FM_POINTS:
			return D3DFILL_POINT;
		case FM_WIREFRAME:
			return D3DFILL_WIREFRAME;
		case FM_SOLID:
			return D3DFILL_SOLID;
		}
		//���ᵽ����
		return D3DFILL_SOLID;
	}

	//��ȡD3D9�����ѡģʽ
	D3DCULL MappingsD3D9::getCullingMode(CullingMode cm)
	{
		switch( cm)
		{
		case CULL_NONE:
			return D3DCULL_NONE;
		case CULL_CLOCKWISE:
			return D3DCULL_CW;
		case CULL_COUNTERCLOCKWISE:
			return D3DCULL_CCW;
		}
		//���ᵽ����
		return D3DCULL_NONE;
	}

	//��ȡD3D9���ģʽ
	D3DFOGMODE MappingsD3D9::getFogMode(FogMode fm)
	{
		switch( fm)
		{
		case FOG_NONE:
			return D3DFOG_NONE;
		case FOG_LINEAR:
			return D3DFOG_LINEAR;
		case FOG_EXP:
			return D3DFOG_EXP;
		case FOG_EXP2:
			return D3DFOG_EXP2;
		}
		//���ᵽ����
		return D3DFOG_EXP;
	}

	//��ȡD3D9��ȼ�⺯��
	D3DCMPFUNC MappingsD3D9::getDepthFunc(CompareFunction cf)
	{
		switch( cf)
		{
		case CMPF_ALWAYS_FAIL:
			return  D3DCMP_NEVER;
		case CMPF_ALWAYS_PASS:
			return D3DCMP_ALWAYS;
		case CMPF_LESS:
			return D3DCMP_LESS;
		case CMPF_LESS_EQUAL:
			return D3DCMP_LESSEQUAL;
		case CMPF_EQUAL:
			return D3DCMP_EQUAL;
		case CMPF_GREATER_EQUAL:
			return D3DCMP_GREATEREQUAL;
		case CMPF_GREATER:
			return D3DCMP_GREATER;
		}
		//���ᵽ����
		return D3DCMP_LESS;
	}

	//��ȡD3D9Alpha��⺯��
	D3DCMPFUNC MappingsD3D9::getAlphaFunc(CompareFunction cf)
	{
		switch( cf)
		{
		case CMPF_ALWAYS_FAIL:
			return  D3DCMP_NEVER;
		case CMPF_ALWAYS_PASS:
			return D3DCMP_ALWAYS;
		case CMPF_LESS:
			return D3DCMP_LESS;
		case CMPF_LESS_EQUAL:
			return D3DCMP_LESSEQUAL;
		case CMPF_EQUAL:
			return D3DCMP_EQUAL;
		case CMPF_GREATER_EQUAL:
			return D3DCMP_GREATEREQUAL;
		case CMPF_GREATER:
			return D3DCMP_GREATER;
		}
		//���ᵽ����
		return D3DCMP_ALWAYS;
	}

	//��ȡD3D9ģ���⺯��
	D3DCMPFUNC MappingsD3D9::getStencilFunc(CompareFunction cf)
	{
		switch( cf)
		{
		case CMPF_ALWAYS_FAIL:
			return  D3DCMP_NEVER;
		case CMPF_ALWAYS_PASS:
			return D3DCMP_ALWAYS;
		case CMPF_LESS:
			return D3DCMP_LESS;
		case CMPF_LESS_EQUAL:
			return D3DCMP_LESSEQUAL;
		case CMPF_EQUAL:
			return D3DCMP_EQUAL;
		case CMPF_GREATER_EQUAL:
			return D3DCMP_GREATEREQUAL;
		case CMPF_GREATER:
			return D3DCMP_GREATER;
		}
		//���ᵽ����
		return D3DCMP_ALWAYS;
	}

	//��ȡD3D9ģ�������ʽ
	D3DSTENCILOP  MappingsD3D9::getStencilOp( StencilOperation so)
	{
		switch ( so )
		{
		case SOP_KEEP:
			return D3DSTENCILOP_KEEP;
		case SOP_ZERO:
			return D3DSTENCILOP_ZERO;
		case SOP_REPLACE:
			return D3DSTENCILOP_REPLACE;
		case SOP_INCREMENT:
			return D3DSTENCILOP_INCRSAT;
		case SOP_DECREMENT:
			return D3DSTENCILOP_DECRSAT;
		case SOP_INCREMENT_WRAP:
			return D3DSTENCILOP_INCR;
		case SOP_DECREMENT_WRAP:
			return D3DSTENCILOP_DECR;
		case SOP_INVERT:
			return D3DSTENCILOP_INVERT;
		}
		//���ᵽ����
		return  D3DSTENCILOP_KEEP;
	}


	//��ȡD3D9 alpha��Ϸ�ʽ
	D3DBLEND  MappingsD3D9::getBlendFactor(SceneBlendFactor factor)
	{
		switch( factor)
		{
		case SBF_ONE:
			return D3DBLEND_ONE;
		case SBF_ZERO:
			return D3DBLEND_ZERO;
		case SBF_DEST_COLOR:
			return D3DBLEND_DESTCOLOR;
		case SBF_SOURCE_COLOR:
			return D3DBLEND_SRCCOLOR;
		case SBF_ONE_MINUS_DEST_COLOR:
			return D3DBLEND_INVDESTCOLOR;
		case SBF_ONE_MINUS_SOURCE_COLOR:
			return D3DBLEND_INVSRCCOLOR;
		case SBF_DEST_ALPHA:
			return D3DBLEND_DESTALPHA;
		case SBF_SOURCE_ALPHA:
			return D3DBLEND_SRCALPHA;
		case SBF_ONE_MINUS_DEST_ALPHA:
			return D3DBLEND_INVDESTALPHA;
		case SBF_ONE_MINUS_SOURCE_ALPHA:
			return  D3DBLEND_INVSRCALPHA;		
		}
		//���ᵽ����
		return D3DBLEND_ONE;	
	}

	//��ȡD3D9��ʽ
	//��ʽװ����Щ�ң�������OGL�ĸ�ʽת�����ġ���ȷ��������֤
	D3DFORMAT MappingsD3D9::getFormat(PixelFormat pf)
	{
		switch(pf)
		{		
		case PF_A8:
			return D3DFMT_A8;
		case PF_L8:
			return D3DFMT_L8;
		case PF_L16:
			return D3DFMT_L16;
		case PF_R3G3B2: 
			return D3DFMT_R3G3B2;
		case PF_A1R5G5B5:
			return D3DFMT_A1R5G5B5;
		//case PF_R5G6B5: //��ӽ��ڲ���ʽ return PF_B5G6R5;
		case PF_B5G6R5: 
			return D3DFMT_R5G6B5;
		case PF_A4R4G4B4:
			return D3DFMT_A4R4G4B4;
#if	RE_ENDIAN == RE_ENDIAN_BIG
		// Formats are in native endian, so R8G8B8 on little endian is
        // BGR, on big endian it is RGB.
		//case PF_R8G8B8: //��ӽ��ڲ���ʽ PF_B8G8R8
		case PF_B8G8R8:
			return D3DFMT_R8G8B8;
		case PF_R8G8B8A8:
			return D3DFMT_A8B8G8R8 ;
		case PF_B8G8R8A8:
			return D3DFMT_A8R8G8B8;
#else
		case PF_R8G8B8:
			return D3DFMT_R8G8B8;
		//case PF_B8G8R8: //��ӽ��ڲ���ʽ PF_R8G8B8
		//case PF_R8G8B8A8: //û�ж�Ӧ�ĸ�ʽ
		//case PF_B8G8R8A8: //û�ж�Ӧ�ĸ�ʽ
#endif
		case PF_X8R8G8B8:
			return D3DFMT_X8R8G8B8;
		case PF_A8R8G8B8:
			return D3DFMT_A8R8G8B8;
		case PF_X8B8G8R8:
			return D3DFMT_X8B8G8R8;
        case PF_A8B8G8R8:
            return D3DFMT_A8B8G8R8;	
		case PF_A2R10G10B10:
			return D3DFMT_A2R10G10B10;
		case PF_A2B10G10R10:
			return D3DFMT_A2B10G10R10;
		case PF_FLOAT16_R:
			return D3DFMT_R16F;
		//case PF_FLOAT16_RGB: //��ӽ��ڲ���ʽPF_FLOAT16_RGBA
		case PF_FLOAT16_RGBA:
			return D3DFMT_A16B16G16R16F;
		case PF_FLOAT32_R:
			return D3DFMT_R32F;
		//case PF_FLOAT32_RGB: //��ӽ��ڲ���ʽPF_FLOAT32_RGBA
		case PF_FLOAT32_RGBA:
			return D3DFMT_A32B32G32R32F;
		case PF_SHORT_RGBA:
			return D3DFMT_A16B16G16R16;
		//case PF_RGB_DXT1: //��ӽ��ڲ���ʽD3DFMT_DXT1
		case PF_DXT1:
			return D3DFMT_DXT1;
		case PF_DXT2:
			return D3DFMT_DXT2;
		case PF_DXT3:
			return D3DFMT_DXT3;
		case PF_DXT4:
			return D3DFMT_DXT4;
		case PF_DXT5:
			return D3DFMT_DXT5;
		case PF_UNKNOWN:
		default:
			return D3DFMT_UNKNOWN;
		}
	}

	//��ȡ�ӽ���D3D9��ʽ
	PixelFormat MappingsD3D9::getClosestSupportedFormat(PixelFormat pf)
	{
		if( getFormat( pf) != PF_UNKNOWN)
			return pf;
		else
		{
			switch(pf)
			{
			case PF_R5G6B5:
				return PF_B5G6R5;
			case PF_R8G8B8:
				return PF_B8G8R8;
			case PF_FLOAT16_RGB:
				return PF_FLOAT16_RGBA;
			case PF_FLOAT32_RGB:
				return PF_FLOAT32_RGBA;
			case PF_RGB_DXT1:
				return PF_DXT1;
			case PF_UNKNOWN:
			default:
				return PF_UNKNOWN;
			}
		}
	}

	//��ȡD3D9�Ĺ���������
	D3DTEXTUREFILTERTYPE MappingsD3D9::getFilterType(FilterOptions fo)
	{
		switch( fo)
		{
		/// No filtering, used for FILT_MIP to turn off mipmapping
		case FO_NONE:
			return D3DTEXF_NONE;
		/// Use the closest pixel
		case FO_POINT:
			return D3DTEXF_POINT;
		/// Average of a 2x2 pixel area, denotes bilinear for MIN and MAG, trilinear for MIP
		case FO_LINEAR:
			return D3DTEXF_LINEAR;
		/// Similar to FO_LINEAR, but compensates for the angle of the texture plane
		case FO_ANISOTROPIC:
			return D3DTEXF_ANISOTROPIC;	
		default://���ᵽ����
			return D3DTEXF_LINEAR;
		}
	}

	//��ȡ����Ĺ���������
	FilterOptions MappingsD3D9::getFilterType( D3DTEXTUREFILTERTYPE texf)
	{
		switch ( texf)
		{
		case D3DTEXF_NONE:
			return FO_NONE;
		case D3DTEXF_POINT:
			return FO_POINT;
		case D3DTEXF_LINEAR:
			return FO_LINEAR;
		case D3DTEXF_ANISOTROPIC:
			return FO_ANISOTROPIC;
		default: //���ᵽ����
			return FO_LINEAR;
		}
	}

	//��ȡD3D9��Ѱַģʽ TAM_CLAMP_TO_EDGE �� TAM_CLAMPһ��?
	D3DTEXTUREADDRESS	MappingsD3D9::getAddressMode( TextureAddressingMode addr)
	{
		switch( addr)
		{
		/// Texture wraps at values over 1.0
		case TAM_WRAP:
			return D3DTADDRESS_WRAP;
		/// Texture mirrors (flips) at joins over 1.0
		case TAM_MIRROR:
			return D3DTADDRESS_MIRROR;
		/// Texture clamps at 1.0
		case TAM_CLAMP_TO_EDGE:
			return D3DTADDRESS_CLAMP;
		//
		case TAM_CLAMP:  // clamp ??
			return D3DTADDRESS_CLAMP;
		default://���ᵽ����
			return D3DTADDRESS_WRAP;
		}
	}

	//��ȡ�����Ѱַģʽ TAM_CLAMP_TO_EDGE �� TAM_CLAMPһ��?
	TextureAddressingMode MappingsD3D9::getAddressMode( D3DTEXTUREADDRESS addr)
	{
		//
		switch( addr)
		{
		case D3DTADDRESS_WRAP:
			return TAM_WRAP;
		case D3DTADDRESS_MIRROR:
			return TAM_MIRROR;
		case D3DTADDRESS_CLAMP:
			return TAM_CLAMP;
		default://���ᵽ����
			return TAM_WRAP;
		}
	}

	//��ȡ����Stage�Ĳ�������
	D3DTEXTUREOP MappingsD3D9::getTextureStageOperator(TextureStageOperator op)
	{
		switch(op)
		{
		case TSO_REPLACE:
			return D3DTOP_SELECTARG1;
		case TSO_MODULATE:
			return D3DTOP_MODULATE;
		case TSO_MODELATE2X:
			return D3DTOP_MODULATE2X;
		case TSO_ADD:
			return D3DTOP_ADD;
		case TSO_ADD_SIGNED:
			return D3DTOP_ADDSIGNED;
		case TSO_SUBTRACT:
			return D3DTOP_SUBTRACT;
		default://�����ᵽ�����
			return D3DTOP_MODULATE;
		}
	}
	//��ȡ�����Stage�Ĳ�����
	DWORD MappingsD3D9::getTextureStageArgument(TextureStageArgument arg)
	{
		switch( arg)
		{
		case TSA_TEXTURE:
			return D3DTA_TEXTURE;
		case TSA_PREVIOUS:
			return D3DTA_CURRENT;
		default://�����ᵽ����
			return D3DTA_TEXTURE;
		}
	}

	//����ת��
	void MappingsD3D9::getMatrix(const xs::Matrix4 & in, D3DXMATRIX & out)
	{
		//D3D9�Ǵ����������������洦��������
		out.m[0][0] = in[0][0]; out.m[0][1] = in[1][0]; out.m[0][2] = in[2][0]; out.m[0][3] = in[3][0];
		out.m[1][0] = in[0][1]; out.m[1][1] = in[1][1]; out.m[1][2] = in[2][1]; out.m[1][3] = in[3][1];
		out.m[2][0] = in[0][2]; out.m[2][1] = in[1][2]; out.m[2][2] = in[2][2]; out.m[2][3] = in[3][2];
		out.m[3][0] = in[0][3]; out.m[3][1] = in[1][3]; out.m[3][2] = in[2][3]; out.m[3][3] = in[3][3];
	}

	//����ת��
	void MappingsD3D9::getMatrix(const D3DXMATRIX & in, xs::Matrix4 & out)
	{
		//D3D9�Ǵ����������������洦��������
		out[0][0] = in.m[0][0]; out[0][1] = in.m[1][0]; out[0][2] = in.m[2][0]; out[0][3] = in.m[3][0];
		out[1][0] = in.m[0][1]; out[1][1] = in.m[1][1]; out[1][2] = in.m[2][1]; out[1][3] = in.m[3][1];
		out[2][0] = in.m[0][2]; out[2][1] = in.m[1][2]; out[2][2] = in.m[2][2]; out[2][3] = in.m[3][2];
		out[3][0] = in.m[0][3]; out[3][1] = in.m[1][3]; out[3][2] = in.m[2][3]; out[3][3] = in.m[3][3];	
	}
}