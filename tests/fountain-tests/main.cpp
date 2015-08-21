#include "fountain.h"
#include "TestApplication.h"

using namespace fei;

Texture tex;
Camera cam;
TestApplication testApp;
Clock mainClock;
ShaderProgram shader;
Image image;

void test()
{
	//auto eg = testApp.getEngine();
	//if (eg->window->getKey(GLFW_KEY_W)) speed += fei::Vec2(0.0f, 2.0f);
	//if (eg->window->getKey(GLFW_KEY_S)) speed += fei::Vec2(0.0f, -2.0f);
	//if (eg->window->getKey(GLFW_KEY_A)) speed += fei::Vec2(-2.0f, 0.0f);
	//if (eg->window->getKey(GLFW_KEY_D)) speed += fei::Vec2(2.0f, 0.0f);
	Vec2 speed(0);
	auto *joystick = fei::Control::getInstance()->getJoystick();
	if (joystick) {
		speed = joystick->getAxes() * 500.0f * mainClock.getDeltaTime();
		image.setAngle(speed.getAngle());
		speed = joystick->getDirection() * 50.0f * mainClock.getDeltaTime();
		tex.rotate(-speed.x);
	}
	//cam.setPosition(pos);
	cam.update();
	tex.draw();
	image.draw();
	//char *buffer = fei::readFileBuffer("1.txt");
	//if (buffer) {
		//std::printf("%s", buffer);
		//delete [] buffer;
	//}
	//std::printf("Time: %f    Frame: %lld\n", fei::Time::getInstance()->getTime(), fei::Time::getInstance()->getFrame());
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

	cam.setCameraSize(fei::Vec2(4000, 3000));
	tex.loadFile("test.png");
	image = tex.getImage(fei::Vec2(100.0f), fei::Vec2(200.0f));
	image.setPosition(fei::Vec2(0.0f, 256.0f));
	shader.loadFile("vs.vert", "fs.frag");
	tex.setScale(2.0f);
	tex.setAnchor(Vec2(0.0f, -256.0f));
	//tex.setShader(&shader);

	//Math::getInstance()->setRandomSeed(9312);
	//Render::getInstance()->setClearColor(FEI_Blue);
	//Scene::getInstance()->gotoScene(new TestScene());
}

int main()
{
	testApp.run();
	return 0;
}
