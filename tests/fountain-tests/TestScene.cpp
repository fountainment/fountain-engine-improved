#include "TestScene.h"
#include "TestApplication.h"

using namespace fei;

void TestScene::init()
{
	pitch = 1.0f;

	setClock(&mainClock);

	mainCam.setCameraSize(Vec2(800, 600));
	mainCam.setCameraScale(2.0f);
	setCamera(&mainCam);
	Physics::getInstance()->setDebugDrawCamera(&mainCam);
	//Physics::getInstance()->setDoDebugDraw(true);

	map.load("res/image/map.png");

	auto winsize = fei::Interface::getInstance()->getCurrentWindow()->getWindowSize();
	UI.load("res/image/UI43.png");
	UI.setHasAlpha(true);
	UI.setScale(0.43f);

	UICam.setCameraSize(winsize);
	UILayer.setCamera(&UICam);
	UILayer.setHasAlpha(true);
	UILayer.add(&UI);
	UILayer.add(&fpsLabel);

	fpsLabel.setPosition(UICam.getCameraSize() * -0.5f);

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

	bomberNormal.bindLocation(1);
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
			mainChar.setSpeed(speed, 0.0f);
		}
	} else if (window) {
		Vec2 speed(Vec2::ZERO);
		bool move = false;
		if (window->getKey(GLFW_KEY_UP)) {
			speed.add( Vec2::UP);
			move = true;
		}
		if (window->getKey(GLFW_KEY_LEFT)) {
			speed.add(Vec2::LEFT);
			move = true;
		}
		if (window->getKey(GLFW_KEY_DOWN)) {
			speed.add(Vec2::DOWN);
			move = true;
		}
		if (window->getKey(GLFW_KEY_RIGHT)) {
			speed.add(Vec2::RIGHT);
			move = true;
		}
		if (move) {
			mainChar.setSpeed(speed, 100.0f);
		} else {
			mainChar.setSpeed(speed, 0.0f);
		}
	}
	mainCam.setPosition(mainChar.getPosition());

	Vec2 pos = mainCam.screenToWorld(window->getRHCursorPos());
	normalShader.setUniform("lightPos", pos);
	normalShader.setUniform("test", pos.x);

	char tmp[100];
	std::sprintf(tmp, "FPS: %.2f", Time::getInstance()->getFps());
	fpsLabel.setString(TestApplication::font, tmp);
}

void TestScene::keyCallback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		mainChar.attack();
	}
}
