#if !defined(_FEI_INTERFACE_H_)
#define _FEI_INTERFACE_H_

#include "base/ModuleBase.h"
#include "interface/Window.h"
#include "math/Vec2.h"

namespace fei {

class Interface : public fei::ModuleBase
{
public:
	bool init() override;
	void destroy() override;

	Window* applyNewWindow();
	void destroyWindow(Window* window);
	void destroyAllWindows();

	void createRootWindow();
	Window* getRootWindow();

	void setCurrentWindow(Window* window);
	Window* getCurrentWindow();

	const Vec2 getCursorPos();
	const Vec2 getRHCursorPos();
	const Vec2 getWindowSize();

	void executeAfterFrame() override;

	static Interface* getInstance();

private:
	Interface();
	Window* rootWindow;
	Window* currentWindow;
	std::vector<fei::Window*> windowList;

	static Interface* instance;
};

} // namespace fei

#endif // _FEI_INTERFACE_H_
