#include "Polygon.h"

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

void Polygon::pushPoint(const Vec2& p)
{
	data.push_back(p);
}