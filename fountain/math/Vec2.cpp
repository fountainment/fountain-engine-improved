#include "math/Vec2.h"

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

