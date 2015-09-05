#include "Physics.h"

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
: world(nullptr)
{
}

bool Physics::init()
{
	b2Vec2 g(0, 10);
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
