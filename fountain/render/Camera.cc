#include "render/Camera.h"

#include <glad/glad.h>

#include "base/basedef.h"
#include "math/mathdef.h"
#include "render/Render.h"

using fei::Camera;

Camera::Camera()
: _cameraType(Type::ORTHOGRAPHIC),
  _cameraScale(1.0f),
  _cameraZPos(perspectiveCameraNear_ + fei::pif),
  _width(1.0f),
  _height(1.0f),
  _needDataUpdate(true)
{
}

Camera::~Camera()
{
	if (fei::Render::getInstance()->getCurrentCamera() == this) {
		fei::Render::getInstance()->setCurrentCamera(nullptr);
	}
}

void Camera::update()
{
	updateCameraData();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (_cameraType == Type::ORTHOGRAPHIC) {
		glOrtho(_left, _right, _bottom, _top, orthoCameraNear_, orthoCameraFar_);
	} else if (_cameraType == Type::PERSPECTIVE) {
		glFrustum(_left, _right, _bottom, _top, perspectiveCameraNear_, perspectiveCameraFar_);
	}
	glTranslatef(-getPositionX(), -getPositionY(), -getCameraZPos());
	glMatrixMode(GL_MODELVIEW);
	fei::Render::getInstance()->setCurrentCamera(this);
}

void Camera::setCameraType(Type type)
{
	if (_cameraType != type) {
		_cameraType = type;
		_needDataUpdate = true;
	}
}

Camera::Type Camera::getCameraType()
{
	return _cameraType;
}

void Camera::setCameraScale(float scale)
{
	if (_cameraScale != scale && std::abs(scale) > fei::eps) {
		_cameraScale = scale;
		_needDataUpdate = true;
	}
}

float Camera::getCameraScale()
{
	return _cameraScale;
}

void Camera::zoomCameraScale(float zoom)
{
	setCameraScale(_cameraScale * zoom);
}

void Camera::zoomCameraScaleAtCenter(const fei::Vec2& center, float zoom)
{
	move((center - getPosition()) * (1.0f - 1.0f / zoom));
	setCameraScale(_cameraScale * zoom);
}

void Camera::setCameraSize(const fei::Vec2& v)
{
	_width = v.x;
	_height = v.y;
	_needDataUpdate = true;
}

const fei::Vec2 Camera::getCameraSize()
{
	return fei::Vec2(_width, _height);
}

void Camera::setCameraRect(const fei::Rect& r)
{
	setCameraSize(r.getSize() * getCameraScale());
	setPosition(r.getCenter());
}

const fei::Rect Camera::getCameraRect()
{
	fei::Rect ret;
	ret.setSize(getCameraSize() / getCameraScale());
	ret.setCenter(getPosition());
	return ret;
}

void Camera::setCameraZPos(float z)
{
	_cameraZPos = z;
	if (_cameraZPos < perspectiveCameraNear_) {
		_cameraZPos = perspectiveCameraNear_ + fei::pif;
	}
	_needDataUpdate = true;
}

float Camera::getCameraZPos()
{
	return _cameraZPos;
}

const fei::Vec2 Camera::screenToWorld(const fei::Vec2& scrPos)
{
	auto camSize = getCameraSize() / getCameraScale();
	auto vpSize = fei::Render::getInstance()->getViewport().getSize();
	auto ans = camSize.zoomed(scrPos.zoomed(vpSize.reciprocal()) - fei::Vec2(0.5f)) + getPosition();
	return ans;
}

const fei::Vec2 Camera::worldToScreen(const fei::Vec2& wrdPos)
{
	auto camSize = getCameraSize() / getCameraScale();
	auto vpSize = fei::Render::getInstance()->getViewport().getSize();
	auto ans = ((wrdPos - getPosition()).zoomed(camSize.reciprocal()) + fei::Vec2(0.5f)).zoomed(vpSize);
	return ans;
}

void Camera::updateCameraData()
{
	if (_needDataUpdate) {
		float ratio = 2.0f * _cameraScale;
		if (_cameraType == Type::PERSPECTIVE) {
			ratio *= getCameraZPos() / perspectiveCameraNear_;
		}
		_left = -_width / ratio;
		_right = _width / ratio;
		_bottom = -_height / ratio;
		_top = _height / ratio;
		_needDataUpdate = false;
	}
}
