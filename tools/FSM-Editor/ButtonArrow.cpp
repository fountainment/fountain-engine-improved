#include "ButtonArrow.h"

#include "FSMEditor.h"
#include "render/Render.h"

ButtonArrow::ButtonArrow(fei::Button* ba, fei::Button* bb, const std::string& labelStr)
: _ba(ba),
  _bb(bb)
{
	_label.setString(FSMEditor::font20, labelStr);
}

void ButtonArrow::drawIt()
{
	auto pa = _ba->getCenter();
	auto pb = _bb->getCenter();
	auto segVec = (pb - pa).normalized();
	auto segVVec = segVec.getVerticalVec2();
	_seg.a = pa - segVVec * 5.0f;
	_seg.b = pb - segVVec * 5.0f;
	fei::Vec2 collideP;
	//TODO: draw differently when _ba == _bb
	if (_bb->getRect().collideSegment(collideP, _seg)) {
		fei::Vec2 bac;
		auto bbc = collideP;
		auto arrowP = collideP - segVec * 21.0f - segVVec * 7.0f;
		fei::Render::drawLine(collideP, arrowP);
		if (_ba->getRect().collideSegment(collideP, _seg)) {
			bac = collideP;
			auto center = (bac + bbc) * 0.5f;
			center -= segVVec * 5.0f;
			if (segVVec.y > 0.0f) {
				center += fei::Vec2(0.0f, -15.0f);
			}
			_label.setCenter(center);
		}
	}
	fei::Render::drawShape(&_seg);
	_label.draw();
}
