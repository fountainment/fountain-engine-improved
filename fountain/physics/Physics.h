#if !defined(_FEI_PHYSICS_H_)
#define _FEI_PHYSICS_H_

#include "base/ModuleBase.h"
#include "math/Vec2.h"
#include <Box2D/Box2D.h>

namespace fei {

class Physics : public ModuleBase
{
public:
	bool init() override;
	void destroy() override;

	void executeBeforeFrame() override;

	void setGravity(const Vec2& g);
	const Vec2 getGravity();

	static Physics* getInstance();

private:
	Physics();

	b2World *world;

	static Physics *instance;
};

}

#endif
