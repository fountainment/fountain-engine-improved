#include "Interface.h"
#include <GLFW/glfw3.h>

using fei::Interface;

Interface* Interface::instance = nullptr;

Interface* Interface::getInstance()
{
	if (!instance) {
		instance = new Interface();
	}
	return instance;
}

Interface::Interface()
{
}

bool Interface::init()
{
	if (_isLoad) return true;
	_isLoad = true;
	if (GL_FALSE == glfwInit()) {
		_isLoad = false;
	} else {
		glfwSwapInterval(1);
	}
	return _isLoad;
}

void Interface::destroy()
{
	if (!_isLoad) return;
	destroyAllWindows();
	glfwTerminate();
	_isLoad = false;
}

fei::Window* Interface::applyNewWindow()
{
	auto ptr = new fei::Window();
	windowList.push_back(ptr);
	return ptr;
}

void Interface::destroyWindow(fei::Window* window)
{
	delete window;
	for (auto it = windowList.begin(); it != windowList.end(); ++it) {
		if ((*it) == window) {
			it = windowList.erase(it);
			--it;
		}
	}
}

void Interface::destroyAllWindows()
{
	for (auto it = windowList.end() - 1; it != windowList.begin() - 1; --it) {
		delete *it;
	}
	windowList.clear();
}

void Interface::executeAfterFrame()
{
	for (auto it = windowList.end() - 1; it != windowList.begin() - 1; --it) {
		(*it)->swapBuffers();
		(*it)->pollEvents();
	}
}

