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
	if (_isLoad) return true;
	_isLoad = true;
	b2Vec2 g(0, 10);
	world = new b2World(g);
	world->SetAllowSleeping(true);
	return _isLoad;
}

void Physics::destroy()
{
	if (!_isLoad) return;
	_isLoad = false;
	delete world;
	world = nullptr;
}

void Physics::executeBeforeFrame()
{
	world->Step(0.0166, 8, 3);
}