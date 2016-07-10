#ifndef _FEI_SEGMENT_H_
#define _FEI_SEGMENT_H_

#include "math/mathdef.h"
#include "math/Shape.h"
#include "math/Vec2.h"

namespace fei {

class Rect;

class Segment : public Shape
{
public:
	Segment();
	Segment(Vec2 aa, Vec2 bb);

	virtual const float* getDataPtr() const override;
	virtual int getDataSize() const override;

	const Vec2 getVector() const;
	float getLength() const;
	float getLengthSq() const;

	const Rect getRect() const;
	const Vec2 getXInterval() const;
	const Vec2 getYInterval() const;

	void swapAB();

	virtual bool collide(const Shape* shape) const;
	virtual bool collidePoint(const Vec2& p) const;
	bool rectCollidePoint(const Vec2& p) const;
	bool collideSegment(Vec2& pt, const Segment& seg) const;
	bool collideRay(Vec2& pt, const Vec2& src, const Vec2& drct) const;
	int onLeftOrRight(const Vec2& pt) const;

	Vec2 a;
	Vec2 b;
};

} // namespace fei

inline const fei::Vec2 fei::Segment::getVector() const
{
	return b - a;
}

inline float fei::Segment::getLength() const
{
	return getVector().getLength();
}

inline float fei::Segment::getLengthSq() const
{
	return getVector().getLengthSq();
}

inline const fei::Vec2 fei::Segment::getXInterval() const
{
	return a.x < b.x ? fei::Vec2(a.x, b.x) : fei::Vec2(b.x, a.x);
}

inline const fei::Vec2 fei::Segment::getYInterval() const
{
	return a.y < b.y ? fei::Vec2(a.y, b.y) : fei::Vec2(b.y, a.y);
}

inline bool fei::Segment::rectCollidePoint(const fei::Vec2& p) const
{
	float x = (p.x - a.x) * (p.x - b.x);;
	float y = (p.y - a.y) * (p.y - b.y);
	return (x < 0.0f || std::abs(x) < fei::epsf) && (y < 0.0f || std::abs(y) < fei::epsf);
}

inline int fei::Segment::onLeftOrRight(const fei::Vec2& pt) const
{
	double cp = getVector().cross(pt - a);
	if (std::abs(cp) < fei::epsf) {
		return 0;
	}
	return cp>0.0f?-1:1;
}
		  
#endif // _FEI_SEGMENT_H_
