#include "math/Polygon.h"

#include "math/mathdef.h"

using fei::Polygon;

int fei::Polygon::getDataSize() const
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

float Polygon::getArea() const
{
	float area = 0.0f;
	if (!isValid()) {
		return area;
	}
	auto lastVec = getVertex(1) - getVertex(0);
	for (int i = 2; i < (int)data.size(); i++) {
		auto curVec = getVertex(i) - getVertex(0);
		area += lastVec.cross(curVec);
		lastVec = curVec;
	}
	area *= 0.5f;
	return area;
}

bool Polygon::isCCW() const
{
	return getArea() > 0.0f;
}

void Polygon::setVertices(int vertexNumber, float* dataPtr)
{
	data.resize(vertexNumber);
	for (int i = 0; i < vertexNumber; i++) {
		data[i] = fei::Vec2(dataPtr[i << 1], dataPtr[i << 1 | 1]);
	}
}

void Polygon::insertVertex(const fei::Vec2& p, int index)
{
	//TODO: assertion
	data.insert(data.begin() + index, p);
}

void Polygon::deleteVertex(int index)
{
	//TODO: assertion
	data.erase(data.begin() + index);
}

void Polygon::moveVertices(const fei::Vec2& v)
{
	for (auto& vertex : data) {
		vertex.add(v);
	}
}

void Polygon::reverseVertices()
{
	std::reverse(data.begin(), data.end());
}

void Polygon::zoom(float f)
{
	for (auto& vertex : data) {
		vertex.zoom(f);
	}
}

const std::vector<Polygon> Polygon::cut(int index) const
{
	std::vector<Polygon> result;
	int best = getBestCutVertexIndex(index);
	if (best != -1) {
		result = cut(index, best);
	} else {
		int prev = indexNormalize(index - 1);
		bool isConcave = isConcaveVertex(index);
		auto leftVec = -getVector(prev);
		auto rightVec = getVector(index);
		auto middleVec = (leftVec.normalized() + rightVec.normalized()).normalized();
		if (isConcave) {
			middleVec *= -1.0f;
		}
		auto pl = collideRay(getVertex(index), middleVec);
		if (!pl.empty()) {
			Polygon polyCopy(*this);
			int segIndex = polyCopy.closestWhichSegment(pl[0]);
			int insertLoc = polyCopy.indexNormalize(segIndex + 1);
			polyCopy.insertVertex(pl[0], insertLoc);
			if (insertLoc <= index) {
				index = polyCopy.indexNormalize(index + 1);
			}
			result = polyCopy.cut(index, insertLoc);
		}
	}
	return result;
}

const std::vector<Polygon> Polygon::cut(int a, int b) const
{
	int curVertex;
	std::vector<Polygon> result;
	Polygon tmpPoly;

	curVertex = b;
	tmpPoly.pushVertex(getVertex(a));
	do {
		tmpPoly.pushVertex(getVertex(curVertex));
		curVertex = indexNormalize(curVertex + 1);
	} while(curVertex != a);
	result.push_back(tmpPoly);

	tmpPoly.clearVertex();

	curVertex = a;
	tmpPoly.pushVertex(getVertex(b));
	do {
		tmpPoly.pushVertex(getVertex(curVertex));
		curVertex = indexNormalize(curVertex + 1);
	} while(curVertex != b);
	result.push_back(tmpPoly);

	return result;
}

int Polygon::closestWhichSegment(const fei::Vec2& p) const
{
	int ans = -1;
	float minR = 1e32f;
	for (int i = 0; i < (int)data.size(); i++) {
		auto seg = getSegment(i);
		float curRatio = std::abs(((p - seg.a).getLength() + (p - seg.b).getLength()) / seg.getLength() - 1.0f);
		if (curRatio <= minR) {
			minR = curRatio;
			ans = i;
		}
	}
	return ans;
}

int Polygon::onWhichSegment(const fei::Vec2& p) const
{
	for (int i = 0; i < (int)data.size(); i++) {
		if (getSegment(i).collidePoint(p)) {
			return i;
		}
	}
	return -1;
}

int Polygon::collideVertex(const fei::Vec2& p, float radius) const
{
	float rSq = radius * radius;
	for (int i = 0; i < (int)data.size(); i++) {
		if (((data[i] + pos) - p).getLengthSq() <= rSq) {
			return i;
		}
	}
	return -1;
}

static bool cmpLength(const fei::Vec2& a, const fei::Vec2& b)
{
	return a.getLengthSq() < b.getLengthSq();
}

const std::vector<fei::Vec2> Polygon::rawCollideRay(const fei::Vec2& src, const fei::Vec2& drct) const
{
	std::vector<fei::Vec2> result;
	for (int i = 0; i < (int)data.size(); i++) {
		auto seg = getSegment(i);
		fei::Vec2 tmp;
		if (seg.collideRay(tmp, src, drct)) {
			result.push_back(tmp - src);
		}
	}
	return result;
}

const std::vector<fei::Vec2> Polygon::collideRay(const fei::Vec2& src, const fei::Vec2& drct) const
{
	std::vector<fei::Vec2> result = rawCollideRay(src, drct);
	std::vector<fei::Vec2> uniqueResult;
	std::sort(result.begin(), result.end(), cmpLength);
	for (int i = 0; i < (int)result.size(); i++) {
		if (result[i].getLengthSq() < 0.01f) continue;
		if (i == 0 || result[i] != result[i - 1]) {
			uniqueResult.push_back(result[i] + src);
		}
	}
	return uniqueResult;
}

void Polygon::normalize()
{
	std::vector<fei::Vec2> nData;
	int sz = data.size();
	for (int i = 0; i < sz; i++) {
		int prev = indexNormalize(i - 1);
		if ((getVector(prev).getLengthSq() >= 0.01f)
		   && (getVector(i).normalized() != getVector(prev).normalized())) {
			nData.push_back(getVertex(i));
		}
	}
	setDataVector(nData);
	if (!isCCW()) {
		reverseVertices();
	}
}

const Polygon Polygon::normalized() const
{
	Polygon poly(*this);
	poly.normalize();
	return poly;
}

bool Polygon::isConcaveVertex(int index) const
{
	//TODO: assertion
	int prevIndex = indexNormalize(index - 1);
	auto prev = getVector(prevIndex);
	auto cur = getVector(index);
	float cp = prev.cross(cur);
	return cp < 0;
}

int Polygon::getOneConcaveVertex() const
{
	int sz = (int)data.size();
	for (int i = 0; i < sz; i++) {
		if (isConcaveVertex(i)) {
			return i;
		}
	}
	return -1;
}

typedef struct CutStruct
{
	CutStruct(const Polygon* pp, int ii, int xx)
	: poly(pp), index(ii), x(xx)
	{
	}

	bool operator>(const CutStruct& rhs) const
	{
		int ai = x;
		int bi = rhs.x;
		int sz = poly->getDataSize();
		bool aConcave = poly->isConcaveVertex(ai);
		bool bConcave = poly->isConcaveVertex(bi);
		if (aConcave == bConcave) {
			int disIA = std::abs(index - ai);
			if (sz - disIA < disIA) {
				disIA = sz - disIA;
			}
			int disIB = std::abs(index - bi);
			if (sz - disIB < disIB) {
				disIB = sz - disIB;
			}
			return disIA > disIB;
		} else {
			return aConcave;
		}
	}

	const Polygon* poly;
	int index;
	int x;
} PolyCutPair;

int Polygon::getBestCutVertexIndex(int index) const
{
	int ans = -1;
	auto iList = getVisibleVerticesIndex(index);

	std::vector<PolyCutPair> uList;
	if (isConcaveVertex(index)) {
		auto left = getSegment(index);
		auto right = getSegment(indexNormalize(index - 1));
		right.swapAB();
		left.b = left.a - left.getVector();
		right.b = right.a - right.getVector();
		for (int vertex : iList) {
			auto p = getVertex(vertex);
			if (left.onLeftOrRight(p) == 1
				 && right.onLeftOrRight(p) == -1) {
				auto pl = collideRay(getVertex(index), p - getVertex(index));
				if (pl.size() == 0 || pl[0] == p) {
					uList.push_back(PolyCutPair(this, index, vertex));
				}
			}
		}
	} else {
		for (int vertex : iList) {
			uList.push_back(PolyCutPair(this, index, vertex));
		}
	}
	if (!uList.empty()) {
		auto maxPcp = uList[0];
		for (auto& pcp : uList) {
			if (pcp > maxPcp) {
				maxPcp = pcp;
			}
		}
		ans = maxPcp.x;
	}
	return ans;
}

std::vector<int> Polygon::getVisibleVerticesIndex(int index) const
{
	std::vector<int> result;
	int left = indexNormalize(index - 1);
	int right = indexNormalize(index + 1);
	bool isConcave = isConcaveVertex(index);
	auto leftSeg = getSegment(left);
	auto rightSeg = getSegment(index);
	leftSeg.swapAB();
	if (isConcave) {
		auto tmp = leftSeg;
		leftSeg = rightSeg;
		rightSeg = tmp;
	}
	for (int i = 0; i < (int)data.size(); i++) {
		auto p = getVertex(i);
		if (i == index || i == left || i == right ||
		   (leftSeg.onLeftOrRight(p) == 1 && rightSeg.onLeftOrRight(p) == -1) == isConcave) {
			continue;
		}
		auto vertexList = collideRay(getVertex(index), p - getVertex(index));
		if (vertexList.size() == 0 || vertexList[0] == p) {
			result.push_back(i);
		}
	}
	return result;
}

bool Polygon::isConvex() const
{
	return getOneConcaveVertex() < 0;
}

const std::vector<Polygon> Polygon::convexDecomposition() const
{
	std::vector<Polygon> result;
	std::queue<Polygon> processQueue;
	processQueue.push(normalized());
	while(!processQueue.empty()) {
		auto currentPoly = processQueue.front();
		processQueue.pop();
		if (currentPoly.isValid()) {
			int concavePoint = currentPoly.getOneConcaveVertex();
			if (concavePoint == -1) {
				result.push_back(currentPoly);
			} else {
				auto twoPoly = currentPoly.cut(concavePoint);
				for (auto& poly : twoPoly) {
					poly.normalize();
					if (poly.isValid()) {
						processQueue.push(poly);
					}
				}
			}
		}
		if (result.size() > 100 || processQueue.size() > 100) {
			break;
		}
	}
	return result;
}

const std::vector<Polygon> Polygon::box2dDecomposition() const
{
	std::vector<Polygon> result;
	std::queue<Polygon> processQueue;
	auto convexList = convexDecomposition();
	for (auto& poly : convexList) {
		processQueue.push(poly);
	}
	while(!processQueue.empty()) {
		auto currentPoly = processQueue.front();
		processQueue.pop();
		if (currentPoly.isValid()) {
			if (currentPoly.getDataSize() <= 8) {
				result.push_back(currentPoly);
			} else {
				auto twoPoly = currentPoly.cut(0);
				for (auto& poly : twoPoly) {
					poly.normalize();
					if (poly.isValid() && (poly.getArea() > fei::epsf)) {
						processQueue.push(poly);
					}
				}
			}
		}
		if (result.size() > 100 || processQueue.size() > 100) {
			break;
		}
	}
	return result;
}

bool Polygon::collide(const fei::Shape* shape) const
{
	bool result = false;
	switch (shape->getType()) {
	//TODO: implement cases
	//case fei::Shape::Type::CIRCLE:
	//case fei::Shape::Type::POLYGON:
	//case fei::Shape::Type::RECT:
	//case fei::Shape::Type::SEGMENT:
	}
	return result;
}

bool Polygon::collidePoint(const Vec2& p) const
{
	auto points = rawCollideRay(p, fei::Vec2::RIGHT);
	return (points.size() & 1) == 1;
}

const Polygon Polygon::makeRegularPolygon(int edgeNum, float radius, float offset)
{
	Polygon polygon;
	for (int i = 0; i < edgeNum; i++) {
		float angle = (float)(2.0 * fei::pi / edgeNum * i + fei::D2R(offset));
		polygon.pushVertex(fei::Vec2(std::cos(angle), std::sin(angle)) * radius);
	}
	return polygon;
}

