#include "fountain.h"
#include "TestApplication.h"

using namespace fei;

Texture tex;
Camera cam;
TestApplication testApp;
Clock mainClock;
Image *image, *image2;
ImagePool testPool;

void test()
{
	cam.setCameraSize(Render::getInstance()->getViewport().getSize());
	auto *joystick = fei::Control::getInstance()->getJoystick();
	if (joystick) {
		Vec2 speed = joystick->getAxes() * 500.0f * (float)mainClock.getDeltaTime();
		image->setAngle(speed.getAngle());
		speed = joystick->getDirection() * 50.0f * (float)mainClock.getDeltaTime();
		tex.rotate(-speed.x);
	}
	cam.update();
	tex.draw();
	image->draw();
	image2->draw();
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
	tex.loadFile("test.png");

	testPool.load(tex, "test.sip");
	image = testPool.getImage(0);
	image2 = testPool.getImage(1);
	image->setPosition(fei::Vec2(0.0f, 256.0f));

	//Math::getInstance()->setRandomSeed(9312);
	//Render::getInstance()->setClearColor(FEI_Blue);
	//Scene::getInstance()->gotoScene(new TestScene());
}

int main()
{
	testApp.run();
	return 0;
}
