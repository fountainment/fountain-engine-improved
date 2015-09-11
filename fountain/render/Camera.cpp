#include "Camera.h"
#include "Render.h"
#include "base/basedef.h"
#include "math/mathdef.h"
#include "interface/Interface.h"
#include <GL/glew.h>

using fei::Camera;

Camera::Camera()
: width(1.0f),
  height(1.0f),
  cameraType(Type::ORTHOGRAPHIC),
  cameraScale(1.0f),
  needDataUpdate(true)
{
}

void Camera::update()
{
	if (needDataUpdate) {
		updateCameraData();
	}
	glMatrixMode(GL_PROJECTION);
	if (cameraType == Type::ORTHOGRAPHIC) {
		glLoadIdentity();
		glOrtho(left, right, bottom, top, near, far);
	} else if (cameraType == Type::PERSPECTIVE) {
		//TODO: write it when you want to test it
	}
	glTranslatef(-pos.x, -pos.y, 0);
	glMatrixMode(GL_MODELVIEW);
}

void Camera::setCameraType(Type type)
{
	if (cameraType != type) {
		cameraType = type;
		needDataUpdate = true;
	}
}

Camera::Type Camera::getCameraType()
{
	return cameraType;
}

void Camera::setCameraScale(float scale)
{
	if (cameraScale != scale && std::abs(scale) > fei::eps) {
		cameraScale = scale;
		needDataUpdate = true;
	}
}

void Camera::setCameraSize(const fei::Vec2& v)
{
	width = v.x;
	height = v.y;
	needDataUpdate = true;
}

const fei::Vec2 Camera::screenToWorld(const fei::Vec2& scrPos)
{
	fei::Vec2 ans;
	auto camSize = fei::Vec2(right - left, top - bottom);
	auto winSize = fei::Interface::getInstance()->getCurrentWindow()->getWindowSize();
	ans = camSize.zoomed(scrPos.zoomed(winSize.reciprocal()) - fei::Vec2(0.5f)) + pos;
	return ans;
}

const fei::Vec2 Camera::worldToScreen(const fei::Vec2& wrdPos)
{
	fei::Vec2 ans;
	auto camSize = fei::Vec2(right - left, top - bottom);
	auto winSize = fei::Interface::getInstance()->getCurrentWindow()->getWindowSize();
	ans = ((wrdPos - pos).zoomed(camSize.reciprocal()) + fei::Vec2(0.5f)).zoomed(winSize);
	return ans;
}

void Camera::updateCameraData()
{
	if (cameraType == Type::ORTHOGRAPHIC) {
		float ratio = 2.0f * cameraScale;
		left = -width / ratio;
		right = width / ratio;
		bottom = -height / ratio;
		top = height / ratio;
		near = -99999;
		far = 99999;
	} else if (cameraType == Type::PERSPECTIVE) {
		//TODO: write it when you want to test it
	}
}
