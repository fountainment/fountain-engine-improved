#include "Shape.h"

using fei::Shape;

Shape::Shape()
: _isSolid(true),
  shapeType(Type::CIRCLE)
{
}

Shape::~Shape()
{
}

bool Shape::collide(const Shape* other)
{
	return false;
}
