#if !defined(_FEI_PHYSICS_H_)
#define _FEI_PHYSICS_H_

#include <Box2D/Box2D.h>

#include "base/ModuleBase.h"
#include "math/Vec2.h"
#include "math/Shape.h"
#include "physics/Body.h"
#include "render/Camera.h"

namespace fei {

class Physics : public ModuleBase
{
public:
	bool init() override;
	void destroy() override;

	void executeBeforeFrame() override;
	void executeAfterFrame() override;

	void setGravity(const Vec2& g);
	const Vec2 getGravity();

	const Vec2 renderToPhysics(const Vec2& v);
	const Vec2 physicsToRender(const Vec2& v);
	float renderToPhysics(float f);
	float physicsToRender(float f);

	void setRatio(float rt);
	float getRatio();

	Body* createBody(const Vec2& pos, Body::Type type = Body::Type::DYNAMIC);
	void destroyBody(Body* body);

	void setDoDebugDraw(bool doDD);
	void setDebugDrawCamera(Camera* cam);

	static b2Shape* ShapeToB2Shape(const Shape* shape);

	static Physics* getInstance();

private:
	Physics();

	b2World *world;
	b2Draw *debugDraw;
	Camera* ddCamera;
	bool doDebugDraw;
	float ratio;

	static Physics *instance;
};

inline const Vec2 Physics::renderToPhysics(const Vec2& v)
{
	return v / ratio;
}

inline const Vec2 Physics::physicsToRender(const Vec2& v)
{
	return v * ratio;
}

inline float Physics::renderToPhysics(float f)
{
	return f / ratio;
}

inline float Physics::physicsToRender(float f)
{
	return f * ratio;
}

} // namespace fei

#endif // _FEI_PHYSICS_H_
