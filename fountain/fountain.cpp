#include "fountain.h"

using fei::Engine;
using fei::Application;

Engine::Engine()
: window(nullptr)
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
	moduleList.push_back(Font::getInstance());

	for (auto module : moduleList) {
		if (!module || !module->feiInit()) {
			loadSuccess = false;
			return loadSuccess;
		}
	}

	window = Interface::getInstance()->applyNewWindow();

	return loadSuccess;
}

void Engine::unloadModule()
{
	if (window) {
		Interface::getInstance()->destroyWindow(window);
	}
	for (auto it = moduleList.rbegin(); it != moduleList.rend(); ++it) {
		if (*it) {
			if ((*it)->isLoaded()) {
				(*it)->feiDestroy();
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
			loadSuccess = engine->feiInit();
		}
	} else {
		loadSuccess = engine->isLoaded();
	}
	return loadSuccess;
}

void Application::unloadEngine()
{
	if (engine) {
		engine->feiDestroy();
		delete engine;
		engine = nullptr;
	}
}

void Application::engineSetting(Engine *engine)
{
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

