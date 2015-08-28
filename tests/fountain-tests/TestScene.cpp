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
	auto window = Interface::getInstance()->getCurrentWindow();
	if (joystick) {
		auto speed = joystick->getAxes();
		float sp = speed.getLengthSq();
		if (sp > 0.49f) {
			mainChar.setSpeed(speed, 200.0f);
		} else if (sp > 0.0001f) {
			mainChar.setSpeed(speed, 100.0f);
		} else {
			mainChar.setSpeed(Vec2(0.0f));
		}
	} else if (window) {
		Vec2 speed(0.0f);
		if (window->getKey(GLFW_KEY_W)) {
			speed.set(0.0f, 1.0f);
		}
		if (window->getKey(GLFW_KEY_A)) {
			speed.set(-1.0f, 0.0f);
		}
		if (window->getKey(GLFW_KEY_S)) {
			speed.set(0.0f, -1.0f);
		}
		if (window->getKey(GLFW_KEY_D)) {
			speed.set(1.0f, 0.0f);
		}
		mainChar.setSpeed(speed, 100.0f);
	}
	mainCam.setPosition(mainChar.getPosition());
}
