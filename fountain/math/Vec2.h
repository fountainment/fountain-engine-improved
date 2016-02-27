#if !defined(_FEI_VEC2_H_)
#define _FEI_VEC2_H_

#include "math/mathdef.h"

namespace fei {

class Vec3;

class Vec2
{
public:
	float x;
	float y;

	Vec2() = default;
	explicit Vec2(float xy);
	explicit Vec2(const Vec3& v3);
	Vec2(float xx, float yy);

	void set(float xx, float yy);

	void add(const Vec2& v);
	void sub(const Vec2& v);
	void mul(float f);
	void div(float f);
	void normalize();
	void zoom(float scale);
	void zoom(const Vec2& v);
	void rotate(float degree);
	void round();

	const Vec2 zoomed(float scale) const;
	const Vec2 zoomed(const Vec2& v) const;
	float dot(const Vec2& v) const;
	float cross(const Vec2& v) const;
	const Vec2 normalized() const;
	const Vec2 reciprocal() const;
	const Vec2 rotated(float degree) const;

	bool isLonger(const Vec2& v) const;
	bool equals(const Vec2& v) const;

	int getQuadrantIndex() const;

	const Vec2 operator-() const;
	const Vec2 operator+(const Vec2& v) const;
	const Vec2 operator-(const Vec2& v) const;
	const Vec2 operator*(float f) const;
	const Vec2 operator/(float f) const;

	void operator+=(const Vec2& v);
	void operator-=(const Vec2& v);
	void operator*=(float f);
	void operator/=(float f);
	bool operator==(const Vec2& v) const;
	bool operator!=(const Vec2& v) const;

	float getLengthSq() const;
	float getLength() const;
	float getAngle() const;

	const Vec2 getVerticalVec2() const;

	static const Vec2 ZERO;
	static const Vec2 UP;
	static const Vec2 DOWN;
	static const Vec2 LEFT;
	static const Vec2 RIGHT;
};

const Vec2 collideLine(const Vec2& pa, const Vec2& pb, const Vec2& pc, const Vec2& pd);

} // namespace fei


inline void fei::Vec2::set(float xx, float yy)
{
	x = xx;
	y = yy;
}

inline void fei::Vec2::add(const fei::Vec2& v)
{
	x += v.x;
	y += v.y;
}

inline void fei::Vec2::sub(const fei::Vec2& v)
{
	x -= v.x;
	y -= v.y;
}

inline void fei::Vec2::mul(float f)
{
	x *= f;
	y *= f;
}

inline void fei::Vec2::div(float f)
{
	mul(1.0f / f);
}

inline void fei::Vec2::normalize()
{
	float n = getLengthSq();
	if (n == 1.0f) return;
	n = std::sqrt(n);
	if (n < fei::epsf) return;
	div(n);
}

inline void fei::Vec2::zoom(float scale)
{
	mul(scale);
}

inline void fei::Vec2::zoom(const Vec2& v)
{
	x *= v.x;
	y *= v.y;
}

inline void fei::Vec2::rotate(float degree)
{
	double rad = fei::D2R(degree);
	double s = std::sin(rad);
	double c = std::cos(rad);
	set((float)(x * c - y * s), (float)(x * s + y * c));
}

inline void fei::Vec2::round()
{
	x = (float)((int)(x < 0.0f ? x - 0.5f : x + 0.5f));
	y = (float)((int)(y < 0.0f ? y - 0.5f : y + 0.5f));
}

inline const fei::Vec2 fei::Vec2::zoomed(float scale) const
{
	fei::Vec2 result(*this);
	result.zoom(scale);
	return result;
}

inline const fei::Vec2 fei::Vec2::zoomed(const Vec2& v) const
{
	fei::Vec2 result(*this);
	result.zoom(v);
	return result;
}

inline float fei::Vec2::dot(const fei::Vec2& v) const
{
	return x * v.x + y * v.y;
}

inline float fei::Vec2::cross(const fei::Vec2& v) const
{
	return x * v.y - v.x * y;
}

inline const fei::Vec2 fei::Vec2::normalized() const
{
	fei::Vec2 result(*this);
	result.normalize();
	return result;
}

inline const fei::Vec2 fei::Vec2::reciprocal() const
{
	return fei::Vec2(1.0f / x, 1.0f / y);
}

inline const fei::Vec2 fei::Vec2::rotated(float degree) const
{
	auto vec = *this;
	vec.rotate(degree);
	return vec;
}

inline bool fei::Vec2::isLonger(const fei::Vec2& v) const
{
	return getLengthSq() > v.getLengthSq();
}

inline bool fei::Vec2::equals(const fei::Vec2& v) const
{
	return (std::abs(x - v.x) < fei::epsf) && (std::abs(y - v.y) < fei::epsf);
}

inline int fei::Vec2::getQuadrantIndex() const
{
	if (x >= 0 && y >= 0) return 0;
	if (x <= 0 && y >= 0) return 1;
	if (x <= 0 && y <= 0) return 2;
	return 3;
}

inline const fei::Vec2 fei::Vec2::operator-() const 
{
	return fei::Vec2(-x, -y);
}

inline const fei::Vec2 fei::Vec2::operator+(const fei::Vec2& v) const
{
	fei::Vec2 result(*this);
	result.add(v);
	return result;
}

inline const fei::Vec2 fei::Vec2::operator-(const fei::Vec2& v) const
{
	fei::Vec2 result(*this);
	result.sub(v);
	return result;
}

inline const fei::Vec2 fei::Vec2::operator*(float f) const
{
	fei::Vec2 result(*this);
	result.mul(f);
	return result;
}

inline const fei::Vec2 fei::Vec2::operator/(float f) const
{
	fei::Vec2 result(*this);
	result.div(f);
	return result;
}

inline void fei::Vec2::operator+=(const fei::Vec2& v)
{
	add(v);
}

inline void fei::Vec2::operator-=(const fei::Vec2& v)
{
	sub(v);
}

inline void fei::Vec2::operator*=(float f)
{
	mul(f);
}

inline void fei::Vec2::operator/=(float f)
{
	div(f);
}

inline bool fei::Vec2::operator==(const fei::Vec2& v) const
{
	return equals(v);
}

inline bool fei::Vec2::operator!=(const fei::Vec2& v) const
{
	return !equals(v);
}

inline float fei::Vec2::getLengthSq() const
{
	return dot(*this);
}

inline float fei::Vec2::getLength() const
{
	return std::sqrt(getLengthSq());
}

inline const fei::Vec2 fei::collideLine(const fei::Vec2& pa, const fei::Vec2& pb, const fei::Vec2& pc, const fei::Vec2& pd)
{
	float x = ((pb.x - pa.x) * (pc.x - pd.x) * (pc.y - pa.y) -
	pc.x * (pb.x - pa.x) * (pc.y - pd.y) + pa.x * (pb.y - pa.y) * (pc.x - pd.x)) /
	((pb.y - pa.y) * (pc.x - pd.x) - (pb.x - pa.x) * (pc.y - pd.y));
	float y = ((pb.y - pa.y) * (pc.y - pd.y) * (pc.x - pa.x) - pc.y
	* (pb.y - pa.y) * (pc.x - pd.x) + pa.y * (pb.x - pa.x) * (pc.y - pd.y))
	/ ((pb.x - pa.x) * (pc.y - pd.y) - (pb.y - pa.y) * (pc.x - pd.x));
	return fei::Vec2(x, y);
}

#endif // _FEI_VEC2_H_
