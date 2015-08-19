#if !defined(_FEI_FOUNTAIN_H_)
#define _FEI_FOUNTAIN_H_

#include "base/basedef.h"
#include "base/ModuleBase.h"
#include "base/fileUtil.h"
#include "interface/Interface.h"
#include "interface/Window.h"
#include "control/Control.h"
#include "render/Render.h"
#include "render/Camera.h"
#include "render/Texture.h"
#include "render/Shader.h"
#include "time/Time.h"
#include "time/Clock.h"
#include "math/Vec2.h"
#include "math/Shape.h"
#include "math/Rect.h"

namespace fei {

class Engine : public ModuleBase
{
public:
	Engine();

	bool init() override;
	void destroy() override;

	bool createWindow();
	void mainLoop();

	void run();
	void exit();

	void setFrameFunc(void (*frameF)());

	Window *window;
private:
	bool loadModule();
	void unloadModule();

	std::vector<ModuleBase*> moduleList;

	//for test
	void (*frameFunc)();
	
	bool shouldExit();

	bool _shouldExit;

	void executeBeforeFrame() override;
	void executeAfterFrame() override;
};

class Application
{
public:
	Application();
	virtual ~Application();

	bool loadEngine();
	void unloadEngine();

	virtual void engineSetting(Engine *eg) = 0;
	void run();
	static Engine* getEngine();
private:

	static Engine *engine;
};

}

#endif
