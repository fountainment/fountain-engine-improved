#include "fountain.h"

using fei::Engine;
using fei::Application;

Engine::Engine()
: window(nullptr)
{
}

bool Engine::init()
{
	if (_isLoad) return true;
	_isLoad = loadModule();
	_shouldExit = false;
	return _isLoad;
}

void Engine::destroy()
{
	if (!_isLoad) return;
	unloadModule();
	_isLoad = false;
}

bool Engine::createWindow()
{
	window->setContextRoot(fei::Interface::getInstance()->getRootWindow());
	if (window->getWindow()) {
		window->setCurrent();
		return true;
	} else {
		return false;
	}
}

void Engine::mainLoop()
{
	while (!shouldExit()) {
		executeBeforeFrame();
		window->sceneManager->renderCurScene();
		executeAfterFrame();
	}
}

void Engine::run()
{
	createWindow();
	mainLoop();
}

void Engine::exit()
{
	_shouldExit = true;
}

bool Engine::loadModule()
{
	bool loadSuccess = true;
	
	moduleList.push_back(Time::getInstance());
	moduleList.push_back(Interface::getInstance());
	moduleList.push_back(Control::getInstance());
	moduleList.push_back(Render::getInstance());
	moduleList.push_back(Audio::getInstance());
	moduleList.push_back(Physics::getInstance());

	for (auto module : moduleList) {
		if (!module || !module->init()) {
			loadSuccess = false;
			break;
		}
	}

	window = Interface::getInstance()->applyNewWindow();

	return loadSuccess;
}

void Engine::unloadModule()
{
	Interface::getInstance()->destroyWindow(window);
	for (auto it = moduleList.rbegin(); it != moduleList.rend(); ++it) {
		if (*it) {
			if ((*it)->isLoad()) {
				(*it)->destroy();
			}
			delete (*it);
		}
	}
	moduleList.clear();
}

bool Engine::shouldExit()
{
	return _shouldExit || window->shouldClose();
}

void Engine::executeBeforeFrame()
{
	for (auto module : moduleList) {
		module->executeBeforeFrame();
	}
}

void Engine::executeAfterFrame()
{
	for (auto it = moduleList.rbegin(); it != moduleList.rend(); ++it) {
		(*it)->executeAfterFrame();
	}
}


Application::Application()
{
	engine = nullptr;
}

Application::~Application()
{
	unloadEngine();
}

bool Application::loadEngine()
{
	bool loadSuccess = false;
	if (!engine) {
		engine = new Engine();
		if (engine) {
			loadSuccess = engine->init();
		}
	} else {
		loadSuccess = engine->isLoad();
	}
	return loadSuccess;
}

void Application::unloadEngine()
{
	if (engine) {
		engine->destroy();
		delete engine;
		engine = nullptr;
	}
}

void Application::run()
{
	bool loadSuccess = loadEngine();
	if (loadSuccess && engine) {
		engineSetting(engine);	
		engine->run();
	} else {
		//TODO: Debug output
	}
	unloadEngine();
}

Engine* Application::getEngine()
{
	return engine;
}

Engine *Application::engine = nullptr;

