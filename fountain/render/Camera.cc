#include "render/Camera.h"

#include <glad/glad.h>

#include "base/basedef.h"
#include "math/mathdef.h"
#include "render/Render.h"

using fei::Camera;

Camera::Camera()
: _width(1.0f),
  _height(1.0f),
  _cameraType(Type::ORTHOGRAPHIC),
  _cameraScale(1.0f),
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
	if (_cameraType == Type::ORTHOGRAPHIC) {
		glLoadIdentity();
		glOrtho(_left, _right, _bottom, _top, _near, _far);
	} else if (_cameraType == Type::PERSPECTIVE) {
		//TODO: write it when you want to test it
	}
	glTranslatef(-getPosition().x, -getPosition().y, 0);
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
	setCameraSize(r.getSize());
	setPosition(r.getCenter());
}

const fei::Rect Camera::getCameraRect()
{
	fei::Rect ret;
	ret.setSize(getCameraSize());
	ret.setCenter(getPosition());
	return ret;
}

const fei::Vec2 Camera::screenToWorld(const fei::Vec2& scrPos)
{
	updateCameraData();
	auto camSize = fei::Vec2(_right - _left, _top - _bottom);
	auto vpSize = fei::Render::getInstance()->getViewport().getSize();
	auto ans = camSize.zoomed(scrPos.zoomed(vpSize.reciprocal()) - fei::Vec2(0.5f)) + getPosition();
	return ans;
}

const fei::Vec2 Camera::worldToScreen(const fei::Vec2& wrdPos)
{
	updateCameraData();
	auto camSize = fei::Vec2(_right - _left, _top - _bottom);
	auto vpSize = fei::Render::getInstance()->getViewport().getSize();
	auto ans = ((wrdPos - getPosition()).zoomed(camSize.reciprocal()) + fei::Vec2(0.5f)).zoomed(vpSize);
	return ans;
}

void Camera::updateCameraData()
{
	if (_needDataUpdate) {
		if (_cameraType == Type::ORTHOGRAPHIC) {
			float ratio = 2.0f * _cameraScale;
			_left = -_width / ratio;
			_right = _width / ratio;
			_bottom = -_height / ratio;
			_top = _height / ratio;
			_near = -99999.0f;
			_far = 99999.0f;
		} else if (_cameraType == Type::PERSPECTIVE) {
			//TODO: write it when you want to test it
		}
		_needDataUpdate = false;
	}
}
