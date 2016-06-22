#ifndef _FEI_PHYSICS_H_
#define _FEI_PHYSICS_H_

#include <Box2D/Box2D.h>

#include "base/ModuleBase.h"
#include "math/Vec2.h"
#include "math/Shape.h"
#include "physics/Body.h"
#include "render/Camera.h"

namespace fei {

struct ContactInfo
{
	inline void setFixture(b2Fixture* a, b2Fixture* b)
	{
		fixtureA = a;
		fixtureB = b;
	}

	b2Fixture* fixtureA;
	b2Fixture* fixtureB;
	bool valid;
	fei::Vec2 normal;
	fei::Vec2 collidePoint;
};

class ContactListener : public b2ContactListener
{
public:
	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

	static ContactInfo* getContactInfo();

private:
	static void updateContactInfo(b2Contact* contact);

	static ContactInfo contactInfo_;
};

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

	void wakeUpAllBodies();

	template<class T = Body>
	T* createBody(const Vec2& pos, Body::Type type = Body::Type::DYNAMIC);
	void destroyBody(Body* body);

	void setDoDebugDraw(bool doDD);
	void setDebugDrawCamera(Camera* cam);

	bool isInStep();

	static b2Shape* ShapeToB2Shape(const Shape* shape);
	static Body* getBodyByB2Fixture(const b2Fixture* fixture);

	static Physics* getInstance();

private:
	Physics();

	b2World* _world;
	b2Draw* _debugDraw;
	b2ContactListener* _contactListener;
	std::queue<Body*> _zombieBodyList;
	Camera* _ddCamera;
	bool _doDebugDraw;
	bool _inStep;
	float _ratio;

	static Physics *instance_;
};

} // namespace fei

inline float fei::Physics::getRatio()
{
	return _ratio;
}

inline const fei::Vec2 fei::Physics::renderToPhysics(const fei::Vec2& v)
{
	return v / getRatio();
}

inline const fei::Vec2 fei::Physics::physicsToRender(const fei::Vec2& v)
{
	return v * getRatio();
}

inline float fei::Physics::renderToPhysics(float f)
{
	return f / getRatio();
}

inline float fei::Physics::physicsToRender(float f)
{
	return f * getRatio();
}

inline fei::Body* fei::Physics::getBodyByB2Fixture(const b2Fixture* fixture)
{
	return static_cast<fei::Body*>(fixture->GetBody()->GetUserData());
}

template<class T>
T* fei::Physics::createBody(const fei::Vec2& pos, fei::Body::Type type)
{
	b2BodyDef bodyDef;
	auto physicsPos = renderToPhysics(pos);
	bodyDef.position.Set(physicsPos.x, physicsPos.y);
	switch(type) {
	case fei::Body::Type::STATIC:
		bodyDef.type = b2_staticBody;
		break;
	case fei::Body::Type::DYNAMIC:
		bodyDef.type = b2_dynamicBody;
		break;
	case fei::Body::Type::KINEMATIC:
		bodyDef.type = b2_kinematicBody;
		break;
	}
	auto b2bd = _world->CreateBody(&bodyDef);
	auto body = new T(b2bd, type);
	return body;
}

#endif // _FEI_PHYSICS_H_
