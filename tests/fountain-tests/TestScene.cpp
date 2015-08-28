#include "TestScene.h"

using namespace fei;

void TestScene::init()
{
	setClock(&mainClock);

	mainCam.setCameraSize(Vec2(800, 600));
	mainCam.setCameraScale(2.0f);

	map.load("map.png");

	UI.load("UI43.png");
	UI.setIsAlpha(true);

	UICam.setCameraSize(Vec2(1920, 1440));
	UILayer.setCamera(&UICam);
	UILayer.setIsAlpha(true);
	UILayer.add(&UI);

	setCamera(&mainCam);

	add(&map);
	add(&mainChar);
	add(&UILayer);
}

void TestScene::update()
{
	auto joystick = Control::getInstance()->getJoystick();
	if (joystick) {
		auto speed = joystick->getAxes();
		float sp = speed.getLengthSq();
		if (sp > 0.49f) {
			mainChar.setSpeed(speed, 80.0f);
		} else if (sp > 0.0001f) {
			mainChar.setSpeed(speed, 30.0f);
		} else {
			mainChar.setSpeed(Vec2(0.0f));
		}
	}
	mainCam.setPosition(mainChar.getPosition());
}
