#include "Body.h"
#include "physics/Physics.h"

using fei::Body;

Body::Body()
: body(nullptr),
  type(Type::DYNAMIC)
{
}

Body::Body(b2Body* b2bd, Type tp)
: body(b2bd),
  type(tp)
{
	body->SetUserData(this);
}

void Body::setBody(b2Body* b2bd)
{
	body = b2bd;
	body->SetUserData(this);
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

void Body::setSpeed(const fei::Vec2& sp)
{
	auto vec = Physics::getInstance()->renderToPhysics(sp);
	body->SetLinearVelocity(b2Vec2(vec.x, vec.y));
}

b2Body* Body::getB2Body() const
{
	return body;
}

b2Fixture* Body::createFixture(const fei::Shape* shape)
{
	float density = 1.0f;
	if (Type::STATIC == type) {
		density = 0.0f;
	}
	auto *b2shape = Physics::ShapeToB2Shape(shape);
	auto fixture = body->CreateFixture(b2shape, density);
	if (b2shape) {
		delete b2shape;
	}
	return fixture;
}

const std::vector<b2Fixture*> Body::createFixture(const std::vector<fei::Shape*>& shapeList)
{
	std::vector<b2Fixture*> result;
	for (auto shape : shapeList) {
		result.push_back(createFixture(shape));
	}
	return result;
}

const std::vector<b2Fixture*> Body::createFixture(const fei::Polygon& poly)
{
	return createFixture(poly.box2dDecomposition());
}

const std::vector<b2Fixture*> Body::createFixture(const std::vector<fei::Polygon>& polyList)
{
	std::vector<b2Fixture*> result;
	for (auto poly : polyList) {
		result.push_back(createFixture(&poly));
	}
	return result;
}

b2Fixture* Body::createFixture(const b2FixtureDef& fixDef)
{
	return body->CreateFixture(&fixDef);
}

void Body::destroyFixture(b2Fixture* fixture)
{
	body->DestroyFixture(fixture);
}

void Body::destroyFixture(const std::vector<b2Fixture*>& fixtures)
{
	for (auto fixture : fixtures) {
		destroyFixture(fixture);
	}
}
