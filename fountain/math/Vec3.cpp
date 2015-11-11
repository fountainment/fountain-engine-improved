#include "math/Vec3.h"

using fei::Vec3;

Vec3::Vec3()
: x(0.0f),
  y(0.0f),
  z(0.0f)
{
}

Vec3::Vec3(float xyz)
: x(xyz),
  y(xyz),
  z(xyz)
{
}

Vec3::Vec3(float xx, float yy, float zz)
: x(xx),
  y(yy),
  z(zz)
{
}

Vec3::Vec3(const fei::Vec2& v, float zz)
: x(v.x),
  y(v.y),
  z(zz)
{
}

const Vec3 Vec3::ZERO = Vec3(0.0f);
