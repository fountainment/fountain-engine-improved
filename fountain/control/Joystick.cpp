#include "control/Joystick.h"

#include <GLFW/glfw3.h>
#include "base/basedef.h"

using fei::Joystick;

Joystick::Joystick()
: _id(-1),
  _type(Type::DEFAULT),
  _axesCount(0),
  _buttonCount(0),
  _accuracy(0.3f)
{
	clearData();
}

void Joystick::init()
{
	clearData();
	if (usable()) {
		const char* name = glfwGetJoystickName(_id);
		std::printf("Detect Joystick: \"%s\"\n", name);
		update();
		if (_axesCount == 12) {
			_type = Type::PS4;
		}
	}
}

void Joystick::update()
{
	if (usable()) {
		int count;
		const float *axes = glfwGetJoystickAxes(_id, &_axesCount);
		count = _axesCount;
		if (count > 16) count = 16;
		for (int i = 0; i < count; i++) {
			if (std::abs(axes[i]) > _accuracy) {
				_axesData[i] = axes[i];
			} else {
				_axesData[i] = 0.0f;
			}
		}
		const unsigned char *button = glfwGetJoystickButtons(_id, &_buttonCount);
		count = _buttonCount;
		if (count > 16) count = 16;
		for (int i = 0; i < count; i++) {
			if (_buttonData[i] == 0) {
				if (button[i] == 0) {
					_buttonState[i] = Joystick::ButtonState::UP;
				} else {
					_buttonState[i] = Joystick::ButtonState::PRESS;
				}
			} else {
				if (button[i] == 0) {
					_buttonState[i] = Joystick::ButtonState::RELEASE;
				} else {
					_buttonState[i] = Joystick::ButtonState::DOWN;
				}
			}
			_buttonData[i] = button[i];
		};
	}
}

void Joystick::clearData()
{
	for (int i = 0; i < 16; i++) {
		_axesData[i] = 0.0f;
		_buttonData[i] = 0;
		_buttonState[i] = Joystick::ButtonState::UP;
	}
}

bool Joystick::usable()
{
	return _id >= GLFW_JOYSTICK_1 && _id <= GLFW_JOYSTICK_LAST && glfwJoystickPresent(_id);
}

void Joystick::setAccuracy(float accuracy)
{
	_accuracy = accuracy;
}

int Joystick::getAxesCount()
{
	return _axesCount;
}

int Joystick::getButtonCount()
{
	return _buttonCount;
}

float Joystick::getAxesX()
{
	return _axesData[0];
}

float Joystick::getAxesY()
{
	return -_axesData[1];
}

fei::Vec2 Joystick::getAxes()
{
	return fei::Vec2(getAxesX(), getAxesY());
}

float Joystick::getDirectionX()
{
	return _axesData[6];
}

float Joystick::getDirectionY()
{
	return -_axesData[7];
}

fei::Vec2 Joystick::getDirection()
{
	return fei::Vec2(getDirectionX(), getDirectionY());
}

bool Joystick::getButton(Joystick::Button button)
{
	return _buttonData[(int)button] != 0;
}

Joystick::ButtonState Joystick::getButtonState(Joystick::Button button)
{
	return _buttonState[(int)button];
}

float Joystick::getTouchX()
{
	return -_axesData[9];
}

float Joystick::getTouchY()
{
	return _axesData[10];
}

fei::Vec2 Joystick::getTouch()
{
	return fei::Vec2(getTouchX(), getTouchY());
}

float Joystick::getTouchId()
{
	return _axesData[11];
}

void Joystick::setId(int id)
{
	_id = id;
}
