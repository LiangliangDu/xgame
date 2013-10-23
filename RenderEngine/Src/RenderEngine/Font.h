#ifndef __Font_H__
#define __Font_H__

namespace xs
{
	class GDITextureFont;
	class FontManager;
	struct MyVector2
	{
		float X;
		float Y;
	};
	struct CharTextureInfo
	{
		//������������
		int nTexIndex;

		//������������е�������Ϣ
		uint left;
		uint top;
		uint width;
		uint height;
		MyVector2 uv[2];
	};

	//һ���ֵ���Ⱦ��Ϣ
	struct CharRenderInfo
	{
		CharTextureInfo  * pInfo;
		float left;
		float top;
		ColorValue color;
		float scale;
	};
	//��Ⱦ��ʱ����,��ͬһ������������ַŵ�һ����Ⱦ,���Ч��
	typedef  std::vector<CharRenderInfo> CharInfoForTex;

	struct ITextureFont
	{
		//�ͷ�
		virtual void release() = 0;
		//����ֵ
		virtual float Ascender() = 0;
		//����ֵ
		virtual float Descender() = 0;
		//�о�
		virtual float LineHeight() = 0;

		//�ַ����İ�Χ��
		virtual void  BBox( const wchar_t* string, float& llx, float& lly, float& llz, float& urx, float& ury, float& urz)= 0;

		virtual float Advance( const wchar_t* string)= 0;
		//��Ⱦһ���ַ��Ŵ�
		virtual void  Render(const wchar_t* c )= 0;
		//��Ⱦһ���ַ��Ŵ�
		virtual void  RenderByScale(const wchar_t* c,float fScale)= 0;
		//�ַ����İ�Χ��
		virtual void  BBox( const char* string, float& llx, float& lly, float& llz, float& urx, float& ury, float& urz)= 0;
		virtual float Advance( const char* string)= 0;
		//��Ⱦһ���ַ��Ŵ�
		virtual void  Render(const char* string )= 0;



		virtual FontRenderDirection setRenderDirection( FontRenderDirection rd)= 0;
		virtual float setFontGap( float gap)= 0;

		//��ɫ����
		virtual void GradientText(Color color1,Color color2)= 0;

		//�����
		virtual void TextOutline(Gdiplus::Color clrOutline, 
			int nThickness)= 0;
		//˫���
		virtual void TextDblOutline(Gdiplus::Color clrOutline1, 
			Gdiplus::Color clrOutline2, 
			int nThickness1, 
			int nThickness2)= 0;

		//����
		virtual void TextGlow(
			Gdiplus::Color clrOutline, 
			int nThickness)= 0;
		//��Ӱ
		virtual void Shadow(
			Gdiplus::Color color, 
			int nThickness,
			Gdiplus::Point ptOffset)= 0;
		//��ɢ����Ӱ
		virtual void DiffusedShadow(
			Gdiplus::Color color, 
			int nThickness,
			Gdiplus::Point ptOffset)= 0;
		//ͻ����,��Ӱ�ں�
		virtual void Extrude(
			Gdiplus::Color color, 
			int nThickness,
			Gdiplus::Point ptOffset)= 0;

		//Ԥ��ʼ��һЩ������
		virtual void InitText(wchar_t *pStr) = 0;
	
		//�������õ�����������
		std::vector<ITexture*> vTextures;
		//��Ⱦ��ʱ����,��ͬһ������������ַŵ�һ����Ⱦ,���Ч��
		std::vector<CharInfoForTex> vCharInfoForTex;
		IRenderSystem*		m_pRenderSystem;
		ITextureManager*	m_pTextureManager;
		//��������Ⱦ
		virtual void RealRender()
		{
			SceneBlendFactor src,dst;
			m_pRenderSystem->getSceneBlending(src,dst);
			m_pRenderSystem->setSceneBlending(SBF_SOURCE_ALPHA,SBF_ONE_MINUS_SOURCE_ALPHA);
			ColorValue oldcolor = m_pRenderSystem->getColor();
			for(int i=0;i<vCharInfoForTex.size();i++)
			{
				m_pRenderSystem->setTexture(0,vTextures[i]);
				//m_pRenderSystem->beginPrimitive(PT_TRIANGLES);

				m_pRenderSystem->beginPrimitive(PT_QUADS);
				
				//��ͬһ��������,�ŵ�һ��ȥ��Ⱦ
				for(int j=0;j<vCharInfoForTex[i].size();j++)
				{
					//��������Ⱦϵͳ���������
					// by yhc 12.12
					if(j>512)
					{
						m_pRenderSystem->endPrimitive();
						m_pRenderSystem->beginPrimitive(PT_QUADS);
					}
					CharRenderInfo * pRenderInfo = &( vCharInfoForTex[i][j]);
					CharTextureInfo * pInfo = pRenderInfo->pInfo;
					m_pRenderSystem->setColor(pRenderInfo->color);
					m_pRenderSystem->setTexcoord(Vector2(pInfo->uv[0].X, pInfo->uv[0].Y));
					m_pRenderSystem->sendVertex(Vector2(pRenderInfo->left, pRenderInfo->top));

					m_pRenderSystem->setTexcoord(Vector2(pInfo->uv[0].X, pInfo->uv[1].Y));
					m_pRenderSystem->sendVertex(Vector2(pRenderInfo->left, pRenderInfo->top+pInfo->height*pRenderInfo->scale ));

					m_pRenderSystem->setTexcoord(Vector2(pInfo->uv[1].X, pInfo->uv[1].Y));
					m_pRenderSystem->sendVertex(Vector2(pRenderInfo->left+pInfo->width*pRenderInfo->scale, pRenderInfo->top+pInfo->height*pRenderInfo->scale ));

					m_pRenderSystem->setTexcoord(Vector2(pInfo->uv[1].X, pInfo->uv[0].Y));
					m_pRenderSystem->sendVertex(Vector2(pRenderInfo->left+pInfo->width*pRenderInfo->scale, pRenderInfo->top));

					
				}

				m_pRenderSystem->endPrimitive();
				vCharInfoForTex[i].clear();
				m_pRenderSystem->setColor(oldcolor);
			}
		}
	};

	class Font : public IFont
	{
	public:
		virtual void release();
		/** ��������
		@param pText Unicode������Ϣ
		*/
		virtual void  render(const wchar_t* pText);										

		/** ��������
		@param pText Ascii������Ϣ
		*/
		virtual void  render(const char* pText);											

		/** 2D״̬�����ӿ�ĳλ�û�������
		@param xx x����
		@param yy y����
		@param zz z����
		@param color ��ɫ
		@param pText Ascii������Ϣ
		*/
		virtual void  render2d(float xx,float yy,float zz,const ColorValue& color,const char* pText);

		/** 2D״̬�����ӿ�ĳλ�û�������
		@param xx x����
		@param yy y����
		@param zz z����
		@param color ��ɫ
		@param pText Unicode������Ϣ
		*/
		virtual void  render2d(float xx,float yy,float zz,const ColorValue& color,const wchar_t* pText);

		/** �����������
		@return �������ƣ���"����"
		*/
		virtual const char*	getFontName();													

		/** ��������С
		@return �����С
		*/
		virtual uint	getFontSize();													

		/** �������Ascender
		@return ����Ascender
		*/
		virtual float getAscender() const;												

		/** �������Descender
		@return ����Descender
		*/
		virtual float getDescender() const;												

		/** �������LineHeight
		@return ����LineHeight
		*/
		virtual float getLineHeight() const;												

		/** �������AABB��Ascii�汾
		@return ����AABB
		*/
		virtual void  getAABB( const char* string, AABB& aabb);							

		/** �������AABB��Unicode�汾
		@return ����AABB
		*/
		virtual void  getAABB( const wchar_t* string, AABB &aabb);						

		/** �������Advance��Unicode�汾
		@return ����Advance
		*/
		virtual float getAdvance( const wchar_t* string);								

		/** �������Advance��Ascii�汾
		@return ����Advance
		*/
		virtual float getAdvance( const char* string);									

		/** �������Advance��Unicode�汾
		@return ����Advance
		*/
		virtual float getAdvance( const wchar_t c);										

		/** �������Advance��Ascii�汾
		@return ����Advance
		*/
		virtual float getAdvance( const char c);

		/**�������ֵĻ��Ʒ���
		@return �ɵĻ��Ʒ���
		*/
		virtual FontRenderDirection setRenderDirection( FontRenderDirection rd);

		/**�������ֵļ��
		@return �ɵļ��
		*/
		virtual float setFontGap( float gap);

		//add by yhc
		//����Ч��
		//��ɫ����
		virtual void GradientText(ColorValue& color1,ColorValue& color2) ;
		//�����
		virtual void TextOutline(ColorValue& clrOutline, int nThickness);
		//˫���
		virtual void TextDblOutline(ColorValue& clrOutline1, ColorValue& clrOutline2, int nThickness1, int nThickness2);
		//����
		virtual void TextGlow(ColorValue& clrOutline, int nThickness);
		//��Ӱ
		virtual void Shadow(ColorValue& color, int nThickness,int nOffsetX,int nOffsetY);
		//��ɢ����Ӱ
		virtual void DiffusedShadow(ColorValue& color, int nThickness,int nOffsetX,int nOffsetY);
		//ͻ����,��Ӱ�ں�
		virtual void Extrude(ColorValue& color, int nThickness,int nOffsetX,int nOffsetY);

		virtual void  render2dByScale(float xx,float yy,float zz,const ColorValue& color,const wchar_t* pText,float fScale);

		//Ԥ��ʼ��һЩ������
		virtual void InitText(wchar_t *pStr);
	public:
		~Font(){};
		Font():m_pFTFont(0),
			m_name(),
			m_strFontName(),
			m_ui32Size(16),
			m_pFontData(0),
			m_pRenderSystem(0),
			m_pFontManager(0),
			m_type(FontType_PIX){};

		bool create(FontManager* pFontMgr, 
			IRenderSystem* pRenderSystem,
			const std::string & name, 
			const std::string & szFontPath,
			uint size,
			FontType fontType);

		//bool	create(IRenderSystem *pRenderSystem,ITextureManager *pTextureManager,const char* szFontName,uint size,FontType fonttype);
	public:
	ITextureFont * m_pFTFont;

	private:
		
		std::string		m_name;//��������
		std::string	m_strFontName;//���������õ�·������...
		FontType	m_type;
		uint	m_ui32Size;
		uchar*	m_pFontData;
		IRenderSystem*	m_pRenderSystem;
		FontManager*	m_pFontManager;
	};
}

#endif