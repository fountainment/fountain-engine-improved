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

void Vec2::zoom(float scale)
{
	mul(scale);
}

void Vec2::zoom(const Vec2& v)
{
	x *= v.x;
	y *= v.y;
}

void Vec2::rotate(float degree)
{
	double rad = fei::D2R(degree);
	double s = std::sin(rad);
	double c = std::cos(rad);
	double xx = x * c - y * s;
	double yy = x * s + y * c;
	set((float)xx, (float)yy);
}

const Vec2 Vec2::zoomed(float scale) const
{
	Vec2 result(*this);
	result.zoom(scale);
	return result;
}

const Vec2 Vec2::zoomed(const Vec2& v) const
{
	Vec2 result(*this);
	result.zoom(v);
	return result;
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

const Vec2 Vec2::reciprocal() const
{
	return fei::Vec2(1.0f / x, 1.0f / y);
}

const Vec2 Vec2::rotated(float degree) const
{
	auto vec = *this;
	vec.rotate(degree);
	return vec;
}

bool Vec2::isLonger(const Vec2& v) const
{
	return getLengthSq() > v.getLengthSq();
}

bool Vec2::equals(const Vec2& v) const
{
	return (std::abs(x - v.x) >= fei::eps) || (std::abs(y - v.y) >= fei::eps);
}

int Vec2::getQuadrantIndex() const
{
	if (x >= 0 && y >= 0) return 0;
	if (x <= 0 && y >= 0) return 1;
	if (x <= 0 && y <= 0) return 2;
	return 3;
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

float Vec2::getAngle() const
{
	//TODO: need optimization
	if (std::abs(x) < fei::eps) {
		if (std::abs(y) < fei::eps || y > 0) {
			return 0.0f;
		} else {
			return 180.0f;
		}
	}
	float ans = std::atan(y / x);
	if (x >= 0) ans += (float)fei::pi * 1.5f;
	else ans += (float)fei::pi * 0.5f;
	ans *= 180.0f / (float)fei::pi;
	return ans;
}

const Vec2 Vec2::ZERO  = Vec2(0.0f);
const Vec2 Vec2::UP    = Vec2(0.0f, 1.0f);
const Vec2 Vec2::DOWN  = Vec2(0.0f, -1.0f);
const Vec2 Vec2::LEFT  = Vec2(-1.0f, 0.0f);
const Vec2 Vec2::RIGHT = Vec2(1.0f, 0.0f);

