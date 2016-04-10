#include "scene/SceneManager.h"

#include "interface/Interface.h"

using fei::SceneManager;

SceneManager::SceneManager()
: _curScene(nullptr),
  _nextScene(nullptr),
  _doDestroyCurScene(false)
{
	defaultCamera.setCameraSize(Vec2::ONE);
	defaultCamera.setPosition(Vec2::ZERO);
}

SceneManager::~SceneManager()
{
	destroyCurScene();
}

void SceneManager::destroyCurScene()
{
	if (_curScene) {
		_curScene->feiDestroy();
		delete _curScene;
		_curScene = nullptr;
	}
}

fei::Scene* SceneManager::getCurScene()
{
	return _curScene;
}

void SceneManager::gotoScene(fei::Scene* goScene, bool destroyCurrent)
{
	if (_curScene) {
		_doDestroyCurScene = destroyCurrent;
	}
	_nextScene = goScene;
}

void SceneManager::renderCurScene()
{
	defaultCamera.update();
	if (_curScene) {
		_curScene->feiUpdate();
		_curScene->draw();
	}
	if (_doDestroyCurScene) {
		destroyCurScene();
		_doDestroyCurScene = false;
	}
	if (_nextScene) {
		_curScene = _nextScene;
		_curScene->setClock(&defaultClock);
		_curScene->feiInit();
		_nextScene = nullptr;
	}
}

SceneManager* SceneManager::getCurrentSceneManager()
{
	SceneManager *ans = nullptr;
	auto window = Interface::getInstance()->getCurrentWindow();
	if (window) {
		ans = window->getSceneManager();
	}
	return ans;
}
