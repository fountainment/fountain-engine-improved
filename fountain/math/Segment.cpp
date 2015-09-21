#include "Segment.h"

using fei::Segment;

Segment::Segment()
: a(fei::Vec2::ZERO),
  b(fei::Vec2::ZERO)
{
	shapeType = fei::Shape::Type::SEGMENT;
}

Segment::Segment(fei::Vec2 aa, fei::Vec2 bb)
: a(aa),
  b(bb)
{
	shapeType = fei::Shape::Type::SEGMENT;
}

const float* Segment::getDataPtr() const
{
	return &a.x;
}

int Segment::getDataSize() const
{
	return 2;
}

void Segment::swapAB()
{
	auto tmp = a;
	a = b;
	b = tmp;
}

bool Segment::collideSegment(fei::Vec2& pt, const Segment& seg) const
{
	auto intersection = fei::collideLine(a, b, seg.a, seg.b);
	if (rectCollidePoint(intersection) && seg.rectCollidePoint(intersection)) {
		pt = intersection;
		return true;
	} else {
		return false;
	}
}

bool Segment::collideRay(fei::Vec2& pt, const fei::Vec2& src, const fei::Vec2& drct) const
{
	auto intersection = fei::collideLine(a, b, src, src + drct);
	if (rectCollidePoint(intersection) && drct.dot(intersection - src) > 0.0f) {
		pt = intersection;
		return true;
	} else {
		return false;
	}
}

