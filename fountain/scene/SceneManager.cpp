#include "scene/SceneManager.h"

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
	curScene->feiInit();
}

void SceneManager::renderCurScene()
{
	if (curScene) {
		curScene->feiUpdate();
		curScene->draw();
	}
}
