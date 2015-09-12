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

	holdVertex = -1;
}

void EditorScene::update()
{
	if (holdVertex >= 0) {
		poly.setVertex(holdVertex, pos);
	}
}

void EditorScene::mouseButtonCallback(int button, int action, int mods)
{
	auto window = Interface::getInstance()->getCurrentWindow();
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			holdVertex = poly.collideVertex(pos, 20.0f);
		}
		if (action == GLFW_RELEASE) {
			holdVertex = -1;
		}
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			if (!window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
				poly.insertVertex(pos, 0);
			}
		}
		if (action == GLFW_RELEASE) {
		}
	}
}

void EditorScene::cursorPosCallback(double xpos, double ypos)
{
	auto window = Interface::getInstance()->getCurrentWindow();
	pos = mainCam.screenToWorld(window->getRHCursorPos());
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
