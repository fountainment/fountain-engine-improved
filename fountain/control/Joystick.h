#if !defined(_FEI_JOYSTICK_H_)
#define _FEI_JOYSTICK_H_

#include "math/Vec2.h"

namespace fei {

class Joystick
{
public:
	friend class Control;
	Joystick();
	//int getKey(int key);
	bool usable();
	int getAxesCount();
	int getButtonCount();
	float getAxesX();
	float getAxesY();
	Vec2 getAxes();
	float getDirectionX();
	float getDirectionY();
	Vec2 getDirection();
	float getTouchX();
	float getTouchY();
	Vec2 getTouch();

private:
	void init();
	void update();
	void clearData();
	int id;
	int axesCount;
	float axesData[16];
	int buttonCount;
	unsigned char buttonData[16];

};

}

#endif
