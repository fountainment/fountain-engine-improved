#include "Scene.h"

using fei::Scene;

void Scene::drawIt()
{
	cameraUpdate();
	listDraw();
}

void Scene::cameraUpdate()
{
	sceneCamera.update();
}

