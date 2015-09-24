#if !defined(_FEI_VEC3_H_)
#define _FEI_VEC3_H_

#include "math/Vec2.h"

namespace fei {

class Vec3
{
public:
	explicit Vec3(float xyz);
	Vec3(float xx, float yy, float zz);
	Vec3(const Vec2& v, float zz);

	void mul(float f);
	void div(float f);

	const Vec3 operator*(float f) const;
	const Vec3 operator/(float f) const;

	float x;
	float y;
	float z;
};

}

inline void fei::Vec3::mul(float f)
{
	x *= f;
	y *= f;
	z *= f;
}

inline void fei::Vec3::div(float f)
{
	mul(1.0f / f);
}

inline const fei::Vec3 fei::Vec3::operator*(float f) const
{
	fei::Vec3 result(*this);
	result.mul(f);
	return result;
}

inline const fei::Vec3 fei::Vec3::operator/(float f) const
{
	fei::Vec3 result(*this);
	result.div(f);
	return result;
}

#endif
