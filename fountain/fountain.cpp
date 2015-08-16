#include "fountain.h"

using fei::Engine;
using fei::Application;

Engine::Engine()
: window(nullptr),
  //for test
  frameFunc(nullptr)
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
		//TODO: move basic key events to Interface::executeBeforeFrame()
		if (window->getKey(GLFW_KEY_F11)) {
			window->setFullscreen(!window->isFullscreen());
		}
		//for test
		if (frameFunc) {
			frameFunc();
		}
		std::printf("%f %lld\n", Time::getInstance()->getTime(), Time::getInstance()->getFrame());
		//TODO: add SceneManager
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

//for test
void Engine::setFrameFunc(void (*frameF)())
{
	frameFunc = frameF;
}

bool Engine::loadModule()
{
	bool loadSuccess = true;
	
	moduleList.push_back(Time::getInstance());

	auto interface = Interface::getInstance();
	interface->init();
	moduleList.push_back(interface);

	moduleList.push_back(Render::getInstance());

	//Temporary window for glewInit() to run correctly
	window = Interface::getInstance()->applyNewWindow();
	window->getWindow();
	window->setCurrent();
	window->hide();

	for (auto module : moduleList) {
		if (!module || !module->init()) {
			loadSuccess = false;
			break;
		}
	}

	//Delete temporary window
	window->delWindow();

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
	bool result = _shouldExit || window->shouldClose();
	return result;
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
	if (engine) {
		unloadEngine();
	}
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

