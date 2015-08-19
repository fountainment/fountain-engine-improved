#include "Joystick.h"
#include "base/basedef.h"
#include <GLFW/glfw3.h>

using fei::Joystick;

Joystick::Joystick()
: id(-1)
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
	}
}

void Joystick::update()
{
	if (usable()) {
		int count;
		const float *axes = glfwGetJoystickAxes(id, &count);
		if (count > 16) count = 16;
		for (int i = 0; i < count; i++) {
			axesData[i] = axes[i];
		}
		const unsigned char *button = glfwGetJoystickButtons(id, &count);
		if (count > 16) count = 16;
		for (int i = 0; i < count; i++) {
			buttonData[i] = button[i];
		}
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
	return fei::Vec2(axesData[0], -axesData[1]);
}

fei::Vec2 Joystick::getTouch()
{
	return fei::Vec2(-axesData[9], axesData[10]);
}
