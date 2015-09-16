#if !defined(_FEI_POLYGON_H_)
#define _FEI_POLYGON_H_

#include "base/basedef.h"
#include "math/Vec2.h"
#include "math/Segment.h"
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
	const Vec2 getVector(int index) const;
	const Segment getSegment(int index) const;

	float getArea() const;
	bool isCCW() const;

	void insertVertex(const Vec2& p, int index);
	void deleteVertex(int index);
	void moveVertices(const Vec2& v);
	int collideVertex(const Vec2& p, float radius) const;

	const std::vector<Vec2> getDataVector() const;

	static const Polygon makeRegularPolygon(int edgeNum, float radius, float offset = 0.0f);

private:
	std::vector<Vec2> data;
};

}

#endif
