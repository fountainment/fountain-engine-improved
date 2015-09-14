#if !defined(_FEI_SEGMENT_H_)
#define _FEI_SEGMENT_H_

#include "math/Vec2.h"

namespace fei {

class Segment
{
public:
	Segment();
	Segment(Vec2 aa, Vec2 bb);

	const Vec2 getVector() const;

	Vec2 a;
	Vec2 b;
};

}

#endif

