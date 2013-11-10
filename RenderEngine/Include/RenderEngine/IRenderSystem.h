#ifndef __I_RenderSystem_H__
#define __I_RenderSystem_H__

namespace xs
{
	/*! \addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/


	struct IFontManager;
	struct ITextureManager;
	struct IBufferManager;
	class RenderSystemCapabilities;
	struct ITexture;
	struct IShaderProgramManager;
	class Light;
	class Viewport;
	class RenderOperation;
	class RenderDirect;
	struct IVideoObject;
	struct IHardwareCursorManager;
	struct IShaderProgram;

	/** ��Ⱦϵͳ�ӿ�
	*/
	struct IRenderSystem
	{
		/** �ͷ���Ⱦϵͳ
		*/
		virtual void			release() = 0;

		/** ��ȡ��Ⱦϵͳ�����ƣ���"OpenGL","D3D9"��
		@return ��Ⱦϵͳ���Ƶ��ַ���
		*/
		virtual const char*		getName() = 0;							

		/** �����Ⱦϵͳ����ָ��
		@return ��Ⱦϵͳ����ָ��
		*/
		virtual RenderSystemCapabilities*	getCapabilities() = 0;	

		/** �����ӿ�
		@param pViewport �ӿ�ָ��
		*/
		virtual void 		setViewport(int left,int top,int width,int height) = 0;			

		/** ��ȡ�ӿ�����
		@param left �ӿھ��봰����ߵľ���
		@param top �ӿھ��봰���ϱߵľ���
		@param width �ӿڵĿ��
		@param height �ӿڵĸ߶�
		*/
		virtual void 		getViewport(int &left,int &top,int &width,int &height) = 0;		

		/** ��������ӿڵı���ɫ
		@param color ����ɫ
		*/
		virtual void 		setClearColor(const ColorValue& color) = 0;

		/** �������ӿڵ���ɫ
		@return ����ӿڵ���ɫ
		*/
		virtual const ColorValue& getClearColor() = 0;				

		/** ���������Ȼ����ֵ���������Ȼ���ʱ����Ȼ����ÿ����λ�������ó����ֵ
		@param depth ���ֵ��Ĭ����������ֵ
		*/
		virtual void 		setClearDepth(float depth) = 0;			

		/** �������ģ�建���ֵ
		@param stencil ���ģ�建���ֵ��Ĭ����0
		*/
		virtual void 		setClearStencil(int stencil = 0) = 0;	

		/** ����ͶӰ����
		@param mtx ͶӰ����
		*/
		virtual void 		setProjectionMatrix(const Matrix4& mtx) = 0;			

		/** �����Ӿ���
		@param mtx �Ӿ���
		*/
		virtual void 		setViewMatrix(const Matrix4& mtx) = 0;	

		/** �����������
		@param mtx �������
		*/
		virtual void 		setWorldMatrix(const Matrix4 &mtx) = 0;	

		/** ��ȡͶӰ����
		@return ��ǰ��Ⱦϵͳ��ͶӰ����
		*/
		virtual const Matrix4&		getProjectionMatrix() = 0;		

		/** ��ȡ�Ӿ���
		@return ��ǰ��Ⱦϵͳ���Ӿ���
		*/
		virtual const Matrix4&		getViewMatrix() = 0;			

		/** ��ȡ�������
		@return ��ǰ��Ⱦϵͳ���������
		*/
		virtual const Matrix4&		getWorldMatrix() = 0;			

		/** ��ȡ��ͼ�������
		@return ��ͼ�������������Multiply
		*/
		virtual const Matrix4&		getModelViewMatrix() = 0;		

		/** ��ʼ����һ��
		@param clearColorBuffer �Ƿ������ɫ����
		@param clearDepthBuffer �Ƿ������Ȼ���
		@param clearStencilBuffer �Ƿ����ģ�建��
		*/
		virtual void 		beginFrame(bool clearColorBuffer = true,bool clearDepthBuffer = true,bool clearStencilBuffer = false) = 0;

		/** ��������һ��,��beginFrame����ʹ��
		*/
		virtual void 		endFrame(int layer = 0) = 0;							

		/** �����Ƿ����д��Ȼ���
		@param enabled true������,false������,Ĭ��Ϊtrue
		*/
		virtual void 		setDepthBufferWriteEnabled(bool enabled) = 0;			

		/** ��ȡ�Ƿ����д��Ȼ���
		@return true��ʾ����,false������
		*/
		virtual bool		isDepthBufferWriteEnabled() = 0;		

		/** �����Ƿ�򿪵ƹ�
		@param enabled true������,false������,Ĭ��Ϊfalse
		*/
		virtual void 		setLightingEnabled(bool enabled) = 0;	

		/** ��ȡ�ƹ��Ƿ���
		@return true��ʾ����,false��ر�
		*/
		virtual bool		isLightingEnabled() = 0;				

		/** �������ģʽ
		@param sdl ���ģʽ
		@see FillMode
		*/
		virtual void 		setFillMode(const FillMode& sdl) = 0;	

		/** ��ȡ���ģʽ
		@return ���ģʽ
		@see FillMode
		*/
		virtual const FillMode&	getFillMode() = 0;

		/** ���������Ŀ��
		@param width ������ȣ���beginPrimitive(PT_LINES)����Ч
		*/
		virtual void setLineWidth(float width) = 0;

		/** ��ȡ�����Ŀ��
		@return �������
		*/
		virtual float getLineWidth() = 0;

		/** �����Ƿ��������У��
		@param enabled true������,false������,Ĭ��Ϊfalse
		*/
		virtual void 		setDepthBufferCheckEnabled(bool enabled) = 0;			

		/** ��ȡ��ǰϵͳ�Ƿ��������У��
		@return true��ʾ����,false������
		*/
		virtual bool		isDepthBufferCheckEnabled() = 0;		

		/** �������У�麯��
		@param cf ���У�麯��,Ĭ��ΪCMPF_LESS
		@see CompareFunction
		*/
		virtual void 		setDepthBufferFunction(const CompareFunction& cf) = 0;

		virtual const CompareFunction& getDepthBufferFunction() = 0;

		/** ��ȡAlphaУ�麯���Ͳο�ֵ
		@param cf AlphaУ�麯��
		@param value �ο�ֵ
		@see CompareFunction
		*/
		virtual void 		getAlphaFunction(CompareFunction& cf,float& value) = 0;	

		/** ����AlphaУ�麯��
		@param cf AlphaУ�麯��,Ĭ��ΪCMPF_ALWAYS
		@param value �ο�ֵ,��cfΪһ����Ҫ�ο�ֵ�ĺ���ʱ
		@see CompareFunction
		*/
		virtual void 		setAlphaFunction(const CompareFunction& cf,float value) = 0;

		/** ����AlphaУ�麯��
		@param cf AlphaУ�麯��,Ĭ��ΪCMPF_ALWAYS
		@param value �ο�ֵ,value / 255����һ��������һ����
		@see CompareFunction
		*/
		virtual void 		setAlphaFunction(const CompareFunction& cf,uchar value)	= 0;				

		/** ��ȡ�Ƿ�����AlphaУ��
		@return true��ʾ����,false������
		*/
		virtual bool		alphaCheckEnabled() = 0;				

		/** �����Ƿ�����AlphaУ��
		@param bEnabled true��ʾ����,false������,Ĭ��Ϊfalse
		@param value �ο�ֵ,��cfΪһ����Ҫ�ο�ֵ�ĺ���ʱ
		*/
		virtual void 		setAlphaCheckEnabled(bool bEnabled) = 0;

		/** ���ñ���ü���ʽ
		@param cm �ü���ʽ
		@see CullingMode
		*/
		virtual void 		setCullingMode(const CullingMode& cm) = 0;

		/** ���ñ߱��
		@param bEdgeFlag true��򿪱߱��,false��ر�,Ĭ��Ϊtrue
		*/
		virtual void 		setEdgeFlag(bool bEdgeFlag) = 0;		

		/** ��ȡ����ü���ʽ
		@return ����ü���ʽ
		@see CullingMode
		*/
		virtual const		CullingMode& getCullingMode() = 0;		

		/** ���ó�����ϲ���
		@param src Դ��ϲ���,Ĭ��ΪSBF_ONE
		@param dst Ŀ���ϲ���,Ĭ��ΪSBF_ZERO
		@see SceneBlendFactor
		*/
		virtual void 		setSceneBlending(const SceneBlendFactor& src,const SceneBlendFactor& dst) = 0;

		/** ��ȡ������ϲ���
		@param src Դ��ϲ���
		@param dst Ŀ���ϲ���
		@see SceneBlendFactor
		*/
		virtual void 		getSceneBlending(SceneBlendFactor& src,SceneBlendFactor& dst) = 0;			

		/** ����������Ⱦ����
		@param param ��Ⱦ����
		@see RenderEngineCreationParameters
		@return true��ʾ�ɹ�,��֮ʧ��
		*/
		virtual bool		switchDisplayMode(RenderEngineCreationParameters* param) = 0;				

		/** ��ȡ������������ָ��
		@return ������������ָ��
		*/
		virtual IBufferManager*		getBufferManager() = 0;			

		/** ��ȡ��ͼ������ָ��
		@return ��ͼ������ָ��
		*/
		virtual ITextureManager*	getTextureManager() = 0;		

		/** ���õ�ǰ��ͼ��ɫ,���еƹ�������,��ɫ��Ч
		@param color ��ɫֵ
		@see ColorValue
		*/
		virtual void 		setColor(const ColorValue& color) = 0;	

		/** ��ȡ��ǰ��ͼ��ɫ
		@return ��ɫֵ
		*/
		virtual const ColorValue& getColor() = 0;					

		/** ���õ�ǰ����ֵ
		@param normal ����
		@see Vector3
		*/
		virtual void 		setNormal(const Vector3& normal) = 0;	

		/** ���õ�ǰ��ͼ����
		@param texcoord ��ͼ����
		*/
		virtual void 		setTexcoord(const Vector2& texcoord) = 0;

		/** ���õ�ǰ��ͼ����
		@param texcoord ��ͼ����
		*/
		virtual void 		setMultiTexcoord(ushort unit,const Vector2& texcoord) = 0;

		/** ���Ͷ���
		@param vertex ��������
		*/
		virtual void 		sendVertex(const Vector2& vertex) = 0;	

		/** ���Ͷ���
		@param vertex ��������
		*/
		virtual void 		sendVertex(const Vector3& vertex) = 0;	

		/** ���Ͷ���
		@param vertex ��������
		*/
		virtual void 		sendVertex(const Vector4& vertex) = 0;	

		/** ��ʼ����һ����״
		@param pt ��ͼ����
		@see PrimitiveType
		*/
		virtual void 		beginPrimitive(PrimitiveType pt) = 0;	

		/** ��������һ����״,��beginPrimitive����ʹ��
		*/
		virtual void 		endPrimitive() = 0;						

		/** �л���2D��Ⱦ״̬
		@param left �ӿ���
		@param top �ӿ���
		@param width �ӿڿ�
		@param height �ӿڸ�
		*/
		virtual void 		switchTo2D(int left,int top,int width,int height) = 0;				

		/** �Ե�ǰ�ӿ�Ϊ�����л���2D��Ⱦ״̬
		*/
		virtual void 		switchTo2D() = 0;							

		/** �л���3D��Ⱦ״̬
		*/
		virtual void 		switchTo3D() = 0;							

		/** ��ǰ�Ƿ���2D״̬
		@return true��ʾ����2D״̬,false����
		*/
		virtual bool		is2dMode() = 0;							
		/*Slow*/																						
		virtual void 		render(const RenderOperation& ro) = 0;	
		/*For Convenience Only*/																		
		virtual void 		render(const RenderDirect& rd) = 0;		

		/** ������ͼѰַ��ʽ
		@param unit ��ͼ�Ĳ�����,��0��ʼ
		@param tamS S�����Ѱַ��ʽ
		@see TextureAddressingMode
		@param tamT T�����Ѱַ��ʽ
		*/
		virtual void 		setTextureWrap(ushort unit,const TextureAddressingMode& tamS,const TextureAddressingMode& tamT) = 0;			

		/** ������ͼѰַ��ʽ
		@param unit ��ͼ�Ĳ�����,��0��ʼ
		@param tam S�����Ѱַ��ʽ
		*/
		virtual void 		setTextureWrapS(ushort unit,const TextureAddressingMode& tam) = 0;			
		virtual TextureAddressingMode	getTextureWrapS(ushort unit) = 0;
		virtual TextureAddressingMode	getTextureWrapT(ushort unit) = 0;

		/** ������ͼѰַ��ʽ
		@param unit ��ͼ�Ĳ�����,��0��ʼ
		@param tam T�����Ѱַ��ʽ
		*/
		virtual void 		setTextureWrapT(ushort unit,const TextureAddressingMode& tam) = 0;			

		/** ������ͼ������㷽ʽ
		@param unit ��ͼ�Ĳ�����,��0��ʼ
		@param m ��ͼ������㷽ʽö��
		@see TexCoordCalcMethod
		*/
		virtual void 		setTextureCoordCalculation(ushort uint,TexCoordCalcMethod m) = 0;			

		/** ���õ�N����ͼ��Ԫ����ͼ
		@param unit ��ͼ�Ĳ�����,��0��ʼ
		@param pTexture ��ͼָ��
		*/
		virtual void 		setTexture(ushort unit,ITexture* pTexture) = 0;			

		/** ����ȫ�ֻ�������ɫ
		@param color ��������ɫ
		*/
		virtual void 		setAmbientLight(const ColorValue& color) = 0;			

		/** ��ȡȫ�ֻ�������ɫ
		@return ��������ɫ
		*/
		virtual const ColorValue& getAmbientLight() = 0;			

		/** ������ͼ���궥�㻺����
		@param unit ��ͼ�Ĳ�����,��0��ʼ
		@param pVB ���㻺�����ĵ�ַ
		@param start ��ʼ������±�,���Բ��ӵ�һ����ʼ
		*/
		virtual void 		setTexcoordVertexBuffer(ushort unit,IVertexBuffer* pVB,uint start = 0 ,uint stride = 0) = 0;

		/** ����λ�ö��㻺����
		@param pVB ���㻺�����ĵ�ַ
		@param start ��ʼ������±�,���Բ��ӵ�һ����ʼ
		*/
		virtual void 		setVertexVertexBuffer(IVertexBuffer* pVB,uint start = 0,uint stride = 0) = 0;				

		/** ���÷��߶��㻺����
		@param pVB ���㻺�����ĵ�ַ
		@param start ��ʼ������±�,���Բ��ӵ�һ����ʼ
		*/
		virtual void 		setNormalVertexBuffer(IVertexBuffer* pVB,uint start = 0 ,uint stride = 0) = 0;				

		/** ������ɫ���㻺����
		@param pVB ���㻺�����ĵ�ַ
		@param start ��ʼ������±�,���Բ��ӵ�һ����ʼ
		*/
		virtual void 		setDiffuseVertexBuffer(IVertexBuffer* pVB,uint start = 0 ,uint stride = 0) = 0;			

		/** ���þ���ⶥ�㻺����
		@param pVB ���㻺�����ĵ�ַ
		@param start ��ʼ������±�,���Բ��ӵ�һ����ʼ
		*/
		virtual void 		setSpecularVertexBuffer(IVertexBuffer* pVB,uint start = 0 ,uint stride = 0) = 0;		

		/** ��������������
		@param pIB �����������ĵ�ַ
		*/
		virtual void 		setIndexBuffer(IIndexBuffer* pIB) = 0;	

		/** ���ƴ������ļ�����״
		@param pt ������״������
		@see PrimitiveType
		@param ui32IndexCount ������Ŀ
		@param it ��������
		@see IndexType
		*/
		virtual void 		drawIndexedPrimitive(PrimitiveType pt,uint ui32IndexCount,IndexType it,void* pdata=0) = 0;

		/** ���ƴ������Ĵ���Χ�ļ�����״
		@param pt ������״������
		@see PrimitiveType
		@param ui32IndexStart ��ʼ�������±�
		@param ui32IndexCount ������Ŀ
		@param ui32VertexStart ��ʼ�Ķ����±�
		@param ui32VertexEnd �����Ķ����±�
		@param it ��������
		@see IndexType
		*/
		virtual void 		drawRangeIndexedPrimitive(													
		PrimitiveType pt,														
		IndexType it,															
		uint ui32IndexStart,													
		uint ui32IndexCount,													
		uint ui32VertexStart,													
		uint ui32VertexEnd) = 0;			

		/** ���Ʋ��������ļ�����״
		@param pt ������״������
		@param ui32VertexStart ��ʼ�Ķ����±�
		@param ui32VertexCount ������Ŀ
		@see PrimitiveType
		*/
		virtual void 		drawPrimitive(PrimitiveType pt,uint ui32VertexStart,uint ui32VertexCount) = 0;

		/** ���������
		@param mode �������
		@see FogMode
		@param color ��ɫ
		@param expDensity EXP���͵������
		@param linearStart ������Ŀ�ʼ����
		@param linearEnd ������Ľ�������
		@see ColorValue
		*/
		virtual void 		setFog(FogMode mode,														
		const ColorValue& color = ColorValue::Black,						
		float expDensity = 0.001,											
		float linearStart = 0.0,												
		float linearEnd = 1.0) = 0;	

		virtual void	enableFog(bool enable) = 0;

		virtual bool	isFogEnabled() = 0;

		/** ���õƹ�
		@param unit �ƹ�ĵ�Ԫ,��ʾҪ���õڼ�յ��
		@param pLight �ƹ�����
		@see Light
		*/
		virtual void 		setLight(ushort unit,Light* pLight) = 0;

		/** ���ò��ʲ�����ɫ�����
		@param diffuse ���������ɫ
		*/
		virtual void 		setSurfaceDiffuse(const ColorValue &diffuse) = 0;

		virtual const ColorValue&	getSurfaceDiffuse() = 0;

		/** ���ò��ʲ�����ɫ�����
		@param ambient ��������ɫ
		@param diffuse ���������ɫ
		@param specular �������ɫ
		@param emissive ���������ɫ
		@param shininess Specular exponent of material
		@see ColorValue
		*/
		virtual void 		setSurfaceParams(															
		const ColorValue &ambient,											
		const ColorValue &diffuse,											
		const ColorValue &specular,											
		const ColorValue &emissive,											
		float shininess) = 0;			

		/** ����setColor����Ӱ�����ɫ����,Ambient,Diffuse��
		@param tracking ��ɫ����ö��
		@see TrackVertexColorEnum
		*/
		virtual void 		setTrackingColorEnum(TrackVertexColorEnum tracking) = 0;

		/** ���õ�ǰ��Ĵ�С
		@param size ���С
		*/
		virtual void 		setPointSize(float size) = 0;			

		/** ���ø��Ӳü���
		@param index �±�,�ڼ����ü���
		@param pPlane ������
		*/
		virtual void 		setClipPlane(uint index,const Plane* pPlane) = 0;		

		/** ���ݵ�ǰ�ľ�������,����ͶӰһ��ͶӰ����ϵ�еĵ㵽��������ϵ
		@param v ͶӰ����ϵ�еĵ�
		@return ��������ͶӰ��ĵ�����,��������ϵ
		*/
		virtual Vector3		unproject(const Vector3& v) = 0;		

		/** ���ݵ�ǰ�ľ�������,ͶӰһ���ֲ�����ϵ�еĵ�
		@param v �ֲ�����ϵ�еĵ�
		@return ����ͶӰ��ĵ�����
		*/
		virtual Vector3		project(const Vector3& v) = 0;			

		/** �����Ƿ�򿪴�ֱͬ��
		@param vsync true��򿪴�ֱͬ��,false��ر�,Ĭ��Ϊfalse
		*/
		virtual void 		setVerticalSync(bool vsync) = 0;		

		/** Turns stencil buffer checking on or off.
		@remarks
		Stencilling (masking off areas of the rendering target based on the stencil 
		buffer) canbe turned on or off using this method. By default, stencilling is
		disabled.
		*/
		virtual void  setStencilCheckEnabled(bool enabled) = 0;		

		/** This method allows you to set all the stencil buffer parameters in one call.
		@remarks
		The stencil buffer is used to mask out pixels in the render target, allowing
		you to do effects like mirrors, cut-outs, stencil shadows and more. Each of
		your batches of rendering is likely to ignore the stencil buffer, 
		update it with new values, or apply it to mask the output of the render.
		The stencil test is:<PRE>
		(Reference Value & Mask) CompareFunction (Stencil Buffer Value & Mask)</PRE>
		The result of this will cause one of 3 actions depending on whether the test fails,
		succeeds but with the depth buffer check still failing, or succeeds with the
		depth buffer check passing too.
		@par
		Unlike other render states, stencilling is left for the application to turn
		on and off when it requires. This is because you are likely to want to change
		parameters between batches of arbitrary objects and control the ordering yourself.
		In order to batch things this way, you'll want to use OGRE's separate render queue
		groups (see RenderQueue) and register a RenderQueueListener to get notifications
		between batches.
		@par
		There are individual state change methods for each of the parameters set using 
		this method. 
		Note that the default values in this method represent the defaults at system 
		start up too.
		@param func The comparison function applied.
		@param refValue The reference value used in the comparison
		@param mask The bitmask applied to both the stencil value and the reference value 
		before comparison
		@param stencilFailOp The action to perform when the stencil check fails
		@param depthFailOp The action to perform when the stencil check passes, but the
		depth buffer check still fails
		@param passOp The action to take when both the stencil and depth check pass.
		@param twoSidedOperation If set to true, then if you render both back and front faces 
		(you'll have to turn off culling) then these parameters will apply for front faces, 
		and the inverse of them will happen for back faces (keep remains the same).
		*/
		virtual void  setStencilBufferParams(CompareFunction func = CMPF_ALWAYS_PASS,					
		uint refValue = 0, uint mask = 0xFFFFFFFF,												
		StencilOperation stencilFailOp = SOP_KEEP,													
		StencilOperation depthFailOp = SOP_KEEP,													
		StencilOperation passOp = SOP_KEEP) = 0;				

		/** ������ɫ�����Red,Green,Blud,Alphaλ�Ƿ����д
		@param red true�����д��ɫ����redλ
		@param green true�����д��ɫ����greenλ
		@param blue true�����д��ɫ����blueλ
		@param alpha true�����д��ɫ����alphaλ
		*/
		virtual void setColorBufferWriteEnabled(bool red, bool green, bool blue, bool alpha) = 0;

		/**��ʼ���г���ѡȡ
		@param ptX ��Ļ����x
		@param ptY ��Ļ����y
		*/
		virtual void beginSelection(int ptX,int ptY,uint variance = 0) = 0;

		/**��������ѡȡ����ѡȡ�Ľ������pBuffer��num����ѡ�е���Ŀ��������64��
		@param num[IN,OUT] ����pBuffer�Ĵ�С������ѡ�е���Ŀ
		@param pBuffer ����ѡ�еĽ��
		*/
		virtual void endSelection(int& num,int* pBuffer) = 0;

		/**����ѡ������
		@param index ����
		*/
		virtual void setSelectionIndex(int index) = 0;

		/**���RenderTarget
		@param hwnd ���ھ��
		@return �Ƿ�ɹ�
		*/
		virtual bool addRenderTarget(uint hwnd) = 0;

		/**ɾ����ȾĿ��
		@param hwnd ���ھ��
		@return �Ƿ�ɹ�
		*/
		virtual bool removeRenderTarget(uint hwnd) = 0;

		/**���߳����RenderTarget
		@param hwnd ���ھ��
		@return �Ƿ�ɹ�
		*/
		virtual uint MTaddRenderTarget(int layer = 0) = 0;

		/**���߳�ɾ����ȾĿ��
		@param hwnd ���ھ��
		@return �Ƿ�ɹ�
		*/
		virtual bool MTremoveRenderTarget(uint key) = 0;

		/**���Overlay RenderTarget
		@note ֻ�ܴ���һ��
		*/
		virtual bool addOverlayRenderTarget() = 0;

		/**ɾ��Overlay RenderTarget
		*/
		virtual void removeOverlayRenderTarget() = 0;

		/**��Overlay RenderTarget����Ϊ��ǰRenderTarget
		*/
		virtual bool setOverlayRenderTarget() = 0;

		/**��õ�ǰ����ȾĿ��
		@return ��ǰ����ȾĿ��Ĵ��ھ����������RTT�ľ��
		*/
		virtual uint getCurrentRenderTarget() = 0;

		/**���õ�ǰ����ȾĿ��
		@param hwnd ���ھ������RTT���
		@return �Ƿ�ɹ�
		*/
		virtual bool setCurrentRenderTarget(uint hwnd) = 0;

		/**����һ��RTT
		@param width ���
		@param height �߶�
		@param min ��С�˲���
		@param mag ����˲���
		@param mip mipmap�˲���ʽ
		@param s ����sѰַ��ʽ
		@param t ����tѰַ��ʽ
		@return ���ɵ�RTT�ľ��
		*/
		virtual uint addRTT(int width,int height, bool alpha = false,
			FilterOptions min = FO_LINEAR, 
			FilterOptions mag = FO_LINEAR, 
			FilterOptions mip = FO_NONE,
			TextureAddressingMode s = TAM_WRAP,											
			TextureAddressingMode t = TAM_WRAP)= 0;

		/**���RTT��ͼָ��
		@param hwnd RTT��������ڴ��ھ�����Ƿ���0
		@return ��ͼָ��
		*/
		virtual const ITexture*	getRenderTargetTexture(uint hwnd) = 0;

		/**�õ�RTT��ͼ����
		@param hwnd RTT��������ڴ��ھ����Ч
		@param pData ���صĻ�����
		@return �Ƿ�ɹ�
		@remarks �˺������ڵ�ͼ�༭������С��ͼ
		*/
		virtual bool getRenderTargetTextureData(uint hwnd,void  *pData) = 0;

		virtual bool isScissorEnabled() = 0;

		virtual void setScissorEnabled(bool enabled) = 0;

		/**����һ����Ƶ����
		@param pszFilename ��Ƶ�ļ�����
		@param type ��Ƶ�ļ����ͣ���enumVideoObjectType
		@param imgWidth ���ɵ�����Ŀ�ȣ�ֻ����ʾ����
		@param imgHeight ���ɵ�����ĸ߶ȣ�ֻ����ʾ����
		@return ��Ƶ����
		*/
		virtual IVideoObject * createVideoObject(const char * pszFilename, uint type, uint imgWidth, uint imgHeight ) = 0;

		//������ͼ����

		/** ��sizeΪ��С�ڵ�ǰλ�û�һ�����
		@param size ��С
		*/
		virtual void 		teapot(float size,const ColorValue& color) = 0;

		virtual void		line(const Point& ptFirst,const Point& ptSecond,const ColorValue& color) = 0;

		virtual void		rectangle(const Rect& rc,const ColorValue& color) = 0;

		virtual void		rectangle(const Rect& rc,const ColorValue& cLeftTop,const ColorValue& cLeftBottom,const ColorValue& cRightTop,const ColorValue& cRightBottom) = 0;

		virtual void		point(const Point& pt,const ColorValue& color) = 0;

		virtual void		rectangle(const Rect& rc,ITexture* pTexture) = 0;

		virtual void		rectangle(const Rect& rc,ITexture* pTexture, const Vector2 & vLetfTop, const Vector2 & vLeftBottom, const Vector2 & vRightBottom, const Vector2 & RightTop) = 0;

		virtual void		box(const Rect& rc,const ColorValue& color) = 0;

		virtual const RenderMode&	getRenderMode() = 0;

		virtual RenderSystemType getRenderSystemType() = 0;

		virtual bool		setTextureStageStatus( uint stage,
													TextureStageOperator colorOP,
													TextureStageArgument colorArg0,
													TextureStageArgument colorArg1,
													TextureStageOperator alphaOP,
													TextureStageArgument alphaArg0,
													TextureStageArgument alphaArg1)= 0;

		virtual void		getTextureStageStatus( uint stage,
													TextureStageOperator & colorOP,
													TextureStageArgument & colorArg0,
													TextureStageArgument & colorArg1,
													TextureStageOperator & alphaOP,
													TextureStageArgument & alphaArg0,
													TextureStageArgument & alphaArg1)= 0;

		virtual IHardwareCursorManager * getHardwareCursorManager() = 0;

		/** ���ö����ϵ�Ȩ�ض��㻺����
		@param pVB ���㻺�����ĵ�ַ
		@param start ��ʼ������±�,���Բ��ӵ�һ����ʼ
		*/
		virtual void		setBlendWeightVertexBuffer(IVertexBuffer* pVB, uint start=0)= 0;

		/** ���ö����ϵľ����������㻺����
		@param pVB ���㻺�����ĵ�ַ
		@param start ��ʼ������±�,���Բ��ӵ�һ����ʼ
		*/
		virtual void		setBlendIndicesVertexBuffer(IVertexBuffer* pVB, uint start=0) = 0;

		/** ��ȡ��ɫ�����������ָ��
		@return ��ɫ�����������ָ��
		*/
		virtual IShaderProgramManager* getShaderProgramManager()=0;

		/** ���֡����
		@param clearColorBuffer �Ƿ������ɫ����
		@param clearDepthBuffer �Ƿ������Ȼ���
		@param clearStencilBuffer �Ƿ����ģ�建��
		*/
		virtual void 		clearFrameBuffer(bool clearColorBuffer = true,bool clearDepthBuffer = true,bool clearStencilBuffer = false) = 0;

		/** ��ȡ��ǰ����ʾģʽ
		@param createParam ��ʾģʽ����
		*/
		virtual bool		getDisplayMode(RenderEngineCreationParameters & createParam) = 0;

		//-------kevin.chen �����ӿ�-------
		//�õ����õ�shaderprogram
		virtual IShaderProgram* getShaderProgram(int id) = 0;
		
		//���õ�ǰ�󶨵�shader,��Ϊ����Ӱ�֮ǰ��shader
		//�ýӿڿ���������shader������shader,����shader ��Ҫ��ע�������ڶԸýӿڵ�Ӱ��
		virtual void		bindCurrentShaderProgram(IShaderProgram* pShaderProgram) = 0;
	};
	/** @} */

}

#endif