#include "math/Rect.h"

using fei::Rect;

Rect::Rect()
{
	setType(fei::Shape::Type::RECT);
	setSize(fei::Vec2(1.0f));
}

Rect::Rect(const fei::Vec2& sz)
{
	setType(fei::Shape::Type::RECT);
	setSize(sz);
}

Rect::Rect(float x, float y, float w, float h)
{
	setType(fei::Shape::Type::RECT);
	setPosition(fei::Vec2(x, y));
	setSize(fei::Vec2(w, h));
	normalize();
}

Rect::Rect(const fei::Vec2& ps, const fei::Vec2& sz)
{
	setType(fei::Shape::Type::RECT);
	setPosition(ps);
	setSize(sz);
	normalize();
}

const fei::Vec2 Rect::getCenter() const
{
	return getPosition() + getSize() / 2.0f;
}

void Rect::setCenter(const fei::Vec2& p)
{
	setPosition(p - getSize() / 2.0f);
}

float Rect::getLeft() const
{
	return getPosition().x;
}

float Rect::getRight() const
{
	return getPosition().x + getSize().x;
}

float Rect::getTop() const
{
	return getPosition().y + getSize().y;
}

float Rect::getBottom() const
{
	return getPosition().y;
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
	_pos.zoom(scale);
	_size.zoom(scale);
}

void Rect::zoom(const fei::Vec2& v)
{
	_pos.zoom(v);
	_size.zoom(v);
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
	if (getSize().x < 0) {
		_pos.x += _size.x;
		_size.x *= -1.0f;
	}
	if (getSize().y < 0) {
		_pos.y += _size.y;
		_size.y *= -1.0f;
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
	auto pos = getPosition();
	auto size = getSize();
	auto rt = pos + size;
	return ((getPosition().x - pt.x) * (rt.x - pt.x) <= 0) && ((pos.y - pt.y) * (rt.y - pt.y) <= 0);
}

bool Rect::collideSegment(fei::Vec2& pt, const fei::Segment& seg) const
{
	fei::Vec2 tmp;
	auto ans = seg.b;
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
	auto pos = getPosition();
	auto size = getSize();
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
	auto size = getSize();
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
