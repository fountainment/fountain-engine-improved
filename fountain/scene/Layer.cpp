#include "Layer.h"
#include <GL/glew.h>

using fei::Layer;

Layer::Layer()
: didCameraPush(false),
  layerCamera(nullptr)
{
}

void Layer::drawIt()
{
	cameraPush();
	listDraw();
	cameraPop();
}

void Layer::setLayerCamera(fei::Camera* camera)
{
	layerCamera = camera;
}

void Layer::cameraPush()
{
	didCameraPush = false;
	if (layerCamera) {
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
