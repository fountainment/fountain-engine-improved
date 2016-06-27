#include "sprite/PhysicsSprite.h"

using fei::PhysicsSprite;

PhysicsSprite::PhysicsSprite()
: _body(nullptr)
{
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
	animeUpdate();
	physicsSpriteUpdate();
}
