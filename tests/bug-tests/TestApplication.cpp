#include "TestApplication.h"
#include "TestScene.h"

using namespace fei;

void TestApplication::engineSetting(Engine *eg)
{
	if (!eg) return;

	eg->getWindow()->setSize(800, 600);
	eg->getWindow()->setTitle("bug-tests");
	eg->getWindow()->setResizable(false);

	Physics::getInstance()->setRatio(30.0f);
	Physics::getInstance()->setGravity(Vec2::ZERO);

	eg->getWindow()->getSceneManager()->gotoScene(new TestScene());
}

