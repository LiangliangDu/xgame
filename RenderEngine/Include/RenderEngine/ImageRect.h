#ifndef __ImageRect_H__
#define __ImageRect_H__

namespace xs
{
	/*! \addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/

	enum ImageRectBlendMode
	{
		IR_OPAQUE,		//��͸��
		IR_TRANSPARENT,	//ColorKey
		IR_ALPHA_BLEND	//Alpha���
	};

	/** 2D��Ⱦ���û����Դ����2^N�ߴ��ͼ�񣬸����Կ���������ܻ��ͼ��Ϊ�����ͼ��
	�����ṩ�ж�ĳһ�������Ƿ���͸���Ĺ���
	*/
	class _RenderEngineExport ImageRect
	{
	public:

		bool	initialize(IRenderSystem *pRenderSystem,Image& image,bool bSplit = true,const ColorValue *pColorKey = 0);
		bool	initialize(
			IRenderSystem *pRenderSystem,
			const std::string& strImageFilename,bool bSplit = true,
			const ColorValue* pColorKey = 0);

		bool	initialize(IRenderSystem *pRenderSystem,xs::Stream* pStream,const std::string& strType,bool bSplit = true,const ColorValue* pColorKey = 0);

		void 	finalize();
		void 	render(int x,int y,float z = 0,const Rect *pSourceRect = 0);
		void 	render(const Rect *pSourceRect = 0);

		uint	getWidth(){return m_width;}
		uint	getHeight(){return m_height;}

		/** (x,y)���Ƿ�͸��
		@param x x����
		@param y y����
		@return true��ʾ͸����false��֮
		*/\
		bool	isTransparent(int x,int y);
	public:
		ImageRect();
		~ImageRect();
	private:
		struct ImageRect2N
		{
			Rect rc;				//�ߴ�
			Vector2	texcoord[4];	//��ͼ����
			ITexture*	texture;	//��ͼָ��
		};
	private:
		typedef std::vector<ImageRect2N>	ImageRectList;
		ImageRectList m_vImageRect;
		IRenderSystem*	m_pRenderSystem;
		ImageRectBlendMode	m_blendMode;

		uint	m_width,m_height;
		uint	m_next_power_of_two_width,m_next_power_of_two_height;

		uchar*	m_pTransparentData;
		uint	m_transparentBytesPerLine;
	private:
		/** ��ͼ���֣����Կ�֧��Non_Power_of_2��ͼ����û�в�֡�
		�����ִ��һ���ݹ�Ĳ�ֲ�����ֱ�����е���ͼ�ĳߴ綼��2^N�ߴ�
		level��ʾ��ȣ�����ֵ���ȳ������ֵ�����Զ�ֹͣ���
		@param pTextureManager ��ͼ�������ӿ�
		@param image ͼ������
		@param list Ŀ��ͼ����б���ֳɵ�����ͼ�ᱻ�ŵ��������
		@param rc ��ǰͼ��ĳߴ�
		@param imageWidth ͼ����(not used yet)
		@param imageHeight ͼ��߶�(not used yet)
		@param level �ݹ����
		@param bSplit �Ƿ���ͼ��true��ʾ��֣�false��ʾֱ�Ӵ���NextPowerOf2��ͼ����Blt
		*/\
		void 	splitImageTo2N(ITextureManager *pTextureManager,const Image& image,ImageRectList& list,const Rect& rc,uint imageWidth,uint imageHeight,uint level,bool bSplit);
	};
	/** @} */
}

#endif