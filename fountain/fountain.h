#if !defined(_FEI_FOUNTAIN_H_)
#define _FEI_FOUNTAIN_H_

#include "base/basedef.h"
#include "base/ModuleBase.h"
#include "interface/Interface.h"
#include "interface/Window.h"
#include "render/Render.h"
#include "time/Time.h"

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

	Window *window;
private:
	bool loadModule();
	void unloadModule();

	std::vector<ModuleBase*> moduleList;
	
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
private:
	static Engine* getEngine();

	static Engine *engine;
};

}

#endif
