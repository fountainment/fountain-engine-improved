#include "physics/Body.h"

#include "physics/Physics.h"

using fei::Body;

Body::Body()
: _body(nullptr),
  _type(Type::DYNAMIC),
  _tag(0),
  _destroyed(false)
{
}

Body::Body(b2Body* b2bd, Type tp)
: _body(b2bd),
  _type(tp),
  _tag(0),
  _destroyed(false)
{
	_body->SetUserData(this);
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

const fei::Vec2 Body::getSpeed()
{
	auto vec = _body->GetLinearVelocity();
	auto ret = Physics::getInstance()->physicsToRender(fei::Vec2(vec.x, vec.y));
	return ret;
}

void Body::setTag(int tag)
{
	_tag = tag;
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
	if (_destroyed) {
		return;
	}
	_body->DestroyFixture(fixture);
}

void Body::destroyFixture(const std::vector<b2Fixture*>& fixtures)
{
	for (auto fixture : fixtures) {
		destroyFixture(fixture);
	}
}

void Body::setCategoryBitsAndMaskBits(uint16 cbits, uint16 mbits)
{
	for (b2Fixture* f = _body->GetFixtureList(); f; f = f->GetNext()) {
		b2Filter fd = f->GetFilterData();
		fd.categoryBits = cbits;
		fd.maskBits = mbits;
		f->SetFilterData(fd);
	}
}

void Body::setGroupIndex(int16 groupIndex)
{
	for (b2Fixture* f = _body->GetFixtureList(); f; f = f->GetNext()) {
		b2Filter fd = f->GetFilterData();
		fd.groupIndex = groupIndex;
		f->SetFilterData(fd);
	}
}

void Body::setCollisionCategory(int category)
{
	uint16 bits = 1 << category;
	setCategoryBitsAndMaskBits(bits, bits);
}

void Body::beginContact(Body* otherBody)
{
	if (_beginContactCallback) {
		_beginContactCallback(otherBody);
	}
}

bool Body::frameContact(Body* otherBody)
{
	bool ret = true;
	if (_frameContactCallback) {
		ret = _frameContactCallback(otherBody);
	}
	return ret;
}

void Body::endContact(Body* otherBody)
{
	if (_endContactCallback) {
		_endContactCallback(otherBody);
	}
}

void Body::setBeginContactCallback(std::function<void(Body*)> callbackFunc)
{
	_beginContactCallback = callbackFunc;
}

void Body::setFrameContactCallback(std::function<bool(Body*)> callbackFunc)
{
	_frameContactCallback = callbackFunc;
}

void Body::setEndContactCallback(std::function<void(Body*)> callbackFunc)
{
	_endContactCallback = callbackFunc;
}
