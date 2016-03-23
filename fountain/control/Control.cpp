#include "control/Control.h"

#include <GLFW/glfw3.h>
#include "interface/Interface.h"

using fei::Control;

Control *Control::instance_ = nullptr;

Control* Control::getInstance()
{
	if (!instance_) {
		instance_ = new Control();
	}
	return instance_;
}

Control::Control()
{
}

bool Control::init()
{
	if (!fei::Interface::getInstance()->feiInit()) {
		return false;
	} else {
		findJoystick();
	}
	return true;
}

void Control::executeBeforeFrame()
{
	if (joystickCheck()) {
		_joystick.update();
	}
}

int Control::findJoystick()
{
	for (int i = GLFW_JOYSTICK_1; i <= GLFW_JOYSTICK_LAST; i++) {
		if (glfwJoystickPresent(i)) {
			_joystick.setId(i);
			_joystick.init();
			return i;
		}
	}
	return -1;
}

bool Control::joystickCheck()
{
	bool ans = false;
	if (_joystick.usable()) {
			ans = true;
	} else {
		/*
		findJoystick();
		if (_joystick.usable()) {
			ans = true;
		} */
	}
	return ans;
}

fei::Joystick* Control::getJoystick()
{
	if (_joystick.usable()) {
		return &_joystick;
	} else {
		return nullptr;
	}
}
