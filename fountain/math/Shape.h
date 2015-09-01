#if !defined(_FEI_SHAPE_H_)
#define _FEI_SHAPE_H_

#include "base/basedef.h"
#include "math/Vec2.h"

namespace fei {

class Shape
{
public:
	enum class Type {
		RECT = 1,
		CIRCLE = 2,
		POLYGON = 3
	};

	Shape();
	virtual ~Shape();

	virtual bool collide(const Shape* other);

	virtual const float* getDataPtr() const = 0;
	virtual int getDataSize() const = 0;

	//TODO: design Shape data storage and render logic

private:
	bool _isSolid;
	Type shapeType;
};

}

#endif
