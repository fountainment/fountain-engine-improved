#include "FSMEditorScene.h"

#include "FSMEditor.h"

using namespace fei;

SignalButton::SignalButton(int sig)
{
	_sig = sig;
}

void SignalButton::init()
{
	setRectSize(Vec2(50.0f));
	getLabel()->setString(FSMEditor::font, "+");
	getLabel()->setCenterAligned(true);
	getLabel()->setPosition(getRectSize() / 2.0f);
	getLabel()->move(Vec2(0.0f, -16.0f));

	setFrontColor(FSMEditor::brightColor);
	setBackColor(FSMEditor::darkColor);
}

void SignalButton::onEnter()
{
	setBackColor(FSMEditor::midColor);
}

void SignalButton::onLeave()
{
	setBackColor(FSMEditor::darkColor);
}

void SignalButton::onClick()
{
}

void SignalButton::onMouseDown()
{
	setBackColor(FSMEditor::lightColor);
}

void SignalButton::onMouseUp()
{
	setBackColor(FSMEditor::midColor);
}

void SignalButton::update()
{
}

void FSMEditorScene::init()
{
	auto win = Interface::getInstance()->getCurrentWindow();
	auto winS = win->getFrameSize();

	add(&_fsmLayer);
	add(&_signalListLayer);
	add(&_helpLayer);

	_mainCam.setCameraSize(winS);
	setCamera(&_mainCam);

	_signalListLayer.add(new SignalButton(1));

	_rect.setSize(Vec2(100.0f));
	_rectObj.setShape(&_rect);
	_helpLayer.add(&_rectObj);
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
