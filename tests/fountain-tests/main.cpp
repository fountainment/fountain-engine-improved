#include "fountain.h"
#include "TestApplication.h"

using namespace fei;

class TestScene : public Scene
{
public:
	void init()
	{
		setClock(&mainClock);

		mainCam.setCameraSize(Vec2(800, 600));
		mainCam.setCameraScale(2.0f);

		map.load("map.png");

		mainCharAnime.load("test.png", "test.sip");
		mainCharAnime.setLoop(true);
		mainCharAnime.setFps(15);

		UI.load("UI.png");
		UI.setIsAlpha(true);

		UICam.setCameraSize(Vec2(1920, 1181));
		UILayer.setCamera(&UICam);	
		UILayer.setIsAlpha(true);
		UILayer.add(&UI);

		setCamera(&mainCam);

		add(&map);
		add(&mainCharAnime);
		add(&UILayer);
	}

	void destroy()
	{
	}

	void update()
	{
	}

private:
	Clock mainClock;
	Camera mainCam, UICam;
	FrameAnime mainCharAnime;
	Texture UI, map;
	Layer UILayer;
};

SceneManager sm;

void test()
{
	sm.renderCurScene();
}

void TestApplication::engineSetting(Engine *eg)
{
	if (!eg) return;
	eg->window->setSize(800, 600);
	eg->window->setTitle("fountain-tests");
	eg->window->setResizable(false);

	eg->setFrameFunc(test);

	sm.gotoScene(new TestScene());

	//Math::getInstance()->setRandomSeed(9312);
	//Render::getInstance()->setClearColor(FEI_Blue);
	//Scene::getInstance()->gotoScene(new TestScene());
}

int main()
{
	TestApplication testApp;
	testApp.run();
	return 0;
}
