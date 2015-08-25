#include "fountain.h"
#include "TestApplication.h"

using namespace fei;

Camera cam, UICam;
TestApplication testApp;
Clock mainClock;
FrameAnime fa;
RenderList rl;
Texture tex, UI;

const int testNum = 100;
Texture texCopy[testNum];
FrameAnime animeCopy[testNum];

void test()
{
	//update
	mainClock.tick();

	auto engine = testApp.getEngine();
	if (engine->window->getKey(GLFW_KEY_P)) {
		fa.switchPlayAndPause();
	}
	//auto mpos = engine->window->getRHCursorPos();
	//std::printf("%.3f %.3f\n", mpos.x, mpos.y);

	auto winSize = engine->window->getWindowSize();
	cam.setCameraSize(winSize);
	UI.setScale(std::min(winSize.x / 1920.0f, winSize.y / 1181.0f));

	auto *joystick = Control::getInstance()->getJoystick();
	if (joystick) {
		Vec2 speed = joystick->getAxes() * 80.0f * (float)mainClock.getDeltaTime();
		fa.move(speed);
	}

	//draw
	cam.update();
	rl.update();
	rl.draw();
}

bool cmp(RenderObj* a, RenderObj* b)
{
	return a->getZPos() < b->getZPos();
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
	tex.loadFile("map.png");
	UI.loadFile("UI.png");

	rl.add(&tex);

	for (int i = 0; i < testNum; i++) {
		texCopy[i] = tex;
		texCopy[i].setPosition(Vec2(i, i));
		rl.add(&texCopy[i]);
	}

	for (int i = 0; i < testNum; i++) {
		animeCopy[i] = fa;
		animeCopy[i].setPosition(Vec2(i, i));
		rl.add(&animeCopy[i]);
	}

	UI.setIsAlpha(true);
	rl.add(&fa);
	rl.add(&UI);
	UICam = cam;
	cam.setCameraScale(2.0f);

	//Math::getInstance()->setRandomSeed(9312);
	//Render::getInstance()->setClearColor(FEI_Blue);
	//Scene::getInstance()->gotoScene(new TestScene());
}

int main()
{
	testApp.run();
	return 0;
}
