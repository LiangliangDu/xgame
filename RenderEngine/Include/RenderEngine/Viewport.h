#ifndef __Viewport_H__
#define __Viewport_H__

namespace xs
{
	/*! \addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/

	class _RenderEngineExport Viewport
	{
		friend class Camera;
	public:
		void  release();

		Viewport();
		~Viewport();

		/** ����ӿڵ�left����
		*/
		int getLeft();

		/** ����ӿڵ�top����
		*/
		int getTop();

		/** ����ӿڿ��
		*/
		int getWidth();

		/** ����ӿڵĸ߶�
		*/
		int getHeight();

		/** �����ӿڵ�left
		*/
		void  setLeft(int left);

		/** �����ӿڵ�top
		*/
		void  setTop(int top);

		/** �����ӿڵĿ��
		*/
		void  setWidth(int width);

		/** �����ӿڵĸ߶�
		*/
		void  setHeight(int height);

		/** ����ӿڵĸ��ֲ���
		*/
		void  setValues(int left,int top,int width,int height);

		/** �����ӿڵĸ�������
		*/
		void  getValues(int& left,int& top,int& width,int& height);

		/** Sets the initial background color of the viewport (before rendering).
		*/
		void  setBackgroundColor(const ColorValue& color);

		/** Gets the background colour.
		*/
		const ColorValue& getBackgroundColor(void ) const;

		/** Determines whether to clear the viewport before rendering.
		@remarks
		If you expecting every pixel on the viewport to be redrawn
		every frame, you can save a little time by not clearing the
		viewport before every frame. Do so by passing 'false' to this
		method (the default is to clear every frame).
		*/
		void  setClearEveryFrame(bool clear);

		/** Determines if the viewport is cleared before every frame.
		*/
		bool getClearEveryFrame(void ) const;

	private:
		int	m_ui32Left,m_ui32Top,m_ui32Width,m_ui32Height;
		bool	m_bClear;
		ColorValue	m_color;
		Camera*	m_pCamera;
	private:
		/***/
		void  setCamera(Camera *pCamera);
	};
	/** @} */
}

#endif