#include "Window.h"
#include <GL/glew.h>

using fei::Window;

Window::Window()
: window(nullptr),
  contextRoot(nullptr),
  width(500),
  height(500),
  title(fei::EngineName),
  _isFullscreen(false),
  _isHide(false)
{
}

Window::~Window()
{
	delWindow();
}

void Window::setSize(int w, int h)
{
	width = w;
	height = h;
	if (window) {
		glfwSetWindowSize(window, w, h);
	}
}

void Window::setTitle(std::string tt)
{
	title = tt;
	if (window) {
		glfwSetWindowTitle(window, tt.c_str());
	}
}

void Window::setResizable(bool resizable)
{
	_isResizable = resizable;
}

void Window::setFullscreen(bool fullscreen)
{
	if (window) {
		if (fullscreen != _isFullscreen) {
			hide();
			delWindow();
			_isFullscreen = fullscreen;
			getWindow();
			setCurrent();
			return;
		}
	} else {
		_isFullscreen = fullscreen;
	}
}

void Window::setHide(bool isHide)
{
	_isHide = isHide;
	if (_isHide) {
		hide();
	} else {
		show();
	}
}

void Window::setContextRoot(Window* root)
{
	if (root) {
		contextRoot = root->getWindow();
	}
}

GLFWwindow* Window::getWindow()
{
	if (!window) {
		glfwDefaultWindowHints();
		auto monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		int w = width, h = height;
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		if (_isHide) {
			glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
		}
		if (!_isResizable) {
			glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		}
		if (_isFullscreen) {
			w = mode->width;
			h = mode->height;
		} else {
			monitor = nullptr;
		}
		window = glfwCreateWindow(w, h, title.c_str(), monitor, contextRoot);
		glfwDefaultWindowHints();
	}
	return window;
}

void Window::delWindow()
{
	if (window) {
		glfwDestroyWindow(window);
		window = nullptr;
	}
}

void Window::setCurrent()
{
	if (window) {
		glfwMakeContextCurrent(window);
	}
}

void Window::hide()
{
	if (window) {
		glfwHideWindow(window);
	}
}

void Window::show()
{
	if (window) {
		glfwShowWindow(window);
	}
}

int Window::shouldClose()
{
	return glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

bool Window::isFullscreen()
{
	return _isFullscreen;
}

int Window::getKey(int key)
{
	int result = 0;
	if (window) {
		result = glfwGetKey(window, key);
	}
	return result;
}

const fei::Vec2 Window::getCursorPos()
{
	fei::Vec2 result;
	if (window) {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		result.set((float)xpos, (float)ypos);
	}
	return result;
}

const fei::Vec2 Window::getRHCursorPos()
{
	fei::Vec2 result;
	if (window) {
		result = getCursorPos();
		result.y = getWindowSize().y - 1 - result.y;
	}
	return result;
}

const fei::Vec2 Window::getWindowSize()
{
	fei::Vec2 result;
	if (window) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		result.set((float)width, (float)height);
	}
	return result;
}

