#include "Button.h"
#include "render/Render.h"
#include "interface/Interface.h"

using fei::Button;

Button::Button()
: _drawCamera(nullptr),
  _backRect(Rect(fei::Vec2::ZERO, fei::Vec2(10.0f))),
  _backColor(fei::Color::White),
  _collide(false)
{
	_label.setHasAlpha(true);
	_label.setColor(fei::Color::Black);
}

void Button::drawIt()
{
	_drawCamera = Render::getInstance()->getCurrentCamera();

	Render::useColor(&_backColor);
	fei::Render::drawShape(&_backRect);

	_label.draw();
}

void Button::feiUpdate()
{
	if (_drawCamera) {
		fei::Vec2 cPos = fei::Interface::getInstance()->getRHCursorPos();
		cPos = _drawCamera->screenToWorld(cPos);
		bool collide = _backRect.collidePoint(cPos - getPosition());
		if (collide != _collide) {
			_collide = collide;
			if (_collide) {
				onEnter();
			} else {
				onLeave();
			}
		}
		if (_collide) {
			onCollide();
		}
	}
	update();
}

void Button::setLabel(const fei::Label& label)
{
	_label = label;
}

void Button::setRectSize(const fei::Vec2& rectSize)
{
	_backRect.setSize(rectSize);
}

void Button::setBackColor(const fei::Color& color)
{
	_backColor = color;
}

void Button::setLabelColor(const fei::Color& color)
{
	_label.setColor(color);
}

void Button::setLabelString(fei::FontCache& fontCache, const std::string& str)
{
	_label.setString(fontCache, str);
}

void Button::onEnter()
{
}

void Button::onLeave()
{
}

void Button::onCollide()
{
}

void Button::onClick()
{
}
