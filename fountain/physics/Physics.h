#if !defined(_FEI_PHYSICS_H_)
#define _FEI_PHYSICS_H_

#include "base/ModuleBase.h"
#include "math/Vec2.h"
#include "math/Shape.h"
#include "physics/Body.h"
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

	const Vec2 renderToPhysics(const Vec2& v);
	const Vec2 physicsToRender(const Vec2& v);
	float renderToPhysics(float f);
	float physicsToRender(float f);

	void setRatio(float rt);

	Body* createBody(const Vec2& pos, Body::Type type = Body::Type::DYNAMIC);
	void destroyBody(Body* body);

	static b2Shape* ShapeToB2Shape(const Shape* shape);

	static Physics* getInstance();

private:
	Physics();

	b2World *world;
	float ratio;

	static Physics *instance;
};

}

#endif