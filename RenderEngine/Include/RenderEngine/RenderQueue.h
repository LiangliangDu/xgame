#ifndef __RenderQueue_H__
#define __RenderQueue_H__

#include <set>
#include "IRenderable.h"

namespace xs
{
	/*! \addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/

	struct IRenderable;

	/** ��Ⱦ���У�����IRenderable���Ͷ���
	*/
	class _RenderEngineExport RenderQueue
	{
	public:
		RenderQueue();
		void 	clear();
		void 	add(IRenderable* pRenderable,int renderOrder);
		void 	render(IRenderSystem* pRenderSystem,bool useMtl);
	private:
		typedef std::vector<IRenderable*> RenderableList;
		RenderableList	m_vRenderableList[RENDER_QUEUE_COUNT];
	};
	/** @} */

}
#endif