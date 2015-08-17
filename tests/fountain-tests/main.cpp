#include "fountain.h"
#include "TestApplication.h"

fei::Texture tex;
fei::Camera cam;
TestApplication testApp;
fei::Clock mainClock;

void test()
{
	auto eg = testApp.getEngine();
	fei::Vec2 speed(0);
	if (eg->window->getKey(GLFW_KEY_W)) speed += fei::Vec2(0.0f, 2.0f);
	if (eg->window->getKey(GLFW_KEY_S)) speed += fei::Vec2(0.0f, -2.0f);
	if (eg->window->getKey(GLFW_KEY_A)) speed += fei::Vec2(-2.0f, 0.0f);
	if (eg->window->getKey(GLFW_KEY_D)) speed += fei::Vec2(2.0f, 0.0f);
	speed *=  mainClock.getDeltaTime();
	cam.move(speed);
	cam.update();
	tex.draw();
	char *buffer = fei::readFileBuffer("1.txt");
	if (buffer) {
		std::printf("%s", buffer);
		delete [] buffer;
	}
	std::printf("Time: %f    Frame: %lld\n", fei::Time::getInstance()->getTime(), fei::Time::getInstance()->getFrame());
	mainClock.tick();
}

void TestApplication::engineSetting(fei::Engine *eg)
{
	if (!eg) return;
	eg->window->setSize(800, 600);
	eg->window->setTitle("fountain-tests");
	eg->window->setResizable(false);

	eg->setFrameFunc(test);

	fei::Render::getInstance()->setViewport(fei::Rect(0, 0, 800, 600));

	cam.setCameraSize(fei::Vec2(8, 6));
	tex.loadFile("test.png");

	//fei::Math::getInstance()->setRandomSeed(9312);
	//fei::Render::getInstance()->setClearColor(FEI_Blue);

	//fei::Scene::getInstance()->gotoScene(new TestScene());
}

int main()
{
	testApp.run();
	return 0;
}
