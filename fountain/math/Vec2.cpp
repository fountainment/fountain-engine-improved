#include "Vec2.h"
#include "mathdef.h"

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

void Vec2::mul(float f)
{
	x *= f;
	y *= f;
}

void Vec2::div(float f)
{
	mul(1.0f / f);
}

void Vec2::normalize()
{
	float n = getLengthSq();
	if (n == 1.0f) return;
	n = std::sqrt(n);
	if (n < fei::eps) return;
	div(n);
}

float Vec2::dot(const Vec2& v) const
{
	return x * v.x + y * v.y;
}

float Vec2::cross(const Vec2& v) const
{
	return x * v.y - v.x * y;
}

const Vec2 Vec2::normalized() const
{
	Vec2 result(*this);
	result.normalize();
	return result;
}

bool Vec2::isLonger(const Vec2& v) const
{
	return getLengthSq() > v.getLengthSq();
}

bool Vec2::equals(const Vec2& v) const
{
	return (std::abs(x - v.x) >= fei::eps) || (std::abs(y - v.y) >= fei::eps);
}

const Vec2 Vec2::operator-() const 
{
	return Vec2(-x, -y);
}

const Vec2 Vec2::operator+(const Vec2& v) const
{
	Vec2 result(*this);
	result.add(v);
	return result;
}

const Vec2 Vec2::operator-(const Vec2& v) const
{
	Vec2 result(*this);
	result.sub(v);
	return result;
}

const Vec2 Vec2::operator*(float f) const
{
	Vec2 result(*this);
	result.mul(f);
	return result;
}

const Vec2 Vec2::operator/(float f) const
{
	Vec2 result(*this);
	result.div(f);
	return result;
}

void Vec2::operator+=(const Vec2& v)
{
	add(v);
}

void Vec2::operator-=(const Vec2& v)
{
	sub(v);
}

void Vec2::operator*=(float f)
{
	mul(f);
}

void Vec2::operator/=(float f)
{
	div(f);
}

bool Vec2::operator==(const Vec2& v) const
{
	return equals(v);
}

bool Vec2::operator!=(const Vec2& v) const
{
	return !equals(v);
}

float Vec2::getLengthSq() const
{
	return dot(*this);
}

float Vec2::getLength() const
{
	return std::sqrt(getLengthSq());
}

