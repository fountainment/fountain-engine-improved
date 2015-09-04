#include "Joystick.h"
#include "base/basedef.h"
#include <GLFW/glfw3.h>

using fei::Joystick;

Joystick::Joystick()
: id(-1),
  type(Type::DEFAULT),
  axesCount(0),
  buttonCount(0),
  accuracy(0.1f)
{
	clearData();
}

void Joystick::init()
{
	clearData();
	if (usable()) {
		const char* name = glfwGetJoystickName(id);
		std::printf("Detect Joystick: \"%s\"\n", name);
		update();
		if (axesCount == 12) {
			type = Type::PS4;
		}
	}
}

void Joystick::update()
{
	if (usable()) {
		int count;
		const float *axes = glfwGetJoystickAxes(id, &axesCount);
		count = axesCount;
		if (count > 16) count = 16;
		for (int i = 0; i < count; i++) {
			if (std::abs(axes[i]) > accuracy) {
				axesData[i] = axes[i];
			} else {
				axesData[i] = 0.0f;
			}
		}
		const unsigned char *button = glfwGetJoystickButtons(id, &buttonCount);
		count = buttonCount;
		if (count > 16) count = 16;
		for (int i = 0; i < count; i++) {
			buttonData[i] = button[i];
		};
	}
}

void Joystick::clearData()
{
	for (int i = 0; i < 16; i++) {
		axesData[i] = 0.0f;
		buttonData[i] = 0;
	}
}

bool Joystick::usable()
{
	return id >= GLFW_JOYSTICK_1 && id <= GLFW_JOYSTICK_LAST && glfwJoystickPresent(id);
}

void Joystick::setAccuracy(float acrc)
{
	accuracy = acrc;
}

int Joystick::getAxesCount()
{
	return axesCount;
}

int Joystick::getButtonCount()
{
	return buttonCount;
}

float Joystick::getAxesX()
{
	return axesData[0];
}

float Joystick::getAxesY()
{
	return -axesData[1];
}

fei::Vec2 Joystick::getAxes()
{
	return fei::Vec2(getAxesX(), getAxesY());
}

float Joystick::getDirectionX()
{
	return axesData[6];
}

float Joystick::getDirectionY()
{
	return -axesData[7];
}

fei::Vec2 Joystick::getDirection()
{
	return fei::Vec2(getDirectionX(), getDirectionY());
}

float Joystick::getTouchX()
{
	return -axesData[9];
}

float Joystick::getTouchY()
{
	return axesData[10];
}

fei::Vec2 Joystick::getTouch()
{
	return fei::Vec2(getTouchX(), getTouchY());
}

float Joystick::getTouchId()
{
	return axesData[11];
}
