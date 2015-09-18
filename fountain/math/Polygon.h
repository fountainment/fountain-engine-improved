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
	void pushVertex(const Vec2& p);
	void clearVertex();

	void setVertex(int index, const Vec2& p);
	const Vec2 getVertex(int index) const;
	const Vec2 getVector(int index) const;
	const Segment getSegment(int index) const;

	int indexNormalize(int index) const;
	float getArea() const;
	bool isCCW() const;

	void insertVertex(const Vec2& p, int index);
	void deleteVertex(int index);
	void moveVertices(const Vec2& v);
	void reverseVertices();
	const std::vector<Polygon> cut(int index) const;
	const std::vector<Polygon> cut(int a, int b) const;

	int closestWhichSegment(const Vec2& p) const;
	int onWhichSegment(const Vec2& p) const;
	int collideVertex(const Vec2& p, float radius) const;
	const std::vector<Vec2> collideRay(const Vec2& src, const Vec2& drct) const;

	const std::vector<Vec2> getDataVector() const;
	void setDataVector(const std::vector<Vec2>& v);

	void normalize();
	const Polygon normalized() const;

	bool isValid() const;
	bool isConcaveVertex(int index) const;
	int getOneConcaveVertex() const;
	int getBestCutVertexIndex(int index) const; 
	std::vector<int> getVisibleVerticesIndex(int index) const; 
	bool isConvex() const;
	
	const std::vector<Polygon> convexDecomposition() const;
	const std::vector<Polygon> box2dDecomposition() const;

	static const Polygon makeRegularPolygon(int edgeNum, float radius, float offset = 0.0f);

private:
	std::vector<Vec2> data;
};

}

inline int fei::Polygon::indexNormalize(int index) const
{
	int sz = (int)data.size();
	return ((index % sz) + sz) % sz;
}

inline void fei::Polygon::setVertex(int index, const fei::Vec2& p)
{
	//TODO: assertion
	data[index] = p;
}

inline const fei::Vec2 fei::Polygon::getVertex(int index) const
{
	//TODO: assertion
	return data[index];
}

inline const fei::Vec2 fei::Polygon::getVector(int index) const
{
	//TODO: assertion
	return data[indexNormalize(index + 1)] - data[index];
}

inline const fei::Segment fei::Polygon::getSegment(int index) const
{
	//TODO: assertion
	return fei::Segment(data[index], data[indexNormalize(index + 1)]);
}

#endif

