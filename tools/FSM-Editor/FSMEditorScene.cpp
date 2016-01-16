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
		if (scene->_sigName != "") {
			fsm->registerSignal(scene->_sigName);
			scene->_sigName = "";
			scene->_sigLabel.clearString();
			scene->updateSignalList();
		}
	} else {
		scene->setSignal(_sig);
	}
}

void SignalButton::update()
{
}

StateButton::StateButton()
{
	setFrontColor(FSMEditor::lighterColor);
	setBackColor(FSMEditor::darkColor);
}

void StateButton::onClick()
{
}

void StateButton::update()
{
}

void FSMEditorScene::init()
{
	Color("#111").setClearColor();

	auto win = Interface::getInstance()->getCurrentWindow();
	auto winS = win->getFrameSize();

	scene = this;
	fsm = &_fsm;

	add(&_fsmLayer);
	add(&_signalListLayer);
	add(&_helpLayer);

	Vec2 startPosition = Interface::getInstance()->getWindowSize();
	startPosition.zoom(Vec2(0.5f, -0.5f));
	auto button = new StateButton();
	button->setLabelString(FSMEditor::font, "+");
	button->feiInit();
	button->setPosition(startPosition + Vec2(-button->getRectSize().x - 1.0f, 1.0f));
	_fsmLayer.add(button);
	updateSignalList();

	_mainCam.setCameraSize(winS);
	setCamera(&_mainCam);

	_rect.setSize(Vec2(100.0f));
	_rectObj.setShape(&_rect);
	_helpLayer.add(&_rectObj);

	_sigLabel.setPosition(Interface::getInstance()->getWindowSize() * -0.5f + Vec2(20.0f));
	add(&_sigLabel);
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
	}
}

void FSMEditorScene::updateSignalList()
{
	auto lv = _signalListLayer.getListVector();
	for (auto i : lv) {
		throwAway(i);
	}
	_signalListLayer.clear();
	auto signalList =_fsm.getSignalVector();
	Vec2 startPosition = Interface::getInstance()->getWindowSize();
	startPosition.zoom(Vec2(-0.5f, 0.5f));
	startPosition.add(Vec2(1.0f, -50.0f - 1.0f));
	for (auto& signal : signalList) {
		auto button = new SignalButton(signal.first);
		button->setLabelString(FSMEditor::font, signal.second);
		button->feiInit();
		button->setPosition(startPosition);
		startPosition.add(Vec2(button->getRectSize().x + 1.0f, 0.0f));
		_signalListLayer.add(button);
	}
	auto button = new SignalButton(-1);
	button->setLabelString(FSMEditor::font, "+");
	button->feiInit();
	button->setPosition(startPosition);
	_signalListLayer.add(button);
}

void FSMEditorScene::updateFSM()
{
}

void FSMEditorScene::setSignal(int sig)
{
	std::printf("%d\n", sig);
}

void FSMEditorScene::charactorCallback(unsigned int codepoint)
{
	char inputChar = (char)codepoint;
	if (inputChar != ' ') {
		_sigName += inputChar;
		_sigLabel.setString(FSMEditor::font, _sigName);
	}
}

void FSMEditorScene::keyCallback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_BACKSPACE && action == GLFW_PRESS) {
		if (!_sigName.empty()) {
			_sigName.pop_back();
			_sigLabel.setString(FSMEditor::font, _sigName);
		}
	}
}
