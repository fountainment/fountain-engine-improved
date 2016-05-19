#include "interface/Interface.h"

#include <GLFW/glfw3.h>

using fei::Interface;

Interface* Interface::instance_ = nullptr;

Interface* Interface::getInstance()
{
	if (!instance_) {
		instance_ = new Interface();
	}
	return instance_;
}

Interface::Interface()
: _rootWindow(nullptr),
  _currentWindow(nullptr)
{
}

bool Interface::init()
{
	if (GLFW_FALSE == glfwInit()) {
		return false;
	} else {
		std::printf("GLFW Version: %s\n", glfwGetVersionString());
		createRootWindow();
	}
	return true;
}

void Interface::destroy()
{
	destroyAllWindows();
	glfwTerminate();
}

fei::Window* Interface::applyNewWindow()
{
	auto ptr = new fei::Window();
	_windowList.push_back(ptr);
	return ptr;
}

void Interface::destroyWindow(fei::Window* window)
{
	auto result = find(_windowList.begin(), _windowList.end(), window);
	if (result != _windowList.end()) {
		_windowList.erase(result);
		delete window;
	}
}

void Interface::destroyAllWindows()
{
	for (auto it = _windowList.rbegin(); it != _windowList.rend(); ++it) {
		delete *it;
	}
	_windowList.clear();
	delete _rootWindow;
	_rootWindow = nullptr;
}

void Interface::createRootWindow()
{
	if (!_rootWindow) {
		_rootWindow = new fei::Window();
		_rootWindow->setHide(true);
		_rootWindow->getWindow();
		_rootWindow->setCurrent();
	}
}

fei::Window* Interface::getRootWindow()
{
	return _rootWindow;
}

void Interface::setCurrentWindow(fei::Window* window)
{
	_currentWindow = window;
}

fei::Window* Interface::getCurrentWindow()
{
	return _currentWindow;
}

const fei::Vec2 Interface::getCursorPos()
{
	if (!_currentWindow) {
		return fei::Vec2::ZERO;
	}
	return _currentWindow->getCursorPos();
}

const fei::Vec2 Interface::getRHCursorPos()
{
	if (!_currentWindow) {
		return fei::Vec2::ZERO;
	}
	return _currentWindow->getRHCursorPos();
}

const fei::Vec2 Interface::getWindowSize()
{
	if (!_currentWindow) {
		return fei::Vec2::ZERO;
	}
	return _currentWindow->getWindowSize();
}

void Interface::executeAfterFrame()
{
	_currentWindow->swapBuffers();
	glfwPollEvents();
	Window::doDelWindows();
}

