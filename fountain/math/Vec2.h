#if !defined(_FEI_VEC2_H_)
#define _FEI_VEC2_H_

namespace fei {

class Vec2
{
public:
	float x;
	float y;

	Vec2();
	explicit Vec2(float xy);
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

	static const Vec2 ZERO;
	static const Vec2 UP;
	static const Vec2 DOWN;
	static const Vec2 LEFT;
	static const Vec2 RIGHT;
};

}

#endif
