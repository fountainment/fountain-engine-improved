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
	float dot(const Vec2& v) const;
	bool isLonger(const Vec2& v) const;

	inline const Vec2 operator-() const;
	inline bool operator!=(const Vec2& v) const;

	float getLengthSq() const;
	float getLength() const;
};

}

#endif
