#include "Button.h"
#include "render/Render.h"
#include "interface/Interface.h"

using fei::Button;

Button::Button()
: _drawCamera(nullptr),
  _backRect(Rect(fei::Vec2::ZERO, fei::Vec2(10.0f)))
{
}

void Button::drawIt()
{
	_drawCamera = Render::getInstance()->getCurrentCamera();
	fei::Render::drawShape(&_backRect);
}

void Button::update()
{
	bool collide = false;
	if (_drawCamera) {
		fei::Vec2 cPos = fei::Interface::getInstance()->getRHCursorPos();
		cPos = _drawCamera->screenToWorld(cPos);
		collide = _backRect.collidePoint(cPos);
	}

}

void Button::click()
{
}