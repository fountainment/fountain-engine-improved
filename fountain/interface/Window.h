#ifndef _FEI_WINDOW_H_
#define _FEI_WINDOW_H_

//TODO: save window's position

#include <GLFW/glfw3.h>

#include "base/basedef.h"
#include "base/ModuleBase.h"
#include "scene/SceneManager.h"
#include "math/Vec2.h"

namespace fei {

class Window
{
public:
	Window();
	~Window();

	void setSize(int w, int h);
	void setTitle(std::string tt);
	void setResizable(bool resizable);
	void setFullscreen(bool fullscreen);
	void setHide(bool isHide);
	void setSamples(int samples);

	void updateVsync();
	void setVsync(bool vsync);

	void setContextRoot(Window* root);

	GLFWwindow* getWindow(); 
	void delWindow();
	static void doDelWindows();

	void setCurrent();
	bool isCurrent();

	void hide();
	void show();

	int shouldClose();
	void swapBuffers();

	bool isFullscreen();

	int getKey(int key);
	int getMouseButton(int button);
	const Vec2 getCursorPos();
	const Vec2 getRHCursorPos();
	const Vec2 getRHCursorDeltaV();
	const Vec2 getWindowSize();
	const Vec2 getFrameSize();
	const Vec2 getWindowPos();

	SceneManager* getSceneManager() const;

private:
	void setCallback();
	void unsetCallback();

	GLFWwindow *_window;
	GLFWwindow *_contextRoot;

	int _width;
	int _height;
	std::string _title;

	bool _isFullscreen;
	bool _isResizable;
	bool _isHide;
	bool _isVsync;
	int _samples;

	SceneManager *_sceneManager;

	static std::queue<GLFWwindow*> delWindows_;
};

} // namespace fei

inline fei::SceneManager* fei::Window::getSceneManager() const
{
	return _sceneManager;
}

#endif // _FEI_WINDOW_H_
