#ifndef __RenderEngine_H__
#define __RenderEngine_H__

#include "IRenderEngine.h"
#include "RenderSystemHelper.h"
#include "Model\ModelManagerHelper.h"

namespace xs
{
	/*! \addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/


class RenderEngine : public IRenderEngine
{
public:
	/** ��Ⱦ��������
	*/
	virtual void 				release();											

	/** ��ȡ��Ⱦϵͳ�ӿ�
	@return ��Ⱦϵͳ�ӿ�
	*/
	virtual IRenderSystem*		getRenderSystem();												

	/** ��ȡģ�͹���ӿ�
	@return ģ�͹���ӿ�
	*/
	virtual IModelManager*		getModelManager();		

	/** ��ȡ�������ӿ�
	@return �������ӿ�
	*/
	virtual IFontManager*		getFontManager();			

	/** ���������
	@param pViewport �ӿ�
	@return �����ָ��
	*/
	virtual Camera*				createCamera(Viewport* pViewport);					

	/** �����ӿ�
	@return �ӿ�ָ��
	*/
	virtual Viewport*			createViewport();

	virtual const RenderEngineCreationParameters& getCreationParams();

public:
	RenderEngine();
	~RenderEngine();

public:
	IRenderSystem*		m_pRenderSystem;
	IModelManager*		m_pModelManager;

private:
	RenderSystemHelper	m_RenderSystem;
	ModelManagerHelper	m_ModelManager;
	RenderEngineCreationParameters	m_param;

	IModelManager*		createModelManager();
	void 				closeRenderSystem();
	virtual IRenderSystem*		createRenderSystem(RenderEngineCreationParameters *param);

public:
	bool			create(RenderEngineCreationParameters* param);
};
	/** @} */

}

#endif