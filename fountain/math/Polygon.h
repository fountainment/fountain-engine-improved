#if !defined(_FEI_POLYGON_H_)
#define _FEI_POLYGON_H_

#include "base/basedef.h"
#include "math/Vec2.h"

namespace fei {

class Polygon
{
public:
	int getSize() const;
	const float* getData() const;
	void pushPoint(const Vec2& p);

private:
	std::vector<Vec2> data;
};

}

#endif