#include "math/Rect.h"

using fei::Rect;

Rect::Rect()
{
	shapeType = fei::Shape::Type::RECT;
	size = fei::Vec2(1.0f);
}

Rect::Rect(const fei::Vec2& sz)
{
	shapeType = fei::Shape::Type::RECT;
	size = sz;
}

Rect::Rect(float x, float y, float w, float h)
{
	shapeType = fei::Shape::Type::RECT;
	pos = fei::Vec2(x, y);
	size = fei::Vec2(w, h);
	normalize();
}

Rect::Rect(const fei::Vec2& ps, const fei::Vec2& sz)
{
	shapeType = fei::Shape::Type::RECT;
	pos = ps;
	size = sz;
	normalize();
}

const fei::Vec2 Rect::getCenter() const
{
	return pos + size / 2.0f;
}

void Rect::setCenter(const fei::Vec2& p)
{
	pos = p - size / 2.0f;
}

const fei::Vec2 Rect::getSize() const
{
	return size;
}

void Rect::setSize(const fei::Vec2& sz)
{
	size = sz;
}

float Rect::getLeft() const
{
	return pos.x;
}

float Rect::getRight() const
{
	return pos.x + size.x;
}

float Rect::getTop() const
{
	return pos.y + size.y;
}

float Rect::getBottom() const
{
	return pos.y;
}

fei::Segment Rect::getLeftSegment() const
{
	fei::Segment ret;
	ret.a = Vec2(getLeft(), getBottom());
	ret.b = Vec2(getLeft(), getTop());
	return ret;
}

fei::Segment Rect::getRightSegment() const
{
	fei::Segment ret;
	ret.a = Vec2(getRight(), getBottom());
	ret.b = Vec2(getRight(), getTop());
	return ret;
}

fei::Segment Rect::getTopSegment() const
{
	fei::Segment ret;
	ret.a = Vec2(getLeft(), getTop());
	ret.b = Vec2(getRight(), getTop());
	return ret;
}

fei::Segment Rect::getBottomSegment() const
{
	fei::Segment ret;
	ret.a = Vec2(getLeft(), getBottom());
	ret.b = Vec2(getRight(), getBottom());
	return ret;
}

void Rect::zoom(float scale)
{
	pos.zoom(scale);
	size.zoom(scale);
}

void Rect::zoom(const fei::Vec2& v)
{
	pos.zoom(v);
	size.zoom(v);
}

const Rect Rect::zoomed(float scale) const
{
	Rect result(*this);
	result.zoom(scale);
	return result;
}

const Rect Rect::zoomed(const fei::Vec2& v) const
{
	Rect result(*this);
	result.zoom(v);
	return result;
}

void Rect::normalize()
{
	if (size.x < 0) {
		pos.x += size.x;
		size.x *= -1.0f;
	}
	if (size.y < 0) {
		pos.y += size.y;
		size.y *= -1.0f;
	}
}

bool Rect::collide(const fei::Shape* other) const
{
	bool result = false;
	switch(other->getType()) {
	case fei::Shape::Type::RECT:
		{
			auto rct = static_cast<const fei::Rect*>(other);
			result = collideRect(*rct);
		}
		break;
	//TODO: implement cases
	//case fei::Shape::Type::CIRCLE:
	//case fei::Shape::Type::POLYGON:
	//case fei::Shape::Type::SEGMENT:
	}
	return result;
}

bool Rect::collidePoint(const fei::Vec2& pt) const
{
	fei::Vec2 rt = pos + size;
	return ((pos.x - pt.x) * (rt.x - pt.x) <= 0) && ((pos.y - pt.y) * (rt.y - pt.y) <= 0);
}

bool Rect::collideSegment(fei::Vec2& pt, const fei::Segment& seg) const
{
	fei::Vec2 ans = seg.b, tmp;
	bool isCollide = false;
	std::vector<fei::Segment> segArray{getLeftSegment(), \
					getRightSegment(), \
					getTopSegment(), \
					getBottomSegment(), \
					};
	for (const auto& eachSeg : segArray) {
		if (seg.collideSegment(tmp, eachSeg)) {
			isCollide = true;
			if ((tmp - seg.a).getLengthSq() < (ans - seg.a).getLengthSq()) {
				ans = tmp;
			}
		}
	}
	if (isCollide) {
		pt = ans;
	}
	return isCollide;
}

bool Rect::collideRect(const Rect& rct) const
{
	auto dv = getCenter() - rct.getCenter();
	float wSum = getSize().x + rct.getSize().x;
	float hSum = getSize().y + rct.getSize().y;
	float xD = std::abs(dv.x * 2.0f);
	float yD = std::abs(dv.y * 2.0f);
	return (xD <= wSum) && (yD <= hSum);
}

void Rect::getStripCoord(float* coord) const
{
	auto rTop = pos + size;
	coord[0] = pos.x;
	coord[1] = rTop.y;
	coord[2] = pos.x;
	coord[3] = pos.y;
	coord[4] = rTop.x;
	coord[5] = rTop.y;
	coord[6] = rTop.x;
	coord[7] = pos.y;
}

const float* Rect::getDataPtr() const
{
	static float data[8] = {0.0f};
	data[2] = size.x;
	data[4] = size.x;
	data[5] = size.y;
	data[7] = size.y;
	return data;
}

int Rect::getDataSize() const
{
	return 4;
}
