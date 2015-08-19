#if !defined(_FEI_JOYSTICK_H_)
#define _FEI_JOYSTICK_H_

#include "math/Vec2.h"

namespace fei {

class Joystick
{
public:
	friend class Control;
	Joystick();
	//int getKey();
	bool usable();
	float getAxesX();
	float getAxesY();
	Vec2 getAxes();
	Vec2 getTouch();

private:
	void init();
	void update();
	void clearData();
	int id;
	float axesData[16];
	unsigned char buttonData[16];

};

}

#endif
