#include "scene/Layer.h"

#include <glad/glad.h>

#include "render/Render.h"

using fei::Layer;

Layer::Layer()
: _didCameraPush(false),
  _oldCamera(nullptr),
  _layerCamera(nullptr)
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
	_didCameraPush = false;
	if (_layerCamera) {
		_oldCamera = fei::Render::getInstance()->getCurrentCamera();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		_didCameraPush = true;
		_layerCamera->update();
	}
}

void Layer::cameraPop()
{
	if (_didCameraPush) {
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		if (_oldCamera) {
			_oldCamera->update();
		}
		_didCameraPush = false;
	}
}

void Layer::setCamera(fei::Camera* camera)
{
	_layerCamera = camera;
}

fei::Camera* Layer::getCamera()
{
	return _layerCamera;
}
