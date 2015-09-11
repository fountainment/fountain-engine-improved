#include "EditorScene.h"

using namespace fei;

void EditorScene::init()
{
	poly = Polygon::makeRegularPolygon(3, 200.0f);
	poly.setSolid(false);

	polyObj.setShape(&poly);
	add(&polyObj);

	auto vec = Interface::getInstance()->getCurrentWindow()->getWindowSize();
	mainCam.setCameraSize(vec);
	setCamera(&mainCam);
}

void EditorScene::update()
{
	auto window = Interface::getInstance()->getCurrentWindow();
	auto pos = window->getRHCursorPos();
	pos = mainCam.screenToWorld(pos);
	std::printf("%f %f\n", pos.x, pos.y);
}
