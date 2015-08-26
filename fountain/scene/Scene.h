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

private:
	Clock *sceneClock;
};

}

#endif

