#ifndef __I_RenderEngine_H__
#define __I_RenderEngine_H__

struct ISceneManager2;
namespace xs
{
	/*! \addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/

	struct IRenderSystem;
	class Camera;
	class Viewport;
	class TextureManager;
	class BufferManager;
	struct ISceneEnv;
	struct IModelManager;
	struct ICynthiaScene;
	struct IFontManager;
	struct IModelInstanceManager;

	/**��Ⱦϵͳ����
	*/
	enum RenderSystemType
	{
		/// OpenGL
		RS_OPENGL,

		/// D3D(��δʵ��)
		RS_D3D9,
		RS_COUNT
	};


	/** RenderEngine Creation Flags
	*/

	struct RenderEngineCreationParameters
	{
		/// ��Ⱦϵͳ����RenderSystemType
		RenderSystemType	rst;

		/// �Ƿ�ȫ��
		bool				fullscreen;	

		/// �Ƿ���StencilBuffer
		bool				stencilBuffer;

		/// ���ھ��������Ϊ��
		void *				hwnd;

		/// ���ڿ��
		uint				w;

		/// ���ڸ߶�
		uint				h;

		/// ˢ����
		uint				refreshRate;

		/// ��ɫ���
		uint				colorDepth;

		/// ��ֱͬ��
		bool				vertcialSync;

		RenderEngineCreationParameters() : hwnd(0),rst(RS_OPENGL),w(800),h(600),fullscreen(false),refreshRate(85),colorDepth(32),vertcialSync(true)
		{
		}
	};
	

	struct IResourceManager;
/** ��Ⱦ����ӿ�
*/
struct IRenderEngine
{
	/** ��Ⱦ��������
	*/
	virtual void 				release() = 0;											

	/** ��ȡ��Ⱦϵͳ�ӿ�
	@return ��Ⱦϵͳ�ӿ�
	*/
	virtual IRenderSystem*		getRenderSystem() = 0;									

	/** ��ȡģ�͹���ӿ�
	@return ģ�͹���ӿ�
	*/
	virtual IModelManager*		getModelManager() = 0;

	/** ��ȡ�������ӿ�
	@return �������ӿ�
	*/
	virtual IFontManager*		getFontManager() = 0;									

	/** ���������
	@param pViewport �ӿ�
	@return �����ָ��
	*/
	virtual Camera*				createCamera(Viewport* pViewport) = 0;					

	/** �����ӿ�
	@return �ӿ�ָ��
	*/
	virtual Viewport*			createViewport() = 0;

	virtual const RenderEngineCreationParameters& getCreationParams() = 0;
};

/** ������Ⱦ����
@param param ����Ĵ�������
@return ��Ⱦ����ָ��
*/
extern "C" __declspec(dllexport) IRenderEngine* LoadRenderEngine(RenderEngineCreationParameters *param);

/** ��ȡ��Ⱦ����ӿ�
@return ��Ⱦ����ָ��
*/
extern "C" __declspec(dllexport) IRenderEngine* getRenderEngine();


extern "C" __declspec(dllexport) void registerImageCodec();

	/** @} */
}

#endif