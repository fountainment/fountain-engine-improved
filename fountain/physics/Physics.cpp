#include "Physics.h"
#include "math/Circle.h"

using fei::Physics;

Physics* Physics::instance = nullptr;

Physics* Physics::getInstance()
{
	if (!instance) {
		instance = new Physics();
	}
	return instance;
}

Physics::Physics()
: world(nullptr),
  ratio(1.0f)
{
}

bool Physics::init()
{
	b2Vec2 g(0.0f, -10.0f);
	world = new b2World(g);
	world->SetAllowSleeping(true);
	return true;
}

void Physics::destroy()
{
	delete world;
	world = nullptr;
}

void Physics::executeBeforeFrame()
{
	world->Step(0.0166f, 8, 3);
}

void Physics::setGravity(const fei::Vec2& g)
{
	world->SetGravity(b2Vec2(g.x, g.y));
}

const fei::Vec2 Physics::getGravity()
{
	auto g = world->GetGravity();
	return fei::Vec2(g.x, g.y);
}

const fei::Vec2 Physics::renderToPhysics(const fei::Vec2& v)
{
	return v / ratio;
}

const fei::Vec2 Physics::physicsToRender(const fei::Vec2& v)
{
	return v * ratio;
}

float Physics::renderToPhysics(float f)
{
	return f / ratio;
}

float Physics::physicsToRender(float f)
{
	return f * ratio;
}

void Physics::setRatio(float rt)
{
	ratio = rt;
}

fei::Body* Physics::createBody(const fei::Vec2& pos, fei::Body::Type type)
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
	auto b2bd = world->CreateBody(&bodyDef);
	auto body = new Body(b2bd, type);
	return body;
}

void Physics::destroyBody(fei::Body* body)
{
	world->DestroyBody(body->body);
	delete body;
}

b2Shape* Physics::ShapeToB2Shape(const fei::Shape* shape)
{
	b2Shape *b2shape = nullptr;
	switch (shape->getType()) {
	case fei::Shape::Type::POLYGON:
		{
			auto pShape = new b2PolygonShape;
			pShape->Set((const b2Vec2*)shape->getDataPtr(), shape->getDataSize());
			b2shape = pShape;
		}
		break;
	case fei::Shape::Type::CIRCLE:
		{
			auto cShape = new b2CircleShape;
			cShape->m_radius = Physics::getInstance()->renderToPhysics(((fei::Circle*)shape)->getRadius());
			b2shape = cShape;
		}
		break;
	}
	return b2shape;
}
