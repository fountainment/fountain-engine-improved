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

	void setVertex(int index, const Vec2& p);
	const Vec2 getVertex(int index) const;
	void insertVertex(const Vec2& p, int index);

	int collideVertex(const Vec2& p, float radius) const;

	const std::vector<Vec2> getDataVector() const;

	static const Polygon makeRegularPolygon(int edgeNum, float radius, float offset = 0.0f);

protected:
	std::vector<Vec2> data;
};

}

#endif
