#include "scene/Layer.h"

#include <GL/glew.h>

#include "render/Render.h"

using fei::Layer;

Layer::Layer()
: didCameraPush(false),
  oldCamera(nullptr),
  layerCamera(nullptr)
{
}

void Layer::drawIt()
{
	cameraPush();
	listDraw();
	cameraPop();
}

void Layer::cameraPush()
{
	didCameraPush = false;
	if (layerCamera) {
		oldCamera = fei::Render::getInstance()->getCurrentCamera();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		didCameraPush = true;
		layerCamera->update();
	}
}

void Layer::cameraPop()
{
	if (didCameraPush) {
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		if (oldCamera) {
			oldCamera->update();
		}
		didCameraPush = false;
	}
}

void Layer::setCamera(fei::Camera* camera)
{
	layerCamera = camera;
}

fei::Camera* Layer::getCamera()
{
	return layerCamera;
}
