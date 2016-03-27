#include "editor.h"

using namespace fei;

void EditorScene::init()
{
	Physics::getInstance()->setDoDebugDraw(true);
	Physics::getInstance()->setDebugDrawCamera(&_camera);
	Physics::getInstance()->setRatio(64.0f);

	setCamera(&_camera);

	add(&_commandLabel);

	_fontCache.loadFont("res/font/wqy.ttc", 20);
	_commandLabel.setFontCache(&_fontCache);

	auto gravityFunc =
		[](std::vector<std::string> params)
		{
			double a = 0.0;
			double b = 0.0;
			if (params.size() == 2) {
				a = std::atof(params[0].c_str());
				b = std::atof(params[1].c_str());
				Physics::getInstance()->setGravity(Vec2(a, b));
			} else {
				return fut::CommandResult(fut::CommandResult::Type::ERROR, "Param size must be 2!");
			}
			return fut::CommandResult::Ok;
		};
	auto newRectFunc =
		[](std::vector<std::string> params)
		{
			double data[4] = {0.0};
			if (params.size() == 4) {
				for (int i = 0; i < 4; i++) {
					data[i] = std::atof(params[i].c_str());
				}
				auto body = Physics::getInstance()->createBody(Vec2::ZERO, Body::Type::DYNAMIC);
				Rect rect(data[0], data[1], data[2], data[3]);
				body->createFixture(&rect);
			} else {
				return fut::CommandResult(fut::CommandResult::Type::ERROR, "Param size must be 4!");
			}
			return fut::CommandResult::Ok;
		};
	auto newCircleFunc =
		[](std::vector<std::string> params)
		{
			double data[3] = {0.0};
			if (params.size() == 3) {
				for (int i = 0; i < 3; i++) {
					data[i] = std::atof(params[i].c_str());
				}
				auto body = Physics::getInstance()->createBody(Vec2::ZERO, Body::Type::DYNAMIC);
				Circle circle(Vec2(data[0], data[1]), data[2]);
				body->createFixture(&circle);
			} else {
				return fut::CommandResult(fut::CommandResult::Type::ERROR, "Param size must be 4!");
			}
			return fut::CommandResult::Ok;
		};
	auto newPolygonFunc =
		[](std::vector<std::string> params)
		{
			//TODO
			return fut::CommandResult::Ok;
		};

	_commandLabel.getInterpreter()->registerCommand({":set", "gravity"}, gravityFunc);
	_commandLabel.getInterpreter()->registerCommand({":new", "rect"}, newRectFunc);
	_commandLabel.getInterpreter()->registerCommand({":new", "circle"}, newCircleFunc);
	_commandLabel.getInterpreter()->registerCommand({":new", "polygon"}, newPolygonFunc);

	initUILayout();
}

void EditorScene::initUILayout()
{
	_camera.setCameraSize(Application::getEngine()->getWindow()->getWindowSize());
	_commandLabel.setPosition(getCamera()->screenToWorld(Vec2(5.0f)));
}

void EditorScene::charactorCallback(unsigned int codepoint)
{
	_commandLabel.inputChar(static_cast<char>(codepoint));
}

void EditorScene::keyCallback(int key, int scancode, int action, int mods)
{
	switch (key) {
	case GLFW_KEY_BACKSPACE:
		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			_commandLabel.deleteChar();
		}
		break;
	case GLFW_KEY_ENTER:
		if (action == GLFW_PRESS) {
			_commandLabel.executeCommand();
		}
	}
}
