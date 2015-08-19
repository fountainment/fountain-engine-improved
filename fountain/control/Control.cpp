#include "Control.h"
#include "interface/Interface.h"
#include <GLFW/glfw3.h>

using fei::Control;

Control *Control::instance = nullptr;

Control* Control::getInstance()
{
	if (!instance) {
		instance = new Control();
	}
	return instance;
}

Control::Control()
{
}

bool Control::init()
{
	if (_isLoad) return true;
	_isLoad = true;
	if (!fei::Interface::getInstance()->init()) {
		_isLoad = false;
	} else {
		findJoystick();
	}
	return _isLoad;
}

void Control::destroy()
{
	if (!_isLoad) return;
	_isLoad = false;
}

void Control::executeBeforeFrame()
{
	if (joystickCheck()) {
		joystick.update();
	}
}

int Control::findJoystick()
{
	for (int i = GLFW_JOYSTICK_1; i <= GLFW_JOYSTICK_LAST; i++) {
		if (glfwJoystickPresent(i)) {
			joystick.id = i;
			joystick.init();
			return i;
		}
	}
	return -1;
}

bool Control::joystickCheck()
{
	bool ans = false;
	if (joystick.usable()) {
			ans = true;
	} else {
		findJoystick();
		if (joystick.usable()) {
			ans = true;
		}
	}
	return ans;
}

fei::Joystick* Control::getJoystick()
{
	if (joystick.usable()) {
		return &joystick;
	} else {
		return nullptr;
	}
}
