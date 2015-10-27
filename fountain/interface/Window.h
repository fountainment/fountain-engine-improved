#if !defined(_FEI_WINDOW_H_)
#define _FEI_WINDOW_H_

//TODO: save window's position

#include "base/basedef.h"
#include "base/ModuleBase.h"
#include "scene/SceneManager.h"
#include "math/Vec2.h"
#include <GLFW/glfw3.h>

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

	void setContextRoot(Window* root);

	GLFWwindow* getWindow(); 
	void delWindow();

	void setCurrent();

	void hide();
	void show();

	int shouldClose();
	void swapBuffers();

	bool isFullscreen();

	int getKey(int key);
	int getMouseButton(int button);
	const Vec2 getCursorPos();
	const Vec2 getRHCursorPos();
	const Vec2 getWindowSize();
	const Vec2 getFrameSize();

	SceneManager *sceneManager;

private:
	void setCallback();

	GLFWwindow *window;
	GLFWwindow *contextRoot;

	int width, height;
	std::string title;

	bool _isFullscreen;
	bool _isResizable;
	bool _isHide;
};

}

#endif
