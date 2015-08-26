#include "Scene.h"

using fei::Scene;

Scene::~Scene()
{
}

void Scene::feiUpdate()
{
	clockTick();
	update();
	listUpdate();
}

void Scene::setClock(fei::Clock* clock)
{
	sceneClock = clock;
}

fei::Clock* Scene::getClock()
{
	return sceneClock;
}

void Scene::clockTick()
{
	if (sceneClock) {
		sceneClock->tick();
	}
}
