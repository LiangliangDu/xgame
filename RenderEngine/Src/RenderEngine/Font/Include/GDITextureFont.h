#ifndef     __GDITextureFont__
#define     __GDITextureFont__
#include "Font.h"

//GDI��������
//֧�����,˫�����,��Ӱ����ɫ�����Ч��
// yhc

#if 0  //add by kevin.chen

#include "PngOutlineText.h"
namespace xs
{
	class GDITextureFont :public ITextureFont
	{
	public:
		//�ͷ�
		virtual void release();
		//����ֵ
		virtual float Ascender() ;
		//����ֵ
		virtual float Descender() ;
		//�о�
		virtual float LineHeight() ;

		//�ַ����İ�Χ��
		virtual void  BBox( const wchar_t* string, float& llx, float& lly, float& llz, float& urx, float& ury, float& urz);

		virtual float Advance( const wchar_t* string);
		//��Ⱦһ���ַ��Ŵ�
		virtual void  Render(const wchar_t* c );
		//�ַ����İ�Χ��
		void  BBox( const char* string, float& llx, float& lly, float& llz, float& urx, float& ury, float& urz);
		virtual float Advance( const char* string);
		//��Ⱦһ���ַ��Ŵ�
		virtual void  Render(const char* string );
		//
		virtual FontRenderDirection setRenderDirection( FontRenderDirection rd);
		//
		virtual float setFontGap( float gap);

	public:
		GDITextureFont();
		bool	create(IRenderSystem *pRenderSystem,const wchar_t* szFontName,uint size);
		~GDITextureFont() {};	

	private:
		//�����ַ�ͼ������
		bool GenerateTextBitmap(wchar_t * szText);
		//
		bool LoadOneTextBitmap( CharTextureInfo * pInfo,wchar_t * szText );
		//��ȡ�հ�����
		bool GetBlankPix( wchar_t * szText );

		//  ��ȡ��Ⱦʱ�õ���������Ϣ
		CharTextureInfo * GetCharTextureInfo(wchar_t wc);

		//Ԥ��ʼ��һЩ������
		virtual void InitText(wchar_t *pStr);

	private:
		//������Ϣ,���ִ�С��
		//std::string	m_strFontName;
		std::wstring	m_strFontName;
		uint	m_ui32Size;
		//����Ч�����ӵ��и�
		uint    m_nFontThickness;
		//LOGFONT m_LogFont;
		FontFamily * m_pFontFamily;
		//������ƶ���
		PngOutlineText m_PngOutlineText;
		//����������
		Gdiplus::Bitmap * m_pbmp;
		//����������
		Graphics * m_pGraphics;

	private:
		//��������Ⱦ�����ַ���������Ϣ
		typedef std::map<wchar_t,CharTextureInfo>		FontTexture;
		FontTexture m_FontTexture;

		//��ǰ���Ƶ�����λ��
		uint m_nDrawTextleft;
		uint m_nDrawTextTop;

		//���ø�������Ч��
		//������ɫ
		Gdiplus::Color fontcolor;
		//��ɫ�����õ�ˢ��
		Gdiplus::LinearGradientBrush * m_pGradientBrush;

		//�ַ���ǰ��հ׵�����
		int m_nBlankPixX,m_nBlankPixY;
	public:

		//��ɫ����
		virtual void GradientText(Color color1,Color color2);

		//�����
		virtual void TextOutline(Gdiplus::Color clrOutline, 
			int nThickness);
		//˫���
		virtual void TextDblOutline(Gdiplus::Color clrOutline1, 
			Gdiplus::Color clrOutline2, 
			int nThickness1, 
			int nThickness2);

		//����
		virtual void TextGlow(
			Gdiplus::Color clrOutline, 
			int nThickness);
		//��Ӱ
		virtual void Shadow(
			Gdiplus::Color color, 
			int nThickness,
			Gdiplus::Point ptOffset);
		//��ɢ����Ӱ
		virtual void DiffusedShadow(
			Gdiplus::Color color, 
			int nThickness,
			Gdiplus::Point ptOffset);
		//ͻ����,��Ӱ�ں�
		virtual void Extrude(
			Gdiplus::Color color, 
			int nThickness,
			Gdiplus::Point ptOffset);
		virtual void  RenderByScale(const wchar_t* c,float fScale);
	};
}

#endif

#endif // __FTTextureFont__


