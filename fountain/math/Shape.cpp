#include "math/Shape.h"

using fei::Shape;

Shape::Shape()
: _isSolid(true),
  shapeType(Type::POLYGON)
{
}

Shape::~Shape()
{
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

void Shape::print()
{
	int ds = getDataSize();
	std::printf("%d\n", ds);
	auto ptr = getDataPtr();
	for (int i = 0; i < ds; i++) {
		std::printf("%f %f\n", ptr[i * 2], ptr[i * 2 + 1]);
	}
}
