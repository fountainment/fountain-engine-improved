#include "fountain.h"

using fei::Application;
using fei::Engine;

Engine::Engine()
: _window(nullptr)
{
}

bool Engine::init()
{
	bool flag = loadModule();
	_shouldExit = false;
	return flag;
}

void Engine::destroy()
{
	unloadModule();
}

bool Engine::createWindow()
{
	getWindow()->setContextRoot(fei::Interface::getInstance()->getRootWindow());
	if (getWindow()->getWindow()) {
		getWindow()->setCurrent();
		fei::Render::getInstance()->setViewport(fei::Rect(getWindow()->getFrameSize()));
		return true;
	} else {
		return false;
	}
}

void Engine::mainLoop()
{
	while (!shouldExit()) {
		executeBeforeFrame();
		getWindow()->getSceneManager()->renderCurScene();
		executeAfterFrame();
	}
}

void Engine::run()
{
	createWindow();
	getWindow()->show();
	mainLoop();
}

void Engine::exit()
{
	_shouldExit = true;
}

bool Engine::loadModule()
{
	bool loadSuccess = true;
	
	_moduleList.push_back(Time::getInstance());
	_moduleList.push_back(Interface::getInstance());
	_moduleList.push_back(Control::getInstance());
	_moduleList.push_back(Audio::getInstance());
	_moduleList.push_back(Physics::getInstance());
	_moduleList.push_back(Font::getInstance());
	_moduleList.push_back(Render::getInstance());

	for (auto module : _moduleList) {
		if (!module || !module->feiInit()) {
			loadSuccess = false;
			return loadSuccess;
		}
	}

	_window = Interface::getInstance()->applyNewWindow();

	return loadSuccess;
}

void Engine::unloadModule()
{
	if (_window) {
		_window->getSceneManager()->destroyCurScene();
		Interface::getInstance()->destroyWindow(_window);
	}
	for (auto it = _moduleList.rbegin(); it != _moduleList.rend(); ++it) {
		if (*it) {
			if ((*it)->isLoaded()) {
				(*it)->feiDestroy();
			}
		}
	}
	_moduleList.clear();
}

bool Engine::shouldExit()
{
	return _shouldExit || getWindow()->shouldClose();
}

void Engine::executeBeforeFrame()
{
	for (auto module : _moduleList) {
		module->executeBeforeFrame();
	}
}

void Engine::executeAfterFrame()
{
	for (auto it = _moduleList.rbegin(); it != _moduleList.rend(); ++it) {
		(*it)->executeAfterFrame();
	}
}


Application::Application()
{
	_engine = nullptr;
}

Application::~Application()
{
	unloadEngine();
}

bool Application::loadEngine()
{
	bool loadSuccess = false;
	if (!_engine) {
	_engine = new Engine();
		if (_engine) {
			loadSuccess = _engine->feiInit();
		}
	} else {
		loadSuccess = _engine->isLoaded();
	}
	return loadSuccess;
}

void Application::unloadEngine()
{
	if (_engine) {
		_engine->feiDestroy();
		delete _engine;
		_engine = nullptr;
	}
}

void Application::engineSetting(Engine *engine)
{
}

void Application::run()
{
	bool loadSuccess = loadEngine();
	if (loadSuccess && _engine) {
		engineSetting(_engine);
		_engine->run();
	} else {
		//TODO: Debug output
	}
	unloadEngine();
}

Engine* Application::getEngine()
{
	return _engine;
}

Engine *Application::_engine = nullptr;

