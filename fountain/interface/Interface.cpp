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
: rootWindow(nullptr),
  currentWindow(nullptr)
{
}

bool Interface::init()
{
	if (GL_FALSE == glfwInit()) {
		return false;
	} else {
		std::printf("GLFW Version: %s\n", glfwGetVersionString());
		glfwSwapInterval(1);
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
	delete rootWindow;
	windowList.clear();
	rootWindow = nullptr;
}

void Interface::createRootWindow()
{
	if (!rootWindow) {
		rootWindow = new fei::Window();
		rootWindow->setHide(true);
		rootWindow->getWindow();
		rootWindow->setCurrent();
	}
}

fei::Window* Interface::getRootWindow()
{
	return rootWindow;
}

void Interface::setCurrentWindow(fei::Window* window)
{
	currentWindow = window;
}

fei::Window* Interface::getCurrentWindow()
{
	return currentWindow;
}

void Interface::executeAfterFrame()
{
	for (auto it = windowList.rbegin(); it != windowList.rend(); ++it) {
		(*it)->swapBuffers();
		(*it)->pollEvents();
	}
}

