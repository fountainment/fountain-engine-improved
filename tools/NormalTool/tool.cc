#include "tool.h"

using namespace fei;

void ToolScene::init()
{
	_camera.setCameraSize(Vec2(1000.0f, 600.0f));
	_camera.setCameraType(Camera::Type::PERSPECTIVE);
	_camera.setCameraZPos(1000.0f);
	_uiCamera.setCameraSize(Vec2(1000.0f, 600.0f));

	_uiLayer.setCamera(&_uiCamera);
	_planeLayer.setCamera(&_camera);

	_backRect.setSize(Vec2(2000.0f));
	_backRect.setCenter(Vec2::ZERO);
	_rect.setSize(Vec2(300.0f));
	_rect.setCenter(Vec2::ZERO);
	_backPlane.setShape(&_backRect);
	_plane.setShape(&_rect);
	_backPlane.setZPos(-300.0f);
	_backPlane.setColor(Color(0.9f));
	_planeLayer.add(&_backPlane);
	_planeLayer.add(&_plane);

	add(&_planeLayer);
	add(&_uiLayer);
}

void ToolScene::update()
{
	auto window = fei::Interface::getInstance()->getCurrentWindow();
	auto deltaV = window->getRHCursorDeltaV();
	if (window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
		deltaV *= 0.005f;
		float nextAngleX = _plane.getAngleX() - deltaV.y;
		float nextAngleY = _plane.getAngleY() + deltaV.x;
		float limit = pif * 0.5f;
		if (nextAngleX >= -limit && nextAngleX <= limit) {
			_plane.rotateX(-deltaV.y);
		}
		if (nextAngleY >= -limit && nextAngleY <= limit) {
			_plane.rotateY(deltaV.x);
		}
	}
}
