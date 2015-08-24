#if !defined(_FEI_FOUNTAIN_H_)
#define _FEI_FOUNTAIN_H_

#include "base/basedef.h"
#include "base/fileUtil.h"
#include "base/ModuleBase.h"
#include "base/NodeBase.h"
#include "base/noncopyable.h"

#include "math/mathdef.h"
#include "math/Rect.h"
#include "math/Shape.h"
#include "math/Vec2.h"
#include "math/Vec3.h"

#include "time/Time.h"
#include "time/Clock.h"

#include "interface/Interface.h"
#include "interface/Window.h"

#include "control/Control.h"
#include "control/Joystick.h"

#include "render/Render.h"
#include "render/RenderObj.h"
#include "render/Camera.h"
#include "render/Color.h"
#include "render/Image.h"
#include "render/ImagePool.h"
#include "render/Texture.h"
#include "render/Shader.h"

#include "anime/FrameAnime.h"

#ifdef _MSC_VER
	#pragma comment(linker, "/NODEFAULTLIB:LIBCMT.lib")
	#ifdef NDEBUG
		#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
	#else
		#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
	#endif
#endif

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
