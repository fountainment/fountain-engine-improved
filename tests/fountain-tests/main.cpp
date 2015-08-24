#include "fountain.h"
#include "TestApplication.h"

using namespace fei;

Camera cam;
TestApplication testApp;
Clock mainClock;
FrameAnime fa;

void test()
{
	cam.setCameraSize(Render::getInstance()->getViewport().getSize());
	auto *joystick = fei::Control::getInstance()->getJoystick();
	if (joystick) {
		Vec2 speed = joystick->getAxes() * 500.0f * (float)mainClock.getDeltaTime();
		fa.move(speed);
	}
	cam.update();
	fa.update();
	fa.draw();
	mainClock.tick();
}

void TestApplication::engineSetting(fei::Engine *eg)
{
	if (!eg) return;
	eg->window->setSize(800, 600);
	eg->window->setTitle("fountain-tests");
	eg->window->setResizable(false);

	eg->setFrameFunc(test);

	cam.setCameraSize(fei::Vec2(800, 600));

	fa.load("test.png", "test.sip");

	//Math::getInstance()->setRandomSeed(9312);
	//Render::getInstance()->setClearColor(FEI_Blue);
	//Scene::getInstance()->gotoScene(new TestScene());
}

int main()
{
	testApp.run();
	return 0;
}
