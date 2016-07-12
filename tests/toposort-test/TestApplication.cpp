#include "TestApplication.h"

#include "TestScene.h"

using namespace fei;

void TopoTest::engineSetting(Engine* eg)
{
	eg->getWindow()->setFullscreen(true);
	eg->getWindow()->getSceneManager()->gotoScene(new TopoScene);
}
