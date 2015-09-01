#if !defined(_FEI_POLYGON_H_)
#define _FEI_POLYGON_H_

#include "base/basedef.h"
#include "math/Vec2.h"
#include "math/Shape.h"

namespace fei {

class Polygon : public Shape
{
public:
	int getDataSize() const override;
	const float* getDataPtr() const override;
	void pushPoint(const Vec2& p);

private:
	std::vector<Vec2> data;
};

}

#endif
