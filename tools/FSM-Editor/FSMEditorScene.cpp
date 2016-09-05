#include "FSMEditorScene.h"

#include "ButtonArrow.h"
#include "FSMEditor.h"

using namespace fei;

StateButton* StateButton::DownStateButton;
static FSMEditorScene* scene;
static fut::FSM* fsm;

ButtonBase::ButtonBase()
{
	setFrontColor(FSMEditor::brightColor);
	setBackColor(FSMEditor::darkColor);
}

void ButtonBase::init()
{
	setRectSize(Vec2(getLabel()->getLength() + 30.0f, 50.0f));
	getLabel()->setCenterAligned(true);
	getLabel()->setPosition(getRectSize() / 2.0f);
	getLabel()->move(Vec2(0.0f, -14.0f));
}

void ButtonBase::onEnter()
{
	if (isButtonDown()) {
		setBackColor(FSMEditor::lightColor);
	} else {
		setBackColor(FSMEditor::midColor);
	}
}

void ButtonBase::onLeave()
{
	setBackColor(FSMEditor::darkColor);
}

void ButtonBase::onMouseDown()
{
	setBackColor(FSMEditor::lightColor);
}

void ButtonBase::onMouseUp()
{
	setBackColor(FSMEditor::midColor);
}

SignalButton::SignalButton(int sig)
{
	_sig = sig;
}

void SignalButton::onClick()
{
	if (_sig == -1) {
		if (!scene->_tmpName.empty()) {
			fsm->registerSignal(unicodeToUtf8(scene->_tmpName));
			scene->_tmpName.clear();
			scene->_tmpLabel.clearString();
			scene->updateSignalList();
		}
	} else {
		scene->setSignal(_sig);
	}
}

StateButton::StateButton(int state)
{
	_state = state;
	setFrontColor(FSMEditor::lighterColor);
	setBackColor(FSMEditor::darkColor);
}

void StateButton::onEnter()
{
	if (isButtonDown()) {
		setBackColor(FSMEditor::lightColor);
	} else {
		setBackColor(FSMEditor::midColor);
	}
	scene->_collideStateButton = this;
}

void StateButton::onLeave()
{
	if (scene->_collideStateButton == this) {
		scene->_collideStateButton = nullptr;
	}
	setBackColor(FSMEditor::darkColor);
}

void StateButton::onClick()
{
	if (_state == -1) {
		if (!scene->_tmpName.empty()) {
			fsm->registerState(unicodeToUtf8(scene->_tmpName));
			scene->_tmpName.clear();
			scene->_tmpLabel.clearString();
			scene->updateFSM();
		}
	} else {
		scene->setState(_state);
	}
}

void StateButton::onButtonDown()
{
	if (_state != -1) {
		DownStateButton = this;
	}
}

void StateButton::onButtonUp()
{
	DownStateButton = nullptr;
}

void StateButton::beforeUpdate()
{
	if (DownStateButton == this) {
		scene->mouseDrag(&scene->_fsmCam, this);
		scene->_statePositionMap[_state] = this->getPosition();
	}
}

int StateButton::getState()
{
	return _state;
}

void FSMEditorScene::init()
{
	scene = this;
	fsm = &_fsm;
	_needUIRefresh = false;

	_currentSignal = -1;
	_drawLine = false;
	_collideStateButton = nullptr;
	_startStateButton = nullptr;
	_endStateButton = nullptr;

	add(&_lineLayer);
	add(&_editingLineLayer);
	add(&_stateListLayer);
	add(&_signalListLayer);
	add(&_helpLayer);
	add(&_fixLayer);

	_addStateButton = new StateButton(-1);
	_addSignalButton = new SignalButton(-1);
	_addSignalButton->setLabelString(FSMEditor::font, "+");
	_addStateButton->setLabelString(FSMEditor::font, "+");
	_addSignalButton->feiInit();
	_addStateButton->feiInit();

	_fixLayer.add(_addSignalButton);
	_fixLayer.add(_addStateButton);
	setCamera(&_mainCam);

	_rect.setSize(Vec2(100.0f));
	_rectObj.setShape(&_rect);
	_helpLayer.add(&_rectObj);

	_editingLineObj.setShape(&_editingLine);
	_editingLineObj.setVisible(false);
	_editingLineLayer.add(&_editingLineObj);

	_editingLineLayer.setCamera(&_fsmCam);
	_stateListLayer.setCamera(&_fsmCam);
	_lineLayer.setCamera(&_fsmCam);

	add(&_tmpLabel);

	refreshWindow();
}

void FSMEditorScene::destroy()
{
	throwAway(_addSignalButton);
	throwAway(_addStateButton);
}

void FSMEditorScene::beforeUpdate()
{
	auto win = Interface::getInstance()->getCurrentWindow();
	if (win) {
		_cursorDeltaV = win->getRHCursorDeltaV();
		if (win->getKey(GLFW_KEY_H)) {
			_helpLayer.setVisible(true);
		} else {
			_helpLayer.setVisible(false);
		}
		if (win->getMouseButton(GLFW_MOUSE_BUTTON_MIDDLE) || win->getKey(GLFW_KEY_SPACE)) {
			mouseDrag(&_fsmCam, &_fsmCam, -1);
		}
		if (_startStateButton && _drawLine) {
			//TODO: add line shape
			_editingLine.a = _startStateButton->getCenter();
			_editingLine.b = _fsmCam.screenToWorld(win->getRHCursorPos());
			_editingLineObj.setVisible(true);
		} else {
			_editingLineObj.setVisible(false);
		}
	}
	if (_needUIRefresh) {
		refreshWindow();
		_needUIRefresh = false;
	}
}

void FSMEditorScene::updateSignalList()
{
	//clear signalListLayer
	_signalListLayer.throwAwayAll();
	_signalListLayer.clear();
	_signalListLayer.garbageRecycle();

	auto signalList =_fsm.getSignalVector();
	Vec2 winSize = Interface::getInstance()->getCurrentWindow()->getFrameSize();
	Vec2 startPosition = winSize.zoomed(Vec2(-0.5f, 0.5f));
	startPosition.add(Vec2(1.0f, -50.0f - 1.0f));
	for (auto& signal : signalList) {
		auto button = new SignalButton(signal.first);
		button->setLabelString(FSMEditor::font, signal.second);
		button->feiInit();
		if (startPosition.x + button->getRectSize().x > winSize.x / 2.0f - 100.0f) {
			startPosition.x = winSize.x / -2.0f + 1.0f;
			startPosition.y -= 51.0f;
		}
		button->setPosition(startPosition);
		startPosition.add(Vec2(button->getRectSize().x + 1.0f, 0.0f));
		_signalListLayer.add(button);
	}
}

void FSMEditorScene::updateFSM()
{
	//clear stateListLayer
	_stateListLayer.throwAwayAll();
	_stateListLayer.clear();
	_stateListLayer.garbageRecycle();

	auto stateList = _fsm.getStateVector();
	for (auto& state : stateList) {
		auto button = new StateButton(state.first);
		button->setLabelString(FSMEditor::font, state.second);
		button->feiInit();
		button->setPosition(_statePositionMap[state.first]);
		_stateListLayer.add(button);
	}
	//TODO:
	//  add save button saving fsm to text file
	updateFSMConnection();
}

void FSMEditorScene::updateFSMConnection()
{
	//TODO:
	//  add all relations to fsm
	_lineLayer.throwAwayAll();
	_lineLayer.clear();
	_lineLayer.garbageRecycle();

	auto stateV = _stateListLayer.getListVector();
	int len = stateV.size();
	for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			auto ba = dynamic_cast<StateButton*>(stateV[i]);
			auto bb = dynamic_cast<StateButton*>(stateV[j]);
			auto bai = ba->getState();
			auto bbi = bb->getState();
			auto abs = _fsm.getLinkSignalVector(bai, bbi);
			auto bbs = _fsm.getLinkSignalVector(bbi, bai);
			if (!abs.empty()) {
				std::string labelStr = _fsm.getSignalName(abs[0]);
				int len = abs.size();
				for (int i = 1; i < len; i++) {
					labelStr += ", " + _fsm.getSignalName(abs[i]);
				}
				_lineLayer.add(new ButtonArrow(ba, bb, labelStr));
			}
			if (!bbs.empty()) {
				std::string labelStr = _fsm.getSignalName(bbs[0]);
				int len = bbs.size();
				for (int i = 1; i < len; i++) {
					labelStr += ", " + _fsm.getSignalName(bbs[i]);
				}
				_lineLayer.add(new ButtonArrow(bb, ba, labelStr));
			}
		}
	}
}

void FSMEditorScene::setSignal(int sig)
{
	std::printf("Signal: %d\n", sig);
	_currentSignal = sig;
	//TODO:
	//  highlight the select SignalButton
}

void FSMEditorScene::setState(int state)
{
	std::printf("State: %d\n", state);
}

void FSMEditorScene::establishLink(StateButton* a, StateButton* b)
{
	if (_currentSignal != -1) {
		int stateA = a->getState();
		int stateB = b->getState();
		_fsm.registerLink(stateA, stateB, _currentSignal);
		std::printf("Link: %d->%d (%d)\n", stateA, stateB, _currentSignal);
		updateFSMConnection();
	}
}

void FSMEditorScene::characterCallback(unsigned int codepoint)
{
	if (_tmpName.size() < 25 && codepoint != (unsigned int)' ') {
		_tmpName.push_back(codepoint);
		_tmpLabel.setString(FSMEditor::font, _tmpName);
	}
}

void FSMEditorScene::keyCallback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_BACKSPACE && action != GLFW_RELEASE) {
		if (!_tmpName.empty()) {
			_tmpName.pop_back();
			_tmpLabel.setString(FSMEditor::font, _tmpName);
		}
	}
	if (key == GLFW_KEY_F11 && action == GLFW_PRESS) {
		auto window = Interface::getInstance()->getCurrentWindow();
		window->setFullscreen(!window->isFullscreen());
	}
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		if (!processCmd(unicodeToUtf8(_tmpName))) {
			if (mods & GLFW_MOD_CONTROL) {
				_addSignalButton->click();
			} else {
				_addStateButton->click();
			}
		}
	}
}

void FSMEditorScene::scrollCallback(double xoffset, double yoffset)
{
	if (yoffset > 0.0) {
		_fsmCam.zoomCameraScale(1.1f);
	}
	else if (yoffset < 0.0) {
		_fsmCam.zoomCameraScale(0.90909f);
	}
}

void FSMEditorScene::mouseButtonCallback(int button, int action, int mods)
{
	if (GLFW_MOUSE_BUTTON_RIGHT == button) {
		if (action == GLFW_PRESS) {
			if (_collideStateButton && _collideStateButton->getState() != -1) {
				_startStateButton = _collideStateButton;
				_drawLine = true;
			}
		} else if (action == GLFW_RELEASE) {
			if (_collideStateButton) {
				if (_drawLine) {
					_endStateButton = _collideStateButton;
					if (_startStateButton && _endStateButton->getState() != -1) {
						establishLink(_startStateButton, _endStateButton);
					}
				}
			}
			_drawLine = false;
		}
	}
}

void FSMEditorScene::framebufferSizeCallback(int width, int height)
{
	_needUIRefresh = true;
}

void FSMEditorScene::mouseDrag(Camera* cam, NodeBase* node, float k)
{
	Vec2 deltaV = _cursorDeltaV / cam->getCameraScale();
	node->move(deltaV * k);
}

bool FSMEditorScene::processCmd(const std::string& cmd)
{
	if (cmd.length() > 1 && cmd.front() == ':') {
		std::string filename = cmd.substr(2);
		_tmpLabel.clearString();
		switch (cmd[1]) {
		case 'w':
			if (filename == fei::EmptyStr) {
				filename = _openFile;
				if (filename == fei::EmptyStr) break;
			}
			_fsm.dump(filename);
			dumpPosition(filename + ".pos");
			dumpSignal(filename + ".sig");
			dumpState(filename + ".sta");
			break;
		case 'e':
			if (!_fsm.load(filename)) {
				break;
			}
			_openFile = filename;
			loadPosition(filename + ".pos");
			updateSignalList();
			updateFSM();
			break;
		}
		_tmpName.clear();
		return true;
	}
	return false;
}

void FSMEditorScene::dumpPosition(const std::string& filename)
{
	auto file = std::fopen(filename.c_str(), "wb");
	for (const auto& statePosition : _statePositionMap) {
		auto name = _fsm.getStateName(statePosition.first);
		auto pos = statePosition.second;
		std::fprintf(file, "%s %f %f\n", name.c_str(), pos.x, pos.y);
	}
	std::fclose(file);
}

void FSMEditorScene::dumpSignal(const std::string& filename)
{
	auto vec = _fsm.getSignalVector();
	auto file = std::fopen(filename.c_str(), "wb");
	for (const auto& signal : vec) {
		std::fprintf(file, "%s\n", signal.second.c_str());
	}
	std::fclose(file);
}

void FSMEditorScene::dumpState(const std::string& filename)
{
	auto vec = _fsm.getStateVector();
	auto file = std::fopen(filename.c_str(), "wb");
	for (const auto& state : vec) {
		std::fprintf(file, "%s\n", state.second.c_str());
	}
	std::fclose(file);
}

void FSMEditorScene::loadPosition(const std::string& filename)
{
	char a[50];
	float x, y;
	auto file = std::fopen(filename.c_str(), "rb");
	if (!file) {
		return;
	}
	_statePositionMap.clear();
	while (std::fscanf(file, "%s %f %f", a, &x, &y) != EOF) {
		int id = _fsm.getStateId(a);
		_statePositionMap[id] = Vec2(x, y);
	}
	std::fclose(file);
}

void FSMEditorScene::refreshWindow()
{
	Color("#555").setClearColor();
	auto win = Interface::getInstance()->getCurrentWindow();
	auto winS = win->getFrameSize();
	_mainCam.setCameraSize(winS);
	_fsmCam.setCameraSize(winS);

	Vec2 startPosition = winS;
	startPosition.zoom(Vec2(0.5f, 0.5f));
	startPosition -= _addStateButton->getRectSize() + Vec2(1.0f);
	_addSignalButton->setPosition(startPosition);

	startPosition = winS;
	startPosition.zoom(Vec2(0.5f, -0.5f));
	_addStateButton->setPosition(startPosition + Vec2(-_addStateButton->getRectSize().x - 1.0f, 1.0f));

	_tmpLabel.setPosition(winS * -0.5f + Vec2(20.0f));

	updateSignalList();
	updateFSM();
}
