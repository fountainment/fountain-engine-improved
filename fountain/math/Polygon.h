#ifndef _FEI_POLYGON_H_
#define _FEI_POLYGON_H_

#include "base/basedef.h"
#include "math/Segment.h"
#include "math/Shape.h"
#include "math/Vec2.h"

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

	void setVertices(int vertexNumber, float* dataPtr);
	void insertVertex(const Vec2& p, int index);
	void insertVertexOnClosestSegment(const Vec2& p);
	void deleteVertex(int index);
	void moveVertices(const Vec2& v);
	void reverseVertices();

	void zoom(float f);

	const std::vector<Polygon> cut(int index) const;
	const std::vector<Polygon> cut(int a, int b) const;

	int closestWhichSegment(const Vec2& p) const;
	int onWhichSegment(const Vec2& p) const;
	int collideVertex(const Vec2& p, float radius) const;
	const std::vector<Vec2> rawCollideRay(const Vec2& src, const Vec2& drct) const;
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

	virtual bool collide(const Shape* shape) const override;
	virtual bool collidePoint(const Vec2& p) const override;

	static const Polygon makeRegularPolygon(int edgeNum, float radius, float offset = 0.0f);

private:
	std::vector<Vec2> _data;
};

} // namespace fei

inline void fei::Polygon::pushVertex(const fei::Vec2& p)
{
	_data.push_back(p);
}

inline void fei::Polygon::clearVertex()
{
	_data.clear();
}

inline const std::vector<fei::Vec2> fei::Polygon::getDataVector() const
{
	return _data;
}

inline void fei::Polygon::setDataVector(const std::vector<fei::Vec2>& v)
{
	_data = v;
}

inline bool fei::Polygon::isValid() const
{
	return _data.size() >= 3;
}

inline int fei::Polygon::indexNormalize(int index) const
{
	if (_data.empty()) {
		return 0;
	}
	int sz = static_cast<int>(_data.size());
	return ((index % sz) + sz) % sz;
}

inline void fei::Polygon::setVertex(int index, const fei::Vec2& p)
{
	//TODO: assertion
	_data[index] = p;
}

inline const fei::Vec2 fei::Polygon::getVertex(int index) const
{
	//TODO: assertion
	return _data[index];
}

inline const fei::Vec2 fei::Polygon::getVector(int index) const
{
	//TODO: assertion
	return _data[indexNormalize(index + 1)] - _data[index];
}

inline const fei::Segment fei::Polygon::getSegment(int index) const
{
	//TODO: assertion
	return fei::Segment(_data[index], _data[indexNormalize(index + 1)]);
}

#endif // _FEI_POLYGON_H_

