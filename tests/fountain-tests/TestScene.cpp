#include "TestScene.h"

using namespace fei;

void TestScene::init()
{
	setClock(&mainClock);

	mainCam.setCameraSize(Vec2(800, 600));
	mainCam.setCameraScale(2.0f);

	map.load("map.png");

	mainCharAnime.load("test.png", "test.sip");
	mainCharAnime.setLoop(true);
	mainCharAnime.setFps(15);

	UI.load("UI43.png");
	UI.setIsAlpha(true);

	UICam.setCameraSize(Vec2(1920, 1440));
	UILayer.setCamera(&UICam);
	UILayer.setIsAlpha(true);
	UILayer.add(&UI);

	setCamera(&mainCam);

	add(&map);
	add(&mainCharAnime);
	add(&UILayer);
}

void TestScene::update()
{
	auto joystick = Control::getInstance()->getJoystick();
	if (joystick) {
		auto speed = joystick->getAxes();
		float sp = speed.getLengthSq();
		speed.normalize();
		if (sp > 0.25f) {
			mainCharAnime.move(speed * 80.0f * mainClock.getDeltaTime());	
		} else if (sp > 0.0001f) {
			mainCharAnime.move(speed * 50.0f * mainClock.getDeltaTime());
		}
	}
	mainCam.setPosition(mainCharAnime.getPosition());
}
