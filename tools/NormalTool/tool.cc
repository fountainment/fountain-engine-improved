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
	_planeLayer.add(&_backPlane);
	_planeLayer.add(&_plane);

	for (int i = 0; i < 13; i++) {
		auto y = -300.0f + i * 50.0f;
		auto seg = new Segment(Vec2(-500.0f, y), Vec2(500.0f, y));
		auto obj = new ShapeObj();
		obj->setShape(seg);
		obj->setColor(Color::Black);
		obj->setZPos(0.01f);
		_planeLayer.add(obj);
	}
	for (int i = 0; i < 21; i++) {
		auto x = -500.0f + i * 50.0f;
		auto seg = new Segment(Vec2(x, -300.0f), Vec2(x, 300.0f));
		auto obj = new ShapeObj();
		obj->setShape(seg);
		obj->setColor(Color::Black);
		obj->setZPos(0.01f);
		_planeLayer.add(obj);
	}

	_planeLayer.setShader(NormalTool::getShader());

	_eulerLabel.setPosition(Vec2(260.0f, 260.0f));
	_normalLabel.setPosition(Vec2(260.0f, 210.0f));
	_colorButton.setPosition(Vec2(250.0f, 100.0f));

	_colorButton.setRectSize(Vec2(200.0f, 50.0f));

	_uiLayer.add(&_eulerLabel);
	_uiLayer.add(&_normalLabel);
	_uiLayer.add(&_colorButton);

	add(&_planeLayer);
	add(&_uiLayer);
}

void ToolScene::update()
{
	auto window = fei::Interface::getInstance()->getCurrentWindow();
	auto deltaV = window->getRHCursorDeltaV();
	if (window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
		rotatePlane(deltaV * 0.005f);
	}
	NormalTool::getShader()->setViewCoord(Vec3(_camera.getPosition(), _camera.getCameraZPos()));
	NormalTool::getShader()->setLightData();

	double x = _plane.getAngleX();
	double y = _plane.getAngleZ();
	_eulerLabel.setString(*NormalTool::getFont(), strFormat("%4.0f %4.0f", R2D(x), R2D(y)));
	double ax = std::sin(x) * std::sin(y);
	double ay = -std::sin(x) * std::cos(y);
	double az = std::cos(x);
	double eps = 0.001;
	if (std::abs(ax) < eps) {
		ax = 0.0;
	}
	if (std::abs(ay) < eps) {
		ay = 0.0;
	}
	if (std::abs(az) < eps) {
		az = 0.0;
	}
	_normalLabel.setString(*NormalTool::getFont(), strFormat("%4.2f %4.2f %4.2f", ax, ay, az));
	Vec3 color = (Vec3(-static_cast<float>(ax), static_cast<float>(ay), static_cast<float>(az)) + Vec3::ONE) * 0.5f;
	_colorButton.setBackColor(color);
	int i = static_cast<int>(std::roundf(color.x * 255.0f));
	i <<= 8;
	i += static_cast<int>(std::roundf(color.y * 255.0f));
	i <<= 8;
	i += static_cast<int>(std::roundf(color.z * 255.0f));
	auto str = strFormat("%06X", i);
	_colorButton.setLabelString(*NormalTool::getFont(), str);
	_colorButton.setName(str);
}

void ToolScene::resetPlane()
{
	_plane.setAngleX(0.0f);
	_plane.setAngleZ(0.0f);
}

void ToolScene::rotatePlane(const Vec2& v)
{
	float nextAngleX = _plane.getAngleX() - v.y;
	float nextAngleZ = _plane.getAngleZ() - v.x;
	float limit = pif * 0.5f;
	if (nextAngleX >= -limit && nextAngleX <= limit) {
		_plane.rotateX(-v.y);
	} else {
		_plane.setAngleX(-_plane.getAngleX());
	}
	if (nextAngleZ >= -limit && nextAngleZ <= limit) {
		_plane.rotateZ(-v.x);
	} else {
		_plane.setAngleX(-_plane.getAngleX());
		_plane.setAngleZ(-_plane.getAngleZ());
	}
	roundAngle();
}

void ToolScene::roundAngle()
{
	auto t = Vec2(_plane.getAngleX(), _plane.getAngleZ());
	t.x = R2Df(t.x);
	t.y = R2Df(t.y);
	t.round();
	_plane.setAngleX(D2Rf(t.x));
	_plane.setAngleZ(D2Rf(t.y));
}

void ToolScene::setColorStr(const std::string & str)
{
	Color color("#" + str);

	auto x = -(color.x * 2.0f - 1.0f);
	auto y = color.y * 2.0f - 1.0f;
	auto z = color.z * 2.0f - 1.0f;

	auto angleX = clamp(std::acosf(z), -pif * 0.5f, pif * 0.5f);
	auto angleY = clamp(std::atanf(-x / y), -pif * 0.5f, pif * 0.5f);
	if (y > 0.0) {
		angleX *= -1.0f;
	}
	_plane.setAngleX(angleX);
	_plane.setAngleZ(angleY);
	roundAngle();
}

void ToolScene::keyCallback(int key, int scancode, int action, int mods)
{
	auto window = fei::Interface::getInstance()->getCurrentWindow();
	if (action != GLFW_RELEASE) {
		float degree = 1.0f;
		if (mods == GLFW_MOD_SHIFT) {
			degree = 2.0f;
		}
		switch (key) {
		case GLFW_KEY_W:
			rotatePlane(Vec2(0.0f, D2Rf(degree)));
			break;
		case GLFW_KEY_S:
			rotatePlane(Vec2(0.0f, D2Rf(-degree)));
			break;
		case GLFW_KEY_A:
			rotatePlane(Vec2(D2Rf(-degree), 0.0f));
			break;
		case GLFW_KEY_D:
			rotatePlane(Vec2(D2Rf(degree), 0.0f));
			break;
		case GLFW_KEY_R:
			resetPlane();
			break;
		case GLFW_KEY_V:
			if (mods == GLFW_MOD_CONTROL) {
				auto str = window->getClipboard();
				if (str.length() == 6) {
					setColorStr(str);
				}
			}
		}
	}
}
