#include "fountain.h"
#include "TestApplication.h"

using namespace fei;

Camera cam;
TestApplication testApp;
Clock mainClock;
FrameAnime fa;

void test()
{
	//update
	mainClock.tick();

	auto engine = testApp.getEngine();
	if (engine->window->getKey(GLFW_KEY_P)) {
		fa.switchPlayAndPause();
	}
	auto mpos = engine->window->getRHCursorPos();
	std::printf("%.3f %.3f\n", mpos.x, mpos.y);
	fa.update();

	cam.setCameraSize(engine->window->getWindowSize());

	auto *joystick = Control::getInstance()->getJoystick();
	if (joystick) {
		Vec2 speed = joystick->getAxes() * 500.0f * (float)mainClock.getDeltaTime();
		fa.move(speed);
	}

	//draw
	cam.update();
	fa.draw();
}

void TestApplication::engineSetting(Engine *eg)
{
	if (!eg) return;
	eg->window->setSize(800, 600);
	eg->window->setTitle("fountain-tests");
	eg->window->setResizable(false);

	eg->setFrameFunc(test);

	fa.load("test.png", "test.sip");
	fa.setFps(15);
	fa.setLoop(true);

	//Math::getInstance()->setRandomSeed(9312);
	//Render::getInstance()->setClearColor(FEI_Blue);
	//Scene::getInstance()->gotoScene(new TestScene());
}

int main()
{
	testApp.run();
	return 0;
}
