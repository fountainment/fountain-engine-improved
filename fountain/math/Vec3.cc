#include "math/Vec3.h"

using fei::Vec3;

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
const Vec3 Vec3::ONE = Vec3(1.0f);
const Vec3 Vec3::XUP = Vec3(1.0f, 0.0f, 0.0f);
const Vec3 Vec3::XDOWN = Vec3(-1.0f, 0.0f, 0.0f);
const Vec3 Vec3::YUP = Vec3(0.0f, 1.0f, 0.0f);
const Vec3 Vec3::YDOWN = Vec3(0.0f, -1.0f, 0.0f);
const Vec3 Vec3::ZUP = Vec3(0.0f, 0.0f, 1.0f);
const Vec3 Vec3::ZDOWN = Vec3(0.0f, 0.0f, -1.0f);
