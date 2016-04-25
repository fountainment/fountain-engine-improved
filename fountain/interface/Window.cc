#include "interface/Window.h"

#include "interface/Interface.h"

using fei::Window;

std::queue<GLFWwindow*> Window::delWindows_;

Window::Window()
: _window(nullptr),
  _contextRoot(nullptr),
  _width(500),
  _height(500),
  _title(fei::EngineName),
  _isFullscreen(false),
  _isResizable(false),
  _isHide(true),
  _isVsync(true),
  _samples(0)
{
	_sceneManager = new fei::SceneManager();
}

Window::~Window()
{
	delWindow();
	doDelWindows();
	delete _sceneManager;
}

void Window::setSize(int w, int h)
{
	_width = w;
	_height = h;
	if (_window) {
		glfwSetWindowSize(_window, w, h);
	}
}

void Window::setTitle(std::string tt)
{
	_title = tt;
	if (_window) {
		glfwSetWindowTitle(_window, tt.c_str());
	}
}

void Window::setResizable(bool resizable)
{
	_isResizable = resizable;
}

void Window::updateVsync()
{
	if (isCurrent()) {
		if (_isVsync) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}
	}
}

void Window::setVsync(bool vsync)
{
	_isVsync = vsync;
	updateVsync();
}

void Window::setFullscreen(bool fullscreen)
{
	if (_window) {
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
		_contextRoot = root->getWindow();
	}
}

GLFWwindow* Window::getWindow()
{
	if (!_window) {
		glfwDefaultWindowHints();
		auto monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		int w = _width, h = _height;

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
		_window = glfwCreateWindow(w, h, _title.c_str(), monitor, _contextRoot);
		glfwSetWindowUserPointer(_window, this);
		setCallback();
		glfwDefaultWindowHints();
	}
	return _window;
}

void Window::delWindow()
{
	if (_window) {
		unsetCallback();
		delWindows_.push(_window);
		_window = nullptr;
	}
}

void Window::doDelWindows()
{
	while (!delWindows_.empty()) {
		auto win = delWindows_.front();
		delWindows_.pop();
		if (win) {
			glfwDestroyWindow(win);
		}
	}
}

void Window::setCurrent()
{
	if (_window) {
		glfwMakeContextCurrent(_window);
		Interface::getInstance()->setCurrentWindow(this);
		updateVsync();
	}
}

bool Window::isCurrent()
{
	return _window != nullptr && \
		Interface::getInstance()->getCurrentWindow() == this;
}

void Window::hide()
{
	if (_window) {
		glfwHideWindow(_window);
	}
}

void Window::show()
{
	if (_window) {
		glfwShowWindow(_window);
	}
}

int Window::shouldClose()
{
	if (_window) {
		return glfwWindowShouldClose(_window);
	} else {
		return 0;
	}
}

void Window::swapBuffers()
{
	if (_window) {
		glfwSwapBuffers(_window);
	}
}

bool Window::isFullscreen()
{
	return _isFullscreen;
}

int Window::getKey(int key)
{
	int result = 0;
	if (_window) {
		result = glfwGetKey(_window, key);
	}
	return result;
}

int Window::getMouseButton(int button)
{
	int result = 0;
	if (_window) {
		result = glfwGetMouseButton(_window, button);
	}
	return result;
}

const fei::Vec2 Window::getKeyAxis()
{
	fei::Vec2 ret = fei::Vec2::ZERO;
	if (getKey(GLFW_KEY_UP)) {
		ret += fei::Vec2::UP;
	}
	if (getKey(GLFW_KEY_DOWN)) {
		ret += fei::Vec2::DOWN;
	}
	if (getKey(GLFW_KEY_LEFT)) {
		ret += fei::Vec2::LEFT;
	}
	if (getKey(GLFW_KEY_RIGHT)) {
		ret += fei::Vec2::RIGHT;
	}
	ret.normalize();
	return ret;
}

const fei::Vec2 Window::getCursorPos()
{
	fei::Vec2 result;
	if (_window) {
		double xpos, ypos;
		glfwGetCursorPos(_window, &xpos, &ypos);
		result.set(static_cast<float>(xpos), static_cast<float>(ypos));
	}
	return result;
}

const fei::Vec2 Window::getRHCursorPos()
{
	fei::Vec2 result;
	if (_window) {
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
	if (_window) {
		int width, height;
		glfwGetWindowSize(_window, &width, &height);
		result.set(static_cast<float>(width), static_cast<float>(height));
	}
	return result;
}

const fei::Vec2 Window::getFrameSize()
{
	fei::Vec2 result;
	if (_window) {
		int width, height;
		glfwGetFramebufferSize(_window, &width, &height);
		result.set(static_cast<float>(width), static_cast<float>(height));
	}
	return result;
}

const fei::Vec2 Window::getWindowPos()
{
	fei::Vec2 result;
	if (_window) {
		int xpos, ypos;
		glfwGetWindowPos(_window, &xpos, &ypos);
		result.set(static_cast<float>(xpos), static_cast<float>(ypos));
	}
	return result;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto scene = Window::getFeiWindow(window)->getSceneManager()->getCurScene();
	if (scene) {
		scene->keyCallback(key, scancode, action, mods);
	}
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	auto scene = Window::getFeiWindow(window)->getSceneManager()->getCurScene();
	if (scene) {
		scene->mouseButtonCallback(button, action, mods);
	}
}

static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	auto scene = Window::getFeiWindow(window)->getSceneManager()->getCurScene();
	if (scene) {
		scene->cursorPosCallback(xpos, ypos);
	}
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	auto scene = Window::getFeiWindow(window)->getSceneManager()->getCurScene();
	if (scene) {
		scene->scrollCallback(xoffset, yoffset);
	}
}

static void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	auto scene = Window::getFeiWindow(window)->getSceneManager()->getCurScene();
	if (scene) {
		scene->charactorCallback(codepoint);
	}
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	auto scene = Window::getFeiWindow(window)->getSceneManager()->getCurScene();
	if (scene) {
		scene->framebufferSizeCallback(width, height);
	}
}

static void drop_callback(GLFWwindow* window, int count, const char** paths)
{
	auto scene = Window::getFeiWindow(window)->getSceneManager()->getCurScene();
	if (scene) {
		scene->dropCallback(count, paths);
	}
}

//TODO: Event queue for input control detection

void Window::setCallback()
{
	if (_window) {
		glfwSetKeyCallback(_window, key_callback);
		glfwSetMouseButtonCallback(_window, mouse_button_callback);
		glfwSetCursorPosCallback(_window, cursor_pos_callback);
		glfwSetScrollCallback(_window, scroll_callback);
		glfwSetCharCallback(_window, character_callback);
		glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
		glfwSetDropCallback(_window, drop_callback);
	}
}

void Window::unsetCallback()
{
	if (_window) {
		glfwSetKeyCallback(_window, nullptr);
		glfwSetMouseButtonCallback(_window, nullptr);
		glfwSetCursorPosCallback(_window, nullptr);
		glfwSetScrollCallback(_window, nullptr);
		glfwSetCharCallback(_window, nullptr);
		glfwSetFramebufferSizeCallback(_window, nullptr);
		glfwSetDropCallback(_window, nullptr);
	}
}

Window* Window::getFeiWindow(GLFWwindow* window)
{
	return static_cast<Window*>(glfwGetWindowUserPointer(window));
}
