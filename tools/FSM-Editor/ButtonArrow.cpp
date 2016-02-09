#include "ButtonArrow.h"

#include "render/Render.h"

ButtonArrow::ButtonArrow(fei::Button* ba, fei::Button* bb)
: _ba(ba),
  _bb(bb)
{
}

void ButtonArrow::drawIt()
{
	auto pa = _ba->getCenter();
	auto pb = _bb->getCenter();
	auto segVec = (pb - pa).normalized();
	auto segVVec = segVec.getVerticalVec2();
	seg.a = pa - segVVec * 5.0f;
	seg.b = pb - segVVec * 5.0f;
	fei::Vec2 collideP;
	if (_bb->getRect().collideSegment(collideP, seg)) {
		auto arrowP = collideP - segVec * 21.0f - segVVec * 7.0f;
		fei::Render::drawLine(collideP, arrowP);
	}
	fei::Render::drawShape(&seg);
}
