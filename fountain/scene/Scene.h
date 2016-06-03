#ifndef _FEI_SCENE_H_
#define _FEI_SCENE_H_

#include "render/Camera.h"
#include "scene/Layer.h"
#include "time/Clock.h"

namespace fei {

class Scene : public Layer
{
public:
	Scene();
	virtual ~Scene();

	void setClock(Clock* clock);
	Clock* getClock();

	virtual void keyCallback(int key, int scancode, int action, int mods);
	virtual void mouseButtonCallback(int button, int action, int mods);
	virtual void scrollCallback(double xoffset, double yoffset);
	virtual void cursorPosCallback(double xpos, double ypos);
	virtual void charactorCallback(unsigned int codepoint);
	virtual void framebufferSizeCallback(int width, int height);
	virtual void dropCallback(int count, const char** paths);
	virtual void joystickCallback(int joy, int event);

private:
	Clock *_sceneClock;
};

} // namespace fei

#endif // _FEI_SCENE_H_

