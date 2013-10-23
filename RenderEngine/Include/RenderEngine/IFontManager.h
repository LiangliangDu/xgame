#ifndef __I_FontManager_H__
#define __I_FontManager_H__

namespace xs
{
	/*! addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/

	/** ����ӿ�
	*/

	/**���ֵĻ��Ʒ���,Ĭ�ϴ�����
	*/
	enum FontRenderDirection
	{
		FRD_LEFT2RIGHT = 0,//��������
		FRD_RIGHT2LEFT,//���ұߵ����
		FRD_TOP2BOTTOM,//���ϵ���
		FRD_BOTTOM2TOP,//���µ���
	};
	enum FontType
	{
		FontType_GDI = 0,//������,GDIЧ��
		FontType_PIX, //��������
	};

	struct IFont
	{
		virtual void release() = 0;
		/** ��������
		@param pText Unicode������Ϣ
		*/
		virtual void  render(const wchar_t* pText) = 0;										

		/** ��������
		@param pText Ascii������Ϣ
		*/
		virtual void  render(const char* pText) = 0;											

		/** 2D״̬�����ӿ�ĳλ�û�������
		@param xx x����
		@param yy y����
		@param zz z����
		@param color ��ɫ
		@param pText Ascii������Ϣ
		*/
		virtual void  render2d(float xx,float yy,float zz,const ColorValue& color,const char* pText) = 0;

		/** 2D״̬�����ӿ�ĳλ�û�������
		@param xx x����
		@param yy y����
		@param zz z����
		@param color ��ɫ
		@param pText Unicode������Ϣ
		*/
		virtual void  render2d(float xx,float yy,float zz,const ColorValue& color,const wchar_t* pText) = 0;

		/** �����������
		@return �������ƣ���"����"
		*/
		virtual const char*	getFontName() = 0;													

		/** ��������С
		@return �����С
		*/
		virtual uint	getFontSize() = 0;													

		/** �������Ascender
		@return ����Ascender
		*/
		virtual float getAscender() const = 0;												

		/** �������Descender
		@return ����Descender
		*/
		virtual float getDescender() const = 0;												

		/** �������LineHeight
		@return ����LineHeight
		*/
		virtual float getLineHeight() const = 0;												

		/** �������AABB��Ascii�汾
		@return ����AABB
		*/
		virtual void  getAABB( const char* string, AABB& aabb) = 0;							

		/** �������AABB��Unicode�汾
		@return ����AABB
		*/
		virtual void  getAABB( const wchar_t* string, AABB &aabb) = 0;						

		/** �������Advance��Unicode�汾
		@return ����Advance
		*/
		virtual float getAdvance( const wchar_t* string) = 0;								

		/** �������Advance��Ascii�汾
		@return ����Advance
		*/
		virtual float getAdvance( const char* string) = 0;									

		/** �������Advance��Unicode�汾
		@return ����Advance
		*/
		virtual float getAdvance( const wchar_t c) = 0;										

		/** �������Advance��Ascii�汾
		@return ����Advance
		*/
		virtual float getAdvance( const char c) = 0;

		/**�������ֵĻ��Ʒ���
		@return �ɵĻ��Ʒ���
		*/
		virtual FontRenderDirection setRenderDirection( FontRenderDirection rd) = 0;

		/**�������ֵļ��
		@return �ɵļ��
		*/
		virtual float setFontGap( float gap)=0;
		
		//add by yhc
		//����Ч��
		//��ɫ����
		virtual void GradientText(ColorValue& color1,ColorValue& color2) = 0;
		//�����
		virtual void TextOutline(ColorValue& clrOutline, int nThickness)= 0;
		//˫���
		virtual void TextDblOutline(ColorValue& clrOutline1, ColorValue& clrOutline2, int nThickness1, int nThickness2)= 0;
		//����
		virtual void TextGlow(ColorValue& clrOutline, int nThickness)= 0;
		//��Ӱ
		virtual void Shadow(ColorValue& color, int nThickness,int nOffsetX,int nOffsetY)= 0;
		//��ɢ����Ӱ
		virtual void DiffusedShadow(ColorValue& color, int nThickness,int nOffsetX,int nOffsetY)= 0;
		//ͻ����,��Ӱ�ں�
		virtual void Extrude(ColorValue& color, int nThickness,int nOffsetX,int nOffsetY)= 0;
		//�����ŵ���
		virtual void  render2dByScale(float xx,float yy,float zz,const ColorValue& color,const wchar_t* pText,float fScale)= 0;

		//Ԥ��ʼ��һЩ������
		virtual void InitText(wchar_t *pStr) = 0;
	};

	struct IRenderSystem;
	struct ITextureManager;

	/** ����������ӿ�
	*/
	struct IFontManager
	{
		/** ��������
		@param IRenderSystem* ��Ⱦϵͳ�ӿ�
		@param ITextureManager* ��ͼ�������ӿ�
		@param name �����ļ���
		@param szFontName ��������
		@param size �����С
		@return ����ӿ�
		*/
		virtual IFont*	createFont(IRenderSystem*,ITextureManager*,const char* name,const char* szFontName,uint size,FontType fonttype) = 0;

		/** ��������
		@param IFont* Ҫ���ٵ�����ӿ�ָ��
		*/
		virtual void 	releaseFont(IFont*) = 0;							

		/** ͨ�����ַ�ʽ��������
		@param name ��������
		*/
		virtual void 	releaseFont(const char* name) = 0;						

		/** �������м��ص�����
		*/
		virtual void 	releaseAll() = 0;									

		/** ͨ�����ַ�ʽ�������ӿ�
		@param name ��������
		@return ����ӿ�
		*/
		virtual IFont*	getFontByName(const char* name) = 0;

		//��Ⱦ��������
		virtual void RenderAllWord()= 0;
	};
	/** @} */

}
#endif