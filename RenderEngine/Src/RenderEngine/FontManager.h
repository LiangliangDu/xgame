#ifndef __FontManager_H__
#define __FontManager_H__

namespace xs
{
	class FontManager : public IFontManager
	{
		typedef std::map<IFont*,std::string>		FontString;
		typedef std::map<std::string,IFont*>		StringFont;
	public:
		/** ��������
		@param IRenderSystem* ��Ⱦϵͳ�ӿ�
		@param ITextureManager* ��ͼ�������ӿ�
		@param name �����ļ���
		@param szFontName ��������
		@param size �����С
		@return ����ӿ�
		*/
		virtual IFont*	createFont(IRenderSystem*,ITextureManager*,const char* name,const char* szFontName,uint size,FontType fonttype);

		/** ��������
		@param IFont* Ҫ���ٵ�����ӿ�ָ��
		*/
		virtual void 	releaseFont(IFont*);							

		/** ͨ�����ַ�ʽ��������
		@param name ��������
		*/
		virtual void 	releaseFont(const char* name);						

		/** �������м��ص�����
		*/
		virtual void 	releaseAll();									

		/** ͨ�����ַ�ʽ�������ӿ�
		@param name ��������
		@return ����ӿ�
		*/
		virtual IFont*	getFontByName(const char* name);
		//��Ⱦ��������
		virtual void RenderAllWord();
	public:
		bool registerFont(IFont* pFont);//�����������ע������
		void unregisterFont(IFont* pFont);//�������������ע������
	protected:
		FontManager();
	public:
		static FontManager*	Instance()
		{
			static FontManager fm;
			return &fm;
		}
		~FontManager();
	private:
		FontString		m_fs;
		StringFont		m_sf;
	};

}

#endif