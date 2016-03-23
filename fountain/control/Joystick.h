#ifndef _FEI_JOYSTICK_H_
#define _FEI_JOYSTICK_H_

//TODO: test different joysticks and support them

#include "math/Vec2.h"

namespace fei {

class Joystick
{
public:
	friend class Control;

	enum class Type {
		DEFAULT = 1,
		PS4 = 2
	};

	enum class Button {
		A = 0,
		B = 1,
		X = 2,
		Y = 3,
		LB = 4,
		RB = 5,
		BACK = 6,
		STRAT = 7,
		ICON = 8,
		L3 = 9,
		R3 = 10
	};

	enum class ButtonState {
		UP = 0,
		PRESS = 1,
		DOWN = 2,
		RELEASE = 3
	};

	Joystick();

	void setAccuracy(float accuracy);

	int getAxesCount();
	int getButtonCount();

	float getAxesX();
	float getAxesY();
	Vec2 getAxes();

	float getDirectionX();
	float getDirectionY();
	Vec2 getDirection();

	bool getButton(Joystick::Button button);
	Joystick::ButtonState getButtonState(Joystick::Button button);

	float getTouchX();
	float getTouchY();
	Vec2 getTouch();
	float getTouchId();

private:
	void init();
	bool usable();
	void update();
	void clearData();

	void setId(int id);

	int _id;
	Type _type;
	int _axesCount;
	float _axesData[16];
	int _buttonCount;
	unsigned char _buttonData[16];
	Joystick::ButtonState _buttonState[16];
	float _accuracy;
};

} // namespace fei

#endif // _FEI_JOYSTICK_H_
