#include "Body.h"
#include "physics/Physics.h"

using fei::Body;

Body::Body()
: body(nullptr),
  type(Type::Dynamic)
{
}

Body::Body(b2Body* b2bd, Type tp)
: body(b2bd),
  type(tp)
{
}

void Body::setBody(b2Body* b2bd)
{
	body = b2bd;
}

const fei::Vec2 Body::getPosition() const
{
	auto b2v = body->GetPosition();
	auto vec = fei::Vec2(b2v.x, b2v.y);
	return Physics::getInstance()->physicsToRender(vec);
}

float Body::getAngle() const
{
	return body->GetAngle();
}