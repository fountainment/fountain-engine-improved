#include "Window.h"

using fei::Window;

Window::Window()
{
	glfwDefaultWindowHints();
	window = nullptr;
	width = height = 500;
	title = fei::EngineName;
	_isFullscreen = false;
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
	auto hint = GL_FALSE;
	if (resizable) {
		hint = GL_TRUE;
	}
	glfwWindowHint(GLFW_RESIZABLE, hint);
}

void Window::setFullscreen(bool fullscreen)
{
	if (window) {
		if (fullscreen != _isFullscreen) {
			hide();
			delWindow();
			_isFullscreen = fullscreen;
			getWindow();
			return;
		}
	}
	_isFullscreen = fullscreen;
}

GLFWwindow* Window::getWindow()
{
	if (!window) {
		auto monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		int w = width, h = height;
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		if (_isFullscreen) {
			w = mode->width;
			h = mode->height;
		} else {
			monitor = nullptr;
		}
		window = glfwCreateWindow(w, h, title.c_str(), monitor, NULL);
	}
	setCurrent();
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

bool Window::shouldClose()
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

