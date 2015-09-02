#if !defined(_FEI_RECT_H_)
#define _FEI_RECT_H_

#include "Vec2.h"
#include "base/NodeBase.h"

namespace fei {

class Rect : public NodeBase
{
public:
	Rect(float x, float y, float w, float h);
	Rect(const Vec2& pos, const Vec2& sz);

	const Vec2 getCenter() const;
	void setCenter(const Vec2& p);
	const Vec2 getSize() const;
	void setSize(const Vec2& sz);

	float getLeft();
	float getRight();
	float getTop();
	float getBottom();

	void zoom(float scale);
	void zoom(const Vec2& v);
	void normalize();

	bool collidePoint(const Vec2& pt) const;

	void getStripCoord(float* coord) const;

private:
	Vec2 size;
};

}

#endif

