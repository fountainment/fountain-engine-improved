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
	~SceneManager();

	void destroyCurScene();
	Scene* getCurScene();

	void gotoScene(Scene* goScene, bool destroyCurrent = true);

	void renderCurScene();

	static SceneManager* getCurrentSceneManager();

	Camera defaultCamera;
	Clock defaultClock;

private:
	Scene *curScene;
	Scene *nextScene;

	bool doDestroyCurScene;
};

}

#endif
