#include "scene/Scene.h"

using fei::Scene;

Scene::~Scene()
{
}

void Scene::feiUpdate()
{
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

void Scene::keyCallback(int key, int scancode, int action, int mods)
{
}

void Scene::mouseButtonCallback(int button, int action, int mods)
{
}

void Scene::cursorPosCallback(double xpos, double ypos)
{
}

void Scene::scrollCallback(double xoffset, double yoffset)
{
}

void Scene::charactorCallback(unsigned int codepoint)
{
}

void Scene::framebufferSizeCallback(int width, int height)
{
}

void Scene::dropCallback(int count, const char** paths)
{
}

