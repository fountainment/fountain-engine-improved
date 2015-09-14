#include "EditorScene.h"

using namespace fei;

void EShapeObj::drawIt()
{
	auto window = Interface::getInstance()->getCurrentWindow();
	auto scene = window->sceneManager->getCurScene();
	auto cam = scene->getCamera();

	Render::getInstance()->drawShape(shape);

	Circle circle(7.0f / cam->getCameraScale());

	const float *data = shape->getDataPtr();
	for (int i = 0; i < shape->getDataSize(); i++) {
		circle.setPosition(fei::Vec2(data[i << 1], data[i << 1 | 1]));
		Render::getInstance()->drawShape(&circle);
	}
}

void EditorScene::init()
{
	Physics::getInstance()->setDoDebugDraw(true);
	Physics::getInstance()->setDebugDrawCamera(&mainCam);
	Physics::getInstance()->setRatio(64.0f);

	poly = Polygon::makeRegularPolygon(4, 200.0f, 45.0f);
	poly.setSolid(false);

	tex.load("image.png");
	add(&tex);

	polyObj.setShape(&poly);
	add(&polyObj);

	auto vec = Interface::getInstance()->getCurrentWindow()->getWindowSize();
	mainCam.setCameraSize(vec);
	setCamera(&mainCam);

	holdVertex = -1;
}

void EditorScene::update()
{
	auto window = Interface::getInstance()->getCurrentWindow();

	if (holdVertex >= 0) {
		poly.setVertex(holdVertex, pos);
	}

	mPos = window->getRHCursorPos();
	deltaV = (mPos - oldPos) / mainCam.getCameraScale();
	oldPos = mPos;

	if (window->getMouseButton(GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
		mainCam.move(-deltaV);
	}

	if (window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT) && window->getKey(GLFW_KEY_LEFT_CONTROL)) {
		poly.moveVertices(deltaV);
	}
}

void EditorScene::mouseButtonCallback(int button, int action, int mods)
{
	auto window = Interface::getInstance()->getCurrentWindow();

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			holdVertex = poly.collideVertex(pos, 10.0f / mainCam.getCameraScale());
		}
		if (action == GLFW_RELEASE) {
			holdVertex = -1;
		}
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		if (!window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
			poly.insertVertex(pos, 0);
		} else {
			if (holdVertex != -1) {
				poly.deleteVertex(holdVertex);
				holdVertex = -1;
			}
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

void EditorScene::keyCallback(int key, int scancode, int action, int mods)
{
	auto window = Interface::getInstance()->getCurrentWindow();

	if (key == GLFW_KEY_SPACE) {
		if (action == GLFW_PRESS) {
			poly.setSolid(true);
		}
		if (action == GLFW_RELEASE) {
			poly.setSolid(false);
		}
	}

	if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
		window->setFullscreen(!window->isFullscreen());
		Render::getInstance()->setViewport(window->getFrameSize());
		mainCam.setCameraSize(window->getFrameSize());
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		auto body = Physics::getInstance()->createBody(Vec2::ZERO);
		body->getB2Body()->SetGravityScale(0.0f);
		auto fix = body->createFixture(&poly);
		fix->SetSensor(true);
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		auto body = Physics::getInstance()->createBody(Vec2::ZERO);
		body->createFixture(&poly);
	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		auto body = Physics::getInstance()->createBody(Vec2::ZERO, Body::Type::STATIC);
		body->createFixture(&poly);
	}
}

void EditorScene::framebufferSizeCallback(int width, int height)
{
	Render::getInstance()->setViewport(Vec2(width, height));
	mainCam.setCameraSize(Vec2(width, height));
}
