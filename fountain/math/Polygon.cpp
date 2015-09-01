#include "Polygon.h"

using fei::Polygon;

int Polygon::getSize() const
{
	return data.size();
}

const float* Polygon::getData() const
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