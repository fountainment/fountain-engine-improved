#include "math/Segment.h"

#include "math/Rect.h"

using fei::Segment;

Segment::Segment()
: a(fei::Vec2::ZERO),
  b(fei::Vec2::ZERO)
{
	setType(fei::Shape::Type::SEGMENT);
}

Segment::Segment(fei::Vec2 aa, fei::Vec2 bb)
: a(aa),
  b(bb)
{
	setType(fei::Shape::Type::SEGMENT);
}

const float* Segment::getDataPtr() const
{
	return &a.x;
}

int Segment::getDataSize() const
{
	return 2;
}

const fei::Rect Segment::getRect() const
{
	return fei::Rect(a, b - a);
}

void Segment::setAB(const fei::Vec2& aa, const fei::Vec2& bb)
{
	a = aa;
	b = bb;
}

void Segment::swapAB()
{
	auto tmp = a;
	a = b;
	b = tmp;
}

bool Segment::collide(const fei::Shape* shape) const
{
	bool result = false;
	Vec2 tmp;
	switch (shape->getType()) {
	//TODO: implement cases
	case fei::Shape::Type::CIRCLE:
	case fei::Shape::Type::POLYGON:
	case fei::Shape::Type::RECT:
		std::printf("Segment::collide Not Implemented!\n");
		break;
	case fei::Shape::Type::SEGMENT:
		result = collideSegment(tmp, *(static_cast<const Segment*>(shape)));
		break;
	}
	return result;
}

bool Segment::collidePoint(const fei::Vec2& p) const
{
	return std::abs((a - p).normalized().dot((b - p).normalized()) + 1.0f) < fei::epsf;
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

int Segment::cmpRenderY(const Segment& seg) const
{
	fei::Vec2 tmp;
	bool yIntersects = getYInterval().intervalIntersects(tmp, seg.getYInterval());
	bool xIntersects = getXInterval().intervalIntersects(tmp, seg.getXInterval());
	if (xIntersects && yIntersects) {
		float x = (tmp.x + tmp.y) * 0.5f;
		return fei::cmp(getY(x), seg.getY(x));
	} else {
		if (xIntersects) {
			return fei::cmp(a.y, seg.a.y);
		} else {
			return 0;
		}
	}
}
