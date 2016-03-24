#include "scene/Scene.h"

using fei::Scene;

Scene::Scene()
: _sceneClock(nullptr)
{
}

Scene::~Scene()
{
}

void Scene::setClock(fei::Clock* clock)
{
	_sceneClock = clock;
}

fei::Clock* Scene::getClock()
{
	return _sceneClock;
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

