#include "physics/Body.h"

#include "physics/Physics.h"

using fei::Body;

Body::Body()
: _body(nullptr),
  _type(Type::DYNAMIC)
{
}

Body::Body(b2Body* b2bd, Type tp)
: _body(b2bd),
  _type(tp)
{
	_body->SetUserData(this);
}

Body::~Body()
{
}

void Body::setBody(b2Body* b2bd)
{
	_body = b2bd;
	_body->SetUserData(this);
}

const fei::Vec2 Body::getPosition() const
{
	auto b2v = _body->GetPosition();
	auto vec = fei::Vec2(b2v.x, b2v.y);
	return Physics::getInstance()->physicsToRender(vec);
}

float Body::getAngle() const
{
	return _body->GetAngle();
}

void Body::setSpeed(const fei::Vec2& sp)
{
	auto vec = Physics::getInstance()->renderToPhysics(sp);
	_body->SetLinearVelocity(b2Vec2(vec.x, vec.y));
}

b2Body* Body::getB2Body() const
{
	return _body;
}

b2Fixture* Body::createFixture(const fei::Shape* shape)
{
	float density = 1.0f;
	if (Type::STATIC == _type) {
		density = 0.0f;
	}
	auto *b2shape = Physics::ShapeToB2Shape(shape);
	auto fixture = _body->CreateFixture(b2shape, density);
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
	return _body->CreateFixture(&fixDef);
}

void Body::destroyFixture(b2Fixture* fixture)
{
	_body->DestroyFixture(fixture);
}

void Body::destroyFixture(const std::vector<b2Fixture*>& fixtures)
{
	for (auto fixture : fixtures) {
		destroyFixture(fixture);
	}
}

void Body::beginContact(Body* otherBody)
{
}

bool Body::frameContact(Body* otherBody)
{
	return true;
}

void Body::endContact(Body* otherBody)
{
}
