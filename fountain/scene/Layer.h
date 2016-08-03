#ifndef _FEI_LAYER_H_
#define _FEI_LAYER_H_

#include "render/Camera.h"
#include "render/RenderList.h"

namespace fei {

class Layer : public RenderList
{
public:
	Layer();

	virtual void drawIt();

	void setCamera(Camera* camera);
	Camera* getCamera();
	void cameraPush();
	void cameraPop();
	//TODO: design control signal catch logic

private:
	bool _didCameraPush;
	Camera *_oldCamera;
	Camera *_layerCamera;
};

} // namespace fei

#endif // _FEI_LAYER_H_
