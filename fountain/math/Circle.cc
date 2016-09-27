#include "math/Circle.h"

#include "base/stringUtil.h"

using fei::Circle;

const std::vector<fei::Vec2> Circle::_data32 = {
fei::Vec2(1.000000f, 0.000000f),
fei::Vec2(0.980785f, 0.195090f),
fei::Vec2(0.923880f, 0.382683f),
fei::Vec2(0.831470f, 0.555570f),
fei::Vec2(0.707107f, 0.707107f),
fei::Vec2(0.555570f, 0.831470f),
fei::Vec2(0.382683f, 0.923880f),
fei::Vec2(0.195090f, 0.980785f),
fei::Vec2(0.000000f, 1.000000f),
fei::Vec2(-0.195090f, 0.980785f),
fei::Vec2(-0.382683f, 0.923880f),
fei::Vec2(-0.555570f, 0.831470f),
fei::Vec2(-0.707107f, 0.707107f),
fei::Vec2(-0.831470f, 0.555570f),
fei::Vec2(-0.923880f, 0.382683f),
fei::Vec2(-0.980785f, 0.195090f),
fei::Vec2(-1.000000f, 0.000000f),
fei::Vec2(-0.980785f, -0.195090f),
fei::Vec2(-0.923880f, -0.382683f),
fei::Vec2(-0.831470f, -0.555570f),
fei::Vec2(-0.707107f, -0.707107f),
fei::Vec2(-0.555570f, -0.831470f),
fei::Vec2(-0.382683f, -0.923880f),
fei::Vec2(-0.195090f, -0.980785f),
fei::Vec2(-0.000000f, -1.000000f),
fei::Vec2(0.195090f, -0.980785f),
fei::Vec2(0.382683f, -0.923880f),
fei::Vec2(0.555570f, -0.831470f),
fei::Vec2(0.707107f, -0.707107f),
fei::Vec2(0.831470f, -0.555570f),
fei::Vec2(0.923880f, -0.382683f),
fei::Vec2(0.980785f, -0.195090f)};

Circle::Circle()
: _radius(1.0f)
{
	setType(fei::Shape::Type::CIRCLE);
}

Circle::Circle(fei::Vec2 origin, float radius)
: _radius(radius)
{
	setPosition(origin);
	setType(fei::Shape::Type::CIRCLE);
}

Circle::Circle(float r)
: _radius(r)
{
	setType(fei::Shape::Type::CIRCLE);
}

int Circle::getDataSize() const
{
	return _data32.size();
}

const float* Circle::getDataPtr() const
{
	if (!_data32.empty()) {
		return &_data32[0].x;
	} else {
		return nullptr;
	}
}

float Circle::getRadius() const
{
	return _radius;
}

void Circle::setRadius(float r)
{
	_radius = r;
}

bool Circle::collide(const fei::Shape* shape) const
{
	bool result = false;
	switch(shape->getType()) {
	case fei::Shape::Type::CIRCLE:
		{
			float sumSq = getRadius() + (static_cast<const Circle*>(shape))->getRadius();
			sumSq *= sumSq;
			float disSq = (getPosition() - shape->getPosition()).getLengthSq();
			if (disSq <= sumSq) {
				result = true;
			}
		}
		break;
	//TODO: implement cases
	case fei::Shape::Type::POLYGON:
	case fei::Shape::Type::RECT:
	case fei::Shape::Type::SEGMENT:
		std::printf("Circle::collide Not Implemented!\n");
		break;
	}
	return result;
}

bool Circle::collidePoint(const fei::Vec2& p) const
{
	return (getPosition() - p).getLengthSq() <= (getRadius() * getRadius());
}

const std::string Circle::dumpString() const
{
	return fei::strFormat("1\n%f %f %f\n", getPositionX(), getPositionY(), getRadius());
}
