#include "Interface.h"
#include <GL/glew.h>
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
	auto it = windowList.begin();
	while (it != windowList.end()) {
		if ((*it) == window) {
			it = windowList.erase(it);
		} else {
			++it;
		}
	}
}

void Interface::destroyAllWindows()
{
	for (auto it = windowList.rbegin(); it != windowList.rend(); ++it) {
		delete *it;
	}
	windowList.clear();
}

void Interface::executeAfterFrame()
{
	for (auto it = windowList.rbegin(); it != windowList.rend(); ++it) {
		(*it)->swapBuffers();
		(*it)->pollEvents();
	}
}

