#include "editor.h"

using namespace fei;

void EditorScene::init()
{
	_saveName = "untitled";
	_editState = EditState::NONE;
	_mouseDown = false;
	_needInitUILayout = false;
	_editCircle.setRadius(64.0f);
	_editPolygon.setSolid(false);

	_editShapeObj.setColorAlpha(0.5f);

	_anime.getClock()->setTimeScale(0.0f);
	_anime.setCurFrameIndex(-1);
	_anime.play();
	_animeObj.setHasAlpha(true);
	_animeObj.setColor(Color::Green);
	_animeObj.setAnime(&_anime);

	Physics::getInstance()->setDoDebugDraw(true);
	Physics::getInstance()->setDebugDrawCamera(&_camera);
	Physics::getInstance()->setRatio(64.0f);

	setCamera(&_camera);

	_texture.setHasAlpha(true);
	_imagePoolLayer.setHasAlpha(true);
	_uiLayer.setHasAlpha(true);
	add(&_texture);
	add(&_imagePoolLayer);
	add(&_animeObj);
	add(&_editShapeObj);
	add(&_uiLayer);

	_uiLayer.setCamera(&_uiCamera);
	_uiLayer.add(&_commandLabel);

	_fontCache.loadFont("res/font/wqy.ttc", 20);
	_commandLabel.setFontCache(&_fontCache);

	auto gravityFunc =
		[](std::vector<std::string> params)
		{
			float a = 0.0f;
			float b = 0.0f;
			if (params.size() == 2) {
				a = static_cast<float>(std::atof(params[0].c_str()));
				b = static_cast<float>(std::atof(params[1].c_str()));
				Physics::getInstance()->setGravity(Vec2(a, b));
			} else {
				return fut::CommandResult(fut::CommandResult::Type::ERROR, "Param size must be 2!");
			}
			return fut::CommandResult::Ok;
		};
	auto newRectFunc =
		[](std::vector<std::string> params)
		{
			float data[4] = {0.0f};
			if (params.size() == 4) {
				for (int i = 0; i < 4; i++) {
					data[i] = static_cast<float>(std::atof(params[i].c_str()));
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
			float data[3] = {0.0f};
			if (params.size() == 3) {
				for (int i = 0; i < 3; i++) {
					data[i] = static_cast<float>(std::atof(params[i].c_str()));
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
	auto vsyncFunc =
		[](std::vector<std::string> params)
		{
			if (params.size() == 1) {
				if (params[0] == "on") {
					Interface::getInstance()->getCurrentWindow()->setVsync(true);
					return fut::CommandResult::Ok;
				} else if (params[0] == "off") {
					Interface::getInstance()->getCurrentWindow()->setVsync(false);
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
			if (!fei::isFileExist(params[0])) {
				return fut::CommandResult(fut::CommandResult::Type::ERROR, "Image file not exist!");
			}
			loadImage(params[0].c_str());
			return fut::CommandResult::Ok;
		};
	auto unloadImageFunc =
		[this](std::vector<std::string> params)
		{
			unloadImage();
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
	auto editSegmentFunc =
		[this](std::vector<std::string> params)
		{
			editSegment();
			return fut::CommandResult::Ok;
		};
	auto editNormalFunc =
		[this](std::vector<std::string> params)
		{
			editNone();
			return fut::CommandResult::Ok;
		};
	auto saveFunc =
		[this](std::vector<std::string> params)
		{
			if (params.size() >= 1) {
				_saveName = params[0];
			}
			save();
			return fut::CommandResult::Ok;
		};
	auto showFpsFunc =
		[](std::vector<std::string> params)
		{
			auto str = fei::strFormat("%f", fei::Time::getInstance()->getFps());
			return fut::CommandResult(fut::CommandResult::Type::OK, str);
		};

	auto interpreter = _commandLabel.getInterpreter();
	interpreter->registerCommand({":set", "gravity"}, gravityFunc);
	interpreter->registerCommand({":set", "debugdraw"}, debugdrawFunc);
	interpreter->registerCommand({":set", "vsync"}, vsyncFunc);
	interpreter->registerCommand({":new", "rect"}, newRectFunc);
	interpreter->registerCommand({":new", "circle"}, newCircleFunc);
	interpreter->registerCommand({":new", "polygon"}, newPolygonFunc);
	interpreter->registerCommand({":load", "img"}, loadImageFunc);
	interpreter->registerCommand({":unload", "img"}, unloadImageFunc);
	interpreter->registerCommand({":edit", "rect"}, editRectFunc);
	interpreter->registerCommand({":edit", "circle"}, editCircleFunc);
	interpreter->registerCommand({":edit", "polygon"}, editPolygonFunc);
	interpreter->registerCommand({":edit", "segment"}, editSegmentFunc);
	interpreter->registerCommand({":edit", "normal"}, editNormalFunc);
	interpreter->registerCommand({":show", "fps"}, showFpsFunc);
	interpreter->registerCommand({":w"}, saveFunc);
	interpreter->registerCommand({":q"}, quitFunc);

	initUILayout();
}

void EditorScene::update()
{
	auto window = Application::getEngine()->getWindow();
	auto deltaV = window->getRHCursorDeltaV() / _camera.getCameraScale();
	if (window->getMouseButton(GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS || window->getKey(GLFW_KEY_SPACE)) {
		_camera.move(-deltaV);
	}

	auto cursorWPos = getCursorWorldPos();
	_editShapeObj.setVisible(_mouseDown && _editState != EditState::NONE);
	switch (_editState) {
	case EditState::NONE:
		{
			if (window->getMouseButton(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
				auto ip = _anime.getFramePool();
				auto num = ip->getImageNum();
				bool collide = false;
				for (int i = 0; i < num; i++) {
					auto image = ip->getImage(i);
					auto rect = getRect(image);
					if (rect.collidePoint(cursorWPos)) {
						Vec2 t1, t2;
						if (!collide || \
							(t1 = ip->getImage(_anime.getCurFrameIndex())->getSize(), t1.x * t1.y) > \
							(t2 = image->getSize(), t2.x * t2.y)) {
							_anime.setCurFrameIndex(i);
						}
						collide = true;
					}
				}
				if (!collide) {
					_anime.setCurFrameIndex(-1);
				}
			}
		}
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
	case EditState::SEGMENT:
		_editSegment = fei::Segment(_mouseDownPos, cursorWPos);
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

void EditorScene::editSegment()
{
	clearEditState();
	_editState = EditState::SEGMENT;
	_editShapeObj.setShape(&_editSegment);
}

void EditorScene::editNone()
{
	clearEditState();
	_editState = EditState::NONE;
	_editShapeObj.setShape(nullptr);
}

void EditorScene::clearCol()
{
	for (auto shapeBody : _shapeBodyMap) {
		Physics::getInstance()->destroyBody(shapeBody.second);
	}
	_shapeBodyMap.clear();
	_shapeIndexMap.clear();
	_rectList.clear();
	_circleList.clear();
	_polygonList.clear();
	_segmentList.clear();
	_shapeList.clear();
}

void EditorScene::addRect(const Rect rect, int index)
{
	auto body = Physics::getInstance()->createBody(Vec2::ZERO, Body::Type::STATIC);
	body->createFixture(&rect);
	_rectList.push_back(rect);
	Shape* shape = &_rectList.back();
	_shapeBodyMap[shape] = body;
	_shapeList.push_back(shape);
	_shapeIndexMap[shape] = index;
}

void EditorScene::addCircle(const Circle circle, int index)
{
	auto body = Physics::getInstance()->createBody(Vec2::ZERO, Body::Type::STATIC);
	body->createFixture(&circle);
	_circleList.push_back(circle);
	Shape* shape = &_circleList.back();
	_shapeBodyMap[shape] = body;
	_shapeList.push_back(shape);
	_shapeIndexMap[shape] = index;
}

void EditorScene::addSegment(const Segment segment, int index)
{
	auto body = Physics::getInstance()->createBody(Vec2::ZERO, Body::Type::STATIC);
	body->createFixture(&segment);
	_segmentList.push_back(segment);
	Shape* shape = &_segmentList.back();
	_shapeBodyMap[shape] = body;
	_shapeList.push_back(shape);
	_shapeIndexMap[shape] = index;
}

void EditorScene::addPolygon(const Polygon polygon, int index)
{
	auto body = Physics::getInstance()->createBody(Vec2::ZERO, Body::Type::STATIC);
	body->createFixture(polygon);
	_polygonList.push_back(polygon);
	Shape* shape = &_polygonList.back();
	_shapeBodyMap[shape] = body;
	_shapeList.push_back(shape);
	_shapeIndexMap[shape] = index;
}

void EditorScene::loadFile(const char* filename)
{
	int len = std::strlen(filename);
	if (len < 3) {
		return;
	}
	auto suffix = std::string(filename + len - 3);
	do {
		if (suffix == "png" || suffix == "jpg") {
			loadImage(filename);
			break;
		}
		if (suffix == "pos") {
			loadPos(filename);
			break;
		}
		if (suffix == "ipi") {
			loadIPI(filename);
			break;
		}
		if (suffix == "sip") {
			loadSIP(filename);
			break;
		}
		if (suffix == "col") {
			loadCol(filename);
			break;
		}
	} while(0);
}

void EditorScene::loadImage(const char* filename)
{
	_texture.load(filename);
	_texture.setVisible(true);
}

void EditorScene::loadSIP(const char* filename)
{
}

void EditorScene::loadIPI(const char* filename)
{
	int len = std::strlen(filename);
	if (len < 4) return;
	if (_texture.isLoaded()) {
		_anime.loadTextureAndIPI(_texture, filename);
		unloadImage();
	} else {
		auto name = std::string(filename, len - 4);
		_anime.loadImageFileAndIPI(name);
	}
	_anime.setCurFrameIndex(0);
	_anime.pause();
	auto ip = _anime.getFramePool();
	auto num = ip->getImageNum();
	_imagePoolLayer.clear();
	for (int i = 0; i < num; i++) {
		auto image = ip->getImage(i);
		image->setHasAlpha(true);
		_imagePoolLayer.add(image);
	}
}

void EditorScene::loadPos(const char* filename)
{
	//TODO: implement loadPos
}

void EditorScene::loadCol(const char* filename)
{
	clearCol();
	int index, n, vn;
	auto f = std::fopen(filename, "r");
	while (std::fscanf(f, "%d", &index) != EOF) {
		std::fscanf(f, "%d", &n);
		for (int i = 0; i < n; i++) {
			float a, b, c, d;
			std::fscanf(f, "%d", &vn);
			switch (vn) {
			case 0:
				{
					std::fscanf(f, "%f%f%f%f", &a, &b, &c, &d);
					addRect(Rect(a, b, c, d), index);
					break;
				}
			case 1:
				{
					std::fscanf(f, "%f%f%f", &a, &b, &c);
					addCircle(Circle(Vec2(a, b), c), index);
					break;
				}
			case 2:
				{
					std::fscanf(f, "%f%f%f%f", &a, &b, &c, &d);
					addSegment(Segment(Vec2(a, b), Vec2(c, d)), index);
					break;
				}
			default:
				{
					Polygon poly;
					for (int i = 0; i < vn; i++) {
						std::fscanf(f, "%f%f", &a, &b);
						poly.pushVertex(Vec2(a, b));
					}
					addPolygon(poly, index);
					break;
				}
			}
		}
	}
	std::fclose(f);
}

void EditorScene::unloadImage()
{
	_texture.setVisible(false);
	_texture.unload();
}

void EditorScene::save()
{
	saveCol();
	savePos();
	saveIPI();
}

void EditorScene::saveCol()
{
	std::string buffer;
	std::vector<std::vector<Shape*>> shapeVec(_anime.getFramePool()->getImageNum());
	for (auto shapeIndex : _shapeIndexMap) {
		shapeVec[shapeIndex.second].push_back(shapeIndex.first);
	}
	int sz = shapeVec.size();
	for (int i = 0; i < sz; i++) {
		if (shapeVec[i].size() == 0) {
			continue;
		}
		buffer += strFormat("%d\n%d\n", i, shapeVec[i].size());
		for (auto shape : shapeVec[i]) {
			buffer += shape->dumpString();
		}
	}
	fei::writeFileBuffer(_saveName + ".col", buffer);
}

void EditorScene::savePos()
{
	std::string buffer;
	auto ip = _anime.getFramePool();
	int num = ip->getImageNum();
	for (int i = 0; i < num; i++) {
		auto image = ip->getImage(i);
		if (image->getPosition() != Vec2::ZERO) {
			buffer += fei::strFormat("%s %.1f %.1f\n", image->getName().c_str(), image->getPositionX(), image->getPositionY());
		}
	}
	fei::writeFileBuffer(_saveName + ".pos", buffer);
}

void EditorScene::saveIPI()
{
	auto ip = _anime.getFramePool();
	ip->dumpIPI(_saveName + ".ipi");
}

const Vec2 EditorScene::getCursorWorldPos()
{
	auto window = Application::getEngine()->getWindow();
	return _camera.screenToWorld(window->getRHCursorPos());
}

void EditorScene::finishShape(fei::Shape* shape)
{
	_shapeList.push_back(shape);
	if (_anime.getCurFrameIndex() >= 0) {
		_shapeIndexMap[shape] = _anime.getCurFrameIndex();
	}
}

void EditorScene::charactorCallback(unsigned int codepoint)
{
	_commandLabel.inputChar(static_cast<char>(codepoint));
}

void EditorScene::keyCallback(int key, int scancode, int action, int mods)
{
	auto window = Application::getEngine()->getWindow();
	switch (key) {
	case GLFW_KEY_ESCAPE:
		if (_commandLabel.isFocus()) {
			_commandLabel.clearString();
			_commandLabel.unfocus();
		}
		break;
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
						if (_editRect.getSize().x < 5.0f || _editRect.getSize().y < 5.0f) {
							break;
						}
						auto body = Physics::getInstance()->createBody(Vec2::ZERO, bodyType);
						body->createFixture(&_editRect);
						_rectList.push_back(_editRect);
						_shapeBodyMap[&_rectList.back()] = body; 
						finishShape(&_rectList.back());
						break;
					}
				case EditState::CIRCLE:
					{
						if (_editCircle.getRadius() < 5.0f) {
							break;
						}
						auto body = Physics::getInstance()->createBody(Vec2::ZERO, bodyType);
						body->createFixture(&_editCircle);
						_circleList.push_back(_editCircle);
						_shapeBodyMap[&_circleList.back()] = body; 
						finishShape(&_circleList.back());
						break;
					}
				case EditState::POLYGON:
					{
						if (!_editPolygon.isValid() || _editPolygon.getArea() < 25.0f) {
							_editPolygon.clearVertex();
							break;
						}
						auto body = Physics::getInstance()->createBody(Vec2::ZERO, bodyType);
						body->createFixture(_editPolygon);
						_polygonList.push_back(_editPolygon);
						_shapeBodyMap[&_polygonList.back()] = body; 
						_editPolygon.clearVertex();
						finishShape(&_polygonList.back());
						break;
					}
				case EditState::SEGMENT:
					{
						if (_editSegment.getLength() < 5.0f) {
							break;
						}
						auto body = Physics::getInstance()->createBody(Vec2::ZERO, bodyType);
						body->createFixture(&_editSegment);
						_segmentList.push_back(_editSegment);
						_shapeBodyMap[&_segmentList.back()] = body; 
						finishShape(&_segmentList.back());
						break;
					}
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
					_shapeBodyMap[*shape] = nullptr;
				}
				Shape* ptr = *shape;
				_shapeList.erase((++shape).base());
				_shapeIndexMap.erase(ptr);
				break;
			}
		}
	}
}

void EditorScene::dropCallback(int count, const char** paths)
{
	for (int i = 0; i < count; i++) {
		loadFile(paths[i]);
	}
}

void EditorScene::framebufferSizeCallback(int width, int height)
{
	_needInitUILayout = true;
}
