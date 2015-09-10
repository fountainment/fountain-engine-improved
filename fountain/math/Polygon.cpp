#include "Polygon.h"
#include "math/mathdef.h"

using fei::Polygon;

int Polygon::getDataSize() const
{
	return data.size();
}

const float* Polygon::getDataPtr() const
{
	if (!data.empty()) {
		return &data[0].x;
	}
	return nullptr;
}

void Polygon::pushPoint(const fei::Vec2& p)
{
	data.push_back(p);
}

const Polygon Polygon::makeRegularPolygon(int edgeNum, float radius)
{
	Polygon polygon;
	for (int i = 0; i < edgeNum; i++) {
		float angle = 2.0 * fei::pi / edgeNum * i;
		polygon.pushPoint(fei::Vec2(std::cos(angle), std::sin(angle)));
	}
	return polygon;
}
