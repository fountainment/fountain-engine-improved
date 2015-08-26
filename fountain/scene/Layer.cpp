#include "Layer.h"

using fei::Layer;

Layer::Layer()
: layerCamera(nullptr)
{
}

void Layer::cameraUpdate()
{
	if (layerCamera) {
		layerCamera->update();
	}
}

