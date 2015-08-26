#include "Layer.h"

using fei::Layer;

Layer::Layer()
: layerCamera(nullptr)
{
}

void Layer::drawIt()
{
	cameraUpdate();
	listDraw();
}

void Layer::setLayerCamera(Camera* camera)
{
	layerCamera = camera;
}

void Layer::cameraUpdate()
{
	if (layerCamera) {
		layerCamera->update();
	}
}

