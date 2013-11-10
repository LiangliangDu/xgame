#ifndef     __PIXTextureFont__
#define     __PIXTextureFont__

#include "Font.h"

//��������
namespace xs
{
	class PixTextureFont : public ITextureFont
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
		PixTextureFont();
		bool create(IRenderSystem *pRenderSystem,const wchar_t* szFontName,uint size);
		~PixTextureFont(){};	

	private:

		void drawGlyphToBuffer(CharTextureInfo * pInfo,wchar_t szText,DWORD dwSize);

		//���Ч��
		void effectGlyphToBuffer (CharTextureInfo * pInfo,wchar_t  szText,DWORD dwSize);
#if (TARGET_PLATFORM == PLATFORM_WIN32)
		//��ɫ����
		virtual void GradientText(Color color1,Color color2) {}

		//�����
		virtual void TextOutline(Gdiplus::Color clrOutline, int nThickness) {}

		//˫���
		virtual void TextDblOutline(Gdiplus::Color clrOutline1, 
			Gdiplus::Color clrOutline2, 
			int nThickness1, 
			int nThickness2)
		{
		}

		//����
		virtual void TextGlow( Gdiplus::Color clrOutline,  int nThickness) {}

		//��Ӱ
		virtual void Shadow( Gdiplus::Color color, int nThickness,Gdiplus::Point ptOffset){}

		//��ɢ����Ӱ
		virtual void DiffusedShadow(Gdiplus::Color color, int nThickness,Gdiplus::Point ptOffset) {}

		//ͻ����,��Ӱ�ں�
		virtual void Extrude(Gdiplus::Color color, int nThickness,Gdiplus::Point ptOffset) {}
#endif

		virtual void  RenderByScale(const wchar_t* c,float fScale) {}

		//  ��ȡ��Ⱦʱ�õ���������Ϣ
		CharTextureInfo * GetCharTextureInfo(wchar_t wc);

		//Ԥ��ʼ��һЩ������
		virtual void InitText(wchar_t *pStr){};

	private:
		//������Ϣ,���ִ�С��
		//std::string	m_strFontName;
		std::wstring  m_strFontName;
		uint	m_ui32Size;

		//�Ƿ����
		bool m_bOutline;
#if (TARGET_PLATFORM == PLATFORM_WIN32)
		HDC m_hdc;
		HFONT m_hFont;
		TEXTMETRIC m_textmetric;
		//������ɫ
		Gdiplus::Color fontcolor;
		//�����ɫ
		Gdiplus::Color effectcolor;
#endif
	private:
		//��������Ⱦ�����ַ���������Ϣ
		typedef std::map<wchar_t,CharTextureInfo>		FontTexture;
		FontTexture m_FontTexture;

		//��ǰ���Ƶ�����λ��
		uint m_nDrawTextleft;
		uint m_nDrawTextTop;

		//���ø�������Ч��

		//��ɫ�����õ�ˢ��

		//�ַ���ǰ��հ׵�����
		int m_nBlankPixX,m_nBlankPixY;

	private:
		xs::IVertexBuffer * m_pVB;//positon vertx buffer
		xs::IVertexBuffer * m_pTexVB; //texcoord vertex buffer

	};
}
#endif // __FTTextureFont__


