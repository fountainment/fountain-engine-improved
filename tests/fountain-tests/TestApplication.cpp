#include "TestApplication.h"
#include "TestScene.h"

using namespace fei;

FontCache TestApplication::font;

void TestApplication::engineSetting(Engine *eg)
{
	if (!eg) return;

	eg->getWindow()->setSize(800, 600);
	eg->getWindow()->setTitle("fountain-tests");
	eg->getWindow()->setResizable(false);

	Physics::getInstance()->setRatio(30.0f);
	Physics::getInstance()->setGravity(Vec2::ZERO);

	font.loadFont("res/font/wqy.ttc");

	eg->getWindow()->getSceneManager()->defaultCamera.setCameraSize(Vec2(800, 600));
	eg->getWindow()->getSceneManager()->gotoScene(new TestScene());
}

