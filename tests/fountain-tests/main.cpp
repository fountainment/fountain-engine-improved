#include "fountain.h"
#include "TestApplication.h"

using namespace fei;

Texture tex;
Camera cam;
TestApplication testApp;
Clock mainClock;
ShaderProgram shader;
Image image, image2;

void test()
{
	auto *joystick = fei::Control::getInstance()->getJoystick();
	if (joystick) {
		Vec2 speed = joystick->getAxes() * 500.0f * (float)mainClock.getDeltaTime();
		image.setAngle(speed.getAngle());
		speed = joystick->getDirection() * 50.0f * (float)mainClock.getDeltaTime();
		tex.rotate(-speed.x);
	}
	cam.update();
	tex.draw();
	image.draw();
	image2.draw();
	mainClock.tick();
}

void TestApplication::engineSetting(fei::Engine *eg)
{
	if (!eg) return;
	eg->window->setSize(800, 600);
	eg->window->setTitle("fountain-tests");
	eg->window->setResizable(false);

	eg->setFrameFunc(test);

	Render::getInstance()->setViewport(fei::Rect(0, 0, 800, 600));

	cam.setCameraSize(fei::Vec2(800, 600));
	tex.loadFile("test.png");
	image = tex.getImage(fei::Vec2(100.0f), fei::Vec2(200.0f));
	image2 = image.getImage(fei::Vec2(0.0f), fei::Vec2(100.0f));
	image.setPosition(fei::Vec2(0.0f, 256.0f));
	shader.loadFile("vs.vert", "fs.frag");
	tex.setScale(0.4f);
	tex.setAnchor(Vec2(0.0f, -256.0f));
	tex.setShader(&shader);

	//Math::getInstance()->setRandomSeed(9312);
	//Render::getInstance()->setClearColor(FEI_Blue);
	//Scene::getInstance()->gotoScene(new TestScene());
}

int main()
{
	testApp.run();
	return 0;
}
