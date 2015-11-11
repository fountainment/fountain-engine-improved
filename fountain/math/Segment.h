#if !defined(_FEI_SEGMENT_H_)
#define _FEI_SEGMENT_H_

#include "math/mathdef.h"
#include "math/Shape.h"
#include "math/Vec2.h"

namespace fei {

class Segment : public Shape
{
public:
	Segment();
	Segment(Vec2 aa, Vec2 bb);

	const float* getDataPtr() const override;
	int getDataSize() const override;

	const Vec2 getVector() const;
	float getLength() const;
	float getLengthSq() const;

	void swapAB();

	bool collidePoint(const Vec2& p) const;
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

inline bool fei::Segment::collidePoint(const Vec2& p) const
{
	return std::abs((a - p).normalized().dot((b - p).normalized()) + 1.0f) < fei::epsf;
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
	if (cp > 0.0f) {
		return -1;
	} else {
		return 1;
	}
}
		  
#endif // _FEI_SEGMENT_H_
