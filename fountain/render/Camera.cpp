#include "Camera.h"
#include "Render.h"
#include <GL/glew.h>

using fei::Camera;

Camera::Camera()
: cameraType(Type::ORTHOGRAPHIC),
  cameraScale(1.0f)
{
}

void Camera::update()
{
	GLint originMode;
	glGetIntegerv(GL_MATRIX_MODE, &originMode);
	glMatrixMode(GL_PROJECTION);
	if (cameraType == Type::ORTHOGRAPHIC) {
	} else if (cameraType == Type::PERSPECTIVE) {
	}
	glMatrixMode(originMode);
}

void Camera::setCameraType(Type type)
{
	if (cameraType != type) {
		cameraType = type;
	}
}

Camera::Type Camera::getCameraType()
{
	return cameraType;
}
