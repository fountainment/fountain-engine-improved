#include "Vec3.h"

using fei::Vec3;

Vec3::Vec3(float xyz)
{
	x = xyz;
	y = xyz;
	z = xyz;
}

Vec3::Vec3(float xx, float yy, float zz)
{
	x = xx;
	y = yy;
	z = zz;
}

Vec3::Vec3(const Vec2& v, float zz)
{
	x = v.x;
	y = v.y;
	z = zz;
}