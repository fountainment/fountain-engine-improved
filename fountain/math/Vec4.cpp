#include "math/Vec4.h"

using fei::Vec4;

Vec4::Vec4(float xyzw)
{
	x = y = w = z = xyzw;
}

Vec4::Vec4(float xx, float yy, float zz, float ww)
{
	x = xx;
	y = yy;
	z = zz;
	w = ww;
}

Vec4::Vec4(const fei::Vec3& xyz, float ww)
{
	x = xyz.x;
	y = xyz.y;
	z = xyz.z;
	w = ww;
}
