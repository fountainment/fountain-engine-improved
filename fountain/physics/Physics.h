#if !defined(_FEI_PHYSICS_H_)
#define _FEI_PHYSICS_H_

#include "base/ModuleBase.h"
#include <Box2D/Box2D.h>

namespace fei {

class Physics : public ModuleBase
{
public:
	

	bool init() override;
	void destroy() override;

	void executeBeforeFrame() override;

	static Physics* getInstance();

private:
	Physics();

	b2World *world;

	static Physics *instance;
};

}

#endif