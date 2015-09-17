#include "Segment.h"

using fei::Segment;

Segment::Segment()
: a(fei::Vec2::ZERO),
  b(fei::Vec2::ZERO)
{
}

Segment::Segment(fei::Vec2 aa, fei::Vec2 bb)
: a(aa),
  b(bb)
{
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

bool Segment::collideRay(Vec2& pt, const Vec2& src, const Vec2& drct) const
{
	auto intersection = fei::collideLine(a, b, src, src + drct);
	if (rectCollidePoint(intersection) && drct.dot(intersection - src) > 0.0f) {
		pt = intersection;
		return true;
	} else {
	std::printf("x%f %f\n", intersection.x, intersection.y);
		return false;
	}
}

