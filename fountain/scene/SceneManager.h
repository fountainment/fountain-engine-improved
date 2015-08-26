#if !defined(_FEI_SCENEMANAGER_H_)
#define _FEI_SCENEMANAGER_H_

#include "scene/Scene.h"
#include "render/Camera.h"
#include "time/Clock.h"

namespace fei {

class SceneManager
{
public:
	SceneManager();

	void destroyCurScene();
	Scene* getCurScene();

	void gotoScene(Scene* scene);

	void renderCurScene();

private:
	Scene *curScene;
	Camera sceneCamera;
	Clock sceneClock;
};

}

#endif
