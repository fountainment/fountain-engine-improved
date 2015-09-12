#if !defined(_FEI_SCENE_H_)
#define _FEI_SCENE_H_

#include "scene/Layer.h"
#include "time/Clock.h"
#include "render/Camera.h"

namespace fei {

class Scene : public Layer
{
public:
	virtual ~Scene();

	virtual void feiUpdate() override;

	void setClock(Clock* clock);
	Clock* getClock();

	void clockTick();

	virtual void keyCallback(int key, int scancode, int action, int mods);
	virtual void mouseButtonCallback(int button, int action, int mods);
	virtual void scrollCallback(double xoffset, double yoffset);
	virtual void cursorPosCallback(double xpos, double ypos);
	virtual void charactorCallback(unsigned int codepoint);
	virtual void framebufferSizeCallback(int width, int height);

private:
	Clock *sceneClock;
};

}

#endif

