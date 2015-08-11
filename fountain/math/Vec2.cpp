#include "Vec2.h"
#include <cmath>

using fei::Vec2;

Vec2::Vec2()
: x(0.0f), y(0.0f)
{
}

Vec2::Vec2(float xy)
: x(xy), y(xy)
{
}

Vec2::Vec2(float xx, float yy)
: x(xx), y(yy)
{
}

void Vec2::set(float xx, float yy)
{
	x = xx;
	y = yy;
}

void Vec2::add(const Vec2& v)
{
	x += v.x;
	y += v.y;
}

void Vec2::sub(const Vec2& v)
{
	x -= v.x;
	y -= v.y;
}

float Vec2::dot(const Vec2& v) const
{
	return x * v.x + y * v.y;
}

bool Vec2::isLonger(const Vec2& v) const
{
	return getLengthSq() > v.getLengthSq();
}

const Vec2 Vec2::operator-() const 
{
	return Vec2(-x, -y);
}

bool Vec2::operator!=(const Vec2& v) const
{
	return x != v.x || y != v.y;
}

float Vec2::getLengthSq() const
{
	return dot(*this);
}

float Vec2::getLength() const
{
	return std::sqrt(dot(*this));
}

