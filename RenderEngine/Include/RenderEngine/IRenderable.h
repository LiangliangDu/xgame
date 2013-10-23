#ifndef __I_Renderable_H__
#define __I_Renderable_H__

namespace xs
{
	/*! \addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/

	struct IRenderSystem;
	class Material;

	/** ����Ⱦ�ӿ�
	*/
	struct IRenderable
	{
		/** ��Ⱦ
		@param pRenderSystem ��Ⱦϵͳ�ӿ�ָ��
		*/
		virtual void  render(IRenderSystem* pRenderSystem,bool useMtl = true) = 0;
	};
	/** @} */
}

#endif