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

bool Shape::collidePoint(const fei::Vec2& p) const
{
	return false;
}

bool Shape::collide(const Shape* other) const
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

Shape::Type Shape::getType() const
{
	return shapeType;
}
