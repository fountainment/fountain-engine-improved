#if !defined(_FEI_LAYER_H_)
#define _FEI_LAYER_H_

#include "render/Camera.h"
#include "render/RenderList.h"

namespace fei {

class Layer : public RenderList
{
public:
	Layer();

	Camera *layerCamera;
	virtual void cameraUpdate();
	//TODO: design control signal catch logic
};

}

#endif
