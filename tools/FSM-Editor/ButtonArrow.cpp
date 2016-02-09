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
	seg.a = pa;
	seg.b = pb;
	fei::Vec2 collideP;
	if (_bb->getRect().collideSegment(collideP, seg)) {
		//TODO:
		//fei::Render::drawLine(collideP, fei::Vec2::ZERO);
	}
	fei::Render::drawShape(&seg);
}
