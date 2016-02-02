#include "interface/Window.h"

#include "interface/Interface.h"

using fei::Window;

std::queue<GLFWwindow*> Window::delWindows;

Window::Window()
: sceneManager(nullptr),
  window(nullptr),
  contextRoot(nullptr),
  width(500),
  height(500),
  title(fei::EngineName),
  _isFullscreen(false),
  _isResizable(false),
  _isHide(true),
  _samples(0)
{
	sceneManager = new fei::SceneManager();
}

Window::~Window()
{
	delWindow();
	doDelWindows();
	delete sceneManager;
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
			show();
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

void Window::setSamples(int samples)
{
	_samples = samples;
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

		if (_samples > 0) {
			glfwWindowHint(GLFW_SAMPLES, _samples);
		}

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
		setCallback();
		glfwDefaultWindowHints();
	}
	return window;
}

void Window::delWindow()
{
	if (window) {
		unsetCallback();
		delWindows.push(window);
		window = nullptr;
	}
}

void Window::doDelWindows()
{
	while (!delWindows.empty()) {
		auto win = delWindows.front();
		delWindows.pop();
		if (win) {
			glfwDestroyWindow(win);
		}
	}
}

void Window::setCurrent()
{
	if (window) {
		glfwMakeContextCurrent(window);
		Interface::getInstance()->setCurrentWindow(this);
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
	if (window) {
		return glfwWindowShouldClose(window);
	} else {
		return 0;
	}
}

void Window::swapBuffers()
{
	if (window) {
		glfwSwapBuffers(window);
	}
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

int Window::getMouseButton(int button)
{
	int result = 0;
	if (window) {
		result = glfwGetMouseButton(window, button);
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

const fei::Vec2 Window::getRHCursorDeltaV()
{
	static Vec2 oldRHCursorPos = getRHCursorPos();
	Vec2 deltaV = getRHCursorPos() - oldRHCursorPos;
	oldRHCursorPos += deltaV;
	return deltaV;
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

const fei::Vec2 Window::getFrameSize()
{
	fei::Vec2 result;
	if (window) {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		result.set((float)width, (float)height);
	}
	return result;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto scene = fei::Interface::getInstance()->getCurrentWindow()->sceneManager->getCurScene();
	if (scene) {
		scene->keyCallback(key, scancode, action, mods);
	}
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	auto scene = fei::Interface::getInstance()->getCurrentWindow()->sceneManager->getCurScene();
	if (scene) {
		scene->mouseButtonCallback(button, action, mods);
	}
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	auto scene = fei::Interface::getInstance()->getCurrentWindow()->sceneManager->getCurScene();
	if (scene) {
		scene->cursorPosCallback(xpos, ypos);
	}
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	auto scene = fei::Interface::getInstance()->getCurrentWindow()->sceneManager->getCurScene();
	if (scene) {
		scene->scrollCallback(xoffset, yoffset);
	}
}

static void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	auto scene = fei::Interface::getInstance()->getCurrentWindow()->sceneManager->getCurScene();
	if (scene) {
		scene->charactorCallback(codepoint);
	}
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	auto scene = fei::Interface::getInstance()->getCurrentWindow()->sceneManager->getCurScene();
	if (scene) {
		scene->framebufferSizeCallback(width, height);
	}
}

static void drop_callback(GLFWwindow* window, int count, const char** paths)
{
	auto scene = fei::Interface::getInstance()->getCurrentWindow()->sceneManager->getCurScene();
	if (scene) {
		scene->dropCallback(count, paths);
	}
}

//TODO: Event queue for input control detection

void Window::setCallback()
{
	if (window) {
		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetCursorPosCallback(window, cursor_pos_callback);
		glfwSetScrollCallback(window, scroll_callback);
		glfwSetCharCallback(window, character_callback);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetDropCallback(window, drop_callback);
	}
}

void Window::unsetCallback()
{
	if (window) {
		glfwSetKeyCallback(window, nullptr);
		glfwSetMouseButtonCallback(window, nullptr);
		glfwSetCursorPosCallback(window, nullptr);
		glfwSetScrollCallback(window, nullptr);
		glfwSetCharCallback(window, nullptr);
		glfwSetFramebufferSizeCallback(window, nullptr);
		glfwSetDropCallback(window, nullptr);
	}
}
