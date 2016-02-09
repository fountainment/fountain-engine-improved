#if !defined(_FEI_VEC3_H_)
#define _FEI_VEC3_H_

#include "math/Vec2.h"

namespace fei {

class Vec3
{
public:
	Vec3();
	explicit Vec3(float xyz);
	Vec3(float xx, float yy, float zz);
	Vec3(const Vec2& v, float zz);

	void add(const Vec3& v);
	void sub(const Vec3& v);
	void mul(float f);
	void div(float f);

	const Vec3 cross(const Vec3& v) const;

	const Vec3 operator+(const Vec3& v) const;
	const Vec3 operator-(const Vec3& v) const;
	const Vec3 operator*(float f) const;
	const Vec3 operator/(float f) const;

	void operator+=(const Vec3& v);
	void operator-=(const Vec3& v);
	void operator*=(float f);
	void operator/=(float f);

	float x;
	float y;
	float z;

	static const Vec3 ZERO;
};

} // namespace fei

inline void fei::Vec3::add(const fei::Vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

inline void fei::Vec3::sub(const fei::Vec3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
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

inline const fei::Vec3 fei::Vec3::cross(const fei::Vec3& v) const
{
	fei::Vec3 ret;
	ret.x = y * v.z - v.y * z;
	ret.y = -(x * v.z - v.x * y);
	ret.z = x * v.y - v.x * y;
	return ret;
}

inline const fei::Vec3 fei::Vec3::operator+(const fei::Vec3& v) const
{
	fei::Vec3 result(*this);
	result.add(v);
	return result;
}

inline const fei::Vec3 fei::Vec3::operator-(const fei::Vec3& v) const
{
	fei::Vec3 result(*this);
	result.sub(v);
	return result;
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

inline void fei::Vec3::operator+=(const fei::Vec3& v)
{
	add(v);
}

inline void fei::Vec3::operator-=(const fei::Vec3& v)
{
	sub(v);
}

inline void fei::Vec3::operator*=(float f)
{
	mul(f);
}

inline void fei::Vec3::operator/=(float f)
{
	div(f);
}

#endif // _FEI_VEC3_H_
