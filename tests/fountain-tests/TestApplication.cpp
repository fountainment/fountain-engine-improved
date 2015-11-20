#include "TestApplication.h"
#include "TestScene.h"

using namespace fei;

FontCache TestApplication::font;

void TestApplication::engineSetting(Engine *eg)
{
	if (!eg) return;

	eg->window->setSize(800, 600);
	eg->window->setTitle("fountain-tests");
	eg->window->setResizable(false);

	Physics::getInstance()->setRatio(30.0f);
	Physics::getInstance()->setGravity(Vec2::ZERO);

	font.loadFont("res/font/wqy.ttc", 32);

	eg->window->sceneManager->defaultCamera.setCameraSize(Vec2(800, 600));
	eg->window->sceneManager->gotoScene(new TestScene());
}

