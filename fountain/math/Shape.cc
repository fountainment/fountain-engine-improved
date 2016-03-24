#include "math/Shape.h"

using fei::Shape;

Shape::Shape()
: _isSolid(true),
  _shapeType(Type::POLYGON)
{
}

Shape::~Shape()
{
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
