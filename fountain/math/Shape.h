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
	bool collide(Shape* other);
	virtual float* getDataPtr() = 0;
	virtual int getDataSize() = 0;
private:
	bool _isSolid;
	Type shapeType;
};

}

#endif
