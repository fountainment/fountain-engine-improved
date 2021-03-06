#ifndef _FEI_WINDOW_H_
#define _FEI_WINDOW_H_

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
	void setSize(const Vec2& size);
	void setTitle(std::string tt);
	void setResizable(bool resizable);
	void setFullscreen(bool fullscreen);
	void setHide(bool isHide);
	void setHideCursor(bool isHide);
	void setBlockCursor(bool isBlock);
	void setSamples(int samples);
	void setClipboard(const std::string& str);

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

	void hideCursor();
	void blockCursor();
	void showCursor();

	int shouldClose();
	void swapBuffers();

	bool isFullscreen();

	int getKey(int key);
	int getMouseButton(int button);

	const Vec2 getKeyAxis();
	const Vec2 getCursorPos();
	const Vec2 getRHCursorPos();
	const Vec2 getRHCursorDeltaV();
	const Vec2 getWindowSize();
	const Vec2 getFrameSize();
	const Vec2 getWindowPos();

	const std::string getClipboard();

	SceneManager* getSceneManager() const;

	static Window* getFeiWindow(GLFWwindow* window);

private:
	void setCallback();
	void unsetCallback();

	GLFWwindow *_window;
	GLFWwindow *_contextRoot;

	int _windowedWidth;
	int _windowedHeight;
	int _windowedXPos;
	int _windowedYPos;
	std::string _title;

	bool _isFullscreen;
	bool _isResizable;
	bool _isHide;
	bool _isHideCursor;
	bool _isBlockCursor;
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
