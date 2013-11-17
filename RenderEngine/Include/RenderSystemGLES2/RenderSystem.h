#ifndef __RenderSystem_H__
#define __RenderSystem_H__

#include "RenderTarget.h"



namespace xs{

class RenderSystem : public IRenderSystem
{
public:
	/** �ͷ���Ⱦϵͳ
	*/
	virtual void			release();

	/** ��ȡ��Ⱦϵͳ�����ƣ���"OpenGL","D3D9"��
	@return ��Ⱦϵͳ���Ƶ��ַ���
	*/
	virtual const char*		getName();							

	/** �����Ⱦϵͳ����ָ��
	@return ��Ⱦϵͳ����ָ��
	*/
	virtual RenderSystemCapabilities*	getCapabilities();	

	/** �����ӿ�
	@param pViewport �ӿ�ָ��
	*/
	virtual void 		setViewport(int left,int top,int width,int height);			

	/** ��ȡ�ӿ�����
	@param left �ӿھ��봰����ߵľ���
	@param top �ӿھ��봰���ϱߵľ���
	@param width �ӿڵĿ��
	@param height �ӿڵĸ߶�
	*/
	virtual void 		getViewport(int &left,int &top,int &width,int &height);		

	/** ��������ӿڵı���ɫ
	@param color ����ɫ
	*/
	virtual void 		setClearColor(const ColorValue& color);
	virtual const ColorValue& getClearColor();				

	/** ���������Ȼ����ֵ���������Ȼ���ʱ����Ȼ����ÿ����λ�������ó����ֵ
	@param depth ���ֵ��Ĭ����������ֵ
	*/
	virtual void 		setClearDepth(float depth);			

	/** �������ģ�建���ֵ
	@param stencil ���ģ�建���ֵ��Ĭ����0
	*/
	virtual void 		setClearStencil(int stencil = 0);	

	/** ����ͶӰ����
	@param mtx ͶӰ����
	*/
	virtual void 		setProjectionMatrix(const Matrix4& mtx);			

	/** �����Ӿ���
	@param mtx �Ӿ���
	*/
	virtual void 		setViewMatrix(const Matrix4& mtx);	

	/** �����������
	@param mtx �������
	*/
	virtual void 		setWorldMatrix(const Matrix4 &mtx);	

	/** ��ȡͶӰ����
	@return ��ǰ��Ⱦϵͳ��ͶӰ����
	*/
	virtual const Matrix4&		getProjectionMatrix();		

	/** ��ȡ�Ӿ���
	@return ��ǰ��Ⱦϵͳ���Ӿ���
	*/
	virtual const Matrix4&		getViewMatrix();			

	/** ��ȡ�������
	@return ��ǰ��Ⱦϵͳ���������
	*/
	virtual const Matrix4&		getWorldMatrix();			

	/** ��ȡ��ͼ�������
	@return ��ͼ�������������Multiply
	*/
	virtual const Matrix4&		getModelViewMatrix();		

	/** ��ʼ����һ��
	@param clearColorBuffer �Ƿ������ɫ����
	@param clearDepthBuffer �Ƿ������Ȼ���
	@param clearStencilBuffer �Ƿ����ģ�建��
	*/
	virtual void 		beginFrame(bool clearColorBuffer = true,bool clearDepthBuffer = true,bool clearStencilBuffer = false);

	/** ��������һ��,��beginFrame����ʹ��
	*/
	virtual void 		endFrame(int layer);							

	/** �����Ƿ����д��Ȼ���
	@param enabled true������,false������,Ĭ��Ϊtrue
	*/
	virtual void 		setDepthBufferWriteEnabled(bool enabled);			

	/** ��ȡ�Ƿ����д��Ȼ���
	@return true��ʾ����,false������
	*/
	virtual bool		isDepthBufferWriteEnabled();		

	/** �����Ƿ�򿪵ƹ�
	@param enabled true������,false������,Ĭ��Ϊfalse
	*/
	virtual void 		setLightingEnabled(bool enabled);	

	/** ��ȡ�ƹ��Ƿ���
	@return true��ʾ����,false��ر�
	*/
	virtual bool		isLightingEnabled();				

	/** �������ģʽ
	@param sdl ���ģʽ
	@see FillMode
	*/
	virtual void 		setFillMode(const FillMode& sdl);	

	/** ��ȡ���ģʽ
	@return ���ģʽ
	@see FillMode
	*/
	virtual const FillMode&	getFillMode();					

	/** ���������Ŀ��
	@param width ������ȣ���beginPrimitive(PT_LINES)����Ч
	*/
	virtual void setLineWidth(float width);

	/** ��ȡ�����Ŀ��
	@return �������
	*/
	virtual float getLineWidth();

	/** �����Ƿ��������У��
	@param enabled true������,false������,Ĭ��Ϊfalse
	*/
	virtual void 		setDepthBufferCheckEnabled(bool enabled);			

	/** ��ȡ��ǰϵͳ�Ƿ��������У��
	@return true��ʾ����,false������
	*/
	virtual bool		isDepthBufferCheckEnabled();		

	/** �������У�麯��
	@param cf ���У�麯��,Ĭ��ΪCMPF_LESS
	@see CompareFunction
	*/
	virtual void 		setDepthBufferFunction(const CompareFunction& cf);	

	virtual const CompareFunction& getDepthBufferFunction();

	/** ��ȡAlphaУ�麯���Ͳο�ֵ
	@param cf AlphaУ�麯��
	@param value �ο�ֵ
	@see CompareFunction
	*/
	virtual void 		getAlphaFunction(CompareFunction& cf,float& value);	

	/** ����AlphaУ�麯��
	@param cf AlphaУ�麯��,Ĭ��ΪCMPF_ALWAYS
	@param value �ο�ֵ,��cfΪһ����Ҫ�ο�ֵ�ĺ���ʱ
	@see CompareFunction
	*/
	virtual void 		setAlphaFunction(const CompareFunction& cf,float value);

	/** ����AlphaУ�麯��
	@param cf AlphaУ�麯��,Ĭ��ΪCMPF_ALWAYS
	@param value �ο�ֵ,value / 255����һ��������һ����
	@see CompareFunction
	*/
	virtual void 		setAlphaFunction(const CompareFunction& cf,uchar value);

	/** ��ȡ�Ƿ�����AlphaУ��
	@return true��ʾ����,false������
	*/
	virtual bool		alphaCheckEnabled();				

	/** �����Ƿ�����AlphaУ��
	@param bEnabled true��ʾ����,false������,Ĭ��Ϊfalse
	@param value �ο�ֵ,��cfΪһ����Ҫ�ο�ֵ�ĺ���ʱ
	*/
	virtual void 		setAlphaCheckEnabled(bool bEnabled);

	/** ���ñ���ü���ʽ
	@param cm �ü���ʽ
	@see CullingMode
	*/
	virtual void 		setCullingMode(const CullingMode& cm);

	/** ���ñ߱��
	@param bEdgeFlag true��򿪱߱��,false��ر�,Ĭ��Ϊtrue
	*/
	virtual void 		setEdgeFlag(bool bEdgeFlag);		

	/** ��ȡ����ü���ʽ
	@return ����ü���ʽ
	@see CullingMode
	*/
	virtual const		CullingMode& getCullingMode();		

	/** ���ó�����ϲ���
	@param src Դ��ϲ���,Ĭ��ΪSBF_ONE
	@param dst Ŀ���ϲ���,Ĭ��ΪSBF_ZERO
	@see SceneBlendFactor
	*/
	virtual void 		setSceneBlending(const SceneBlendFactor& src,const SceneBlendFactor& dst);

	/** ��ȡ������ϲ���
	@param src Դ��ϲ���
	@param dst Ŀ���ϲ���
	@see SceneBlendFactor
	*/
	virtual void 		getSceneBlending(SceneBlendFactor& src,SceneBlendFactor& dst);			

	/** ����������Ⱦ����
	@param param ��Ⱦ����
	@see RenderEngineCreationParameters
	@return true��ʾ�ɹ�,��֮ʧ��
	*/
	virtual bool		switchDisplayMode(RenderEngineCreationParameters* param);				

	/** ��ȡ������������ָ��
	@return ������������ָ��
	*/
	virtual IBufferManager*		getBufferManager();			

	/** ��ȡ��ͼ������ָ��
	@return ��ͼ������ָ��
	*/
	virtual ITextureManager*	getTextureManager();		


	/** ���õ�ǰ��ͼ��ɫ,���еƹ�������,��ɫ��Ч
	@param color ��ɫֵ
	@see ColorValue
	*/
	virtual void 		setColor(const ColorValue& color);	

	/** ��ȡ��ǰ��ͼ��ɫ
	@return ��ɫֵ
	*/
	virtual const ColorValue& getColor();					

	/** ���õ�ǰ����ֵ
	@param normal ����
	@see Vector3
	*/
	virtual void 		setNormal(const Vector3& normal);	

	/** ���õ�ǰ��ͼ����
	@param texcoord ��ͼ����
	*/
	virtual void 		setTexcoord(const Vector2& texcoord);

	/** ���õ�ǰ��ͼ����
	@param texcoord ��ͼ����
	*/
	virtual void 		setMultiTexcoord(ushort unit,const Vector2& texcoord);

	/** ���Ͷ���
	@param vertex ��������
	*/
	virtual void 		sendVertex(const Vector2& vertex);	

	/** ���Ͷ���
	@param vertex ��������
	*/
	virtual void 		sendVertex(const Vector3& vertex);	

	/** ���Ͷ���
	@param vertex ��������
	*/
	virtual void 		sendVertex(const Vector4& vertex);	

	/** ��ʼ����һ����״
	@param pt ��ͼ����
	@see PrimitiveType
	*/
	virtual void 		beginPrimitive(PrimitiveType pt);	

	/** ��������һ����״,��beginPrimitive����ʹ��
	*/
	virtual void 		endPrimitive();						

	/** �л���2D��Ⱦ״̬
	@param left �ӿ���
	@param top �ӿ���
	@param width �ӿڿ�
	@param height �ӿڸ�
	*/
	virtual void 		switchTo2D(int left,int top,int width,int height);				

	/** �Ե�ǰ�ӿ�Ϊ�����л���2D��Ⱦ״̬
	*/
	virtual void 		switchTo2D();							

	/** �л���3D��Ⱦ״̬,��begin2D����ʹ��
	*/
	virtual void 		switchTo3D();							

	/** ��ǰ�Ƿ���2D״̬
	@return true��ʾ����2D״̬,false����
	*/
	virtual bool		is2dMode();							
	/*Slow*/																						
	virtual void 		render(const RenderOperation& ro);	
	/*For Convenience Only*/																		
	virtual void 		render(const RenderDirect& rd);		

	/** ������ͼѰַ��ʽ
	@param unit ��ͼ�Ĳ�����,��0��ʼ
	@param tamS S�����Ѱַ��ʽ
	@see TextureAddressingMode
	@param tamT T�����Ѱַ��ʽ
	*/
	virtual void 		setTextureWrap(ushort unit,const TextureAddressingMode& tamS,const TextureAddressingMode& tamT);			

	/** ������ͼѰַ��ʽ
	@param unit ��ͼ�Ĳ�����,��0��ʼ
	@param tam S�����Ѱַ��ʽ
	*/
	virtual void 		setTextureWrapS(ushort unit,const TextureAddressingMode& tam);			
	virtual TextureAddressingMode	getTextureWrapS(ushort unit);
	virtual TextureAddressingMode	getTextureWrapT(ushort unit);

	/** ������ͼѰַ��ʽ
	@param unit ��ͼ�Ĳ�����,��0��ʼ
	@param tam T�����Ѱַ��ʽ
	*/
	virtual void 		setTextureWrapT(ushort unit,const TextureAddressingMode& tam);			

	/** ������ͼ������㷽ʽ
	@param unit ��ͼ�Ĳ�����,��0��ʼ
	@param m ��ͼ������㷽ʽö��
	@see TexCoordCalcMethod
	*/
	virtual void 		setTextureCoordCalculation(ushort uint,TexCoordCalcMethod m);			

	/** ���õ�N����ͼ��Ԫ����ͼ
	@param unit ��ͼ�Ĳ�����,��0��ʼ
	@param pTexture ��ͼָ��
	*/
	virtual void 		setTexture(ushort unit,ITexture* pTexture);			

	/** ����ȫ�ֻ�������ɫ
	@param color ��������ɫ
	*/
	virtual void 		setAmbientLight(const ColorValue& color);			

	/** ��ȡȫ�ֻ�������ɫ
	@return ��������ɫ
	*/
	virtual const ColorValue& getAmbientLight();			

	/** ������ͼ���궥�㻺����
	@param unit ��ͼ�Ĳ�����,��0��ʼ
	@param pVB ���㻺�����ĵ�ַ
	@param start ��ʼ������±�,���Բ��ӵ�һ����ʼ
	*/
	virtual void 		setTexcoordVertexBuffer(ushort unit,IVertexBuffer* pVB,uint start = 0 ,uint stride = 0);

	/** ����λ�ö��㻺����
	@param pVB ���㻺�����ĵ�ַ
	@param start ��ʼ������±�,���Բ��ӵ�һ����ʼ
	*/
	virtual void 		setVertexVertexBuffer(IVertexBuffer* pVB,uint start = 0,uint stride = 0);				

	/** ���÷��߶��㻺����
	@param pVB ���㻺�����ĵ�ַ
	@param start ��ʼ������±�,���Բ��ӵ�һ����ʼ
	*/
	virtual void 		setNormalVertexBuffer(IVertexBuffer* pVB,uint start = 0 ,uint stride = 0);				

	/** ������ɫ���㻺����
	@param pVB ���㻺�����ĵ�ַ
	@param start ��ʼ������±�,���Բ��ӵ�һ����ʼ
	*/
	virtual void 		setDiffuseVertexBuffer(IVertexBuffer* pVB,uint start = 0 ,uint stride = 0);			

	/** ���þ���ⶥ�㻺����
	@param pVB ���㻺�����ĵ�ַ
	@param start ��ʼ������±�,���Բ��ӵ�һ����ʼ
	*/
	virtual void 		setSpecularVertexBuffer(IVertexBuffer* pVB,uint start = 0 ,uint stride = 0);	

	/** ��������������
	@param pIB �����������ĵ�ַ
	*/
	virtual void 		setIndexBuffer(IIndexBuffer* pIB);	

	/** ���ƴ������ļ�����״
	@param pt ������״������
	@see PrimitiveType
	@param ui32IndexCount ������Ŀ
	@param it ��������
	@see IndexType
	*/
	virtual void 		drawIndexedPrimitive(PrimitiveType pt,uint ui32IndexCount,IndexType it,void* pdata=0);

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
		uint ui32VertexEnd);			

	/** ���Ʋ��������ļ�����״
	@param pt ������״������
	@param ui32VertexStart ��ʼ�Ķ����±�
	@param ui32VertexCount ������Ŀ
	@see PrimitiveType
	*/
	virtual void 		drawPrimitive(PrimitiveType pt,uint ui32VertexStart,uint ui32VertexCount);

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
		float linearEnd = 1.0);

	virtual void	enableFog(bool enable);

	virtual bool	isFogEnabled();

	/** ���õƹ�
	@param unit �ƹ�ĵ�Ԫ,��ʾҪ���õڼ�յ��
	@param pLight �ƹ�����
	@see Light
	*/
	virtual void 		setLight(ushort unit,Light* pLight);

	const ColorValue&	getSurfaceDiffuse();

	virtual void setSurfaceDiffuse(const ColorValue &diffuse);

	/** ���ò��ʲ�����ɫ��������
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
		float shininess);			

	/** ����setColor����Ӱ�����ɫ����,Ambient,Diffuse��
	@param tracking ��ɫ����ö��
	@see TrackVertexColorEnum
	*/
	virtual void 		setTrackingColorEnum(TrackVertexColorEnum tracking);

	/** ���õ�ǰ��Ĵ�С
	@param size ���С
	*/
	virtual void 		setPointSize(float size);			

	/** ���ø��Ӳü���
	@param index �±�,�ڼ����ü���
	@param pPlane ������
	*/
	virtual void 		setClipPlane(uint index,const Plane* pPlane);				

	/** ���ݵ�ǰ�ľ�������,����ͶӰһ��ͶӰ����ϵ�еĵ㵽��������ϵ
	@param v ͶӰ����ϵ�еĵ�
	@return ��������ͶӰ��ĵ�����,��������ϵ
	*/
	virtual Vector3		unproject(const Vector3& v);		

	/** ���ݵ�ǰ�ľ�������,ͶӰһ���ֲ�����ϵ�еĵ�
	@param v �ֲ�����ϵ�еĵ�
	@return ����ͶӰ��ĵ�����
	*/
	virtual Vector3		project(const Vector3& v);			

	/** �����Ƿ�򿪴�ֱͬ��
	@param vsync true��򿪴�ֱͬ��,false��ر�,Ĭ��Ϊfalse
	*/
	virtual void 		setVerticalSync(bool vsync);		

	/** Turns stencil buffer checking on or off.
	@remarks
	Stencilling (masking off areas of the rendering target based on the stencil 
	buffer) canbe turned on or off using this method. By default, stencilling is
	disabled.
	*/
	virtual void  setStencilCheckEnabled(bool enabled);		

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
		StencilOperation passOp = SOP_KEEP);				

	/** ������ɫ�����Red,Green,Blud,Alphaλ�Ƿ����д
	@param red true�����д��ɫ����redλ
	@param green true�����д��ɫ����greenλ
	@param blue true�����д��ɫ����blueλ
	@param alpha true�����д��ɫ����alphaλ
	*/
	virtual void setColorBufferWriteEnabled(bool red, bool green, bool blue, bool alpha);

	/**��ʼ���г���ѡȡ
	@param ptX ��Ļ����x
	@param ptY ��Ļ����y
	*/
	virtual void beginSelection(int ptX,int ptY,uint variance);

	/**��������ѡȡ����ѡȡ�Ľ������pBuffer��num����ѡ�е���Ŀ��������64��
	@param num[IN,OUT] ����pBuffer�Ĵ�С������ѡ�е���Ŀ
	@param pBuffer ����ѡ�еĽ��
	*/
	virtual void endSelection(int& num,int* pBuffer);

	/**����ѡ������
	@param index ����
	*/
	virtual void setSelectionIndex(int index);

	/**���RenderTarget
	@param hwnd ���ھ��
	@return �Ƿ�ɹ�
	*/
	virtual bool addRenderTarget(uint hwnd);

	/**ɾ����ȾĿ��
	@param hwnd ���ھ��
	@return �Ƿ�ɹ�
	*/
	virtual bool removeRenderTarget(uint hwnd);

	/**���߳����RenderTarget
	@param hwnd ���ھ��
	@return �Ƿ�ɹ�
	*/
	virtual uint MTaddRenderTarget(int layer);

	/**���߳�ɾ����ȾĿ��
	@param hwnd ���ھ��
	@return �Ƿ�ɹ�
	*/
	virtual bool MTremoveRenderTarget(uint key);

	/**���Overlay RenderTarget
	@note ֻ�ܴ���һ��
	*/
	virtual bool addOverlayRenderTarget();

	/**ɾ��Overlay RenderTarget
	*/
	virtual void removeOverlayRenderTarget();

	/**��Overlay RenderTarget����Ϊ��ǰRenderTarget
	*/
	virtual bool setOverlayRenderTarget();

	/**��õ�ǰ����ȾĿ��
	@return ��ǰ����ȾĿ��Ĵ��ھ����������RTT�ľ��
	*/
	virtual uint getCurrentRenderTarget();

	/**���õ�ǰ����ȾĿ��
	@param hwnd ���ھ������RTT���
	@return �Ƿ�ɹ�
	*/
	virtual bool setCurrentRenderTarget(uint hwnd);

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
		TextureAddressingMode t = TAM_WRAP);

	/**���RTT��ͼָ��
	@param hwnd RTT��������ڴ��ھ�����Ƿ���0
	@return ��ͼָ��
	*/
	virtual const ITexture*	getRenderTargetTexture(uint hwnd);

	/**�õ�RTT��ͼ����
	@param hwnd RTT��������ڴ��ھ����Ч
	@param pData ���صĻ�����
	@return �Ƿ�ɹ�
	@remarks �˺������ڵ�ͼ�༭������С��ͼ
	*/
	virtual bool getRenderTargetTextureData(uint hwnd,void  *pData);

	virtual bool isScissorEnabled();

	virtual void setScissorEnabled(bool enabled);

	virtual IVideoObject * createVideoObject(const char * pszFilename, uint type , uint imgWidth, uint imgHeight);

	/** ��sizeΪ��С�ڵ�ǰλ�û�һ�����
	@param size ��С
	*/
	virtual void 		teapot(float size,const ColorValue& color);

	virtual void		line(const Point& ptFirst,const Point& ptSecond,const ColorValue& color);

	virtual void		rectangle(const Rect& rc,const ColorValue& color);

	virtual void		rectangle(const Rect& rc,const ColorValue& cLeftTop,const ColorValue& cLeftBottom,const ColorValue& cRightTop,const ColorValue& cRightBottom);

	virtual void		point(const Point& pt,const ColorValue& color);

	virtual void		rectangle(const Rect& rc,ITexture* pTexture);

	virtual void		rectangle(const Rect& rc,ITexture* pTexture, const Vector2 & vLetfTop, const Vector2 & vLeftBottom, const Vector2 & vRightBottom, const Vector2 & RightTop);

	virtual void		box(const Rect& rc,const ColorValue& color);

	virtual const RenderMode&	getRenderMode();

	virtual RenderSystemType getRenderSystemType();

	virtual bool		setTextureStageStatus(	
		uint stage,
		TextureStageOperator colorOP,
		TextureStageArgument colorArg0,
		TextureStageArgument colorArg1,
		TextureStageOperator alphaOP,
		TextureStageArgument alphaArg0,
		TextureStageArgument alphaArg1);

	virtual void		getTextureStageStatus(	
		uint stage,
		TextureStageOperator & colorOP,
		TextureStageArgument & colorArg0,
		TextureStageArgument & colorArg1,
		TextureStageOperator & alphaOP,
		TextureStageArgument & alphaArg0,
		TextureStageArgument & alphaArg1);

	virtual IHardwareCursorManager * getHardwareCursorManager();

	/** ���ö����ϵ�Ȩ�ض��㻺����
	@param pVB ���㻺�����ĵ�ַ
	@param start ��ʼ������±�,���Բ��ӵ�һ����ʼ
	*/
	virtual void		setBlendWeightVertexBuffer(IVertexBuffer* pVB, uint start=0);

	/** ���ö����ϵľ����������㻺����
	@param pVB ���㻺�����ĵ�ַ
	@param start ��ʼ������±�,���Բ��ӵ�һ����ʼ
	*/
	virtual void		setBlendIndicesVertexBuffer(IVertexBuffer* pVB, uint start=0);

	/** ��ȡ��ɫ�����������ָ��
	@return ��ɫ�����������ָ��
	*/
	virtual IShaderProgramManager* getShaderProgramManager();

	/** ���֡����
	@param clearColorBuffer �Ƿ������ɫ����
	@param clearDepthBuffer �Ƿ������Ȼ���
	@param clearStencilBuffer �Ƿ����ģ�建��
	*/
	virtual void 		clearFrameBuffer(bool clearColorBuffer = true,bool clearDepthBuffer = true,bool clearStencilBuffer = false);

	/** ��ȡ��ǰ����ʾģʽ
	@param createParam ��ʾģʽ����
	*/
	virtual bool		getDisplayMode(RenderEngineCreationParameters & createParam);

	virtual IShaderProgram* getShaderProgram(int id);

	virtual void		bindCurrentShaderProgram(IShaderProgram* pShaderProgram,bool setShaderConst = false);
public:
	TextureStageOperator getTextureStageOp(GLint op);
	GLint				 getTextureStageOp( TextureStageOperator op);
	TextureStageArgument getTextureStageArg(GLint arg);
	GLint				 getTextureStageArg(TextureStageArgument arg);

	RenderSystem();

	bool	create(RenderEngineCreationParameters *);

	void	close();
private:
	void	setDefaultMatrix(uint cx,uint cy);
	GLint	convertCompareFunction(CompareFunction func) const;
	GLint	getBlendMode(SceneBlendFactor blend) const;
	void	initCapabilities();
	bool	checkMinGLVersion(const std::string& v) const;
	void 	setRenderState(RenderTarget::RenderState *pRenderState);
private:
	IIndexBuffer*	m_pIndexBuffer;

	RenderSystemCapabilities	m_rsc;
	std::string	m_strVersion;
	std::string	m_strVendor;
	std::string	m_strRenderer;
	std::string	m_strExtensions;

	uchar	m_stencilBuffer;
	float	m_lineWidth;
	bool	m_scissorEnabled;

	ushort	m_textureUnit;

public:
    
#if (TARGET_PLATFORM == PLATFORM_WIN32)
	HDC			m_hDC;
	HWND		m_hWnd;
	EGLContext	m_hRC;
	
	EGLDisplay	m_eglDisplay;
	EGLConfig	m_eglConfig;
	EGLSurface	m_eglSurface;
#elif (TARGET_PLATFORM == PLATFORM_IOS)
    void*       m_hWnd;           //ios uiview
    void*       m_pContext;
#else
   
#endif

	ColorValue	m_surfaceDiffuse;
private:
	// Selection
	GLuint m_SelectionBuffer[64];

private:
	// MultiRenderTarget
	typedef HASH_MAP_NAMESPACE::hash_map<uint,RenderTarget*> RenderTargetType;
	RenderTargetType	m_vRenderTarget;
	RenderTargetType	m_vRenderTargetMT;
	RenderTarget* initializeRenderTarget(HWND hWnd,int layer);
	uint	m_currentRenderTarget;
	RenderTarget*	m_pCurrentRenderTarget;
	RenderTarget*	m_pOverlayRenderTarget;

	static bool	m_sCapabilitiesInit;
	static std::list<IRenderSystem*>		m_vRenderSystems;

	RenderMode		m_RenderMode;


//add by kevin.chen
	ITexture*	    m_pWhiteTex;				
	void			_setTempTexture();

	IHighLevelShaderProgram* m_pCurrentShaderProgram;
	
	bool			_createInnerShader();
	void			_releaseInnerShader();
	IHighLevelShaderProgram* m_pInnerShader[ESP_NUM];
	void			_setWorldViewProj2Shader();
//-----Ϊ����setVetext��setTexCoord֮���ԭ�ӿڣ����еĸ���buff batch cache
#define VERTEX_CACHE_MAX 80 //������,must be 4 �ı���!
	struct BatchStatus
	{
		PrimitiveType pt;				//��ǰpt
		bool		  isPrimitiveing;	//�Ƿ������ύ״̬

		union
		{
			unsigned int vertexflag;	//��¼�����������Ƿ���

			struct  
			{
				bool vertex		: 1;	
				bool normal		: 1;
				bool texCoord0  : 1;
				bool texCoord1	: 1;
			}
			flagBits;

		};

		Vector3*		vertexs;
		Vector3*		normals;
		Vector2*		texCoord0s;
		Vector2*		texCoord1s;
		unsigned int*   colors;	//һ������ɫ

		unsigned short* indexs;  //ֻ���������ı���

		unsigned int	vertexCount;
		unsigned int	normalCount;
		unsigned int	texCoord0Count;
		unsigned int	texCoord1Count;
		unsigned int	colorCount;

		BatchStatus();
		~BatchStatus();

		bool isOverCache(unsigned int count);
		void clear();
	};

	BatchStatus m_batchStatus;
	void _checkCacheAndFlush(unsigned int count);
	void _flush();
	
};

}

#endif