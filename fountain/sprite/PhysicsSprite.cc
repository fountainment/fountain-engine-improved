#include "sprite/PhysicsSprite.h"

#include "physics/Physics.h"

using fei::PhysicsSprite;

PhysicsSprite::PhysicsSprite()
: _body(nullptr)
{
}

PhysicsSprite::~PhysicsSprite()
{
	destroyBody();
}

void PhysicsSprite::initBody(fei::Body::Type type)
{
	if (!_body) {
		_body = fei::Physics::getInstance()->createBody(getPosition(), type);
	}
}

void PhysicsSprite::destroyBody()
{
	if (_body) {
		fei::Physics::getInstance()->destroyBody(_body);
		_body = nullptr;
	}
}

void PhysicsSprite::physicsSpriteUpdate()
{
	if (getBody()) {
		setPosition(getBody()->getPosition());
		setAngle(getBody()->getAngle());
	}
}

void PhysicsSprite::feiBasicUpdate()
{
	Sprite::feiBasicUpdate();
	physicsSpriteUpdate();
}
