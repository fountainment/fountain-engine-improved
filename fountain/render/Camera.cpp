#include "Camera.h"
#include "Render.h"
#include "base/basedef.h"
#include "math/mathdef.h"
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
	updateCameraData();
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

float Camera::getCameraScale()
{
	return cameraScale;
}

void Camera::zoomCameraScale(float zoom)
{
	setCameraScale(cameraScale * zoom);
}

void Camera::zoomCameraScaleAtCenter(const fei::Vec2& center, float zoom)
{
	move((center - pos) * (1.0f - 1.0f / zoom));
	setCameraScale(cameraScale * zoom);
}

void Camera::setCameraSize(const fei::Vec2& v)
{
	width = v.x;
	height = v.y;
	needDataUpdate = true;
}

const fei::Vec2 Camera::screenToWorld(const fei::Vec2& scrPos)
{
	updateCameraData();
	auto camSize = fei::Vec2(right - left, top - bottom);
	auto vpSize = fei::Render::getViewport().getSize();
	auto ans = camSize.zoomed(scrPos.zoomed(vpSize.reciprocal()) - fei::Vec2(0.5f)) + pos;
	return ans;
}

const fei::Vec2 Camera::worldToScreen(const fei::Vec2& wrdPos)
{
	updateCameraData();
	auto camSize = fei::Vec2(right - left, top - bottom);
	auto vpSize = fei::Render::getViewport().getSize();
	auto ans = ((wrdPos - pos).zoomed(camSize.reciprocal()) + fei::Vec2(0.5f)).zoomed(vpSize);
	return ans;
}

void Camera::updateCameraData()
{
	if (needDataUpdate) {
		if (cameraType == Type::ORTHOGRAPHIC) {
			float ratio = 2.0f * cameraScale;
			left = -width / ratio;
			right = width / ratio;
			bottom = -height / ratio;
			top = height / ratio;
			near = -99999.0f;
			far = 99999.0f;
		} else if (cameraType == Type::PERSPECTIVE) {
			//TODO: write it when you want to test it
		}
		needDataUpdate = false;
	}
}
