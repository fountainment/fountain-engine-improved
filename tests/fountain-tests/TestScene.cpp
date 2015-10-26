#include "TestScene.h"

using namespace fei;

void TestScene::init()
{
	pitch = 1.0f;

	setClock(&mainClock);

	mainCam.setCameraSize(Vec2(800, 600));
	mainCam.setCameraScale(2.0f);
	setCamera(&mainCam);
	Physics::getInstance()->setDebugDrawCamera(&mainCam);
	Physics::getInstance()->setDoDebugDraw(true);

	map.load("res/image/map.png");

	UI.load("res/image/UI43.png");
	UI.setHasAlpha(true);

	UICam.setCameraSize(Vec2(1920, 1440));
	UILayer.setCamera(&UICam);
	UILayer.setHasAlpha(true);
	UILayer.add(&UI);

	UI.setColor(Color(Vec3(1.0f), 0.8f));

	Rect rect[2] = {Rect(Vec2(550.0f, 20.0f)), Rect(Vec2(20.0f, 550.0f))};
	rect[0].setCenter(Vec2::ZERO);
	rect[1].setCenter(Vec2::ZERO);

	Vec2 v[4] = {Vec2(0.0f, -280.0f), Vec2(0.0f, 260.0f), Vec2(-260.0f, 0.0f), Vec2(260.0f, 0.0f)};

	for (int i = 0; i < 4; i++) {
		ground[i] = Physics::getInstance()->createBody(v[i], Body::Type::STATIC);
		ground[i]->createFixture(&rect[i / 2]);
	}

	normalShader.loadFile("res/shader/normal.vert", "res/shader/normal.frag");
	bomber.load("res/image/Walk_s1.png");
	bomber.setShader(&normalShader);

	bomberNormal.load("res/image/Walk_s2.png");

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bomberNormal.getId());
	glActiveTexture(GL_TEXTURE0);
	normalShader.setUniform("feiNormalTex", 1);

	add(&map);
	add(&bomber);
	add(&mainChar);
	add(&UILayer);
}

void TestScene::destroy()
{
	for (int i = 0; i < 4; i++) {
		Physics::getInstance()->destroyBody(ground[i]);
	}
	Physics::getInstance()->setDebugDrawCamera(nullptr);
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
			mainChar.setSpeed(Vec2::ZERO);
		}
	} else if (window) {
		Vec2 speed(Vec2::ZERO);
		if (window->getKey(GLFW_KEY_UP)) {
			speed.add(Vec2::UP);
		}
		if (window->getKey(GLFW_KEY_LEFT)) {
			speed.add(Vec2::LEFT);
		}
		if (window->getKey(GLFW_KEY_DOWN)) {
			speed.add(Vec2::DOWN);
		}
		if (window->getKey(GLFW_KEY_RIGHT)) {
			speed.add(Vec2::RIGHT);
		}
		mainChar.setSpeed(speed, 100.0f);
	}
	mainCam.setPosition(mainChar.getPosition());

	Vec2 pos = mainCam.screenToWorld(window->getRHCursorPos());
	normalShader.setUniform("lightPos", pos);
	normalShader.setUniform("test", pos.x);

	std::printf("%.2f\n", Time::getInstance()->getFps());
}
