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
#include "math/Polygon.h"
#include "math/Circle.h"
#include "math/Segment.h"
#include "math/Vec2.h"
#include "math/Vec3.h"
#include "math/Vec4.h"
#include "math/hash.h"
#include "math/coding.h"

#include "time/Time.h"
#include "time/Clock.h"

#include "interface/Interface.h"
#include "interface/Window.h"

#include "control/Control.h"
#include "control/Joystick.h"

#include "render/Render.h"
#include "render/RenderObj.h"
#include "render/RenderList.h"
#include "render/RenderTree.h"
#include "render/Camera.h"
#include "render/Color.h"
#include "render/Image.h"
#include "render/ImagePool.h"
#include "render/Texture.h"
#include "render/Shader.h"
#include "render/ShapeObj.h"

#include "anime/FrameAnime.h"

#include "scene/Layer.h"
#include "scene/Scene.h"
#include "scene/SceneManager.h"

#include "audio/Audio.h"
#include "audio/Source.h"

#include "physics/Physics.h"
#include "physics/Body.h"
#include "physics/FixtureGroup.h"

#include "font/Font.h"
#include "font/FontCache.h"

#include "ui/Label.h"

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

	virtual void engineSetting(Engine *engine);
	void run();

	static Engine* getEngine();

private:
	static Engine *engine;
};

}

#endif
