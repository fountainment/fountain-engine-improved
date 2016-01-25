#include "FSMEditorScene.h"

#include "FSMEditor.h"

using namespace fei;

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
	setBackColor(FSMEditor::midColor);
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

void SignalButton::update()
{
}

StateButton::StateButton(int state)
{
	_state = state;
	setFrontColor(FSMEditor::lighterColor);
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

void StateButton::update()
{
}

void FSMEditorScene::init()
{

	scene = this;
	fsm = &_fsm;

	add(&_fsmLayer);
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
	_fsmLayer.setCamera(&_fsmCam);

	_rect.setSize(Vec2(100.0f));
	_rectObj.setShape(&_rect);
	_helpLayer.add(&_rectObj);

	add(&_tmpLabel);

	refreshWindow();
}

void FSMEditorScene::destroy()
{
	throwAway(_addSignalButton);
	throwAway(_addStateButton);
}

void FSMEditorScene::update()
{
	auto win = Interface::getInstance()->getCurrentWindow();
	if (win) {
		if (win->getKey(GLFW_KEY_H)) {
			_helpLayer.setVisible(true);
		} else {
			_helpLayer.setVisible(false);
		}
		mouseDrag(&_fsmCam, &_fsmCam);
	}
}

void FSMEditorScene::updateSignalList()
{
	//clear signalListLayer
	_signalListLayer.throwAwayAll();
	_signalListLayer.clear();
	_signalListLayer.garbageRecycle();

	auto signalList =_fsm.getSignalVector();
	Vec2 winSize = Interface::getInstance()->getWindowSize();
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
	//clear fsmLayer
	_fsmLayer.throwAwayAll();
	_fsmLayer.clear();
	_fsmLayer.garbageRecycle();

	auto stateList = _fsm.getStateVector();
	for (auto& state : stateList) {
		auto button = new StateButton(state.first);
		button->setLabelString(FSMEditor::font, state.second);
		button->feiInit();
		button->setPosition(_statePositionMap[state.first]);
		_fsmLayer.add(button);
	}
	//TODO:
	//  memorize StateButton's position
	//  add all relations to fsm
	//  add save button saving fsm to text file
}

void FSMEditorScene::setSignal(int sig)
{
	std::printf("Signal: %d\n", sig);
	//TODO:
	//  memorize the select signal
	//  highlight the select SignalButton
}

void FSMEditorScene::setState(int state)
{
	std::printf("State: %d\n", state);
	//TODO:
	//  implement UI component draging logic
}

void FSMEditorScene::charactorCallback(unsigned int codepoint)
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
	if (key == GLFW_KEY_F11 && action == GLFW_RELEASE) {
		auto window = Interface::getInstance()->getCurrentWindow();
		window->setFullscreen(!window->isFullscreen());
		refreshWindow();
	}
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		if (mods & GLFW_MOD_CONTROL) {
			_addSignalButton->click();
		} else {
			_addStateButton->click();
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

void FSMEditorScene::mouseDrag(Camera* cam, NodeBase* node)
{
	auto window = Interface::getInstance()->getCurrentWindow();
	static Vec2 oldPos = window->getRHCursorPos();
	Vec2 deltaV = (window->getRHCursorPos() - oldPos) / -cam->getCameraScale();
	oldPos = window->getRHCursorPos();
	if (window->getMouseButton(GLFW_MOUSE_BUTTON_MIDDLE)) {
		node->move(deltaV);
	}
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
