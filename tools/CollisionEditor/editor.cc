#include "editor.h"

using namespace fei;

void EditorScene::init()
{
	_editState = EditState::NONE;
	_mouseDown = false;
	_needInitUILayout = false;
	_editCircle.setRadius(64.0f);
	_editPolygon.setSolid(false);

	_editShapeObj.setColorAlpha(0.5f);

	Physics::getInstance()->setDoDebugDraw(true);
	Physics::getInstance()->setDebugDrawCamera(&_camera);
	Physics::getInstance()->setRatio(64.0f);

	setCamera(&_camera);

	_texture.setHasAlpha(true);
	add(&_texture);
	add(&_editShapeObj);
	add(&_uiLayer);

	_uiLayer.setCamera(&_uiCamera);
	_uiLayer.add(&_commandLabel);

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
			if (params.size() < 6) {
				auto ret = fut::CommandResult::Error;
				ret._result = "Vertices less than 3!";
				return ret;
			}
			Polygon poly;
			poly.setDataVector(fei::strVecToVec2Vec(params));
			auto body = Physics::getInstance()->createBody(Vec2::ZERO, Body::Type::DYNAMIC);
			body->createFixture(poly);
			return fut::CommandResult::Ok;
		};
	auto debugdrawFunc =
		[](std::vector<std::string> params)
		{
			if (params.size() == 1) {
				if (params[0] == "on") {
					Physics::getInstance()->setDoDebugDraw(true);
					return fut::CommandResult::Ok;
				} else if (params[0] == "off") {
					Physics::getInstance()->setDoDebugDraw(false);
					return fut::CommandResult::Ok;
				}
			}
			return fut::CommandResult(fut::CommandResult::Type::ERROR, "Param must be 'on' or 'off'!");
		};
	auto quitFunc =
		[](std::vector<std::string> params)
		{
			Application::getEngine()->exit();
			return fut::CommandResult::Ok;
		};
	auto loadImageFunc =
		[this](std::vector<std::string> params)
		{
			if (params.size() != 1) {
				return fut::CommandResult(fut::CommandResult::Type::ERROR, "Param must be image filename!");
			}
			_texture.load(params[0]);
			return fut::CommandResult::Ok;
		};
	auto editRectFunc =
		[this](std::vector<std::string> params)
		{
			editRect();
			return fut::CommandResult::Ok;
		};
	auto editCircleFunc =
		[this](std::vector<std::string> params)
		{
			editCircle();
			return fut::CommandResult::Ok;
		};
	auto editPolygonFunc =
		[this](std::vector<std::string> params)
		{
			editPolygon();
			return fut::CommandResult::Ok;
		};
	auto saveFunc =
		[this](std::vector<std::string> params)
		{
			if (params.size() >= 1) {
				_saveName = params[0];
			}
			return fut::CommandResult::Ok;
		};

	auto interpreter = _commandLabel.getInterpreter();
	interpreter->registerCommand({":set", "gravity"}, gravityFunc);
	interpreter->registerCommand({":set", "debugdraw"}, debugdrawFunc);
	interpreter->registerCommand({":new", "rect"}, newRectFunc);
	interpreter->registerCommand({":new", "circle"}, newCircleFunc);
	interpreter->registerCommand({":new", "polygon"}, newPolygonFunc);
	interpreter->registerCommand({":load", "img"}, loadImageFunc);
	interpreter->registerCommand({":edit", "rect"}, editRectFunc);
	interpreter->registerCommand({":edit", "circle"}, editCircleFunc);
	interpreter->registerCommand({":edit", "polygon"}, editPolygonFunc);
	interpreter->registerCommand({":w"}, saveFunc);
	interpreter->registerCommand({":q"}, quitFunc);

	initUILayout();
}

void EditorScene::update()
{
	auto window = Application::getEngine()->getWindow();
	auto deltaV = window->getRHCursorDeltaV() / _camera.getCameraScale();
	if (window->getMouseButton(GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
		_camera.move(-deltaV);
	}

	auto cursorWPos = getCursorWorldPos();
	_editShapeObj.setVisible(_mouseDown && _editState != EditState::NONE);
	switch (_editState) {
	case EditState::NONE:
		break;
	case EditState::RECT:
		_editRect = fei::Rect(_mouseDownPos, cursorWPos - _mouseDownPos);
		break;
	case EditState::CIRCLE:
		if (_mouseDown && window->getKey(GLFW_KEY_W)) {
			_editCircle.setRadius(_editCircle.getRadius() + 1.0f);
		}
		if (_mouseDown && window->getKey(GLFW_KEY_S)) {
			_editCircle.setRadius(_editCircle.getRadius() - 1.0f);
		}
		_editCircle.setPosition(cursorWPos);
		break;
	case EditState::POLYGON:
		break;
	}

	if (_needInitUILayout) {
		initUILayout();
		_needInitUILayout = false;
	}
}

void EditorScene::initUILayout()
{
	auto window = Application::getEngine()->getWindow();
	_camera.setCameraSize(window->getFrameSize());
	_uiCamera.setCameraSize(window->getFrameSize());
	_commandLabel.setPosition(_uiCamera.screenToWorld(Vec2(5.0f)));
}

void EditorScene::clearEditState()
{
	_mouseDown = false;
}

void EditorScene::editRect()
{
	clearEditState();
	_editState = EditState::RECT;
	_editShapeObj.setShape(&_editRect);
}

void EditorScene::editCircle()
{
	clearEditState();
	_editState = EditState::CIRCLE;
	_editShapeObj.setShape(&_editCircle);
}

void EditorScene::editPolygon()
{
	clearEditState();
	_editState = EditState::POLYGON;
	_editShapeObj.setShape(&_editPolygon);
}

const Vec2 EditorScene::getCursorWorldPos()
{
	auto window = Application::getEngine()->getWindow();
	return _camera.screenToWorld(window->getRHCursorPos());
}

void EditorScene::charactorCallback(unsigned int codepoint)
{
	_commandLabel.inputChar(static_cast<char>(codepoint));
}

void EditorScene::keyCallback(int key, int scancode, int action, int mods)
{
	auto window = Application::getEngine()->getWindow();
	switch (key) {
	case GLFW_KEY_BACKSPACE:
		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			_commandLabel.deleteChar();
		}
		break;
	case GLFW_KEY_F11:
		if (action == GLFW_PRESS) {
			window->setFullscreen(!window->isFullscreen());
			_needInitUILayout = true;
		}
		break;
	case GLFW_KEY_ENTER:
		if (action == GLFW_PRESS) {
			_commandLabel.executeCommand();
		}
		break;
	case GLFW_KEY_UP:
		if (action == GLFW_PRESS) {
			_commandLabel.prevCommand();
		}
		break;
	case GLFW_KEY_DOWN:
		if (action == GLFW_PRESS) {
			_commandLabel.nextCommand();
		}
		break;
	case GLFW_KEY_I:
		if (action == GLFW_PRESS && _editState == EditState::POLYGON && _mouseDown) {
			_editPolygon.insertVertexOnClosestSegment(getCursorWorldPos() - _editPolygon.getPosition());
		}
		break;
	case GLFW_KEY_V:
		if (action == GLFW_PRESS && _editState == EditState::POLYGON && _mouseDown) {
			_editPolygon.pushVertex(getCursorWorldPos() - _editPolygon.getPosition());
		}
		break;
	}
}

void EditorScene::scrollCallback(double xoffset, double yoffset)
{
	if (yoffset > 0.0) {
		_camera.zoomCameraScale(1.1f);
	} else if (yoffset < 0.0) {
		_camera.zoomCameraScale(0.9f);
	}
}

void EditorScene::mouseButtonCallback(int button, int action, int mods)
{
	auto bodyType = Body::Type::STATIC; 
	auto cursorWPos = getCursorWorldPos();
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			if (_editState != EditState::NONE) {
				_mouseDown = true;
				_mouseDownPos = getCursorWorldPos();
			}
		} else if (action == GLFW_RELEASE) {
			if (_mouseDown) {
				switch (_editState) {
				case EditState::NONE:
					break;
				case EditState::RECT:
					{
						auto body = Physics::getInstance()->createBody(Vec2::ZERO, bodyType);
						body->createFixture(&_editRect);
						_rectList.push_back(_editRect);
						_shapeList.push_back(&_rectList.back());
						_shapeBodyMap[&_rectList.back()] = body; 
						break;
					}
				case EditState::CIRCLE:
					{
						auto body = Physics::getInstance()->createBody(Vec2::ZERO, bodyType);
						body->createFixture(&_editCircle);
						_circleList.push_back(_editCircle);
						_shapeList.push_back(&_circleList.back());
						_shapeBodyMap[&_circleList.back()] = body; 
						break;
					}
				case EditState::POLYGON:
					{
						if (!_editPolygon.isValid()) {
							_editPolygon.clearVertex();
							break;
						}
						auto body = Physics::getInstance()->createBody(Vec2::ZERO, bodyType);
						body->createFixture(_editPolygon);
						_polygonList.push_back(_editPolygon);
						_shapeList.push_back(&_polygonList.back());
						_shapeBodyMap[&_polygonList.back()] = body; 
						_editPolygon.clearVertex();
					}
					break;
				}
				_mouseDown = false;
			}
		}
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		for (auto shape = _shapeList.rbegin(); shape != _shapeList.rend(); ++shape) {
			if ((*shape)->collidePoint(cursorWPos)) {
				auto body = _shapeBodyMap[*shape];
				if (body) {
					Physics::getInstance()->destroyBody(body);
				}
				_shapeList.erase((++shape).base());
				break;
			}
		}
	}
}
