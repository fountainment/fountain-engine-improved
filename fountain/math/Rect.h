#ifndef _FEI_RECT_H_
#define _FEI_RECT_H_

#include "base/basedef.h"
#include "math/Segment.h"
#include "math/Shape.h"
#include "math/Vec2.h"

namespace fei {

class Rect : public Shape
{
public:
	Rect();
	Rect(const Vec2& sz);
	Rect(float x, float y, float w, float h);
	Rect(const Vec2& pos, const Vec2& sz);

	const Vec2 getCenter() const;
	void setCenter(const Vec2& p);

	const Vec2 getSize() const;
	float getSizeX() const;
	float getSizeY() const;

	void setSize(const Vec2& sz);
	void setSizeX(float x);
	void setSizeY(float y);

	float getLeft() const;
	float getRight() const;
	float getBottom() const;
	float getTop() const;

	void setLeft(float left);
	void setRight(float right);
	void setBottom(float bottom);
	void setTop(float top);

	const Vec2 getLB() const;
	const Vec2 getLT() const;
	const Vec2 getRB() const;
	const Vec2 getRT() const;

	void setLB(const Vec2& lb);
	void setLT(const Vec2& lt);
	void setRB(const Vec2& rb);
	void setRT(const Vec2& rt);

	const Segment getLeftSegment() const;
	const Segment getRightSegment() const;
	const Segment getTopSegment() const;
	const Segment getBottomSegment() const;
	const std::vector<Segment> getAllSegments() const;

	void mergeRect(const Rect& rect);

	void zoom(float scale);
	void zoom(const Vec2& v);
	const Rect zoomed(float scale) const;
	const Rect zoomed(const Vec2& v) const;
	void normalize();

	virtual bool collide(const Shape* other) const override;

	virtual bool collidePoint(const Vec2& pt) const override;

	bool collideSegment(Vec2& pt, const Segment& seg) const;

	bool collideRect(const Rect& rct) const;

	void getStripCoord(float* coord) const;

	const float* getDataPtr() const override;
	int getDataSize() const override;

private:
	Vec2 _size;
};

} // namespace fei

inline const fei::Vec2 fei::Rect::getSize() const
{
	return _size;
}

inline float fei::Rect::getSizeX() const
{
	return _size.x;
}

inline float fei::Rect::getSizeY() const
{
	return _size.y;
}

inline void fei::Rect::setSize(const fei::Vec2& sz)
{
	_size = sz;
}

inline void fei::Rect::setSizeX(float x)
{
	_size.x = x;
}

inline void fei::Rect::setSizeY(float y)
{
	_size.y = y;
}

inline float fei::Rect::getLeft() const
{
	return getPositionX();
}

inline float fei::Rect::getRight() const
{
	return getPositionX() + getSizeX();
}

inline float fei::Rect::getTop() const
{
	return getPositionY() + getSizeY();
}

inline float fei::Rect::getBottom() const
{
	return getPositionY();
}

inline void fei::Rect::setLeft(float left)
{
	setPositionX(left);
}

inline void fei::Rect::setRight(float right)
{
	setPositionX(right - getSizeX());
}

inline void fei::Rect::setBottom(float bottom)
{
	setPositionY(bottom);
}

inline void fei::Rect::setTop(float top)
{
	setPositionY(top - getSizeY());
}

inline const fei::Vec2 fei::Rect::getLB() const
{
	return fei::Vec2(getLeft(), getBottom());
}

inline const fei::Vec2 fei::Rect::getLT() const
{
	return fei::Vec2(getLeft(), getTop());
}

inline const fei::Vec2 fei::Rect::getRB() const
{
	return fei::Vec2(getRight(), getBottom());
}

inline const fei::Vec2 fei::Rect::getRT() const
{
	return fei::Vec2(getRight(), getTop());
}

inline void fei::Rect::setLB(const Vec2& lb)
{
	setLeft(lb.x);
	setBottom(lb.y);
}

inline void fei::Rect::setLT(const Vec2& lt)
{
	setLeft(lt.x);
	setTop(lt.y);
}

inline void fei::Rect::setRB(const Vec2& rb)
{
	setRight(rb.x);
	setBottom(rb.y);
}

inline void fei::Rect::setRT(const Vec2& rt)
{
	setRight(rt.x);
	setTop(rt.y);
}

inline const fei::Segment fei::Rect::getLeftSegment() const
{
	return fei::Segment(getLB(), getLT());
}

inline const fei::Segment fei::Rect::getRightSegment() const
{
	return fei::Segment(getRB(), getRT());
}

inline const fei::Segment fei::Rect::getTopSegment() const
{
	return fei::Segment(getLT(), getRT());
}

inline const fei::Segment fei::Rect::getBottomSegment() const
{
	return fei::Segment(getLB(), getRB());
}

#endif // _FEI_RECT_H_
