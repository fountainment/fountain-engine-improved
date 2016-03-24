#ifndef _FEI_SHAPE_H_
#define _FEI_SHAPE_H_

#include "base/basedef.h"
#include "base/NodeBase.h"
#include "math/Vec2.h"

namespace fei {

class Shape : public NodeBase
{
public:
	enum class Type {
		POLYGON = 1,
		CIRCLE = 2,
		RECT = 3,
		SEGMENT = 4
	};

	Shape();
	virtual ~Shape();

	virtual bool collidePoint(const Vec2& p) const = 0;
	virtual bool collide(const Shape* other) const = 0;

	virtual const float* getDataPtr() const = 0;
	virtual int getDataSize() const = 0;

	void setSolid(bool solid);
	bool isSolid() const;

	Type getType() const;
	void setType(Type shapeType);

	void print();

private:
	bool _isSolid;
	Type _shapeType;
};

} // namespace fei

inline void fei::Shape::setSolid(bool solid)
{
	_isSolid = solid;
}

inline bool fei::Shape::isSolid() const
{
	return _isSolid;
}

inline void fei::Shape::setType(fei::Shape::Type shapeType)
{
	_shapeType = shapeType;
}

inline fei::Shape::Type fei::Shape::getType() const
{
	return _shapeType;
}

#endif // _FEI_SHAPE_H_
