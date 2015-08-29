#include "scene/SceneManager.h"
#include "interface/Interface.h"

using fei::SceneManager;

SceneManager::SceneManager()
: curScene(nullptr)
{
}

void SceneManager::destroyCurScene()
{
	if (curScene) {
		curScene->feiDestroy();
		delete curScene;
		curScene = nullptr;
	}
}

fei::Scene* SceneManager::getCurScene()
{
	return curScene;
}

void SceneManager::gotoScene(fei::Scene* scene)
{
	destroyCurScene();
	curScene = scene;
	curScene->setClock(&defaultClock);
	curScene->feiInit();
}

void SceneManager::renderCurScene()
{
	defaultClock.tick();
	defaultCamera.update();
	if (curScene) {
		curScene->feiUpdate();
		curScene->draw();
	}
}

SceneManager* SceneManager::getCurrentSceneManager()
{
	SceneManager *ans = nullptr;
	auto window = Interface::getInstance()->getCurrentWindow();
	if (window) {
		ans = window->sceneManager;
	}
	return ans;
}
