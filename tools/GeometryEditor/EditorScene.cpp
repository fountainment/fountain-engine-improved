#include "EditorScene.h"

using namespace fei;

void EShapeObj::drawIt()
{
	auto window = Interface::getInstance()->getCurrentWindow();
	auto scene = window->sceneManager->getCurScene();
	auto cam = scene->getCamera();

	Render::drawShape(shape);

	Circle circle(7.0f / cam->getCameraScale());

	const float *data = shape->getDataPtr();
	for (int i = 0; i < shape->getDataSize(); i++) {
		circle.setPosition(fei::Vec2(data[i << 1], data[i << 1 | 1]));
		Render::drawShape(&circle);
	}
}

void Cross::drawIt()
{
	Render::drawShape(&a);
	Render::drawShape(&b);
}

void Cross::setSize(float sz)
{
	a.a = Vec2(-sz / 2.0f, 0.0f);
	a.b = Vec2(sz / 2.0f, 0.0f);
	b.a = Vec2(0.0f, -sz / 2.0f);
	b.b = Vec2(0.0f, sz / 2.0f);
}

void EditorScene::init()
{
	Physics::getInstance()->setDoDebugDraw(true);
	Physics::getInstance()->setDebugDrawCamera(&mainCam);
	Physics::getInstance()->setRatio(64.0f);

	for (int i = 0; i < 10; i++) {
		poly[i] = Polygon::makeRegularPolygon(4, 100.0f, 45.0f);
		poly[i].setSolid(false);
	}

	for (int i = 0; i < 10; i++) {
		char tmpStr[2];
		tmpStr[0] = '0' + i;
		tmpStr[1] = '\0';
		std::string t(tmpStr);
		t += ".png";
		tex[i].load(t.c_str());
	}
	image = tex[0].getImage();
	add(&image);

	centerCross.setSize(10.0f);
	add(&centerCross);

	polyObj.setShape(&poly[0]);
	add(&polyObj);

	auto vec = Interface::getInstance()->getCurrentWindow()->getWindowSize();
	mainCam.setCameraSize(vec);
	setCamera(&mainCam);

	curEdit = 0;
	holdVertex = -1;

	animeBody = Physics::getInstance()->createBody(Vec2::ZERO, Body::Type::STATIC);
	animeBody->getB2Body()->SetGravityScale(0.0f);
	add(&animeObj);
}

void EditorScene::update()
{
	auto window = Interface::getInstance()->getCurrentWindow();

	if (holdVertex >= 0) {
		poly[curEdit].setVertex(holdVertex, pos);
	}

	mPos = window->getRHCursorPos();
	deltaV = (mPos - oldPos) / mainCam.getCameraScale();
	oldPos = mPos;

	if (window->getMouseButton(GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
		mainCam.move(-deltaV);
	}

	if (window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT) && window->getKey(GLFW_KEY_LEFT_CONTROL)) {
		poly[curEdit].moveVertices(deltaV);
	}

	if (window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT) && window->getKey(GLFW_KEY_LEFT_SHIFT)) {
		anime[curEdit].getFramePool()->moveImageAnchor(-deltaV);
	}

	if (window->getKey(GLFW_KEY_A)) {
		auto list = poly[curEdit].box2dDecomposition();
		auto body = Physics::getInstance()->createBody(Vec2::ZERO, Body::Type::DYNAMIC);
		body->createFixture(list);
	}
}

void EditorScene::loadAnime(const std::string& path)
{
	auto name = path;
	name.erase(name.size() - 3, 3);
	ipiName = name + "ipi";
	anime[curEdit].loadImageFileAndIPI(name + "png", ipiName);
	animeObj.setAnime(&anime[curEdit]);
	anime[curEdit].setFps(15);
	anime[curEdit].setLoop(true);
	anime[curEdit].setBody(animeBody);
	anime[curEdit].play();
}

void EditorScene::mouseButtonCallback(int button, int action, int mods)
{
	auto window = Interface::getInstance()->getCurrentWindow();

	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			holdVertex = poly[curEdit].collideVertex(pos, 10.0f / mainCam.getCameraScale());
		}
		if (action == GLFW_RELEASE) {
			holdVertex = -1;
		}
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		if (!window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT)) {
			int loc = poly[curEdit].closestWhichSegment(pos);
			loc = poly[curEdit].indexNormalize(loc + 1);
			poly[curEdit].insertVertex(pos, loc);
		} else {
			if (holdVertex != -1) {
				poly[curEdit].deleteVertex(holdVertex);
				holdVertex = -1;
			}
		}
	}
}

void EditorScene::cursorPosCallback(double xpos, double ypos)
{
	auto window = Interface::getInstance()->getCurrentWindow();
	pos = mainCam.screenToWorld(window->getRHCursorPos());
}

void EditorScene::scrollCallback(double xoffset, double yoffset)
{
	if (yoffset > 0.0f) {
		mainCam.zoomCameraScale(1.1f);
	}
	if (yoffset < 0.0f) {
		mainCam.zoomCameraScale(0.9f);
	}
}

void EditorScene::keyCallback(int key, int scancode, int action, int mods)
{
	auto window = Interface::getInstance()->getCurrentWindow();

	if (key == GLFW_KEY_SPACE) {
		if (action == GLFW_PRESS) {
			poly[curEdit].setSolid(true);
		}
		if (action == GLFW_RELEASE) {
			poly[curEdit].setSolid(false);
		}
	}

	if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
		window->setFullscreen(!window->isFullscreen());
		Render::getInstance()->setViewport(window->getFrameSize());
		mainCam.setCameraSize(window->getFrameSize());
	}

	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		auto list = poly[curEdit].box2dDecomposition();
		auto body = Physics::getInstance()->createBody(Vec2::ZERO, Body::Type::DYNAMIC);
		body->getB2Body()->SetGravityScale(0.0f);
		FixtureGroup fixtures = body->createFixture(list);
		fixtures.setSensor(true);
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		auto list = poly[curEdit].box2dDecomposition();
		auto body = Physics::getInstance()->createBody(Vec2::ZERO, Body::Type::DYNAMIC);
		body->createFixture(list);
	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		auto list = poly[curEdit].box2dDecomposition();
		auto body = Physics::getInstance()->createBody(Vec2::ZERO, Body::Type::STATIC);
		body->createFixture(list);
	}

	if (key >= GLFW_KEY_F1 && key <= GLFW_KEY_F10 && action == GLFW_PRESS) {
		curEdit = key - GLFW_KEY_F1;
		image = tex[curEdit].getImage();
		polyObj.setShape(&poly[curEdit]);
		holdVertex = -1;
	}

	if (key >= GLFW_KEY_0 && key <= GLFW_KEY_9 && action == GLFW_PRESS) {
		int t = key - GLFW_KEY_0;
		anime[curEdit].setCurFrameIndex(t);
		anime[curEdit].pause();
	}

	if (key == GLFW_KEY_I && action == GLFW_PRESS) {
		anime[curEdit].insertFrame(anime[curEdit].getCurFrameIndex(), poly[curEdit]);
	}

	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		anime[curEdit].play();
	}

	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		anime[curEdit].print();
	}

	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		anime[curEdit].getFramePool()->roundAnchor();
	}

	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		if (ipiName == "") {
			ipiName = "new.ipi";
		}
		anime[curEdit].getFramePool()->dumpIPI(ipiName);
	}
}

void EditorScene::framebufferSizeCallback(int width, int height)
{
	Vec2 framebufferSize((float)width, (float)height);
	mainCam.setCameraSize(framebufferSize);
}

void EditorScene::dropCallback(int count, const char** paths)
{
	int len = std::strlen(paths[0]);
	if (len < 3) {
		return;
	}
	if (std::strcmp(&paths[0][len - 3], "ipi") == 0 || \
				std::strcmp(&paths[0][len - 3], "png") == 0) {
		loadAnime(paths[0]);
	}
}
