#if !defined(_FEI_SCENE_H_)
#define _FEI_SCENE_H_

#include "scene/Layer.h"
#include "time/Clock.h"
#include "render/Camera.h"

namespace fei {

class Scene : public Layer
{
public:
	Clock sceneClock;
	Camera sceneCamera;

	virtual void drawIt();

	void cameraUpdate();
};

}

#endif

