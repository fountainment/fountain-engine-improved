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

void Polygon::setVertex(int index, const fei::Vec2& p)
{
	//TODO: assertion
	data[index] = p;
}

const fei::Vec2 Polygon::getVertex(int index) const
{
	//TODO: assertion
	return data[index];
}

void Polygon::insertVertex(const fei::Vec2& p, int index)
{
	//TODO: assertion
	data.insert(data.begin() + index, p);
}

int Polygon::collideVertex(const fei::Vec2& p, float radius) const
{
	float rSq = radius * radius;
	for (int i = 0; i < (int)data.size(); i++) {
		if ((data[i] - p).getLengthSq() <= rSq) {
			return i;
		}
	}
	return -1;
}

const std::vector<fei::Vec2> Polygon::getDataVector() const
{
	return data;
}

const Polygon Polygon::makeRegularPolygon(int edgeNum, float radius)
{
	Polygon polygon;
	for (int i = 0; i < edgeNum; i++) {
		float angle = 2.0 * fei::pi / edgeNum * i;
		polygon.pushPoint(fei::Vec2(std::cos(angle), std::sin(angle)) * radius);
	}
	return polygon;
}
