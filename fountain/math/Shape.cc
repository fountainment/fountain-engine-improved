#include "math/Shape.h"

#include "base/stringUtil.h"

using fei::Shape;

Shape::Shape()
: _isSolid(true),
  _shapeType(Type::POLYGON)
{
}

Shape::~Shape()
{
}

const std::string Shape::dumpString() const
{
	std::string ret;
	int ds = getDataSize();
	ret += fei::strFormat("%d\n", ds);
	auto ptr = getDataPtr();
	for (int i = 0; i < ds; i++) {
		ret += fei::strFormat("%f %f\n", ptr[i * 2] + getPositionX(), ptr[i * 2 + 1] + getPositionY());
	}
	return ret;
}

void Shape::print()
{
	std::printf("%s", dumpString().c_str());
}
