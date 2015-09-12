#include "EditorScene.h"

using namespace fei;

void EditorScene::init()
{
	poly = Polygon::makeRegularPolygon(3, 200.0f);
	poly.setSolid(false);

	polyObj.setShape(&poly);
	add(&polyObj);

	auto vec = Interface::getInstance()->getCurrentWindow()->getWindowSize();
	mainCam.setCameraSize(vec);
	setCamera(&mainCam);
}

void EditorScene::update()
{
}

void EditorScene::mouseButtonCallback(int button, int action, int mods)
{
	auto window = Interface::getInstance()->getCurrentWindow();
	auto pos = window->getRHCursorPos();
	pos = mainCam.screenToWorld(pos);
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			//holdVertex = poly.collideVertex(pos, 5.0f);
		}
		if (action == GLFW_RELEASE) {
			//holdVertex = -1;
		}
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
		}
		if (action == GLFW_RELEASE) {
		}
	}
}

void EditorScene::scrollCallback(double xoffset, double yoffset)
{
	if (yoffset > 0.0f) {
		mainCam.cameraScaleZoom(1.1f);
	}
	if (yoffset < 0.0f) {
		mainCam.cameraScaleZoom(0.9f);
	}
}
