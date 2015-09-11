#include "scene/SceneManager.h"
#include "interface/Interface.h"

using fei::SceneManager;

SceneManager::SceneManager()
: curScene(nullptr),
  nextScene(nullptr),
  doDestroyCurScene(false)
{
}

SceneManager::~SceneManager()
{
	destroyCurScene();
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

void SceneManager::gotoScene(fei::Scene* goScene, bool destroyCurrent)
{
	if (curScene) {
		doDestroyCurScene = destroyCurrent;
	}
	nextScene = goScene;
}

void SceneManager::renderCurScene()
{
	defaultClock.tick();
	defaultCamera.update();
	if (curScene) {
		curScene->feiUpdate();
		curScene->draw();
	}
	if (doDestroyCurScene) {
		destroyCurScene();
		doDestroyCurScene = false;
	}
	if (nextScene) {
		curScene = nextScene;
		curScene->setClock(&defaultClock);
		curScene->feiInit();
		nextScene = nullptr;
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
