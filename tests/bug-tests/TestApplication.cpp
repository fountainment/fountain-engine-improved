#include "TestApplication.h"
#include "TestScene.h"

using namespace fei;

void TestApplication::engineSetting(Engine *eg)
{
	if (!eg) return;

	eg->window->setSize(800, 600);
	eg->window->setTitle("bug-tests");
	eg->window->setResizable(false);

	Physics::getInstance()->setRatio(30.0f);
	Physics::getInstance()->setGravity(Vec2::ZERO);

	eg->window->getSceneManager()->defaultCamera.setCameraSize(Vec2(800, 600));
	eg->window->getSceneManager()->gotoScene(new TestScene());
}

