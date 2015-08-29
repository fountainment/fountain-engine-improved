#include "Shape.h"

using fei::Shape;

Shape::Shape()
: _isSolid(true),
  shapeType(Type::CIRCLE)
{
}

bool Shape::collide(Shape * other)
{
	return false;
}
