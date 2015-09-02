#include "Shape.h"

using fei::Shape;

Shape::Shape()
: _isSolid(true),
  shapeType(Type::POLYGON)
{
}

Shape::~Shape()
{
}

bool Shape::collide(const Shape* other)
{
	return false;
}

void Shape::setSolid(bool solid)
{
	_isSolid = solid;
}

bool Shape::isSolid() const
{
	return _isSolid;
}