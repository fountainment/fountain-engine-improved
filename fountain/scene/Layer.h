#if !defined(_FEI_LAYER_H_)
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
	//TODO: design control signal catch logic

private:
	bool didCameraPush;
	Camera *layerCamera;

	void cameraPush();
	void cameraPop();
};

}

#endif
